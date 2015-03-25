#if DEBUG

#  include "../Constants.h"
#  include "../LinJam.h"
#  include "Trace.h"


/* Trace class private class variables */

Array<String> Trace::UnknowwnChannels = Array<String>() ;


/* Trace class public class methods */

void Trace::TraceEvent(String msg)   { if (DEBUG_TRACE_EVENTS) DBG("[EVENT]:   " + msg) ; }
void Trace::TraceConfig(String msg)  { if (DEBUG_TRACE_STATE)  DBG("[CONFIG]:  " + msg) ; }
void Trace::TraceClient(String msg)  { if (DEBUG_TRACE_STATE)  DBG("[CLIENT]:  " + msg) ; }
void Trace::TraceServer(String msg)  { if (DEBUG_TRACE_STATE)  DBG("[SERVER]:  " + msg) ; }
void Trace::TraceGui(String msg)     { if (DEBUG_TRACE_EVENTS) DBG("[GUI]:     " + msg) ; }
void Trace::TraceVerbose(String msg) { if (DEBUG_TRACE_VB)     DBG("[DEBUG]:   " + msg) ; }
#ifndef DEBUG_ANSI_COLORS
void Trace::TraceState(String msg)   { if (DEBUG_TRACE_STATE)  DBG("[STATE]:   " + msg) ; }
void Trace::TraceError(String msg)   { if (DEBUG_TRACE_STATE)  DBG("[ERROR]:   " + msg) ; }
// void Trace::TraceNetwork(String msg) { if (DEBUG_TRACE_EVENTS) DBG("[NETWORK]: " + msg) ; }
#else // DEBUG_ANSI_COLORS
void Trace::TraceState(String msg)
  { if (DEBUG_TRACE_STATE)  DBG("\033[1;33m[STATE]:   " + msg + "\033[0m") ; }
void Trace::TraceError(String msg)
  { if (DEBUG_TRACE_STATE)  DBG("\033[0;31m[ERROR]:   " + msg + "\033[0m") ; }
// void Trace::TraceNetwork(String msg)
//   { if (DEBUG_TRACE_EVENTS) DBG("\033[0;32m[NETWORK]: " + msg + "\033[0m") ; }
#endif // DEBUG_ANSI_COLORS
void Trace::DumpStoreXml(ValueTree store)
{ DBG(String(store.getType()) + " xml=\n" + store.toXmlString()) ; }

String Trace::DumpStoredChannels()
{
  String    dump     = "  localChannels =>" ;
  ValueTree channels = LinJam::Config->localChannels ;
  ValueTree users    = LinJam::Config->remoteUsers ;

  for (int ch_n = 0 ; ch_n < channels.getNumChildren() ; ++ch_n)
    dump += "\n    " + channels.getChild(ch_n)[CONFIG::CHANNEL_NAME_ID].toString() ;

  dump += "\n  remoteChannels =>" ;
  for (int user_n = 0 ; user_n < users.getNumChildren() ; ++user_n)
  {
    channels = users.getChild(user_n) ;
    for (int ch_n = 0 ; ch_n < channels.getNumChildren() ; ++ch_n)
      dump += "\n    " + String(channels.getType()) + " "                +
              channels.getChild(ch_n)[CONFIG::CHANNEL_NAME_ID].toString() ;
  }

  return dump ;
}

String Trace::DumpClientChannels()
{
  String dump = "\n  client locals =>" ; int channel_n = -1 ; int channel_idx ;
  while (~(channel_idx = LinJam::Client->EnumLocalChannels(++channel_n)))
    dump += "\n    " + LinJam::GetLocalChannelClientName(channel_idx) ;

  dump =+ "\n  client remotes =>" ;
  int user_idx = LinJam::Client->GetNumUsers() ; String user_name ;
  while ((user_name = LinJam::GetRemoteUserName(--user_idx)).isNotEmpty())
  {
    dump += "\n    " + user_name + " =>" ;
    int channel_n = -1 ; int channel_idx ;
    while (~(channel_idx = LinJam::Client->EnumUserChannels(user_idx , ++channel_n)))
      dump += "\n      " + LinJam::GetRemoteChannelClientName(user_idx , channel_idx) ;
  }

  return dump ;
}

