#if DEBUG

#include "Trace.h"


// enable debug features
// #define DEBUG_EXIT_IMMEDIATELY
// #define DEBUG_AUTOJOIN_HOST if (cli_args.isEmpty()) cli_args = "localhost:2049"
// #define DEBUG_AUTOJOIN_HOST if (cli_args.isEmpty()) cli_args = "ninbot.com:2049"
// #define DEBUG_AUTOJOIN_HOST if (cli_args.isEmpty()) cli_args = "ninjamer.com:2051"


/* state */

#ifdef DEBUG_AUTOJOIN_HOST
#define DEBUG_TRACE_INIT Trace::TraceState("initializing") ; \
        DEBUG_AUTOJOIN_HOST                                  ;
#else // DEBUG_AUTOJOIN_HOST
#define DEBUG_TRACE_INIT Trace::TraceState("initializing") ;
#endif // DEBUG_AUTOJOIN_HOST

#define DEBUG_TRACE_SESSIONDIR                                                          \
  Trace::TraceClient("preparing session dir '" + SessionDir.getFullPathName() + "'- " + \
                     (SessionDir.isDirectory() ? "already exists" : "created")        ) ;

#define DEBUG_TRACE_STATUS_CHANGED                                               \
  int    prev_status   = Trace::DbgPrevStatus ;                                  \
  int    curr_status   = Trace::DbgPrevStatus = int(Status.getValue()) ;         \
  String prev_state    = Trace::Status2String(prev_status) ;                     \
  String curr_state    = Trace::Status2String(curr_status) ;                     \
  char*  client_error  = Client->GetErrorStr() ;                                 \
  Trace::TraceState(prev_state + " -> " + curr_state) ;                          \
  if (curr_status == APP::NJC_STATUS_OK)                                         \
    Trace::TraceServer("connected to host: " + String(Client->GetHostName())) ;  \
  if (client_error[0])                                                           \
    Trace::TraceServer("Error: " + CharPointer_UTF8(client_error)) ;             \
  Trace::TraceGui(                                                               \
      (Status == APP::LINJAM_STATUS_AUDIOERROR    ) ? "showing config pane"    : \
      (Status == APP::LINJAM_STATUS_CONFIGPENDING ) ? "showing config pane"    : \
      (Status == APP::LINJAM_STATUS_LICENSEPENDING) ? "showing license pane"   : \
      (Status == APP::LINJAM_STATUS_ROOMFULL      ) ? "showing login pane"     : \
      (Status == APP::NJC_STATUS_DISCONNECTED     ) ? "showing login pane"     : \
      (Status == APP::NJC_STATUS_INVALIDAUTH      ) ? "showing login pane"     : \
      (Status == APP::NJC_STATUS_CANTCONNECT      ) ? "showing login pane"     : \
      (Status == APP::NJC_STATUS_OK               ) ? "showing main pane"      : \
      (Status == APP::NJC_STATUS_PRECONNECT       ) ? "showing login pane"     : \
                                                      "showing background pane") ;

#define DEBUG_TRACE_CONNECT                                                  \
  Trace::TraceState((!IsAgreed())? "connecting to " + host :                 \
                                   "joining "       + host + " as " + login) ;

#define DEBUG_TRACE_LICENSE                                          \
  Trace::TraceState((IsAgreed())? "agreeing to license" :            \
                                  "prompting for license agreement") ;

#define DEBUG_TRACE_SHUTDOWN Trace::TraceState("clean shutdown - bye") ;


/* audio */

