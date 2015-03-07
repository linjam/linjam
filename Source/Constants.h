/*
  ==============================================================================

    Constants.h
    Created: 24 May 2014 11:41:00am
    Author:  me

  ==============================================================================
*/

#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <ninjam/audiostream.h>
#include <ninjam/njclient.h>
#include "JuceHeader.h"

/*\ CAVEATS:
|*|  when adding GUI components to Channels be sure to update N_STATIC_CHANNELS_CHILDREN
|*|    and when adding GUI components to Mixer be sure to update N_STATIC_MIXER_CHILDREN
|*|    or else segfault is a near certainty
|*|
|*|  when adding nodes or properties to CONFIG_XML be sure to
|*|    * document them in                     LinJamConfig.h
|*|    * denote property datatypes in         #define CONFIG_TYPES_XML
|*|    * switch on nodes in                   LinJamConfig::restoreVarTypeInfo()
|*|    * verify nodes in                      LinJamConfig::sanityCheck()
|*|    * if channel property - verify data in LinJamConfig::sanityCheckChannels()
|*|                            and add to     LinJamConfig::newChannel()
|*|    * optionally dump data or errors in    #define DEBUG_TRACE_SANITY_CHECK
|*|                                           #define DEBUG_TRACE_SANITY_CHECK_CHANNEL
|*|                                           #define DEBUG_TRACE_ADD_CHANNEL_GUI
|*|                                           #define DEBUG_TRACE_CONFIGURE_LOCAL_CHANNEL
|*|                                           #define DEBUG_TRACE_REMOTE_CHANNELS
|*|                                           #define DEBUG_TRACE_CONFIGURE_REMOTE
\*/


#define CONFIG_XML "<?xml version=\"1.0\"?><"                                 + \
  PERSISTENCE_KEY          + "><"                                             + \
    CLIENT_KEY             + " "                                              + \
      SAVE_AUDIO_MODE_KEY  + "=\"" + String(DEFAULT_SAVE_AUDIO_MODE)  + "\" " + \
      MIXDOWN_MODE_KEY     + "=\"" + String(DEFAULT_MIXDOWN_MODE)     + "\" " + \
      SHOULD_SAVE_LOG_KEY  + "=\"" + String(DEFAULT_SHOULD_SAVE_LOG)  + "\" " + \
      DEBUG_LEVEL_KEY      + "=\"" + String(DEFAULT_DEBUG_LEVEL)      + "\" " + \
      SHOULD_HIDE_BOTS_KEY + "=\"" + String(DEFAULT_SHOULD_HIDE_BOTS) + "\" " + \
    "/><"                                                                     + \
    SUBSCRIPTIONS_KEY      + " "                                              + \
      SUBSCRIBE_MODE_KEY   + "=\"" + String(DEFAULT_SUBSCRIBE_MODE)   + "\" " + \
    "/><"                                                                     + \
    AUDIO_KEY              + " "                                              + \
      WIN_AUDIO_IF_KEY     + "=\"" + String(DEFAULT_WIN_AUDIO_IF)     + "\" " + \
      ASIO_DRIVER_KEY      + "=\"" + String(DEFAULT_ASIO_DRIVER)      + "\" " + \
      ASIO_INPUT0_KEY      + "=\"" + String(DEFAULT_ASIO_INPUT0)      + "\" " + \
      ASIO_INPUT1_KEY      + "=\"" + String(DEFAULT_ASIO_INPUT1)      + "\" " + \
      ASIO_OUTPUT0_KEY     + "=\"" + String(DEFAULT_ASIO_OUTPUT0)     + "\" " + \
      ASIO_OUTPUT1_KEY     + "=\"" + String(DEFAULT_ASIO_OUTPUT1)     + "\" " + \
      KS_INPUT_KEY         + "=\"" + String(DEFAULT_KS_INPUT)         + "\" " + \
      KS_OUTPUT_KEY        + "=\"" + String(DEFAULT_KS_OUTPUT)        + "\" " + \
      KS_BITDEPTH_KEY      + "=\"" + String(DEFAULT_KS_BITDEPTH)      + "\" " + \
      KS_SAMPLERATE_KEY    + "=\"" + String(DEFAULT_KS_SAMPLERATE)    + "\" " + \
      KS_BLOCKSIZE_KEY     + "=\"" + String(DEFAULT_KS_BLOCKSIZE)     + "\" " + \
      KS_NBLOCKS_KEY       + "=\"" + String(DEFAULT_KS_N_BLOCKS)      + "\" " + \
      DS_INPUT0_KEY        + "=\"" + String(DEFAULT_DS_INPUT0)        + "\" " + \
      DS_INPUT1_KEY        + "=\"" + String(DEFAULT_DS_INPUT1)        + "\" " + \
      DS_INPUT2_KEY        + "=\"" + String(DEFAULT_DS_INPUT2)        + "\" " + \
      DS_INPUT3_KEY        + "=\"" + String(DEFAULT_DS_INPUT3)        + "\" " + \
      DS_OUTPUT0_KEY       + "=\"" + String(DEFAULT_DS_OUTPUT0)       + "\" " + \
      DS_OUTPUT1_KEY       + "=\"" + String(DEFAULT_DS_OUTPUT1)       + "\" " + \
      DS_OUTPUT2_KEY       + "=\"" + String(DEFAULT_DS_OUTPUT2)       + "\" " + \
      DS_OUTPUT3_KEY       + "=\"" + String(DEFAULT_DS_OUTPUT3)       + "\" " + \
      DS_BITDEPTH_KEY      + "=\"" + String(DEFAULT_DS_BITDEPTH)      + "\" " + \
      DS_SAMPLERATE_KEY    + "=\"" + String(DEFAULT_DS_SAMPLERATE)    + "\" " + \
      DS_BLOCKSIZE_KEY     + "=\"" + String(DEFAULT_DS_BLOCKSIZE)     + "\" " + \
      DS_NBLOCKS_KEY       + "=\"" + String(DEFAULT_DS_N_BLOCKS)      + "\" " + \
      WAVE_INPUT_KEY       + "=\"" + String(DEFAULT_WAVE_INPUT)       + "\" " + \
      WAVE_OUTPUT_KEY      + "=\"" + String(DEFAULT_WAVE_OUTPUT)      + "\" " + \
      WAVE_BITDEPTH_KEY    + "=\"" + String(DEFAULT_WAVE_BITDEPTH)    + "\" " + \
      WAVE_SAMPLERATE_KEY  + "=\"" + String(DEFAULT_WAVE_SAMPLERATE)  + "\" " + \
      WAVE_BLOCKSIZE_KEY   + "=\"" + String(DEFAULT_WAVE_BLOCKSIZE)   + "\" " + \
      WAVE_NBLOCKS_KEY     + "=\"" + String(DEFAULT_WAVE_N_BLOCKS)    + "\" " + \
      MAC_DEVICE_KEY       + "=\"" + String(DEFAULT_MAC_DEVICE)       + "\" " + \
      MAC_NINPUTS_KEY      + "=\"" + String(DEFAULT_N_INPUTS)         + "\" " + \
      MAC_BITDEPTH_KEY     + "=\"" + String(DEFAULT_MAC_BITDEPTH)     + "\" " + \
      MAC_SAMPLERATE_KEY   + "=\"" + String(DEFAULT_MAC_SAMPLERATE)   + "\" " + \
      NIX_AUDIO_IF_KEY     + "=\"" + String(DEFAULT_NIX_AUDIO_IF)     + "\" " + \
      JACK_SERVER_KEY      + "=\"" + String(DEFAULT_JACK_SERVER)      + "\" " + \
      JACK_NAME_KEY        + "=\"" + String(DEFAULT_JACK_NAME)        + "\" " + \
      JACK_NINPUTS_KEY     + "=\"" + String(DEFAULT_N_INPUTS)         + "\" " + \
      JACK_NOUTPUTS_KEY    + "=\"" + String(DEFAULT_N_OUTPUTS)        + "\" " + \
      ALSA_CONFIG_KEY      + "=\"" + String(DEFAULT_ALSA_CONFIG)      + "\" " + \
    "/><"                                                                     + \
    SERVER_KEY             + " "                                              + \
      HOST_KEY             + "=\"" + String(DEFAULT_HOST)             + "\" " + \
      LOGIN_KEY            + "=\"" + String(DEFAULT_LOGIN)            + "\" " + \
      PASS_KEY             + "=\"" + String(DEFAULT_PASS)             + "\" " + \
      IS_ANONYMOUS_KEY     + "=\"" + String(DEFAULT_IS_ANONYMOUS)     + "\" " + \
      IS_AGREED_KEY        + "=\"" + String(DEFAULT_IS_AGREED)        + "\" " + \
      SHOULD_AGREE_KEY     + "=\"" + String(DEFAULT_SHOULD_AGREE)     + "\" " + \
    "/><"                                                                     + \
    SERVERS_KEY            + " /><"                                           + \
    MASTERS_KEY            + "><"                                             + \
      MASTER_KEY           + " "                                              + \
        CHANNEL_NAME_KEY   + "=\"" + String(MASTER_KEY)               + "\" " + \
        VOLUME_KEY         + "=\"" + String(DEFAULT_VOLUME)           + "\" " + \
        PAN_KEY            + "=\"" + String(DEFAULT_PAN)              + "\" " + \
        IS_MUTED_KEY       + "=\"" + String(DEFAULT_IS_MUTED)         + "\" " + \
        STEREO_KEY         + "=\"" + String(STEREO)                   + "\" " + \
        VU_LEFT_KEY        + "=\"" + String(DEFAULT_VU)               + "\" " + \
        VU_RIGHT_KEY       + "=\"" + String(DEFAULT_VU)               + "\" " + \
    "/><"                                                                     + \
      METRO_KEY            + " "                                              + \
        CHANNEL_NAME_KEY   + "=\"" + String(METRO_KEY)                + "\" " + \
        VOLUME_KEY         + "=\"" + String(DEFAULT_VOLUME)           + "\" " + \
        PAN_KEY            + "=\"" + String(DEFAULT_PAN)              + "\" " + \
        IS_MUTED_KEY       + "=\"" + String(DEFAULT_IS_MUTED)         + "\" " + \
        SOURCE_N_KEY       + "=\"" + String(DEFAULT_SOURCE_N)         + "\" " + \
        STEREO_KEY         + "=\"" + String(STEREO)                   + "\" " + \
        VU_LEFT_KEY        + "=\"" + String(DEFAULT_VU)               + "\" " + \
        VU_RIGHT_KEY       + "=\"" + String(DEFAULT_VU)               + "\" " + \
    "/>"                                                                      + \
    "</" + MASTERS_KEY     + "><"                                             + \
    LOCALS_KEY             + " /><"                                           + \
    REMOTES_KEY            + " />"                                            + \
  "</" + PERSISTENCE_KEY   + ">"

