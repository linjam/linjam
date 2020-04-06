/* Constants.h
   this file defines global configuration/persistence and runtime constants
*/
#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <ninjam/audiostream.h>
#include <ninjam/njclient.h>

#include "JuceHeader.h"


/*\ CAVEATS:
|*|  when adding GUI components to Channels be sure to update N_STATIC_CHANNELS_CHILDREN
|*|    and when adding GUI components to Mixer be sure to update N_STATIC_MIXER_CHILDREN
|*|
|*|  when adding nodes or properties to CONFIG_XML be sure to
|*|    * if new property - denote datatype in #define CONFIG_TYPES_XML
|*|                      - sanitize data in   LinJamConfig::sanitizeGui()
|*|                                           LinJamConfig::sanitizeClient()    // TODO: nyi
|*|                                           LinJamConfig::sanitizeBlacklist() // TODO: nyi
|*|                                           LinJamConfig::sanitizeAudio()     // TODO: nyi
|*|                                           LinJamConfig::sanitizeServer()    // TODO: nyi
|*|                                           LinJamConfig::sanitizeUser()      // TODO: nyi
|*|                                           LinJamConfig::sanitizeChannel()   // TODO: nyi
|*|    * if user property - verify data in    LinJamConfig::validateUsers()
|*|    * if channel property - verify data in LinJamConfig::validateChannels()
|*|                          - add to         LinJamConfig::newChannel()
|*|    * if new node - switch in              LinJamConfig::restoreVarTypeInfo()
|*|                  - validate in            LinJamConfig::validateConfig()
|*|                  - invalidate in          LinJamConfig::isConfigValid()
|*|    * validate and trace data/errors in    #define DEBUG_VALIDATE_CONFIG_DEFAULTS
|*|                                           #define DEBUG_VALIDATE_CONFIG_ROOT
|*|                                           #define DEBUG_VALIDATE_CONFIG_GUI
|*|                                           #define DEBUG_VALIDATE_CONFIG_CLIENT
|*|                                           #define DEBUG_VALIDATE_CONFIG_BLACKLIST
|*|                                           #define DEBUG_VALIDATE_CONFIG_AUDIO
|*|                                           #define DEBUG_VALIDATE_CONFIG_SERVER
|*|                                           #define DEBUG_VALIDATE_CONFIG_MASTERS
|*|                                           #define DEBUG_TRACE_VALIDATE_CONFIG
|*|                                           #define DEBUG_TRACE_VALIDATE_USER
|*|                                           #define DEBUG_TRACE_VALIDATE_CHANNEL
|*|                                           #define DEBUG_TRACE_ADD_CHANNEL_GUI
|*|                                           #define DEBUG_TRACE_CONFIGURE_LOCAL_CHANNEL
|*|                                           #define DEBUG_TRACE_REMOTE_CHANNELS
|*|                                           #define DEBUG_TRACE_CONFIGURE_REMOTE
|*|                                           #define DEBUG_TRACE_SANITIZE_GUI
|*|                                           #define DEBUG_TRACE_SANITIZE_CLIENT
|*|                                           #define DEBUG_TRACE_SANITIZE_BLACKLIST
|*|                                           #define DEBUG_TRACE_SANITIZE_AUDIO
|*|                                           #define DEBUG_TRACE_SANITIZE_SERVER
|*|                                           #define DEBUG_TRACE_SANITIZE_USER
|*|                                           #define DEBUG_TRACE_SANITIZE_CHANNEL
\*/


/* default configuration raw data */

#define XML_HEADER "<?xml version=\"1.0\"?><"

#ifdef _WIN32
#  define WIN_AUDIO_XML                                                         \
      ASIO_DRIVER_KEY      + "=\"" + String(DEFAULT_ASIO_DRIVERN    ) + "\" " + \
      ASIO_INPUTB_KEY      + "=\"" + String(DEFAULT_ASIO_INPUTBN    ) + "\" " + \
      ASIO_INPUTE_KEY      + "=\"" + String(DEFAULT_ASIO_INPUTEN    ) + "\" " + \
      ASIO_OUTPUTB_KEY     + "=\"" + String(DEFAULT_ASIO_OUTPUTBN   ) + "\" " + \
      ASIO_OUTPUTE_KEY     + "=\"" + String(DEFAULT_ASIO_OUTPUTEN   ) + "\" " + \
      ASIO_CONTROL_KEY     + "=\"" + String(DEFAULT_ASIO_CONTROL    ) + "\" " + \
      KS_INPUT_KEY         + "=\"" + String(DEFAULT_KS_INPUTN       ) + "\" " + \
      KS_OUTPUT_KEY        + "=\"" + String(DEFAULT_KS_OUTPUTN      ) + "\" " + \
      KS_SAMPLERATE_KEY    + "=\"" + String(DEFAULT_KS_SAMPLERATE   ) + "\" " + \
      KS_BITDEPTH_KEY      + "=\"" + String(DEFAULT_KS_BITDEPTH     ) + "\" " + \
      KS_NBLOCKS_KEY       + "=\"" + String(DEFAULT_KS_NBLOCKS      ) + "\" " + \
      KS_BLOCKSIZE_KEY     + "=\"" + String(DEFAULT_KS_BLOCKSIZE    ) + "\" " + \
      DS_INPUT_KEY         + "=\"" + String(DEFAULT_DS_INPUT_NAME   ) + "\" " + \
      DS_OUTPUT_KEY        + "=\"" + String(DEFAULT_DS_OUTPUT_NAME  ) + "\" " + \
      DS_SAMPLERATE_KEY    + "=\"" + String(DEFAULT_DS_SAMPLERATE   ) + "\" " + \
      DS_BITDEPTH_KEY      + "=\"" + String(DEFAULT_DS_BITDEPTH     ) + "\" " + \
      DS_NBLOCKS_KEY       + "=\"" + String(DEFAULT_DS_NBLOCKS      ) + "\" " + \
      DS_BLOCKSIZE_KEY     + "=\"" + String(DEFAULT_DS_BLOCKSIZE    ) + "\" " + \
      WAVE_INPUT_KEY       + "=\"" + String(DEFAULT_WAVE_INPUTN     ) + "\" " + \
      WAVE_OUTPUT_KEY      + "=\"" + String(DEFAULT_WAVE_OUTPUTN    ) + "\" " + \
      WAVE_SAMPLERATE_KEY  + "=\"" + String(DEFAULT_WAVE_SAMPLERATE ) + "\" " + \
      WAVE_BITDEPTH_KEY    + "=\"" + String(DEFAULT_WAVE_BITDEPTH   ) + "\" " + \
      WAVE_NBLOCKS_KEY     + "=\"" + String(DEFAULT_WAVE_NBLOCKS    ) + "\" " + \
      WAVE_BLOCKSIZE_KEY   + "=\"" + String(DEFAULT_WAVE_BLOCKSIZE  ) + "\" "
#  define MAC_AUDIO_XML ""
#  define NIX_AUDIO_XML ""
#else // _WIN32
#  ifdef _MAC
#    define WIN_AUDIO_XML ""
#    define NIX_AUDIO_XML ""
#    define MAC_AUDIO_XML                                                       \
      CA_INPUT_KEY         + "=\"" + String(DEFAULT_CA_INPUT_NAME   ) + "\" " + \
      CA_OUTPUT_KEY        + "=\"" + String(DEFAULT_CA_OUTPUT_NAME  ) + "\" " + \
      CA_NCHANNELS_KEY     + "=\"" + String(DEFAULT_CA_NCHANNELS    ) + "\" " + \
      CA_SAMPLERATE_KEY    + "=\"" + String(DEFAULT_CA_SAMPLERATE   ) + "\" " + \
      CA_BITDEPTH_KEY      + "=\"" + String(DEFAULT_CA_BITDEPTH     ) + "\" "
