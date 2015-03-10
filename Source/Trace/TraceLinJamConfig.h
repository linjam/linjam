#if DEBUG

#  include "Trace.h"
#  include "TraceLinJam.h"


/* storage */

#define DEBUG_TRACE_LOAD_CONFIG                                                   \
  Identifier root_node_id = CONFIG::PERSISTENCE_ID ;                              \
  if (default_xml == nullptr || !default_xml->hasTagName(root_node_id))           \
      Trace::TraceConfig("default config invalid - bailing") ;                    \
  else Trace::TraceConfig("default config loaded") ;                              \
  if (stored_xml == nullptr)                                                      \
      Trace::TraceConfig("stored config not found - falling back on defaults") ;  \
  else if (!stored_xml->hasTagName(CONFIG::PERSISTENCE_ID))                       \
      Trace::TraceConfig("stored config is invalid - falling back on defaults") ; \
  else Trace::TraceConfig("stored config found") ;

#if TRACE_SANITIZE_CONFIG
#  define DEBUG_TRACE_SANITIZE_CONFIG                                              \
  if (has_stored_config)                                                           \
    Trace::TraceConfig("stored config parsed successfully => " +                   \
                       Trace::DumpConfig(ValueTree::fromXml(*default_xml) ,        \
                                         ValueTree::fromXml(*stored_xml)  , "  ")) ;
#else // TRACE_SANITIZE_CONFIG
#  define DEBUG_TRACE_SANITIZE_CONFIG ;
#endif // TRACE_SANITIZE_CONFIG

#if TRACE_CONFIG_TYPES
#  define DEBUG_TRACE_CONFIG_TYPES_VB                                                    \
  String parent_id = (node_id == CONFIG::PERSISTENCE_ID)             ? "root " :         \
                     (grandparent_node == this->remoteUsers)                   ?         \
                     CONFIG::REMOTES_KEY + " " + String(parent_node.getType()) :         \
                     String(parent_node.getType())                             ;         \
  if (parent_node == this->servers        ||                                             \
      parent_node == this->masterChannels ||                                             \
      parent_node == this->localChannels)                                                \
    parent_id = String(parent_node.getType()) ; /* KLUDGE: (issue #33) */                \
  Trace::TraceConfig("restoring types - " + parent_id + " " + String(node_id)          + \
                     " (" + String(config_store.getNumProperties()) + " properties - " + \
                     String(config_store.getNumChildren())     + " children)") ;
#  define DEBUG_TRACE_CONFIG_TYPES_VB_EACH                                         \
  bool   is_valid = is_bool || is_double || is_int || is_string ;                  \
  String type     = (is_valid) ? Trace::VarType(config_store[key]) : "(deleted)" ; \
  Trace::TraceConfig("  " + String(key) + " => " + type) ;
#else // TRACE_CONFIG_TYPES
#  define DEBUG_TRACE_CONFIG_TYPES_VB ;
#  define DEBUG_TRACE_CONFIG_TYPES_VB_EACH ;
#endif // TRACE_CONFIG_TYPES

