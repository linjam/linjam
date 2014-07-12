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


/* LinJamConfig public class methods */

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

  // create static config ValueTree
  if (is_stored_config_bogus)
    this->configValueTree = ValueTree::fromXml(*default_config_xml) ;
  else
    this->configValueTree = sanitizeConfig(ValueTree::fromXml(*default_config_xml) ,
                                           ValueTree::fromXml(*stored_config_xml)) ;

  // set session dir and log file - these are too dangerous to be user-configuraable
  ValueTree client = this->configValueTree.getChildWithName(CONFIG::CLIENT_ID) ;
  client.setProperty(CONFIG::SESSIONDIR_ID , CONFIG::SESSIONDIR , nullptr) ;
  client.setProperty(CONFIG::LOGFILE_ID    , CONFIG::LOGFILE    , nullptr) ;

  storeConfig() ; delete default_config_xml ; delete stored_config_xml ;

  // instantiate shared value holders
  establishSharedStore() ;
}

LinJamConfig::~LinJamConfig() { storeConfig() ; }


/* LinJamConfig public instance methods */

bool LinJamConfig::sanityCheck()
{
  // TODO: (issue #33)
  //       most of these are unused or redundant and no longer needed as Value holders
  //       only ValueTree::Listeners are being used and all of their properties will
  //       exist after sanitizeConfig() so only transient channels need be validated here
  ValueTree master_channel = this->masterChannels.getChildWithName(CONFIG::MASTER_ID) ;
  ValueTree metro_channel  = this->masterChannels.getChildWithName(CONFIG::METRO_ID) ;

  // subscribed trees
  bool root_is_valid                         =
    this->configValueTree     .isValid()                              ;
  bool auto_subscribe_users_is_valid         =
    this->autoSubscribeUsers  .isValid()                              ;
  bool master_channels_is_valid              =
    this->masterChannels      .isValid()                              ;
  bool local_channels_is_valid               =
    this->localChannels       .isValid()                              ;
  bool servers_is_valid                      =
    this->servers             .isValid()                              ;

  // implicitly subscribed values (via above trees)
  bool master_channel_has_name_property   =
    master_channel            .hasProperty(CONFIG::CHANNELNAME_ID)    ;
  bool master_channel_has_volume_property =
    master_channel            .hasProperty(CONFIG::VOLUME_ID)         ;
  bool master_channel_has_pan_property    =
    master_channel            .hasProperty(CONFIG::PAN_ID)            ;
  bool master_channel_has_mute_property   =
    master_channel            .hasProperty(CONFIG::IS_MUTED_ID)       ;
  bool metro_channel_has_name_property    =
    metro_channel             .hasProperty(CONFIG::CHANNELNAME_ID)    ;
  bool metro_channel_has_volume_property  =
    metro_channel             .hasProperty(CONFIG::VOLUME_ID)         ;
  bool metro_channel_has_pan_property     =
    metro_channel             .hasProperty(CONFIG::PAN_ID)            ;
  bool metro_channel_has_mute_property    =
    metro_channel             .hasProperty(CONFIG::IS_MUTED_ID)       ;
  bool metro_channel_has_source_property  =
    metro_channel             .hasProperty(CONFIG::SOURCE_N_ID)       ;
  bool metro_channel_has_stereo_property  =
    metro_channel             .hasProperty(CONFIG::IS_STEREO_ID)      ;

  // transient channels
  sanityCheckChannels(this->localChannels) ;
//   sanityCheckChannels(this->remoteUsers) ; // TODO: (issue #33)

  // explicitly subscribed values
  bool should_save_audio_has_value        =
    !this->shouldSaveAudio    .refersToSameSourceAs(this->dummyValue) ;
  bool should_save_log_has_value          =
    !this->shouldSaveLog      .refersToSameSourceAs(this->dummyValue) ;
  bool debug_level_has_value              =
    !this->debugLevel         .refersToSameSourceAs(this->dummyValue) ;
  bool should_auto_subscribe_has_value    =
    !this->shouldAutoSubscribe.refersToSameSourceAs(this->dummyValue) ;
  bool audio_if_n_has_value               =
    !this->audioIfN           .refersToSameSourceAs(this->dummyValue) ;
  bool n_inputs_has_value                 =
    !this->nInputs            .refersToSameSourceAs(this->dummyValue) ;
  bool n_outputs_has_value                =
    !this->nOutputs           .refersToSameSourceAs(this->dummyValue) ;
  bool bit_depth_has_value                =
    !this->bitDepth           .refersToSameSourceAs(this->dummyValue) ;
  bool sample_rate_has_value              =
    !this->sampleRate         .refersToSameSourceAs(this->dummyValue) ;
  bool jack_name_has_value                =
    !this->jackName           .refersToSameSourceAs(this->dummyValue) ;
  bool current_host_has_value             =
    !this->currentHost        .refersToSameSourceAs(this->dummyValue) ;
  bool current_login_has_value            =
    !this->currentLogin       .refersToSameSourceAs(this->dummyValue) ;
  bool current_pass_has_value             =
    !this->currentPass        .refersToSameSourceAs(this->dummyValue) ;
  bool current_is_anonymous_has_value     =
    !this->currentIsAnonymous .refersToSameSourceAs(this->dummyValue) ;
  bool current_is_agreed_has_value        =
    !this->currentIsAgreed    .refersToSameSourceAs(this->dummyValue) ;
  bool should_hide_bots_has_value         =
    !this->shouldHideBots     .refersToSameSourceAs(this->dummyValue) ;

DEBUG_TRACE_SANITY_CHECK

  return (root_is_valid                           &&
          auto_subscribe_users_is_valid           &&
          master_channels_is_valid                &&
          local_channels_is_valid                 &&
//           remote_users_is_valid                &&
          servers_is_valid                        &&
          master_channel_has_name_property        &&
          master_channel_has_volume_property      &&
          master_channel_has_pan_property         &&
          master_channel_has_mute_property        &&
          metro_channel_has_name_property         &&
          metro_channel_has_volume_property       &&
          metro_channel_has_pan_property          &&
          metro_channel_has_mute_property         &&
          metro_channel_has_source_property       &&
          metro_channel_has_stereo_property       &&
          should_save_audio_has_value             &&
          should_save_log_has_value               &&
          debug_level_has_value                   &&
          should_auto_subscribe_has_value         &&
          audio_if_n_has_value                    &&
          n_inputs_has_value                      &&
          n_outputs_has_value                     &&
          bit_depth_has_value                     &&
          sample_rate_has_value                   &&
          jack_name_has_value                     &&
          current_host_has_value                  &&
          current_login_has_value                 &&
          current_pass_has_value                  &&
          current_is_anonymous_has_value          &&
          current_is_agreed_has_value             &&
          should_hide_bots_has_value               ) ;
}

