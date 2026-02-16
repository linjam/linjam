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

#include <JuceHeader.h>

#include "Constants.h"
#include "Vote.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  Toolbox is a sub-section of the main jam "screen"
  it displays the room topic and hosts controls to
  change the topic and to vote for BPM/BPI change
                                                                    //[/Comments]
*/
class Toolbox  : public juce::Component,
                 public juce::Label::Listener
{
public:
    //==============================================================================
    Toolbox ();
    ~Toolbox() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  friend class LinJam ;

    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void labelTextChanged (juce::Label* labelThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  String prevTopicText ;

  void setTopic(String topic_text) ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> topicLabel;
    std::unique_ptr<Vote> vote;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Toolbox)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