#define CONFIG_TYPES_XML "<?xml version=\"1.0\"?><"            + \
  PERSISTENCE_TYPES_KEY          + "><"                        + \
    CLIENT_KEY                   + " "                         + \
      SAVE_AUDIO_MODE_KEY        + "=\"" + INT_TYPE    + "\" " + \
      MIXDOWN_MODE_KEY           + "=\"" + INT_TYPE    + "\" " + \
      SHOULD_SAVE_LOG_KEY        + "=\"" + BOOL_TYPE   + "\" " + \
      DEBUG_LEVEL_KEY            + "=\"" + INT_TYPE    + "\" " + \
      SHOULD_HIDE_BOTS_KEY       + "=\"" + BOOL_TYPE   + "\" " + \
    "/><"                                                      + \
    SUBSCRIPTIONS_KEY            + " "                         + \
      SUBSCRIBE_MODE_KEY         + "=\"" + INT_TYPE    + "\" " + \
    "/><"                                                      + \
    AUDIO_KEY                    + " "                         + \
      WIN_AUDIO_IF_KEY           + "=\"" + INT_TYPE    + "\" " + \
      ASIO_DRIVER_KEY            + "=\"" + INT_TYPE    + "\" " + \
      ASIO_INPUT0_KEY            + "=\"" + INT_TYPE    + "\" " + \
      ASIO_INPUT1_KEY            + "=\"" + INT_TYPE    + "\" " + \
      ASIO_OUTPUT0_KEY           + "=\"" + INT_TYPE    + "\" " + \
      ASIO_OUTPUT1_KEY           + "=\"" + INT_TYPE    + "\" " + \
      KS_INPUT_KEY               + "=\"" + INT_TYPE    + "\" " + \
      KS_OUTPUT_KEY              + "=\"" + INT_TYPE    + "\" " + \
      KS_BITDEPTH_KEY            + "=\"" + INT_TYPE    + "\" " + \
      KS_SAMPLERATE_KEY          + "=\"" + INT_TYPE    + "\" " + \
      KS_NBLOCKS_KEY             + "=\"" + INT_TYPE    + "\" " + \
      KS_BLOCKSIZE_KEY           + "=\"" + INT_TYPE    + "\" " + \
      DS_INPUT0_KEY              + "=\"" + INT_TYPE    + "\" " + \
      DS_INPUT1_KEY              + "=\"" + INT_TYPE    + "\" " + \
      DS_INPUT2_KEY              + "=\"" + INT_TYPE    + "\" " + \
      DS_INPUT3_KEY              + "=\"" + INT_TYPE    + "\" " + \
      DS_OUTPUT0_KEY             + "=\"" + INT_TYPE    + "\" " + \
      DS_OUTPUT1_KEY             + "=\"" + INT_TYPE    + "\" " + \
      DS_OUTPUT2_KEY             + "=\"" + INT_TYPE    + "\" " + \
      DS_OUTPUT3_KEY             + "=\"" + INT_TYPE    + "\" " + \
      DS_BITDEPTH_KEY            + "=\"" + INT_TYPE    + "\" " + \
      DS_SAMPLERATE_KEY          + "=\"" + INT_TYPE    + "\" " + \
      DS_NBLOCKS_KEY             + "=\"" + INT_TYPE    + "\" " + \
      DS_BLOCKSIZE_KEY           + "=\"" + INT_TYPE    + "\" " + \
      WAVE_INPUT_KEY             + "=\"" + INT_TYPE    + "\" " + \
      WAVE_OUTPUT_KEY            + "=\"" + INT_TYPE    + "\" " + \
      WAVE_BITDEPTH_KEY          + "=\"" + INT_TYPE    + "\" " + \
      WAVE_SAMPLERATE_KEY        + "=\"" + INT_TYPE    + "\" " + \
      WAVE_NBLOCKS_KEY           + "=\"" + INT_TYPE    + "\" " + \
      WAVE_BLOCKSIZE_KEY         + "=\"" + INT_TYPE    + "\" " + \
      MAC_DEVICE_KEY             + "=\"" + STRING_TYPE + "\" " + \
      MAC_NINPUTS_KEY            + "=\"" + INT_TYPE    + "\" " + \
      MAC_BITDEPTH_KEY           + "=\"" + INT_TYPE    + "\" " + \
      MAC_SAMPLERATE_KEY         + "=\"" + INT_TYPE    + "\" " + \
      NIX_AUDIO_IF_KEY           + "=\"" + INT_TYPE    + "\" " + \
      JACK_SERVER_KEY            + "=\"" + INT_TYPE    + "\" " + \
      JACK_NAME_KEY              + "=\"" + STRING_TYPE + "\" " + \
      JACK_NINPUTS_KEY           + "=\"" + INT_TYPE    + "\" " + \
      JACK_NOUTPUTS_KEY          + "=\"" + INT_TYPE    + "\" " + \
      ALSA_CONFIG_KEY            + "=\"" + STRING_TYPE + "\" " + \
    "/><"                                                      + \
    SERVER_KEY                   + " "                         + \
      HOST_KEY                   + "=\"" + STRING_TYPE + "\" " + \
      LOGIN_KEY                  + "=\"" + STRING_TYPE + "\" " + \
      PASS_KEY                   + "=\"" + STRING_TYPE + "\" " + \
      IS_ANONYMOUS_KEY           + "=\"" + BOOL_TYPE   + "\" " + \
      IS_AGREED_KEY              + "=\"" + BOOL_TYPE   + "\" " + \
      SHOULD_AGREE_KEY           + "=\"" + BOOL_TYPE   + "\" " + \
    "/><"                                                      + \
    USERS_KEY                    + " "                         + \
      USER_IDX_KEY               + "=\"" + INT_TYPE    + "\" " + \
    "/><"                                                      + \
    CHANNELS_KEY                 + " "                         + \
      CHANNEL_NAME_KEY           + "=\"" + STRING_TYPE + "\" " + \
      CHANNEL_IDX_KEY            + "=\"" + INT_TYPE    + "\" " + \
      PAIR_IDX_KEY               + "=\"" + INT_TYPE    + "\" " + \
      VOLUME_KEY                 + "=\"" + DOUBLE_TYPE + "\" " + \
      PAN_KEY                    + "=\"" + DOUBLE_TYPE + "\" " + \
      IS_XMIT_RCV_KEY            + "=\"" + BOOL_TYPE   + "\" " + \
      IS_MUTED_KEY               + "=\"" + BOOL_TYPE   + "\" " + \
      IS_SOLO_KEY                + "=\"" + BOOL_TYPE   + "\" " + \
      SOURCE_N_KEY               + "=\"" + INT_TYPE    + "\" " + \
      STEREO_KEY                 + "=\"" + INT_TYPE    + "\" " + \
      VU_LEFT_KEY                + "=\"" + DOUBLE_TYPE + "\" " + \
      VU_RIGHT_KEY               + "=\"" + DOUBLE_TYPE + "\" " + \
    "/>"                                                       + \
  "</" + PERSISTENCE_TYPES_KEY   + ">"


