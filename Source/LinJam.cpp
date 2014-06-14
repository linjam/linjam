/*
  ==============================================================================

    Linjam.cpp
    Created: 24 May 2014 5:03:01pm
    Author:  me

  ==============================================================================
*/

#include "LinJam.h"
#include "Constants.h"
#include "Trace.h"


/* LinJam public class variables */

LinJamConfig* LinJam::Config ;


/* LinJam private class variables */

audioStreamer*        LinJam::Audio          = nullptr ; // Initialize()
NJClient*             LinJam::Client         = nullptr ; // Initialize()
MainContentComponent* LinJam::Gui            = nullptr ; // Initialize()
bool                  LinJam::IsAudioEnabled = false ;   // Initialize() TODO: use Client->>m_audio_enable instead ?? (issue #11)
File                  LinJam::SessionDir ;               // Initialize()


/* LinJam public class methods */

bool LinJam::Initialize(NJClient* client , MainContentComponent* contentComponent ,
                       const String& args)
{
DEBUG_TRACE_LINJAM_INIT

  Client = client ;
  Gui    = contentComponent ;


// TODO: parse command line args for autojoin (issue #9)


// TODO: load master and local channels from persistent config (issue #6)

/* TODO:  (issue #19)
  audio_config =>
    win =>
      -noaudiocfg
      -jesusonic <path to jesusonic root dir>
    mac =>
      -audiostr device_name[,output_device_name]
    nix =>
      -audiostr "option value [option value ...]"
        ALSA audio options are:
          in hw:0,0    -- set input device
          out hw:0,0   -- set output device
          srate 48000  -- set samplerate
          nch 2        -- set channels
          bps 16       -- set bits/sample
          bsize 2048   -- set blocksize (bytes)
          nblock 16    -- set number of blocks
*/

  // load persistent configuration
  Config = new LinJamConfig() ; if (!Config->sanityCheck()) return false ;

  // configure audio , session directory , and NINJAM client
  if (InitializeAudio())         ConfigureAudio() ;  else return false ;
  if (PrepareSessionDirectory()) ConfigureNinjam() ; else return false ;

  // initialize networking
  JNL::open_socketlib() ;

  return true ;
}

void LinJam::Connect()
{
  Client->Disconnect() ;

  String host         =      Config->currentHost.toString() ;
  String login        =      Config->currentLogin.toString() ;
  String pass         =      Config->currentPass.toString() ;
  bool   is_anonymous = bool(Config->currentIsAnonymous.getValue()) ;

  if (is_anonymous) { login = "anonymous:" + login ; pass  = "" ; }

DEBUG_TRACE_CONNECT

  Gui->statusbarComponent->setStatusL(GUI::CONNECTING_STATUS_TEXT + host) ;
  Client->Connect(host.toRawUTF8() , login.toRawUTF8() , pass.toRawUTF8()) ;
  IsAudioEnabled = true ;
}

void LinJam::Disconnect() { IsAudioEnabled = false ; Client->Disconnect() ; }

void LinJam::Shutdown()
{
  JNL::close_socketlib() ; delete Audio ;
  CleanSessionDir() ; delete Config ;
}


/* NJClient callbacks */

int LinJam::OnLicense(int user32 , char* license_text)
{
  ValueTree server         = Config->getCurrentServerConfig() ;
  bool should_always_agree = server.isValid() &&
                             bool(server.getProperty(STORAGE::AGREE_IDENTIFIER)) ;
  bool is_agreed           = IsAgreed() || should_always_agree ;
  Config->currentIsAgreed  = is_agreed ;

  if (!is_agreed)
  {
    Gui->licenseComponent->setLicenseText(CharPointer_UTF8(license_text)) ;
    Config->setServerConfig() ;
  }

DEBUG_TRACE_LICENSE

  return is_agreed ;
}

