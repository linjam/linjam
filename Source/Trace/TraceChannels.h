#include "Trace.h"


/* channels */

#if TRACE_DUMP_CHANNELS_GUI
#  define DEBUG_TRACE_DUMP_CHANNELS_GUI_VB                                            \
  String dump = getComponentID() + " has " + String(getNumChannels()) + " channels" ; \
  for (int channel_n = 0 ; channel_n < getNumChannels() ; ++channel_n)                \
  {                                                                                   \
    Channel* channel = (Channel*)getChildComponent(channel_n) ;                       \
    dump += "\n  channel[" + String(channel_n) + "] => "   +                          \
           channel->getComponentID().paddedRight(' ' , 12) +                          \
           " '" + channel->nameLabel->getText() + "'" ;                               \
  }                                                                                   \
  Trace::TraceGui(dump) ;
#else // TRACE_DUMP_CHANNELS_GUI
#  define DEBUG_TRACE_DUMP_CHANNELS_GUI_VB ;
#endif // TRACE_DUMP_CHANNELS_GUI

#define DEBUG_TRACE_ADD_CHANNEL_GUI_FAIL                                      \
  String dbg  = "adding channel slice '" + String(channel_store.getType()) +  \
                "' to '" + getComponentID() + "' channels" ;                  \
  if (!channel_store.isValid())                                               \
    Trace::TraceError("channel store invalid " + dbg) ;                       \
  else if (int(channel_store[CONFIG::STEREO_ID]) == CONFIG::STEREO_R)         \
    Trace::TraceGui(dbg + " (hidden stereo slave)") ;

#if TRACE_ADD_CHANNEL_GUI_VB
#  define DEBUG_TRACE_ADD_CHANNEL_GUI                                           \
  Trace::TraceGui(String("added channel slice " + String(channel_id) + " =>") + \
    "\n  mixer_group  => " + String(getComponentID())                         + \
    "\n  channel_name => " + channel_store[CONFIG::CHANNELNAME_ID].toString() + \
    "\n  volume       => " + channel_store[CONFIG::VOLUME_ID].toString()      + \
    "\n  pan          => " + channel_store[CONFIG::PAN_ID].toString()         + \
    "\n  is_xmit      => " + channel_store[CONFIG::IS_XMIT_RCV_ID].toString() + \
    "\n  is_muted     => " + channel_store[CONFIG::IS_MUTED_ID].toString()    + \
    "\n  is_solo      => " + channel_store[CONFIG::IS_SOLO_ID].toString()     + \
    "\n  source_ch    => " + channel_store[CONFIG::SOURCE_N_ID].toString()    + \
    "\n  stereo_state => " + channel_store[CONFIG::STEREO_ID].toString()) ;     \
  DEBUG_TRACE_DUMP_CHANNELS_GUI_VB
#else // TRACE_ADD_CHANNEL_GUI_VB
#  define DEBUG_TRACE_ADD_CHANNEL_GUI                                  \
  Trace::TraceGui("added channel slice " + String(channel_id) + " '" + \
                  channel_store[CONFIG::CHANNELNAME_ID].toString()   + \
                  "' to '" + String(getComponentID()) + "'") ;         \
  DEBUG_TRACE_DUMP_CHANNELS_GUI_VB
#endif // TRACE_ADD_CHANNEL_GUI_VB

#define DEBUG_TRACE_RENAME_CHANNEL_GUI                                                \
  Channel* ch       = getChannel(channel_id) ;                                        \
  String   prevname = (ch)? ch->nameLabel->getText() : "" ;                           \
  String   newname  = (ch)? ch->configStore[CONFIG::CHANNELNAME_ID].toString() : "" ; \
  String   dbg      = "renaming channel '" + String(channel_id) + "'" ;               \
  if (prevname.compare(newname))                                                      \
    if (ch) Trace::TraceGui(dbg + " from '" + prevname + "' to '" + newname + "'") ;  \
    else    Trace::TraceError("no such channel " + dbg) ;

#define DEBUG_TRACE_REMOVE_CHANNEL_GUI                                                    \
  Channel* ch           = getChannel(channel_id) ;                                        \
  bool     is_stereo    = ch && int(ch->configStore[CONFIG::STEREO_ID]) != CONFIG::MONO ; \
  String   channel_type = (ch)? ((!is_stereo)? "mono" : "stereo") : "unknown" ;           \
  String   dbg          = "removing "   + channel_type                        +           \
                          " channel '"  + String(channel_id)                  +           \
                          "' from '"    + getComponentID()     + "' channels" ;           \
  if (ch) Trace::TraceGui(dbg) ; else Trace::TraceError(dbg) ;                            \
  DEBUG_TRACE_DUMP_CHANNELS_GUI_VB

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


/* vu */

#if 0
#  define DEBUG_TRACE_VU_GUI_VB                                                  \
  String name = (!!channel)? "'" + channel->nameLabel->getText() + "'" : "n/a" ; \
  Trace::TraceGui("updating VU for "                                           + \
                  getComponentID()  .paddedRight(' ' , 18).substring(0 , 18)   + \
                  String(channel_id).paddedRight(' ' , 12)                     + \
                  name              .paddedRight(' ' , 12).substring(0 , 12)   + \
                  String((int)vu)   .paddedRight(' ' ,  6)                     + \
                  ((!!channel)? "" : " (hidden)")) ;
#else // TRACE_VU_GUI
#  define DEBUG_TRACE_VU_GUI_VB ;
#endif // TRACE_VU_GUI
