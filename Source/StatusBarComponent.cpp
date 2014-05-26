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

#include "StatusBarComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
StatusBarComponent::StatusBarComponent ()
{
    setName ("StatusBarComponent");
    addAndMakeVisible (statusLLabel = new Label ("statusLLabel",
                                                 TRANS("connection status")));
    statusLLabel->setFont (Font (15.00f, Font::plain));
    statusLLabel->setJustificationType (Justification::centredLeft);
    statusLLabel->setEditable (false, false, false);
    statusLLabel->setColour (Label::textColourId, Colours::grey);
    statusLLabel->setColour (Label::outlineColourId, Colours::white);
    statusLLabel->setColour (TextEditor::textColourId, Colours::black);
    statusLLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (statusRLabel = new Label ("statusRLabel",
                                                 TRANS("bpi-bpm")));
    statusRLabel->setFont (Font (16.60f, Font::plain));
    statusRLabel->setJustificationType (Justification::centredLeft);
    statusRLabel->setEditable (false, false, false);
    statusRLabel->setColour (Label::textColourId, Colours::grey);
    statusRLabel->setColour (Label::outlineColourId, Colours::white);
    statusRLabel->setColour (TextEditor::textColourId, Colours::black);
    statusRLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    statusLLabel->setText("" , dontSendNotification) ;
    statusRLabel->setText("" , dontSendNotification) ;
    //[/UserPreSize]

    setSize (622, 24);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

StatusBarComponent::~StatusBarComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    statusLLabel = nullptr;
    statusRLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void StatusBarComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff101010));

    g.setColour (Colour (0xff202020));
    g.fillRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), static_cast<float> (getHeight() - 0), 10.000f);

    g.setColour (Colours::white);
    g.drawRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), static_cast<float> (getHeight() - 0), 10.000f, 1.000f);

    g.setColour (Colours::white);
    g.drawRect (128, 4, getWidth() - 256, 16, 1);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void StatusBarComponent::resized()
{
    statusLLabel->setBounds (4, 4, 120, 16);
    statusRLabel->setBounds (getWidth() - 4 - 120, 4, 120, 16);
    //[UserResized] Add your own custom resize handling here..
/*
  statusLLabel->setBounds(GUI::STATUS_PAD_X , GUI::STATUS_PAD_Y ,
                          GUI::STATUS_W     , GUI::STATUS_H     ) ;
  statusRLabel->setBounds(this->getWidth() - GUI::STATUS_PAD_X - GUI::STATUS_W ,
                          GUI::STATUS_PAD_Y                                    ,
                          GUI::STATUS_W - GUI::STATUS_PAD_X                    ,
                          GUI::STATUS_H - GUI::STATUS_PAD_Y                    ) ;
*/
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
  void StatusBarComponent::setStatusL(String statusText)
  { statusLLabel->setText(statusText , dontSendNotification) ; }
//  void StatusBarComponent::setStatusC(TODO: list of btns) {;}
  void StatusBarComponent::setStatusR(String statusText)
  { statusRLabel->setText(statusText , dontSendNotification) ; }
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="StatusBarComponent" componentName="StatusBarComponent"
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="622" initialHeight="24">
  <BACKGROUND backgroundColour="ff101010">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10" fill="solid: ff202020" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <RECT pos="128 4 256M 16" fill="solid: 0" hasStroke="1" stroke="1, mitered, butt"
          strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <LABEL name="statusLLabel" id="2b89e84fd708c8e0" memberName="statusLLabel"
         virtualName="" explicitFocusOrder="0" pos="4 4 120 16" textCol="ff808080"
         outlineCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="connection status"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="statusRLabel" id="d9ab2c99c74ba401" memberName="statusRLabel"
         virtualName="" explicitFocusOrder="0" pos="4Rr 4 120 16" textCol="ff808080"
         outlineCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="bpi-bpm"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="16.600000000000001421" bold="0"
         italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
