/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "LoginComponent.h"
#include "LicenseComponent.h"
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

//   bool prompt_license(String license_text) ;

private:

  ScopedPointer<LoginComponent>     loginComponent ;
  ScopedPointer<LicenseComponent>   licenseComponent ;
  ScopedPointer<StatusBarComponent> statusComponent ;

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
} ;

#endif // MAINCOMPONENT_H_INCLUDED
