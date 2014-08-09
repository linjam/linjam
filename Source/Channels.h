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

  bool addChannel(    ValueTree channel_store) ;
  void removeChannel( Identifier channel_id) ;
  int  getNumChannels() ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.


protected:

  virtual Channel* newChannel(ValueTree channel_store) = 0 ;
          Channel* getChannel(Identifier channel_id) ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> channelsLabel;
    ScopedPointer<TextButton> addButton;
    ScopedPointer<TextButton> expandButton;
    ScopedPointer<TextButton> ignoreButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Channels)
};

//[EndFile] You can add extra defines here...

class MasterChannels : public Channels
{
public:

  MasterChannels() ;


private:

  void     buttonClicked(Button* buttonThatWasClicked) ;
  Channel* newChannel(ValueTree channel_store) override ;
} ;


class LocalChannels : public Channels , public ButtonListener
{
public:

  LocalChannels() ;


private:

  void     buttonClicked(Button* buttonThatWasClicked) ;
  Channel* newChannel(   ValueTree channel_store) override ;
} ;


class RemoteChannels : public Channels , public ButtonListener
{
public:

  RemoteChannels(ValueTree user_store , ValueTree subscriptions) ;


private:

  ValueTree configStore ;
  ValueTree subscriptions ;
  bool      isExpanded ;


  void     buttonClicked(       Button* buttonThatWasClicked) ;
  void     toggleExpandChannels() ;
  Channel* newChannel(          ValueTree channel_store) override ;
} ;

//[/EndFile]

#endif   // __JUCE_HEADER_8B661D82CCFDE918__
