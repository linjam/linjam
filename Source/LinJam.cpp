/*
  ==============================================================================

    Linjam.cpp
    Created: 24 May 2014 5:03:01pm
    Author:  me

  ==============================================================================
*/

// #define DEBUG_STATIC_CHANNEL "localhost:2049"
#define DEBUG_STATIC_CHANNEL "ninbot.com:2052"
// #define DEBUG_STATIC_CHANNEL "ninjamer.com:2049"


#include "LinJam.h"
#include "Channel.h"
#include "Constants.h"


// class LinJamApplication ;


/* LinJam public class variables */

LinJamConfig* LinJam::Config ;


/* LinJam private class variables */

NJClient*      LinJam::Client         = nullptr ; // Initialize()
MainContent*   LinJam::Gui            = nullptr ; // Initialize()
audioStreamer* LinJam::Audio          = nullptr ; // Initialize()
bool           LinJam::IsAudioEnabled = false ;   // InitializeAudio()
float          LinJam::GuiBeatOffset ;            // InitializeAudio()
File           LinJam::SessionDir ;               // PrepareSessionDirectory()
int            LinJam::PrevStatus ;               // Initialize()
String         LinJam::PrevRecordingTime ;        // Disconnect()


/* LinJam public class methods */

/* state methods */

bool LinJam::Initialize(NJClient*     njClient , MainContent* mainCcontent ,
                        const String& args                                 )
{
DEBUG_TRACE_LINJAM_INIT

  Client  = njClient ;
  Gui     = mainCcontent ;


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
  Config = new LinJamConfig() ; if (!Config->sanityCheck())         return false ;

  // configure audio , session directory , and NINJAM client
  if (InitializeAudio())         ConfigureInitialChannels() ;  else return false ;
  if (PrepareSessionDirectory()) ConfigureNinjam() ;           else return false ;

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

  Gui->statusbar->setStatusL(GUI::CONNECTING_STATUS_TEXT + host) ;
  Client->Connect(host.toRawUTF8() , login.toRawUTF8() , pass.toRawUTF8()) ;
}

void LinJam::Disconnect() { Client->Disconnect() ; PrevRecordingTime = "" ; }

