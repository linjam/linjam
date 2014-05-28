
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
#define DEBUG_TRACE_LOGIN              Trace::TraceEvent("joining '" + Server + "' as '" + login +"'(" + Login + "):'" + Pass + "'") ;
#define DEBUG_TRACE_CONNECT_STATUS     \
    switch (this->GetStatus())         \
    {                                  \
      case -3 : Trace::TraceStatus("NJC_STATUS_DISCONNECTED") ; break ; \
      case -2 : Trace::TraceStatus("NJC_STATUS_INVALIDAUTH") ;  break ; \
      case -1 : Trace::TraceStatus("NJC_STATUS_CANTCONNECT") ;  break ; \
      case  0 : Trace::TraceStatus("NJC_STATUS_OK") ;           break ; \
      case  1 : Trace::TraceStatus("NJC_STATUS_PRECONNECT") ;   break ; \
      default:  break ;                \
    }                                  \
    //if (this->GetErrorStr()[0]) Trace::TraceError(this->GetErrorStr()) ; // TODO: segfault - we probably dont need this anyway

#else // #if DEBUG_TRACE

#define DEBUG_TRACE_MAIN_RESIZED       ;
#define DEBUG_TRACE_LOGIN_LOGINCLICKED ;
#define DEBUG_TRACE_LOGIN_ANONCLICKED  ;
#define DEBUG_TRACE_LOGIN              ;
#define DEBUG_TRACE_CONNECT_STATUS     ;

#endif // #if DEBUG_TRACE

class Trace
{
private:

  static bool SanityCheck() ;
  static bool TraceEvs() ;
  static bool TraceIn() ;
  static bool TraceOut() ;
  static bool TraceVb() ;

public:

  static void TraceEvent(       String msg) ;
  static void TraceEventVerbose(String msg) ;
  static void TraceStatus(      String msg) ;
  static void TraceError(       String msg) ;
} ;

#endif // TRACE_H_INCLUDED
