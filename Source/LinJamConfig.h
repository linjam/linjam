#ifndef _LINJAMCONFIG_H_
#define _LINJAMCONFIG_H_


#include "Constants.h"
#include "JuceHeader.h"


/**
  LinJamConfig is the model class
  it holds the runtime configuration via shared value holders
      and handles persistence via flat XML files
  it is also the controller for its shared value holders
      because the LinJmam controller class is currently static
*/
class LinJamConfig : public Value::Listener , public ValueTree::Listener
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
  static Value      GetValueHolder(   ValueTree config_store , Identifier a_key) ;


  /* value holders (see Constants.h CONFIG_XML and CONFIG_DATATYPES_XML) */

private:
  // config root (STORAGE_TYPES_KEY datatypes)
  ValueTree configRoot ;     // STORAGE_ID node - parent of all nodes below
public:
  // client config (GUI_KEY datatypes)
  ValueTree gui ;            // GUI_ID node - gui-specific data

  // client config (CLIENT_KEY datatypes)
  ValueTree client ;         // CLIENT_ID node - client-specific data

  // blacklist (BLACKLIST_KEY datatypes)
  ValueTree blacklist ;      // BLACKLIST_ID node - blacklist-specific data

  // audio device config (AUDIO_KEY datatypes)
  ValueTree audio ;          // AUDIO_KEY node - api-specific audio hardware initialization data

  // TODO: server[IS_AGREED_ID] exists only so OnLicense doesnt block (issue #14)
  // credentials (SERVER_KEY datatypes - IS_AGREED_ID is <server> node only)
  ValueTree server ;         // SERVER_ID node  - transient login credentials
  // credentials (list of SERVER_KEY datatypes)
  ValueTree servers ;        // SERVERS_ID node - per-server credentials

  // peers (list of USERS_KEY datatypes - children are channels as below)
  ValueTree remoteUsers ;    // REMOTES_ID node - per-peer data

  // channels (list of CHANNELS_KEY datatypes)
  ValueTree masterChannels ; // MASTERS_ID node - per-channel data (master and metro)
  ValueTree localChannels ;  // LOCALS_ID node  - per-channel data
                             // remoteUsers[n]  - per-channel data (each remoteUsers)


private:

  File  dataDir ;
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
  void      sanitizeGui() ;
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
  void      updateRemoteUserState(ValueTree user_store , int user_idx , bool should_rcv) ;
  void      setCredentials(       String host         , String login , String pass ,
                                  bool   is_anonymous                              ) ;
  ValueTree getCredentials(       String host) ;
  void      storeServer() ;
  ValueTree getServer(            String host) ;
  void      setStereo(            ValueTree channel_store , int stereo_status) ;
  int       setRemoteStereo(      ValueTree user_store        , ValueTree channel_store ,
                                  String    prev_channel_name                           ) ;

  // event handlers
  void valueChanged(            Value& value)                              override ;
  void valueTreePropertyChanged(ValueTree& node , const Identifier& key)   override ;
  void valueTreeChildAdded(     ValueTree& parent_node , ValueTree& node)  override ;
  void valueTreeChildRemoved(   ValueTree& parent_node , ValueTree& node ,
                                int /*prev_idx*/                         ) override ;

  // unused ValueTree::Listener interface implementations
  void valueTreeChildOrderChanged(ValueTree& /*parent_node*/ ,
                                  int /*prev_idx*/           , int /*curr_idx*/) override {} ;
  void valueTreeParentChanged(    ValueTree& /*node*/)                           override {} ;
  void valueTreeRedirected(       ValueTree& /*node*/)                           override {} ;


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinJamConfig) ;
} ;

#endif // _LINJAMCONFIG_H_
