#if DEBUG

#  include "Trace.h"


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

#define DEBUG_TRACE_ADD_CHANNEL_GUI_FAIL                                    \
  String ch_id        = String(channel_store.getType()) ;                   \
  String ch_name      = channel_store[CONFIG::CHANNEL_NAME_ID].toString() ; \
  int    stereo_state = int(channel_store[CONFIG::STEREO_ID]) ;             \
  String dbg   = "adding channel slice " + ch_id + " '" + ch_name +         \
                 "' to '" + getComponentID() + "' channels" ;               \
  if (!channel_store.isValid())                                             \
    Trace::TraceError("channel store invalid " + dbg) ;                     \
  else if (!getChannel(ch_id) && stereo_state == CONFIG::STEREO_R)          \
    Trace::TraceGui(dbg + " (hidden)") ;

#if TRACE_ADD_CHANNEL_GUI_VB
#  define DEBUG_TRACE_ADD_CHANNEL_GUI                                            \
  Trace::TraceGui(String("added channel slice " + String(channel_id) + " =>")  + \
    "\n  mixer_group  => " + String(getComponentID())                          + \
    "\n  channel_name => " + channel_store[CONFIG::CHANNEL_NAME_ID].toString() + \
    "\n  channel_idx  => " + channel_store[CONFIG::CHANNEL_IDX_ID].toString()  + \
    "\n  pair_idx     => " + channel_store[CONFIG::PAIR_IDX_ID].toString()     + \
    "\n  volume       => " + channel_store[CONFIG::VOLUME_ID].toString()       + \
    "\n  pan          => " + channel_store[CONFIG::PAN_ID].toString()          + \
    "\n  is_xmit      => " + channel_store[CONFIG::IS_XMIT_RCV_ID].toString()  + \
    "\n  is_muted     => " + channel_store[CONFIG::IS_MUTED_ID].toString()     + \
    "\n  is_solo      => " + channel_store[CONFIG::IS_SOLO_ID].toString()      + \
    "\n  source_ch    => " + channel_store[CONFIG::SOURCE_N_ID].toString()     + \
    "\n  stereo_state => " + channel_store[CONFIG::STEREO_ID].toString()) ;      \
  DEBUG_TRACE_DUMP_CHANNELS_GUI_VB
#else // TRACE_ADD_CHANNEL_GUI_VB
#  define DEBUG_TRACE_ADD_CHANNEL_GUI                                   \
  Trace::TraceGui("added channel slice " + String(channel_id) + " '"  + \
                  channel_store[CONFIG::CHANNEL_NAME_ID].toString()   + \
                  "' to '" + String(getComponentID()) + "'") ;          \
  DEBUG_TRACE_DUMP_CHANNELS_GUI_VB
#endif // TRACE_ADD_CHANNEL_GUI_VB

#define DEBUG_TRACE_RENAME_CHANNEL_GUI_VIA_LABEL                         \
  String prev_name = this->channelName.getValue().toString() ;           \
  String new_name  = this->nameLabel->getText() ;                        \
  if (prev_name.compare(new_name))                                       \
    Trace::TraceGui("renaming channel " + getComponentID() +             \
                    " from '" + prev_name + "' to '"  + new_name  + "'") ;

#define DEBUG_TRACE_RENAME_CHANNEL_GUI_VIA_CALLOUTBOX                    \
  String prev_name = this->nameLabel->getText() ;                        \
  String new_name  = this->channelName.getValue().toString() ;           \
  if (prev_name.compare(new_name))                                       \
    Trace::TraceGui("renaming channel " + getComponentID() +             \
                    " from '" + prev_name + "' to '"  + new_name  + "'") ;

#define DEBUG_TRACE_REMOVE_CHANNEL_GUI                                                     \
  Channel* ch           = getChannel(channel_id) ;                                         \
  bool     is_stereo    = ch && int(ch->configStore[CONFIG::STEREO_ID]) != CONFIG::MONO ;  \
  String   channel_type = (ch)? ((!is_stereo)? "mono" : "stereo") : "unknown" ;            \
  String   channel_name = (ch)? ch->configStore[CONFIG::CHANNEL_NAME_ID].toString() : "" ; \
  String   dbg          = "removing " + channel_type                             +         \
                          " channel " + String(channel_id) + " '" + channel_name +         \
                          "' from '"  + getComponentID()   + "' channels" ;                \
  if (ch) Trace::TraceGui(dbg) ; else Trace::TraceError(dbg) ;                             \
  DEBUG_TRACE_DUMP_CHANNELS_GUI_VB

#define DEBUG_TRACE_STEREO_STATE_GUI                                                  \
  int        stereo_status = int(this->stereoStatus.getValue()) ;                     \
  Identifier parent_id     = (!this->configStore.getParent().isValid())? "orphan" :   \
                             this->configStore.getParent().getType() ;                \
  Trace::TraceGui(String(parent_id) + " channel '" + this->nameLabel->getText()     + \
                  "' stereo status is "                                             + \
                  ((stereo_status == CONFIG::MONO)    ? "MONO"     :                  \
                   (stereo_status == CONFIG::STEREO_L)? "STEREO_L" :                  \
                   (stereo_status == CONFIG::STEREO_R)? "STEREO_R" :                  \
                   (stereo_status == CONFIG::STEREO)  ? "STEREO"   : "NFG")) ;

#else // DEBUG

// channels
#define DEBUG_TRACE_DUMP_CHANNELS_GUI_VB              ;
#define DEBUG_TRACE_ADD_CHANNEL_GUI_FAIL              ;
#define DEBUG_TRACE_ADD_CHANNEL_GUI                   ;
#define DEBUG_TRACE_RENAME_CHANNEL_GUI_VIA_LABEL      ;
#define DEBUG_TRACE_RENAME_CHANNEL_GUI_VIA_CALLOUTBOX ;
#define DEBUG_TRACE_REMOVE_CHANNEL_GUI                ;
#define DEBUG_TRACE_STEREO_STATE_GUI                  ;

#endif // DEBUG