#define DEBUG_TRACE_AUDIO_INIT_WIN                                                           \
  String type =(audio_api_n == audioStreamer::WIN_AUDIO_ASIO) ? GUI::ASIO_DEVICE_TYPE :      \
               (audio_api_n == audioStreamer::WIN_AUDIO_KS)   ? GUI::KS_DEVICE_TYPE   :      \
               (audio_api_n == audioStreamer::WIN_AUDIO_DS)   ? GUI::DS_DEVICE_TYPE   :      \
               (audio_api_n == audioStreamer::WIN_AUDIO_WAVE) ? GUI::WAVE_DEVICE_TYPE :      \
                                                                GUI::NFG_DEVICE_TYPE  ;      \
  String init_msg = "initializing " + type + " audiostreamer" ;                              \
  if (!TRACE_AUDIO_INIT_VB) Trace::TraceClient(init_msg) ;                                   \
  else {                    Trace::TraceClient(init_msg + " =>") ;                           \
    switch ((audioStreamer::WinApi)audio_api_n)                                              \
    {                                                                                        \
      case audioStreamer::WIN_AUDIO_ASIO:                                                    \
        Trace::TraceKVP("\t" , CONFIG::ASIO_DRIVER_KEY     , String(asio_driver_n       )) ; \
        Trace::TraceKVP("\t" , CONFIG::ASIO_INPUTB_KEY     , String(asio_input_b_n      )) ; \
        Trace::TraceKVP("\t" , CONFIG::ASIO_INPUTE_KEY     , String(asio_input_e_n      )) ; \
        Trace::TraceKVP("\t" , CONFIG::ASIO_OUTPUTB_KEY    , String(asio_output_b_n     )) ; \
        Trace::TraceKVP("\t" , CONFIG::ASIO_OUTPUTE_KEY    , String(asio_output_e_n     )) ; \
      break ;                                                                                \
      case audioStreamer::WIN_AUDIO_KS:                                                      \
        Trace::TraceKVP("\t" , CONFIG::KS_SAMPLERATE_KEY   , String(ks_sample_rate      )) ; \
        Trace::TraceKVP("\t" , CONFIG::KS_BITDEPTH_KEY     , String(ks_bit_depth        )) ; \
        Trace::TraceKVP("\t" , CONFIG::KS_NBLOCKS_KEY      , String(ks_n_buffers        )) ; \
        Trace::TraceKVP("\t" , CONFIG::KS_BLOCKSIZE_KEY    , String(ks_buffer_size      )) ; \
      break ;                                                                                \
      case audioStreamer::WIN_AUDIO_DS:                                                      \
        Trace::TraceKVP("\t" , CONFIG::DS_INPUT_KEY        , String(ds_input_device     )) ; \
        Trace::TraceKVP("\t" , CONFIG::DS_OUTPUT_KEY       , String(ds_output_device    )) ; \
        Trace::TraceKVP("\t" , CONFIG::DS_SAMPLERATE_KEY   , String(ds_sample_rate      )) ; \
        Trace::TraceKVP("\t" , CONFIG::DS_BITDEPTH_KEY     , String(ds_bit_depth        )) ; \
        Trace::TraceKVP("\t" , CONFIG::DS_NBLOCKS_KEY      , String(ds_n_buffers        )) ; \
        Trace::TraceKVP("\t" , CONFIG::DS_BLOCKSIZE_KEY    , String(ds_buffer_size      )) ; \
      break ;                                                                                \
      case audioStreamer::WIN_AUDIO_WAVE:                                                    \
        Trace::TraceKVP("\t" , CONFIG::WAVE_INPUT_KEY      , String(wave_input_device_n )) ; \
        Trace::TraceKVP("\t" , CONFIG::WAVE_OUTPUT_KEY     , String(wave_output_device_n)) ; \
        Trace::TraceKVP("\t" , CONFIG::WAVE_SAMPLERATE_KEY , String(wave_sample_rate    )) ; \
        Trace::TraceKVP("\t" , CONFIG::WAVE_BITDEPTH_KEY   , String(wave_bit_depth      )) ; \
        Trace::TraceKVP("\t" , CONFIG::WAVE_NBLOCKS_KEY    , String(wave_n_buffers      )) ; \
        Trace::TraceKVP("\t" , CONFIG::WAVE_BLOCKSIZE_KEY  , String(wave_buffer_size    )) ; \
      break ;                                                                                \
  } }

