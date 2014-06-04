
#include "Constants.h"

// client
const StringRef CLIENT::CHATMSG_TYPE_TOPIC   = "TOPIC" ;
const StringRef CLIENT::CHATMSG_TYPE_MSG     = "MSG" ;
const StringRef CLIENT::CHATMSG_TYPE_PRIVMSG = "PRIVMSG" ;
const StringRef CLIENT::CHATMSG_TYPE_JOIN    = "JOIN" ;
const StringRef CLIENT::CHATMSG_TYPE_PART    = "PART" ;

// audio
char* CLIENT::WIN_INI_FILE = "linjam.ini" ;

// main
const StringRef CLIENT::AUDIO_INIT_ERROR_MSG = "audio device error" ;

// contentComponent
const StringRef GUI::CONTENT_GUI_ID = StringRef("main-content-gui") ;

// loginComponent
const StringRef GUI::LOGIN_GUI_ID = StringRef("login-gui") ;

// licenseComponent
const StringRef GUI::LICENSE_GUI_ID =StringRef( "license-gui") ;

// chatComponent
const StringRef GUI::CHAT_GUI_ID = StringRef( "chat-gui") ;
const StringRef GUI::SERVER_NICK = "NINJAM" ;

// statusComponent
const StringRef GUI::STATUS_GUI_ID = StringRef("statusbar-gui") ;
