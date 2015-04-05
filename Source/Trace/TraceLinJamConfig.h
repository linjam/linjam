#if DEBUG

#include "TraceLinJam.h"


/* storage */

#define DEBUG_TRACE_LOAD_CONFIG                                                   \
  Identifier root_node_id = CONFIG::STORAGE_ID ;                                  \
  if (default_xml == nullptr || !default_xml->hasTagName(root_node_id))           \
      Trace::TraceConfig("default config invalid - bailing") ;                    \
  else Trace::TraceConfig("default config loaded") ;                              \
  if (stored_xml == nullptr)                                                      \
      Trace::TraceConfig("stored config not found - falling back on defaults") ;  \
  else if (!stored_xml->hasTagName(CONFIG::STORAGE_ID))                           \
      Trace::TraceConfig("stored config is invalid - falling back on defaults") ; \
  else Trace::TraceConfig("stored config found") ;

#define DEBUG_TRACE_DUMP_CONFIG                                                         \
  String latest_version = String(CONFIG::CONFIG_VERSION) ;                              \
  Trace::TraceConfig("stored config parsed successfully v" + String(stored_version) +   \
                     ((do_versions_match) ? ""                                  :       \
                     " (latest is v" + latest_version + " - restoring defualts)")   ) ; \
  if (TRACE_DUMP_CONFIG && has_stored_config)                                           \
    Trace::TraceConfig(Trace::DumpConfig(ValueTree::fromXml(*default_xml) ,             \
                                         ValueTree::fromXml(*stored_xml)  , "  "))      ;

#if TRACE_CONFIG_TYPES
#  define DEBUG_TRACE_CONFIG_TYPES_VB                                                 \
  String parent_id = (node_id == CONFIG::STORAGE_ID) ?                "root::" :      \
                     (grandparent_node == this->remoteUsers)                   ?      \
                     CONFIG::REMOTES_KEY + " " + String(parent_node.getType()) :      \
                     String(parent_node.getType())                             ;      \
  String restore_msg = "restoring types for " + parent_id + "::" + String(node_id) ;  \
  int n_properties   = config_store.getNumProperties() ;                              \
  int n_children     = config_store.getNumChildren() ;                                \
  if (!types_store.isValid() && !!n_properties)                                       \
    Trace::TraceError("error " + restore_msg + " - missing CONFIG_TYPES") ;           \
  else                                                                                \
    Trace::TraceConfig(restore_msg + " (" + String(n_properties) + " properties - " + \
                                            String(n_children  ) + " children)"     ) ;
#  define DEBUG_TRACE_CONFIG_TYPES_VB_EACH                                            \
  bool   is_valid = is_bool || is_double || is_int || is_string ;                     \
  String type     = (is_valid) ? Trace::VarType(config_store[key]) : "(deleted)" ;    \
  Trace::TraceConfig("  " + String(key).paddedRight(' ' , 20) + " => " + type) ;
#else // TRACE_CONFIG_TYPES
#  define DEBUG_TRACE_CONFIG_TYPES_VB ;
#  define DEBUG_TRACE_CONFIG_TYPES_VB_EACH ;
#endif // TRACE_CONFIG_TYPES

#define DEBUG_TRACE_VALIDATE_USER                                                      \
  String user_name = String(user_store.getType()) ;                                    \
  if (!user_has_useridx_property)                                                      \
  {                                                                                    \
    Trace::TraceMissingProperty(user_name , CONFIG::USER_IDX_KEY) ;                    \
    Trace::TraceError("destroying invalid remote channel store '" + user_name + "'") ; \
  }

#define DEBUG_TRACE_VALIDATE_CHANNEL                                                       \
  String channels_name = String(channels.getType()) ;                                      \
  String channel_name  = LinJam::GetStoredChannelName(channel) ;                           \
                                                                                           \
  /* query channel datatypes */                                                            \
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
    Trace::TraceTypeMismatch(channel             ,         CONFIG::CHANNEL_NAME_KEY ,      \
                             CONFIG::STRING_TYPE , channel[CONFIG::CHANNEL_NAME_ID] ,      \
                             channels_name                                          ) ;    \
  if (!channel_idx_is_int)                                                                 \
    Trace::TraceTypeMismatch(channel             ,         CONFIG::CHANNEL_IDX_KEY  ,      \
                             CONFIG::INT_TYPE    , channel[CONFIG::CHANNEL_IDX_ID ] ,      \
                             channels_name                                          ) ;    \
  if (!channel_pair_idx_is_int)                                                            \
    Trace::TraceTypeMismatch(channel             ,         CONFIG::PAIR_IDX_KEY     ,      \
                             CONFIG::INT_TYPE    , channel[CONFIG::PAIR_IDX_ID    ] ,      \
                             channels_name                                          ) ;    \
  if (!channel_volume_is_double)                                                           \
    Trace::TraceTypeMismatch(channel             ,         CONFIG::VOLUME_KEY       ,      \
                             CONFIG::DOUBLE_TYPE , channel[CONFIG::VOLUME_ID      ] ,      \
                             channels_name                                          ) ;    \
  if (!channel_pan_is_double)                                                              \
    Trace::TraceTypeMismatch(channel             ,         CONFIG::PAN_KEY          ,      \
                             CONFIG::DOUBLE_TYPE , channel[CONFIG::PAN_ID         ] ,      \
                             channels_name                                          ) ;    \
  if (!channel_xmit_is_bool)                                                               \
    Trace::TraceTypeMismatch(channel             ,         CONFIG::IS_XMIT_RCV_KEY  ,      \
                             CONFIG::BOOL_TYPE   , channel[CONFIG::IS_XMIT_RCV_ID ] ,      \
                             channels_name                                          ) ;    \
  if (!channel_mute_is_bool)                                                               \
    Trace::TraceTypeMismatch(channel             ,         CONFIG::IS_MUTED_KEY     ,      \
                             CONFIG::BOOL_TYPE   , channel[CONFIG::IS_MUTED_ID    ] ,      \
                             channels_name                                          ) ;    \
  if (!channel_solo_is_bool)                                                               \
    Trace::TraceTypeMismatch(channel             ,         CONFIG::IS_SOLO_KEY      ,      \
                             CONFIG::BOOL_TYPE   , channel[CONFIG::IS_SOLO_ID     ] ,      \
                             channels_name                                          ) ;    \
  if (!channel_source_is_int)                                                              \
    Trace::TraceTypeMismatch(channel             ,         CONFIG::SOURCE_N_KEY     ,      \
                             CONFIG::INT_TYPE    , channel[CONFIG::SOURCE_N_ID    ] ,      \
                             channels_name                                          ) ;    \
  if (!channel_stereo_is_int)                                                              \
    Trace::TraceTypeMismatch(channel             ,         CONFIG::STEREO_KEY       ,      \
                             CONFIG::INT_TYPE    , channel[CONFIG::STEREO_ID      ] ,      \
                             channels_name                                          ) ;    \
  if (!channel_vuleft_is_double)                                                           \
    Trace::TraceTypeMismatch(channel             ,         CONFIG::VU_LEFT_KEY      ,      \
                             CONFIG::DOUBLE_TYPE , channel[CONFIG::VU_LEFT_KEY    ] ,      \
                             channels_name                                          ) ;    \
  if (!channel_vuright_is_double)                                                          \
    Trace::TraceTypeMismatch(channel             ,         CONFIG::VU_RIGHT_KEY     ,      \
                             CONFIG::DOUBLE_TYPE , channel[CONFIG::VU_RIGHT_KEY   ] ,      \
                             channels_name                                          ) ;    \
                                                                                           \
  /* validate channel properties */                                                        \
  if (!channel_has_channelname_property || !channel_has_channelidx_property ||             \
      !channel_has_pairidx_property     || !channel_has_volume_property     ||             \
      !channel_has_pan_property         || !channel_has_xmit_property       ||             \
      !channel_has_mute_property        || !channel_has_solo_property       ||             \
      !channel_has_source_property      || !channel_has_stereo_property     ||             \
      !channel_has_vuleft_property      || !channel_has_vuright_property     )             \
    Trace::TraceError("destroying invalid " + channels_name +                              \
                      " channel store '"    + channel_name  + "'") ;

#define DEBUG_VALIDATE_CONFIG_DEFAULTS                                            \
  /* query default values */                                                      \
  bool has_valid_version_declaration    = CONFIG::CONFIG_VERSION > 0.0 ;          \
  bool has_valid_sessiondir_declaration = CLIENT::SESSION_DIRNAME.isNotEmpty() ;  \
  bool has_valid_logfile_declaration    = CLIENT::LOG_FILENAME   .isNotEmpty() ;  \
                                                                                  \
  /* trace invalid default values */                                              \
  if (!has_valid_version_declaration)                                             \
    Trace::TraceInvalidDefault(CONFIG::CONFIG_VERSION_KEY) ;                      \
  if (!has_valid_sessiondir_declaration)                                          \
    Trace::TraceInvalidDefault("CLIENT::SESSION_DIRNAME") ;                       \
  if (!has_valid_logfile_declaration)                                             \
    Trace::TraceInvalidDefault("CLIENT::LOG_FILENAME") ;                          \
                                                                                  \
  /* modify return value */                                                       \
  is_valid = is_valid                                                          && \
             has_valid_version_declaration && has_valid_sessiondir_declaration && \
             has_valid_logfile_declaration                                        ;

