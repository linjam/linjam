
#ifndef _TRACE_H_
#define _TRACE_H_

#if DEBUG

// disable standard features
//#define NO_UPDATE_LOOP_PROGRESS_GUI
//#define NO_UPDATE_VU_METERS_GUI
//#define NO_UPDATE_RECORDING_TIME_GUI
//#define NO_UPDATE_REMOTES
// enable buggy features
//#define ACCEPT_CHAT_COMMANDS         // (issue #19)
//#define FADE_HIDDEN_REMOTES

// enable debug features
#define DEBUG_ANSI_COLORS


// tracing
#define DEBUG_TRACE              DEBUG && 1
#define DEBUG_TRACE_EVENTS       DEBUG && 1
#define DEBUG_TRACE_STATE        DEBUG && 1
#define DEBUG_TRACE_VB           DEBUG && 1
#define TRACE_DUMP_CONFIG        DEBUG_TRACE_VB && 0
#define TRACE_CONFIG_TYPES       DEBUG_TRACE_VB && 0
#define TRACE_STORE_CONFIG_VB    DEBUG_TRACE_VB && 0
#define TRACE_AUDIO_INIT_VB      DEBUG_TRACE_VB && 1
#define TRACE_LOGIN_HOST         DEBUG_TRACE_VB && 0
#define TRACE_LOCAL_CHANNELS_VB  DEBUG_TRACE_VB && 0
#define TRACE_REMOTE_CHANNELS_VB DEBUG_TRACE_VB && 0
#define TRACE_ADD_CHANNEL_GUI_VB DEBUG_TRACE_VB && 0
#define TRACE_DUMP_FREE_INPUTS   DEBUG_TRACE_VB && 0
#define TRACE_DUMP_CHANNELS_GUI  DEBUG_TRACE_VB && 0
#define TRACE_DUMP_SUBSCRIPTIONS DEBUG_TRACE_VB && 0
#define TRACE_MIXER_COMPONENTS   DEBUG_TRACE_VB && 0


class Trace
{
public:

  static Array<String> UnknowwnChannels ;


  static void TraceEvent(  String msg) ;
  static void TraceConfig( String msg) ;
  static void TraceClient( String msg) ;
  static void TraceGui(    String msg) ;
  static void TraceVerbose(String msg) ;
  static void TraceState(  String msg) ;
//   static void TraceNetwork(String msg) ;
  static void TraceError(  String msg) ;
  static void TraceServer( String msg) ;

  static void   DumpStoreXml(      ValueTree store) ;
  static String DumpStoredChannels() ;
  static String DumpClientChannels() ;

  static String DumpConfig(          ValueTree default_config , ValueTree stored_config ,
                                     String    pad                                      ) ;
  static void   TraceInvalidDefault( String a_default_name) ;
  static void   TraceInvalidNode(    String a_node_key) ;
  static void   TraceMissingValue(   String a_node_name , String a_value_key) ;
  static void   TraceMissingProperty(String a_node_name      , String a_property_name ,
                                     String parent_node_name = String::empty          ) ;
  static void   TraceTypeMismatch(   ValueTree a_node           , String a_property_name ,
                                     String    expected_type    , var    a_var           ,
                                     String    parent_node_name = String::empty          ) ;

  static String VarType(var a_var) ;
  static String DumpVar(String val_name , var a_var) ;

  static String Status2String(int status) ;
} ;

#endif // DEBUG
#endif // _TRACE_H_
