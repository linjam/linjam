
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


/* GUI class public class constants */

// main
const String GUI::AUDIO_INIT_ERROR_MSG          = "audio device error" ;
const String GUI::DISCONNECTED_STATUS_TEXT      = "Disconnected" ;
const String GUI::ROOM_FULL_STATUS_TEXT         = "Jam room full" ;
const String GUI::INVALID_AUTH_STATUS_TEXT      = "Invalid login/pass" ;
const String GUI::PENDING_LICENSE_STATUS_TEXT   = "Pending license" ;
const String GUI::FAILED_CONNECTION_STATUS_TEXT = "Connection failed" ;
const String GUI::CONNECTED_STATUS_TEXT         = "Connected to " ;
const String GUI::IDLE_STATUS_TEXT              = "Idle" ;
const String GUI::UNKNOWN_STATUS_TEXT           = "Status: " ;

// contentComponent
const String GUI::CONTENT_GUI_ID = "main-content-gui" ;

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
const String GUI::LOCAL_CHANNEL_GUI_ID  = "local-channel" ;
const String GUI::MASTER_CHANNEL_GUI_ID = "master-channel" ;
const String GUI::METRO_CHANNEL_GUI_ID  = "metro-channel" ;

// mixerGroupComponent
const String GUI::LOCAL_MIXER_GUI_ID  = "Local" ;
const String GUI::MASTER_MIXER_GUI_ID = "Master" ;

// mixerComponent
const String GUI::MIXER_GUI_ID = "mixer-gui" ;

// statusComponent
const String GUI::STATUS_GUI_ID = "statusbar-gui" ;


/* STORAGE class public class constants */

const String     STORAGE::PERSISTENCE_FILENAME     = "linjam.xml" ;
const String     STORAGE::PERSISTENCE_KEY          = "linjam-data" ;
const Identifier STORAGE::PERSISTENCE_IDENTIFIER   = PERSISTENCE_KEY ;

const String     STORAGE::MASTER_KEY               = "master" ;
const Identifier STORAGE::MASTER_IDENTIFIER        = MASTER_KEY ;
const String     STORAGE::MASTER_VOLUME_KEY        = "master-volume" ;
const Identifier STORAGE::MASTER_VOLUME_IDENTIFIER = MASTER_VOLUME_KEY ;
const String     STORAGE::MASTER_PAN_KEY           = "master-pan" ;
const Identifier STORAGE::MASTER_PAN_IDENTIFIER    = MASTER_PAN_KEY ;
const String     STORAGE::MASTER_MUTE_KEY          = "master-mute" ;
const Identifier STORAGE::MASTER_MUTE_IDENTIFIER   = MASTER_MUTE_KEY ;
const String     STORAGE::METRO_VOLUME_KEY         = "metro-volume" ;
const Identifier STORAGE::METRO_VOLUME_IDENTIFIER  = METRO_VOLUME_KEY ;
const String     STORAGE::METRO_PAN_KEY            = "metro-pan" ;
const Identifier STORAGE::METRO_PAN_IDENTIFIER     = METRO_PAN_KEY ;
const String     STORAGE::METRO_MUTE_KEY           = "metro-mute" ;
const Identifier STORAGE::METRO_MUTE_IDENTIFIER    = METRO_MUTE_KEY ;
const String     STORAGE::METRO_CHANNEL_KEY        = "metro-channel" ;
const Identifier STORAGE::METRO_CHANNEL_IDENTIFIER = METRO_CHANNEL_KEY ;
const String     STORAGE::METRO_STEREO_KEY         = "metro-stereo" ;
const Identifier STORAGE::METRO_STEREO_IDENTIFIER  = METRO_STEREO_KEY ;

const String     STORAGE::HOST_KEY                 = "host" ;
const Identifier STORAGE::HOST_IDENTIFIER          = HOST_KEY ;
const String     STORAGE::LOGIN_KEY                = "login" ;
const Identifier STORAGE::LOGIN_IDENTIFIER         = LOGIN_KEY ;
const String     STORAGE::PASS_KEY                 = "pass" ;
const Identifier STORAGE::PASS_IDENTIFIER          = PASS_KEY ;
const String     STORAGE::ANON_KEY                 = "is-anonymous" ;
const Identifier STORAGE::ANON_IDENTIFIER          = ANON_KEY ;
const String     STORAGE::AGREE_KEY                = "should-agree" ;
const Identifier STORAGE::AGREE_IDENTIFIER         = AGREE_KEY ;

const String     STORAGE::SERVER_KEY               = "server" ;
const Identifier STORAGE::SERVER_IDENTIFIER        = SERVER_KEY ;
const String     STORAGE::MISC_KEY                 = "misc" ;
const Identifier STORAGE::MISC_IDENTIFIER          = MISC_KEY ;

