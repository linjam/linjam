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
             filteredName(user_name.upToFirstOccurrenceOf(CONFIG::AT_CHAR , false , true)) :
             CONFIG::DEFAULT_USER_NAME + String(user_idx)) ;
}

String LinJamConfig::decodeUserId(Identifier user_id) { return String(user_id) ; }

ValueTree LinJamConfig::getChannelConfig(Identifier mixergroup_id , Identifier channel_id)
{
  if      (mixergroup_id == GUI::MASTER_MIXERGROUP_IDENTIFIER)
    return this->masterChannels.getChildWithName(channel_id) ;
  else if (mixergroup_id == GUI::LOCAL_MIXERGROUP_IDENTIFIER)
    return this->localChannels .getChildWithName(channel_id) ;

  // assume this is a remote channel
  ValueTree user_config = this->configValueTree.getChildWithName(mixergroup_id) ;

  return (user_config.isValid())?
             user_config.getChildWithName(channel_id) :
             ValueTree::invalid ;
}

void LinJamConfig::setServerConfig()
{
  // copy volatile login state to persistent storage
  String host         =      this->currentHost.toString() ;
  String login        =      this->currentLogin.toString() ;
  String pass         =      this->currentPass.toString() ;
  bool   is_anonymous = bool(this->currentIsAnonymous.getValue()) ;

  ValueTree server = addServerConfig(host , login , pass , is_anonymous) ;
  server.setProperty(CONFIG::HOST_IDENTIFIER  , host         , nullptr) ;
  server.setProperty(CONFIG::LOGIN_IDENTIFIER , login        , nullptr) ;
  server.setProperty(CONFIG::PASS_IDENTIFIER  , pass         , nullptr) ;
  server.setProperty(CONFIG::ANON_IDENTIFIER  , is_anonymous , nullptr) ;
}

ValueTree LinJamConfig::getCurrentServerConfig()
{ return getServerConfig(this->currentHost.toString()) ; }

ValueTree LinJamConfig::getServerConfig(String host)
{ return this->servers.getChildWithProperty(CONFIG::HOST_IDENTIFIER , var(host)) ; }

void LinJamConfig::setShouldAgree(bool should_agree)
{
  // continuation of setServerConfig() after license agreement
  ValueTree server = getCurrentServerConfig() ;
  if (!server.isValid()) return ;

  server.setProperty(CONFIG::AGREE_IDENTIFIER , should_agree , nullptr) ;
}

ValueTree LinJamConfig::getOrCreateRemoteUserConfig(Identifier user_name)
{ return this->configValueTree.getOrCreateChildWithName(user_name , nullptr) ; }


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
      default_config.removeChild(default_child , nullptr) ;
      stored_config.addChild(default_child , -1 , nullptr) ;
      --child_n ; continue ;
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
  this->shouldSaveAudio    .referTo(getClientConfigValueObj(CONFIG::SAVE_AUDIO_IDENTIFIER)) ;
  this->shouldSaveLog      .referTo(getClientConfigValueObj(CONFIG::SAVE_LOG_IDENTIFIER)) ;
  this->debugLevel         .referTo(getClientConfigValueObj(CONFIG::DEBUGLEVEL_IDENTIFIER)) ;
  this->shouldAutoSubscribe.referTo(getClientConfigValueObj(CONFIG::AUTOSUBSCRIBE_IDENTIFIER)) ;
  this->autoSubscribeUsers = getConfigTreeObj(CONFIG::SUBSCRIPTIONS_IDENTIFIER) ;

  // device config
  this->audioIfN       .referTo(getAudioConfigValueObj(CONFIG::AUDIO_IF_IDENTIFIER)) ;
  this->nInputs        .referTo(getAudioConfigValueObj(CONFIG::N_INPUTS_IDENTIFIER)) ;
  this->nOutputs       .referTo(getAudioConfigValueObj(CONFIG::N_OUTPUTS_IDENTIFIER)) ;
  this->bitDepth       .referTo(getAudioConfigValueObj(CONFIG::BITDEPTH_IDENTIFIER)) ;
  this->sampleRate     .referTo(getAudioConfigValueObj(CONFIG::SAMPLERATE_IDENTIFIER)) ;
  this->jackName       .referTo(getAudioConfigValueObj(CONFIG::JACK_NAME_IDENTIFIER)) ;

  // login state
  this->currentHost       .referTo(getServerConfigValueObj(CONFIG::HOST_IDENTIFIER)) ;
  this->currentLogin      .referTo(getServerConfigValueObj(CONFIG::LOGIN_IDENTIFIER)) ;
  this->currentPass       .referTo(getServerConfigValueObj(CONFIG::PASS_IDENTIFIER)) ;
  this->currentIsAnonymous.referTo(getServerConfigValueObj(CONFIG::ANON_IDENTIFIER)) ;
  this->currentIsAgreed   .referTo(getServerConfigValueObj(CONFIG::AGREED_IDENTIFIER)) ;
  this->shouldHideBots    .referTo(getServerConfigValueObj(CONFIG::BOTS_IDENTIFIER)) ;

  // channels
  this->masterChannels = getConfigTreeObj(CONFIG::MASTERS_IDENTIFIER) ;
  this->localChannels  = getConfigTreeObj(CONFIG::LOCALS_IDENTIFIER) ;