Identifier LinJamConfig::makeChannelId(int channel_idx)
{
  return Identifier(CONFIG::CHANNEL_BASE_ID + "-" + String(channel_idx)) ;
}

String LinJamConfig::parseUsername(String user_name)
{
  return user_name.upToFirstOccurrenceOf(CONFIG::USER_IP_SPLIT_CHAR , false , true) ;
}

Identifier LinJamConfig::encodeUserId(String user_name , int user_idx)
{
  return filteredName(parseUsername(user_name)) ;
}

ValueTree LinJamConfig::getOrCreateUser(String user_name , int   user_idx ,
                                        float  volume    , float pan      , bool is_muted)
{
  Identifier user_id    = encodeUserId(user_name , user_idx) ;
  ValueTree  user_store = getUserById(user_id) ;

  if (!user_store.isValid())
  {
    user_store = ValueTree(user_id) ;
    this->remoteUsers.addChild(user_store , -1 , nullptr) ;

DEBUG_TRACE_ADD_REMOTE_USER_STORE
  }

  return user_store ;
}

ValueTree LinJamConfig::getOrCreateChannel(Identifier channels_id   , String channel_name ,
                                           int        channel_idx   , float  volume       ,
                                           float      pan           , bool   is_xmit_rcv  ,
                                           bool       is_muted      , bool   is_solo      ,
                                           int        source_sink_n , bool   is_stereo    )
{
  Identifier channel_id    = (channel_idx == CLIENT::MASTER_IDX)?
                             channel_name                       :
                             makeChannelId(channel_idx)       ;
  ValueTree  channel_store = getChannelById(channels_id , channel_id) ;

  if (!channel_store.isValid())
  {
#ifdef KLUDGE_SET_INITIAL_REMOTE_GAIN_TO_ZERO
    volume = 0.0f ;
#endif // KLUDGE_SET_INITIAL_REMOTE_GAIN_TO_ZERO

    // add new channel
    channel_store = ValueTree(channel_id) ;
    channel_store.setProperty(CONFIG::CHANNELIDX_ID  , channel_idx   , nullptr) ;
    channel_store.setProperty(CONFIG::CHANNELNAME_ID , channel_name  , nullptr) ;
    channel_store.setProperty(CONFIG::VOLUME_ID      , volume        , nullptr) ;
    channel_store.setProperty(CONFIG::PAN_ID         , pan           , nullptr) ;
    channel_store.setProperty(CONFIG::IS_XMIT_ID     , is_xmit_rcv   , nullptr) ;
    channel_store.setProperty(CONFIG::IS_MUTED_ID    , is_muted      , nullptr) ;
    channel_store.setProperty(CONFIG::IS_SOLO_ID     , is_solo       , nullptr) ;
    channel_store.setProperty(CONFIG::SOURCE_N_ID    , source_sink_n , nullptr) ;
    channel_store.setProperty(CONFIG::IS_STEREO_ID   , is_stereo     , nullptr) ;
    if (channels_id == GUI::LOCALS_ID)
      this->localChannels.addChild(channel_store , -1 , nullptr) ;
    else
    {
      // assume this is a remote channel // TODO: (issue #33)
      ValueTree user_store = getUserById(channels_id) ;
      if (user_store.isValid()) user_store.addChild(channel_store , -1 , nullptr) ;
    }

DEBUG_TRACE_ADD_CHANNEL_STORE
  }

  return channel_store ;
}

