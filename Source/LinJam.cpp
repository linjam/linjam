/*
  ==============================================================================

    Linjam.cpp
    Created: 24 May 2014 5:03:01pm
    Author:  me

  ==============================================================================
*/


//#define DEBUG_SERVER "ninbot.com:2049"
#define DEBUG_SERVER "ninbot.com:2050"


#include "LinJam.h"
#include "Constants.h"
#include "Trace.h"


/* LinJam public class variables */

#if ! PERSISTENCE_TRANSITION
bool LinJam::IsAgreed = false ;
#else // PERSISTENCE_TRANSITION
LinJamConfig* LinJam::Config ;
#endif // PERSISTENCE_TRANSITION


/* LinJam private class variables */

audioStreamer*        LinJam::Audio          = nullptr ; // Initialize()
NJClient*             LinJam::Client         = nullptr ; // Initialize()
MainContentComponent* LinJam::Gui            = nullptr ; // Initialize()
bool                  LinJam::IsAudioEnabled = false ;   // Initialize() TODO: use Client->>m_audio_enable instead ?? (issue #11)
File                  LinJam::SessionDir ;               // Initialize()

#if ! PERSISTENCE_TRANSITION
bool   LinJam::ShouldAutoJoin = false ; // TODO: persistent config            (issue #6)
String LinJam::Server         = "" ;    // TODO: persistent config            (issue #6)
String LinJam::Login          = "" ;    // TODO: persistent config per Server (issue #6)
String LinJam::Pass           = ""  ;   // TODO: persistent config per Server (issue #6)
bool   LinJam::IsAnonymous    = true ;  // TODO: persistent config per Server (issue #6)
bool   LinJam::ShouldAgree    = false ; // TODO: persistent config per Server (issue #6)
#endif // PERSISTENCE_TRANSITION


/* LinJam public class methods */

