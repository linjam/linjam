#include "Trace.h"


/* channels */

#define DEBUG_TRACE_ADD_REMOTE_USER                                        \
  Trace::TraceGui("added remote channels group '" + String(user_id) + "'") ;

#define DEBUG_REMOVE_CHANNELS                                 \
  String user_id = channels->getComponentID() ;               \
  Trace::TraceState("user parted => '" + user_id + "'") ;     \
  Trace::TraceEvent("removing remote user '" + user_id + "'") ;


/* mixer */

#if TRACE_MIXER_COMPONENTS
#  define DEBUG_TRACE_MIXER_COMPONENTS_VB                                       \
  if (this->masterChannels   == nullptr || this->localChannels    == nullptr || \
      this->prevScrollButton == nullptr || this->nextScrollButton == nullptr  ) \
    Trace::TraceVerbose("mixer resized - GUI not ready") ;                      \
  String dbg = "mixer resized " + String(getNumChildComponents())    +          \
                " mixer components ("                                 +          \
                String(GUI::N_STATIC_MIXER_CHILDREN) + " static) =>"  ;          \
  for (int n = 0 ; n < getNumChildComponents() ; ++n)                           \
  {                                                                             \
    Component* child = getChildComponent(n) ; String id ;                       \
    if      (child == this->masterChannels)   id = "masterChannels" ;           \
    else if (child == this->prevScrollButton) id = "prevScrollButton" ;         \
    else if (child == this->nextScrollButton) id = "nextScrollButton" ;         \
    else if (child == this->localsResizer)    id = "localsResizer" ;            \
    else if (child == this->mastersResizer)   id = "mastersResizer" ;           \
    else                                      id = child->getComponentID() ;    \
    dbg += "\n  component[" + String(n) + "] => " + String(id) ;                \
  }                                                                             \
  Trace::TraceVerbose(dbg) ;
#else // TRACE_MIXER_COMPONENTS
#  define DEBUG_TRACE_MIXER_COMPONENTS_VB ;
#endif // TRACE_MIXER_COMPONENTS
