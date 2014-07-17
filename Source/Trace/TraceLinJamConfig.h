#include "Trace.h"
#include "TraceLinJam.h"


/* storage */

#define DEBUG_TRACE_LOAD_CONFIG                                                       \
  Identifier root_node_id = CONFIG::PERSISTENCE_ID ;                                  \
  if (default_config_xml == nullptr || !default_config_xml->hasTagName(root_node_id)) \
      Trace::TraceConfig("default config invalid - bailing") ;                        \
  else Trace::TraceConfig("default config loaded") ;                                  \
  if (stored_config_xml == nullptr)                                                   \
      Trace::TraceConfig("stored config not found - falling back on defaults") ;      \
  else if (!stored_config_xml->hasTagName(CONFIG::PERSISTENCE_ID))                    \
      Trace::TraceConfig("stored config is invalid - falling back on defaults") ;     \
  else Trace::TraceConfig("stored config found") ;

#if TRACE_SANITIZE_CONFIG
#  define DEBUG_TRACE_SANITIZE_CONFIG                                                   \
  if (!is_stored_config_bogus)                                                          \
    Trace::TraceConfig("stored config parsed successfully =>" +                         \
                       Trace::SanitizeConfig(ValueTree::fromXml(*default_config_xml) ,  \
                                             ValueTree::fromXml(*stored_config_xml)  ,  \
                                             "  "                                    )) ;
#else // TRACE_SANITIZE_CONFIG
#  define DEBUG_TRACE_SANITIZE_CONFIG ;
#endif // TRACE_SANITIZE_CONFIG

#if TRACE_CONFIG_TYPES
#  define DEBUG_TRACE_CONFIG_TYPES_VB                                               \
  String parent_id = (node_id == CONFIG::PERSISTENCE_ID)             ? "root " :    \
                     (grandparent_node == this->remoteUsers)                   ?    \
                     CONFIG::REMOTES_KEY + " " + String(parent_node.getType()) :    \
                     String(parent_node.getType())                             ;    \
  if (parent_node == this->servers        ||                                        \
      parent_node == this->masterChannels ||                                        \
      parent_node == this->localChannels)                                           \
    parent_id = String(parent_node.getType()) ; /* KLUDGE: (issue #33) */           \
  String dbg = "restoring types - " + parent_id + " " + String(node_id)           + \
                " (" + String(config_store.getNumProperties()) + " properties - " + \
               String(config_store.getNumChildren())     + " children)" ;           \
  for (int prop_n = 0 ; prop_n < config_store.getNumProperties() ; ++prop_n)        \
  {                                                                                 \
    Identifier key = config_store.getPropertyName(prop_n) ;                         \
    dbg           += "\n  " + Trace::VarType(String(key) , config_store[key]) ;     \
  }                                                                                 \
  Trace::TraceConfig(dbg) ;
#else // TRACE_CONFIG_TYPES
#  define DEBUG_TRACE_CONFIG_TYPES_VB ;
#endif // TRACE_CONFIG_TYPES

#if TRACE_SHARED_CONFIG
#  define DEBUG_TRACE_CONFIG_TREE                                              \
  bool valid = tree_node.isValid() ; String n = String(tree_node_id) ;         \
  Trace::TraceConfig("node '" + n + ((valid)? "' (" : "' (in") + "valid) - ")) ;
#  define DEBUG_TRACE_CONFIG_VALUE                                                \
  bool valid = value_node.isValid() ; String name = String(child_node_id) ;       \
  String k = String(key) ;                                                        \
  Trace::TraceConfig("node '" + name + ((valid)? "' (" : "' (in") + "valid) - " + \
                    ((valid && value_node.hasProperty(key))?                      \
                        "has shared value on key '"        + k + "'" :            \
                        "has dummy value on missing key '" + k + "'"))) ;
#else // TRACE_SHARED_CONFIG
#  define DEBUG_TRACE_CONFIG_TREE  ;
#  define DEBUG_TRACE_CONFIG_VALUE ;
#endif // TRACE_SHARED_CONFIG