bool LinJam::Initialize(NJClient* client , MainContentComponent* contentComponent ,
                       const String& args)
{
DEBUG_TRACE_LINJAM_INIT

  Client = client ;
  Gui    = contentComponent ;

  // audio config defaults
  int                       should_save_local_audio = 0 ;
#ifdef _WIN32
  audioStreamer::WinAudioIf win_audio_if_n          = audioStreamer::WINDOWS_AUDIO_WAVE ;
#else // _WIN32
#  ifdef _MAC
  int                       mac_n_input_channels    = 2 ;
  int                       mac_sample_rate         = 48000 ;
  int                       mac_bit_depth           = 16 ;
  char*                     audio_config            = "" ;
#  else // _MAC
  int                       nix_audio_driver        = 0 ;
  String                    jack_client_name        = "linjam" ;
  int                       jack_n_input_channels   = 2 ;
  int                       jack_n_output_channels  = 2 ;
  char*                     audio_config            = "" ;
#  endif // _MAC
#endif // _WIN32
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

#if ! PERSISTENCE_TRANSITION
// XML_DEFAULTS begin
// DEFAULTS_DONE begin
  // master channels config defaults
  float master_volume = 1.0f ; // DB2VAL(-120.0) .. DB2VAL(20.0) db gain
// DEFAULTS_DONE end
#endif // PERSISTENCE_TRANSITION
  float master_pan    = 0.0f ; // -1.0 .. 1.0
  bool  master_mute   = false ;
  float metro_volume  = DB2VAL(-36.0f) ;
  float metro_pan     = 0.0f ;
  bool  metro_mute    = false ;
  int   metro_channel = 0 ;
  bool  metro_stereo  = true ;
// XML_DEFAULTS end

  // input channels config defaults
  const int     MAX_INPUT_CHANNELS = Client->GetMaxLocalChannels() ;
  Array<String> channel_names ;     String channel_name   = String("unnamed channel ") ;
  Array<int   > channel_source_ns ;
  Array<bool  > channel_xmits ;     bool   channel_xmit   = false ;
  Array<bool  > channel_mutes ;     bool   channel_mute   = false ;
  Array<bool  > channel_solos ;     bool   channel_solo   = false ;
  Array<float > channel_volumes ;   float  channel_volume = 0.0f ;
  Array<float > channel_pans ;      float  channel_pan    = 0.0f ;
  for (int ch_n = 0 ; ch_n < MAX_INPUT_CHANNELS ; ++ch_n)
  {
    channel_names.add(channel_name + String(ch_n)) ;
    channel_source_ns.add(ch_n) ;
  }
  channel_xmits  .insertMultiple(0 , channel_xmit   , MAX_INPUT_CHANNELS) ;
  channel_mutes  .insertMultiple(0 , channel_mute   , MAX_INPUT_CHANNELS) ;
  channel_solos  .insertMultiple(0 , channel_solo   , MAX_INPUT_CHANNELS) ;
  channel_volumes.insertMultiple(0 , channel_volume , MAX_INPUT_CHANNELS) ;
  channel_pans   .insertMultiple(0 , channel_pan    , MAX_INPUT_CHANNELS) ;

  // misc config defaults
  String session_dirname     = "/.linjam/session" ;
  bool   should_save_log     = true ;
  String log_filename        = "clipsort.log" ;
  int    debug_level         = 0 ; // TODO: what are the accepted values
  bool should_auto_subscribe = true ;
  Array<String> auto_subscribe_users ;

// TODO: parse command line args for autojoin (issue #9)


// TODO: load master and local channels from persistent config (issue #6)
#if PERSISTENCE_TRANSITION
  Config = new LinJamConfig() ;

// Config->masterVolume.addListener(Gui->loginComponent) ; Config->masterVolume = 42.0 ;
// DBG("Config->masterVolume=" + Config->masterVolume.getValue().toString()) ;
#endif // PERSISTENCE_TRANSITION













  // initialize audio
#ifdef _WIN32
  Audio = CreateConfiguredStreamer(CLIENT::WIN_INI_FILE , win_audio_if_n , OnSamples) ;
#else // _WIN32
#  ifdef _MAC
  Audio = create_audioStreamer_CoreAudio(&audio_config , mac_sample_rate ,
                                         mac_n_input_channels , mac_bit_depth , OnSamples) ;
#  else // _MAC
  switch (nix_audio_driver)
  {
    case 0: // JACK
      Audio = create_audioStreamer_JACK(jack_client_name.toRawUTF8() , jack_n_input_channels ,
                                        jack_n_output_channels , OnSamples , Client) ;

DEBUG_TRACE_JACK_INIT

      if (Audio) break ;
    case 1: // ALSA
    default:
      Audio = create_audioStreamer_ALSA(audio_config , OnSamples) ;
  }
#  endif // _MAC
#endif // _WIN32

DEBUG_TRACE_AUDIO_INIT

  if (!Audio) return false ;

  // configure master channels
  Client->config_mastervolume        = 1.0;//float(MasterVolume.getValue()) ;
  Client->config_masterpan           = master_pan ;
  Client->config_mastermute          = master_mute ;
  Client->config_metronome           = metro_volume ;
  Client->config_metronome_pan       = metro_pan ;
  Client->config_metronome_mute      = metro_mute ;
  Client->config_metronome_channel   = metro_channel ;
  Client->config_metronome_stereoout = metro_stereo ;
  Gui->mixerComponent->addMasterChannelComponent(GUI::MASTER_CHANNEL_GUI_ID) ;
  Gui->mixerComponent->addMasterChannelComponent(GUI::METRO_CHANNEL_GUI_ID) ;

  // configure input channels
  int n_input_channels = Audio->m_innch ;
  for (int ch_n = 0 ; ch_n < n_input_channels ; ++ch_n)
  {
    Client->SetLocalChannelInfo(ch_n , channel_names[ch_n].toRawUTF8() , true  , channel_source_ns[ch_n] , false , 0 , true  , channel_xmits[ch_n]) ;
    Client->SetLocalChannelMonitoring(ch_n , true  , channel_volumes[ch_n] , true  , channel_pans[ch_n] , true  , channel_mutes[ch_n] , true  , channel_solos[ch_n]) ;

#ifdef INPUT_FX
#  ifdef _WIN32
    void *p=CreateJesusInstance(ch,"",Audio->m_srate);
    if (p) Client->SetLocalChannelProcessor(ch,jesusonic_processor,p);
#  endif
#endif

    Gui->mixerComponent->addLocalChannelComponent(GUI::LOCAL_CHANNEL_GUI_ID + String(ch_n)) ;
  }

  // prepare session directory
  File home_dir = File::getSpecialLocation(File::userApplicationDataDirectory) ;
  if (home_dir.isDirectory())
  {
    session_dirname = (session_dirname.startsWith("/"))?
        home_dir.getFullPathName() + session_dirname :
        home_dir.getFullPathName() + String("/") + session_dirname ;
    SessionDir = File(session_dirname) ;
    SessionDir.createDirectory() ; CleanSessionDir() ;
  }
  bool does_session_dir_exist = SessionDir.isDirectory() ;
  if (does_session_dir_exist) Client->SetWorkDir(session_dirname.toRawUTF8()) ;

  // configure NINJAM client
  Client->LicenseAgreementCallback = OnLicense ;
  Client->ChatMessage_Callback     = OnChatmsg ;
  Client->config_savelocalaudio    = should_save_local_audio ;
  Client->config_debug_level       = debug_level ;
  Client->config_autosubscribe     = should_auto_subscribe ;
  if (should_save_log && does_session_dir_exist)
    Client->SetLogFile((session_dirname + log_filename).toRawUTF8()) ;
  for (int user_n = 0 ; user_n < auto_subscribe_users.size() ; ++user_n)
    Client->config_autosubscribe_userlist.insert(auto_subscribe_users[user_n].toRawUTF8()) ;

  // initialize networking
  JNL::open_socketlib() ;

  return does_session_dir_exist ;
}

