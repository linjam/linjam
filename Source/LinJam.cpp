/*
  ==============================================================================

    Linjam.cpp
    Created: 24 May 2014 5:03:01pm
    Author:  me

  ==============================================================================
*/

#include "LinJam.h"
#include "./Trace/TraceLinJam.h"

#ifdef _MSC_VER
#  include <float.h>
#  define isnan(x) _isnan(x)
#endif


/* LinJam class public class variables */

LinJamConfig* LinJam::Config ;


/* LinJam class private class variables */

NJClient*      LinJam::Client               = nullptr ;          // Initialize()
MainContent*   LinJam::Gui                  = nullptr ;          // Initialize()
MultiTimer*    LinJam::Timer                = nullptr ;          // Initialize()
audioStreamer* LinJam::Audio                = nullptr ;          // Initialize()
String         LinJam::AutoJoinHost ;                            // Initialize()
Value          LinJam::Status               = Value() ;          // Initialize()
bool           LinJam::IsAudioInitialized   = false ;            // InitializeAudio()
SortedSet<int> LinJam::FreeAudioSources     = SortedSet<int>() ; // InitializeAudio()
SortedSet<int> LinJam::FreeAudioSourcePairs = SortedSet<int>() ; // InitializeAudio()
double         LinJam::GuiBeatOffset ;                           // InitializeAudio()
File           LinJam::SessionDir ;                              // PrepareSessionDirectory()
int            LinJam::RetryLogin ;                              // Connect()
String         LinJam::PrevRecordingTime ;                       // Disconnect()


/* LinJam class public class methods */

/* state methods */

void LinJam::SignIn(String host , String login , String pass , bool is_anonymous)
{
  Config->setCredentials(host , login , pass , is_anonymous) ;
  RetryLogin = NETWORK::N_LOGIN_RETRIES ; Connect() ;
}

void LinJam::Connect()
{
  Client->Disconnect() ;

  String host         = str( Config->server[CONFIG::HOST_ID        ]) ;
  String login        = str( Config->server[CONFIG::LOGIN_ID       ]) ;
  String pass         = str( Config->server[CONFIG::PASS_ID        ]) ;
  bool   is_anonymous = bool(Config->server[CONFIG::IS_ANONYMOUS_ID]) ;

  if (is_anonymous) { login = "anonymous:" + login ; pass  = "" ; }

DEBUG_TRACE_CONNECT

  Gui->statusbar->setStatusL(GUI::CONNECTING_TEXT + host) ;
  Client->Connect(host.toRawUTF8() , login.toRawUTF8() , pass.toRawUTF8()) ;
}

void LinJam::Disconnect() { Client->Disconnect() ; PrevRecordingTime = "" ; }


/* getters/setters */

ValueTree LinJam::GetCredentials(String host) { return Config->getCredentials(host) ; }

bool LinJam::IsAgreed() { return bool(Config->server[CONFIG::IS_AGREED_ID]) ; }

SortedSet<int> LinJam::GetFreeAudioSources() { return FreeAudioSources ; }

SortedSet<int> LinJam::GetFreeAudioSourcePairs() { return FreeAudioSourcePairs ; }


/* GUI event handlers */

bool LinJam::AddLocalChannel(ValueTree channel_store)
{
DEBUG_TRACE_ADD_LOCAL_CHANNEL

  int  channel_idx = int(channel_store[CONFIG::CHANNEL_IDX_ID]) ;
  int  source_n    = int(channel_store[CONFIG::SOURCE_N_ID   ]) ;
  bool is_stereo   = int(channel_store[CONFIG::STEREO_ID     ]) != CONFIG::MONO ;

  // sanity check
  int  n_sources                 = GetNumAudioSources() ;
  int  max_n_channels            = Client->GetMaxLocalChannels() ;
  int  n_vacant_channels         = GetNumVacantChannels() ;
  bool is_valid_channel_idx      = channel_idx >= 0 && channel_idx < max_n_channels ;
  bool is_valid_source_n         = source_n    >= 0 && source_n    < n_sources ;
  bool does_channel_exist        = IsConfiguredChannel(channel_idx) ;
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
  Config->removeChannel(Config->localChannels , channel_store) ;

DEBUG_TRACE_DUMP_FREE_INPUTS_VB
}

