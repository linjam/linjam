/*
  ==============================================================================

    Constants.h
    Created: 24 May 2014 11:41:00am
    Author:  me

  ==============================================================================
*/

#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_


#include "JuceHeader.h"


// NOTE: when adding nodes or leaves to CONFIG_XML be sure to
//         * store the datatype in   #define CONFIG_TYPES_XML
//         * restore the datatype in LinJamConfig::applyVarTypeInfo()
//         * note the datatype in    LinJamConfig.h
//         * verify data and type in LinJamConfig::sanityCheck() or sanityCheckChannels()
//         * dump data in            #define DEBUG_CONFIG_TYPES_VB
//                                   #define DEBUG_TRACE_SANITY_CHECK
//                                   #define DEBUG_TRACE_SANITY_CHECK_CHANNEL
//                                   #define DEBUG_TRACE_ADDED_CHANNEL
//                                   #define TRACE_CONFIGURE_LOCAL_CHANNEL_VB
//                                   #define DEBUG_TRACE_REMOTE_CHANNELS
//                                   #define DEBUG_TRACE_CONFIGURE_REMOTE
#define CONFIG_XML "<?xml version=\"1.0\"?><"                                 + \
  PERSISTENCE_KEY          + "><"                                             + \
    CLIENT_KEY             + " "                                              + \
      SAVE_AUDIO_KEY       + "=\"" + String(DEFAULT_SAVE_AUDIO)       + "\" " + \
      SAVE_LOG_KEY         + "=\"" + String(DEFAULT_SAVE_LOG)         + "\" " + \
      DEBUGLEVEL_KEY       + "=\"" + String(DEFAULT_DEBUGLEVEL)       + "\" " + \
      AUTOSUBSCRIBE_KEY    + "=\"" + String(DEFAULT_AUTOSUBSCRIBE)    + "\" " + \
    "/><"                                                                     + \
    AUDIO_KEY              + " "                                              + \
      AUDIO_IF_KEY         + "=\"" + String(DEFAULT_AUDIO_IF)         + "\" " + \
      N_INPUTS_KEY         + "=\"" + String(DEFAULT_N_INPUTS)         + "\" " + \
      N_OUTPUTS_KEY        + "=\"" + String(DEFAULT_N_OUTPUTS)        + "\" " + \
      BITDEPTH_KEY         + "=\"" + String(DEFAULT_BITDEPTH)         + "\" " + \
      SAMPLERATE_KEY       + "=\"" + String(DEFAULT_SAMPLERATE)       + "\" " + \
      JACK_NAME_KEY        + "=\"" + String(DEFAULT_JACK_NAME)        + "\" " + \
    "/><"                                                                     + \
    SERVER_KEY             + " "                                              + \
      HOST_KEY             + "=\"" + String(DEFAULT_HOST)             + "\" " + \
      LOGIN_KEY            + "=\"" + String(DEFAULT_LOGIN)            + "\" " + \
      PASS_KEY             + "=\"" + String(DEFAULT_PASS)             + "\" " + \
      IS_ANON_KEY          + "=\"" + String(DEFAULT_IS_ANON)          + "\" " + \
      IS_AGREED_KEY        + "=\"" + String(DEFAULT_IS_AGREED)        + "\" " + \
      SHOULD_AGREE_KEY     + "=\"" + String(DEFAULT_SHOULD_AGREE)     + "\" " + \
      SHOULD_HIDE_BOTS_KEY + "=\"" + String(DEFAULT_SHOULD_HIDE_BOTS) + "\" " + \
    "/><"                                                                     + \
    SERVERS_KEY            + " /><"                                           + \
    SUBSCRIPTIONS_KEY      + " /><"                                           + \
    MASTERS_KEY            + "><"                                             + \
      MASTER_KEY           + " "                                              + \
        CHANNELNAME_KEY    + "=\"" + String(MASTER_KEY)               + "\" " + \
        VOLUME_KEY         + "=\"" + String(DEFAULT_VOLUME)           + "\" " + \
        PAN_KEY            + "=\"" + String(DEFAULT_PAN)              + "\" " + \
        IS_MUTED_KEY       + "=\"" + String(DEFAULT_IS_MUTED)         + "\" " + \
    "/><"                                                                     + \
      METRO_KEY            + " "                                              + \
        CHANNELNAME_KEY    + "=\"" + String(METRO_KEY)                + "\" " + \
        VOLUME_KEY         + "=\"" + String(DEFAULT_VOLUME)           + "\" " + \
        PAN_KEY            + "=\"" + String(DEFAULT_PAN)              + "\" " + \
        IS_MUTED_KEY       + "=\"" + String(DEFAULT_IS_MUTED)         + "\" " + \
        SOURCE_N_KEY       + "=\"" + String(DEFAULT_SOURCE_N)         + "\" " + \
        IS_STEREO_KEY      + "=\"" + String(DEFAULT_IS_STEREO)        + "\" " + \
    "/>"                                                                      + \
    "</" + MASTERS_KEY     + "><"                                             + \
    LOCALS_KEY             + " /><"                                           + \
    REMOTES_KEY            + " />"                                            + \
  "</" + PERSISTENCE_KEY   + ">"

