
#ifndef _TRACE_H_
#define _TRACE_H_


// standard features
#define UPDATE_GUI
#define UPDATE_REMOTES
#define BUGGY_CHAT_COMMANDS                    // (issue #19)
#define BUGGY_ADD_DUPLICATE_LOCAL_CHANNELS     // (issue #n/a)
#define BUGGY_DUPLICATE_CHANNEL_NAMES
//#define DEBUG_DUPLICATE_CHANNEL_NAMES_VU_BUG
#define BUGGY_EMPTY_OR_DUPLICATE_CHANNEL_NAMES
#define KLUDGE_SET_INITIAL_REMOTE_GAIN_TO_ZERO // NJClient initializes remote channels gain to 1.0

#if DEBUG
// debug features
//#define DEBUG_EXIT_IMMEDIAYELY
#define DEBUG_LOCALHOST_LOGIN_BUTTON
//#define DEBUG_AUTOLOGIN_NYI
#endif // DEBUG

// tracing
#define DEBUG_TRACE              DEBUG && 1
#define DEBUG_TRACE_EVENTS       DEBUG && 1
#define DEBUG_TRACE_STATE        DEBUG && 1
#define DEBUG_TRACE_IN           DEBUG && 1
#define DEBUG_TRACE_OUT          DEBUG && 1
#define DEBUG_TRACE_VB           DEBUG && 0
#define DEBUG_SANITIZE_CONFIG_VB DEBUG && 0
#define DEBUG_SHARED_CONFIG      DEBUG && 0
#define DEBUG_STORE_CONFIG_VB    DEBUG && 0
#define DEBUG_ADDED_CHANNEL_VB   DEBUG && 0


#if DEBUG_TRACE

// state
#  define DEBUG_TRACE_LINJAM_INIT Trace::TraceEvent("initializing") ;
#  define DEBUG_TRACE_LOGIN_LOAD                                                     \
    Trace::TraceState("Lobby - storage " + String((server.isValid())? "" : "not ") + \
                      "found for currentHost => '" + host + "'") ;
#  define DEBUG_TRACE_LOGIN_BTNS                                                     \
    Button* btn = buttonThatWasClicked ;                                             \
    if      (btn == loginButton) Trace::TraceEvent("loginButton clicked") ;          \
    else if (btn == anonButton)  Trace::TraceEvent("anonButton clicked") ;           \
    else if (loginButtons.contains((TextButton*)btn))                                \
      Trace::TraceEvent("quick-login button clicked " + btn->getButtonText().trim()) ;
#  define DEBUG_TRACE_CONNECT                                                  \
    Trace::TraceState((!IsAgreed())? "connecting to " + host :                 \
                                     "joining "       + host + " as " + login) ;

#  define DEBUG_TRACE_LICENSE_CLICKED                                                          \
    Button* btn = buttonThatWasClicked ;                                      \
    if      (btn == cancelButton) Trace::TraceEvent("cancelButton clicked") ; \
    else if (btn == agreeButton)  Trace::TraceEvent("agreeButton clicked") ;  \
    else if (btn == alwaysButton) Trace::TraceEvent("alwaysButton clicked") ;
#  define DEBUG_TRACE_LICENSE                                         \
    Trace::TraceState((is_agreed)? "agreeing to license" :            \
                                   "prompting for license agreement") ;
#  define DEBUG_TRACE_CLEAN_SESSION                                              \
    File thisfile     = File::getSpecialLocation(File::currentExecutableFile) ;  \
    File thisdir      = thisfile.getParentDirectory() ;                          \
    String sessiondir = SessionDir.getFullPathName() ;                           \
    if (!SessionDir.isDirectory() || !SessionDir.isAChildOf(thisdir))            \
        Trace::TraceError("session directory '" + sessiondir + "' is invalid") ; \
    else Trace::TraceState("cleaning session directory '" + sessiondir + "'") ;
#  define DEBUG_TRACE_SHUTDOWN Trace::TraceState("clean shutdown - bye") ;

// audio
#  define DEBUG_TRACE_AUDIO_INIT_WIN                                        \
    String type = "unknown" ; /* this can not be so */                      \
    if      (if_n == audioStreamer::WINDOWS_AUDIO_ASIO)  type = "ASIO" ;    \
    else if (if_n == audioStreamer::WINDOWS_AUDIO_KS)    type = "KS" ;      \
    else if (if_n == audioStreamer::WINDOWS_AUDIO_DS)    type = "DS" ;      \
    else if (if_n == audioStreamer::WINDOWS_AUDIO_WAVE)  type = "WAVE" ;    \
    if (Audio) Trace::TraceConfig("using " + type + " audiostreamerobject") ;
