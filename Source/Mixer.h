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

#ifndef _MIXER_H_
#define _MIXER_H_


//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"
#include "Channels.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Mixer  : public Component
{
public:
    //==============================================================================
    Mixer ();
    ~Mixer();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  Channels*   getRemoteChannelsGroup(Identifier user_id) ;
  void        addChannel(            Identifier mixergroup_id ,
                                     ValueTree  channel_store) ;
  void        updateChannelVU(       Identifier mixergroup_id ,
                                     String     channel_id    , double vu) ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  Channels* masterChannels;
  Channels* localChannels;


  Channels* addChannels(String mixer_group_id) ;

    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mixer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // _MIXER_H_