void LinJam::Shutdown()
{
  IsAudioEnabled = false ;
  JNL::close_socketlib() ; delete Audio ;
  CleanSessionDir() ;      delete Config ;
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

void LinJam::UpdateGuiHighPriority()
{
#ifndef UPDATE_GUI
  return ;
#endif // UPDATE_GUI

  // loop progress
  int    sample_n , n_samples ; Client->GetPosition(&sample_n , &n_samples) ;
  int    bpi               = Client->GetBPI() ;
  float  bpm               = Client->GetActualBPM() ;
  double linear_progress   = (sample_n + GuiBeatOffset) / n_samples ;
  int    beat_n            = ((int)(bpi * linear_progress) % bpi) + 1 ;
  double discrete_progress = (float)beat_n / bpi ;
  Gui->loop->updateBeat(beat_n) ;
  Gui->loop->loopProgress = discrete_progress ; // linear_progress ;
  Gui->statusbar->setStatusR(String(bpi) + " bpi @ " + String(bpm) + " bpm") ;

  // master VU
  ValueTree metro_store = Config->getChannelById(GUI::MASTERS_ID , CONFIG::METRO_KEY) ;
  double    master_vu   = VAL2DB(Client->GetOutputPeak()) ;
  double    metro_vu    = (bool(metro_store[CONFIG::IS_MUTED_ID]))? GUI::VU_DB_MIN :
                          (discrete_progress * GUI::VU_DB_RANGE) + GUI::VU_DB_MIN ;
  Gui->mixer->updateChannelVU(GUI::MASTERS_ID , CONFIG::MASTER_KEY , master_vu) ;
  Gui->mixer->updateChannelVU(GUI::MASTERS_ID , CONFIG::METRO_KEY  , metro_vu) ;

  // local VU
  int channel_n = -1 ; int channel_idx ;
  while (~(channel_idx = Client->EnumLocalChannels(++channel_n)))
    Gui->mixer->updateChannelVU(GUI::LOCALS_ID                                  ,
                                String(GetChannelName(channel_idx))             ,
                                VAL2DB(Client->GetLocalChannelPeak(channel_idx))) ;

  // remote VU
  int user_idx = -1 ; char* user_c_name ;
  while (user_c_name = Client->GetUserState(++user_idx))
  {
#ifdef DEBUG_DUPLICATE_CHANNEL_NAMES_VU_BUG
DBG("user[" + String(user_idx) + "]=" + String(Config->encodeUserId(user_c_name , user_idx))) ;
#endif // DEBUG_DUPLICATE_CHANNEL_NAMES_VU_BUG

    Identifier user_id    = Config->encodeUserId(user_c_name , user_idx) ;
    float      master_vu  = 0.0f ; channel_n = -1 ;
    while (~(channel_idx = Client->EnumUserChannels(user_idx , ++channel_n)))
    {
      // update remote channel VU
      char*  channel_name = Client->GetUserChannelState(user_idx , channel_idx) ;
      String channel_id   = String(Config->encodeChannelId(channel_name , channel_idx)) ;
      float  channel_vu   = Client->GetUserChannelPeak(user_idx , channel_idx) ;
      master_vu += channel_vu ;
      Gui->mixer->updateChannelVU(user_id , channel_id , VAL2DB(channel_vu)) ;

#ifdef DEBUG_DUPLICATE_CHANNEL_NAMES_VU_BUG
DBG("user[" + String(user_idx) + "]=" + String(user_id) + " channel[" + String(channel_n) + "/" + String(channel_idx) + "]="+ channel_id) ;
#endif // DEBUG_DUPLICATE_CHANNEL_NAMES_VU_BUG
    }
    // update remote master VU
    Gui->mixer->updateChannelVU(user_id , CONFIG::MASTER_KEY , VAL2DB(master_vu)) ;
  }
}

void LinJam::UpdateGuiLowPriority()
{
  if (PrevStatus != NJClient::NJC_STATUS_OK) return ;

  // NOTE: recording time is brittle - it is assuming that the bot exists
  //       in the first user slot and that the recording time is name of first channel
  String host           = String(Client->GetHostName()) ;
  String bpi            = String(Client->GetBPI()) ;
  String bpm            = String((int)Client->GetActualBPM()) ;
  bool   server_has_bot = NETWORK::KNOWN_HOSTS.contains(host) ;
  String recording_time = String(Client->GetUserChannelState(CLIENT::BOT_USERIDX ,
                                                             CLIENT::BOT_CHANNELIDX)) ;
  if (server_has_bot && recording_time.compare(PrevRecordingTime) &&
      PrevRecordingTime.isNotEmpty())
       Gui->setTitle(host + " - " + bpi + "bpi / " + bpm + "bpm - " + recording_time) ;
  else Gui->setTitle(host + " - " + bpi + "bpi / " + bpm + "bpm") ;
  PrevRecordingTime = recording_time ;
}


/* getters/setters */

bool LinJam::IsAgreed() { return bool(Config->currentIsAgreed.getValue()) ; }


/* GUI event handlers */

void LinJam::AddLocalChannel(String channel_name)
{
DEBUG_TRACE_ADD_LOCAL_CHANNEL_FAIL

  // ensure that we do not exceed our maximum number of local channels
  int channel_idx = GetVacantLocalChannelIdx() ; if (!(~channel_idx)) return ;

  // ensure that a channel with this name does not already exist
  Identifier channel_id = Config->encodeChannelId(channel_name , channel_idx) ;
  if (Config->doesChannelExist(GUI::LOCALS_ID , String(channel_id))) return ;

  // create stored config for this channel
  ValueTree  channel_store = Config->createChannel(GUI::LOCALS_ID            ,
                                                   channel_name              ,
                                                   channel_idx               ,
                                                   CONFIG::DEFAULT_VOLUME    ,
                                                   CONFIG::DEFAULT_PAN       ,
                                                   CONFIG::DEFAULT_IS_XMIT   ,
                                                   CONFIG::DEFAULT_IS_MUTED  ,
                                                   CONFIG::DEFAULT_IS_SOLO   ,
                                                   CONFIG::DEFAULT_SOURCE_N  ,
                                                   CONFIG::DEFAULT_IS_STEREO ) ;
  if (!channel_store.isValid()) return ;

  // create local Channel GUI and configure NJClient input channel
  if (Gui->mixer->addChannel(GUI::LOCALS_GUI_ID , channel_store))
    channel_store.setProperty(CONFIG::CHANNELIDX_ID , channel_idx , nullptr) ;
  ConfigureLocalChannel(channel_store , CONFIG::CONFIG_ALL_ID) ;
}

void LinJam::RemoveLocalChannel(Identifier channel_id)
{
DEBUG_TRACE_REMOVE_LOCAL_CHANNEL

  Client->DeleteLocalChannel(GetLocalChannelIdx(channel_id)) ;
  Client->NotifyServerOfChannelChange() ;
}

void LinJam::SendChat(String chat_text)
{
DEBUG_TRACE_CHAT_OUT

  if ((chat_text = chat_text.trim()).isEmpty()) return ;

  if (chat_text.startsWith("/")) HandleChatCommand(chat_text) ;
  else Client->ChatMessage_Send(CLIENT::CHATMSG_TYPE_MSG.toRawUTF8() , chat_text.toRawUTF8()) ;
}


/* LinJam class private class methods */

/* NJClient callbacks */

int LinJam::OnLicense(int user32 , char* license_text)
{
#ifdef DEBUG_AUTOLOGIN_NYI
  return true ;
#endif // DEBUG_AUTOLOGIN_NYI

  ValueTree server         = Config->getCurrentServer() ;
  bool should_always_agree = server.isValid() &&
                             bool(server.getProperty(CONFIG::AGREE_ID)) ;
  bool is_agreed           = IsAgreed() || should_always_agree ;

  if (!is_agreed) Gui->license->setLicenseText(CharPointer_UTF8(license_text)) ;
  else            Config->currentIsAgreed = false ;

DEBUG_TRACE_LICENSE

  return is_agreed ;
}

void LinJam::OnChatmsg(int user32 , NJClient* instance , const char** parms , int nparms)
{
  if (!parms[0]) return ;

  String chat_type  = String(CharPointer_UTF8(parms[CLIENT::CHATMSG_TYPE_IDX])) ;
  String chat_user  = String(CharPointer_UTF8(parms[CLIENT::CHATMSG_USER_IDX]))
                      .upToFirstOccurrenceOf(CONFIG::USER_IP_SPLIT_CHAR , false , false) ;
  String chat_text  = String(CharPointer_UTF8(parms[CLIENT::CHATMSG_MSG_IDX])) ;
  bool is_topic_msg = (!chat_type.compare(CLIENT::CHATMSG_TYPE_TOPIC)) ;
  bool is_bcast_msg = (!chat_type.compare(CLIENT::CHATMSG_TYPE_MSG)) ;
  bool is_priv_msg  = (!chat_type.compare(CLIENT::CHATMSG_TYPE_PRIVMSG)) ;
  bool is_join_msg  = (!chat_type.compare(CLIENT::CHATMSG_TYPE_JOIN)) ;
  bool is_part_msg  = (!chat_type.compare(CLIENT::CHATMSG_TYPE_PART)) ;

DEBUG_TRACE_CHAT_IN

  if (is_topic_msg)
  {
    if (chat_text.isEmpty()) return ;

    if (chat_user.isEmpty()) chat_text = GUI::MOTD_TEXT                 + chat_text ;
    else                     chat_text = chat_user + GUI::SET_MOTD_TEXT + chat_text ;
    chat_user = GUI::SERVER_NICK ;

    Gui->chat->setTopic(chat_text) ;
  }
  else if (is_bcast_msg)
  {
    if (chat_text.isEmpty()) return ;

    if      (chat_user.isEmpty()) chat_user = GUI::SERVER_NICK ;
    else if (chat_text.startsWith(CLIENT::CHATMSG_CMD_VOTE))
    {
      // customize voting messages
      chat_text = chat_text.fromFirstOccurrenceOf(StringRef(" ") , false , true).trim() ;
      String bpi_bpm_cmd = chat_text.upToFirstOccurrenceOf(StringRef(" ") , false , true)
                                    .trim() ;
      String bpi_bpm_val = chat_text.fromFirstOccurrenceOf(StringRef(" ") , false , true)
                                    .trim() ;
      if (!bpi_bpm_val.containsOnly(NETWORK::DIGITS)) return ; // server rejects this - yes?

      chat_text = chat_user + " votes to set " + bpi_bpm_cmd + " to " + bpi_bpm_val ;
      chat_user = GUI::SERVER_NICK ;
    }
  }
  else if (is_priv_msg)
  {
    if (chat_user.isEmpty() || chat_text.isEmpty()) return ;

    chat_user += GUI::PM_TEXT ;
  }
  else if (is_join_msg || is_part_msg)
  {
    if (chat_user.isEmpty()) return ;

    chat_text = chat_user + GUI::JOINPART_TEXTa +
                ((is_join_msg)? GUI::JOIN_TEXT : GUI::PART_TEXT) + GUI::JOINPART_TEXTb ;
    chat_user = GUI::SERVER_NICK ;
  }
  Gui->chat->addChatLine(chat_user , chat_text) ;
}

void LinJam::OnSamples(float** input_buffer  , int n_input_channels  ,
                       float** output_buffer , int n_output_channels ,
                       int     n_samples     , int sample_rate)
{
  if (!IsAudioEnabled)
  {
    // clear all output buffers
    size_t n_bytes = n_samples * sizeof(float) ;
    for (int channel_n = 0 ; channel_n < n_output_channels ; ++channel_n)
      memset(output_buffer[channel_n] , 0 , n_bytes) ;
  }
  else Client->AudioProc(input_buffer  , n_input_channels  ,
                         output_buffer , n_output_channels ,
                         n_samples     , sample_rate       ) ;
}


/* NJClient runtime helpers */

void LinJam::HandleStatusChanged(int client_status)
{
DEBUG_TRACE_CONNECT_STATUS
#ifdef DEBUG_AUTOLOGIN_NYI
if (!Gui->statusbar->getStatusL().compare(GUI::DISCONNECTED_STATUS_TEXT))
{ Config->setCurrentServer(DEBUG_STATIC_CHANNEL , "nobody" , "" , true) ;
  Connect() ; }
#endif // DEBUG_AUTOLOGIN_NYI

  // server config
  if (client_status == NJClient::NJC_STATUS_OK) Config->setServer() ;

  // GUI state
  switch (client_status)
  {
    case NJClient::NJC_STATUS_DISCONNECTED: Gui->login     ->toFront(true)  ;
                                            Gui->background->toBehind(Gui->login) ;   break ;
    case NJClient::NJC_STATUS_INVALIDAUTH:  (IsAgreed())?
                                            Gui->login     ->toFront(true)  :
                                            Gui->license   ->toFront(true)  ;
                                            (IsAgreed())?
                                            Gui->background->toBehind(Gui->login)   :
                                            Gui->background->toBehind(Gui->license) ; break ;
    case NJClient::NJC_STATUS_CANTCONNECT:  Gui->login     ->toFront(true)  ;
                                            Gui->background->toBehind(Gui->login) ;   break ;
    case NJClient::NJC_STATUS_OK:           Gui->chat      ->toFront(true)  ;
                                            Gui->mixer     ->toFront(false) ;
                                            Gui->loop      ->toFront(false) ;
                                            Gui->background->toBehind(Gui->chat) ;    break ;
    case NJClient::NJC_STATUS_PRECONNECT:   Gui->login     ->toFront(true)  ;
                                            Gui->background->toBehind(Gui->login) ;   break ;
    default:                                                                          break ;
  }

  // status indicator
  String host = Client->GetHostName() ; String status_text ;
  switch (client_status)
  {
    case NJClient::NJC_STATUS_DISCONNECTED:
      status_text = GUI::DISCONNECTED_STATUS_TEXT ;                    break ;
    case NJClient::NJC_STATUS_INVALIDAUTH:
      status_text = (IsAgreed())? ((IsRoomFull())?
                    GUI::ROOM_FULL_STATUS_TEXT :
                    GUI::INVALID_AUTH_STATUS_TEXT) :
                    GUI::PENDING_LICENSE_STATUS_TEXT ;                 break ;
    case NJClient::NJC_STATUS_CANTCONNECT:
      status_text = GUI::FAILED_CONNECTION_STATUS_TEXT ;               break ;
    case NJClient::NJC_STATUS_OK:
      status_text = GUI::CONNECTED_STATUS_TEXT + host ;                break ;
    case NJClient::NJC_STATUS_PRECONNECT:
      status_text = GUI::IDLE_STATUS_TEXT ;                            break ;
    default:
      status_text = GUI::UNKNOWN_STATUS_TEXT + String(client_status) ; break ;
  }
  Gui->statusbar->setStatusL(status_text) ;
}

void LinJam::HandleUserInfoChanged()
{
#ifndef UPDATE_REMOTES
  return ;
#endif // UPDATE_REMOTES
DEBUG_TRACE_REMOTE_CHANNELS_VB

  // initialize dictionary for pruning GUI elements for parted users
  ValueTree active_users = ValueTree("active-users") ;

  // fetch remote user states from server
  char* user_c_name ; float volume ;  float pan ;          bool is_muted ;
  bool  is_rcv ;      bool  is_solo ; int   sink_channel ; bool is_stereo ; int user_idx = -1 ;
  while (user_c_name = Client->GetUserState(++user_idx , &volume , &pan , &is_muted))
  {
    Identifier user_id = Config->encodeUserId(String(user_c_name) , user_idx) ;
    if (bool(Config->shouldHideBots.getValue()) &&
        NETWORK::KNOWN_BOTS.contains(user_id)) continue ;

    // create remote user storage and GUI
    ValueTree user_store = GetOrAddRemoteUser(user_id , user_idx , volume , pan , is_muted) ;
    user_id              = user_store.getType() ;
    if (!user_store.isValid()) continue ;

    // create remote user GUI
    bool user_gui_was_added = Gui->mixer->addRemoteUser(user_store) ;

    // list this user as active for GUI pruning
    ValueTree active_user_channels = ValueTree(user_id) ;

    int channel_n = -1 ; int channel_idx ;
    while (~(channel_idx = Client->EnumUserChannels(user_idx , ++channel_n)))
    {
      // load remote channel state
      String channel_name = String(Client->GetUserChannelState(user_idx      , channel_idx ,
                                                               &is_rcv                     ,
                                                               &volume       , &pan        ,
                                                               &is_muted     , &is_solo    ,
                                                               &sink_channel , &is_stereo  )) ;

      // create remote channel storage and GUI
      ValueTree channel_store = GetOrAddRemoteChannel(user_id      , user_idx      ,
                                                      channel_name , channel_idx   ,
                                                      volume       , pan           ,
                                                      is_rcv       , is_muted      ,
                                                      is_solo      , sink_channel  ,
                                                      is_stereo) ;
      if (!channel_store.isValid()) continue ;

      // create remote channel GUI
      if (Gui->mixer->addChannel(String(user_id) , channel_store))
      {
        // update stored NJClient remote channel index
        channel_store.setProperty(CONFIG::CHANNELIDX_ID , channel_idx , nullptr) ;

        // restore stored NJClient remote channel state
        ConfigureRemoteChannel(user_store , channel_store , CONFIG::CONFIG_ALL_ID) ;
      }

      // add channel to GUI prune list
      active_user_channels.setProperty(channel_store.getType() , -1 , nullptr) ;
    }
    // add user to GUI prune list
    active_users.addChild(active_user_channels , -1 , nullptr) ;

    if (user_gui_was_added)
    {
      // update stored NJClient remote user index
      user_store.setProperty(CONFIG::USERIDX_ID , user_idx , nullptr) ;

      // restore stored NJClient remote user master state
      ValueTree channel_store = Config->getChannelById(user_id , CONFIG::MASTER_ID) ;
      ConfigureRemoteChannel(user_store , channel_store , CONFIG::CONFIG_ALL_ID) ;
    }
  }
  // prune user and channel GUIs
  Gui->mixer->pruneRemotes(active_users) ;
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

#ifdef BUGGY_CHAT_COMMANDS // (issue #19)
  Gui->chat->addChatLine(GUI::SERVER_NICK , "commands disabled") ; return ;
#endif // CHAT_COMMANDS_BUGGY

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
      Gui->chat->addChatLine(GUI::SERVER_NICK , GUI::INVALID_PM_MSG) ;
    else // if (does_user_exist(to_user)) // TODO: this safe yea ? // (issue #19)
    {
      Client->ChatMessage_Send(CLIENT::CHATMSG_TYPE_PRIVMSG.toRawUTF8() , msg.toRawUTF8()) ;
      Gui->chat->addChatLine("(PM -> " + to_user + ")" , msg) ;
    }
  }
  else Gui->chat->addChatLine(GUI::SERVER_NICK , GUI::UNKNOWN_COMMAND_MSG) ;
}

