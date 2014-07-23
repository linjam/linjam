/*
  ==============================================================================

    Linjam.cpp
    Created: 24 May 2014 5:03:01pm
    Author:  me

  ==============================================================================
*/

#include "LinJam.h"
#include "Channel.h"
#include "Constants.h"


#if DEBUG
#  include "./Trace/TraceLinJam.h"

#  ifdef DEBUG_AUTOLOGIN
#  define DEBUG_STATIC_CHANNEL "localhost:2049"
// #    define DEBUG_STATIC_CHANNEL "ninbot.com:2049"
// #  define DEBUG_STATIC_CHANNEL "ninjamer.com:2049"
#  endif // DEBUG_AUTOLOGIN
#endif // DEBUG


/* LinJam class public class variables */

LinJamConfig* LinJam::Config ;


/* LinJam class private class variables */

NJClient*      LinJam::Client                = nullptr ;          // Initialize()
MainContent*   LinJam::Gui                   = nullptr ;          // Initialize()
audioStreamer* LinJam::Audio                 = nullptr ;          // Initialize()
SortedSet<int> LinJam::FreeInputChannels     = SortedSet<int>() ; // InitializeAudio() ;
SortedSet<int> LinJam::FreeInputChannelPairs = SortedSet<int>() ; // InitializeAudio() ;
bool           LinJam::IsAudioEnabled        = false ;            // InitializeAudio()
double         LinJam::GuiBeatOffset ;                            // InitializeAudio()
File           LinJam::SessionDir ;                               // PrepareSessionDirectory()
int            LinJam::PrevStatus ;                               // Initialize()
bool           LinJam::IsInitialized         = false ;            // Initialize()
String         LinJam::PrevRecordingTime ;                        // Disconnect()


/* LinJam class public class methods */

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

  String host         =      Config->host.toString() ;
  String login        =      Config->login.toString() ;
  String pass         =      Config->pass.toString() ;
  bool   is_anonymous = bool(Config->isAnonymous.getValue()) ;

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

void LinJam::UpdateGuiHighPriority() { UpdateLoopProgress() ; UpdateVuMeters() ; }

void LinJam::UpdateGuiLowPriority() { UpdateRecordingTime() ; }


/* getters/setters */

bool LinJam::IsAgreed()
{
  ValueTree server              = Config->getCurrentServer() ;
  bool      should_always_agree = server.isValid() &&
                                  bool(server.getProperty(CONFIG::SHOULD_AGREE_ID)) ;
  bool      is_agreed           = bool(Config->isAgreed.getValue()) ||
                                  should_always_agree ;

  return is_agreed ;
}

SortedSet<int> LinJam::GetFreeInputChannels() { return FreeInputChannels ; }

SortedSet<int> LinJam::GetFreeInputChannelPairs() { return FreeInputChannelPairs ; }


/* GUI event handlers */

bool LinJam::AddLocalChannel(ValueTree channel_store)
{
DEBUG_TRACE_ADD_LOCAL_CHANNEL

  int  channel_idx = int(channel_store[CONFIG::CHANNEL_IDX_ID]) ;
  int  source_n    = int(channel_store[CONFIG::SOURCE_N_ID]) ;
  bool is_stereo   = int(channel_store[CONFIG::STEREO_ID]) != CONFIG::MONO ;

  // sanity check
  int  max_n_channels            = Client->GetMaxLocalChannels() ;
  bool is_valid_channel_idx      = channel_idx >= 0 && channel_idx < max_n_channels ;
  bool does_channel_exist        = IsConfiguredChannel(channel_idx) ;
  bool is_valid_source_n         = source_n >= 0 && source_n < GetNumInputChannels() ;
  int  n_vacant_channels         = GetNumVacantChannels() ;
  bool are_sufficient_n_channels = (!is_stereo && n_vacant_channels >= 1) ||
                                    (is_stereo && n_vacant_channels >= 2)  ;
  if (does_channel_exist || !is_valid_source_n || !are_sufficient_n_channels)
    return false ;

  // assign NJClient channel index for new unstored local channel
  if (!is_valid_channel_idx)
  {
    channel_idx = GetVacantLocalChannelIdx() ;
    channel_store.setProperty(CONFIG::CHANNEL_IDX_ID , channel_idx , nullptr) ;
  }

  // add new channel to store
  channel_store = Config->addChannel(Config->localChannels , channel_store) ;
  if (!channel_store.isValid()) return false ;

DEBUG_TRACE_DUMP_FREE_INPUTS_VB
DEBUG_TRACE_INSTANTIATE_LOCAL_CHANNEL

  // create local Channel GUI
  Gui->mixer->addChannel(GUI::LOCALS_GUI_ID , channel_store) ;

  // configure NJClient
  ConfigureLocalChannel(channel_store , CONFIG::CONFIG_INIT_ID) ;

  return true ;
}

