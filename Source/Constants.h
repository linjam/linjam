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
//         * note the datatype in   LinJamConfig.h
//         * verify them in         LinJamConfig::sanityCheck()
//         * dump them in           Trace::DEBUG_TRACE_SANITY_CHECK
//                                  Trace::DEBUG_TRACE_SANITY_CHECK_CHANNEL
//                                  Trace::DEBUG_TRACE_ADDED_CHANNEL
//                                  Trace::TRACE_CONFIGURE_LOCAL_CHANNEL_VB
//                                  Trace::DEBUG_TRACE_REMOTE_CHANNELS
//                                  Trace::DEBUG_TRACE_CONFIGURE_REMOTE
#define CONFIG_XML "<?xml version=\"1.0\"?><"              + \
    PERSISTENCE_KEY          + "><"                        + \
      CLIENT_KEY             + " "                         + \
        SAVE_AUDIO_KEY       + "=\"-1\" "                  + \
        SAVE_LOG_KEY         + "=\"false\" "               + \
        DEBUGLEVEL_KEY       + "=\"0\" "                   + \
        AUTOSUBSCRIBE_KEY    + "=\"1\" "                   + \
      "/><"                                                + \
      AUDIO_KEY              + " "                         + \
        AUDIO_IF_KEY         + "=\"0\" "                   + \
        N_INPUTS_KEY         + "=\"2\" "                   + \
        N_OUTPUTS_KEY        + "=\"2\" "                   + \
        BITDEPTH_KEY         + "=\"16\" "                  + \
        SAMPLERATE_KEY       + "=\"48000\" "               + \
        JACK_NAME_KEY        + "=\"linjam\" "              + \
      "/><"                                                + \
      SERVER_KEY             + " "                         + \
        HOST_KEY             + "=\"\" "                    + \
        LOGIN_KEY            + "=\"\" "                    + \
        PASS_KEY             + "=\"\" "                    + \
        ANON_KEY             + "=\"true\" "                + \
        AGREED_KEY           + "=\"false\" "               + \
        BOTS_KEY             + "=\"true\" "                + \
      "/><"                                                + \
      SERVERS_KEY            + " /><"                      + \
      SUBSCRIPTIONS_KEY      + " /><"                      + \
      MASTERS_KEY            + "><"                        + \
        MASTER_KEY           + " "                         + \
          CHANNELNAME_KEY    + "=\"" + MASTER_KEY + "\" "  + \
          VOLUME_KEY         + "=\"0.0\" "                 + \
          PAN_KEY            + "=\"0.0\" "                 + \
          IS_MUTED_KEY       + "=\"false\" "               + \
      "/><"                                                + \
        METRO_KEY            + " "                         + \
          CHANNELNAME_KEY    + "=\"" + METRO_KEY  + "\" "  + \
          VOLUME_KEY         + "=\"0.0\" "                 + \
          PAN_KEY            + "=\"0.0\" "                 + \
          IS_MUTED_KEY       + "=\"false\" "               + \
          SOURCE_N_KEY       + "=\"0\" "                   + \
          IS_STEREO_KEY      + "=\"true\" "                + \
      "/>"                                                 + \
      "</" + MASTERS_KEY     + "><"                        + \
      LOCALS_KEY             + " /><"                      + \
      REMOTES_KEY            + " />"                       + \
    "</" + PERSISTENCE_KEY   + ">"


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

  // config root
  static const String     PERSISTENCE_FILENAME = "linjam.xml" ;
  static const String     PERSISTENCE_KEY      = "linjam-data" ;
  static const Identifier PERSISTENCE_ID       = PERSISTENCE_KEY ;

  // client config
  static const String     CLIENT_KEY        = "client" ;
  static const Identifier CLIENT_ID         = CLIENT_KEY ;
  static const String     SAVE_AUDIO_KEY    = "should-save-audio" ;
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

  // device config
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

  // network config
  static const String     SERVER_KEY  = "server" ;
  static const Identifier SERVER_ID   = SERVER_KEY ;
  static const String     HOST_KEY    = "host" ;
  static const Identifier HOST_ID     = HOST_KEY ;
  static const String     LOGIN_KEY   = "login" ;
  static const Identifier LOGIN_ID    = LOGIN_KEY ;
  static const String     PASS_KEY    = "pass" ;
  static const Identifier PASS_ID     = PASS_KEY ;
  static const String     ANON_KEY    = "is-anonymous" ;
  static const Identifier ANON_ID     = ANON_KEY ;
  static const String     AGREED_KEY  = "is-agreed" ;
  static const Identifier AGREED_ID   = AGREED_KEY ;
  static const String     AGREE_KEY   = "should-agree" ;
  static const Identifier AGREE_ID    = AGREE_KEY ;
  static const String     BOTS_KEY    = "should-hide-bots" ;
  static const Identifier BOTS_ID     = BOTS_KEY ;
  static const String     SERVERS_KEY = "servers" ;
  static const Identifier SERVERS_ID  = SERVERS_KEY ;

  // channels
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
  static const Identifier USERIDX_KEY     = "user-idx" ;
  static const Identifier USERIDX_ID      = USERIDX_KEY ;
  static const String     CHANNELIDX_KEY  = "channel-idx" ;
  static const Identifier CHANNELIDX_ID   = CHANNELIDX_KEY ;
  static const String     CHANNELNAME_KEY = "channel-name" ;
  static const Identifier CHANNELNAME_ID  = CHANNELNAME_KEY ;
  static const String     VOLUME_KEY      = "volume" ;
  static const Identifier VOLUME_ID       = VOLUME_KEY ;
  static const String     PAN_KEY         = "pan" ;
  static const Identifier PAN_ID          = PAN_KEY ;
  static const String     IS_XMIT_KEY     = "should-xmit-rcv" ;
  static const Identifier IS_XMIT_ID      = IS_XMIT_KEY ;
  static const String     IS_MUTED_KEY    = "is-muted" ;
  static const Identifier IS_MUTED_ID     = IS_MUTED_KEY ;
  static const String     IS_SOLO_KEY     = "is-solo" ;
  static const Identifier IS_SOLO_ID      = IS_SOLO_KEY ;
  static const String     SOURCE_N_KEY    = "source-channel-n" ;
  static const Identifier SOURCE_N_ID     = SOURCE_N_KEY ;
  static const String     IS_STEREO_KEY   = "is-stereo" ;
  static const Identifier IS_STEREO_ID    = IS_STEREO_KEY ;

  // defaults
  static const Identifier NEWCHANNEL_ID        = "new-channel" ;
  static const String     CHANNEL_BASE_ID      = "channel" ;
  static const String     DEFAULT_CHANNEL_NAME = "unnamed" ;
  static const float      DEFAULT_VOLUME       = 0.0 ;
  static const float      DEFAULT_PAN          = 0.0 ;
  static const bool       DEFAULT_IS_XMIT      = true ;
  static const bool       DEFAULT_IS_MUTED     = false ;
  static const bool       DEFAULT_IS_SOLO      = false ;
  static const int        DEFAULT_SOURCE_N     = 0 ;
  static const bool       DEFAULT_IS_STEREO    = false ;

  // validation
  static const StringRef VALID_NAME_CHARS   = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_- " ;
  static const StringRef USER_IP_SPLIT_CHAR = "@" ;

  // config storage
  static const String DEFAULT_CONFIG_XML = String(CONFIG_XML) ;
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
