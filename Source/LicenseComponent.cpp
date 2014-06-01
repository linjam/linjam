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
#include "Linjam.h" // TODO: use persistent config instead
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
    licenseTextEditor->setColour (TextEditor::backgroundColourId, Colours::black);
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

    setSize (630, 446);


    //[Constructor] You can add your own custom stuff here..
#if DEBUG_LICENSE_MULTITHREADED
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
#if DEBUG_LICENSE_MULTITHREADED
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

    g.fillAll (Colour (0xff101010));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void LicenseComponent::resized()
{
    licenseTextEditor->setBounds (4, 4, 628, 410);
    cancelButton->setBounds (184, getHeight() - 28 - 24, 64, 24);
    agreeButton->setBounds (312, getHeight() - 28 - 24, 64, 24);
    alwaysButton->setBounds (432, getHeight() - 28 - 24, 64, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void LicenseComponent::buttonClicked (Button* buttonThatWasClicked)
{
  //[UserbuttonClicked_Pre]
DEBUG_TRACE_LICENSE_CLICKED

  this->setVisible(false) ;
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
    LinJam::SetShouldAgree(true) ;
    //[/UserButtonCode_alwaysButton]
  }

  //[UserbuttonClicked_Post]
  LinJam::Disconnect() ; if (LinJam::IsAgreed) LinJam::Connect() ;
  //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
// bool LicenseComponent::getIsAgreed() { return this->isAgreed ; }//isAgreed = false ;
void LicenseComponent::setLicenseText(String license_text)
{ this->licenseTextEditor->setText(TRANS(license_text)) ; this->toFront(true) ; }
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
                 fixedSize="0" initialWidth="630" initialHeight="446">
  <BACKGROUND backgroundColour="ff101010"/>
  <TEXTEDITOR name="licenseTextEditor" id="ba11ad8bfe4752c1" memberName="licenseTextEditor"
              virtualName="" explicitFocusOrder="0" pos="4 4 628 410" textcol="ff808080"
              bkgcol="ff000000" initialText="" multiline="1" retKeyStartsLine="0"
              readonly="1" scrollbars="1" caret="0" popupmenu="0"/>
  <TEXTBUTTON name="cancelButton" id="e40ccd6a36998aa2" memberName="cancelButton"
              virtualName="" explicitFocusOrder="0" pos="184 28Rr 64 24" buttonText="Cancel"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="agreeButton" id="1c12b4600196bad4" memberName="agreeButton"
              virtualName="" explicitFocusOrder="1" pos="312 28Rr 64 24" buttonText="Agree"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="alwaysButton" id="fee5be226ba0b7b5" memberName="alwaysButton"
              virtualName="" explicitFocusOrder="2" pos="432 28Rr 64 24" buttonText="Always"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
// WaitableEvent* LicenseComponent::agreeEvent = new WaitableEvent(false) ;
//[/EndFile]