#define CONFIG_TYPES_XML "<?xml version=\"1.0\"?><"          + \
  PERSISTENCE_TYPES_KEY        + "><"                        + \
    CLIENT_KEY                 + " "                         + \
      SAVE_AUDIO_KEY           + "=\"" + INT_TYPE    + "\" " + \
      SAVE_LOG_KEY             + "=\"" + BOOL_TYPE   + "\" " + \
      DEBUGLEVEL_KEY           + "=\"" + INT_TYPE    + "\" " + \
      AUTOSUBSCRIBE_KEY        + "=\"" + INT_TYPE    + "\" " + \
    "/><"                                                    + \
    AUDIO_KEY                  + " "                         + \
      AUDIO_IF_KEY             + "=\"" + INT_TYPE    + "\" " + \
      N_INPUTS_KEY             + "=\"" + INT_TYPE    + "\" " + \
      N_OUTPUTS_KEY            + "=\"" + INT_TYPE    + "\" " + \
      BITDEPTH_KEY             + "=\"" + INT_TYPE    + "\" " + \
      SAMPLERATE_KEY           + "=\"" + INT_TYPE    + "\" " + \
      JACK_NAME_KEY            + "=\"" + STRING_TYPE + "\" " + \
    "/><"                                                    + \
    SERVER_KEY                 + " "                         + \
      HOST_KEY                 + "=\"" + STRING_TYPE + "\" " + \
      LOGIN_KEY                + "=\"" + STRING_TYPE + "\" " + \
      PASS_KEY                 + "=\"" + STRING_TYPE + "\" " + \
      IS_ANON_KEY              + "=\"" + BOOL_TYPE   + "\" " + \
      IS_AGREED_KEY            + "=\"" + BOOL_TYPE   + "\" " + \
      SHOULD_AGREE_KEY         + "=\"" + BOOL_TYPE   + "\" " + \
      SHOULD_HIDE_BOTS_KEY     + "=\"" + BOOL_TYPE   + "\" " + \
    "/><"                                                    + \
    CHANNELS_KEY               + " "                         + \
      CHANNELNAME_KEY          + "=\"" + STRING_TYPE + "\" " + \
      CHANNELIDX_KEY           + "=\"" + INT_TYPE    + "\" " + \
      VOLUME_KEY               + "=\"" + DOUBLE_TYPE + "\" " + \
      PAN_KEY                  + "=\"" + DOUBLE_TYPE + "\" " + \
      IS_XMIT_RCV_KEY          + "=\"" + BOOL_TYPE   + "\" " + \
      IS_MUTED_KEY             + "=\"" + BOOL_TYPE   + "\" " + \
      IS_SOLO_KEY              + "=\"" + BOOL_TYPE   + "\" " + \
      SOURCE_N_KEY             + "=\"" + INT_TYPE    + "\" " + \
      IS_STEREO_KEY            + "=\"" + BOOL_TYPE   + "\" " + \
    "/><"                                                    + \
    USERS_KEY                  + " "                         + \
      USERIDX_KEY              + "=\"" + INT_TYPE    + "\" " + \
    "/>"                                                     + \
  "</" + PERSISTENCE_TYPES_KEY + ">"