#define DEBUG_TRACE_SANITY_CHECK                                                      \
  /* subscribed trees */                                                              \
  if (!root_is_valid)                                                                 \
    Trace::TraceInvalidNode(CONFIG::PERSISTENCE_KEY) ;                                \
  if (!auto_subscribe_users_is_valid)                                                 \
    Trace::TraceInvalidNode(CONFIG::SUBSCRIPTIONS_KEY) ;                              \
  if (!master_channels_is_valid)                                                      \
    Trace::TraceInvalidNode(CONFIG::MASTERS_KEY) ;                                    \
  if (!local_channels_is_valid)                                                       \
    Trace::TraceInvalidNode(CONFIG::LOCALS_KEY) ;                                     \
  if (!remote_users_is_valid)                                                         \
    Trace::TraceInvalidNode(CONFIG::REMOTES_KEY) ;                                    \
  if (!servers_is_valid)                                                              \
    Trace::TraceInvalidNode(CONFIG::SERVERS_KEY) ;                                    \
                                                                                      \
  /* implicitly subscribed values (via above trees) */                                \
  if (!master_channel_has_name_property)                                              \
    Trace::TraceMissingProperty(CONFIG::MASTER_KEY , CONFIG::CHANNELNAME_KEY) ;       \
  if (!master_channel_has_volume_property)                                            \
    Trace::TraceMissingProperty(CONFIG::MASTER_KEY , CONFIG::VOLUME_KEY) ;            \
  if (!master_channel_has_pan_property)                                               \
    Trace::TraceMissingProperty(CONFIG::MASTER_KEY , CONFIG::PAN_KEY) ;               \
  if (!master_channel_has_mute_property)                                              \
    Trace::TraceMissingProperty(CONFIG::MASTER_KEY , CONFIG::IS_MUTED_KEY) ;          \
  if (!metro_channel_has_name_property)                                               \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::CHANNELNAME_KEY) ;       \
  if (!metro_channel_has_volume_property)                                             \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::VOLUME_KEY) ;            \
  if (!metro_channel_has_pan_property)                                                \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::PAN_KEY) ;               \
  if (!metro_channel_has_mute_property)                                               \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::IS_MUTED_KEY) ;          \
  if (!metro_channel_has_source_property)                                             \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::SOURCE_N_KEY) ;          \
  if (!metro_channel_has_stereo_property)                                             \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::STEREO_KEY) ;            \
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
  if (!host_has_value)                                                                \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::HOST_KEY) ;                 \
  if (!login_has_value)                                                               \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::LOGIN_KEY) ;                \
  if (!pass_has_value)                                                                \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::PASS_KEY) ;                 \
  if (!is_anonymous_has_value)                                                        \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::IS_ANON_KEY) ;              \
  if (!is_agreed_has_value)                                                           \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::IS_AGREED_KEY) ;            \
  if (!should_agree_has_value)                                                        \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::SHOULD_AGREE_KEY) ;         \
  if (!should_hide_bots_has_value)                                                    \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::SHOULD_HIDE_BOTS_KEY) ;     \
                                                                                      \
  /* data types */                                                                    \
  ValueTree master = master_channel ; ValueTree metro = metro_channel ;               \
  if (!master_name_is_string)                                                         \
    Trace::TraceTypeMismatch(CONFIG::MASTER_KEY  , CONFIG::CHANNELNAME_KEY          , \
                             CONFIG::STRING_TYPE , master[CONFIG::CHANNELNAME_KEY]) ; \
  if (!master_volume_is_double)                                                       \
    Trace::TraceTypeMismatch(CONFIG::MASTER_KEY  , CONFIG::VOLUME_KEY               , \
                             CONFIG::DOUBLE_TYPE , master[CONFIG::VOLUME_KEY]) ;      \
  if (!master_pan_is_double)                                                          \
    Trace::TraceTypeMismatch(CONFIG::MASTER_KEY  , CONFIG::PAN_KEY                  , \
                             CONFIG::DOUBLE_TYPE , master[CONFIG::PAN_KEY]) ;         \
  if (!master_mute_is_bool)                                                           \
    Trace::TraceTypeMismatch(CONFIG::MASTER_KEY  , CONFIG::IS_MUTED_KEY             , \
                             CONFIG::BOOL_TYPE   , master[CONFIG::IS_MUTED_KEY]) ;    \
  if (!metro_name_is_string)                                                          \
    Trace::TraceTypeMismatch(CONFIG::METRO_KEY   , CONFIG::CHANNELNAME_KEY          , \
                             CONFIG::STRING_TYPE , metro[CONFIG::CHANNELNAME_KEY]) ;  \
  if (!metro_volume_is_double)                                                        \
    Trace::TraceTypeMismatch(CONFIG::METRO_KEY   , CONFIG::VOLUME_KEY               , \
                             CONFIG::DOUBLE_TYPE , metro[CONFIG::VOLUME_KEY]) ;       \
  if (!metro_pan_is_double)                                                           \
    Trace::TraceTypeMismatch(CONFIG::METRO_KEY   , CONFIG::PAN_KEY                  , \
                             CONFIG::DOUBLE_TYPE , metro[CONFIG::PAN_KEY]) ;          \
  if (!metro_mute_is_bool)                                                            \
    Trace::TraceTypeMismatch(CONFIG::METRO_KEY   , CONFIG::IS_MUTED_KEY             , \
                             CONFIG::BOOL_TYPE   , metro[CONFIG::IS_MUTED_KEY]) ;     \
  if (!metro_source_is_int)                                                           \
    Trace::TraceTypeMismatch(CONFIG::METRO_KEY   , CONFIG::SOURCE_N_KEY             , \
                             CONFIG::INT_TYPE    , metro[CONFIG::SOURCE_N_KEY]) ;     \
  if (!metro_stereo_is_int)                                                           \
    Trace::TraceTypeMismatch(CONFIG::METRO_KEY   , CONFIG::STEREO_KEY               , \
                             CONFIG::INT_TYPE    , metro[CONFIG::STEREO_KEY]) ;       \
  if (!save_audio_is_int)                                                             \
    Trace::TraceTypeMismatch(CONFIG::CLIENT_KEY  , CONFIG::SAVE_AUDIO_KEY           , \
                             CONFIG::INT_TYPE    , this->saveAudio.getValue()) ;      \
  if (!save_log_is_bool)                                                              \
    Trace::TraceTypeMismatch(CONFIG::CLIENT_KEY  , CONFIG::SAVE_LOG_KEY             , \
                             CONFIG::BOOL_TYPE   , this->shouldSaveLog.getValue()) ;  \
  if (!deuglevel_is_int)                                                              \
    Trace::TraceTypeMismatch(CONFIG::CLIENT_KEY  , CONFIG::DEBUGLEVEL_KEY           , \
                             CONFIG::INT_TYPE    , this->debugLevel.getValue()) ;     \
  if (!autosubscribe_is_int)                                                          \
    Trace::TraceTypeMismatch(CONFIG::CLIENT_KEY  , CONFIG::AUTOSUBSCRIBE_KEY        , \
                             CONFIG::INT_TYPE    , this->autoSubscribe.getValue()) ;  \
  if (!audio_ifn_is_int)                                                              \
    Trace::TraceTypeMismatch(CONFIG::AUDIO_KEY   , CONFIG::AUDIO_IF_KEY             , \
                             CONFIG::INT_TYPE    , this->audioIfN.getValue()) ;       \
  if (!n_inputs_is_int)                                                               \
    Trace::TraceTypeMismatch(CONFIG::AUDIO_KEY   , CONFIG::N_INPUTS_KEY             , \
                             CONFIG::INT_TYPE    , this->nInputs.getValue()) ;        \
  if (!n_outputs_is_int)                                                              \
    Trace::TraceTypeMismatch(CONFIG::AUDIO_KEY   , CONFIG::N_OUTPUTS_KEY            , \
                             CONFIG::INT_TYPE    , this->nOutputs.getValue()) ;       \
  if (!bitdepth_is_int)                                                               \
    Trace::TraceTypeMismatch(CONFIG::AUDIO_KEY   , CONFIG::BITDEPTH_KEY             , \
                             CONFIG::INT_TYPE    , this->bitDepth.getValue()) ;       \
  if (!samplerate_is_int)                                                             \
    Trace::TraceTypeMismatch(CONFIG::AUDIO_KEY   , CONFIG::SAMPLERATE_KEY           , \
                             CONFIG::INT_TYPE    , this->sampleRate.getValue()) ;     \
  if (!jack_name_is_string)                                                           \
    Trace::TraceTypeMismatch(CONFIG::AUDIO_KEY   , CONFIG::JACK_NAME_KEY            , \
                             CONFIG::STRING_TYPE , this->jackName.getValue()) ;       \
  if (!host_name_is_string)                                                           \
    Trace::TraceTypeMismatch(CONFIG::SERVER_KEY  , CONFIG::HOST_KEY                 , \
                             CONFIG::STRING_TYPE , this->host.getValue()) ;           \
  if (!login_is_string)                                                               \
    Trace::TraceTypeMismatch(CONFIG::SERVER_KEY  , CONFIG::LOGIN_KEY                , \
                             CONFIG::STRING_TYPE , this->login.getValue()) ;          \
  if (!pass_is_string)                                                                \
    Trace::TraceTypeMismatch(CONFIG::SERVER_KEY  , CONFIG::PASS_KEY                 , \
                             CONFIG::STRING_TYPE , this->pass.getValue()) ;           \
  if (!is_anon_is_bool)                                                               \
    Trace::TraceTypeMismatch(CONFIG::SERVER_KEY  , CONFIG::IS_ANON_KEY              , \
                             CONFIG::BOOL_TYPE   , this->isAnonymous.getValue()) ;    \
  if (!is_agreed_is_bool)                                                             \
    Trace::TraceTypeMismatch(CONFIG::SERVER_KEY  , CONFIG::IS_AGREED_KEY            , \
                             CONFIG::BOOL_TYPE   , this->isAgreed.getValue()) ;       \
  if (!should_agree_is_bool)                                                          \
    Trace::TraceTypeMismatch(CONFIG::SERVER_KEY  , CONFIG::SHOULD_AGREE_KEY         , \
                             CONFIG::BOOL_TYPE   , this->shouldAgree.getValue()) ;    \
  if (!should_hide_bots_is_bool)                                                      \
    Trace::TraceTypeMismatch(CONFIG::SERVER_KEY  , CONFIG::SHOULD_HIDE_BOTS_KEY     , \
                             CONFIG::BOOL_TYPE   , this->shouldHideBots.getValue()) ;