#  define DEBUG_TRACE_AUDIO_INIT_MAC                                     \
    if (Audio) Trace::TraceConfig("using CoreAudio audiostreamerobject") ;
#  define DEBUG_TRACE_AUDIO_INIT_JACK                                                \
    if (Audio) Trace::TraceConfig("using JACK audiostreamer") ;                      \
    else       Trace::TraceState("could not connect to JACK - falling back to ALSA") ;
#  define DEBUG_TRACE_AUDIO_INIT_ALSA                         \
    if (Audio) Trace::TraceConfig("using ALSA audiostreamer") ;
#  define DEBUG_TRACE_AUDIO_INIT                                   \
    if (!Audio) Trace::TraceError("error opening audio device") ;  \
    else Trace::TraceState("opened audio device at "             + \
                           String(Audio->m_srate)  + "Hz "       + \
                           String(Audio->m_bps)    + "bps "      + \
                           String(Audio->m_innch)  + "in -> "    + \
                           String(Audio->m_outnch) + "out "      ) ;

// storage
#  define DEBUG_TRACE_LOAD_CONFIG                                                       \
    Identifier root_node_id = CONFIG::PERSISTENCE_ID ;                                  \
    if (default_config_xml == nullptr || !default_config_xml->hasTagName(root_node_id)) \
        Trace::TraceConfig("default config invalid - bailing") ;                        \
    else Trace::TraceConfig("default config loaded") ;                                  \
    if (stored_config_xml == nullptr)                                                   \
        Trace::TraceConfig("stored config not found - falling back on defaults") ;      \
    else if (!stored_config_xml->hasTagName(CONFIG::PERSISTENCE_ID))                    \
        Trace::TraceConfig("stored config is invalid - falling back on defaults") ;     \
    else Trace::TraceConfig("stored config found") ;
#  if DEBUG_SANITIZE_CONFIG_VB
#    define DEBUG_TRACE_SANITIZE_CONFIG                                                   \
    if (!is_stored_config_bogus)                                                          \
      Trace::TraceConfig("stored config parsed successfully =>" +                         \
                         Trace::SanitizeConfig(ValueTree::fromXml(*default_config_xml) ,  \
                                               ValueTree::fromXml(*stored_config_xml)  ,  \
                                               "  "                                    )) ;
#  else // DEBUG_SANITIZE_CONFIG_VB
#    define DEBUG_TRACE_SANITIZE_CONFIG ;
#  endif // DEBUG_SANITIZE_CONFIG_VB
#  if DEBUG_SHARED_CONFIG
#    define DEBUG_TRACE_CONFIG_TREE                                              \
    bool valid = tree_node.isValid() ; String n = String(tree_node_id) ;         \
    Trace::TraceConfig("node '" + n + ((valid)? "' (" : "' (in") + "valid) - ")) ;
#    define DEBUG_TRACE_CONFIG_VALUE                                                \
    bool valid = value_node.isValid() ; String name = String(child_node_id) ;       \
    String k = String(key) ;                                                        \
    Trace::TraceConfig("node '" + name + ((valid)? "' (" : "' (in") + "valid) - " + \
        ((valid && value_node.hasProperty(key))?                                    \
            "has shared value on key '"        + k + "'" :                          \
            "has dummy value on missing key '" + k + "'"))) ;
