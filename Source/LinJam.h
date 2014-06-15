/*
  ==============================================================================

    LinJam.h
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

#include "LinJamConfig.h"
#include "MainComponent.h"


class LinJam
{
    friend class LinJamConfig ;


public:

  // state methods
  static bool Initialize(NJClient* client , MainContentComponent* mainGUI ,
                         const String& args) ;
  static void Connect() ;
  static void Disconnect() ;
  static void Shutdown() ;

  // getters/setters
  static bool IsAgreed() ;

  // chat helpers
  static void SendChat(String chat_text) ;


  static LinJamConfig* Config ;


private:

  static audioStreamer*        Audio ;
  static MainContentComponent* Gui ;
  static NJClient*             Client ;
  static bool                  IsAudioEnabled ;
  static File                  SessionDir ;


  // NJClient callbacks
  static int  OnLicense(int user32            , char* license_text) ;
  static void OnChatmsg(int user32            , NJClient* instance ,
                        const char** parms    , int nparms)        ;
  static void OnSamples(float** input_buffer  , int n_input_channels  ,
                        float** output_buffer , int n_output_channels ,
                        int n_samples         , int sample_rate)      ;

  // helpers
  static bool InitializeAudio() ;
  static void ConfigureAudio() ;
  static bool PrepareSessionDirectory() ;
  static void ConfigureNinjam() ;
  static void CleanSessionDir() ;
  static void HandleChatCommand(String chat_text) ;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinJam) ;
} ;

#endif  // LINJAM_H_INCLUDED
