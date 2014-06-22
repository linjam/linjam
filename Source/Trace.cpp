
//#include <ninjam/njclient.h>
#include "Constants.h"
#include "LinJam.h"
#include "Trace.h"



#if DEBUG_TRACE

/* public class methods */

void Trace::TraceConfig(String msg)       { if (TraceState())  Dbg("CONFIG"     , msg) ; }
void Trace::TraceEvent(String msg)        { if (TraceEvs())    Dbg("EVENT"      , msg) ; }
void Trace::TraceVerbose(String msg)      { if (TraceVb())     Dbg("DEBUG"      , msg) ; }
void Trace::TraceState(String msg)        { if (TraceState())  Dbg("STATE"      , msg) ; }
void Trace::TraceConnection(String msg)   { if (TraceState())  Dbg("CONNECTION" , msg) ; }
void Trace::TraceError(String msg)        { if (TraceState())
DBG("TraceError()") ;
Dbg("ERROR"      , msg) ; }
void Trace::TraceServer(String msg)       { if (TraceState())  Dbg("SERVER"     , msg) ; }

void Trace::Dbg(String type , String msg) { DBG(String("[" + type + "]: " + msg)) ; }
void Trace::DumpStoreXml(ValueTree store)
{ DBG(String(store.getType()) + " xml=\n" + store.toXmlString()) ; }


/* private class methods */

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
  user_keys.add(CONFIG::LOCALS_IDENTIFIER) ;
//  user_keys.add(CONFIG::REMOTES_IDENTIFIER) ; // TODO:
  user_keys.add(CONFIG::SUBSCRIPTIONS_IDENTIFIER) ; // TODO:
  user_keys.add(CONFIG::SERVERS_IDENTIFIER) ;
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
{
DBG("TraceInvalidNode()") ;
  Trace::TraceError("node '" + a_node_key + "' invalid") ; }

void Trace::TraceMissingValue(String a_node_key , String a_value_key)
{ Trace::TraceError("node '" + a_node_key + "' - missing key '" + a_value_key + "'") ; }

void Trace::TraceMissingProperty(String a_node_key , String a_property_key)
{ Trace::TraceError("node '" + a_node_key + "' - missing key '" + a_property_key + "'") ; }

#endif // #if DEBUG_TRACE
