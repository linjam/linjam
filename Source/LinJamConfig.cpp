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
  this->configXmlFile = this_binary.getSiblingFile(STORAGE::PERSISTENCE_FILENAME) ;
  XmlElement* default_config_xml = XmlDocument::parse(STORAGE::DEFAULT_CONFIG_XML) ;
  XmlElement* stored_config_xml  = XmlDocument::parse(this->configXmlFile) ;

DEBUG_TRACE_LOAD_CONFIG
DEBUG_TRACE_SANITIZE_CONFIG

  // create static config ValueTree
  if (stored_config_xml == nullptr ||
     !stored_config_xml->hasTagName(STORAGE::PERSISTENCE_IDENTIFIER))
    this->configValueTree = ValueTree::fromXml(*default_config_xml) ;
  else
    this->configValueTree = sanitizeConfig(ValueTree::fromXml(*default_config_xml) ,
                                           ValueTree::fromXml(*stored_config_xml)) ;

  // set session dir and log file - these are too dangerous to be user-configuraable
  ValueTree client = this->configValueTree.getChildWithName(STORAGE::CLIENT_IDENTIFIER) ;
  client.setProperty(STORAGE::SESSIONDIR_IDENTIFIER , STORAGE::SESSIONDIR , nullptr) ;
  client.setProperty(STORAGE::LOGFILE_IDENTIFIER    , STORAGE::LOGFILE    , nullptr) ;

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

  return ( autoSubscribeUsers       .isValid()                                 &&
           masterChannels           .isValid()                                 &&
           localChannels            .isValid()                                 &&
           remoteChannels           .isValid()                                 &&
           servers                  .isValid()                                 &&
          !this->shouldSaveAudio    .refersToSameSourceAs(this->dummyValue)    &&
          !this->shouldSaveLog      .refersToSameSourceAs(this->dummyValue)    &&
          !this->debugLevel         .refersToSameSourceAs(this->dummyValue)    &&
          !this->shouldAutoSubscribe.refersToSameSourceAs(this->dummyValue)    &&
          !this->audioIfN           .refersToSameSourceAs(this->dummyValue)    &&
          !this->nInputs            .refersToSameSourceAs(this->dummyValue)    &&
          !this->nOutputs           .refersToSameSourceAs(this->dummyValue)    &&
          !this->bitDepth           .refersToSameSourceAs(this->dummyValue)    &&
          !this->sampleRate         .refersToSameSourceAs(this->dummyValue)    &&
          !this->jackName           .refersToSameSourceAs(this->dummyValue)    &&
          !this->currentHost        .refersToSameSourceAs(this->dummyValue)    &&
          !this->currentLogin       .refersToSameSourceAs(this->dummyValue)    &&
          !this->currentPass        .refersToSameSourceAs(this->dummyValue)    &&
          !this->currentIsAnonymous .refersToSameSourceAs(this->dummyValue)    &&
          !this->currentIsAgreed    .refersToSameSourceAs(this->dummyValue)    &&
           master_channel           .hasProperty(STORAGE::VOLUME_IDENTIFIER)   &&
           master_channel           .hasProperty(STORAGE::PAN_IDENTIFIER)      &&
           master_channel           .hasProperty(STORAGE::MUTE_IDENTIFIER)     &&
           metro_channel            .hasProperty(STORAGE::VOLUME_IDENTIFIER)   &&
           metro_channel            .hasProperty(STORAGE::PAN_IDENTIFIER)      &&
           metro_channel            .hasProperty(STORAGE::MUTE_IDENTIFIER)     &&
           metro_channel            .hasProperty(STORAGE::SOURCE_N_IDENTIFIER) &&
           metro_channel            .hasProperty(STORAGE::STEREO_IDENTIFIER)   &&
           default_channel          .hasProperty(STORAGE::VOLUME_IDENTIFIER)   &&
           default_channel          .hasProperty(STORAGE::PAN_IDENTIFIER)      &&
           default_channel          .hasProperty(STORAGE::XMIT_IDENTIFIER)     &&
           default_channel          .hasProperty(STORAGE::MUTE_IDENTIFIER)     &&
           default_channel          .hasProperty(STORAGE::SOLO_IDENTIFIER)     &&
           default_channel          .hasProperty(STORAGE::SOURCE_N_IDENTIFIER) &&
           default_channel          .hasProperty(STORAGE::STEREO_IDENTIFIER)    ) ;
}

void LinJamConfig::setServerConfig()
{
  // copy volatile login state to persistent storage
  String host         =      this->currentHost.toString() ;
  String login        =      this->currentLogin.toString() ;
  String pass         =      this->currentPass.toString() ;
  bool   is_anonymous = bool(this->currentIsAnonymous.getValue()) ;

  ValueTree server = addServerConfig(host , login , pass , is_anonymous) ;
  server.setProperty(STORAGE::HOST_IDENTIFIER  , host         , nullptr) ;
  server.setProperty(STORAGE::LOGIN_IDENTIFIER , login        , nullptr) ;
  server.setProperty(STORAGE::PASS_IDENTIFIER  , pass         , nullptr) ;
  server.setProperty(STORAGE::ANON_IDENTIFIER  , is_anonymous , nullptr) ;
}

