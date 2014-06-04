/*
  ==============================================================================

    Constants.h
    Created: 24 May 2014 11:41:00am
    Author:  me

  ==============================================================================
*/

#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"



class CLIENT
{
public:

  // audio
  static       char* WIN_INI_FILE ;

  // NJClient
  static const uint8  CHATMSG_TYPE_IDX = 0 ;
  static const uint8  CHATMSG_USER_IDX = 1 ;
  static const uint8  CHATMSG_MSG_IDX  = 2 ;
  static const StringRef CHATMSG_TYPE_TOPIC ;
  static const StringRef CHATMSG_TYPE_MSG ;
  static const StringRef CHATMSG_TYPE_PRIVMSG ;
  static const StringRef CHATMSG_TYPE_JOIN ;
  static const StringRef CHATMSG_TYPE_PART ;

  // main
  static const int CLIENT_DRIVER_ID = 0 ; static const int CLIENT_DRIVER_IVL = 50 ;
  static const int STATUS_POLL_ID   = 1 ; static const int STATUS_POLL_IVL   = 500 ;
  static const StringRef AUDIO_INIT_ERROR_MSG ;
} ;


class GUI
{
public:

  // global
  static const uint16 PAD  = 4 ;
  static const uint16 PAD2 = PAD * 2 ;

  // contentComponent
  static const StringRef CONTENT_GUI_ID ;
  static const uint16 CONTAINER_W = 630 ;
  static const uint16 CONTAINER_H = 470 ;

  // LoginComponent
  static const StringRef LOGIN_GUI_ID ;

  // licenseComponent
  static const StringRef LICENSE_GUI_ID ;

  // chatComponent
  static const StringRef CHAT_GUI_ID ;
  static const StringRef SERVER_NICK ;

  // statusComponent
  static const StringRef STATUS_GUI_ID ;
  static const uint16 STATUSBAR_L   = 4 ;
  static const uint16 STATUSBAR_H   = 24 ;
  static const uint16 STATUS_W      = 120 ;
  static const uint16 STATUS_H      = 20 ;
  static const uint16 STATUS_PAD_X  = 8 ;
  static const uint16 STATUS_PAD_Y  = 2 ;
} ;

#endif // CONSTANTS_H_INCLUDED