//   this->remoteChannels = getConfigTreeObj(CONFIG::REMOTES_IDENTIFIER) ; // (issue #33)
this->remoteChannels = this->configValueTree ; // kludge (issue #33)

  // per server user data
  this->servers        = getConfigTreeObj(CONFIG::SERVERS_IDENTIFIER) ;

  this->configValueTree.addListener(this) ;
}

ValueTree LinJamConfig::getConfigTreeObj(Identifier tree_node_id)
{
  ValueTree tree_node = this->configValueTree.getChildWithName(tree_node_id) ;

DEBUG_TRACE_CONFIG_TREE

  return tree_node ;
}

Value LinJamConfig::getConfigValueObj(ValueTree parent_node , Identifier child_node_id ,
                                      Identifier key)
{
  ValueTree value_node = parent_node.getChildWithName(child_node_id) ;

DEBUG_TRACE_CONFIG_VALUE

  return (value_node.isValid() && value_node.hasProperty(key))?
              value_node.getPropertyAsValue(key , nullptr) :
              this->dummyValue ;
}

Value LinJamConfig::getClientConfigValueObj(Identifier key)
{ return getConfigValueObj(this->configValueTree , CONFIG::CLIENT_IDENTIFIER , key) ; }

Value LinJamConfig::getAudioConfigValueObj(Identifier key)
{ return getConfigValueObj(this->configValueTree , CONFIG::AUDIO_IDENTIFIER  , key) ; }

Value LinJamConfig::getServerConfigValueObj(Identifier key)
{ return getConfigValueObj(this->configValueTree , CONFIG::SERVER_IDENTIFIER , key) ; }

