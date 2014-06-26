/*
  ==============================================================================

    Constants.h
    Created: 24 May 2014 11:41:00am
    Author:  me

  ==============================================================================
*/

#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_


#include "LinJam.h"


class CLIENT
{
public:

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

  // audio
  static char* WIN_INI_FILE ;

  // main
  static const int CLIENT_DRIVER_ID = 0 ; static const int CLIENT_DRIVER_IVL = 50 ;
  static const int GUI_DRIVER_ID    = 1 ; static const int GUI_DRIVER_IVL    = 125 ;
} ;


class NETWORK
{
public:

  // known hosts
  static const String            NINJAM_2049_URL ;
  static const String            NINJAM_2050_URL ;
  static const String            NINJAM_2051_URL ;
  static const String            NINJAM_2052_URL ;
  static const String            NINJAM_2600_URL ;
  static const String            NINJAM_2601_URL ;
  static const String            NINBOT_2049_URL ;
  static const String            NINBOT_2050_URL ;
  static const String            NINBOT_2051_URL ;
  static const String            NINBOT_2052_URL ;
  static const String            NINJAMER_2049_URL ;
  static const String            NINJAMER_2050_URL ;
  static const String            NINJAMER_2051_URL ;
  static const String            NINJAMER_2052_URL ;
#if DEBUG_LOCALHOST_LOGIN_BUTTON
  static const String            LOCALHOST_2049_URL ;
  static const int               N_KNOWN_HOSTS = 9 ;
#else // DEBUG_LOCALHOST_LOGIN_BUTTON
  static const int               N_KNOWN_HOSTS = 8 ;
#endif // DEBUG_LOCALHOST_LOGIN_BUTTON
  static const Identifier        NINBOT_USER ;
  static const Identifier        JAMBOT_USER ;
  static const int               N_KNOWN_BOTS = 2 ;
  static const Array<String>     KNOWN_HOSTS ;
  static const Array<Identifier> KNOWN_BOTS ;

  // login
  static const StringRef HOST_MASK ;
  static const StringRef LETTERS ;
  static const StringRef DIGITS ;
  static const StringRef URL_CHARS ;
} ;


class GUI
{
public:

  // common
  static const int PAD     = 4 ;
  static const int PAD2    = PAD * 2 ;
  static const int PAD3    = PAD * 3 ;
  static const int PAD4    = PAD * 4 ;
  static const int LABEL_H = 12 ;

  // Main
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

  // MainContent
  static const String CONTENT_GUI_ID ;
  static const int    CONTENT_W = 630 ;
  static const int    CONTENT_H = 470 ;

  // Background
  static const String BACKGROUND_GUI_ID ;

  // Login
  static const String LOGIN_GUI_ID ;
  static const int    LOGIN_BUTTON_L = GUI::PAD ;
  static const int    LOGIN_BUTTON_T = GUI::PAD ;
  static const int    LOGIN_BUTTON_W = 96 ;
  static const int    LOGIN_BUTTON_H = 24 ;

  // License
  static const String LICENSE_GUI_ID ;

  // Chat
  static const String CHAT_GUI_ID ;
  static const String SERVER_NICK ;
  static const String UNKNOWN_COMMAND_MSG ;
  static const String INVALID_PM_MSG ;

  // Channel
  static const String MASTER_CHANNEL_GUI_ID ;
  static const String METRO_CHANNEL_GUI_ID ;
  static const String XMIT_LABEL_TEXT ;
  static const String RCV_LABEL_TEXT ;
  static const int    N_STATIC_CHANNEL_CHILDREN = 2 ;
  static const int    CHANNEL_Y                 = LABEL_H + PAD2 ;
  static const int    CHANNEL_W                 = 60 ;
  static const int    CHANNEL_H                 = 252 ;
  static const int    VU_RANGE                  = 140 ;
  static const int    VU_OFFSET                 = 120 ;

  // Channels
  static const String     MASTER_MIXERGROUP_GUI_ID ;
  static const Identifier MASTER_MIXERGROUP_IDENTIFIER ;
  static const String     LOCAL_MIXERGROUP_GUI_ID ;
  static const Identifier LOCAL_MIXERGROUP_IDENTIFIER ;
  static const int        MIXERGROUP_Y  = PAD ;
  static const int        MIXERGROUP_H  = CHANNEL_H + LABEL_H + PAD3 ;
  static       int        MIXERGROUP_W(int n_channels) { return PAD + (n_channels * (CHANNEL_W + PAD)) ; }
  static const int        MASTERGROUP_W =                       PAD + (2          * (CHANNEL_W + PAD)) ;

  // Mixer
  static const String      MIXER_GUI_ID ;
  static const Identifier ACTIVEUSERS_IDENTIFIER ;
  static const int        MIXER_H                 = PAD2 + MIXERGROUP_H ;
  static const int        RESIZER_W               = PAD  + 2 ;
  static const int        N_STATIC_MIXER_CHILDREN = 5 ;
  static const int        LOCALS_IDX              = 0 ;
  static const int        FIRST_REMOTE_IDX        = 1 ;
  static const int        CHANNEL_SCROLL_BTN_Y    = MIXERGROUP_Y + (MIXERGROUP_H / 4) ;
  static const int        CHANNEL_SCROLL_BTN_W    = 24 ;
  static const int        CHANNEL_SCROLL_BTN_H    = MIXERGROUP_H / 2 ;

