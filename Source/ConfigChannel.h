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
  ConfigChannel is the instantiation and configurations dialog
      for individual mixer slices
                                                                    //[/Comments]
*/
class ConfigChannel  : public Component,
                       public Button::Listener,
                       public juce::ComboBox::Listener
{
public:
    //==============================================================================
    ConfigChannel (ValueTree channel_store);
    ~ConfigChannel() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree      channelStore ;
  SortedSet<int> freeAudioSourceNs ;
  SortedSet<int> freeAudioSourcePairNs ;
  StringArray    freeAudioSourceOptions ;
  StringArray    freeAudioSourcePairOptions ;
  bool           isNewChannel ;
  int            sourceN ;
  bool           isStereo ;


  void   buttonClicked(             Button* a_button) ;
  String makeMonoSelectOption(      int channel_n) ;
  String makeStereoSelectOption(    int channel_n) ;
  void   createChannelSelectOptions() ;
  void   populateChannelSelect() ;
  void   refreshHardwareChannels() ;
  void   configureLocalChannel() ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> nameLabel;
    std::unique_ptr<juce::TextEditor> nameText;
    std::unique_ptr<juce::ToggleButton> monoButton;
    std::unique_ptr<juce::ToggleButton> stereoButton;
    std::unique_ptr<juce::Label> inputLabel;
    std::unique_ptr<juce::ComboBox> channelSelect;
    std::unique_ptr<juce::TextButton> okButton;
    std::unique_ptr<juce::TextButton> cancelButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigChannel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

