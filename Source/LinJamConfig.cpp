/*
  ==============================================================================

    LinJamConfig.cpp
    Created: 12 Jun 2014 7:05:12am
    Author:  me

  ==============================================================================
*/

#include "LinJam.h"
#include "LinJamConfig.h"


#if DEBUG
#  include "./Trace/TraceLinJamConfig.h"
#endif // DEBUG


/* LinJamConfig class public class methods */

LinJamConfig::LinJamConfig()
{
  // load default and stored configs
  File this_binary    = File::getSpecialLocation(File::currentExecutableFile) ;
  this->configXmlFile = this_binary.getSiblingFile(CONFIG::PERSISTENCE_FILENAME) ;
  XmlElement* default_config_xml = XmlDocument::parse(CONFIG::DEFAULT_CONFIG_XML) ;
  XmlElement* stored_config_xml  = XmlDocument::parse(this->configXmlFile) ;
  bool is_stored_config_bogus = (stored_config_xml == nullptr ||
                                !stored_config_xml->hasTagName(CONFIG::PERSISTENCE_ID)) ;

DEBUG_TRACE_LOAD_CONFIG

  if (default_config_xml == nullptr) return ;

DEBUG_TRACE_SANITIZE_CONFIG

  // create static config ValueTree from stored xml persistence or default
  if (is_stored_config_bogus)
    this->configValueTree = ValueTree::fromXml(*default_config_xml) ;
  else
    this->configValueTree = sanitizeConfig(ValueTree::fromXml(*default_config_xml) ,
                                           ValueTree::fromXml(*stored_config_xml)) ;

  // instantiate shared value holders and restore type data
  establishSharedStore() ; restoreVarTypeInfo(this->configValueTree) ;

  // write back sanitized config to disk and cleanup
  storeConfig() ; delete default_config_xml ; delete stored_config_xml ;

  // set session dir and log file - these are too dangerous to be user-configuraable
  ValueTree client = this->configValueTree.getChildWithName(CONFIG::CLIENT_ID) ;
  client.setProperty(CONFIG::SESSIONDIR_ID , CONFIG::SESSIONDIR , nullptr) ;
  client.setProperty(CONFIG::LOGFILE_ID    , CONFIG::LOGFILE    , nullptr) ;

  this->configValueTree.addListener(this) ;
}

LinJamConfig::~LinJamConfig() { storeConfig() ; }


/* LinJamConfig class public instance methods */

/* validation */

