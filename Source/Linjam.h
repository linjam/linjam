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
  friend class ClientTimer ;

public:

//   static int  Initialize( NJClient* client , const String& args) ;
  static bool Initialize(NJClient* client , MainContentComponent* mainGUI ,
                         const String& args) ;
  static void Connect() ;
  static void Disconnect() ;
  static void Shutdown() ;

  // getters/setters
  static bool   GetShouldAutoJoin() ;              // TODO: persistent config
  static String GetServer() ;                      // TODO: persistent config
  static String GetLogin() ;                       // TODO: persistent config per Server
  static String GetPass() ;                        // TODO: persistent config per Server
  static bool   GetIsAnonymous() ;                 // TODO: persistent config per Server
  static bool   GetShouldAgree() ;                 // TODO: persistent config per Server
  static void   SetShouldAgree(bool shouldAgree) ; // TODO: persistent config per Server
  static void   SetIsAgreed(   bool isAgreed) ;

  // NJClient callbacks
  static int  OnLicense(int user32 , char* license_text) ;
  static void OnChatmsg(int user32 , NJClient* instance ,
                        const char** parms , int nparms) ;
  static void OnSamples(float** in_buffer , int in_n_channels ,
                        float** out_buffer , int out_n_channels ,
                        int len , int sample_rate) ;
/*
  static void OnUnderflow() ;
  static void OnOverflow() ;
*/

  static bool IsAgreed ;

private:

  static audioStreamer*        Audio  ;
  static NJClient*             Client ;
  static MainContentComponent* Gui ;

  static bool   ShouldAutoJoin ; // TODO: persistent config
  static String Server ;         // TODO: persistent config
  static String Login ;          // TODO: persistent config per Server
  static String Pass ;           // TODO: persistent config per Server
  static bool   IsAnonymous ;    // TODO: persistent config per Server
  static bool   ShouldAgree ;    // TODO: persistent config per Server
} ;

#endif  // LINJAM_H_INCLUDED
