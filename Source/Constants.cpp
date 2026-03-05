
#include "Constants.h"
#include "LinJamConfig.h"
#include "Trace/TraceLogin.h"


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
// NOTE: The following servers are indexed by ninjam,com (NETWORK::POLL_JAMS_URL)
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
const String     NETWORK::GETAROOM_URL      = "getaroom-na.ninjam.com:2049" ; // "lobby" chat - no audio
const String     NETWORK::MUSICORNER_URL    = "musicorner.redirectme.net:2050" ;
const String     NETWORK::MUTANTLAB_URL     = "mutantlab.com:2049" ;
const String     NETWORK::ROOTSOCIETY_URL   = "ninbot.rootsociety.nl:8001" ;
const String     NETWORK::BOTNU_URL         = "ninjam.bot.nu:2049" ;
const Identifier NETWORK::NINBOT_LOGIN      = "ninbot_" ;
const Identifier NETWORK::JAMBOT_LOGIN      = "Jambot" ;
const String     NETWORK::KNOWN_HOSTS_KEY   = "known-hosts" ;
const String     NETWORK::LOBBY_HOSTS_KEY   = "lobby-hosts" ;
const String     NETWORK::KNOWN_BOTS_KEY    = "known-bots" ;
const String     NETWORK::KNOWN_STREAMS_KEY = "known-streams" ;
ValueTree        NETWORK::KNOWN_HOSTS ;   // APP::Initialize()
ValueTree        NETWORK::LOBBY_HOSTS ;   // APP::Initialize()
ValueTree        NETWORK::KNOWN_BOTS ;    // APP::Initialize()
ValueTree        NETWORK::KNOWN_STREAMS ; // APP::Initialize()

// http requests
const URL    NETWORK::POLL_JAMS_URL    = URL("http://autosong.ninjam.com/serverlist.php") ; // WIP: new stats
const URL    NETWORK::POLL_SIGNALS_URL = URL("http://" + DEVEL_HOST + "/jammers.csv") ; // WIP: heroku server is long gone - re-implement signalling
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
  UPTR<XmlElement> known_hosts   = XmlDocument::parse(String(KNOWN_HOSTS_XML  )) ;
  UPTR<XmlElement> lobby_hosts   = XmlDocument::parse(String(LOBBY_HOSTS_XML  )) ;
  UPTR<XmlElement> known_bots    = XmlDocument::parse(String(KNOWN_BOTS_XML   )) ;
  // UPTR<XmlElement> known_streams = XmlDocument::parse(String(KNOWN_STREAMS_XML)) ; // WIP: stream audition
  NETWORK::KNOWN_HOSTS           = ValueTree::fromXml(*known_hosts  ) ;
  NETWORK::LOBBY_HOSTS           = ValueTree::fromXml(*lobby_hosts  ) ;
  NETWORK::KNOWN_BOTS            = ValueTree::fromXml(*known_bots   ) ;
  // NETWORK::KNOWN_STREAMS         = ValueTree::fromXml(*known_streams) ;            // WIP: stream audition
}


/* helpers */

StringArray APP::ParseServerlist(String serverlist)
{
  // example serverlist (http://autosong.ninjam.com/serverlist.php)
  //   jam   servers eg: SERVER "hostname.tld:2049" "100 BPM/32" "1/8:(empty)" SERVER ... END
  //   lobby servers eg: SERVER "hostname.tld:2049" "lobby"      "Public/private NINJAM room server North America : 0/30 rooms occupied 0 users total in rooms 0 users in lobby" END
  serverlist               = serverlist.replace("SERVER" , "\n").replace("END" , "") ;
 	StringArray servers_data = APP::ParseLines(serverlist) ;
  uint8       server_n      ; String      server_data ;
  String      logins_csv    ; StringArray logins ;
  String      jam_csv       ; StringArray jams ;
  uint8       login_n       ; String      login ;
  StringArray tokens        ;
  String      host          ;
  String      bpi           ;
  String      bpm           ;
  String      n_users       ;
  String      n_slots       ;
  String      host_id       ;
  bool        is_known_host ;
  bool        is_bot        ;

DEBUG_TRACE_SERVERLIST

  for (server_n = 0 ; server_n < servers_data.size() ; ++server_n)
  {
    server_data = servers_data[server_n] ;

    // parse channel stats
    tokens        = StringArray::fromTokens(server_data , true) ;
    tokens.set(0  , tokens[0].removeCharacters("\"")) ;
    tokens.set(1  , tokens[1].removeCharacters("\"")) ;
    tokens.set(2  , tokens[2].removeCharacters("\"")) ;
    host          = tokens[0] ;
    bpi           = tokens[1].fromLastOccurrenceOf ("/" , false , false) ;
    bpm           = tokens[1].upToFirstOccurrenceOf(" " , false , false) ;
    n_users       = tokens[2].upToFirstOccurrenceOf("/" , false , false) ;
    n_slots       = tokens[2].fromLastOccurrenceOf ("/" , false , false)
                             .upToFirstOccurrenceOf(":" , false , false) ;
    logins_csv    = tokens[2].fromLastOccurrenceOf (":" , false , false).replace("(empty)" , "") ;
    is_known_host = NETWORK::IsKnownHost(host) ;
    logins        = APP::ParseCSV(logins_csv) ;
    host_id       = Id2Str(LinJamConfig::MakeHostId(host)) ;
    jam_csv       = StringArray(host , n_users , n_slots , bpi , bpm).joinIntoString(",") ;

DEBUG_TRACE_SERVERLIST_SERVER

    // filter unknown hosts
    if (! is_known_host) continue ;

    // filter known bots
    for (login_n = 0 ; login_n < logins.size() ; ++login_n)
    {
      login  = logins[login_n] ;
      is_bot = NETWORK::IsKnownBot(host_id , login) ;

      if (! is_bot) jam_csv = jam_csv + "," + login ;

DEBUG_TRACE_SERVERLIST_CLIENT
    }

    jams.add(jam_csv) ;
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

bool NETWORK::IsLobbyHost(String host)
{
  return host.isNotEmpty() && LOBBY_HOSTS.getChildWithName(Identifier(host)).isValid() ;
}

bool NETWORK::IsKnownBot(String host , String login)
{
  return str(KNOWN_BOTS.getProperty(host , "")) == login ;
}