namespace CLIENT
{
  // client
  static const String SERVER_FULL_STATUS = "server full" ;
  static const int    BOT_USERIDX        = 0 ;
  static const int    BOT_CHANNELIDX     = 0 ;
  static const uint8  CHATMSG_TYPE_IDX   = 0 ;
  static const uint8  CHATMSG_USER_IDX   = 1 ;
  static const uint8  CHATMSG_MSG_IDX    = 2 ;

  // chat
  static const String    CHATMSG_TYPE_TOPIC   = "TOPIC" ;
  static const String    CHATMSG_TYPE_MSG     = "MSG" ;
  static const String    CHATMSG_TYPE_PRIVMSG = "PRIVMSG" ;
  static const String    CHATMSG_TYPE_JOIN    = "JOIN" ;
  static const String    CHATMSG_TYPE_PART    = "PART" ;
  static const String    CHATMSG_TYPE_ADMIN   = "ADMIN" ;
  static const String    CHATMSG_CMD_ME       = "/me " ;
  static const String    CHATMSG_CMD_MSG      = "/msg " ;
  static const String    CHATMSG_CMD_TOPIC    = "/topic " ;
  static const String    CHATMSG_CMD_KICK     = "/kick " ;
  static const String    CHATMSG_CMD_BPM      = "/bpm " ;
  static const String    CHATMSG_CMD_BPI      = "/bpi " ;
  static const String    CHATMSG_CMD_ADMIN    = "/admin " ;
  static const StringRef CHATMSG_CMD_VOTE     = "!vote " ;

  // main
  static const int CLIENT_TIMER_ID = 0 ; static const int CLIENT_DRIVER_IVL = 50 ;
  static const int GUI_TIMER_HI_ID = 1 ; static const int GUI_UPDATE_HI_IVL = 125 ;
  static const int GUI_TIMER_LO_ID = 2 ; static const int GUI_UPDATE_LO_IVL = 30000 ;

