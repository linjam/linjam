/*
  ==============================================================================

    LinJamConfig.cpp
    Created: 12 Jun 2014 7:05:12am
    Author:  me

  ==============================================================================
*/

#include "LinJam.h"
#include "LinJamConfig.h"


/* LinJamConfig public class methods */

LinJamConfig::LinJamConfig()
{
  // load default and stored configs
  File this_binary    = File::getSpecialLocation(File::currentExecutableFile) ;
  this->configXmlFile = this_binary.getSiblingFile(CONFIG::PERSISTENCE_FILENAME) ;
  XmlElement* default_config_xml = XmlDocument::parse(CONFIG::DEFAULT_CONFIG_XML) ;
  XmlElement* stored_config_xml  = XmlDocument::parse(this->configXmlFile) ;

DEBUG_TRACE_LOAD_CONFIG
DEBUG_TRACE_SANITIZE_CONFIG

  // create static config ValueTree
  if (stored_config_xml == nullptr ||
     !stored_config_xml->hasTagName(CONFIG::PERSISTENCE_IDENTIFIER))
    this->configValueTree = ValueTree::fromXml(*default_config_xml) ;
  else
    this->configValueTree = sanitizeConfig(ValueTree::fromXml(*default_config_xml) ,
                                           ValueTree::fromXml(*stored_config_xml)) ;

  // set session dir and log file - these are too dangerous to be user-configuraable
  ValueTree client = this->configValueTree.getChildWithName(CONFIG::CLIENT_IDENTIFIER) ;
  client.setProperty(CONFIG::SESSIONDIR_IDENTIFIER , CONFIG::SESSIONDIR , nullptr) ;
  client.setProperty(CONFIG::LOGFILE_IDENTIFIER    , CONFIG::LOGFILE    , nullptr) ;

  storeConfig() ; delete default_config_xml ; delete stored_config_xml ;

  // instantiate shared value holders
  establishSharedStore() ;
}

LinJamConfig::~LinJamConfig() { storeConfig() ; }


/* LinJamConfig public instance methods */