#define DEBUG_TRACE_SANITY_CHECK                                                         \
  /* NOTE: these checks normally should be unnecessary                        */         \
  /*       all tree nodes and properties will exist after sanitizeConfig()    */         \
  /*       and will be of the proper types after restoreVarTypeInfo()         */         \
  /*       only transient channels are not sanitized and so need be validated */         \
                                                                                         \
  ValueTree root   = this->configValueTree ;                                             \
  ValueTree client = this->client ;                                                      \
  ValueTree subs   = this->subscriptions ;                                               \
  ValueTree audio  = this->audio ;                                                       \
  ValueTree server = this->server ;                                                      \
  ValueTree master = this->masterChannels.getChildWithName(CONFIG::MASTER_ID) ;          \
  ValueTree metro  = this->masterChannels.getChildWithName(CONFIG::METRO_ID) ;           \
                                                                                         \
  /* query default values */                                                             \
  bool has_valid_version_declaration    =  CONFIG::CONFIG_VERSION > 0.0 ;                \
  bool has_valid_sessiondir_declaration = !CLIENT::SESSION_DIR.isEmpty() ;               \
  bool has_valid_logfile_declaration    = !CLIENT::LOG_FILE.isEmpty() ;                  \
                                                                                         \
  /* query root properties */                                                            \
  bool root_has_appversion_property        =                                             \
      root.hasProperty(CONFIG::CONFIG_VERSION_ID)  ;                                     \
                                                                                         \
  /* query client properties */                                                          \
  bool client_has_saveaudio_property       =                                             \
      client.hasProperty(CONFIG::SAVE_AUDIO_MODE_ID)  ;                                  \
  bool client_has_mixdown_property         =                                             \
      client.hasProperty(CONFIG::MIXDOWN_MODE_KEY)    ;                                  \
  bool client_has_savelog_property         =                                             \
      client.hasProperty(CONFIG::SHOULD_SAVE_LOG_ID)  ;                                  \
  bool client_has_debuglevel_property      =                                             \
      client.hasProperty(CONFIG::DEBUG_LEVEL_ID)      ;                                  \
  bool client_has_hide_bots_property       =                                             \
      client.hasProperty(CONFIG::SHOULD_HIDE_BOTS_ID) ;                                  \
                                                                                         \
  /* query subscriptions properties */                                                   \
  bool subs_has_autosubscribe_property     =                                             \
      subs.hasProperty(CONFIG::SUBSCRIBE_MODE_ID)     ;                                  \
                                                                                         \
  /* query audio properties */                                                           \
  bool audio_has_winifn_property           =                                             \
      audio .hasProperty(CONFIG::WIN_AUDIO_IF_ID)     ;                                  \
  bool audio_has_asiodriver_property       =                                             \
      audio .hasProperty(CONFIG::ASIO_DRIVER_ID)      ;                                  \
  bool audio_has_asioinput0_property       =                                             \
      audio .hasProperty(CONFIG::ASIO_INPUT0_ID)      ;                                  \
  bool audio_has_asioinput1_property       =                                             \
      audio .hasProperty(CONFIG::ASIO_INPUT1_ID)      ;                                  \
  bool audio_has_asiooutput0_property      =                                             \
      audio .hasProperty(CONFIG::ASIO_OUTPUT0_ID)     ;                                  \
  bool audio_has_asiooutput1_property      =                                             \
      audio .hasProperty(CONFIG::ASIO_OUTPUT1_ID)     ;                                  \
  bool audio_has_ksinput_property          =                                             \
      audio .hasProperty(CONFIG::KS_INPUT_ID)         ;                                  \
  bool audio_has_ksoutput_property         =                                             \
      audio .hasProperty(CONFIG::KS_OUTPUT_ID)        ;                                  \
  bool audio_has_kssamplerate_property     =                                             \
      audio .hasProperty(CONFIG::KS_SAMPLERATE_ID)    ;                                  \
  bool audio_has_ksbitdepth_property       =                                             \
      audio .hasProperty(CONFIG::KS_BITDEPTH_ID)      ;                                  \
  bool audio_has_ksnblocks_property        =                                             \
      audio .hasProperty(CONFIG::KS_NBLOCKS_ID)       ;                                  \
  bool audio_has_ksblocksize_property      =                                             \
      audio .hasProperty(CONFIG::KS_BLOCKSIZE_ID)     ;                                  \
  bool audio_has_dsinput0_property         =                                             \
      audio .hasProperty(CONFIG::DS_INPUT0_ID)        ;                                  \
  bool audio_has_dsinput1_property         =                                             \
      audio .hasProperty(CONFIG::DS_INPUT1_ID)        ;                                  \
  bool audio_has_dsinput2_property         =                                             \
      audio .hasProperty(CONFIG::DS_INPUT2_ID)        ;                                  \
  bool audio_has_dsinput3_property         =                                             \
      audio .hasProperty(CONFIG::DS_INPUT3_ID)        ;                                  \
  bool audio_has_dsoutput0_property        =                                             \
      audio .hasProperty(CONFIG::DS_OUTPUT0_ID)       ;                                  \
  bool audio_has_dsoutput1_property        =                                             \
      audio .hasProperty(CONFIG::DS_OUTPUT1_ID)       ;                                  \
  bool audio_has_dsoutput2_property        =                                             \
      audio .hasProperty(CONFIG::DS_OUTPUT2_ID)       ;                                  \
  bool audio_has_dsoutput3_property        =                                             \
      audio .hasProperty(CONFIG::DS_OUTPUT3_ID)       ;                                  \
  bool audio_has_dssamplerate_property     =                                             \
      audio .hasProperty(CONFIG::DS_SAMPLERATE_ID)    ;                                  \
  bool audio_has_dsbitdepth_property       =                                             \
      audio .hasProperty(CONFIG::DS_BITDEPTH_ID)      ;                                  \
  bool audio_has_dsnblocks_property        =                                             \
      audio .hasProperty(CONFIG::DS_NBLOCKS_ID)       ;                                  \
  bool audio_has_dsblocksize_property      =                                             \
      audio .hasProperty(CONFIG::DS_BLOCKSIZE_ID)     ;                                  \
  bool audio_has_waveinput_property        =                                             \
      audio .hasProperty(CONFIG::WAVE_INPUT_ID)       ;                                  \
  bool audio_has_waveoutput_property       =                                             \
      audio .hasProperty(CONFIG::WAVE_OUTPUT_ID)      ;                                  \
  bool audio_has_wavesamplerate_property   =                                             \
      audio .hasProperty(CONFIG::WAVE_SAMPLERATE_ID)  ;                                  \
  bool audio_has_wavebitdepth_property     =                                             \
      audio .hasProperty(CONFIG::WAVE_BITDEPTH_ID)    ;                                  \
  bool audio_has_wavenblocks_property      =                                             \
      audio .hasProperty(CONFIG::WAVE_NBLOCKS_ID)     ;                                  \
  bool audio_has_waveblocksize_property    =                                             \
      audio .hasProperty(CONFIG::WAVE_BLOCKSIZE_ID)   ;                                  \
  bool audio_has_macdevice_property        =                                             \
      audio .hasProperty(CONFIG::MAC_DEVICE_ID)       ;                                  \
  bool audio_has_macninputs_property       =                                             \
      audio .hasProperty(CONFIG::MAC_NINPUTS_ID)      ;                                  \
  bool audio_has_macsamplerate_property    =                                             \
      audio .hasProperty(CONFIG::MAC_SAMPLERATE_ID)   ;                                  \
  bool audio_has_macbitdepth_property      =                                             \
      audio .hasProperty(CONFIG::MAC_BITDEPTH_ID)     ;                                  \
  bool audio_has_nixifn_property           =                                             \
      audio .hasProperty(CONFIG::NIX_AUDIO_IF_ID)     ;                                  \
  bool audio_has_jackserver_property       =                                             \
      audio .hasProperty(CONFIG::JACK_SERVER_ID)      ;                                  \
  bool audio_has_jackname_property         =                                             \
      audio .hasProperty(CONFIG::JACK_NAME_ID)        ;                                  \
  bool audio_has_jackninputs_property      =                                             \
      audio .hasProperty(CONFIG::JACK_NINPUTS_ID)     ;                                  \
  bool audio_has_jacknoutputs_property     =                                             \
      audio .hasProperty(CONFIG::JACK_NOUTPUTS_ID)    ;                                  \
  bool audio_has_alsaconfig_property         =                                           \
      audio .hasProperty(CONFIG::ALSA_CONFIG_ID)      ;                                  \
                                                                                         \
  /* query server properties */                                                          \
  bool server_has_host_property            =                                             \
      server.hasProperty(CONFIG::HOST_ID)             ;                                  \
  bool server_has_login_property           =                                             \
      server.hasProperty(CONFIG::LOGIN_ID)            ;                                  \
  bool server_has_pass_property            =                                             \
      server.hasProperty(CONFIG::PASS_ID)             ;                                  \
  bool server_has_is_anonymous_property    =                                             \
      server.hasProperty(CONFIG::IS_ANONYMOUS_ID)     ;                                  \
  bool server_has_is_agreed_property       =                                             \
      server.hasProperty(CONFIG::IS_AGREED_ID)        ;                                  \
  bool server_has_should_agree_property    =                                             \
      server.hasProperty(CONFIG::SHOULD_AGREE_ID)     ;                                  \
                                                                                         \
  /* query masters properties */                                                         \
  bool master_channel_has_name_property    =                                             \
      master.hasProperty(CONFIG::CHANNEL_NAME_ID)     ;                                  \
  bool master_channel_has_volume_property  =                                             \
      master.hasProperty(CONFIG::VOLUME_ID)           ;                                  \
  bool master_channel_has_pan_property     =                                             \
      master.hasProperty(CONFIG::PAN_ID)              ;                                  \
  bool master_channel_has_mute_property    =                                             \
      master.hasProperty(CONFIG::IS_MUTED_ID)         ;                                  \
  bool master_channel_has_stereo_property  =                                             \
      master.hasProperty(CONFIG::STEREO_ID)           ;                                  \
  bool master_channel_has_vuleft_property  =                                             \
      master.hasProperty(CONFIG::VU_LEFT_ID)          ;                                  \
  bool master_channel_has_vuright_property =                                             \
      master.hasProperty(CONFIG::VU_RIGHT_ID)         ;                                  \
  bool metro_channel_has_name_property     =                                             \
      metro .hasProperty(CONFIG::CHANNEL_NAME_ID)     ;                                  \
  bool metro_channel_has_volume_property   =                                             \
      metro .hasProperty(CONFIG::VOLUME_ID)           ;                                  \
  bool metro_channel_has_pan_property      =                                             \
      metro .hasProperty(CONFIG::PAN_ID)              ;                                  \
  bool metro_channel_has_mute_property     =                                             \
      metro .hasProperty(CONFIG::IS_MUTED_ID)         ;                                  \
  bool metro_channel_has_source_property   =                                             \
      metro .hasProperty(CONFIG::SOURCE_N_ID)         ;                                  \
  bool metro_channel_has_stereo_property   =                                             \
      metro .hasProperty(CONFIG::STEREO_ID)           ;                                  \
  bool metro_channel_has_vuleft_property   =                                             \
      metro .hasProperty(CONFIG::VU_LEFT_ID)          ;                                  \
  bool metro_channel_has_vuright_property  =                                             \
      metro .hasProperty(CONFIG::VU_RIGHT_ID)         ;                                  \
                                                                                         \
                                                                                         \
  /* query root datatypes */                                                             \
  bool app_version_is_double    = root  [CONFIG::CONFIG_VERSION_ID]     .isDouble() ;    \
                                                                                         \
  /* query client datatypes */                                                           \
  bool save_audio_is_int        = client[CONFIG::SAVE_AUDIO_MODE_ID] .isInt()    ;       \
  bool mixdown_is_int           = client[CONFIG::MIXDOWN_MODE_KEY]   .isInt()    ;       \
  bool save_log_is_bool         = client[CONFIG::SHOULD_SAVE_LOG_ID] .isBool()   ;       \
  bool debug_level_is_int       = client[CONFIG::DEBUG_LEVEL_ID]     .isInt()    ;       \
  bool should_hide_bots_is_bool = client[CONFIG::SHOULD_HIDE_BOTS_ID].isBool()   ;       \
                                                                                         \
  /* query subscriptions datatypes */                                                    \
  bool autosubscribe_is_int     = subs  [CONFIG::SUBSCRIBE_MODE_ID]  .isInt()    ;       \
                                                                                         \
  /* query audio datatypes */                                                            \
  bool win_audio_ifn_is_int     = audio [CONFIG::WIN_AUDIO_IF_ID]    .isInt()    ;       \
  bool asio_driver_is_int       = audio [CONFIG::ASIO_DRIVER_ID]     .isInt()    ;       \
  bool asio_input0_is_int       = audio [CONFIG::ASIO_INPUT0_ID]     .isInt()    ;       \
  bool asio_inout1_is_int       = audio [CONFIG::ASIO_INPUT1_ID]     .isInt()    ;       \
  bool asio_output0_is_int      = audio [CONFIG::ASIO_OUTPUT0_ID]    .isInt()    ;       \
  bool asio_output1_is_int      = audio [CONFIG::ASIO_OUTPUT1_ID]    .isInt()    ;       \
  bool ks_input_is_int          = audio [CONFIG::KS_INPUT_ID]        .isInt()    ;       \
  bool ks_output_is_int         = audio [CONFIG::KS_OUTPUT_ID]       .isInt()    ;       \
  bool ks_samplerate_is_int     = audio [CONFIG::KS_SAMPLERATE_ID]   .isInt()    ;       \
  bool ks_bitdepth_is_int       = audio [CONFIG::KS_BITDEPTH_ID]     .isInt()    ;       \
  bool ks_n_blocks_is_int       = audio [CONFIG::KS_NBLOCKS_ID]      .isInt()    ;       \
  bool ks_blocksize_is_int      = audio [CONFIG::KS_BLOCKSIZE_ID]    .isInt()    ;       \
  bool ds_input0_is_int         = audio [CONFIG::DS_INPUT0_ID]       .isInt()    ;       \
  bool ds_input1_is_int         = audio [CONFIG::DS_INPUT1_ID]       .isInt()    ;       \
  bool ds_input2_is_int         = audio [CONFIG::DS_INPUT2_ID]       .isInt()    ;       \
  bool ds_input3_is_int         = audio [CONFIG::DS_INPUT3_ID]       .isInt()    ;       \
  bool ds_output0_is_int        = audio [CONFIG::DS_OUTPUT0_ID]      .isInt()    ;       \
  bool ds_output1_is_int        = audio [CONFIG::DS_OUTPUT1_ID]      .isInt()    ;       \
  bool ds_output2_is_int        = audio [CONFIG::DS_OUTPUT2_ID]      .isInt()    ;       \
  bool ds_output3_is_int        = audio [CONFIG::DS_OUTPUT3_ID]      .isInt()    ;       \
  bool ds_samplerate_is_int     = audio [CONFIG::DS_SAMPLERATE_ID]   .isInt()    ;       \
  bool ds_bitdepth_is_int       = audio [CONFIG::DS_BITDEPTH_ID]     .isInt()    ;       \
  bool ds_n_blocks_is_int       = audio [CONFIG::DS_NBLOCKS_ID]      .isInt()    ;       \
  bool ds_blocksize_is_int      = audio [CONFIG::DS_BLOCKSIZE_ID]    .isInt()    ;       \
  bool wave_input_is_int        = audio [CONFIG::WAVE_INPUT_ID]      .isInt()    ;       \
  bool wave_output_is_int       = audio [CONFIG::WAVE_OUTPUT_ID]     .isInt()    ;       \
  bool wave_samplerate_is_int   = audio [CONFIG::WAVE_SAMPLERATE_ID] .isInt()    ;       \
  bool wave_bitdepth_is_int     = audio [CONFIG::WAVE_BITDEPTH_ID]   .isInt()    ;       \
  bool wave_n_blocks_is_int     = audio [CONFIG::WAVE_NBLOCKS_ID]    .isInt()    ;       \
  bool wave_blocksize_is_int    = audio [CONFIG::WAVE_BLOCKSIZE_ID]  .isInt()    ;       \
  bool mac_device_is_string     = audio [CONFIG::MAC_DEVICE_ID]      .isString() ;       \
  bool mac_n_inputs_is_int      = audio [CONFIG::MAC_NINPUTS_ID]     .isInt()    ;       \
  bool mac_samplerate_is_int    = audio [CONFIG::MAC_SAMPLERATE_ID]  .isInt()    ;       \
  bool mac_bitdepth_is_int      = audio [CONFIG::MAC_BITDEPTH_ID]    .isInt()    ;       \
  bool nix_audio_ifn_is_int     = audio [CONFIG::NIX_AUDIO_IF_ID]    .isInt()    ;       \
  bool jack_server_is_int       = audio [CONFIG::JACK_SERVER_ID]     .isInt()    ;       \
  bool jack_name_is_string      = audio [CONFIG::JACK_NAME_ID]       .isString() ;       \
  bool jack_n_inputs_is_int     = audio [CONFIG::JACK_NINPUTS_ID]    .isInt()    ;       \
  bool jack_n_outputs_is_int    = audio [CONFIG::JACK_NOUTPUTS_ID]   .isInt()    ;       \
  bool alsa_config_is_string    = audio [CONFIG::ALSA_CONFIG_ID]     .isString() ;       \
                                                                                         \
  /* query server datatypes */                                                           \
  bool host_name_is_string      = server[CONFIG::HOST_ID]            .isString() ;       \
  bool login_is_string          = server[CONFIG::LOGIN_ID]           .isString() ;       \
  bool pass_is_string           = server[CONFIG::PASS_ID]            .isString() ;       \
  bool is_anon_is_bool          = server[CONFIG::IS_ANONYMOUS_ID]    .isBool()   ;       \
  bool is_agreed_is_bool        = server[CONFIG::IS_AGREED_ID]       .isBool()   ;       \
  bool should_agree_is_bool     = server[CONFIG::SHOULD_AGREE_ID]    .isBool()   ;       \
                                                                                         \
  /* query masters datatypes */                                                          \
  bool master_name_is_string    = master[CONFIG::CHANNEL_NAME_ID]    .isString() ;       \
  bool master_volume_is_double  = master[CONFIG::VOLUME_ID]          .isDouble() ;       \
  bool master_pan_is_double     = master[CONFIG::PAN_ID]             .isDouble() ;       \
  bool master_mute_is_bool      = master[CONFIG::IS_MUTED_ID]        .isBool()   ;       \
  bool master_stereo_is_int     = master[CONFIG::STEREO_ID]          .isInt()    ;       \
  bool master_vuleft_is_double  = master[CONFIG::VU_LEFT_ID]         .isDouble() ;       \
  bool master_vuright_is_double = master[CONFIG::VU_RIGHT_ID]        .isDouble() ;       \
  bool metro_name_is_string     = metro [CONFIG::CHANNEL_NAME_ID]    .isString() ;       \
  bool metro_volume_is_double   = metro [CONFIG::VOLUME_ID]          .isDouble() ;       \
  bool metro_pan_is_double      = metro [CONFIG::PAN_ID]             .isDouble() ;       \
  bool metro_mute_is_bool       = metro [CONFIG::IS_MUTED_ID]        .isBool()   ;       \
  bool metro_source_is_int      = metro [CONFIG::SOURCE_N_ID]        .isInt()    ;       \
  bool metro_stereo_is_int      = metro [CONFIG::STEREO_ID]          .isInt()    ;       \
  bool metro_vuleft_is_double   = metro [CONFIG::VU_LEFT_ID]         .isDouble() ;       \
  bool metro_vuright_is_double  = metro [CONFIG::VU_RIGHT_ID]        .isDouble() ;       \
                                                                                         \
                                                                                         \
  /* trace subscribed sub-trees */                                                       \
  if (!root_is_valid)                                                                    \
    Trace::TraceInvalidNode(CONFIG::PERSISTENCE_KEY) ;                                   \
  if (!client_is_valid)                                                                  \
    Trace::TraceInvalidNode(CONFIG::CLIENT_KEY) ;                                        \
  if (!subscriptions_is_valid)                                                           \
    Trace::TraceInvalidNode(CONFIG::SUBSCRIPTIONS_KEY) ;                                 \
  if (!audio_is_valid)                                                                   \
    Trace::TraceInvalidNode(CONFIG::AUDIO_KEY) ;                                         \
  if (!server_is_valid)                                                                  \
    Trace::TraceInvalidNode(CONFIG::SERVER_KEY) ;                                        \
  if (!servers_is_valid)                                                                 \
    Trace::TraceInvalidNode(CONFIG::SERVERS_KEY) ;                                       \
  if (!master_channels_is_valid)                                                         \
    Trace::TraceInvalidNode(CONFIG::MASTERS_KEY) ;                                       \
  if (!local_channels_is_valid)                                                          \
    Trace::TraceInvalidNode(CONFIG::LOCALS_KEY) ;                                        \
  if (!remote_users_is_valid)                                                            \
    Trace::TraceInvalidNode(CONFIG::REMOTES_KEY) ;                                       \
                                                                                         \
                                                                                         \
  /* trace invalid default values */                                                     \
  if (!has_valid_version_declaration)                                                    \
    Trace::TraceInvalidDefault(CONFIG::CONFIG_VERSION_KEY) ;                             \
  if (!has_valid_sessiondir_declaration)                                                 \
    Trace::TraceInvalidDefault("CLIENT::SESSION_DIR") ;                                  \
  if (!has_valid_logfile_declaration)                                                    \
    Trace::TraceInvalidDefault("CLIENT::LOG_FILE") ;                                     \
                                                                                         \
  /* trace missing root properties */                                                    \
  if (!root_has_appversion_property)                                                     \
    Trace::TraceMissingProperty(CONFIG::PERSISTENCE_KEY , CONFIG::CONFIG_VERSION_KEY) ;  \
                                                                                         \
  /* trace missing client properties */                                                  \
  if (!client_has_saveaudio_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::CLIENT_KEY , CONFIG::SAVE_AUDIO_MODE_KEY) ;      \
  if (!client_has_mixdown_property)                                                      \
    Trace::TraceMissingProperty(CONFIG::CLIENT_KEY , CONFIG::MIXDOWN_MODE_KEY) ;         \
  if (!client_has_savelog_property)                                                      \
    Trace::TraceMissingProperty(CONFIG::CLIENT_KEY , CONFIG::SHOULD_SAVE_LOG_KEY) ;      \
  if (!client_has_debuglevel_property)                                                   \
    Trace::TraceMissingProperty(CONFIG::CLIENT_KEY , CONFIG::DEBUG_LEVEL_KEY) ;          \
  if (!client_has_hide_bots_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::CLIENT_KEY , CONFIG::SHOULD_HIDE_BOTS_KEY) ;     \
                                                                                         \
  /* trace missing subscriptions properties */                                           \
  if (!subs_has_autosubscribe_property)                                                  \
    Trace::TraceMissingProperty(CONFIG::SUBSCRIPTIONS_KEY , CONFIG::SUBSCRIBE_MODE_KEY) ;\
                                                                                         \
  /* trace missing audio properties */                                                   \
  if (!audio_has_winifn_property)                                                        \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::WIN_AUDIO_IF_KEY) ;          \
  if (!audio_has_asiodriver_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::ASIO_DRIVER_KEY) ;           \
  if (!audio_has_asioinput0_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::ASIO_INPUT0_KEY) ;           \
  if (!audio_has_asioinput1_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::ASIO_INPUT1_KEY) ;           \
  if (!audio_has_asiooutput0_property)                                                   \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::ASIO_OUTPUT0_KEY) ;          \
  if (!audio_has_asiooutput1_property)                                                   \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::ASIO_OUTPUT1_KEY) ;          \
  if (!audio_has_ksinput_property)                                                       \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::KS_INPUT_KEY) ;              \
  if (!audio_has_ksoutput_property)                                                      \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::KS_OUTPUT_KEY) ;             \
  if (!audio_has_ksbitdepth_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::KS_BITDEPTH_KEY) ;           \
  if (!audio_has_kssamplerate_property)                                                  \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::KS_SAMPLERATE_KEY) ;         \
  if (!audio_has_ksnblocks_property)                                                     \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::KS_NBLOCKS_KEY) ;            \
  if (!audio_has_ksblocksize_property)                                                   \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::KS_BLOCKSIZE_KEY) ;          \
  if (!audio_has_dsinput0_property)                                                      \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::DS_INPUT0_KEY) ;             \
  if (!audio_has_dsinput1_property)                                                      \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::DS_INPUT1_KEY) ;             \
  if (!audio_has_dsinput2_property)                                                      \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::DS_INPUT2_KEY) ;             \
  if (!audio_has_dsinput3_property)                                                      \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::DS_INPUT3_KEY) ;             \
  if (!audio_has_dsoutput0_property)                                                     \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::DS_OUTPUT0_KEY) ;            \
  if (!audio_has_dsoutput1_property)                                                     \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::DS_OUTPUT1_KEY) ;            \
  if (!audio_has_dsoutput2_property)                                                     \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::DS_OUTPUT2_KEY) ;            \
  if (!audio_has_dsoutput3_property)                                                     \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::DS_OUTPUT3_KEY) ;            \
  if (!audio_has_dsbitdepth_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::DS_BITDEPTH_KEY) ;           \
  if (!audio_has_dssamplerate_property)                                                  \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::DS_SAMPLERATE_KEY) ;         \
  if (!audio_has_dsnblocks_property)                                                     \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::DS_NBLOCKS_KEY) ;            \
  if (!audio_has_dsblocksize_property)                                                   \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::DS_BLOCKSIZE_KEY) ;          \
  if (!audio_has_waveinput_property)                                                     \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::WAVE_INPUT_KEY) ;            \
  if (!audio_has_waveoutput_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::WAVE_OUTPUT_KEY) ;           \
  if (!audio_has_wavebitdepth_property)                                                  \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::WAVE_BITDEPTH_KEY) ;         \
  if (!audio_has_wavesamplerate_property)                                                \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::WAVE_SAMPLERATE_KEY) ;       \
  if (!audio_has_wavenblocks_property)                                                   \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::WAVE_NBLOCKS_KEY) ;          \
  if (!audio_has_waveblocksize_property)                                                 \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::WAVE_BLOCKSIZE_KEY) ;        \
  if (!audio_has_macdevice_property)                                                     \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::MAC_DEVICE_KEY) ;            \
  if (!audio_has_macninputs_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::MAC_NINPUTS_KEY) ;           \
  if (!audio_has_macbitdepth_property)                                                   \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::MAC_BITDEPTH_KEY) ;          \
  if (!audio_has_macsamplerate_property)                                                 \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::MAC_SAMPLERATE_KEY) ;        \
  if (!audio_has_nixifn_property)                                                        \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::NIX_AUDIO_IF_KEY) ;          \
  if (!audio_has_jackserver_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::JACK_SERVER_KEY) ;           \
  if (!audio_has_jackname_property)                                                      \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::JACK_NAME_KEY) ;             \
  if (!audio_has_jackninputs_property)                                                   \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::JACK_NINPUTS_KEY) ;          \
  if (!audio_has_jacknoutputs_property)                                                  \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::JACK_NOUTPUTS_KEY) ;         \
  if (!audio_has_alsaconfig_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::ALSA_CONFIG_KEY) ;           \
                                                                                         \
  /* trace missing server properties */                                                  \
  if (!server_has_host_property)                                                         \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::HOST_KEY) ;                    \
  if (!server_has_login_property)                                                        \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::LOGIN_KEY) ;                   \
  if (!server_has_pass_property)                                                         \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::PASS_KEY) ;                    \
  if (!server_has_is_anonymous_property)                                                 \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::IS_ANONYMOUS_KEY) ;            \
  if (!server_has_is_agreed_property)                                                    \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::IS_AGREED_KEY) ;               \
  if (!server_has_should_agree_property)                                                 \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::SHOULD_AGREE_KEY) ;            \
                                                                                         \
  /* trace missing masters properties */                                                 \
  if (!master_channel_has_name_property)                                                 \
    Trace::TraceMissingProperty(CONFIG::MASTER_KEY , CONFIG::CHANNEL_NAME_KEY) ;         \
  if (!master_channel_has_volume_property)                                               \
    Trace::TraceMissingProperty(CONFIG::MASTER_KEY , CONFIG::VOLUME_KEY) ;               \
  if (!master_channel_has_pan_property)                                                  \
    Trace::TraceMissingProperty(CONFIG::MASTER_KEY , CONFIG::PAN_KEY) ;                  \
  if (!master_channel_has_mute_property)                                                 \
    Trace::TraceMissingProperty(CONFIG::MASTER_KEY , CONFIG::IS_MUTED_KEY) ;             \
  if (!master_channel_has_stereo_property)                                               \
    Trace::TraceMissingProperty(CONFIG::MASTER_KEY , CONFIG::STEREO_KEY) ;               \
  if (!master_channel_has_vuleft_property)                                               \
    Trace::TraceMissingProperty(CONFIG::MASTER_KEY , CONFIG::VU_LEFT_KEY) ;              \
  if (!master_channel_has_vuright_property)                                              \
    Trace::TraceMissingProperty(CONFIG::MASTER_KEY , CONFIG::VU_RIGHT_KEY) ;             \
  if (!metro_channel_has_name_property)                                                  \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::CHANNEL_NAME_KEY) ;         \
  if (!metro_channel_has_volume_property)                                                \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::VOLUME_KEY) ;               \
  if (!metro_channel_has_pan_property)                                                   \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::PAN_KEY) ;                  \
  if (!metro_channel_has_mute_property)                                                  \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::IS_MUTED_KEY) ;             \
  if (!metro_channel_has_source_property)                                                \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::SOURCE_N_KEY) ;             \
  if (!metro_channel_has_stereo_property)                                                \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::STEREO_KEY) ;               \
  if (!metro_channel_has_vuleft_property)                                                \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::VU_LEFT_KEY) ;              \
  if (!metro_channel_has_vuright_property)                                               \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::VU_RIGHT_KEY) ;             \
                                                                                         \
                                                                                         \
  /* trace invalid root datatypes */                                                     \
  if (!app_version_is_double)                                                            \
    Trace::TraceTypeMismatch(root                , CONFIG::CONFIG_VERSION_KEY       ,    \
                             CONFIG::DOUBLE_TYPE , root[CONFIG::CONFIG_VERSION_ID]) ;    \
                                                                                         \
  /* trace invalid client datatypes */                                                   \
  if (!save_audio_is_int)                                                                \
    Trace::TraceTypeMismatch(client              , CONFIG::SAVE_AUDIO_MODE_KEY         , \
                             CONFIG::INT_TYPE    , client[CONFIG::SAVE_AUDIO_MODE_ID]) ; \
  if (!mixdown_is_int)                                                                   \
    Trace::TraceTypeMismatch(client              , CONFIG::MIXDOWN_MODE_KEY          ,   \
                             CONFIG::INT_TYPE    , client[CONFIG::MIXDOWN_MODE_KEY]) ;   \
  if (!save_log_is_bool)                                                                 \
    Trace::TraceTypeMismatch(client              , CONFIG::SHOULD_SAVE_LOG_KEY         , \
                             CONFIG::BOOL_TYPE   , client[CONFIG::SHOULD_SAVE_LOG_ID]) ; \
  if (!debug_level_is_int)                                                               \
    Trace::TraceTypeMismatch(client              , CONFIG::DEBUG_LEVEL_KEY         ,     \
                             CONFIG::INT_TYPE    , client[CONFIG::DEBUG_LEVEL_ID]) ;     \
  if (!should_hide_bots_is_bool)                                                         \
    Trace::TraceTypeMismatch(client              , CONFIG::SHOULD_HIDE_BOTS_KEY  ,       \
                             CONFIG::BOOL_TYPE   , client[CONFIG::SHOULD_HIDE_BOTS_ID]) ;\
                                                                                         \
  /* trace subscriptions datatypes */                                                          \
  if (!autosubscribe_is_int)                                                             \
    Trace::TraceTypeMismatch(subs                , CONFIG::SUBSCRIBE_MODE_KEY         ,  \
                             CONFIG::INT_TYPE    , client[CONFIG::SUBSCRIBE_MODE_ID]) ;  \
                                                                                         \
  /* trace invalid audio datatypes */                                                    \
  if (!win_audio_ifn_is_int)                                                             \
    Trace::TraceTypeMismatch(audio               , CONFIG::WIN_AUDIO_IF_KEY        ,     \
                             CONFIG::INT_TYPE    , audio[CONFIG::WIN_AUDIO_IF_ID]) ;     \
  if (!asio_driver_is_int)                                                               \
    Trace::TraceTypeMismatch(audio               , CONFIG::ASIO_DRIVER_KEY        ,      \
                             CONFIG::INT_TYPE    , audio[CONFIG::ASIO_DRIVER_ID]) ;      \
  if (!asio_input0_is_int)                                                               \
    Trace::TraceTypeMismatch(audio               , CONFIG::ASIO_INPUT0_KEY        ,      \
                             CONFIG::INT_TYPE    , audio[CONFIG::ASIO_INPUT0_ID]) ;      \
  if (!asio_inout1_is_int)                                                               \
    Trace::TraceTypeMismatch(audio               , CONFIG::ASIO_INPUT1_KEY         ,     \
                             CONFIG::INT_TYPE    , audio[CONFIG::ASIO_INPUT1_ID]) ;      \
  if (!asio_output0_is_int)                                                              \
    Trace::TraceTypeMismatch(audio               , CONFIG::ASIO_OUTPUT0_KEY        ,     \
                             CONFIG::INT_TYPE    , audio[CONFIG::ASIO_OUTPUT0_ID]) ;     \
  if (!asio_output1_is_int)                                                              \
    Trace::TraceTypeMismatch(audio               , CONFIG::ASIO_OUTPUT1_KEY        ,     \
                             CONFIG::INT_TYPE    , audio[CONFIG::ASIO_OUTPUT1_ID]) ;     \
  if (!ks_input_is_int)                                                                  \
    Trace::TraceTypeMismatch(audio               , CONFIG::KS_INPUT_KEY        ,         \
                             CONFIG::INT_TYPE    , audio[CONFIG::KS_INPUT_ID]) ;         \
  if (!ks_output_is_int)                                                                 \
    Trace::TraceTypeMismatch(audio               , CONFIG::KS_OUTPUT_KEY        ,        \
                             CONFIG::INT_TYPE    , audio[CONFIG::KS_OUTPUT_ID]) ;        \
  if (!ks_samplerate_is_int)                                                             \
    Trace::TraceTypeMismatch(audio               , CONFIG::KS_SAMPLERATE_KEY        ,    \
                             CONFIG::INT_TYPE    , audio[CONFIG::KS_SAMPLERATE_ID]) ;    \
  if (!ks_bitdepth_is_int)                                                               \
    Trace::TraceTypeMismatch(audio               , CONFIG::KS_BITDEPTH_KEY        ,      \
                             CONFIG::INT_TYPE    , audio[CONFIG::KS_BITDEPTH_ID]) ;      \
  if (!ks_n_blocks_is_int)                                                               \
    Trace::TraceTypeMismatch(audio               , CONFIG::KS_NBLOCKS_KEY        ,       \
                             CONFIG::INT_TYPE    , audio[CONFIG::KS_NBLOCKS_ID]) ;       \
  if (!ks_blocksize_is_int)                                                              \
    Trace::TraceTypeMismatch(audio               , CONFIG::KS_BLOCKSIZE_KEY        ,     \
                             CONFIG::INT_TYPE    , audio[CONFIG::KS_BLOCKSIZE_ID]) ;     \
  if (!ds_input0_is_int)                                                                 \
    Trace::TraceTypeMismatch(audio               , CONFIG::DS_INPUT0_KEY        ,        \
                             CONFIG::INT_TYPE    , audio[CONFIG::DS_INPUT0_ID]) ;        \
  if (!ds_input1_is_int)                                                                 \
    Trace::TraceTypeMismatch(audio               , CONFIG::DS_INPUT1_KEY        ,        \
                             CONFIG::INT_TYPE    , audio[CONFIG::DS_INPUT1_ID]) ;        \
  if (!ds_input2_is_int)                                                                 \
    Trace::TraceTypeMismatch(audio               , CONFIG::DS_INPUT2_KEY        ,        \
                             CONFIG::INT_TYPE    , audio[CONFIG::DS_INPUT2_ID]) ;        \
  if (!ds_input3_is_int)                                                                 \
    Trace::TraceTypeMismatch(audio               , CONFIG::DS_INPUT3_KEY        ,        \
                             CONFIG::INT_TYPE    , audio[CONFIG::DS_INPUT3_ID]) ;        \
  if (!ds_output0_is_int)                                                                \
    Trace::TraceTypeMismatch(audio               , CONFIG::DS_OUTPUT0_KEY        ,       \
                             CONFIG::INT_TYPE    , audio[CONFIG::DS_OUTPUT0_ID]) ;       \
  if (!ds_output1_is_int)                                                                \
    Trace::TraceTypeMismatch(audio               , CONFIG::DS_OUTPUT1_KEY        ,       \
                             CONFIG::INT_TYPE    , audio[CONFIG::DS_OUTPUT1_ID]) ;       \
  if (!ds_output2_is_int)                                                                \
    Trace::TraceTypeMismatch(audio               , CONFIG::DS_OUTPUT2_KEY        ,       \
                             CONFIG::INT_TYPE    , audio[CONFIG::DS_OUTPUT2_ID]) ;       \
  if (!ds_output3_is_int)                                                                \
    Trace::TraceTypeMismatch(audio               , CONFIG::DS_OUTPUT3_KEY        ,       \
                             CONFIG::INT_TYPE    , audio[CONFIG::DS_OUTPUT3_ID]) ;       \
  if (!ds_samplerate_is_int)                                                             \
    Trace::TraceTypeMismatch(audio               , CONFIG::DS_SAMPLERATE_KEY        ,    \
                             CONFIG::INT_TYPE    , audio[CONFIG::DS_SAMPLERATE_ID]) ;    \
  if (!ds_bitdepth_is_int)                                                               \
    Trace::TraceTypeMismatch(audio               , CONFIG::DS_BITDEPTH_KEY        ,      \
                             CONFIG::INT_TYPE    , audio[CONFIG::DS_BITDEPTH_ID]) ;      \
  if (!ds_n_blocks_is_int)                                                               \
    Trace::TraceTypeMismatch(audio               , CONFIG::DS_NBLOCKS_KEY        ,       \
                             CONFIG::INT_TYPE    , audio[CONFIG::DS_NBLOCKS_ID]) ;       \
  if (!ds_blocksize_is_int)                                                              \
    Trace::TraceTypeMismatch(audio               , CONFIG::DS_BLOCKSIZE_KEY        ,     \
                             CONFIG::INT_TYPE    , audio[CONFIG::DS_BLOCKSIZE_ID]) ;     \
  if (!wave_input_is_int)                                                                \
    Trace::TraceTypeMismatch(audio               , CONFIG::WAVE_INPUT_KEY        ,       \
                             CONFIG::INT_TYPE    , audio[CONFIG::WAVE_INPUT_ID]) ;       \
  if (!wave_output_is_int)                                                               \
    Trace::TraceTypeMismatch(audio               , CONFIG::WAVE_OUTPUT_KEY        ,      \
                             CONFIG::INT_TYPE    , audio[CONFIG::WAVE_OUTPUT_ID]) ;      \
  if (!wave_samplerate_is_int)                                                           \
    Trace::TraceTypeMismatch(audio               , CONFIG::WAVE_SAMPLERATE_KEY        ,  \
                             CONFIG::INT_TYPE    , audio[CONFIG::WAVE_SAMPLERATE_ID]) ;  \
  if (!wave_bitdepth_is_int)                                                             \
    Trace::TraceTypeMismatch(audio               , CONFIG::WAVE_BITDEPTH_KEY        ,    \
                             CONFIG::INT_TYPE    , audio[CONFIG::WAVE_BITDEPTH_ID]) ;    \
  if (!wave_n_blocks_is_int)                                                             \
    Trace::TraceTypeMismatch(audio               , CONFIG::WAVE_NBLOCKS_KEY        ,     \
                             CONFIG::INT_TYPE    , audio[CONFIG::WAVE_NBLOCKS_ID]) ;     \
  if (!wave_blocksize_is_int)                                                            \
    Trace::TraceTypeMismatch(audio               , CONFIG::WAVE_BLOCKSIZE_KEY        ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::WAVE_BLOCKSIZE_ID]) ;   \
  if (!mac_device_is_string)                                                             \
    Trace::TraceTypeMismatch(audio               , CONFIG::MAC_DEVICE_KEY        ,       \
                             CONFIG::STRING_TYPE , audio[CONFIG::MAC_DEVICE_ID]) ;       \
  if (!mac_n_inputs_is_int)                                                              \
    Trace::TraceTypeMismatch(audio               , CONFIG::MAC_NINPUTS_KEY        ,      \
                             CONFIG::INT_TYPE    , audio[CONFIG::MAC_NINPUTS_ID]) ;      \
  if (!mac_bitdepth_is_int)                                                              \
    Trace::TraceTypeMismatch(audio               , CONFIG::MAC_BITDEPTH_KEY        ,     \
                             CONFIG::INT_TYPE    , audio[CONFIG::MAC_BITDEPTH_ID]) ;     \
  if (!mac_samplerate_is_int)                                                            \
    Trace::TraceTypeMismatch(audio               , CONFIG::MAC_SAMPLERATE_KEY        ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::MAC_SAMPLERATE_ID]) ;   \
  if (!nix_audio_ifn_is_int)                                                             \
    Trace::TraceTypeMismatch(audio               , CONFIG::NIX_AUDIO_IF_KEY        ,     \
                             CONFIG::INT_TYPE    , audio[CONFIG::NIX_AUDIO_IF_ID]) ;     \
  if (!jack_server_is_int)                                                               \
    Trace::TraceTypeMismatch(audio               , CONFIG::JACK_SERVER_KEY        ,      \
                             CONFIG::INT_TYPE    , audio[CONFIG::JACK_SERVER_ID]) ;      \
  if (!jack_name_is_string)                                                              \
    Trace::TraceTypeMismatch(audio               , CONFIG::JACK_NAME_KEY        ,        \
                             CONFIG::STRING_TYPE , audio[CONFIG::JACK_NAME_ID]) ;        \
  if (!jack_n_inputs_is_int)                                                             \
    Trace::TraceTypeMismatch(audio               , CONFIG::JACK_NINPUTS_KEY        ,     \
                             CONFIG::INT_TYPE    , audio[CONFIG::JACK_NINPUTS_ID]) ;     \
  if (!jack_n_outputs_is_int)                                                            \
    Trace::TraceTypeMismatch(audio               , CONFIG::JACK_NOUTPUTS_KEY        ,    \
                             CONFIG::INT_TYPE    , audio[CONFIG::JACK_NOUTPUTS_ID]) ;    \
  if (!alsa_config_is_string)                                                            \
    Trace::TraceTypeMismatch(audio               , CONFIG::ALSA_CONFIG_KEY        ,      \
                             CONFIG::STRING_TYPE , audio[CONFIG::ALSA_CONFIG_ID]) ;      \
                                                                                         \
  /* trace invalid server datatypes */                                                   \
  if (!host_name_is_string)                                                              \
    Trace::TraceTypeMismatch(server              , CONFIG::HOST_KEY       ,              \
                             CONFIG::STRING_TYPE , server[CONFIG::HOST_ID]) ;            \
  if (!login_is_string)                                                                  \
    Trace::TraceTypeMismatch(server              , CONFIG::LOGIN_KEY       ,             \
                             CONFIG::STRING_TYPE , server[CONFIG::LOGIN_ID]) ;           \
  if (!pass_is_string)                                                                   \
    Trace::TraceTypeMismatch(server              , CONFIG::PASS_KEY       ,              \
                             CONFIG::STRING_TYPE , server[CONFIG::PASS_ID]) ;            \
  if (!is_anon_is_bool)                                                                  \
    Trace::TraceTypeMismatch(server              , CONFIG::IS_ANONYMOUS_KEY       ,      \
                             CONFIG::BOOL_TYPE   , server[CONFIG::IS_ANONYMOUS_ID]) ;    \
  if (!is_agreed_is_bool)                                                                \
    Trace::TraceTypeMismatch(server              , CONFIG::IS_AGREED_KEY       ,         \
                             CONFIG::BOOL_TYPE   , server[CONFIG::IS_AGREED_ID]) ;       \
  if (!should_agree_is_bool)                                                             \
    Trace::TraceTypeMismatch(server              , CONFIG::SHOULD_AGREE_KEY       ,      \
                             CONFIG::BOOL_TYPE   , server[CONFIG::SHOULD_AGREE_ID]) ;    \
                                                                                         \
  /* trace invalid masters datatypes */                                                  \
  if (!master_name_is_string)                                                            \
    Trace::TraceTypeMismatch(master              , CONFIG::CHANNEL_NAME_KEY         ,    \
                             CONFIG::STRING_TYPE , master[CONFIG::CHANNEL_NAME_ID]) ;    \
  if (!master_volume_is_double)                                                          \
    Trace::TraceTypeMismatch(master              , CONFIG::VOLUME_KEY         ,          \
                             CONFIG::DOUBLE_TYPE , master[CONFIG::VOLUME_ID]) ;          \
  if (!master_pan_is_double)                                                             \
    Trace::TraceTypeMismatch(master              , CONFIG::PAN_KEY         ,             \
                             CONFIG::DOUBLE_TYPE , master[CONFIG::PAN_ID]) ;             \
  if (!master_mute_is_bool)                                                              \
    Trace::TraceTypeMismatch(master              , CONFIG::IS_MUTED_KEY         ,        \
                             CONFIG::BOOL_TYPE   , master[CONFIG::IS_MUTED_ID]) ;        \
  if (!master_stereo_is_int)                                                             \
    Trace::TraceTypeMismatch(master              , CONFIG::STEREO_KEY         ,          \
                             CONFIG::INT_TYPE    , master[CONFIG::STEREO_ID]) ;          \
  if (!master_vuleft_is_double)                                                          \
    Trace::TraceTypeMismatch(master              , CONFIG::VU_LEFT_KEY         ,         \
                             CONFIG::DOUBLE_TYPE , master[CONFIG::VU_LEFT_ID]) ;         \
  if (!master_vuright_is_double)                                                         \
    Trace::TraceTypeMismatch(master              , CONFIG::VU_RIGHT_KEY         ,        \
                             CONFIG::DOUBLE_TYPE , master[CONFIG::VU_RIGHT_ID]) ;        \
  if (!metro_name_is_string)                                                             \
    Trace::TraceTypeMismatch(metro               , CONFIG::CHANNEL_NAME_KEY        ,     \
                             CONFIG::STRING_TYPE , metro[CONFIG::CHANNEL_NAME_ID]) ;     \
  if (!metro_volume_is_double)                                                           \
    Trace::TraceTypeMismatch(metro               , CONFIG::VOLUME_KEY        ,           \
                             CONFIG::DOUBLE_TYPE , metro[CONFIG::VOLUME_ID]) ;           \
  if (!metro_pan_is_double)                                                              \
    Trace::TraceTypeMismatch(metro               , CONFIG::PAN_KEY        ,              \
                             CONFIG::DOUBLE_TYPE , metro[CONFIG::PAN_ID]) ;              \
  if (!metro_mute_is_bool)                                                               \
    Trace::TraceTypeMismatch(metro               , CONFIG::IS_MUTED_KEY        ,         \
                             CONFIG::BOOL_TYPE   , metro[CONFIG::IS_MUTED_ID]) ;         \
  if (!metro_source_is_int)                                                              \
    Trace::TraceTypeMismatch(metro               , CONFIG::SOURCE_N_KEY        ,         \
                             CONFIG::INT_TYPE    , metro[CONFIG::SOURCE_N_ID]) ;         \
  if (!metro_stereo_is_int)                                                              \
    Trace::TraceTypeMismatch(metro               , CONFIG::STEREO_KEY        ,           \
                             CONFIG::INT_TYPE    , metro[CONFIG::STEREO_ID]) ;           \
  if (!metro_vuleft_is_double)                                                           \
    Trace::TraceTypeMismatch(metro               , CONFIG::VU_LEFT_KEY        ,          \
                             CONFIG::DOUBLE_TYPE , metro[CONFIG::VU_LEFT_ID]) ;          \
  if (!metro_vuright_is_double)                                                          \
    Trace::TraceTypeMismatch(metro               , CONFIG::VU_RIGHT_KEY        ,         \
                             CONFIG::DOUBLE_TYPE , metro[CONFIG::VU_RIGHT_ID]) ;         \
                                                                                         \
                                                                                         \
  /* modify return value and/or restore defauilt config */                               \
  is_valid = is_valid                                                          &&        \
                                                                                         \
      /* validate default values */                                                      \
      has_valid_version_declaration                                            &&        \
      has_valid_sessiondir_declaration                                         &&        \
      has_valid_logfile_declaration                                            &&        \
                                                                                         \
                                                                                         \
      /* validate root properties */                                                     \
      root_has_appversion_property                                             &&        \
                                                                                         \
      /* validate client properties */                                                   \
      client_has_saveaudio_property      && client_has_mixdown_property        &&        \
      client_has_savelog_property        && client_has_debuglevel_property     &&        \
      client_has_hide_bots_property                                            &&        \
                                                                                         \
      /* validate subscriptions properties */                                            \
      subs_has_autosubscribe_property                                          &&        \
                                                                                         \
      /* validate audio properties */                                                    \
      audio_has_winifn_property                                                &&        \
      audio_has_asiodriver_property      && audio_has_asioinput0_property      &&        \
      audio_has_asioinput1_property      && audio_has_asiooutput0_property     &&        \
      audio_has_asiooutput1_property                                           &&        \
      audio_has_ksinput_property         && audio_has_ksoutput_property        &&        \
      audio_has_ksbitdepth_property      && audio_has_kssamplerate_property    &&        \
      audio_has_ksnblocks_property       && audio_has_ksblocksize_property     &&        \
      audio_has_dsinput0_property        && audio_has_dsinput1_property        &&        \
      audio_has_dsinput2_property        && audio_has_dsinput3_property        &&        \
      audio_has_dsoutput0_property       && audio_has_dsoutput1_property       &&        \
      audio_has_dsoutput2_property       && audio_has_dsoutput3_property       &&        \
      audio_has_dsbitdepth_property      && audio_has_dssamplerate_property    &&        \
      audio_has_dsnblocks_property       && audio_has_dsblocksize_property     &&        \
      audio_has_waveinput_property       && audio_has_waveoutput_property      &&        \
      audio_has_wavebitdepth_property    && audio_has_wavesamplerate_property  &&        \
      audio_has_wavenblocks_property     && audio_has_waveblocksize_property   &&        \
      audio_has_macdevice_property       && audio_has_macninputs_property      &&        \
      audio_has_macbitdepth_property     && audio_has_macsamplerate_property   &&        \
      audio_has_nixifn_property          && audio_has_jackserver_property      &&        \
      audio_has_jackname_property        && audio_has_jackninputs_property     &&        \
      audio_has_jacknoutputs_property    && audio_has_alsaconfig_property      &&        \
                                                                                         \
      /* validate server properties */                                                   \
      server_has_host_property           && server_has_login_property          &&        \
      server_has_pass_property           && server_has_is_anonymous_property   &&        \
      server_has_is_agreed_property      && server_has_should_agree_property   &&        \
                                                                                         \
      /* validate masters properties */                                                  \
      master_channel_has_name_property   && master_channel_has_volume_property &&        \
      master_channel_has_pan_property    && master_channel_has_mute_property   &&        \
      master_channel_has_stereo_property && master_channel_has_vuleft_property &&        \
      master_channel_has_vuright_property                                      &&        \
      metro_channel_has_name_property    && metro_channel_has_volume_property  &&        \
      metro_channel_has_pan_property     && metro_channel_has_mute_property    &&        \
      metro_channel_has_source_property  && metro_channel_has_stereo_property  &&        \
      metro_channel_has_vuleft_property  && metro_channel_has_vuleft_property  &&        \
                                                                                         \
                                                                                         \
      /* validate client datatypes */                                                    \
      save_audio_is_int                  && mixdown_is_int                     &&        \
      save_log_is_bool                   && debug_level_is_int                 &&        \
      should_hide_bots_is_bool                                                 &&        \
                                                                                         \
      /* validate subscriptions properties */                                            \
      autosubscribe_is_int                                                     &&        \
                                                                                         \
      /* validate audio datatypes */                                                     \
      win_audio_ifn_is_int                                                     &&        \
      asio_driver_is_int                 && asio_input0_is_int                 &&        \
      asio_inout1_is_int                 && asio_output0_is_int                &&        \
      asio_output1_is_int                                                      &&        \
      ks_input_is_int                    && ks_output_is_int                   &&        \
      ks_bitdepth_is_int                 && ks_samplerate_is_int               &&        \
      ks_n_blocks_is_int                 && ks_blocksize_is_int                &&        \
      ds_input0_is_int                   && ds_input1_is_int                   &&        \
      ds_input2_is_int                   && ds_input3_is_int                   &&        \
      ds_output0_is_int                  && ds_output1_is_int                  &&        \
      ds_output2_is_int                  && ds_output3_is_int                  &&        \
      ds_bitdepth_is_int                 && ds_samplerate_is_int               &&        \
      ds_n_blocks_is_int                 && ds_blocksize_is_int                &&        \
      wave_input_is_int                  && wave_output_is_int                 &&        \
      wave_bitdepth_is_int               && wave_samplerate_is_int             &&        \
      wave_n_blocks_is_int               && wave_blocksize_is_int              &&        \
      mac_device_is_string               && mac_n_inputs_is_int                &&        \
      mac_bitdepth_is_int                && mac_samplerate_is_int              &&        \
      nix_audio_ifn_is_int               && jack_server_is_int                 &&        \
      jack_name_is_string                && jack_n_inputs_is_int               &&        \
      jack_n_outputs_is_int              && alsa_config_is_string              &&        \
                                                                                         \
      /* validate server datatypes */                                                    \
      host_name_is_string                && login_is_string                    &&        \
      pass_is_string                     && is_anon_is_bool                    &&        \
      is_agreed_is_bool                  && should_agree_is_bool               &&        \
                                                                                         \
      /* validate masters datatypes */                                                   \
      master_name_is_string              && master_volume_is_double            &&        \
      master_pan_is_double               && master_mute_is_bool                &&        \
      master_stereo_is_int               && master_vuleft_is_double            &&        \
      master_vuright_is_double                                                 &&        \
      metro_name_is_string               && metro_volume_is_double             &&        \
      metro_pan_is_double                && metro_mute_is_bool                 &&        \
      metro_source_is_int                && metro_stereo_is_int                &&        \
      metro_vuleft_is_double             && metro_vuright_is_double             ;