/*
#define DEBUG_TRACE_SANITY_CHECK_USER                                                \
  String user_name = String(channels.getType()) ;                                    \
  if (!remote_has_useridx_property)                                                  \
    Trace::TraceMissingProperty(user_name , CONFIG::USERIDX_KEY) ;                   \
  if (!remote_has_useridx_property)                                                  \
    Trace::TraceError("destroying invalid remote channel store '" + user_name + "'") ;
*/

#define DEBUG_TRACE_SANITY_CHECK_CHANNEL                                               \
  String channel_name = String(channels.getType()) ;                                   \
  if (!channel_has_channelname_property)                                               \
    Trace::TraceMissingProperty(channel_name , CONFIG::CHANNELNAME_KEY) ;              \
  if (!channel_has_channelidx_property)                                                \
    Trace::TraceMissingProperty(channel_name , CONFIG::CHANNELIDX_KEY) ;               \
  if (!channel_has_volume_property)                                                    \
    Trace::TraceMissingProperty(channel_name , CONFIG::VOLUME_KEY) ;                   \
  if (!channel_has_pan_property)                                                       \
    Trace::TraceMissingProperty(channel_name , CONFIG::PAN_KEY) ;                      \
  if (!channel_has_xmit_property)                                                      \
    Trace::TraceMissingProperty(channel_name , CONFIG::IS_XMIT_RCV_KEY) ;              \
  if (!channel_has_mute_property)                                                      \
    Trace::TraceMissingProperty(channel_name , CONFIG::IS_MUTED_KEY) ;                 \
  if (!channel_has_solo_property)                                                      \
    Trace::TraceMissingProperty(channel_name , CONFIG::IS_SOLO_KEY) ;                  \
  if (!channel_has_source_property)                                                    \
    Trace::TraceMissingProperty(channel_name , CONFIG::SOURCE_N_KEY) ;                 \
  if (!channel_has_stereo_property)                                                    \
    Trace::TraceMissingProperty(channel_name , CONFIG::STEREO_KEY) ;                   \
                                                                                       \
  if (!channel_name_is_string)                                                         \
    Trace::TraceTypeMismatch(channel_name , CONFIG::CHANNELNAME_KEY ,                  \
                             CONFIG::STRING_TYPE , channel[CONFIG::CHANNELNAME_ID]) ;  \
  if (!channel_idx_is_int)                                                             \
    Trace::TraceTypeMismatch(channel_name , CONFIG::CHANNELIDX_KEY  ,                  \
                             CONFIG::INT_TYPE    , channel[CONFIG::CHANNELIDX_ID]) ;   \
  if (!channel_volume_is_double)                                                       \
    Trace::TraceTypeMismatch(channel_name , CONFIG::VOLUME_KEY      ,                  \
                             CONFIG::DOUBLE_TYPE , channel[CONFIG::VOLUME_ID]) ;       \
  if (!channel_pan_is_double)                                                          \
    Trace::TraceTypeMismatch(channel_name , CONFIG::PAN_KEY         ,                  \
                             CONFIG::DOUBLE_TYPE , channel[CONFIG::PAN_ID]) ;          \
  if (!channel_xmit_is_bool)                                                           \
    Trace::TraceTypeMismatch(channel_name , CONFIG::IS_XMIT_RCV_KEY ,                  \
                             CONFIG::BOOL_TYPE   , channel[CONFIG::IS_XMIT_RCV_ID]) ;  \
  if (!channel_mute_is_bool)                                                           \
    Trace::TraceTypeMismatch(channel_name , CONFIG::IS_MUTED_KEY    ,                  \
                             CONFIG::BOOL_TYPE   , channel[CONFIG::IS_MUTED_ID]) ;     \
  if (!channel_solo_is_bool)                                                           \
    Trace::TraceTypeMismatch(channel_name , CONFIG::IS_SOLO_KEY     ,                  \
                             CONFIG::BOOL_TYPE   , channel[CONFIG::IS_SOLO_ID]) ;      \
  if (!channel_source_is_int)                                                          \
    Trace::TraceTypeMismatch(channel_name , CONFIG::SOURCE_N_KEY    ,                  \
                             CONFIG::INT_TYPE    , channel[CONFIG::SOURCE_N_ID]) ;     \
  if (!channel_stereo_is_int)                                                          \
    Trace::TraceTypeMismatch(channel_name , CONFIG::STEREO_KEY   ,                     \
                             CONFIG::INT_TYPE   , channel[CONFIG::STEREO_ID]) ;        \
                                                                                       \
  if (!channel_has_channelname_property || !channel_has_channelidx_property ||         \
      !channel_has_volume_property      || !channel_has_pan_property        ||         \
      !channel_has_xmit_property        || !channel_has_mute_property       ||         \
      !channel_has_solo_property        || !channel_has_source_property     ||         \
      !channel_has_stereo_property                                           )         \
    Trace::TraceError("destroying invalid local channel store '" + channel_name + "'") ;