#define DEBUG_TRACE_AUDIO_INIT_MAC                                               \
  String type = GUI::CA_DEVICE_TYPE ;                                            \
  String init_msg = "initializing " + type + " audiostreamer" ;                  \
  if (!TRACE_AUDIO_INIT_VB) Trace::TraceClient(init_msg) ;                       \
  else {                    Trace::TraceClient(init_msg + " =>") ;               \
    Trace::TraceKVP("\t" , CONFIG::CA_INPUT_KEY      , ca_input_name         ) ; \
    Trace::TraceKVP("\t" , CONFIG::CA_OUTPUT_KEY     , ca_output_name        ) ; \
    Trace::TraceKVP("\t" , CONFIG::CA_NCHANNELS_KEY  , String(ca_n_channels )) ; \
    Trace::TraceKVP("\t" , CONFIG::CA_SAMPLERATE_KEY , String(ca_sample_rate)) ; \
    Trace::TraceKVP("\t" , CONFIG::CA_BITDEPTH_KEY   , String(ca_bit_depth  )) ; }

#define DEBUG_TRACE_AUDIO_INIT_JACK                                            \
  Trace::TraceKVP("\t" , CONFIG::JACK_NAME_KEY     , jack_client_name      ) ; \
  Trace::TraceKVP("\t" , CONFIG::JACK_NINPUTS_KEY  , String(jack_n_inputs )) ; \
  Trace::TraceKVP("\t" , CONFIG::JACK_NOUTPUTS_KEY , String(jack_n_outputs)) ;

#define DEBUG_TRACE_AUDIO_INIT_ALSA                                                \
  Trace::TraceKVP("\t" , CONFIG::ALSA_INPUT_KEY      , alsa_input_device       ) ; \
  Trace::TraceKVP("\t" , CONFIG::ALSA_OUTPUT_KEY     , alsa_output_device      ) ; \
  Trace::TraceKVP("\t" , CONFIG::ALSA_NCHANNELS_KEY  , String(alsa_n_channels) ) ; \
  Trace::TraceKVP("\t" , CONFIG::ALSA_SAMPLERATE_KEY , String(alsa_sample_rate)) ; \
  Trace::TraceKVP("\t" , CONFIG::ALSA_BITDEPTH_KEY   , String(alsa_bit_depth)  ) ; \
  Trace::TraceKVP("\t" , CONFIG::ALSA_NBLOCKS_KEY    , String(alsa_n_buffers)  ) ; \
  Trace::TraceKVP("\t" , CONFIG::ALSA_BLOCKSIZE_KEY  , String(alsa_buffer_size)) ;

#define DEBUG_TRACE_AUDIO_INIT_NIX                                                       \
  String type = (audio_api_n == audioStreamer::NIX_AUDIO_JACK) ? GUI::JACK_DEVICE_TYPE : \
                (audio_api_n == audioStreamer::NIX_AUDIO_ALSA) ? GUI::ALSA_DEVICE_TYPE : \
                                                                 GUI::NFG_DEVICE_TYPE ;  \
  String init_msg = "initializing " + type + " audiostreamer" ;                          \
  if (!TRACE_AUDIO_INIT_VB) Trace::TraceClient(init_msg) ;                               \
  else {                    Trace::TraceClient(init_msg + " =>") ;                       \
    if (audio_api_n == audioStreamer::NIX_AUDIO_JACK) DEBUG_TRACE_AUDIO_INIT_JACK ;      \
    if (audio_api_n == audioStreamer::NIX_AUDIO_ALSA) DEBUG_TRACE_AUDIO_INIT_ALSA        }

#define DEBUG_TRACE_AUDIO_INIT_JACK_FAIL                                              \
  if (!Audio) { Trace::TraceState("could not connect to " + GUI::JACK_DEVICE_TYPE +   \
                                  " - falling back to "   + GUI::ALSA_DEVICE_TYPE ) ; \
                type = GUI::ALSA_DEVICE_TYPE ;                                        \
                if (TRACE_AUDIO_INIT_VB) { DEBUG_TRACE_AUDIO_INIT_ALSA }              }

