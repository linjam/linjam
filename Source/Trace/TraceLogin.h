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

#define DEBUG_TRACE_LOGIN_ARRANGE_ROOMS                                          \
  for (int i = 0 ; i < this->serversStore.getNumChildren() ; ++i)                \
  { ValueTree server    = this->serversStore.getChild(i) ;                       \
    ValueTree clients   = server.getChildWithName(CONFIG::CLIENTS_ID) ;          \
    String    n_clients = String(clients.getNumChildren()) ;                     \
    Trace::TraceGuiVb("button order: server[" + String(i) + "](" + n_clients +   \
                      " clients)="            + String(server.getType())     ) ; }


/* network */

#if TRACE_LOGIN_HOST
#  define DEBUG_TRACE_LOGIN_HOST_VB                                              \
  if (is_valid_host) Trace::TraceGuiVb("validated host '"        + host + "'") ; \
  else               Trace::TraceGuiVb("error validating host '" + host + "'"  + \
    "\n  parsed server '"   + server + "'"                                     + \
    "\n  parsed name   '"   + name   + "'"                                     + \
    "\n  parsed tld    '"   + tld    + "'"                                     + \
    "\n  parsed port   '"   + port   + "'"                                     + \
    "\n  is_localhost   = " + String(is_localhost)                             + \
    "\n  is_known_host  = " + String(is_known_host)                            + \
    "\n  is_custom_host = " + String(is_custom_host)                           + \
    "\n  has_valid_form = " + String(has_valid_form)                           + \
    "\n  is_valid_name  = " + String(is_valid_name)                            + \
    "\n  is_valid_tld   = " + String(is_valid_tld)                             + \
    "\n  is_valid_port  = " + String(is_valid_port)                            ) ;
#else // TRACE_LOGIN_HOST
#  define DEBUG_TRACE_LOGIN_HOST_VB ;
#endif // TRACE_LOGIN_HOST

#else // DEBUG

// state
#define DEBUG_TRACE_LOGIN_LOAD          ;
#define DEBUG_TRACE_LOBBY_QUICKLOGIN    ;
#define DEBUG_TRACE_LOGIN_VALIDATION    ;
#define DEBUG_TRACE_LOGIN_ARRANGE_ROOMS ;
// network
#define DEBUG_TRACE_LOGIN_HOST_VB       ;

#endif // DEBUG