#  else // DEBUG_SHARED_CONFIG
#    define DEBUG_TRACE_CONFIG_TREE  ;
#    define DEBUG_TRACE_CONFIG_VALUE ;
#  endif // DEBUG_SHARED_CONFIG
#  define DEBUG_TRACE_SANITY_CHECK                                                      \
    /* subscribed trees */                                                              \
    if (!root_is_valid)                                                                 \
      Trace::TraceInvalidNode(CONFIG::PERSISTENCE_KEY) ;                                \
    if (!auto_subscribe_users_is_valid)                                                 \
      Trace::TraceInvalidNode(CONFIG::SUBSCRIPTIONS_KEY) ;                              \
    if (!master_channels_is_valid)                                                      \
      Trace::TraceInvalidNode(CONFIG::MASTERS_KEY) ;                                    \
    if (!local_channels_is_valid)                                                       \
      Trace::TraceInvalidNode(CONFIG::LOCALS_KEY) ;                                     \
    if (!servers_is_valid)                                                              \
      Trace::TraceInvalidNode(CONFIG::SERVERS_KEY) ;                                    \
                                                                                        \
    /* implicitly subscribed values (via above trees) */                                \
    if (!master_channel_has_volume_property)                                            \
      Trace::TraceMissingProperty(CONFIG::MASTER_KEY        , CONFIG::VOLUME_KEY) ;     \
    if (!master_channel_has_pan_property)                                               \
      Trace::TraceMissingProperty(CONFIG::MASTER_KEY        , CONFIG::PAN_KEY) ;        \
    if (!master_channel_has_mute_property)                                              \
      Trace::TraceMissingProperty(CONFIG::MASTER_KEY        , CONFIG::IS_MUTED_KEY) ;   \
    if (!metro_channel_has_volume_property)                                             \
      Trace::TraceMissingProperty(CONFIG::METRO_KEY         , CONFIG::VOLUME_KEY) ;     \
    if (!metro_channel_has_pan_property)                                                \
      Trace::TraceMissingProperty(CONFIG::METRO_KEY         , CONFIG::PAN_KEY) ;        \
    if (!metro_channel_has_mute_property)                                               \
      Trace::TraceMissingProperty(CONFIG::METRO_KEY         , CONFIG::IS_MUTED_KEY) ;   \
    if (!metro_channel_has_source_property)                                             \
      Trace::TraceMissingProperty(CONFIG::METRO_KEY         , CONFIG::SOURCE_N_KEY) ;   \
    if (!metro_channel_has_stereo_property)                                             \
      Trace::TraceMissingProperty(CONFIG::METRO_KEY         , CONFIG::IS_STEREO_KEY) ;  \
    if (!local_channel_has_channelidx_property)                                         \
      Trace::TraceMissingProperty(CONFIG::INITIAL_LOCAL_KEY , CONFIG::CHANNELIDX_KEY) ; \
    if (!local_channel_has_volume_property)                                             \
      Trace::TraceMissingProperty(CONFIG::INITIAL_LOCAL_KEY , CONFIG::VOLUME_KEY) ;     \
    if (!local_channel_has_pan_property)                                                \
      Trace::TraceMissingProperty(CONFIG::INITIAL_LOCAL_KEY , CONFIG::PAN_KEY) ;        \
    if (!local_channel_has_xmit_property)                                               \
      Trace::TraceMissingProperty(CONFIG::INITIAL_LOCAL_KEY , CONFIG::IS_XMIT_KEY) ;    \
    if (!local_channel_has_mute_property)                                               \
      Trace::TraceMissingProperty(CONFIG::INITIAL_LOCAL_KEY , CONFIG::IS_MUTED_KEY) ;   \
    if (!local_channel_has_solo_property)                                               \
      Trace::TraceMissingProperty(CONFIG::INITIAL_LOCAL_KEY , CONFIG::IS_SOLO_KEY) ;    \
    if (!local_channel_has_source_property)                                             \
      Trace::TraceMissingProperty(CONFIG::INITIAL_LOCAL_KEY , CONFIG::SOURCE_N_KEY) ;   \
    if (!local_channel_has_stereo_property)                                             \
      Trace::TraceMissingProperty(CONFIG::INITIAL_LOCAL_KEY , CONFIG::IS_STEREO_KEY) ;  \
                                                                                        \
    /* explicitly subscribed values */                                                  \
    if (!should_save_audio_has_value)                                                   \
      Trace::TraceMissingValue(CONFIG::CLIENT_KEY , CONFIG::SAVE_AUDIO_KEY) ;           \
    if (!should_save_log_has_value)                                                     \
      Trace::TraceMissingValue(CONFIG::CLIENT_KEY , CONFIG::SAVE_LOG_KEY) ;             \
    if (!debug_level_has_value)                                                         \
      Trace::TraceMissingValue(CONFIG::CLIENT_KEY , CONFIG::DEBUGLEVEL_KEY) ;           \
    if (!should_auto_subscribe_has_value)                                               \
      Trace::TraceMissingValue(CONFIG::CLIENT_KEY , CONFIG::AUTOSUBSCRIBE_KEY) ;        \
    if (!audio_if_n_has_value)                                                          \
      Trace::TraceMissingValue(CONFIG::AUDIO_KEY  , CONFIG::AUDIO_IF_KEY) ;             \
    if (!n_inputs_has_value)                                                            \
      Trace::TraceMissingValue(CONFIG::AUDIO_KEY  , CONFIG::N_INPUTS_KEY) ;             \
    if (!n_outputs_has_value)                                                           \
      Trace::TraceMissingValue(CONFIG::AUDIO_KEY  , CONFIG::N_OUTPUTS_KEY) ;            \
    if (!bit_depth_has_value)                                                           \
      Trace::TraceMissingValue(CONFIG::AUDIO_KEY  , CONFIG::BITDEPTH_KEY) ;             \
    if (!sample_rate_has_value)                                                         \
      Trace::TraceMissingValue(CONFIG::AUDIO_KEY  , CONFIG::SAMPLERATE_KEY) ;           \
    if (!jack_name_has_value)                                                           \
      Trace::TraceMissingValue(CONFIG::AUDIO_KEY  , CONFIG::JACK_NAME_KEY) ;            \
    if (!current_host_has_value)                                                        \
      Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::HOST_KEY) ;                 \
    if (!current_login_has_value)                                                       \
      Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::LOGIN_KEY) ;                \
    if (!current_pass_has_value)                                                        \
      Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::PASS_KEY) ;                 \
    if (!current_is_anonymous_has_value)                                                \
      Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::ANON_KEY) ;                 \
    if (!current_is_agreed_has_value)                                                   \
      Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::AGREED_KEY) ;               \
    if (!should_hide_bots_has_value)                                                    \
      Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::BOTS_KEY) ;