bool LinJamConfig::sanityCheck()
{
  // TODO: (issue #33)
  //       most of these are unused or redundant and no longer needed as Value holders
  //       only ValueTree::Listeners are being used and all of their properties will
  //       exist after sanitizeConfig() so only transient channels need be validated here
  ValueTree master_channel = this->masterChannels.getChildWithName(CONFIG::MASTER_ID) ;
  ValueTree metro_channel  = this->masterChannels.getChildWithName(CONFIG::METRO_ID) ;

  // subscribed trees
  bool root_is_valid                 = this->configValueTree   .isValid() ;
  bool auto_subscribe_users_is_valid = this->autoSubscribeUsers.isValid() ;
  bool master_channels_is_valid      = this->masterChannels    .isValid() ;
  bool local_channels_is_valid       = this->localChannels     .isValid() ;
  bool remote_users_is_valid         = this->remoteUsers       .isValid() ;
  bool servers_is_valid              = this->servers           .isValid() ;

  // implicitly subscribed transient channels
  bool are_local_channels_sane = sanityCheckChannels(this->localChannels) ;
//   bool are_remote_channels_sane = sanityCheckChannels(this->remoteUsers) ; // TODO: (issue #33)

  // implicitly subscribed values (via above trees)
  bool master_channel_has_name_property    =
    master_channel            .hasProperty(CONFIG::CHANNEL_NAME_ID)  ;
  bool master_channel_has_volume_property  =
    master_channel            .hasProperty(CONFIG::VOLUME_ID)        ;
  bool master_channel_has_pan_property     =
    master_channel            .hasProperty(CONFIG::PAN_ID)           ;
  bool master_channel_has_mute_property    =
    master_channel            .hasProperty(CONFIG::IS_MUTED_ID)      ;
  bool master_channel_has_stereo_property   =
    master_channel            .hasProperty(CONFIG::STEREO_ID)        ;
  bool master_channel_has_vuleft_property  =
    master_channel            .hasProperty(CONFIG::VU_LEFT_ID)       ;
  bool master_channel_has_vuright_property =
    master_channel            .hasProperty(CONFIG::VU_RIGHT_ID)      ;
  bool metro_channel_has_name_property     =
    metro_channel             .hasProperty(CONFIG::CHANNEL_NAME_ID)  ;
  bool metro_channel_has_volume_property   =
    metro_channel             .hasProperty(CONFIG::VOLUME_ID)        ;
  bool metro_channel_has_pan_property      =
    metro_channel             .hasProperty(CONFIG::PAN_ID)           ;
  bool metro_channel_has_mute_property     =
    metro_channel             .hasProperty(CONFIG::IS_MUTED_ID)      ;
  bool metro_channel_has_source_property   =
    metro_channel             .hasProperty(CONFIG::SOURCE_N_ID)      ;
  bool metro_channel_has_stereo_property   =
    metro_channel             .hasProperty(CONFIG::STEREO_ID)        ;
  bool metro_channel_has_vuleft_property   =
    metro_channel             .hasProperty(CONFIG::VU_LEFT_ID)       ;
  bool metro_channel_has_vuright_property  =
    metro_channel             .hasProperty(CONFIG::VU_RIGHT_ID)      ;

  // explicitly subscribed values
  bool should_save_audio_has_value     =
    !this->saveAudio     .refersToSameSourceAs(this->dummyValue) ;
  bool should_save_log_has_value       =
    !this->shouldSaveLog .refersToSameSourceAs(this->dummyValue) ;
  bool debug_level_has_value           =
    !this->debugLevel    .refersToSameSourceAs(this->dummyValue) ;
  bool should_auto_subscribe_has_value =
    !this->autoSubscribe .refersToSameSourceAs(this->dummyValue) ;
  bool audio_if_n_has_value            =
    !this->audioIfN      .refersToSameSourceAs(this->dummyValue) ;
  bool n_inputs_has_value              =
    !this->nInputs       .refersToSameSourceAs(this->dummyValue) ;
  bool n_outputs_has_value             =
    !this->nOutputs      .refersToSameSourceAs(this->dummyValue) ;
  bool bit_depth_has_value             =
    !this->bitDepth      .refersToSameSourceAs(this->dummyValue) ;
  bool sample_rate_has_value           =
    !this->sampleRate    .refersToSameSourceAs(this->dummyValue) ;
  bool jack_name_has_value             =
    !this->jackName      .refersToSameSourceAs(this->dummyValue) ;
  bool host_has_value                  =
    !this->host          .refersToSameSourceAs(this->dummyValue) ;
  bool login_has_value                 =
    !this->login         .refersToSameSourceAs(this->dummyValue) ;
  bool pass_has_value                  =
    !this->pass          .refersToSameSourceAs(this->dummyValue) ;
  bool is_anonymous_has_value          =
    !this->isAnonymous   .refersToSameSourceAs(this->dummyValue) ;
  bool is_agreed_has_value             =
    !this->isAgreed      .refersToSameSourceAs(this->dummyValue) ;
  bool should_agree_has_value          =
    !this->shouldAgree   .refersToSameSourceAs(this->dummyValue) ;
  bool should_hide_bots_has_value      =
    !this->shouldHideBots.refersToSameSourceAs(this->dummyValue) ;

  // data types
  bool master_name_is_string    = master_channel[CONFIG::CHANNEL_NAME_ID].isString() ;
  bool master_volume_is_double  = master_channel[CONFIG::VOLUME_ID]      .isDouble() ;
  bool master_pan_is_double     = master_channel[CONFIG::PAN_ID]         .isDouble() ;
  bool master_mute_is_bool      = master_channel[CONFIG::IS_MUTED_ID]    .isBool()   ;
  bool master_stereo_is_int     = master_channel[CONFIG::STEREO_ID]      .isInt()    ;
  bool master_vuleft_is_double  = master_channel[CONFIG::VU_LEFT_ID]     .isDouble() ;
  bool master_vuright_is_double = master_channel[CONFIG::VU_RIGHT_ID]    .isDouble() ;
  bool metro_name_is_string     = metro_channel [CONFIG::CHANNEL_NAME_ID].isString() ;
  bool metro_volume_is_double   = metro_channel [CONFIG::VOLUME_ID]      .isDouble() ;
  bool metro_pan_is_double      = metro_channel [CONFIG::PAN_ID]         .isDouble() ;
  bool metro_mute_is_bool       = metro_channel [CONFIG::IS_MUTED_ID]    .isBool()   ;
  bool metro_source_is_int      = metro_channel [CONFIG::SOURCE_N_ID]    .isInt()    ;
  bool metro_stereo_is_int      = metro_channel [CONFIG::STEREO_ID]      .isInt()    ;
  bool metro_vuleft_is_double   = metro_channel [CONFIG::VU_LEFT_ID]     .isDouble() ;
  bool metro_vuright_is_double  = metro_channel [CONFIG::VU_RIGHT_ID]    .isDouble() ;
  bool save_audio_is_int        = this->saveAudio     .getValue()        .isInt()    ;
  bool save_log_is_bool         = this->shouldSaveLog .getValue()        .isBool()   ;
  bool deuglevel_is_int         = this->debugLevel    .getValue()        .isInt()    ;
  bool autosubscribe_is_int     = this->autoSubscribe .getValue()        .isInt()    ;
  bool audio_ifn_is_int         = this->audioIfN      .getValue()        .isInt()    ;
  bool n_inputs_is_int          = this->nInputs       .getValue()        .isInt()    ;
  bool n_outputs_is_int         = this->nOutputs      .getValue()        .isInt()    ;
  bool bitdepth_is_int          = this->bitDepth      .getValue()        .isInt()    ;
  bool samplerate_is_int        = this->sampleRate    .getValue()        .isInt()    ;
  bool jack_name_is_string      = this->jackName      .getValue()        .isString() ;
  bool host_name_is_string      = this->host          .getValue()        .isString() ;
  bool login_is_string          = this->login         .getValue()        .isString() ;
  bool pass_is_string           = this->pass          .getValue()        .isString() ;
  bool is_anon_is_bool          = this->isAnonymous   .getValue()        .isBool()   ;
  bool is_agreed_is_bool        = this->isAgreed      .getValue()        .isBool()   ;
  bool should_agree_is_bool     = this->shouldAgree   .getValue()        .isBool()   ;
  bool should_hide_bots_is_bool = this->shouldHideBots.getValue()        .isBool()   ;

DEBUG_TRACE_SANITY_CHECK

  // TODO: no real need to return anything here to LinJam and quit
  //       just call this from sanitizeConfig (or merge it in)
  //       then restore default config if necessary
  return (root_is_valid                      && auto_subscribe_users_is_valid      &&
          master_channels_is_valid           && local_channels_is_valid            &&
          remote_users_is_valid              && servers_is_valid                   &&

          are_local_channels_sane            && //are_remote_channels_sane           &&

          master_channel_has_name_property   && master_channel_has_volume_property &&
          master_channel_has_pan_property    && master_channel_has_mute_property   &&
          master_channel_has_stereo_property && master_channel_has_vuleft_property &&
          master_channel_has_vuleft_property                                       &&

          metro_channel_has_name_property    && metro_channel_has_volume_property  &&
          metro_channel_has_pan_property     && metro_channel_has_mute_property    &&
          metro_channel_has_source_property  && metro_channel_has_stereo_property  &&
          metro_channel_has_vuleft_property  && metro_channel_has_vuleft_property  &&

          should_save_audio_has_value        && should_save_log_has_value          &&
          debug_level_has_value              && should_auto_subscribe_has_value    &&

          audio_if_n_has_value               && n_inputs_has_value                 &&
          n_outputs_has_value                && bit_depth_has_value                &&
          sample_rate_has_value              && jack_name_has_value                &&

          host_has_value                     && login_has_value                    &&
          pass_has_value                     && is_anonymous_has_value             &&
          is_agreed_has_value                && should_agree_has_value             &&
          should_hide_bots_has_value                                               &&

          master_name_is_string              && master_volume_is_double            &&
          master_pan_is_double               && master_mute_is_bool                &&
          master_stereo_is_int               && master_vuleft_is_double            &&
          master_vuright_is_double                                                 &&

          metro_name_is_string               && metro_volume_is_double             &&
          metro_pan_is_double                && metro_mute_is_bool                 &&
          metro_source_is_int                && metro_stereo_is_int                &&
          metro_vuleft_is_double             && metro_vuright_is_double            &&

          save_audio_is_int                  && save_log_is_bool                   &&
          deuglevel_is_int                   && autosubscribe_is_int               &&

          audio_ifn_is_int                   && n_inputs_is_int                    &&
          n_outputs_is_int                   && bitdepth_is_int                    &&
          samplerate_is_int                  && jack_name_is_string                &&

          host_name_is_string                && login_is_string                    &&
          pass_is_string                     && is_anon_is_bool                    &&
          is_agreed_is_bool                  && should_agree_is_bool               &&
          should_hide_bots_is_bool                                                  ) ;
}

