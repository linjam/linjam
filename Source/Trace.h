
#ifndef _TRACE_H_
#define _TRACE_H_

#define DEBUG_TRACE            DEBUG && 1
#define DEBUG_TRACE_EVENTS     DEBUG && 1
#define DEBUG_TRACE_STATE      DEBUG && 1
#define DEBUG_TRACE_IN         DEBUG && 1
#define DEBUG_TRACE_OUT        DEBUG && 1
#define DEBUG_TRACE_VB         DEBUG && 0
#define DEBUG_SANITIZE_CONFIG  DEBUG && 0
#define DEBUG_SHARED_CONFIG    DEBUG && 0
#define DEBUG_STORE_CONFIG_VB  DEBUG && 0
#define DEBUG_ADDED_CHANNEL_VB DEBUG && 0

#define DEBUG_EXIT_IMMEDIAYELY       0
#define DEBUG_LOCALHOST_LOGIN_BUTTON 0

#define BUGGY_CHAT_COMMANDS
#define ADD_REMOTES         1
#define UPDATE_VU           0


#if DEBUG_TRACE

#  define DEBUG_TRACE_LINJAM_INIT Trace::TraceEvent("initializing") ;

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

#  define DEBUG_TRACE_LOAD_CONFIG                                                       \
    Identifier root_node_id = CONFIG::PERSISTENCE_IDENTIFIER ;                          \
    if (default_config_xml == nullptr || !default_config_xml->hasTagName(root_node_id)) \
        Trace::TraceConfig("default config invalid") ;                                  \
    else Trace::TraceConfig("default config loaded") ;                                  \
    if (stored_config_xml == nullptr)                                                   \
        Trace::TraceConfig("stored config not found - falling back on defaults") ;      \
    else if (!stored_config_xml->hasTagName(CONFIG::PERSISTENCE_IDENTIFIER))            \
        Trace::TraceConfig("stored config is invalid - falling back on defaults") ;     \
    else Trace::TraceConfig("stored config found") ;
#  if DEBUG_SANITIZE_CONFIG
#    define DEBUG_TRACE_SANITIZE_CONFIG                                                 \
    if      (default_config_xml == nullptr)                                             \
    { Trace::TraceError("default_config_xml invalid - bailing") ; return ; }            \
    else if (stored_config_xml != nullptr &&                                            \
             stored_config_xml->hasTagName(CONFIG::PERSISTENCE_IDENTIFIER))             \
      Trace::TraceConfig("stored config parsed successfully =>" +                       \
                        Trace::SanitizeConfig(ValueTree::fromXml(*default_config_xml) , \
                                              ValueTree::fromXml(*stored_config_xml) , "  ")) ;
#  else // DEBUG_SANITIZE_CONFIG
#    define DEBUG_TRACE_SANITIZE_CONFIG ;
#  endif // DEBUG_SANITIZE_CONFIG
#  if DEBUG_SHARED_CONFIG
#    define DEBUG_TRACE_CONFIG_TREE                                               \
    bool valid = tree_node.isValid() ; String n = String(tree_node_id) ;          \
    Trace::TraceConfig("node '" + n + ((valid)? "' (" : "' (in") + "valid) - ") ;
#    define DEBUG_TRACE_CONFIG_VALUE                                                \
    bool valid = value_node.isValid() ; String name = String(child_node_id) ;       \
    String k = String(key) ;                                                        \
    Trace::TraceConfig("node '" + name + ((valid)? "' (" : "' (in") + "valid) - " + \
        ((valid && value_node.hasProperty(key))?                                    \
            "has shared value on key '"        + k + "'" :                          \
            "has dummy value on missing key '" + k + "'")) ;
