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

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Vote  : public juce::Component,
              public juce::Label::Listener
{
public:
    //==============================================================================
    Vote ();
    ~Vote() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  friend class LinJam ;

    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void labelTextChanged (juce::Label* labelThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  bool  isVoting       = false ;
  uint8 voteBpiPending = 0 ;
  uint8 voteBpmPending = 0 ;

  // business
  void setBpi(uint8 bpi , bool should_cancel_vote) ;
  void setBpm(uint8 bpm , bool should_cancel_vote) ;

  // event handlers
  void editorShown( Label* vote_label , TextEditor& /*unused*/) override ;
  void editorHidden(Label* vote_label , TextEditor& /*unused*/) override ;

  // helpers
  void vote(String vote , Label* vote_label) ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> bpiLabel;
    std::unique_ptr<juce::Label> bpmLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Vote)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

