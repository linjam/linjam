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


//[Headers] You can add your own extra header files here...
//[/Headers]

#include "Loop.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Loop::Loop ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    setName ("Loop");
    progressBar.reset (new ProgressBar (this->loopProgress , ProgressBar::Style::linear));
    addAndMakeVisible (progressBar.get());
    progressBar->setName ("progressBar");


    //[UserPreSize]

    //[/UserPreSize]

    setSize (256, 24);


    //[Constructor] You can add your own custom stuff here..

  this->progressBar->setColour(ProgressBar::foregroundColourId , Colour(0xFF8080FF)) ;
  this->progressBar->setColour(ProgressBar::backgroundColourId , Colour(0x00000000)) ;

  this->progressBar->setPercentageDisplay(false) ;

    //[/Constructor]
}

Loop::~Loop()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    progressBar = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Loop::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..

  UNUSED(g) ;

    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Loop::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    progressBar->setBounds (0, 0, getWidth() - 0, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* Loop private instance methods */

void Loop::updateBeatN(int beat_n)
{
  // NOTE: text is barely visible - setPercentageDisplay() disables text updates
  //       but only until setTextToDisplay() is called
  // return ;

  this->progressBar->setTextToDisplay(String(beat_n)) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Loop" componentName="Loop"
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="0" snapShown="0" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="256" initialHeight="24">
  <BACKGROUND backgroundColour="0"/>
  <GENERICCOMPONENT name="progressBar" id="de373a8913a42503" memberName="progressBar"
                    virtualName="" explicitFocusOrder="0" pos="0 0 0M 16" class="ProgressBar"
                    params="this-&gt;loopProgress , ProgressBar::Style::linear"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