#  if DEBUG_STORE_CONFIG_VB
#    define DEBUG_TRACE_STORE_CONFIG Trace::TraceConfig("storing config xml=\n" +      \
                                                        configValueTree.toXmlString()) ;
#  else // DEBUG_STORE_CONFIG_VB
#    define DEBUG_TRACE_STORE_CONFIG Trace::TraceConfig("storing config xml") ;
#  endif // DEBUG_STORE_CONFIG_VB
#  define DEBUG_TRACE_CONFIG_TREE_CHANGED                      \
    String node   = String(a_node.getType()) ;                 \
    String parent = String(a_node.getParent().getType()) ;     \
    String key    = String(a_key) ;                            \
    String val    = a_node[a_key].toString() ;                 \
    Trace::TraceEvent("value changed for " + parent + " => " + \
                      node + "[" + key + "] => " + val) ;
#  define DEBUG_TRACE_CONFIG_TREE_ADDED                                        \
    Trace::TraceConfig("node '" + String(a_child_node.getType()) +             \
                       "' added to '" + String(a_parent_node.getType()) + "'") ;
#  define DEBUG_TRACE_CONFIG_TREE_REMOVED                                          \
    Trace::TraceConfig("node '" + String(a_child_node.getType()) +                 \
                       "' removed from '" + String(a_parent_node.getType()) + "'") ;

// network
#  define DEBUG_TRACE_LOGIN_HOST_VB                                                     \
    String h  = this->hostText->getText().trim() ; String dbg ;                         \
    String hn = h.upToLastOccurrenceOf( StringRef(".") , false , true) ;                \
    String ht = h.fromLastOccurrenceOf( StringRef(".") , false , true)                  \
                 .upToFirstOccurrenceOf(StringRef(":") , false , true) ;                \
    String hp = h.fromFirstOccurrenceOf(StringRef(":") , false , true) ;                \
    bool valid = (NETWORK::KNOWN_HOSTS.contains(h)                                ||    \
                 (h                   .matchesWildcard(NETWORK::HOST_MASK , true) &&    \
                  hn                  .containsOnly(   NETWORK::URL_CHARS)        &&    \
                  ht                  .containsOnly(   NETWORK::LETTERS)          &&    \
                  hp                  .containsOnly(   NETWORK::DIGITS)           )) ;  \
    if (valid) Trace::TraceVerbose("validated host '"        + h + "'") ;               \
    else       Trace::TraceVerbose("error validating host '" + h + "'" +                \
      "\n  parsed host="      + h  +                                                    \
      "\n  parsed host_tld="  + ht +                                                    \
      "\n  parsed host_port=" + hp +                                                    \
      "\n  is_known_host="    + String(NETWORK::KNOWN_HOSTS.contains(h))              + \
      "\n  is_valid_host="    + String(h .matchesWildcard(NETWORK::HOST_MASK , true)) + \
      "\n  is_valid_url="     + String(hn.containsOnly(   NETWORK::URL_CHARS) &&        \
                                       hn.isNotEmpty())                               + \
      "\n  is_valid_tld="     + String(ht.containsOnly(   NETWORK::LETTERS)   &&        \
                                       ht.isNotEmpty())                               + \
      "\n  is_valid_port="    + String(hp.containsOnly(   NETWORK::DIGITS)    &&        \
                                       hp.isNotEmpty())                               ) ;
