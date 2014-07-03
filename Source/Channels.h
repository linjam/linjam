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

#ifndef __JUCE_HEADER_8B661D82CCFDE918__
#define __JUCE_HEADER_8B661D82CCFDE918__

//[Headers]     -- You can add your own extra header files here --

#include "Channel.h"
#include "JuceHeader.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    This is the component superclass of channels mixergroups.

    It is a container for related Channel mixer slices
        with an expand/add button.
                                                                    //[/Comments]
*/
class Channels  : public Component
{
public:
    //==============================================================================
    Channels ();
    ~Channels();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  bool addChannel(     ValueTree channel_store) ;
  void removeChannel(  Channel* channel) ;
  int  getNumChannels() ;
  void updateChannelVU(String channel_id , double vu) ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  void broughtToFront() override ;


protected:

  virtual Channel* newChannel(ValueTree channel_store) {}

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> channelsLabel;
    ScopedPointer<TextButton> expandButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Channels)
};

//[EndFile] You can add extra defines here...

class MasterChannels : public Channels
{
public:

  MasterChannels() ;


private:

  Channel* newChannel(ValueTree channel_store) override ;
} ;


class LocalChannels : public Channels , public ButtonListener
{
public:

  LocalChannels() ;
  void removeChannel(Channel* channel) ;

private:

  void     buttonClicked(Button* buttonThatWasClicked) ;
  Channel* newChannel(   ValueTree channel_store) override ;
} ;


class RemoteChannels : public Channels , public ButtonListener
{
public:

  RemoteChannels(ValueTree user_store) ;


private:

  bool isExpanded ;


  void     buttonClicked(       Button* buttonThatWasClicked) ;
  void     toggleExpandChannels() ;
  Channel* newChannel(          ValueTree channel_store) override ;
} ;

//[/EndFile]

#endif   // __JUCE_HEADER_8B661D82CCFDE918__
