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

#ifndef __JUCE_HEADER_321A28830126E8DE__
#define __JUCE_HEADER_321A28830126E8DE__

//[Headers]     -- You can add your own extra header files here --
/*
#if DEBUG
#  include "Trace.h"
#endif // DEBUG
*/

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
    Channel (ValueTree channel_store);
    ~Channel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
/*
#if DEBUG_TRACE
  friend class Trace ;
#endif // DEBUG_TRACE
*/
  void updateChannelVU(double vu) ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

protected:

  ValueTree configStore ;


  void buttonClicked(   Button* a_button) ;
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

class MasterChannel : public Channel
{
  friend class MasterChannels ;

  MasterChannel(ValueTree channel_store) ;
} ;

class LocalChannel  : public Channel
{
  friend class LocalChannels ;

  LocalChannel(ValueTree channel_store) ;
} ;

class RemoteChannel : public Channel
{
  friend class RemoteChannels ;

  RemoteChannel(ValueTree channel_store) ;
} ;

//[/EndFile]

#endif   // __JUCE_HEADER_321A28830126E8DE__