ValueTree LinJamConfig::getServerConfig(String host)
{ return this->servers.getChildWithProperty(STORAGE::HOST_IDENTIFIER , var(host)) ; }

ValueTree LinJamConfig::getCurrentServerConfig()
{ return getServerConfig(this->currentHost.toString()) ; }

void LinJamConfig::setShouldAgree(bool should_agree)
{
  // continuation of setServerConfig() after license agreement
  ValueTree server = getCurrentServerConfig() ;
  if (!server.isValid()) return ;

  server.setProperty(STORAGE::AGREE_IDENTIFIER , should_agree , nullptr) ;
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
  XmlElement* client     = config_xml->getChildByName(STORAGE::CLIENT_IDENTIFIER) ;

  // unset session dir and log file - these are too dangerous to be user-configuraable
  client->removeAttribute(STORAGE::SESSIONDIR_KEY) ;
  client->removeAttribute(STORAGE::LOGFILE_KEY) ;

  config_xml->writeToFile(this->configXmlFile , StringRef() , StringRef("UTF-8") , 0) ;
  delete config_xml ;
}

void LinJamConfig::establishSharedStore()
{
  // client config
  this->shouldSaveAudio    .referTo(getClientConfigValueObj(STORAGE::SAVE_AUDIO_IDENTIFIER)) ;
  this->shouldSaveLog      .referTo(getClientConfigValueObj(STORAGE::SAVE_LOG_IDENTIFIER)) ;
  this->debugLevel         .referTo(getClientConfigValueObj(STORAGE::DEBUGLEVEL_IDENTIFIER)) ;
  this->shouldAutoSubscribe.referTo(getClientConfigValueObj(STORAGE::AUTOSUBSCRIBE_IDENTIFIER)) ;
  this->autoSubscribeUsers = this->configValueTree.getOrCreateChildWithName(STORAGE::SUBSCRIPTIONS_IDENTIFIER , nullptr) ;
  this->autoSubscribeUsers.addListener(this) ;

  // device config
  this->audioIfN       .referTo(getAudioConfigValueObj(STORAGE::AUDIO_IF_IDENTIFIER)) ;
  this->nInputs        .referTo(getAudioConfigValueObj(STORAGE::N_INPUTS_IDENTIFIER)) ;
  this->nOutputs       .referTo(getAudioConfigValueObj(STORAGE::N_OUTPUTS_IDENTIFIER)) ;
  this->bitDepth       .referTo(getAudioConfigValueObj(STORAGE::BITDEPTH_IDENTIFIER)) ;
  this->sampleRate     .referTo(getAudioConfigValueObj(STORAGE::SAMPLERATE_IDENTIFIER)) ;
  this->jackName       .referTo(getAudioConfigValueObj(STORAGE::JACK_NAME_IDENTIFIER)) ;

  // transient login state
  this->currentHost       .referTo(getServerConfigValueObj(STORAGE::HOST_IDENTIFIER)) ;
  this->currentLogin      .referTo(getServerConfigValueObj(STORAGE::LOGIN_IDENTIFIER)) ;
  this->currentPass       .referTo(getServerConfigValueObj(STORAGE::PASS_IDENTIFIER)) ;
  this->currentIsAnonymous.referTo(getServerConfigValueObj(STORAGE::ANON_IDENTIFIER)) ;
  this->currentIsAgreed   .referTo(getServerConfigValueObj(STORAGE::AGREED_IDENTIFIER)) ;

  // static channels
  this->masterChannels = this->configValueTree.getOrCreateChildWithName(STORAGE::MASTERS_IDENTIFIER , nullptr) ;
  this->masterChannels.addListener(this) ;

  // transient channels
  this->localChannels  = this->configValueTree.getOrCreateChildWithName(STORAGE::LOCALS_IDENTIFIER , nullptr) ;
  this->localChannels .addListener(this) ;
  this->remoteChannels = this->configValueTree.getOrCreateChildWithName(STORAGE::REMOTES_IDENTIFIER , nullptr) ;
  this->remoteChannels.addListener(this) ;

  // per server user data
  this->servers = this->configValueTree.getOrCreateChildWithName(STORAGE::SERVERS_IDENTIFIER , nullptr) ;
  this->servers.addListener(this) ;
}

Value LinJamConfig::getConfigValueObj(ValueTree parent_node , Identifier child_node_id ,
                                      Identifier key)
{
  ValueTree child_node  = parent_node.getChildWithName(child_node_id) ;

DEBUG_TRACE_CONFIG_VALUE

  return (child_node.isValid() && child_node.hasProperty(key))?
    child_node.getPropertyAsValue(key , &this->configUndoManager) :
    this->dummyValue ;
}

