/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "BlankComponent.h"
#include "LoginComponent.h"
#include "LicenseComponent.h"
#include "ChatComponent.h"
#include "MixerComponent.h"
#include "StatusBarComponent.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent : public Component
{
  friend class LinJam ;

public:
  //==============================================================================
  MainContentComponent() ;
  ~MainContentComponent() ;

  void paint(Graphics&) ;
  void resized() ;

#ifdef DEBUG_LICENSE_MULTITHREADED // TODO: (issue #14)
  bool prompt_license(String license_text) ;
#endif // DEBUG_LICENSE_MULTITHREADED

private:

  ScopedPointer<BlankComponent>     blankComponent ;
  ScopedPointer<LoginComponent>     loginComponent ;
  ScopedPointer<LicenseComponent>   licenseComponent ;
  ScopedPointer<ChatComponent>      chatComponent ;
  ScopedPointer<MixerComponent>     mixerComponent ;
  ScopedPointer<StatusBarComponent> statusbarComponent ;

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
} ;

#endif // MAINCOMPONENT_H_INCLUDED
