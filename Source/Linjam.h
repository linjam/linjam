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
  static bool   GetShouldAutoJoin() ;              // TODO: persistent config
  static String GetServer() ;                      // TODO: persistent config
  static String GetLogin() ;                       // TODO: persistent config per Server
  static String GetPass() ;                        // TODO: persistent config per Server
  static bool   GetIsAnonymous() ;                 // TODO: persistent config per Server
  static bool   GetShouldAgree() ;                 // TODO: persistent config per Server
  static void   SetShouldAgree(bool shouldAgree) ; // TODO: persistent config per Server
  static void   SetIsAgreed(   bool isAgreed) ;

  // chat helpers
  static void SendChat(String chat_text) ;
  static void HandleChatCommand(String chat_text) ;

  // misc helpers
  static void CleanSessionDir() ;


  static bool IsAgreed ; // TODO: ?? this exists only so we dont block waiting for user
                         //       but we must instead attempt login in twice
                         //       once to get the license and again after agreed

private:

  static audioStreamer*        Audio ;
  static MainContentComponent* Gui ;
  static NJClient*             Client ;
  static bool                  IsAudioEnabled ;
  static File                  SessionDir ;

  static bool   ShouldAutoJoin ; // TODO: persistent config
  static String Server ;         // TODO: persistent config
  static String Login ;          // TODO: persistent config per Server
  static String Pass ;           // TODO: persistent config per Server
  static bool   IsAnonymous ;    // TODO: persistent config per Server
  static bool   ShouldAgree ;    // TODO: persistent config per Server
} ;

#endif  // LINJAM_H_INCLUDED
