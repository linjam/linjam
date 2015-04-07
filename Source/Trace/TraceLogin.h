#if DEBUG

#include "Trace.h"


/* state */

#define DEBUG_TRACE_LOGIN_LOAD                                                             \
  Trace::TraceState("lobby - " + ((host.isEmpty()) ? "no previous logins" :                \
                                                     "restoring credentials for " + host)) ;

#define DEBUG_TRACE_LOBBY_QUICKLOGIN                                                     \
  String status = String((credentials.isValid()) ? "" : "not ") ;                        \
  Trace::TraceEvent("quick-login - storage " + status + "found for host '" + host + "'") ;

#define DEBUG_TRACE_LOGIN_VALIDATION                                                           \
  if (!validateHost() || !validateLogin() || !validatePass())                                  \
    Trace::TraceError(String("error validating credentials:")                                + \
                      " host("  + String((validateHost() ) ? "ok)" : "nfg)='" + host  + "'") + \
                      " login(" + String((validateLogin()) ? "ok)" : "nfg)='" + login + "'") + \
                      " pass("  + String((validatePass() ) ? "ok)" : "nfg)"                ) ) ;


/* network */

#if TRACE_LOGIN_HOST
#  define DEBUG_TRACE_LOGIN_HOST_VB                                                \
  if (is_valid_host) Trace::TraceVerbose("validated host '"        + host + "'") ; \
  else               Trace::TraceVerbose("error validating host '" + host + "'"  + \
    "\n  parsed server '"   + server + "'"                                       + \
    "\n  parsed name   '"   + name   + "'"                                       + \
    "\n  parsed tld    '"   + tld    + "'"                                       + \
    "\n  parsed port   '"   + port   + "'"                                       + \
    "\n  is_localhost   = " + String(is_localhost)                               + \
    "\n  is_known_host  = " + String(is_known_host)                              + \
    "\n  is_custom_host = " + String(is_custom_host)                             + \
    "\n  has_valid_form = " + String(has_valid_form)                             + \
    "\n  is_valid_name  = " + String(is_valid_name)                              + \
    "\n  is_valid_tld   = " + String(is_valid_tld)                               + \
    "\n  is_valid_port  = " + String(is_valid_port)                              ) ;
#else // TRACE_LOGIN_HOST
#  define DEBUG_TRACE_LOGIN_HOST_VB ;
#endif // TRACE_LOGIN_HOST

#else // DEBUG

// state
#define DEBUG_TRACE_LOGIN_LOAD       ;
#define DEBUG_TRACE_LOBBY_QUICKLOGIN ;
#define DEBUG_TRACE_LOGIN_VALIDATION ;
// network
#define DEBUG_TRACE_LOGIN_HOST_VB    ;

#endif // DEBUG
