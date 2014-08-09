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

#ifndef __JUCE_HEADER_CB08A39AD889D82__
#define __JUCE_HEADER_CB08A39AD889D82__

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
class ConfigClient  : public Component,
                      public ComboBoxListener,
                      public ButtonListener
{
public:
    //==============================================================================
    ConfigClient (ValueTree config_store);
    ~ConfigClient();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree configStore ;


  void setConfig(Identifier a_key , var a_value) ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> saveAudioLabel;
    ScopedPointer<ComboBox> saveAudioComboBox;
    ScopedPointer<ToggleButton> oggMixdownButton;
    ScopedPointer<ToggleButton> wavMixdownButton;
    ScopedPointer<Label> debugLevelLabel;
    ScopedPointer<ComboBox> debugLevelComboBox;
    ScopedPointer<ToggleButton> saveLogButton;
    ScopedPointer<ToggleButton> hideBotsButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigClient)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_CB08A39AD889D82__
