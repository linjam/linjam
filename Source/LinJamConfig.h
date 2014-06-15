/*
  ==============================================================================

    LinJamConfig.h
    Created: 12 Jun 2014 7:05:12am
    Author:  me

  ==============================================================================
*/

#ifndef LINJAMCONFIG_H_INCLUDED
#define LINJAMCONFIG_H_INCLUDED

#include "Constants.h"
#include "Trace.h"

#include "../JuceLibraryCode/JuceHeader.h"


class LinJamConfig : public Value::Listener
{
public:

  LinJamConfig() ;
  ~LinJamConfig() ;


  // client config
  Value     shouldSaveAudio ;     // bool
  Value     shouldSaveLog ;       // bool
  Value     debugLevel ;          // int
  Value     shouldAutoSubscribe ; // bool
  ValueTree autoSubscribeUsers ;

  // device config
  Value audioIfN ;        // int
  Value bitDepth ;        // int
  Value sampleRate ;      // int
  Value nInputs ;         // int
  Value nOutputs ;        // int
  Value jackName ;        // string
  Value configAudio ;     // string

  // static channels
  ValueTree masterChannels ;
  Value     masterVolume ;  // float
  Value     masterPan ;     // float
  Value     isMasterMuted ; // bool
  Value     metroVolume ;   // float
  Value     metroPan ;      // float
  Value     isMetroMuted ;  // bool
  Value     metroChannel ;  // int
  Value     isMetroStereo ; // bool

  // transient channels
  ValueTree localChannels ;
  ValueTree remoteChannels ;

  // transient login state
  Value currentHost ;        // string
  Value currentLogin ;       // string
  Value currentPass ;        // string
  Value currentIsAnonymous ; // bool
  Value currentIsAgreed ;    // bool // TODO: ?? this exists only so OnLicense doesnt block (issue #14)

  // per server config (subtree)
  ValueTree servers ;

  // validation
  bool sanityCheck() ;

  // getters/setters
  void      setServerConfig() ;
  ValueTree getServerConfig(String host) ;
  ValueTree getCurrentServerConfig() ;
  void      setShouldAgree( bool should_agree) ;


private:

  File        configXmlFile ;
  ValueTree   configValueTree ;
  UndoManager configUndoManager ;
  Value       dummyValue ;


  // event handlers
  void valueChanged(Value& a_value) override ;

  // helpers
  ValueTree sanitizeConfig(ValueTree default_config , ValueTree stored_config) ;
  void      storeConfig() ;
  void      establishSharedStore() ;
  Value     getConfigValueObj(      ValueTree parent_node , Identifier child_node_id ,
                                    Identifier key) ;
  Value     getClientConfigValueObj(Identifier key) ;
  Value     getAudioConfigValueObj( Identifier key) ;
  Value     getServerConfigValueObj(Identifier key) ;
  Value     getMasterConfigValueObj(Identifier channel_id , Identifier key) ;
  Value     getLocalConfigValueObj( Identifier channel_id , Identifier key) ;
  Value     getRemoteConfigValueObj(Identifier channel_id , Identifier key) ;
  ValueTree addServerConfig(String host , String login , String pass , bool is_anonymous) ;


void DBGConfigValueType(String val_name , Value a_value) ;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinJamConfig) ;
} ;

#endif  // LINJAMCONFIG_H_INCLUDED