#  else // DEBUG_SHARED_CONFIG
#    define DEBUG_TRACE_CONFIG_TREE  ;
#    define DEBUG_TRACE_CONFIG_VALUE ;
#  endif // DEBUG_SHARED_CONFIG
#  define DEBUG_TRACE_SANITY_CHECK                                                      \
    /* subscribed trees */                                                              \
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
      Trace::TraceMissingProperty(CONFIG::MASTER_KEY        , CONFIG::MUTE_KEY) ;       \
    if (!metro_channel_has_volume_property)                                             \
      Trace::TraceMissingProperty(CONFIG::METRO_KEY         , CONFIG::VOLUME_KEY) ;     \
    if (!metro_channel_has_pan_property)                                                \
      Trace::TraceMissingProperty(CONFIG::METRO_KEY         , CONFIG::PAN_KEY) ;        \
    if (!metro_channel_has_mute_property)                                               \
      Trace::TraceMissingProperty(CONFIG::METRO_KEY         , CONFIG::MUTE_KEY) ;       \
    if (!metro_channel_has_source_property)                                             \
      Trace::TraceMissingProperty(CONFIG::METRO_KEY         , CONFIG::SOURCE_N_KEY) ;   \
    if (!metro_channel_has_stereo_property)                                             \
      Trace::TraceMissingProperty(CONFIG::METRO_KEY         , CONFIG::STEREO_KEY) ;     \
    if (!default_channel_has_volume_property)                                           \
      Trace::TraceMissingProperty(CONFIG::INITIAL_LOCAL_KEY , CONFIG::VOLUME_KEY) ;     \
    if (!default_channel_has_pan_property)                                              \
      Trace::TraceMissingProperty(CONFIG::INITIAL_LOCAL_KEY , CONFIG::PAN_KEY) ;        \
    if (!default_channel_has_xmit_property)                                             \
      Trace::TraceMissingProperty(CONFIG::INITIAL_LOCAL_KEY , CONFIG::XMIT_KEY) ;       \
    if (!default_channel_has_mute_property)                                             \
      Trace::TraceMissingProperty(CONFIG::INITIAL_LOCAL_KEY , CONFIG::MUTE_KEY) ;       \
    if (!default_channel_has_solo_property)                                             \
      Trace::TraceMissingProperty(CONFIG::INITIAL_LOCAL_KEY , CONFIG::SOLO_KEY) ;       \
    if (!default_channel_has_source_property)                                           \
      Trace::TraceMissingProperty(CONFIG::INITIAL_LOCAL_KEY , CONFIG::SOURCE_N_KEY) ;   \
    if (!default_channel_has_stereo_property)                                           \
      Trace::TraceMissingProperty(CONFIG::INITIAL_LOCAL_KEY , CONFIG::STEREO_KEY) ;     \
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
#    define DEBUG_TRACE_STORE_CONFIG Trace::TraceConfig("storing config xml=\n" +        \
                                                        configValueTree.toXmlString()) ;
#  else // DEBUG_STORE_CONFIG_VB
#    define DEBUG_TRACE_STORE_CONFIG Trace::TraceConfig("storing config xml") ;
#  endif // DEBUG_STORE_CONFIG_VB
#  define DEBUG_TRACE_CONFIG_CHANGED String event_source ;                                      \
    if      (a_value.refersToSameSourceAs(this->masterVolume)) event_source = "masterVolume" ;  \
    else if (etc);                                                                              \
    Trace::TraceEvent("value changed " + event_source + " = " + a_value.getValue().toString()) ;
#  define DEBUG_TRACE_CONFIG_TREE_CHANGED                                           \
    String node = String(a_node.getType()) ; String val = a_node[key].toString() ;  \
    Trace::TraceEvent("value changed " + node + "[" + String(key) + "] = " + val) ;

#  define DEBUG_TRACE_LOGIN_LOAD                                                     \
    Trace::TraceState("Lobby - storage " + String((server.isValid())? "" : "not ") + \
                      "found for currentHost => '" + host + "'") ;
