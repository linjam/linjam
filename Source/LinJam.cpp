/*
  ==============================================================================

    Linjam.cpp
    Created: 24 May 2014 5:03:01pm
    Author:  me

  ==============================================================================
*/


//#define DEBUG_AUTOJOIN_STATIC_CHANNEL
#define DEBUG_STATIC_CHANNEL "ninjamer.com:2049"


#include "LinJam.h"
#include "Constants.h"
#include "Trace.h"


class LinJamApplication ;


/* LinJam public class variables */

LinJamConfig* LinJam::Config ;


/* LinJam private class variables */

audioStreamer*        LinJam::Audio          = nullptr ; // Initialize()
NJClient*             LinJam::Client         = nullptr ; // Initialize()
MainContentComponent* LinJam::Gui            = nullptr ; // Initialize()
int                   LinJam::GuiBeatOffset ;            // InitializeAudio()
File                  LinJam::SessionDir ;               // PrepareSessionDirectory()
int                   LinJam::PrevStatus ;               // Initialize()
bool                  LinJam::IsAudioEnabled = false ;   // TODO: use Client->IsAudioRunning() instead ?? (issue #11)


/* LinJam public class methods */

bool LinJam::Initialize(NJClient* client , MainContentComponent* contentComponent ,
                        const String& args)
{
DEBUG_TRACE_LINJAM_INIT

  Client = client ;
  Gui    = contentComponent ;


// TODO: parse command line args for autojoin (issue #9)

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
          nblock 16    -- set number of blocks */


  // load persistent configuration
  Config = new LinJamConfig() ; if (!Config->sanityCheck()) return false ;

  // configure audio , session directory , and NINJAM client
  if (InitializeAudio())         ConfigureAudio() ;  else return false ;
  if (PrepareSessionDirectory()) ConfigureNinjam() ; else return false ;

  // initialize networking
  PrevStatus = NJClient::NJC_STATUS_DISCONNECTED ; JNL::open_socketlib() ;

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


/* NJClient runtime routines */

void LinJam::DriveClient()
{
  int client_status = Client->GetStatus() ;
  if (client_status != PrevStatus) HandleStatusChanged(PrevStatus = client_status) ;
  if (client_status == NJClient::NJC_STATUS_OK && Client->HasUserInfoChanged())
    HandleUserInfoChanged() ;
  if (client_status >= NJClient::NJC_STATUS_OK) while (!Client->Run()) ;
}

void LinJam::UpdateGUI()
{
  // master VU
  Gui->mixerComponent->updateChannelVU(GUI::MASTER_MIXERGROUP_IDENTIFIER ,
                                       STORAGE::MASTER_KEY               ,
                                       VAL2DB(Client->GetOutputPeak())   ) ;

  // local VU
  int channel_n = -1 ; int channel_idx ;
  while ((channel_idx = Client->EnumLocalChannels(++channel_n)) != -1)
  {
    ValueTree channel_config = Config->localChannels.getChild(channel_n) ;
    if (channel_config.isValid())
      Gui->mixerComponent->updateChannelVU(GUI::LOCAL_MIXERGROUP_IDENTIFIER ,
                                           String(channel_config.getType()) ,
                                           VAL2DB(Client->GetLocalChannelPeak(channel_idx))) ;
  }

  // local and remote VU
  // TODO: remote channels vu (issue #22)

  // loop progress
  int   sample_n , n_samples ; Client->GetPosition(&sample_n , &n_samples) ;
  int   bpi      = Client->GetBPI() ;
  float bpm      = Client->GetActualBPM() ;
  float progress = (sample_n + GuiBeatOffset) / (float)n_samples ;
  int   beat_n   = ((int)(bpi * progress) % bpi) + 1 ;
  Gui->loopComponent->updateBeat(beat_n) ;
  Gui->loopComponent->updateBPI(bpi) ;
  Gui->statusbarComponent->setStatusR(String(bpi) + " bpi @ " + String(bpm) + " bpm") ;
}


/* helpers */

void LinJam::SendChat(String chat_text)
{
DEBUG_TRACE_CHAT_OUT

  if ((chat_text = chat_text.trim()).isEmpty()) return ;

  if (chat_text.startsWith("/")) HandleChatCommand(chat_text) ;
  else Client->ChatMessage_Send(CLIENT::CHATMSG_TYPE_MSG.toRawUTF8() , chat_text.toRawUTF8()) ;
}


/* getters/setters */

bool LinJam::IsAgreed() { return bool(Config->currentIsAgreed.getValue()) ; }


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


/* NJClient runtime helpers */

void LinJam::HandleStatusChanged(int client_status)
{
DEBUG_TRACE_CONNECT_STATUS
#ifdef DEBUG_AUTOJOIN_STATIC_CHANNEL
if (client_status == NJClient::NJC_STATUS_PRECONNECT)
{ Config->currentHost        = DEBUG_STATIC_CHANNEL ;
  Config->currentLogin       =  "nobody" ;
  Config->currentIsAnonymous = true ; Connect() ; }
#endif // DEBUG_AUTOJOIN_STATIC_CHANNEL

  bool is_agreed = IsAgreed() ;

  // GUI state
  Gui->blankComponent->toFront(false) ;
  switch (client_status)
  {
    case NJClient::NJC_STATUS_DISCONNECTED: Gui->loginComponent  ->toFront(true)  ; break ;
    case NJClient::NJC_STATUS_INVALIDAUTH:  (is_agreed)?
                                            Gui->loginComponent  ->toFront(true)  :
                                            Gui->licenseComponent->toFront(true)  ; break ;
    case NJClient::NJC_STATUS_CANTCONNECT:  Gui->loginComponent  ->toFront(true)  ; break ;
    case NJClient::NJC_STATUS_OK:           Gui->chatComponent   ->toFront(true)  ;
                                            Gui->mixerComponent  ->toFront(false) ;
                                            Gui->loopComponent   ->toFront(false) ; break ;
    case NJClient::NJC_STATUS_PRECONNECT:   Gui->loginComponent  ->toFront(true)  ; break ;
    default:                                                                        break ;
  }

  // status indicator
  String status_text ;
  switch (client_status)
  {
    case NJClient::NJC_STATUS_DISCONNECTED:
      status_text = GUI::DISCONNECTED_STATUS_TEXT ;                              break ;
    case NJClient::NJC_STATUS_INVALIDAUTH:
      status_text = (is_agreed)? ((IsRoomFull())?
                    GUI::ROOM_FULL_STATUS_TEXT :
                    GUI::INVALID_AUTH_STATUS_TEXT) :
                    GUI::PENDING_LICENSE_STATUS_TEXT ;                           break ;
    case NJClient::NJC_STATUS_CANTCONNECT:
      status_text = GUI::FAILED_CONNECTION_STATUS_TEXT ;                         break ;
    case NJClient::NJC_STATUS_OK:
      status_text = GUI::CONNECTED_STATUS_TEXT + String(Client->GetHostName()) ; break ;
    case NJClient::NJC_STATUS_PRECONNECT:
      status_text = GUI::IDLE_STATUS_TEXT ;                                      break ;
    default:
      status_text = GUI::UNKNOWN_STATUS_TEXT + String(client_status) ;           break ;
  }
  Gui->statusbarComponent->setStatusL(status_text) ;
}

void LinJam::HandleUserInfoChanged()
{
DEBUG_TRACE_REMOTE_CHANNELS

  int user_n = -1 ; char* user_name ; float user_volume ; float user_pan ; bool  user_mute ;
  while (user_name = Client->GetUserState(++user_n , &user_volume , &user_pan , &user_mute))
  {
    int channel_n = -1 ; while (Client->EnumUserChannels(user_n , ++channel_n) != -1)
    {
      bool is_rcv ;  float channel_volume ; float channel_pan ; bool channel_mute ;
      bool is_solo ; int   output_channel ; bool  is_stereo ;
      char* channel_name = Client->GetUserChannelState(user_n , channel_n , &is_rcv      ,
                                                       &channel_volume    , &channel_pan ,
                                                       &channel_mute      , &is_solo     ,
                                                       &output_channel    , &is_stereo   ) ;

//Gui->mixerComponent->addLocalChannelComponent(name) ;
    }
  }
}

bool LinJam::IsRoomFull()
{
#ifdef WIN32 // TODO: GetErrorStr() linux .so segfault (issue #15)
  String err = String(CharPointer_UTF8(Client->GetErrorStr())) ;
  return (err.isNotEmpty() && !err.compare(CLIENT::SERVER_FULL_STATUS)) ;
#else // WIN32
  return true ;
/*
  if (GetErrorStr()[0]) // <-- segfault here
    return (!strcmp(GetErrorStr() , "room full")) ;
  else
    return false ;
*/
#endif
}


/* LinJam class private class methods */

bool LinJam::InitializeAudio()
{
        int   interface_n   = int(Config->audioIfN  .getValue()) ;
        int   n_inputs      = int(Config->nInputs   .getValue()) ;
        int   n_outputs     = int(Config->nOutputs  .getValue()) ;
        int   bit_depth     = int(Config->bitDepth  .getValue()) ;
        int   sample_rate   = int(Config->sampleRate.getValue()) ;
  const char* jack_name     =     Config->jackName  .toString().toRawUTF8() ;
        char* config_string = "" ;
#ifdef _WIN32
#  ifndef AUDIOCONFIG_CPP_NYI_TODO
  audioStreamer::WinAudioIf if_n = audioStreamer::WinAudioIf::WINDOWS_AUDIO_WAVE ; // 3
  interface_n = if_n ;
#  else // AUDIOCONFIG_CPP_NYI_TODO
// TODO reimplement audioconfig.cpp client-side (issue #27)
#  endif // AUDIOCONFIG_CPP_NYI_TODO
  Audio = CreateConfiguredStreamer(CLIENT::WIN_INI_FILE , (audioStreamer::WinAudioIf)interface_n , OnSamples) ;
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

  GuiBeatOffset = Audio->m_srate * (CLIENT::GUI_DRIVER_IVL * 0.001) ;

DEBUG_TRACE_AUDIO_INIT

  return (!!Audio) ;
}

void LinJam::ConfigureAudio()
{
  // configure master channels
  ValueTree master_channel = Config->masterChannels.getChildWithName(GUI::MASTER_CHANNEL_GUI_ID) ;
  ValueTree metro_channel  = Config->masterChannels.getChildWithName(GUI::METRO_CHANNEL_GUI_ID) ;
  float master_volume      = float(master_channel.getProperty(STORAGE::VOLUME_IDENTIFIER)) ;
  float master_pan         = float(master_channel.getProperty(STORAGE::PAN_IDENTIFIER)) ;
  bool  is_master_muted    = bool( master_channel.getProperty(STORAGE::MUTE_IDENTIFIER)) ;
  float metro_volume       = float(metro_channel .getProperty(STORAGE::VOLUME_IDENTIFIER)) ;
  float metro_pan          = float(metro_channel .getProperty(STORAGE::PAN_IDENTIFIER)) ;
  bool  is_metro_muted     = bool( metro_channel .getProperty(STORAGE::MUTE_IDENTIFIER)) ;
  int   metro_source       = int(  metro_channel .getProperty(STORAGE::SOURCE_N_IDENTIFIER)) ;
  bool  is_metro_stereo    = bool( metro_channel .getProperty(STORAGE::STEREO_IDENTIFIER)) ;

  Client->config_mastervolume        = (float)DB2VAL(master_volume) ;
  Client->config_masterpan           = master_pan ;
  Client->config_mastermute          = is_master_muted ;
  Client->config_metronome           = (float)DB2VAL(metro_volume) ;
  Client->config_metronome_pan       = metro_pan ;
  Client->config_metronome_mute      = is_metro_muted ;
  Client->config_metronome_channel   = metro_source ;
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
    bool       is_xmit   = bool( channel.getProperty(STORAGE::XMIT_IDENTIFIER)) ;
    bool       is_muted  = bool( channel.getProperty(STORAGE::MUTE_IDENTIFIER)) ;
    bool       is_solo   = bool( channel.getProperty(STORAGE::SOLO_IDENTIFIER)) ;
    int        source_n  = int(  channel.getProperty(STORAGE::SOURCE_N_IDENTIFIER)) ;
//     bool       is_stereo = bool( channel.getProperty(STORAGE::STEREO_IDENTIFIER)) ;

    Client->SetLocalChannelInfo(ch_n , c_name , true  , source_n ,
                                                false , 0        ,
                                                true  , is_xmit  ) ;
    Client->SetLocalChannelMonitoring(ch_n , true  , (float)DB2VAL(volume) ,
                                             true  , pan                   ,
                                             true  , is_muted              ,
                                             true  , is_solo               ) ;

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
  int       should_save_audio     = int( Config->shouldSaveAudio    .getValue()) ;
  bool      should_save_log       = bool(Config->shouldSaveLog      .getValue()) ;
  int       debug_level           = int( Config->debugLevel         .getValue()) ;
  int       should_auto_subscribe = int( Config->shouldAutoSubscribe.getValue()) ;
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

#ifdef CHAT_COMMANDS_BUGGY // (issue #19)
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
    else // if (does_user_exist(to_user)) // TODO: this safe yea ? // (issue #19)
    {
      Client->ChatMessage_Send(CLIENT::CHATMSG_TYPE_PRIVMSG.toRawUTF8() , msg.toRawUTF8()) ;
      Gui->chatComponent->addChatLine("(PM -> " + to_user + ")" , msg) ;
    }
  }
  else Gui->chatComponent->addChatLine(GUI::SERVER_NICK , GUI::UNKNOWN_COMMAND_MSG) ;

#endif // CHAT_COMMANDS_BUGGY
}

