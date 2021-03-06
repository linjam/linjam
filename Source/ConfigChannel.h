/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_87598446A41E477A__
#define __JUCE_HEADER_87598446A41E477A__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ConfigChannel  : public Component,
                       public ButtonListener,
                       public ComboBoxListener
{
public:
    //==============================================================================
    ConfigChannel (ValueTree config_store);
    ~ConfigChannel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  void   buttonClicked(             Button* a_button) ;
  String makeMonoSelectOption(      int channel_n) ;
  String makeStereoSelectOption(    int channel_n) ;
  void   createChannelSelectOptions() ;
  void   populateChannelSelect() ;


  SortedSet<int> freeAudioSourceNs ;
  SortedSet<int> freeAudioSourcePairNs ;
  StringArray    freeAudioSourceOptions ;
  StringArray    freeAudioSourcePairOptions ;
  ValueTree      configStore ;
  bool           isNewChannel ;
  int            sourceN ;
  bool           isStereo ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> nameLabel;
    ScopedPointer<TextEditor> nameText;
    ScopedPointer<ToggleButton> monoButton;
    ScopedPointer<ToggleButton> stereoButton;
    ScopedPointer<Label> inputLabel;
    ScopedPointer<ComboBox> channelSelect;
    ScopedPointer<TextButton> okButton;
    ScopedPointer<TextButton> cancelButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigChannel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_87598446A41E477A__
