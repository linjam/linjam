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

#ifndef _CONFIGAUDIO_H_
#define _CONFIGAUDIO_H_

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
                     public Button::Listener,
                     public ComboBox::Listener,
                     public Slider::Listener
{
public:
    //==============================================================================
    ConfigAudio (ValueTree audio_store);
    ~ConfigAudio();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  friend class Config ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void sliderValueChanged (Slider* sliderThatWasMoved);



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
    ScopedPointer<GroupComponent> ioGroup;
    ScopedPointer<GroupComponent> formatGroup;
    ScopedPointer<GroupComponent> buffersGroup;
    ScopedPointer<GroupComponent> routingGroup;
    ScopedPointer<TextButton> defaultsButton;
    ScopedPointer<TextButton> asioButton;
    ScopedPointer<Label> modeLabel;
    ScopedPointer<ComboBox> apiComboBox;
    ScopedPointer<Label> driverLabel;
    ScopedPointer<ComboBox> driverComboBox;
    ScopedPointer<Label> sourceLabel;
    ScopedPointer<ComboBox> sourceComboBox;
    ScopedPointer<Label> sinkLabel;
    ScopedPointer<ComboBox> sinkComboBox;
    ScopedPointer<Label> bitdepthLabel;
    ScopedPointer<ToggleButton> bps16Button;
    ScopedPointer<ToggleButton> bps24Button;
    ScopedPointer<ToggleButton> bps32Button;
    ScopedPointer<Label> samplerateLabel;
    ScopedPointer<ToggleButton> kHz44Button;
    ScopedPointer<ToggleButton> kHz48Button;
    ScopedPointer<ToggleButton> kHz96Button;
    ScopedPointer<Label> buffersLabel;
    ScopedPointer<Slider> nBuffersSlider;
    ScopedPointer<Label> xLabel;
    ScopedPointer<ComboBox> bufferComboBox;
    ScopedPointer<Label> bytesLabel;
    ScopedPointer<Label> jackNameLabel;
    ScopedPointer<TextEditor> jackNameText;
    ScopedPointer<Label> nSourcesLabel;
    ScopedPointer<Slider> nSourcesSlider;
    ScopedPointer<Label> nSinksLabel;
    ScopedPointer<Slider> nSinksSlider;
    ScopedPointer<ToggleButton> jackPortsButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigAudio)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // _CONFIGAUDIO_H_
