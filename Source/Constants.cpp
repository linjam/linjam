
#include "Constants.h"

// client
const StringRef CLIENT::CHATMSG_TYPE_TOPIC   = "TOPIC" ;
const StringRef CLIENT::CHATMSG_TYPE_MSG     = "MSG" ;
const StringRef CLIENT::CHATMSG_TYPE_PRIVMSG = "PRIVMSG" ;
const StringRef CLIENT::CHATMSG_TYPE_JOIN    = "JOIN" ;
const StringRef CLIENT::CHATMSG_TYPE_PART    = "PART" ;
const StringRef CLIENT::CHATMSG_TYPE_ADMIN   = "ADMIN" ;
const StringRef CLIENT::CHATMSG_CMD_ME    = "/me " ; 
const StringRef CLIENT::CHATMSG_CMD_MSG   = "/msg " ;
const StringRef CLIENT::CHATMSG_CMD_TOPIC = "/topic " ;
const StringRef CLIENT::CHATMSG_CMD_KICK  = "/kick " ;
const StringRef CLIENT::CHATMSG_CMD_BPM   = "/bpm " ;
const StringRef CLIENT::CHATMSG_CMD_BPI   = "/bpi " ;
const StringRef CLIENT::CHATMSG_CMD_ADMIN = "/admin " ;

// audio
char* CLIENT::WIN_INI_FILE = "linjam.ini" ;

// main
const StringRef GUI::AUDIO_INIT_ERROR_MSG          = "audio device error" ;
const String    GUI::DISCONNECTED_STATUS_TEXT      = "Disconnected" ;
const String    GUI::INVALID_AUTH_STATUS_TEXT      = "Invalid login/pass" ;
const String    GUI::PENDING_LICENSE_STATUS_TEXT   = "Pending license" ;
const String    GUI::FAILED_CONNECTION_STATUS_TEXT = "Connection failed" ;
const String    GUI::CONNECTED_STATUS_TEXT         = "Connected to " ;
const String    GUI::IDLE_STATUS_TEXT              = "Idle" ;
const String    GUI::UNKNOWN_STATUS_TEXT           = "Status: " ;

// contentComponent
const StringRef GUI::CONTENT_GUI_ID = "main-content-gui" ;

// loginComponent
const StringRef GUI::LOGIN_GUI_ID = "login-gui" ;

// licenseComponent
const StringRef GUI::LICENSE_GUI_ID = "license-gui" ;

// chatComponent
const StringRef GUI::CHAT_GUI_ID         = "chat-gui" ;
const StringRef GUI::SERVER_NICK         = "NINJAM" ;
const String    GUI::UNKNOWN_COMMAND_MSG = "Error: unknown command" ;
const String    GUI::INVALID_PM_MSG      = "Error: /msg requires a username and a message" ;

// statusComponent
const StringRef GUI::STATUS_GUI_ID = "statusbar-gui" ;