bool LinJamConfig::sanityCheck()
{
  ValueTree master_channel  = this->masterChannels.getChildWithName(GUI::MASTER_CHANNEL_GUI_ID) ;
  ValueTree metro_channel   = this->masterChannels.getChildWithName(GUI::METRO_CHANNEL_GUI_ID) ;
  ValueTree default_channel = this->localChannels .getChild(0) ;

  // subscribed trees
  bool auto_subscribe_users_is_valid       =
    autoSubscribeUsers        .isValid()                                 ;
  bool master_channels_is_valid            =
    masterChannels            .isValid()                                 ;
  bool local_channels_is_valid             =
    localChannels             .isValid()                                 ;
  bool servers_is_valid                    =
    servers                   .isValid()                                 ;

  // implicitly subscribed values (via above trees)
  bool master_channel_has_volume_property  =
    master_channel            .hasProperty(CONFIG::VOLUME_IDENTIFIER)   ;
  bool master_channel_has_pan_property     =
    master_channel            .hasProperty(CONFIG::PAN_IDENTIFIER)      ;
  bool master_channel_has_mute_property    =
    master_channel            .hasProperty(CONFIG::MUTE_IDENTIFIER)     ;
  bool metro_channel_has_volume_property   =
    metro_channel             .hasProperty(CONFIG::VOLUME_IDENTIFIER)   ;
  bool metro_channel_has_pan_property      =
    metro_channel             .hasProperty(CONFIG::PAN_IDENTIFIER)      ;
  bool metro_channel_has_mute_property     =
    metro_channel             .hasProperty(CONFIG::MUTE_IDENTIFIER)     ;
  bool metro_channel_has_source_property   =
    metro_channel             .hasProperty(CONFIG::SOURCE_N_IDENTIFIER) ;
  bool metro_channel_has_stereo_property   =
    metro_channel             .hasProperty(CONFIG::STEREO_IDENTIFIER)   ;
  bool default_channel_has_volume_property =
    default_channel           .hasProperty(CONFIG::VOLUME_IDENTIFIER)   ;
  bool default_channel_has_pan_property    =
    default_channel           .hasProperty(CONFIG::PAN_IDENTIFIER)      ;
  bool default_channel_has_xmit_property   =
    default_channel           .hasProperty(CONFIG::XMIT_IDENTIFIER)     ;
  bool default_channel_has_mute_property   =
    default_channel           .hasProperty(CONFIG::MUTE_IDENTIFIER)     ;
  bool default_channel_has_solo_property   =
    default_channel           .hasProperty(CONFIG::SOLO_IDENTIFIER)     ;
  bool default_channel_has_source_property =
    default_channel           .hasProperty(CONFIG::SOURCE_N_IDENTIFIER) ;
  bool default_channel_has_stereo_property =
    default_channel           .hasProperty(CONFIG::STEREO_IDENTIFIER)   ;

  // explicitly subscribed values
  bool should_save_audio_has_value         =
    !this->shouldSaveAudio    .refersToSameSourceAs(this->dummyValue)    ;
  bool should_save_log_has_value           =
    !this->shouldSaveLog      .refersToSameSourceAs(this->dummyValue)    ;
  bool debug_level_has_value               =
    !this->debugLevel         .refersToSameSourceAs(this->dummyValue)    ;
  bool should_auto_subscribe_has_value     =
    !this->shouldAutoSubscribe.refersToSameSourceAs(this->dummyValue)    ;
  bool audio_if_n_has_value                =
    !this->audioIfN           .refersToSameSourceAs(this->dummyValue)    ;
  bool n_inputs_has_value                  =
    !this->nInputs            .refersToSameSourceAs(this->dummyValue)    ;
  bool n_outputs_has_value                 =
    !this->nOutputs           .refersToSameSourceAs(this->dummyValue)    ;
  bool bit_depth_has_value                 =
    !this->bitDepth           .refersToSameSourceAs(this->dummyValue)    ;
  bool sample_rate_has_value               =
    !this->sampleRate         .refersToSameSourceAs(this->dummyValue)    ;
  bool jack_name_has_value                 =
    !this->jackName           .refersToSameSourceAs(this->dummyValue)    ;
  bool current_host_has_value              =
    !this->currentHost        .refersToSameSourceAs(this->dummyValue)    ;
  bool current_login_has_value             =
    !this->currentLogin       .refersToSameSourceAs(this->dummyValue)    ;
  bool current_pass_has_value              =
    !this->currentPass        .refersToSameSourceAs(this->dummyValue)    ;
  bool current_is_anonymous_has_value      =
    !this->currentIsAnonymous .refersToSameSourceAs(this->dummyValue)    ;
  bool current_is_agreed_has_value         =
    !this->currentIsAgreed    .refersToSameSourceAs(this->dummyValue)    ;
  bool should_hide_bots_has_value          =
    !this->shouldHideBots     .refersToSameSourceAs(this->dummyValue)    ;

DEBUG_TRACE_SANITY_CHECK

  return (auto_subscribe_users_is_valid       &&
          master_channels_is_valid            &&
          local_channels_is_valid             &&
          servers_is_valid                    &&
          master_channel_has_volume_property  &&
          master_channel_has_pan_property     &&
          master_channel_has_mute_property    &&
          metro_channel_has_volume_property   &&
          metro_channel_has_pan_property      &&
          metro_channel_has_mute_property     &&
          metro_channel_has_source_property   &&
          metro_channel_has_stereo_property   &&
          default_channel_has_volume_property &&
          default_channel_has_pan_property    &&
          default_channel_has_xmit_property   &&
          default_channel_has_mute_property   &&
          default_channel_has_solo_property   &&
          default_channel_has_source_property &&
          default_channel_has_stereo_property &&
          should_save_audio_has_value         &&
          should_save_log_has_value           &&
          debug_level_has_value               &&
          should_auto_subscribe_has_value     &&
          audio_if_n_has_value                &&
          n_inputs_has_value                  &&
          n_outputs_has_value                 &&
          bit_depth_has_value                 &&
          sample_rate_has_value               &&
          jack_name_has_value                 &&
          current_host_has_value              &&
          current_login_has_value             &&
          current_pass_has_value              &&
          current_is_anonymous_has_value      &&
          current_is_agreed_has_value         &&
          should_hide_bots_has_value           ) ;
}