String LinJamConfig::parseUsername(String user_name)
{
  return user_name.upToFirstOccurrenceOf(CONFIG::USER_IP_SPLIT_CHAR , false , true) ;
}

Identifier LinJamConfig::makeHostId(String host_name)
{
  return Identifier(CONFIG::SERVER_ID.toString() + "-" +
                    host_name.replaceCharacter('.' , '-')
                             .replaceCharacter(':' , '-')) ;
}

Identifier LinJamConfig::makeUserId(String user_name , int user_idx)
{
  return filteredName(parseUsername(user_name)) ;
}

Identifier LinJamConfig::makeChannelId(int channel_idx)
{
  return (channel_idx == CONFIG::MASTER_CHANNEL_IDX)                     ?
         CONFIG::MASTER_ID                                               :
         Identifier(CONFIG::CHANNEL_BASE_ID + "-" + String(channel_idx)) ;
}

String LinJamConfig::trimStereoName(String channel_name)
{
  String stereo_postfix = channel_name.getLastCharacters(CLIENT::STEREO_POSTFIX_N_CHARS) ;

  return (stereo_postfix != CLIENT::STEREO_L_POSTFIX &&
          stereo_postfix != CLIENT::STEREO_R_POSTFIX  )? channel_name  :
          channel_name.dropLastCharacters(CLIENT::STEREO_POSTFIX_N_CHARS) ;
}

String LinJamConfig::makeStereoName(String channel_name , int stereo_status)
{
  return trimStereoName(channel_name) +
         ((stereo_status == CONFIG::STEREO_L)? CLIENT::STEREO_L_POSTFIX :
          (stereo_status == CONFIG::STEREO_R)? CLIENT::STEREO_R_POSTFIX : "") ;
}

void LinJamConfig::setStereo(ValueTree channel_store , int stereo_status)
{
  channel_store.setProperty(CONFIG::STEREO_ID , stereo_status , nullptr) ;
}

int LinJamConfig::parseStereoStatus(String channel_name)
{
  // determine faux-stereo stereo status based on channel name
  String postfix = channel_name.getLastCharacters(CLIENT::STEREO_POSTFIX_N_CHARS) ;
  return (!postfix.compare(CLIENT::STEREO_L_POSTFIX))? CONFIG::STEREO_L :
         (!postfix.compare(CLIENT::STEREO_R_POSTFIX))? CONFIG::STEREO_R :
                                                       CONFIG::MONO     ;
}

