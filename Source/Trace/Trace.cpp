
#include "../Constants.h"
#include "../LinJam.h"
#include "Trace.h"


#if DEBUG_TRACE

/* Trace class private class variables */

Array<String> Trace::UnknowwnChannels = Array<String>() ;


/* Trace class public class methods */

void Trace::TraceEvent(String msg)   { if (DEBUG_TRACE_EVENTS) DBG("[EVENT]:   " + msg) ; }
void Trace::TraceConfig(String msg)  { if (DEBUG_TRACE_STATE)  DBG("[CONFIG]:  " + msg) ; }
void Trace::TraceClient(String msg)  { if (DEBUG_TRACE_STATE)  DBG("[CLIENT]:  " + msg) ; }
void Trace::TraceGui(String msg)     { if (DEBUG_TRACE_EVENTS) DBG("[GUI]:     " + msg) ; }
void Trace::TraceVerbose(String msg) { if (DEBUG_TRACE_VB)     DBG("[DEBUG]:   " + msg) ; }
void Trace::TraceState(String msg)   { if (DEBUG_TRACE_STATE)  DBG("[STATE]:   " + msg) ; }
void Trace::TraceNetwork(String msg) { if (DEBUG_TRACE_STATE)  DBG("[NETWORK]: " + msg) ; }
void Trace::TraceError(String msg)   { if (DEBUG_TRACE_STATE)  DBG("[ERROR]:   " + msg) ; }
void Trace::TraceServer(String msg)  { if (DEBUG_TRACE_STATE)  DBG("[SERVER]:  " + msg) ; }

void Trace::DumpStoreXml(ValueTree store)
{ DBG(String(store.getType()) + " xml=\n" + store.toXmlString()) ; }

String Trace::DumpStoredChannels()
{
  String    dump     = "\n  localChannels =>" ;
  ValueTree channels = LinJam::Config->localChannels ;
  ValueTree users    = LinJam::Config->remoteUsers ;

  for (int ch_n = 0 ; ch_n < channels.getNumChildren() ; ++ch_n)
    dump += "\n    " + channels.getChild(ch_n)[CONFIG::CHANNELNAME_ID].toString() ;

  dump += "\n  remoteChannels =>" ;
  for (int user_n = 0 ; user_n < users.getNumChildren() ; ++user_n)
  {
    channels = users.getChild(user_n) ;
    /* TODO: KLUDGE (issue #33) nyi remote-channels node */
    if (!channels.hasProperty(CONFIG::USERIDX_ID)) continue ;

    for (int ch_n = 0 ; ch_n < channels.getNumChildren() ; ++ch_n)
      dump += "\n    " + String(channels.getType()) + " "                +
              channels.getChild(ch_n)[CONFIG::CHANNELNAME_ID].toString() ;
  }

  return dump ;
}

String Trace::DumpClientChannels()
{
  String dump = "\n  client locals =>" ; int channel_n = -1 ; int channel_idx ;
  while (~(channel_idx = LinJam::Client->EnumLocalChannels(++channel_n)))
    dump += "\n    " + LinJam::GetLocalChannelClientName(channel_idx) ;

  dump = "\n  client remotes =>" ;
  int user_idx = LinJam::Client->GetNumUsers() ; String user_name ;
  while ((user_name = LinJam::GetRemoteUserName(--user_idx)).isNotEmpty())
  {
    dump = "\n    " + user_name + " =>" ;
    int channel_n = -1 ; int channel_idx ;
    while (~(channel_idx = LinJam::Client->EnumUserChannels(user_idx , ++channel_n)))
      dump += "\n      " + LinJam::GetRemoteChannelClientName(user_idx , channel_idx) ;
  }

  return dump ;
}

String Trace::SanitizeConfig(ValueTree default_config , ValueTree stored_config ,
                             String pad)
{
  if (!default_config.isValid()) return "ERROR: default config invalid" ;
  if (!stored_config.isValid())  return "ERROR: stored config invalid" ;

  Identifier node_name   = default_config.getType() ;
  int n_default_children = default_config.getNumChildren() ;
  int n_stored_children  = stored_config.getNumChildren() ;
  int n_unique_children  = n_default_children ;
  if (stored_config.isValid())
    for (int child_n = 0 ; child_n < stored_config.getNumChildren() ; ++child_n)
    {
      Identifier node_name = stored_config.getChild(child_n).getType() ;
      if (!default_config.getChildWithName(node_name).isValid())
        ++n_unique_children ;
    }
  String dbg = "\n" + pad + "default node => " + String(node_name) + " (" +
               String(n_default_children) + " default "         +
               String(n_stored_children)  + " stored "          +
               String(n_unique_children)  + " unique children)" ;

  for (int child_n = 0 ; child_n < default_config.getNumChildren() ; ++child_n)
  {
    ValueTree  default_child = default_config.getChild(child_n) ;
    Identifier node_name     = default_child.getType() ;
    ValueTree  stored_child  = stored_config.getChildWithName(node_name) ;
    int        n_children    = default_child.getNumChildren() ;
    int        n_properties  = default_child.getNumProperties() ;

    if (n_properties)
    {
      dbg += "\n" + pad + "  default node => " + String(node_name) + " (" +
             ((n_properties)? String(n_properties) + " properties" : "empty") + ")" +
             ((!stored_child.isValid())? " - stored node n/a - adding" : "") ;

      for (int property_n = 0 ; property_n < n_properties ; ++property_n)
      {
        Identifier key           = default_child.getPropertyName(property_n) ;
        String     default_value = default_child.getProperty(key).toString() ;
        String     stored_value  = (!stored_child.isValid())? "n/a - adding" :
                                   stored_child.getProperty(key , "n/a - adding").toString() ;
        dbg += "\n" + pad + "    key => "             + String(key)   +
               "\n" + pad + "      default_value => " + default_value +
               "\n" + pad + "      stored_value  => " + stored_value ;
      }
    }
    else dbg += SanitizeConfig(default_child , stored_child , pad + "  ") ;
  }

  Array<Identifier> user_keys ;
  user_keys.add(CONFIG::LOCALS_ID) ;
//  user_keys.add(CONFIG::REMOTES_ID) ; // TODO:
  user_keys.add(CONFIG::SUBSCRIPTIONS_ID) ; // TODO:
  user_keys.add(CONFIG::SERVERS_ID) ;
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

void Trace::TraceTypeMismatch(String a_node_name      , String a_property_name ,
                              String expected_type    , var    a_var           ,
                              String parent_node_name                          )
{
  if (parent_node_name.isNotEmpty()) parent_node_name += " " ;
  Trace::TraceError("type mismatch - " + parent_node_name + a_node_name         +
                    "["                + a_property_name  + "] => "             +
                    VarType(a_var)     + " (expected "     + expected_type + ")") ;
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

#endif // #if DEBUG_TRACE
