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

#include "Background.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Background::Background ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    setName ("Background");
    progressBar.reset (new ProgressBar (this->spinnerProgress, ProgressBar::Style::circular));
    addAndMakeVisible (progressBar.get());
    progressBar->setName ("progressBar");

    spinnerLabel.reset (new juce::Label ("spinnerLabel",
                                         TRANS ("Logging Out ...")));
    addAndMakeVisible (spinnerLabel.get());
    spinnerLabel->setFont (juce::Font (24.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
    spinnerLabel->setJustificationType (juce::Justification::centred);
    spinnerLabel->setEditable (false, false, false);
    spinnerLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    spinnerLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (790, 470);


    //[Constructor] You can add your own custom stuff here..

  this->progressBar->setColour(ProgressBar::foregroundColourId , Colour(0xFF8080FF)) ;
  this->progressBar->setColour(ProgressBar::backgroundColourId , Colour(0xFFFF0000)) ;

  this->progressBar->setPercentageDisplay(false) ;

  // hide spinner by default
  this->progressBar ->setVisible(false) ;
  this->spinnerLabel->setVisible(false) ;

    //[/Constructor]
}

Background::~Background()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    progressBar = nullptr;
    spinnerLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Background::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff202020));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Background::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    progressBar->setBounds ((getWidth() / 2) - (256 / 2), (getHeight() / 2) - (256 / 2), 256, 256);
    spinnerLabel->setBounds ((getWidth() / 2) - (256 / 2), (getHeight() / 2) - (24 / 2), 256, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Background" componentName="Background"
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="790" initialHeight="470">
  <BACKGROUND backgroundColour="ff202020"/>
  <GENERICCOMPONENT name="progressBar" id="de373a8913a42503" memberName="progressBar"
                    virtualName="" explicitFocusOrder="0" pos="0Cc 0Cc 256 256" class="ProgressBar"
                    params="this-&gt;spinnerProgress, ProgressBar::Style::circular"/>
  <LABEL name="spinnerLabel" id="1fff84ce88afe330" memberName="spinnerLabel"
         virtualName="" explicitFocusOrder="0" pos="0Cc 0Cc 256 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Logging Out ..." editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="24.0" kerning="0.0" bold="1" italic="0" justification="36"
         typefaceStyle="Bold"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

