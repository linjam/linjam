/*
  ==============================================================================

    Linjam.h
    Created: 24 May 2014 5:03:01pm
    Author:  me

  ==============================================================================
*/
#ifndef LINJAM_H_INCLUDED
#define LINJAM_H_INCLUDED


#include <ninjam/audiostream.h>
#include <ninjam/njclient.h>
#include <ninjam/njmisc.h>

#include "../JuceLibraryCode/JuceHeader.h"


class LinJamClient
{
public:

  static int  Initialize( NJClient* client , const String& args) ;
  static void Shutdown() ;
  static int  OnLicense(  int user32 , char* license_text) ;
  static void OnChatmsg(  int user32 , NJClient* instance ,
                          const char** parms , int nparms) ;
  static void OnSamples(  float** in_buffer , int in_n_channels ,
                          float** out_buffer , int out_n_channels ,
                          int len , int sample_rate) ;
  static void OnUnderflow() ;
  static void OnOverflow() ;

private:

  static const char* WIN_INI_FILE ;
} ;

#endif  // LINJAM_H_INCLUDED
