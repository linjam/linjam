
#ifndef TRACE_H_INCLUDED
#define TRACE_H_INCLUDED

#define DEBUG_TRACE        DEBUG && 1
#define DEBUG_TRACE_EVENTS DEBUG && 1
#define DEBUG_TRACE_STATE  DEBUG && 1
#define DEBUG_TRACE_IN     DEBUG && 1
#define DEBUG_TRACE_OUT    DEBUG && 1
#define DEBUG_TRACE_VB     DEBUG && 1

#define EXIT_IMMEDIAYELY    1
#define DEBUG_STATIC_SERVER 1 // DEBUG_SERVER defined in LinJam.cpp

#define CHAT_COMMANDS_BUGGY

#include "JuceHeader.h"


#if DEBUG_TRACE

#  define DEBUG_TRACE_LINJAM_INIT        Trace::TraceEvent("initializing") ;
#  define DEBUG_TRACE_JACK_INIT  if (!Audio) Trace::TraceError("error connecting to JACK - falling back to ALSA") ;
#  define DEBUG_TRACE_AUDIO_INIT if (!Audio) Trace::TraceError("error opening audio device") ; \
                                 else        Trace::TraceState("opened audio device at " +     \
                                                 String(Audio->m_srate)    + "Hz "       +     \
                                                 String(Audio->m_bps)      + "bps "      +     \
                                                 String(Audio->m_innch)    + "in -> "    +     \
                                                 String(Audio->m_outnch)   + "out "            ) ;

#  define DEBUG_TRACE_LOAD_CONFIG                                                       \
    Identifier root_node_id = STORAGE::PERSISTENCE_IDENTIFIER ;                         \
    if (default_config_xml == nullptr || !default_config_xml->hasTagName(root_node_id)) \
        Trace::TraceConfig("default config invalid") ;                                  \
    else Trace::TraceConfig("default config loaded") ;                                  \
    if (stored_config_xml == nullptr)                                                   \
        Trace::TraceConfig("stored config not found - falling back on defaults") ;      \
    else if (!stored_config_xml->hasTagName(STORAGE::PERSISTENCE_IDENTIFIER))           \
        Trace::TraceConfig("stored config is invalid - falling back on defaults") ;     \
    else Trace::TraceConfig("stored config found") ;
#define DEBUG_TRACE_SANITIZE_CONFIG                                                    \
    Trace::TraceConfig("stored config parsed successfully =>" +                        \
                       Trace::SanitizeConfig(ValueTree::fromXml(*default_config_xml) , \
                                             ValueTree::fromXml(*stored_config_xml) , "  ")) ;
#  define DEBUG_TRACE_STORE_CONFIG       Trace::TraceConfig("storing config xml=\n" + LinjamValueTree.toXmlString()) ;
#  define DEBUG_TRACE_CONFIG_VALUE                                                         \
    bool valid = a_node.isValid() ; String n = String(node_id) ; String k = String(key) ;  \
    Trace::TraceConfig("node '" + n + ((valid)? "' is" : "' not") + " valid - " +          \
        ((valid && a_node.hasProperty(key))? "has key '"     + k + "' - is shared value" : \
                                             "missing key '" + k + "' - has dummy value")) ;

#  define DEBUG_TRACE_LOGIN_CLICKED                                                          \
    if      (buttonThatWasClicked == loginButton) Trace::TraceEvent("loginButton clicked") ; \
    else if (buttonThatWasClicked == anonButton)  Trace::TraceEvent("anonButton clicked") ;
#  define DEBUG_TRACE_CONNECT if (!IsAgreed)                                                   \
                                   Trace::TraceState("connecting") ;                           \
                              else Trace::TraceState("joining '" + Server + "' as '" + login + \
                                     "'(" + ((Login == "")? "nil" : Login) + "):'" + Pass + "'") ;

#  define DEBUG_TRACE_LICENSE_CLICKED                                                          \
    if      (buttonThatWasClicked == cancelButton) Trace::TraceEvent("cancelButton clicked") ; \
    else if (buttonThatWasClicked == agreeButton)  Trace::TraceEvent("agreeButton clicked") ;  \
    else if (buttonThatWasClicked == alwaysButton) Trace::TraceEvent("alwaysButton clicked") ;
