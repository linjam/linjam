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
DEBUG_TRACE_CONFIG_CHANGED

  bool a_bool  = bool( a_value.getValue()) ;
  bool an_int  = int(  a_value.getValue()) ;
  bool a_float = float(a_value.getValue()) ;

  if      (a_value.refersToSameSourceAs(this->masterVolume))
    LinJam::Client->config_mastervolume        = a_float ;
  else if (a_value.refersToSameSourceAs(this->masterPan))
    LinJam::Client->config_masterpan           = a_float ;
  else if (a_value.refersToSameSourceAs(this->isMasterMuted))
    LinJam::Client->config_mastermute          = a_bool ;
  else if (a_value.refersToSameSourceAs(this->metroVolume))
    LinJam::Client->config_metronome           = a_float ;
  else if (a_value.refersToSameSourceAs(this->metroPan))
    LinJam::Client->config_metronome_pan       = a_float ;
  else if (a_value.refersToSameSourceAs(this->isMetroMuted))
    LinJam::Client->config_metronome_mute      = a_bool ;
  else if (a_value.refersToSameSourceAs(this->metroChannel))
    LinJam::Client->config_metronome_channel   = an_int ;
  else if (a_value.refersToSameSourceAs(this->isMetroStereo))
    LinJam::Client->config_metronome_stereoout = a_bool ;
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
  this->shouldSaveAudio    .referTo(getClientConfigValueObj(STORAGE::SAVE_AUDIO_IDENTIFIER)) ;
  this->shouldSaveLog      .referTo(getClientConfigValueObj(STORAGE::SAVE_LOG_IDENTIFIER)) ;
  this->debugLevel         .referTo(getClientConfigValueObj(STORAGE::DEBUGLEVEL_IDENTIFIER)) ;
  this->shouldAutoSubscribe.referTo(getClientConfigValueObj(STORAGE::AUTOSUBSCRIBE_IDENTIFIER)) ;
  this->autoSubscribeUsers = this->configValueTree.getOrCreateChildWithName(STORAGE::SUBSCRIPTIONS_IDENTIFIER , nullptr) ;

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
  this->masterVolume .referTo(getMasterConfigValueObj(STORAGE::MASTER_IDENTIFIER , STORAGE::VOLUME_IDENTIFIER)) ;
  this->masterVolume .addListener(this) ;
  this->masterPan    .referTo(getMasterConfigValueObj(STORAGE::MASTER_IDENTIFIER , STORAGE::PAN_IDENTIFIER)) ;
  this->masterPan    .addListener(this) ;
  this->isMasterMuted.referTo(getMasterConfigValueObj(STORAGE::MASTER_IDENTIFIER , STORAGE::MUTE_IDENTIFIER)) ;
  this->isMasterMuted.addListener(this) ;
  this->metroVolume  .referTo(getMasterConfigValueObj(STORAGE::METRO_IDENTIFIER  , STORAGE::VOLUME_IDENTIFIER)) ;
  this->metroVolume  .addListener(this) ;
  this->metroPan     .referTo(getMasterConfigValueObj(STORAGE::METRO_IDENTIFIER  , STORAGE::PAN_IDENTIFIER)) ;
  this->masterPan    .addListener(this) ;
  this->isMetroMuted .referTo(getMasterConfigValueObj(STORAGE::METRO_IDENTIFIER  , STORAGE::MUTE_IDENTIFIER)) ;
  this->isMetroMuted .addListener(this) ;
  this->metroChannel .referTo(getMasterConfigValueObj(STORAGE::METRO_IDENTIFIER  , STORAGE::SOURCE_N_IDENTIFIER)) ;
  this->metroChannel .addListener(this) ;
  this->isMetroStereo.referTo(getMasterConfigValueObj(STORAGE::METRO_IDENTIFIER  , STORAGE::STEREO_IDENTIFIER)) ;
  this->isMetroStereo.addListener(this) ;

  // transient channels
  this->localChannels  = this->configValueTree.getOrCreateChildWithName(STORAGE::LOCALS_IDENTIFIER , nullptr) ;
  this->remoteChannels = this->configValueTree.getOrCreateChildWithName(STORAGE::REMOTES_IDENTIFIER , nullptr) ;

  // per server user data
  this->servers = this->configValueTree.getOrCreateChildWithName(STORAGE::SERVERS_IDENTIFIER , nullptr) ;
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

Value LinJamConfig::getMasterConfigValueObj(Identifier channel_id , Identifier key)
{ return getConfigValueObj(this->masterChannels , channel_id , key) ; }

Value LinJamConfig::getLocalConfigValueObj(Identifier channel_id , Identifier key)
{ return getConfigValueObj(this->localChannels  , channel_id , key) ; }

Value LinJamConfig::getRemoteConfigValueObj(Identifier channel_id , Identifier key)
{ return getConfigValueObj(this->remoteChannels , channel_id , key) ; }

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