#  else // _MAC
#    define WIN_AUDIO_XML ""
#    define MAC_AUDIO_XML ""
#    define NIX_AUDIO_XML                                                       \
      JACK_SERVER_KEY      + "=\"" + String(DEFAULT_JACK_SERVERN    ) + "\" " + \
      JACK_NAME_KEY        + "=\"" + String(DEFAULT_JACK_NAME       ) + "\" " + \
      JACK_NINPUTS_KEY     + "=\"" + String(DEFAULT_JACK_NINPUTS    ) + "\" " + \
      JACK_NOUTPUTS_KEY    + "=\"" + String(DEFAULT_JACK_NOUTPUTS   ) + "\" " + \
      ALSA_INPUT_KEY       + "=\"" + String(DEFAULT_ALSA_INPUT_NAME ) + "\" " + \
      ALSA_OUTPUT_KEY      + "=\"" + String(DEFAULT_ALSA_OUTPUT_NAME) + "\" " + \
      ALSA_NCHANNELS_KEY   + "=\"" + String(DEFAULT_ALSA_NCHANNELS  ) + "\" " + \
      ALSA_SAMPLERATE_KEY  + "=\"" + String(DEFAULT_ALSA_SAMPLERATE ) + "\" " + \
      ALSA_BITDEPTH_KEY    + "=\"" + String(DEFAULT_ALSA_BITDEPTH   ) + "\" " + \
      ALSA_NBLOCKS_KEY     + "=\"" + String(DEFAULT_ALSA_NBLOCKS    ) + "\" " + \
      ALSA_BLOCKSIZE_KEY   + "=\"" + String(DEFAULT_ALSA_BLOCKSIZE  ) + "\" "
#  endif // _MAC
#endif // _WIN32

/** CONFIG_XML, WIN_AUDIO_XML, NIX_AUDIO_XML, MAC_AUDIO_XML
  *     define the schema and default values for the configuration/persistence model
  * this data is instantiated below as DEFAULT_CONFIG_XML */
#define CONFIG_XML XML_HEADER                                                 + \
  STORAGE_KEY              +                                            " "   + \
    CONFIG_VERSION_KEY     + "=\"" + String(CONFIG_VERSION          ) + "\""  + \
  "><"                                                                        + \
    GUI_KEY                +                                            " "   + \
      FONT_SIZE_KEY        + "=\"" + String(DEFAULT_FONT_SIZE_N     ) + "\" " + \
      UPDATE_IVL_KEY       + "=\"" + String(DEFAULT_UPDATE_IVL_N    ) + "\" " + \
    "/><"                                                                     + \
    CLIENT_KEY             +                                            " "   + \
      SAVE_AUDIO_MODE_KEY  + "=\"" + String(DEFAULT_SAVE_AUDIO_MODE ) + "\" " + \
      MIXDOWN_MODE_KEY     + "=\"" + String(DEFAULT_MIXDOWN_MODE    ) + "\" " + \
      SHOULD_SAVE_LOG_KEY  + "=\"" + String(DEFAULT_SHOULD_SAVE_LOG ) + "\" " + \
      DEBUG_LEVEL_KEY      + "=\"" + String(DEFAULT_DEBUG_LEVEL     ) + "\" " + \
      SHOULD_HIDE_BOTS_KEY + "=\"" + String(DEFAULT_SHOULD_HIDE_BOTS) + "\" " + \
    "/><"                                                                     + \
    BLACKLIST_KEY          +                                            " "   + \
      SUBSCRIBE_MODE_KEY   + "=\"" + String(DEFAULT_SUBSCRIBE_MODE  ) + "\" " + \
    "/><"                                                                     + \
    AUDIO_KEY              +                                            " "   + \
      AUDIO_API_KEY        + "=\"" + String(DEFAULT_AUDIO_API       ) + "\" " + \
      String(WIN_AUDIO_XML)                                                   + \
      String(MAC_AUDIO_XML)                                                   + \
      String(NIX_AUDIO_XML)                                                   + \
    "/><"                                                                     + \
    SERVER_KEY             +                                            " "   + \
      HOST_KEY             + "=\"" + String(DEFAULT_HOST            ) + "\" " + \
      LOGIN_KEY            + "=\"" + String(DEFAULT_LOGIN           ) + "\" " + \
      PASS_KEY             + "=\"" + String(DEFAULT_PASS            ) + "\" " + \
      IS_ANONYMOUS_KEY     + "=\"" + String(DEFAULT_IS_ANONYMOUS    ) + "\" " + \
      IS_AGREED_KEY        + "=\"" + String(DEFAULT_IS_AGREED       ) + "\" " + \
      SHOULD_AGREE_KEY     + "=\"" + String(DEFAULT_SHOULD_AGREE    ) + "\" " + \
      BOT_NAME_KEY         + "=\"" + String(DEFAULT_BOT_NAME        ) + "\" " + \
      BOT_USERIDX_KEY      + "=\"" + String(DEFAULT_BOT_USERIDX     ) + "\" " + \
    "/><"                                                                     + \
    SERVERS_KEY            + " /><"                                           + \
    MASTERS_KEY            + "><"                                             + \
      MASTER_KEY           +                                            " "   + \
        CHANNEL_NAME_KEY   + "=\"" + String(MASTER_KEY              ) + "\" " + \
        VOLUME_KEY         + "=\"" + String(DEFAULT_VOLUME          ) + "\" " + \
        PAN_KEY            + "=\"" + String(DEFAULT_PAN             ) + "\" " + \
        IS_MUTED_KEY       + "=\"" + String(DEFAULT_IS_MUTED        ) + "\" " + \
        STEREO_KEY         + "=\"" + String(STEREO                  ) + "\" " + \
        VU_LEFT_KEY        + "=\"" + String(DEFAULT_VU              ) + "\" " + \
        VU_RIGHT_KEY       + "=\"" + String(DEFAULT_VU              ) + "\" " + \
    "/><"                                                                     + \
      METRO_KEY            +                                            " "   + \
        CHANNEL_NAME_KEY   + "=\"" + String(METRO_KEY               ) + "\" " + \
        VOLUME_KEY         + "=\"" + String(DEFAULT_VOLUME          ) + "\" " + \
        PAN_KEY            + "=\"" + String(DEFAULT_PAN             ) + "\" " + \
        IS_MUTED_KEY       + "=\"" + String(DEFAULT_IS_MUTED        ) + "\" " + \
        SOURCE_N_KEY       + "=\"" + String(DEFAULT_SOURCE_N        ) + "\" " + \
        STEREO_KEY         + "=\"" + String(STEREO                  ) + "\" " + \
        VU_LEFT_KEY        + "=\"" + String(DEFAULT_VU              ) + "\" " + \
        VU_RIGHT_KEY       + "=\"" + String(DEFAULT_VU              ) + "\" " + \
    "/>"                                                                      + \
    "</" + MASTERS_KEY     + "><"                                             + \
    LOCALS_KEY             + " /><"                                           + \
    REMOTES_KEY            + " />"                                            + \
  "</" + STORAGE_KEY       + ">"

/** CONFIG_TYPES_XML denotes the property datatypes for the CONFIG_XML data above
  *      there is not a one-to-one correspondence with the schema
  *  these are grouped by leaf type
  *      because <channel> leaves for example are found in several locations
  *      and some list nodes such as <locals> have no intrinsic properties
  *  this data is instantiated below as CONFIG_DATATYPES_XML */
