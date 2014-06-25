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

#ifndef _CHANNEL_H_
#define _CHANNEL_H_


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
class Channel  : public Component,
                 public ButtonListener,
                 public SliderListener
{
public:
    //==============================================================================
    Channel (ValueTree channel_config);
    ~Channel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  void updateChannelVU(double vu) ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree configStore ;


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
    ScopedPointer<TextButton> removeButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Channel)
};

//[EndFile] You can add extra defines here...

// TODO: subclass ChannelComponent (eliminating mixergroup_id and xmit_rcv_text) (issue #29)

//[/EndFile]

#endif // _CHANNEL_H_
