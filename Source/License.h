/*\
|*|  Copyright 2014,2015,2020,2026 bill-auger <bill-auger@programmer.net>
|*|
|*|  This file is part of the LinJam program.
|*|
|*|  LinJam is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  LinJam is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU General Public License for more details.
|*|
|*|  You should have received a copy of the GNU General Public License
|*|  along with LinJam.  If not, see <http://www.gnu.org/licenses/>.
\*/


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