int LinJamConfig::setRemoteStereo(ValueTree user_store        , ValueTree channel_store ,
                                  String    prev_channel_name                           )
{
  String channel_name  = channel_store[CONFIG::CHANNEL_NAME_ID].toString() ;
  int    stereo_status = parseStereoStatus(channel_name) ;
  int    prev_status   = parseStereoStatus(prev_channel_name) ;

  // ensure remote faux-stereo channels are paired
  if (stereo_status != CONFIG::MONO)
  {
    // find channel with name matching this channel_name + opposite_postfix
    // to ignore duplicate names this assumes that stereo pairs are contiguous
    int    channel_idx = int(channel_store[CONFIG::CHANNEL_IDX_ID]) ;
    String l_pair_name = makeStereoName(channel_name , CONFIG::STEREO_L) ;
    String r_pair_name = makeStereoName(channel_name , CONFIG::STEREO_R) ;
    String expected_pair_name ; int pair_stereo_status ;
    int    l_pair_idx ;         int r_pair_idx ;

    if      (stereo_status == CONFIG::STEREO_L)
    {
      l_pair_idx         = channel_idx ;
      r_pair_idx         = channel_idx + 1 ;
      expected_pair_name = r_pair_name ;
      pair_stereo_status = CONFIG::STEREO_R ;
    }
    else if (stereo_status == CONFIG::STEREO_R)
    {
      l_pair_idx         = channel_idx - 1 ;
      r_pair_idx         = channel_idx ;
      expected_pair_name = l_pair_name ;
      pair_stereo_status = CONFIG::STEREO_L ;
    }

    ValueTree l_pair_store = getChannelByIdx(user_store , l_pair_idx) ;
    ValueTree r_pair_store = getChannelByIdx(user_store , r_pair_idx) ;
    ValueTree pair_store   = (pair_stereo_status == CONFIG::STEREO_L)? l_pair_store :
                                                                       r_pair_store ;
    String    pair_name    = pair_store[CONFIG::CHANNEL_NAME_ID].toString() ;
    bool      is_paired    = !pair_name.compare(expected_pair_name) ;

    // set this and matched pair channel stereo status to stereo
    if (is_paired)
    {
      l_pair_store.setProperty(CONFIG::PAIR_IDX_ID , r_pair_idx , nullptr) ;
      setStereo(channel_store , stereo_status) ;
      setStereo(pair_store    , pair_stereo_status) ;
    }
    // set this unpaired channel stereo status to mono
    else setStereo(channel_store , (stereo_status = CONFIG::MONO)) ;

DEBUG_TRACE_STEREO_STATUS
  }

  if (stereo_status == CONFIG::MONO && stereo_status != prev_status)
  {
    // find channel with name matching prev_channel_name + either_postfix
    String    l_pair_name          = makeStereoName(prev_channel_name , CONFIG::STEREO_L) ;
    String    r_pair_name          = makeStereoName(prev_channel_name , CONFIG::STEREO_R) ;
    ValueTree l_pair_channel_store = getChannelByName(user_store , l_pair_name) ;
    ValueTree r_pair_channel_store = getChannelByName(user_store , r_pair_name) ;
    bool      has_l_pair           = l_pair_channel_store.isValid() &&
                                     l_pair_name.compare(channel_name) ;
    bool      has_r_pair           = r_pair_channel_store.isValid() &&
                                     r_pair_name.compare(channel_name) ;
    bool      has_orphaned_pair    = has_l_pair != has_r_pair ;

DEBUG_TRACE_MONO_STATUS

    // set orphaned pair channel stereo status to mono
    if (has_orphaned_pair)
    {
      if      (has_l_pair) setStereo(l_pair_channel_store , CONFIG::MONO) ;
      else if (has_r_pair) setStereo(r_pair_channel_store , CONFIG::MONO) ;
    }
    // set this channel stereo status to mono
    setStereo(channel_store , CONFIG::MONO) ;
  }

  return stereo_status ;
}


/* getters/setters */

ValueTree LinJamConfig::newChannel(String channel_name , int channel_idx)
{
  return ValueTree(CONFIG::NEWCHANNEL_ID)
         .setProperty(CONFIG::CHANNEL_NAME_ID , channel_name                  , nullptr)
         .setProperty(CONFIG::CHANNEL_IDX_ID  , channel_idx                   , nullptr)
         .setProperty(CONFIG::PAIR_IDX_ID     , CONFIG::DEFAULT_CHANNEL_IDX   , nullptr)
         .setProperty(CONFIG::VOLUME_ID       , CONFIG::DEFAULT_VOLUME        , nullptr)
         .setProperty(CONFIG::PAN_ID          , CONFIG::DEFAULT_PAN           , nullptr)
         .setProperty(CONFIG::IS_XMIT_RCV_ID  , CONFIG::DEFAULT_IS_XMIT_RCV   , nullptr)
         .setProperty(CONFIG::IS_MUTED_ID     , CONFIG::DEFAULT_IS_MUTED      , nullptr)
         .setProperty(CONFIG::IS_SOLO_ID      , CONFIG::DEFAULT_IS_SOLO       , nullptr)
         .setProperty(CONFIG::SOURCE_N_ID     , CONFIG::DEFAULT_SOURCE_N      , nullptr)
         .setProperty(CONFIG::VU_LEFT_ID      , CONFIG::DEFAULT_VU            , nullptr)
         .setProperty(CONFIG::VU_RIGHT_ID     , CONFIG::DEFAULT_VU            , nullptr)
         .setProperty(CONFIG::STEREO_ID       , CONFIG::DEFAULT_STEREO_STATUS , nullptr) ;
}