#if TRACE_STORE_CONFIG_VB
#  define DEBUG_TRACE_STORE_CONFIG Trace::TraceConfig("storing config xml=\n" +      \
                                                      configValueTree.toXmlString()) ;
#else // TRACE_STORE_CONFIG_VB
#  define DEBUG_TRACE_STORE_CONFIG Trace::TraceConfig("storing config xml") ;
#endif // TRACE_STORE_CONFIG_VB

#define DEBUG_TRACE_CONFIG_TREE_CHANGED                       \
  String node   = String(a_node.getType()) ;                  \
  String parent = String(a_node.getParent().getType()) ;      \
  String key    = String(a_key) ;                             \
  String val    = a_node[a_key].toString() ;                  \
  Trace::TraceConfig("value changed for " + parent + " => " + \
                     node + "[" + key + "] => " + val) ;


/* channels */

#define DEBUG_TRACE_MONO_STATUS                                                         \
  bool   is_new    = !getChannelByName(user_store , channel_name).isValid() ;           \
  String pair_name = (has_l_pair)? l_pair_name : l_pair_name ;                          \
  if (has_orphaned_pair) Trace::TraceConfig("setting remote channel '" + pair_name    + \
                                            "' status to MONO") ;                       \
  if (is_new)            Trace::TraceConfig("adding remote channel '"  + channel_name + \
                                            "' as MONO") ;                              \
  else                   Trace::TraceConfig("setting remote channel '" + channel_name + \
                                            "' status to MONO") ;

