
//#include <ninjam/njclient.h>
#include "Constants.h"
#include "LinJam.h"
#include "Trace.h"


#if DEBUG_TRACE

/* Trace class private class variables */

Array<String> Trace::UnknowwnChannels = Array<String>() ;


/* Trace class public class methods */

void Trace::TraceEvent(String msg)   { if (TraceEvs())    DBG("[EVENT]:   " + msg) ; }
void Trace::TraceConfig(String msg)  { if (TraceState())  DBG("[CONFIG]:  " + msg) ; }
void Trace::TraceGui(String msg)     { if (TraceEvs())    DBG("[GUI]:     " + msg) ; }
void Trace::TraceVerbose(String msg) { if (TraceVb())     DBG("[DEBUG]:   " + msg) ; }
void Trace::TraceState(String msg)   { if (TraceState())  DBG("[STATE]:   " + msg) ; }
void Trace::TraceNetwork(String msg) { if (TraceState())  DBG("[NETWORK]: " + msg) ; }
void Trace::TraceError(String msg)   { if (TraceState())  DBG("[ERROR]:   " + msg) ; }
void Trace::TraceServer(String msg)  { if (TraceState())  DBG("[SERVER]:  " + msg) ; }

void Trace::DumpStoreXml(ValueTree store)
{ DBG(String(store.getType()) + " xml=\n" + store.toXmlString()) ; }


/* Trace class private class methods */

bool Trace::SanityCheck() { return true ; }

bool Trace::TraceEvs()   { return (DEBUG_TRACE_EVENTS || !SanityCheck()) ; }
bool Trace::TraceVb()    { return (DEBUG_TRACE_VB     || !SanityCheck()) ; }
bool Trace::TraceState() { return (DEBUG_TRACE_STATE  || !SanityCheck()) ; }

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
      Identifier node_name     = stored_child   .getType() ;
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

void Trace::TraceInvalidNode(String a_node_key)
{ Trace::TraceError("node '" + a_node_key + "' invalid") ; }

void Trace::TraceMissingValue(String a_node_key , String a_value_key)
{ Trace::TraceError("node '" + a_node_key + "' - missing key '" + a_value_key + "'") ; }

void Trace::TraceMissingProperty(String a_node_key , String a_property_key)
{ Trace::TraceError("node '" + a_node_key + "' - missing key '" + a_property_key + "'") ; }

void Trace::DbgValueType(String dbg_val_name , var a_var)
{
  String dynamic_type ;
  if      (a_var.isVoid())       dynamic_type = "Void" ;
  else if (a_var.isUndefined())  dynamic_type = "Undefined" ;
  else if (a_var.isInt())        dynamic_type = "Int" ;
  else if (a_var.isInt64())      dynamic_type = "Int64" ;
  else if (a_var.isBool())       dynamic_type = "Bool" ;
  else if (a_var.isDouble())     dynamic_type = "Double" ;
  else if (a_var.isString())     dynamic_type = "String" ;
  else if (a_var.isObject())     dynamic_type = "Object" ;
  else if (a_var.isArray())      dynamic_type = "Array" ;
  else if (a_var.isBinaryData()) dynamic_type = "Binary" ;
  else if (a_var.isMethod())     dynamic_type = "Method" ;
  DBG(dbg_val_name + " type is " + dynamic_type) ;
}

#endif // #if DEBUG_TRACE