ValueTree LinJamConfig::addChannel(ValueTree channels_store , ValueTree new_channel_node)
{
DEBUG_TRACE_ADD_CHANNEL_STORE

  // ensure trees are valid and storage does not already exist for this channel
  if (!channels_store.isValid() || !new_channel_node.isValid()) return ValueTree::invalid ;
  if (new_channel_node.getParent() == channels_store)           return new_channel_node ;

  int       channel_idx   = int(new_channel_node[CONFIG::CHANNEL_IDX_ID]) ;
  ValueTree channel_store = ValueTree(makeChannelId(channel_idx)) ;

  channel_store .copyPropertiesFrom(new_channel_node , nullptr) ;
  channels_store.addChild(channel_store , -1  , nullptr) ;

  return channel_store ;
}

void LinJamConfig::destroyChannel(ValueTree channels_store , ValueTree channel_store)
{
DEBUG_TRACE_DESTROY_CHANNEL_STORE

  channels_store.removeChild(channel_store , nullptr) ;
}

ValueTree LinJamConfig::getOrAddRemoteUser(String user_name , int user_idx)
{
  Identifier user_id    = makeUserId(user_name , user_idx) ;
  ValueTree  user_store = getUserById(user_id) ;

  if (!user_store.isValid())
  {
    user_store = ValueTree(user_id) ;
    this->remoteUsers.addChild(user_store , -1 , nullptr) ;

DEBUG_TRACE_ADD_REMOTE_USER_STORE
  }

  return user_store ;
}

ValueTree LinJamConfig::getOrAddRemoteChannel(Identifier user_id      ,
                                              String     channel_name ,
                                              int        channel_idx  )
{
  ValueTree  user_store    = getUserById(user_id) ;
  ValueTree  channel_store = getChannelByIdx(user_store , channel_idx) ;

  if (user_store.isValid() && !channel_store.isValid())
  {
    // add new channel to store (masters always faux-stereo)
    channel_store = newChannel(channel_name , channel_idx) ;
    if (channel_idx == CONFIG::DEFAULT_CHANNEL_IDX)
      setStereo(channel_store , CONFIG::STEREO_L) ;
    channel_store = addChannel(user_store , channel_store) ;
  }

  return channel_store ;
}

ValueTree LinJamConfig::getUserById(Identifier user_id)
{
  return this->configValueTree.getChildWithName(user_id) ;
}

ValueTree LinJamConfig::getChannelById(Identifier channels_id , Identifier channel_id)
{
  ValueTree channels_store ;
  if      (channels_id == CONFIG::MASTERS_ID) channels_store = this->masterChannels ;
  else if (channels_id == CONFIG::LOCALS_ID)  channels_store = this->localChannels ;
  else                                        channels_store = getUserById(channels_id) ;

  return channels_store.getChildWithName(channel_id) ;
}

ValueTree LinJamConfig::getChannelByIdx(ValueTree channels_store , int channel_idx)
{
  return channels_store.getChildWithProperty(CONFIG::CHANNEL_IDX_ID , channel_idx) ;
}

ValueTree LinJamConfig::getChannelByPairIdx(ValueTree channels_store , int pair_idx)
{
  return channels_store.getChildWithProperty(CONFIG::PAIR_IDX_ID , pair_idx) ;
}

ValueTree LinJamConfig::getChannelByName(ValueTree channels_store , String channel_name)
{
  return channels_store.getChildWithProperty(CONFIG::CHANNEL_NAME_ID , channel_name) ;
}

ValueTree LinJamConfig::getUserMasterChannel(ValueTree user_store)
{
  return getChannelByIdx(user_store , CONFIG::MASTER_CHANNEL_IDX) ;
}

void LinJamConfig::setServer()
{
  // copy volatile login state to persistent storage
  String host         =      this->host.toString() ;
  String login        =      this->login.toString() ;
  String pass         =      this->pass.toString() ;
  bool   is_anonymous = bool(this->isAnonymous.getValue()) ;

  ValueTree server = addServer(host , login , pass , is_anonymous) ;
  server.setProperty(CONFIG::HOST_ID    , host         , nullptr) ;
  server.setProperty(CONFIG::LOGIN_ID   , login        , nullptr) ;
  server.setProperty(CONFIG::PASS_ID    , pass         , nullptr) ;
  server.setProperty(CONFIG::IS_ANON_ID , is_anonymous , nullptr) ;
}

ValueTree LinJamConfig::getServer(String host_name)
{
  return this->servers.getChildWithProperty(CONFIG::HOST_ID , var(host_name)) ;
}

void LinJamConfig::setCurrentServer(String host_name , String login        ,
                                    String pass      , bool   is_anonymous )
{
  this->host        = host_name ;
  this->login       = login ;
  this->pass        = (is_anonymous)? "" : pass ;
  this->isAnonymous = is_anonymous ;
  this->isAgreed    = false ;
  this->shouldAgree = false ;
}

ValueTree LinJamConfig::getCurrentServer() { return getServer(this->host.toString()) ; }