#  define DEBUG_TRACE_CONNECT_STATUS                                           \
    String host_name = Client->GetHostName() ;                                 \
    switch (client_status)                                                     \
    {                                                                          \
      case -3: Trace::TraceNetwork("NJC_STATUS_DISCONNECTED") ;        break ; \
      case -2: Trace::TraceNetwork((IsAgreed())?                               \
                   "NJC_STATUS_INVALIDAUTH" : "LICENSE_PENDING") ;     break ; \
      case -1: Trace::TraceNetwork("NJC_STATUS_CANTCONNECT") ;         break ; \
      case  0: Trace::TraceNetwork("NJC_STATUS_OK") ;                          \
               Trace::TraceServer("connected to host: " + host_name) ; break ; \
      case  1: Trace::TraceNetwork("NJC_STATUS_PRECONNECT") ;          break ; \
      default:                                                         break ; \
    }                                                                          \
    if (Client->GetErrorStr()[0])                                              \
      Trace::TraceServer("Error: " + String(Client->GetErrorStr())) ;

// channels
#  define DEBUG_TRACE_ADD_CHANNEL_GUI                                               \
    String name = String(channel_store.getType()) ;                                 \
    if (!channel_store.isValid())                                                   \
         Trace::TraceError("adding channel GUI for '" + getComponentID() +          \
                           "' - channel store is invalid") ;                        \
    else if (name.isEmpty())                                                        \
         Trace::TraceError("adding channel GUI for '" + getComponentID() +          \
                           "' - channel name is empty") ;                           \
    else if (findChildWithID(StringRef(name))) ; /* already exists */               \
    else if (!getComponentID().compare(GUI::MASTERS_GUI_ID))                        \
         Trace::TraceGui("adding master channel slice '" + name  + "'") ;           \
    else if (!getComponentID().compare(GUI::LOCALS_GUI_ID))                         \
         Trace::TraceGui("adding local channel slice '"  + name  + "'") ;           \
    else Trace::TraceGui("adding remote channel slice '" + name  + "' for '" +      \
                         String(channel_store.getParent().getType()) + "'") ;
#  define DEBUG_TRACE_ADD_LOCAL_CHANNEL_FAIL                                           \
    int    ch_idx       = GetVacantLocalChannelIdx() ;                                 \
    String ch_id        = String(Config->encodeChannelId(channel_name , ch_idx + 1)) ; \
    String max_channels = String(Client->GetMaxLocalChannels()) ;                      \
    if (!(~ch_idx))                                                                    \
      Trace::TraceError("cannot create new local channel '" + ch_id +                  \
                        "' - maximum input channels = " + max_channels) ;              \
    else if (Config->getChannelById(GUI::LOCALS_ID , ch_id).isValid())                 \
      Trace::TraceError("cannot create new local channel '" + ch_id +                  \
                        "' - channel already exists") ;
#  define DEBUG_TRACE_ADD_CHANNEL_STORE                                        \
    String dbgA = "created storage for new " ;                                 \
    String dbgB = " channel[" + String(channel_idx) +                          \
                  "] - '" + String(channel_id) + "' " ;                        \
    if (channels_id == GUI::LOCALS_ID)                                         \
         Trace::TraceConfig(dbgA + "local" + dbgB) ;                           \
    else Trace::TraceConfig(dbgA + "remote" + dbgB + "for '" +                 \
                            String(getUserById(channels_id).getType())  + "'") ;
#  define DEBUG_TRACE_CONFIGURE_LOCAL_CHANNEL                                     \
  int idx ; String channel_status = "unknwon" ;                                   \
  if      (~(idx = GetLocalChannelIdx(channel_id))) channel_status = "existing" ; \
  else if (~(idx = GetVacantLocalChannelIdx()))     channel_status = "new" ;      \
  String dbg ="configuring " + channel_status + " local channel[" +               \
              String(idx) + "] '" + String(channel_id) + "'" ;                    \
  if (!(~idx))             Trace::TraceError("index out of range " + dbg) ;       \
  else if (DEBUG_TRACE_VB) Trace::TraceConfig(dbg                               + \
      ((should_set_volume)?    "\n  volume    => " + String(volume)    : "")    + \
      ((should_set_pan)?       "\n  pan       => " + String(pan)       : "")    + \
      ((should_set_is_xmit)?   "\n  is_xmit   => " + String(is_xmit)   : "")    + \
      ((should_set_is_muted)?  "\n  is_muted  => " + String(is_muted)  : "")    + \
      ((should_set_is_solo)?   "\n  is_solo   => " + String(is_solo)   : "")    + \
      ((should_set_source_n)?  "\n  source_n  => " + String(source_n)  : "")    + \
      ((should_set_is_stereo)? "\n  is_stereo => " + String(is_stereo) : "")    ) ;
