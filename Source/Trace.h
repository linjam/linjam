
#ifndef TRACE_H_INCLUDED
#define TRACE_H_INCLUDED

#define DEBUG_TRACE        1
#define DEBUG_TRACE_EVENTS 1
#define DEBUG_TRACE_STATE  1
#define DEBUG_TRACE_IN     1
#define DEBUG_TRACE_OUT    1
#define DEBUG_TRACE_VB     1


#include "JuceHeader.h"


#if DEBUG_TRACE

#define DEBUG_TRACE_LINJAM_INIT        Trace::TraceEvent("initializing") ;
#define DEBUG_TRACE_JACK_INIT  if (!Audio) Trace::TraceError("error connecting to JACK - falling back to ALSA") ;
#define DEBUG_TRACE_AUDIO_INIT if (!Audio) Trace::TraceError("error opening audio device") ; \
                               else        Trace::TraceState("opened audio device at " +     \
                                               String(Audio->m_srate)    + "Hz "       +     \
                                               String(Audio->m_bps)      + "bps "      +     \
                                               String(Audio->m_innch)    + "in -> "    +     \
                                               String(Audio->m_outnch)   + "out ") ;

#define DEBUG_TRACE_LOGIN_CLICKED                                                            \
    if      (buttonThatWasClicked == loginButton) Trace::TraceEvent("loginButton clicked") ; \
    else if (buttonThatWasClicked == anonButton)  Trace::TraceEvent("anonButton clicked") ;
#define DEBUG_TRACE_CONNECT if (!IsAgreed)                                                   \
                                 Trace::TraceState("connecting") ;                           \
                            else Trace::TraceState("joining '" + Server + "' as '" + login + \
                                   "'(" + ((Login == "")? "nil" : Login) + "):'" + Pass + "'") ;
#define DEBUG_TRACE_LICENSE_CLICKED                                                            \
    if      (buttonThatWasClicked == cancelButton) Trace::TraceEvent("cancelButton clicked") ; \
    else if (buttonThatWasClicked == agreeButton)  Trace::TraceEvent("agreeButton clicked") ;  \
    else if (buttonThatWasClicked == alwaysButton) Trace::TraceEvent("alwaysButton clicked") ;
#define DEBUG_TRACE_LICENSE if (IsAgreed)                                               \
                                 Trace::TraceState("agreeing to license") ;             \
                            else Trace::TraceState("prompting for license agreement") ;

#define DEBUG_TRACE_CONNECT_STATUS                                         \
    switch (this->GetStatus())                                             \
    {                                                                      \
      case -3: Trace::TraceConnection("NJC_STATUS_DISCONNECTED") ; break ; \
      case -2: Trace::TraceConnection((LinJam::IsAgreed)?                  \
                   "NJC_STATUS_INVALIDAUTH" : "LICENSE_PENDING") ; break ; \
      case -1: Trace::TraceConnection("NJC_STATUS_CANTCONNECT") ;  break ; \
      case  0: Trace::TraceConnection("NJC_STATUS_OK") ;           break ; \
      case  1: Trace::TraceConnection("NJC_STATUS_PRECONNECT") ;   break ; \
      default:                                                     break ; \
    }                                                                      \
    if (status == 0)                                                       \
      Trace::TraceServer("connected to host: " + String(GetHostName())) ;  \
    if (this->GetErrorStr()[0])                                            \
      Trace::TraceServer("Error: " + String(this->GetErrorStr())) ;

#define DEBUG_TRACE_CHAT_IN            Trace::TraceEvent("incoming chat: " + String(parms[CLIENT::CHATMSG_TYPE_IDX])) ;
//#define DEBUG_TRACE_CHATIN String msg = "|" ; for (;nparms--;) msg += String(parms[nparms]) + "|" ; Trace::TraceEvent("LinJam::OnChatmsg()=\n\"" + msg + "\"") ;
//#define DEBUG_TRACE_CHATIN Trace::TraceEvent("LinJam::OnChatmsg()=\n") ; for (;nparms--;) Trace::TraceEvent("\tnparms[" + String(nparms) + "]='" + String(parms[nparms]) + "'\n") ;

#define DEBUG_AUDIO_STATE if (is_topic_msg)                                     \
  {                                                                             \
    String dbg = "master mastervol " + String(Client->config_mastervolume) +    \
                " masterpan " + String(Client->config_masterpan) +              \
                " metrovol " + String(Client->config_metronome) +               \
                " metropan " + String(Client->config_metronome_pan) +           \
                " mastermute " + String(Client->config_mastermute) +            \
                " metromute " + String(Client->config_metronome_mute) ;         \
    Gui->chatComponent->addChatLine("DEBUG" , dbg) ;                            \
                                                                                \
    for (int x = 0;;x++)                                                        \
    {                                                                           \
      int a=Client->EnumLocalChannels(x) ; if (a < 0) break ;                   \
                                                                                \
      int sch = 0 ; bool bc = 0 ; void *has_jesus = 0 ;                         \
      char *lcn ; float v = 0.0f , p = 0.0f ; bool m=0 , s=0 ;                  \
      lcn = Client->GetLocalChannelInfo(a , &sch , NULL , &bc) ;                \
      Client->GetLocalChannelMonitoring(a , &v , &p , &m , &s) ;                \
      Client->GetLocalChannelProcessor(a , NULL , &has_jesus) ;                 \
                                                                                \
      char *ptr = lcn ; while (*ptr) { if (*ptr == '`') *ptr = '\'' ; ptr++ ; } \
      dbg = "local " + String(a) +                                              \
            " source " + String(sch) +                                          \
            " bc " + String(bc) +                                               \
            " mute " + String(m) +                                              \
            " solo " + String(s) +                                              \
            " volume " + String(v) +                                            \
            " pan " + String(p) +                                               \
            " jesus " + String(!!has_jesus) +                                   \
            " name " + String(lcn) ;                                            \
      Gui->chatComponent->addChatLine("DEBUG" , dbg) ;                          \
    }                                                                           \
  }

#define DEBUG_TRACE_MAIN_RESIZED       Trace::TraceEventVerbose("statusW=" + String(statusW) + " statusH=" + String(statusH) + " statusL=" + String(statusL) + " statusT=" + String(statusT)) ;

#else // #if DEBUG_TRACE

#define DEBUG_TRACE_LINJAM_INIT     ;
#define DEBUG_TRACE_JACK_INIT       ;
#define DEBUG_TRACE_AUDIO_INIT      ;
#define DEBUG_TRACE_LOGIN_CLICKED   ;
#define DEBUG_TRACE_CONNECT         ;
#define DEBUG_TRACE_LICENSE_CLICKED ;
#define DEBUG_TRACE_LICENSE         ;
#define DEBUG_TRACE_CONNECT_STATUS  ;
#define DEBUG_TRACE_CHAT_IN         ;
#define DEBUG_TRACE_MAIN_RESIZED    ;

#endif // #if DEBUG_TRACE


class Trace
{
public:

  static void Dbg(String type , String msg) ;

  static void TraceEvent(       String msg) ;
  static void TraceEventVerbose(String msg) ;
  static void TraceState(       String msg) ;
  static void TraceConnection(  String msg) ;
  static void TraceError(       String msg) ;
  static void TraceServer(      String msg) ;

private:

  static bool SanityCheck() ;

  static bool TraceEvs() ;
  static bool TraceVb() ;
  static bool TraceState() ;
} ;

#endif // TRACE_H_INCLUDED
