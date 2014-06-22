
#include "Constants.h"


/* CLIENT class public class constants */

// client
const String CLIENT::SERVER_FULL_STATUS   = "server full" ;

// chat
const String CLIENT::CHATMSG_TYPE_TOPIC   = "TOPIC" ;
const String CLIENT::CHATMSG_TYPE_MSG     = "MSG" ;
const String CLIENT::CHATMSG_TYPE_PRIVMSG = "PRIVMSG" ;
const String CLIENT::CHATMSG_TYPE_JOIN    = "JOIN" ;
const String CLIENT::CHATMSG_TYPE_PART    = "PART" ;
const String CLIENT::CHATMSG_TYPE_ADMIN   = "ADMIN" ;
const String CLIENT::CHATMSG_CMD_ME    = "/me " ;
const String CLIENT::CHATMSG_CMD_MSG   = "/msg " ;
const String CLIENT::CHATMSG_CMD_TOPIC = "/topic " ;
const String CLIENT::CHATMSG_CMD_KICK  = "/kick " ;
const String CLIENT::CHATMSG_CMD_BPM   = "/bpm " ;
const String CLIENT::CHATMSG_CMD_BPI   = "/bpi " ;
const String CLIENT::CHATMSG_CMD_ADMIN = "/admin " ;

// audio
char* CLIENT::WIN_INI_FILE = "linjam.ini" ;

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
const String        known_hosts[NETWORK::N_KNOWN_HOSTS] = {
/*
                        NETWORK::NINJAM_2049_URL          ,
                        NETWORK::NINJAM_2050_URL          ,
                        NETWORK::NINJAM_2051_URL          ,
                        NETWORK::NINJAM_2052_URL          ,
                        NETWORK::NINJAM_2600_URL          ,
                        NETWORK::NINJAM_2601_URL          ,
*/
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
const StringRef NETWORK::HOST_VALIDATION_MASK = "*.*:*" ;
const StringRef NETWORK::LETTERS              = "abcdefghijklmnopqrstuvwxyz" ;
const StringRef NETWORK::DIGITS               = "0123456789" ;
const StringRef NETWORK::VALID_URL_CHARS      = "0123456789abcdefghijklmnopqrstuvwxyz-." ;


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

// contentComponent
const String GUI::CONTENT_GUI_ID = "main-content-gui" ;

// blankComponent
const String GUI::BLANK_GUI_ID = "blank-gui" ;

// loginComponent
const String GUI::LOGIN_GUI_ID = "login-gui" ;

// licenseComponent
const String GUI::LICENSE_GUI_ID = "license-gui" ;

// chatComponent
const String GUI::CHAT_GUI_ID         = "chat-gui" ;
const String GUI::SERVER_NICK         = "NINJAM" ;
const String GUI::UNKNOWN_COMMAND_MSG = "Error: unknown command" ;
const String GUI::INVALID_PM_MSG      = "Error: /msg requires a username and a message" ;

// ChannelComponents
const String GUI::MASTER_CHANNEL_GUI_ID = "master" ;
const String GUI::METRO_CHANNEL_GUI_ID  = "metronome" ;
const String GUI::XMIT_LABEL_TEXT       = "XMIT" ;
const String GUI::RCV_LABEL_TEXT        = "RCV" ;

// mixerGroupComponent
const String     GUI::MASTER_MIXERGROUP_GUI_ID     = "Master" ;
const Identifier GUI::MASTER_MIXERGROUP_IDENTIFIER = MASTER_MIXERGROUP_GUI_ID ;
const String     GUI::LOCAL_MIXERGROUP_GUI_ID      = "Local" ;
const Identifier GUI::LOCAL_MIXERGROUP_IDENTIFIER  = LOCAL_MIXERGROUP_GUI_ID ;

// mixerComponent
const String GUI::MIXER_GUI_ID = "mixer-gui" ;

// statusComponent
const String GUI::STATUS_GUI_ID = "statusbar-gui" ;

// loopComponent
const String GUI::LOOP_GUI_ID = "loop-gui" ;


/* CONFIG class public class constants */

// NOTE: many of these *_KEY *_IDENTIFIER pairs maybe redundant or unused (issue #30)

// config root
const String     CONFIG::PERSISTENCE_FILENAME     = "linjam.xml" ;
const String     CONFIG::PERSISTENCE_KEY          = "linjam-data" ;
const Identifier CONFIG::PERSISTENCE_IDENTIFIER   = PERSISTENCE_KEY ;

// client config
const String     CONFIG::CLIENT_KEY               = "client" ;
const Identifier CONFIG::CLIENT_IDENTIFIER        = CLIENT_KEY ;
const String     CONFIG::SAVE_AUDIO_KEY           = "should-save-audio" ;
const Identifier CONFIG::SAVE_AUDIO_IDENTIFIER    = SAVE_AUDIO_KEY ;
const String     CONFIG::SAVE_LOG_KEY             = "should-save-log" ;
const Identifier CONFIG::SAVE_LOG_IDENTIFIER      = SAVE_LOG_KEY ;
const String     CONFIG::DEBUGLEVEL_KEY           = "debug-level" ;
const Identifier CONFIG::DEBUGLEVEL_IDENTIFIER    = DEBUGLEVEL_KEY ;
const String     CONFIG::AUTOSUBSCRIBE_KEY        = "should-subscribe" ;
const Identifier CONFIG::AUTOSUBSCRIBE_IDENTIFIER = AUTOSUBSCRIBE_KEY ;
const String     CONFIG::SESSIONDIR_KEY           = "session-dir" ;
const Identifier CONFIG::SESSIONDIR_IDENTIFIER    = SESSIONDIR_KEY ;
const String     CONFIG::LOGFILE_KEY              = "log-file" ;
const Identifier CONFIG::LOGFILE_IDENTIFIER       = LOGFILE_KEY ;
const String     CONFIG::SESSIONDIR               = "/session" ;
const String     CONFIG::LOGFILE                  = "/clipsort.log" ;
const String     CONFIG::SUBSCRIPTIONS_KEY        = "subscriptions" ;
const Identifier CONFIG::SUBSCRIPTIONS_IDENTIFIER = SUBSCRIPTIONS_KEY ;

// device config
const String     CONFIG::AUDIO_KEY                = "audio" ;
const Identifier CONFIG::AUDIO_IDENTIFIER         = AUDIO_KEY ;
const String     CONFIG::AUDIO_IF_KEY             = "audio-if-n" ;
const Identifier CONFIG::AUDIO_IF_IDENTIFIER      = AUDIO_IF_KEY ;
const String     CONFIG::N_INPUTS_KEY             = "n-inputs" ;
const Identifier CONFIG::N_INPUTS_IDENTIFIER      = N_INPUTS_KEY ;
const String     CONFIG::N_OUTPUTS_KEY            = "n-outputs" ;
const Identifier CONFIG::N_OUTPUTS_IDENTIFIER     = N_OUTPUTS_KEY ;
const String     CONFIG::BITDEPTH_KEY             = "bit-depth" ;
const Identifier CONFIG::BITDEPTH_IDENTIFIER      = BITDEPTH_KEY ;
const String     CONFIG::SAMPLERATE_KEY           = "sample-rate" ;
const Identifier CONFIG::SAMPLERATE_IDENTIFIER    = SAMPLERATE_KEY ;
const String     CONFIG::JACK_NAME_KEY            = "jack-name" ;
const Identifier CONFIG::JACK_NAME_IDENTIFIER     = JACK_NAME_KEY ;

// network config
const String     CONFIG::SERVERS_KEY              = "servers" ;
const Identifier CONFIG::SERVERS_IDENTIFIER       = SERVERS_KEY ;
const String     CONFIG::SERVER_KEY               = "server" ;
const Identifier CONFIG::SERVER_IDENTIFIER        = SERVER_KEY ;
const String     CONFIG::HOST_KEY                 = "host" ;
const Identifier CONFIG::HOST_IDENTIFIER          = HOST_KEY ;
const String     CONFIG::LOGIN_KEY                = "login" ;
const Identifier CONFIG::LOGIN_IDENTIFIER         = LOGIN_KEY ;
const String     CONFIG::PASS_KEY                 = "pass" ;
const Identifier CONFIG::PASS_IDENTIFIER          = PASS_KEY ;
const String     CONFIG::ANON_KEY                 = "is-anonymous" ;
const Identifier CONFIG::ANON_IDENTIFIER          = ANON_KEY ;
const String     CONFIG::AGREED_KEY               = "is-agreed" ;
const Identifier CONFIG::AGREED_IDENTIFIER        = AGREED_KEY ;
const String     CONFIG::AGREE_KEY                = "should-agree" ;
const Identifier CONFIG::AGREE_IDENTIFIER         = AGREE_KEY ;
const String     CONFIG::BOTS_KEY                 = "should-hide-bots" ;
const Identifier CONFIG::BOTS_IDENTIFIER          = BOTS_KEY ;

// channels
const String     CONFIG::MASTERS_KEY              = "master-channels" ;
const Identifier CONFIG::MASTERS_IDENTIFIER       = MASTERS_KEY ;
const String     CONFIG::MASTER_KEY               = GUI::MASTER_CHANNEL_GUI_ID ;
const Identifier CONFIG::MASTER_IDENTIFIER        = MASTER_KEY ;
const String     CONFIG::METRO_KEY                = GUI::METRO_CHANNEL_GUI_ID ;
const Identifier CONFIG::METRO_IDENTIFIER         = METRO_KEY ;
const String     CONFIG::LOCALS_KEY               = "local-channels" ;
const Identifier CONFIG::LOCALS_IDENTIFIER        = LOCALS_KEY ;
const String     CONFIG::VOLUME_KEY               = "volume" ;
const Identifier CONFIG::VOLUME_IDENTIFIER        = VOLUME_KEY ;
const String     CONFIG::PAN_KEY                  = "pan" ;
const Identifier CONFIG::PAN_IDENTIFIER           = PAN_KEY ;
const String     CONFIG::XMIT_KEY                 = "should-xmit-rcv" ;
const Identifier CONFIG::XMIT_IDENTIFIER          = XMIT_KEY ;
const String     CONFIG::MUTE_KEY                 = "is-muted" ;
const Identifier CONFIG::MUTE_IDENTIFIER          = MUTE_KEY ;
const String     CONFIG::SOLO_KEY                 = "is-solo" ;
const Identifier CONFIG::SOLO_IDENTIFIER          = SOLO_KEY ;
const String     CONFIG::SOURCE_N_KEY             = "source-channel-n" ;
const Identifier CONFIG::SOURCE_N_IDENTIFIER      = SOURCE_N_KEY ;
const String     CONFIG::STEREO_KEY               = "is-stereo" ;
const Identifier CONFIG::STEREO_IDENTIFIER        = STEREO_KEY ;
const String     CONFIG::INITIAL_LOCAL_KEY        = "default-L " ;
const Identifier CONFIG::INITIAL_LOCAL_IDENTIFIER = STEREO_KEY ;
const StringRef  CONFIG::VALID_NAME_CHARS         = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_- " ;
const StringRef  CONFIG::AT_CHAR                  = "@" ;
const String     CONFIG::DEFAULT_CHANNEL_NAME     = "channel-" ;
const String     CONFIG::DEFAULT_USER_NAME        = "user-" ;
const float      CONFIG::DEFAULT_VOLUME           = 0.0 ;
const float      CONFIG::DEFAULT_PAN              = 0.0 ;
const bool       CONFIG::DEFAULT_IS_XMIT          = false ;
const bool       CONFIG::DEFAULT_IS_MUTE          = false ;
const bool       CONFIG::DEFAULT_IS_SOLO          = false ;
const int        CONFIG::DEFAULT_SOURCE_N         = 0 ;
const bool       CONFIG::DEFAULT_IS_STEREO        = false ;
// NOTE: when adding nodes to CONFIG_XML be sure to
//         * attach them to values in LinJamConfig::establishSharedStore()
//         * verify them in           LinJamConfig::sanityCheck()
#define CONFIG_XML "<?xml version=\"1.0\"?><" + \
    PERSISTENCE_KEY        + "><"             + \
      CLIENT_KEY           + " "              + \
        SAVE_AUDIO_KEY     + "=\"-1\" "       + \
        SAVE_LOG_KEY       + "=\"false\" "    + \
        DEBUGLEVEL_KEY     + "=\"0\" "        + \
        AUTOSUBSCRIBE_KEY  + "=\"1\" "        + \
      "/><"                                   + \
      AUDIO_KEY            + " "              + \
        AUDIO_IF_KEY       + "=\"0\" "        + \
        N_INPUTS_KEY       + "=\"2\" "        + \
        N_OUTPUTS_KEY      + "=\"2\" "        + \
        BITDEPTH_KEY       + "=\"16\" "       + \
        SAMPLERATE_KEY     + "=\"48000\" "    + \
        JACK_NAME_KEY      + "=\"linjam\" "   + \
      "/><"                                   + \
      SERVER_KEY           + " "              + \
        HOST_KEY           + "=\"\" "         + \
        LOGIN_KEY          + "=\"\" "         + \
        PASS_KEY           + "=\"\" "         + \
        ANON_KEY           + "=\"true\" "     + \
        AGREED_KEY         + "=\"false\" "    + \
        BOTS_KEY           + "=\"true\" "     + \
      "/><"                                   + \
      MASTERS_KEY          + "><"             + \
        MASTER_KEY         + " "              + \
          VOLUME_KEY       + "=\"0.0\" "      + \
          PAN_KEY          + "=\"0.0\" "      + \
          MUTE_KEY         + "=\"false\" "    + \
      "/><"                                   + \
        METRO_KEY          + " "              + \
          VOLUME_KEY       + "=\"0.0\" "      + \
          PAN_KEY          + "=\"0.0\" "      + \
          MUTE_KEY         + "=\"false\" "    + \
          SOURCE_N_KEY     + "=\"0\" "        + \
          STEREO_KEY       + "=\"true\" "     + \
      "/>"                                    + \
      "</" + MASTERS_KEY   + "><"             + \
      LOCALS_KEY           + "><"             + \
        INITIAL_LOCAL_KEY                     + \
          VOLUME_KEY       + "=\"0.0\" "      + \
          PAN_KEY          + "=\"0.0\" "      + \
          XMIT_KEY         + "=\"false\" "    + \
          MUTE_KEY         + "=\"false\" "    + \
          SOLO_KEY         + "=\"false\" "    + \
          SOURCE_N_KEY     + "=\"0\" "        + \
          STEREO_KEY       + "=\"false\" "    + \
        "/>"                                  + \
      "</" + LOCALS_KEY    + "><"             + \
      SUBSCRIPTIONS_KEY    + " /><"           + \
      SERVERS_KEY          + " />"            + \
    "</" + PERSISTENCE_KEY + ">"
const String CONFIG::DEFAULT_CONFIG_XML = String(CONFIG_XML) ;