/*
#define DEBUG_TRACE_SANITY_CHECK_SERVER // TODO:                                     \
#define DEBUG_TRACE_SANITY_CHECK_USER                                                \
  String user_name = String(channels.getType()) ;                                    \
  if (!remote_has_useridx_property)                                                  \
    Trace::TraceMissingProperty(user_name , CONFIG::USERIDX_KEY) ;                   \
  if (!remote_has_useridx_property)                                                  \
    Trace::TraceError("destroying invalid remote channel store '" + user_name + "'") ;
*/

#define DEBUG_TRACE_SANITY_CHECK_CHANNEL                                                   \
  String channels_name = String(channels.getType()) ;                                      \
  String channel_name  = channel[CONFIG::CHANNEL_NAME_ID].toString() ;                     \
                                                                                           \
  /* query channel datatypes */                                                            \
  /* NOTE: these type-checks normally should be unnecessary                      */        \
  /*       all tree nodes will be of the proper types after restoreVarTypeInfo() */        \
  bool channel_name_is_string    = channel[CONFIG::CHANNEL_NAME_ID].isString() ;           \
  bool channel_idx_is_int        = channel[CONFIG::CHANNEL_IDX_ID] .isInt()    ;           \
  bool channel_pair_idx_is_int   = channel[CONFIG::PAIR_IDX_ID]    .isInt()    ;           \
  bool channel_volume_is_double  = channel[CONFIG::VOLUME_ID]      .isDouble() ;           \
  bool channel_pan_is_double     = channel[CONFIG::PAN_ID]         .isDouble() ;           \
  bool channel_xmit_is_bool      = channel[CONFIG::IS_XMIT_RCV_ID] .isBool()   ;           \
  bool channel_mute_is_bool      = channel[CONFIG::IS_MUTED_ID]    .isBool()   ;           \
  bool channel_solo_is_bool      = channel[CONFIG::IS_SOLO_ID]     .isBool()   ;           \
  bool channel_source_is_int     = channel[CONFIG::SOURCE_N_ID]    .isInt()    ;           \
  bool channel_stereo_is_int     = channel[CONFIG::STEREO_ID]      .isInt()    ;           \
  bool channel_vuleft_is_double  = channel[CONFIG::VU_LEFT_ID]     .isDouble() ;           \
  bool channel_vuright_is_double = channel[CONFIG::VU_RIGHT_ID]    .isDouble() ;           \
                                                                                           \
  /* trace missing channel properties */                                                   \
  if (!channel_has_channelname_property)                                                   \
    Trace::TraceMissingProperty(channel_name , CONFIG::CHANNEL_NAME_KEY , channels_name) ; \
  if (!channel_has_channelidx_property)                                                    \
    Trace::TraceMissingProperty(channel_name , CONFIG::CHANNEL_IDX_KEY  , channels_name) ; \
  if (!channel_has_pairidx_property)                                                       \
    Trace::TraceMissingProperty(channel_name , CONFIG::PAIR_IDX_KEY     , channels_name) ; \
  if (!channel_has_volume_property)                                                        \
    Trace::TraceMissingProperty(channel_name , CONFIG::VOLUME_KEY       , channels_name) ; \
  if (!channel_has_pan_property)                                                           \
    Trace::TraceMissingProperty(channel_name , CONFIG::PAN_KEY          , channels_name) ; \
  if (!channel_has_xmit_property)                                                          \
    Trace::TraceMissingProperty(channel_name , CONFIG::IS_XMIT_RCV_KEY  , channels_name) ; \
  if (!channel_has_mute_property)                                                          \
    Trace::TraceMissingProperty(channel_name , CONFIG::IS_MUTED_KEY     , channels_name) ; \
  if (!channel_has_solo_property)                                                          \
    Trace::TraceMissingProperty(channel_name , CONFIG::IS_SOLO_KEY      , channels_name) ; \
  if (!channel_has_source_property)                                                        \
    Trace::TraceMissingProperty(channel_name , CONFIG::SOURCE_N_KEY     , channels_name) ; \
  if (!channel_has_stereo_property)                                                        \
    Trace::TraceMissingProperty(channel_name , CONFIG::STEREO_KEY       , channels_name) ; \
  if (!channel_has_vuleft_property)                                                        \
    Trace::TraceMissingProperty(channel_name , CONFIG::VU_LEFT_KEY      , channels_name) ; \
  if (!channel_has_vuright_property)                                                       \
    Trace::TraceMissingProperty(channel_name , CONFIG::VU_RIGHT_KEY     , channels_name) ; \
                                                                                           \
  /* trace invalid channel datatypes */                                                    \
  if (!channel_name_is_string)                                                             \
    Trace::TraceTypeMismatch(channel             , CONFIG::CHANNEL_NAME_KEY         ,      \
                             CONFIG::STRING_TYPE , channel[CONFIG::CHANNEL_NAME_ID] ,      \
                             channels_name                                         ) ;     \
  if (!channel_idx_is_int)                                                                 \
    Trace::TraceTypeMismatch(channel             , CONFIG::CHANNEL_IDX_KEY          ,      \
                             CONFIG::INT_TYPE    , channel[CONFIG::CHANNEL_IDX_ID]  ,      \
                             channels_name                                         ) ;     \
  if (!channel_pair_idx_is_int)                                                            \
    Trace::TraceTypeMismatch(channel             , CONFIG::PAIR_IDX_KEY          ,         \
                             CONFIG::INT_TYPE    , channel[CONFIG::PAIR_IDX_ID]  ,         \
                             channels_name                                         ) ;     \
  if (!channel_volume_is_double)                                                           \
    Trace::TraceTypeMismatch(channel             , CONFIG::VOLUME_KEY              ,       \
                             CONFIG::DOUBLE_TYPE , channel[CONFIG::VOLUME_ID]      ,       \
                             channels_name                                         ) ;     \
  if (!channel_pan_is_double)                                                              \
    Trace::TraceTypeMismatch(channel             , CONFIG::PAN_KEY                 ,       \
                             CONFIG::DOUBLE_TYPE , channel[CONFIG::PAN_ID]         ,       \
                             channels_name                                         ) ;     \
  if (!channel_xmit_is_bool)                                                               \
    Trace::TraceTypeMismatch(channel             , CONFIG::IS_XMIT_RCV_KEY         ,       \
                             CONFIG::BOOL_TYPE   , channel[CONFIG::IS_XMIT_RCV_ID] ,       \
                             channels_name                                         ) ;     \
  if (!channel_mute_is_bool)                                                               \
    Trace::TraceTypeMismatch(channel             , CONFIG::IS_MUTED_KEY            ,       \
                             CONFIG::BOOL_TYPE   , channel[CONFIG::IS_MUTED_ID]    ,       \
                             channels_name                                         ) ;     \
  if (!channel_solo_is_bool)                                                               \
    Trace::TraceTypeMismatch(channel             , CONFIG::IS_SOLO_KEY             ,       \
                             CONFIG::BOOL_TYPE   , channel[CONFIG::IS_SOLO_ID]     ,       \
                             channels_name                                         ) ;     \
  if (!channel_source_is_int)                                                              \
    Trace::TraceTypeMismatch(channel             , CONFIG::SOURCE_N_KEY            ,       \
                             CONFIG::INT_TYPE    , channel[CONFIG::SOURCE_N_ID]    ,       \
                             channels_name                                         ) ;     \
  if (!channel_stereo_is_int)                                                              \
    Trace::TraceTypeMismatch(channel             , CONFIG::STEREO_KEY              ,       \
                             CONFIG::INT_TYPE    , channel[CONFIG::STEREO_ID]      ,       \
                             channels_name                                         ) ;     \
  if (!channel_vuleft_is_double)                                                           \
    Trace::TraceTypeMismatch(channel             , CONFIG::VU_LEFT_KEY             ,       \
                             CONFIG::DOUBLE_TYPE , channel[CONFIG::VU_LEFT_KEY]    ,       \
                             channels_name                                         ) ;     \
  if (!channel_vuright_is_double)                                                          \
    Trace::TraceTypeMismatch(channel             , CONFIG::VU_RIGHT_KEY            ,       \
                             CONFIG::DOUBLE_TYPE , channel[CONFIG::VU_RIGHT_KEY]   ,       \
                             channels_name                                         ) ;     \
                                                                                           \
  /* validate channel properties */                                                        \
  if (!channel_has_channelname_property || !channel_has_channelidx_property ||             \
      !channel_has_pairidx_property     || !channel_has_volume_property     ||             \
      !channel_has_pan_property         || !channel_has_xmit_property       ||             \
      !channel_has_mute_property        || !channel_has_solo_property       ||             \
      !channel_has_source_property      || !channel_has_stereo_property     ||             \
      !channel_has_vuleft_property      || !channel_has_vuright_property     )             \
    Trace::TraceError("destroying invalid local channel store '" + channel_name + "'") ;