String LinJamConfig::parseUsername(String user_name)
{ return user_name.upToFirstOccurrenceOf(CONFIG::AT_CHAR , false , true) ; }

Identifier LinJamConfig::encodeChannelId(String channel_name , int channel_idx)
{
  return ((channel_name.isNotEmpty())?
             filteredName(channel_name) :
             CONFIG::DEFAULT_CHANNEL_NAME + String(channel_idx)) ;
}

String LinJamConfig::decodeChannelId(Identifier channel_id) { return String(channel_id) ; }

Identifier LinJamConfig::encodeUserId(String user_name , int user_idx)
{
  return ((user_name.isNotEmpty())?
             filteredName(parseUsername(user_name)) :
             CONFIG::DEFAULT_USER_NAME + String(user_idx)) ;
}

String LinJamConfig::decodeUserId(Identifier user_id) { return String(user_id) ; }

bool LinJamConfig::doesChannelExist(Identifier channels_id , String channel_name)
{
  Identifier channel_id = encodeChannelId(channel_name , 0) ;
  return (getChannel(channels_id , channel_id).isValid()) ;
}

ValueTree LinJamConfig::getOrCreateUser(String user_name , int   user_idx ,
                                        float  volume    , float pan      , bool is_muted)
{
  Identifier user_id    = encodeUserId(user_name , user_idx) ;
  ValueTree  user_store = getUser(user_id) ;
  if (!user_store.isValid())
  {
DEBUG_TRACE_ADD_REMOTE_USER

    // create new remote user config
    ValueTree channel_store = ValueTree(CONFIG::MASTER_IDENTIFIER) ;
    channel_store.setProperty(CONFIG::VOLUME_IDENTIFIER , volume   , nullptr) ;
    channel_store.setProperty(CONFIG::PAN_IDENTIFIER    , pan      , nullptr) ;
    channel_store.setProperty(CONFIG::MUTE_IDENTIFIER   , is_muted , nullptr) ;

/*
    channel_store.setProperty(CONFIG::XMIT_IDENTIFIER , CONFIG::DEFAULT_IS_XMIT  , nullptr) ;
    channel_store.setProperty(CONFIG::SOLO_IDENTIFIER , CONFIG::DEFAULT_IS_SOLO  , nullptr) ;
    channel_store.setProperty(CONFIG::SOURCE_N_IDENTIFIER , CONFIG::DEFAULT_SOURCE_N   , nullptr) ;
    channel_store.setProperty(CONFIG::STEREO_IDENTIFIER , CONFIG::DEFAULT_IS_STEREO   , nullptr) ;
*/


    user_store = ValueTree(user_id) ;
    this->configValueTree.addChild(user_store , -1 , nullptr) ;
    user_store.addChild(channel_store , -1 , nullptr) ;
  }
  user_store.setProperty(CONFIG::USERIDX_IDENTIFIER , user_idx , nullptr) ;

  return user_store ;
}

