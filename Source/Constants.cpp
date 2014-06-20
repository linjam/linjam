
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
const String        known_hosts[NETWORK::N_KNOWN_HOSTS] = {
/*
                        NETWORK::NINJAM_2049_URL   ,
                        NETWORK::NINJAM_2050_URL   ,
                        NETWORK::NINJAM_2051_URL   ,
                        NETWORK::NINJAM_2052_URL   ,
                        NETWORK::NINJAM_2600_URL   ,
                        NETWORK::NINJAM_2601_URL   ,
*/
                        NETWORK::NINBOT_2049_URL   ,
                        NETWORK::NINBOT_2050_URL   ,
                        NETWORK::NINBOT_2051_URL   ,
                        NETWORK::NINBOT_2052_URL   ,
                        NETWORK::NINJAMER_2049_URL ,
                        NETWORK::NINJAMER_2050_URL ,
                        NETWORK::NINJAMER_2051_URL ,
                        NETWORK::NINJAMER_2052_URL } ;
const Array<String> NETWORK::KNOWN_HOSTS = Array<String>(known_hosts , NETWORK::N_KNOWN_HOSTS) ;


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
const String GUI::MASTER_CHANNEL_GUI_ID  = "master" ;
const String GUI::METRO_CHANNEL_GUI_ID   = "metronome" ;
const String GUI::XMIT_LABEL_TEXT        = "XMIT" ;
const String GUI::RCV_LABEL_TEXT         = "RCV" ;

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


/* STORAGE class public class constants */

const String     STORAGE::PERSISTENCE_FILENAME     = "linjam.xml" ;
const String     STORAGE::PERSISTENCE_KEY          = "linjam-data" ;
const Identifier STORAGE::PERSISTENCE_IDENTIFIER   = PERSISTENCE_KEY ;

// client config
const String     STORAGE::CLIENT_KEY               = "client" ;
const Identifier STORAGE::CLIENT_IDENTIFIER        = CLIENT_KEY ;
const String     STORAGE::SAVE_AUDIO_KEY           = "should-save-audio" ;
const Identifier STORAGE::SAVE_AUDIO_IDENTIFIER    = SAVE_AUDIO_KEY ;
const String     STORAGE::SAVE_LOG_KEY             = "should-save-log" ;
const Identifier STORAGE::SAVE_LOG_IDENTIFIER      = SAVE_LOG_KEY ;
const String     STORAGE::DEBUGLEVEL_KEY           = "debug-level" ;
const Identifier STORAGE::DEBUGLEVEL_IDENTIFIER    = DEBUGLEVEL_KEY ;
const String     STORAGE::AUTOSUBSCRIBE_KEY        = "should-subscribe" ;
const Identifier STORAGE::AUTOSUBSCRIBE_IDENTIFIER = AUTOSUBSCRIBE_KEY ;
const String     STORAGE::SESSIONDIR_KEY           = "session-dir" ;
const Identifier STORAGE::SESSIONDIR_IDENTIFIER    = SESSIONDIR_KEY ;
const String     STORAGE::LOGFILE_KEY              = "log-file" ;
const Identifier STORAGE::LOGFILE_IDENTIFIER       = LOGFILE_KEY ;
const String     STORAGE::SESSIONDIR               = "/session" ;
const String     STORAGE::LOGFILE                  = "/clipsort.log" ;
const String     STORAGE::SUBSCRIPTIONS_KEY        = "subscriptions" ;
const Identifier STORAGE::SUBSCRIPTIONS_IDENTIFIER = SUBSCRIPTIONS_KEY ;

// device config
const String     STORAGE::AUDIO_KEY                = "audio" ;
const Identifier STORAGE::AUDIO_IDENTIFIER         = AUDIO_KEY ;
const String     STORAGE::AUDIO_IF_KEY             = "audio-if-n" ;
const Identifier STORAGE::AUDIO_IF_IDENTIFIER      = AUDIO_IF_KEY ;
const String     STORAGE::N_INPUTS_KEY             = "n-inputs" ;
const Identifier STORAGE::N_INPUTS_IDENTIFIER      = N_INPUTS_KEY ;
const String     STORAGE::N_OUTPUTS_KEY            = "n-outputs" ;
const Identifier STORAGE::N_OUTPUTS_IDENTIFIER     = N_OUTPUTS_KEY ;
const String     STORAGE::BITDEPTH_KEY             = "bit-depth" ;
const Identifier STORAGE::BITDEPTH_IDENTIFIER      = BITDEPTH_KEY ;
const String     STORAGE::SAMPLERATE_KEY           = "sample-rate" ;
const Identifier STORAGE::SAMPLERATE_IDENTIFIER    = SAMPLERATE_KEY ;
const String     STORAGE::JACK_NAME_KEY            = "jack-name" ;
const Identifier STORAGE::JACK_NAME_IDENTIFIER     = JACK_NAME_KEY ;

