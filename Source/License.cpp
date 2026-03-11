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

#include "LinJam.h"

//[/Headers]

#include "License.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
License::License (Value is_agreed, Value always_agree)
    : isAgreed(is_agreed), alwaysAgree(always_agree)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    setName ("License");
    licenseTextEditor.reset (new juce::TextEditor ("licenseTextEditor"));
    addAndMakeVisible (licenseTextEditor.get());
    licenseTextEditor->setMultiLine (true);
    licenseTextEditor->setReturnKeyStartsNewLine (false);
    licenseTextEditor->setReadOnly (true);
    licenseTextEditor->setScrollbarsShown (true);
    licenseTextEditor->setCaretVisible (false);
    licenseTextEditor->setPopupMenuEnabled (false);
    licenseTextEditor->setColour (juce::TextEditor::textColourId, juce::Colours::silver);
    licenseTextEditor->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0xff404040));
    licenseTextEditor->setText (juce::String());

    cancelButton.reset (new juce::TextButton ("cancelButton"));
    addAndMakeVisible (cancelButton.get());
    cancelButton->setTooltip (TRANS ("Check this if you do not agree to these above terms. You will not be able to jam here."));
    cancelButton->setExplicitFocusOrder (2);
    cancelButton->setButtonText (TRANS ("Cancel"));
    cancelButton->addListener (this);

    agreeButton.reset (new juce::TextButton ("agreeButton"));
    addAndMakeVisible (agreeButton.get());
    agreeButton->setTooltip (TRANS ("Check this to agree to the above terms for this session only."));
    agreeButton->setExplicitFocusOrder (1);
    agreeButton->setButtonText (TRANS ("Agree"));
    agreeButton->addListener (this);

    alwaysButton.reset (new juce::ToggleButton ("alwaysButton"));
    addAndMakeVisible (alwaysButton.get());
    alwaysButton->setTooltip (TRANS ("Check this to automatically agree to these terms on this server. You will not see this screen again unless the terms should change."));
    alwaysButton->setButtonText (TRANS ("Always Agree"));
    alwaysButton->addListener (this);
    alwaysButton->setColour (juce::ToggleButton::textColourId, juce::Colours::grey);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (622, 442);


    //[Constructor] You can add your own custom stuff here..

  this->alwaysAgree.addListener(this) ;

    //[/Constructor]
}

License::~License()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    licenseTextEditor = nullptr;
    cancelButton = nullptr;
    agreeButton = nullptr;
    alwaysButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void License::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 0.0f, y = 0.0f, width = static_cast<float> (getWidth() - 0), height = static_cast<float> (getHeight() - 0);
        juce::Colour fillColour = juce::Colour (0xff101010);
        juce::Colour strokeColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.000f);
    }

    {
        float x = 4.0f, y = 4.0f, width = static_cast<float> (getWidth() - 8), height = static_cast<float> (getHeight() - 36);
        juce::Colour fillColour = juce::Colours::black;
        juce::Colour strokeColour = juce::Colours::grey;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void License::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    licenseTextEditor->setBounds (4, 4, getWidth() - 8, getHeight() - 36);
    cancelButton->setBounds (getWidth() - 68, getHeight() - 28, 64, 24);
    agreeButton->setBounds (getWidth() - 136, getHeight() - 28, 64, 24);
    alwaysButton->setBounds (getWidth() - 204, getHeight() - 28, 64, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void License::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == cancelButton.get())
    {
        //[UserButtonCode_cancelButton] -- add your button handler code here..

      this->isAgreed = false ;

        //[/UserButtonCode_cancelButton]
    }
    else if (buttonThatWasClicked == agreeButton.get())
    {
        //[UserButtonCode_agreeButton] -- add your button handler code here..

      this->isAgreed = true ;

        //[/UserButtonCode_agreeButton]
    }
    else if (buttonThatWasClicked == alwaysButton.get())
    {
        //[UserButtonCode_alwaysButton] -- add your button handler code here..

      this->isAgreed    = this->alwaysButton->getToggleState() ;
      this->alwaysAgree = this->alwaysButton->getToggleState() ;

        //[/UserButtonCode_alwaysButton]
    }

    //[UserbuttonClicked_Post]

  if (this->isAgreed == true) LinJam::Connect() ; else LinJam::Disconnect() ;

    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void License::valueChanged(Value& a_value)
{
  if (!a_value.refersToSameSourceAs(this->alwaysAgree)) return ;

  bool alwaysAgree = bool(this->alwaysAgree.getValue()) ;
  this->alwaysButton->setToggleState(alwaysAgree , juce::dontSendNotification) ;
}

void License::setLicenseText(String license_text)
{
  this->licenseTextEditor->setText(TRANS(license_text)) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="License" componentName="License"
                 parentClasses="public Component, public ValueListener" constructorParams="Value is_agreed, Value always_agree"
                 variableInitialisers="isAgreed(is_agreed), alwaysAgree(always_agree)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="622" initialHeight="442">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10.0" fill="solid: ff101010" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <ROUNDRECT pos="4 4 8M 36M" cornerSize="10.0" fill="solid: ff000000" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ff808080"/>
  </BACKGROUND>
  <TEXTEDITOR name="licenseTextEditor" id="ba11ad8bfe4752c1" memberName="licenseTextEditor"
              virtualName="" explicitFocusOrder="0" pos="4 4 8M 36M" textcol="ffc0c0c0"
              bkgcol="ff404040" initialText="" multiline="1" retKeyStartsLine="0"
              readonly="1" scrollbars="1" caret="0" popupmenu="0"/>
  <TEXTBUTTON name="cancelButton" id="e40ccd6a36998aa2" memberName="cancelButton"
              virtualName="" explicitFocusOrder="2" pos="68R 28R 64 24" tooltip="Check this if you do not agree to these above terms. You will not be able to jam here."
              buttonText="Cancel" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="agreeButton" id="1c12b4600196bad4" memberName="agreeButton"
              virtualName="" explicitFocusOrder="1" pos="136R 28R 64 24" tooltip="Check this to agree to the above terms for this session only."
              buttonText="Agree" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="alwaysButton" id="7f039929e852c525" memberName="alwaysButton"
                virtualName="" explicitFocusOrder="0" pos="204R 28R 64 24" tooltip="Check this to automatically agree to these terms on this server. You will not see this screen again unless the terms should change."
                txtcol="ff808080" buttonText="Always Agree" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