void LinJam::SendChat(String chat_text)
{
DEBUG_TRACE_CHAT_OUT

  if ((chat_text = chat_text.trim()).isEmpty()) return ;

  if (!chat_text.startsWith("/"))
    Client->ChatMessage_Send(CLIENT::CHATMSG_TYPE_MSG.toRawUTF8() , chat_text.toRawUTF8()) ;
  else
  {
    // handle irc-style command
    String command        = chat_text.upToFirstOccurrenceOf(" " , false , false) ;
    bool is_me_command    = (!command.compare(CLIENT::CHATMSG_CMD_ME)) ;
    bool is_pm_command    = (!command.compare(CLIENT::CHATMSG_CMD_MSG)) ;
    bool is_admin_command = (!command.compare(CLIENT::CHATMSG_CMD_ADMIN)) ;
    bool is_user_command  = (!command.compare(CLIENT::CHATMSG_CMD_TOPIC) ||
                             !command.compare(CLIENT::CHATMSG_CMD_KICK)  ||
                             !command.compare(CLIENT::CHATMSG_CMD_BPI)   ||
                             !command.compare(CLIENT::CHATMSG_CMD_BPM)    ) ;

#ifndef ACCEPT_CHAT_COMMANDS // (issue #19)
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
}

void LinJam::CleanSessionDir() { SessionDir.deleteRecursively() ; }


/* LinJam class private class methods */

/* initialization methods */

bool LinJam::Initialize(NJClient*   nj_client   , MainContent*  main_content ,
                        MultiTimer* multi_timer , const String& cli_args     )
{
DEBUG_TRACE_INIT

  Client       = nj_client ;
  Gui          = main_content ;
  Timer        = multi_timer ;
  AutoJoinHost = cli_args ; // TODO: parse/validate command line for auto-join (issue #9)
  Status       = APP::LINJAM_STATUS_INIT ;

  // prepare runtime initialized constants
  APP::Initialize() ;

  // load persistent configuration and prepare audio save directory
  if ((Config = new LinJamConfig()) == nullptr ||
      !Config->isConfigValid()                 ||
      !PrepareSessionDirectory()                ) return false ;

  // instantiate GUI components requiring model hooks
  Gui->instantiate(Config->gui   , Config->client , Config->blacklist ,
                   Config->audio , Config->server , Status            ) ;

  // configure NINJAM client and initialize networking
  ConfigureNinjam() ; JNL::open_socketlib() ;

  // instantiate audioStreamer
  if (InitializeAudio()) Status = APP::LINJAM_STATUS_READY ;

  // start NJClient pump and GUI update timers
  Timer->startTimer(APP::CLIENT_TIMER_ID , APP::CLIENT_DRIVER_IVL) ;
  Timer->startTimer(APP::GUI_LO_TIMER_ID , APP::GUI_LO_UPDATE_IVL) ;
//Timer->startTimer(APP::GUI_MD_TIMER_ID , APP::GUI_MD_UPDATE_IVL) ; // unused
  Timer->startTimer(APP::GUI_HI_TIMER_ID , APP::GUI_LO_UPDATE_IVL) ;
  ConfigureGui(CONFIG::UPDATE_IVL_ID) ;

  return true ;
}

bool LinJam::PrepareSessionDirectory()
{
  SessionDir = Config->dataDir.getChildFile(CLIENT::SESSION_DIRNAME) ;

  SessionDir.createDirectory() ;

DEBUG_TRACE_SESSIONDIR

  bool does_session_dir_exist = SessionDir.isDirectory() ;
  if (does_session_dir_exist)
    Client->SetWorkDir(SessionDir.getFullPathName().toRawUTF8()) ;

  return does_session_dir_exist ;
}

void LinJam::ConfigureNinjam()
{
  int  save_audio_mode  = int( Config->client   [CONFIG::SAVE_AUDIO_MODE_ID]) ;
  bool should_save_log  = bool(Config->client   [CONFIG::SHOULD_SAVE_LOG_ID]) ;
  int  debug_level      = int( Config->client   [CONFIG::DEBUG_LEVEL_ID    ]) ;
  int  subscribe_mode   = int( Config->blacklist[CONFIG::SUBSCRIBE_MODE_ID ]) ;

  Client->LicenseAgreementCallback = OnLicense ;
  Client->ChatMessage_Callback     = OnChatmsg ;
  Client->config_savelocalaudio    = save_audio_mode ;
  Client->config_debug_level       = debug_level ;
  Client->config_autosubscribe     = subscribe_mode ;

  // set log file
  if (should_save_log && save_audio_mode > NJClient::SAVE_NONE)
    Client->SetLogFile((SessionDir.getFullPathName() + CLIENT::LOG_FILENAME).toRawUTF8()) ;

  // add bots and ignored users to ignore list
  ConfigureBlacklist() ;
}

void LinJam::ConfigureGui(const Identifier& a_key)
{
  if (a_key != CONFIG::UPDATE_IVL_ID) return ;

  int gui_update_ivl_n = int(Config->gui[CONFIG::UPDATE_IVL_ID]) ;
  int gui_update_ivl   = APP::GUI_HI_UPDATE_IVLS[gui_update_ivl_n] ;

  if (!!gui_update_ivl) Timer->startTimer(APP::GUI_HI_TIMER_ID , gui_update_ivl) ;
  else                  Timer->stopTimer( APP::GUI_HI_TIMER_ID                 ) ;

  if (!!gui_update_ivl) return ;

  // zero all VUs
  int n_channels = Config->localChannels.getNumChildren() ;
  for (int channel_n = 0 ; channel_n < n_channels ; ++channel_n)
  {
    ValueTree channel_store = Config->localChannels.getChild(channel_n) ;
    channel_store.setProperty(CONFIG::VU_LEFT_ID  , 0.0 , nullptr) ;
    channel_store.setProperty(CONFIG::VU_RIGHT_ID , 0.0 , nullptr) ;
  }
  int n_users = Config->remoteUsers.getNumChildren() ;
  for (int user_n = 0 ; user_n < n_users ; ++user_n)
  {
    ValueTree user_store = Config->remoteUsers.getChild(user_n) ;
    int       n_channels = user_store.getNumChildren() ;
    for (int channel_n = 0 ; channel_n < n_channels ; ++channel_n)
    {
      ValueTree channel_store = user_store.getChild(channel_n) ;
      channel_store.setProperty(CONFIG::VU_LEFT_ID  , 0.0 , nullptr) ;
      channel_store.setProperty(CONFIG::VU_RIGHT_ID , 0.0 , nullptr) ;
    }
  }
  ValueTree master_store = Config->getChannelById(CONFIG::MASTERS_ID , CONFIG::MASTER_ID) ;
  ValueTree metro_store  = Config->getChannelById(CONFIG::MASTERS_ID , CONFIG::METRO_ID ) ;
  master_store.setProperty(CONFIG::VU_LEFT_ID  , 0.0 , nullptr) ;
  master_store.setProperty(CONFIG::VU_RIGHT_ID , 0.0 , nullptr) ;
  metro_store .setProperty(CONFIG::VU_LEFT_ID  , 0.0 , nullptr) ;
  metro_store .setProperty(CONFIG::VU_RIGHT_ID , 0.0 , nullptr) ;
}

void LinJam::ConfigureBlacklist()
{
DEBUG_TRACE_BLACKLIST

  ValueTree blacklist           = Config->blacklist.createCopy() ;
  int       subscribe_mode      = int( Config->blacklist[CONFIG::SUBSCRIBE_MODE_ID  ]) ;
  int       should_hide_bots    = bool(Config->client   [CONFIG::SHOULD_HIDE_BOTS_ID]) ;
  bool      should_ignore_users = subscribe_mode == NJClient::SUBSCRIBE_DENY ;

  Client->config_autosubscribe_userlist.clear() ;
  if (!should_ignore_users) return ;

  if (should_hide_bots)
    for (int bot_n = 0 ; bot_n < NETWORK::KNOWN_BOTS->getNumAttributes() ; ++bot_n)
    {
      String bot_name = NETWORK::KNOWN_BOTS->getAttributeValue(bot_n) ;
      blacklist.getOrCreateChildWithName(Identifier(bot_name) , nullptr) ;
    }

  for (int user_n = 0 ; user_n < blacklist.getNumChildren() ; ++user_n)
  {
    String user_name = String(blacklist.getChild(user_n).getType()) ;

    Client->config_autosubscribe_userlist.insert(user_name.toStdString()) ;
  }
}

bool LinJam::InitializeAudio()
{
  if (Audio != nullptr) { delete Audio ; Audio = nullptr ; }

  // load config
  int    audio_api_n          = int(Config->audio[CONFIG::AUDIO_API_ID      ]) ;
#ifdef _WIN32
  int    asio_driver_n        = int(Config->audio[CONFIG::ASIO_DRIVER_ID    ]) ;
  int    asio_input_b_n       = int(Config->audio[CONFIG::ASIO_INPUTB_ID    ]) ;
  int    asio_input_e_n       = int(Config->audio[CONFIG::ASIO_INPUTE_ID    ]) ;
  int    asio_output_b_n      = int(Config->audio[CONFIG::ASIO_OUTPUTB_ID   ]) ;
  int    asio_output_e_n      = int(Config->audio[CONFIG::ASIO_OUTPUTE_ID   ]) ;
  bool   should_show_asio_cp  = int(Config->audio[CONFIG::ASIO_CONTROL_ID   ]) ;
  int    ks_sample_rate       = int(Config->audio[CONFIG::KS_SAMPLERATE_ID  ]) ;
  int    ks_input_device_n    = int(Config->audio[CONFIG::KS_INPUT_ID       ]) ;
  int    ks_output_device_n   = int(Config->audio[CONFIG::KS_OUTPUT_ID      ]) ;
  int    ks_bit_depth         = int(Config->audio[CONFIG::KS_BITDEPTH_ID    ]) ;
  int    ks_n_buffers         = int(Config->audio[CONFIG::KS_NBLOCKS_ID     ]) ;
  int    ks_buffer_size       = int(Config->audio[CONFIG::KS_BLOCKSIZE_ID   ]) ;
  String ds_input_device      = str(Config->audio[CONFIG::DS_INPUT_ID       ]) ;
  String ds_output_device     = str(Config->audio[CONFIG::DS_OUTPUT_ID      ]) ;
  int    ds_sample_rate       = int(Config->audio[CONFIG::DS_SAMPLERATE_ID  ]) ;
  int    ds_bit_depth         = int(Config->audio[CONFIG::DS_BITDEPTH_ID    ]) ;
  int    ds_n_buffers         = int(Config->audio[CONFIG::DS_NBLOCKS_ID     ]) ;
  int    ds_buffer_size       = int(Config->audio[CONFIG::DS_BLOCKSIZE_ID   ]) ;
  int    wave_input_device_n  = int(Config->audio[CONFIG::WAVE_INPUT_ID     ]) ;
  int    wave_output_device_n = int(Config->audio[CONFIG::WAVE_OUTPUT_ID    ]) ;
  int    wave_sample_rate     = int(Config->audio[CONFIG::WAVE_SAMPLERATE_ID]) ;
  int    wave_bit_depth       = int(Config->audio[CONFIG::WAVE_BITDEPTH_ID  ]) ;
  int    wave_n_buffers       = int(Config->audio[CONFIG::WAVE_NBLOCKS_ID   ]) ;
  int    wave_buffer_size     = int(Config->audio[CONFIG::WAVE_BLOCKSIZE_ID ]) ;
#else // _WIN32
#  ifdef _MAC
  String ca_input_device      = str(Config->audio[CONFIG::CA_INPUT_ID       ]) ;
  String ca_output_device     = str(Config->audio[CONFIG::CA_OUTPUT_ID      ]) ;
  int    ca_n_channels        = int(Config->audio[CONFIG::CA_NCHANNELS_ID   ]) ;
  int    ca_sample_rate       = int(Config->audio[CONFIG::CA_SAMPLERATE_ID  ]) ;
  int    ca_bit_depth         = int(Config->audio[CONFIG::CA_BITDEPTH_ID    ]) ;
#  else // _MAC
  int    jack_server_n        = int(Config->audio[CONFIG::JACK_SERVER_ID    ]) ;
  String jack_client_name     = str(Config->audio[CONFIG::JACK_NAME_ID      ]) ;
  int    jack_n_inputs        = int(Config->audio[CONFIG::JACK_NINPUTS_ID   ]) ;
  int    jack_n_outputs       = int(Config->audio[CONFIG::JACK_NOUTPUTS_ID  ]) ;
  String alsa_input_device    = str(Config->audio[CONFIG::ALSA_INPUT_ID     ]) ;
  String alsa_output_device   = str(Config->audio[CONFIG::ALSA_OUTPUT_ID    ]) ;
  int    alsa_n_channels      = int(Config->audio[CONFIG::ALSA_NCHANNELS_ID ]) ;
  int    alsa_sample_rate     = int(Config->audio[CONFIG::ALSA_SAMPLERATE_ID]) ;
  int    alsa_bit_depth       = int(Config->audio[CONFIG::ALSA_BITDEPTH_ID  ]) ;
  int    alsa_n_buffers       = int(Config->audio[CONFIG::ALSA_NBLOCKS_ID   ]) ;
  int    alsa_buffer_size     = int(Config->audio[CONFIG::ALSA_BLOCKSIZE_ID ]) ;
#  endif // _MAC
#endif // _WIN32
#ifdef _WIN32
DEBUG_TRACE_AUDIO_INIT_WIN

  switch ((audioStreamer::WinApi)audio_api_n)
  {
#  ifndef NO_SUPPORT_ASIO
    case audioStreamer::WIN_AUDIO_ASIO:
    {
      Audio = audioStreamer::NewASIO(OnSamples           , asio_driver_n   ,
                                     asio_input_b_n      , asio_input_e_n  ,
                                     asio_output_b_n     , asio_output_e_n ,
                                     should_show_asio_cp                   ) ;

      break ;
    }
#  endif // NO_SUPPORT_ASIO
#  ifndef NO_SUPPORT_KS
    case audioStreamer::WIN_AUDIO_KS:
    {
      // TODO: ks_input_device_n, ks_output_device_n unused
      Audio = audioStreamer::NewKS(OnSamples                       ,
                                   ks_sample_rate , ks_bit_depth   ,
                                   &ks_n_buffers  , &ks_buffer_size) ;

      // store back possibly modified params
      Config->audio.removeListener(Config) ;
      Config->audio.setProperty(CONFIG::KS_NBLOCKS_ID   , ks_n_buffers   , nullptr) ;
      Config->audio.setProperty(CONFIG::KS_BLOCKSIZE_ID , ks_buffer_size , nullptr) ;
      Config->audio.addListener(Config) ;

      break ;
    }
#  endif // NO_SUPPORT_KS
#  ifndef NO_SUPPORT_DS
    case audioStreamer::WIN_AUDIO_DS:
    {
      GUID input_guid , output_guid ;
      audioStreamer::GetDsGuidByName(ds_input_device .toRawUTF8() , &input_guid) ;
      audioStreamer::GetDsGuidByName(ds_output_device.toRawUTF8() , &output_guid) ;

      Audio = audioStreamer::NewDS(OnSamples                      ,
                                   input_guid     , output_guid   ,
                                   ds_sample_rate , ds_bit_depth  ,
                                   ds_n_buffers   , ds_buffer_size) ;

      break ;
    }
#  endif // NO_SUPPORT_DS
#  ifndef NO_SUPPORT_WAVE
    case audioStreamer::WIN_AUDIO_WAVE:
    {
      Audio = audioStreamer::NewWAVE(OnSamples                                  ,
                                     wave_input_device_n , wave_output_device_n ,
                                     wave_sample_rate    , wave_bit_depth       ,
                                     wave_n_buffers      , wave_buffer_size     ) ;

      break ;
    }
#  endif // NO_SUPPORT_WAVE
    default: break ;
  }
#else // _WIN32
#  ifdef _MAC
  UNUSED(audio_api_n) ;

  std::string input_device  = ca_input_device .toStdString() ;
  std::string output_device = ca_output_device.toStdString() ;
  Audio = audioStreamer::NewCA(OnSamples     , input_device   , output_device ,
                               ca_n_channels , ca_sample_rate , ca_bit_depth  ) ;

  Config->audio.setProperty(CONFIG::CA_DEVICE_ID , device_names , nullptr) ;

DEBUG_TRACE_AUDIO_INIT_MAC

#  else // _MAC
DEBUG_TRACE_AUDIO_INIT_NIX

  switch ((audioStreamer::NixApi)audio_api_n)
  {
    case audioStreamer::NIX_AUDIO_JACK:
    {
      UNUSED(jack_server_n) ;

      std::string jack_name = jack_client_name.toStdString() ;
      Audio = audioStreamer::NewJACK(OnSamples , Client                        ,
                                     jack_name , jack_n_inputs , jack_n_outputs) ;

DEBUG_TRACE_AUDIO_INIT_JACK_FAIL

      if (Audio != nullptr) break ; // else fallback on ALSA
    }
    case audioStreamer::NIX_AUDIO_ALSA:
    {
      std::string input_device  = alsa_input_device .toStdString() ;
      std::string output_device = alsa_output_device.toStdString() ;
      Audio = audioStreamer::NewALSA(OnSamples                          ,
                                     input_device     , output_device   ,
                                     alsa_n_channels                    ,
                                     alsa_sample_rate , alsa_bit_depth  ,
                                     alsa_n_buffers   , alsa_buffer_size) ;

      break ;
    }
    default: break ;
  }
#  endif // _MAC
#endif // _WIN32

DEBUG_TRACE_AUDIO_INIT

  bool isAudioEnabled = Audio != nullptr ;

  if (isAudioEnabled)
  {
    // kludge to sync loop progress to audible ticks
    // TODO: this may not be necessary at hipri update speed
    //           probably just disable loop progress at lopri speed
    double update_ivl = double(Config->gui[CONFIG::UPDATE_IVL_ID]) ;
    GuiBeatOffset     = Audio->getSampleRate() * (update_ivl * 0.002) ;

    // populate input source names arrays for ChannelConfig GUI
    int n_audio_sources = GetNumAudioSources() ;
    FreeAudioSources.clear() ; FreeAudioSourcePairs.clear() ;
    for (int source_n = 0 ; source_n < n_audio_sources ; ++source_n)
    {
      FreeAudioSources.add(source_n) ;
      if (source_n % 2) FreeAudioSourcePairs.add(source_n - 1) ;
    }

    // create master and stored local input channels
    if (!IsAudioInitialized) { ConfigureInitialChannels() ; IsAudioInitialized = true ; }
  }

  // set audio and status value holders for Config GUI
  Status = (isAudioEnabled) ? APP::LINJAM_STATUS_CONFIGPENDING :
                              APP::LINJAM_STATUS_AUDIOERROR    ;

  return isAudioEnabled ;
}

void LinJam::ConfigureInitialChannels()
{
  if (IsAudioInitialized) return ;

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
      Config->removeChannel(Config->localChannels , channel_store) ;
      --channel_n ;
    }
  }
}

