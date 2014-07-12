
#include "Constants.h"


/* CLIENT class public class constants */

// client
const String CLIENT::SERVER_FULL_STATUS   = "server full" ;

// chat
const String    CLIENT::CHATMSG_TYPE_TOPIC   = "TOPIC" ;
const String    CLIENT::CHATMSG_TYPE_MSG     = "MSG" ;
const String    CLIENT::CHATMSG_TYPE_PRIVMSG = "PRIVMSG" ;
const String    CLIENT::CHATMSG_TYPE_JOIN    = "JOIN" ;
const String    CLIENT::CHATMSG_TYPE_PART    = "PART" ;
const String    CLIENT::CHATMSG_TYPE_ADMIN   = "ADMIN" ;
const String    CLIENT::CHATMSG_CMD_ME    = "/me " ;
const String    CLIENT::CHATMSG_CMD_MSG   = "/msg " ;
const String    CLIENT::CHATMSG_CMD_TOPIC = "/topic " ;
const String    CLIENT::CHATMSG_CMD_KICK  = "/kick " ;
const String    CLIENT::CHATMSG_CMD_BPM   = "/bpm " ;
const String    CLIENT::CHATMSG_CMD_BPI   = "/bpi " ;
const String    CLIENT::CHATMSG_CMD_ADMIN = "/admin " ;
const StringRef CLIENT::CHATMSG_CMD_VOTE  = "!vote " ;

// audio
char* CLIENT::WIN_INI_FILE = "linjam.ini" ;

// config
const String CLIENT::STEREO_L_POSTFIX = "-L" ;
const String CLIENT::STEREO_R_POSTFIX = "-R" ;


/* NETWORK class public class constants */