namespace CLIENT
{
  // client
  static const String SERVER_FULL_STATUS = "server full" ;
  static const int    BOT_USERIDX        = 0 ;
  static const int    BOT_CHANNELIDX     = 0 ;
  static const uint8  CHATMSG_TYPE_IDX   = 0 ;
  static const uint8  CHATMSG_USER_IDX   = 1 ;
  static const uint8  CHATMSG_MSG_IDX    = 2 ;

  // chat
  static const String    CHATMSG_TYPE_TOPIC   = "TOPIC" ;
  static const String    CHATMSG_TYPE_MSG     = "MSG" ;
  static const String    CHATMSG_TYPE_PRIVMSG = "PRIVMSG" ;
  static const String    CHATMSG_TYPE_JOIN    = "JOIN" ;
  static const String    CHATMSG_TYPE_PART    = "PART" ;
  static const String    CHATMSG_TYPE_ADMIN   = "ADMIN" ;
  static const String    CHATMSG_CMD_ME       = "/me " ;
  static const String    CHATMSG_CMD_MSG      = "/msg " ;
  static const String    CHATMSG_CMD_TOPIC    = "/topic " ;
  static const String    CHATMSG_CMD_KICK     = "/kick " ;
  static const String    CHATMSG_CMD_BPM      = "/bpm " ;
  static const String    CHATMSG_CMD_BPI      = "/bpi " ;
  static const String    CHATMSG_CMD_ADMIN    = "/admin " ;
  static const StringRef CHATMSG_CMD_VOTE     = "!vote " ;

  // main
  static const int CLIENT_TIMER_ID = 0 ; static const int CLIENT_DRIVER_IVL = 50 ;
  static const int GUI_TIMER_HI_ID = 1 ; static const int GUI_UPDATE_HI_IVL = 125 ;
  static const int GUI_TIMER_LO_ID = 2 ; static const int GUI_UPDATE_LO_IVL = 30000 ;

  // config
  static const uint8  MASTER_IDX             = 42 ;
  static const String STEREO_L_POSTFIX       = "-L" ;
  static const String STEREO_R_POSTFIX       = "-R" ;
  static const int    STEREO_POSTFIX_N_CHARS = STEREO_L_POSTFIX.length() ;
}


namespace NETWORK
{
  // known hosts
  static const String            NINJAM_2049_URL            = "test-ninjam-com-2049" ;
  static const String            NINJAM_2050_URL            = "test.ninjam.com:2050" ;
  static const String            NINJAM_2051_URL            = "test.ninjam.com:2051" ;
  static const String            NINJAM_2052_URL            = "test.ninjam.com:2052" ;
  static const String            NINJAM_2600_URL            = "test.ninjam.com:2600" ;
  static const String            NINJAM_2601_URL            = "test.ninjam.com:2601" ;
  static const String            NINBOT_2049_URL            = "ninbot.com:2049" ;
  static const String            NINBOT_2050_URL            = "ninbot.com:2050" ;
  static const String            NINBOT_2051_URL            = "ninbot.com:2051" ;
  static const String            NINBOT_2052_URL            = "ninbot.com:2052" ;
  static const String            NINJAMER_2049_URL          = "ninjamer.com:2049" ;
  static const String            NINJAMER_2050_URL          = "ninjamer.com:2050" ;
  static const String            NINJAMER_2051_URL          = "ninjamer.com:2051" ;
  static const String            NINJAMER_2052_URL          = "ninjamer.com:2052" ;
  static const Identifier        NINBOT_USER                = "ninbot" ;
  static const Identifier        JAMBOT_USER                = "Jambot" ;
  static const int               N_KNOWN_BOTS               = 2 ;
#ifndef DEBUG_LOCALHOST_LOGIN_BUTTON
  static const int               N_KNOWN_HOSTS              = 8 ;
  static const String            known_hosts[N_KNOWN_HOSTS] = {
#else // DEBUG_LOCALHOST_LOGIN_BUTTON
  static const int               N_KNOWN_HOSTS              = 9 ;
  static const String            LOCALHOST_2049_URL         = "localhost:2049" ;
  static const String            known_hosts[N_KNOWN_HOSTS] = {
                                     LOCALHOST_2049_URL       ,
#endif // DEBUG_LOCALHOST_LOGIN_BUTTON
                                     NINBOT_2049_URL          ,
                                     NINBOT_2050_URL          ,
                                     NINBOT_2051_URL          ,
                                     NINBOT_2052_URL          ,
                                     NINJAMER_2049_URL        ,
                                     NINJAMER_2050_URL        ,
                                     NINJAMER_2051_URL        ,
                                     NINJAMER_2052_URL        } ;
  static const Identifier        known_bots[N_KNOWN_BOTS]   = {
                                     NINBOT_USER              ,
                                     JAMBOT_USER              } ;
  static const Array<String>     KNOWN_HOSTS                =
               Array<String>(    known_hosts , N_KNOWN_HOSTS) ;
  static const Array<Identifier> KNOWN_BOTS                 =
               Array<Identifier>(known_bots  , N_KNOWN_BOTS) ;

  // login
  static const StringRef HOST_MASK = "*.*:*" ;
  static const StringRef LETTERS   = "abcdefghijklmnopqrstuvwxyz" ;
  static const StringRef DIGITS    = "0123456789" ;
  static const StringRef URL_CHARS = "0123456789abcdefghijklmnopqrstuvwxyz-." ;
}


namespace CONFIG
{
// NOTE: many of these *_KEY *_ID pairs maybe redundant or unused (issue #30)