#define CONFIG_TYPES_XML XML_HEADER                       + \
  STORAGE_TYPES_KEY        +                       " "    + \
    CONFIG_VERSION_KEY     + "=\"" + DOUBLE_TYPE + "\"><" + \
    GUI_KEY                +                       " "    + \
      FONT_SIZE_KEY        + "=\"" + INT_TYPE    + "\" "  + \
      UPDATE_IVL_KEY       + "=\"" + INT_TYPE    + "\" "  + \
    "/><"                                                 + \
    CLIENT_KEY             +                       " "    + \
      SAVE_AUDIO_MODE_KEY  + "=\"" + INT_TYPE    + "\" "  + \
      MIXDOWN_MODE_KEY     + "=\"" + INT_TYPE    + "\" "  + \
      SHOULD_SAVE_LOG_KEY  + "=\"" + BOOL_TYPE   + "\" "  + \
      DEBUG_LEVEL_KEY      + "=\"" + INT_TYPE    + "\" "  + \
      SHOULD_HIDE_BOTS_KEY + "=\"" + BOOL_TYPE   + "\" "  + \
    "/><"                                                 + \
    BLACKLIST_KEY          +                       " "    + \
      SUBSCRIBE_MODE_KEY   + "=\"" + INT_TYPE    + "\" "  + \
    "/><"                                                 + \
    AUDIO_KEY              +                       " "    + \
      AUDIO_API_KEY        + "=\"" + INT_TYPE    + "\" "  + \
      ASIO_DRIVER_KEY      + "=\"" + INT_TYPE    + "\" "  + \
      ASIO_INPUTB_KEY      + "=\"" + INT_TYPE    + "\" "  + \
      ASIO_INPUTE_KEY      + "=\"" + INT_TYPE    + "\" "  + \
      ASIO_OUTPUTB_KEY     + "=\"" + INT_TYPE    + "\" "  + \
      ASIO_OUTPUTE_KEY     + "=\"" + INT_TYPE    + "\" "  + \
      ASIO_CONTROL_KEY     + "=\"" + INT_TYPE    + "\" "  + \
      KS_INPUT_KEY         + "=\"" + INT_TYPE    + "\" "  + \
      KS_OUTPUT_KEY        + "=\"" + INT_TYPE    + "\" "  + \
      KS_SAMPLERATE_KEY    + "=\"" + INT_TYPE    + "\" "  + \
      KS_BITDEPTH_KEY      + "=\"" + INT_TYPE    + "\" "  + \
      KS_NBLOCKS_KEY       + "=\"" + INT_TYPE    + "\" "  + \
      KS_BLOCKSIZE_KEY     + "=\"" + INT_TYPE    + "\" "  + \
      DS_INPUT_KEY         + "=\"" + STRING_TYPE + "\" "  + \
      DS_OUTPUT_KEY        + "=\"" + STRING_TYPE + "\" "  + \
      DS_SAMPLERATE_KEY    + "=\"" + INT_TYPE    + "\" "  + \
      DS_BITDEPTH_KEY      + "=\"" + INT_TYPE    + "\" "  + \
      DS_NBLOCKS_KEY       + "=\"" + INT_TYPE    + "\" "  + \
      DS_BLOCKSIZE_KEY     + "=\"" + INT_TYPE    + "\" "  + \
      WAVE_INPUT_KEY       + "=\"" + INT_TYPE    + "\" "  + \
      WAVE_OUTPUT_KEY      + "=\"" + INT_TYPE    + "\" "  + \
      WAVE_SAMPLERATE_KEY  + "=\"" + INT_TYPE    + "\" "  + \
      WAVE_BITDEPTH_KEY    + "=\"" + INT_TYPE    + "\" "  + \
      WAVE_NBLOCKS_KEY     + "=\"" + INT_TYPE    + "\" "  + \
      WAVE_BLOCKSIZE_KEY   + "=\"" + INT_TYPE    + "\" "  + \
      CA_INPUT_KEY         + "=\"" + STRING_TYPE + "\" "  + \
      CA_OUTPUT_KEY        + "=\"" + STRING_TYPE + "\" "  + \
      CA_NCHANNELS_KEY     + "=\"" + INT_TYPE    + "\" "  + \
      CA_SAMPLERATE_KEY    + "=\"" + INT_TYPE    + "\" "  + \
      CA_BITDEPTH_KEY      + "=\"" + INT_TYPE    + "\" "  + \
      JACK_SERVER_KEY      + "=\"" + INT_TYPE    + "\" "  + \
      JACK_NAME_KEY        + "=\"" + STRING_TYPE + "\" "  + \
      JACK_NINPUTS_KEY     + "=\"" + INT_TYPE    + "\" "  + \
      JACK_NOUTPUTS_KEY    + "=\"" + INT_TYPE    + "\" "  + \
      ALSA_INPUT_KEY       + "=\"" + STRING_TYPE + "\" "  + \
      ALSA_OUTPUT_KEY      + "=\"" + STRING_TYPE + "\" "  + \
      ALSA_NCHANNELS_KEY   + "=\"" + INT_TYPE    + "\" "  + \
      ALSA_SAMPLERATE_KEY  + "=\"" + INT_TYPE    + "\" "  + \
      ALSA_BITDEPTH_KEY    + "=\"" + INT_TYPE    + "\" "  + \
      ALSA_NBLOCKS_KEY     + "=\"" + INT_TYPE    + "\" "  + \
      ALSA_BLOCKSIZE_KEY   + "=\"" + INT_TYPE    + "\" "  + \
    "/><"                                                 + \
    SERVER_KEY             +                       " "    + \
      HOST_KEY             + "=\"" + STRING_TYPE + "\" "  + \
      LOGIN_KEY            + "=\"" + STRING_TYPE + "\" "  + \
      PASS_KEY             + "=\"" + STRING_TYPE + "\" "  + \
      IS_ANONYMOUS_KEY     + "=\"" + BOOL_TYPE   + "\" "  + \
      IS_AGREED_KEY        + "=\"" + BOOL_TYPE   + "\" "  + \
      SHOULD_AGREE_KEY     + "=\"" + BOOL_TYPE   + "\" "  + \
      BOT_NAME_KEY         + "=\"" + STRING_TYPE + "\" "  + \
      BOT_USERIDX_KEY      + "=\"" + INT_TYPE    + "\" "  + \
    "/><"                                                 + \
    USERS_KEY              +                       " "    + \
      USER_IDX_KEY         + "=\"" + INT_TYPE    + "\" "  + \
    "/><"                                                 + \
    CHANNELS_KEY           +                       " "    + \
      CHANNEL_NAME_KEY     + "=\"" + STRING_TYPE + "\" "  + \
      CHANNEL_IDX_KEY      + "=\"" + INT_TYPE    + "\" "  + \
      PAIR_IDX_KEY         + "=\"" + INT_TYPE    + "\" "  + \
      VOLUME_KEY           + "=\"" + DOUBLE_TYPE + "\" "  + \
      PAN_KEY              + "=\"" + DOUBLE_TYPE + "\" "  + \
      IS_XMIT_RCV_KEY      + "=\"" + BOOL_TYPE   + "\" "  + \
      IS_MUTED_KEY         + "=\"" + BOOL_TYPE   + "\" "  + \
      IS_SOLO_KEY          + "=\"" + BOOL_TYPE   + "\" "  + \
      SOURCE_N_KEY         + "=\"" + INT_TYPE    + "\" "  + \
      STEREO_KEY           + "=\"" + INT_TYPE    + "\" "  + \
      VU_LEFT_KEY          + "=\"" + DOUBLE_TYPE + "\" "  + \
      VU_RIGHT_KEY         + "=\"" + DOUBLE_TYPE + "\" "  + \
    "/>"                                                  + \
  "</" + STORAGE_TYPES_KEY + "> "

#define KNOWN_HOSTS_XML XML_HEADER         + \
  NETWORK::KNOWN_HOSTS_KEY      + "><"     + \
    NETWORK::LOCALHOST_2049_URL + " /><"   + \
    NETWORK::NINBOT_2049_URL    + " /><"   + \
    NETWORK::NINBOT_2050_URL    + " /><"   + \
    NETWORK::NINBOT_2051_URL    + " /><"   + \
    NETWORK::NINBOT_2052_URL    + " /><"   + \
    NETWORK::NINJAMER_2049_URL  + " /><"   + \
    NETWORK::NINJAMER_2050_URL  + " /><"   + \
    NETWORK::NINJAMER_2051_URL  + " /><"   + \
    NETWORK::NINJAMER_2052_URL  + " /></"  + \
  NETWORK::KNOWN_HOSTS_KEY      + ">"