void LinJam::Shutdown()
{
  // NJClient teardown
  JNL::close_socketlib() ;

  // LinJam teardown
  delete Audio ; delete Config ;

  // Constants teardown
  delete NETWORK::KNOWN_HOSTS ; delete NETWORK::KNOWN_BOTS ;

DEBUG_TRACE_SHUTDOWN
}


/* NJClient callbacks */

int LinJam::OnLicense(int user32 , char* license_text)
{
  UNUSED(user32) ;

  if (!IsAgreed()) Gui->license->setLicenseText(CharPointer_UTF8(license_text)) ;

DEBUG_TRACE_LICENSE

  return IsAgreed() ;
}

void LinJam::OnChatmsg(int user32 , NJClient* instance , const char** parms , int nparms)
{
  UNUSED(user32) ; UNUSED(instance) ; UNUSED(nparms) ;
  if (!parms[0]) return ;

  String chat_type    = String(CharPointer_UTF8(parms[CLIENT::CHATMSG_TYPE_IDX])) ;
  String chat_user    = String(CharPointer_UTF8(parms[CLIENT::CHATMSG_USER_IDX]))
                        .upToFirstOccurrenceOf(CONFIG::USER_IP_SPLIT_CHAR , false , false) ;
  String chat_text    = String(CharPointer_UTF8(parms[CLIENT::CHATMSG_MSG_IDX])) ;
  bool   is_topic_msg = (!chat_type.compare(CLIENT::CHATMSG_TYPE_TOPIC)) ;
  bool   is_bcast_msg = (!chat_type.compare(CLIENT::CHATMSG_TYPE_MSG)) ;
  bool   is_priv_msg  = (!chat_type.compare(CLIENT::CHATMSG_TYPE_PRIVMSG)) ;
  bool   is_join_msg  = (!chat_type.compare(CLIENT::CHATMSG_TYPE_JOIN)) ;
  bool   is_part_msg  = (!chat_type.compare(CLIENT::CHATMSG_TYPE_PART)) ;

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
                       int     n_samples     , int sample_rate       )
{
  if (Audio == nullptr)
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


/* NJClient runtime routines */

void LinJam::HandleTimer(int timer_id)
{
#if DEBUG_EXIT_IMMEDIAYELY
DBG("[DEBUG]: DEBUG_EXIT_IMMEDIAYELY defined - bailing") ; Client->quit() ;
#endif // DEBUG_EXIT_IMMEDIAYELY

  switch (timer_id)
  {
    case APP::CLIENT_TIMER_ID:     PumpClient() ;            break ;
    case APP::GUI_LO_TIMER_ID:     UpdateGuiLowPriority() ;  break ;
//  case APP::GUI_MD_TIMER_ID:     /* unused */              break ;
    case APP::GUI_HI_TIMER_ID:     UpdateGuiHighPriority() ; break ;
    case APP::AUDIO_INIT_TIMER_ID: InitializeAudio() ;       break ;
    default:                                                 break ;
  }

  if (timer_id == APP::AUDIO_INIT_TIMER_ID) Timer->stopTimer(timer_id) ;
}

void LinJam::PumpClient()
{
  UpdateStatus() ;

  if (Client->HasUserInfoChanged()             ) HandleUserInfoChanged() ;
  if (Client->GetStatus() >= APP::NJC_STATUS_OK) while (!Client->Run()) ;
}

void LinJam::UpdateStatus()
{
  // update status if not in an init, error, or hold state
  int  status   = int(Status.getValue()) ;
  bool is_ready = status >= APP::LINJAM_STATUS_READY ;
  if (is_ready) status = Client->GetStatus() ;

  String error_msg          = CharPointer_UTF8(Client->GetErrorStr()) ;
  bool   is_licence_pending = status == APP::NJC_STATUS_INVALIDAUTH && !IsAgreed() ;
  bool   is_room_full       = is_ready && !error_msg.compare(CLIENT::SERVER_FULL_ERROR) ;

  if      (is_licence_pending) status = APP::LINJAM_STATUS_LICENSEPENDING ;
  else if (is_room_full      ) status = APP::LINJAM_STATUS_ROOMFULL ;

  Status = status ;
}

void LinJam::HandleStatusChanged()
{
DEBUG_TRACE_STATUS_CHANGED

  APP::LinJamStatus status = (APP::LinJamStatus)int(Status.getValue()) ;

  // ignore sentinel value
  if (status == APP::LINJAM_STATUS_READY) return ;

  // set status indicator
  String host        = Client->GetHostName() ;
  String status_text =
      (status == APP::LINJAM_STATUS_AUDIOERROR    ) ? GUI::AUDIO_INIT_ERROR_MSG   :
      (status == APP::LINJAM_STATUS_AUDIOINIT     ) ? GUI::AUDIO_INIT_MSG         :
      (status == APP::LINJAM_STATUS_CONFIGPENDING ) ? GUI::CONFIG_PENDING_MSG     :
      (status == APP::LINJAM_STATUS_LICENSEPENDING) ? GUI::LICENSE_PENDING_TEXT   :
      (status == APP::LINJAM_STATUS_ROOMFULL      ) ? GUI::ROOM_FULL_TEXT         :
      (status == APP::NJC_STATUS_DISCONNECTED     ) ? GUI::DISCONNECTED_TEXT      :
      (status == APP::NJC_STATUS_INVALIDAUTH      ) ? GUI::INVALID_AUTH_TEXT      :
      (status == APP::NJC_STATUS_CANTCONNECT      ) ? GUI::FAILED_CONNECTION_TEXT :
      (status == APP::NJC_STATUS_OK               ) ? GUI::CONNECTED_TEXT + host  :
      (status == APP::NJC_STATUS_PRECONNECT       ) ? GUI::IDLE_TEXT              :
                                                      Status.toString()           ;
  Gui->statusbar->setStatusL(status_text) ;

  // set front-most GUI container
  Component* top_component =
      (status == APP::LINJAM_STATUS_AUDIOERROR    ) ?             Gui->config     :
      (status == APP::LINJAM_STATUS_AUDIOINIT     ) ?             Gui->config     :
      (status == APP::LINJAM_STATUS_CONFIGPENDING ) ?             Gui->config     :
      (status == APP::LINJAM_STATUS_LICENSEPENDING) ?             Gui->license    :
      (status == APP::LINJAM_STATUS_ROOMFULL      ) ?             Gui->login      :
      (status == APP::NJC_STATUS_DISCONNECTED     ) ?             Gui->login      :
      (status == APP::NJC_STATUS_INVALIDAUTH      ) ?             Gui->login      :
      (status == APP::NJC_STATUS_CANTCONNECT      ) ?             Gui->login      :
      (status == APP::NJC_STATUS_OK               ) ?             Gui->chat       :
      (status == APP::NJC_STATUS_PRECONNECT       ) ?             Gui->login      :
                                                      (Component*)Gui->background ;
  top_component  ->toFront(true) ;
  Gui->background->toBehind(top_component) ;

  // responses
  switch (status)
  {
    // retry login
    case APP::NJC_STATUS_INVALIDAUTH:
    case APP::NJC_STATUS_CANTCONNECT: // retry login (server occasionally rejects)
      if (RetryLogin-- > 0) Connect() ;                                      break ;
    case APP::NJC_STATUS_OK:          // store server credentials and present mixer GUI
      Config->setServer() ;
      UpdateGuiLowPriority() ;
      Gui->mixer->toFront(false) ;
      Gui->loop ->toFront(false) ;                                           break ;
    case APP::NJC_STATUS_PRECONNECT:  // auto-join
      if (AutoJoinHost.isNotEmpty() && Gui->login->quickLogin(AutoJoinHost))
        Gui->background->toFront(true) ;
      AutoJoinHost = "" ;                                                    break ;

    default:                                                                 break ;
  }
}

void LinJam::HandleUserInfoChanged()
{
#ifdef NO_UPDATE_REMOTES
  return ;
#endif // NO_UPDATE_REMOTES

  StringRef host = LinJamConfig::MakeHostId(str(Config->server[CONFIG::HOST_ID])) ;

DEBUG_TRACE_REMOTE_CHANNELS_VB

  // initialize dictionary for pruning parted users GUI elements
  ValueTree active_users = ValueTree("active-users") ;

  // fetch remote user states from server
  int user_idx = -1 ; String user_name ;
  while ((user_name = GetRemoteUserName(++user_idx)).isNotEmpty())
  {
    Identifier  user_id    = Config->MakeUserId(user_name) ;
    std::string nick       = (user_name = String(user_id)).toStdString() ;
    bool        is_ignored = !!Client->config_autosubscribe_userlist.count(nick) ;
    bool        is_bot     = NETWORK::KNOWN_BOTS->compareAttribute(host , user_name) ;

    // cache bot user_idx for recording time updates
    if (is_bot) Config->server.setProperty(CONFIG::BOT_USERIDX_ID , user_idx , nullptr) ;
    // TODO: we may be able to bail now without storing bot userdata (issue #64)

    // get or create remote user storage
    ValueTree user_store = Config->getOrAddRemoteUser(user_name) ;
    if (!user_store.isValid()) continue ;

    // update stored remote user state
    Config->updateRemoteUserState(user_store , user_idx , !is_ignored) ;
    if (is_ignored) continue ;

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

void LinJam::UpdateGuiHighPriority() { UpdateLoopProgress() ; UpdateVuMeters() ; }

void LinJam::UpdateGuiLowPriority() { UpdateRecordingTime() ; }

void LinJam::UpdateLoopProgress()
{
#ifdef NO_UPDATE_LOOP_PROGRESS_GUI
  return ;
#endif // NO_UPDATE_LOOP_PROGRESS_GUI

  // set loop progress to strobing effect when idle
  if (Status != APP::NJC_STATUS_OK) { Gui->loop->loopProgress = 1.0 ; return ; }

  // compute loop progress
  int    sample_n , n_samples ; Client->GetPosition(&sample_n , &n_samples) ;
  int    bpi               = Client->GetBPI() ;
  float  bpm               = Client->GetActualBPM() ;
  double linear_progress   = (sample_n + GuiBeatOffset) / n_samples ;
  int    beat_n            = ((int)(bpi * linear_progress) % bpi) + 1 ;
  double discrete_progress = (float)beat_n / bpi ;

  // update statusbar loop progress
  Gui->loop->updateBeatN(beat_n) ;
  Gui->loop->loopProgress = discrete_progress ; // linear_progress ;
  Gui->statusbar->setStatusR(String(bpi) + " bpi @ " + String(bpm) + " bpm") ;

  // sompute metro VU loop progress
  ValueTree metro_store    = Config->getChannelById(CONFIG::MASTERS_ID , CONFIG::METRO_ID) ;
  double    metro_is_muted = bool(  metro_store[CONFIG::IS_MUTED_ID]) ;
  double    metro_pan      = double(metro_store[CONFIG::PAN_ID]) ;
  double    metro_vu       = (metro_is_muted) ? 0.0 : discrete_progress ;
  double    metro_vu_l     = (metro_pan < 0.0) ? metro_vu : metro_vu * (1.0 - metro_pan) ;
  double    metro_vu_r     = (metro_pan > 0.0) ? metro_vu : metro_vu * (1.0 + metro_pan) ;

  // update metro VU loop progress
  metro_store.setProperty(CONFIG::VU_LEFT_ID  , metro_vu_l , nullptr) ;
  metro_store.setProperty(CONFIG::VU_RIGHT_ID , metro_vu_r , nullptr) ;
}

void LinJam::UpdateVuMeters()
{
#ifdef NO_UPDATE_VU_METERS_GUI
  return ;
#endif // NO_UPDATE_VU_METERS_GUI

  double master_vu_l = 0.0 ; double master_vu_r = 0.0 ;


  /* update local VUs */

  int channel_n = -1 ; int channel_idx ;
  while (~(channel_idx = Client->EnumLocalChannels(++channel_n)))
  {
    ValueTree channel_store = Config->getChannelByIdx(Config->localChannels , channel_idx) ;
    double    local_pan     = double(channel_store[CONFIG::PAN_ID]) ;
    double    local_vu_l    = GetChannelDb(channel_idx) - GUI::VU_DB_MIN ;
    int       stereo_status = int(channel_store[CONFIG::STEREO_ID]) ;
    if (!channel_store.isValid()) continue ;

    if (stereo_status == CONFIG::MONO)
    {
      channel_store.setProperty(CONFIG::VU_LEFT_ID , local_vu_l , nullptr) ;

      // compensate master VUs for local channel pan
      ScalePannedMonoVus(local_vu_l , local_pan , &master_vu_l , &master_vu_r) ; // mutates
    }
    else if (stereo_status == CONFIG::STEREO_L)
    {
      // ensure this faux-stereo channel has a matching faux-stereo pair channel
      int    pair_idx   = int(channel_store[CONFIG::PAIR_IDX_ID]) ;
      double local_vu_r = GetChannelDb(pair_idx) - GUI::VU_DB_MIN ;

      // compensate faux-stereo VUs for faux-stereo pan
      ComputePannedVus(local_pan , &local_vu_l , &local_vu_r) ; // mutates

      // update local channel VUs asynchronously
      channel_store.setProperty(CONFIG::VU_LEFT_ID  , local_vu_l , nullptr) ;
      master_vu_l = AddDecibels(master_vu_l , local_vu_l) ;
      channel_store.setProperty(CONFIG::VU_RIGHT_ID , local_vu_r , nullptr) ;
      master_vu_r = AddDecibels(master_vu_r , local_vu_r) ;
    }
  }


  /* update remote VUs */

  int user_idx = -1 ; String user_name ;
  while ((user_name = GetRemoteUserName(++user_idx)).isNotEmpty())
  {
    Identifier user_id            = Config->MakeUserId(user_name) ;
    ValueTree  user_store         = Config->getUserById(user_id) ;
    double     remote_master_vu_l = 0.0 ;
    double     remote_master_vu_r = 0.0 ; channel_n = -1 ; Identifier vu_id ;

    while (~(channel_idx = Client->EnumUserChannels(user_idx , ++channel_n)))
    {
      ValueTree channel_store = Config->getChannelByIdx(user_store , channel_idx) ;
      double    remote_pan    = double(channel_store[CONFIG::PAN_ID]) ;
      double    remote_vu_l   = GetChannelDb(user_idx , channel_idx) - GUI::VU_DB_MIN ;
      int       stereo_status = int(channel_store[CONFIG::STEREO_ID]) ;
      if (!channel_store.isValid()) continue ;

      if (stereo_status == CONFIG::MONO)
      {
        channel_store.setProperty(CONFIG::VU_LEFT_ID , remote_vu_l , nullptr) ;

        // compensate remote master VUs for remote channel pan
        ScalePannedMonoVus( remote_vu_l        , remote_pan         ,
                           &remote_master_vu_l , &remote_master_vu_r) ; // mutates
      }
      else if (stereo_status == CONFIG::STEREO_L)
      {
        // ensure this faux-stereo channel has a matching faux-stereo pair channel
        int    pair_idx    = int(channel_store[CONFIG::PAIR_IDX_ID]) ;
        double remote_vu_r = GetChannelDb(user_idx , pair_idx) - GUI::VU_DB_MIN ;

        // compensate faux-stereo VUs for faux-stereo pan
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

    // compensate remote master VUs for remote master pan
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


  /* update master VU */

  ValueTree master_store = Config->getChannelById(CONFIG::MASTERS_ID , CONFIG::MASTER_ID) ;
  double    master_pan   = double(master_store[CONFIG::PAN_ID]) ;

  // compensate master VUs for master pan
  if (master_pan > 0.0)
    ScalePannedMonoVus(master_vu_l , master_pan , &master_vu_l , &master_vu_r) ; // mutates
  if (master_pan < 0.0)
    ScalePannedMonoVus(master_vu_r , master_pan , &master_vu_l , &master_vu_r) ; // mutates

  master_store.setProperty(CONFIG::VU_LEFT_ID  , master_vu_l , nullptr) ;
  master_store.setProperty(CONFIG::VU_RIGHT_ID , master_vu_r , nullptr) ;
}

void LinJam::UpdateRecordingTime()
{
#ifdef NO_UPDATE_RECORDING_TIME_GUI
  return ;
#endif // NO_UPDATE_RECORDING_TIME_GUI

  if (Status != APP::NJC_STATUS_OK) return ;

  // NOTE: parsing recording time is somewhat brittle - (issue #64)
  //       dependent on constants such as NETWORK::KNOWN_BOTS and CLIENT::BOT_CHANNELIDX
  //       though these values are more conventional than canonical
  int    bot_useridx    = Config->server[CONFIG::BOT_USERIDX_ID] ;
  String host           = String(Client->GetHostName()) ;
  String bpi            = String(Client->GetBPI()) ;
  String bpm            = String((int)Client->GetActualBPM()) ;
  String recording_time = String::empty ;

  if (~bot_useridx)
  {
    recording_time  = GetRemoteChannelClientName(bot_useridx , CLIENT::BOT_CHANNELIDX) ;

    bool has_recording_time_changed = !!recording_time.compare(PrevRecordingTime) ;
    bool is_this_first_pass         = PrevRecordingTime.isEmpty() ;
    bool should_show_time           = (has_recording_time_changed && !is_this_first_pass) ;

    PrevRecordingTime = recording_time ;
    recording_time    = (should_show_time)? " - " + recording_time : String::empty ;
  }

  Gui->setTitle(host + " - " + bpi + "bpi / " + bpm + "bpm" + recording_time) ;
}


/* NJClient configuration */

void LinJam::ConfigureAudio()
{
  // defer initialization of audio devices to accommodate flooding
  //     e.g. per ConfigAudio::restoreDefults()
  Status = APP::LINJAM_STATUS_AUDIOINIT ;
  Timer->startTimer(APP::AUDIO_INIT_TIMER_ID , APP::AUDIO_INIT_DELAY) ;
}

void LinJam::ConfigureMasterChannel(Identifier a_key)
{
  ValueTree master_store = Config->getChannelById(CONFIG::MASTERS_ID , CONFIG::MASTER_ID) ;
  if (!master_store.isValid()) return ;

  // load stored config for this channel
  float volume   = float(master_store[CONFIG::VOLUME_ID  ]) ;
  float pan      = float(master_store[CONFIG::PAN_ID     ]) ;
  bool  is_muted = bool( master_store[CONFIG::IS_MUTED_ID]) ;

  // determine which NJClient channel params to modify
  bool should_init_all     = (a_key == CONFIG::CONFIG_INIT_ID                   ) ;
  bool should_set_volume   = (a_key == CONFIG::VOLUME_ID      || should_init_all) ;
  bool should_set_pan      = (a_key == CONFIG::PAN_ID         || should_init_all) ;
  bool should_set_is_muted = (a_key == CONFIG::IS_MUTED_ID    || should_init_all) ;

  // configure NJClient master channel
  if (should_set_volume  ) Client->config_mastervolume = (float)DB2VAL(volume) ;
  if (should_set_pan     ) Client->config_masterpan    = pan ;
  if (should_set_is_muted) Client->config_mastermute   = is_muted ;
}

void LinJam::ConfigureMetroChannel(Identifier a_key)
{
  ValueTree metro_store = Config->getChannelById(CONFIG::MASTERS_ID , CONFIG::METRO_ID) ;
  if (!metro_store.isValid()) return ;

  // load stored config for this channel
  float volume    = float(metro_store[CONFIG::VOLUME_ID  ]) ;
  float pan       = float(metro_store[CONFIG::PAN_ID     ]) ;
  bool  is_muted  = bool( metro_store[CONFIG::IS_MUTED_ID]) ;
  int   source_n  = int(  metro_store[CONFIG::SOURCE_N_ID]) ;
  bool  is_stereo = int(  metro_store[CONFIG::STEREO_ID  ]) != CONFIG::MONO ;

  // determine which NJClient channel params to modify
  bool should_init_all     = (a_key == CONFIG::CONFIG_INIT_ID                   ) ;
  bool should_set_volume   = (a_key == CONFIG::VOLUME_ID      || should_init_all) ;
  bool should_set_pan      = (a_key == CONFIG::PAN_ID         || should_init_all) ;
  bool should_set_is_muted = (a_key == CONFIG::IS_MUTED_ID    || should_init_all) ;
  bool should_set_source_n = (a_key == CONFIG::SOURCE_N_ID    || should_init_all) ;
  bool should_set_stereo   = (a_key == CONFIG::STEREO_ID      || should_init_all) ;

  // configure NJClient metro channel
  if (should_set_volume  ) Client->config_metronome           = (float)DB2VAL(volume) ;
  if (should_set_pan     ) Client->config_metronome_pan       = pan ;
  if (should_set_is_muted) Client->config_metronome_mute      = is_muted ;
  if (should_set_source_n) Client->config_metronome_channel   = source_n ;
  if (should_set_stereo  ) Client->config_metronome_stereoout = is_stereo ;
}

void LinJam::ConfigureLocalChannel(ValueTree channel_store , Identifier a_key)
{
  // filter uninteresting config params
  if (!channel_store.isValid()                                       ||
     a_key == CONFIG::CHANNEL_IDX_ID || a_key == CONFIG::PAIR_IDX_ID ||
     a_key == CONFIG::VU_LEFT_ID     || a_key == CONFIG::VU_RIGHT_ID  ) return ;

  // determine which NJClient channel params to modify
  bool should_init_all      = (a_key == CONFIG::CONFIG_INIT_ID                    ) ;
  bool should_set_name      = (a_key == CONFIG::CHANNEL_NAME_ID || should_init_all) ;
  bool should_set_volume    = (a_key == CONFIG::VOLUME_ID       || should_init_all) ;
  bool should_set_pan       = (a_key == CONFIG::PAN_ID          ||
                               a_key == CONFIG::STEREO_ID       || should_init_all) ;
  bool should_set_is_xmit   = (a_key == CONFIG::IS_XMIT_RCV_ID  || should_init_all) ;
  bool should_set_is_muted  = (a_key == CONFIG::IS_MUTED_ID     || should_init_all) ;
  bool should_set_is_solo   = (a_key == CONFIG::IS_SOLO_ID      || should_init_all) ;
  bool should_set_source_n  = (a_key == CONFIG::SOURCE_N_ID     || should_init_all) ;
  bool should_set_bit_depth = (a_key == CONFIG::BIT_DEPTH_ID    || should_init_all) ;
  bool should_set_is_stereo = (a_key == CONFIG::STEREO_ID       || should_init_all) ;

  // load stored config for this channel
  String channel_name  = str(  channel_store[CONFIG::CHANNEL_NAME_ID]) ;
  int    channel_idx   = int(  channel_store[CONFIG::CHANNEL_IDX_ID ]) ;
  int    pair_idx      = int(  channel_store[CONFIG::PAIR_IDX_ID    ]) ;
  float  volume        = float(channel_store[CONFIG::VOLUME_ID      ]) ;
  float  pan           = float(channel_store[CONFIG::PAN_ID         ]) ;
  bool   is_xmit       = bool( channel_store[CONFIG::IS_XMIT_RCV_ID ]) ;
  bool   is_muted      = bool( channel_store[CONFIG::IS_MUTED_ID    ]) ;
  bool   is_solo       = bool( channel_store[CONFIG::IS_SOLO_ID     ]) ;
  int    source_n      = int(  channel_store[CONFIG::SOURCE_N_ID    ]) ;
  int    bit_depth     = int(  channel_store[CONFIG::BIT_DEPTH_ID   ]) ;
  int    stereo_status = int(  channel_store[CONFIG::STEREO_ID      ]) ;

         channel_name  = Config->MakeStereoName(channel_name , stereo_status) ;

DEBUG_TRACE_CONFIGURE_LOCAL_CHANNEL

  // handle channel name change
  const char* new_name = (should_set_name)? channel_name.toRawUTF8() : nullptr ;

  // handle faux-stereo panning
  if (should_set_pan) pan = ClientPan(pan , stereo_status) ;

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
    if (should_set_is_stereo)
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
      String    pair_name     = Config->MakeStereoName(channel_name , CONFIG::STEREO_R) ;
      int       pair_source_n = source_n + 1 ;

      pair_store.setProperty(CONFIG::CHANNEL_NAME_ID , pair_name        , nullptr) ;
      pair_store.setProperty(CONFIG::CHANNEL_IDX_ID  , pair_idx         , nullptr) ;
      pair_store.setProperty(CONFIG::SOURCE_N_ID     , pair_source_n    , nullptr) ;
      pair_store.setProperty(CONFIG::STEREO_ID       , CONFIG::STEREO_R , nullptr) ;

      ConfigureLocalChannel(pair_store , a_key) ;
    }

    // update client channels names on mono->stereo conversion
    if (should_set_is_stereo)
      channel_store.setProperty(CONFIG::CHANNEL_NAME_ID , channel_name , nullptr) ;
  }
  // handle stereo->mono conversion
  else if (stereo_status == CONFIG::MONO && should_set_is_stereo)
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
  // filter uninteresting config params
  if (!user_store.isValid()           || !channel_store.isValid()     ||
     a_key == CONFIG::CHANNEL_NAME_ID                                 ||
     a_key == CONFIG::CHANNEL_IDX_ID  || a_key == CONFIG::PAIR_IDX_ID ||
     a_key == CONFIG::VU_LEFT_ID      || a_key == CONFIG::VU_RIGHT_ID  ) return ;

  // determine which NJClient channel params to modify
  bool should_init_all      = (a_key == CONFIG::CONFIG_INIT_ID                   ) ;
  bool should_set_volume    = (a_key == CONFIG::VOLUME_ID      || should_init_all) ;
  bool should_set_pan       = (a_key == CONFIG::PAN_ID         ||
                               a_key == CONFIG::STEREO_ID      || should_init_all) ;
  bool should_set_is_rcv    = (a_key == CONFIG::IS_XMIT_RCV_ID || should_init_all) ;
  bool should_set_is_muted  = (a_key == CONFIG::IS_MUTED_ID    || should_init_all) ;
  bool should_set_is_solo   = (a_key == CONFIG::IS_SOLO_ID     || should_init_all) ;
  bool should_set_is_stereo = (a_key == CONFIG::STEREO_ID      || should_init_all) ;

  // load stored config for this channel
  int   user_idx      = int(  user_store   [CONFIG::USER_IDX_ID   ]) ;
  int   channel_idx   = int(  channel_store[CONFIG::CHANNEL_IDX_ID]) ;
  int   pair_idx      = int(  channel_store[CONFIG::PAIR_IDX_ID   ]) ;
  float volume        = float(channel_store[CONFIG::VOLUME_ID     ]) ;
  float pan           = float(channel_store[CONFIG::PAN_ID        ]) ;
  bool  is_rcv        = bool( channel_store[CONFIG::IS_XMIT_RCV_ID]) ;
  bool  is_muted      = bool( channel_store[CONFIG::IS_MUTED_ID   ]) ;
  bool  is_solo       = bool( channel_store[CONFIG::IS_SOLO_ID    ]) ;
  int   sink_n        = 0 ; // TODO: not yet clear how to handle remote sink_n
  int   stereo_status = int(  channel_store[CONFIG::STEREO_ID     ]) ;                           \
  bool  is_pannable   = true ;

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
    if (should_set_pan) pan = ClientPan(pan , stereo_status) ;

    // configure NJClient remote channel allowing master overrides
    ValueTree master_store   = Config->getUserMasterChannel(user_store) ;
    bool      is_master_rcv  = bool(master_store[CONFIG::IS_XMIT_RCV_ID]) ;
    bool      is_master_solo = bool(master_store[CONFIG::IS_SOLO_ID    ]) ;
    Client->SetUserChannelState(user_idx            , channel_idx               ,
                                should_set_is_rcv   , is_rcv && is_master_rcv   ,
                                should_set_volume   , (float)DB2VAL(volume)     ,
                                should_set_pan      , pan                       ,
                                should_set_is_muted , is_muted                  ,
                                should_set_is_solo  , is_solo || is_master_solo ,
                                should_init_all     , sink_n                    ,
                                should_init_all     , is_pannable               ) ;

    // configure faux-stereo pair implicitly
    if (stereo_status == CONFIG::STEREO_L)
    {
      ValueTree pair_store = Config->getChannelByIdx(user_store , pair_idx) ;
      if (should_set_is_stereo || should_init_all)
        ConfigureRemoteChannel(user_store , pair_store , CONFIG::CONFIG_INIT_ID) ;
      else pair_store.setProperty(a_key , channel_store[a_key] , nullptr) ;
    }
  }
}


/* audio signal helpers */

double LinJam::AddDecibels(double vu_l , double vu_r)
{
  return 10 * log10(pow(10.0 , (vu_l / 10.0)) + pow(10.0 , (vu_r / 10.0))) ;
}

void LinJam::ComputePannedVus(double pan , double* vu_l , double* vu_r)
{
  double vu_l_in = *vu_l ;
  double vu_r_in = *vu_r ;

  // scale master VU meters per master pan
  if (pan > 0.0) // pan right
  {
    // decrease left contribution to left vu
    *vu_l *= log10(10.0 * (1.0 - pan)) ;
    // increase left contribution to right vu
    *vu_r = AddDecibels(vu_r_in , vu_l_in * pan) ;
  }

  if (pan < 0.0) // pan left
  {
    // increase right contribution to left VU
    *vu_l = AddDecibels(vu_l_in , vu_r_in * -pan) ;
    // decrease right contribution to right VU
    *vu_r *= log10(10.0 * (1.0 + pan)) ;
  }

  // cap underflows
  if (isnan(*vu_l)) *vu_l = 0.0 ;
  if (isnan(*vu_r)) *vu_r = 0.0 ;
  if (vu_l_in == 0.0 && vu_r_in == 0.0) *vu_l = *vu_r = 0.0 ;
}

void LinJam::ScalePannedMonoVus(double vu_mono , double pan , double* vu_l , double* vu_r)
{
  // compute panned mono channel contributions to left and right master VU meters
  *vu_l = (pan > 0.0) ? vu_mono * log10(10.0 * (1.0 - pan)) : vu_mono ; // pan_left
  *vu_r = (pan < 0.0) ? vu_mono * log10(10.0 * (1.0 + pan)) : vu_mono ; // pan right

  // cap underflows
  if (isnan(*vu_l)) *vu_l = 0.0 ;
  if (isnan(*vu_r)) *vu_r = 0.0 ;
}

float LinJam::ClientPan(float pan , int stereo_status)
{
  // interpret faux-stereo pan for a real NJClient channel
  bool is_mono_channel = stereo_status == CONFIG::MONO ;
  bool is_pair_channel = stereo_status == CONFIG::STEREO_R ;
  return (is_mono_channel)? pan : (!is_pair_channel)                             ?
                                  ((pan <= 0.0f) ? -1.0f : -1.0f + (pan * 2.0f)) :
                                  ((pan >= 0.0f) ? +1.0f : +1.0f + (pan * 2.0f)) ;
}


/* NJClient config helpers */

int LinJam::GetNumAudioSources()
{
  return (Audio != nullptr)? Audio->getNInputChannels() : 0 ;
}

int LinJam::GetNumLocalChannels()
{
  int n_occupied_slots = -1 ; while (~Client->EnumLocalChannels(++n_occupied_slots)) ;
  return n_occupied_slots ;
}

int LinJam::GetNumVacantChannels()
{
  return (Audio != nullptr)? GetNumAudioSources() - GetNumLocalChannels() : 0 ;
}

int LinJam::GetVacantLocalChannelIdx()
{
  // find the first vacant NJClient local channel slot index
  int channel_idx = -1 ; while (IsConfiguredChannel(++channel_idx)) ;
  bool is_vacant_slot = (channel_idx < GetNumAudioSources()) ;

  return (is_vacant_slot)? channel_idx : -1 ;
}

String LinJam::GetStoredChannelName(ValueTree channel_store)
{
  return str(channel_store[CONFIG::CHANNEL_NAME_ID]) ;
}

String LinJam::GetLocalChannelClientName(int channel_idx)
{
  return CharPointer_UTF8(Client->GetLocalChannelName(channel_idx)) ;
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

double LinJam::GetChannelDb(int channel_idx)
{
  return VAL2DB(Client->GetLocalChannelPeak(channel_idx)) ;
}

double LinJam::GetChannelDb(int user_idx , int channel_idx)
{
  return VAL2DB(Client->GetUserChannelPeak(user_idx , channel_idx)) ;
}
