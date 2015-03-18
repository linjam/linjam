/*
  ==============================================================================

    LinJamConfig.cpp
    Created: 12 Jun 2014 7:05:12am
    Author:  me

  ==============================================================================
*/

#include "LinJam.h"
#include "./Trace/TraceLinJamConfig.h"


/* LinJamConfig class public class methods */

LinJamConfig::LinJamConfig() { initialize() ; }

LinJamConfig::~LinJamConfig() { storeConfig() ; }

Identifier LinJamConfig::MakeHostId(String host)
{
  return Identifier(CONFIG::SERVER_KEY + "-" + host.replaceCharacters(".:" , "--")) ;
}

Identifier LinJamConfig::MakeUserId(String user_name)
{
  return user_name.upToFirstOccurrenceOf(CONFIG::USER_IP_SPLIT_CHAR , false , true)
                  .retainCharacters(CONFIG::VALID_NAME_CHARS)
                  .replaceCharacter(' ', '-') ;
}

Identifier LinJamConfig::MakeChannelId(int channel_idx)
{
  return (channel_idx == CONFIG::MASTER_CHANNEL_IDX)                     ?
         CONFIG::MASTER_ID                                               :
         Identifier(CONFIG::CHANNEL_BASE_ID + "-" + String(channel_idx)) ;
}

String LinJamConfig::MakeStereoName(String channel_name , int stereo_status)
{
  return TrimStereoName(channel_name) +
         ((stereo_status == CONFIG::STEREO_L)? CLIENT::STEREO_L_POSTFIX :
          (stereo_status == CONFIG::STEREO_R)? CLIENT::STEREO_R_POSTFIX : "") ;
}

String LinJamConfig::TrimStereoName(String channel_name)
{
  String stereo_postfix = channel_name.getLastCharacters(CLIENT::STEREO_POSTFIX_N_CHARS) ;

  return (stereo_postfix != CLIENT::STEREO_L_POSTFIX &&
          stereo_postfix != CLIENT::STEREO_R_POSTFIX  )? channel_name  :
          channel_name.dropLastCharacters(CLIENT::STEREO_POSTFIX_N_CHARS) ;
}

int LinJamConfig::ParseStereoStatus(String channel_name)
{
  // determine faux-stereo stereo status based on channel name
  String postfix = channel_name.getLastCharacters(CLIENT::STEREO_POSTFIX_N_CHARS) ;
  return (!postfix.compare(CLIENT::STEREO_L_POSTFIX))? CONFIG::STEREO_L :
         (!postfix.compare(CLIENT::STEREO_R_POSTFIX))? CONFIG::STEREO_R :
                                                       CONFIG::MONO     ;
}

ValueTree LinJamConfig::NewChannel(String channel_name , int channel_idx)
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


/* LinJamConfig class private instance methods */

/* init */

void LinJamConfig::initialize()
{
  // load default and stored configs
  File        this_binary       = File::getSpecialLocation(File::currentExecutableFile) ;
  this->      configXmlFile     = this_binary.getSiblingFile(CONFIG::PERSISTENCE_FILENAME) ;
  XmlElement* default_xml       = XmlDocument::parse(CONFIG::DEFAULT_CONFIG_XML) ;
  XmlElement* stored_xml        = XmlDocument::parse(this->configXmlFile) ;
  bool        has_stored_config = stored_xml != nullptr                         &&
                                  stored_xml->hasTagName(CONFIG::PERSISTENCE_ID) ;

DEBUG_TRACE_LOAD_CONFIG

  if (default_xml == nullptr) { delete stored_xml ; return ; } // panic

DEBUG_TRACE_DUMP_CONFIG

  // validate config version
  double stored_version  = (!has_stored_config) ? 0.0                                :
                           stored_xml->getDoubleAttribute(CONFIG::CONFIG_VERSION_ID) ;
  bool do_versions_match = stored_version == CONFIG::CONFIG_VERSION ;
  if (!do_versions_match) ; // TODO: convert (if ever necessary)

  // create static config ValueTree from stored xml persistence or default
  if (has_stored_config && do_versions_match)
    this->configRoot = sanitizeConfig(ValueTree::fromXml(*default_xml) ,
                                      ValueTree::fromXml(*stored_xml)) ;
  else
    this->configRoot = ValueTree::fromXml(*default_xml) ;

  // instantiate shared value holders and restore type data
  establishSharedStore() ; restoreVarTypeInfo(this->configRoot) ;

  // prune any corrupted user-defined data
  validateServers() ; validateUsers() ;
  validateChannels(this->localChannels) ;

  // write back sanitized config to disk and cleanup
  storeConfig() ; delete default_xml ; delete stored_xml ;

  // register listeners on interesting nodes for central dispatcher
  this->subscriptions .addListener(this) ;
  this->audio         .addListener(this) ;
  this->masterChannels.addListener(this) ;
  this->localChannels .addListener(this) ;
  this->remoteUsers   .addListener(this) ;
}

