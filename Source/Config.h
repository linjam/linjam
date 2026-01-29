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

#include "ConfigAudio.h"
#include "ConfigClient.h"
#include "ConfigGui.h"
#include "ConfigBlacklist.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  Config is the configuration screen
  specific configuration options are distriibuted across several tabs
                                                                    //[/Comments]
*/
class Config  : public Component,
                public Value::Listener
{
public:
    //==============================================================================
    Config (ValueTree audio_store, ValueTree client_store, ValueTree gui_store, ValueTree blacklist_store, Value linjam_status);
    ~Config() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

//   ConfigAudio*     configAudio ;
//   ConfigClient*    configClient ;
//   ConfigGui*       configGui ;
//   ConfigBlacklist* configBlacklist ;
  UPTR<ConfigAudio>     configAudio ;
  UPTR<ConfigClient>    configClient ;
  UPTR<ConfigGui>       configGui ;
  UPTR<ConfigBlacklist> configBlacklist ;


  void valueChanged(Value& a_value) ;


  Value linjamStatus ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::TabbedComponent> configTabs;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Config)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