#define DEBUG_VALIDATE_CONFIG_ROOT                                                     \
  /* query root properties */                                                          \
  bool root_has_configversion_property = root.hasProperty(CONFIG::CONFIG_VERSION_ID) ; \
                                                                                       \
  /* query root datatypes */                                                           \
  bool config_version_is_double = root[CONFIG::CONFIG_VERSION_ID].isDouble() ;         \
                                                                                       \
  /* trace missing root properties */                                                  \
  if (!root_has_configversion_property)                                                \
    Trace::TraceMissingProperty(CONFIG::STORAGE_KEY , CONFIG::CONFIG_VERSION_KEY) ;    \
                                                                                       \
  /* trace invalid root datatypes */                                                   \
  if (!config_version_is_double)                                                       \
    Trace::TraceTypeMismatch(root                ,      CONFIG::CONFIG_VERSION_KEY ,   \
                             CONFIG::DOUBLE_TYPE , root[CONFIG::CONFIG_VERSION_ID] ) ; \
                                                                                       \
  /* modify return value */                                                            \
  is_valid = is_valid                                                    &&            \
             root_has_configversion_property && config_version_is_double               ;

#define DEBUG_VALIDATE_CONFIG_GUI                                                 \
  /* query gui properties */                                                      \
  bool gui_has_fontsize_property  = gui.hasProperty(CONFIG::FONT_SIZE_ID ) ;      \
  bool gui_has_updateivl_property = gui.hasProperty(CONFIG::UPDATE_IVL_ID) ;      \
                                                                                  \
  /* query gui datatypes */                                                       \
  bool fontsize_is_int  = gui[CONFIG::FONT_SIZE_ID ].isInt() ;                    \
  bool updateivl_is_int = gui[CONFIG::UPDATE_IVL_ID].isInt() ;                    \
                                                                                  \
  /* trace missing gui properties */                                              \
  if (!gui_has_fontsize_property)                                                 \
    Trace::TraceMissingProperty(CONFIG::GUI_KEY , CONFIG::FONT_SIZE_KEY ) ;       \
  if (!gui_has_updateivl_property)                                                \
    Trace::TraceMissingProperty(CONFIG::GUI_KEY , CONFIG::UPDATE_IVL_KEY) ;       \
                                                                                  \
  /* trace gui datatypes */                                                       \
  if (!fontsize_is_int)                                                           \
    Trace::TraceTypeMismatch(gui              ,        CONFIG::FONT_SIZE_KEY  ,   \
                             CONFIG::INT_TYPE , client[CONFIG::FONT_SIZE_ID ] ) ; \
  if (!updateivl_is_int)                                                          \
    Trace::TraceTypeMismatch(gui              ,        CONFIG::UPDATE_IVL_KEY ,   \
                             CONFIG::INT_TYPE , client[CONFIG::UPDATE_IVL_ID] ) ; \
                                                                                  \
  /* modify return value */                                                       \
  is_valid = is_valid                                       &&                    \
             gui_has_fontsize_property && fontsize_is_int   &&                    \
             gui_has_updateivl_property && updateivl_is_int                       ;

#define DEBUG_VALIDATE_CONFIG_CLIENT                                                      \
  /* query client properties */                                                           \
  bool client_has_saveaudio_property  = client.hasProperty(CONFIG::SAVE_AUDIO_MODE_ID ) ; \
  bool client_has_mixdown_property    = client.hasProperty(CONFIG::MIXDOWN_MODE_KEY   ) ; \
  bool client_has_savelog_property    = client.hasProperty(CONFIG::SHOULD_SAVE_LOG_ID ) ; \
  bool client_has_debuglevel_property = client.hasProperty(CONFIG::DEBUG_LEVEL_ID     ) ; \
  bool client_has_hide_bots_property  = client.hasProperty(CONFIG::SHOULD_HIDE_BOTS_ID) ; \
                                                                                          \
  /* query client datatypes */                                                            \
  bool save_audio_is_int        = client[CONFIG::SAVE_AUDIO_MODE_ID ].isInt()  ;          \
  bool mixdown_is_int           = client[CONFIG::MIXDOWN_MODE_KEY   ].isInt()  ;          \
  bool save_log_is_bool         = client[CONFIG::SHOULD_SAVE_LOG_ID ].isBool() ;          \
  bool debug_level_is_int       = client[CONFIG::DEBUG_LEVEL_ID     ].isInt()  ;          \
  bool should_hide_bots_is_bool = client[CONFIG::SHOULD_HIDE_BOTS_ID].isBool() ;          \
                                                                                          \
  /* trace missing client properties */                                                   \
  if (!client_has_saveaudio_property)                                                     \
    Trace::TraceMissingProperty(CONFIG::CLIENT_KEY , CONFIG::SAVE_AUDIO_MODE_KEY ) ;      \
  if (!client_has_mixdown_property)                                                       \
    Trace::TraceMissingProperty(CONFIG::CLIENT_KEY , CONFIG::MIXDOWN_MODE_KEY    ) ;      \
  if (!client_has_savelog_property)                                                       \
    Trace::TraceMissingProperty(CONFIG::CLIENT_KEY , CONFIG::SHOULD_SAVE_LOG_KEY ) ;      \
  if (!client_has_debuglevel_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::CLIENT_KEY , CONFIG::DEBUG_LEVEL_KEY     ) ;      \
  if (!client_has_hide_bots_property)                                                     \
    Trace::TraceMissingProperty(CONFIG::CLIENT_KEY , CONFIG::SHOULD_HIDE_BOTS_KEY) ;      \
                                                                                          \
  /* trace invalid client datatypes */                                                    \
  if (!save_audio_is_int)                                                                 \
    Trace::TraceTypeMismatch(client            ,        CONFIG::SAVE_AUDIO_MODE_KEY  ,    \
                             CONFIG::INT_TYPE  , client[CONFIG::SAVE_AUDIO_MODE_ID ] ) ;  \
  if (!mixdown_is_int)                                                                    \
    Trace::TraceTypeMismatch(client            ,        CONFIG::MIXDOWN_MODE_KEY     ,    \
                             CONFIG::INT_TYPE  , client[CONFIG::MIXDOWN_MODE_KEY   ] ) ;  \
  if (!save_log_is_bool)                                                                  \
    Trace::TraceTypeMismatch(client            ,        CONFIG::SHOULD_SAVE_LOG_KEY  ,    \
                             CONFIG::BOOL_TYPE , client[CONFIG::SHOULD_SAVE_LOG_ID ] ) ;  \
  if (!debug_level_is_int)                                                                \
    Trace::TraceTypeMismatch(client            ,        CONFIG::DEBUG_LEVEL_KEY      ,    \
                             CONFIG::INT_TYPE  , client[CONFIG::DEBUG_LEVEL_ID     ] ) ;  \
  if (!should_hide_bots_is_bool)                                                          \
    Trace::TraceTypeMismatch(client            ,        CONFIG::SHOULD_HIDE_BOTS_KEY ,    \
                             CONFIG::BOOL_TYPE , client[CONFIG::SHOULD_HIDE_BOTS_ID] ) ;  \
                                                                                          \
  /* modify return value */                                                               \
  is_valid = is_valid                                                   &&                \
             client_has_saveaudio_property  && save_audio_is_int        &&                \
             client_has_mixdown_property    && mixdown_is_int           &&                \
             client_has_savelog_property    && save_log_is_bool         &&                \
             client_has_debuglevel_property && debug_level_is_int       &&                \
             client_has_hide_bots_property  && should_hide_bots_is_bool                   ;

#define DEBUG_VALIDATE_CONFIG_BLACKLIST                                                 \
  /* query blacklist properties */                                                      \
  bool blacklist_has_mode_property = blacklist.hasProperty(CONFIG::SUBSCRIBE_MODE_ID) ; \
                                                                                        \
  /* query blacklist datatypes */                                                       \
  bool subscribemode_is_int = blacklist[CONFIG::SUBSCRIBE_MODE_ID].isInt() ;            \
                                                                                        \
  /* trace missing blacklist properties */                                              \
  if (!blacklist_has_mode_property)                                                     \
    Trace::TraceMissingProperty(CONFIG::BLACKLIST_KEY , CONFIG::SUBSCRIBE_MODE_KEY) ;   \
                                                                                        \
  /* trace blacklist datatypes */                                                       \
  if (!subscribemode_is_int)                                                            \
    Trace::TraceTypeMismatch(blacklist        ,        CONFIG::SUBSCRIBE_MODE_KEY ,     \
                             CONFIG::INT_TYPE , client[CONFIG::SUBSCRIBE_MODE_ID] ) ;   \
                                                                                        \
  /* modify return value */                                                             \
  is_valid = is_valid                                            &&                     \
             blacklist_has_mode_property && subscribemode_is_int                        ;