void LinJamConfig::setServerShouldAgree(bool should_agree)
{
  // continuation of setServer() after license agreement
  ValueTree server = getCurrentServer() ; if (!server.isValid()) return ;

  server.setProperty(CONFIG::SHOULD_AGREE_ID , should_agree , nullptr) ;
}


/* LinJamConfig class private instance methods */

/* validation */

ValueTree LinJamConfig::sanitizeConfig(ValueTree default_config , ValueTree stored_config)
{
  // add any missing nodes and attributes to stored config
  for (int child_n = 0 ; child_n < default_config.getNumChildren() ; ++child_n)
  {
    ValueTree default_child = default_config.getChild(child_n) ;
    ValueTree stored_child  = stored_config.getChildWithName(default_child.getType()) ;

    // transfer missing node
    if (!stored_child.isValid())
    {
      // for local channels we transfer the default channel only if none are stored
      if (default_config.getType() != CONFIG::LOCALS_ID ||
         !stored_config.getNumChildren())
      {
        default_config.removeChild(default_child , nullptr) ;
        stored_config.addChild(default_child , -1 , nullptr) ;
        --child_n ;
      }
      continue ;
    }

    int n_grandchildren = default_child.getNumChildren() ;
    int n_properties    = default_child.getNumProperties() ;

    // recurse if node has children ignoring atrributes
    if (n_grandchildren) { sanitizeConfig(default_child , stored_child) ; continue ; }

    // transfer missing attributes
    for (int property_n = 0 ; property_n < n_properties ; ++property_n)
    {
      Identifier key   = default_child.getPropertyName(property_n) ;
      var        value = default_child.getProperty(key) ;
      if (!stored_child.hasProperty(key)) stored_child.setProperty(key , value , nullptr) ;
    }
  }

  return stored_config ;
}

void LinJamConfig::restoreVarTypeInfo(ValueTree config_store)
{
  Identifier  node_id          = config_store.getType() ;
  ValueTree   parent_node      = config_store.getParent() ;
  ValueTree   grandparent_node = config_store.getParent().getParent() ;
  XmlElement* config_types_xml = XmlDocument::parse(CONFIG::CONFIG_TYPES) ;
  ValueTree   config_types     = ValueTree::fromXml(*config_types_xml) ;
  ValueTree   types_store ;                   delete config_types_xml ;

  if      (parent_node         == this->configValueTree &&
          (node_id             == CONFIG::CLIENT_ID ||
           node_id             == CONFIG::AUDIO_ID  ||
           node_id             == CONFIG::SERVER_ID  )   )
    types_store = config_types.getChildWithName(node_id) ;
  else if (parent_node         == this->servers)
    types_store = config_types.getChildWithName(CONFIG::SERVER_ID) ;
  else if (parent_node         == this->masterChannels ||
           parent_node         == this->localChannels  ||
           grandparent_node    == this->remoteUsers     )
    types_store = config_types.getChildWithName(CONFIG::CHANNELS_ID) ;
  else if (parent_node         == this->remoteUsers)
    types_store = config_types.getChildWithName(CONFIG::USERS_ID) ;

  for (int property_n = 0 ; property_n < config_store.getNumProperties() ; ++property_n)
  {
    Identifier key       = config_store.getPropertyName(property_n) ;
    var        a_var     = config_store[key] ;
    String     datatype  = types_store[key] ;
    bool       is_bool   = !datatype.compare(CONFIG::BOOL_TYPE) ;
    bool       is_double = !datatype.compare(CONFIG::DOUBLE_TYPE) ;
    bool       is_int    = !datatype.compare(CONFIG::INT_TYPE) ;
    bool       is_string = !datatype.compare(CONFIG::STRING_TYPE) ;

    if      (is_bool)   config_store.setProperty(key , bool(  a_var)           , nullptr) ;
    else if (is_double) config_store.setProperty(key , double(a_var)           , nullptr) ;
    else if (is_int)    config_store.setProperty(key , int(   a_var)           , nullptr) ;
    else if (is_string) config_store.setProperty(key ,        a_var.toString() , nullptr) ;
  }

DEBUG_TRACE_CONFIG_TYPES_VB

  for (int child_n = 0 ; child_n < config_store.getNumChildren() ; ++child_n)
    restoreVarTypeInfo(config_store.getChild(child_n)) ;
}

