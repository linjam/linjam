
#include "Constants.h"
#include "LinJamConfig.h"


// timers
int              gui_hi_update_ivls[4]   = { 0 , 1000 , 125 , 62 } ;
const Array<int> APP::GUI_HI_UPDATE_IVLS = Array<int>(gui_hi_update_ivls , 4) ;

// login and validations
const int       NETWORK::N_LOGIN_RETRIES = 3 ;
const StringRef NETWORK::HOST_MASK       = "*.*:*" ;
const StringRef NETWORK::LETTERS         = "abcdefghijklmnopqrstuvwxyz" ;
const StringRef NETWORK::DIGITS          = "0123456789" ;
const String    NETWORK::HOST_CHARS      = NINJAM::HOST_CHARS ;
const String    NETWORK::NICK_CHARS      = NINJAM::NICK_CHARS ;

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
ValueTree         NETWORK::KNOWN_HOSTS ; // APP::Initialize()
ValueTree         NETWORK::KNOWN_BOTS ;  // APP::Initialize()

// http requests
const String NETWORK::WEBSITE_URL = "http://teamstream.herokuapp.com" ;
const String NETWORK::VERSION_URL = WEBSITE_URL + "/version.txt" ;
const String NETWORK::CLIENTS_URL = WEBSITE_URL + "/clients.text" ;
const URL    NETWORK::POLL_URL    = URL(CLIENTS_URL) ;
// outbound control messages
const String NETWORK::LOGIN_KEY   = "login" ;
const String NETWORK::HOST_KEY    = "server" ;
// const String NETWORK::MODE_KEY    = "mode" ;
// const String NETWORK::LINKS_KEY   = "links" ;
// const String NETWORK::COLOR_KEY   = "color" ;
// inbound control messages
const String NETWORK::USER_KEY    = "user" ;


/* setup */

void APP::Initialize()
{
  // KNOWN_HOSTS and KNOWN_BOTS are destroyed in LinJam::Shutdown()
//   NETWORK::KNOWN_HOSTS = XmlDocument::parse(String(KNOWN_HOSTS_XML)) ;
//   NETWORK::KNOWN_BOTS  = XmlDocument::parse(String(KNOWN_BOTS_XML )) ;
  UPTR<XmlElement> known_hosts = XmlDocument::parse(String(KNOWN_HOSTS_XML)) ;
  NETWORK::KNOWN_HOSTS         = ValueTree::fromXml(*known_hosts) ;
  UPTR<XmlElement> known_bots  = XmlDocument::parse(String(KNOWN_BOTS_XML)) ;
  NETWORK::KNOWN_BOTS          = ValueTree::fromXml(*known_bots) ;
}


/* helpers */

StringArray APP::ParseLines(String a_string)
{
  StringArray lines = StringArray::fromLines(a_string) ;
  lines.trim() ; lines.removeEmptyStrings() ;

  return lines ;
}

StringArray APP::ParseCSV(String a_string)
{
  return StringArray::fromTokens(a_string , "," , String()) ;
}

String APP::Pluck(StringArray* a_stringarray , int idx)
{
  String a_string = (*a_stringarray)[idx] ; a_stringarray->remove(idx) ;

  return a_string ;
}

bool NETWORK::IsKnownHost(String host)
{
  return host.isNotEmpty() && KNOWN_HOSTS.getChildWithName(Identifier(host)).isValid() ;
}