#define KNOWN_BOTS_XML XML_HEADER                                         + \
  NETWORK::KNOWN_BOTS_KEY                                         + " "   + \
    String(LinJamConfig::MakeHostId(NETWORK::NINBOT_2049_URL   )) + "=\"" + \
    String(NETWORK::NINBOT_USER)                                  + "\" " + \
    String(LinJamConfig::MakeHostId(NETWORK::NINBOT_2050_URL   )) + "=\"" + \
    String(NETWORK::NINBOT_USER)                                  + "\" " + \
    String(LinJamConfig::MakeHostId(NETWORK::NINBOT_2051_URL   )) + "=\"" + \
    String(NETWORK::NINBOT_USER)                                  + "\" " + \
    String(LinJamConfig::MakeHostId(NETWORK::NINBOT_2052_URL   )) + "=\"" + \
    String(NETWORK::NINBOT_USER)                                  + "\" " + \
    String(LinJamConfig::MakeHostId(NETWORK::NINJAMER_2049_URL )) + "=\"" + \
    String(NETWORK::JAMBOT_USER)                                  + "\" " + \
    String(LinJamConfig::MakeHostId(NETWORK::NINJAMER_2050_URL )) + "=\"" + \
    String(NETWORK::JAMBOT_USER)                                  + "\" " + \
    String(LinJamConfig::MakeHostId(NETWORK::NINJAMER_2051_URL )) + "=\"" + \
    String(NETWORK::JAMBOT_USER)                                  + "\" " + \
    String(LinJamConfig::MakeHostId(NETWORK::NINJAMER_2052_URL )) + "=\"" + \
    String(NETWORK::JAMBOT_USER)                                  + "\" " + \
    String(LinJamConfig::MakeHostId(NETWORK::SERVEBEER_2049_URL)) + "=\"" + \
    String(NETWORK::BEERBOT_USER)                                 + "\" " + \
  "/>"


/* global constants */

/** APP defines configuration and runtime constants
  *     pertaining to the core LinJam application and business logic */
class APP
{
public:

  // app state
  enum LinJamStatus { LINJAM_STATUS_INIT           = -10 ,
                      LINJAM_STATUS_AUDIOINIT      = -9  ,
                      LINJAM_STATUS_CONFIGPENDING  = -8  ,
                      LINJAM_STATUS_AUDIOERROR     = -7  ,
                      LINJAM_STATUS_READY          = -6  ,
                      LINJAM_STATUS_LICENSEPENDING = -5  ,
                      LINJAM_STATUS_ROOMFULL       = -4  ,
                      NJC_STATUS_DISCONNECTED      = -3  ,   // NJClient::ConnectionStatus
                      NJC_STATUS_INVALIDAUTH       = -2  ,   // NJClient::ConnectionStatus
                      NJC_STATUS_CANTCONNECT       = -1  ,   // NJClient::ConnectionStatus
                      NJC_STATUS_OK                =  0  ,   // NJClient::ConnectionStatus
                      NJC_STATUS_PRECONNECT        =  1  } ; // NJClient::ConnectionStatus

  // timers
  static const int CLIENT_TIMER_ID     = 0 ; static const int CLIENT_DRIVER_IVL = 50 ;
  static const int AUDIO_INIT_TIMER_ID = 1 ; static const int AUDIO_INIT_DELAY  = 250 ;
  static const int GUI_LO_TIMER_ID     = 2 ; static const int GUI_LO_UPDATE_IVL = 30000 ;
  static const int GUI_MD_TIMER_ID     = 3 ; static const int GUI_MD_UPDATE_IVL = 2000 ;
  static const int GUI_HI_TIMER_ID     = 4 ; static const Array<int> GUI_HI_UPDATE_IVLS ;


  // runtime initialization of static constants
  static void Initialize() ;
} ;


/** CLIENT defines configuration and runtime constants
  *     pertaining to NJClient                            */
namespace CLIENT
{
  // server
  static const String SERVER_FULL_ERROR = "server full" ;
  static const int    CHATMSG_TYPE_IDX  = 0 ;
  static const int    CHATMSG_USER_IDX  = 1 ;
  static const int    CHATMSG_MSG_IDX   = 2 ;
  static const int    BOT_CHANNELIDX    = 0 ;

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

  // configuration
  static const String STEREO_L_POSTFIX       = "-L" ;
  static const String STEREO_R_POSTFIX       = "-R" ;
  static const int    STEREO_POSTFIX_N_CHARS = STEREO_L_POSTFIX.length() ;

  // persistence and storage
#ifdef _WIN32
  static const String STORAGE_DIRNAME  = "LinJam\\" ;
  static const String SESSION_DIRNAME  = STORAGE_DIRNAME + "Session" ;
#else // _WIN32
  static const String STORAGE_DIRNAME  = ".linjam/" ;
  static const String SESSION_DIRNAME  = STORAGE_DIRNAME + "session" ;
#endif // _WIN32
  static const String STORAGE_FILENAME = STORAGE_DIRNAME + "linjam.xml" ;
  static const String LOG_FILENAME     = STORAGE_DIRNAME + "clipsort.log" ;
}


/** NETWORK defines configuration and runtime constants
  *     pertaining to login and communications */
class NETWORK
{
public:

  // login and validations
  static const int       N_LOGIN_RETRIES ;
  static const StringRef HOST_MASK ;
  static const StringRef LETTERS ;
  static const StringRef DIGITS ;
  static const String    HOST_CHARS ;
  static const String    NICK_CHARS ;

  // known hosts and bots
  static const String      LOCALHOST_HOSTNAME ;
  static const String      LOCALHOST_2049_URL ;
  static const String      NINJAM_2049_URL ;
  static const String      NINJAM_2050_URL ;
  static const String      NINJAM_2051_URL ;
  static const String      NINJAM_2052_URL ;
  static const String      NINJAM_2600_URL ;
  static const String      NINJAM_2601_URL ;
  static const String      NINBOT_2049_URL ;
  static const String      NINBOT_2050_URL ;
  static const String      NINBOT_2051_URL ;
  static const String      NINBOT_2052_URL ;
  static const String      NINJAMER_2049_URL ;
  static const String      NINJAMER_2050_URL ;
  static const String      NINJAMER_2051_URL ;
  static const String      NINJAMER_2052_URL ;
  static const String      SERVEBEER_2049_URL ;
  static const String      SERVEBEER_2050_URL ;
  static const String      MUTANTLAB_2049_URL ;
  static const Identifier  NINBOT_USER ;
  static const Identifier  JAMBOT_USER ;
  static const Identifier  BEERBOT_USER ;
  static const String      KNOWN_HOSTS_KEY ;
  static const String      KNOWN_BOTS_KEY ;
  static const XmlElement* KNOWN_HOSTS ;
  static const XmlElement* KNOWN_BOTS ;


  static bool IsKnownHost(String host) ;
} ;


/** CONFIG defines keys/value pairs and default value constants
        pertaining to the configuration/persistence model          */
namespace CONFIG
{
  /* config XML and ValueTree keys */

  // config root keys
  static const String     STORAGE_KEY           = "linjam-data" ;
  static const Identifier STORAGE_ID            = STORAGE_KEY ;
  static const String     STORAGE_TYPES_KEY     = STORAGE_KEY + "-types" ;
  static const String     CONFIG_VERSION_KEY    = "config-version" ;
  static const Identifier CONFIG_VERSION_ID     = CONFIG_VERSION_KEY ;

  // gui config keys
  static const String     GUI_KEY              = "gui" ;
  static const Identifier GUI_ID               = GUI_KEY ;
  static const String     FONT_SIZE_KEY        = "chat-font-size" ;
  static const Identifier FONT_SIZE_ID         = FONT_SIZE_KEY ;
  static const String     UPDATE_IVL_KEY       = "gui-update-ivl" ;
  static const Identifier UPDATE_IVL_ID        = UPDATE_IVL_KEY ;

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

