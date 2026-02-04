
#include "Constants.h"
#include "LinJamConfig.h"
#include "Trace/Trace.h"


// timers
const int        gui_hi_update_ivls[4]   = { 0 , 1000 , 125 , 62 } ;
const Array<int> APP::GUI_HI_UPDATE_IVLS = Array<int>(gui_hi_update_ivls , 4) ;

// login and validations
const int       NETWORK::N_LOGIN_RETRIES = 3 ;
const StringRef NETWORK::HOST_MASK       = "*.*:*" ;
const StringRef NETWORK::LETTERS         = "abcdefghijklmnopqrstuvwxyz" ;
const StringRef NETWORK::DIGITS          = "0123456789" ;
const String    NETWORK::HOST_CHARS      = NINJAM::HOST_CHARS ;
const String    NETWORK::NICK_CHARS      = NINJAM::NICK_CHARS ;

// known hosts and bots
// NOTE: The following servers are indexed by ninjam,com (NETWORK::POLL_URL)
//       but are usually (or perhaps always) offine.
//       For this reason, no *_URL constant is defined for these
//       and these are not declared in KNOWN_HOSTS_XML or KNOWN_BOTS_XML.
// * jam.onlinemusiccollabs.com:2049
// * lazapada.net:2049
// * ninjam.jaminpeace.net:2049
const String     NETWORK::DEVEL_HOST        = "localhost" ;
const String     NETWORK::DEVEL_HOST_URL    = "localhost:2049" ;
const String     NETWORK::NINBOT_2049_URL   = "ninbot.com:2049" ;
const String     NETWORK::NINBOT_2050_URL   = "ninbot.com:2050" ;
const String     NETWORK::NINBOT_2051_URL   = "ninbot.com:2051" ;
const String     NETWORK::NINBOT_2052_URL   = "ninbot.com:2052" ;
const String     NETWORK::NINBOT_2053_URL   = "ninbot.com:2053" ;
const String     NETWORK::NINBOT_2054_URL   = "ninbot.com:2054" ;
const String     NETWORK::NINJAMER_2049_URL = "ninjamer.com:2049" ;
const String     NETWORK::NINJAMER_2050_URL = "ninjamer.com:2050" ;
const String     NETWORK::NINJAMER_2051_URL = "ninjamer.com:2051" ;
const String     NETWORK::NINJAMER_2052_URL = "ninjamer.com:2052" ;
const String     NETWORK::GETAROOM_URL      = "getaroom-na.ninjam.com:2049" ;
const String     NETWORK::MUSICORNER_URL    = "musicorner.redirectme.net:2050" ;
const String     NETWORK::MUTANTLAB_URL     = "mutantlab.com:2049" ;
const String     NETWORK::ROOTSOCIETY_URL   = "ninbot.rootsociety.nl:8001" ;
const String     NETWORK::BOTNU_URL         = "ninjam.bot.nu:2049" ;
const Identifier NETWORK::NINBOT_LOGIN      = "ninbot_" ;
const Identifier NETWORK::JAMBOT_LOGIN      = "Jambot" ;
const String     NETWORK::KNOWN_HOSTS_KEY   = "known-hosts" ;
const String     NETWORK::KNOWN_BOTS_KEY    = "known-bots" ;
ValueTree        NETWORK::KNOWN_HOSTS ;    // APP::Initialize()
ValueTree        NETWORK::KNOWN_BOTS ;     // APP::Initialize()

// http requests
// const String NETWORK::WEBSITE_URL = "http://teamstream.herokuapp.com" ; // WIP: new stats
// const String NETWORK::VERSION_URL = WEBSITE_URL + "/version.txt" ;      // WIP: new stats
// const String NETWORK::CLIENTS_URL = WEBSITE_URL + "/clients.text" ;     // WIP: new stats
// const URL    NETWORK::POLL_URL    = URL(CLIENTS_URL) ;                  // WIP: new stats
// const URL    NETWORK::POLL_URL    = URL("http://192.168.254.1/jammers.csv") ; // WIP: new stats
const URL    NETWORK::POLL_URL    = URL("http://autosong.ninjam.com/server-list.php") ; // WIP: new stats
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
  // NOTE: destruction in LinJam::Shutdown()
  UPTR<XmlElement> known_hosts = XmlDocument::parse(String(KNOWN_HOSTS_XML)) ;
  NETWORK::KNOWN_HOSTS         = ValueTree::fromXml(*known_hosts) ;
  UPTR<XmlElement> known_bots  = XmlDocument::parse(String(KNOWN_BOTS_XML)) ;
  NETWORK::KNOWN_BOTS          = ValueTree::fromXml(*known_bots) ;
}


/* helpers */

StringArray APP::ParseServerlist(String html)
{
  StringArray lines = APP::ParseLines(html) ;
  int         line_n ;
  String      line ;
  StringArray jams ;
  String      host ;
  String      stats ;
  String      topic ;
  String      bpi ;
  String      bpm ;
  String      n_users ;
  String      n_slots ;
  String      login ;
  String      host_id  ;
  bool        is_bot ;
  int         jam_n ;
  String      jam_csv ;

  for (line_n = 0 ; line_n < lines.size() ; ++line_n)
  {
    line = lines[line_n] ;

    // parse channel stats
    if (line.contains("<ul>"))
    {
      if (line.startsWith("</ul>"))
        line  = line   .fromFirstOccurrenceOf("</ul>" , false , false) ;
      host    = line   .upToFirstOccurrenceOf(" <"    , false , false) ;
      stats   = line   .fromFirstOccurrenceOf("<ul>"  , false , false)
                       .upToFirstOccurrenceOf("<UL>"  , false , false) ;
      topic   = stats  .upToFirstOccurrenceOf("<BR>"  , false , false) ;
      bpm     = stats  .fromFirstOccurrenceOf("<BR>"  , false , false)
                       .upToFirstOccurrenceOf(" BPM/" , false , false) ;
      bpi     = stats  .fromFirstOccurrenceOf(" BPM/" , false , false)
                       .upToFirstOccurrenceOf("<BR>"  , false , false) ;
      n_users = stats  .fromLastOccurrenceOf ("<BR>"  , false , false)
                       .upToFirstOccurrenceOf(" "     , false , false) ;
      n_slots = n_users.fromFirstOccurrenceOf("/"     , false , false) ;
      n_users = n_users.upToFirstOccurrenceOf("/"     , false , false) ;
      jam_csv = StringArray(host , topic , n_slots , n_users , bpi , bpm).joinIntoString(",") ;

      if (! topic.startsWith("Server down:")) jams.add(jam_csv) ; // hide offline servers

      Trace::TraceNetworkVb("collecting jammers at: " + host) ;
    }

    // parse channel users
    else if (! line.contains("<UL>") && ! line.contains("</UL>"))
    {
      if (host.isEmpty()                 ) continue ;
      if (line.contains(">Last updated ")) break ;

      login   = line.upToFirstOccurrenceOf("<" , false , false) ;
      host_id = Id2Str(LinJamConfig::MakeHostId(host)) ;
      is_bot  = NETWORK::IsKnownBot(host_id , login) ;

      if (! is_bot)
      {
        jam_n   = jams.size() - 1 ;
        jam_csv = jams[jam_n] + "," + login ;
        jams.set(jam_n , jam_csv) ;
      }

      Trace::TraceNetworkVb("\tjammer: " + login + (is_bot ? " (known bot)" : "")) ;
    }
  }

  return jams ;
}

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

bool NETWORK::IsKnownBot(String host , String login)
{
  return str(KNOWN_BOTS.getProperty(host , "")) == login ;
}
