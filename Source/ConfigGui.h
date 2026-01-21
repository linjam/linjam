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
  ConfigGui is a tab of the configuration screen
  it configures options specific to the LinJam GUI
                                                                    //[/Comments]
*/
class ConfigGui  : public Component,
                   public juce::ComboBox::Listener
{
public:
    //==============================================================================
    ConfigGui (ValueTree gui_store);
    ~ConfigGui() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree guiStore ;


  void setConfig(Identifier a_key , var a_value) ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::GroupComponent> mixerGroup;
    std::unique_ptr<juce::GroupComponent> chatGroup;
    std::unique_ptr<juce::Label> fontsizeLabel;
    std::unique_ptr<juce::Label> updateLabel;
    std::unique_ptr<juce::ComboBox> updateComboBox;
    std::unique_ptr<juce::ComboBox> fontsizeComboBox;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigGui)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

