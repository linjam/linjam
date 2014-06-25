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

#ifndef _LICENSE_H_
#define _LICENSE_H_


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
    License ();
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
  void setLicenseText(String license_text) ;
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

#endif // _LICENSE_H_