  // StatusBar
  static const String STATUS_GUI_ID ;
  static const int    STATUSBAR_H  = 24 ;
  static const int    STATUS_W     = 160 ;
  static const int    STATUS_H     = 16 ;
  static const int    STATUS_PAD_X = 8 ;
  static const int    STATUS_PAD_Y = 2 ;

  // Loop
  static const String LOOP_GUI_ID ;
  static const int    LOOP_X = STATUS_W + PAD3 ;
  static const int    LOOP_H = STATUS_H ;
} ;


class CONFIG
{
public:

  static const String     PERSISTENCE_FILENAME ;
  static const String     PERSISTENCE_KEY ;
  static const Identifier PERSISTENCE_IDENTIFIER ;

  // client config
  static const String     CLIENT_KEY ;
  static const Identifier CLIENT_IDENTIFIER ;
  static const String     SAVE_AUDIO_KEY ;
  static const Identifier SAVE_AUDIO_IDENTIFIER ;
  static const String     SAVE_LOG_KEY ;
  static const Identifier SAVE_LOG_IDENTIFIER ;
  static const String     DEBUGLEVEL_KEY ;
  static const Identifier DEBUGLEVEL_IDENTIFIER ;
  static const String     AUTOSUBSCRIBE_KEY ;
  static const Identifier AUTOSUBSCRIBE_IDENTIFIER ;
  static const String     SESSIONDIR_KEY ;
  static const Identifier SESSIONDIR_IDENTIFIER ;
  static const String     LOGFILE_KEY ;
  static const Identifier LOGFILE_IDENTIFIER ;
  static const String     SESSIONDIR ;
  static const String     LOGFILE ;
  static const String     SUBSCRIPTIONS_KEY ;
  static const Identifier SUBSCRIPTIONS_IDENTIFIER ;

  // device config
  static const String     AUDIO_KEY ;
  static const Identifier AUDIO_IDENTIFIER ;
  static const String     AUDIO_IF_KEY ;
  static const Identifier AUDIO_IF_IDENTIFIER ;
  static const String     BITDEPTH_KEY ;
  static const Identifier BITDEPTH_IDENTIFIER ;
  static const String     SAMPLERATE_KEY ;
  static const Identifier SAMPLERATE_IDENTIFIER ;
  static const String     N_INPUTS_KEY ;
  static const Identifier N_INPUTS_IDENTIFIER ;
  static const String     N_OUTPUTS_KEY ;
  static const Identifier N_OUTPUTS_IDENTIFIER ;
  static const String     JACK_NAME_KEY ;
  static const Identifier JACK_NAME_IDENTIFIER ;

  // network
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
  static const String     BOTS_KEY ;
  static const Identifier BOTS_IDENTIFIER ;

  // channels
  static const String     MASTERS_KEY ;
  static const Identifier MASTERS_IDENTIFIER ;
  static const String     MASTER_KEY ;
  static const Identifier MASTER_IDENTIFIER ;
  static const String     METRO_KEY ;
  static const Identifier METRO_IDENTIFIER ;
  static const String     LOCALS_KEY ;
  static const Identifier LOCALS_IDENTIFIER ;
  static const String     VOLUME_KEY ;
  static const Identifier VOLUME_IDENTIFIER ;
  static const String     PAN_KEY ;
  static const Identifier PAN_IDENTIFIER ;
  static const String     XMIT_KEY ;
  static const Identifier XMIT_IDENTIFIER ;
  static const String     MUTE_KEY ;
  static const Identifier MUTE_IDENTIFIER ;
  static const String     SOLO_KEY ;
  static const Identifier SOLO_IDENTIFIER ;
  static const String     SOURCE_N_KEY ;
  static const Identifier SOURCE_N_IDENTIFIER ;
  static const String     STEREO_KEY ;
  static const Identifier STEREO_IDENTIFIER ;

  // validation
  static const StringRef VALID_NAME_CHARS ;
  static const StringRef AT_CHAR ;

  // defaults
  static const String     INITIAL_LOCAL_KEY ;
  static const Identifier INITIAL_LOCAL_IDENTIFIER ;
  static const String     DEFAULT_NAME ;
  static const String     DEFAULT_CHANNEL_NAME ;
  static const String     DEFAULT_USER_NAME ;
  static const float      DEFAULT_VOLUME ;
  static const float      DEFAULT_PAN ;
  static const bool       DEFAULT_IS_XMIT ;
  static const bool       DEFAULT_IS_MUTE ;
  static const bool       DEFAULT_IS_SOLO ;
  static const int        DEFAULT_SOURCE_N ;
  static const bool       DEFAULT_IS_STEREO ;
  static const int        DEFAULT_AUDIO_IF = audioStreamer::WINDOWS_AUDIO_ASIO ;
  static const String     DEFAULT_CONFIG_XML ;
} ;

#endif // _CONSTANTS_H_
