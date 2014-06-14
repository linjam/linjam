/*
  ==============================================================================

    LinJamConfig.cpp
    Created: 12 Jun 2014 7:05:12am
    Author:  me

  ==============================================================================
*/

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

void LinJamConfig::setShouldAgree(bool should_agree)
{
  // continuation of setServerConfig() after license agreement
  ValueTree server = getCurrentServerConfig() ;
  if (!server.isValid()) return ;

  server.setProperty(STORAGE::AGREE_IDENTIFIER , should_agree , nullptr) ;
}

ValueTree LinJamConfig::getServerConfig(String host)
{ return this->servers.getChildWithProperty(STORAGE::HOST_IDENTIFIER , var(host)) ; }

ValueTree LinJamConfig::getCurrentServerConfig()
{ return getServerConfig(this->currentHost.toString()) ; }


/* LinJamConfig private instance methods */

void LinJamConfig::valueChanged(Value& a_value)
{
DBG("LinJamConfig::valueChanged()=" + a_value.getValue().toString()) ;
}

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
  this->shouldSaveAudio    .referTo(getConfigValueObj(STORAGE::CLIENT_IDENTIFIER , STORAGE::SAVE_AUDIO_IDENTIFIER)) ;
  this->shouldSaveLog      .referTo(getConfigValueObj(STORAGE::CLIENT_IDENTIFIER , STORAGE::SAVE_LOG_IDENTIFIER)) ;
  this->debugLevel         .referTo(getConfigValueObj(STORAGE::CLIENT_IDENTIFIER , STORAGE::DEBUGLEVEL_IDENTIFIER)) ;
  this->shouldAutoSubscribe.referTo(getConfigValueObj(STORAGE::CLIENT_IDENTIFIER , STORAGE::AUTOSUBSCRIBE_IDENTIFIER)) ;
  this->autoSubscribeUsers = this->configValueTree.getOrCreateChildWithName(STORAGE::SUBSCRIPTIONS_IDENTIFIER , nullptr) ;

  // device config
  this->audioIfN       .referTo(getConfigValueObj(STORAGE::AUDIO_IDENTIFIER , STORAGE::AUDIO_IF_IDENTIFIER)) ;
  this->nInputs        .referTo(getConfigValueObj(STORAGE::AUDIO_IDENTIFIER , STORAGE::N_INPUTS_IDENTIFIER)) ;
  this->nOutputs       .referTo(getConfigValueObj(STORAGE::AUDIO_IDENTIFIER , STORAGE::N_OUTPUTS_IDENTIFIER)) ;
  this->bitDepth       .referTo(getConfigValueObj(STORAGE::AUDIO_IDENTIFIER , STORAGE::BITDEPTH_IDENTIFIER)) ;
  this->sampleRate     .referTo(getConfigValueObj(STORAGE::AUDIO_IDENTIFIER , STORAGE::SAMPLERATE_IDENTIFIER)) ;
  this->jackName       .referTo(getConfigValueObj(STORAGE::AUDIO_IDENTIFIER , STORAGE::JACK_NAME_IDENTIFIER)) ;

  // master channels
  this->masterVolume .referTo(getConfigValueObj(STORAGE::MASTER_IDENTIFIER , STORAGE::MASTER_VOLUME_IDENTIFIER)) ;
  this->masterVolume .addListener(this) ;
  this->masterPan    .referTo(getConfigValueObj(STORAGE::MASTER_IDENTIFIER , STORAGE::MASTER_PAN_IDENTIFIER)) ;
  this->isMasterMuted.referTo(getConfigValueObj(STORAGE::MASTER_IDENTIFIER , STORAGE::MASTER_MUTE_IDENTIFIER)) ;
  this->metroVolume  .referTo(getConfigValueObj(STORAGE::MASTER_IDENTIFIER , STORAGE::METRO_VOLUME_IDENTIFIER)) ;
  this->metroPan     .referTo(getConfigValueObj(STORAGE::MASTER_IDENTIFIER , STORAGE::METRO_PAN_IDENTIFIER)) ;
  this->isMetroMuted .referTo(getConfigValueObj(STORAGE::MASTER_IDENTIFIER , STORAGE::METRO_MUTE_IDENTIFIER)) ;
  this->metroChannel .referTo(getConfigValueObj(STORAGE::MASTER_IDENTIFIER , STORAGE::METRO_CHANNEL_IDENTIFIER)) ;
  this->isMetroStereo.referTo(getConfigValueObj(STORAGE::MASTER_IDENTIFIER , STORAGE::METRO_STEREO_IDENTIFIER)) ;

  // local channels
  this->localChannels = this->configValueTree.getOrCreateChildWithName(STORAGE::LOCALS_IDENTIFIER , nullptr) ;

  // transient login state
  this->currentHost       .referTo(getConfigValueObj(STORAGE::SERVER_IDENTIFIER , STORAGE::HOST_IDENTIFIER)) ;
  this->currentLogin      .referTo(getConfigValueObj(STORAGE::SERVER_IDENTIFIER , STORAGE::LOGIN_IDENTIFIER)) ;
  this->currentPass       .referTo(getConfigValueObj(STORAGE::SERVER_IDENTIFIER , STORAGE::PASS_IDENTIFIER)) ;
  this->currentIsAnonymous.referTo(getConfigValueObj(STORAGE::SERVER_IDENTIFIER , STORAGE::ANON_IDENTIFIER)) ;
  this->currentIsAgreed   .referTo(getConfigValueObj(STORAGE::SERVER_IDENTIFIER , STORAGE::AGREED_IDENTIFIER)) ;

  // per server user data
  this->servers = this->configValueTree.getOrCreateChildWithName(STORAGE::SERVERS_IDENTIFIER , nullptr) ;
}