  // ConfigAudio options
  static const String      ASIO_DEVICE_TYPE       = "ASIO" ;
  static const String      DS_DEVICE_TYPE         = "DirectSound" ;
  static const String      WASAPI_DEVICE_TYPE     = "WASAPI" ;
  static const String      CA_DEVICE_TYPE         = "CoreAudio" ;
  static const String      JACK_DEVICE_TYPE       = "JACK" ;
  static const String      ALSA_DEVICE_TYPE       = "ALSA" ;
  static const String      ROID_DEVICE_TYPE       = "Android" ;
  static const String      SLES_DEVICE_TYPE       = "OpenSLES" ;
  static const String      IOS_DEVICE_TYPE        = "iOSAudio" ;
  static const String      KS_DEVICE_TYPE         = "Win32KernaelStreaming" ; // non-juce
  static const String      WAVE_DEVICE_TYPE       = "Win32Wave" ;             // non-juce
  static const String      NFG_DEVICE_TYPE        = "unknown" ;               // non-juce
  static const StringArray WIN_AUDIO_IFS          =
      StringArray::fromLines(StringRef("asio\nkernel streaming\ndirect sound\nwave out")) ;
  static const StringArray NIX_AUDIO_IFS          =
      StringArray::fromLines(StringRef("jack\nalsa")) ;
  static const StringArray BUFFER_SIZES           =
      StringArray::fromLines(StringRef("32\n64\n128\n256\n512\n1024\n2048\n4096\n8192")) ;
  static const int         BIT_DEPTH_16           = 16 ;
  static const int         BIT_DEPTH_24           = 24 ;
  static const int         BIT_DEPTH_32           = 32 ;
  static const int         SAMPLE_RATE_44100      = 44100 ;
  static const int         SAMPLE_RATE_48000      = 48000 ;
  static const int         SAMPLE_RATE_96000      = 96000 ;
  static const int         MIN_N_BUFFERS          = 2 ;
  static const int         MAX_N_BUFFERS          = 16 ;
  static const int         MIN_N_SOURCES          = 0 ;
  static const int         MAX_N_SOURCES          = 16 ;
  static const int         MIN_N_SINKS            = 0 ;
  static const int         MAX_N_SINKS            = 16 ;
  static const double      VU_DB_RANGE            = 140.0 ;
  static const double      VU_DB_MIN              = -120.0 ;
  static const char*       ASIO_DEVICE_FMT        = "%d:%d,%d:%d,%d" ;

  // configuration
  static const String STEREO_L_POSTFIX       = "-L" ;
  static const String STEREO_R_POSTFIX       = "-R" ;
  static const int    STEREO_POSTFIX_N_CHARS = STEREO_L_POSTFIX.length() ;
}


namespace NETWORK
{
  // known hosts
  static const String            LOCALHOST_HOSTNAME         = "localhost" ;
  static const String            LOCALHOST_2049_URL         = LOCALHOST_HOSTNAME + ":2049" ;
  static const String            NINJAM_2049_URL            = "test-ninjam-com-2049" ;
  static const String            NINJAM_2050_URL            = "test.ninjam.com:2050" ;
  static const String            NINJAM_2051_URL            = "test.ninjam.com:2051" ;
  static const String            NINJAM_2052_URL            = "test.ninjam.com:2052" ;
  static const String            NINJAM_2600_URL            = "test.ninjam.com:2600" ;
  static const String            NINJAM_2601_URL            = "test.ninjam.com:2601" ;
  static const String            NINBOT_2049_URL            = "ninbot.com:2049" ;
  static const String            NINBOT_2050_URL            = "ninbot.com:2050" ;
  static const String            NINBOT_2051_URL            = "ninbot.com:2051" ;
  static const String            NINBOT_2052_URL            = "ninbot.com:2052" ;
  static const String            NINJAMER_2049_URL          = "ninjamer.com:2049" ;
  static const String            NINJAMER_2050_URL          = "ninjamer.com:2050" ;
  static const String            NINJAMER_2051_URL          = "ninjamer.com:2051" ;
  static const String            NINJAMER_2052_URL          = "ninjamer.com:2052" ;
  static const Identifier        NINBOT_USER                = "ninbot" ;
  static const Identifier        JAMBOT_USER                = "Jambot" ;
  static const int               N_KNOWN_BOTS               = 2 ;
#ifndef DEBUG_LOCALHOST_LOGIN_BUTTON
  static const int               N_KNOWN_HOSTS              = 8 ;
  static const String            known_hosts[N_KNOWN_HOSTS] = {
#else // DEBUG_LOCALHOST_LOGIN_BUTTON
  static const int               N_KNOWN_HOSTS              = 9 ;
  static const String            known_hosts[N_KNOWN_HOSTS] = {
                                     LOCALHOST_2049_URL       ,
#endif // DEBUG_LOCALHOST_LOGIN_BUTTON
                                     NINBOT_2049_URL          ,
                                     NINBOT_2050_URL          ,
                                     NINBOT_2051_URL          ,
                                     NINBOT_2052_URL          ,
                                     NINJAMER_2049_URL        ,
                                     NINJAMER_2050_URL        ,
                                     NINJAMER_2051_URL        ,
                                     NINJAMER_2052_URL        } ;
  static const Identifier        known_bots[N_KNOWN_BOTS]   = {
                                     NINBOT_USER              ,
                                     JAMBOT_USER              } ;
  static const Array<String>     KNOWN_HOSTS                =
               Array<String>(    known_hosts , N_KNOWN_HOSTS) ;
  static const Array<Identifier> KNOWN_BOTS                 =
               Array<Identifier>(known_bots  , N_KNOWN_BOTS) ;

  // login
  static const StringRef HOST_MASK = "*.*:*" ;
  static const StringRef LETTERS   = "abcdefghijklmnopqrstuvwxyz" ;
  static const StringRef DIGITS    = "0123456789" ;
  static const StringRef URL_CHARS = "0123456789abcdefghijklmnopqrstuvwxyz-." ;
}


namespace CONFIG
{
  // config root keys
  static const String     PERSISTENCE_FILENAME  = "linjam.xml" ;
  static const String     PERSISTENCE_KEY       = "linjam-data" ;
  static const Identifier PERSISTENCE_ID        = PERSISTENCE_KEY ;
  static const String     PERSISTENCE_TYPES_KEY = PERSISTENCE_KEY + "-types" ;

  // client config keys
  static const String     CLIENT_KEY           = "client" ;
  static const Identifier CLIENT_ID            = CLIENT_KEY ;
  static const String     SAVE_AUDIO_MODE_KEY  = "save-multitrack-mode" ;
  static const Identifier SAVE_AUDIO_MODE_ID   = SAVE_AUDIO_MODE_KEY ;
  static const String     MIXDOWN_MODE_KEY     = "save-mixdown-mode" ;
  static const Identifier MIXDOWN_MODE_ID      = MIXDOWN_MODE_KEY ;
  static const String     SHOULD_SAVE_LOG_KEY  = "should-save-log" ;
  static const Identifier SHOULD_SAVE_LOG_ID   = SHOULD_SAVE_LOG_KEY ;
  static const String     DEBUG_LEVEL_KEY      = "debug-level" ;
  static const Identifier DEBUG_LEVEL_ID       = DEBUG_LEVEL_KEY ;
  static const String     SHOULD_HIDE_BOTS_KEY = "should-hide-bots" ;
  static const Identifier SHOULD_HIDE_BOTS_ID  = SHOULD_HIDE_BOTS_KEY ;
  static const String     SESSION_DIR_KEY      = "session-dir" ;
  static const Identifier SESSION_DIR_ID       = SESSION_DIR_KEY ;
  static const String     LOG_FILE_KEY         = "log-file" ;
  static const Identifier LOG_FILE_ID          = LOG_FILE_KEY ;
  static const String     SESSION_DIR          = "/session" ;
  static const String     LOG_FILE             = "/clipsort.log" ;

