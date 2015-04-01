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

#ifndef _CONFIGGUI_H_
#define _CONFIGGUI_H_

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
                   public ComboBoxListener
{
public:
    //==============================================================================
    ConfigGui (ValueTree gui_store);
    ~ConfigGui();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree guiStore ;


  void setConfig(Identifier a_key , var a_value) ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> mixerGroup;
    ScopedPointer<GroupComponent> chatGroup;
    ScopedPointer<Label> fontsizeLabel;
    ScopedPointer<Label> updateLabel;
    ScopedPointer<ComboBox> updateComboBox;
    ScopedPointer<ComboBox> fontsizeComboBox;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigGui)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // _CONFIGGUI_H_