  // config root keys
  static const String     PERSISTENCE_FILENAME  = "linjam.xml" ;
  static const String     PERSISTENCE_KEY       = "linjam-data" ;
  static const Identifier PERSISTENCE_ID        = PERSISTENCE_KEY ;
  static const String     PERSISTENCE_TYPES_KEY = PERSISTENCE_KEY + "-types" ;

  // client config keys
  static const String     CLIENT_KEY        = "client" ;
  static const Identifier CLIENT_ID         = CLIENT_KEY ;
  static const String     SAVE_AUDIO_KEY    = "save-audio" ;
  static const Identifier SAVE_AUDIO_ID     = SAVE_AUDIO_KEY ;
  static const String     SAVE_LOG_KEY      = "should-save-log" ;
  static const Identifier SAVE_LOG_ID       = SAVE_LOG_KEY ;
  static const String     DEBUGLEVEL_KEY    = "debug-level" ;
  static const Identifier DEBUGLEVEL_ID     = DEBUGLEVEL_KEY ;
  static const String     AUTOSUBSCRIBE_KEY = "should-subscribe" ;
  static const Identifier AUTOSUBSCRIBE_ID  = AUTOSUBSCRIBE_KEY ;
  static const String     SESSIONDIR_KEY    = "session-dir" ;
  static const Identifier SESSIONDIR_ID     = SESSIONDIR_KEY ;
  static const String     LOGFILE_KEY       = "log-file" ;
  static const Identifier LOGFILE_ID        = LOGFILE_KEY ;
  static const String     SESSIONDIR        = "/session" ;
  static const String     LOGFILE           = "/clipsort.log" ;
  static const String     SUBSCRIPTIONS_KEY = "subscriptions" ;
  static const Identifier SUBSCRIPTIONS_ID  = SUBSCRIPTIONS_KEY ;

  // device config keys
  static const String     AUDIO_KEY      = "audio" ;
  static const Identifier AUDIO_ID       = AUDIO_KEY ;
  static const String     AUDIO_IF_KEY   = "audio-if-n" ;
  static const Identifier AUDIO_IF_ID    = AUDIO_IF_KEY ;
  static const String     N_INPUTS_KEY   = "n-inputs" ;
  static const Identifier N_INPUTS_ID    = N_INPUTS_KEY ;
  static const String     N_OUTPUTS_KEY  = "n-outputs" ;
  static const Identifier N_OUTPUTS_ID   = N_OUTPUTS_KEY ;
  static const String     BITDEPTH_KEY   = "bit-depth" ;
  static const Identifier BITDEPTH_ID    = BITDEPTH_KEY ;
  static const String     SAMPLERATE_KEY = "sample-rate" ;
  static const Identifier SAMPLERATE_ID  = SAMPLERATE_KEY ;
  static const String     JACK_NAME_KEY  = "jack-name" ;
  static const Identifier JACK_NAME_ID   = JACK_NAME_KEY ;