  // subscriptions config keys
  static const String     SUBSCRIPTIONS_KEY  = "subscriptions" ;
  static const Identifier SUBSCRIPTIONS_ID   = SUBSCRIPTIONS_KEY ;
  static const String     SUBSCRIBE_MODE_KEY = "subscribe-mode" ;
  static const Identifier SUBSCRIBE_MODE_ID  = SUBSCRIBE_MODE_KEY ;

  // audio device config keys
  static const String     AUDIO_KEY           = "audio" ;
  static const Identifier AUDIO_ID            = AUDIO_KEY ;
  static const String     WIN_AUDIO_IF_KEY    = "win-audio-if-n" ;
  static const Identifier WIN_AUDIO_IF_ID     = WIN_AUDIO_IF_KEY ;
  static const String     ASIO_DRIVER_KEY     = "asio-driver" ;
  static const Identifier ASIO_DRIVER_ID      = ASIO_DRIVER_KEY ;
  static const String     ASIO_INPUT0_KEY     = "asio-input0" ;
  static const Identifier ASIO_INPUT0_ID      = ASIO_INPUT0_KEY ;
  static const String     ASIO_INPUT1_KEY     = "asio-input1" ;
  static const Identifier ASIO_INPUT1_ID      = ASIO_INPUT1_KEY ;
  static const String     ASIO_OUTPUT0_KEY    = "asio-output0" ;
  static const Identifier ASIO_OUTPUT0_ID     = ASIO_OUTPUT0_KEY ;
  static const String     ASIO_OUTPUT1_KEY    = "asio-output1" ;
  static const Identifier ASIO_OUTPUT1_ID     = ASIO_OUTPUT1_KEY ;
  static const String     KS_INPUT_KEY        = "ks-input" ;
  static const Identifier KS_INPUT_ID         = KS_INPUT_KEY ;
  static const String     KS_OUTPUT_KEY       = "ks-output" ;
  static const Identifier KS_OUTPUT_ID        = KS_OUTPUT_KEY ;
  static const String     KS_SAMPLERATE_KEY   = "ks-sample-rate" ;
  static const Identifier KS_SAMPLERATE_ID    = KS_SAMPLERATE_KEY ;
  static const String     KS_BITDEPTH_KEY     = "ks-bit-depth" ;
  static const Identifier KS_BITDEPTH_ID      = KS_BITDEPTH_KEY ;
  static const String     KS_BLOCKSIZE_KEY    = "ks-block-size" ;
  static const Identifier KS_BLOCKSIZE_ID     = KS_BLOCKSIZE_KEY ;
  static const String     KS_NBLOCKS_KEY      = "ks-n-blocks" ;
  static const Identifier KS_NBLOCKS_ID       = KS_NBLOCKS_KEY ;
  static const String     DS_INPUT0_KEY       = "ds-input0" ;
  static const Identifier DS_INPUT0_ID        = DS_INPUT0_KEY ;
  static const String     DS_INPUT1_KEY       = "ds-input1" ;
  static const Identifier DS_INPUT1_ID        = DS_INPUT1_KEY ;
  static const String     DS_INPUT2_KEY       = "ds-input2" ;
  static const Identifier DS_INPUT2_ID        = DS_INPUT2_KEY ;
  static const String     DS_INPUT3_KEY       = "ds-input3" ;
  static const Identifier DS_INPUT3_ID        = DS_INPUT3_KEY ;
  static const String     DS_OUTPUT0_KEY      = "ds-output0" ;
  static const Identifier DS_OUTPUT0_ID       = DS_OUTPUT0_KEY ;
  static const String     DS_OUTPUT1_KEY      = "ds-output1" ;
  static const Identifier DS_OUTPUT1_ID       = DS_OUTPUT1_KEY ;
  static const String     DS_OUTPUT2_KEY      = "ds-output2" ;
  static const Identifier DS_OUTPUT2_ID       = DS_OUTPUT2_KEY ;
  static const String     DS_OUTPUT3_KEY      = "ds-output3" ;
  static const Identifier DS_OUTPUT3_ID       = DS_OUTPUT3_KEY ;
  static const String     DS_SAMPLERATE_KEY   = "ds-sample-rate" ;
  static const Identifier DS_SAMPLERATE_ID    = DS_SAMPLERATE_KEY ;
  static const String     DS_BITDEPTH_KEY     = "ds-bit-depth" ;
  static const Identifier DS_BITDEPTH_ID      = DS_BITDEPTH_KEY ;
  static const String     DS_BLOCKSIZE_KEY    = "ds-block-size" ;
  static const Identifier DS_BLOCKSIZE_ID     = DS_BLOCKSIZE_KEY ;
  static const String     DS_NBLOCKS_KEY      = "ds-n-blocks" ;
  static const Identifier DS_NBLOCKS_ID       = DS_NBLOCKS_KEY ;
  static const String     WAVE_INPUT_KEY      = "wave-input" ;
  static const Identifier WAVE_INPUT_ID       = WAVE_INPUT_KEY ;
  static const String     WAVE_OUTPUT_KEY     = "wave-output" ;
  static const Identifier WAVE_OUTPUT_ID      = WAVE_OUTPUT_KEY ;
  static const String     WAVE_SAMPLERATE_KEY = "wave-sample-rate" ;
  static const Identifier WAVE_SAMPLERATE_ID  = WAVE_SAMPLERATE_KEY ;
  static const String     WAVE_BITDEPTH_KEY   = "wave-bit-depth" ;
  static const Identifier WAVE_BITDEPTH_ID    = WAVE_BITDEPTH_KEY ;
  static const String     WAVE_BLOCKSIZE_KEY  = "wave-block-size" ;
  static const Identifier WAVE_BLOCKSIZE_ID   = WAVE_BLOCKSIZE_KEY ;
  static const String     WAVE_NBLOCKS_KEY    = "wave-n-blocks" ;
  static const Identifier WAVE_NBLOCKS_ID     = WAVE_NBLOCKS_KEY ;
  static const String     MAC_DEVICE_KEY      = "mac-device" ;
  static const Identifier MAC_DEVICE_ID       = MAC_DEVICE_KEY ;
  static const String     MAC_NINPUTS_KEY     = "mac-n-inputs" ;
  static const Identifier MAC_NINPUTS_ID      = MAC_NINPUTS_KEY ;
  static const String     MAC_SAMPLERATE_KEY  = "mac-sample-rate" ;
  static const Identifier MAC_SAMPLERATE_ID   = MAC_SAMPLERATE_KEY ;
  static const String     MAC_BITDEPTH_KEY    = "mac-bit-depth" ;
  static const Identifier MAC_BITDEPTH_ID     = MAC_BITDEPTH_KEY ;
  static const String     NIX_AUDIO_IF_KEY    = "nix-audio-if-n" ;
  static const Identifier NIX_AUDIO_IF_ID     = NIX_AUDIO_IF_KEY ;
  static const String     JACK_SERVER_KEY     = "jack-server" ;
  static const Identifier JACK_SERVER_ID      = JACK_SERVER_KEY ;
  static const String     JACK_NAME_KEY       = "jack-name" ;
  static const Identifier JACK_NAME_ID        = JACK_NAME_KEY ;
  static const String     JACK_NINPUTS_KEY    = "jack-n-inputs" ;
  static const Identifier JACK_NINPUTS_ID     = JACK_NINPUTS_KEY ;
  static const String     JACK_NOUTPUTS_KEY   = "jack-n-outputs" ;
  static const Identifier JACK_NOUTPUTS_ID    = JACK_NOUTPUTS_KEY ;
  static const String     ALSA_CONFIG_KEY     = "alsa-config" ;
  static const Identifier ALSA_CONFIG_ID      = ALSA_CONFIG_KEY ;

