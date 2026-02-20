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

#include "Channel.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  Channels is the abstract superclass of channel mixergroups:
      LocalChannels, RemoteChannels, MasterChannels
      which are containers for related Channel slices of Mixer
                                                                    //[/Comments]
*/
class Channels  : public Component
{
public:
    //==============================================================================
    Channels ();
    ~Channels() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  bool addChannel(    ValueTree  channel_store) ;
  void removeChannel( Identifier channel_id) ;
  int  getNumChannels() ;

    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.


protected:

  virtual Channel* newChannel(ValueTree  channel_store) = 0 ;
          Channel* getChannel(Identifier channel_id) ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> loginLabel;
    std::unique_ptr<juce::TextButton> addButton;
    std::unique_ptr<juce::TextButton> expandButton;
    std::unique_ptr<juce::TextButton> ignoreButton;


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
  Channel* newChannel(   ValueTree channel_store) override ;
} ;


class LocalChannels : public Channels , public Button::Listener
{
public:

  LocalChannels() ;


private:

  void     buttonClicked(Button* buttonThatWasClicked) ;
  Channel* newChannel(   ValueTree channel_store) override ;
} ;


class RemoteChannels : public Channels , public Button::Listener
{
public:

  RemoteChannels(ValueTree user_store , ValueTree blacklist_store) ;


private:

  ValueTree userStore ;
  ValueTree blacklistStore ;
  bool      isExpanded ;


  void     buttonClicked(       Button* buttonThatWasClicked) ;
  void     toggleExpandChannels() ;
  void     addUserToBlacklist() ;
  Channel* newChannel(          ValueTree channel_store) override ;
} ;

//[/EndFile]