  // blacklist config keys
  static const String     BLACKLIST_KEY      = "blacklist" ;
  static const Identifier BLACKLIST_ID       = BLACKLIST_KEY ;
  static const String     SUBSCRIBE_MODE_KEY = "subscribe-mode" ;
  static const Identifier SUBSCRIBE_MODE_ID  = SUBSCRIBE_MODE_KEY ;

  // audio device config keys
  static const String     AUDIO_KEY           = "audio" ;
  static const Identifier AUDIO_ID            = AUDIO_KEY ;
  static const String     AUDIO_API_KEY       = "audio-api-n" ;
  static const Identifier AUDIO_API_ID        = AUDIO_API_KEY ;
  static const String     ASIO_DRIVER_KEY     = "asio-driver-n" ;
  static const Identifier ASIO_DRIVER_ID      = ASIO_DRIVER_KEY ;
  static const String     ASIO_INPUTB_KEY     = "asio-input-begin-n" ;
  static const Identifier ASIO_INPUTB_ID      = ASIO_INPUTB_KEY ;
  static const String     ASIO_INPUTE_KEY     = "asio-input1-end-n" ;
  static const Identifier ASIO_INPUTE_ID      = ASIO_INPUTE_KEY ;
  static const String     ASIO_OUTPUTB_KEY    = "asio-output-begin-n" ;
  static const Identifier ASIO_OUTPUTB_ID     = ASIO_OUTPUTB_KEY ;
  static const String     ASIO_OUTPUTE_KEY    = "asio-output-end-n" ;
  static const Identifier ASIO_OUTPUTE_ID     = ASIO_OUTPUTE_KEY ;
  static const String     ASIO_CONTROL_KEY    = "should-show-asio-cp" ;
  static const Identifier ASIO_CONTROL_ID     = ASIO_CONTROL_KEY ;
  static const String     KS_INPUT_KEY        = "ks-input-n" ;
  static const Identifier KS_INPUT_ID         = KS_INPUT_KEY ;
  static const String     KS_OUTPUT_KEY       = "ks-output-n" ;
  static const Identifier KS_OUTPUT_ID        = KS_OUTPUT_KEY ;
  static const String     KS_SAMPLERATE_KEY   = "ks-sample-rate" ;
  static const Identifier KS_SAMPLERATE_ID    = KS_SAMPLERATE_KEY ;
  static const String     KS_BITDEPTH_KEY     = "ks-bit-depth" ;
  static const Identifier KS_BITDEPTH_ID      = KS_BITDEPTH_KEY ;
  static const String     KS_NBLOCKS_KEY      = "ks-n-blocks" ;
  static const Identifier KS_NBLOCKS_ID       = KS_NBLOCKS_KEY ;
  static const String     KS_BLOCKSIZE_KEY    = "ks-block-size" ;
  static const Identifier KS_BLOCKSIZE_ID     = KS_BLOCKSIZE_KEY ;
  static const String     DS_INPUT_KEY        = "ds-input" ;
  static const Identifier DS_INPUT_ID         = DS_INPUT_KEY ;
  static const String     DS_OUTPUT_KEY       = "ds-output" ;
  static const Identifier DS_OUTPUT_ID        = DS_OUTPUT_KEY ;
  static const String     DS_SAMPLERATE_KEY   = "ds-sample-rate" ;
  static const Identifier DS_SAMPLERATE_ID    = DS_SAMPLERATE_KEY ;
  static const String     DS_BITDEPTH_KEY     = "ds-bit-depth" ;
  static const Identifier DS_BITDEPTH_ID      = DS_BITDEPTH_KEY ;
  static const String     DS_NBLOCKS_KEY      = "ds-n-blocks" ;
  static const Identifier DS_NBLOCKS_ID       = DS_NBLOCKS_KEY ;
  static const String     DS_BLOCKSIZE_KEY    = "ds-block-size" ;
  static const Identifier DS_BLOCKSIZE_ID     = DS_BLOCKSIZE_KEY ;
  static const String     WAVE_INPUT_KEY      = "wave-input-n" ;
  static const Identifier WAVE_INPUT_ID       = WAVE_INPUT_KEY ;
  static const String     WAVE_OUTPUT_KEY     = "wave-output-n" ;
  static const Identifier WAVE_OUTPUT_ID      = WAVE_OUTPUT_KEY ;
  static const String     WAVE_SAMPLERATE_KEY = "wave-sample-rate" ;
  static const Identifier WAVE_SAMPLERATE_ID  = WAVE_SAMPLERATE_KEY ;
  static const String     WAVE_BITDEPTH_KEY   = "wave-bit-depth" ;
  static const Identifier WAVE_BITDEPTH_ID    = WAVE_BITDEPTH_KEY ;
  static const String     WAVE_NBLOCKS_KEY    = "wave-n-blocks" ;
  static const Identifier WAVE_NBLOCKS_ID     = WAVE_NBLOCKS_KEY ;
  static const String     WAVE_BLOCKSIZE_KEY  = "wave-block-size" ;
  static const Identifier WAVE_BLOCKSIZE_ID   = WAVE_BLOCKSIZE_KEY ;
  static const String     CA_INPUT_KEY        = "ca-input" ;
  static const Identifier CA_INPUT_ID         = CA_INPUT_KEY ;
  static const String     CA_OUTPUT_KEY       = "ca-output" ;
  static const Identifier CA_OUTPUT_ID        = CA_OUTPUT_KEY ;
  static const String     CA_NCHANNELS_KEY    = "ca-n-channels" ;
  static const Identifier CA_NCHANNELS_ID     = CA_NCHANNELS_KEY ;
  static const String     CA_SAMPLERATE_KEY   = "ca-sample-rate" ;
  static const Identifier CA_SAMPLERATE_ID    = CA_SAMPLERATE_KEY ;
  static const String     CA_BITDEPTH_KEY     = "ca-bit-depth" ;
  static const Identifier CA_BITDEPTH_ID      = CA_BITDEPTH_KEY ;
  static const String     JACK_SERVER_KEY     = "jack-server" ;
  static const Identifier JACK_SERVER_ID      = JACK_SERVER_KEY ;
  static const String     JACK_NAME_KEY       = "jack-name" ;
  static const Identifier JACK_NAME_ID        = JACK_NAME_KEY ;
  static const String     JACK_NINPUTS_KEY    = "jack-n-inputs" ;
  static const Identifier JACK_NINPUTS_ID     = JACK_NINPUTS_KEY ;
  static const String     JACK_NOUTPUTS_KEY   = "jack-n-outputs" ;
  static const Identifier JACK_NOUTPUTS_ID    = JACK_NOUTPUTS_KEY ;
  static const String     ALSA_INPUT_KEY      = "alsa-input" ;
  static const Identifier ALSA_INPUT_ID       = ALSA_INPUT_KEY ;
  static const String     ALSA_OUTPUT_KEY     = "alsa-output" ;
  static const Identifier ALSA_OUTPUT_ID      = ALSA_OUTPUT_KEY ;
  static const String     ALSA_NCHANNELS_KEY  = "alsa-n-channels" ;
  static const Identifier ALSA_NCHANNELS_ID   = ALSA_NCHANNELS_KEY ;
  static const String     ALSA_SAMPLERATE_KEY = "alsa-sample-rate" ;
  static const Identifier ALSA_SAMPLERATE_ID  = ALSA_SAMPLERATE_KEY ;
  static const String     ALSA_BITDEPTH_KEY   = "alsa-bit-depth" ;
  static const Identifier ALSA_BITDEPTH_ID    = ALSA_BITDEPTH_KEY ;
  static const String     ALSA_NBLOCKS_KEY    = "alsa-n-blocks" ;
  static const Identifier ALSA_NBLOCKS_ID     = ALSA_NBLOCKS_KEY ;
  static const String     ALSA_BLOCKSIZE_KEY  = "alsa-block-size" ;
  static const Identifier ALSA_BLOCKSIZE_ID   = ALSA_BLOCKSIZE_KEY ;

