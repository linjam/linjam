#if DEBUG

#include "Trace.h"


// fonts

#define DEBUG_TRACE_SET_FONTSIZE Trace::TraceGui("chat font size changed "         + \
    String(this->chatText->getFont().getHeight()) + " => "  + String(getFontSize())) ;

#else // DEBUG

#define DEBUG_TRACE_SET_FONTSIZE ;

#endif // DEBUG