  // login config keys
  static const String     SERVER_KEY       = "server" ;
  static const Identifier SERVER_ID        = SERVER_KEY ;
  static const String     HOST_KEY         = "host" ;
  static const Identifier HOST_ID          = HOST_KEY ;
  static const String     LOGIN_KEY        = "login" ;
  static const Identifier LOGIN_ID         = LOGIN_KEY ;
  static const String     PASS_KEY         = "pass" ;
  static const Identifier PASS_ID          = PASS_KEY ;
  static const String     IS_ANONYMOUS_KEY = "is-anonymous" ;
  static const Identifier IS_ANONYMOUS_ID  = IS_ANONYMOUS_KEY ;
  static const String     IS_AGREED_KEY    = "is-agreed" ;
  static const Identifier IS_AGREED_ID     = IS_AGREED_KEY ;
  static const String     SHOULD_AGREE_KEY = "should-agree" ;
  static const Identifier SHOULD_AGREE_ID  = SHOULD_AGREE_KEY ;
  static const String     SERVERS_KEY      = "servers" ;
  static const Identifier SERVERS_ID       = SERVERS_KEY ;

  // channel config keys
  static const Identifier CONFIG_INIT_ID   = "configure-all" ;
  static const String     MASTERS_KEY      = "master-channels" ;
  static const Identifier MASTERS_ID       = MASTERS_KEY ;
  static const String     MASTER_KEY       = "master" ;
  static const Identifier MASTER_ID        = MASTER_KEY ;
  static const String     METRO_KEY        = "metronome" ;
  static const Identifier METRO_ID         = METRO_KEY ;
  static const String     LOCALS_KEY       = "local-channels" ;
  static const Identifier LOCALS_ID        = LOCALS_KEY ;
  static const String     REMOTES_KEY      = "remote-channels" ;
  static const Identifier REMOTES_ID       = REMOTES_KEY ;
  static const String     USER_IDX_KEY     = "user-idx" ;
  static const Identifier USER_IDX_ID      = USER_IDX_KEY ;
  static const String     CHANNEL_NAME_KEY = "channel-name" ;
  static const Identifier CHANNEL_NAME_ID  = CHANNEL_NAME_KEY ;
  static const String     CHANNEL_IDX_KEY  = "channel-idx" ;
  static const Identifier CHANNEL_IDX_ID   = CHANNEL_IDX_KEY ;
  static const String     PAIR_IDX_KEY     = "stereo-pair-idx" ;
  static const Identifier PAIR_IDX_ID      = PAIR_IDX_KEY ;
  static const String     VOLUME_KEY       = "volume" ;
  static const Identifier VOLUME_ID        = VOLUME_KEY ;
  static const String     PAN_KEY          = "pan" ;
  static const Identifier PAN_ID           = PAN_KEY ;
  static const String     IS_XMIT_RCV_KEY  = "should-xmit-rcv" ;
  static const Identifier IS_XMIT_RCV_ID   = IS_XMIT_RCV_KEY ;
  static const String     IS_MUTED_KEY     = "is-muted" ;
  static const Identifier IS_MUTED_ID      = IS_MUTED_KEY ;
  static const String     IS_SOLO_KEY      = "is-solo" ;
  static const Identifier IS_SOLO_ID       = IS_SOLO_KEY ;
  static const String     SOURCE_N_KEY     = "source-sink-n" ;
  static const Identifier SOURCE_N_ID      = SOURCE_N_KEY ;
  static const String     BIT_DEPTH_KEY    = "bit-depth" ;
  static const Identifier BIT_DEPTH_ID     = BIT_DEPTH_KEY ;
  static const String     STEREO_KEY       = "stereo-status" ;
  static const Identifier STEREO_ID        = STEREO_KEY ;
  static const String     VU_LEFT_KEY      = "vu-left" ;
  static const Identifier VU_LEFT_ID       = VU_LEFT_KEY ;
  static const String     VU_RIGHT_KEY     = "vu-right" ;
  static const Identifier VU_RIGHT_ID      = VU_RIGHT_KEY ;

  // client config defaults
  static const int  SAVE_AUDIO_ENUM_OFFSET  = 2 ;
  static const int  DEFAULT_SAVE_AUDIO_MODE = (int)NJClient::SAVE_AUDIO_DELETE_ASAP ;
  static const int  DEFAULT_MIXDOWN_MODE    = (int)NJClient::SAVE_MIXDOWN_NONE ;
  static const bool DEFAULT_SHOULD_SAVE_LOG = false ;
  static const int  DEFAULT_DEBUG_LEVEL     = (int)NJClient::DEBUG_LEVEL_SILENT ;

  // subscriptions config defaults
  static const int DEFAULT_SUBSCRIBE_MODE = (int)NJClient::SUBSCRIBE_DENY ;