#  define DEBUG_TRACE_LOGIN_BTNS                                                             \
    if      (buttonThatWasClicked == loginButton) Trace::TraceEvent("loginButton clicked") ; \
    else if (buttonThatWasClicked == anonButton)  Trace::TraceEvent("anonButton clicked") ;  \
    else if (loginButtons.contains((TextButton*)buttonThatWasClicked))                       \
      Trace::TraceEvent("quick-login button clicked " +                                      \
          buttonThatWasClicked->getButtonText().trim()) ;
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
#  define DEBUG_TRACE_CONNECT Trace::TraceState((!IsAgreed())?                               \
                                                "connecting to " + host :                    \
                                                "joining "       + host + " as " + login) ;

#  define DEBUG_TRACE_LICENSE_CLICKED                                                          \
    if      (buttonThatWasClicked == cancelButton) Trace::TraceEvent("cancelButton clicked") ; \
    else if (buttonThatWasClicked == agreeButton)  Trace::TraceEvent("agreeButton clicked") ;  \
    else if (buttonThatWasClicked == alwaysButton) Trace::TraceEvent("alwaysButton clicked") ;
#  define DEBUG_TRACE_LICENSE Trace::TraceState((is_agreed)? "agreeing to license" : \
                                                "prompting for license agreement") ;

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

#  define DEBUG_TRACE_CHANNELS_VB /* TODO: do not use - some of this is obsolete */ \
    /* master channel */                                                            \
    this->chatComponent->addChatLine("" , "") ;                                     \
    this->chatComponent->addChatLine("master channel:\n" ,                          \
        String("mastervol=")   + String(this->config_mastervolume)  +               \
        String(" masterpan=")  + String(this->config_masterpan)     +               \
        String(" mastermute=") + String(this->config_mastermute)    +               \
        String(" metrovol=")   + String(this->config_metronome)     +               \
        String(" metropan=")   + String(this->config_metronome_pan) +               \
        String(" metromute=")  + String(this->config_metronome_mute)) ;             \
    this->chatComponent->addChatLine("" , "") ;                                     \
                                                                                    \
    /* local channels */                                                            \
    int ch_n = -1 ; int ch_idx ;                                                    \
    while ((ch_idx = EnumLocalChannels(++ch_n)) >= 0)                               \
    {                                                                               \
      int source_n = 0 ; bool xmit = 0 ; void* fx = 0 ;                             \
      float vol = 0.0f , pan = 0.0f ; bool mute = 0 , solo = 0 ;                    \
      char* name = GetLocalChannelInfo(ch_idx , &source_n , NULL , &xmit) ;         \
      GetLocalChannelMonitoring(ch_idx , &vol , &pan , &mute , &solo) ;             \
      GetLocalChannelProcessor(ch_idx , NULL , &fx) ;                               \
      this->chatComponent->addChatLine(                                             \
          String("local channel ")   + String(ch_n)     +                           \
              String(" (")   + String(ch_idx)   + String("):\n") ,                  \
          String("name=")    + String(name)     +                                   \
          String(" source=") + String(source_n) +                                   \
          String(" xmit=")   + String(xmit)     +                                   \
          String(" mute=")   + String(mute)     +                                   \
          String(" solo=")   + String(solo)     +                                   \
          String(" volume=") + String(vol)      +                                   \
          String(" pan=")    + String(pan)      +                                   \
          String(" fx=")     + String(!!fx)     ) ;                                 \
    }                                                                               \
                                                                                    \
    /* remote users */                                                              \
    int user_n = -1 ; ch_n = -1 ; int n_users = m_remoteusers.GetSize() ;           \
    while (++user_n < n_users)                                                      \
    {                                                                               \
      float vol = 0.0f , pan = 0.0f ; bool mute = 0 ;                               \
      char* name = GetUserState(user_n , &vol , &pan , &mute) ;                     \
      this->chatComponent->addChatLine("" , "") ;                                   \
      this->chatComponent->addChatLine(                                             \
          String("remote user ") + String(user_n) + String(":\n") ,                 \
          String("name=")        + String(name)   +                                 \
          String(" volume=")     + String(vol)    +                                 \
          String(" pan=")        + String(pan)    +                                 \
          String(" mute=")       + String(mute)                   ) ;               \
                                                                                    \
      /* remote user channels */                                                    \
      ch_n = -1 ;                                                                   \
      while ((ch_idx = EnumUserChannels(user_n , ++ch_n)) >= 0)                     \
      {                                                                             \
        float vol = 0.0f , pan = 0.0f ; bool sub = 0 , mute = 0 , solo = 0 ;        \
        int out_ch = 0 ; bool stereo = 0 ;                                          \
        char* name = GetUserChannelState(user_n , ch_idx  , &sub    ,               \
                                         &vol   , &pan    , &mute   ,               \
                                         &solo  , &out_ch , &stereo ) ;             \
        this->chatComponent->addChatLine(                                           \
            String("    remote channel ") + String(ch_n)     +                      \
                String(" (")              + String(ch_idx)   + String("):\n") ,     \
            String("    name=")           + String(name)     +                      \
            String(" subscribed=")        + String(sub)      +                      \
            String(" volume=")            + String(vol)      +                      \
            String(" pan=")               + String(pan)      +                      \
            String(" mute=")              + String(mute)     +                      \
            String(" solo=")              + String(solo)     +                      \
            String(" out_ch=")            + String(out_ch)   +                      \
            String(" stereo=")            + String(stereo)                    ) ;   \
      }                                                                             \
    }
