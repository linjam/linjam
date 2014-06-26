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

#ifndef __JUCE_HEADER_EB46FF61849DA256__
#define __JUCE_HEADER_EB46FF61849DA256__


//[Headers]     -- You can add your own extra header files here --

#include "Channels.h"
#include "JuceHeader.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Mixer  : public Component,
               public ButtonListener
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
  void        positionResizers() ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ScopedPointer<Channels>               masterChannels ;
  ScopedPointer<Channels>               localChannels ;
  ScopedPointer<TextButton>             prevScrollButton ;
  ScopedPointer<TextButton>             nextScrollButton ;
  ScopedPointer<ResizableEdgeComponent> localsResizer ;
  ScopedPointer<ResizableEdgeComponent> mastersResizer ;


  uint8 scrollZ ;


  void        buttonClicked(      Button* buttonThatWasClicked) override ;
  TextButton* addScrollButton(    String button_id) ;
  Channels*   addChannels(        String mixer_group_id) ;
  int         getNumDynamicMixers() ;
  int         getLocalsResizerNextX() ;
  int         getMastersResizerNextX() ;

    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mixer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_EB46FF61849DA256__