bool LinJam::IsRoomFull()
{
  String err = String(CharPointer_UTF8(Client->GetErrorStr())) ;
  return (err.isNotEmpty() && !err.compare(CLIENT::SERVER_FULL_STATUS)) ;
}


/* state helpers */

bool LinJam::InitializeAudio()
{
  IsAudioEnabled = false ; if (Audio) delete Audio ;

        int   interface_n   = int(Config->audioIfN  .getValue()) ;
        int   n_inputs      = int(Config->nInputs   .getValue()) ;
        int   n_outputs     = int(Config->nOutputs  .getValue()) ;
        int   bit_depth     = int(Config->bitDepth  .getValue()) ;
        int   sample_rate   = int(Config->sampleRate.getValue()) ;
  const char* jack_name     =     Config->jackName  .toString().toRawUTF8() ;
        char* config_string = "" ;

#ifdef _WIN32
  audioStreamer::WinAudioIf if_n = (audioStreamer::WinAudioIf)interface_n ;
  Audio = CreateConfiguredStreamer(CLIENT::WIN_INI_FILE , if_n , OnSamples) ;

DEBUG_TRACE_AUDIO_INIT_WIN

#else // _WIN32
#  ifdef _MAC
  Audio = create_audioStreamer_CoreAudio(&config_string , sample_rate ,
                                         n_inputs , bit_depth , OnSamples) ;

DEBUG_TRACE_AUDIO_INIT_MAC

#  else // _MAC
  switch (interface_n)
  {
    case 0: // JACK
      Audio = create_audioStreamer_JACK(jack_name , n_inputs , n_outputs ,
                                        OnSamples , Client) ;

DEBUG_TRACE_AUDIO_INIT_JACK

      if (Audio) break ;
    case 1: // ALSA
    default:
      Audio = create_audioStreamer_ALSA(config_string , OnSamples) ;

DEBUG_TRACE_AUDIO_INIT_ALSA
  }
#  endif // _MAC
#endif // _WIN32

  if (Audio)
  {
    IsAudioEnabled = true ;
    GuiBeatOffset = Audio->m_srate * GUI::BEAT_PROGRESS_OFFSET ;
  }

DEBUG_TRACE_AUDIO_INIT

  return (!!Audio) ;
}