#  define DEBUG_TRACE_LICENSE if (IsAgreed)                                               \
                                   Trace::TraceState("agreeing to license") ;             \
                              else Trace::TraceState("prompting for license agreement") ;

#  define DEBUG_TRACE_CONNECT_STATUS                                              \
    switch (status)                                                               \
    {                                                                             \
      case -3: Trace::TraceConnection("NJC_STATUS_DISCONNECTED") ; break ;        \
      case -2: Trace::TraceConnection((LinJam::IsAgreed)?                         \
                   "NJC_STATUS_INVALIDAUTH" : "LICENSE_PENDING") ; break ;        \
      case -1: Trace::TraceConnection("NJC_STATUS_CANTCONNECT") ;  break ;        \
      case  0: Trace::TraceConnection("NJC_STATUS_OK") ;           break ;        \
      case  1: Trace::TraceConnection("NJC_STATUS_PRECONNECT") ;   break ;        \
      default:                                                     break ;        \
    }                                                                             \
    Trace::TraceServer("connected to host: " + String(GetHostName())) ;           \
    if (this->GetErrorStr()[0])                                                   \
      Trace::TraceServer("Error: " + String(this->GetErrorStr())) ;

#  define DEBUG_CHANNELS                 Trace::TraceServer("handleUserInfoChanged()") ;
#  define DEBUG_CHANNELS_VB                                                         \
    /* master channel */                                                            \
    this->chatComponent->addChatLine("" , "") ;                                     \
    this->chatComponent->addChatLine("master channel:\n" ,                          \
        String("mastervol=")   + String(this->config_mastervolume)  +               \
        String(" masterpan=")  + String(this->config_masterpan)     +               \
        String(" mastermute=") + String(this->config_mastermute)    +               \
        String(" metrovol=")   + String(this->config_metronome)     +               \
        String(" metropan=")   + String(this->config_metronome_pan) +               \
        String(" metromute=")  + String(this->config_metronome_mute)) ;             \
    this->chatComponent->addChatLine("" , "") ;                                     \
                                                                                    \
    /* local channels */                                                            \
    int ch_n = -1 ; int ch_idx ;                                                    \
    while ((ch_idx = EnumLocalChannels(++ch_n)) >= 0)                               \
    {                                                                               \
      int source_n = 0 ; bool xmit = 0 ; void* fx = 0 ;                             \
      float vol = 0.0f , pan = 0.0f ; bool mute = 0 , solo = 0 ;                    \
      char* name = GetLocalChannelInfo(ch_idx , &source_n , NULL , &xmit) ;         \
      GetLocalChannelMonitoring(ch_idx , &vol , &pan , &mute , &solo) ;             \
      GetLocalChannelProcessor(ch_idx , NULL , &fx) ;                               \
      this->chatComponent->addChatLine(                                             \
          String("local channel ")   + String(ch_n)     +                           \
              String(" (")   + String(ch_idx)   + String("):\n") ,                  \
          String("name=")    + String(name)     +                                   \
          String(" source=") + String(source_n) +                                   \
          String(" xmit=")   + String(xmit)     +                                   \
          String(" mute=")   + String(mute)     +                                   \
          String(" solo=")   + String(solo)     +                                   \
          String(" volume=") + String(vol)      +                                   \
          String(" pan=")    + String(pan)      +                                   \
          String(" fx=")     + String(!!fx)     ) ;                                 \
    }                                                                               \
                                                                                    \
    /* remote users */                                                              \
    int user_n = -1 ; ch_n = -1 ; int n_users = m_remoteusers.GetSize() ;           \
    while (++user_n < n_users)                                                      \
    {                                                                               \
      float vol = 0.0f , pan = 0.0f ; bool mute = 0 ;                               \
      char* name = GetUserState(user_n , &vol , &pan , &mute) ;                     \
      this->chatComponent->addChatLine("" , "") ;                                   \
      this->chatComponent->addChatLine(                                             \
          String("remote user ") + String(user_n) + String(":\n") ,                 \
          String("name=")        + String(name)   +                                 \
          String(" volume=")     + String(vol)    +                                 \
          String(" pan=")        + String(pan)    +                                 \
          String(" mute=")       + String(mute)                   ) ;               \
                                                                                    \
      /* remote user channels */                                                    \
      ch_n = -1 ;                                                                   \
      while ((ch_idx = EnumUserChannels(user_n , ++ch_n)) >= 0)                     \
      {                                                                             \
        float vol = 0.0f , pan = 0.0f ; bool sub = 0 , mute = 0 , solo = 0 ;        \
        int out_ch = 0 ; bool stereo = 0 ;                                          \
        char* name = GetUserChannelState(user_n , ch_idx  , &sub    ,               \
                                         &vol   , &pan    , &mute   ,               \
                                         &solo  , &out_ch , &stereo ) ;             \
        this->chatComponent->addChatLine(                                           \
            String("    remote channel ") + String(ch_n)     +                      \
                String(" (")              + String(ch_idx)   + String("):\n") ,     \
            String("    name=")           + String(name)     +                      \
            String(" subscribed=")        + String(sub)      +                      \
            String(" volume=")            + String(vol)      +                      \
            String(" pan=")               + String(pan)      +                      \
            String(" mute=")              + String(mute)     +                      \
            String(" solo=")              + String(solo)     +                      \
            String(" out_ch=")            + String(out_ch)   +                      \
            String(" stereo=")            + String(stereo)                    ) ;   \
      }                                                                             \
    }