#  define DEBUG_TRACE_REMOTE_CHANNELS                                                \
      String dbg = "found remote user[" + String(u_n) + "] =>" +                     \
          "\n  user_name   => " + String(u_name)               +                     \
          "\n  user_volume => " + String(u_vol)                +                     \
          "\n  user_pan    => " + String(u_pan)                +                     \
          "\n  user_mute   => " + String(u_mute) ;                                   \
      int c_n = -1 ; while (Client->EnumUserChannels(u_n , ++c_n) != -1)             \
      {                                                                              \
        bool c_rcv ;  float c_vol ; float c_pan ; bool c_mute ;                      \
        bool c_solo ; int   c_chan ; bool  c_stereo ;                                \
        char* c_name = Client->GetUserChannelState(u_n , c_n , &c_rcv  , &c_vol  ,   \
                                                   &c_pan    , &c_mute , &c_solo ,   \
                                                   &c_chan   , &c_stereo         ) ; \
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
#  define DEBUG_TRACE_REMOTE_CHANNELS_VB if (DEBUG_TRACE_VB) {                              \
    Trace::TraceServer("user info changed - " + String(Client->GetNumUsers()) + " users") ; \
    int u_n = -1 ; char* u_name ; float u_vol ; float u_pan ; bool u_mute ;                 \
    while (u_name = Client->GetUserState(++u_n , &u_vol , &u_pan , &u_mute))                \
      { DEBUG_TRACE_REMOTE_CHANNELS }                        }
#  define DEBUG_TRACE_ADD_REMOTE_USER                                                \
    int   u_n   = user_idx ;    char* u_name = user_name ;                           \
    float u_vol = user_volume ; float u_pan  = user_pan ; bool u_mute = user_muted ; \
    DEBUG_TRACE_REMOTE_CHANNELS                                                      \
    Trace::TraceConfig("adding remote user " + String(user_id)) ;
#  define DEBUG_TRACE_ADD_CHANNEL                                                   \
    if      (mixergroup_id == GUI::MASTER_MIXERGROUP_IDENTIFIER)                    \
         Trace::TraceConfig("adding master channel '" + String(channel_id) + "'") ; \
    else if (mixergroup_id == GUI::LOCAL_MIXERGROUP_IDENTIFIER)                     \
         Trace::TraceConfig("adding local channel[" + String(channel_idx) +         \
                            "] - " + String(channel_id)) ;                          \
    else Trace::TraceEvent("adding remote channel '" + String(channel_id) +         \
                           "' for user " + String(mixergroup_id)) ;
#  define DEBUG_TRACE_NEW_LOCAL_CHANNEL_FAIL                                            \
    int n_chs = -1 ; while (~Client->EnumLocalChannels(++n_chs)) ;                      \
    if (n_chs >= Client->GetMaxLocalChannels())                                         \
      Trace::TraceError("cannot create new local channel - maximum input channels = " + \
                        String(Client->GetMaxLocalChannels())) ;
