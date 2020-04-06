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

#ifndef _CONFIGCHANNEL_H_
#define _CONFIGCHANNEL_H_

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
                       public ButtonListener,
                       public ComboBoxListener
{
public:
    //==============================================================================
    ConfigChannel (ValueTree channel_store);
    ~ConfigChannel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



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

#endif // _CONFIGCHANNEL_H_