bool LinJam::SetChannelInfoByName(const char* channel_name                         ,
                                        bool  should_set_source_n , int   source_n ,
                                        bool  should_set_bitrate  , int   bitrate  ,
                                        bool  should_set_is_xmit  , bool  is_xmit  ,
                                        bool  should_set_volume   , float volume   ,
                                        bool  should_set_pan      , float pan      ,
                                        bool  should_set_is_muted , bool  is_muted ,
                                        bool  should_set_is_solo  , bool  is_solo  )
{
  int channel_n = -1 ; int channel_idx ;
  while ((channel_idx = LinJam::Client->EnumLocalChannels(++channel_n)) != -1)
    if (!strcmp(channel_name , Client->GetLocalChannelInfo(channel_idx , NULL , NULL , NULL)))
    {
      // TODO: channel name changes (issue #12)
      if (should_set_source_n || should_set_bitrate || should_set_is_xmit)
        Client->SetLocalChannelInfo(channel_idx , NULL , should_set_source_n , source_n ,
                                                         should_set_bitrate  , bitrate  ,
                                                         should_set_is_xmit  , is_xmit  ) ;
      if (should_set_volume || should_set_pan || should_set_is_muted || should_set_is_solo)
        Client->SetLocalChannelMonitoring(channel_idx                                 ,
                                          should_set_volume   , (float)DB2VAL(volume) ,
                                          should_set_pan      , pan                   ,
                                          should_set_is_muted , is_muted              ,
                                          should_set_is_solo  , is_solo               ) ;
      return true ;
    }
  // TODO: iterate remote channels (issue #22)

  return false ;
}