void LinJam::OnChatmsg(int user32 , NJClient* instance , const char** parms , int nparms)
{
  if (!parms[0]) return ;

  String chat_type = String(CharPointer_UTF8(parms[CLIENT::CHATMSG_TYPE_IDX])) ;
  String chat_user = String(CharPointer_UTF8(parms[CLIENT::CHATMSG_USER_IDX])).upToFirstOccurrenceOf("@", false , false) ;
  String chat_text = String(CharPointer_UTF8(parms[CLIENT::CHATMSG_MSG_IDX])) ;
  bool is_topic_msg = (!chat_type.compare(CLIENT::CHATMSG_TYPE_TOPIC)) ;
  bool is_bcast_msg = (!chat_type.compare(CLIENT::CHATMSG_TYPE_MSG)) ;
  bool is_priv_msg  = (!chat_type.compare(CLIENT::CHATMSG_TYPE_PRIVMSG)) ;
  bool is_join_msg  = (!chat_type.compare(CLIENT::CHATMSG_TYPE_JOIN)) ;
  bool is_part_msg  = (!chat_type.compare(CLIENT::CHATMSG_TYPE_PART)) ;  

DEBUG_TRACE_CHAT_IN

  if (is_topic_msg)
  {
    if (chat_text.isEmpty()) return ;

    if (chat_user.isEmpty()) chat_text = "Topic is: "                   + chat_text ;
    else                     chat_text = chat_user + " sets topic to: " + chat_text ;
    chat_user = GUI::SERVER_NICK ;

    Gui->chatComponent->setTopic(chat_text) ;
  }
  else if (is_bcast_msg)
    { if (chat_user.isEmpty() || chat_text.isEmpty()) return ; }
  else if (is_priv_msg)
  {
    if (chat_user.isEmpty() || chat_text.isEmpty()) return ;

    chat_user += " (whispers)" ;
  } 
  else if (is_join_msg || is_part_msg)
  {
    if (chat_user.isEmpty()) return ;

    chat_text = chat_user + " has " + ((is_join_msg)? "joined" : "left") + " the jam" ;
    chat_user = GUI::SERVER_NICK ;
  } 
  Gui->chatComponent->addChatLine(chat_user , chat_text) ;
}

void LinJam::OnSamples(float** input_buffer  , int n_input_channels  ,
                       float** output_buffer , int n_output_channels ,
                       int     n_samples     , int sample_rate)
{
  if (!IsAudioEnabled)
  {
    // clear all output buffers
    uint8 n_bytes = n_samples * sizeof(float) ;
    for (int ch_n = 0 ; ch_n < n_output_channels ; ++ch_n)
      memset(output_buffer[ch_n] , 0 , n_bytes) ;
  }
  else Client->AudioProc(input_buffer  , n_input_channels  ,
                         output_buffer , n_output_channels ,
                         n_samples     , sample_rate       ) ;
}


/* getters/setters */

bool LinJam::IsAgreed() { return bool(Config->currentIsAgreed.getValue()) ; }


/* chat helpers */

void LinJam::SendChat(String chat_text)
{
DEBUG_TRACE_CHAT_OUT

  if ((chat_text = chat_text.trim()).isEmpty()) return ;

  if (chat_text.startsWith("/")) HandleChatCommand(chat_text) ;
  else Client->ChatMessage_Send(CLIENT::CHATMSG_TYPE_MSG.toRawUTF8() , chat_text.toRawUTF8()) ;
}


/* LinJam class private class functions */

bool LinJam::InitializeAudio()
{
  int   interface_n   = int(Config->audioIfN  .getValue()) ;
  int   n_inputs      = int(Config->nInputs   .getValue()) ;
  int   n_outputs     = int(Config->nOutputs  .getValue()) ;
  int   bit_depth     = int(Config->bitDepth  .getValue()) ;
  int   sample_rate   = int(Config->sampleRate.getValue()) ;
  WDL_String jack_name_wdl( Config->jackName  .toString().toRawUTF8()) ;
  char* jack_name     = jack_name_wdl.Get() ;
  char* config_string = "" ;
#ifdef _WIN32
  Audio = CreateConfiguredStreamer(CLIENT::WIN_INI_FILE , interface_n , OnSamples) ;
#else // _WIN32
#  ifdef _MAC
  Audio = create_audioStreamer_CoreAudio(&config_string , sample_rate ,
                                         n_inputs , bit_depth , OnSamples) ;
#  else // _MAC
  switch (interface_n)
  {
    case 0: // JACK
      Audio = create_audioStreamer_JACK(jack_name , n_inputs , n_outputs ,
                                        OnSamples , Client) ;

DEBUG_TRACE_JACK_INIT

      if (Audio) break ;
    case 1: // ALSA
    default:
      Audio = create_audioStreamer_ALSA(config_string , OnSamples) ;
  }
#  endif // _MAC
#endif // _WIN32

DEBUG_TRACE_AUDIO_INIT

  return (!!Audio) ;
}

