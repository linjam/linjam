#if DEBUG

#include "Trace.h"


/* MainContent GUI */

#define DEBUG_TRACE_KEYPRESSED                                       \
  Trace::TraceGuiVb("key pressed: " + String(keypress.getKeyCode())) ;

#define DEBUG_TRACE_UPDATEMODEBTN                                                        \
  Trace::TraceGuiVb("Status: "     + String(int(linjamStatus.getValue()))              + \
                    " - updating mode: " + ( (is_config) ? "config" :                    \
                                           ( (is_jam   ) ? "jam"    :                    \
                                           ( (is_logout) ? "logout" :                    \
                                           ( (is_lobby ) ? "lobby"  : "un-handled" ))))) ;

#else // DEBUG

// MainContent GUI
#define DEBUG_TRACE_KEYPRESSED    ;
#define DEBUG_TRACE_UPDATEMODEBTN ;

#endif // DEBUG
