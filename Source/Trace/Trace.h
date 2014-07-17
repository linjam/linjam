
#ifndef _TRACE_H_
#define _TRACE_H_


// standard features
#define UPDATE_GUI
#define UPDATE_REMOTES
#define BUGGY_CHAT_COMMANDS                    // (issue #19)
#define KLUDGE_SET_INITIAL_REMOTE_GAIN_TO_ZERO // NJClient initializes remote channels gain to 1.0
//#define FADE_HIDDEN_REMOTES
//#define FAUX_STEREO_REMOTES_NYI

#if DEBUG
// debug features
//#define DEBUG_EXIT_IMMEDIAYELY
#define DEBUG_LOCALHOST_LOGIN_BUTTON
#define DEBUG_AUTOLOGIN
#endif // DEBUG

// tracing
#define DEBUG_TRACE                      DEBUG && 1
#define DEBUG_TRACE_EVENTS               DEBUG && 1
#define DEBUG_TRACE_STATE                DEBUG && 1
#define DEBUG_TRACE_IN                   DEBUG && 1
#define DEBUG_TRACE_OUT                  DEBUG && 1
#define DEBUG_TRACE_VB                   DEBUG && 1
#define TRACE_SANITIZE_CONFIG            DEBUG_TRACE_VB && 0
#define TRACE_CONFIG_TYPES               DEBUG_TRACE_VB && 0
#define TRACE_SHARED_CONFIG              DEBUG_TRACE_VB && 0
#define TRACE_STORE_CONFIG_VB            DEBUG_TRACE_VB && 0
#define TRACE_LOGIN_HOST                 DEBUG_TRACE_VB && 0
#define TRACE_DUMP_FREE_INPUTS           DEBUG_TRACE_VB && 1
#define TRACE_DUMP_CHANNELS_GUI          DEBUG_TRACE_VB && 1
#define TRACE_CONFIGURE_LOCAL_CHANNEL_VB DEBUG_TRACE_VB && 1
#define TRACE_ADD_CHANNEL_GUI_VB         DEBUG_TRACE_VB && 0
#define TRACE_REMOTES                    DEBUG_TRACE_VB && 0
#define TRACE_ADD_REMOTES_VB             DEBUG_TRACE_VB && 0
#define TRACE_MIXER_COMPONENTS           DEBUG_TRACE_VB && 0
#define TRACE_VU_GUI                     DEBUG_TRACE_VB && 1


class Trace
{
public:

#if DEBUG_TRACE
  static Array<String> UnknowwnChannels ;


  static void TraceEvent(  String msg) ;
  static void TraceConfig( String msg) ;
  static void TraceClient( String msg) ;
  static void TraceGui(    String msg) ;
  static void TraceVerbose(String msg) ;
  static void TraceState(  String msg) ;
  static void TraceNetwork(String msg) ;
  static void TraceError(  String msg) ;
  static void TraceServer( String msg) ;

  static void   DumpStoreXml(ValueTree store) ;
  static String DumpStoredChannels() ;
  static String DumpClientChannels() ;

  static String SanitizeConfig(      ValueTree default_config , ValueTree stored_config ,
                                     String pad) ;
  static void   TraceInvalidNode(    String a_node_key) ;
  static void   TraceMissingValue(   String a_node_key , String a_value_key) ;
  static void   TraceMissingProperty(String a_node_key , String a_property_key) ;
  static void   TraceTypeMismatch(   String a_node_key    , String a_property_key ,
                                     String expected_type , var    a_var          ) ;
  static String VarType(             var a_var) ;
  static String DumpVar(             String val_name , var a_var) ;



private:

  static bool SanityCheck() ;

  static bool TraceEvs() ;
  static bool TraceVb() ;
  static bool TraceState() ;

#endif // DEBUG_TRACE
} ;

#endif // _TRACE_H_
