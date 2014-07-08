/*
  ==============================================================================

    Linjam.cpp
    Created: 24 May 2014 5:03:01pm
    Author:  me

  ==============================================================================
*/

// #define DEBUG_STATIC_CHANNEL "localhost:2049"
#define DEBUG_STATIC_CHANNEL "ninbot.com:2049"
// #define DEBUG_STATIC_CHANNEL "ninjamer.com:2050"


#include "LinJam.h"
#include "Channel.h"
#include "Constants.h"


/* LinJam public class variables */

LinJamConfig* LinJam::Config ;


/* LinJam private class variables */

NJClient*      LinJam::Client                = nullptr ;          // Initialize()
MainContent*   LinJam::Gui                   = nullptr ;          // Initialize()
audioStreamer* LinJam::Audio                 = nullptr ;          // Initialize()
SortedSet<int> LinJam::FreeInputChannels     = SortedSet<int>() ; // InitializeAudio() ;
SortedSet<int> LinJam::FreeInputChannelPairs = SortedSet<int>() ; // InitializeAudio() ;
bool           LinJam::IsAudioEnabled        = false ;            // InitializeAudio()
float          LinJam::GuiBeatOffset ;                            // InitializeAudio()
File           LinJam::SessionDir ;                               // PrepareSessionDirectory()
int            LinJam::PrevStatus ;                               // Initialize()
bool           LinJam::IsInitialized         = false ;            // Initialize()
String         LinJam::PrevRecordingTime ;                        // Disconnect()


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

  IsInitialized = true ;

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
                                GetLocalChannelDisplayName(channel_idx)         ,
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

  // NOTE: parsing recording time is brittle - strictly dependent on the values
  //       in NETWORK::KNOWN_HOSTS , NETWORK::KNOWN_BOTS , and CLIENT::BOT_CHANNELIDX
  String host           = String(Client->GetHostName()) ;
  String bpi            = String(Client->GetBPI()) ;
  String bpm            = String((int)Client->GetActualBPM()) ;
  bool   server_has_bot = NETWORK::KNOWN_HOSTS.contains(host) ;
  String recording_time = String::empty ;

  if (server_has_bot)
  {
    int bot_n = NETWORK::N_KNOWN_BOTS ; int bot_idx ;
    while (bot_n--)
      if (~(bot_idx = GetRemoteUserIdx(NETWORK::KNOWN_BOTS.getUnchecked(bot_n))))
        recording_time = " - " + GetRemoteChannelName(bot_idx , CLIENT::BOT_CHANNELIDX) ;

    bool has_recording_time_changed = recording_time.compare(PrevRecordingTime) ;
    bool is_this_first_pass         = PrevRecordingTime.isEmpty() ;
    bool should_show_recording_time = (has_recording_time_changed && !is_this_first_pass) ;

    PrevRecordingTime = recording_time ;
    if (!should_show_recording_time) recording_time = String::empty ;
  }

  Gui->setTitle(host + " - " + bpi + "bpi / " + bpm + "bpm" + recording_time) ;
}


/* getters/setters */

bool LinJam::IsAgreed() { return bool(Config->currentIsAgreed.getValue()) ; }

SortedSet<int> LinJam::GetFreeInputChannels() { return FreeInputChannels ; }

SortedSet<int> LinJam::GetFreeInputChannelPairs() { return FreeInputChannelPairs ; }


/* GUI event handlers */