void LinJam::RemoveLocalChannel(ValueTree channel_store)
{
  if (!IsInitialized) return ; // destroyed corrupted storage

DEBUG_TRACE_REMOVE_LOCAL_CHANNEL

  Identifier channel_id  = channel_store.getType() ;
  int        channel_idx = int(channel_store[CONFIG::CHANNEL_IDX_ID]) ;
  int        pair_idx    = int(channel_store[CONFIG::PAIR_IDX_ID]) ;

  // configure NJClient
  Client->DeleteLocalChannel(channel_idx) ;
  Client->DeleteLocalChannel(pair_idx) ;

  Client->NotifyServerOfChannelChange() ;

  // destroy channel GUI
  Gui->mixer->removeChannel(GUI::LOCALS_GUI_ID , channel_id) ;

  // destroy channel storage
  Config->destroyChannel(Config->localChannels , channel_store) ;

DEBUG_TRACE_DUMP_FREE_INPUTS_VB
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
  if (!IsAgreed()) Gui->license->setLicenseText(CharPointer_UTF8(license_text)) ;

DEBUG_TRACE_LICENSE

  return IsAgreed() ;
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
#ifdef DEBUG_AUTOLOGIN
if (client_status == NJClient::NJC_STATUS_PRECONNECT)
{ Config->setCurrentServer(DEBUG_STATIC_CHANNEL , "nobody" , "" , true) ;
  LinJam::Config->isAgreed = true ; Connect() ; }
#endif // DEBUG_AUTOLOGIN

  // server config
  if (client_status == NJClient::NJC_STATUS_OK) Config->setServer() ;

  // status indicator
  String client_error_msg = CharPointer_UTF8(Client->GetErrorStr()) ;
  bool   is_room_full     = !client_error_msg.compare(CLIENT::SERVER_FULL_STATUS) ;
  String host             = Client->GetHostName() ; String status_text ;
  switch (client_status)
  {
    case NJClient::NJC_STATUS_DISCONNECTED:
      status_text = GUI::DISCONNECTED_STATUS_TEXT ;                    break ;
    case NJClient::NJC_STATUS_INVALIDAUTH:
      status_text = (IsAgreed())? ((is_room_full)?
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
                                              Gui   ->login     ->toFront(true) ;
                                              Gui   ->background->toBehind(Gui->login) ;
                                              Config->isAgreed = false ;
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

  // initialize dictionary for pruning parted users GUI elements
  ValueTree active_users = ValueTree("active-users") ;

  // fetch remote user states from server
  int user_idx = -1 ; String user_name ;
  while ((user_name = GetRemoteUserName(++user_idx)).isNotEmpty())
  {
    Identifier user_id   = Config->makeUserId(user_name , user_idx) ;
    String     user_name = String(user_id) ;
    if (should_hide_bots && NETWORK::KNOWN_BOTS.contains(user_id)) continue ;

    // get or create remote user storage
    ValueTree user_store = Config->getOrAddRemoteUser(user_name , user_idx) ;
    user_id              = user_store.getType() ;
    if (!user_store.isValid()) continue ;

    // update stored NJClient remote user index
    user_store.setProperty(CONFIG::USER_IDX_ID , user_idx , nullptr) ;

    // create remote user GUI
    if (Gui->mixer->addRemoteUser(user_store))
    {
      // create remote master channel storage
      ValueTree master_store = Config->getOrAddRemoteChannel(user_id , CONFIG::MASTER_KEY) ;
      if (!master_store.isValid()) continue ;

      // create remote master channel GUI and restore stored NJClient user state
      if (Gui->mixer->addChannel(user_id , master_store))
        ConfigureRemoteChannel(user_store , master_store , CONFIG::CONFIG_INIT_ID) ;
    }

    // initialize array for pruning removed channels GUI elements
    Array<var> active_channels = Array<var>() ;

    int channel_n = -1 ; int channel_idx ;
    while (~(channel_idx = Client->EnumUserChannels(user_idx , ++channel_n)))
    {
      // get or create remote channel storage
      String    channel_name  = GetRemoteChannelClientName(user_idx , channel_idx) ;
      ValueTree channel_store = Config->getOrAddRemoteChannel(user_id     , channel_name ,
                                                              channel_idx                ) ;
      String    stored_name   = GetStoredChannelName(channel_store) ;
      if (!channel_store.isValid()) continue ;

      // rename existing channel (and GUI asynchronously)
      if (channel_name.compare(stored_name))
        channel_store.setProperty(CONFIG::CHANNEL_NAME_ID , channel_name , nullptr) ;

      // update faux-stereo status (configures NJClient and GUI asynchronously)
      int stereo_status = Config->setRemoteStereo(user_store , channel_store , stored_name) ;

      // create remote channel GUI and restore stored NJClient remote channel state
      if (Gui->mixer->addChannel(user_id , channel_store))
        ConfigureRemoteChannel(user_store , channel_store , CONFIG::CONFIG_INIT_ID) ;

      // add channel to GUI prune list unless hidden stereo pair channel
      if (stereo_status != CONFIG::STEREO_R)
        active_channels.add(var(String(channel_store.getType()))) ;
    }
    // add user to GUI prune list
    active_users.setProperty(user_id , active_channels , nullptr) ;
  }
  // prune user and channel GUIs
  Gui->mixer->pruneRemotes(active_users) ;
}

void LinJam::UpdateLoopProgress()
{
#ifndef UPDATE_LOOP_PROGRESS_GUI
  return ;
#endif // UPDATE_LOOP_PROGRESS_GUI

  // compute loop progress
  int    sample_n , n_samples ; Client->GetPosition(&sample_n , &n_samples) ;
  int    bpi               = Client->GetBPI() ;
  float  bpm               = Client->GetActualBPM() ;
  double linear_progress   = (sample_n + GuiBeatOffset) / n_samples ;
  int    beat_n            = ((int)(bpi * linear_progress) % bpi) + 1 ;
  double discrete_progress = (float)beat_n / bpi ;

  // update loop progress
  Gui->loop->updateBeat(beat_n) ;
  Gui->loop->loopProgress = discrete_progress ; // linear_progress ;
  Gui->statusbar->setStatusR(String(bpi) + " bpi @ " + String(bpm) + " bpm") ;

  // update metro VU loop progress
  ValueTree metro_store   = Config->getChannelById(CONFIG::MASTERS_ID , CONFIG::METRO_ID) ;
  double   metro_is_muted = bool(  metro_store[CONFIG::IS_MUTED_ID]) ;
  double   metro_pan      = double(metro_store[CONFIG::PAN_ID]) ;
  double   metro_vu       = (metro_is_muted)? 0.0 : discrete_progress ;
  double   metro_vu_l     = (metro_pan < 0.0)? metro_vu : metro_vu * (1.0 - metro_pan) ;
  double   metro_vu_r     = (metro_pan > 0.0)? metro_vu : metro_vu * (1.0 + metro_pan) ;

  metro_store.setProperty(CONFIG::VU_LEFT_ID  , metro_vu_l , nullptr) ;
  metro_store.setProperty(CONFIG::VU_RIGHT_ID , metro_vu_r , nullptr) ;
}

void LinJam::UpdateVuMeters()
{
#ifndef UPDATE_VU_METERS_GUI
  return ;
#endif // UPDATE_VU_METERS_GUI

  double master_vu_l = 0.0 ; double master_vu_r = 0.0 ;

  /* update local VUs asynchronously */

  int channel_n = -1 ; int channel_idx ;
  while (~(channel_idx = Client->EnumLocalChannels(++channel_n)))
  {
    ValueTree channel_store = Config->getChannelByIdx(Config->localChannels , channel_idx) ;
    double    local_pan     = double(channel_store[CONFIG::PAN_ID]) ;
    double    local_vu_l    = VAL2DB(Client->GetLocalChannelPeak(channel_idx)) -
                              CLIENT::VU_DB_MIN ;
    int       stereo_status = int(channel_store[CONFIG::STEREO_ID]) ;
    bool      pan_left      = local_pan < 0.0 ;
    bool      pan_right     = local_pan > 0.0 ;
    if (!channel_store.isValid()) continue ;

    if (stereo_status == CONFIG::MONO)
    {
      channel_store.setProperty(CONFIG::VU_LEFT_ID , local_vu_l , nullptr) ;

      // compensate master for local channel pan
      ScalePannedMonoVus(local_vu_l , local_pan , &master_vu_l , &master_vu_r) ; // mutates
    }
    else if (stereo_status == CONFIG::STEREO_L)
    {
      // ensure this faux-stereo channel has a matching faux-stereo pair channel
      int    pair_idx   = int(channel_store[CONFIG::PAIR_IDX_ID]) ;
      double local_vu_r = VAL2DB(Client->GetLocalChannelPeak(pair_idx)) -
                          CLIENT::VU_DB_MIN ;

      // compensate for pan
      ComputePannedVus(local_pan , &local_vu_l , &local_vu_r) ; // mutates

      // update local channel VUs asynchronously
      channel_store.setProperty(CONFIG::VU_LEFT_ID  , local_vu_l , nullptr) ;
      master_vu_l = AddDecibels(master_vu_l , local_vu_l) ;
      channel_store.setProperty(CONFIG::VU_RIGHT_ID , local_vu_r , nullptr) ;
      master_vu_r = AddDecibels(master_vu_r , local_vu_r) ;
    }
  }


  /* update remote VUs asynchronously */

  int user_idx = -1 ; String user_name ;
  while ((user_name = GetRemoteUserName(++user_idx)).isNotEmpty())
  {
    Identifier user_id            = Config->makeUserId(user_name , user_idx) ;
    ValueTree  user_store         = Config->getUserById(user_id) ;
    double     remote_master_vu_l = 0.0 ;
    double     remote_master_vu_r = 0.0 ; channel_n = -1 ; Identifier vu_id ;

    while (~(channel_idx = Client->EnumUserChannels(user_idx , ++channel_n)))
    {
      ValueTree channel_store = Config->getChannelByIdx(user_store , channel_idx) ;
      double    remote_pan    = double(channel_store[CONFIG::PAN_ID]) ;
      double    remote_vu_l   = VAL2DB(Client->GetUserChannelPeak(user_idx , channel_idx)) -
                                CLIENT::VU_DB_MIN ;
      int       stereo_status = int(channel_store[CONFIG::STEREO_ID]) ;
      if (!channel_store.isValid()) continue ;

      if (stereo_status == CONFIG::MONO)
      {
        channel_store.setProperty(CONFIG::VU_LEFT_ID , remote_vu_l , nullptr) ;

        // compensate remote master for remote channel pan
        ScalePannedMonoVus(remote_vu_l         , remote_pan         ,
                           &remote_master_vu_l , &remote_master_vu_r) ; // mutates
      }
      else if (stereo_status == CONFIG::STEREO_L)
      {
        // ensure this faux-stereo channel has a matching faux-stereo pair channel
        int    pair_idx    = int(channel_store[CONFIG::PAIR_IDX_ID]) ;
        double remote_vu_r = VAL2DB(Client->GetUserChannelPeak(user_idx , pair_idx)) -
                             CLIENT::VU_DB_MIN ;

        // compensate for pan
        ComputePannedVus(remote_pan , &remote_vu_l , &remote_vu_r) ; // mutates

        // update remote channel VUs asynchronously
        channel_store.setProperty(CONFIG::VU_LEFT_ID  , remote_vu_l , nullptr) ;
        remote_master_vu_l = AddDecibels(remote_master_vu_l , remote_vu_l) ;
        channel_store.setProperty(CONFIG::VU_RIGHT_ID , remote_vu_r , nullptr) ;
        remote_master_vu_r = AddDecibels(remote_master_vu_r , remote_vu_r) ;
      }
    }

    // update remote master VUs asynchronously
    ValueTree remote_master_store = Config->getChannelById(user_id , CONFIG::MASTER_ID) ;
    double    remote_master_pan   = double(remote_master_store[CONFIG::PAN_ID]) ;
    if (!remote_master_store.isValid()) continue ;

    // compensate remote master for remote master pan
    if (remote_master_pan > 0.0)
      ScalePannedMonoVus( remote_master_vu_l , remote_master_pan  ,
                         &remote_master_vu_l , &remote_master_vu_r) ; // mutates
    if (remote_master_pan < 0.0)
      ScalePannedMonoVus( remote_master_vu_r , remote_master_pan  ,
                         &remote_master_vu_l , &remote_master_vu_r) ; // mutates

    remote_master_store.setProperty(CONFIG::VU_LEFT_ID  , remote_master_vu_l , nullptr) ;
    remote_master_store.setProperty(CONFIG::VU_RIGHT_ID , remote_master_vu_r , nullptr) ;
    master_vu_l = AddDecibels(master_vu_l , remote_master_vu_l) ;
    master_vu_r = AddDecibels(master_vu_r , remote_master_vu_r) ;
  }


  /* update master VU asynchronously */

  ValueTree master_store = Config->getChannelById(CONFIG::MASTERS_ID , CONFIG::MASTER_ID) ;
  double    master_pan   = double(master_store[CONFIG::PAN_ID]) ;

  // compensate master for master pan
  if (master_pan > 0.0)
    ScalePannedMonoVus(master_vu_l , master_pan , &master_vu_l , &master_vu_r) ; // mutates
  if (master_pan < 0.0)
    ScalePannedMonoVus(master_vu_r , master_pan , &master_vu_l , &master_vu_r) ; // mutates

  master_store.setProperty(CONFIG::VU_LEFT_ID  , master_vu_l , nullptr) ;
  master_store.setProperty(CONFIG::VU_RIGHT_ID , master_vu_r , nullptr) ;
}

void LinJam::UpdateRecordingTime()
{
#ifndef UPDATE_RECORDING_TIME_GUI
  return ;
#endif // UPDATE_RECORDING_TIME_GUI

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
    for (int bot_n = 0 ; bot_n < NETWORK::N_KNOWN_BOTS ; ++bot_n)
    {
      ValueTree user_store = Config->getUserById(NETWORK::KNOWN_BOTS.getUnchecked(bot_n)) ;
      if (!user_store.isValid()) continue ;

      int bot_idx    = int(user_store[CONFIG::USER_IDX_ID]) ;
      recording_time = GetRemoteChannelClientName(bot_idx , CLIENT::BOT_CHANNELIDX) ;
    }
    bool has_recording_time_changed = recording_time.compare(PrevRecordingTime) ;
    bool is_this_first_pass         = PrevRecordingTime.isEmpty() ;
    bool should_show_time           = (has_recording_time_changed && !is_this_first_pass) ;

    PrevRecordingTime = recording_time ;
    recording_time    = (should_show_time)? " - " + recording_time : String::empty ;
  }

  Gui->setTitle(host + " - " + bpi + "bpi / " + bpm + "bpm" + recording_time) ;
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


/* state helpers */

bool LinJam::InitializeAudio()
{
  IsAudioEnabled = false ; if (Audio) delete Audio ;

  int    interface_n   = int(Config->audioIfN  .getValue()) ;
  int    n_inputs      = int(Config->nInputs   .getValue()) ;
  int    n_outputs     = int(Config->nOutputs  .getValue()) ;
  int    bit_depth     = int(Config->bitDepth  .getValue()) ;
  int    sample_rate   = int(Config->sampleRate.getValue()) ;
  String jack_name     =     Config->jackName  .toString() ;
  char*  config_string = "" ;

#ifdef _WIN32
  audioStreamer::WinAudioIf if_n = (audioStreamer::WinAudioIf)interface_n ;
  Audio = CreateConfiguredStreamer("linjam.ini" , if_n , OnSamples) ;

DEBUG_TRACE_AUDIO_INIT_WIN

#else // _WIN32
#  ifdef _MAC
  Audio = create_audioStreamer_CoreAudio(&config_string , sample_rate , n_inputs ,
                                         bit_depth      , OnSamples              ) ;

DEBUG_TRACE_AUDIO_INIT_MAC

#  else // _MAC
  switch (interface_n)
  {
    case 0: // JACK
      Audio = create_audioStreamer_JACK(jack_name.toRawUTF8() , n_inputs , n_outputs ,
                                        OnSamples             , Client               ) ;

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
      FreeInputChannels.add(channel_n) ;
      if (channel_n % 2) FreeInputChannelPairs.add(channel_n - 1) ;
    }
  }

DEBUG_TRACE_AUDIO_INIT

  return (!!Audio) ;
}

void LinJam::ConfigureInitialChannels()
{
  // add master and metro channel GUI mixers and configure NJClient master channels
  ValueTree master_store = Config->getChannelById(CONFIG::MASTERS_ID , CONFIG::MASTER_ID) ;
  ValueTree metro_store  = Config->getChannelById(CONFIG::MASTERS_ID , CONFIG::METRO_ID) ;
  Gui->mixer->addChannel(GUI::MASTERS_GUI_ID , master_store) ;
  Gui->mixer->addChannel(GUI::MASTERS_GUI_ID , metro_store) ;
  ConfigureMasterChannel(CONFIG::CONFIG_INIT_ID) ;
  ConfigureMetroChannel( CONFIG::CONFIG_INIT_ID) ;

DEBUG_TRACE_INITIAL_CHANNELS

  // add local Channel GUI mixers and configure NJClient input channels
  ValueTree channels = Config->localChannels ;
  for (int channel_n = 0 ; channel_n < channels.getNumChildren() ; ++channel_n)
  {
    ValueTree channel_store = Config->localChannels.getChild(channel_n) ;
    if (!AddLocalChannel(channel_store))
    {
      // destroy corrupted channel storage
      Config->destroyChannel(Config->localChannels , channel_store) ;
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
  int       save_audio      = int( Config->saveAudio    .getValue()) ;
  bool      should_save_log = bool(Config->shouldSaveLog.getValue()) ;
  int       debug_level     = int( Config->debugLevel   .getValue()) ;
  int       auto_subscribe  = int( Config->autoSubscribe.getValue()) ;
  ValueTree subscriptions   =      Config->autoSubscribeUsers ;

  Client->LicenseAgreementCallback = OnLicense ;
  Client->ChatMessage_Callback     = OnChatmsg ;
  Client->config_savelocalaudio    = save_audio ;
  Client->config_debug_level       = debug_level ;
  Client->config_autosubscribe     = auto_subscribe ;
  if (save_audio && should_save_log)
    Client->SetLogFile((SessionDir.getFullPathName() + CONFIG::LOGFILE).toRawUTF8()) ;
  for (int user_n = 0 ; user_n < subscriptions.getNumChildren() ; ++user_n)
  {
    WDL_String user_name_wdl(subscriptions.getChild(user_n).getType().getCharPointer()) ;
    Client->config_autosubscribe_userlist.insert(user_name_wdl.Get()) ;
  }
}

void LinJam::CleanSessionDir()
{
  bool save_audio = bool(Config->saveAudio.getValue()) ;
  if (save_audio > 0) return ;

DEBUG_TRACE_CLEAN_SESSION

#ifdef CLEAN_SESSION
  File this_binary = File::getSpecialLocation(File::currentExecutableFile) ;
  File this_dir    = this_binary.getParentDirectory() ;
  if (!SessionDir.isDirectory() || !SessionDir.isAChildOf(this_dir)) return ;

  // TODO: the *.ninjam directories created when save_loca_audio == -1 (delete ASAP)
  //           are not being deleted implicitly as they presumably should be (issue #32)
  DirectoryIterator session_dir_iter(SessionDir , false , "*.*" , File::findFilesAndDirectories) ;
  while (session_dir_iter.next()) session_dir_iter.getFile().deleteRecursively() ;
#endif // CLEAN_SESSION
}


/* NJClient config helpers */

int LinJam::GetNumInputChannels() { return Audio->m_innch ; }

int LinJam::GetNumVacantChannels()
{
  int n_active_channels = -1 ; while (~Client->EnumLocalChannels(++n_active_channels)) ;
  return Audio->m_innch - n_active_channels ;
}

int LinJam::GetVacantLocalChannelIdx()
{
  // find the first vacant NJClient local channel slot index
  int channel_idx = -1 ; while (IsConfiguredChannel(++channel_idx)) ;
  bool is_vacant_slot = (channel_idx < GetNumInputChannels()) ;

  return (is_vacant_slot)? channel_idx : -1 ;
}

String LinJam::GetStoredChannelName(ValueTree channel_store)
{
  return channel_store[CONFIG::CHANNEL_NAME_ID].toString() ;
}

String LinJam::GetLocalChannelClientName(int channel_idx)
{
  return CharPointer_UTF8(Client->GetLocalChannelInfo(channel_idx , NULL , NULL , NULL)) ;
}

String LinJam::GetRemoteUserName(int user_idx)
{
  return CharPointer_UTF8(Client->GetUserState(user_idx)) ;
}

String LinJam::GetRemoteChannelClientName(int user_idx , int channel_idx)
{
  return CharPointer_UTF8(Client->GetUserChannelState(user_idx , channel_idx)) ;
}

bool LinJam::IsConfiguredChannel(int channel_idx)
{
  return GetLocalChannelClientName(channel_idx).isNotEmpty() ;
}

double LinJam::AddDecibels(double vu_l , double vu_r)
{
  return 10 * log10(pow(10.0 , (vu_l / 10.0)) + pow(10.0 , (vu_r / 10.0))) ;
}

void LinJam::ComputePannedVus(double pan , double* vu_l , double* vu_r)
{
  double vu_l_in = *vu_l ;
  double vu_r_in = *vu_r ;

  if (pan > 0.0) // pan right
  {
    // decrease left contribution to left vu
    *vu_l *= log10(10.0 * (1.0 - pan)) ;
    // increase left contribution to right vu
    *vu_r = AddDecibels(vu_r_in , vu_l_in * pan) ;
  }

  if (pan < 0.0) // pan left
  {
    // increase right contribution to left vu
    *vu_l = AddDecibels(vu_l_in , vu_r_in * -pan) ;
    // decrease right contribution to right vu
    *vu_r *= log10(10.0 * (1.0 + pan)) ;
  }

  // cap underflows
  if (isnan(*vu_l)) *vu_l = 0.0 ;
  if (isnan(*vu_r)) *vu_r = 0.0 ;
  if (vu_l_in == 0.0 && vu_r_in == 0.0) *vu_l = *vu_r = 0.0 ;
}

void LinJam::ScalePannedMonoVus(double vu_mono , double pan , double* vu_l , double* vu_r)
{
  // compute panned mono channel contributions to left and right VU master meters
  *vu_l = (pan > 0.0)? vu_mono * log10(10.0 * (1.0 - pan)) : vu_mono ; // pan_left
  *vu_r = (pan < 0.0)? vu_mono * log10(10.0 * (1.0 + pan)) : vu_mono ; // pan right

  // cap underflows
  if (isnan(*vu_l)) *vu_l = 0.0 ;
  if (isnan(*vu_r)) *vu_r = 0.0 ;
}

float LinJam::ComputeStereoPan(float pan , int stereo_status)
{
  bool is_mono_channel = stereo_status == CONFIG::MONO ;
  bool is_pair_channel = stereo_status == CONFIG::STEREO_R ;
  return (is_mono_channel)? pan                                         :
                            (!is_pair_channel)                         ?
                              ((pan <= 0.0)? -1.0 : -1.0 + (pan * 2.0)) :
                              ((pan >= 0.0)? +1.0 : +1.0 + (pan * 2.0)) ;
}

void LinJam::ConfigureMasterChannel(Identifier a_key)
{
  ValueTree master_store = Config->getChannelById(CONFIG::MASTERS_ID , CONFIG::MASTER_ID) ;
  if (!master_store.isValid()) return ;

  // load stored config for this channel
  float volume   = float(master_store[CONFIG::VOLUME_ID]) ;
  float pan      = float(master_store[CONFIG::PAN_ID]) ;
  bool  is_muted = bool( master_store[CONFIG::IS_MUTED_ID]) ;

  // determine which NJClient channel params to modify
  bool should_init_all      = (a_key == CONFIG::CONFIG_INIT_ID) ;
  bool should_set_volume    = (should_init_all || a_key == CONFIG::VOLUME_ID) ;
  bool should_set_pan       = (should_init_all || a_key == CONFIG::PAN_ID) ;
  bool should_set_is_muted  = (should_init_all || a_key == CONFIG::IS_MUTED_ID) ;

  // configure NJClient master channel
  if (should_set_volume)   Client->config_mastervolume = (float)DB2VAL(volume) ;
  if (should_set_pan)      Client->config_masterpan    = pan ;
  if (should_set_is_muted) Client->config_mastermute   = is_muted ;
}

void LinJam::ConfigureMetroChannel(Identifier a_key)
{
  ValueTree metro_store = Config->getChannelById(CONFIG::MASTERS_ID , CONFIG::METRO_ID) ;
  if (!metro_store.isValid()) return ;

  // load stored config for this channel
  float volume    = float(metro_store[CONFIG::VOLUME_ID]) ;
  float pan       = float(metro_store[CONFIG::PAN_ID]) ;
  bool  is_muted  = bool( metro_store[CONFIG::IS_MUTED_ID]) ;
  int   source_n  = int(  metro_store[CONFIG::SOURCE_N_ID]) ;
  bool  is_stereo = int(  metro_store[CONFIG::STEREO_ID]) != CONFIG::MONO ;

  // determine which NJClient channel params to modify
  bool should_init_all      = (a_key == CONFIG::CONFIG_INIT_ID) ;
  bool should_set_volume    = (should_init_all || a_key == CONFIG::VOLUME_ID) ;
  bool should_set_pan       = (should_init_all || a_key == CONFIG::PAN_ID) ;
  bool should_set_is_muted  = (should_init_all || a_key == CONFIG::IS_MUTED_ID) ;
  bool should_set_source_n  = (should_init_all || a_key == CONFIG::SOURCE_N_ID) ;
  bool should_set_stereo    = (should_init_all || a_key == CONFIG::STEREO_ID) ;

  // configure NJClient metro channel
  if (should_set_volume)    Client->config_metronome           = (float)DB2VAL(volume) ;
  if (should_set_pan)       Client->config_metronome_pan       = pan ;
  if (should_set_is_muted)  Client->config_metronome_mute      = is_muted ;
  if (should_set_source_n)  Client->config_metronome_channel   = source_n ;
  if (should_set_stereo)    Client->config_metronome_stereoout = is_stereo ;
}

void LinJam::ConfigureLocalChannel(ValueTree channel_store , Identifier a_key)
{
  if (!channel_store.isValid()                                       ||
     a_key == CONFIG::CHANNEL_IDX_ID || a_key == CONFIG::PAIR_IDX_ID ||
     a_key == CONFIG::VU_LEFT_ID     || a_key == CONFIG::VU_RIGHT_ID  ) return ;

  // load stored config for this channel
  int    channel_idx   = int(  channel_store[CONFIG::CHANNEL_IDX_ID]) ;
  int    pair_idx      = int(  channel_store[CONFIG::PAIR_IDX_ID]) ;
  float  volume        = float(channel_store[CONFIG::VOLUME_ID]) ;
  float  pan           = float(channel_store[CONFIG::PAN_ID]) ;
  bool   is_xmit       = bool( channel_store[CONFIG::IS_XMIT_RCV_ID]) ;
  bool   is_muted      = bool( channel_store[CONFIG::IS_MUTED_ID]) ;
  bool   is_solo       = bool( channel_store[CONFIG::IS_SOLO_ID]) ;
  int    source_n      = int(  channel_store[CONFIG::SOURCE_N_ID]) ;
  int    bit_depth     = int(  channel_store[CONFIG::BITDEPTH_ID]) ;
  int    stereo_status = int(  channel_store[CONFIG::STEREO_ID]) ;
  String channel_name  = channel_store[CONFIG::CHANNEL_NAME_ID].toString() ;
         channel_name  = Config->makeStereoName(channel_name , stereo_status) ;

  // determine which NJClient channel params to modify
  bool should_init_all      = a_key == CONFIG::CONFIG_INIT_ID ;
  bool should_set_name      = a_key == CONFIG::CHANNEL_NAME_ID || should_init_all ;
  bool should_set_volume    = a_key == CONFIG::VOLUME_ID       || should_init_all ;
  bool should_set_pan       = a_key == CONFIG::PAN_ID          ||
                              a_key == CONFIG::STEREO_ID       || should_init_all ;
  bool should_set_is_xmit   = a_key == CONFIG::IS_XMIT_RCV_ID  || should_init_all ;
  bool should_set_is_muted  = a_key == CONFIG::IS_MUTED_ID     || should_init_all ;
  bool should_set_is_solo   = a_key == CONFIG::IS_SOLO_ID      || should_init_all ;
  bool should_set_source_n  = a_key == CONFIG::SOURCE_N_ID     || should_init_all ;
  bool should_set_bit_depth = a_key == CONFIG::BITDEPTH_ID     || should_init_all ;
  bool should_set_stereo    = a_key == CONFIG::STEREO_ID       || should_init_all ;

DEBUG_TRACE_CONFIGURE_LOCAL_CHANNEL

  // handle name change
  char* new_name = NULL ; WDL_String name_wdl ;
  if (should_set_name)
  {
    // convert channel name from juce::String into non-const char*
    name_wdl.Set(channel_name.toRawUTF8()) ; new_name = name_wdl.Get() ;
  }

  // handle faux-stereo panning
  if (should_set_pan) pan = ComputeStereoPan(pan , stereo_status) ;

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

  // configure faux-stereo pair implicitly
  if (stereo_status == CONFIG::STEREO_L)
  {
    if (should_set_stereo)
    {
      // handle mono->stereo conversion
      if (~(pair_idx = GetVacantLocalChannelIdx()))
      {
        a_key = CONFIG::CONFIG_INIT_ID ;
        channel_store.setProperty(CONFIG::PAIR_IDX_ID , pair_idx     , nullptr) ;
      }
      else
      {
        channel_store.setProperty(CONFIG::STEREO_ID   , CONFIG::MONO , nullptr) ;

        return ;
      }
    }

    // force mono conversion bypassing configuration of pair to be deleted (fires next case)
    if (a_key == CONFIG::SOURCE_N_ID && source_n % 2)
      channel_store.setProperty(CONFIG::STEREO_ID , CONFIG::MONO , nullptr) ;
    // configure unstored pair channel
    else
    {
      ValueTree pair_store    = channel_store.createCopy() ;
      String    pair_name     = Config->makeStereoName(channel_name , CONFIG::STEREO_R) ;
      int       pair_source_n = source_n + 1 ;

      pair_store.setProperty(CONFIG::CHANNEL_NAME_ID , pair_name        , nullptr) ;
      pair_store.setProperty(CONFIG::CHANNEL_IDX_ID  , pair_idx         , nullptr) ;
      pair_store.setProperty(CONFIG::SOURCE_N_ID     , pair_source_n    , nullptr) ;
      pair_store.setProperty(CONFIG::STEREO_ID       , CONFIG::STEREO_R , nullptr) ;

      ConfigureLocalChannel(pair_store , a_key) ;
    }

    // update client channels names on mono->stereo conversion
    if (should_set_stereo)
      channel_store.setProperty(CONFIG::CHANNEL_NAME_ID , channel_name , nullptr) ;
  }
  // handle stereo->mono conversion
  else if (stereo_status == CONFIG::MONO && should_set_stereo)
  {
    Client->DeleteLocalChannel(pair_idx) ;
    channel_store.setProperty(CONFIG::PAIR_IDX_ID , CONFIG::DEFAULT_CHANNEL_IDX , nullptr) ;
    channel_store.setProperty(CONFIG::CHANNEL_NAME_ID , channel_name , nullptr) ;
  }

  Client->NotifyServerOfChannelChange() ;
}

void LinJam::ConfigureRemoteChannel(ValueTree  user_store , ValueTree channel_store ,
                                    Identifier a_key                                )
{
  if (!user_store.isValid()           || !channel_store.isValid()     ||
     a_key == CONFIG::CHANNEL_NAME_ID                                 ||
     a_key == CONFIG::CHANNEL_IDX_ID  || a_key == CONFIG::PAIR_IDX_ID ||
     a_key == CONFIG::VU_LEFT_ID      || a_key == CONFIG::VU_RIGHT_ID  ) return ;

  // load stored config for this channel
  int   user_idx      = int(  user_store   [CONFIG::USER_IDX_ID]) ;
  int   channel_idx   = int(  channel_store[CONFIG::CHANNEL_IDX_ID]) ;
  int   pair_idx      = int(  channel_store[CONFIG::PAIR_IDX_ID]) ;
  float volume        = float(channel_store[CONFIG::VOLUME_ID]) ;
  float pan           = float(channel_store[CONFIG::PAN_ID]) ;
  bool  is_rcv        = bool( channel_store[CONFIG::IS_XMIT_RCV_ID]) ;
  bool  is_muted      = bool( channel_store[CONFIG::IS_MUTED_ID]) ;
  bool  is_solo       = bool( channel_store[CONFIG::IS_SOLO_ID]) ;
  int   sink_n        = 0 ; // TODO: not yet clear how to handle remote sink_n
  int   stereo_status = int(  channel_store[CONFIG::STEREO_ID]) ;                           \
  bool  is_stereo     = true ;

  // determine which NJClient channel params to modify
  bool should_init_all     = a_key == CONFIG::CONFIG_INIT_ID ;
  bool should_set_volume   = a_key == CONFIG::VOLUME_ID      || should_init_all ;
  bool should_set_pan      = a_key == CONFIG::PAN_ID         ||
                             a_key == CONFIG::STEREO_ID      || should_init_all ;
  bool should_set_is_rcv   = a_key == CONFIG::IS_XMIT_RCV_ID || should_init_all ;
  bool should_set_is_muted = a_key == CONFIG::IS_MUTED_ID    || should_init_all ;
  bool should_set_is_solo  = a_key == CONFIG::IS_SOLO_ID     || should_init_all ;
  bool should_set_stereo   = a_key == CONFIG::STEREO_ID      || should_init_all ;

DEBUG_TRACE_CONFIGURE_REMOTE_CHANNEL

  if (channel_idx == CONFIG::MASTER_CHANNEL_IDX)
  {
    int channel_n = -1 ;
    // configure NJClient remote master channel
    if      (should_set_volume || should_set_pan || should_set_is_muted)
      Client->SetUserState(user_idx                                    ,
                           should_set_volume   , (float)DB2VAL(volume) ,
                           should_set_pan      , pan                   ,
                           should_set_is_muted , is_muted              ) ;
    // or apply user master pseudo rcv or solo control over all real user channels
    else if (should_set_is_rcv || should_set_is_solo)
      while (~(channel_idx = Client->EnumUserChannels(user_idx , ++channel_n)))
      {
        channel_store = Config->getChannelByIdx(user_store , channel_idx) ;
        ConfigureRemoteChannel(user_store , channel_store , a_key) ;
      }
  }
  else
  {
    // handle faux-stereo panning
    if (should_set_pan) pan = ComputeStereoPan(pan , stereo_status) ;

    // configure NJClient remote channel allowing master overrides
    ValueTree master_store   = Config->getUserMasterChannel(user_store) ;
    bool      is_master_rcv  = bool(master_store[CONFIG::IS_XMIT_RCV_ID]) ;
    bool      is_master_solo = bool(master_store[CONFIG::IS_SOLO_ID]) ;
    Client->SetUserChannelState(user_idx            , channel_idx               ,
                                should_set_is_rcv   , is_rcv && is_master_rcv   ,
                                should_set_volume   , (float)DB2VAL(volume)     ,
                                should_set_pan      , pan                       ,
                                should_set_is_muted , is_muted                  ,
                                should_set_is_solo  , is_solo || is_master_solo ,
                                should_init_all     , sink_n                    ,
                                should_init_all     , is_stereo                 ) ;

    // configure faux-stereo pair implicitly
    if (stereo_status == CONFIG::STEREO_L)
    {
      int       pair_idx   = int(channel_store[CONFIG::PAIR_IDX_ID]) ;
      ValueTree pair_store = Config->getChannelByIdx(user_store , pair_idx) ;
      if (should_set_stereo || should_init_all)
        ConfigureRemoteChannel(user_store , pair_store , CONFIG::CONFIG_INIT_ID) ;
      else pair_store.setProperty(a_key , channel_store[a_key] , nullptr) ;
    }
  }
}