void LinJamConfig::establishSharedStore()
{
  // client config
  this->client         = this->configRoot.getChildWithName(CONFIG::CLIENT_ID) ;
  // ignore list
  this->subscriptions  = this->configRoot.getChildWithName(CONFIG::SUBSCRIPTIONS_ID) ;
  // device config
  this->audio          = this->configRoot.getChildWithName(CONFIG::AUDIO_ID) ;
  // login state
  this->server         = this->configRoot.getChildWithName(CONFIG::SERVER_ID) ;
  // per server credentials
  this->servers        = this->configRoot.getChildWithName(CONFIG::SERVERS_ID) ;
  // channels
  this->masterChannels = this->configRoot.getChildWithName(CONFIG::MASTERS_ID) ;
  this->localChannels  = this->configRoot.getChildWithName(CONFIG::LOCALS_ID) ;
  this->remoteUsers    = this->configRoot.getChildWithName(CONFIG::REMOTES_ID) ;
}

void LinJamConfig::restoreVarTypeInfo(ValueTree config_store)
{
  Identifier  node_id          = config_store.getType() ;
  ValueTree   parent_node      = config_store.getParent() ;
  ValueTree   grandparent_node = config_store.getParent().getParent() ;
  XmlElement* config_types_xml = XmlDocument::parse(CONFIG::CONFIG_TYPES) ;
  ValueTree   config_types     = ValueTree::fromXml(*config_types_xml) ;
  ValueTree   types_store ;                   delete config_types_xml ;

  if      (config_store        == this->configRoot)
    types_store = config_types ;
  else if (config_store        == this->client          ||
           config_store        == this->subscriptions   ||
           config_store        == this->audio           ||
           config_store        == this->server           )
    types_store = config_types.getChildWithName(node_id) ;
  else if (parent_node         == this->servers)
    types_store = config_types.getChildWithName(CONFIG::SERVER_ID) ;
  else if (parent_node         == this->masterChannels ||
           parent_node         == this->localChannels  ||
           grandparent_node    == this->remoteUsers     )
    types_store = config_types.getChildWithName(CONFIG::CHANNELS_ID) ;
  else if (parent_node         == this->remoteUsers)
    types_store = config_types.getChildWithName(CONFIG::USERS_ID) ;

DEBUG_TRACE_CONFIG_TYPES_VB

  for (int property_n = 0 ; property_n < config_store.getNumProperties() ; ++property_n)
  {
    Identifier key       = config_store.getPropertyName(property_n) ;
    var        a_var     = config_store[key] ;
    String     datatype  = types_store[key] ;
    bool       is_bool   = !datatype.compare(CONFIG::BOOL_TYPE) ;
    bool       is_double = !datatype.compare(CONFIG::DOUBLE_TYPE) ;
    bool       is_int    = !datatype.compare(CONFIG::INT_TYPE) ;
    bool       is_string = !datatype.compare(CONFIG::STRING_TYPE) ;

    if      (is_bool)    config_store.setProperty(   key , bool(  a_var) , nullptr) ;
    else if (is_double)  config_store.setProperty(   key , double(a_var) , nullptr) ;
    else if (is_int)     config_store.setProperty(   key , int(   a_var) , nullptr) ;
    else if (!is_string) config_store.removeProperty(key ,                 nullptr) ;

DEBUG_TRACE_CONFIG_TYPES_VB_EACH
  }

  for (int child_n = 0 ; child_n < config_store.getNumChildren() ; ++child_n)
    restoreVarTypeInfo(config_store.getChild(child_n)) ;
}

void LinJamConfig::storeConfig()
{
DEBUG_TRACE_STORE_CONFIG

  XmlElement* config_xml = this->configRoot.createXml() ;

  config_xml->writeToFile(this->configXmlFile , StringRef() , StringRef("UTF-8") , 0) ;
  delete config_xml ;
}


/* validation */

