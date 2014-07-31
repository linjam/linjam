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

#ifndef __JUCE_HEADER_345EFA79F96DC706__
#define __JUCE_HEADER_345EFA79F96DC706__

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
class ConfigNinjam  : public Component,
                      public ComboBoxListener,
                      public ButtonListener
{
public:
    //==============================================================================
    ConfigNinjam ();
    ~ConfigNinjam();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ComboBox> saveAudioComboBox;
    ScopedPointer<Label> saveAudioLabel;
    ScopedPointer<Label> debugLevelLabel;
    ScopedPointer<ComboBox> debugLevelComboBox;
    ScopedPointer<ToggleButton> saveLogButton;
    ScopedPointer<ToggleButton> hideBotsButton;
    ScopedPointer<ToggleButton> saveLogButton2;
    ScopedPointer<ToggleButton> hideBotsButton2;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigNinjam)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_345EFA79F96DC706__
