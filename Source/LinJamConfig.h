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
  ValueTree client ;
  ValueTree subscriptions ;
/*
  Value     saveAudio ;     // int
  Value     shouldSaveLog ; // bool
  Value     debugLevel ;    // int
  Value     autoSubscribe ; // int
*/
  // audio device config
  ValueTree audio ;
/*
  var       win-audio-if-n    // int (audioStreamer::WinAudioIf enum)
  var       asio-driver       // int
  var       asio-input0       // int
  var       asio-input1       // int
  var       asio-output0      // int
  var       asio-output1      // int
  var       ks-input          // int
  var       ks-output         // int
  var       ks-sample-rate    // int
  var       ks-bit-depth      // int
  var       ks-block-size     // int
  var       ks-n-blocks       // int
  var       ds-input0         // int
  var       ds-input1         // int
  var       ds-input2         // int
  var       ds-input3         // int
  var       ds-output0        // int
  var       ds-output1        // int
  var       ds-output2        // int
  var       ds-output3        // int
  var       ds-sample-rate    // int
  var       ds-bit-depth      // int
  var       ds-block-size     // int
  var       ds-n-blocks       // int
  var       wave-input        // int
  var       wave-output       // int
  var       wave-sample-rate  // int
  var       wave-bit-depth    // int
  var       wave-block-size   // int
  var       wave-n-blocks     // int
  var       mac-n-inputs ;    // int
  var       mac-sample-rate ; // int
  var       mac-bit-depth ;   // int
  var       jack-n-inputs ;   // int
  var       jack-n-outputs ;  // int
  var       jack-name ;       // string
*/

  // login config
  ValueTree server ;
  Value     host ;           // string
  Value     login ;          // string
  Value     pass ;           // string
  Value     isAnonymous ;    // bool
  Value     isAgreed ;       // bool // TODO: ?? this exists only so OnLicense doesnt block (issue #14)
  Value     shouldAgree ;    // bool // TODO: unused
  Value     shouldHideBots ; // bool // TODO: this needs a new catagory e.g. <linjam-features>

  // per server config
  ValueTree servers ;
/*
  var       host             // string
  var       login            // string
  var       pass             // string
  var       is-anonymous     // bool
  var       should-agree     // bool
  var       should-hide-bots // bool
*/

  // channels
  ValueTree masterChannels ; // children: master , metro channels as below
  ValueTree localChannels ;  // children: channels as below
  ValueTree remoteUsers ;    // children: users , grandchildren: channels as below
/* per-user data - access through above remoteUsers
  var       user-idx         // int
/* per-channel data - access through above *Channels
  var       channel-name     // string
  var       channel-idx      // int
  var       stereo-pair-idx  // int
  var       volume           // double
  var       pan              // double
  var       is-xmitrcv       // bool
  var       is-muted         // bool
  var       is-solo          // bool
  var       source-sink-n    // int
  var       stereo-status    // int
  var       vu-left          // double
  var       vu-right         // double
*/

  // validation
  bool       isConfigSane() ;
  String     parseUsername(    String user_name) ;
  Identifier makeHostId(       String host_name) ;
  Identifier makeUserId(       String channel_name) ;
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
  ValueTree getOrAddRemoteUser(   String user_name) ;
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
  void      initialize() ;
  ValueTree sanitizeConfig(    ValueTree default_config , ValueTree stored_config) ;
  void      restoreVarTypeInfo(ValueTree store) ;
  void      sanitizeChannels(  ValueTree channels) ;
  void      storeConfig() ;
  void      establishSharedStore() ;
  bool      sanityCheck() ;

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