ValueTree LinJamConfig::createChannel(Identifier channels_id   , String channel_name ,
                                      int        channel_idx   , float  volume       ,
                                      float      pan           , bool   is_xmit_rcv  ,
                                      bool       is_muted      , bool   is_solo      ,
                                      int        source_sink_n , bool   is_stereo    )
{
  Identifier channel_id   = encodeChannelId(channel_name , channel_idx + 1) ;
  ValueTree channel_store = getChannel(channels_id , channel_id) ;
  if (!channel_store.isValid())
  {
    // add new channel
    channel_store = ValueTree(channel_id) ;
    channel_store.setProperty(CONFIG::VOLUME_IDENTIFIER   , volume        , nullptr) ;
    channel_store.setProperty(CONFIG::PAN_IDENTIFIER      , pan           , nullptr) ;
    channel_store.setProperty(CONFIG::XMIT_IDENTIFIER     , is_xmit_rcv   , nullptr) ;
    channel_store.setProperty(CONFIG::MUTE_IDENTIFIER     , is_muted      , nullptr) ;
    channel_store.setProperty(CONFIG::SOLO_IDENTIFIER     , is_solo       , nullptr) ;
    channel_store.setProperty(CONFIG::SOURCE_N_IDENTIFIER , source_sink_n , nullptr) ;
    channel_store.setProperty(CONFIG::STEREO_IDENTIFIER   , is_stereo     , nullptr) ;
    if (channels_id == GUI::LOCALS_IDENTIFIER)
      this->localChannels.addChild(channel_store , -1 , nullptr) ;
    else
    {
      // assume this is a remote channel // TODO: (issue #33)
      ValueTree user_store = getUser(channels_id) ;
      if (!user_store.isValid()) channel_store = ValueTree::invalid ;
      else user_store.addChild(channel_store , -1 , nullptr) ;
    }
  }

  return channel_store ;
}

ValueTree LinJamConfig::getChannel(Identifier channels_id , Identifier channel_id)
{
  if      (channels_id == GUI::MASTERS_IDENTIFIER)
    return this->masterChannels.getChildWithName(channel_id) ;
  else if (channels_id == GUI::LOCALS_IDENTIFIER)
    return this->localChannels .getChildWithName(channel_id) ;

  // assume this is a remote channel // TODO: (issue #33)
  ValueTree user_store = getUser(channels_id) ;
  return (user_store.isValid())?
             user_store.getChildWithName(channel_id) :
             ValueTree::invalid ;
}

void LinJamConfig::setServer()
{
  // copy volatile login state to persistent storage
  String host         =      this->currentHost.toString() ;
  String login        =      this->currentLogin.toString() ;
  String pass         =      this->currentPass.toString() ;
  bool   is_anonymous = bool(this->currentIsAnonymous.getValue()) ;

  ValueTree server = addServer(host , login , pass , is_anonymous) ;
  server.setProperty(CONFIG::HOST_IDENTIFIER  , host         , nullptr) ;
  server.setProperty(CONFIG::LOGIN_IDENTIFIER , login        , nullptr) ;
  server.setProperty(CONFIG::PASS_IDENTIFIER  , pass         , nullptr) ;
  server.setProperty(CONFIG::ANON_IDENTIFIER  , is_anonymous , nullptr) ;
}

void LinJamConfig::setCurrentServer(String host , String login , String pass ,
                                    bool   is_anonymous)
{
  this->currentHost        = host ;
  this->currentLogin       = login ;
  this->currentPass        = (is_anonymous)? "" : pass ;
  this->currentIsAnonymous = is_anonymous ;
  this->currentIsAgreed    = false ;
}

ValueTree LinJamConfig::getCurrentServer()
{ return getServer(this->currentHost.toString()) ; }

ValueTree LinJamConfig::getServer(String host)
{ return this->servers.getChildWithProperty(CONFIG::HOST_IDENTIFIER , var(host)) ; }