  // network config keys
  static const String     SERVER_KEY           = "server" ;
  static const Identifier SERVER_ID            = SERVER_KEY ;
  static const String     HOST_KEY             = "host" ;
  static const Identifier HOST_ID              = HOST_KEY ;
  static const String     LOGIN_KEY            = "login" ;
  static const Identifier LOGIN_ID             = LOGIN_KEY ;
  static const String     PASS_KEY             = "pass" ;
  static const Identifier PASS_ID              = PASS_KEY ;
  static const String     IS_ANON_KEY          = "is-anonymous" ;
  static const Identifier IS_ANON_ID           = IS_ANON_KEY ;
  static const String     IS_AGREED_KEY        = "is-agreed" ;
  static const Identifier IS_AGREED_ID         = IS_AGREED_KEY ;
  static const String     SHOULD_AGREE_KEY     = "should-agree" ;
  static const Identifier SHOULD_AGREE_ID      = SHOULD_AGREE_KEY ;
  static const String     SHOULD_HIDE_BOTS_KEY = "should-hide-bots" ;
  static const Identifier SHOULD_HIDE_BOTS_ID  = SHOULD_HIDE_BOTS_KEY ;
  static const String     SERVERS_KEY          = "servers" ;
  static const Identifier SERVERS_ID           = SERVERS_KEY ;

  // channel config keys
  static const Identifier CONFIG_ALL_ID   = "configure-all" ;
  static const String     MASTERS_KEY     = "master-channels" ;
  static const Identifier MASTERS_ID      = MASTERS_KEY ;
  static const String     MASTER_KEY      = "master" ;
  static const Identifier MASTER_ID       = MASTER_KEY ;
  static const String     METRO_KEY       = "metronome" ;
  static const Identifier METRO_ID        = METRO_KEY ;
  static const String     LOCALS_KEY      = "local-channels" ;
  static const Identifier LOCALS_ID       = LOCALS_KEY ;
  static const String     REMOTES_KEY     = "remote-channels" ;
  static const Identifier REMOTES_ID      = REMOTES_KEY ;
  static const String     USERIDX_KEY     = "user-idx" ;
  static const Identifier USERIDX_ID      = USERIDX_KEY ;
  static const String     CHANNELIDX_KEY  = "channel-idx" ;
  static const Identifier CHANNELIDX_ID   = CHANNELIDX_KEY ;
  static const String     CHANNELNAME_KEY = "channel-name" ;
  static const Identifier CHANNELNAME_ID  = CHANNELNAME_KEY ;
  static const String     VOLUME_KEY      = "volume" ;
  static const Identifier VOLUME_ID       = VOLUME_KEY ;
  static const String     PAN_KEY         = "pan" ;
  static const Identifier PAN_ID          = PAN_KEY ;
  static const String     IS_XMIT_RCV_KEY = "should-xmit-rcv" ;
  static const Identifier IS_XMIT_RCV_ID  = IS_XMIT_RCV_KEY ;
  static const String     IS_MUTED_KEY    = "is-muted" ;
  static const Identifier IS_MUTED_ID     = IS_MUTED_KEY ;
  static const String     IS_SOLO_KEY     = "is-solo" ;
  static const Identifier IS_SOLO_ID      = IS_SOLO_KEY ;
  static const String     SOURCE_N_KEY    = "source-channel-n" ;
  static const Identifier SOURCE_N_ID     = SOURCE_N_KEY ;
  static const String     IS_STEREO_KEY   = "is-stereo" ;
  static const Identifier IS_STEREO_ID    = IS_STEREO_KEY ;

  // client config defaults
  static const int  DEFAULT_SAVE_AUDIO    = -1 ;
  static const bool DEFAULT_SAVE_LOG      = false ;
  static const int  DEFAULT_DEBUGLEVEL    = 0 ;
  static const int  DEFAULT_AUTOSUBSCRIBE = 1 ;

  // audio config defaults
  static const int    DEFAULT_AUDIO_IF   = 0 ;
  static const int    DEFAULT_N_INPUTS   = 2 ;
  static const int    DEFAULT_N_OUTPUTS  = 2 ;
  static const int    DEFAULT_BITDEPTH   = 16 ;
  static const int    DEFAULT_SAMPLERATE = 48000 ;
  static const String DEFAULT_JACK_NAME  = "LinJam" ;