Value LinJamConfig::getClientConfigValueObj(Identifier key)
{ return getConfigValueObj(this->configValueTree , STORAGE::CLIENT_IDENTIFIER , key) ; }

Value LinJamConfig::getAudioConfigValueObj(Identifier key)
{ return getConfigValueObj(this->configValueTree , STORAGE::AUDIO_IDENTIFIER  , key) ; }

Value LinJamConfig::getServerConfigValueObj(Identifier key)
{ return getConfigValueObj(this->configValueTree , STORAGE::SERVER_IDENTIFIER , key) ; }

ValueTree LinJamConfig::addServerConfig(String host , String login , String pass ,
                                        bool is_anonymous)
{
  ValueTree server = getServerConfig(host) ;
  if (!server.isValid())
  {
    Identifier host_id = Identifier(STORAGE::SERVER_IDENTIFIER.toString() + "-" +
                         host.replaceCharacter('.' , '-')
                             .replaceCharacter(':' , '-')) ;

    server = ValueTree(host_id) ;
    server.setProperty(STORAGE::HOST_IDENTIFIER  , host         , nullptr) ;
    server.setProperty(STORAGE::LOGIN_IDENTIFIER , login        , nullptr) ;
    server.setProperty(STORAGE::PASS_IDENTIFIER  , pass         , nullptr) ;
    server.setProperty(STORAGE::ANON_IDENTIFIER  , is_anonymous , nullptr) ;
    server.setProperty(STORAGE::AGREE_IDENTIFIER , false        , nullptr) ;

    this->servers        .addChild(server        , -1 , nullptr) ;
    this->configValueTree.addChild(this->servers , -1 , nullptr) ;
  }

  return server ;
}

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
  if (node_id == STORAGE::MASTER_IDENTIFIER)
  {
    if      (key == STORAGE::VOLUME_IDENTIFIER)
      LinJam::Client->config_mastervolume = (float)DB2VAL(a_double) ;
    else if (key == STORAGE::PAN_IDENTIFIER)
      LinJam::Client->config_masterpan    = a_float ;
    else if (key == STORAGE::MUTE_IDENTIFIER)
      LinJam::Client->config_mastermute   = a_bool ;

    return ;
  }
  if (node_id == STORAGE::METRO_IDENTIFIER)
  {
    if      (key == STORAGE::VOLUME_IDENTIFIER)
      LinJam::Client->config_metronome           = (float)DB2VAL(a_double) ;
    else if (key == STORAGE::PAN_IDENTIFIER)
      LinJam::Client->config_metronome_pan       = a_float ;
    else if (key == STORAGE::MUTE_IDENTIFIER)
      LinJam::Client->config_metronome_mute      = a_bool ;
    else if (key == STORAGE::SOURCE_N_IDENTIFIER)
      LinJam::Client->config_metronome_channel   = an_int ;
    else if (key == STORAGE::STEREO_IDENTIFIER)
      LinJam::Client->config_metronome_stereoout = a_bool ;

    return ;
  }

  // local and remote channels
//   ValueTree channel_config ; int channel_idx ;
  // TODO: this seems much cleaner but Local_Channel::name is protected
//   else if (channel_idx = LinJam::Client->GetLocalChannelIdxByName(node_id) != -1)
//   if (channel_config = this->localChannels.getChildWithName(node_id))
//   int source_n ; int bitrate ; bool is_xmit ;
  bool  should_set_volume   = (key == STORAGE::VOLUME_IDENTIFIER) ;
  bool  should_set_pan      = (key == STORAGE::PAN_IDENTIFIER) ;
  bool  should_set_is_xmit  = (key == STORAGE::XMIT_IDENTIFIER) ;
  bool  should_set_is_muted = (key == STORAGE::MUTE_IDENTIFIER) ;
  bool  should_set_is_solo  = (key == STORAGE::SOLO_IDENTIFIER) ;
  bool  should_set_source_n = (key == STORAGE::SOURCE_N_IDENTIFIER) ;
  bool  should_set_bitrate  = (key == STORAGE::SAMPLERATE_IDENTIFIER) ;
  if      (LinJam::SetLocalChannelInfoByName(String(node_id).toRawUTF8()             ,
                                             should_set_source_n           , an_int  ,
                                             should_set_bitrate            , an_int  ,
                                             should_set_is_xmit            , a_bool  ,
                                             should_set_volume             , a_float ,
                                             should_set_pan                , a_float ,
                                             should_set_is_muted           , a_bool  ,
                                             should_set_is_solo            , a_bool))
  {
DBG("valueTreePropertyChanged() SetLocalChannelInfoByName() returned true") ;
//    channel_idx = this->localChannels.indexOf(channel_config) ;
  }
}

// unused ValueTree::Listener interface methods
void LinJamConfig::valueTreeChildAdded(ValueTree& a_parent_tree , ValueTree& a_child_tree)   {}
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
