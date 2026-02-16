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

#include "StatusBar.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
StatusBar::StatusBar ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    setName ("StatusBar");
    statusLLabel.reset (new juce::Label ("statusLLabel",
                                         juce::String()));
    addAndMakeVisible (statusLLabel.get());
    statusLLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    statusLLabel->setJustificationType (juce::Justification::centredLeft);
    statusLLabel->setEditable (false, false, false);
    statusLLabel->setColour (juce::Label::backgroundColourId, juce::Colours::black);
    statusLLabel->setColour (juce::Label::textColourId, juce::Colours::grey);
    statusLLabel->setColour (juce::Label::outlineColourId, juce::Colours::white);
    statusLLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    statusLLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    statusLLabel->setBounds (0, 0, 160, 24);

    statusRLabel.reset (new juce::Label ("statusRLabel",
                                         juce::String()));
    addAndMakeVisible (statusRLabel.get());
    statusRLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    statusRLabel->setJustificationType (juce::Justification::centredRight);
    statusRLabel->setEditable (false, false, false);
    statusRLabel->setColour (juce::Label::backgroundColourId, juce::Colours::black);
    statusRLabel->setColour (juce::Label::textColourId, juce::Colours::grey);
    statusRLabel->setColour (juce::Label::outlineColourId, juce::Colours::white);
    statusRLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    statusRLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));


    //[UserPreSize]

  this->statusLLabel->setText(String() , dontSendNotification) ;
  this->statusRLabel->setText(String() , dontSendNotification) ;

    //[/UserPreSize]

    setSize (622, 24);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

StatusBar::~StatusBar()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    statusLLabel = nullptr;
    statusRLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void StatusBar::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        int x = 164, y = 0, width = getWidth() - 328, height = 24;
        juce::Colour fillColour = juce::Colours::black;
        juce::Colour strokeColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void StatusBar::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    statusRLabel->setBounds (getWidth() - 160, 0, 160, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void StatusBar::setStatusL(String statusText)
{ this->statusLLabel->setText(statusText , juce::dontSendNotification) ; }

void StatusBar::setStatusR(String statusText)
{ this->statusRLabel->setText(statusText , juce::dontSendNotification) ; }

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="StatusBar" componentName="StatusBar"
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="0" snapShown="0" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="782" initialHeight="32">
  <BACKGROUND backgroundColour="0">
    <RECT pos="164 0 328M 24" fill="solid: ff000000" hasStroke="1" stroke="1, mitered, butt"
          strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <LABEL name="statusLLabel" id="2b89e84fd708c8e0" memberName="statusLLabel"
         virtualName="" explicitFocusOrder="0" pos="0 0 160 24" bkgCol="ff000000"
         textCol="ff808080" outlineCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="statusRLabel" id="d9ab2c99c74ba401" memberName="statusRLabel"
         virtualName="" explicitFocusOrder="0" pos="160R 0 160 24" bkgCol="ff000000"
         textCol="ff808080" outlineCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

