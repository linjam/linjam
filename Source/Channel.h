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

#ifndef _CHANNEL_H_
#define _CHANNEL_H_

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  instances of Channel represent individual mixer channel slices
  they are contained within a Channels group
                                                                    //[/Comments]
*/
class Channel  : public Component,
                 public Button::Listener,
                 public Slider::Listener,
                 public Value::Listener,
                 public Label::Listener
{
public:
    //==============================================================================
    Channel (ValueTree channel_store);
    ~Channel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

#if DEBUG
friend class Channels ;
#endif // DEBUG

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void labelTextChanged (Label* labelThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  Value channelName ;
  Value stereoStatus ;
  Value vuLeft ;
  Value vuRight ;


  void  buttonClicked(Button* a_button) override ;
  void  valueChanged( Value& a_value)   override ;
  void  updateVU(     Slider* a_vu_slider , Label* a_vu_label , Value vu_var) ;
  void  setConfig(    Identifier a_key , var a_value) ;


protected:

  ValueTree channelStore ;


  bool handleButtonClicked(Button* a_button) ;
  void setStereoState() ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ToggleButton> xmitButton;
    ScopedPointer<ToggleButton> muteButton;
    ScopedPointer<ToggleButton> soloButton;
    ScopedPointer<TextButton> removeButton;
    ScopedPointer<TextButton> configButton;
    ScopedPointer<Slider> panSlider;
    ScopedPointer<Slider> gainSlider;
    ScopedPointer<Label> nameLabel;
    ScopedPointer<Label> stereoLabel;
    ScopedPointer<Slider> vuLeftSlider;
    ScopedPointer<Slider> vuRightSlider;
    ScopedPointer<Label> vuLeftLabel;
    ScopedPointer<Label> vuRightLabel;


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

  void buttonClicked(Button* a_button) ;
} ;

class RemoteChannel : public Channel
{
  friend class RemoteChannels ;

  RemoteChannel(ValueTree channel_store) ;
} ;

//[/EndFile]

#endif // _CHANNEL_H_