#  define DEBUG_TRACE_CHAT_IN            if (chat_user.compare(Config->Login)) Trace::TraceEvent("incoming chat: " + String(parms[CLIENT::CHATMSG_TYPE_IDX])) ;
//#  define DEBUG_TRACE_CHATIN String msg = "|" ; for (;nparms--;) msg += String(parms[nparms]) + "|" ; Trace::TraceEvent("LinJam::OnChatmsg()=\n\"" + msg + "\"") ;
//#  define DEBUG_TRACE_CHATIN Trace::TraceEvent("LinJam::OnChatmsg()=\n") ; for (;nparms--;) Trace::TraceEvent("\tnparms[" + String(nparms) + "]='" + String(parms[nparms]) + "'\n") ;

#  define DEBUG_TRACE_CHAT_OUT                                      \
    if ((chat_text = chat_text.trim()).isNotEmpty())                \
      Trace::TraceEvent("outgoing chat: " + ((chat_text[0] == '/')? \
          chat_text.upToFirstOccurrenceOf(" " , false , false) :    \
          CLIENT::CHATMSG_TYPE_MSG)) ;
// DBG("LinJam::SendChat() =" + chat_text) ;

#  define DEBUG_TRACE_SHUTDOWN           Trace::TraceState("clean shutdown - bye") ;

#else // #if DEBUG_TRACE

#  define DEBUG_TRACE_LINJAM_INIT     ;
#  define DEBUG_TRACE_JACK_INIT       ;
#  define DEBUG_TRACE_AUDIO_INIT      ;
#  define DEBUG_TRACE_LOAD_CONFIG     ;
#  define DEBUG_TRACE_PARSE_CONFIG    ;
#  define DEBUG_TRACE_STORE_CONFIG    ;
#  define DEBUG_TRACE_CONFIG_VALUE    ;
#  define DEBUG_TRACE_LOGIN_CLICKED   ;
#  define DEBUG_TRACE_CONNECT         ;
#  define DEBUG_TRACE_LICENSE_CLICKED ;
#  define DEBUG_TRACE_LICENSE         ;
#  define DEBUG_TRACE_CONNECT_STATUS  ;
#  define DEBUG_CHANNELS              ;
#  define DEBUG_CHANNELS_VB           ;
#  define DEBUG_TRACE_CHAT_IN         ;
#  define DEBUG_TRACE_CHAT_OUT        ;
#  define DEBUG_TRACE_SHUTDOWN        ;

#endif // #if DEBUG_TRACE


class Trace
{
public:

  static void TraceConfig(      String msg) ;
  static void TraceEvent(       String msg) ;
  static void TraceEventVerbose(String msg) ;
  static void TraceState(       String msg) ;
  static void TraceConnection(  String msg) ;
  static void TraceError(       String msg) ;
  static void TraceServer(      String msg) ;

  static void Dbg(String type , String msg) ;

  static String SanitizeConfig(ValueTree default_config , ValueTree stored_config ,
                               String pad) ;

private:

  static bool SanityCheck() ;

  static bool TraceEvs() ;
  static bool TraceVb() ;
  static bool TraceState() ;
} ;

#endif // TRACE_H_INCLUDED
