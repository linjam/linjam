
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
#define DEBUG_TRACE              (DEBUG          && 1)
#define DEBUG_TRACE_EVENTS       (DEBUG          && 1)
#define DEBUG_TRACE_STATE        (DEBUG          && 1)
#define DEBUG_TRACE_VB           (DEBUG          && 0)
#define TRACE_DUMP_CONFIG        (DEBUG_TRACE_VB && 0) // full compare default<->stored
#define TRACE_CONFIG_TYPES       (DEBUG_TRACE_VB && 0) // per property datatype info
#define TRACE_STORE_CONFIG_VB    (DEBUG_TRACE_VB && 0) // dump output XML
#define TRACE_AUDIO_INIT_VB      (DEBUG_TRACE_VB && 1) // full audio initialization params
#define TRACE_LOGIN_HOST         (DEBUG_TRACE_VB && 0) // credentials
#define TRACE_LOCAL_CHANNELS_VB  (DEBUG_TRACE_VB && 0) // full dump params for all channels
#define TRACE_REMOTE_CHANNELS_VB (DEBUG_TRACE_VB && 0) // full dump params for all channels
#define TRACE_ADD_CHANNEL_GUI_VB (DEBUG_TRACE_VB && 0)
#define TRACE_DUMP_FREE_INPUTS   (DEBUG_TRACE_VB && 0) // dump input device free list
#define TRACE_DUMP_CHANNELS_GUI  (DEBUG_TRACE_VB && 0)
#define TRACE_DUMP_BLACKLIST     (DEBUG_TRACE_VB && 0) // dump blacklist
#define TRACE_MIXER_COMPONENTS   (DEBUG_TRACE_VB && 0)


class Trace
{
public:

  static int DbgPrevStatus ;


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
  static void   TraceKVP(          String indent , String a_key , String a_value) ;
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
  static void   TraceInvalidValue(   ValueTree a_node , Identifier a_property_id) ;

  static String VarType(var a_var) ;
  static String DumpVar(String val_name , var a_var) ;

  static String Status2String(int status) ;
} ;

#endif // DEBUG
#endif // _TRACE_H_
