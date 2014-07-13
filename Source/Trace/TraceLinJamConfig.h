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
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::IS_STEREO_KEY) ;         \
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
/*
#define DEBUG_TRACE_SANITY_CHECK_USER                                                 \
  String user_name = String(channels.getType()) ;                                     \
  if (!remote_has_useridx_property)                                                   \
    Trace::TraceMissingProperty(user_name , CONFIG::USERIDX_KEY) ;                    \
  if (!remote_has_useridx_property)                                                   \
    Trace::TraceError("destroying invalid remote channel store '" + user_name + "'") ;
*/

#define DEBUG_TRACE_SANITY_CHECK_CHANNEL                                                 \
  String channel_name = String(channels.getType()) ;                                   \
  if (!channel_has_channelidx_property)                                                \
    Trace::TraceMissingProperty(channel_name , CONFIG::CHANNELIDX_KEY) ;               \
  if (!channel_has_volume_property)                                                    \
    Trace::TraceMissingProperty(channel_name , CONFIG::VOLUME_KEY) ;                   \
  if (!channel_has_pan_property)                                                       \
    Trace::TraceMissingProperty(channel_name , CONFIG::PAN_KEY) ;                      \
  if (!channel_has_xmit_property)                                                      \
    Trace::TraceMissingProperty(channel_name , CONFIG::IS_XMIT_KEY) ;                  \
  if (!channel_has_mute_property)                                                      \
    Trace::TraceMissingProperty(channel_name , CONFIG::IS_MUTED_KEY) ;                 \
  if (!channel_has_solo_property)                                                      \
    Trace::TraceMissingProperty(channel_name , CONFIG::IS_SOLO_KEY) ;                  \
  if (!channel_has_source_property)                                                    \
    Trace::TraceMissingProperty(channel_name , CONFIG::SOURCE_N_KEY) ;                 \
  if (!channel_has_stereo_property)                                                    \
    Trace::TraceMissingProperty(channel_name , CONFIG::IS_STEREO_KEY) ;                \
  if (!channel_has_channelidx_property || !channel_has_volume_property ||              \
      !channel_has_pan_property        || !channel_has_xmit_property   ||              \
      !channel_has_mute_property       || !channel_has_solo_property   ||              \
      !channel_has_source_property     || !channel_has_stereo_property  )              \
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

#define DEBUG_TRACE_CONFIG_TREE_ADDED                                       \
  Trace::TraceEvent("node '" + String(a_child_node.getType()) +             \
                    "' added to '" + String(a_parent_node.getType()) + "'") ;

#define DEBUG_TRACE_CONFIG_TREE_REMOVED                                         \
  Trace::TraceEvent("node '" + String(a_child_node.getType()) +                 \
                    "' removed from '" + String(a_parent_node.getType()) + "'") ;


/* channels */

#define DEBUG_TRACE_ADD_CHANNEL_STORE                                       \
  String dbgA = "created storage for new " ;                                \
  String dbgB = " " + String(channel_id) + " '" + channel_name + "' " ;     \
  if (channels_id == CONFIG::LOCALS_ID)                                     \
       Trace::TraceConfig(dbgA + "local"  + dbgB) ;                         \
  else Trace::TraceConfig(dbgA + "remote" + dbgB + "for '" +                \
                          String(getUserById(channels_id).getType()) + "'") ;

#define DEBUG_TRACE_ADD_REMOTE_USER_STORE                                          \
  Trace::TraceConfig("created storage for new remote user " + String(user_id)) ;   \
  if (TRACE_ADD_REMOTES_VB)                                                        \
  {                                                                                \
    char*      host      = LinJam::Client->GetHostName() ;                         \
    bool       has_bot   = NETWORK::KNOWN_HOSTS.contains(String(host)) ;           \
    bool       hide_bots = has_bot && bool(this->shouldHideBots.getValue()) ;      \
    float      u_vol     = volume ;                                                \
    float      u_pan     = pan ;                                                   \
    bool       u_mute    = is_muted ;                                              \
    int        u_idx     = -1 ; String u_name ; Identifier u_id ;                  \
    while ((u_name = LinJam::GetRemoteUserName(++u_idx)).isNotEmpty())             \
      { u_id = encodeUserId(u_name , u_idx) ; if (user_id == u_id) break ; }       \
    DEBUG_TRACE_REMOTE_CHANNELS                                                    \
  }