Value LinJamConfig::getConfigValueObj(Identifier node_id , Identifier key)
{
  ValueTree a_node = this->configValueTree.getChildWithName(node_id) ;

DEBUG_TRACE_CONFIG_VALUE

  return (a_node.isValid() && a_node.hasProperty(key))?
    a_node.getPropertyAsValue(key , &this->configUndoManager) : this->dummyValue ;
}

bool LinJamConfig::sanityCheck()
{
  return (!this->shouldSaveAudio    .refersToSameSourceAs(this->dummyValue) &&
          !this->shouldSaveLog      .refersToSameSourceAs(this->dummyValue) &&
          !this->debugLevel         .refersToSameSourceAs(this->dummyValue) &&
          !this->shouldAutoSubscribe.refersToSameSourceAs(this->dummyValue) &&
          !this->audioIfN           .refersToSameSourceAs(this->dummyValue) &&
          !this->nInputs            .refersToSameSourceAs(this->dummyValue) &&
          !this->nOutputs           .refersToSameSourceAs(this->dummyValue) &&
          !this->bitDepth           .refersToSameSourceAs(this->dummyValue) &&
          !this->sampleRate         .refersToSameSourceAs(this->dummyValue) &&
          !this->jackName           .refersToSameSourceAs(this->dummyValue) &&
          !this->masterVolume       .refersToSameSourceAs(this->dummyValue) &&
          !this->masterPan          .refersToSameSourceAs(this->dummyValue) &&
          !this->isMasterMuted      .refersToSameSourceAs(this->dummyValue) &&
          !this->metroVolume        .refersToSameSourceAs(this->dummyValue) &&
          !this->metroPan           .refersToSameSourceAs(this->dummyValue) &&
          !this->isMetroMuted       .refersToSameSourceAs(this->dummyValue) &&
          !this->metroChannel       .refersToSameSourceAs(this->dummyValue) &&
          !this->isMetroStereo      .refersToSameSourceAs(this->dummyValue) &&
          !this->currentHost        .refersToSameSourceAs(this->dummyValue) &&
          !this->currentLogin       .refersToSameSourceAs(this->dummyValue) &&
          !this->currentPass        .refersToSameSourceAs(this->dummyValue) &&
          !this->currentIsAnonymous .refersToSameSourceAs(this->dummyValue) &&
          !this->currentIsAgreed    .refersToSameSourceAs(this->dummyValue) &&
          autoSubscribeUsers.isValid()                                      &&
          localChannels.isValid()                                           &&
          servers.isValid()                                                  ) ;
}

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


// DEBUG
void LinJamConfig::DBGConfigValueType(String val_name , Value a_value)
{
  var a_var = a_value.getValue() ; String dynamic_type ;
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
  DBG(val_name + " type is " + dynamic_type) ;
}
