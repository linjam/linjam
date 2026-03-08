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
    std::unique_ptr<juce::Label> layourLabel;
    std::unique_ptr<juce::ComboBox> layoutComboBox;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigGui)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