  // login config defaults
  static const String DEFAULT_HOST             = "" ;
  static const String DEFAULT_LOGIN            = "" ;
  static const String DEFAULT_PASS             = "" ;
  static const bool   DEFAULT_IS_ANON          = true ;
  static const bool   DEFAULT_IS_AGREED        = false ;
  static const bool   DEFAULT_SHOULD_AGREE     = false ;
  static const bool   DEFAULT_SHOULD_HIDE_BOTS = true ;

  // channel config defaults
  static const Identifier NEWCHANNEL_ID        = "new-channel" ;
  static const String     CHANNEL_BASE_ID      = "channel" ;
  static const String     DEFAULT_CHANNEL_NAME = "unnamed" ;
  static const String     CHANNELS_KEY         = "channels" ;
  static const Identifier CHANNELS_ID          = CHANNELS_KEY ;
  static const String     USERS_KEY            = "users" ;
  static const Identifier USERS_ID             = USERS_KEY ;
  static const float      DEFAULT_VOLUME       = 0.0 ;
  static const float      DEFAULT_PAN          = 0.0 ;
  static const bool       DEFAULT_IS_XMIT_RCV  = true ;
  static const bool       DEFAULT_IS_MUTED     = false ;
  static const bool       DEFAULT_IS_SOLO      = false ;
  static const int        DEFAULT_SOURCE_N     = 0 ;
  static const bool       DEFAULT_IS_STEREO    = false ;

  // config types
  static const String BOOL_TYPE   = "bool" ;
  static const String DOUBLE_TYPE = "double" ;
  static const String INT_TYPE    = "int" ;
  static const String STRING_TYPE = "string" ;

  // validation
  static const StringRef VALID_NAME_CHARS   = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_- " ;
  static const StringRef USER_IP_SPLIT_CHAR = "@" ;

  // config storage
  static const String DEFAULT_CONFIG_XML = String(CONFIG_XML) ;
  static const String CONFIG_TYPES       = String(CONFIG_TYPES_XML) ;
/*
  static const ValueTree DEFAULT_CONFIG     = ValueTree(PERSISTENCE_DEFAULTS_ID) ;
               ValueTree client_defaults    = ValueTree(CLIENT_ID) ;
               ValueTree audio_defaults     = ValueTree(AUDIO_ID) ;
               ValueTree server_defaults    = ValueTree(SERVER_ID) ;
               ValueTree channel_defaults   = ValueTree(CHANNELS_ID) ;
  CONFIG::DEFAULT_CONFIG.addChild(client_defaults  , -1 , nullptr) ;
  CONFIG::DEFAULT_CONFIG.addChild(audio_defaults   , -1 , nullptr) ;
  CONFIG::DEFAULT_CONFIG.addChild(server_defaults  , -1 , nullptr) ;
  CONFIG::DEFAULT_CONFIG.addChild(channel_defaults , -1 , nullptr) ;
  client_defaults .setProperty(SAVE_AUDIO_ID        , DEFAULT_SAVE_AUDIO       , nullptr) ;
  client_defaults .setProperty(SAVE_LOG_ID          , DEFAULT_SAVE_LOG         , nullptr) ;
  client_defaults .setProperty(DEBUGLEVEL_ID        , DEFAULT_DEBUGLEVEL       , nullptr) ;
  client_defaults .setProperty(AUTOSUBSCRIBE_ID     , DEFAULT_AUTOSUBSCRIBE    , nullptr) ;
  audio_defaults  .setProperty(AUDIO_IF_ID          , DEFAULT_AUDIO_IF         , nullptr) ;
  audio_defaults  .setProperty(N_INPUTS_ID          , DEFAULT_N_INPUTS         , nullptr) ;
  audio_defaults  .setProperty(N_OUTPUTS_ID         , DEFAULT_N_OUTPUTS        , nullptr) ;
  audio_defaults  .setProperty(BITDEPTH_ID          , DEFAULT_BITDEPTH         , nullptr) ;
  audio_defaults  .setProperty(SAMPLERATE_ID        , DEFAULT_SAMPLERATE       , nullptr) ;
  audio_defaults  .setProperty(JACK_NAME_ID         , DEFAULT_JACK_NAME        , nullptr) ;
  server_defaults .setProperty(HOST_ID              , DEFAULT_HOST             , nullptr) ;
  server_defaults .setProperty(LOGIN_ID             , DEFAULT_LOGIN            , nullptr) ;
  server_defaults .setProperty(PASS_ID              , DEFAULT_PASS             , nullptr) ;
  server_defaults .setProperty(IS_ANON_ID           , DEFAULT_IS_ANON          , nullptr) ;
  server_defaults .setProperty(IS_AGREED_ID         , DEFAULT_IS_AGREED        , nullptr) ;
  server_defaults .setProperty(SHOULD_HIDE_BOTS_KEY , DEFAULT_SHOULD_HIDE_BOTS , nullptr) ;
  channel_defaults.setProperty(CHANNELNAME_ID       , DEFAULT_CHANNEL_NAME     , nullptr) ;
  channel_defaults.setProperty(CHANNELIDX_ID        , 42                       , nullptr) ;
  channel_defaults.setProperty(VOLUME_ID            , DEFAULT_VOLUME           , nullptr) ;
  channel_defaults.setProperty(PAN_ID               , DEFAULT_PAN              , nullptr) ;
  channel_defaults.setProperty(IS_XMIT_RCV_ID       , DEFAULT_IS_XMIT_RCV      , nullptr) ;
  channel_defaults.setProperty(IS_MUTED_ID          , DEFAULT_IS_MUTED         , nullptr) ;
  channel_defaults.setProperty(IS_SOLO_ID           , DEFAULT_IS_SOLO          , nullptr) ;
  channel_defaults.setProperty(SOURCE_N_ID          , DEFAULT_SOURCE_N         , nullptr) ;
  channel_defaults.setProperty(IS_STEREO_ID         , DEFAULT_IS_STEREO        , nullptr) ;
*/
}


namespace GUI
{
  // common
  static const int PAD  = 4 ;
  static const int PAD2 = PAD * 2 ;
  static const int PAD3 = PAD * 3 ;
  static const int PAD4 = PAD * 4 ;