void LinJam::ConfigureAudio()
{
  float master_volume   = float(Config->masterVolume .getValue()) ;
  float master_pan      = float(Config->masterPan    .getValue()) ;
  bool  is_master_muted = bool( Config->isMasterMuted.getValue()) ;
  float metro_volume    = float(Config->metroVolume  .getValue()) ;
  float metro_pan       = float(Config->metroPan     .getValue()) ;
  bool  is_metro_muted  = bool( Config->isMetroMuted .getValue()) ;
  int   metro_channel   = int(  Config->metroChannel .getValue()) ;
  bool  is_metro_stereo = bool( Config->isMetroStereo.getValue()) ;

  // configure master channels
  Client->config_mastervolume        = master_volume ;
  Client->config_masterpan           = master_pan ;
  Client->config_mastermute          = is_master_muted ;
  Client->config_metronome           = metro_volume ;
  Client->config_metronome_pan       = metro_pan ;
  Client->config_metronome_mute      = is_metro_muted ;
  Client->config_metronome_channel   = metro_channel ;
  Client->config_metronome_stereoout = is_metro_stereo ;
  Gui->mixerComponent->addMasterChannelComponent(GUI::MASTER_CHANNEL_GUI_ID) ;
  Gui->mixerComponent->addMasterChannelComponent(GUI::METRO_CHANNEL_GUI_ID) ;

  // configure input channels
  for (int ch_n = 0 ; ch_n < Config->localChannels.getNumChildren() ; ++ch_n)
  {
    ValueTree  channel   = Config->localChannels.getChild(ch_n) ;
    String     name      = String(channel.getType()) ;
    WDL_String name_wdl(name.toRawUTF8()) ;
    char*      c_name    = name_wdl.Get() ;
    float      volume    = float(channel.getProperty(STORAGE::VOLUME_IDENTIFIER)) ;
    float      pan       = float(channel.getProperty(STORAGE::PAN_IDENTIFIER)) ;
    float      is_xmit   = float(channel.getProperty(STORAGE::XMIT_IDENTIFIER)) ;
    float      is_muted  = float(channel.getProperty(STORAGE::MUTE_IDENTIFIER)) ;
    float      is_solo   = float(channel.getProperty(STORAGE::SOLO_IDENTIFIER)) ;
    float      source_n  = float(channel.getProperty(STORAGE::SOURCE_N_IDENTIFIER)) ;
    float      is_stereo = float(channel.getProperty(STORAGE::STEREO_IDENTIFIER)) ;

    Client->SetLocalChannelInfo(ch_n , c_name , true  , source_n ,
                                                false , 0        ,
                                                true  , is_xmit  ) ;
    Client->SetLocalChannelMonitoring(ch_n , true  , volume   ,
                                             true  , pan      ,
                                             true  , is_muted ,
                                             true  , is_solo  ) ;

#ifdef INPUT_FX
#  ifdef _WIN32
    void *p=CreateJesusInstance(ch,"",Audio->m_srate);
    if (p) Client->SetLocalChannelProcessor(ch,jesusonic_processor,p);
#  endif
#endif

    Gui->mixerComponent->addLocalChannelComponent(name) ;
  }
}

bool LinJam::PrepareSessionDirectory()
{
  File this_binary = File::getSpecialLocation(File::currentExecutableFile) ;
  File this_dir    = this_binary.getParentDirectory() ;
  SessionDir       = File(this_dir.getFullPathName() + STORAGE::SESSIONDIR) ;

  SessionDir.createDirectory() ; CleanSessionDir() ;

  bool does_session_dir_exist = SessionDir.isDirectory() ;
  if (does_session_dir_exist) Client->SetWorkDir(SessionDir.getFullPathName().toRawUTF8()) ;

  return does_session_dir_exist ;
}

