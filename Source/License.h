/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_B211D150B4BBC96A__
#define __JUCE_HEADER_B211D150B4BBC96A__

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
class License  : public Component,
                 public ButtonListener
{
public:
    //==============================================================================
    License (ValueTree login_store);
    ~License();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  friend class LinJam ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree loginStore ;


  void setLicenseText(String license_text) ;
  void setConfig(     Identifier a_key , var a_value) ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextEditor> licenseTextEditor;
    ScopedPointer<TextButton> cancelButton;
    ScopedPointer<TextButton> agreeButton;
    ScopedPointer<ToggleButton> alwaysButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (License)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_B211D150B4BBC96A__
