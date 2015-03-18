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
  friend class LinJam ;


public:

  LinJamConfig() ;
  ~LinJamConfig() ;


  // validation
  static Identifier MakeHostId(       String host) ;
  static Identifier MakeUserId(       String channel_name) ;
  static Identifier MakeChannelId(    int channel_idx) ;
  static String     MakeStereoName(   String channel_name , int stereo_status) ;
  static String     TrimStereoName(   String channel_name) ;
  static int        ParseStereoStatus(String channel_name) ;
  static ValueTree  NewChannel(       String channel_name = CONFIG::DEFAULT_CHANNEL_NAME ,
                                      int    channel_idx  = CONFIG::DEFAULT_CHANNEL_IDX  ) ;


  /* value holders (see Constants.h CONFIG_XML and CONFIG_TYPES_XML) */

private:
  // config root (PERSISTENCE_TYPES_KEY datatypes)
  ValueTree configRoot ; // PERSISTENCE_ID node - parent of all nodes below
public:
  // client config (CLIENT_KEY datatypes)
  ValueTree client ; // CLIENT_ID node - client-specific data

  // subscriptions (SUBSCRIPTIONS_KEY datatypes)
  ValueTree subscriptions ; // SUBSCRIPTIONS_ID node - subscriptions-specific data

  // audio device config (AUDIO_KEY datatypes)
  ValueTree audio ; // AUDIO_KEY node - api-specific audio hardware initialization data

  // TODO: server[IS_AGREED_ID] exists only so OnLicense doesnt block (issue #14)
  // credentials (SERVER_KEY datatypes - IS_AGREED_ID is <server> node only)
  ValueTree server ;  // SERVER_ID node  - transient login credentials
  // credentials (list of SERVER_KEY datatypes)
  ValueTree servers ; // SERVERS_ID node - per-server credentials

  // peers (list of USERS_KEY datatypes - children are channels as below)
  ValueTree remoteUsers ; // REMOTES_ID node - per-peer data

  // channels (list of CHANNELS_KEY datatypes)
  ValueTree masterChannels ; // MASTERS_ID node - per-channel data (master and metro)
  ValueTree localChannels ;  // LOCALS_ID node  - per-channel data
                             // remoteUsers[n]  - per-channel data (each remoteUsers)


private:

  File  configXmlFile ;
  Value dummyValue ;

  // setup
  void initialize() ;
  void establishSharedStore() ;
  void restoreVarTypeInfo( ValueTree config_store) ;
  void storeConfig() ;

  // validation
  ValueTree sanitizeConfig(  ValueTree default_config , ValueTree stored_config) ;
  void      validateServers() ;
  void      validateUsers() ;
  void      validateChannels(ValueTree channels) ;
  bool      validateConfig() ;
  bool      isConfigValid() ;

  // getters/setters
  ValueTree addChannel(           ValueTree channels_store , ValueTree new_store) ;
  void      removeChannel(        ValueTree channels_store , ValueTree channel_store) ;
  ValueTree getOrAddRemoteUser(   String user_name) ;
  ValueTree getOrAddRemoteChannel(Identifier user_id     , String channel_name        ,
                                  int        channel_idx = CONFIG::DEFAULT_CHANNEL_IDX) ;
  ValueTree getUserById(          Identifier user_id) ;
  ValueTree getChannelById(       Identifier channels_id , Identifier channel_id) ;
  ValueTree getChannelByIdx(      ValueTree channels_store , int channel_idx) ;
  ValueTree getChannelByPairIdx(  ValueTree channels_store , int pair_idx) ;
  ValueTree getChannelByName(     ValueTree channels_store , String channel_name) ;
  ValueTree getUserMasterChannel( ValueTree user_store) ;
  void      setCredentials(       String host         , String login , String pass ,
                                  bool   is_anonymous                              ) ;
  ValueTree getCredentials(       String host) ;
  void      setServer() ;
  ValueTree getServer(            String host) ;
  void      setStereo(            ValueTree channel_store , int stereo_status) ;
  int       setRemoteStereo(      ValueTree user_store        , ValueTree channel_store ,
                                  String    prev_channel_name                           ) ;

  // event handlers
  void valueChanged(            Value& a_value)                               override ;
  void valueTreePropertyChanged(ValueTree& a_node , const Identifier& key)    override ;
  void valueTreeChildAdded(     ValueTree& a_parent_node , ValueTree& a_node) override ;
  void valueTreeChildRemoved(   ValueTree& a_parent_node , ValueTree& a_node) override ;

  // unused ValueTree::Listener interface implementations
  // called when a tree's children have been re-shuffled.
  void valueTreeChildOrderChanged(ValueTree& a_parent_node)                override {} ;
  // called when a tree has been added or removed from a parent node.
  void valueTreeParentChanged(    ValueTree& a_node)                       override {} ;
  // called when a tree is made to point to a different internal shared object.
  void valueTreeRedirected(       ValueTree& a_node)                       override {} ;


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinJamConfig) ;
} ;

#endif // _LINJAMCONFIG_H_