#if TRACE_STORE_CONFIG_VB
#  define DEBUG_TRACE_STORE_CONFIG Trace::TraceConfig("storing config xml=\n" +      \
                                                      configValueTree.toXmlString()) ;
#else // TRACE_STORE_CONFIG_VB
#  define DEBUG_TRACE_STORE_CONFIG Trace::TraceConfig("storing config xml") ;
#endif // TRACE_STORE_CONFIG_VB

#define DEBUG_TRACE_CONFIG_VALUE_CHANGED                                                \
  String a_var = (a_value.refersToSameSourceAs(LinJam::Status))? "Status" : "unknown" ; \
  String status = Trace::Status2String(int(LinJam::Status.getValue())) ;                \
  Trace::TraceEvent("value changed => " + a_var + " => " + status)                      ;

#define DEBUG_TRACE_CONFIG_TREE_CHANGED                            \
  String node   = String(a_node.getType()) ;                       \
  String parent = String(a_node.getParent().getType()) ;           \
  String key    = String(a_key) ;                                  \
  String val    = a_node[a_key].toString() ;                       \
  if (a_key != CONFIG::VU_LEFT_ID && a_key != CONFIG::VU_RIGHT_ID) \
    Trace::TraceEvent("value changed for " + parent              + \
                      " => " + node + "[" + key + "] => " + val) ;