#  define DEBUG_VALIDATE_CONFIG_AUDIO_WIN                                                \
  /* query win audio properties */                                                       \
  bool audio_has_api_property            =                                               \
      audio.hasProperty(CONFIG::AUDIO_API_ID      ) ;                                    \
  bool audio_has_asiodriver_property     =                                               \
      audio.hasProperty(CONFIG::ASIO_DRIVER_ID    ) ;                                    \
  bool audio_has_asioinputb_property     =                                               \
      audio.hasProperty(CONFIG::ASIO_INPUTB_ID    ) ;                                    \
  bool audio_has_asioinpute_property     =                                               \
      audio.hasProperty(CONFIG::ASIO_INPUTE_ID    ) ;                                    \
  bool audio_has_asiooutputb_property    =                                               \
      audio.hasProperty(CONFIG::ASIO_OUTPUTB_ID   ) ;                                    \
  bool audio_has_asiooutpute_property    =                                               \
      audio.hasProperty(CONFIG::ASIO_OUTPUTE_ID   ) ;                                    \
  bool audio_has_ksinput_property        =                                               \
      audio.hasProperty(CONFIG::KS_INPUT_ID       ) ;                                    \
  bool audio_has_ksoutput_property       =                                               \
      audio.hasProperty(CONFIG::KS_OUTPUT_ID      ) ;                                    \
  bool audio_has_kssamplerate_property   =                                               \
      audio.hasProperty(CONFIG::KS_SAMPLERATE_ID  ) ;                                    \
  bool audio_has_ksbitdepth_property     =                                               \
      audio.hasProperty(CONFIG::KS_BITDEPTH_ID    ) ;                                    \
  bool audio_has_ksnblocks_property      =                                               \
      audio.hasProperty(CONFIG::KS_NBLOCKS_ID     ) ;                                    \
  bool audio_has_ksblocksize_property    =                                               \
      audio.hasProperty(CONFIG::KS_BLOCKSIZE_ID   ) ;                                    \
  bool audio_has_dsinput_property        =                                               \
      audio.hasProperty(CONFIG::DS_INPUT_ID       ) ;                                    \
  bool audio_has_dsoutput_property       =                                               \
      audio.hasProperty(CONFIG::DS_OUTPUT_ID      ) ;                                    \
  bool audio_has_dssamplerate_property   =                                               \
      audio.hasProperty(CONFIG::DS_SAMPLERATE_ID  ) ;                                    \
  bool audio_has_dsbitdepth_property     =                                               \
      audio.hasProperty(CONFIG::DS_BITDEPTH_ID    ) ;                                    \
  bool audio_has_dsnblocks_property      =                                               \
      audio.hasProperty(CONFIG::DS_NBLOCKS_ID     ) ;                                    \
  bool audio_has_dsblocksize_property    =                                               \
      audio.hasProperty(CONFIG::DS_BLOCKSIZE_ID   ) ;                                    \
  bool audio_has_waveinput_property      =                                               \
      audio.hasProperty(CONFIG::WAVE_INPUT_ID     ) ;                                    \
  bool audio_has_waveoutput_property     =                                               \
      audio.hasProperty(CONFIG::WAVE_OUTPUT_ID    ) ;                                    \
  bool audio_has_wavesamplerate_property =                                               \
      audio.hasProperty(CONFIG::WAVE_SAMPLERATE_ID) ;                                    \
  bool audio_has_wavebitdepth_property   =                                               \
      audio.hasProperty(CONFIG::WAVE_BITDEPTH_ID  ) ;                                    \
  bool audio_has_wavenblocks_property    =                                               \
      audio.hasProperty(CONFIG::WAVE_NBLOCKS_ID   ) ;                                    \
  bool audio_has_waveblocksize_property  =                                               \
      audio.hasProperty(CONFIG::WAVE_BLOCKSIZE_ID ) ;                                    \
                                                                                         \
  /* query win audio datatypes */                                                        \
  bool audio_api_is_int       = audio[CONFIG::AUDIO_API_ID      ].isInt()    ;           \
  bool asio_driver_is_int     = audio[CONFIG::ASIO_DRIVER_ID    ].isInt()    ;           \
  bool asio_inputb_is_int     = audio[CONFIG::ASIO_INPUTB_ID    ].isInt()    ;           \
  bool asio_inoute_is_int     = audio[CONFIG::ASIO_INPUTE_ID    ].isInt()    ;           \
  bool asio_outputb_is_int    = audio[CONFIG::ASIO_OUTPUTB_ID   ].isInt()    ;           \
  bool asio_outpute_is_int    = audio[CONFIG::ASIO_OUTPUTE_ID   ].isInt()    ;           \
  bool ks_input_is_int        = audio[CONFIG::KS_INPUT_ID       ].isInt()    ;           \
  bool ks_output_is_int       = audio[CONFIG::KS_OUTPUT_ID      ].isInt()    ;           \
  bool ks_samplerate_is_int   = audio[CONFIG::KS_SAMPLERATE_ID  ].isInt()    ;           \
  bool ks_bitdepth_is_int     = audio[CONFIG::KS_BITDEPTH_ID    ].isInt()    ;           \
  bool ks_nblocks_is_int      = audio[CONFIG::KS_NBLOCKS_ID     ].isInt()    ;           \
  bool ks_blocksize_is_int    = audio[CONFIG::KS_BLOCKSIZE_ID   ].isInt()    ;           \
  bool ds_input_is_string     = audio[CONFIG::DS_INPUT_ID       ].isString() ;           \
  bool ds_output_is_string    = audio[CONFIG::DS_OUTPUT_ID      ].isString() ;           \
  bool ds_samplerate_is_int   = audio[CONFIG::DS_SAMPLERATE_ID  ].isInt()    ;           \
  bool ds_bitdepth_is_int     = audio[CONFIG::DS_BITDEPTH_ID    ].isInt()    ;           \
  bool ds_nblocks_is_int      = audio[CONFIG::DS_NBLOCKS_ID     ].isInt()    ;           \
  bool ds_blocksize_is_int    = audio[CONFIG::DS_BLOCKSIZE_ID   ].isInt()    ;           \
  bool wave_input_is_int      = audio[CONFIG::WAVE_INPUT_ID     ].isInt()    ;           \
  bool wave_output_is_int     = audio[CONFIG::WAVE_OUTPUT_ID    ].isInt()    ;           \
  bool wave_samplerate_is_int = audio[CONFIG::WAVE_SAMPLERATE_ID].isInt()    ;           \
  bool wave_bitdepth_is_int   = audio[CONFIG::WAVE_BITDEPTH_ID  ].isInt()    ;           \
  bool wave_nblocks_is_int    = audio[CONFIG::WAVE_NBLOCKS_ID   ].isInt()    ;           \
  bool wave_blocksize_is_int  = audio[CONFIG::WAVE_BLOCKSIZE_ID ].isInt()    ;           \
                                                                                         \
  /* trace missing win audio properties */                                               \
  if (!audio_has_api_property)                                                           \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::AUDIO_API_KEY      ) ;       \
  if (!audio_has_asiodriver_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::ASIO_DRIVER_KEY    ) ;       \
  if (!audio_has_asioinputb_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::ASIO_INPUTB_KEY    ) ;       \
  if (!audio_has_asioinpute_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::ASIO_INPUTE_KEY    ) ;       \
  if (!audio_has_asiooutputb_property)                                                   \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::ASIO_OUTPUTB_KEY   ) ;       \
  if (!audio_has_asiooutpute_property)                                                   \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::ASIO_OUTPUTE_KEY   ) ;       \
  if (!audio_has_ksinput_property)                                                       \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::KS_INPUT_KEY       ) ;       \
  if (!audio_has_ksoutput_property)                                                      \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::KS_OUTPUT_KEY      ) ;       \
  if (!audio_has_kssamplerate_property)                                                  \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::KS_SAMPLERATE_KEY  ) ;       \
  if (!audio_has_ksbitdepth_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::KS_BITDEPTH_KEY    ) ;       \
  if (!audio_has_ksnblocks_property)                                                     \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::KS_NBLOCKS_KEY     ) ;       \
  if (!audio_has_ksblocksize_property)                                                   \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::KS_BLOCKSIZE_KEY   ) ;       \
  if (!audio_has_dsinput_property)                                                       \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::DS_INPUT_KEY       ) ;       \
  if (!audio_has_dsoutput_property)                                                      \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::DS_OUTPUT_KEY      ) ;       \
  if (!audio_has_dssamplerate_property)                                                  \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::DS_SAMPLERATE_KEY  ) ;       \
  if (!audio_has_dsbitdepth_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::DS_BITDEPTH_KEY    ) ;       \
  if (!audio_has_dsnblocks_property)                                                     \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::DS_NBLOCKS_KEY     ) ;       \
  if (!audio_has_dsblocksize_property)                                                   \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::DS_BLOCKSIZE_KEY   ) ;       \
  if (!audio_has_waveinput_property)                                                     \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::WAVE_INPUT_KEY     ) ;       \
  if (!audio_has_waveoutput_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::WAVE_OUTPUT_KEY    ) ;       \
  if (!audio_has_wavesamplerate_property)                                                \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::WAVE_SAMPLERATE_KEY) ;       \
  if (!audio_has_wavebitdepth_property)                                                  \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::WAVE_BITDEPTH_KEY  ) ;       \
  if (!audio_has_wavenblocks_property)                                                   \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::WAVE_NBLOCKS_KEY   ) ;       \
  if (!audio_has_waveblocksize_property)                                                 \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::WAVE_BLOCKSIZE_KEY ) ;       \
                                                                                         \
  /* trace invalid win audio datatypes */                                                \
  if (!audio_api_is_int)                                                                 \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::AUDIO_API_KEY       ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::AUDIO_API_ID      ] ) ; \
  if (!asio_driver_is_int)                                                               \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::ASIO_DRIVER_KEY     ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::ASIO_DRIVER_ID    ] ) ; \
  if (!asio_inputb_is_int)                                                               \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::ASIO_INPUTB_KEY     ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::ASIO_INPUTB_ID    ] ) ; \
  if (!asio_inoute_is_int)                                                               \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::ASIO_INPUTE_KEY     ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::ASIO_INPUTE_ID    ] ) ; \
  if (!asio_outputb_is_int)                                                              \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::ASIO_OUTPUTB_KEY    ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::ASIO_OUTPUTB_ID   ] ) ; \
  if (!asio_outpute_is_int)                                                              \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::ASIO_OUTPUTE_KEY    ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::ASIO_OUTPUTE_ID   ] ) ; \
  if (!ks_input_is_int)                                                                  \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::KS_INPUT_KEY        ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::KS_INPUT_ID       ] ) ; \
  if (!ks_output_is_int)                                                                 \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::KS_OUTPUT_KEY       ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::KS_OUTPUT_ID      ] ) ; \
  if (!ks_samplerate_is_int)                                                             \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::KS_SAMPLERATE_KEY   ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::KS_SAMPLERATE_ID  ] ) ; \
  if (!ks_bitdepth_is_int)                                                               \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::KS_BITDEPTH_KEY     ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::KS_BITDEPTH_ID    ] ) ; \
  if (!ks_nblocks_is_int)                                                                \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::KS_NBLOCKS_KEY      ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::KS_NBLOCKS_ID     ] ) ; \
  if (!ks_blocksize_is_int)                                                              \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::KS_BLOCKSIZE_KEY    ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::KS_BLOCKSIZE_ID   ] ) ; \
  if (!ds_input_is_string)                                                               \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::DS_INPUT_KEY        ,   \
                             CONFIG::STRING_TYPE , audio[CONFIG::DS_INPUT_ID       ] ) ; \
  if (!ds_output_is_string)                                                              \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::DS_OUTPUT_KEY       ,   \
                             CONFIG::STRING_TYPE , audio[CONFIG::DS_OUTPUT_ID      ] ) ; \
  if (!ds_samplerate_is_int)                                                             \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::DS_SAMPLERATE_KEY   ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::DS_SAMPLERATE_ID  ] ) ; \
  if (!ds_bitdepth_is_int)                                                               \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::DS_BITDEPTH_KEY     ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::DS_BITDEPTH_ID    ] ) ; \
  if (!ds_nblocks_is_int)                                                                \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::DS_NBLOCKS_KEY      ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::DS_NBLOCKS_ID     ] ) ; \
  if (!ds_blocksize_is_int)                                                              \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::DS_BLOCKSIZE_KEY    ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::DS_BLOCKSIZE_ID   ] ) ; \
  if (!wave_input_is_int)                                                                \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::WAVE_INPUT_KEY      ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::WAVE_INPUT_ID     ] ) ; \
  if (!wave_output_is_int)                                                               \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::WAVE_OUTPUT_KEY     ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::WAVE_OUTPUT_ID    ] ) ; \
  if (!wave_samplerate_is_int)                                                           \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::WAVE_SAMPLERATE_KEY ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::WAVE_SAMPLERATE_ID] ) ; \
  if (!wave_bitdepth_is_int)                                                             \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::WAVE_BITDEPTH_KEY   ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::WAVE_BITDEPTH_ID  ] ) ; \
  if (!wave_nblocks_is_int)                                                              \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::WAVE_NBLOCKS_KEY    ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::WAVE_NBLOCKS_ID   ] ) ; \
  if (!wave_blocksize_is_int)                                                            \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::WAVE_BLOCKSIZE_KEY  ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::WAVE_BLOCKSIZE_ID ] ) ; \
                                                                                         \
  /* modify return value */                                                              \
  is_valid = is_valid                                                    &&              \
             audio_has_api_property            && audio_api_is_int       &&              \
             audio_has_asiodriver_property     && asio_driver_is_int     &&              \
             audio_has_asioinputb_property     && asio_inputb_is_int     &&              \
             audio_has_asioinpute_property     && asio_inoute_is_int     &&              \
             audio_has_asiooutputb_property    && asio_outputb_is_int    &&              \
             audio_has_asiooutpute_property    && asio_outpute_is_int    &&              \
             audio_has_ksinput_property        && ks_input_is_int        &&              \
             audio_has_ksoutput_property       && ks_output_is_int       &&              \
             audio_has_kssamplerate_property   && ks_samplerate_is_int   &&              \
             audio_has_ksbitdepth_property     && ks_bitdepth_is_int     &&              \
             audio_has_ksnblocks_property      && ks_nblocks_is_int      &&              \
             audio_has_ksblocksize_property    && ks_blocksize_is_int    &&              \
             audio_has_dsinput_property        && ds_input_is_string     &&              \
             audio_has_dsoutput_property       && ds_output_is_string    &&              \
             audio_has_dssamplerate_property   && ds_samplerate_is_int   &&              \
             audio_has_dsbitdepth_property     && ds_bitdepth_is_int     &&              \
             audio_has_dsnblocks_property      && ds_nblocks_is_int      &&              \
             audio_has_dsblocksize_property    && ds_blocksize_is_int    &&              \
             audio_has_waveinput_property      && wave_input_is_int      &&              \
             audio_has_waveoutput_property     && wave_output_is_int     &&              \
             audio_has_wavesamplerate_property && wave_samplerate_is_int &&              \
             audio_has_wavebitdepth_property   && wave_bitdepth_is_int   &&              \
             audio_has_wavenblocks_property    && wave_nblocks_is_int    &&              \
             audio_has_waveblocksize_property  && wave_blocksize_is_int                  ;

