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

#include "LoopComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
LoopComponent::LoopComponent ()
{
    addAndMakeVisible (progressSlider = new Slider ("progressSlider"));
    progressSlider->setRange (0, 32, 1);
    progressSlider->setSliderStyle (Slider::LinearBar);
    progressSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    progressSlider->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (256, 16);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

LoopComponent::~LoopComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    progressSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void LoopComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void LoopComponent::resized()
{
    progressSlider->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void LoopComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == progressSlider)
    {
        //[UserSliderCode_progressSlider] -- add your slider handling code here..
        //[/UserSliderCode_progressSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void LoopComponent::updateBeat(int beat_n) { this->progressSlider->setValue(beat_n) ; }

void LoopComponent::updateBPI(int bpi) { this->progressSlider->setRange( 0 , bpi , 1) ; }

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="LoopComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="256" initialHeight="16">
  <BACKGROUND backgroundColour="0"/>
  <SLIDER name="progressSlider" id="b7584d379dc52155" memberName="progressSlider"
          virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" min="0"
          max="32" int="1" style="LinearBar" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
