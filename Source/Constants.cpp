
#include "Constants.h"
#include "LinJamConfig.h"


// login and validations
const int       NETWORK::N_LOGIN_RETRIES = 3 ;
const StringRef NETWORK::HOST_MASK       = "*.*:*" ;
const StringRef NETWORK::LETTERS         = "abcdefghijklmnopqrstuvwxyz" ;
const StringRef NETWORK::DIGITS          = "0123456789" ;
const StringRef NETWORK::URL_CHARS       = "0123456789abcdefghijklmnopqrstuvwxyz-." ;

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
const String            NETWORK::KNOWN_HOSTS_KEY            = "known-hosts" ;
const String            NETWORK::KNOWN_BOTS_KEY             = "known-bots" ;

// KNOWN_HOSTS and KNOWN_BOTS are destroyed in LinJam::Shutdown()
const XmlElement* NETWORK::KNOWN_HOSTS = XmlDocument::parse(String(KNOWN_HOSTS_XML)) ;
const XmlElement* NETWORK::KNOWN_BOTS ;
void NETWORK::Initialize()
{
  // KNOWN_BOTS is destroyed in LinJam::Shutdown()
  KNOWN_BOTS = XmlDocument::parse(String(KNOWN_BOTS_XML)) ;
}

// helpers
bool NETWORK::IsKnownHost(String host)
{
  return KNOWN_HOSTS->getChildByName(host) != nullptr ;
}
