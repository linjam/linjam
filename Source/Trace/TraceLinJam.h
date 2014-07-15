#include "Trace.h"


/* state */

#define DEBUG_TRACE_LINJAM_INIT Trace::TraceEvent("initializing") ;

#define DEBUG_TRACE_CONNECT                                                  \
  Trace::TraceState((!IsAgreed())? "connecting to " + host :                 \
                                    "joining "       + host + " as " + login) ;

#define DEBUG_TRACE_LICENSE                                          \
  Trace::TraceState((IsAgreed())? "agreeing to license" :            \
                                  "prompting for license agreement") ;

#ifdef CLEAN_SESSION
#  define DEBUG_TRACE_CLEAN_SESSION                                            \
  File thisfile     = File::getSpecialLocation(File::currentExecutableFile) ;  \
  File thisdir      = thisfile.getParentDirectory() ;                          \
  String sessiondir = SessionDir.getFullPathName() ;                           \
  if (!SessionDir.isDirectory() || !SessionDir.isAChildOf(thisdir))            \
      Trace::TraceError("session directory '" + sessiondir + "' is invalid") ; \
  else Trace::TraceState("cleaning session directory '" + sessiondir + "'") ;
#else // CLEAN_SESSION
#  define DEBUG_TRACE_CLEAN_SESSION                                               \
  String sessiondir = SessionDir.getFullPathName() ;                              \
  Trace::TraceState("cleaning session directory '" + sessiondir + "' (disabled)") ;
#endif // CLEAN_SESSION

/* audio */

#define DEBUG_TRACE_AUDIO_INIT_WIN                                        \
  String type = "unknown" ; /* this can not be so */                      \
  if      (if_n == audioStreamer::WINDOWS_AUDIO_ASIO)  type = "ASIO" ;    \
  else if (if_n == audioStreamer::WINDOWS_AUDIO_KS)    type = "KS" ;      \
  else if (if_n == audioStreamer::WINDOWS_AUDIO_DS)    type = "DS" ;      \
  else if (if_n == audioStreamer::WINDOWS_AUDIO_WAVE)  type = "WAVE" ;    \
  if (Audio) Trace::TraceConfig("using " + type + " audiostreamerobject") ;

#define DEBUG_TRACE_AUDIO_INIT_MAC                                     \
  if (Audio) Trace::TraceConfig("using CoreAudio audiostreamerobject") ;

#define DEBUG_TRACE_AUDIO_INIT_JACK                                                \
  if (Audio) Trace::TraceConfig("using JACK audiostreamer") ;                      \
  else       Trace::TraceState("could not connect to JACK - falling back to ALSA") ;

#define DEBUG_TRACE_AUDIO_INIT_ALSA                         \
  if (Audio) Trace::TraceConfig("using ALSA audiostreamer") ;

#define DEBUG_TRACE_AUDIO_INIT                                   \
  if (!Audio) Trace::TraceError("error opening audio device") ;  \
  else Trace::TraceState("opened audio device at "             + \
                         String(Audio->m_srate)  + "Hz "       + \
                         String(Audio->m_bps)    + "bps "      + \
                         String(Audio->m_innch)  + "in -> "    + \
                         String(Audio->m_outnch) + "out "      ) ;


/* network */

#define DEBUG_TRACE_CONNECT_STATUS                                             \
  String host_name = Client->GetHostName() ;                                   \
  switch (client_status)                                                       \
  {                                                                            \
    case -3: Trace::TraceNetwork("NJC_STATUS_DISCONNECTED") ;          break ; \
    case -2: Trace::TraceNetwork((IsAgreed())?                                 \
                                 "NJC_STATUS_INVALIDAUTH" :                    \
                                 "LICENSE_PENDING") ;                  break ; \
    case -1: Trace::TraceNetwork("NJC_STATUS_CANTCONNECT") ;           break ; \
    case  0: Trace::TraceNetwork("NJC_STATUS_OK") ;                            \
             Trace::TraceServer("connected to host: " + host_name) ;   break ; \
    case  1: Trace::TraceNetwork("NJC_STATUS_PRECONNECT") ;            break ; \
    default: Trace::TraceNetwork("Status: " + String(client_status)) ; break ; \
  }                                                                            \
  if (Client->GetErrorStr()[0])                                                \
    Trace::TraceServer("Error: " + String(Client->GetErrorStr())) ;


/* channels */

