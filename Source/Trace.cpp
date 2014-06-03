
//#include <ninjam/njclient.h>
#include "LinJam.h"
#include "Trace.h"



#if DEBUG_TRACE

/* public class methods */

void Trace::TraceEvent(String msg)        { if (TraceEvs())    Dbg("EVENT"      , msg) ; }
void Trace::TraceEventVerbose(String msg) { if (TraceVb())     Dbg("EVENT"      , msg) ; }
void Trace::TraceState(String msg)        { if (TraceState())  Dbg("STATE"      , msg) ; }
void Trace::TraceConnection(String msg)   { if (TraceState())  Dbg("CONNECTION" , msg) ; }
void Trace::TraceError(String msg)        { if (TraceState())  Dbg("ERROR"      , msg) ; }
void Trace::TraceServer(String msg)       { if (TraceState())  Dbg("SERVER"     , msg) ; }


/* private class methods */

bool Trace::SanityCheck() { return true ; }

bool Trace::TraceEvs()   { return (DEBUG_TRACE_EVENTS || !SanityCheck()) ; }
bool Trace::TraceVb()    { return (DEBUG_TRACE_VB     || !SanityCheck()) ; }
bool Trace::TraceState() { return (DEBUG_TRACE_STATE  || !SanityCheck()) ; }

void Trace::Dbg(String type , String msg) { DBG(String("[" + type + "]: " + msg)) ; }

#endif // #if DEBUG_TRACE
