#if  DEBUG

#  include "Trace.h"


/* state */

#define DEBUG_TRACE_LICENSE_CLICKED                                         \
  Button* btn = buttonThatWasClicked ;                                      \
  if      (btn == cancelButton) Trace::TraceEvent("cancelButton clicked") ; \
  else if (btn == agreeButton)  Trace::TraceEvent("agreeButton clicked") ;  \
  else if (btn == alwaysButton) Trace::TraceEvent("alwaysButton clicked") ;

#else // DEBUG

// state
#define DEBUG_TRACE_LICENSE_CLICKED ;

#endif // DEBUG