#define DEBUG_VALIDATE_CONFIG_AUDIO_MAC                                                \
  /* query mac audio properties */                                                     \
  bool audio_has_api_property          = audio.hasProperty(CONFIG::AUDIO_API_ID    ) ; \
  bool audio_has_cainput_property      = audio.hasProperty(CONFIG::CA_INPUT_ID     ) ; \
  bool audio_has_caoutput_property     = audio.hasProperty(CONFIG::CA_OUTPUT_ID    ) ; \
  bool audio_has_canchannels_property  = audio.hasProperty(CONFIG::CA_NCHANNELS_ID ) ; \
  bool audio_has_casamplerate_property = audio.hasProperty(CONFIG::CA_SAMPLERATE_ID) ; \
  bool audio_has_cabitdepth_property   = audio.hasProperty(CONFIG::CA_BITDEPTH_ID  ) ; \
                                                                                       \
  /* query mac audio datatypes */                                                      \
  bool audio_api_is_int     = audio[CONFIG::AUDIO_API_ID    ].isInt()    ;             \
  bool ca_input_is_string   = audio[CONFIG::CA_INPUT_ID     ].isString() ;             \
  bool ca_output_is_string  = audio[CONFIG::CA_OUTPUT_ID    ].isString() ;             \
  bool ca_nchannels_is_int  = audio[CONFIG::CA_NCHANNELS_ID ].isInt()    ;             \
  bool ca_samplerate_is_int = audio[CONFIG::CA_SAMPLERATE_ID].isInt()    ;             \
  bool ca_bitdepth_is_int   = audio[CONFIG::CA_BITDEPTH_ID  ].isInt()    ;             \
                                                                                       \
  /* trace missing mac audio properties */                                             \
  if (!audio_has_api_property)                                                         \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::AUDIO_API_KEY    ) ;       \
  if (!audio_has_cainput_property)                                                     \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::CA_INPUT_KEY     ) ;       \
  if (!audio_has_caoutput_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::CA_OUTPUT_KEY    ) ;       \
  if (!audio_has_canchannels_property)                                                 \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::CA_NCHANNELS_KEY ) ;       \
  if (!audio_has_casamplerate_property)                                                \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::CA_SAMPLERATE_KEY) ;       \
  if (!audio_has_cabitdepth_property)                                                  \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::CA_BITDEPTH_KEY  ) ;       \
                                                                                       \
  /* trace invalid mac audio datatypes */                                              \
  if (!audio_api_is_int)                                                               \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::AUDIO_API_KEY     ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::AUDIO_API_ID    ] ) ; \
  if (!ca_input_is_string)                                                             \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::CA_INPUT_KEY      ,   \
                             CONFIG::STRING_TYPE , audio[CONFIG::CA_INPUT_ID     ] ) ; \
  if (!ca_output_is_string)                                                            \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::CA_OUTPUT_KEY     ,   \
                             CONFIG::STRING_TYPE , audio[CONFIG::CA_OUTPUT_ID    ] ) ; \
  if (!ca_nchannels_is_int)                                                            \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::CA_NCHANNELS_KEY  ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::CA_NCHANNELS_ID ] ) ; \
  if (!ca_samplerate_is_int)                                                           \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::CA_SAMPLERATE_KEY ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::CA_SAMPLERATE_ID] ) ; \
  if (!ca_bitdepth_is_int)                                                             \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::CA_BITDEPTH_KEY   ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::CA_BITDEPTH_ID  ] ) ; \
                                                                                       \
  /* modify return value */                                                            \
  is_valid = is_valid                                                &&                \
             audio_has_api_property          && audio_api_is_int     &&                \
             audio_has_cainput_property      && ca_input_is_string   &&                \
             audio_has_caoutput_property     && ca_output_is_string  &&                \
             audio_has_canchannels_property  && ca_nchannels_is_int  &&                \
             audio_has_casamplerate_property && ca_samplerate_is_int &&                \
             audio_has_cabitdepth_property   && ca_bitdepth_is_int                     ;