#define DEBUG_TRACE_ADD_LOCAL_CHANNEL                                               \
  String channel_name =      channel_store[CONFIG::CHANNELNAME_ID].toString() ;     \
  int    source       = int( channel_store[CONFIG::SOURCE_N_ID]) ;                  \
  bool   stereo       = bool(channel_store[CONFIG::IS_STEREO_ID]) ;                 \
  String type         = (!stereo)? "mono" : "stereo" ;                              \
  bool   valid_source = source >= 0 ;                                               \
  int    n_vacant     = GetNumVacantChannels() ;                                    \
  bool   no_chs       = (!stereo && n_vacant < 1 || stereo && n_vacant < 2) ;       \
  bool   slot_vacant  = GetLocalChannelClientName(source).isEmpty() ;               \
  String dbg          = "adding new local " + type                              +   \
                        " input[" + String(source) + "] '" + channel_name + "'" ;   \
  if      (!valid_source)                                                           \
       Trace::TraceError("non-existent source " + dbg) ;                            \
  else if (no_chs && valid_source || !no_chs && !valid_source)                      \
       Trace::TraceError("corrupted free-set state " + dbg) ;                       \
  else if (no_chs)                                                                  \
       Trace::TraceError("no free channels " + dbg) ;                               \
  else if (!slot_vacant)                                                            \
       Trace::TraceError("slot occupied " + dbg) ;                                  \
  else Trace::TraceEvent(dbg) ;

#if TRACE_DUMP_FREE_INPUTS
#  define DEBUG_TRACE_DUMP_FREE_INPUTS_VB                                           \
  SortedSet<int> monos   = FreeInputChannels ;     int n_monos   = monos.size() ;   \
  SortedSet<int> stereos = FreeInputChannelPairs ; int n_stereos = stereos.size() ; \
  String dump = String(n_monos)   + " FreeInputChannels     = [" ;                  \
  for (int i = 0 ; i < n_monos ; ++i)   dump += String(monos[i])   + " " ;          \
  Trace::TraceVerbose(dump.trim() + "]") ;                                          \
  dump        = String(n_stereos) + " FreeInputChannelPairs = [" ;                  \
  for (int i = 0 ; i < n_stereos ; ++i) dump += String(stereos[i]) + " " ;          \
  Trace::TraceVerbose(dump.trim() + "]") ;
#else // TRACE_DUMP_FREE_INPUTS
#  define DEBUG_TRACE_DUMP_FREE_INPUTS ;
#endif // TRACE_DUMP_FREE_INPUTS

#define DEBUG_TRACE_CREATE_LOCAL_CHANNEL                                             \
  String ch_id  = String(Config->makeChannelId(source_n)) ;                          \
  String max    = String(Client->GetMaxLocalChannels()) ;                            \
  dbg           = "creating new local " + type + " " + ch_id + " '" + channel_name ; \
  if (!(~source_n))                                                                  \
       Trace::TraceError(max + " input channels max " + dbg + "'") ;                 \
  else if (Config->getChannelById(CONFIG::LOCALS_ID , ch_id).isValid())              \
       Trace::TraceConfig("channel storage already exists " + dbg + "'") ;           \
  else Trace::TraceConfig(dbg + "'") ;

#define DEBUG_TRACE_INSTANTIATE_LOCAL_CHANNEL                                     \
  dbg = "instantiating local " + type + " " + ch_id + " '" + channel_name + "'" ; \
  if (!channel_store.isValid()) Trace::TraceError("invalid config " + dbg) ;      \
  else                          Trace::TraceState(dbg) ;