// per server user data
const String     STORAGE::SERVERS_KEY              = "servers" ;
const Identifier STORAGE::SERVERS_IDENTIFIER       = SERVERS_KEY ;
const String     STORAGE::SERVER_KEY               = "server" ;
const Identifier STORAGE::SERVER_IDENTIFIER        = SERVER_KEY ;
const String     STORAGE::HOST_KEY                 = "host" ;
const Identifier STORAGE::HOST_IDENTIFIER          = HOST_KEY ;
const String     STORAGE::LOGIN_KEY                = "login" ;
const Identifier STORAGE::LOGIN_IDENTIFIER         = LOGIN_KEY ;
const String     STORAGE::PASS_KEY                 = "pass" ;
const Identifier STORAGE::PASS_IDENTIFIER          = PASS_KEY ;
const String     STORAGE::ANON_KEY                 = "is-anonymous" ;
const Identifier STORAGE::ANON_IDENTIFIER          = ANON_KEY ;
const String     STORAGE::AGREED_KEY               = "is-agreed" ;
const Identifier STORAGE::AGREED_IDENTIFIER        = AGREED_KEY ;
const String     STORAGE::AGREE_KEY                = "should-agree" ;
const Identifier STORAGE::AGREE_IDENTIFIER         = AGREE_KEY ;

// channels
const String     STORAGE::MASTERS_KEY              = "master-channels" ;
const Identifier STORAGE::MASTERS_IDENTIFIER       = MASTERS_KEY ;
const String     STORAGE::MASTER_KEY               = GUI::MASTER_CHANNEL_GUI_ID ;
const Identifier STORAGE::MASTER_IDENTIFIER        = MASTER_KEY ;
const String     STORAGE::METRO_KEY                = GUI::METRO_CHANNEL_GUI_ID ;
const Identifier STORAGE::METRO_IDENTIFIER         = METRO_KEY ;
const String     STORAGE::LOCALS_KEY               = "local-channels" ;
const Identifier STORAGE::LOCALS_IDENTIFIER        = LOCALS_KEY ;
const String     STORAGE::VOLUME_KEY               = "volume" ;
const Identifier STORAGE::VOLUME_IDENTIFIER        = VOLUME_KEY ;
const String     STORAGE::PAN_KEY                  = "pan" ;
const Identifier STORAGE::PAN_IDENTIFIER           = PAN_KEY ;
const String     STORAGE::XMIT_KEY                 = "should-xmit-rcv" ;
const Identifier STORAGE::XMIT_IDENTIFIER          = XMIT_KEY ;
const String     STORAGE::MUTE_KEY                 = "is-muted" ;
const Identifier STORAGE::MUTE_IDENTIFIER          = MUTE_KEY ;
const String     STORAGE::SOLO_KEY                 = "is-solo" ;
const Identifier STORAGE::SOLO_IDENTIFIER          = SOLO_KEY ;
const String     STORAGE::SOURCE_N_KEY             = "source-channel-n" ;
const Identifier STORAGE::SOURCE_N_IDENTIFIER      = SOURCE_N_KEY ;
const String     STORAGE::STEREO_KEY               = "is-stereo" ;
const Identifier STORAGE::STEREO_IDENTIFIER        = STEREO_KEY ;
const StringRef  STORAGE::VALID_CHARS              = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_- " ;
const StringRef  STORAGE::AT_CHAR                  = "@" ;
const String     STORAGE::DEFAULT_CHANNEL_NAME     = "channel-" ;
const String     STORAGE::DEFAULT_USER_NAME        = "user-" ;
const float      STORAGE::DEFAULT_VOLUME           = 0.0 ;
const float      STORAGE::DEFAULT_PAN              = 0.0 ;
const bool       STORAGE::DEFAULT_IS_XMIT          = false ;
const bool       STORAGE::DEFAULT_IS_MUTE          = false ;
const bool       STORAGE::DEFAULT_IS_SOLO          = false ;
const int        STORAGE::DEFAULT_SOURCE_N         = 0 ;
const bool       STORAGE::DEFAULT_IS_STEREO        = false ;

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
        "default-L "                          + \
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

const String STORAGE::DEFAULT_CONFIG_XML = String(CONFIG_XML) ;
