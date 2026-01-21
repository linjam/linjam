/*\
|*|  Copyright 2014,2015,2020,2026 bill-auger <bill-auger@programmer.net>
|*|
|*|  This file is part of the LinJam program.
|*|
|*|  LinJam is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  LinJam is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU General Public License for more details.
|*|
|*|  You should have received a copy of the GNU General Public License
|*|  along with LinJam.  If not, see <http://www.gnu.org/licenses/>.
\*/


#pragma once

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
    ~Mixer() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  bool addRemoteUser(   ValueTree user_store) ;
  bool addChannel(      Identifier channels_id , ValueTree channel_store) ;
  void removeChannel(   Identifier channels_id , Identifier channel_id) ;
  void positionResizers() ;
  void pruneRemotes(    ValueTree active_users) ;

    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;



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

