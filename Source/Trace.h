
#ifndef TRACE_H_INCLUDED
#define TRACE_H_INCLUDED

#define DEBUG_TRACE     1
#define DEBUG_TRACE_EVS 1
#define DEBUG_TRACE_IN  1
#define DEBUG_TRACE_OUT 1
#define DEBUG_TRACE_VB  1


#include "JuceHeader.h"


#if DEBUG_TRACE

#define DEBUG_TRACE_MAIN_RESIZED       Trace::TraceEventVerbose("statusW=" + String(statusW) + " statusH=" + String(statusH) + " statusL=" + String(statusL) + " statusT=" + String(statusT)) ;
#define DEBUG_TRACE_LOGIN_LOGINCLICKED Trace::TraceEvent("loginButton clicked") ;
#define DEBUG_TRACE_LOGIN_ANONCLICKED  Trace::TraceEvent("anonButton clicked") ;

#else // #if DEBUG_TRACE

#define DEBUG_TRACE_MAIN_RESIZED       ;
#define DEBUG_TRACE_LOGIN_LOGINCLICKED ;
#define DEBUG_TRACE_LOGIN_ANONCLICKED  ;

#endif // #if DEBUG_TRACE

class Trace
{
private:

  static bool SanityCheck() ;
  static bool TraceEvs(   ) ;
  static bool TraceIn(    ) ;
  static bool TraceOut(   ) ;
  static bool TraceVb(    ) ;

public:

  static void TraceEvent(       String msg) ;
  static void TraceEventVerbose(String msg) ;
} ;

#endif // TRACE_H_INCLUDED
