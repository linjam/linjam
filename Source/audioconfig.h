
// TODO: transitional - this function is slightly modified from the win32 client
//           it functionality is to be reimplemented in juce client (issue #27)
// NOTE: this file is not included in the jucer project


#include <windows.h>
#include <stdio.h>
#include <WDL/string.h>
#include <WDL/ptrlist.h>
#include <ninjam/audiostream.h>

#ifndef NO_SUPPORT_ASIO
#  include <ninjam/njasiodrv/njasiodrv_if.h>
#endif // NO_SUPPORT_ASIO


class audioStreamer_ASIO ;          // DEBUG
class audioStreamer_KS_asiosim ;    // DEBUG
class audioStreamer_win32_asiosim ; // DEBUG
class audioStreamer_CoreAudio ;     // DEBUG
class audioStreamer_JACK ;          // DEBUG
class audioStreamer_asiosim ;       // DEBUG


audioStreamer* CreateConfiguredStreamer(char*                     ini_file             ,
                                        audioStreamer::WinAudioIf audio_if_n           ,
                                        SPLPROC                   audiostream_onsamples) ;