  // Main
  static const int    BORDERS_W                     = 2 ;
  static const int    TITLEBAR_H                    = 24 ;
  static const String AUDIO_INIT_ERROR_MSG          = "audio device error" ;
  static const String DISCONNECTED_STATUS_TEXT      = "Disconnected" ;
  static const String ROOM_FULL_STATUS_TEXT         = "Jam room full" ;
  static const String INVALID_AUTH_STATUS_TEXT      = "Invalid login/pass" ;
  static const String PENDING_LICENSE_STATUS_TEXT   = "Pending license" ;
  static const String FAILED_CONNECTION_STATUS_TEXT = "Connection failed" ;
  static const String CONNECTING_STATUS_TEXT        = "Connecting to " ;
  static const String CONNECTED_STATUS_TEXT         = "Connected to " ;
  static const String IDLE_STATUS_TEXT              = "Idle" ;
  static const String UNKNOWN_STATUS_TEXT           = "Status: " ;

  // MainContent
  static const String CONTENT_GUI_ID = "main-content-gui" ;
  static const int    CONTENT_W      = 640 - BORDERS_W ;
  static const int    CONTENT_H      = 480 - BORDERS_W - TITLEBAR_H ;

  // Background
  static const String BACKGROUND_GUI_ID = "background-gui" ;

  // Login
  static const String LOGIN_GUI_ID   = "login-gui" ;
  static const int    LOGIN_BUTTON_L = GUI::PAD ;
  static const int    LOGIN_BUTTON_T = GUI::PAD ;
  static const int    LOGIN_BUTTON_W = 96 ;
  static const int    LOGIN_BUTTON_H = 24 ;

  // License
  static const String LICENSE_GUI_ID = "license-gui" ;