#define DEBUG_TRACE_AUDIO_INIT                                                            \
  String streamer_msg = " audio device using " + type  + " AudioStreamer" ;               \
  if (Audio == nullptr) Trace::TraceError("error opening" + streamer_msg) ;               \
  else                  Trace::TraceState("opened"        + streamer_msg      + " - "  +  \
                                          String(Audio->getNInputChannels() ) + "in "  +  \
                                          String(Audio->getNOutputChannels()) + "out " +  \
                                          String(Audio->getSampleRate()     ) + "Hz "  +  \
                                          String(Audio->getBitDepth()       ) + "bit"  )  ;


/* channels */

#define DEBUG_TRACE_INITIAL_CHANNELS                                               \
  int n_chs = Config->localChannels.getNumChildren() ;                             \
  if (!n_chs) Trace::TraceConfig("no stored channels found") ;                     \
  else Trace::TraceConfig("restoring " + String(n_chs) + " stored local channels") ;

#define DEBUG_TRACE_ADD_LOCAL_CHANNEL                                                     \
  String channel_name = str(channel_store[CONFIG::CHANNEL_NAME_ID]) ;                     \
  int    ch_idx       = int(channel_store[CONFIG::CHANNEL_IDX_ID ]) ;                     \
  int    source       = int(channel_store[CONFIG::SOURCE_N_ID    ]) ;                     \
  bool   stereo       = int(channel_store[CONFIG::STEREO_ID      ]) != CONFIG::MONO ;     \
  String type         = (!stereo)? "mono" : "stereo" ;                                    \
  bool   is_new       = ch_idx == CONFIG::DEFAULT_CHANNEL_IDX ;                           \
  bool   exists       = IsConfiguredChannel(ch_idx) ;                                     \
  bool   valid_source = source >= 0 && source < GetNumAudioSources() ;                    \
  int    n_vacant     = GetNumVacantChannels() ;                                          \
  bool   no_free_chs  = (!stereo && n_vacant < 1) || (stereo && n_vacant < 2) ;           \
  String dbg          = "when adding " + String((is_new)? "new" : "stored") + " local " + \
                        type + " input[" + String(source) + "] '" + channel_name + "'" ;  \
  if (exists)                                                                             \
    Trace::TraceError("channel already exists " + dbg) ;                                  \
  else if (!valid_source)                                                                 \
    Trace::TraceError("non-existent source " + dbg) ;                                     \
  else if (no_free_chs)                                                                   \
  {                                                                                       \
    Trace::TraceError("insufficient free channels " + dbg) ;                              \
    if (TRACE_LOCAL_CHANNELS_VB)                                                          \
      DBG(Trace::DumpStoredChannels() + Trace::DumpClientChannels()) ;                    \
  }                                                                                       \
  else Trace::TraceEvent(dbg) ;

#define DEBUG_TRACE_INSTANTIATE_LOCAL_CHANNEL                                    \
  Trace::TraceState("instantiating local " + type + " " +                        \
                    String(channel_store.getType()) + " '" + channel_name + "'") ;

