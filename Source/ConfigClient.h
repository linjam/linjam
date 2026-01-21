/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.12

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

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
                      public juce::ComboBox::Listener,
                      public juce::Button::Listener
{
public:
    //==============================================================================
    ConfigClient (ValueTree client_store);
    ~ConfigClient() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree clientStore ;


  void setConfig(Identifier a_key , var a_value) ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> saveAudioLabel;
    std::unique_ptr<juce::ComboBox> saveAudioComboBox;
    std::unique_ptr<juce::ToggleButton> oggMixdownButton;
    std::unique_ptr<juce::ToggleButton> wavMixdownButton;
    std::unique_ptr<juce::Label> debugLevelLabel;
    std::unique_ptr<juce::ComboBox> debugLevelComboBox;
    std::unique_ptr<juce::ToggleButton> saveLogButton;
    std::unique_ptr<juce::ToggleButton> hideBotsButton;
    std::unique_ptr<juce::TextButton> cleanButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigClient)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

