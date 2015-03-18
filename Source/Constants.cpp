
#include "Constants.h"
#include "LinJamConfig.h"


// known hosts and bots
const String            NETWORK::LOCALHOST_HOSTNAME         = "localhost" ;
const String            NETWORK::NINJAM_HOSTNAME            = "test.ninjam.com" ;
const String            NETWORK::NINBOT_HOSTNAME            = "ninbot.com" ;
const String            NETWORK::NINJAMER_HOSTNAME          = "ninjamer.com" ;
const String            NETWORK::LOCALHOST_2049_URL         = LOCALHOST_HOSTNAME + ":2049" ;
const String            NETWORK::NINJAM_2049_URL            = NINJAM_HOSTNAME    + ":2049" ;
const String            NETWORK::NINJAM_2050_URL            = NINJAM_HOSTNAME    + ":2050" ;
const String            NETWORK::NINJAM_2051_URL            = NINJAM_HOSTNAME    + ":2051" ;
const String            NETWORK::NINJAM_2052_URL            = NINJAM_HOSTNAME    + ":2052" ;
const String            NETWORK::NINJAM_2600_URL            = NINJAM_HOSTNAME    + ":2600" ;
const String            NETWORK::NINJAM_2601_URL            = NINJAM_HOSTNAME    + ":2601" ;
const String            NETWORK::NINBOT_2049_URL            = NINBOT_HOSTNAME    + ":2049" ;
const String            NETWORK::NINBOT_2050_URL            = NINBOT_HOSTNAME    + ":2050" ;
const String            NETWORK::NINBOT_2051_URL            = NINBOT_HOSTNAME    + ":2051" ;
const String            NETWORK::NINBOT_2052_URL            = NINBOT_HOSTNAME    + ":2052" ;
const String            NETWORK::NINJAMER_2049_URL          = NINJAMER_HOSTNAME  + ":2049" ;
const String            NETWORK::NINJAMER_2050_URL          = NINJAMER_HOSTNAME  + ":2050" ;
const String            NETWORK::NINJAMER_2051_URL          = NINJAMER_HOSTNAME  + ":2051" ;
const String            NETWORK::NINJAMER_2052_URL          = NINJAMER_HOSTNAME  + ":2052" ;
const Identifier        NETWORK::NINBOT_USER                = "ninbot" ;
const Identifier        NETWORK::JAMBOT_USER                = "Jambot" ;
#ifdef KNOWN_HOSTS_AS_ARRAY // (issue #64)
const String            NETWORK::known_hosts[N_KNOWN_HOSTS] = { LOCALHOST_2049_URL ,
                                                                NINBOT_2049_URL    ,
                                                                NINBOT_2050_URL    ,
                                                                NINBOT_2051_URL    ,
                                                                NINBOT_2052_URL    ,
                                                                NINJAMER_2049_URL  ,
                                                                NINJAMER_2050_URL  ,
                                                                NINJAMER_2051_URL  ,
                                                                NINJAMER_2052_URL  } ;
const Array<String>     NETWORK::KNOWN_HOSTS                =
      Array<String>(    known_hosts , N_KNOWN_HOSTS) ;
//StringArray            NETWORK::KNOWN_HOSTS ;
#else // KNOWN_HOSTS_AS_ARRAY
#  ifdef KNOWN_HOSTS_AS_XML // (issue #64)
const String NETWORK::KNOWN_HOSTS_KEY = "known-hosts" ;
#define XML_HEADER "<?xml version=\"1.0\"?><"
#define KNOWN_HOSTS_XML XML_HEADER + \
  KNOWN_HOSTS_KEY       + "><"     + \
    LOCALHOST_2049_URL  + " /><"   + \
    NINBOT_2049_URL     + " /><"   + \
    NINBOT_2050_URL     + " /><"   + \
    NINBOT_2051_URL     + " /><"   + \
    NINBOT_2052_URL     + " /><"   + \
    NINJAMER_2049_URL   + " /><"   + \
    NINJAMER_2050_URL   + " /><"   + \
    NINJAMER_2051_URL   + " /><"   + \
    NINJAMER_2052_URL   + " /></"  + \
  KNOWN_HOSTS_KEY       + ">"
// destroyed in LinJam::Shutdown()
const XmlElement* NETWORK::KNOWN_HOSTS = XmlDocument::parse(String(KNOWN_HOSTS_XML)) ;
#  endif // KNOWN_HOSTS_AS_XML
#endif // KNOWN_HOSTS_AS_ARRAY
#ifdef KNOWN_BOTS_AS_MAP // (issue #64)
HashMap<String , Identifier> NETWORK::KNOWN_BOTS ;