#define DEBUG_TRACE_CONFIGURE_LOCAL_CHANNEL                                              \
  String chan        = String(channel_store.getType()) + " '" + channel_name + "'" ;     \
  bool   is_new      = !IsConfiguredChannel(channel_idx) ;                               \
  bool   is_mono     = stereo_status == CONFIG::MONO ;                                   \
  bool   is_stereo   = stereo_status != CONFIG::MONO ;                                   \
  bool   is_stereo_l = stereo_status == CONFIG::STEREO_L ;                               \
  bool   is_stereo_r = stereo_status == CONFIG::STEREO_R ;                               \
  String pairidx     = String(pair_idx) + ((is_mono && !is_new) ? " (deleting)" :        \
                                           (is_stereo_l       ) ? " (pending)"  : "") ;  \
  String type        = (is_mono  )    ? "mono"        : "stereo" ;                       \
  String prev_type   = (is_stereo)    ? "mono"        : "stereo" ;                       \
  String pan_str     = " (" + String(ClientPan(pan , stereo_status)) + " faux-stereo)" ; \
  String pan_msg     = String(pan)       + ((is_mono    ) ? ""            : pan_str) ;   \
  String stereo      = String(is_stereo) + ((is_mono    ) ? " (MONO)"     :              \
                                            (is_stereo_l) ? " (STEREO_L)" :              \
                                            (is_stereo_r) ? " (STEREO_R)" : "") ;        \
  if (should_set_is_stereo && !should_init_all)                                          \
    Trace::TraceClient("converting local " + prev_type + " " + chan + " to " + type) ;   \
  Trace::TraceClient("configuring " + String((is_new) ? "new"  : "existing")           + \
    " local " + type + " " + chan + ((is_stereo_l) ? " and its stereo pair" : "")      + \
    ((!TRACE_LOCAL_CHANNELS_VB) ? ""                                                 :   \
      (((should_set_name     ) ? "\n  name        => " + channel_name        : "") +     \
       ((should_init_all     ) ? "\n  channel_idx => " + String(channel_idx) : "") +     \
       ((should_set_is_stereo) ? "\n  pair_idx    => " + pairidx             : "") +     \
       ((should_set_volume   ) ? "\n  volume      => " + String(volume)      : "") +     \
       ((should_set_pan      ) ? "\n  pan         => " + pan_msg             : "") +     \
       ((should_set_is_xmit  ) ? "\n  is_xmit     => " + String(is_xmit)     : "") +     \
       ((should_set_is_muted ) ? "\n  is_muted    => " + String(is_muted)    : "") +     \
       ((should_set_is_solo  ) ? "\n  is_solo     => " + String(is_solo)     : "") +     \
       ((should_set_source_n ) ? "\n  source_n    => " + String(source_n)    : "") +     \
       ((should_set_bit_depth) ? "\n  bit_depth   => " + String(bit_depth)   : "") +     \
       ((should_set_is_stereo) ? "\n  is_stereo   => " + stereo              : "") ) ) ) ;

#define DEBUG_TRACE_REMOVE_LOCAL_CHANNEL                                       \
  String type = (int(channel_store[CONFIG::STEREO_ID]) == CONFIG::MONO) ?      \
                "mono" : "stereo" ;                                            \
  Trace::TraceEvent("destroying local " + type + " channel["                 + \
                    channel_store[CONFIG::CHANNEL_IDX_ID].toString() + "] '" + \
                    String(channel_store.getType()) + "'"                    ) ;

#if TRACE_DUMP_FREE_INPUTS
#  define DEBUG_TRACE_DUMP_FREE_INPUTS_VB                                          \
  SortedSet<int> monos   = FreeAudioSources ;     int n_monos   = monos.size() ;   \
  SortedSet<int> stereos = FreeAudioSourcePairs ; int n_stereos = stereos.size() ; \
  String dump = String(n_monos)   + " FreeAudioSources     = [" ;                  \
  for (int i = 0 ; i < n_monos ; ++i)   dump += String(monos[i])   + " " ;         \
  Trace::TraceConfigVb(dump.trim() + "]") ;                                        \
  dump       = String(n_stereos)  + " FreeAudioSourcePairs = [" ;                  \
  for (int i = 0 ; i < n_stereos ; ++i) dump += String(stereos[i]) + " " ;         \
  Trace::TraceConfigVb(dump.trim() + "]") ;
#else // TRACE_DUMP_FREE_INPUTS
#  define DEBUG_TRACE_DUMP_FREE_INPUTS_VB ;
#endif // TRACE_DUMP_FREE_INPUTS