const Identifier STORAGE::SERVERS_IDENTIFIER       = "servers" ;

/*
#define CONFIG_XML "              \
    <?xml version=\"1.0\"?>       \
    <linjam-data>                 \
      <!-- master channels config defaults --> \
      <" + MASTER_VOLUME_KEY + ">0.0f</" + MASTER_VOLUME_KEY + "> \
      <" + MASTER_PAN_KEY + ">1.0f   </" + MASTER_PAN_KEY + "> \
      <" + MASTER_MUTE_KEY + ">false </" + MASTER_MUTE_KEY + "> \
      <" + METRO_VOLUME_KEY + ">0.1f </" + METRO_VOLUME_KEY + "> \
      <" + METRO_PAN_KEY + ">0.0f    </" + METRO_PAN_KEY + "> \
      <" + METRO_MUTE_KEY + ">false  </" + METRO_MUTE_KEY + "> \
      <" + METRO_CHANNEL_KEY + ">0   </" + METRO_CHANNEL_KEY + "> \
      <" + METRO_STEREO_KEY + ">true </" + METRO_STEREO_KEY + "> \
      <to>Tove</to>               \
      <from>Jani</from>           \
      <heading>Reminder</heading> \
      <body></body>               \
    </linjam-data>"
*/


/* ok
#define CONFIG_XML "              \
    <?xml version=\"1.0\"?>       \
    <linjam-data " +                 \
      /* master channels config defaults * / \
      MASTER_VOLUME_KEY + "=\"1.0f\" "  +        \
      MASTER_PAN_KEY    + "=\"0.0f\" "  +        \
      MASTER_MUTE_KEY   + "=\"false\" " +        \
      METRO_VOLUME_KEY  + "=\"0.1f\" "  +        \
      METRO_PAN_KEY     + "=\"0.0f\" "  +        \
      METRO_MUTE_KEY    + "=\"false\" " +        \
      METRO_CHANNEL_KEY + "=\"0\" "     +        \
      METRO_STEREO_KEY  + "=\"true\" "  +        \
    "/>"
*/
/* ok
#define CONFIG_XML "<?xml version=\"1.0\"?><" + \
    PERSISTENCE_KEY     + " "                 + \
      SERVER_KEY        + "=\"\" "            + \
                                                \
      /* master channels config defaults * /     \
      MASTER_VOLUME_KEY + "=\"1.0f\" "        + \
      MASTER_PAN_KEY    + "=\"0.0f\" "        + \
      MASTER_MUTE_KEY   + "=\"false\" "       + \
      METRO_VOLUME_KEY  + "=\"0.1f\" "        + \
      METRO_PAN_KEY     + "=\"0.0f\" "        + \
      METRO_MUTE_KEY    + "=\"false\" "       + \
      METRO_CHANNEL_KEY + "=\"0\" "           + \
      METRO_STEREO_KEY  + "=\"true\" "        + \
    "/>"
*/

#define CONFIG_XML "<?xml version=\"1.0\"?><" + \
    PERSISTENCE_KEY        + "><"             + \
      MASTER_KEY           + " "              + \
        MASTER_VOLUME_KEY  + "=\"1.0f\" "     + \
        MASTER_PAN_KEY     + "=\"0.0f\" "     + \
        MASTER_MUTE_KEY    + "=\"false\" "    + \
        METRO_VOLUME_KEY   + "=\"0.1f\" "     + \
        METRO_PAN_KEY      + "=\"0.0f\" "     + \
        METRO_MUTE_KEY     + "=\"false\" "    + \
        METRO_CHANNEL_KEY  + "=\"0\" "        + \
        METRO_STEREO_KEY   + "=\"true\" "     + \
      "/><"                                   + \
      MISC_KEY             + " "              + \
        SERVER_KEY         + "=\"\" "         + \
      "/>"                                    + \
    "</" + PERSISTENCE_KEY + ">"
const String STORAGE::DEFAULT_CONFIG_XML = String(CONFIG_XML) ;
/*
      <master-volume>1.0f</master-volume> \
      <master-pan>1.0f   </master-pan> \
      <master-mute>false </master-mute> \
      <metro-volume>0.1f </metro-volume> \
      <metro-pan>0.0f    </metro-pan> \
      <metro-mute>false  </metro-mute> \
      <metro-channel>0   </metro-channel> \
      <metro-stereo>true </metro-stereo> \
 */
#define SERVER_XML(host) String("<" + \
    host        + " "               + \
      HOST_KEY  + "=\"\" "          + \
      LOGIN_KEY + "=\"\" "          + \
      PASS_KEY  + "=\"\" "          + \
      ANON_KEY  + "=\"true\" "      + \
      AGREE_KEY + "=\"false\" "     + \
    "/>")
