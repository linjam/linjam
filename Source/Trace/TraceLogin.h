#if DEBUG

#include "Trace.h"


/* state */

#define DEBUG_TRACE_LOGIN_LOAD                                                             \
  Trace::TraceState("lobby - " + ((host.isEmpty()) ? "no previous logins" :                \
                                                     "restoring credentials for " + host)) ;

#define DEBUG_TRACE_LOBBY_QUICKLOGIN                                                         \
  String status = String((credentials.isValid()) ? "" : "not ") ;                            \
  Trace::TraceEvent("quick-login - storage " + status + "found for host '" + host + "' - " + \
                    ((should_agree) ? "loading" : "ignoring")                              ) ;

#define DEBUG_TRACE_LOGIN_VALIDATION                                                           \
  if (!validateHost() || !validateLogin() || !validatePass())                                  \
    Trace::TraceError(String("error validating credentials:")                                + \
                      " host("  + String((validateHost() ) ? "ok)" : "nfg)='" + host  + "'") + \
                      " login(" + String((validateLogin()) ? "ok)" : "nfg)='" + login + "'") + \
                      " pass("  + String((validatePass() ) ? "ok)" : "nfg)"                ) ) ;

#define DEBUG_TRACE_LOGIN_UPDATECLIENTS                                       \
  { StringArray logins ; String log_msg ;                                     \
    uint8 n_clients = changed_clients.getNumChildren() ;                      \
    for (int client_n = 0 ; client_n < n_clients ; ++client_n)                \
      logins.add(str(changed_clients.getChild(client_n)[CONFIG::LOGIN_ID])) ; \
    log_msg = "updating host: " + client_host                +                \
              " ("              + String(n_clients)          +                \
              ") clients: "     + logins.joinIntoString(",") ;                \
    Trace::TraceConfig(log_msg) ;                                             }

#define DEBUG_TRACE_LOGIN_LAYOUTLOGINBTNS StringArray hosts ;                           \
  for (int host_n = 0 ; host_n < serversStore.getNumChildren() ; ++host_n)              \
  {                                                                                     \
    ValueTree   server_store  = serversStore.getChild(host_n) ;                         \
    ValueTree   clients_store = server_store.getChildWithName(CONFIG::CLIENTS_ID) ;     \
    String      host          = Id2Str(server_store.getType()) ;                        \
    String      server_n      = String(host_n).paddedLeft('0' , 2) ;                    \
    uint8       n_clients     = clients_store.getNumChildren() ;                        \
    Trace::TraceGuiVb("button order: server[" + server_n + "](" + String(n_clients) +   \
                      " clients)="            + host                                ) ; \
                                                                                        \
    StringArray logins ; String log_msgvb ;                                             \
    for (int client_n = 0 ; client_n < n_clients ; ++client_n)                          \
      logins.add(str(clients_store.getChild(client_n)[CONFIG::LOGIN_ID])) ;             \
    log_msgvb = "sorted login button for jam at host: " + host +                        \
                " " + logins.joinIntoString(",")               ;                        \
    if (n_clients) { hosts.add(host) ; Trace::TraceGuiVb(log_msgvb) ; }                 \
  }                                                                                     \
  if (hosts.size()) Trace::TraceGui( "sorted (" + String(hosts.size()) + "/" +          \
                                       String(serversStore.getNumChildren())   +        \
                                       ") login buttons for jams at hosts: "   +        \
                                       hosts.joinIntoString(",")               )        ;


/* network */

#  define DEBUG_TRACE_SERVERLIST                                                               \
  uint8       n_servers     = servers_data.size() ;                                            \
  uint8       n_lobby_hosts = 0 ;                                                              \
  StringArray serverdata ;                                                                     \
  for (server_n = 0 ; server_n < servers_data.size() ; ++server_n)                             \
  {                                                                                            \
    serverdata    = StringArray::fromTokens(servers_data[server_n] , true) ;                   \
    host          = serverdata[0].removeCharacters("\"") ;                                     \
    n_lobby_hosts = n_lobby_hosts + (NETWORK::IsLobbyHost(host) ? 1 : 0) ;                     \
  }                                                                                            \
  if (! servers_data.isEmpty())                                                                \
    Trace::TraceNetwork("updated (" + String(n_servers - n_lobby_hosts) + ") jam servers " +   \
                        "("         + String(            n_lobby_hosts) + ") lobby servers") ; \
  else Trace::TraceError("PollJamsUrl failed to update servers") ;

#  define DEBUG_TRACE_SERVERLIST_SERVER                                                      \
  String err_msg       = "parsing serverlist: " + NETWORK::POLL_JAMS_URL.toString(false) ;   \
  String n_logins      = String(logins.size()) ;                                             \
  bool   is_lobby_host = NETWORK::IsLobbyHost(host) ;                                        \
  if      (host.isEmpty()) Trace::TraceError("invalid host - " + err_msg) ;                  \
  else if (is_known_host ) Trace::TraceNetworkVb("("  + n_logins + ") jammers at: " + host + \
                                                 " (" + logins_csv + ")"                 ) ; \
  else if (!is_lobby_host) Trace::TraceError("invalid or unknown server: '" + host + "' " +  \
                                             err_msg + " - add it to NETWORK::KNOWN_HOSTS")  ;

#  define DEBUG_TRACE_SERVERLIST_CLIENT                                        \
  Trace::TraceNetworkVb("\tjammer: " + login + (is_bot ? " (known bot)" : "")) ;

#if TRACE_LOGIN_HOST
#  define DEBUG_TRACE_LOGIN_HOST_VB                                              \
  if (is_valid_host) Trace::TraceGuiVb("validated host '"        + host + "'") ; \
  else               Trace::TraceGuiVb("error validating host '" + host + "'"  + \
    "\n  parsed server '"   + server + "'"                                     + \
    "\n  parsed name   '"   + name   + "'"                                     + \
    "\n  parsed tld    '"   + tld    + "'"                                     + \
    "\n  parsed port   '"   + port   + "'"                                     + \
    "\n  is_localhost   = " + Bool2Str(is_localhost)                           + \
    "\n  is_known_host  = " + Bool2Str(is_known_host)                          + \
    "\n  is_custom_host = " + Bool2Str(is_custom_host)                         + \
    "\n  has_valid_form = " + Bool2Str(has_valid_form)                         + \
    "\n  is_valid_name  = " + Bool2Str(is_valid_name)                          + \
    "\n  is_valid_tld   = " + Bool2Str(is_valid_tld)                           + \
    "\n  is_valid_port  = " + Bool2Str(is_valid_port)                          ) ;
#else // TRACE_LOGIN_HOST
#  define DEBUG_TRACE_LOGIN_HOST_VB ;
#endif // TRACE_LOGIN_HOST

#else // DEBUG

// state
#  define DEBUG_TRACE_LOGIN_LOAD            ;
#  define DEBUG_TRACE_LOBBY_QUICKLOGIN      ;
#  define DEBUG_TRACE_LOGIN_VALIDATION      ;
#  define DEBUG_TRACE_LOGIN_LAYOUTLOGINBTNS ;
// network
#  define DEBUG_TRACE_SERVERLIST        ;
#  define DEBUG_TRACE_SERVERLIST_SERVER ;
#  define DEBUG_TRACE_SERVERLIST_CLIENT ;
#  define DEBUG_TRACE_LOGIN_HOST_VB     ;

#endif // DEBUG
