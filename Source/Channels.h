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

#ifndef _CHANNELS_H_
#define _CHANNELS_H_

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "Channel.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Channels  : public Component,
                  public ButtonListener
{
public:
    //==============================================================================
    Channels (String channels_id);
    ~Channels();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  void addChannel(     ValueTree channel_store) ;
  int  getNumChannels() ;
  void updateChannelVU(String channel_id , double vu) ;

// ResizableEdgeComponent* resizer ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> channelsLabel;
    ScopedPointer<TextButton> addButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Channels)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // _CHANNELS_H_