#  define DEBUG_TRACE_NEW_LOCAL_CHANNEL                                    \
    Trace::TraceEvent("created new local channel[" + String(channel_idx) + \
                      "] - " + String(channel_id)) ;
#  define DEBUG_TRACE_CONFIGURE_LOCAL_CHANNEL                                    \
    Trace::TraceConfig("configuring local channel "  + channel_name            + \
        ((should_set_volume)?    "\n  volume    => " + String(volume)    : "") + \
        ((should_set_pan)?       "\n  pan       => " + String(pan)       : "") + \
        ((should_set_is_xmit)?   "\n  is_xmit   => " + String(is_xmit)   : "") + \
        ((should_set_is_muted)?  "\n  is_muted  => " + String(is_muted)  : "") + \
        ((should_set_is_solo)?   "\n  is_solo   => " + String(is_solo)   : "") + \
        ((should_set_source_n)?  "\n  source_n  => " + String(source_n)  : "") + \
        ((should_set_bit_depth)? "\n  bit_depth => " + String(bit_depth) : "") + \
        ((should_set_is_stereo)? "\n  is_stereo => " + String(is_stereo) : "") ) ;
#  if DEBUG_ADDED_CHANNEL_VB
#    define DEBUG_TRACE_ADDED_CHANNEL Trace::TraceEvent(String("channel added =>") + \
    "\n  mixergroup      => " + String(this->configStore.getParent().getType())         + \
    "\n  name            => " + name                                               + \
    "\n  volume          => " + String(volume)                                     + \
    "\n  pan             => " + String(pan)                                        + \
    "\n  is_xmit         => " + String(is_xmit)                                    + \
    "\n  is_muted        => " + String(is_muted)                                   + \
    "\n  is_solo         => " + String(is_solo)                                    + \
    "\n  source_ch       => " + String(source_ch)                                  + \
    "\n  is_stereo       => " + String(is_stereo)) ;
#  else // DEBUG_ADDED_CHANNEL_VB
#    define DEBUG_TRACE_ADDED_CHANNEL                              \
    Trace::TraceEvent(String(this->configStore.getParent().getType()) + \
                      " - channel added '" + name + "'") ;
#  endif // DEBUG_ADDED_CHANNEL_VB
#  define DEBUG_TRACE_INVALID_CHANNELID                                 \
    else Trace::TraceError("invalid channel_id '" + channel_id + "'") ;

#  define DEBUG_TRACE_CHAT_IN                                                          \
    if (chat_user.compare(Config->currentLogin.toString()))                            \
      Trace::TraceEvent("incoming chat: " + String(parms[CLIENT::CHATMSG_TYPE_IDX])) ;
//#  define DEBUG_TRACE_CHATIN String msg = "|" ; for (;nparms--;) msg += String(parms[nparms]) + "|" ; Trace::TraceEvent("LinJam::OnChatmsg()=\n\"" + msg + "\"") ;
//#  define DEBUG_TRACE_CHATIN Trace::TraceEvent("LinJam::OnChatmsg()=\n") ; for (;nparms--;) Trace::TraceEvent("\tnparms[" + String(nparms) + "]='" + String(parms[nparms]) + "'\n") ;
#  define DEBUG_TRACE_CHAT_OUT                                      \
    if ((chat_text = chat_text.trim()).isNotEmpty())                \
      Trace::TraceEvent("outgoing chat: " + ((chat_text[0] == '/')? \
          chat_text.upToFirstOccurrenceOf(" " , false , false) :    \
          CLIENT::CHATMSG_TYPE_MSG)) ;
// DBG("LinJam::SendChat() =" + chat_text) ;

