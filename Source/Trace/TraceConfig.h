#if DEBUG

#include "Trace.h"


// audio
#define DEBUG_TRACE_CONFIG_AUDIO_GUI_LOAD                                \
  Trace::TraceGui("current audio configuration is "                    + \
                  String((is_asio) ? GUI::ASIO_DEVICE_TYPE + " " : "") + \
                  String((is_ks  ) ? GUI::KS_DEVICE_TYPE   + " " : "") + \
                  String((is_ds  ) ? GUI::DS_DEVICE_TYPE   + " " : "") + \
                  String((is_wave) ? GUI::WAVE_DEVICE_TYPE + " " : "") + \
                  String((is_ca  ) ? GUI::CA_DEVICE_TYPE   + " " : "") + \
                  String((is_jack) ? GUI::JACK_DEVICE_TYPE + " " : "") + \
                  String((is_alsa) ? GUI::ALSA_DEVICE_TYPE + " " : "") + \
                  String((!is_asio && !is_ks   && !is_ds && !is_wave &&  \
                          !is_ca   && !is_jack && !is_alsa) ?            \
                          GUI::NFG_DEVICE_TYPE : ""                  ) ) ;

#define DEBUG_TRACE_UPDATE_LATENCY                                                     \
  if (DEBUG_TRACE_VB) Trace::TraceGui("updating latency display => "                 + \
      String(latency_ms)              + " ms\n\t"                                    + \
      String(sample_rate)             + " x "   + String(bit_depth)   + " bits\n\t"  + \
      String(n_buffers)               + " x "   + String(buffer_size) + " Bytes\n\t" + \
      String(n_buffers * buffer_size) + " total_buffer_size\n\t"                     + \
      String(bytes_per_ms)            + " bytes_per_ms"                              ) ;
#else // DEBUG

// audio
#define DEBUG_TRACE_CONFIG_AUDIO_GUI_LOAD ;
#define DEBUG_TRACE_UPDATE_LATENCY        ;

#endif // DEBUG