#define DEBUG_VALIDATE_CONFIG_AUDIO_NIX                                                  \
  /* query nix audio properties */                                                       \
  bool audio_has_api_property            =                                               \
      audio.hasProperty(CONFIG::AUDIO_API_ID      ) ;                                    \
  bool audio_has_jackserver_property     =                                               \
      audio.hasProperty(CONFIG::JACK_SERVER_ID    ) ;                                    \
  bool audio_has_jackname_property       =                                               \
      audio.hasProperty(CONFIG::JACK_NAME_ID      ) ;                                    \
  bool audio_has_jackninputs_property    =                                               \
      audio.hasProperty(CONFIG::JACK_NINPUTS_ID   ) ;                                    \
  bool audio_has_jacknoutputs_property   =                                               \
      audio.hasProperty(CONFIG::JACK_NOUTPUTS_ID  ) ;                                    \
  bool audio_has_alsainput_property      =                                               \
      audio.hasProperty(CONFIG::ALSA_INPUT_ID     ) ;                                    \
  bool audio_has_alsaoutput_property     =                                               \
      audio.hasProperty(CONFIG::ALSA_OUTPUT_ID    ) ;                                    \
  bool audio_has_alsanchannels_property  =                                               \
      audio.hasProperty(CONFIG::ALSA_NCHANNELS_ID ) ;                                    \
  bool audio_has_alsasamplerate_property =                                               \
      audio.hasProperty(CONFIG::ALSA_SAMPLERATE_ID) ;                                    \
  bool audio_has_alsabitdepth_property   =                                               \
      audio.hasProperty(CONFIG::ALSA_BITDEPTH_ID  ) ;                                    \
  bool audio_has_alsanblocks_property    =                                               \
      audio.hasProperty(CONFIG::ALSA_NBLOCKS_ID   ) ;                                    \
  bool audio_has_alsablocksize_property  =                                               \
      audio.hasProperty(CONFIG::ALSA_BLOCKSIZE_ID ) ;                                    \
                                                                                         \
  /* query nix audio datatypes */                                                        \
  bool audio_api_is_int       = audio[CONFIG::AUDIO_API_ID      ].isInt()    ;           \
  bool jack_server_is_int     = audio[CONFIG::JACK_SERVER_ID    ].isInt()    ;           \
  bool jack_name_is_string    = audio[CONFIG::JACK_NAME_ID      ].isString() ;           \
  bool jack_ninputs_is_int    = audio[CONFIG::JACK_NINPUTS_ID   ].isInt()    ;           \
  bool jack_noutputs_is_int   = audio[CONFIG::JACK_NOUTPUTS_ID  ].isInt()    ;           \
  bool alsa_input_is_string   = audio[CONFIG::ALSA_INPUT_ID     ].isString() ;           \
  bool alsa_output_is_string  = audio[CONFIG::ALSA_OUTPUT_ID    ].isString() ;           \
  bool alsa_nchannels_is_int  = audio[CONFIG::ALSA_NCHANNELS_ID ].isInt()    ;           \
  bool alsa_samplerate_is_int = audio[CONFIG::ALSA_SAMPLERATE_ID].isInt()    ;           \
  bool alsa_bitdepth_is_int   = audio[CONFIG::ALSA_BITDEPTH_ID  ].isInt()    ;           \
  bool alsa_nblocks_is_int    = audio[CONFIG::ALSA_NBLOCKS_ID   ].isInt()    ;           \
  bool alsa_blocksize_is_int  = audio[CONFIG::ALSA_BLOCKSIZE_ID ].isInt()    ;           \
                                                                                         \
  /* trace missing nix audio properties */                                               \
  if (!audio_has_api_property)                                                           \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::AUDIO_API_KEY      ) ;       \
  if (!audio_has_jackserver_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::JACK_SERVER_KEY    ) ;       \
  if (!audio_has_jackname_property)                                                      \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::JACK_NAME_KEY      ) ;       \
  if (!audio_has_jackninputs_property)                                                   \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::JACK_NINPUTS_KEY   ) ;       \
  if (!audio_has_jacknoutputs_property)                                                  \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::JACK_NOUTPUTS_KEY  ) ;       \
  if (!audio_has_alsainput_property)                                                     \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::ALSA_INPUT_KEY     ) ;       \
  if (!audio_has_alsaoutput_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::ALSA_OUTPUT_KEY    ) ;       \
  if (!audio_has_alsanchannels_property)                                                 \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::ALSA_NCHANNELS_KEY ) ;       \
  if (!audio_has_alsasamplerate_property)                                                \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::ALSA_SAMPLERATE_KEY) ;       \
  if (!audio_has_alsabitdepth_property)                                                  \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::ALSA_BITDEPTH_KEY  ) ;       \
  if (!audio_has_alsanblocks_property)                                                   \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::ALSA_NBLOCKS_KEY   ) ;       \
  if (!audio_has_alsablocksize_property)                                                 \
    Trace::TraceMissingProperty(CONFIG::AUDIO_KEY , CONFIG::ALSA_BLOCKSIZE_KEY ) ;       \
                                                                                         \
  /* trace invalid nix audio datatypes */                                                \
  if (!audio_api_is_int)                                                                 \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::AUDIO_API_KEY       ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::AUDIO_API_ID      ] ) ; \
  if (!jack_server_is_int)                                                               \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::JACK_SERVER_KEY     ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::JACK_SERVER_ID    ] ) ; \
  if (!jack_name_is_string)                                                              \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::JACK_NAME_KEY       ,   \
                             CONFIG::STRING_TYPE , audio[CONFIG::JACK_NAME_ID      ] ) ; \
  if (!jack_ninputs_is_int)                                                              \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::JACK_NINPUTS_KEY    ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::JACK_NINPUTS_ID   ] ) ; \
  if (!jack_noutputs_is_int)                                                             \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::JACK_NOUTPUTS_KEY   ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::JACK_NOUTPUTS_ID  ] ) ; \
  if (!alsa_input_is_string)                                                             \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::ALSA_INPUT_KEY      ,   \
                             CONFIG::STRING_TYPE , audio[CONFIG::ALSA_INPUT_ID     ] ) ; \
  if (!alsa_output_is_string)                                                            \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::ALSA_OUTPUT_KEY     ,   \
                             CONFIG::STRING_TYPE , audio[CONFIG::ALSA_OUTPUT_ID    ] ) ; \
  if (!alsa_nchannels_is_int)                                                            \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::ALSA_NCHANNELS_KEY  ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::ALSA_NCHANNELS_ID ] ) ; \
  if (!alsa_samplerate_is_int)                                                           \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::ALSA_SAMPLERATE_KEY ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::ALSA_SAMPLERATE_ID] ) ; \
  if (!alsa_bitdepth_is_int)                                                             \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::ALSA_BITDEPTH_KEY   ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::ALSA_BITDEPTH_ID  ] ) ; \
  if (!alsa_nblocks_is_int)                                                              \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::ALSA_NBLOCKS_KEY    ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::ALSA_NBLOCKS_ID   ] ) ; \
  if (!alsa_blocksize_is_int)                                                            \
    Trace::TraceTypeMismatch(audio               ,       CONFIG::ALSA_BLOCKSIZE_KEY  ,   \
                             CONFIG::INT_TYPE    , audio[CONFIG::ALSA_BLOCKSIZE_ID ] ) ; \
                                                                                         \
  /* modify return value */                                                              \
  is_valid = is_valid                                                    &&              \
             audio_has_api_property            && audio_api_is_int       &&              \
             audio_has_jackserver_property     && jack_server_is_int     &&              \
             audio_has_jackname_property       && jack_name_is_string    &&              \
             audio_has_jackninputs_property    && jack_ninputs_is_int    &&              \
             audio_has_jacknoutputs_property   && jack_noutputs_is_int   &&              \
             audio_has_alsainput_property      && alsa_input_is_string   &&              \
             audio_has_alsaoutput_property     && alsa_output_is_string  &&              \
             audio_has_alsanchannels_property  && alsa_nchannels_is_int  &&              \
             audio_has_alsasamplerate_property && alsa_samplerate_is_int &&              \
             audio_has_alsabitdepth_property   && alsa_bitdepth_is_int   &&              \
             audio_has_alsanblocks_property    && alsa_nblocks_is_int    &&              \
             audio_has_alsablocksize_property  && alsa_blocksize_is_int                  ;

#ifdef _WIN32
#  define   DEBUG_VALIDATE_CONFIG_AUDIO DEBUG_VALIDATE_CONFIG_AUDIO_WIN
#else // _WIN32
#  ifdef _MAC
#    define DEBUG_VALIDATE_CONFIG_AUDIO DEBUG_VALIDATE_CONFIG_AUDIO_MAC
#  else // _MAC
#    define DEBUG_VALIDATE_CONFIG_AUDIO DEBUG_VALIDATE_CONFIG_AUDIO_NIX
#  endif // _MAC
#endif // _WIN32

