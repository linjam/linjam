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
  ConfigAudio is a tab of the configuration screen
  it instantiates and configures the current AudioStreamer
                                                                    //[/Comments]
*/
class ConfigAudio  : public Component,
                     public juce::Button::Listener,
                     public juce::ComboBox::Listener,
                     public juce::Slider::Listener
{
public:
    //==============================================================================
    ConfigAudio (ValueTree audio_store);
    ~ConfigAudio() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  friend class Config ;

    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree audioStore ;


  void loadParams() ;
  void populateDevices() ;
  void restoreDefaults() ;
  void disableComponents() ;
  void enableComponents() ;
#ifdef _WIN32
  bool queryAsioDevices() ;
  bool queryKsDevices() ;
  bool queryDsDevices() ;
  bool queryWaveDevices() ;
#else // _WIN32
#  ifdef _MAC
  bool queryCaDevices() ;
#  else // _MAC
  bool queryJackServers() ;
  bool queryAlsaDevices() ;
#  endif // _MAC
#endif // _WIN32
  int  getItemIndex( ComboBox* combo_box , String item_text) ;
  void updateLatency() ;
  void setConfig(    Identifier a_key , var a_value) ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::GroupComponent> ioGroup;
    std::unique_ptr<juce::GroupComponent> formatGroup;
    std::unique_ptr<juce::GroupComponent> buffersGroup;
    std::unique_ptr<juce::GroupComponent> routingGroup;
    std::unique_ptr<juce::TextButton> defaultsButton;
    std::unique_ptr<juce::TextButton> asioButton;
    std::unique_ptr<juce::Label> modeLabel;
    std::unique_ptr<juce::ComboBox> apiComboBox;
    std::unique_ptr<juce::Label> driverLabel;
    std::unique_ptr<juce::ComboBox> driverComboBox;
    std::unique_ptr<juce::Label> sourceLabel;
    std::unique_ptr<juce::ComboBox> sourceComboBox;
    std::unique_ptr<juce::Label> sinkLabel;
    std::unique_ptr<juce::ComboBox> sinkComboBox;
    std::unique_ptr<juce::Label> bitdepthLabel;
    std::unique_ptr<juce::ToggleButton> bps16Button;
    std::unique_ptr<juce::ToggleButton> bps24Button;
    std::unique_ptr<juce::ToggleButton> bps32Button;
    std::unique_ptr<juce::Label> samplerateLabel;
    std::unique_ptr<juce::ToggleButton> kHz44Button;
    std::unique_ptr<juce::ToggleButton> kHz48Button;
    std::unique_ptr<juce::ToggleButton> kHz96Button;
    std::unique_ptr<juce::Label> buffersLabel;
    std::unique_ptr<juce::Slider> nBuffersSlider;
    std::unique_ptr<juce::Label> xLabel;
    std::unique_ptr<juce::ComboBox> bufferComboBox;
    std::unique_ptr<juce::Label> bytesLabel;
    std::unique_ptr<juce::Label> jackNameLabel;
    std::unique_ptr<juce::TextEditor> jackNameText;
    std::unique_ptr<juce::Label> nSourcesLabel;
    std::unique_ptr<juce::Slider> nSourcesSlider;
    std::unique_ptr<juce::Label> nSinksLabel;
    std::unique_ptr<juce::Slider> nSinksSlider;
    std::unique_ptr<juce::ToggleButton> jackPortsButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigAudio)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