#define DEBUG_TRACE_CONFIG_TREE_ADDED                                      \
  if (a_parent_node == this->subscriptions)                                \
    Trace::TraceEvent("node added to " + String(a_parent_node.getType()) + \
                      " => " + String(a_node.getType())) ;

#define DEBUG_TRACE_CONFIG_TREE_REMOVED                                        \
  if (a_parent_node == this->subscriptions)                                    \
    Trace::TraceEvent("node removed from " + String(a_parent_node.getType()) + \
                      " => " + String(a_node.getType())) ;


/* channels */

#define DEBUG_TRACE_STEREO_STATUS                                                     \
  String status      = (stereo_status == CONFIG::STEREO_L)? "STEREO_L" :              \
                       (stereo_status == CONFIG::STEREO_R)? "STEREO_R" : "MONO" +     \
                       String((is_paired)? " (paired)" : " (unpaired)") ;             \
  String pair_status = ((pair_stereo_status == CONFIG::STEREO_L)?                     \
                       "STEREO_L" : "STEREO_R") + String(" (paired)") ;               \
  String dbgA        = "setting remote channel '" ; String dbgB = "' status to " ;    \
  if (is_paired) Trace::TraceConfig(dbgA + pair_name    + dbgB + pair_status) ;       \
                 Trace::TraceConfig(dbgA + channel_name + dbgB + status) ;

