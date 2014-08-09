#if DEBUG

#  include "Trace.h"


// audio
#define DEBUG_TRACE_AUDIO_CONFIG_LOAD                          \
  Trace::TraceGui("showing current audio configuration for " + \
                  String((is_asio)? "asio " : "")            + \
                  String((is_ks)  ? "ks "   : "")            + \
                  String((is_ds)  ? "ds "   : "")            + \
                  String((is_wave)? "wave " : "")            + \
                  String((is_jack)? "jack " : "")            + \
                  String((is_alsa)? "alsa"  : "")            ) ;

#else // DEBUG

// audio
#define DEBUG_TRACE_AUDIO_CONFIG_LOAD ;

#endif // DEBUG
