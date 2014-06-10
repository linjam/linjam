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
#include "LinJam.h" // TODO: use persistent config instead (issue #6)
#include "Trace.h"
//[/Headers]

#include "LicenseComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
LicenseComponent::LicenseComponent ()
{
    addAndMakeVisible (licenseTextEditor = new TextEditor ("licenseTextEditor"));
    licenseTextEditor->setMultiLine (true);
    licenseTextEditor->setReturnKeyStartsNewLine (false);
    licenseTextEditor->setReadOnly (true);
    licenseTextEditor->setScrollbarsShown (true);
    licenseTextEditor->setCaretVisible (false);
    licenseTextEditor->setPopupMenuEnabled (false);
    licenseTextEditor->setColour (TextEditor::textColourId, Colours::grey);
    licenseTextEditor->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    licenseTextEditor->setText (String::empty);

    addAndMakeVisible (cancelButton = new TextButton ("cancelButton"));
    cancelButton->setButtonText (TRANS("Cancel"));
    cancelButton->addListener (this);

    addAndMakeVisible (agreeButton = new TextButton ("agreeButton"));
    agreeButton->setExplicitFocusOrder (1);
    agreeButton->setButtonText (TRANS("Agree"));
    agreeButton->addListener (this);

    addAndMakeVisible (alwaysButton = new TextButton ("alwaysButton"));
    alwaysButton->setExplicitFocusOrder (2);
    alwaysButton->setButtonText (TRANS("Always"));
    alwaysButton->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (622, 442);


    //[Constructor] You can add your own custom stuff here..
#ifdef DEBUG_LICENSE_MULTITHREADED
    agreeEvent = new WaitableEvent(false) ; isAgreed = false ;
#endif // DEBUG_LICENSE_MULTITHREADED
    //[/Constructor]
}

LicenseComponent::~LicenseComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    licenseTextEditor = nullptr;
    cancelButton = nullptr;
    agreeButton = nullptr;
    alwaysButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
#ifdef DEBUG_LICENSE_MULTITHREADED
    agreeEvent = nullptr ;
//     delete (agreeEvent) ;
#endif // DEBUG_LICENSE_MULTITHREADED
    //[/Destructor]
}

//==============================================================================
void LicenseComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0xff101010));
    g.fillRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), static_cast<float> (getHeight() - 0), 10.000f);

    g.setColour (Colours::white);
    g.drawRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), static_cast<float> (getHeight() - 0), 10.000f, 1.000f);

    g.setColour (Colours::black);
    g.fillRoundedRectangle (4.0f, 4.0f, static_cast<float> (getWidth() - 8), static_cast<float> (getHeight() - 36), 10.000f);

    g.setColour (Colours::grey);
    g.drawRoundedRectangle (4.0f, 4.0f, static_cast<float> (getWidth() - 8), static_cast<float> (getHeight() - 36), 10.000f, 1.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void LicenseComponent::resized()
{
    licenseTextEditor->setBounds (4, 4, getWidth() - 8, getHeight() - 36);
    cancelButton->setBounds (getWidth() - 140 - 64, getHeight() - 4 - 24, 64, 24);
    agreeButton->setBounds (getWidth() - 72 - 64, getHeight() - 4 - 24, 64, 24);
    alwaysButton->setBounds (getWidth() - 4 - 64, getHeight() - 4 - 24, 64, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void LicenseComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
DEBUG_TRACE_LICENSE_CLICKED

  this->toBack() ;
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == cancelButton)
    {
        //[UserButtonCode_cancelButton] -- add your button handler code here..
    LinJam::IsAgreed = false ;
        //[/UserButtonCode_cancelButton]
    }
    else if (buttonThatWasClicked == agreeButton)
    {
        //[UserButtonCode_agreeButton] -- add your button handler code here..
    LinJam::IsAgreed = true ;
        //[/UserButtonCode_agreeButton]
    }
    else if (buttonThatWasClicked == alwaysButton)
    {
        //[UserButtonCode_alwaysButton] -- add your button handler code here..

    LinJam::IsAgreed = true ;
#if ! PERSISTENCE_TRANSITION
    LinJam::SetShouldAgree(true) ;
#else // PERSISTENCE_TRANSITION
//    LinJam::Config->ShouldAlwaysAgree = true ;
#endif // PERSISTENCE_TRANSITION

        //[/UserButtonCode_alwaysButton]
    }

    //[UserbuttonClicked_Post]
  LinJam::Disconnect() ; if (LinJam::IsAgreed) LinJam::Connect() ;
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
// bool LicenseComponent::getIsAgreed() { return this->isAgreed ; }//isAgreed = false ;
void LicenseComponent::setLicenseText(String license_text)
{ this->licenseTextEditor->setText(TRANS(license_text)) ; }
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="LicenseComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="622" initialHeight="442">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10" fill="solid: ff101010" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <ROUNDRECT pos="4 4 8M 36M" cornerSize="10" fill="solid: ff000000" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ff808080"/>
  </BACKGROUND>
  <TEXTEDITOR name="licenseTextEditor" id="ba11ad8bfe4752c1" memberName="licenseTextEditor"
              virtualName="" explicitFocusOrder="0" pos="4 4 8M 36M" textcol="ff808080"
              bkgcol="0" initialText="" multiline="1" retKeyStartsLine="0"
              readonly="1" scrollbars="1" caret="0" popupmenu="0"/>
  <TEXTBUTTON name="cancelButton" id="e40ccd6a36998aa2" memberName="cancelButton"
              virtualName="" explicitFocusOrder="0" pos="140Rr 4Rr 64 24" buttonText="Cancel"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="agreeButton" id="1c12b4600196bad4" memberName="agreeButton"
              virtualName="" explicitFocusOrder="1" pos="72Rr 4Rr 64 24" buttonText="Agree"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="alwaysButton" id="fee5be226ba0b7b5" memberName="alwaysButton"
              virtualName="" explicitFocusOrder="2" pos="4Rr 4Rr 64 24" buttonText="Always"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
// WaitableEvent* LicenseComponent::agreeEvent = new WaitableEvent(false) ;
//[/EndFile]