#  if DEBUG_ADDED_CHANNEL_VB
#    define DEBUG_TRACE_ADDED_CHANNEL Trace::TraceEvent(String("channel added =>") + \
    "\n  mixergroup      => " + String(this->configStore.getParent().getType())    + \
    "\n  name            => " + name                                               + \
    "\n  volume          => " + String(volume)                                     + \
    "\n  pan             => " + String(pan)                                        + \
    "\n  is_xmit         => " + String(is_xmit)                                    + \
    "\n  is_muted        => " + String(is_muted)                                   + \
    "\n  is_solo         => " + String(is_solo)                                    + \
    "\n  source_ch       => " + String(source_ch)                                  + \
    "\n  is_stereo       => " + String(is_stereo)) ;
#  else // DEBUG_ADDED_CHANNEL_VB
#    define DEBUG_TRACE_ADDED_CHANNEL                                      \
    Trace::TraceGui("added channel slice '" + name + "' to '" +            \
                    String(this->configStore.getParent().getType()) + "'") ;
#  endif // DEBUG_ADDED_CHANNEL_VB
#  define DEBUG_TRACE_REMOVE_LOCAL_CHANNEL                               \
    Trace::TraceEvent("destroying channel '" + String(channel_id) + "'") ;
#  define DEBUG_REMOVE_CHANNELS                                 \
    String user_id = channels->getComponentID() ;               \
    Trace::TraceState("user parted => '" + user_id + "'") ;     \
    Trace::TraceEvent("removing remote user '" + user_id + "'") ;
#  define DEBUG_REMOVE_CHANNEL                                                   \
    Trace::TraceEvent("removing channel '" + String(channel->getComponentID()) + \
                      "' from '" + getComponentID() + "'") ;
#  define DEBUG_TRACE_REMOTE_CHANNELS                                                \
      String dbg = "new remote user[" + String(u_n) + "] =>" +                       \
          "\n  user_name   => " + String(u_name)               +                     \
          "\n  user_volume => " + String(u_vol)                +                     \
          "\n  user_pan    => " + String(u_pan)                +                     \
          "\n  user_mute   => " + String(u_mute) ;                                   \
      int c_n = -1 ; while (LinJam::Client->EnumUserChannels(u_n , ++c_n) != -1)     \
      {                                                                              \
        bool c_rcv ;  float c_vol ; float c_pan ; bool c_mute ;                      \
        bool c_solo ; int   c_chan ; bool  c_stereo ;                                \
        char* c_name = LinJam::Client->GetUserChannelState(u_n     , c_n     ,       \
                                                           &c_rcv  , &c_vol  ,       \
                                                           &c_pan  , &c_mute ,       \
                                                           &c_solo , &c_chan ,       \
                                                           &c_stereo         ) ;     \
        dbg += "\n  found remote channel[" + String(c_n) + "] =>" +                  \
               "\n    channel_name   => "  + String(c_name)       +                  \
               "\n    is_rcv         => "  + String(c_rcv)        +                  \
               "\n    channel_volume => "  + String(c_vol)        +                  \
               "\n    channel_pan    => "  + String(c_pan)        +                  \
               "\n    channel_mute   => "  + String(c_mute)       +                  \
               "\n    is_solo        => "  + String(c_solo)       +                  \
               "\n    output_channel => "  + String(c_chan)       +                  \
               "\n    is_stereo      => "  + String(c_stereo) ;                      \
      }                                                                              \
      Trace::TraceState(dbg) ;
#  define DEBUG_TRACE_REMOTE_CHANNELS_VB if (DEBUG_TRACE_VB) {               \
    Trace::TraceServer("user info changed - " +                              \
                       String(Client->GetNumUsers()) + " users") ;           \
    int u_n = -1 ; char* u_name ; float u_vol ; float u_pan ; bool u_mute ;  \
    while (u_name = Client->GetUserState(++u_n , &u_vol , &u_pan , &u_mute)) \
      { DEBUG_TRACE_REMOTE_CHANNELS }                        }
#  if DEBUG_TRACE_VB
#    define DEBUG_TRACE_ADD_REMOTE_USER_STORE                                    \
    Trace::TraceEvent("user joined => '" + String(user_id) + "'") ;              \
    Trace::TraceConfig("created storage for new remote user " + String(user_id)) ;