ValueTree LinJamConfig::addServerConfig(String host , String login , String pass ,
                                        bool is_anonymous)
{
  ValueTree server = getServerConfig(host) ;
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

String LinJamConfig::filteredName(String a_string)
{ return a_string.retainCharacters(CONFIG::VALID_NAME_CHARS).replaceCharacter(' ', '-') ; }

void LinJamConfig::valueChanged(Value& a_value)
{
/*
DEBUG_TRACE_CONFIG_VALUE_CHANGED

  bool   a_bool   = bool( a_value.getValue()) ;
  int    an_int   = int(  a_value.getValue()) ;
  float  a_float  = float(a_value.getValue()) ;
  String a_string =       a_value.toString() ;

  if      (a_value.refersToSameSourceAs(this->masterVolume))
    LinJam::Client->config_mastervolume = a_float ;
  else if (etc) ;
*/
}

void LinJamConfig::valueTreePropertyChanged(ValueTree& a_node , const Identifier& key)
{
DEBUG_TRACE_CONFIG_TREE_CHANGED

  Identifier node_id  =        a_node.getType() ;
  bool       a_bool   = bool(  a_node[key]) ;
  int        an_int   = int(   a_node[key]) ;
  float      a_float  = float( a_node[key]) ;
  double     a_double = double(a_node[key]) ;
  String     a_string =        a_node[key].toString() ;

  // master channels
  if (node_id == CONFIG::MASTER_IDENTIFIER)
  {
    if      (key == CONFIG::VOLUME_IDENTIFIER)
      LinJam::Client->config_mastervolume = (float)DB2VAL(a_double) ;
    else if (key == CONFIG::PAN_IDENTIFIER)
      LinJam::Client->config_masterpan    = a_float ;
    else if (key == CONFIG::MUTE_IDENTIFIER)
      LinJam::Client->config_mastermute   = a_bool ;

    return ;
  }
  if (node_id == CONFIG::METRO_IDENTIFIER)
  {
    if      (key == CONFIG::VOLUME_IDENTIFIER)
      LinJam::Client->config_metronome           = (float)DB2VAL(a_double) ;
    else if (key == CONFIG::PAN_IDENTIFIER)
      LinJam::Client->config_metronome_pan       = a_float ;
    else if (key == CONFIG::MUTE_IDENTIFIER)
      LinJam::Client->config_metronome_mute      = a_bool ;
    else if (key == CONFIG::SOURCE_N_IDENTIFIER)
      LinJam::Client->config_metronome_channel   = an_int ;
    else if (key == CONFIG::STEREO_IDENTIFIER)
      LinJam::Client->config_metronome_stereoout = a_bool ;

    return ;
  }

  if (node_id == CONFIG::CLIENT_IDENTIFIER)        return ; // most likely will handle this eventuall
  if (node_id == CONFIG::SUBSCRIPTIONS_IDENTIFIER) return ; // most likely will handle this eventuall
  if (node_id == CONFIG::AUDIO_IDENTIFIER  ||               // most likely wont need to handle these
      node_id == CONFIG::SERVER_IDENTIFIER ||               // but we must guard for now (issue #33)
      node_id == CONFIG::SERVERS_IDENTIFIER)       return ;

  // local and remote channels
  // TODO: channel name changes (issue #12)
  ValueTree parent_node          = a_node.getParent() ; int channel_idx ;
  bool      should_set_volume    = (key == CONFIG::VOLUME_IDENTIFIER) ;
  bool      should_set_pan       = (key == CONFIG::PAN_IDENTIFIER) ;
  bool      should_set_is_xmit   = (key == CONFIG::XMIT_IDENTIFIER) ;
  bool      should_set_is_muted  = (key == CONFIG::MUTE_IDENTIFIER) ;
  bool      should_set_is_solo   = (key == CONFIG::SOLO_IDENTIFIER) ;
  bool      should_set_source_n  = (key == CONFIG::SOURCE_N_IDENTIFIER) ;
  bool      should_set_bit_depth = (key == CONFIG::SAMPLERATE_IDENTIFIER) ;
  bool      should_set_is_stereo = (key == CONFIG::STEREO_IDENTIFIER) ;

  // configure local channel
  if (parent_node == this->localChannels)
  {
    if (~(channel_idx = LinJam::GetLocalChannelIdx(node_id)))
      LinJam::ConfigureLocalChannel(channel_idx          , String::empty ,
                                    should_set_volume    , a_float       ,
                                    should_set_pan       , a_float       ,
                                    should_set_is_xmit   , a_bool        ,
                                    should_set_is_muted  , a_bool        ,
                                    should_set_is_solo   , a_bool        ,
                                    should_set_source_n  , an_int        ,
                                    should_set_bit_depth , an_int        ,
                                    should_set_is_stereo , a_bool        ) ;
    return ;
  }

  // configure remote channels
  Identifier parent_node_id = parent_node.getType() ; int user_idx ;
  if (parent_node == this->remoteChannels) // TODO: nyi GUI for these
  {
    if (~(user_idx = LinJam::GetRemoteUserIdx(parent_node_id)))
      LinJam::ConfigureRemoteUser(user_idx                      ,
                                  should_set_volume   , a_float ,
                                  should_set_pan      , a_float ,
                                  should_set_is_muted , a_bool  ) ;
    return ;
  }

  if (parent_node.getParent() == this->remoteChannels  &&
    ~(user_idx    = LinJam::GetRemoteUserIdx(parent_node_id)) &&
    ~(channel_idx = LinJam::GetRemoteChannelIdx(user_idx , node_id)))
    LinJam::ConfigureRemoteChannel(user_idx                             ,
                                   channel_idx          , String::empty ,
                                   should_set_volume    , a_float       ,
                                   should_set_pan       , a_float       ,
                                   should_set_is_xmit   , a_bool        , // aka is_rcv
                                   should_set_is_muted  , a_bool        ,
                                   should_set_is_solo   , a_bool        ,
                                   should_set_source_n  , an_int        , // aka sink_n
                                   should_set_is_stereo , a_bool        ) ;
}

void LinJamConfig::valueTreeChildAdded(ValueTree& a_parent_tree , ValueTree& a_child_tree)
{
DBG("valueTreeChildAdded() a_parent_tree=" + a_parent_tree.getType().toString() +
  " a_child_tree="  + a_child_tree.getType().toString()) ;

//   a_child_tree.addListener(this) ;
}

// unused ValueTree::Listener interface methods
void LinJamConfig::valueTreeChildRemoved(ValueTree& a_parent_tree , ValueTree& a_child_tree) {}
void LinJamConfig::valueTreeChildOrderChanged(ValueTree& a_parent_tree)                      {}
void LinJamConfig::valueTreeParentChanged(ValueTree& a_tree)                                 {}
void LinJamConfig::valueTreeRedirected(ValueTree& a_tree)                                    {}



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
