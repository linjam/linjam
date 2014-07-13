#include "Trace.h"


/* channels */

#define DEBUG_TRACE_ADD_CHANNEL_GUI_FAIL                                      \
  String dbg  = " adding channel slice '" + String(channel_store.getType()) + \
                "' to '" + getComponentID() + "' channels" ;                  \
  if (!channel_store.isValid())                                               \
    Trace::TraceError("channel store invalid" + dbg) ;                        \
  else if (bool(channel_store[CONFIG::IS_STEREO_ID])  &&                      \
           int( channel_store[CONFIG::SOURCE_N_ID]) % 2)                      \
    Trace::TraceGui(dbg + " (hidden stereo slave)") ;

#define DEBUG_TRACE_RENAME_CHANNEL                                                \
  Channel* ch   = getChannel(channel_id) ;                                        \
  String   name = (ch)? ch->configStore[CONFIG::CHANNELNAME_ID].toString() : "" ; \
  String   dbg  = "renaming channel '" + String(channel_id) + "'" ;               \
  if (ch) Trace::TraceGui(dbg + " to '" + name + "'") ;                           \
  else    Trace::TraceError("no such channel " + dbg) ;

#define DEBUG_TRACE_REMOVE_CHANNEL                                              \
  Channel* ch           = getChannel(channel_id) ;                              \
  bool     is_stereo    = ch && bool(ch->configStore[CONFIG::IS_STEREO_ID]) ;   \
  String   channel_type = (ch)? ((!is_stereo)? "mono" : "stereo") : "unknown" ; \
  String   dbg          = "removing "   + channel_type                        + \
                          " channel '"  + String(channel_id)                  + \
                          "' from '"    + getComponentID()     + "' channels" ; \
  if (ch) Trace::TraceGui(dbg) ; else Trace::TraceError(dbg) ;

#define DEBUG_TRACE_INVALID_CHANNELID                                            \
/* TODO: maybe? if VUs were listening on a store value then this trace  */       \
/*       and the chain ofupdateChannelVU() methods would be unnecessary */       \
  Channel* ch  = (Channel*)findChildWithID(StringRef(channel_name)) ;            \
  String   dbg = ((channel_name.isEmpty())? "empty" : ((!ch)? "unknown" : "")) + \
                 String(" channel_name '") + channel_name                      + \
                 "' updating VU for '"     + getComponentID() + "' channels"   + \
                 Trace::DumpStoredChannels()                                   + \
                 "\n  " + getComponentID() + " GUI Channels =>" ;                \
  for (int ch_n = 0 ; ch_n < getNumChannels() ; ++ch_n)                          \
    dbg += "\n    " + getChildComponent(ch_n)->getComponentID() ;                \
  if ((channel_name.isEmpty() || !ch) &&                                         \
     !Trace::UnknowwnChannels.contains(channel_name))                            \
  /* && ignore stereo pair 'phantom' channels            */                      \
  /* TODO: configStore is private to Channels base class */                      \
  /* (!bool(ch->configStore[CONFIG::IS_STEREO_ID])  ||   */                      \
  /*  !int( ch->configStore[CONFIG::SOURCE_N_ID]) % 2)   */                      \
  {                                                                              \
    Trace::TraceError(dbg) ; Trace::UnknowwnChannels.add(channel_name) ;         \
  }