#  else // DEBUG_TRACE_VB
#    define DEBUG_TRACE_ADD_REMOTE_USER_STORE                                    \
    float  u_vol  = volume ; float u_pan  = pan ; bool  u_mute = is_muted ;      \
    String u_name = String(user_id) ;                                            \
    int    u_n    = LinJam::Client->GetNumUsers() ; char* c_name ;               \
    while ((c_name = LinJam::Client->GetUserState(--u_n)))                       \
      { String name = String(encodeUserId(c_name , u_n)) ;                       \
        if (!String(user_id).compare(name)) break ; }                            \
    DEBUG_TRACE_REMOTE_CHANNELS                                                  \
    Trace::TraceConfig("created storage for new remote user " + String(user_id)) ;
#  endif // DEBUG_TRACE_VB
#  define DEBUG_TRACE_CONFIGURE_REMOTE                                                   \
    Identifier u_id  = user_store   .getType() ;                                         \
    Identifier ch_id = channel_store.getType() ;                                         \
  /*bool user_mismatch    = user_idx    != GetRemoteUserIdx(u_id) ;                    */\
  /*bool channel_mismatch = channel_idx != GetRemoteChannelIdx(user_idx , ch_id) ;     */\
    String dbg = "configuring remote channel[" + String(channel_idx) + "] '" +           \
                 String(ch_id) + "' for user[" + String(user_idx)    + "] '" +           \
                 String(u_id) + "'" ;                                                    \
    if      (!(~user_idx))     Trace::TraceError("user index out of range "    + dbg) ;  \
  /*else if (user_mismatch)    Trace::TraceError("user index mismatch "        + dbg) ;*/\
    else if (!(~channel_idx))  Trace::TraceError("channel index out of range " + dbg) ;  \
  /*else if (channel_mismatch) Trace::TraceError("channel index mismatch "     + dbg) ;*/\
    else if (DEBUG_TRACE_VB)   Trace::TraceConfig(dbg                                  + \
        ((should_set_volume)?    "\n  volume    => " + String(volume)    : "")         + \
        ((should_set_pan)?       "\n  pan       => " + String(pan)       : "")         + \
        ((should_set_is_rcv)?    "\n  is_rcv    => " + String(is_rcv)    : "")         + \
        ((should_set_is_muted)?  "\n  is_muted  => " + String(is_muted)  : "")         + \
        ((should_set_is_solo)?   "\n  is_solo   => " + String(is_solo)   : "")         + \
        ((should_set_sink_n)?    "\n  sink_n    => " + String(sink_n)    : "")         + \
        ((should_set_is_stereo)? "\n  is_stereo => " + String(is_stereo) : "")         ) ;
#  define DEBUG_TRACE_INVALID_CHANNELID                                     \
    if (channel_id.isEmpty())                                               \
      Trace::TraceError("empty channel_id for " + getComponentID() + "'") ; \
    else if (!findChildWithID(StringRef(channel_id)))                       \
      Trace::TraceError("unknown channel_id '" + channel_id +               \
                        "' for '" + getComponentID() + "'") ;
#  define DEBUG_TRACE_MIXER_COMPONENTS_VB                                      \
    String dbg = String(getNumChildComponents()) + " mixer components (" +     \
        String(GUI::N_STATIC_MIXER_CHILDREN) + " static)=>"  ;                 \
    for (int n = 0 ; n < getNumChildComponents() ; ++n)                        \
    {                                                                          \
      Component* child = getChildComponent(n) ; String id ;                    \
      if      (child == this->masterChannels)   id = "masterChannels" ;        \
      else if (child == this->prevScrollButton) id = "prevScrollButton" ;      \
      else if (child == this->nextScrollButton) id = "nextScrollButton" ;      \
      else if (child == this->localsResizer)    id = "localsResizer" ;         \
      else if (child == this->mastersResizer)   id = "mastersResizer" ;        \
      else                                      id = child->getComponentID() ; \
      dbg += "\n  component[" + String(n) + "] => " + String(id) ;             \
    }                                                                          \
    Trace::TraceVerbose(dbg) ;

// chat
#  define DEBUG_TRACE_CHAT_IN                                                        \
    if (chat_user.compare(Config->currentLogin.toString()))                          \
      Trace::TraceEvent("incoming chat: " + String(parms[CLIENT::CHATMSG_TYPE_IDX])) ;