#define DEBUG_TRACE_CONFIGURE_LOCAL_CHANNEL                                        \
  int    ch_idx = int(channel_store[CONFIG::CHANNELIDX_ID]) ;                      \
  bool   is_new = !IsConfiguredChannel(ch_idx) ;                                   \
  String type   = (!is_stereo)? "mono" : "stereo" ;                                \
  String dbg    = String((is_new)? "new" : "existing") + " local " + type  + " " + \
                  String(channel_store.getType()) + " '" + channel_name + "'" ;    \
  if (is_new && !(~GetVacantLocalChannelIdx()))                                    \
  {                                                                                \
    Trace::TraceError("no available channels configuring " + dbg) ;                \
    if (TRACE_CONFIGURE_LOCAL_CHANNEL_VB)                                          \
      DBG(Trace::DumpStoredChannels() + Trace::DumpClientChannels()) ;             \
  }                                                                                \
  else if (a_key == CONFIG::SOURCE_N_ID)                                           \
    Trace::TraceClient("re-instantiating " + dbg) ;                                \
  else                                                                             \
  {                                                                                \
    if (is_stereo && !(source_n % 2)) dbg += " and its stereo pair" ;              \
    if (TRACE_CONFIGURE_LOCAL_CHANNEL_VB) dbg +=                                   \
      ((should_set_name)?      "\n  name      => " + channel_name      : "") +     \
      ((should_set_volume)?    "\n  volume    => " + String(volume)    : "") +     \
      ((should_set_pan)?       "\n  pan       => " + String(pan)       : "") +     \
      ((should_set_is_xmit)?   "\n  is_xmit   => " + String(is_xmit)   : "") +     \
      ((should_set_is_muted)?  "\n  is_muted  => " + String(is_muted)  : "") +     \
      ((should_set_is_solo)?   "\n  is_solo   => " + String(is_solo)   : "") +     \
      ((should_set_source_n)?  "\n  source_n  => " + String(source_n)  : "") +     \
      ((should_set_bit_depth)? "\n  bit_depth => " + String(bit_depth) : "") +     \
      ((should_set_is_stereo)? "\n  is_stereo => " + String(is_stereo) : "") ;     \
    Trace::TraceClient("configuring " + dbg) ;                                     \
  }

#define DEBUG_TRACE_REMOVE_LOCAL_CHANNEL                                      \
  Trace::TraceEvent("destroying channel["                                   + \
                    channel_store[CONFIG::CHANNELIDX_ID].toString() + "] '" + \
                    String(channel_store.getType()) + "'"                   ) ;

#define DEBUG_TRACE_REMOTE_CHANNELS                                           \
    String hidden  = (hide_bots && NETWORK::KNOWN_BOTS.contains(u_id))?       \
                     " (bot hidden)" : "" ;                                   \
    String dbg = "remote user[" + String(u_idx) + "] =>" + hidden +           \
        "\n  user_name   => "   + String(u_name)                  +           \
        "\n  user_volume => "   + String(u_vol)                   +           \
        "\n  user_pan    => "   + String(u_pan)                   +           \
        "\n  user_mute   => "   + String(u_mute) ;                            \
    int ch_n = -1 ; int ch_idx ;                                              \
    while (~(ch_idx = LinJam::Client->EnumUserChannels(u_idx , ++ch_n)))      \
    {                                                                         \
      bool ch_rcv ;  float ch_vol ;  float ch_pan ; bool ch_mute ;            \
      bool ch_solo ; int   ch_chan ; bool  ch_stereo ;                        \
      String ch_name = LinJam::GetRemoteChannelName(u_idx , ch_idx) ;         \
      LinJam::Client->GetUserChannelState(u_idx    , ch_idx   , &ch_rcv   ,   \
                                          &ch_vol  , &ch_pan  , &ch_mute  ,   \
                                          &ch_solo , &ch_chan , &ch_stereo) ; \
      dbg += "\n  found remote channel[" + String(ch_n)   + "] =>" +          \
             "\n    channel_idx    => "  + String(ch_idx)          +          \
             "\n    channel_name   => "  + String(ch_name)         +          \
             "\n    is_rcv         => "  + String(ch_rcv)          +          \
             "\n    channel_volume => "  + String(ch_vol)          +          \
             "\n    channel_pan    => "  + String(ch_pan)          +          \
             "\n    channel_mute   => "  + String(ch_mute)         +          \
             "\n    is_solo        => "  + String(ch_solo)         +          \
             "\n    output_channel => "  + String(ch_chan)         +          \
             "\n    is_stereo      => "  + String(ch_stereo) ;                \
    }                                                                         \
    Trace::TraceState(dbg) ;

#if TRACE_REMOTES
#  define DEBUG_TRACE_REMOTE_CHANNELS_VB                                          \
  bool has_bot   = NETWORK::KNOWN_HOSTS.contains(String(Client->GetHostName())) ; \
  bool hide_bots = has_bot && bool(Config->shouldHideBots.getValue()) ;           \
  Trace::TraceServer("user info changed - " +                                     \
                     String(Client->GetNumUsers()) + " users") ;                  \
  int u_idx = -1 ; String u_name ; float u_vol ; float u_pan ; bool u_mute ;      \
  while ((u_name = GetRemoteUserName(++u_idx)).isNotEmpty())                      \
  {                                                                               \
    Client->GetUserState(u_idx , &u_vol , &u_pan , &u_mute) ;                     \
    Identifier u_id = Config->encodeUserId(String(u_name) , u_idx) ;              \
    DEBUG_TRACE_REMOTE_CHANNELS                                                   \
  }