#define DEBUG_TRACE_MONO_STATUS                                                 \
  String dbgA = "setting remote channel '" ; String dbgB = "' status to MONO" ; \
  String pair_name = (has_l_pair)? l_pair_name : r_pair_name ;                  \
  if (has_orphaned_pair)                                                        \
    Trace::TraceConfig(dbgA + pair_name    + dbgB + " (orphaned)") ;            \
  if (parseStereoStatus(channel_name) == CONFIG::MONO)                          \
    Trace::TraceConfig(dbgA + channel_name + dbgB) ;

#define DEBUG_TRACE_ADD_CHANNEL_STORE                                               \
  String user_id      = String(channels_store.getType()) ;                          \
  int    ch_idx       = int(new_channel_node[CONFIG::CHANNEL_IDX_ID]) ;             \
  String channel_id   = String(makeChannelId(ch_idx)) ;                             \
  String channel_name = LinJam::GetStoredChannelName(new_channel_node) ;            \
  bool   is_local     = channels_store == this->localChannels ;                     \
  String group        = (is_local)? "local" : "remote" ;                            \
  String dbgA         = "created storage for new " ;                                \
  String dbgB         = group + " " + channel_id + " '" + channel_name + "'" ;      \
  if      (!channels_store.isValid())                                               \
       Trace::TraceError("invlaid parent creating channel storage for '" + dbgB) ;  \
  else if (!new_channel_node.isValid())                                             \
       Trace::TraceError("invlaid node creating " + user_id + " channel storage") ; \
  if (new_channel_node.getParent() == channels_store)                               \
       Trace::TraceConfig("storage exists for " + dbgB) ;                           \
  else if (is_local)                                                                \
       Trace::TraceConfig(dbgA + dbgB) ;                                            \
  else Trace::TraceConfig(dbgA + dbgB + " for '" + user_id + "'") ;                 \
  if (TRACE_LOCAL_CHANNELS_VB)                                                      \
    DBG(Trace::DumpStoredChannels() + Trace::DumpClientChannels()) ;