#  define DEBUG_TRACE_CHAT_OUT                                      \
    if ((chat_text = chat_text.trim()).isNotEmpty())                \
      Trace::TraceEvent("outgoing chat: " + ((chat_text[0] == '/')? \
          chat_text.upToFirstOccurrenceOf(" " , false , false) :    \
          CLIENT::CHATMSG_TYPE_MSG)) ;

#else // #if DEBUG_TRACE

// state
#  define DEBUG_TRACE_LINJAM_INIT              ;
#  define DEBUG_TRACE_LOGIN_LOAD               ;
#  define DEBUG_TRACE_LOGIN_BTNS               ;
#  define DEBUG_TRACE_CONNECT                  ;
#  define DEBUG_TRACE_LICENSE_CLICKED          ;
#  define DEBUG_TRACE_LICENSE                  ;
#  define DEBUG_TRACE_CLEAN_SESSION            ;
#  define DEBUG_TRACE_SHUTDOWN                 ;
// audio
#  define DEBUG_TRACE_AUDIO_INIT_WIN           ;
#  define DEBUG_TRACE_AUDIO_INIT_MAC           ;
#  define DEBUG_TRACE_AUDIO_INIT_JACK          ;
#  define DEBUG_TRACE_AUDIO_INIT_ALSA          ;
#  define DEBUG_TRACE_AUDIO_INIT               ;
// storage
#  define DEBUG_TRACE_LOAD_CONFIG              ;
#  define DEBUG_TRACE_SANITIZE_CONFIG          ;
#  define DEBUG_TRACE_CONFIG_TREE              ;
#  define DEBUG_TRACE_SANITY_CHECK             ;
#  define DEBUG_TRACE_CONFIG_VALUE             ;
#  define DEBUG_TRACE_STORE_CONFIG             ;
#  define DEBUG_TRACE_CONFIG_TREE_CHANGED      ;
#  define DEBUG_TRACE_CONFIG_TREE_ADDED        ;
  #define DEBUG_TRACE_CONFIG_TREE_REMOVED      ;
// network
#  define DEBUG_TRACE_LOGIN_HOST_VB            ;
#  define DEBUG_TRACE_CONNECT_STATUS           ;
// channels
#  define DEBUG_TRACE_CHANNELS_VB              ;
#  define DEBUG_TRACE_ADD_CHANNEL_GUI          ;
#  define DEBUG_TRACE_ADD_LOCAL_CHANNEL_FAIL   ;
#  define DEBUG_TRACE_ADD_CHANNEL_STORE        ;
#  define DEBUG_TRACE_CONFIGURE_LOCAL_CHANNEL  ;
#  define DEBUG_TRACE_ADDED_CHANNEL            ;
#  define DEBUG_TRACE_REMOVE_LOCAL_CHANNEL     ;
#  define DEBUG_REMOVE_CHANNELS                ;
#  define DEBUG_REMOVE_CHANNEL                 ;
#  define DEBUG_TRACE_REMOTE_CHANNELS          ;
#  define DEBUG_TRACE_REMOTE_CHANNELS_VB       ;
#  define DEBUG_TRACE_ADD_REMOTE_USER_STORE    ;
#  define DEBUG_TRACE_CONFIGURE_REMOTE         ;
#  define DEBUG_TRACE_INVALID_CHANNELID        ;
#  define DEBUG_TRACE_MIXER_COMPONENTS_VB      ;
// chat
#  define DEBUG_TRACE_CHAT_IN                  ;
#  define DEBUG_TRACE_CHAT_OUT                 ;

#endif // #if DEBUG_TRACE


class Trace
{
public:

  static void TraceEvent(  String msg) ;
  static void TraceConfig( String msg) ;
  static void TraceGui(    String msg) ;
  static void TraceVerbose(String msg) ;
  static void TraceState(  String msg) ;
  static void TraceNetwork(String msg) ;
  static void TraceError(  String msg) ;
  static void TraceServer( String msg) ;

  static void DumpStoreXml(ValueTree store) ;

  static String SanitizeConfig(      ValueTree default_config , ValueTree stored_config ,
                                     String pad) ;
  static void   TraceInvalidNode(    String a_node_key) ;
  static void   TraceMissingValue(   String a_node_key , String a_value_key) ;
  static void   TraceMissingProperty(String a_node_key , String a_property_key) ;

  static void   DbgValueType(String val_name , var a_var) ;


private:

  static bool SanityCheck() ;

  static bool TraceEvs() ;
  static bool TraceVb() ;
  static bool TraceState() ;
} ;

#endif // _TRACE_H_
