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

#ifndef _MIXER_H_
#define _MIXER_H_

//[Headers]     -- You can add your own extra header files here --

#include "Channels.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  Mixer is a sub-section of the main jam "screen"
  it is the container for Channels channel groups
     each of which contain a number of individual Channel mixer slices
                                                                    //[/Comments]
*/
class Mixer  : public Component,
               public Button::Listener
{
public:
    //==============================================================================
    Mixer (ValueTree blacklist_store);
    ~Mixer();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  bool addRemoteUser(   ValueTree user_store) ;
  bool addChannel(      Identifier channels_id , ValueTree channel_store) ;
  void removeChannel(   Identifier channels_id , Identifier channel_id) ;
  void positionResizers() ;
  void pruneRemotes(    ValueTree active_users) ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ScopedPointer<MasterChannels>         masterChannels ;
  ScopedPointer<LocalChannels>          localChannels ;
  ScopedPointer<TextButton>             prevScrollButton ;
  ScopedPointer<TextButton>             nextScrollButton ;
  ScopedPointer<ResizableEdgeComponent> localsResizer ;
  ScopedPointer<ResizableEdgeComponent> mastersResizer ;

  ValueTree blacklistStore ;
  uint8     scrollZ ;


  void      buttonClicked(         Button* buttonThatWasClicked) override ;
  void      addChannels(           Channels* channels , Identifier channels_id) ;
  void      removeChannels(        Channels* channels) ;
  void      addScrollButton(       TextButton* scroll_button , String button_text) ;
  void      addResizer(            ResizableEdgeComponent* resizer) ;
  Channels* getChannels(           Identifier channels_id) ;
  int       getNumDynamicMixers() ;
  int       getLocalsResizerNextX() ;
  int       getMastersResizerNextX() ;

    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mixer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // _MIXER_H_
