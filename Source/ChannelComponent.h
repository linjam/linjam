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

#ifndef __JUCE_HEADER_2B00F310AD58FBC0__
#define __JUCE_HEADER_2B00F310AD58FBC0__

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"


class ChannelConfig ;

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ChannelComponent  : public Component,
                          public ButtonListener,
                          public SliderListener
{
public:
    //==============================================================================
    ChannelComponent (ChannelConfig* channel_config);
    ~ChannelComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  void updateChannelVU(float vu) ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  void setChannelConfig(Identifier config_key , var value) ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ToggleButton> xmitButton;
    ScopedPointer<ToggleButton> muteButton;
    ScopedPointer<ToggleButton> soloButton;
    ScopedPointer<Slider> panSlider;
    ScopedPointer<Slider> vuSlider;
    ScopedPointer<Slider> gainSlider;
    ScopedPointer<Label> vuLabel;
    ScopedPointer<Label> gainLabel;
    ScopedPointer<Label> nameLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelComponent)
};

//[EndFile] You can add extra defines here...

class ChannelConfig
{
public:

    ChannelConfig(String channel_id      , bool   is_xmit_enabled ,
                  bool   is_solo_enabled , String xmit_rcv_text   ,
                  double volume          , double pan             ,
                  bool   is_xmit         , bool   is_muted        ,
                  bool   is_solo         , int    source_ch       ,
                  bool   is_stereo)
    {
      this->channel_id      = channel_id ;
      this->is_xmit_enabled = is_xmit_enabled ;
      this->is_solo_enabled = is_solo_enabled ;
      this->xmit_rcv_text   = xmit_rcv_text ;
      this->volume          = volume ;
      this->pan             = pan ;
      this->is_xmit         = is_xmit ;
      this->is_muted        = is_muted ;
      this->is_solo         = is_solo ;
      this->source_ch       = source_ch ;
      this->is_stereo       = is_stereo ;
    }

    ~ChannelConfig() ;

    String channel_id ;
    bool   is_xmit_enabled ;
    bool   is_solo_enabled ;
    String xmit_rcv_text ;
    double volume ;
    double pan ;
    bool   is_xmit ;
    bool   is_muted ;
    bool   is_solo ;
    int    source_ch ;
    bool   is_stereo ;
} ;

//[/EndFile]

#endif   // __JUCE_HEADER_2B00F310AD58FBC0__