#define DEBUG_TRACE_STEREO_STATUS                                                     \
  bool   is_new      = !getChannelByName(user_store , channel_name).isValid() ;       \
  String status      = (stereo_status == CONFIG::STEREO_L)? "STEREO_L" : "STEREO_R" ; \
  String pair_status = (pair_stereo_status == CONFIG::STEREO_L)?                      \
                       "STEREO_L" : "STEREO_R" ;                                      \
  String pair_error  = (!is_paired)? " (unpaired)" : "" ;                             \
  if (is_paired) Trace::TraceConfig("setting remote channel '" + pair_name          + \
                                    "' status to " + pair_status) ;                   \
  if (is_new)    Trace::TraceConfig("adding remote channel '"  + channel_name       + \
                                    "' as " + status) ;                               \
  else           Trace::TraceConfig("setting remote channel '" + channel_name       + \
                                    "' status to " + status) ;

#define DEBUG_TRACE_ADD_CHANNEL_STORE                                               \
  String user_id      = String(channels_store.getType()) ;                          \
  String channel_id   = String(makeChannelId(channel_idx)) ;                        \
  String channel_name = LinJam::GetStoredChannelName(new_node) ;                    \
  bool   is_local     = channels_store == this->localChannels ;                     \
  String group        = (is_local)? "local" : "remote" ;                            \
  String dbgA         = "created storage for new " ;                                \
  String dbgB         = group + " " + channel_id + " '" + channel_name + "'" ;      \
  if      (!channels_store.isValid())                                               \
       Trace::TraceError("invlaid parent creating channel storage for '" + dbgB) ;  \
  else if (!new_node.isValid())                                                     \
       Trace::TraceError("invlaid node creating " + user_id + " channel storage") ; \
  if (new_node.getParent() == channels_store)                                       \
       Trace::TraceConfig("storage already exists for " + dbgB) ;                   \
  else if (is_local)                                                                \
       Trace::TraceConfig(dbgA + dbgB) ;                                            \
  else Trace::TraceConfig(dbgA + dbgB + " for '" + user_id + "'") ;

