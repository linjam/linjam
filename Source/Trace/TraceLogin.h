#if DEBUG

#  include "Trace.h"


/* state */

#define DEBUG_TRACE_LOGIN_LOAD                                                     \
  Trace::TraceState("Lobby - storage " + String((server.isValid())? "" : "not ") + \
                    "found for currentHost => '" + host + "'") ;

#define DEBUG_TRACE_LOGIN_BTNS                                                     \
  Button* btn = buttonThatWasClicked ;                                             \
  if      (btn == loginButton) Trace::TraceEvent("loginButton clicked") ;          \
  else if (btn == anonButton)  Trace::TraceEvent("anonButton clicked") ;           \
  else if (loginButtons.contains((TextButton*)btn))                                \
    Trace::TraceEvent("quick-login button clicked " + btn->getButtonText().trim()) ;


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
#define DEBUG_TRACE_LOGIN_LOAD    ;
#define DEBUG_TRACE_LOGIN_BTNS    ;
// network
#define DEBUG_TRACE_LOGIN_HOST_VB ;

#endif // DEBUG