// known hosts
const String        NETWORK::NINJAM_2049_URL            = "test-ninjam-com-2049" ;
const String        NETWORK::NINJAM_2050_URL            = "test.ninjam.com:2050" ;
const String        NETWORK::NINJAM_2051_URL            = "test.ninjam.com:2051" ;
const String        NETWORK::NINJAM_2052_URL            = "test.ninjam.com:2052" ;
const String        NETWORK::NINJAM_2600_URL            = "test.ninjam.com:2600" ;
const String        NETWORK::NINJAM_2601_URL            = "test.ninjam.com:2601" ;
const String        NETWORK::NINBOT_2049_URL            = "ninbot.com:2049" ;
const String        NETWORK::NINBOT_2050_URL            = "ninbot.com:2050" ;
const String        NETWORK::NINBOT_2051_URL            = "ninbot.com:2051" ;
const String        NETWORK::NINBOT_2052_URL            = "ninbot.com:2052" ;
const String        NETWORK::NINJAMER_2049_URL          = "ninjamer.com:2049" ;
const String        NETWORK::NINJAMER_2050_URL          = "ninjamer.com:2050" ;
const String        NETWORK::NINJAMER_2051_URL          = "ninjamer.com:2051" ;
const String        NETWORK::NINJAMER_2052_URL          = "ninjamer.com:2052" ;
const Identifier    NETWORK::NINBOT_USER                = "ninbot" ;
const Identifier    NETWORK::JAMBOT_USER                = "Jambot" ;
#ifndef DEBUG_LOCALHOST_LOGIN_BUTTON
const String        known_hosts[NETWORK::N_KNOWN_HOSTS] = {
#else // DEBUG_LOCALHOST_LOGIN_BUTTON
const String        NETWORK::LOCALHOST_2049_URL         = "localhost:2049" ;
const String        known_hosts[NETWORK::N_KNOWN_HOSTS] = {
                        NETWORK::LOCALHOST_2049_URL       ,
#endif // DEBUG_LOCALHOST_LOGIN_BUTTON
                        NETWORK::NINBOT_2049_URL          ,
                        NETWORK::NINBOT_2050_URL          ,
                        NETWORK::NINBOT_2051_URL          ,
                        NETWORK::NINBOT_2052_URL          ,
                        NETWORK::NINJAMER_2049_URL        ,
                        NETWORK::NINJAMER_2050_URL        ,
                        NETWORK::NINJAMER_2051_URL        ,
                        NETWORK::NINJAMER_2052_URL        } ;
const Identifier    known_bots[NETWORK::N_KNOWN_BOTS]   = {
                        NETWORK::NINBOT_USER              ,
                        NETWORK::JAMBOT_USER              } ;
const Array<String>     NETWORK::KNOWN_HOSTS            =
      Array<String>(    known_hosts , NETWORK::N_KNOWN_HOSTS) ;
const Array<Identifier> NETWORK::KNOWN_BOTS             =
      Array<Identifier>(known_bots  , NETWORK::N_KNOWN_BOTS) ;

// login
const StringRef NETWORK::HOST_MASK = "*.*:*" ;
const StringRef NETWORK::LETTERS   = "abcdefghijklmnopqrstuvwxyz" ;
const StringRef NETWORK::DIGITS    = "0123456789" ;
const StringRef NETWORK::URL_CHARS = "0123456789abcdefghijklmnopqrstuvwxyz-." ;


/* GUI class public class constants */

// main
const String GUI::AUDIO_INIT_ERROR_MSG          = "audio device error" ;
const String GUI::DISCONNECTED_STATUS_TEXT      = "Disconnected" ;
const String GUI::ROOM_FULL_STATUS_TEXT         = "Jam room full" ;
const String GUI::INVALID_AUTH_STATUS_TEXT      = "Invalid login/pass" ;
const String GUI::PENDING_LICENSE_STATUS_TEXT   = "Pending license" ;
const String GUI::FAILED_CONNECTION_STATUS_TEXT = "Connection failed" ;
const String GUI::CONNECTING_STATUS_TEXT        = "Connecting to " ;
const String GUI::CONNECTED_STATUS_TEXT         = "Connected to " ;
const String GUI::IDLE_STATUS_TEXT              = "Idle" ;
const String GUI::UNKNOWN_STATUS_TEXT           = "Status: " ;

// MainContent
const String GUI::CONTENT_GUI_ID = "main-content-gui" ;

// Background
const String GUI::BACKGROUND_GUI_ID = "background-gui" ;

// Login
const String GUI::LOGIN_GUI_ID = "login-gui" ;

// License
const String GUI::LICENSE_GUI_ID = "license-gui" ;

// Chat
const String GUI::CHAT_GUI_ID         = "chat-gui" ;
const String GUI::SERVER_NICK         = "NINJAM" ;
const String GUI::TOPIC_TEXT          = "Topic is: " ;
const String GUI::SET_TOPIC_TEXT      = " sets topic to: " ;
const String GUI::PM_TEXT             = " (whispers)" ;
const String GUI::JOINPART_TEXTa      = " has " ;
const String GUI::JOIN_TEXT           = "joined" ;
const String GUI::PART_TEXT           = "left" ;
const String GUI::JOINPART_TEXTb      = " the jam" ;
const String GUI::UNKNOWN_COMMAND_MSG = "Error: unknown command" ;
const String GUI::INVALID_PM_MSG      = "Error: /msg requires a username and a message" ;

// Channel
const String GUI::MASTER_CHANNEL_GUI_ID = "master" ;
const String GUI::METRO_CHANNEL_GUI_ID  = "metronome" ;
const String GUI::XMIT_LABEL_TEXT       = "XMIT" ;
const String GUI::RCV_LABEL_TEXT        = "RCV" ;

// Channels
const  String     GUI::MASTERS_GUI_ID = "Master" ;
const  Identifier GUI::MASTERS_ID     = MASTERS_GUI_ID ;
const  String     GUI::LOCALS_GUI_ID  = "Local" ;
const  Identifier GUI::LOCALS_ID      = LOCALS_GUI_ID ;

// Mixer
const String GUI::MIXER_GUI_ID = "mixer-gui" ;

// StatusBar
const String GUI::STATUS_GUI_ID = "statusbar-gui" ;

// Loop
const String GUI::LOOP_GUI_ID          = "loop-gui" ;
const float  GUI::BEAT_PROGRESS_OFFSET = CLIENT::GUI_UPDATE_HI_IVL * 0.002 ;


/* CONFIG class public class constants */

// NOTE: many of these *_KEY *_ID pairs maybe redundant or unused (issue #30)

// config root
const String     CONFIG::PERSISTENCE_FILENAME = "linjam.xml" ;
const String     CONFIG::PERSISTENCE_KEY      = "linjam-data" ;
const Identifier CONFIG::PERSISTENCE_ID       = PERSISTENCE_KEY ;

// client config
const String     CONFIG::CLIENT_KEY        = "client" ;
const Identifier CONFIG::CLIENT_ID         = CLIENT_KEY ;
const String     CONFIG::SAVE_AUDIO_KEY    = "should-save-audio" ;
const Identifier CONFIG::SAVE_AUDIO_ID     = SAVE_AUDIO_KEY ;
const String     CONFIG::SAVE_LOG_KEY      = "should-save-log" ;
const Identifier CONFIG::SAVE_LOG_ID       = SAVE_LOG_KEY ;
const String     CONFIG::DEBUGLEVEL_KEY    = "debug-level" ;
const Identifier CONFIG::DEBUGLEVEL_ID     = DEBUGLEVEL_KEY ;
const String     CONFIG::AUTOSUBSCRIBE_KEY = "should-subscribe" ;
const Identifier CONFIG::AUTOSUBSCRIBE_ID  = AUTOSUBSCRIBE_KEY ;
const String     CONFIG::SESSIONDIR_KEY    = "session-dir" ;
const Identifier CONFIG::SESSIONDIR_ID     = SESSIONDIR_KEY ;
const String     CONFIG::LOGFILE_KEY       = "log-file" ;
const Identifier CONFIG::LOGFILE_ID        = LOGFILE_KEY ;
const String     CONFIG::SESSIONDIR        = "/session" ;
const String     CONFIG::LOGFILE           = "/clipsort.log" ;
const String     CONFIG::SUBSCRIPTIONS_KEY = "subscriptions" ;
const Identifier CONFIG::SUBSCRIPTIONS_ID  = SUBSCRIPTIONS_KEY ;

// device config
const String     CONFIG::AUDIO_KEY      = "audio" ;
const Identifier CONFIG::AUDIO_ID       = AUDIO_KEY ;
const String     CONFIG::AUDIO_IF_KEY   = "audio-if-n" ;
const Identifier CONFIG::AUDIO_IF_ID    = AUDIO_IF_KEY ;
const String     CONFIG::N_INPUTS_KEY   = "n-inputs" ;
const Identifier CONFIG::N_INPUTS_ID    = N_INPUTS_KEY ;
const String     CONFIG::N_OUTPUTS_KEY  = "n-outputs" ;
const Identifier CONFIG::N_OUTPUTS_ID   = N_OUTPUTS_KEY ;
const String     CONFIG::BITDEPTH_KEY   = "bit-depth" ;
const Identifier CONFIG::BITDEPTH_ID    = BITDEPTH_KEY ;
const String     CONFIG::SAMPLERATE_KEY = "sample-rate" ;
const Identifier CONFIG::SAMPLERATE_ID  = SAMPLERATE_KEY ;
const String     CONFIG::JACK_NAME_KEY  = "jack-name" ;
const Identifier CONFIG::JACK_NAME_ID   = JACK_NAME_KEY ;

// network config
const String     CONFIG::SERVER_KEY  = "server" ;
const Identifier CONFIG::SERVER_ID   = SERVER_KEY ;
const String     CONFIG::HOST_KEY    = "host" ;
const Identifier CONFIG::HOST_ID     = HOST_KEY ;
const String     CONFIG::LOGIN_KEY   = "login" ;
const Identifier CONFIG::LOGIN_ID    = LOGIN_KEY ;
const String     CONFIG::PASS_KEY    = "pass" ;
const Identifier CONFIG::PASS_ID     = PASS_KEY ;
const String     CONFIG::ANON_KEY    = "is-anonymous" ;
const Identifier CONFIG::ANON_ID     = ANON_KEY ;
const String     CONFIG::AGREED_KEY  = "is-agreed" ;
const Identifier CONFIG::AGREED_ID   = AGREED_KEY ;
const String     CONFIG::AGREE_KEY   = "should-agree" ;
const Identifier CONFIG::AGREE_ID    = AGREE_KEY ;
const String     CONFIG::BOTS_KEY    = "should-hide-bots" ;
const Identifier CONFIG::BOTS_ID     = BOTS_KEY ;
const String     CONFIG::SERVERS_KEY = "servers" ;
const Identifier CONFIG::SERVERS_ID  = SERVERS_KEY ;

// channels
const Identifier CONFIG::CONFIG_ALL_ID   = "configure-all" ;
const String     CONFIG::MASTERS_KEY     = "master-channels" ;
const Identifier CONFIG::MASTERS_ID      = MASTERS_KEY ;
const String     CONFIG::MASTER_KEY      = GUI::MASTER_CHANNEL_GUI_ID ;
const Identifier CONFIG::MASTER_ID       = MASTER_KEY ;
const String     CONFIG::METRO_KEY       = GUI::METRO_CHANNEL_GUI_ID ;
const Identifier CONFIG::METRO_ID        = METRO_KEY ;
const String     CONFIG::LOCALS_KEY      = "local-channels" ;
const Identifier CONFIG::LOCALS_ID       = LOCALS_KEY ;
const String     CONFIG::REMOTES_KEY     = "remote-channels" ;
const Identifier CONFIG::REMOTES_ID      = REMOTES_KEY ;
const Identifier CONFIG::USERIDX_KEY     = "user-idx" ;
const Identifier CONFIG::USERIDX_ID      = USERIDX_KEY ;
const String     CONFIG::CHANNELIDX_KEY  = "channel-idx" ;
const Identifier CONFIG::CHANNELIDX_ID   = CHANNELIDX_KEY ;
const String     CONFIG::CHANNELNAME_KEY = "channel-name" ;
const Identifier CONFIG::CHANNELNAME_ID  = CHANNELNAME_KEY ;
const String     CONFIG::VOLUME_KEY      = "volume" ;
const Identifier CONFIG::VOLUME_ID       = VOLUME_KEY ;
const String     CONFIG::PAN_KEY         = "pan" ;
const Identifier CONFIG::PAN_ID          = PAN_KEY ;
const String     CONFIG::IS_XMIT_KEY     = "should-xmit-rcv" ;
const Identifier CONFIG::IS_XMIT_ID      = IS_XMIT_KEY ;
const String     CONFIG::IS_MUTED_KEY    = "is-muted" ;
const Identifier CONFIG::IS_MUTED_ID     = IS_MUTED_KEY ;
const String     CONFIG::IS_SOLO_KEY     = "is-solo" ;
const Identifier CONFIG::IS_SOLO_ID      = IS_SOLO_KEY ;
const String     CONFIG::SOURCE_N_KEY    = "source-channel-n" ;
const Identifier CONFIG::SOURCE_N_ID     = SOURCE_N_KEY ;
const String     CONFIG::IS_STEREO_KEY   = "is-stereo" ;
const Identifier CONFIG::IS_STEREO_ID    = IS_STEREO_KEY ;

// defaults
const String CONFIG::CHANNEL_BASE_ID      = "channel" ;
const String CONFIG::DEFAULT_CHANNEL_NAME = "unnamed" ;
const float  CONFIG::DEFAULT_VOLUME       = 0.0 ;
const float  CONFIG::DEFAULT_PAN          = 0.0 ;
const bool   CONFIG::DEFAULT_IS_XMIT      = true ;
const bool   CONFIG::DEFAULT_IS_MUTED     = false ;
const bool   CONFIG::DEFAULT_IS_SOLO      = false ;
const int    CONFIG::DEFAULT_SOURCE_N     = 0 ;
const bool   CONFIG::DEFAULT_IS_STEREO    = false ;

// validation
const StringRef CONFIG::VALID_NAME_CHARS   = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_- " ;
const StringRef CONFIG::USER_IP_SPLIT_CHAR = "@" ;

// NOTE: when adding nodes or leaves to CONFIG_XML be sure to
//         * verify them in   LinJamConfig::sanityCheck()
//         * dump them in     Trace::DEBUG_TRACE_SANITY_CHECK
//                            Trace::DEBUG_TRACE_SANITY_CHECK_CHANNEL
//                            Trace::DEBUG_TRACE_ADDED_CHANNEL
//                            Trace::TRACE_CONFIGURE_LOCAL_CHANNEL_VB
//                            Trace::DEBUG_TRACE_REMOTE_CHANNELS
//                            Trace::DEBUG_TRACE_CONFIGURE_REMOTE
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
const String CONFIG::DEFAULT_CONFIG_XML = String(CONFIG_XML) ;