#define DEBUG_VALIDATE_CONFIG_SERVER                                                    \
  /* query server properties */                                                         \
  bool server_has_host_property         = server.hasProperty(CONFIG::HOST_ID        ) ; \
  bool server_has_login_property        = server.hasProperty(CONFIG::LOGIN_ID       ) ; \
  bool server_has_pass_property         = server.hasProperty(CONFIG::PASS_ID        ) ; \
  bool server_has_is_anonymous_property = server.hasProperty(CONFIG::IS_ANONYMOUS_ID) ; \
  bool server_has_is_agreed_property    = server.hasProperty(CONFIG::IS_AGREED_ID   ) ; \
  bool server_has_should_agree_property = server.hasProperty(CONFIG::SHOULD_AGREE_ID) ; \
  bool server_has_bot_name_property     = server.hasProperty(CONFIG::BOT_NAME_ID    ) ; \
  bool server_has_bot_useridx_property  = server.hasProperty(CONFIG::BOT_USERIDX_ID ) ; \
                                                                                        \
  /* query server datatypes */                                                          \
  bool host_name_is_string  = server[CONFIG::HOST_ID        ].isString() ;              \
  bool login_is_string      = server[CONFIG::LOGIN_ID       ].isString() ;              \
  bool pass_is_string       = server[CONFIG::PASS_ID        ].isString() ;              \
  bool is_anon_is_bool      = server[CONFIG::IS_ANONYMOUS_ID].isBool()   ;              \
  bool is_agreed_is_bool    = server[CONFIG::IS_AGREED_ID   ].isBool()   ;              \
  bool should_agree_is_bool = server[CONFIG::SHOULD_AGREE_ID].isBool()   ;              \
  bool bot_name_is_string   = server[CONFIG::BOT_NAME_ID    ].isString() ;              \
  bool bot_useridx_is_int   = server[CONFIG::BOT_USERIDX_ID ].isInt()    ;              \
                                                                                        \
  /* trace missing server properties */                                                 \
  if (!server_has_host_property)                                                        \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::HOST_KEY        ) ;           \
  if (!server_has_login_property)                                                       \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::LOGIN_KEY       ) ;           \
  if (!server_has_pass_property)                                                        \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::PASS_KEY        ) ;           \
  if (!server_has_is_anonymous_property)                                                \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::IS_ANONYMOUS_KEY) ;           \
  if (!server_has_is_agreed_property)                                                   \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::IS_AGREED_KEY   ) ;           \
  if (!server_has_should_agree_property)                                                \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::SHOULD_AGREE_KEY) ;           \
  if (!server_has_bot_name_property)                                                    \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::BOT_NAME_KEY    ) ;           \
  if (!server_has_bot_useridx_property)                                                 \
    Trace::TraceMissingValue(CONFIG::SERVER_KEY , CONFIG::BOT_USERIDX_KEY ) ;           \
                                                                                        \
  /* trace invalid server datatypes */                                                  \
  if (!host_name_is_string)                                                             \
    Trace::TraceTypeMismatch(server              ,        CONFIG::HOST_KEY         ,    \
                             CONFIG::STRING_TYPE , server[CONFIG::HOST_ID        ] ) ;  \
  if (!login_is_string)                                                                 \
    Trace::TraceTypeMismatch(server              ,        CONFIG::LOGIN_KEY        ,    \
                             CONFIG::STRING_TYPE , server[CONFIG::LOGIN_ID       ] ) ;  \
  if (!pass_is_string)                                                                  \
    Trace::TraceTypeMismatch(server              ,        CONFIG::PASS_KEY         ,    \
                             CONFIG::STRING_TYPE , server[CONFIG::PASS_ID        ] ) ;  \
  if (!is_anon_is_bool)                                                                 \
    Trace::TraceTypeMismatch(server              ,        CONFIG::IS_ANONYMOUS_KEY ,    \
                             CONFIG::BOOL_TYPE   , server[CONFIG::IS_ANONYMOUS_ID] ) ;  \
  if (!is_agreed_is_bool)                                                               \
    Trace::TraceTypeMismatch(server              ,        CONFIG::IS_AGREED_KEY    ,    \
                             CONFIG::BOOL_TYPE   , server[CONFIG::IS_AGREED_ID   ] ) ;  \
  if (!should_agree_is_bool)                                                            \
    Trace::TraceTypeMismatch(server              ,        CONFIG::SHOULD_AGREE_KEY ,    \
                             CONFIG::BOOL_TYPE   , server[CONFIG::SHOULD_AGREE_ID] ) ;  \
  if (!bot_name_is_string)                                                              \
    Trace::TraceTypeMismatch(server              ,        CONFIG::BOT_NAME_KEY     ,    \
                             CONFIG::STRING_TYPE , server[CONFIG::BOT_NAME_ID    ] ) ;  \
  if (!bot_useridx_is_int)                                                              \
    Trace::TraceTypeMismatch(server              ,        CONFIG::BOT_USERIDX_KEY  ,    \
                             CONFIG::INT_TYPE    , server[CONFIG::BOT_USERIDX_ID ] ) ;  \
                                                                                        \
  /* modify return value */                                                             \
  is_valid = is_valid                                                 &&                \
             server_has_host_property         && host_name_is_string  &&                \
             server_has_login_property        && login_is_string      &&                \
             server_has_pass_property         && pass_is_string       &&                \
             server_has_is_anonymous_property && is_anon_is_bool      &&                \
             server_has_is_agreed_property    && is_agreed_is_bool    &&                \
             server_has_should_agree_property && should_agree_is_bool &&                \
             server_has_bot_name_property     && bot_name_is_string   &&                \
             server_has_bot_useridx_property  && bot_useridx_is_int                     ;