  // server config keys
  static const String     SERVER_KEY       = "server" ;
  static const Identifier SERVER_ID        = SERVER_KEY ;
  static const String     SERVERS_KEY      = "servers" ;
  static const Identifier SERVERS_ID       = SERVERS_KEY ;
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
  static const String     BOT_NAME_KEY     = "bot-name" ;
  static const Identifier BOT_NAME_ID      = BOT_NAME_KEY ;
  static const String     BOT_USERIDX_KEY  = "bot-useridx" ;
  static const Identifier BOT_USERIDX_ID   = BOT_USERIDX_KEY ;

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


  /* config XML and ValueTree default values */

  // config root defaults
  static const double CONFIG_VERSION = 0.27 ; // major.minor at last schema change

  // gui config defaults
  static const int  DEFAULT_FONT_SIZE_N  = 2 ;
  static const int  DEFAULT_UPDATE_IVL_N = 3 ;

  // client config defaults
  static const int  SAVE_AUDIO_ENUM_OFFSET   = 2 ;
  static const int  DEFAULT_SAVE_AUDIO_MODE  = (int)NJClient::SAVE_TEMP ;
  static const int  DEFAULT_MIXDOWN_MODE     = (int)NJClient::MIXDOWN_NONE ;
  static const bool DEFAULT_SHOULD_SAVE_LOG  = false ;
  static const int  DEFAULT_DEBUG_LEVEL      = (int)NJClient::DEBUG_SILENT ;
  static const bool DEFAULT_SHOULD_HIDE_BOTS = true ;

  // blacklist config defaults
  static const int DEFAULT_SUBSCRIBE_MODE = (int)NJClient::SUBSCRIBE_DENY ;

  // audio config defaults
#ifdef _WIN32
  static const int    DEFAULT_AUDIO_API        = (int)audioStreamer::WIN_AUDIO_WAVE ;
  static const int    DEFAULT_ASIO_DRIVERN     = audioStreamer::DEFAULT_ASIO_DRIVER_N ;
  static const int    DEFAULT_ASIO_INPUTBN     = audioStreamer::DEFAULT_ASIO_INPUTB_N ;
  static const int    DEFAULT_ASIO_INPUTEN     = audioStreamer::DEFAULT_ASIO_INPUTE_N ;
  static const int    DEFAULT_ASIO_OUTPUTBN    = audioStreamer::DEFAULT_ASIO_OUTPUTB_N ;
  static const int    DEFAULT_ASIO_OUTPUTEN    = audioStreamer::DEFAULT_ASIO_OUTPUTE_N ;
  static const int    DEFAULT_ASIO_CONTROL     = audioStreamer::DEFAULT_ASIO_CONTROL ;
  static const int    DEFAULT_KS_INPUTN        = -1 ; // libninjam does not implement this
  static const int    DEFAULT_KS_OUTPUTN       = -1 ; // libninjam does not implement this
  static const int    DEFAULT_KS_SAMPLERATE    = audioStreamer::DEFAULT_SAMPLE_RATE ;
  static const int    DEFAULT_KS_BITDEPTH      = audioStreamer::DEFAULT_BIT_DEPTH ;
  static const int    DEFAULT_KS_NBLOCKS       = audioStreamer::DEFAULT_KS_N_BLOCKS ;
  static const int    DEFAULT_KS_BLOCKSIZE     = audioStreamer::DEFAULT_KS_BLOCK_SIZE ;
  static const String DEFAULT_DS_INPUT_NAME    = audioStreamer::DEFAULT_DS_DEVICE_NAME ;
  static const String DEFAULT_DS_OUTPUT_NAME   = audioStreamer::DEFAULT_DS_DEVICE_NAME ;
  static const int    DEFAULT_DS_SAMPLERATE    = audioStreamer::DEFAULT_SAMPLE_RATE ;
  static const int    DEFAULT_DS_BITDEPTH      = audioStreamer::DEFAULT_BIT_DEPTH ;
  static const int    DEFAULT_DS_NBLOCKS       = audioStreamer::DEFAULT_DS_N_BLOCKS ;
  static const int    DEFAULT_DS_BLOCKSIZE     = audioStreamer::DEFAULT_DS_BLOCK_SIZE ;
  static const int    DEFAULT_WAVE_INPUTN      = audioStreamer::DEFAULT_WAVE_INPUT_N ;
  static const int    DEFAULT_WAVE_OUTPUTN     = audioStreamer::DEFAULT_WAVE_OUTPUT_N ;
  static const int    DEFAULT_WAVE_SAMPLERATE  = audioStreamer::DEFAULT_SAMPLE_RATE ;
  static const int    DEFAULT_WAVE_BITDEPTH    = audioStreamer::DEFAULT_BIT_DEPTH ;
  static const int    DEFAULT_WAVE_NBLOCKS     = audioStreamer::DEFAULT_WAVE_N_BLOCKS ;
  static const int    DEFAULT_WAVE_BLOCKSIZE   = audioStreamer::DEFAULT_WAVE_BLOCK_SIZE ;
#else // _WIN32
#  ifdef _MAC
  static const int    DEFAULT_AUDIO_API        = (int)audioStreamer::MAC_AUDIO_CA ;
  static const String DEFAULT_CA_INPUT_NAME    = audioStreamer::DEFAULT_CA_INPUT_NAME ;
  static const String DEFAULT_CA_OUTPUT_NAME   = audioStreamer::DEFAULT_CA_OUTPUT_NAME ;
  static const int    DEFAULT_CA_NCHANNELS     = audioStreamer::DEFAULT_N_INPUTS ;
  static const int    DEFAULT_CA_SAMPLERATE    = audioStreamer::DEFAULT_SAMPLE_RATE ;
  static const int    DEFAULT_CA_BITDEPTH      = audioStreamer::DEFAULT_BIT_DEPTH ;
#  else // _MAC
  static const int    DEFAULT_AUDIO_API        = (int)audioStreamer::NIX_AUDIO_JACK ;
  static const int    DEFAULT_JACK_SERVERN     = 0 ; // libninjam does not implement this
  static const String DEFAULT_JACK_NAME        = "LinJam" ;
  static const int    DEFAULT_JACK_NINPUTS     = audioStreamer::DEFAULT_N_INPUTS ;
  static const int    DEFAULT_JACK_NOUTPUTS    = audioStreamer::DEFAULT_N_OUTPUTS ;
  static const String DEFAULT_ALSA_INPUT_NAME  = audioStreamer::DEFAULT_ALSA_INPUT_NAME ;
  static const String DEFAULT_ALSA_OUTPUT_NAME = audioStreamer::DEFAULT_ALSA_OUTPUT_NAME ;
  static const int    DEFAULT_ALSA_NCHANNELS   = audioStreamer::DEFAULT_N_INPUTS ;
  static const int    DEFAULT_ALSA_SAMPLERATE  = audioStreamer::DEFAULT_SAMPLE_RATE ;
  static const int    DEFAULT_ALSA_BITDEPTH    = audioStreamer::DEFAULT_BIT_DEPTH ;
  static const int    DEFAULT_ALSA_NBLOCKS     = audioStreamer::DEFAULT_ALSA_N_BLOCKS ;
  static const int    DEFAULT_ALSA_BLOCKSIZE   = audioStreamer::DEFAULT_ALSA_BLOCK_SIZE ;
#  endif // _MAC
#endif // _WIN32