ValueTree LinJamConfig::getUserById(Identifier user_id)
{
  return this->configValueTree.getChildWithName(user_id) ;
}

ValueTree LinJamConfig::getChannelByIdx(ValueTree channels_store , int channel_idx)
{
  return channels_store.getChildWithProperty(CONFIG::CHANNELIDX_ID , channel_idx) ;
}

ValueTree LinJamConfig::getChannelById(Identifier channels_id , Identifier channel_id)
{
  ValueTree channels_store ;
  if      (channels_id == GUI::MASTERS_ID) channels_store = this->masterChannels ;
  else if (channels_id == GUI::LOCALS_ID)  channels_store = this->localChannels ;
  else                                     channels_store = getUserById(channels_id) ;

  return channels_store.getChildWithName(channel_id) ;
}

void LinJamConfig::setServer()
{
  // copy volatile login state to persistent storage
  String host         =      this->currentHost.toString() ;
  String login        =      this->currentLogin.toString() ;
  String pass         =      this->currentPass.toString() ;
  bool   is_anonymous = bool(this->currentIsAnonymous.getValue()) ;

  ValueTree server = addServer(host , login , pass , is_anonymous) ;
  server.setProperty(CONFIG::HOST_ID  , host         , nullptr) ;
  server.setProperty(CONFIG::LOGIN_ID , login        , nullptr) ;
  server.setProperty(CONFIG::PASS_ID  , pass         , nullptr) ;
  server.setProperty(CONFIG::ANON_ID  , is_anonymous , nullptr) ;
}

void LinJamConfig::setCurrentServer(String host , String login , String pass ,
                                    bool   is_anonymous                      )
{
  this->currentHost        = host ;
  this->currentLogin       = login ;
  this->currentPass        = (is_anonymous)? "" : pass ;
  this->currentIsAnonymous = is_anonymous ;
  this->currentIsAgreed    = false ;
}

ValueTree LinJamConfig::getCurrentServer()
{
  return getServer(this->currentHost.toString()) ;
}

ValueTree LinJamConfig::getServer(String host)
{
  return this->servers.getChildWithProperty(CONFIG::HOST_ID , var(host)) ;
}

void LinJamConfig::setServerShouldAgree(bool should_agree)
{
  // continuation of setServer() after license agreement
  ValueTree server = getCurrentServer() ; if (!server.isValid()) return ;

  server.setProperty(CONFIG::AGREE_ID , should_agree , nullptr) ;
}


/* LinJamConfig private instance methods */

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