void LinJamConfig::setShouldAgree(bool should_agree)
{
  // continuation of setServer() after license agreement
  ValueTree server = getCurrentServer() ;
  if (!server.isValid()) return ;

  server.setProperty(CONFIG::AGREE_IDENTIFIER , should_agree , nullptr) ;
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
      if (default_config.getType() != CONFIG::LOCALS_IDENTIFIER ||
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

void LinJamConfig::storeConfig()
{
DEBUG_TRACE_STORE_CONFIG

  XmlElement* config_xml = this->configValueTree.createXml() ;
  XmlElement* client     = config_xml->getChildByName(CONFIG::CLIENT_IDENTIFIER) ;

  // unset session dir and log file - these are too dangerous to be user-configuraable
  client->removeAttribute(CONFIG::SESSIONDIR_KEY) ;
  client->removeAttribute(CONFIG::LOGFILE_KEY) ;

  config_xml->writeToFile(this->configXmlFile , StringRef() , StringRef("UTF-8") , 0) ;
  delete config_xml ;
}

void LinJamConfig::establishSharedStore()
{
  // client config
  this->shouldSaveAudio    .referTo(getClient(CONFIG::SAVE_AUDIO_IDENTIFIER)) ;
  this->shouldSaveLog      .referTo(getClient(CONFIG::SAVE_LOG_IDENTIFIER)) ;
  this->debugLevel         .referTo(getClient(CONFIG::DEBUGLEVEL_IDENTIFIER)) ;
  this->shouldAutoSubscribe.referTo(getClient(CONFIG::AUTOSUBSCRIBE_IDENTIFIER)) ;
  this->autoSubscribeUsers = getNode(CONFIG::SUBSCRIPTIONS_IDENTIFIER) ;

  // device config
  this->audioIfN       .referTo(getAudio(CONFIG::AUDIO_IF_IDENTIFIER)) ;
  this->nInputs        .referTo(getAudio(CONFIG::N_INPUTS_IDENTIFIER)) ;
  this->nOutputs       .referTo(getAudio(CONFIG::N_OUTPUTS_IDENTIFIER)) ;
  this->bitDepth       .referTo(getAudio(CONFIG::BITDEPTH_IDENTIFIER)) ;
  this->sampleRate     .referTo(getAudio(CONFIG::SAMPLERATE_IDENTIFIER)) ;
  this->jackName       .referTo(getAudio(CONFIG::JACK_NAME_IDENTIFIER)) ;

  // login state
  this->currentHost       .referTo(getServer(CONFIG::HOST_IDENTIFIER)) ;
  this->currentLogin      .referTo(getServer(CONFIG::LOGIN_IDENTIFIER)) ;
  this->currentPass       .referTo(getServer(CONFIG::PASS_IDENTIFIER)) ;
  this->currentIsAnonymous.referTo(getServer(CONFIG::ANON_IDENTIFIER)) ;
  this->currentIsAgreed   .referTo(getServer(CONFIG::AGREED_IDENTIFIER)) ;
  this->shouldHideBots    .referTo(getServer(CONFIG::BOTS_IDENTIFIER)) ;

  // channels
  this->masterChannels = getNode(CONFIG::MASTERS_IDENTIFIER) ;
  this->localChannels  = getNode(CONFIG::LOCALS_IDENTIFIER) ;
//   this->remoteChannels = getNode(CONFIG::REMOTES_IDENTIFIER) ; // (issue #33)
this->remoteChannels = this->configValueTree ; // kludge (issue #33)

  // per server user data
  this->servers        = getNode(CONFIG::SERVERS_IDENTIFIER) ;

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
              value_node.getPropertyAsValue(key , nullptr) :
              this->dummyValue ;
}

Value LinJamConfig::getClient(Identifier key)
{ return getLeaf(this->configValueTree , CONFIG::CLIENT_IDENTIFIER , key) ; }

Value LinJamConfig::getAudio(Identifier key)
{ return getLeaf(this->configValueTree , CONFIG::AUDIO_IDENTIFIER  , key) ; }

Value LinJamConfig::getServer(Identifier key)
{ return getLeaf(this->configValueTree , CONFIG::SERVER_IDENTIFIER , key) ; }

ValueTree LinJamConfig::addServer(String host , String login , String pass ,
                                  bool is_anonymous)
{
  ValueTree server = getServer(host) ;
  if (!server.isValid())
  {
    Identifier host_id = Identifier(CONFIG::SERVER_IDENTIFIER.toString() + "-" +
                         host.replaceCharacter('.' , '-')
                             .replaceCharacter(':' , '-')) ;

    server = ValueTree(host_id) ;
    server.setProperty(CONFIG::HOST_IDENTIFIER  , host         , nullptr) ;
    server.setProperty(CONFIG::LOGIN_IDENTIFIER , login        , nullptr) ;
    server.setProperty(CONFIG::PASS_IDENTIFIER  , pass         , nullptr) ;
    server.setProperty(CONFIG::ANON_IDENTIFIER  , is_anonymous , nullptr) ;
    server.setProperty(CONFIG::AGREE_IDENTIFIER , false        , nullptr) ;

    this->servers        .addChild(server        , -1 , nullptr) ;
    this->configValueTree.addChild(this->servers , -1 , nullptr) ;
  }

  return server ;
}

ValueTree LinJamConfig::getUser(Identifier user_id)
{ return this->configValueTree.getChildWithName(user_id) ; }

String LinJamConfig::filteredName(String a_string)
{ return a_string.retainCharacters(CONFIG::VALID_NAME_CHARS).replaceCharacter(' ', '-') ; }

void LinJamConfig::valueTreePropertyChanged(ValueTree& a_node , const Identifier& a_key)
{
DEBUG_TRACE_CONFIG_TREE_CHANGED

  Identifier node_id     = a_node.getType() ;
  ValueTree  parent_node = a_node.getParent() ;
  Identifier parent_id   = parent_node.getType() ;

  if      (node_id == CONFIG::MASTER_IDENTIFIER)
    LinJam::ConfigureMasterChannel(a_key) ;
  else if (node_id == CONFIG::METRO_IDENTIFIER)
    LinJam::ConfigureMetroChannel(a_key) ;
  else if (parent_node == this->localChannels)
    LinJam::ConfigureLocalChannel(a_node , a_key) ;

  else if (node_id   == CONFIG::CLIENT_IDENTIFIER)        return ; // most likely will handle this eventuall
  else if (parent_id == CONFIG::SUBSCRIPTIONS_IDENTIFIER) return ; // most likely will handle this eventuall
  else if (node_id   == CONFIG::AUDIO_IDENTIFIER)         return ; // may or may not handle this (issue #12)
  else if (node_id   == CONFIG::SERVER_IDENTIFIER)        return ; // most likely wont need to handle these
  else if (parent_id == CONFIG::SERVERS_IDENTIFIER)       return ; // but we must guard for now (issue #33)

//  else if (node_id == CONFIG::REMOTES_IDENTIFIER) (issue #33)
  else if (parent_node == this->remoteChannels)
    LinJam::ConfigureRemoteUser(a_node , a_key) ;
  else if (parent_node.getParent() == this->remoteChannels)
    LinJam::ConfigureRemoteChannel(parent_node , a_node , a_key) ;
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

  if (a_parent_node == this->localChannels)
    LinJam::RemoveLocalChannel(a_child_node.getType()) ;
}

// unused ValueTree::Listener interface methods
void LinJamConfig::valueTreeChildOrderChanged(ValueTree& a_parent_node)                      {}
void LinJamConfig::valueTreeParentChanged(ValueTree& a_node)                                 {}
void LinJamConfig::valueTreeRedirected(ValueTree& a_node)                                    {}



// DEBUG
void LinJamConfig::DBGConfigValueType(String dbg_val_name , var a_var)
{
  String dynamic_type ;
  if      (a_var.isVoid())       dynamic_type = "Void" ;
  else if (a_var.isUndefined())  dynamic_type = "Undefined" ;
  else if (a_var.isInt())        dynamic_type = "Int" ;
  else if (a_var.isInt64())      dynamic_type = "Int64" ;
  else if (a_var.isBool())       dynamic_type = "Bool" ;
  else if (a_var.isDouble())     dynamic_type = "Double" ;
  else if (a_var.isString())     dynamic_type = "String" ;
  else if (a_var.isObject())     dynamic_type = "Object" ;
  else if (a_var.isArray())      dynamic_type = "Array" ;
  else if (a_var.isBinaryData()) dynamic_type = "Binary" ;
  else if (a_var.isMethod())     dynamic_type = "Method" ;
  DBG(dbg_val_name + " type is " + dynamic_type) ;
}
