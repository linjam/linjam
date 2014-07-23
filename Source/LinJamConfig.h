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
  Value     saveAudio ;          // int
  Value     shouldSaveLog ;      // bool
  Value     debugLevel ;         // int
  Value     autoSubscribe ;      // int
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
  ValueTree masterChannels ; // children: master , metro channels as below
  ValueTree localChannels ;  // children: channels as below
  ValueTree remoteUsers ;    // children: users , grandchildren: channels as below
/* per-user data - access through above remoteUsers
  Value     user-idx         // int
/* per-channel data - access through above ValueTrees
  Value     channel-name     // string
  Value     channel-idx      // int
  Value     stereo-pair-idx  // int
  Value     volume           // double
  Value     pan              // double
  Value     is-xmitrcv       // bool
  Value     is-muted         // bool
  Value     is-solo          // bool
  Value     source-sink-n    // int
  Value     stereo-status    // int
  Value     vu-left          // double
  Value     vu-right         // double
*/

  // current server config
  Value host ;           // string
  Value login ;          // string
  Value pass ;           // string
  Value isAnonymous ;    // bool
  Value isAgreed ;       // bool // TODO: ?? this exists only so OnLicense doesnt block (issue #14)
  Value shouldAgree ;    // bool // TODO: unused
  Value shouldHideBots ; // bool

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
  String     parseUsername(    String user_name) ;
  Identifier makeHostId(       String host_name) ;
  Identifier makeUserId(       String channel_name , int user_idx) ;
  Identifier makeChannelId(    int channel_idx) ;
  String     trimStereoName(   String channel_name) ;
  String     makeStereoName(   String channel_name , int stereo_status) ;
  int        parseStereoStatus(String channel_name) ;
  void       setStereo(        ValueTree channel_store , int stereo_status) ;
  int        setRemoteStereo(  ValueTree user_store        , ValueTree channel_store ,
                               String    prev_channel_name                           ) ;

  // getters/setters
  ValueTree newChannel(           String channel_name = CONFIG::DEFAULT_CHANNEL_NAME ,
                                  int    channel_idx  = CONFIG::DEFAULT_CHANNEL_IDX  ) ;
  ValueTree addChannel(           ValueTree channels_store , ValueTree new_store) ;
  void      destroyChannel(       ValueTree channels_store , ValueTree channel_store) ;
  ValueTree getOrAddRemoteUser(   String user_name , int user_idx) ;
  ValueTree getOrAddRemoteChannel(Identifier user_id     , String channel_name        ,
                                  int        channel_idx = CONFIG::DEFAULT_CHANNEL_IDX) ;
  ValueTree getUserById(          Identifier user_id) ;
  ValueTree getChannelById(       Identifier channels_id , Identifier channel_id) ;
  ValueTree getChannelByIdx(      ValueTree channels_store , int channel_idx) ;
  ValueTree getChannelByPairIdx(  ValueTree channels_store , int pair_idx) ;
  ValueTree getChannelByName(     ValueTree channels_store , String channel_name) ;
  ValueTree getUserMasterChannel( ValueTree user_store) ;
  void      setServer() ;
  ValueTree getServer(            String host_name) ;
  void      setCurrentServer(     String host_name    , String login , String pass ,
                                  bool   is_anonymous                              ) ;
  ValueTree getCurrentServer() ;
  void      setServerShouldAgree( bool should_agree) ;


private:

  File        configXmlFile ;
  ValueTree   configValueTree ;
  Value       dummyValue ;


  // validation
  ValueTree sanitizeConfig(     ValueTree default_config , ValueTree stored_config) ;
  void      restoreVarTypeInfo( ValueTree store) ;
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
  ValueTree  addServer(   String host_name , String login       ,
                          String pass      , bool   is_anonymous) ;
  String     filteredName(String a_name) ;

  // event handlers
  void valueTreePropertyChanged(ValueTree& a_node , const Identifier& key) override ;

  // unused ValueTree::Listener interface methods
  // called when a child sub-tree is added.
  void valueTreeChildAdded(ValueTree& a_parent_node , ValueTree& a_node)   override {}
  // called when a child sub-tree is removed.
  void valueTreeChildRemoved(ValueTree& a_parent_node , ValueTree& a_node) override {}
  // called when a tree's children have been re-shuffled.
  void valueTreeChildOrderChanged(ValueTree& a_parent_node)                override {} ;
  // called when a tree has been added or removed from a parent node.
  void valueTreeParentChanged(ValueTree& a_node)                           override {} ;
  // called when a tree is made to point to a different internal shared object.
  void valueTreeRedirected(ValueTree& a_node)                              override {} ;


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinJamConfig) ;
} ;

#endif // _LINJAMCONFIG_H_