bool LinJamConfig::sanityCheckChannels(ValueTree channels)
{
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
    bool channel_has_channelidx_property = channel.hasProperty(CONFIG::CHANNELIDX_ID) ;
    bool channel_has_volume_property     = channel.hasProperty(CONFIG::VOLUME_ID)     ;
    bool channel_has_pan_property        = channel.hasProperty(CONFIG::PAN_ID)        ;
    bool channel_has_xmit_property       = channel.hasProperty(CONFIG::IS_XMIT_ID)    ;
    bool channel_has_mute_property       = channel.hasProperty(CONFIG::IS_MUTED_ID)   ;
    bool channel_has_solo_property       = channel.hasProperty(CONFIG::IS_SOLO_ID)    ;
    bool channel_has_source_property     = channel.hasProperty(CONFIG::SOURCE_N_ID)   ;
    bool channel_has_stereo_property     = channel.hasProperty(CONFIG::IS_STEREO_ID)  ;

DEBUG_TRACE_SANITY_CHECK_CHANNEL

    if (channel_has_channelidx_property && channel_has_volume_property &&
        channel_has_pan_property        && channel_has_xmit_property   &&
        channel_has_mute_property       && channel_has_solo_property   &&
        channel_has_source_property     && channel_has_stereo_property  )
      continue ;

    channels.removeChild(channel , nullptr) ; --channel_n ;
  }
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
  this->shouldSaveAudio    .referTo(getClient(CONFIG::SAVE_AUDIO_ID)) ;
  this->shouldSaveLog      .referTo(getClient(CONFIG::SAVE_LOG_ID)) ;
  this->debugLevel         .referTo(getClient(CONFIG::DEBUGLEVEL_ID)) ;
  this->shouldAutoSubscribe.referTo(getClient(CONFIG::AUTOSUBSCRIBE_ID)) ;
  this->autoSubscribeUsers = getNode(CONFIG::SUBSCRIPTIONS_ID) ;

  // device config
  this->audioIfN  .referTo(getAudio(CONFIG::AUDIO_IF_ID)) ;
  this->nInputs   .referTo(getAudio(CONFIG::N_INPUTS_ID)) ;
  this->nOutputs  .referTo(getAudio(CONFIG::N_OUTPUTS_ID)) ;
  this->bitDepth  .referTo(getAudio(CONFIG::BITDEPTH_ID)) ;
  this->sampleRate.referTo(getAudio(CONFIG::SAMPLERATE_ID)) ;
  this->jackName  .referTo(getAudio(CONFIG::JACK_NAME_ID)) ;

  // login state
  this->currentHost       .referTo(getServer(CONFIG::HOST_ID)) ;
  this->currentLogin      .referTo(getServer(CONFIG::LOGIN_ID)) ;
  this->currentPass       .referTo(getServer(CONFIG::PASS_ID)) ;
  this->currentIsAnonymous.referTo(getServer(CONFIG::ANON_ID)) ;
  this->currentIsAgreed   .referTo(getServer(CONFIG::AGREED_ID)) ;
  this->shouldHideBots    .referTo(getServer(CONFIG::BOTS_ID)) ;

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

  this->configValueTree.addListener(this) ;
}

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

ValueTree LinJamConfig::addServer(String host , String login , String pass ,
                                  bool is_anonymous)
{
  ValueTree server = getServer(host) ;
  if (!server.isValid())
  {
    Identifier host_id = Identifier(CONFIG::SERVER_ID.toString() + "-" +
                                    host.replaceCharacter('.' , '-')
                                        .replaceCharacter(':' , '-')) ;

    server = ValueTree(host_id) ;
    server.setProperty(CONFIG::HOST_ID  , host         , nullptr) ;
    server.setProperty(CONFIG::LOGIN_ID , login        , nullptr) ;
    server.setProperty(CONFIG::PASS_ID  , pass         , nullptr) ;
    server.setProperty(CONFIG::ANON_ID  , is_anonymous , nullptr) ;
    server.setProperty(CONFIG::AGREE_ID , false        , nullptr) ;

    this->servers        .addChild(server        , -1 , nullptr) ;
    this->configValueTree.addChild(this->servers , -1 , nullptr) ;
  }

  return server ;
}

String LinJamConfig::filteredName(String a_string)
{
  return a_string.retainCharacters(CONFIG::VALID_NAME_CHARS).replaceCharacter(' ', '-') ;
}

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

void LinJamConfig::valueTreeChildAdded(ValueTree& a_parent_node , ValueTree& a_child_node)
{
DEBUG_TRACE_CONFIG_TREE_ADDED

// TODO: remotes added to '<remote-channels>' node (issue #33)
//   a_child_node.addListener(this) ;
}

void LinJamConfig::valueTreeChildRemoved(ValueTree& a_parent_node , ValueTree& a_child_node)
{
DEBUG_TRACE_CONFIG_TREE_REMOVED

  if (a_parent_node == this->localChannels) LinJam::RemoveLocalChannel(a_child_node) ;
}

// unused ValueTree::Listener interface methods
void LinJamConfig::valueTreeChildOrderChanged(ValueTree& a_parent_node)                      {}
void LinJamConfig::valueTreeParentChanged(ValueTree& a_node)                                 {}
void LinJamConfig::valueTreeRedirected(ValueTree& a_node)                                    {}
