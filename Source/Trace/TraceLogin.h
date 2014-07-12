#include "Trace.h"


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

#define DEBUG_TRACE_LOGIN_HOST_VB                                                     \
  String h  = this->hostText->getText().trim() ; String dbg ;                         \
  String hn = h.upToLastOccurrenceOf( StringRef(".") , false , true) ;                \
  String ht = h.fromLastOccurrenceOf( StringRef(".") , false , true)                  \
               .upToFirstOccurrenceOf(StringRef(":") , false , true) ;                \
  String hp = h.fromFirstOccurrenceOf(StringRef(":") , false , true) ;                \
  bool valid = (NETWORK::KNOWN_HOSTS.contains(h)                                ||    \
               (h                   .matchesWildcard(NETWORK::HOST_MASK , true) &&    \
                hn                  .containsOnly(   NETWORK::URL_CHARS)        &&    \
                ht                  .containsOnly(   NETWORK::LETTERS)          &&    \
                hp                  .containsOnly(   NETWORK::DIGITS)           )) ;  \
  if (valid) Trace::TraceVerbose("validated host '"        + h + "'") ;               \
  else       Trace::TraceVerbose("error validating host '" + h + "'" +                \
    "\n  parsed host="      + h  +                                                    \
    "\n  parsed host_tld="  + ht +                                                    \
    "\n  parsed host_port=" + hp +                                                    \
    "\n  is_known_host="    + String(NETWORK::KNOWN_HOSTS.contains(h))              + \
    "\n  is_valid_host="    + String(h .matchesWildcard(NETWORK::HOST_MASK , true)) + \
    "\n  is_valid_url="     + String(hn.containsOnly(   NETWORK::URL_CHARS) &&        \
                                     hn.isNotEmpty())                               + \
    "\n  is_valid_tld="     + String(ht.containsOnly(   NETWORK::LETTERS)   &&        \
                                     ht.isNotEmpty())                               + \
    "\n  is_valid_port="    + String(hp.containsOnly(   NETWORK::DIGITS)    &&        \
                                     hp.isNotEmpty())                               ) ;