#define DEBUG_TRACE_DESTROY_CHANNEL_STORE                                     \
  String channel_id   = String(channel_store.getType()) ;                     \
  String channel_name = channel_store[CONFIG::CHANNEL_NAME_ID].toString() ;   \
  String user_id      = String(channels_store.getType()) ;                    \
  String dbgA         = "destroyed storage for " ;                            \
  String dbgB         = " " + channel_id + " '" + channel_name + "' " ;       \
  if (channel_store.getParent() == channels_store)                            \
    if (channels_store == this->localChannels)                                \
        Trace::TraceConfig(dbgA + "local"  + dbgB) ;                          \
    else Trace::TraceConfig(dbgA + "remote" + dbgB + "for '" + user_id + "'") ;

#define DEBUG_TRACE_ADD_REMOTE_USER_STORE                                          \
  Trace::TraceEvent("user joined => '" + String(user_id) + "'") ;                  \
  Trace::TraceConfig("created storage for new remote user " + String(user_id)) ;   \
  if (TRACE_REMOTE_CHANNELS_VB)                                                    \
  {                                                                                \
    char* host      = LinJam::Client->GetHostName() ;                              \
    bool  has_bot   = NETWORK::KNOWN_HOSTS.contains(String(host)) ;                \
    bool  hide_bots = has_bot && bool(this->client[CONFIG::SHOULD_HIDE_BOTS_ID]) ; \
    float u_vol     = CONFIG::DEFAULT_VOLUME ;                                     \
    bool  u_mute    = CONFIG::DEFAULT_IS_MUTED ;                                   \
    float u_pan     = CONFIG::DEFAULT_PAN ;                                        \
    int   u_idx     = -1 ; String u_name ; Identifier u_id ;                       \
    while ((u_name = LinJam::GetRemoteUserName(++u_idx)).isNotEmpty())             \
      { u_id = makeUserId(u_name) ; if (user_id == u_id) break ; }                 \
    DEBUG_TRACE_REMOTE_CHANNELS                                                    \
  }

#else // DEBUG

// storage
#define DEBUG_TRACE_LOAD_CONFIG           ;
#define DEBUG_TRACE_SANITIZE_CONFIG       ;
#define DEBUG_TRACE_CONFIG_TYPES_VB       ;
#define DEBUG_TRACE_SANITY_CHECK          ;
//#define DEBUG_TRACE_SANITY_CHECK_USER   ;
#define DEBUG_TRACE_SANITY_CHECK_CHANNEL  ;
#define DEBUG_TRACE_STORE_CONFIG          ;
#define DEBUG_TRACE_CONFIG_VALUE_CHANGED  ;
#define DEBUG_TRACE_CONFIG_TREE_CHANGED   ;
#define DEBUG_TRACE_CONFIG_TREE_ADDED     ;
#define DEBUG_TRACE_CONFIG_TREE_REMOVED   ;
// channels
#define DEBUG_TRACE_STEREO_STATUS         ;
#define DEBUG_TRACE_MONO_STATUS           ;
#define DEBUG_TRACE_ADD_CHANNEL_STORE     ;
#define DEBUG_TRACE_DESTROY_CHANNEL_STORE ;
#define DEBUG_TRACE_ADD_REMOTE_USER_STORE ;

#endif // DEBUG