ValueTree LinJamConfig::sanitizeConfig(ValueTree default_config , ValueTree stored_config)
{
  Identifier default_node_name  = default_config.getType() ;
  int        n_properties       = default_config.getNumProperties() ;
  int        n_default_children = default_config.getNumChildren() ;
  int        n_stored_children  = stored_config .getNumChildren() ;

  // transfer any missing attributes
  for (int property_n = 0 ; property_n < n_properties ; ++property_n)
  {
    Identifier key   = default_config.getPropertyName(property_n) ;
    var        value = default_config.getProperty(key) ;
    if (!stored_config.hasProperty(key)) stored_config.setProperty(key , value , nullptr) ;
  }

  // transfer any missing nodes
  for (int child_n = 0 ; child_n < n_default_children ; ++child_n)
  {
    ValueTree  default_child      = default_config.getChild(child_n) ;
    Identifier default_child_name = default_child .getType() ;
    ValueTree  stored_child       = stored_config .getChildWithName(default_child_name) ;

    // transfer missing node
    if (!stored_child.isValid())
    {
      // for local channels we transfer the default channel only if none are stored
      if (default_node_name != CONFIG::LOCALS_ID || !n_stored_children)
      {
        default_config.removeChild(default_child ,      nullptr) ;
        stored_config .addChild(   default_child , -1 , nullptr) ;
        --child_n ;
      }
      continue ;
    }

    // recurse on child node
    sanitizeConfig(default_child , stored_child) ;
  }

  return stored_config ;
}

void LinJamConfig::validateServers() {} // TODO:

void LinJamConfig::validateUsers()
{
  for (int user_n = 0 ; user_n < this->remoteUsers.getNumChildren() ; ++user_n)
  {
    ValueTree user_store = this->remoteUsers.getChild(user_n) ;
    bool user_has_useridx_property = user_store.hasProperty(CONFIG::USER_IDX_ID) ;
    if (!user_has_useridx_property) this->remoteUsers.removeChild(user_store , nullptr) ;
    else
    {
      // ensure that NJClient will be configured for ignored users upon join
      ValueTree master_store = getChannelByIdx(user_store , CONFIG::MASTER_CHANNEL_IDX) ;
      master_store.setProperty(CONFIG::IS_XMIT_RCV_ID , true , nullptr) ;

      validateChannels(user_store) ;
    }

DEBUG_TRACE_VALIDATE_USER
  }
}

void LinJamConfig::validateChannels(ValueTree channels)
{
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

    if (!channel_has_channelname_property || !channel_has_channelidx_property ||
        !channel_has_pairidx_property     || !channel_has_volume_property     ||
        !channel_has_pan_property         || !channel_has_xmit_property       ||
        !channel_has_mute_property        || !channel_has_solo_property       ||
        !channel_has_source_property      || !channel_has_stereo_property     ||
        !channel_has_vuleft_property      || !channel_has_vuright_property     )
    { channels.removeChild(channel , nullptr) ; --channel_n ; }

DEBUG_TRACE_VALIDATE_CHANNEL
  }
}

bool LinJamConfig::validateConfig()
{
  // validate subscribed trees
  bool root_is_valid            = this->configRoot     .isValid() ;
  bool client_is_valid          = this->client         .isValid() ;
  bool subscriptions_is_valid   = this->subscriptions  .isValid() ;
  bool audio_is_valid           = this->audio          .isValid() ;
  bool server_is_valid          = this->server         .isValid() ;
  bool servers_is_valid         = this->servers        .isValid() ;
  bool master_channels_is_valid = this->masterChannels .isValid() ;
  bool local_channels_is_valid  = this->localChannels  .isValid() ;
  bool remote_users_is_valid    = this->remoteUsers    .isValid() ;

  bool is_valid = (root_is_valid            && client_is_valid         &&
                   subscriptions_is_valid   && audio_is_valid          &&
                   server_is_valid          && servers_is_valid        &&
                   master_channels_is_valid && local_channels_is_valid &&
                   remote_users_is_valid                                ) ;

DEBUG_TRACE_VALIDATE_CONFIG // modifies 'bool is_valid'

  return is_valid ;
}

bool LinJamConfig::isConfigValid()
{
  bool is_config_valid = validateConfig() ;

  if (!is_config_valid)
  {
    this->configRoot = ValueTree::invalid ;
    if (this->configXmlFile.existsAsFile())
    { this->configXmlFile.deleteFile() ; initialize() ; }

DEBUG_TRACE_CLOBBER_CONFIG

    is_config_valid = validateConfig() ;
  }

  return is_config_valid ;
}


/* getters/setters */