#  define DEBUG_TRACE_CLEAN_SESSION                                                                \
    File thisdir = File::getSpecialLocation(File::currentExecutableFile).getParentDirectory() ;    \
    if (!SessionDir.isDirectory() || !SessionDir.isAChildOf(thisdir))                              \
        Trace::TraceError("session directory '" + SessionDir.getFullPathName() + "' is invalid") ; \
    else Trace::TraceState("cleaning session directory '" + SessionDir.getFullPathName() + "'") ;
#  define DEBUG_TRACE_SHUTDOWN           Trace::TraceState("clean shutdown - bye") ;

#else // #if DEBUG_TRACE

#  define DEBUG_TRACE_LINJAM_INIT             ;
#  define DEBUG_TRACE_AUDIO_INIT_WIN          ;
#  define DEBUG_TRACE_AUDIO_INIT_MAC          ;
#  define DEBUG_TRACE_AUDIO_INIT_JACK         ;
#  define DEBUG_TRACE_AUDIO_INIT_ALSA         ;
#  define DEBUG_TRACE_AUDIO_INIT              ;
#  define DEBUG_TRACE_LOAD_CONFIG             ;
#  define DEBUG_TRACE_SANITIZE_CONFIG         ;
#  define DEBUG_TRACE_CONFIG_TREE             ;
#  define DEBUG_TRACE_SANITY_CHECK            ;
#  define DEBUG_TRACE_CONFIG_VALUE            ;
#  define DEBUG_TRACE_STORE_CONFIG            ;
#  define DEBUG_TRACE_CONFIG_CHANGED          ;
#  define DEBUG_TRACE_CONFIG_TREE_CHANGED     ;
#  define DEBUG_TRACE_LOGIN_LOAD              ;
#  define DEBUG_TRACE_LOGIN_BTNS              ;
#  define DEBUG_TRACE_LOGIN_HOST_VB           ;
#  define DEBUG_TRACE_CONNECT                 ;
#  define DEBUG_TRACE_LICENSE_CLICKED         ;
#  define DEBUG_TRACE_LICENSE                 ;
#  define DEBUG_TRACE_CONNECT_STATUS          ;
#  define DEBUG_TRACE_CHANNELS_VB             ;
#  define DEBUG_TRACE_REMOTE_CHANNELS         ;
#  define DEBUG_TRACE_REMOTE_CHANNELS_VB      ;
#  define DEBUG_TRACE_ADD_REMOTE_USER         ;
#  define DEBUG_TRACE_ADD_CHANNEL             ;
#  define DEBUG_TRACE_NEW_LOCAL_CHANNEL_FAIL  ;
#  define DEBUG_TRACE_NEW_LOCAL_CHANNEL       ;
#  define DEBUG_TRACE_CONFIGURE_LOCAL_CHANNEL ;
#  define DEBUG_TRACE_ADDED_CHANNEL           ;
#  define DEBUG_TRACE_INVALID_CHANNELID       ;
#  define DEBUG_TRACE_CHAT_IN                 ;
#  define DEBUG_TRACE_CHAT_OUT                ;
#  define DEBUG_TRACE_CLEAN_SESSION           ;
#  define DEBUG_TRACE_SHUTDOWN                ;

#endif // #if DEBUG_TRACE


class Trace
{
public:

  static void TraceConfig( String msg) ;
  static void TraceEvent(  String msg) ;
  static void TraceVerbose(String msg) ;
  static void TraceState(  String msg) ;
  static void TraceNetwork(String msg) ;
  static void TraceError(  String msg) ;
  static void TraceServer( String msg) ;

  static void Dbg(         String    type , String msg) ;
  static void DumpStoreXml(ValueTree store) ;

  static String SanitizeConfig(      ValueTree default_config , ValueTree stored_config ,
                                     String pad) ;
  static void   TraceInvalidNode(    String a_node_key) ;
  static void   TraceMissingValue(   String a_node_key , String a_value_key) ;
  static void   TraceMissingProperty(String a_node_key , String a_property_key) ;


private:

  static bool SanityCheck() ;

  static bool TraceEvs() ;
  static bool TraceVb() ;
  static bool TraceState() ;
} ;

#endif // _TRACE_H_