bool LinJamConfig::sanityCheckChannels(ValueTree channels)
{
  bool are_channels_sane = true ;
/* TODO: (issue #33)
  if (channels.getParent() == this->remoteUsers)
  {
    bool remote_has_useridx_property = channels.hasProperty(CONFIG::USERIDX_ID) ;
    if (!remote_has_useridx_property)
      channels.getParent().removeChild(channels , nullptr) ;

DEBUG_TRACE_SANITY_CHECK_USER
  }
*/
  for (int channel_n = 0 ; channel_n < channels.getNumChildren() ; ++channel_n)
  {
    ValueTree channel = channels.getChild(channel_n) ;

    bool channel_has_channelname_property = channel.hasProperty(CONFIG::CHANNEL_NAME_ID) ;
    bool channel_has_channelidx_property  = channel.hasProperty(CONFIG::CHANNEL_IDX_ID)  ;
    bool channel_has_pairidx_property     = channel.hasProperty(CONFIG::PAIR_IDX_ID)     ;
    bool channel_has_volume_property      = channel.hasProperty(CONFIG::VOLUME_ID)       ;
    bool channel_has_pan_property         = channel.hasProperty(CONFIG::PAN_ID)          ;
    bool channel_has_xmit_property        = channel.hasProperty(CONFIG::IS_XMIT_RCV_ID)  ;
    bool channel_has_mute_property        = channel.hasProperty(CONFIG::IS_MUTED_ID)     ;
    bool channel_has_solo_property        = channel.hasProperty(CONFIG::IS_SOLO_ID)      ;
    bool channel_has_source_property      = channel.hasProperty(CONFIG::SOURCE_N_ID)     ;
    bool channel_has_stereo_property      = channel.hasProperty(CONFIG::STEREO_ID)       ;
    bool channel_has_vuleft_property      = channel.hasProperty(CONFIG::VU_LEFT_ID)      ;
    bool channel_has_vuright_property     = channel.hasProperty(CONFIG::VU_RIGHT_ID)     ;

    bool channel_name_is_string    = channel[CONFIG::CHANNEL_NAME_ID].isString() ;
    bool channel_idx_is_int        = channel[CONFIG::CHANNEL_IDX_ID] .isInt()    ;
    bool channel_pair_idx_is_int   = channel[CONFIG::PAIR_IDX_ID]    .isInt()    ;
    bool channel_volume_is_double  = channel[CONFIG::VOLUME_ID]      .isDouble() ;
    bool channel_pan_is_double     = channel[CONFIG::PAN_ID]         .isDouble() ;
    bool channel_xmit_is_bool      = channel[CONFIG::IS_XMIT_RCV_ID] .isBool()   ;
    bool channel_mute_is_bool      = channel[CONFIG::IS_MUTED_ID]    .isBool()   ;
    bool channel_solo_is_bool      = channel[CONFIG::IS_SOLO_ID]     .isBool()   ;
    bool channel_source_is_int     = channel[CONFIG::SOURCE_N_ID]    .isInt()    ;
    bool channel_stereo_is_int     = channel[CONFIG::STEREO_ID]      .isInt()    ;
    bool channel_vuleft_is_double  = channel[CONFIG::VU_LEFT_ID]     .isDouble() ;
    bool channel_vuright_is_double = channel[CONFIG::VU_RIGHT_ID]    .isDouble() ;

DEBUG_TRACE_SANITY_CHECK_CHANNEL

    bool is_channel_sane =
        (channel_has_channelname_property && channel_has_channelidx_property &&
         channel_has_pairidx_property     && channel_has_volume_property     &&
         channel_has_pan_property         && channel_has_xmit_property       &&
         channel_has_mute_property        && channel_has_solo_property       &&
         channel_has_source_property      && channel_has_stereo_property     &&
         channel_has_vuleft_property      && channel_has_vuright_property     ) ;

    bool do_types_match = (channel_name_is_string    && channel_idx_is_int        &&
                           channel_pair_idx_is_int   && channel_volume_is_double  &&
                           channel_pan_is_double     && channel_xmit_is_bool      &&
                           channel_mute_is_bool      && channel_solo_is_bool      &&
                           channel_source_is_int     && channel_stereo_is_int     &&
                           channel_vuleft_is_double  && channel_vuright_is_double  ) ;

    if (!is_channel_sane)
    {
      channels.removeChild(channel , nullptr) ; --channel_n ;
      is_channel_sane = true ;
    }

    are_channels_sane = (are_channels_sane && is_channel_sane && do_types_match) ;
  }

  return are_channels_sane ;
}

void LinJamConfig::storeConfig()
{
DEBUG_TRACE_STORE_CONFIG

  XmlElement* config_xml = this->configValueTree.createXml() ;
  XmlElement* client     = config_xml->getChildByName(CONFIG::CLIENT_ID) ;

  // unset session dir and log file - these are too dangerous to be user-configuraable
  client->removeAttribute(CONFIG::SESSIONDIR_KEY) ;
  client->removeAttribute(CONFIG::LOGFILE_KEY) ;

  config_xml->writeToFile(this->configXmlFile , StringRef() , StringRef("UTF-8") , 0) ;
  delete config_xml ;
}