String Trace::DumpConfig(ValueTree default_config , ValueTree stored_config , String pad)
{
  if (!default_config.isValid()) return "\nERROR: default config invalid" ;
  if (!stored_config .isValid()) return "\nERROR: stored config invalid" ;

  Identifier node_name          = default_config.getType() ;
  int        n_properties       = default_config.getNumProperties() ;
  int        n_default_children = default_config.getNumChildren() ;
  int        n_stored_children  = stored_config .getNumChildren() ;
  int        n_unique_children  = n_default_children ;

  // count unique child nodes
  if (stored_config.isValid())
    for (int child_n = 0 ; child_n < stored_config.getNumChildren() ; ++child_n)
    {
      Identifier child_node_name = stored_config.getChild(child_n).getType() ;
      if (!default_config.getChildWithName(child_node_name).isValid())
        ++n_unique_children ;
    }
  String dbg = "\n" + pad + "node => "       + String(node_name)                         +
                            " (properties: " + String(n_properties      )                +
                            " - children: "  + String(n_default_children) + " default, " +
                                               String(n_stored_children ) + " stored, "  +
                                               String(n_unique_children ) + " unique"    +
               ((!stored_config.isValid()) ?   "- stored node n/a - adding)" : ")")      ;

  // enumnerate properties
  if (n_properties)
  {
    for (int property_n = 0 ; property_n < n_properties ; ++property_n)
    {
      Identifier key           = default_config.getPropertyName(property_n) ;
      var        default_value = default_config.getProperty(key) ;
      var        stored_value  = (!stored_config.isValid()) ?      "n/a - adding" :
                                   stored_config.getProperty(key , "n/a - adding") ;
      dbg += "\n" + pad + "  key => "             + String(key)              +
             "\n" + pad + "    default_value => " + default_value.toString() +
             "\n" + pad + "    stored_value  => " + stored_value.toString()  ;
    }
  }

  // recurse on child nodes
  for (int child_n = 0 ; child_n < default_config.getNumChildren() ; ++child_n)
  {
    ValueTree  default_child   = default_config.getChild(child_n) ;
    Identifier child_node_name = default_child .getType() ;
    ValueTree  stored_child    = stored_config .getChildWithName(child_node_name) ;
    dbg                       += DumpConfig(default_child , stored_child , pad + "  ") ;
  }

  // user-defined nodes
  Array<Identifier> user_keys ;
  user_keys.add(CONFIG::SUBSCRIPTIONS_ID) ;
  user_keys.add(CONFIG::SERVERS_ID) ;
  user_keys.add(CONFIG::LOCALS_ID) ;
  user_keys.add(CONFIG::REMOTES_ID) ;
  if (user_keys.contains(node_name))
  {
    for (int child_n = 0 ; child_n < stored_config.getNumChildren() ; ++child_n)
    {
      ValueTree  stored_child  = stored_config .getChild(child_n) ;
      Identifier node_name     = stored_child  .getType() ;
      ValueTree  default_child = default_config.getChildWithName(node_name) ;
      int        n_children    = stored_child  .getNumChildren() ;
      int        n_properties  = stored_child  .getNumProperties() ;

      if (default_child.isValid() || n_children) continue ;

      dbg += "\n" + pad + "  stored node => " + String(node_name) + " (" +
              ((n_properties)? String(n_properties) + " properties" : "empty") + ")" ;

      for (int property_n = 0 ; property_n < n_properties ; ++property_n)
      {
        Identifier key          = stored_child.getPropertyName(property_n) ;
        String     stored_value = stored_child.getProperty(key).toString() ;
        dbg += "\n" + pad + "    key => "             + String(key)   +
               "\n" + pad + "      stored_value  => " + stored_value ;
      }
    }
  }

  return dbg ;
}

void Trace::TraceInvalidDefault(String a_default_name)
{ Trace::TraceError("default '" + a_default_name + "' invalid") ; }

void Trace::TraceInvalidNode(String a_node_name)
{ Trace::TraceError("node '" + a_node_name + "' invalid") ; }

void Trace::TraceMissingValue(String a_node_name , String a_value_name)
{ Trace::TraceError("node '" + a_node_name + "' - missing key '" + a_value_name + "'") ; }

void Trace::TraceMissingProperty(String a_node_name      , String a_property_name ,
                                 String parent_node_name                          )
{
  if (parent_node_name.isNotEmpty()) parent_node_name += " " ;
  Trace::TraceError(parent_node_name         + "node '"        + a_node_name +
                    "' - missing property '" + a_property_name + "'") ;
}

void Trace::TraceTypeMismatch(ValueTree a_node           , String a_property_name ,
                              String    expected_type    , var    a_var           ,
                              String    parent_node_name                          )
{
  String a_node_name = String(a_node.getType()) ;
  if (parent_node_name.isNotEmpty()) parent_node_name += " " ;
  Trace::TraceError("type mismatch - " + parent_node_name + a_node_name        +
                    "["                + a_property_name  + "] => "            +
                    VarType(a_var)     + " (expected "    + expected_type + ")") ;
}

String Trace::VarType(var a_var)
{
  String dynamic_type = "unknown" ;

  if      (a_var.isVoid())       dynamic_type = "void" ;
  else if (a_var.isUndefined())  dynamic_type = "undefined" ;
  else if (a_var.isInt())        dynamic_type = "int" ;
  else if (a_var.isInt64())      dynamic_type = "int64" ;
  else if (a_var.isBool())       dynamic_type = "bool" ;
  else if (a_var.isDouble())     dynamic_type = "double" ;
  else if (a_var.isString())     dynamic_type = "string" ;
  else if (a_var.isObject())     dynamic_type = "object" ;
  else if (a_var.isArray())      dynamic_type = "array" ;
  else if (a_var.isBinaryData()) dynamic_type = "binary" ;
  else if (a_var.isMethod())     dynamic_type = "method" ;

  return dynamic_type ;
}

String Trace::DumpVar(String val_name , var a_var)
{
  return "key => "     + val_name      .paddedRight(' ' , 20) +
         " type => "   + VarType(a_var).paddedRight(' ' , 10) +
         " value => "  + a_var.toString() ;
}

String Trace::Status2String(int status)
{
  return (status == -9)? "LINJAM_STATUS_INIT"                :
         (status == -8)? "LINJAM_STATUS_AUDIOERROR"          :
         (status == -7)? "LINJAM_STATUS_CONFIGPENDING"       :
         (status == -6)? "LINJAM_STATUS_READY"               :
         (status == -5)? "LINJAM_STATUS_LICENSEPENDING"      :
         (status == -4)? "LINJAM_STATUS_ROOMFULL"            :
         (status == -3)? "NJC_STATUS_DISCONNECTED"           :
         (status == -2)? "NJC_STATUS_INVALIDAUTH"            :
         (status == -1)? "NJC_STATUS_CANTCONNECT"            :
         (status ==  0)? "NJC_STATUS_OK"                     :
         (status ==  1)? "NJC_STATUS_PRECONNECT"             :
                         "(unknown: " + String(status) + ")" ;
}

#endif // #if DEBUG