ValueTree LinJamConfig::addChannel(ValueTree channels_store  ,
                                   ValueTree new_channel_node)
{
DEBUG_TRACE_ADD_CHANNEL_STORE

  // ensure trees are valid and storage does not already exist for this channel
  if (!channels_store.isValid() || !new_channel_node.isValid())  return ValueTree::invalid ;
  if (new_channel_node.getParent() == channels_store)            return new_channel_node ;

  int       channel_idx   = int(new_channel_node[CONFIG::CHANNEL_IDX_ID]) ;
  ValueTree channel_store = ValueTree(MakeChannelId(channel_idx)) ;

  channel_store .copyPropertiesFrom(new_channel_node , nullptr) ;
  channels_store.addChild(channel_store , -1  , nullptr) ;

  return channel_store ;
}

void LinJamConfig::removeChannel(ValueTree channels_store , ValueTree channel_store)
{
DEBUG_TRACE_REMOVE_CHANNEL_STORE

  channels_store.removeChild(channel_store , nullptr) ;
}

ValueTree LinJamConfig::getOrAddRemoteUser(String user_name)
{
  Identifier user_id    = MakeUserId(user_name) ;
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
    channel_store = NewChannel(channel_name , channel_idx) ;
    if (channel_idx == CONFIG::DEFAULT_CHANNEL_IDX)
      setStereo(channel_store , CONFIG::STEREO_L) ;
    channel_store = addChannel(user_store , channel_store) ;
  }

  return channel_store ;
}

