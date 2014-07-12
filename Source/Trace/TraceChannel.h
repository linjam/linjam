#include "Trace.h"


/* channels */

#if TRACE_ADDED_CHANNEL_VB
#  define DEBUG_TRACE_ADDED_CHANNEL                                             \
  Trace::TraceGui(String("channel slice added =>")                            + \
    "\n  mixer_group  => " + String(this->configStore.getParent().getType())  + \
    "\n  channel_name => " + channel_name                                     + \
    "\n  volume       => " + String(volume)                                   + \
    "\n  pan          => " + String(pan)                                      + \
    "\n  is_xmit      => " + String(is_xmit)                                  + \
    "\n  is_muted     => " + String(is_muted)                                 + \
    "\n  is_solo      => " + String(is_solo)                                  + \
    "\n  source_ch    => " + String(source_ch)                                + \
    "\n  is_stereo    => " + String(is_stereo)) ;
#else // TRACE_ADDED_CHANNEL_VB
#  define DEBUG_TRACE_ADDED_CHANNEL                                      \
  Trace::TraceGui("added channel slice '" + channel_name + "' to '" +    \
                  String(this->configStore.getParent().getType()) + "'") ;
#endif // TRACE_ADDED_CHANNEL_VB

