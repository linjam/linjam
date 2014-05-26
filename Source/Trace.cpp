
#include "Trace.h"


#if DEBUG_TRACE

/* private class methods */

bool SanityCheck() { return true ; }

bool Trace::TraceEvs() { return (DEBUG_TRACE_EVS || !SanityCheck()) ; }

bool Trace::TraceVb()  { return (DEBUG_TRACE_VB  || !SanityCheck()) ; }

bool Trace::TraceIn()  { return (DEBUG_TRACE_IN  || !SanityCheck()) ; }

bool Trace::TraceOut() { return (DEBUG_TRACE_OUT || !SanityCheck()) ; }


/* public class methods */

void Trace::TraceEvent(String msg)
{ if (TraceEvs())       DBG(String("[EVENT]: "    + msg)) ; }

void Trace::TraceEventVerbose(String msg)
{ if (Trace::TraceVb()) DBG(String("[EVENT_VB]: " + msg)) ; }

#endif // #if DEBUG_TRACE