  // server config defaults
  static const String DEFAULT_HOST         = "" ;
  static const String DEFAULT_LOGIN        = "" ;
  static const String DEFAULT_PASS         = "" ;
  static const bool   DEFAULT_IS_ANONYMOUS = true ;
  static const bool   DEFAULT_IS_AGREED    = false ;
  static const bool   DEFAULT_SHOULD_AGREE = false ;
  static const String DEFAULT_BOT_NAME     = "" ;
  static const int    DEFAULT_BOT_USERIDX  = -1 ;

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
  static const double     DEFAULT_VOLUME        = 0.0f ;
  static const double     DEFAULT_PAN           = 0.0f ;
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

  // config XML storage
  static const String BOOL_TYPE            = "bool" ;
  static const String DOUBLE_TYPE          = "double" ;
  static const String INT_TYPE             = "int" ;
  static const String STRING_TYPE          = "string" ;
  static const String DEFAULT_CONFIG_XML   = String(CONFIG_XML) ;
  static const String CONFIG_DATATYPES_XML = String(CONFIG_TYPES_XML) ;

  // validation
  static const StringRef VALID_NAME_CHARS   = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_- " ;
  static const StringRef USER_IP_SPLIT_CHAR = "@" ;
}


/** GUI defines configuration and runtime constants
  *     pertaining to graphical elements               */
namespace GUI
{
  // common
  static const int    PAD                   = 4 ;
  static const float  PADF                  = 4.0f ;
  static const int    PAD2                  = PAD  * 2 ;
  static const float  PAD2F                 = PADF * 2.0f ;
  static const int    PAD3                  = PAD  * 3 ;
  static const float  PAD3F                 = PADF * 3.0f ;
  static const int    PAD4                  = PAD  * 4 ;
  static const float  PAD4F                 = PADF * 4.0f ;
  static const int    PAD5                  = PAD  * 5 ;
  static const float  PAD5F                 = PADF * 5.0f ;
  static const float  BORDER_PX             = 1.0f ;
  static const float  BORDER2_PX            = 2.0f ;
  static const float  BORDER_RADIUS         = 10.0f ;
  static const Colour BORDER_L0_COLOR       = Colour(0xFF808080) ; // nest level 0
  static const Colour BORDER_L1_COLOR       = Colour(0xFFA0A0A0) ; // ...
  static const Colour BORDER_L2_COLOR       = Colour(0xFFC0C0C0) ; // ...
  static const Colour BORDER_L3_COLOR       = Colour(0xFFE0E0E0) ; // ...
  static const Colour BORDER_L4_COLOR       = Colour(0xFFFFFFFF) ; // nest level 4
  static const Colour BACKGROUND_L0_COLOR   = Colour(0xFF404040) ; // nest level 0
  static const Colour BACKGROUND_L1_COLOR   = Colour(0xFF303030) ; // ...
  static const Colour BACKGROUND_L2_COLOR   = Colour(0xFF202020) ; // ...
  static const Colour BACKGROUND_L3_COLOR   = Colour(0xFF101010) ; // ...
  static const Colour BACKGROUND_LTOP_COLOR = Colour(0xFF000000) ; // innermost nest level
  static const Colour TEXT_EMPTY_COLOR      = Colour(0x80808080) ;
  static const Colour TEXT_NORMAL_COLOR     = Colour(0xFFFFFFFF) ;
  static const Colour TEXT_HILITE_COLOR     = Colour(0xFFFFFFFF) ;
  static const Colour TEXT_HILITEBG_COLOR   = Colour(0xFF000040) ;
  static const Colour TEXT_CARET_COLOR      = Colour(0xFFBBBBFF) ;

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
  static const String CONFIG_GUI_ID                 = "config-gui" ;
  static const int    AUDIO_TAB_IDX                 = 0 ;
  static const int    CLIENT_TAB_IDX                = 1 ;
  static const int    GUI_TAB_IDX                   = 2 ;
  static const int    BLACKLIST_TAB_IDX             = 3 ;
  static const String AUDIO_TAB_TEXT                = "audio" ;
  static const String CLIENT_TAB_TEXT               = "client" ;
  static const String GUI_TAB_TEXT                  = "gui" ;
  static const String BLACKLIST_TAB_TEXT            = "ignores" ;
  static const Colour AUDIO_TAB_COLOR               = Colour(0xFF002000) ;
  static const Colour CLIENT_TAB_COLOR              = Colour(0xFF202000) ;
  static const Colour GUI_TAB_COLOR                 = Colour(0xFF000020) ;
  static const Colour BLACKLIST_TAB_COLOR           = Colour(0xFF200000) ;
  static const Colour DISMISS_BTN_OUT_INIT_COLOR    = Colour(0xFF404000) ;
  static const Colour DISMISS_BTN_OUT_ERROR_COLOR   = Colour(0xFF400000) ;
  static const Colour DISMISS_BTN_OUT_NORMAL_COLOR  = Colour(0xFF004000) ;
  static const Colour DISMISS_BTN_IN_INIT_COLOR     = Colour(0xFF808000) ;
  static const Colour DISMISS_BTN_IN_ERROR_COLOR    = Colour(0xFF800000) ;
  static const Colour DISMISS_BTN_IN_NORMAL_COLOR   = Colour(0xFF008000) ;
  static const Colour DISMISS_BTN_TEXT_INIT_COLOR   = Colour(0xFFFFFF00) ;
  static const Colour DISMISS_BTN_TEXT_ERROR_COLOR  = Colour(0xFFFF0000) ;
  static const Colour DISMISS_BTN_TEXT_NORMAL_COLOR = Colour(0xFF00FF00) ;
  static const String DISMISS_BTN_INIT_TEXT         = "initializing" ;
  static const String DISMISS_BTN_ERROR_TEXT        = "error" ;
  static const String DISMISS_BTN_NORMAL_TEXT       = "done" ;

  // ConfigAudio
  static const int         DEFAULT_DS_INDEX     = 0 ;
  static const int         DEFAULT_CA_INDEX     = 0 ;
  static const int         DEFAULT_ALSA_INDEX   = 0 ;
  static const String      BUFFERS_GROUP_TEXT   = "buffers" ;
  static const String      NSOURCES_LABEL_TEXT  = "# of sources" ;
  static const String      NCHANNELS_LABEL_TEXT = "# of channels" ;
  static const String      ASIO_DEVICE_TYPE     = "ASIO" ;
  static const String      KS_DEVICE_TYPE       = "KernelStreaming" ; // non-juce
  static const String      DS_DEVICE_TYPE       = "DirectSound" ;
  static const String      WAVE_DEVICE_TYPE     = "Wave" ;            // non-juce
  static const String      WASAPI_DEVICE_TYPE   = "WASAPI" ;
  static const String      CA_DEVICE_TYPE       = "CoreAudio" ;
  static const String      JACK_DEVICE_TYPE     = "JACK" ;
  static const String      ALSA_DEVICE_TYPE     = "ALSA" ;
  static const String      ROID_DEVICE_TYPE     = "Android" ;
  static const String      SLES_DEVICE_TYPE     = "OpenSLES" ;
  static const String      IOS_DEVICE_TYPE      = "iOSAudio" ;
  static const String      NFG_DEVICE_TYPE      = "unknown" ;         // non-juce
#define WINAUDIOAPIS ASIO_DEVICE_TYPE + "\n" + KS_DEVICE_TYPE   + "\n" + \
                     DS_DEVICE_TYPE   + "\n" + WAVE_DEVICE_TYPE
#define MACAUDIOAPIS CA_DEVICE_TYPE
#define NIXAUDIOAPIS JACK_DEVICE_TYPE + "\n" + ALSA_DEVICE_TYPE
#define BUFFERSIZES  "32\n64\n128\n256\n512\n1024\n2048\n4096\n8192"
#ifdef _WIN32
  static const StringArray AUDIO_APIS           = StringArray::fromLines(WINAUDIOAPIS) ;
#else // _WIN32
#  ifdef _MAC
  static const StringArray AUDIO_APIS           = StringArray::fromLines(MACAUDIOAPIS) ;
#  else // _MAC
  static const StringArray AUDIO_APIS           = StringArray::fromLines(NIXAUDIOAPIS) ;
#  endif // _MAC
#endif // _WIN32
  static const StringArray BUFFER_SIZES         = StringArray::fromLines(BUFFERSIZES) ;
  static const int         BIT_DEPTH_16         = 16 ;
  static const int         BIT_DEPTH_24         = 24 ;
  static const int         BIT_DEPTH_32         = 32 ;
  static const int         SAMPLE_RATE_44100    = 44100 ;
  static const int         SAMPLE_RATE_48000    = 48000 ;
  static const int         SAMPLE_RATE_96000    = 96000 ;
  static const int         MIN_N_BUFFERS        = 2 ;
  static const int         MAX_N_BUFFERS        = 16 ;
  static const int         MIN_N_SOURCES        = 0 ;
  static const int         MAX_N_SOURCES        = 16 ;
  static const int         MIN_N_SINKS          = 0 ;
  static const int         MAX_N_SINKS          = 16 ;

