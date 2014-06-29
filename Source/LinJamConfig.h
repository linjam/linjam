/*
  ==============================================================================

    LinJamConfig.h
    Created: 12 Jun 2014 7:05:12am
    Author:  me

  ==============================================================================
*/

#ifndef _LINJAMCONFIG_H_
#define _LINJAMCONFIG_H_


#include "LinJam.h"
#include "Constants.h"


class LinJamConfig : public ValueTree::Listener
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
  Value audioIfN ;    // int
  Value bitDepth ;    // int
  Value sampleRate ;  // int
  Value nInputs ;     // int
  Value nOutputs ;    // int
  Value jackName ;    // string
  Value configAudio ; // string

  // channels
  ValueTree masterChannels ;
  ValueTree localChannels ;
  ValueTree remoteChannels ;
/* per-channel data - access through above ValueTrees
  Value     volume ;        // float
  Value     pan ;           // float
  Value     isXmitRcv ;     // bool
  Value     isMuted ;       // bool
  Value     isSolo ;        // bool
  Value     sourceChannel ; // int
  Value     isStereo ;      // bool
*/

  // current server config
  Value currentHost ;        // string
  Value currentLogin ;       // string
  Value currentPass ;        // string
  Value currentIsAnonymous ; // bool
  Value currentIsAgreed ;    // bool // TODO: ?? this exists only so OnLicense doesnt block (issue #14)
  Value shouldHideBots ;     // bool

  // per server config (subtree)
  ValueTree servers ;


  // validation
  bool       sanityCheck() ;
  String     parseUsername(   String user_name) ;
  Identifier encodeChannelId( String     channel_name , int channel_idx) ;
  String     decodeChannelId( Identifier channel_id) ;
  Identifier encodeUserId(    String     channel_name , int user_idx) ;
  String     decodeUserId(    Identifier channel_id) ;
  bool       doesChannelExist(Identifier channels_id , String channel_id) ;

  // getters/setters
  ValueTree getOrCreateUser(   String user_name , int   user_idx ,
                               float  volume    , float pan      , bool is_muted) ;
  ValueTree createChannel(     Identifier channels_id   , String channel_name ,
                               int        channel_idx   , float  volume       ,
                               float      pan           , bool   is_xmit_rcv  ,
                               bool       is_muted      , bool   is_solo      ,
                               int        source_sink_n , bool   is_stereo    ) ;
  ValueTree getChannel(        Identifier channels_id , Identifier channel_id) ;
  void      setServer() ;
  ValueTree getServer(         String host) ;
  void      setCurrentServer(  String host , String login , String pass , bool is_anonymous) ;
  ValueTree getCurrentServer() ;
  void      setShouldAgree(    bool should_agree) ;


private:

  File        configXmlFile ;
  ValueTree   configValueTree ;
  Value       dummyValue ;


  ValueTree sanitizeConfig(ValueTree default_config , ValueTree stored_config) ;
  void      storeConfig() ;
  void      establishSharedStore() ;

  // helpers
  ValueTree  getNode(       Identifier tree_node_id) ;
  Value      getLeaf(       ValueTree parent_node , Identifier child_node_id ,
                            Identifier key) ;
  Value      getClient(     Identifier key) ;
  Value      getAudio(      Identifier key) ;
  Value      getServer(     Identifier key) ;
  ValueTree  addServer(     String host , String login , String pass , bool is_anonymous) ;
  ValueTree  getUser(       Identifier user_id) ;
  String     filteredName(  String a_name) ;
  Identifier saneIdentifier(String name) ;

  // event handlers
  void valueTreePropertyChanged(ValueTree& a_node , const Identifier& key)          override ;
  void valueTreeChildAdded(     ValueTree& a_parent_tree , ValueTree& a_child_tree) override ;
  void valueTreeChildRemoved(   ValueTree& a_parent_tree , ValueTree& a_child_tree) override ;

  // unused ValueTree::Listener interface methods
//  void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)=0 override ;
  // This method is called when a property of this node (or of one of its sub-nodes) has changed.
//  void valueTreeChildAdded(ValueTree& a_parent_tree , ValueTree& a_child_tree)    override ;
  // This method is called when a child sub-tree is added.
//   void valueTreeChildRemoved(ValueTree& a_parent_tree , ValueTree& a_child_tree)  override ;
  // This method is called when a child sub-tree is removed.
  void valueTreeChildOrderChanged(ValueTree& a_parent_tree)                       override ;
  // This method is called when a tree's children have been re-shuffled.
  void valueTreeParentChanged(ValueTree& a_tree)                                  override ;
  // This method is called when a tree has been added or removed from a parent node.
  void valueTreeRedirected(ValueTree& a_tree)                                     override ;
  // This method is called when a tree is made to point to a different internal shared object.


void DBGConfigValueType(String val_name , var a_var) ;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinJamConfig) ;
} ;

#endif // _LINJAMCONFIG_H_
