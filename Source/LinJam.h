/*
  ==============================================================================

    LinJam.h
    Created: 24 May 2014 5:03:01pm
    Author:  me

  ==============================================================================
*/
#ifndef LINJAM_H_INCLUDED
#define LINJAM_H_INCLUDED
#define PERSISTENCE_TRANSITION 1

#include <ninjam/audiostream.h>
#include <ninjam/njclient.h>
#include <ninjam/njmisc.h>

#include "../JuceLibraryCode/JuceHeader.h"

#include "LinJamConfig.h"
#include "MainComponent.h"


class LinJam
{
public:

  static bool Initialize(NJClient* client , MainContentComponent* mainGUI ,
                         const String& args) ;
  static void Connect() ;
  static void Disconnect() ;
  static void Shutdown() ;

  // NJClient callbacks
  static int  OnLicense(int user32            , char* license_text) ;
  static void OnChatmsg(int user32            , NJClient* instance ,
                        const char** parms    , int nparms)        ;
  static void OnSamples(float** input_buffer  , int n_input_channels  ,
                        float** output_buffer , int n_output_channels ,
                        int n_samples         , int sample_rate)      ;

  // getters/setters
#if ! PERSISTENCE_TRANSITION
  static bool   GetShouldAutoJoin() ;              // TODO: persistent config            (issue #6)
  static String GetServer() ;                      // TODO: persistent config            (issue #6)
  static String GetLogin() ;                       // TODO: persistent config per Server (issue #6)
  static String GetPass() ;                        // TODO: persistent config per Server (issue #6)
  static bool   GetIsAnonymous() ;                 // TODO: persistent config per Server (issue #6)
  static bool   GetShouldAgree() ;                 // TODO: persistent config per Server (issue #6)
  static void   SetShouldAgree(bool shouldAgree) ; // TODO: persistent config per Server (issue #6)
  static void   SetIsAgreed(   bool isAgreed) ;
#else
  static bool IsAgreed() ;
#endif // PERSISTENCE_TRANSITION


  // chat helpers
  static void SendChat(String chat_text) ;
  static void HandleChatCommand(String chat_text) ;

  // misc helpers
  static void CleanSessionDir() ;


#if ! PERSISTENCE_TRANSITION
  static bool IsAgreed ; // TODO: ?? this exists only so OnLicense doesnt block (issue #14)
#else // PERSISTENCE_TRANSITION
  static LinJamConfig* Config ;
#endif // PERSISTENCE_TRANSITION

private:

  static audioStreamer*        Audio ;
  static MainContentComponent* Gui ;
  static NJClient*             Client ;
  static bool                  IsAudioEnabled ;
  static File                  SessionDir ;
#if ! PERSISTENCE_TRANSITION
  static bool   ShouldAutoJoin ; // TODO: persistent config            (issue #6)
  static String Server ;         // TODO: persistent config            (issue #6)
  static String Login ;          // TODO: persistent config per Server (issue #6)
  static String Pass ;           // TODO: persistent config per Server (issue #6)
  static bool   IsAnonymous ;    // TODO: persistent config per Server (issue #6)
  static bool   ShouldAgree ;    // TODO: persistent config per Server (issue #6)
#endif // PERSISTENCE_TRANSITION

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinJam) ;
} ;

#endif  // LINJAM_H_INCLUDED
