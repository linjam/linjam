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

#ifndef _CONFIGBLACKLIST_H_
#define _CONFIGBLACKLIST_H_

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  ConfigBlacklist is a tab of the configuration screen
  it configures options specific to the NJClient subscriptions list
                                                                    //[/Comments]
*/
class ConfigBlacklist  : public Component,
                         public ButtonListener
{
public:
    //==============================================================================
    ConfigBlacklist (ValueTree blacklist_store);
    ~ConfigBlacklist();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree blacklistStore ;


  void setConfig(Identifier a_key , var a_value) ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ToggleButton> subscribeButton;
    ScopedPointer<ToggleButton> ignoreButton;
    ScopedPointer<Label> bansLabel;
    ScopedPointer<Viewport> blacklistViewport;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigBlacklist)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // _CONFIGBLACKLIST_H_