  // audio config defaults
  static const int    DEFAULT_N_INPUTS        = (int)audioStreamer::DEFAULT_N_INPUTS ;
  static const int    DEFAULT_N_OUTPUTS       = (int)audioStreamer::DEFAULT_N_OUTPUTS ;
  static const int    DEFAULT_SAMPLERATE      = (int)audioStreamer::DEFAULT_SAMPLERATE ;
  static const int    DEFAULT_BITDEPTH        = (int)audioStreamer::DEFAULT_BITDEPTH ;
  static const int    DEFAULT_WIN_AUDIO_IF    = (int)audioStreamer::WIN_AUDIO_WAVE ;
  static const int    DEFAULT_ASIO_DRIVER     = 0 ;
  static const int    DEFAULT_ASIO_INPUT0     = 0 ;
  static const int    DEFAULT_ASIO_INPUT1     = 1 ;
  static const int    DEFAULT_ASIO_OUTPUT0    = 0 ;
  static const int    DEFAULT_ASIO_OUTPUT1    = 1 ;
  static const int    DEFAULT_KS_INPUT        = -1 ;
  static const int    DEFAULT_KS_OUTPUT       = -1 ;
  static const int    DEFAULT_KS_BITDEPTH     = DEFAULT_BITDEPTH ;
  static const int    DEFAULT_KS_SAMPLERATE   = DEFAULT_SAMPLERATE ;
  static const int    DEFAULT_KS_N_BLOCKS     = 8 ;
  static const int    DEFAULT_KS_BLOCKSIZE    = 512 ;
  static const int    DEFAULT_DS_INPUT0       = 0 ;
  static const int    DEFAULT_DS_INPUT1       = 0 ;
  static const int    DEFAULT_DS_INPUT2       = 0 ;
  static const int    DEFAULT_DS_INPUT3       = 0 ;
  static const int    DEFAULT_DS_OUTPUT0      = 0 ;
  static const int    DEFAULT_DS_OUTPUT1      = 0 ;
  static const int    DEFAULT_DS_OUTPUT2      = 0 ;
  static const int    DEFAULT_DS_OUTPUT3      = 0 ;
  static const int    DEFAULT_DS_BITDEPTH     = DEFAULT_BITDEPTH ;
  static const int    DEFAULT_DS_SAMPLERATE   = 44100 ;
  static const int    DEFAULT_DS_N_BLOCKS     = 16 ;
  static const int    DEFAULT_DS_BLOCKSIZE    = 1024 ;
  static const int    DEFAULT_WAVE_INPUT      = -1 ;
  static const int    DEFAULT_WAVE_OUTPUT     = -1 ;
  static const int    DEFAULT_WAVE_BITDEPTH   = DEFAULT_BITDEPTH ;
  static const int    DEFAULT_WAVE_SAMPLERATE = 44100 ;
  static const int    DEFAULT_WAVE_N_BLOCKS   = 8 ;
  static const int    DEFAULT_WAVE_BLOCKSIZE  = 4096 ;
  static const String DEFAULT_MAC_DEVICE      = "" ;
  static const int    DEFAULT_MAC_BITDEPTH    = DEFAULT_BITDEPTH ;
  static const int    DEFAULT_MAC_SAMPLERATE  = DEFAULT_SAMPLERATE ;
  static const int    DEFAULT_NIX_AUDIO_IF    = (int)audioStreamer::NIX_AUDIO_JACK ;
  static const int    DEFAULT_JACK_SERVER     = 0 ;
  static const String DEFAULT_JACK_NAME       = "LinJam" ;
  static const String DEFAULT_ALSA_CONFIG     = "" ;

  // login config defaults
  static const String DEFAULT_HOST             = "" ;
  static const String DEFAULT_LOGIN            = "" ;
  static const String DEFAULT_PASS             = "" ;
  static const bool   DEFAULT_IS_ANONYMOUS     = true ;
  static const bool   DEFAULT_IS_AGREED        = false ;
  static const bool   DEFAULT_SHOULD_AGREE     = false ;
  static const bool   DEFAULT_SHOULD_HIDE_BOTS = true ;

  // channel config defaults
  static const Identifier NEWCHANNEL_ID         = "new-channel" ;
  static const String     CHANNEL_BASE_ID       = "channel" ;
  static const String     CHANNELS_KEY          = "channels" ;
  static const Identifier CHANNELS_ID           = CHANNELS_KEY ;
  static const String     USERS_KEY             = "users" ;
  static const Identifier USERS_ID              = USERS_KEY ;
  static const String     DEFAULT_CHANNEL_NAME  = "unnamed" ;
  static const int        DEFAULT_CHANNEL_IDX   = 42 ; // this is o/c outside bounds
  static const int        MASTER_CHANNEL_IDX    = DEFAULT_CHANNEL_IDX ;
  static const float      DEFAULT_VOLUME        = 0.0f ;
  static const float      DEFAULT_PAN           = 0.0f ;
  static const bool       DEFAULT_IS_XMIT_RCV   = true ;
  static const bool       DEFAULT_IS_MUTED      = false ;
  static const bool       DEFAULT_IS_SOLO       = false ;
  static const int        DEFAULT_SOURCE_N      = 0 ;
  static const int        MONO                  =  0 ; // default NJClient mono
  static const int        STEREO_L              = -1 ; // faux-stereo pairs
  static const int        STEREO_R              = +1 ; // faux-stereo pairs
  static const int        STEREO                = 42 ; // masters and metro
  static const int        DEFAULT_STEREO_STATUS = MONO ;
  static const double     DEFAULT_VU            = -120.0 ;

  // config types
  static const String BOOL_TYPE   = "bool" ;
  static const String DOUBLE_TYPE = "double" ;
  static const String INT_TYPE    = "int" ;
  static const String STRING_TYPE = "string" ;

  // validation
  static const StringRef VALID_NAME_CHARS   = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_- " ;
  static const StringRef USER_IP_SPLIT_CHAR = "@" ;

  // config storage
  static const String DEFAULT_CONFIG_XML = String(CONFIG_XML) ;
  static const String CONFIG_TYPES       = String(CONFIG_TYPES_XML) ;
}


namespace GUI
{
  // common
  static const int PAD  = 4 ;
  static const int PAD2 = PAD * 2 ;
  static const int PAD3 = PAD * 3 ;
  static const int PAD4 = PAD * 4 ;

  // MainWindow
  static const String APP_NAME     = "LinJam" ;
  static const int    BORDERS_W    = 2 ;
  static const int    TITLEBAR_H   = 24 ;
  static const int    CONFIG_BTN_X = GUI::PAD ;
  static const int    CONFIG_BTN_Y = 3 ;
  static const int    CONFIG_BTN_W = GUI::TITLEBAR_H - GUI::PAD ;
  static const int    CONFIG_BTN_H = GUI::TITLEBAR_H - GUI::PAD ;

  // MainContent
  static const String CONTENT_GUI_ID = "main-content-gui" ;
  static const int    CONTENT_W      = 640 - BORDERS_W ;
  static const int    CONTENT_H      = 480 - BORDERS_W - TITLEBAR_H ;

  // Background
  static const String BACKGROUND_GUI_ID = "background-gui" ;

