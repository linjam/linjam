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
  static char* WIN_INI_FILE ;

  // NJClient
  static const String SERVER_FULL_STATUS ;
  static const uint8  CHATMSG_TYPE_IDX = 0 ;
  static const uint8  CHATMSG_USER_IDX = 1 ;
  static const uint8  CHATMSG_MSG_IDX  = 2 ;
  static const String CHATMSG_TYPE_TOPIC ;
  static const String CHATMSG_TYPE_MSG ;
  static const String CHATMSG_TYPE_PRIVMSG ;
  static const String CHATMSG_TYPE_JOIN ;
  static const String CHATMSG_TYPE_PART ;
  static const String CHATMSG_TYPE_ADMIN ;
  static const String CHATMSG_CMD_ME ;
  static const String CHATMSG_CMD_MSG ;
  static const String CHATMSG_CMD_TOPIC ;
  static const String CHATMSG_CMD_KICK ;
  static const String CHATMSG_CMD_BPM ;
  static const String CHATMSG_CMD_BPI ;
  static const String CHATMSG_CMD_ADMIN ;

  // main
  static const int CLIENT_DRIVER_ID = 0 ; static const int CLIENT_DRIVER_IVL = 50 ;
//  static const int STATUS_POLL_ID   = 1 ; static const int STATUS_POLL_IVL   = 500 ;
} ;


class NETWORK
{
public:

  static const String        NINJAM_2049_URL ;
  static const String        NINJAM_2050_URL ;
  static const String        NINJAM_2051_URL ;
  static const String        NINJAM_2052_URL ;
  static const String        NINJAM_2600_URL ;
  static const String        NINJAM_2601_URL ;
  static const String        NINBOT_2049_URL ;
  static const String        NINBOT_2050_URL ;
  static const String        NINBOT_2051_URL ;
  static const String        NINBOT_2052_URL ;
  static const String        NINJAMER_2049_URL ;
  static const String        NINJAMER_2050_URL ;
  static const String        NINJAMER_2051_URL ;
  static const String        NINJAMER_2052_URL ;
  static const int           N_KNOWN_HOSTS = 8 ;
  static const Array<String> KNOWN_HOSTS ;
} ;

class GUI
{
public:

  // common
  static const int PAD     = 4 ;
  static const int PAD3    = PAD * 3 ;
  static const int PAD2    = PAD * 2 ;
  static const int LABEL_H = 12 ;

  // main
  static const String AUDIO_INIT_ERROR_MSG ;
  static const String DISCONNECTED_STATUS_TEXT ;
  static const String ROOM_FULL_STATUS_TEXT ;
  static const String INVALID_AUTH_STATUS_TEXT ;
  static const String PENDING_LICENSE_STATUS_TEXT ;
  static const String FAILED_CONNECTION_STATUS_TEXT ;
  static const String CONNECTING_STATUS_TEXT ;
  static const String CONNECTED_STATUS_TEXT ;
  static const String IDLE_STATUS_TEXT ;
  static const String UNKNOWN_STATUS_TEXT ;

  // contentComponent
  static const String CONTENT_GUI_ID ;
  static const int    CONTENT_W = 630 ;
  static const int    CONTENT_H = 470 ;

  // blankComponent
  static const String BLANK_GUI_ID ;

  // LoginComponent
  static const String LOGIN_GUI_ID ;
  static const int    LOGIN_BUTTON_L = GUI::PAD ;
  static const int    LOGIN_BUTTON_T = GUI::PAD ;
  static const int    LOGIN_BUTTON_W = 96 ;
  static const int    LOGIN_BUTTON_H = 24 ;

  // licenseComponent
  static const String LICENSE_GUI_ID ;

  // chatComponent
  static const String CHAT_GUI_ID ;
  static const String SERVER_NICK ;
  static const String UNKNOWN_COMMAND_MSG ;
  static const String INVALID_PM_MSG ;

  // ChannelComponents
  static const String LOCAL_CHANNEL_GUI_ID ;
  static const String MASTER_CHANNEL_GUI_ID ;
  static const String METRO_CHANNEL_GUI_ID ;
  static const int    CHANNEL_Y = LABEL_H + PAD2 ;//20 ;
  static const int    CHANNEL_W = 60 ;
  static const int    CHANNEL_H = 252 ;

  // MixerGroupComponent
  static const String LOCAL_MIXER_GUI_ID ;
  static const String MASTER_MIXER_GUI_ID ;
  static const int    MIXERGROUP_Y  = PAD ;
  static const int    MASTERGROUP_W =                       PAD + (2          * (CHANNEL_W + PAD)) ;//132
  static       int    MIXERGROUP_W(int n_channels) { return PAD + (n_channels * (CHANNEL_W + PAD)) ; }
  static const int    MIXERGROUP_H  = CHANNEL_H + LABEL_H + PAD3 ; // 276

  // MixerComponent
  static const String MIXER_GUI_ID ;
  static const int    MIXER_H = MIXERGROUP_H + PAD2 ;//284 ;

  // statusComponent
  static const String STATUS_GUI_ID ;
  static const int    STATUSBAR_H  = 24 ;
  static const int    STATUS_W     = 120 ;
  static const int    STATUS_H     = 16 ;
  static const int    STATUS_PAD_X = 8 ;
  static const int    STATUS_PAD_Y = 2 ;
} ;


class STORAGE
{
public:

  static const String     PERSISTENCE_FILENAME ;
  static const String     PERSISTENCE_KEY ;
  static const Identifier PERSISTENCE_IDENTIFIER ;

  static const String     MASTER_KEY ;
  static const Identifier MASTER_IDENTIFIER ;
  static const String     MASTER_VOLUME_KEY ;
  static const Identifier MASTER_VOLUME_IDENTIFIER ;
  static const String     MASTER_PAN_KEY ;
  static const Identifier MASTER_PAN_IDENTIFIER ;
  static const String     MASTER_MUTE_KEY ;
  static const Identifier MASTER_MUTE_IDENTIFIER ;
  static const String     METRO_VOLUME_KEY ;
  static const Identifier METRO_VOLUME_IDENTIFIER ;
  static const String     METRO_PAN_KEY ;
  static const Identifier METRO_PAN_IDENTIFIER ;
  static const String     METRO_MUTE_KEY ;
  static const Identifier METRO_MUTE_IDENTIFIER ;
  static const String     METRO_CHANNEL_KEY ;
  static const Identifier METRO_CHANNEL_IDENTIFIER ;
  static const String     METRO_STEREO_KEY ;
  static const Identifier METRO_STEREO_IDENTIFIER ;

  static const String     SERVERS_KEY ;
  static const Identifier SERVERS_IDENTIFIER ;
  static const String     SERVER_KEY ;
  static const Identifier SERVER_IDENTIFIER ;
  static const String     HOST_KEY ;
  static const Identifier HOST_IDENTIFIER ;
  static const String     LOGIN_KEY ;
  static const Identifier LOGIN_IDENTIFIER ;
  static const String     PASS_KEY ;
  static const Identifier PASS_IDENTIFIER ;
  static const String     ANON_KEY ;
  static const Identifier ANON_IDENTIFIER ;
  static const String     AGREED_KEY ;
  static const Identifier AGREED_IDENTIFIER ;
  static const String     AGREE_KEY ;
  static const Identifier AGREE_IDENTIFIER ;

  static const String     DEFAULT_CONFIG_XML ;
} ;

#endif // CONSTANTS_H_INCLUDED
