#include "Trace.h"


/* channels */

#define DEBUG_TRACE_ADD_CHANNEL_GUI_FAIL                       \
  String name = String(channel_store.getType()) ;              \
  String dbg  = " adding channel slice '" + name  + "' to '" + \
                getComponentID() + "' channels" ;              \
  if (!channel_store.isValid())                                \
    Trace::TraceError("channel store invalid" + dbg) ;         \
  else if (name.isEmpty())                                     \
    Trace::TraceError("channel name empty" + dbg) ;            \
  else if (bool(channel_store[CONFIG::IS_STEREO_ID])  &&       \
           int( channel_store[CONFIG::SOURCE_N_ID]) % 2)       \
    Trace::TraceGui(dbg + " (hidden stereo slave)") ;

#define DEBUG_REMOVE_CHANNEL                                                \
  bool   is_stereo     = bool(channel->configStore[CONFIG::IS_STEREO_ID]) ; \
  String channel_type  = (!is_stereo)? "mono" : "stereo" ;                  \
  String channels_name = getComponentID() ;                                 \
  Trace::TraceGui("removing " + channel_type + " channel '" +               \
                  channel->getComponentID()  + "' from '"   +               \
                  channels_name + "' channels") ;

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