void LinJam::ConfigureInitialChannels()
{
  // add master and metro channel GUI mixers and configure NJClient master channels
  ValueTree master_store = Config->masterChannels.getChildWithName(GUI::MASTER_CHANNEL_GUI_ID) ;
  ValueTree metro_store  = Config->masterChannels.getChildWithName(GUI::METRO_CHANNEL_GUI_ID) ;
  Gui->mixer->addChannel(GUI::MASTERS_GUI_ID , master_store) ;
  Gui->mixer->addChannel(GUI::MASTERS_GUI_ID , metro_store) ;
  ConfigureMasterChannel(CONFIG::CONFIG_ALL_ID) ;
  ConfigureMetroChannel( CONFIG::CONFIG_ALL_ID) ;

  // add local Channel GUI mixers and configure NJClient input channels
  for (int channel_n = 0 ; channel_n < Config->localChannels.getNumChildren() ; ++channel_n)
  {
    ValueTree channel_store = Config->localChannels.getChild(channel_n) ;

    Gui->mixer->addChannel(GUI::LOCALS_GUI_ID , channel_store) ;
    ConfigureLocalChannel(channel_store , CONFIG::CONFIG_ALL_ID) ;
  }
}

bool LinJam::PrepareSessionDirectory()
{
  File this_binary = File::getSpecialLocation(File::currentExecutableFile) ;
  File this_dir    = this_binary.getParentDirectory() ;
  SessionDir       = File(this_dir.getFullPathName() + CONFIG::SESSIONDIR) ;

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
    Client->SetLogFile((SessionDir.getFullPathName() + CONFIG::LOGFILE).toRawUTF8()) ;
  for (int user_n = 0 ; user_n < subscriptions.getNumChildren() ; ++user_n)
  {
    WDL_String user_name_wdl(subscriptions.getChild(user_n).getType().getCharPointer()) ;
    Client->config_autosubscribe_userlist.insert(user_name_wdl.Get()) ;
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

  // NOTE: the *.ninjam directories created when save_loca_audio == -1 (delete ASAP)
  //           are not being deleted implicitly as they presumably should be (issue #32)
  DirectoryIterator session_dir_iter(SessionDir , false , "*.*" , File::findFilesAndDirectories) ;
  while (session_dir_iter.next()) session_dir_iter.getFile().deleteRecursively() ;
}


/* server event handlers */

ValueTree LinJam::GetOrAddRemoteUser(Identifier user_id , int   user_idx ,
                                     float      volume  , float pan      , bool is_muted)
{
  ValueTree user_store = Config->getUserById(user_id) ;

  // create remote user storage
  bool was_previously_stored_user = user_store.isValid() ;
  if (!was_previously_stored_user)
  {
    user_store = Config->createUser(String(user_id) , user_idx , volume , pan , is_muted) ;
    user_id    = user_store.getType() ;
  }

  return user_store ;
}

ValueTree LinJam::GetOrAddRemoteChannel(Identifier user_id      , int   user_idx    ,
                                        String     channel_name , int   channel_idx ,
                                        float      volume       , float pan         ,
                                        bool       is_rcv       , bool  is_muted    ,
                                        bool       is_solo      , int   sink_n      ,
                                        bool       is_stereo                        )
{
  ValueTree  user_store    = Config->getUserById(user_id) ;
  Identifier channel_id    = Config->encodeChannelId(channel_name , channel_idx) ;
  ValueTree  channel_store = Config->getChannelById(user_id , channel_id) ;

  // create remote channel storage
  bool was_previously_stored_user = channel_store.isValid() ;
  if (!was_previously_stored_user)
    channel_store = Config->createChannel(user_id   , String(channel_id) , channel_idx ,
                                          volume    , pan                , is_rcv      ,
                                          is_muted  , is_solo            , sink_n      ,
                                          is_stereo                                    ) ;

  return channel_store ;
}


/* NJClient config helpers */

char* LinJam::GetChannelName(int channel_idx)
{
  return Client->GetLocalChannelInfo(channel_idx , NULL , NULL , NULL) ;
}

int LinJam::GetVacantLocalChannelIdx()
{
  int channel_idx = -1 ; while (GetChannelName(++channel_idx)) ;
  bool is_vacant_slot = (channel_idx < Client->GetMaxLocalChannels()) ;

  return (is_vacant_slot)? channel_idx : -1 ;
}

int LinJam::GetLocalChannelIdx(Identifier channel_id)
{
  // find local channel
  int channel_n = -1 ; int channel_idx ;
  while (~(channel_idx = LinJam::Client->EnumLocalChannels(++channel_n)))
  {
    char*  channel_c_name = GetChannelName(channel_idx) ;
    String channel_name   = String(Config->encodeChannelId(channel_c_name , channel_idx)) ;
    if (!String(channel_id).compare(channel_name)) break ;
  }

  return channel_idx ;
}

int LinJam::GetRemoteUserIdx(Identifier user_id)
{
  // find remote user
  int user_idx = Client->GetNumUsers() ; char* user_c_name ;
  while ((user_c_name = Client->GetUserState(--user_idx)))
  {
    String user_name = String(Config->encodeUserId(user_c_name , user_idx)) ;
    if (!String(user_id).compare(user_name)) break ;
  }

  return user_idx ;
}

int LinJam::GetRemoteChannelIdx(int user_idx , Identifier channel_id)
{
  // find remote channel
  int channel_n = -1 ; int channel_idx ;
  while (~(channel_idx = Client->EnumUserChannels(user_idx , ++channel_n)))
  {
    char*  channel_c_name = Client->GetUserChannelState(user_idx , channel_idx) ;
    String channel_name   = String(Config->encodeChannelId(channel_c_name , channel_idx)) ;
    if (!String(channel_id).compare(channel_name)) break ;
  }

  return channel_idx ;
}

void LinJam::ConfigureMasterChannel(Identifier a_key)
{
  ValueTree channel_store = Config->getChannelById(CONFIG::MASTERS_ID , CONFIG::MASTER_ID) ;
  if (!channel_store.isValid()) return ;

  // load stored config for this channel
  float volume   = float(channel_store[CONFIG::VOLUME_ID]) ;
  float pan      = float(channel_store[CONFIG::PAN_ID]) ;
  bool  is_muted = bool( channel_store[CONFIG::IS_MUTED_ID]) ;

  // determine which NJClient channel params to modify
  bool should_set_all      = (a_key == CONFIG::CONFIG_ALL_ID) ;
  bool should_set_volume   = (should_set_all || a_key == CONFIG::VOLUME_ID) ;
  bool should_set_pan      = (should_set_all || a_key == CONFIG::PAN_ID) ;
  bool should_set_is_muted = (should_set_all || a_key == CONFIG::IS_MUTED_ID) ;

  // configure NJClient master channel
  if (should_set_volume)   Client->config_mastervolume = (float)DB2VAL(volume) ;
  if (should_set_pan)      Client->config_masterpan    = pan ;
  if (should_set_is_muted) Client->config_mastermute   = is_muted ;
}

void LinJam::ConfigureMetroChannel(Identifier a_key)
{
  ValueTree channel_store = Config->getChannelById(CONFIG::MASTERS_ID , CONFIG::METRO_ID) ;
  if (!channel_store.isValid()) return ;

  // load stored config for this channel
  float volume    = float(channel_store[CONFIG::VOLUME_ID]) ;
  float pan       = float(channel_store[CONFIG::PAN_ID]) ;
  bool  is_muted  = bool( channel_store[CONFIG::IS_MUTED_ID]) ;
  int   source_n  = int(  channel_store[CONFIG::SOURCE_N_ID]) ;
  bool  is_stereo = bool( channel_store[CONFIG::IS_STEREO_ID]) ;

  // determine which NJClient channel params to modify
  bool should_set_all       = (a_key == CONFIG::CONFIG_ALL_ID) ;
  bool should_set_volume    = (should_set_all || a_key == CONFIG::VOLUME_ID) ;
  bool should_set_pan       = (should_set_all || a_key == CONFIG::PAN_ID) ;
  bool should_set_is_muted  = (should_set_all || a_key == CONFIG::IS_MUTED_ID) ;
  bool should_set_source_n  = (should_set_all || a_key == CONFIG::SOURCE_N_ID) ;
  bool should_set_is_stereo = (should_set_all || a_key == CONFIG::IS_STEREO_ID) ;

  // configure NJClient metro channel
  if (should_set_volume)    Client->config_metronome           = (float)DB2VAL(volume) ;
  if (should_set_pan)       Client->config_metronome_pan       = pan ;
  if (should_set_is_muted)  Client->config_metronome_mute      = is_muted ;
  if (should_set_source_n)  Client->config_metronome_channel   = source_n ;
  if (should_set_is_stereo) Client->config_metronome_stereoout = is_stereo ;
}

void LinJam::ConfigureLocalChannel(ValueTree channel_store , Identifier a_key)
{
  if (!channel_store.isValid()) return ;

  // load stored config for this channel
  Identifier channel_id =       channel_store.getType() ;
  float      volume     = float(channel_store[CONFIG::VOLUME_ID]) ;
  float      pan        = float(channel_store[CONFIG::PAN_ID]) ;
  bool       is_xmit    = bool( channel_store[CONFIG::IS_XMIT_ID]) ;
  bool       is_muted   = bool( channel_store[CONFIG::IS_MUTED_ID]) ;
  bool       is_solo    = bool( channel_store[CONFIG::IS_SOLO_ID]) ;
  int        source_n   = int(  channel_store[CONFIG::SOURCE_N_ID]) ;
  int        bit_depth  = int(  channel_store[CONFIG::BITDEPTH_ID]) ;
  bool       is_stereo  = bool( channel_store[CONFIG::IS_STEREO_ID]) ;

  // determine which NJClient channel params to modify
  bool should_set_all       = (a_key == CONFIG::CONFIG_ALL_ID) ;
  bool should_set_name      = (should_set_all || false) ; // TODO: (issue #23)
  bool should_set_volume    = (should_set_all || a_key == CONFIG::VOLUME_ID) ;
  bool should_set_pan       = (should_set_all || a_key == CONFIG::PAN_ID) ;
  bool should_set_is_xmit   = (should_set_all || a_key == CONFIG::IS_XMIT_ID) ;
  bool should_set_is_muted  = (should_set_all || a_key == CONFIG::IS_MUTED_ID) ;
  bool should_set_is_solo   = (should_set_all || a_key == CONFIG::IS_SOLO_ID) ;
  bool should_set_source_n  = (should_set_all || a_key == CONFIG::SOURCE_N_ID) ;
  bool should_set_bit_depth = (should_set_all || a_key == CONFIG::BITDEPTH_ID) ;
  bool should_set_is_stereo = (should_set_all || a_key == CONFIG::IS_STEREO_ID) ;

DEBUG_TRACE_CONFIGURE_LOCAL_CHANNEL

  // find NJClient channel_idx for existing or new channel
  int channel_idx ; if (!(~(channel_idx = GetLocalChannelIdx(channel_id))) &&
                        !(~(channel_idx = GetVacantLocalChannelIdx()))      ) return ;

  // convert channel name from juce::String into non-const char*
  String name = String(channel_id) ; char* new_name = NULL ; WDL_String name_wdl ;
  if (should_set_name) { name_wdl.Set(name.toRawUTF8()) ; new_name = name_wdl.Get() ; }

  // configure NJClient local channel
  if (should_set_name || should_set_source_n || should_set_bit_depth || should_set_is_xmit)
    Client->SetLocalChannelInfo(channel_idx          , new_name  ,
                                should_set_source_n  , source_n  ,
                                should_set_bit_depth , bit_depth ,
                                should_set_is_xmit   , is_xmit   ) ;

  if (should_set_volume || should_set_pan || should_set_is_muted || should_set_is_solo)
    Client->SetLocalChannelMonitoring(channel_idx                                 ,
                                      should_set_volume   , (float)DB2VAL(volume) ,
                                      should_set_pan      , pan                   ,
                                      should_set_is_muted , is_muted              ,
                                      should_set_is_solo  , is_solo               ) ;
  Client->NotifyServerOfChannelChange() ;
}

void LinJam::ConfigureRemoteChannel(ValueTree  user_store , ValueTree channel_store ,
                                    Identifier a_key                                )
{
  if (!user_store.isValid() || !channel_store.isValid()) return ;

  // load stored config for this channel
  Identifier user_id     = user_store   .getType() ;
  Identifier channel_id  = channel_store.getType() ;
  int        user_idx    = int(  user_store   [CONFIG::USERIDX_ID]) ;
  int        channel_idx = int(  channel_store[CONFIG::CHANNELIDX_ID]) ;
  int        channel_n   = -1 ;
  float      volume      = float(channel_store[CONFIG::VOLUME_ID]) ;
  float      pan         = float(channel_store[CONFIG::PAN_ID]) ;
  bool       is_rcv      = bool( channel_store[CONFIG::IS_XMIT_ID]) ;
  bool       is_muted    = bool( channel_store[CONFIG::IS_MUTED_ID]) ;
  bool       is_solo     = bool( channel_store[CONFIG::IS_SOLO_ID]) ;
  int        sink_n      = int(  channel_store[CONFIG::SOURCE_N_ID]) ;
  bool       is_stereo   = bool( channel_store[CONFIG::IS_STEREO_ID]) ;

  // determine which NJClient channel params to modify
  bool should_set_all       = (a_key == CONFIG::CONFIG_ALL_ID) ;
  bool should_set_volume    = (should_set_all || a_key == CONFIG::VOLUME_ID) ;
  bool should_set_pan       = (should_set_all || a_key == CONFIG::PAN_ID) ;
  bool should_set_is_rcv    = (should_set_all || a_key == CONFIG::IS_XMIT_ID) ;
  bool should_set_is_muted  = (should_set_all || a_key == CONFIG::IS_MUTED_ID) ;
  bool should_set_is_solo   = (should_set_all || a_key == CONFIG::IS_SOLO_ID) ;
  bool should_set_sink_n    = (should_set_all || a_key == CONFIG::SOURCE_N_ID) ;
  bool should_set_is_stereo = (should_set_all || a_key == CONFIG::IS_STEREO_ID) ;

DEBUG_TRACE_CONFIGURE_REMOTE

  if (channel_id == CONFIG::MASTER_ID)
  {
    if      ((should_set_is_rcv && !is_rcv) || (should_set_is_solo && is_solo))
      // apply user master pseudo rcv or solo control to all user channels
      while (~(channel_idx = Client->EnumUserChannels(user_idx , ++channel_n)))
        Client->SetUserChannelState(user_idx           , channel_idx              ,
                                    should_set_is_rcv  , is_rcv                   ,
                                    false              , CONFIG::DEFAULT_VOLUME   ,
                                    false              , CONFIG::DEFAULT_PAN      ,
                                    false              , CONFIG::DEFAULT_IS_MUTED ,
                                    should_set_is_solo , is_solo                  ,
                                    false              , CONFIG::DEFAULT_SOURCE_N ,
                                    false              , CONFIG::DEFAULT_IS_STEREO) ;
    else if ((should_set_is_rcv && is_rcv) || (should_set_is_solo && !is_solo))
      // restore per channel rcv or solo state
      while (~(channel_idx = Client->EnumUserChannels(user_idx , ++channel_n)))
      {
        channel_store = Config->getChannelByIdx(user_store , channel_idx) ;
        ConfigureRemoteChannel(user_store , channel_store , a_key) ;
      }
    else if (should_set_volume || should_set_pan || should_set_is_muted)
      // configure NJClient remote master channel
      Client->SetUserState(user_idx                                    ,
                           should_set_volume   , (float)DB2VAL(volume) ,
                           should_set_pan      , pan                   ,
                           should_set_is_muted , is_muted              ) ;
  }
  else
    // configure NJClient remote channel
    Client->SetUserChannelState(user_idx             , channel_idx           ,
                                should_set_is_rcv    , is_rcv                ,
                                should_set_volume    , (float)DB2VAL(volume) ,
                                should_set_pan       , pan                   ,
                                should_set_is_muted  , is_muted              ,
                                should_set_is_solo   , is_solo               ,
                                should_set_sink_n    , sink_n                ,
                                should_set_is_stereo , is_stereo             ) ;
}
