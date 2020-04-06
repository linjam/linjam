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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "Loop.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Loop::Loop ()
{
    setName ("Loop");
    addAndMakeVisible (progressBar = new ProgressBar (this->loopProgress = 0.0));
    progressBar->setName ("progressBar");


    //[UserPreSize]

  progressBar->setColour(ProgressBar::backgroundColourId , Colour(0x00000000));

    //[/UserPreSize]

    setSize (256, 16);


    //[Constructor] You can add your own custom stuff here..
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
void Loop::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Loop::resized()
{
    progressBar->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void Loop::updateBeatN(int beat_n)
{
  this->progressBar->setTextToDisplay(String(beat_n)) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Loop" componentName="Loop"
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="256" initialHeight="16">
  <BACKGROUND backgroundColour="0"/>
  <GENERICCOMPONENT name="progressBar" id="de373a8913a42503" memberName="progressBar"
                    virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" class="ProgressBar"
                    params="this-&gt;loopProgress = 0.0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