#define DEBUG_TRACE_REMOTE_CHANNELS                                                   \
    bool   is_bot = str(NETWORK::KNOWN_BOTS.getProperty(host , "")) == String(u_id) ; \
    String hidden = (hide_bots && is_bot) ? " (bot hidden)" : "" ;                    \
    String dbg    = "NJClient remote user[" + String(u_idx) + "] =>" + hidden +       \
        "\n  user_name   => "   + String(u_name)                              +       \
        "\n  user_volume => "   + String(u_vol)                               +       \
        "\n  user_pan    => "   + String(u_pan)                               +       \
        "\n  user_mute   => "   + String(u_mute)                              ;       \
    int ch_n = -1 ; int ch_idx ;                                                      \
    while (~(ch_idx = LinJam::Client->EnumUserChannels(u_idx , ++ch_n)))              \
    {                                                                                 \
      bool ch_rcv ;  float ch_vol ;  float ch_pan ; bool ch_mute ;                    \
      bool ch_solo ; int   ch_sink ; bool  ch_pannable ;                              \
      String ch_name = LinJam::GetRemoteChannelClientName(u_idx , ch_idx) ;           \
      LinJam::Client->GetUserChannelState(u_idx    , ch_idx   , &ch_rcv   ,           \
                                          &ch_vol  , &ch_pan  , &ch_mute  ,           \
                                          &ch_solo , &ch_sink , &ch_pannable) ;       \
      dbg += "\n  found remote channel[" + String(ch_n)   + "] =>" +                  \
             "\n    channel_idx    => "  + String(ch_idx)          +                  \
             "\n    channel_name   => "  + String(ch_name)         +                  \
             "\n    channel_volume => "  + String(ch_vol)          +                  \
             "\n    channel_pan    => "  + String(ch_pan)          +                  \
             "\n    is_rcv         => "  + String(ch_rcv)          +                  \
             "\n    channel_mute   => "  + String(ch_mute)         +                  \
             "\n    is_solo        => "  + String(ch_solo)         +                  \
             "\n    sink_n         => "  + String(ch_sink)         +                  \
             "\n    is_pannable    => "  + String(ch_pannable) ;                      \
    }                                                                                 \
    Trace::TraceState(dbg) ;

#if TRACE_REMOTE_CHANNELS_VB
#  define                                                                    \
  bool has_bot = NETWORK::KNOWN_BOTS.getChildWithName(host).isValid() ;      \
  bool hide_bots = has_bot && bool(Config->shouldHideBots.getValue()) ;      \
  Trace::TraceServer("user info changed - " +                                \
                     String(Client->GetNumUsers()) + " users") ;             \
  int u_idx = -1 ; String u_name ; float u_vol ; float u_pan ; bool u_mute ; \
  while ((u_name = GetRemoteUserName(++u_idx)).isNotEmpty())                 \
  {                                                                          \
    Client->GetUserState(u_idx , &u_vol , &u_pan , &u_mute) ;                \
    Identifier u_id = Config->encodeUserId(String(u_name) , u_idx) ;         \
    DEBUG_TRACE_REMOTE_CHANNELS                                              \
  }
#else // TRACE_REMOTE_CHANNELS_VB
#  define DEBUG_TRACE_REMOTE_CHANNELS_VB ;
#endif // TRACE_REMOTE_CHANNELS_VB