#define DEBUG_VALIDATE_CONFIG_MASTERS                                                      \
  /* query masters properties */                                                           \
  bool master_channel_has_name_property    = master.hasProperty(CONFIG::CHANNEL_NAME_ID) ; \
  bool master_channel_has_volume_property  = master.hasProperty(CONFIG::VOLUME_ID      ) ; \
  bool master_channel_has_pan_property     = master.hasProperty(CONFIG::PAN_ID         ) ; \
  bool master_channel_has_mute_property    = master.hasProperty(CONFIG::IS_MUTED_ID    ) ; \
  bool master_channel_has_stereo_property  = master.hasProperty(CONFIG::STEREO_ID      ) ; \
  bool master_channel_has_vuleft_property  = master.hasProperty(CONFIG::VU_LEFT_ID     ) ; \
  bool master_channel_has_vuright_property = master.hasProperty(CONFIG::VU_RIGHT_ID    ) ; \
  bool metro_channel_has_name_property     = metro .hasProperty(CONFIG::CHANNEL_NAME_ID) ; \
  bool metro_channel_has_volume_property   = metro .hasProperty(CONFIG::VOLUME_ID      ) ; \
  bool metro_channel_has_pan_property      = metro .hasProperty(CONFIG::PAN_ID         ) ; \
  bool metro_channel_has_mute_property     = metro .hasProperty(CONFIG::IS_MUTED_ID    ) ; \
  bool metro_channel_has_source_property   = metro .hasProperty(CONFIG::SOURCE_N_ID    ) ; \
  bool metro_channel_has_stereo_property   = metro .hasProperty(CONFIG::STEREO_ID      ) ; \
  bool metro_channel_has_vuleft_property   = metro .hasProperty(CONFIG::VU_LEFT_ID     ) ; \
  bool metro_channel_has_vuright_property  = metro .hasProperty(CONFIG::VU_RIGHT_ID    ) ; \
                                                                                           \
  /* query masters datatypes */                                                            \
  bool master_name_is_string    = master[CONFIG::CHANNEL_NAME_ID].isString() ;             \
  bool master_volume_is_double  = master[CONFIG::VOLUME_ID      ].isDouble() ;             \
  bool master_pan_is_double     = master[CONFIG::PAN_ID         ].isDouble() ;             \
  bool master_mute_is_bool      = master[CONFIG::IS_MUTED_ID    ].isBool()   ;             \
  bool master_stereo_is_int     = master[CONFIG::STEREO_ID      ].isInt()    ;             \
  bool master_vuleft_is_double  = master[CONFIG::VU_LEFT_ID     ].isDouble() ;             \
  bool master_vuright_is_double = master[CONFIG::VU_RIGHT_ID    ].isDouble() ;             \
  bool metro_name_is_string     = metro [CONFIG::CHANNEL_NAME_ID].isString() ;             \
  bool metro_volume_is_double   = metro [CONFIG::VOLUME_ID      ].isDouble() ;             \
  bool metro_pan_is_double      = metro [CONFIG::PAN_ID         ].isDouble() ;             \
  bool metro_mute_is_bool       = metro [CONFIG::IS_MUTED_ID    ].isBool()   ;             \
  bool metro_source_is_int      = metro [CONFIG::SOURCE_N_ID    ].isInt()    ;             \
  bool metro_stereo_is_int      = metro [CONFIG::STEREO_ID      ].isInt()    ;             \
  bool metro_vuleft_is_double   = metro [CONFIG::VU_LEFT_ID     ].isDouble() ;             \
  bool metro_vuright_is_double  = metro [CONFIG::VU_RIGHT_ID    ].isDouble() ;             \
                                                                                           \
  /* trace missing masters properties */                                                   \
  if (!master_channel_has_name_property)                                                   \
    Trace::TraceMissingProperty(CONFIG::MASTER_KEY , CONFIG::CHANNEL_NAME_KEY) ;           \
  if (!master_channel_has_volume_property)                                                 \
    Trace::TraceMissingProperty(CONFIG::MASTER_KEY , CONFIG::VOLUME_KEY      ) ;           \
  if (!master_channel_has_pan_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::MASTER_KEY , CONFIG::PAN_KEY         ) ;           \
  if (!master_channel_has_mute_property)                                                   \
    Trace::TraceMissingProperty(CONFIG::MASTER_KEY , CONFIG::IS_MUTED_KEY    ) ;           \
  if (!master_channel_has_stereo_property)                                                 \
    Trace::TraceMissingProperty(CONFIG::MASTER_KEY , CONFIG::STEREO_KEY      ) ;           \
  if (!master_channel_has_vuleft_property)                                                 \
    Trace::TraceMissingProperty(CONFIG::MASTER_KEY , CONFIG::VU_LEFT_KEY     ) ;           \
  if (!master_channel_has_vuright_property)                                                \
    Trace::TraceMissingProperty(CONFIG::MASTER_KEY , CONFIG::VU_RIGHT_KEY    ) ;           \
  if (!metro_channel_has_name_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::CHANNEL_NAME_KEY) ;           \
  if (!metro_channel_has_volume_property)                                                  \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::VOLUME_KEY      ) ;           \
  if (!metro_channel_has_pan_property)                                                     \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::PAN_KEY         ) ;           \
  if (!metro_channel_has_mute_property)                                                    \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::IS_MUTED_KEY    ) ;           \
  if (!metro_channel_has_source_property)                                                  \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::SOURCE_N_KEY    ) ;           \
  if (!metro_channel_has_stereo_property)                                                  \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::STEREO_KEY      ) ;           \
  if (!metro_channel_has_vuleft_property)                                                  \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::VU_LEFT_KEY     ) ;           \
  if (!metro_channel_has_vuright_property)                                                 \
    Trace::TraceMissingProperty(CONFIG::METRO_KEY  , CONFIG::VU_RIGHT_KEY    ) ;           \
                                                                                           \
  /* trace invalid masters datatypes */                                                    \
  if (!master_name_is_string)                                                              \
    Trace::TraceTypeMismatch(master              ,        CONFIG::CHANNEL_NAME_KEY ,       \
                             CONFIG::STRING_TYPE , master[CONFIG::CHANNEL_NAME_ID] ) ;     \
  if (!master_volume_is_double)                                                            \
    Trace::TraceTypeMismatch(master              ,        CONFIG::VOLUME_KEY       ,       \
                             CONFIG::DOUBLE_TYPE , master[CONFIG::VOLUME_ID      ] ) ;     \
  if (!master_pan_is_double)                                                               \
    Trace::TraceTypeMismatch(master              ,        CONFIG::PAN_KEY          ,       \
                             CONFIG::DOUBLE_TYPE , master[CONFIG::PAN_ID         ] ) ;     \
  if (!master_mute_is_bool)                                                                \
    Trace::TraceTypeMismatch(master              ,        CONFIG::IS_MUTED_KEY     ,       \
                             CONFIG::BOOL_TYPE   , master[CONFIG::IS_MUTED_ID    ] ) ;     \
  if (!master_stereo_is_int)                                                               \
    Trace::TraceTypeMismatch(master              ,        CONFIG::STEREO_KEY       ,       \
                             CONFIG::INT_TYPE    , master[CONFIG::STEREO_ID      ] ) ;     \
  if (!master_vuleft_is_double)                                                            \
    Trace::TraceTypeMismatch(master              ,        CONFIG::VU_LEFT_KEY      ,       \
                             CONFIG::DOUBLE_TYPE , master[CONFIG::VU_LEFT_ID     ] ) ;     \
  if (!master_vuright_is_double)                                                           \
    Trace::TraceTypeMismatch(master              ,        CONFIG::VU_RIGHT_KEY     ,       \
                             CONFIG::DOUBLE_TYPE , master[CONFIG::VU_RIGHT_ID    ] ) ;     \
  if (!metro_name_is_string)                                                               \
    Trace::TraceTypeMismatch(metro               ,        CONFIG::CHANNEL_NAME_KEY ,       \
                             CONFIG::STRING_TYPE , metro [CONFIG::CHANNEL_NAME_ID] ) ;     \
  if (!metro_volume_is_double)                                                             \
    Trace::TraceTypeMismatch(metro               ,        CONFIG::VOLUME_KEY       ,       \
                             CONFIG::DOUBLE_TYPE , metro [CONFIG::VOLUME_ID      ] ) ;     \
  if (!metro_pan_is_double)                                                                \
    Trace::TraceTypeMismatch(metro               ,        CONFIG::PAN_KEY          ,       \
                             CONFIG::DOUBLE_TYPE , metro [CONFIG::PAN_ID         ] ) ;     \
  if (!metro_mute_is_bool)                                                                 \
    Trace::TraceTypeMismatch(metro               ,        CONFIG::IS_MUTED_KEY     ,       \
                             CONFIG::BOOL_TYPE   , metro [CONFIG::IS_MUTED_ID    ] ) ;     \
  if (!metro_source_is_int)                                                                \
    Trace::TraceTypeMismatch(metro               ,        CONFIG::SOURCE_N_KEY     ,       \
                             CONFIG::INT_TYPE    , metro [CONFIG::SOURCE_N_ID    ] ) ;     \
  if (!metro_stereo_is_int)                                                                \
    Trace::TraceTypeMismatch(metro               ,        CONFIG::STEREO_KEY       ,       \
                             CONFIG::INT_TYPE    , metro [CONFIG::STEREO_ID      ] ) ;     \
  if (!metro_vuleft_is_double)                                                             \
    Trace::TraceTypeMismatch(metro               ,        CONFIG::VU_LEFT_KEY      ,       \
                             CONFIG::DOUBLE_TYPE , metro [CONFIG::VU_LEFT_ID     ] ) ;     \
  if (!metro_vuright_is_double)                                                            \
    Trace::TraceTypeMismatch(metro               ,        CONFIG::VU_RIGHT_KEY     ,       \
                             CONFIG::DOUBLE_TYPE , metro [CONFIG::VU_RIGHT_ID    ] ) ;     \
                                                                                           \
  /* modify return value */                                                                \
  is_valid = is_valid                                                        &&            \
             master_channel_has_name_property    && master_name_is_string    &&            \
             master_channel_has_volume_property  && master_volume_is_double  &&            \
             master_channel_has_pan_property     && master_pan_is_double     &&            \
             master_channel_has_mute_property    && master_mute_is_bool      &&            \
             master_channel_has_stereo_property  && master_stereo_is_int     &&            \
             master_channel_has_vuleft_property  && master_vuleft_is_double  &&            \
             master_channel_has_vuright_property && master_vuright_is_double &&            \
             metro_channel_has_name_property     && metro_name_is_string     &&            \
             metro_channel_has_volume_property   && metro_volume_is_double   &&            \
             metro_channel_has_pan_property      && metro_pan_is_double      &&            \
             metro_channel_has_mute_property     && metro_mute_is_bool       &&            \
             metro_channel_has_source_property   && metro_source_is_int      &&            \
             metro_channel_has_stereo_property   && metro_stereo_is_int      &&            \
             metro_channel_has_vuleft_property   && metro_vuleft_is_double   &&            \
             metro_channel_has_vuleft_property   && metro_vuright_is_double                ;

#define DEBUG_TRACE_VALIDATE_CONFIG                                                \
  /* NOTE: these checks normally should be unnecessary in the Release build   */   \
  /*       all tree nodes and properties will exist after sanitizeConfig()    */   \
  /*       and will be of the proper types after restoreVarTypeInfo()         */   \
  /*       only transient channels must be validated explicitly               */   \
                                                                                   \
  ValueTree root      = this->configRoot ;                                         \
  ValueTree gui       = this->gui ;                                                \
  ValueTree client    = this->client ;                                             \
  ValueTree blacklist = this->blacklist ;                                          \
  ValueTree audio     = this->audio ;                                              \
  ValueTree server    = this->server ;                                             \
  ValueTree master    = this->masterChannels.getChildWithName(CONFIG::MASTER_ID) ; \
  ValueTree metro     = this->masterChannels.getChildWithName(CONFIG::METRO_ID ) ; \
                                                                                   \
  /* trace subscribed sub-trees */                                                 \
  if (!root_is_valid           ) Trace::TraceInvalidNode(CONFIG::STORAGE_KEY  ) ;  \
  if (!gui_is_valid            ) Trace::TraceInvalidNode(CONFIG::GUI_KEY      ) ;  \
  if (!client_is_valid         ) Trace::TraceInvalidNode(CONFIG::CLIENT_KEY   ) ;  \
  if (!blacklist_is_valid      ) Trace::TraceInvalidNode(CONFIG::BLACKLIST_KEY) ;  \
  if (!audio_is_valid          ) Trace::TraceInvalidNode(CONFIG::AUDIO_KEY    ) ;  \
  if (!server_is_valid         ) Trace::TraceInvalidNode(CONFIG::SERVER_KEY   ) ;  \
  if (!servers_is_valid        ) Trace::TraceInvalidNode(CONFIG::SERVERS_KEY  ) ;  \
  if (!master_channels_is_valid) Trace::TraceInvalidNode(CONFIG::MASTERS_KEY  ) ;  \
  if (!local_channels_is_valid ) Trace::TraceInvalidNode(CONFIG::LOCALS_KEY   ) ;  \
  if (!remote_users_is_valid   ) Trace::TraceInvalidNode(CONFIG::REMOTES_KEY  ) ;  \
                                                                                   \
  /* trace sub-trees properties and datatypes */                                   \
  DEBUG_VALIDATE_CONFIG_DEFAULTS                                                   \
  DEBUG_VALIDATE_CONFIG_ROOT                                                       \
  DEBUG_VALIDATE_CONFIG_GUI                                                        \
  DEBUG_VALIDATE_CONFIG_CLIENT                                                     \
  DEBUG_VALIDATE_CONFIG_BLACKLIST                                                  \
  DEBUG_VALIDATE_CONFIG_AUDIO                                                      \
  DEBUG_VALIDATE_CONFIG_SERVER                                                     \
  DEBUG_VALIDATE_CONFIG_MASTERS