ValueTree LinJamConfig::getUserById(Identifier user_id)
{
  return this->remoteUsers.getChildWithName(user_id) ;
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

void LinJamConfig::setCredentials(String host , String login       ,
                                  String pass , bool   is_anonymous)
{
  if (is_anonymous) pass = "" ;
  bool   is_agreed = bool(getServer(host)[CONFIG::SHOULD_AGREE_ID]) ;
#ifdef KNOWN_BOTS_AS_ARRAY
  String bot_name  = "nfg-thats-why-xml" ;
#else // KNOWN_BOTS_AS_ARRAY
#  ifdef KNOWN_BOTS_AS_XML
  String bot_name  = NETWORK::KNOWN_BOTS->getStringAttribute(MakeHostId(host) , "") ;
#  endif // KNOWN_BOTS_AS_XML
#endif // KNOWN_BOTS_AS_ARRAY
  int    bot_idx   = CONFIG::DEFAULT_BOT_USERIDX ;

  this->server.setProperty(CONFIG::HOST_ID         , host         , nullptr)
              .setProperty(CONFIG::LOGIN_ID        , login        , nullptr)
              .setProperty(CONFIG::PASS_ID         , pass         , nullptr)
              .setProperty(CONFIG::IS_ANONYMOUS_ID , is_anonymous , nullptr)
              .setProperty(CONFIG::SHOULD_AGREE_ID , is_agreed    , nullptr)
              .setProperty(CONFIG::IS_AGREED_ID    , is_agreed    , nullptr)
              .setProperty(CONFIG::BOT_NAME_ID     , bot_name     , nullptr)
              .setProperty(CONFIG::BOT_USERIDX_ID  , bot_idx      , nullptr) ;
}

ValueTree LinJamConfig::getCredentials(String host)
{
  // return copy of stored credentials
  ValueTree stored_server = getServer(host) ;
  ValueTree server_copy   = ValueTree(MakeHostId(host)) ;

  if (stored_server.isValid()) server_copy.copyPropertiesFrom(stored_server , nullptr) ;
  else                         server_copy = ValueTree::invalid ;

  return server_copy ;
}

void LinJamConfig::setServer()
{
  // copy volatile login state to persistent storage
  String    host         =      this->server[CONFIG::HOST_ID        ].toString() ;
  String    login        =      this->server[CONFIG::LOGIN_ID       ].toString() ;
  String    pass         =      this->server[CONFIG::PASS_ID        ].toString() ;
  bool      is_anonymous = bool(this->server[CONFIG::IS_ANONYMOUS_ID]) ;
  bool      should_agree = bool(this->server[CONFIG::SHOULD_AGREE_ID]) ;
  ValueTree server       = getServer(host) ;

  // create new server entry
  if (!server.isValid())
  {
    server = ValueTree(MakeHostId(host)) ;
    this->servers.addChild(server , -1 , nullptr) ;
  }

  // set per server credentials
  server.setProperty(CONFIG::HOST_ID         , host         , nullptr)
        .setProperty(CONFIG::LOGIN_ID        , login        , nullptr)
        .setProperty(CONFIG::PASS_ID         , pass         , nullptr)
        .setProperty(CONFIG::IS_ANONYMOUS_ID , is_anonymous , nullptr)
        .setProperty(CONFIG::SHOULD_AGREE_ID , should_agree , nullptr) ;
}

ValueTree LinJamConfig::getServer(String host)
{
  return this->servers.getChildWithProperty(CONFIG::HOST_ID , var(host)) ;
}

void LinJamConfig::setStereo(ValueTree channel_store , int stereo_status)
{
  channel_store.setProperty(CONFIG::STEREO_ID , stereo_status , nullptr) ;
}

int LinJamConfig::setRemoteStereo(ValueTree user_store        , ValueTree channel_store ,
                                  String    prev_channel_name                           )
{
  String channel_name  = channel_store[CONFIG::CHANNEL_NAME_ID].toString() ;
  int    stereo_status = ParseStereoStatus(channel_name) ;
  int    prev_status   = ParseStereoStatus(prev_channel_name) ;

  // ensure remote faux-stereo channels are paired
  if (stereo_status != CONFIG::MONO)
  {
    // find channel with name matching this channel_name + opposite_postfix
    // to ignore duplicate names this assumes that stereo pairs are contiguous
    int    channel_idx = int(channel_store[CONFIG::CHANNEL_IDX_ID]) ;
    String l_pair_name = MakeStereoName(channel_name , CONFIG::STEREO_L) ;
    String r_pair_name = MakeStereoName(channel_name , CONFIG::STEREO_R) ;
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
    String    l_pair_name          = MakeStereoName(prev_channel_name , CONFIG::STEREO_L) ;
    String    r_pair_name          = MakeStereoName(prev_channel_name , CONFIG::STEREO_R) ;
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


/* event handlers */

void LinJamConfig::valueChanged(Value& a_value)
{
DEBUG_TRACE_CONFIG_VALUE_CHANGED

  // update state
  if (a_value.refersToSameSourceAs(LinJam::Status)) LinJam::HandleStatusChanged() ;

  // store server credentials on successful login
  if (LinJam::Status == NJClient::NJC_STATUS_OK) setServer() ;
}

void LinJamConfig::valueTreePropertyChanged(ValueTree& a_node , const Identifier& a_key)
{
  Identifier node_id          = a_node     .getType() ;
  ValueTree  parent_node      = a_node     .getParent() ;
  Identifier parent_id        = parent_node.getType() ;
  ValueTree  grandparent_node = parent_node.getParent() ;

  bool       is_subscriptions = a_node           == this->subscriptions ;
  bool       is_audio         = a_node           == this->audio ;
  bool       is_master        = parent_node      == this->masterChannels &&
                                node_id          == CONFIG::MASTER_ID ;
  bool       is_metro         = parent_node      == this->masterChannels &&
                                node_id          == CONFIG::METRO_ID ;
  bool       is_local         = parent_node      == this->localChannels ;
  bool       is_remote        = grandparent_node == this->remoteUsers ;

DEBUG_TRACE_CONFIG_TREE_CHANGED

  if      (is_subscriptions) LinJam::ConfigureSubscriptions() ;
  else if (is_audio)         LinJam::InitializeAudio() ;
  else if (is_master)        LinJam::ConfigureMasterChannel(a_key) ;
  else if (is_metro)         LinJam::ConfigureMetroChannel(a_key) ;
  else if (is_local)         LinJam::ConfigureLocalChannel(a_node , a_key) ;
  else if (is_remote)        LinJam::ConfigureRemoteChannel(parent_node , a_node , a_key) ;
}

void LinJamConfig::valueTreeChildAdded(ValueTree& a_parent_node , ValueTree& a_node)
{
DEBUG_TRACE_CONFIG_TREE_ADDED

  Identifier node_id          = a_node.getType() ;
  bool       is_subscriptions = a_parent_node == this->subscriptions ;

  if (is_subscriptions)
  {
    LinJam::ConfigureSubscriptions() ; LinJam::HandleUserInfoChanged() ;
  }
}

void LinJamConfig::valueTreeChildRemoved(ValueTree& a_parent_node , ValueTree& a_node)
{
DEBUG_TRACE_CONFIG_TREE_REMOVED

  Identifier node_id          = a_node.getType() ;
  bool       is_subscriptions = a_parent_node == this->subscriptions ;

  if (is_subscriptions)
  {
    LinJam::ConfigureSubscriptions() ; LinJam::HandleUserInfoChanged() ;
  }
}