#define DEBUG_TRACE_CONFIGURE_REMOTE_CHANNEL                                             \
  String user_name   = String(user_store.getType()) ;                                    \
  bool   is_mono     = stereo_status == CONFIG::MONO ;                                   \
  String dbg         = "configuring remote " + String(channel_store.getType()) + " '" +  \
                       GetStoredChannelName(channel_store) + "' for user["            +  \
                       String(user_idx) + "] '" + user_name + "'"                     ;  \
  String pan_str     = " (" + String(ClientPan(pan , stereo_status)) + " faux-stereo)" ; \
  String pan_msg     = String(pan) + ((is_mono) ? "" : pan_str) ;                        \
  String pannable    = String(is_pannable)                                      +        \
                       ((stereo_status == CONFIG::MONO    ) ? " (MONO)"     :            \
                        (stereo_status == CONFIG::STEREO_L) ? " (STEREO_L)" :            \
                        (stereo_status == CONFIG::STEREO_R) ? " (STEREO_R)" : "") ;      \
  String pseudo_ctrl = (should_set_is_rcv ) ? "RCV"  :                                   \
                       (should_set_is_solo) ? "SOLO" : "" ;                              \
  bool is_master = (channel_idx == CONFIG::MASTER_CHANNEL_IDX) ;                         \
  if (!is_master)                                                                        \
  {                                                                                      \
    if (stereo_status == CONFIG::STEREO_L) dbg += " and its stereo pair" ;               \
    ValueTree store     = Config->getUserMasterChannel(user_store) ;                     \
    bool master_rcv_or  = !bool(store[CONFIG::IS_XMIT_RCV_ID]) ;                         \
    bool master_solo_or =  bool(store[CONFIG::IS_SOLO_ID    ]) ;                         \
    is_rcv              = is_rcv  && !master_rcv_or ;                                    \
    is_solo             = is_solo || master_solo_or ;                                    \
    if (master_rcv_or)  dbg += " (master rcv override)" ;                                \
    if (master_solo_or) dbg += " (master solo override)" ;                               \
  }                                                                                      \
  if      (a_key == CONFIG::STEREO_ID && stereo_status == CONFIG::STEREO_R) ;            \
  else if (!(~user_idx))    Trace::TraceError("user index out of range "    + dbg) ;     \
  else if (!(~channel_idx)) Trace::TraceError("channel index out of range " + dbg) ;     \
  else if (TRACE_REMOTE_CHANNELS_VB) Trace::TraceClient(dbg                    +         \
      ((should_set_volume  ) ? "\n  volume      => " + String(volume)    : "") +         \
      ((should_set_pan     ) ? "\n  pan         => " + pan_msg           : "") +         \
      ((should_set_is_rcv  ) ? "\n  is_rcv      => " + String(is_rcv)    : "") +         \
      ((should_set_is_muted) ? "\n  is_muted    => " + String(is_muted)  : "") +         \
      ((should_set_is_solo ) ? "\n  is_solo     => " + String(is_solo)   : "") +         \
      ((should_init_all    ) ? "\n  sink_n      => " + String(sink_n)    : "") +         \
      ((should_init_all    ) ? "\n  is_pannable => " + pannable          : "") ) ;       \
  if (is_master && !should_set_volume && !should_set_pan && !should_set_is_muted &&      \
     (should_set_is_rcv || should_set_is_solo))                                          \
    Trace::TraceClient("applying user master " + pseudo_ctrl                +            \
                       " pseudo control over all " + user_name + " channels") ;


/* blacklist */

#define DEBUG_TRACE_BLACKLIST                                                         \
  ValueTree             subs  = Config->blacklist.createCopy() ;                      \
  std::set<std::string> users = Client->config_autosubscribe_userlist ;               \
  for (int user_n = 0 ; user_n < subs.getNumChildren() ; ++user_n)                    \
  {                                                                                   \
    String user_name = String(subs.getChild(user_n).getType()) ;                      \
    if (!users.count(user_name.toStdString()))                                        \
      Trace::TraceClient("ignoring remote user '" + user_name + "'") ;                \
  }                                                                                   \
  for (std::set<std::string>::iterator it = users.begin() ; it != users.end() ; ++it) \
  {                                                                                   \
    String user_name = String(*it) ;                                                  \
    if (subs.getChildWithName(Identifier(user_name)).isValid())                       \
      Trace::TraceClient("subscribing to remote user '" + user_name + "'") ;          \
  }                                                                                   \
  if (TRACE_DUMP_BLACKLIST)                                                           \
  {                                                                                   \
    String dbg = "ignore_list =>" ; int n_users = subs.getNumChildren() ;             \
    for (int user_n = 0 ; user_n < n_users ; ++user_n)                                \
      dbg += "\n  " + String(subs.getChild(user_n).getType()) ;                       \
    Trace::TraceClient(dbg + ((!n_users)? " (none)" : "")) ;                          \
  }


