/*
  ==============================================================================

    LinJamConfig.h
    Created: 12 Jun 2014 7:05:12am
    Author:  me

  ==============================================================================
*/

#ifndef _LINJAMCONFIG_H_
#define _LINJAMCONFIG_H_


#include "Constants.h"
#include "JuceHeader.h"


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
  ValueTree autoSubscribeUsers ;  // probably wont use this

  // device config
  Value audioIfN ;    // int
  Value bitDepth ;    // int
  Value sampleRate ;  // int
  Value nInputs ;     // int
  Value nOutputs ;    // int
  Value jackName ;    // string
  Value configAudio ; // string

  // channels
  ValueTree masterChannels ; // children: master , metro channels as below
  ValueTree localChannels ;  // children: channels as below
  ValueTree remoteUsers ;    // children: users , grandchildren: channels as below
/* per-user data - access through above remoteUsers
  Value     user-idx         // int
/* per-channel data - access through above ValueTrees
  Value     channel-name     // string
  Value     channel-idx      // int
  Value     volume           // float
  Value     pan              // float
  Value     is-xmitrcv       // bool
  Value     is-muted         // bool
  Value     is-solo          // bool
  Value     source-channel-n // int
  Value     is-stereo        // bool
*/

  // current server config
  Value currentHost ;        // string
  Value currentLogin ;       // string
  Value currentPass ;        // string
  Value currentIsAnonymous ; // bool
  Value currentIsAgreed ;    // bool // TODO: ?? this exists only so OnLicense doesnt block (issue #14)
  Value shouldHideBots ;     // bool

  // per server config
  ValueTree servers ;
/*
  Value     host             // string
  Value     login            // string
  Value     pass             // string
  Value     is-anonymous     // bool
  Value     should-agree     // bool
  Value     should-hide-bots // bool
*/

  // validation
  bool       sanityCheck() ;
  String     parseUsername(String user_name) ;
  Identifier encodeUserId( String channel_name , int user_idx) ;
  Identifier makeChannelId(int channel_idx) ;

  // getters/setters
  ValueTree newChannel(          String channel_name  = CONFIG::DEFAULT_CHANNEL_NAME ,
                                 int    channel_idx   = CONFIG::DEFAULT_SOURCE_N     ,
                                 float  volume        = CONFIG::DEFAULT_VOLUME       ,
                                 float  pan           = CONFIG::DEFAULT_PAN          ,
                                 bool   is_xmit_rcv   = CONFIG::DEFAULT_IS_XMIT      ,
                                 bool   is_muted      = CONFIG::DEFAULT_IS_MUTED     ,
                                 bool   is_solo       = CONFIG::DEFAULT_IS_SOLO      ,
                                 int    source_sink_n = CONFIG::DEFAULT_SOURCE_N     ,
                                 bool   is_stereo     = CONFIG::DEFAULT_IS_STEREO    ) ;
  ValueTree setChannel(          Identifier channels_id   , Identifier new_id ,
                                 ValueTree  channel_store                     ) ;
  ValueTree getOrCreateUser(     String user_name , int   user_idx ,
                                 float  volume    , float pan      , bool is_muted) ;
  ValueTree getOrCreateChannel(  Identifier channels_id   , String channel_name ,
                                 int        channel_idx   , float  volume       ,
                                 float      pan           , bool   is_xmit_rcv  ,
                                 bool       is_muted      , bool   is_solo      ,
                                 int        source_sink_n , bool   is_stereo    ) ;
  ValueTree getUserById(         Identifier user_id) ;
  ValueTree getChannelByIdx(     ValueTree channel_store , int channel_idx) ;
  ValueTree getChannelById(      Identifier channels_id , Identifier channel_id) ;
  void      setServer() ;
  ValueTree getServer(           String host) ;
  void      setCurrentServer(    String host         , String login , String pass ,
                                 bool   is_anonymous                              ) ;
  ValueTree getCurrentServer() ;
  void      setServerShouldAgree(bool should_agree) ;


private:

  File        configXmlFile ;
  ValueTree   configValueTree ;
  Value       dummyValue ;


  // validation
  ValueTree sanitizeConfig(     ValueTree default_config , ValueTree stored_config) ;
  bool      sanityCheckChannels(ValueTree channels) ;
  void      storeConfig() ;
  void      establishSharedStore() ;

  // helpers
  ValueTree  getNode(     Identifier tree_node_id) ;
  Value      getLeaf(     ValueTree parent_node , Identifier child_node_id ,
                          Identifier key) ;
  Value      getClient(   Identifier key) ;
  Value      getAudio(    Identifier key) ;
  Value      getServer(   Identifier key) ;
  ValueTree  addServer(   String host , String login , String pass , bool is_anonymous) ;
  String     filteredName(String a_name) ;

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


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinJamConfig) ;
} ;

#endif // _LINJAMCONFIG_H_
