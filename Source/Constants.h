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

  // main
  static const int CLIENT_DRIVER_ID = 0 ; static const int CLIENT_DRIVER_IVL = 50 ;
  static const int STATUS_POLL_ID   = 1 ; static const int STATUS_POLL_IVL   = 500 ;

  // audio
  static const char* WIN_INI_FILE ;

  // NJClient
  static const uint8 CHATMSG_TYPE_IDX = 0 ;
  static const uint8 CHATMSG_MSG_IDX  = 2 ;
} ;


class GUI
{
public:

  // global
  static const uint16 PAD = 4 ;

  // contentComponent
  static const String CONTENT_GUI_ID ;
  static const uint16 CONTAINER_W = 630 ;
  static const uint16 CONTAINER_H = 470 ;

  // LoginComponent
  static const String LOGIN_GUI_ID ;

  // licenseComponent
  static const String LICENSE_GUI_ID ;

  // statusComponent
  static const String STATUS_GUI_ID ;
  static const uint16 STATUSBAR_L   = 4 ;
  static const uint16 STATUSBAR_H   = 24 ;
  static const uint16 STATUS_W      = 120 ;
  static const uint16 STATUS_H      = 20 ;
  static const uint16 STATUS_PAD_X  = 8 ;
  static const uint16 STATUS_PAD_Y  = 2 ;
} ;

#endif // CONSTANTS_H_INCLUDED
