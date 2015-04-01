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

#ifndef _CONFIGCLIENT_H_
#define _CONFIGCLIENT_H_

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  ConfigClient is a tab of the configuration screen
  it configures misc options specific to the NJClient
      that are not otherwise on the ConfigAudio or ConfigBlacklist tabs
                                                                    //[/Comments]
*/
class ConfigClient  : public Component,
                      public ComboBoxListener,
                      public ButtonListener
{
public:
    //==============================================================================
    ConfigClient (ValueTree client_store);
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

  ValueTree clientStore ;


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
    ScopedPointer<TextButton> cleanButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigClient)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // _CONFIGCLIENT_H_