  // ConfigClient
  static const int CONFIG_SCROLLBAR_W   = 12 ;
  static const int BLACKLIST_X          = 24 ;
  static const int BLACKLIST_Y          = 68 ;
  static const int BLACKLIST_W          = 144 ;
  static const int BLACKLIST_H          = 76 ;
#define SAVEMODES "delete asap\ndo not save\nsave ogg\nsave ogg and wav"
#define DEBUGLEVELS "silent\naudio\naudio and network\nlinjam trace"
  static const StringArray SAVE_MODES   = StringArray::fromLines(SAVEMODES  ) ;
  static const StringArray DEBUG_LEVELS = StringArray::fromLines(DEBUGLEVELS) ;

  // ConfigGui
#define FONTSIZES  "12\n16\n20\n24\n36\n48"
#define UPDATEIVLS "none\nslow\nnormal\nfast"
  static const StringArray FONT_SIZES  = StringArray::fromLines(FONTSIZES ) ;
  static const StringArray UPDATE_IVLS = StringArray::fromLines(UPDATEIVLS) ;

  // ConfigBlacklist
  static const int BLACKLIST_ENTRY_W = BLACKLIST_W - CONFIG_SCROLLBAR_W - PAD2 ;
  static const int BLACKLIST_ENTRY_H = 16 ;

  // Login
  static const String LOGIN_GUI_ID                   = "login-gui" ;
  static const int    N_STATIC_LOGIN_CHILDREN        = 6 ;
  static const int    LOGIN_BUTTON_L                 = GUI::PAD ;
  static const int    LOGIN_BUTTON_T                 = GUI::PAD ;
  static const int    LOGIN_BUTTON_W                 = 128 ;
  static const int    LOGIN_BUTTON_H                 = 24 ;
  static const Colour PROMPT_BACKGROUND_NORMAL_COLOR = Colour(0xFF000000) ;
  static const Colour PROMPT_BORDER_NORMAL_COLOR     = Colour(0xFFFFFFFF) ;
  static const Colour PROMPT_FOCUS_NORMAL_COLOR      = Colour(0xFFFFFFFF) ;
  static const Colour PROMPT_BACKGROUND_ERROR_COLOR  = Colour(0xFF200000) ;
  static const Colour PROMPT_BORDER_ERROR_COLOR      = Colour(0xFF800000) ;
  static const Colour PROMPT_FOCUS_ERROR_COLOR       = Colour(0xFFFF0000) ;
  static const String HOST_PROMPT_TEXT               = "<type a server url here>" ;
  static const String LOGIN_PROMPT_TEXT              = "<type a nickname here>" ;
  static const String PASS_PROMPT_TEXT               = "<type a password here>" ;

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
  static const String CHAT_PROMPT_TEXT      = "<type some chat here - then press ENTER key to send>" ;
  static const Colour TOPIC_TEXT_COLOR      = Colour(0xFF8080FF) ;
  static const Colour CHAT_TEXT_COLOR       = Colour(0xFF808080) ;
  static const Colour CHAT_OUTLINE_COLOR    = Colour(0x00000000) ;
  static const Colour CHAT_FOCUS_COLOR      = Colour(0x00000000) ;
  static const Colour CHAT_SHADOW_COLOR     = Colour(0x00000000) ;
  static const Colour CHAT_TEXT_BG_COLOR    = Colour(0x00000000) ;
  static const int    MIN_SHOW_TOPIC_CHAT_H = 200 ;
  static const float  CHAT_PANE_BORDER_X    = 0.0f ;
  static const float  CHAT_PANE_BORDER_Y    = 0.0f ;
  static const float  TOPIC_FONT_H          = 16.0f ;
  static const int    TOPIC_H               = TOPIC_FONT_H ;
  static const float  TOPIC_BORDER_X        = PAD2F ;
  static const float  TOPIC_BORDER_Y        = PAD2F ;
  static const float  TOPIC_BORDER_PADW     = PAD4F ;
  static const float  TOPIC_BORDER_H        = TOPIC_H + PADF ;
  static const int    TOPIC_X               = TOPIC_BORDER_X + PAD ;
  static const int    TOPIC_PADW            = TOPIC_X * 2 ;
  static const int    TOPIC_PADH            = PAD / 2 ;
  static const int    TOPIC_Y               = TOPIC_BORDER_Y + TOPIC_PADH ;
  static const int    CHAT_X                = PAD2 ;
  static const int    CHAT_Y                = PAD2 ;
  static const int    CHAT_WITH_TOPIC_Y     = CHAT_Y + TOPIC_H + PAD2 ;
  static const int    CHAT_PADH             = PAD3 ;
  static const int    CHAT_PADW             = CHAT_X * 2 ;
  static const float  CHAT_ENTRY_PADH       = PADF / 2.0 ;
  static const int    CHAT_ENTRY_PADY       = (CHAT_ENTRY_PADH * 2) + PAD ;
  static const float  CHAT_BORDER_X         = PADF ;
  static const float  CHAT_BORDER_Y         = PADF ;
  static const float  CHAT_BORDER_PADW      = CHAT_BORDER_X * 2.0 ;

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
  static const double           VU_DB_RANGE                = 140.0 ;
  static const double           VU_DB_MIN                  = -120.0 ;

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
  static const int    CHANNEL_SCROLL_BTN_Y    = MIXERGROUP_Y               +
                                                (MIXERGROUP_H / 2)         -
                                                (CHANNEL_SCROLL_BTN_H / 2) ;

  // StatusBar
  static const String STATUS_GUI_ID          = "statusbar-gui" ;
  static const String AUDIO_INIT_MSG         = "initializing audio" ;
  static const String AUDIO_INIT_ERROR_MSG   = "audio device error" ;
  static const String CONFIG_PENDING_MSG     = "press '" + DISMISS_BTN_NORMAL_TEXT + "' to continue" ;
  static const String DISCONNECTED_TEXT      = "Disconnected" ;
  static const String ROOM_FULL_TEXT         = "Jam room full" ;
  static const String INVALID_AUTH_TEXT      = "Invalid login/pass" ;
  static const String LICENSE_PENDING_TEXT   = "Pending license" ;
  static const String FAILED_CONNECTION_TEXT = "Connection failed" ;
  static const String CONNECTING_TEXT        = "Connecting to " ;
  static const String CONNECTED_TEXT         = "Connected to " ;
  static const String IDLE_TEXT              = "Ready" ;
  static const int    STATUSBAR_H            = 24 ;
  static const int    STATUS_W               = 160 ;
  static const int    STATUS_H               = 16 ;
  static const int    STATUS_PAD_X           = 8 ;
  static const int    STATUS_PAD_Y           = 2 ;

  // Loop
  static const String LOOP_GUI_ID = "loop-gui" ;
  static const int    LOOP_X      = STATUS_W + PAD3 ;
  static const int    LOOP_H      = STATUS_H ;
}


// KLUDGE: no valid conversion for String(a_var) on linux
#define str(a_var) a_var.toString()

#endif // _CONSTANTS_H_