  // Config
  static const String DISMISS_BTN_TEXT       = "done" ;
  static const String DISMISS_BTN_ERROR_TEXT = "error" ;

  // ConfigClient
  static const String CONFIG_GUI_ID      = "config-gui" ;
  static const int    CONFIG_SCROLLBAR_W = 12 ;
  static const int    SUBSCRIPTIONS_X    = 24 ;
  static const int    SUBSCRIPTIONS_Y    = 68 ;
  static const int    SUBSCRIPTIONS_W    = 144 ;
  static const int    SUBSCRIPTIONS_H    = 76 ;

  // ConfigAudio
  static const String JACK_NAME_LABEL_TEXT   = "name" ;
  static const String ALSA_CONFIG_LABEL_TEXT = "config" ;

  // ConfigSubscriptions
  static const int SUBSCRIPTION_W = SUBSCRIPTIONS_W - CONFIG_SCROLLBAR_W - PAD2 ;
  static const int SUBSCRIPTION_H = 16 ;

  // Login
  static const String LOGIN_GUI_ID            = "login-gui" ;
  static const int    N_STATIC_LOGIN_CHILDREN = 6 ;
  static const int    LOGIN_BUTTON_L          = GUI::PAD ;
  static const int    LOGIN_BUTTON_T          = GUI::PAD ;
  static const int    LOGIN_BUTTON_W          = 128 ;
  static const int    LOGIN_BUTTON_H          = 24 ;

  // License
  static const String LICENSE_GUI_ID = "license-gui" ;

  // Chat
  static const String CHAT_GUI_ID           = "chat-gui" ;
  static const String SERVER_NICK           = "NINJAM" ;
  static const String TOPIC_TEXT            = "Topic is: " ;
  static const String SET_TOPIC_TEXT        = " sets topic to: " ;
  static const String PM_TEXT               = " (whispers)" ;
  static const String JOINPART_TEXTa        = " has " ;
  static const String JOIN_TEXT             = "joined" ;
  static const String PART_TEXT             = "left" ;
  static const String JOINPART_TEXTb        = " the jam" ;
  static const String UNKNOWN_COMMAND_MSG   = "Error: unknown command" ;
  static const String INVALID_PM_MSG        = "Error: /msg requires a username and a message" ;
  static const int    TOPIC_H               = 16 ;
  static const int    TOPIC_PADDED_H        = TOPIC_H + PAD2 ;
  static const int    MIN_SHOW_TOPIC_CHAT_H = 200 ;

  // Channel
  static const Identifier       MASTER_GUI_ID              = CONFIG::MASTER_ID ;
  static const Identifier       METRO_GUI_ID               = CONFIG::METRO_ID ;
  static const String           XMIT_LABEL_TEXT            = "XMIT" ;
  static const String           RCV_LABEL_TEXT             = "RCV" ;
  static const CharPointer_UTF8 INFINITY_CHAR              = CharPointer_UTF8("\xe2\x88\x9e") ;
  static const int              N_STATIC_CHANNELS_CHILDREN = 4 ;
  static const int              CHANNEL_LABEL_H            = 12 ;
  static const int              CHANNEL_Y                  = CHANNEL_LABEL_H + PAD2 ;
  static const int              CHANNEL_W                  = 60 ;
  static const int              CHANNEL_H                  = 252 ;
  static const int              HOVER_BTN_W                = 15 ;
  static const int              HOVER_BTN_H                = 16 ;
  static const int              HOVER_BTN_XC               = HOVER_BTN_W / 2 ;
  static const int              HOVER_BTN_YC               = HOVER_BTN_H / 2 ;

  // Channels
  static const  Identifier MASTERS_GUI_ID     = CONFIG::MASTERS_ID ;
  static const  Identifier LOCALS_GUI_ID      = CONFIG::LOCALS_ID ;
  static const  String     MASTERS_LABEL_TEXT = "Master" ;
  static const  String     LOCALS_LABEL_TEXT  = "Local" ;
  static const  int        CHANNEL_CONFIG_W   = 200 ;
  static const  int        CHANNEL_CONFIG_H   = 200 ;
  static const  int        MIXERGROUP_Y       = PAD ;
  static const  int        MIXERGROUP_H       = CHANNEL_H + CHANNEL_LABEL_H + PAD3 ;
  static inline int        MIXERGROUP_W(int n_channels)
  {
    return PAD + (n_channels * (CHANNEL_W + PAD)) ;
  }

  // Mixer
  static const String MIXER_GUI_ID            = "mixer-gui" ;
  static const int    MIXER_H                 = PAD2 + MIXERGROUP_H ;
  static const int    RESIZER_W               = PAD  + 2 ;
  static const int    N_STATIC_MIXER_CHILDREN = 5 ;
  static const int    LOCALS_IDX              = 0 ;
  static const int    FIRST_REMOTE_IDX        = 1 ;
  static const int    CHANNEL_SCROLL_BTN_H    = MIXERGROUP_H / 4 ;
  static const int    CHANNEL_SCROLL_BTN_W    = 24 ;
  static const int    CHANNEL_SCROLL_BTN_Y    = MIXERGROUP_Y +
                                               (MIXERGROUP_H / 2) -
                                               (CHANNEL_SCROLL_BTN_H / 2) ;

  // StatusBar
  static const String STATUS_GUI_ID                 = "statusbar-gui" ;
  static const String AUDIO_INIT_ERROR_MSG          = "audio device error" ;
  static const String CONFIG_PENDING_MSG            = "press '" + DISMISS_BTN_TEXT + "' to continue" ;
  static const String DISCONNECTED_STATUS_TEXT      = "Disconnected" ;
  static const String ROOM_FULL_STATUS_TEXT         = "Jam room full" ;
  static const String INVALID_AUTH_STATUS_TEXT      = "Invalid login/pass" ;
  static const String PENDING_LICENSE_STATUS_TEXT   = "Pending license" ;
  static const String FAILED_CONNECTION_STATUS_TEXT = "Connection failed" ;
  static const String CONNECTING_STATUS_TEXT        = "Connecting to " ;
  static const String CONNECTED_STATUS_TEXT         = "Connected to " ;
  static const String IDLE_STATUS_TEXT              = "Ready" ;
  static const int    STATUSBAR_H                   = 24 ;
  static const int    STATUS_W                      = 160 ;
  static const int    STATUS_H                      = 16 ;
  static const int    STATUS_PAD_X                  = 8 ;
  static const int    STATUS_PAD_Y                  = 2 ;

  // Loop
  static const String LOOP_GUI_ID          = "loop-gui" ;
  static const int    LOOP_X               = STATUS_W + PAD3 ;
  static const int    LOOP_H               = STATUS_H ;
  static const double BEAT_PROGRESS_OFFSET = CLIENT::GUI_UPDATE_HI_IVL * 0.002 ;
}

#endif // _CONSTANTS_H_