void NETWORK::Init()
{
/* StringArray - ok if non-const
  KNOWN_HOSTS.addTokens(StringRef("LOCALHOST_2049_URL                   ") , false) ;
  KNOWN_HOSTS.addTokens(StringRef("NINBOT_2049_URL    NINBOT_2050_URL   ") , false) ;
  KNOWN_HOSTS.addTokens(StringRef("NINBOT_2051_URL    NINBOT_2052_URL   ") , false) ;
  KNOWN_HOSTS.addTokens(StringRef("NINJAMER_2049_URL  NINJAMER_2050_URL ") , false) ;
  KNOWN_HOSTS.addTokens(StringRef("NINJAMER_2051_URL  NINJAMER_2052_URL ") , false) ;
*/

  KNOWN_BOTS.set(NINBOT_2049_URL   , NINBOT_USER) ;
  KNOWN_BOTS.set(NINBOT_2050_URL   , NINBOT_USER) ;
  KNOWN_BOTS.set(NINBOT_2051_URL   , NINBOT_USER) ;
  KNOWN_BOTS.set(NINBOT_2052_URL   , NINBOT_USER) ;
  KNOWN_BOTS.set(NINJAMER_2049_URL , JAMBOT_USER) ;
  KNOWN_BOTS.set(NINJAMER_2050_URL , JAMBOT_USER) ;
  KNOWN_BOTS.set(NINJAMER_2051_URL , JAMBOT_USER) ;
  KNOWN_BOTS.set(NINJAMER_2052_URL , JAMBOT_USER) ;

//   N_KNOWN_HOSTS = KNOWN_HOSTS.size() ;
//DBG("N_KNOWN_HOSTS=" + String(KNOWN_HOSTS.size())) ;
}
#else // KNOWN_BOTS_AS_MAP
#  ifdef KNOWN_BOTS_AS_XML // (issue #64)
const String NETWORK::KNOWN_BOTS_KEY = "known-bots" ;
#define KNOWN_BOTS_XML XML_HEADER                                        + \
  NETWORK::KNOWN_BOTS_KEY                                        + " "   + \
    String(LinJamConfig::MakeHostId(NETWORK::NINBOT_2049_URL  )) + "=\"" + \
    String(NETWORK::NINBOT_USER)                                 + "\" " + \
    String(LinJamConfig::MakeHostId(NETWORK::NINBOT_2050_URL  )) + "=\"" + \
    String(NETWORK::NINBOT_USER)                                 + "\" " + \
    String(LinJamConfig::MakeHostId(NETWORK::NINBOT_2051_URL  )) + "=\"" + \
    String(NETWORK::NINBOT_USER)                                 + "\" " + \
    String(LinJamConfig::MakeHostId(NETWORK::NINBOT_2052_URL  )) + "=\"" + \
    String(NETWORK::NINBOT_USER)                                 + "\" " + \
    String(LinJamConfig::MakeHostId(NETWORK::NINJAMER_2049_URL)) + "=\"" + \
    String(NETWORK::JAMBOT_USER)                                 + "\" " + \
    String(LinJamConfig::MakeHostId(NETWORK::NINJAMER_2050_URL)) + "=\"" + \
    String(NETWORK::JAMBOT_USER)                                 + "\" " + \
    String(LinJamConfig::MakeHostId(NETWORK::NINJAMER_2051_URL)) + "=\"" + \
    String(NETWORK::JAMBOT_USER)                                 + "\" " + \
    String(LinJamConfig::MakeHostId(NETWORK::NINJAMER_2052_URL)) + "=\"" + \
    String(NETWORK::JAMBOT_USER)                                 + "\" " + \
  "/>"
const XmlElement* NETWORK::KNOWN_BOTS ;

void NETWORK::Initialize()
{
  // KNOWN_BOTS is destroyed in LinJam::Shutdown()
  KNOWN_BOTS = XmlDocument::parse(String(KNOWN_BOTS_XML)) ;
/*
  KNOWN_BOTS = XmlDocument::parse(String(
  "<?xml version=\"1.0\"?><"                        +
    KNOWN_BOTS_KEY                                        + " "   +
      String(LinJamConfig::MakeHostId(NINBOT_HOSTNAME  ))         +
          "=\"" + String(NINBOT_USER)                     + "\" " +
      String(LinJamConfig::MakeHostId(NINJAMER_HOSTNAME))         +
          "=\"" + String(JAMBOT_USER)                     + "\" " +
    "/>"
  )) ;
*/
}

/* or load XmlElement explicitly like:
void NETWORK::Init()
{
  // (if non-const)
  KNOWN_BOTS = new XmlElement(KNOWN_BOTS_KEY) ;
  KNOWN_BOTS->setAttribute(LinJamConfig::MakeHostId(NINBOT_2049_URL)   ,
                           String(NINBOT_USER)) ;
  KNOWN_BOTS->setAttribute(LinJamConfig::MakeHostId(NINJAMER_2049_URL) ,
                           String(JAMBOT_USER)) ;
}
*/

bool NETWORK::IsKnownHost(String host)
{
  return KNOWN_HOSTS->getChildByName(host) != nullptr ;
}
#  endif // KNOWN_BOTS_AS_XML
#endif // KNOWN_BOTS_AS_MAP

// login and validations
const StringRef NETWORK::HOST_MASK = "*.*:*" ;
const StringRef NETWORK::LETTERS   = "abcdefghijklmnopqrstuvwxyz" ;
const StringRef NETWORK::DIGITS    = "0123456789" ;
const StringRef NETWORK::URL_CHARS = "0123456789abcdefghijklmnopqrstuvwxyz-." ;