bool LinJam::AddLocalChannel(String channel_name , bool is_stereo , int set_idx)
{
DEBUG_TRACE_ADD_LOCAL_CHANNEL

  // extract source_n from the appropriate free list (set members are 1-based)
  int freeset_member = (!is_stereo)? FreeInputChannels    [set_idx] :
                                     FreeInputChannelPairs[set_idx] ;
  int source_n       = freeset_member - 1 ;

  // sanity check
  int  n_vacant_channels         = GetNumVacantChannels() ;
  bool are_sufficient_n_channels = (!is_stereo && n_vacant_channels >= 1 ||
                                     is_stereo && n_vacant_channels >= 2) ;
  if (!(~set_idx)                ||                  // empty list or invalid index
      !are_sufficient_n_channels || !freeset_member) // corrupted list or xml
    return false ;                                   // (no free channels)

  // remove selected channel(s) from free lists
  if (!is_stereo)
  {
    int pair_member = (freeset_member % 2)? freeset_member : freeset_member - 1 ;
    FreeInputChannels    .removeValue(freeset_member) ;
    FreeInputChannelPairs.removeValue(freeset_member) ;
  }
  else
  {
    FreeInputChannels    .removeValue(freeset_member) ;
    FreeInputChannels    .removeValue(freeset_member + 1) ;
    FreeInputChannelPairs.removeValue(freeset_member) ;
  }

  // add new local channel(s)
  CreateLocalChannel(channel_name , is_stereo , source_n) ;

// DEBUG_TRACE_DUMP_FREE_INPUTS_VB
    SortedSet<int> monos   = FreeInputChannels ;     int n_monos   = monos.size() ;
    SortedSet<int> stereos = FreeInputChannelPairs ; int n_stereos = stereos.size() ;
    String dump = "AddLocalChannel() " + String(n_monos)   + " FreeInputChannels     = [" ;
    for (int i = 0 ; i < n_monos ; ++i)   dump += String(monos[i])   + " " ;
    DBG(dump + "]") ;
    dump        = "AddLocalChannel() " + String(n_stereos) + " FreeInputChannelPairs = [" ;
    for (int i = 0 ; i < n_stereos ; ++i) dump += String(stereos[i]) + " " ;
    DBG(dump + "]") ;

  return true ;
}

