/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_F1008AB42F514BC4__
#define __JUCE_HEADER_F1008AB42F514BC4__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class LicenseComponent  : public Component,
                          public ButtonListener
{
public:
    //==============================================================================
    LicenseComponent ();
    ~LicenseComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
  friend class LinJam ;

//   bool getIsAgreed() ; // TODO: onvisibility set agreeState = pending (issue #14)
//     WaitableEvent* agreeEvent ;
//   ScopedPointer<WaitableEvent> agreeEvent ; bool isAgreed ;
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
  void setLicenseText(String license_text) ;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextEditor> licenseTextEditor;
    ScopedPointer<TextButton> cancelButton;
    ScopedPointer<TextButton> agreeButton;
    ScopedPointer<TextButton> alwaysButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LicenseComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_F1008AB42F514BC4__
