/*\
|*|  Trace.h
|*|  this file manages logging and defines feature switches for debugging
|*|
|*|  Copyright 2014,2015,2020,2026 bill-auger <bill-auger@programmer.net>
|*|
|*|  This file is part of the LinJam program.
|*|
|*|  LinJam is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  LinJam is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU General Public License for more details.
|*|
|*|  You should have received a copy of the GNU General Public License
|*|  along with LinJam.  If not, see <http://www.gnu.org/licenses/>.
\*/


#pragma once


#if DEBUG

/* disable standard features */

// #define NO_UPDATE_REMOTES
// #define NO_UPDATE_LOOP_PROGRESS_GUI
// #define NO_UPDATE_VU_METERS_GUI
// #define NO_UPDATE_JAMS
// #define NO_UPDATE_RECORDING_TIME_GUI
// #define NO_CHAT_TIMESTAMPS


/* enable buggy features */

// #define ACCEPT_CHAT_COMMANDS         // (issue #19)
// #define FADE_HIDDEN_REMOTES


/* enable debug features */

#define DEBUG_ANSI_COLORS
// #define DEBUG_EXIT_IMMEDIATELY
// #define DEBUG_AUTOJOIN_HOST if (cli_args.isEmpty()) AutoJoinHost = NETWORK::DEVEL_HOST_URL ;


/* logging */

#define DEBUG_TRACE              (DEBUG               &&                    1 )
#define DEBUG_TRACE_VB           (DEBUG_TRACE         &&                    0 )
#define DEBUG_TRACE_EVENTS       (DEBUG_TRACE         &&                    1 )
#define DEBUG_TRACE_STATE        (DEBUG_TRACE         &&                    1 )
#define DEBUG_TRACE_NETWORK      (DEBUG_TRACE         &&                    1 )
#define DEBUG_TRACE_NETWORK_VB   (DEBUG_TRACE_NETWORK && (DEBUG_TRACE_VB || 0))
#define DEBUG_TRACE_CONFIG       (DEBUG_TRACE_STATE                           )
#define DEBUG_TRACE_CONFIG_VB    (DEBUG_TRACE_CONFIG  && (DEBUG_TRACE_VB || 0))
#define DEBUG_TRACE_CLIENT       (DEBUG_TRACE_STATE                           )
#define DEBUG_TRACE_SERVER       (DEBUG_TRACE_STATE                           )
#define DEBUG_TRACE_GUI          (DEBUG_TRACE_EVENTS                          )
#define DEBUG_TRACE_GUI_VB       (DEBUG_TRACE_GUI     && (DEBUG_TRACE_VB || 0))
#define TRACE_DUMP_CONFIG        (DEBUG_TRACE_VB      &&                    0 ) // full compare default<->stored
#define TRACE_CONFIG_TYPES       (DEBUG_TRACE_VB      &&                    0 ) // per property datatype info
#define TRACE_STORE_CONFIG_VB    (DEBUG_TRACE_VB      &&                    0 ) // dump output XML
#define TRACE_AUDIO_INIT_VB      (DEBUG_TRACE_VB      &&                    0 ) // full audio initialization params
#define TRACE_LOGIN_HOST         (DEBUG_TRACE_VB      &&                    0 ) // credentials
#define TRACE_LOCAL_CHANNELS_VB  (DEBUG_TRACE_VB      &&                    0 ) // full dump params for all channels
#define TRACE_REMOTE_CHANNELS_VB (DEBUG_TRACE_VB      &&                    0 ) // full dump params for all channels
#define TRACE_ADD_CHANNEL_GUI_VB (DEBUG_TRACE_VB      &&                    0 )
#define TRACE_DUMP_FREE_INPUTS   (DEBUG_TRACE_VB      &&                    0 ) // dump input device free list
#define TRACE_DUMP_CHANNELS_GUI  (DEBUG_TRACE_VB      &&                    0 )
#define TRACE_DUMP_BLACKLIST     (DEBUG_TRACE_VB      &&                    0 ) // dump blacklist
#define TRACE_MIXER_COMPONENTS   (DEBUG_TRACE_VB      &&                    0 )


class Trace
{
public:

  static int DbgPrevStatus ;


  static void TraceEvent    (String msg) ;
  static void TraceConfig   (String msg) ;
  static void TraceConfigVb (String msg) ;
  static void TraceClient   (String msg) ;
  static void TraceGui      (String msg) ;
  static void TraceGuiVb    (String msg) ;
  static void TraceState    (String msg) ;
  static void TraceNetwork  (String msg) ;
  static void TraceNetworkVb(String msg) ;
  static void TraceError    (String msg) ;
  static void TraceServer   (String msg) ;

  static void   DumpStoreXml      (ValueTree store) ;
  static void   TraceKVP          (String indent , String a_key , String a_value) ;
  static String DumpStoredChannels() ;
  static String DumpClientChannels() ;

  static String DumpConfig          (ValueTree default_config , ValueTree stored_config ,
                                     String    pad                                      ) ;
  static void   TraceInvalidDefault (String a_default_name) ;
  static void   TraceInvalidNode    (String a_node_key) ;
  static void   TraceMissingValue   (String a_node_name , String a_value_key) ;
  static void   TraceMissingProperty(String a_node_name      , String a_property_name ,
                                     String parent_node_name = String()               ) ;
  static void   TraceTypeMismatch   (ValueTree a_node           , String a_property_name ,
                                     String    expected_type    , var    a_var           ,
                                     String    parent_node_name = String()               ) ;
  static void   TraceInvalidValue   (ValueTree a_node , Identifier a_property_id) ;

  static String VarType(var a_var) ;
  static String DumpVar(String val_name , var a_var) ;

  static String Status2String(int status) ;
} ;

#endif // DEBUG