void LinJam::RemoveLocalChannel(ValueTree channel_store)
{
  if (!IsInitialized) return ; // destroyed corrupted storage

DEBUG_TRACE_REMOVE_LOCAL_CHANNEL

  bool channel_idx    = int( channel_store[CONFIG::CHANNELIDX_ID]) ;
  int  source_n       = int( channel_store[CONFIG::SOURCE_N_ID]) ;
  bool is_stereo      = bool(channel_store[CONFIG::IS_STEREO_ID]) ;
  int  freeset_member = source_n + 1 ; // list entries are 1-based

  // add removed channel(s) to free lists
  if (!is_stereo)
  {
    // pair is source +1 if this source could be the base of a stereo pair (source_n even)
    // pair is source -1 if this source could be the pair of a stereo pair (source_n odd)
    int stereo_pair_offset = 1 - (2 * !(freeset_member % 2)) ;

    FreeInputChannels.add(freeset_member) ;
    if (FreeInputChannels.contains(freeset_member + stereo_pair_offset))
      FreeInputChannelPairs.add(freeset_member) ;

    Client->DeleteLocalChannel(channel_idx) ;
  }
  else
  {
    FreeInputChannels    .add(freeset_member) ;
    FreeInputChannels    .add(freeset_member + 1) ;
    FreeInputChannelPairs.add(freeset_member) ;

    Client->DeleteLocalChannel(channel_idx) ;
    String pair_name = String(channel_store.getType()) + CLIENT::STEREO_R_POSTFIX ;
    Client->DeleteLocalChannel(GetLocalChannelIdx(pair_name)) ;
  }

  Client->NotifyServerOfChannelChange() ;

// DEBUG_TRACE_DUMP_FREE_INPUTS_VB
    SortedSet<int> monos   = FreeInputChannels ;     int n_monos   = monos.size() ;
    SortedSet<int> stereos = FreeInputChannelPairs ; int n_stereos = stereos.size() ;
    String dump = "RemoveLocalChannel() " + String(n_monos)   + " FreeInputChannels     = [" ;
    for (int i = 0 ; i < n_monos ; ++i)   dump += String(monos[i])   + " " ;
    DBG(dump + "]") ;
    dump        = "RemoveLocalChannel() " + String(n_stereos) + " FreeInputChannelPairs = [" ;
    for (int i = 0 ; i < n_stereos ; ++i) dump += String(stereos[i]) + " " ;
    DBG(dump + "]") ;
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

    Gui->chat->setTopic(chat_text) ;

    if (chat_user.isEmpty()) chat_text = GUI::TOPIC_TEXT                 + chat_text ;
    else                     chat_text = chat_user + GUI::SET_TOPIC_TEXT + chat_text ;
    chat_user = GUI::SERVER_NICK ;
  }
  else if (is_bcast_msg)
  {
    if (chat_text.isEmpty()) return ;

    if      (chat_user.isEmpty()) chat_user = GUI::SERVER_NICK ;
    else if (chat_text.startsWith(CLIENT::CHATMSG_CMD_VOTE))
    {
      // customize voting messages
      StringArray tokens = StringArray::fromTokens(StringRef(chat_text) , false) ;
      String bpi_bpm_cmd = tokens[1] ;
      String bpi_bpm_val = tokens[2] ;

      bool is_bpi_msg = !bpi_bpm_cmd.compare(CLIENT::CHATMSG_CMD_BPI.substring(1).trim()) ;
      bool is_bpm_msg = !bpi_bpm_cmd.compare(CLIENT::CHATMSG_CMD_BPM.substring(1).trim()) ;
      if ((is_bpi_msg || is_bpm_msg) && bpi_bpm_val.containsOnly(NETWORK::DIGITS))
      {
        chat_text = chat_user + " votes to set " + bpi_bpm_cmd + " to " + bpi_bpm_val ;
        chat_user = GUI::SERVER_NICK ;
      }
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

  // GUI state
  switch (client_status)
  {
    case NJClient::NJC_STATUS_DISCONNECTED: Gui->login     ->toFront(true)  ;
                                            Gui->background->toBehind(Gui->login) ;   break ;
    case NJClient::NJC_STATUS_INVALIDAUTH:  if (IsAgreed())
                                            {
                                              Gui->login     ->toFront(true) ;
                                              Gui->background->toBehind(Gui->login) ;
                                              Config->currentIsAgreed = false ;
                                            }
                                            else
                                            {
                                              Gui->license   ->toFront(true)  ;
                                              Gui->background->toBehind(Gui->license) ;
                                            }                                         break ;
    case NJClient::NJC_STATUS_CANTCONNECT:  Gui->login     ->toFront(true)  ;
                                            Gui->background->toBehind(Gui->login) ;   break ;
    case NJClient::NJC_STATUS_OK:           Gui->chat      ->toFront(true)  ;
                                            Gui->mixer     ->toFront(false) ;
                                            Gui->loop      ->toFront(false) ;
                                            UpdateGuiLowPriority() ;
                                            Gui->background->toBehind(Gui->chat) ;    break ;
    case NJClient::NJC_STATUS_PRECONNECT:   Gui->login     ->toFront(true)  ;
                                            Gui->background->toBehind(Gui->login) ;   break ;
    default:                                                                          break ;
  }
}

void LinJam::HandleUserInfoChanged()
{
#ifndef UPDATE_REMOTES
  return ;
#endif // UPDATE_REMOTES
DEBUG_TRACE_REMOTE_CHANNELS_VB

  bool server_has_bot   = NETWORK::KNOWN_HOSTS.contains(String(Client->GetHostName())) ;
  bool should_hide_bots = server_has_bot && bool(Config->shouldHideBots.getValue()) ;

  // initialize dictionary for pruning GUI elements for parted users
  ValueTree active_users = ValueTree("active-users") ;

  // fetch remote user states from server
  char* user_c_name ; float volume ;  float pan ;    bool is_muted ;
  bool  is_rcv ;      bool  is_solo ; int   sink_n ; bool is_stereo ; int user_idx = -1 ;
  while (user_c_name = Client->GetUserState(++user_idx , &volume , &pan , &is_muted))
  {
    Identifier user_id = Config->encodeUserId(String(user_c_name) , user_idx) ;
    if (should_hide_bots && NETWORK::KNOWN_BOTS.contains(user_id)) continue ;

    // get or create remote user storage
    ValueTree user_store = Config->getOrCreateUser(String(user_id) , user_idx ,
                                                   volume          , pan      , is_muted) ;
    String    user_name  = String(user_id = user_store.getType()) ;
    if (!user_store.isValid()) continue ;

    // create remote user GUI
    bool user_gui_was_added = Gui->mixer->addRemoteUser(user_store) ;

    // list this user as active for GUI pruning
    ValueTree active_user_channels = ValueTree(user_id) ;

    int channel_n = -1 ; int channel_idx ;
    while (~(channel_idx = Client->EnumUserChannels(user_idx , ++channel_n)))
    {
      // load remote channel state
      String channel_name = String(Client->GetUserChannelState(user_idx  , channel_idx ,
                                                               &is_rcv   , &volume     ,
                                                               &pan      , &is_muted   ,
                                                               &is_solo  , &sink_n     ,
                                                               &is_stereo              )) ;

      // get or create remote channel storage
      Identifier channel_id    = Config->encodeChannelId(channel_name , channel_idx) ;
      ValueTree  channel_store = Config->getOrCreateChannel(user_id     , channel_name ,
                                                            channel_idx , volume       ,
                                                            pan         , is_rcv       ,
                                                            is_muted    , is_solo      ,
                                                            sink_n      , is_stereo    ) ;
      if (!channel_store.isValid()) continue ;

      // create remote channel GUI
      if (Gui->mixer->addChannel(user_name , channel_store))
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
                           !command.compare(CLIENT::CHATMSG_CMD_BPI)   ||
                           !command.compare(CLIENT::CHATMSG_CMD_BPM)    ) ;

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
    GuiBeatOffset  = Audio->m_srate * GUI::BEAT_PROGRESS_OFFSET ;

    // populate input channel names arrays for ChannelConfig GUI
    int n_input_channels = Audio->m_innch ;
    FreeInputChannels.clear() ; FreeInputChannelPairs.clear() ;
    for (int channel_n = 0 ; channel_n < n_input_channels ; ++channel_n)
    {
      int list_entry = channel_n + 1 ; // list entries are 1-based
      FreeInputChannels.add(list_entry) ;
      if (list_entry % 2 && channel_n < n_input_channels)
        FreeInputChannelPairs.add(list_entry) ;
    }
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
  ValueTree channels = Config->localChannels ;
  for (int channel_n = 0 ; channel_n < channels.getNumChildren() ; ++channel_n)
  {
    ValueTree channel_store = Config->localChannels.getChild(channel_n) ;
    String    channel_name  = String(channel_store.getType()) ;
    bool      is_stereo     = bool(channel_store[CONFIG::IS_STEREO_ID]) ;
    int       channel_idx   = int( channel_store[CONFIG::CHANNELIDX_ID]) ;

    if (!AddLocalChannel(channel_name , is_stereo , channel_idx))
    {
      // destroy corrupted storage
      Config->localChannels.removeChild(channel_store , nullptr) ;
      --channel_n ;
    }
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


/* config storage helpers */

void LinJam::CreateLocalChannel(String channel_name , bool is_stereo , int source_n)
{
DEBUG_TRACE_CREATE_LOCAL_CHANNEL

  // ensure that we do not exceed our maximum number of local channels
  int channel_idx = GetVacantLocalChannelIdx() ; if (!(~channel_idx)) return ;

  // create local channel storage
  if (!channel_name.compare(CONFIG::DEFAULT_CHANNEL_NAME)) channel_name = String::empty ;
  Identifier channel_id    = Config->encodeChannelId(channel_name , channel_idx) ;
  ValueTree  channel_store = Config->getOrCreateChannel(GUI::LOCALS_ID           ,
                                                        channel_name             ,
                                                        channel_idx              ,
                                                        CONFIG::DEFAULT_VOLUME   ,
                                                        CONFIG::DEFAULT_PAN      ,
                                                        CONFIG::DEFAULT_IS_XMIT  ,
                                                        CONFIG::DEFAULT_IS_MUTED ,
                                                        CONFIG::DEFAULT_IS_SOLO  ,
                                                        source_n                 ,
                                                        is_stereo                ) ;
  InstantiateLocalChannel(channel_store , channel_idx) ;
}


/* NJClient config helpers */

void LinJam::InstantiateLocalChannel(ValueTree channel_store , int channel_idx)
{
DEBUG_TRACE_INSTANTIATE_LOCAL_CHANNEL

  if (!channel_store.isValid()) return ;

  // create local Channel GUI and configure NJClient input channel
  if (Gui->mixer->addChannel(GUI::LOCALS_GUI_ID , channel_store))
    channel_store.setProperty(CONFIG::CHANNELIDX_ID , channel_idx , nullptr) ;
  String channel_name = String(channel_store.getType()) + CLIENT::STEREO_L_POSTFIX ;
  ConfigureLocalChannel(channel_store , CONFIG::CONFIG_ALL_ID , channel_name) ;

  if (is_stereo)
  {
    String     pair_name  = String(channel_store.getType()) + CLIENT::STEREO_R_POSTFIX ;
    ValueTree  pair_store = channel_store.createCopy() ;
    int        pair_idx   = GetVacantLocalChannelIdx() ; if (!(~pair_idx)) return ;
    pair_store.setProperty(CONFIG::CHANNELIDX_ID , pair_idx , nullptr) ;
    ConfigureLocalChannel(pair_store , CONFIG::CONFIG_ALL_ID , pair_name) ;
  }
}

int LinJam::GetNumActiveChannels()
{
  int n_channels = -1 ; while (~Client->EnumLocalChannels(++n_channels)) ;
  return n_channels ;
}

int LinJam::GetNumVacantChannels()
{
  return Audio->m_innch - GetNumActiveChannels() ;
}

int LinJam::GetVacantLocalChannelIdx()
{
  // find the first vacant NJClient local channel slot index
  int channel_idx = -1 ; while (GetLocalChannelClientName(++channel_idx).isNotEmpty()) ;
  bool is_vacant_slot = (channel_idx < Audio->m_innch) ;

  return (is_vacant_slot)? channel_idx : -1 ;
}

String LinJam::GetLocalChannelClientName(int channel_idx)
{
  return Client->GetLocalChannelInfo(channel_idx , NULL , NULL , NULL) ;
}

String LinJam::GetChannelDisplayName(ValueTree channels , int channel_idx)
{
  ValueTree channel_store = Config->getChannelByIdx(channels , channel_idx) ;
  return String(channel_store.getType()) ; ;
}

String LinJam::GetLocalChannelDisplayName(int channel_idx)
{
  return GetChannelDisplayName(Config->localChannels , channel_idx) ;
}

String LinJam::GetRemoteChannelName(int user_idx , int channel_idx)
{
  return String(Client->GetUserChannelState(user_idx , channel_idx)) ;
}

int LinJam::GetLocalChannelIdx(Identifier channel_id)
{
  // find local channel slot index
  int channel_n = -1 ; int channel_idx ;
  while (~(channel_idx = Client->EnumLocalChannels(++channel_n)))
  {
    String     channel_name = GetLocalChannelClientName(channel_idx) ;
    Identifier id           = Config->encodeChannelId(channel_name , channel_idx) ;
    if (channel_id == id) break ;
  }

  return channel_idx ;
}

int LinJam::GetRemoteUserIdx(Identifier user_id)
{
  // find remote user slot index
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
  // find remote channel slot index
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

void LinJam::ConfigureLocalChannel(ValueTree channel_store , Identifier a_key ,
                                   String    new_name                         )
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
  char* name = NULL ; WDL_String name_wdl ;
  if (should_set_name)
  {
    // TODO: name changes will not yet persist (issue #23)
    //       for now this is only to set the NJClient name
    //       to something other than the stored name (e.g. stereo-L)
    Identifier new_id = Config->encodeChannelId(new_name , channel_idx) ;
    name_wdl.Set(String(new_id).toRawUTF8()) ; name = name_wdl.Get() ;
  }

  // configure NJClient local channel
  if (should_set_name || should_set_source_n || should_set_bit_depth || should_set_is_xmit)
    Client->SetLocalChannelInfo(channel_idx          , name      ,
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
