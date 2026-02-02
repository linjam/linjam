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
  License is the per-server license presentation and configuration "screen"
                                                                    //[/Comments]
*/
class License  : public Component,
                 public Value::Listener,
                 public juce::Button::Listener
{
public:
    //==============================================================================
    License (Value is_agreed, Value always_agree);
    ~License() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  friend class LinJam ;

    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  Value isAgreed ;
  Value alwaysAgree ;


  void valueChanged(  Value& a_value) override ;
  void setLicenseText(String license_text) ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::TextEditor> licenseTextEditor;
    std::unique_ptr<juce::TextButton> cancelButton;
    std::unique_ptr<juce::TextButton> agreeButton;
    std::unique_ptr<juce::ToggleButton> alwaysButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (License)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

