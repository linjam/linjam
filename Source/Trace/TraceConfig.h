#if DEBUG

#  include "Trace.h"


// audio
#define DEBUG_TRACE_CONFIG_AUDIO_GUI_LOAD                                   \
  Trace::TraceGui("current audio configuration is "                       + \
                  String((is_asio) ? CLIENT::ASIO_DEVICE_TYPE + " " : "") + \
                  String((is_ks  ) ? CLIENT::KS_DEVICE_TYPE   + " " : "") + \
                  String((is_ds  ) ? CLIENT::DS_DEVICE_TYPE   + " " : "") + \
                  String((is_wave) ? CLIENT::WAVE_DEVICE_TYPE + " " : "") + \
                  String((is_ca  ) ? CLIENT::CA_DEVICE_TYPE   + " " : "") + \
                  String((is_jack) ? CLIENT::JACK_DEVICE_TYPE + " " : "") + \
                  String((is_alsa) ? CLIENT::ALSA_DEVICE_TYPE + " " : "") + \
                  String((!is_asio && !is_ks   && !is_ds && !is_wave &&     \
                          !is_ca   && !is_jack && !is_alsa) ?               \
                          CLIENT::NFG_DEVICE_TYPE : ""                  ) ) ;

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