#else // TRACE_REMOTES
#  define DEBUG_TRACE_REMOTE_CHANNELS_VB ;
#endif // TRACE_REMOTES

#define DEBUG_TRACE_CONFIGURE_REMOTE                                                   \
  String dbg     = "configuring remote " + String(channel_store.getType()) +           \
                   " '" + channel_name + "' for user[" + String(user_idx)  +           \
                   "] '" + String(user_id) + "'" ;                                     \
  bool is_master = (channel_idx == CLIENT::MASTER_IDX) ;                               \
  if (!is_master)                                                                      \
  {                                                                                    \
    ValueTree store     = Config->getChannelByIdx(user_store , CLIENT::MASTER_IDX) ;   \
    bool master_rcv_or  = !bool(store[CONFIG::IS_XMIT_RCV_ID]) ;                           \
    bool master_solo_or = bool(store[CONFIG::IS_SOLO_ID]) ;                            \
    is_rcv              = is_rcv  && !master_rcv_or ;                                  \
    is_solo             = is_solo || master_solo_or ;                                  \
    if (master_rcv_or)  dbg += " (master rcv override)" ;                              \
    if (master_solo_or) dbg += " (master solo override)" ;                             \
  }                                                                                    \
  if      (!(~user_idx))    Trace::TraceError("user index out of range "    + dbg) ;   \
  else if (!(~channel_idx)) Trace::TraceError("channel index out of range " + dbg) ;   \
  else if (DEBUG_TRACE_VB)  Trace::TraceClient(dbg                           +         \
      ((should_set_volume)?    "\n  volume    => " + String(volume)    : "") +         \
      ((should_set_pan)?       "\n  pan       => " + String(pan)       : "") +         \
      ((should_set_is_rcv)?    "\n  is_rcv    => " + String(is_rcv)    : "") +         \
      ((should_set_is_muted)?  "\n  is_muted  => " + String(is_muted)  : "") +         \
      ((should_set_is_solo)?   "\n  is_solo   => " + String(is_solo)   : "") +         \
      ((should_set_sink_n)?    "\n  sink_n    => " + String(sink_n)    : "") +         \
      ((should_set_is_stereo)? "\n  is_stereo => " + String(is_stereo) : "") ) ;       \
  if (is_master && !should_set_volume && !should_set_pan && !should_set_is_muted &&    \
     (should_set_is_rcv || should_set_is_solo))                                        \
      Trace::TraceClient("applying user master pseudo control over all user channels") ;
/*
  String stored_u_idx       = String(user_idx) ;                                       \
  String stored_ch_idx      = String(channel_idx) ;                                    \
  String channel_id         = String(channel_store.getType()) ;                        \
  int    client_user_idx    = GetRemoteUserIdx(user_id) ;                              \
  int    client_channel_idx = GetRemoteChannelIdx(user_idx , channel_name) ;           \
  String u_idxs             = stored_u_idx  + "/" + String(client_user_idx)    + " " ; \
  String ch_idxs            = stored_ch_idx + "/" + String(client_channel_idx) + " " ; \
  bool   user_mismatch      = user_idx    != client_user_idx ;                         \
  bool   ch_mismatch        = channel_idx != client_channel_idx &&                     \
                              channel_idx != CLIENT::MASTER_IDX ;                      \
  else if (user_mismatch)                                                              \
    Trace::TraceError("user index mismatch "        + u_idxs  + dbg) ;                 \
  else if (!(~channel_idx))                                                            \
    Trace::TraceError("channel index out of range "           + dbg) ;                 \
  else if (ch_mismatch)                                                                \
    Trace::TraceError("channel index mismatch "     + ch_idxs + dbg) ;                 \
*/


/* chat */

#define DEBUG_TRACE_CHAT_IN                                                        \
  if (chat_user.compare(Config->login.toString()))                                 \
    Trace::TraceEvent("incoming chat: " + String(parms[CLIENT::CHATMSG_TYPE_IDX])) ;

#define DEBUG_TRACE_CHAT_OUT                                                    \
  if ((chat_text = chat_text.trim()).isNotEmpty())                              \
    Trace::TraceEvent("outgoing chat: " + ((chat_text[0] == '/')?               \
                      chat_text.upToFirstOccurrenceOf(" " , false , false) :    \
                      CLIENT::CHATMSG_TYPE_MSG)) ;

