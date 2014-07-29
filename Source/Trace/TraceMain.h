#if DEBUG

#  include "Trace.h"


/* state */

#  define DEBUG_TRACE_SHUTDOWN Trace::TraceState("clean shutdown - bye") ;

#else // DEBUG

#  define DEBUG_TRACE_SHUTDOWN ;

#endif // DEBUG