  // Chat
  static const String CHAT_GUI_ID           = "chat-gui" ;
  static const String SERVER_NICK           = "NINJAM" ;
  static const String TOPIC_TEXT            = "Topic is: " ;
  static const String SET_TOPIC_TEXT        = " sets topic to: " ;
  static const String PM_TEXT               = " (whispers)" ;
  static const String JOINPART_TEXTa        = " has " ;
  static const String JOIN_TEXT             = "joined" ;
  static const String PART_TEXT             = "left" ;
  static const String JOINPART_TEXTb        = " the jam" ;
  static const String UNKNOWN_COMMAND_MSG   = "Error: unknown command" ;
  static const String INVALID_PM_MSG        = "Error: /msg requires a username and a message" ;
  static const int    TOPIC_H               = 16 ;
  static const int    TOPIC_PADDED_H        = TOPIC_H + PAD2 ;
  static const int    MIN_SHOW_TOPIC_CHAT_H = 200 ;

  // Channel
  static const Identifier MASTER_GUI_ID          = CONFIG::MASTER_ID ;
  static const Identifier METRO_GUI_ID           = CONFIG::METRO_ID ;
  static const String XMIT_LABEL_TEXT            = "XMIT" ;
  static const String RCV_LABEL_TEXT             = "RCV" ;
  static const int    N_STATIC_CHANNELS_CHILDREN = 2 ;
  static const int    CHANNEL_LABEL_H            = 12 ;
  static const int    CHANNEL_Y                  = CHANNEL_LABEL_H + PAD2 ;
  static const int    CHANNEL_W                  = 60 ;
  static const int    CHANNEL_H                  = 252 ;
  static const int    CONFIG_BTN_W               = 15 ;
  static const int    CONFIG_BTN_H               = 16 ;
  static const int    VU_DB_RANGE                = 140 ;
  static const int    VU_DB_MIN                  = -120 ;

  // Channels
  static const  String     MASTERS_LABEL_TEXT = "Master" ;
  static const  String     LOCALS_LABEL_TEXT  = "Local" ;
  static const  Identifier MASTERS_GUI_ID     = CONFIG::MASTERS_ID ;
  static const  Identifier LOCALS_GUI_ID      = CONFIG::LOCALS_ID ;
  static const  int        CHANNEL_CONFIG_W   = 200 ;
  static const  int        CHANNEL_CONFIG_H   = 200 ;
  static const  int        EXPAND_BTN_W       = 15 ;
  static const  int        EXPAND_BTN_H       = 16 ;
  static const  int        EXPAND_BTN_XC      = EXPAND_BTN_W / 2 ;
  static const  int        EXPAND_BTN_YC      = EXPAND_BTN_H / 2 ;
  static const  int        MIXERGROUP_Y       = PAD ;
  static const  int        MIXERGROUP_H       = CHANNEL_H + CHANNEL_LABEL_H + PAD3 ;
  static inline int        MIXERGROUP_W(int n_channels)
  {
    return PAD + (n_channels * (CHANNEL_W + PAD)) ;
  }

  // Mixer
  static const String MIXER_GUI_ID            = "mixer-gui" ;
  static const int    MIXER_H                 = PAD2 + MIXERGROUP_H ;
  static const int    RESIZER_W               = PAD  + 2 ;
  static const int    N_STATIC_MIXER_CHILDREN = 5 ;
  static const int    LOCALS_IDX              = 0 ;
  static const int    FIRST_REMOTE_IDX        = 1 ;
  static const int    CHANNEL_SCROLL_BTN_H    = MIXERGROUP_H / 4 ;
  static const int    CHANNEL_SCROLL_BTN_W    = 24 ;
  static const int    CHANNEL_SCROLL_BTN_Y    = MIXERGROUP_Y +
                                               (MIXERGROUP_H / 2) -
                                               (CHANNEL_SCROLL_BTN_H / 2) ;

  // StatusBar
  static const String STATUS_GUI_ID = "statusbar-gui" ;
  static const int    STATUSBAR_H   = 24 ;
  static const int    STATUS_W      = 160 ;
  static const int    STATUS_H      = 16 ;
  static const int    STATUS_PAD_X  = 8 ;
  static const int    STATUS_PAD_Y  = 2 ;

  // Loop
  static const String LOOP_GUI_ID          = "loop-gui" ;
  static const int    LOOP_X               = STATUS_W + PAD3 ;
  static const int    LOOP_H               = STATUS_H ;
  static const float  BEAT_PROGRESS_OFFSET = CLIENT::GUI_UPDATE_HI_IVL * 0.002 ;
}

#endif // _CONSTANTS_H_