void LinJamConfig::establishSharedStore()
{
  // TODO: the Value objects created here are no longer being used
  //           although some of the instance vars are used for convenience
  //           it may be cleaner to use only the tree listener (issue #33)
  // client config
  this->saveAudio    .referTo(getClient(CONFIG::SAVE_AUDIO_ID)) ;
  this->shouldSaveLog.referTo(getClient(CONFIG::SAVE_LOG_ID)) ;
  this->debugLevel   .referTo(getClient(CONFIG::DEBUGLEVEL_ID)) ;
  this->autoSubscribe.referTo(getClient(CONFIG::AUTOSUBSCRIBE_ID)) ;
  this->autoSubscribeUsers = getNode(CONFIG::SUBSCRIPTIONS_ID) ;

  // device config
  this->audioIfN  .referTo(getAudio(CONFIG::AUDIO_IF_ID)) ;
  this->nInputs   .referTo(getAudio(CONFIG::N_INPUTS_ID)) ;
  this->nOutputs  .referTo(getAudio(CONFIG::N_OUTPUTS_ID)) ;
  this->bitDepth  .referTo(getAudio(CONFIG::BITDEPTH_ID)) ;
  this->sampleRate.referTo(getAudio(CONFIG::SAMPLERATE_ID)) ;
  this->jackName  .referTo(getAudio(CONFIG::JACK_NAME_ID)) ;

  // login state
  this->host          .referTo(getServer(CONFIG::HOST_ID)) ;
  this->login         .referTo(getServer(CONFIG::LOGIN_ID)) ;
  this->pass          .referTo(getServer(CONFIG::PASS_ID)) ;
  this->isAnonymous   .referTo(getServer(CONFIG::IS_ANON_ID)) ;
  this->isAgreed      .referTo(getServer(CONFIG::IS_AGREED_ID)) ;
  this->shouldAgree   .referTo(getServer(CONFIG::SHOULD_AGREE_ID)) ;
  this->shouldHideBots.referTo(getServer(CONFIG::SHOULD_HIDE_BOTS_ID)) ;

  // channels
  this->masterChannels = getNode(CONFIG::MASTERS_ID) ;
  this->localChannels  = getNode(CONFIG::LOCALS_ID) ;
// TODO: we are adding remote users directly to the root node for now for simplicity
//           mostly because Trace::SanitizeConfig() does not yet handle nested lists
//           but for clarity there should be a <remote-channels> tree (issue #33)
//   this->remoteUsers = getNode(CONFIG::REMOTES_ID) ; // (issue #33)
this->remoteUsers = this->configValueTree ; // kludge (issue #33)

  // per server user data
  this->servers = getNode(CONFIG::SERVERS_ID) ;
}


/* helpers */

ValueTree LinJamConfig::getNode(Identifier tree_node_id)
{
  ValueTree tree_node = this->configValueTree.getChildWithName(tree_node_id) ;

DEBUG_TRACE_CONFIG_TREE

  return tree_node ;
}

Value LinJamConfig::getLeaf(ValueTree parent_node , Identifier child_node_id ,
                                      Identifier key)
{
  ValueTree value_node = parent_node.getChildWithName(child_node_id) ;

DEBUG_TRACE_CONFIG_VALUE

  return (value_node.isValid() && value_node.hasProperty(key))?
         value_node.getPropertyAsValue(key , nullptr)         :
         this->dummyValue                                     ;
}

Value LinJamConfig::getClient(Identifier key)
{
  return getLeaf(this->configValueTree , CONFIG::CLIENT_ID , key) ;
}

Value LinJamConfig::getAudio(Identifier key)
{
  return getLeaf(this->configValueTree , CONFIG::AUDIO_ID  , key) ;
}

Value LinJamConfig::getServer(Identifier key)
{
  return getLeaf(this->configValueTree , CONFIG::SERVER_ID , key) ;
}

ValueTree LinJamConfig::addServer(String host_name , String login        ,
                                  String pass      , bool   is_anonymous )
{
  ValueTree server = getServer(host_name) ;
  if (!server.isValid())
  {
    server = ValueTree(makeHostId(host_name)) ;
    server.setProperty(CONFIG::HOST_ID         , host_name    , nullptr) ;
    server.setProperty(CONFIG::LOGIN_ID        , login        , nullptr) ;
    server.setProperty(CONFIG::PASS_ID         , pass         , nullptr) ;
    server.setProperty(CONFIG::IS_ANON_ID      , is_anonymous , nullptr) ;
    server.setProperty(CONFIG::SHOULD_AGREE_ID , false        , nullptr) ;

    this->servers        .addChild(server        , -1 , nullptr) ;
    this->configValueTree.addChild(this->servers , -1 , nullptr) ;
  }

  return server ;
}

String LinJamConfig::filteredName(String a_string)
{
  return a_string.retainCharacters(CONFIG::VALID_NAME_CHARS).replaceCharacter(' ', '-') ;
}


/* event handlers */

void LinJamConfig::valueTreePropertyChanged(ValueTree& a_node , const Identifier& a_key)
{
  Identifier node_id          = a_node     .getType() ;
  ValueTree  parent_node      = a_node     .getParent() ;
  Identifier parent_id        = parent_node.getType() ;
  ValueTree  grandparent_node = parent_node.getParent() ;
  bool       is_master        = parent_node      == this->masterChannels &&
                                node_id          == CONFIG::MASTER_ID ;
  bool       is_metro         = parent_node      == this->masterChannels &&
                                node_id          == CONFIG::METRO_ID ;
  bool       is_local         = parent_node      == this->localChannels ;
  bool       is_remote        = grandparent_node == this->remoteUsers ;

DEBUG_TRACE_CONFIG_TREE_CHANGED

  if      (node_id   == CONFIG::CLIENT_ID)        return ; // most likely will handle this eventuall
  else if (parent_id == CONFIG::SUBSCRIPTIONS_ID) return ; // most likely will handle this eventuall
  else if (node_id   == CONFIG::AUDIO_ID)         return ; // may or may not handle this (issue #12)
  else if (node_id   == CONFIG::SERVER_ID)        return ; // most likely wont need to handle these
  else if (parent_id == CONFIG::SERVERS_ID)       return ; // but we must guard for now (issue #33)

  if      (is_master) LinJam::ConfigureMasterChannel(a_key) ;
  else if (is_metro)  LinJam::ConfigureMetroChannel(a_key) ;
  else if (is_local)  LinJam::ConfigureLocalChannel(a_node , a_key) ;
  else if (is_remote) LinJam::ConfigureRemoteChannel(parent_node , a_node , a_key) ;
}
