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


class LinJamConfig : public ValueTree::Listener , public Value::Listener
{
public:

  LinJamConfig() ;
  ~LinJamConfig() ;


  static String    TrimStereoName(String channel_name) ;
  static ValueTree NewChannel(    String channel_name = CONFIG::DEFAULT_CHANNEL_NAME ,
                                  int    channel_idx  = CONFIG::DEFAULT_CHANNEL_IDX  ) ;


  /* config root
  ValueTree configValueTree ; (private)
  {
    CONFIG_VERSION_ID => double
  } */

  // client config
  ValueTree client ; /* CLIENT_ID - client-specfic data
  {
    SAVE_AUDIO_MODE_ID  => int    ,
    MIXDOWN_MODE_ID     => int    ,
    SHOULD_SAVE_LOG_ID  => bool   ,
    DEBUG_LEVEL_ID      => int    ,
    SHOULD_HIDE_BOTS_ID => bool   ,
  }                  */
  ValueTree subscriptions ; /* SUBSCRIPTIONS_ID - subscriptions-specfic data
  {
    SUBSCRIBE_MODE_ID => int
  }                         */

  // audio device config
  ValueTree audio ; /* AUDIO_KEY - audio-specfic data
  {
    WIN_AUDIO_IF_ID    => int (audioStreamer::Interface enum)
    ASIO_DRIVER_ID     => int
    ASIO_INPUT0_ID     => int
    ASIO_INPUT1_ID     => int
    ASIO_OUTPUT0_ID    => int
    ASIO_OUTPUT1_ID    => int
    KS_INPUT_ID        => int
    KS_OUTPUT_ID       => int
    KS_SAMPLERATE_ID   => int
    KS_BITDEPTH_ID     => int
    KS_NBLOCKS_ID      => int
    KS_BLOCKSIZE_ID    => int
    DS_INPUT0_ID       => int
    DS_INPUT1_ID       => int
    DS_INPUT2_ID       => int
    DS_INPUT3_ID       => int
    DS_OUTPUT0_ID      => int
    DS_OUTPUT1_ID      => int
    DS_OUTPUT2_ID      => int
    DS_OUTPUT3_ID      => int
    DS_SAMPLERATE_ID   => int
    DS_BITDEPTH_ID     => int
    DS_NBLOCKS_ID      => int
    DS_BLOCKSIZE_ID    => int
    WAVE_INPUT_ID      => int
    WAVE_OUTPUT_ID     => int
    WAVE_SAMPLERATE_ID => int
    WAVE_BITDEPTH_ID   => int
    WAVE_NBLOCKS_ID    => int
    WAVE_BLOCKSIZE_ID  => int
    MAC_DEVICE_ID      => string
    MAC_NINPUTS_ID     => int
    MAC_SAMPLERATE_ID  => int
    MAC_BITDEPTH_ID    => int
    NIX_AUDIO_IF_ID    => int (audioStreamer::Interface enum)
    JACK_SERVER_ID     => int
    JACK_NAME_ID       => string
    JACK_NINPUTS_ID    => int
    JACK_NOUTPUTS_ID   => int
    ALSA_CONFIG_ID     => string
  }                 */

  // server credentials
  ValueTree server ;  // SERVER_ID  - transient login credentials
  ValueTree servers ; /* SERVERS_ID - per-server credentials
  [
    {
      HOST_ID         => string
      LOGIN_ID        => string
      PASS_ID         => string
      IS_ANONYMOUS_ID => bool
      SHOULD_AGREE_ID => bool
      IS_AGREED_ID    => bool   // <server> node only - TODO: this exists only so OnLicense doesnt block (issue #14)
    }
  ]                   */

  // peers
  ValueTree remoteUsers ; /* REMOTES_ID - per-peer data
  [
    {
      USER_IDX_ID => int                 ,
      child_nodes => [ a_channel , ... ] // channels as below
    } ,
    ...
  ]                       */

  // channels
  ValueTree masterChannels ; // MASTERS_ID          - per-channel data (master and metro)
  ValueTree localChannels ;  // LOCALS_ID           - per-channel data
                             /* remoteUsers[A_USER] - per-channel data
  [
    {
      CHANNEL_NAME_ID => string ,
      CHANNEL_IDX_ID  => int    ,
      PAIR_IDX_ID     => int    ,
      VOLUME_ID       => double ,
      PAN_ID          => double ,
      IS_XMIT_RCV_ID  => bool   ,
      IS_MUTED_ID     => bool   ,
      IS_SOLO_ID      => bool   ,
      SOURCE_N_ID     => int    ,

      STEREO_ID       => int    ,
      VU_LEFT_ID      => double ,
      VU_RIGHT_ID     => double
    } ,
    ...
  ]                          */

  // validation
  bool       isConfigSane() ;
  String     parseUsername(    String user_name) ;
  Identifier makeHostId(       String host_name) ;
  Identifier makeUserId(       String channel_name) ;
  Identifier makeChannelId(    int channel_idx) ;
  String     makeStereoName(   String channel_name , int stereo_status) ;
  int        parseStereoStatus(String channel_name) ;
  void       setStereo(        ValueTree channel_store , int stereo_status) ;
  int        setRemoteStereo(  ValueTree user_store        , ValueTree channel_store ,
                               String    prev_channel_name                           ) ;

  // getters/setters
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


private:

  File      configXmlFile ;
  ValueTree configValueTree ;
  Value     dummyValue ;


  // validation
  void      initialize() ;
  ValueTree sanitizeConfig(    ValueTree default_config , ValueTree stored_config) ;
  void      restoreVarTypeInfo(ValueTree config_store) ;
  void      validateServers() ;
  void      validateUsers() ;
  void      validateChannels(  ValueTree channels) ;
  void      storeConfig() ;
  void      establishSharedStore() ;
  bool      sanityCheck() ;

  // helpers
  String filteredName(String a_name) ;

  // event handlers
  void valueChanged(            Value& a_value)                               override ;
  void valueTreePropertyChanged(ValueTree& a_node , const Identifier& key)    override ;
  void valueTreeChildAdded(     ValueTree& a_parent_node , ValueTree& a_node) override ;
  void valueTreeChildRemoved(   ValueTree& a_parent_node , ValueTree& a_node) override ;

  // unused ValueTree::Listener interface methods
  // called when a tree's children have been re-shuffled.
  void valueTreeChildOrderChanged(ValueTree& a_parent_node)                override {} ;
  // called when a tree has been added or removed from a parent node.
  void valueTreeParentChanged(ValueTree& a_node)                           override {} ;
  // called when a tree is made to point to a different internal shared object.
  void valueTreeRedirected(ValueTree& a_node)                              override {} ;


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinJamConfig) ;
} ;

#endif // _LINJAMCONFIG_H_