void LinJam::Connect()
{
  Client->Disconnect() ;
#if ! PERSISTENCE_TRANSITION
  String login = Login ;
  if (IsAnonymous)
  {
    login = "anonymous:" + ((Login == "")? "nobody" : Login) ;
    Pass  = "" ;
  }
#  if DEBUG_STATIC_SERVER
Server = DEBUG_SERVER ; // TODO: get Server Login Pass IsAnonymous from config (issue #6)
#  endif // DEBUG_STATIC_SERVER
#if DEBUG_BYPASS_LICENSE
  IsAgreed = true ;
#endif
DEBUG_TRACE_CONNECT

  Client->Connect(Server.toRawUTF8() , login.toRawUTF8() , Pass.toRawUTF8()) ;
#else // PERSISTENCE_TRANSITION
  String host         =      Config->currentHost.toString() ;
  String login        =      Config->currentLogin.toString() ;
  String pass         =      Config->currentPass.toString() ;
  bool   is_anonymous = bool(Config->currentIsAnonymous.getValue()) ;

  if (is_anonymous) { login = "anonymous:" + login ; pass  = "" ; }

DEBUG_TRACE_CONNECT

  Gui->statusbarComponent->setStatusL(GUI::CONNECTING_STATUS_TEXT + host) ;
  Client->Connect(host.toRawUTF8() , login.toRawUTF8() , pass.toRawUTF8()) ;
#endif // PERSISTENCE_TRANSITION
  IsAudioEnabled = true ;
}

void LinJam::Disconnect() { IsAudioEnabled = false ; Client->Disconnect() ; }

void LinJam::Shutdown()
{
  delete Audio ; delete Config ;
  JNL::close_socketlib() ; CleanSessionDir() ;
}


/* NJClient callbacks */

int LinJam::OnLicense(int user32 , char* license_text)
{
#if ! PERSISTENCE_TRANSITION
  if (!(IsAgreed = (IsAgreed || GetShouldAgree())))
  {
    Gui->licenseComponent->setLicenseText(CharPointer_UTF8(license_text)) ;
    Config->setServerConfig() ;
  }

DEBUG_TRACE_LICENSE

  return IsAgreed ;

#else // PERSISTENCE_TRANSITION
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
#endif // PERSISTENCE_TRANSITION
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

// TODO: get/set persistent config (issue #6)
#if ! PERSISTENCE_TRANSITION
String LinJam::GetServer() { return Server ; }
String LinJam::GetLogin() { return Login ; }
String LinJam::GetPass() { return Pass ; }
bool   LinJam::GetIsAnonymous() { return IsAnonymous; }
bool   LinJam::GetShouldAgree() { return ShouldAgree ; }
void   LinJam::SetShouldAgree(bool shouldAgree) { ShouldAgree = shouldAgree ; }
void   LinJam::SetIsAgreed(bool isAgreed) { IsAgreed = isAgreed ; }
#else // PERSISTENCE_TRANSITION
bool LinJam::IsAgreed() { return bool(Config->currentIsAgreed.getValue()) ; }
#endif // PERSISTENCE_TRANSITION


/* chat helpers */

void LinJam::SendChat(String chat_text)
{
DEBUG_TRACE_CHAT_OUT

  if ((chat_text = chat_text.trim()).isEmpty()) return ;

  if (chat_text.startsWith("/")) HandleChatCommand(chat_text) ;
  else Client->ChatMessage_Send(CLIENT::CHATMSG_TYPE_MSG.toRawUTF8() , chat_text.toRawUTF8()) ;
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


/* misc helpers */

void LinJam::CleanSessionDir()
{
  if (!SessionDir.isDirectory()) return ;

  DirectoryIterator session_dir_iter (SessionDir , false , "*.*" , File::findFilesAndDirectories) ;
  while (session_dir_iter.next()) session_dir_iter.getFile().deleteRecursively() ;
}
