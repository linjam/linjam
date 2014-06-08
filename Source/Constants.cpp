
#include "Constants.h"

// client
const String CLIENT::SERVER_FULL_STATUS   = "server full" ;
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