//#define DEBUG_TRACE_SANITIZE_GUI       // TODO: (issue #61)
//#define DEBUG_TRACE_SANITIZE_CLIENT    // TODO: (issue #61)
//#define DEBUG_TRACE_SANITIZE_BLACKLIST // TODO: (issue #61)
//#define DEBUG_TRACE_SANITIZE_AUDIO     // TODO: (issue #61)
//#define DEBUG_TRACE_SANITIZE_SERVER    // TODO: (issue #61)
//#define DEBUG_TRACE_SANITIZE_USER      // TODO: (issue #61)
//#define DEBUG_TRACE_SANITIZE_CHANNEL   // TODO: (issue #61)

#define DEBUG_TRACE_CLOBBER_CONFIG                                                    \
  Trace::TraceError("stored config invalid - restoring defaults and re-initializing") ;

#if TRACE_STORE_CONFIG_VB
#  define DEBUG_TRACE_STORE_CONFIG                                                \
    Trace::TraceConfig("storing config xml '" + configXmlFile.getFullPathName() + \
                       "'=\n" + configRoot.toXmlString()                        ) ;
#else // TRACE_STORE_CONFIG_VB
#  define DEBUG_TRACE_STORE_CONFIG                                                   \
  Trace::TraceConfig("storing config xml '" + configXmlFile.getFullPathName() + "'") ;
#endif // TRACE_STORE_CONFIG_VB

#define DEBUG_TRACE_CONFIG_VALUE_CHANGED                                 \
  bool is_status_change = a_value.refersToSameSourceAs(LinJam::Status) ; \
  String a_var  = (is_status_change)? "Status" : "unknown" ;             \
  String status = Trace::Status2String(int(LinJam::Status.getValue())) ; \
  if (DEBUG_TRACE_VB && is_status_change)                                \
    Trace::TraceEvent("value changed => " + a_var + " => " + status)     ;

#define DEBUG_TRACE_CONFIG_TREE_CHANGED                            \
  String node   = String(a_node.getType()) ;                       \
  String parent = String(a_node.getParent().getType()) ;           \
  String key    = String(a_key) ;                                  \
  String val    = a_node[a_key].toString() ;                       \
  if (a_key != CONFIG::VU_LEFT_ID && a_key != CONFIG::VU_RIGHT_ID) \
    Trace::TraceEvent("value changed for " + parent            +   \
                      " => " + node + "[" + key + "] => " + val) ;

#define DEBUG_TRACE_CONFIG_TREE_ADDED                                      \
  if (a_parent_node == this->blacklist)                                    \
    Trace::TraceEvent("node added to " + String(a_parent_node.getType()) + \
                      " => " + String(a_node.getType())                  ) ;

#define DEBUG_TRACE_CONFIG_TREE_REMOVED                                        \
  if (a_parent_node == this->blacklist)                                        \
    Trace::TraceEvent("node removed from " + String(a_parent_node.getType()) + \
                      " => " + String(a_node.getType())                      ) ;


/* channels */

#define DEBUG_TRACE_STEREO_STATUS                                                  \
  bool is_stereo_l   = stereo_status == CONFIG::STEREO_L ;                         \
  bool is_stereo_r   = stereo_status == CONFIG::STEREO_R ;                         \
  String status      = String((is_stereo_l) ? "STEREO_L"  :                        \
                              (is_stereo_r) ? "STEREO_R"  : "MONO"       ) +       \
                       String((is_paired  ) ? " (paired)" : " (unpaired)") ;       \
  String pair_status = ((pair_stereo_status == CONFIG::STEREO_L) ?                 \
                       "STEREO_L" : "STEREO_R") + String(" (paired)") ;            \
  String dbgA        = "setting remote channel '" ; String dbgB = "' status to " ; \
  if (is_paired) Trace::TraceConfig(dbgA + pair_name    + dbgB + pair_status) ;    \
                 Trace::TraceConfig(dbgA + channel_name + dbgB + status) ;

#define DEBUG_TRACE_MONO_STATUS                                                 \
  String dbgA = "setting remote channel '" ; String dbgB = "' status to MONO" ; \
  String pair_name = (has_l_pair)? l_pair_name : r_pair_name ;                  \
  if (has_orphaned_pair)                                                        \
    Trace::TraceConfig(dbgA + pair_name    + dbgB + " (orphaned)") ;            \
  if (ParseStereoStatus(channel_name) == CONFIG::MONO)                          \
    Trace::TraceConfig(dbgA + channel_name + dbgB) ;

#define DEBUG_TRACE_ADD_CHANNEL_STORE                                               \
  String user_id      = String(channels_store.getType()) ;                          \
  int    ch_idx       = int(new_channel_node[CONFIG::CHANNEL_IDX_ID]) ;             \
  String channel_id   = String(MakeChannelId(ch_idx)) ;                             \
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

#define DEBUG_TRACE_REMOVE_CHANNEL_STORE                                      \
  String channel_id   = String(channel_store.getType()) ;                     \
  String channel_name = LinJam::GetStoredChannelName(channel_store) ;         \
  String user_id      = String(channels_store.getType()) ;                    \
  String dbgA         = "destroyed storage for " ;                            \
  String dbgB         = " " + channel_id + " '" + channel_name + "' " ;       \
  if (channel_store.getParent() == channels_store)                            \
    if (channels_store == this->localChannels)                                \
        Trace::TraceConfig(dbgA + "local"  + dbgB) ;                          \
    else Trace::TraceConfig(dbgA + "remote" + dbgB + "for '" + user_id + "'") ;

#define DEBUG_TRACE_ADD_REMOTE_USER_STORE                                              \
  Trace::TraceEvent("user joined => '" + String(user_id) + "'") ;                      \
  Trace::TraceConfig("created storage for new remote user " + String(user_id)) ;       \
  if (TRACE_REMOTE_CHANNELS_VB)                                                        \
  {                                                                                    \
    StringRef host      = MakeHostId(str(this->server[CONFIG::HOST_ID])) ;             \
    bool      has_bot   = NETWORK::KNOWN_BOTS->hasAttribute(host) ;                    \
    bool      hide_bots = has_bot && bool(this->client[CONFIG::SHOULD_HIDE_BOTS_ID]) ; \
    float     u_vol     = CONFIG::DEFAULT_VOLUME ;                                     \
    bool      u_mute    = CONFIG::DEFAULT_IS_MUTED ;                                   \
    float     u_pan     = CONFIG::DEFAULT_PAN ;                                        \
    int       u_idx     = -1 ; String u_name ; Identifier u_id ;                       \
    while ((u_name = LinJam::GetRemoteUserName(++u_idx)).isNotEmpty())                 \
      { u_id = MakeUserId(u_name) ; if (user_id == u_id) break ; }                     \
    DEBUG_TRACE_REMOTE_CHANNELS                                                        \
  }

#else // DEBUG

// storage
#define DEBUG_TRACE_LOAD_CONFIG            ;
#define DEBUG_TRACE_DUMP_CONFIG            ;
#define DEBUG_TRACE_CONFIG_TYPES_VB        ;
#define DEBUG_TRACE_CONFIG_TYPES_VB_EACH   ;
#define DEBUG_TRACE_VALIDATE_USER          ;
#define DEBUG_TRACE_VALIDATE_CHANNEL       ;
#define DEBUG_TRACE_VALIDATE_CONFIG        ;
//#define DEBUG_TRACE_SANITIZE_GUI         ;
//#define DEBUG_TRACE_SANITIZE_CLIENT      ;
//#define DEBUG_TRACE_SANITIZE_BLACKLIST   ;
//#define DEBUG_TRACE_SANITIZE_AUDIO       ;
//#define DEBUG_TRACE_SANITIZE_SERVER      ;
//#define DEBUG_TRACE_SANITIZE_USER        ;
//#define DEBUG_TRACE_SANITIZE_CHANNEL     ;
#define DEBUG_TRACE_CLOBBER_CONFIG         ;
#define DEBUG_TRACE_STORE_CONFIG           ;
#define DEBUG_TRACE_CONFIG_VALUE_CHANGED   ;
#define DEBUG_TRACE_CONFIG_TREE_CHANGED    ;
#define DEBUG_TRACE_CONFIG_TREE_ADDED      ;
#define DEBUG_TRACE_CONFIG_TREE_REMOVED    ;
// channels
#define DEBUG_TRACE_STEREO_STATUS          ;
#define DEBUG_TRACE_MONO_STATUS            ;
#define DEBUG_TRACE_ADD_CHANNEL_STORE      ;
#define DEBUG_TRACE_REMOVE_CHANNEL_STORE   ;
#define DEBUG_TRACE_ADD_REMOTE_USER_STORE  ;

#endif // DEBUG
