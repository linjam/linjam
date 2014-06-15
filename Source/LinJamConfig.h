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


class LinJamConfig : public Value::Listener ,
                     public ValueTree::Listener
{
public:

  LinJamConfig() ;
  ~LinJamConfig() ;


  // client config
  Value     shouldSaveAudio ;     // bool
  Value     shouldSaveLog ;       // bool
  Value     debugLevel ;          // int
  Value     shouldAutoSubscribe ; // bool
  ValueTree autoSubscribeUsers ; // probably wont use this

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
  ValueTree getServerConfig(        String host) ;
  ValueTree getCurrentServerConfig() ;
  void      setShouldAgree(         bool should_agree) ;
  Value     getClientConfigValueObj(Identifier key) ;
  Value     getAudioConfigValueObj( Identifier key) ;
  Value     getServerConfigValueObj(Identifier key) ;
  Value     getMasterConfigValueObj(Identifier channel_id , Identifier key) ;
  Value     getLocalConfigValueObj( Identifier channel_id , Identifier key) ;
  Value     getRemoteConfigValueObj(Identifier channel_id , Identifier key) ;


private:

  File        configXmlFile ;
  ValueTree   configValueTree ;
  UndoManager configUndoManager ;
  Value       dummyValue ;


  // helpers
  ValueTree sanitizeConfig(      ValueTree default_config , ValueTree stored_config) ;
  void      storeConfig() ;
  void      establishSharedStore() ;
  Value     getConfigValueObj(   ValueTree parent_node , Identifier child_node_id ,
                                 Identifier key) ;
  ValueTree addServerConfig(     String host , String login , String pass ,
                                 bool is_anonymous) ;

  // event handlers
  void valueChanged(            Value& a_value)                                   override ;
  void valueTreePropertyChanged(ValueTree& a_node , const Identifier& key)        override ;

  // unused ValueTree::Listener interface methods
//  void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)=0 override ;
  // This method is called when a property of this node (or of one of its sub-nodes) has changed.
  void valueTreeChildAdded(ValueTree& a_parent_tree , ValueTree& a_child_tree)    override ;
  // This method is called when a child sub-tree is added.
  void valueTreeChildRemoved(ValueTree& a_parent_tree , ValueTree& a_child_tree)  override ;
  // This method is called when a child sub-tree is removed.
  void valueTreeChildOrderChanged(ValueTree& a_parent_tree)                       override ;
  // This method is called when a tree's children have been re-shuffled.
  void valueTreeParentChanged(ValueTree& a_tree)                                  override ;
  // This method is called when a tree has been added or removed from a parent node.
  void valueTreeRedirected(ValueTree& a_tree)                                     override ;
  // This method is called when a tree is made to point to a different internal shared object.


void DBGConfigValueType(String val_name , Value a_value) ;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinJamConfig) ;
} ;

#endif  // LINJAMCONFIG_H_INCLUDED