void LinJam::ConfigureNinjam()
{
  bool      should_save_audio     = bool(Config->shouldSaveAudio    .getValue()) ;
  bool      should_save_log       = bool(Config->shouldSaveLog      .getValue()) ;
  int       debug_level           = int( Config->debugLevel         .getValue()) ;
  bool      should_auto_subscribe = bool(Config->shouldAutoSubscribe.getValue()) ;
  ValueTree subscriptions         = Config->autoSubscribeUsers ;

  Client->LicenseAgreementCallback = OnLicense ;
  Client->ChatMessage_Callback     = OnChatmsg ;
  Client->config_savelocalaudio    = should_save_audio ;
  Client->config_debug_level       = debug_level ;
  Client->config_autosubscribe     = should_auto_subscribe ;
  if (should_save_audio && should_save_log)
    Client->SetLogFile((SessionDir.getFullPathName() + STORAGE::LOGFILE).toRawUTF8()) ;
  for (int user_n = 0 ; user_n < subscriptions.getNumChildren() ; ++user_n)
  {
    WDL_String user_wdl(String(subscriptions.getChild(user_n).getType()).toRawUTF8()) ;
    Client->config_autosubscribe_userlist.insert(user_wdl.Get()) ;
  }
}

void LinJam::HandleChatCommand(String chat_text)
{
  String command        = chat_text.upToFirstOccurrenceOf(" " , false , false) ;
  bool is_me_command    = (!command.compare(CLIENT::CHATMSG_CMD_ME)) ;
  bool is_pm_command    = (!command.compare(CLIENT::CHATMSG_CMD_MSG)) ;
  bool is_admin_command = (!command.compare(CLIENT::CHATMSG_CMD_ADMIN)) ;
  bool is_user_command  = (!command.compare(CLIENT::CHATMSG_CMD_TOPIC) ||
                           !command.compare(CLIENT::CHATMSG_CMD_KICK)  ||
                           !command.compare(CLIENT::CHATMSG_CMD_BPM)   ||
                           !command.compare(CLIENT::CHATMSG_CMD_BPI)    ) ;

#ifdef CHAT_COMMANDS_BUGGY
  Gui->chatComponent->addChatLine(GUI::SERVER_NICK , "commands disabled") ;
#else // CHAT_COMMANDS_BUGGY

  if      (is_me_command)
  {
    String msg = String(Client->GetUserName()) + " " + chat_text ;
    Client->ChatMessage_Send(CLIENT::CHATMSG_TYPE_MSG.toRawUTF8() , msg.toRawUTF8()) ;
  }
  else if (is_user_command)
  {
    String msg = chat_text.substring(1) ;
    Client->ChatMessage_Send(CLIENT::CHATMSG_TYPE_ADMIN.toRawUTF8() , msg.toRawUTF8()) ;
  }
  else if (is_admin_command)
  {
    String msg = chat_text.substring(6).trim() ;
    Client->ChatMessage_Send(CLIENT::CHATMSG_TYPE_ADMIN.toRawUTF8() , msg.toRawUTF8()) ;
  }
  else if (is_pm_command)
  {
    String to_user = chat_text.substring(4).trim() ;
    to_user        = to_user.upToFirstOccurrenceOf(StringRef(" ") , false , false) ;
    String msg     = to_user.fromFirstOccurrenceOf(StringRef(" ") , false , false).trim() ;

    if (to_user.isEmpty() || msg.isEmpty())
      Gui->chatComponent->addChatLine(GUI::SERVER_NICK , GUI::INVALID_PM_MSG) ;
    else // if (does_user_exist(to_user)) // TODO: this safe yea ?
    {
      Client->ChatMessage_Send(CLIENT::CHATMSG_TYPE_PRIVMSG.toRawUTF8() , msg.toRawUTF8()) ;
      Gui->chatComponent->addChatLine("(PM -> " + to_user + ")" , msg) ;
    }
  }
  else Gui->chatComponent->addChatLine(GUI::SERVER_NICK , GUI::UNKNOWN_COMMAND_MSG) ;

#endif // CHAT_COMMANDS_BUGGY
}

void LinJam::CleanSessionDir()
{
  bool should_save_audio = bool(Config->shouldSaveAudio.getValue()) ;
  if (should_save_audio) return ;

DEBUG_TRACE_CLEAN_SESSION

  File this_binary = File::getSpecialLocation(File::currentExecutableFile) ;
  File this_dir    = this_binary.getParentDirectory() ;
  if (!SessionDir.isDirectory() || !SessionDir.isAChildOf(this_dir)) return ;

  DirectoryIterator session_dir_iter(SessionDir , false , "*.*" , File::findFilesAndDirectories) ;
  while (session_dir_iter.next()) session_dir_iter.getFile().deleteRecursively() ;
}