/* chat */

#define DEBUG_TRACE_CHAT_IN                                                        \
  if (chat_user.compare(str(Config->server[CONFIG::LOGIN_ID])))                    \
    Trace::TraceEvent("incoming chat: " + String(parms[CLIENT::CHATMSG_TYPE_IDX])) ;

#define DEBUG_TRACE_CHAT_OUT                                                    \
  if ((chat_text = chat_text.trim()).isNotEmpty())                              \
    Trace::TraceEvent("outgoing chat: " + ((chat_text[0] == '/')?               \
                      chat_text.upToFirstOccurrenceOf(" " , false , false) :    \
                      CLIENT::CHATMSG_TYPE_MSG)) ;

/* rooms */

#define DEBUG_UPDATE_ROOMS_RESP ;// Trace::TraceNetworkVb("LinJam::UpdateRooms() resp=" + response) ;
// e.g. response:
//   ninbot.com:2049,nick1,nick2,nick3,
//   ninjamer.com:2049,nick1,
//   user,THIS_NICK,999,0,false

#define DEBUG_UPDATE_ROOMS_USERDATA ;//Trace::TraceCofigVb("LinJam::UpdateRooms() Status=" + String(int(Status.getValue())) + " is_ready=" + String(Status == APP::NJC_STATUS_OK) + " n_rooms=" + String(rooms.size()) + " userdata=" + userdata) ;

#define DEBUG_UPDATE_ROOMS_ROOMDATA ;//Trace::TraceCofigVb("LinJam::UpdateRooms() roomdata=" + rooms[room_n]) ;

#else // DEBUG

// state
#define DEBUG_TRACE_INIT                      ;
#define DEBUG_TRACE_SESSIONDIR                ;
#define DEBUG_TRACE_STATUS_CHANGED            ;
#define DEBUG_TRACE_CONNECT                   ;
#define DEBUG_TRACE_LICENSE                   ;
#define DEBUG_TRACE_SHUTDOWN                  ;
// audio
#define DEBUG_TRACE_AUDIO_INIT_WIN            ;
#define DEBUG_TRACE_AUDIO_INIT_MAC            ;
#define DEBUG_TRACE_AUDIO_INIT_JACK           ;
#define DEBUG_TRACE_AUDIO_INIT_ALSA           ;
#define DEBUG_TRACE_AUDIO_INIT_JACK_FAIL      ;
#define DEBUG_TRACE_AUDIO_INIT_NIX            ;
#define DEBUG_TRACE_AUDIO_INIT                ;
// channels
#define DEBUG_TRACE_INITIAL_CHANNELS          ;
#define DEBUG_TRACE_ADD_LOCAL_CHANNEL         ;
#define DEBUG_TRACE_INSTANTIATE_LOCAL_CHANNEL ;
#define DEBUG_TRACE_CONFIGURE_LOCAL_CHANNEL   ;
#define DEBUG_TRACE_REMOVE_LOCAL_CHANNEL      ;
#define DEBUG_TRACE_DUMP_FREE_INPUTS_VB       ;
#define DEBUG_TRACE_REMOTE_CHANNELS           ;
#define DEBUG_TRACE_REMOTE_CHANNELS_VB        ;
#define DEBUG_TRACE_CONFIGURE_REMOTE_CHANNEL  ;
// blacklist
#define DEBUG_TRACE_BLACKLIST                 ;
// chat
#define DEBUG_TRACE_CHAT_IN                   ;
#define DEBUG_TRACE_CHAT_OUT                  ;
// rooms
#define DEBUG_UPDATE_ROOMS_RESP               ;
#define DEBUG_UPDATE_ROOMS_USERDATA           ;
#define DEBUG_UPDATE_ROOMS_ROOMDATA           ;

#endif // DEBUG
