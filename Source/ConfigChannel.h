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

