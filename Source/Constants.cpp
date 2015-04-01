
#include "Constants.h"
#include "LinJamConfig.h"


// login and validations
const int       NETWORK::N_LOGIN_RETRIES = 3 ;
const StringRef NETWORK::HOST_MASK       = "*.*:*" ;
const StringRef NETWORK::LETTERS         = "abcdefghijklmnopqrstuvwxyz" ;
const StringRef NETWORK::DIGITS          = "0123456789" ;
const StringRef NETWORK::URL_CHARS       = "0123456789abcdefghijklmnopqrstuvwxyz-." ;

// known hosts and bots
const String      NETWORK::LOCALHOST_HOSTNAME = "localhost" ;
const String      NETWORK::LOCALHOST_2049_URL = "localhost:2049" ;
const String      NETWORK::NINJAM_2049_URL    = "test.ninjam.com:2049" ;
const String      NETWORK::NINJAM_2050_URL    = "test.ninjam.com:2050" ;
const String      NETWORK::NINJAM_2051_URL    = "test.ninjam.com:2051" ;
const String      NETWORK::NINJAM_2052_URL    = "test.ninjam.com:2052" ;
const String      NETWORK::NINJAM_2600_URL    = "test.ninjam.com:2600" ;
const String      NETWORK::NINJAM_2601_URL    = "test.ninjam.com:2601" ;
const String      NETWORK::NINBOT_2049_URL    = "ninbot.com:2049" ;
const String      NETWORK::NINBOT_2050_URL    = "ninbot.com:2050" ;
const String      NETWORK::NINBOT_2051_URL    = "ninbot.com:2051" ;
const String      NETWORK::NINBOT_2052_URL    = "ninbot.com:2052" ;
const String      NETWORK::NINJAMER_2049_URL  = "ninjamer.com:2049" ;
const String      NETWORK::NINJAMER_2050_URL  = "ninjamer.com:2050" ;
const String      NETWORK::NINJAMER_2051_URL  = "ninjamer.com:2051" ;
const String      NETWORK::NINJAMER_2052_URL  = "ninjamer.com:2052" ;
const String      NETWORK::SERVEBEER_2049_URL = "ninjamers.servebeer.com:2049" ;
const String      NETWORK::SERVEBEER_2050_URL = "ninjam-studio.servebeer.com:2050" ;
const String      NETWORK::MUTANTLAB_2049_URL = "mutantlab.com:2049" ;
const Identifier  NETWORK::NINBOT_USER        = "ninbot" ;
const Identifier  NETWORK::JAMBOT_USER        = "Jambot" ;
const Identifier  NETWORK::BEERBOT_USER       = "LiveStream" ;
const String      NETWORK::KNOWN_HOSTS_KEY    = "known-hosts" ;
const String      NETWORK::KNOWN_BOTS_KEY     = "known-bots" ;
const XmlElement* NETWORK::KNOWN_HOSTS ;
const XmlElement* NETWORK::KNOWN_BOTS ;

// setup
void NETWORK::Initialize()
{
  // KNOWN_HOSTS and KNOWN_BOTS are destroyed in LinJam::Shutdown()
  KNOWN_HOSTS = XmlDocument::parse(String(KNOWN_HOSTS_XML)) ;
  KNOWN_BOTS  = XmlDocument::parse(String(KNOWN_BOTS_XML )) ;
}

// helpers
bool NETWORK::IsKnownHost(String host)
{
  return host.isNotEmpty() && KNOWN_HOSTS->getChildByName(host) != nullptr ;
}
