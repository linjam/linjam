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
  ConfigBlacklist is a tab of the configuration screen
  it configures options specific to the NJClient subscriptions list
                                                                    //[/Comments]
*/
class ConfigBlacklist  : public Component,
                         public juce::Button::Listener
{
public:
    //==============================================================================
    ConfigBlacklist (ValueTree blacklist_store);
    ~ConfigBlacklist() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree blacklistStore ;


  void setConfig(Identifier a_key , var a_value) ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::ToggleButton> subscribeButton;
    std::unique_ptr<juce::ToggleButton> ignoreButton;
    std::unique_ptr<juce::Label> bansLabel;
    std::unique_ptr<juce::Viewport> blacklistViewport;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigBlacklist)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