#define DEBUG_TRACE_DESTROY_CHANNEL_STORE                                   \
  String channel_id   = String(channel_store.getType()) ;                   \
  String channel_name = channel_store[CONFIG::CHANNELNAME_ID].toString() ;  \
  String user_id      = String(channels_store.getType()) ;                  \
  String dbgA         = "destroyed storage for " ;                          \
  String dbgB         = " " + channel_id + " '" + channel_name + "' " ;     \
  if (channels_store == this->localChannels)                                \
       Trace::TraceConfig(dbgA + "local"  + dbgB) ;                         \
  else Trace::TraceConfig(dbgA + "remote" + dbgB + "for '" + user_id + "'") ;

#define DEBUG_TRACE_ADD_REMOTE_USER_STORE                                        \
  Trace::TraceEvent("user joined => '" + String(user_id) + "'") ;                \
  Trace::TraceConfig("created storage for new remote user " + String(user_id)) ; \
  if (TRACE_ADD_REMOTES_VB)                                                      \
  {                                                                              \
    char*      host      = LinJam::Client->GetHostName() ;                       \
    bool       has_bot   = NETWORK::KNOWN_HOSTS.contains(String(host)) ;         \
    bool       hide_bots = has_bot && bool(this->shouldHideBots.getValue()) ;    \
    float      u_vol     = CONFIG::DEFAULT_VOLUME ;                              \
    bool       u_mute    = CONFIG::DEFAULT_IS_MUTED ;                            \
    float      u_pan     = CONFIG::DEFAULT_PAN ;                                 \
    int        u_idx     = -1 ; String u_name ; Identifier u_id ;                \
    while ((u_name = LinJam::GetRemoteUserName(++u_idx)).isNotEmpty())           \
      { u_id = makeUserId(u_name , u_idx) ; if (user_id == u_id) break ; }       \
    DEBUG_TRACE_REMOTE_CHANNELS                                                  \
  }

