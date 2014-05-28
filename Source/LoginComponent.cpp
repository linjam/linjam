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
#include "Linjam.h"
#include "Trace.h"
//[/Headers]

#include "LoginComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
LoginComponent::LoginComponent ()
{
    this->setName("LoginComponent") ;
    this->addAndMakeVisible(this->loginLabel = new Label ("loginLabel" , TRANS("Username:"))) ;
    this->loginLabel->setFont(Font(15.00f, Font::plain)) ;
    this->loginLabel->setJustificationType(Justification::centredLeft) ;
    this->loginLabel->setEditable(false, false, false) ;
    this->loginLabel->setColour(Label::textColourId , Colours::grey) ;
    this->loginLabel->setColour(TextEditor::textColourId , Colours::black) ;
    this->loginLabel->setColour(TextEditor::backgroundColourId , Colour(0x00000000)) ;

    this->addAndMakeVisible(this->loginText = new TextEditor("loginText")) ;
    this->loginText->setMultiLine(false) ;
    this->loginText->setReturnKeyStartsNewLine(false) ;
    this->loginText->setReadOnly(false) ;
    this->loginText->setScrollbarsShown(false) ;
    this->loginText->setCaretVisible(true) ;
    this->loginText->setPopupMenuEnabled(true) ;
    this->loginText->setColour(TextEditor::textColourId , Colours::grey) ;
    this->loginText->setColour(TextEditor::backgroundColourId , Colour(0x00000000)) ;
    this->loginText->setColour(TextEditor::outlineColourId , Colours::white) ;
    this->loginText->setText(String::empty) ;

    this->addAndMakeVisible (this->passLabel = new Label("passLabel" , TRANS("Password:"))) ;
    this->passLabel->setFont(Font(15.00f , Font::plain)) ;
    this->passLabel->setJustificationType(Justification::centredLeft) ;
    this->passLabel->setEditable(false, false, false) ;
    this->passLabel->setColour(Label::textColourId , Colours::grey) ;
    this->passLabel->setColour(TextEditor::textColourId , Colours::black) ;
    this->passLabel->setColour(TextEditor::backgroundColourId , Colour(0x00000000)) ;

    this->addAndMakeVisible(this->passText = new TextEditor("passText")) ;
    this->passText->setExplicitFocusOrder(2) ;
    this->passText->setMultiLine(false) ;
    this->passText->setReturnKeyStartsNewLine(false) ;
    this->passText->setReadOnly(false) ;
    this->passText->setScrollbarsShown(false) ;
    this->passText->setCaretVisible(true) ;
    this->passText->setPopupMenuEnabled(true) ;
    this->passText->setColour(TextEditor::textColourId , Colours::grey) ;
    this->passText->setColour(TextEditor::backgroundColourId , Colour (0x00000000)) ;
    this->passText->setColour(TextEditor::outlineColourId , Colours::white) ;
    this->passText->setText(String::empty) ;

    this->addAndMakeVisible(this->loginButton = new TextButton("loginButton")) ;
    this->loginButton->setButtonText(TRANS("Connect")) ;
    this->loginButton->addListener(this) ;

    this->addAndMakeVisible(this->anonButton = new ToggleButton("anonButton")) ;
    this->anonButton->setExplicitFocusOrder(1) ;
    this->anonButton->setButtonText(TRANS("anonymous")) ;
    this->anonButton->addListener(this) ;
    this->anonButton->setToggleState(true, dontSendNotification) ;
    this->anonButton->setColour(ToggleButton::textColourId , Colours::grey) ;


    //[UserPreSize]
    //[/UserPreSize]

    this->setSize (630, 446);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

LoginComponent::~LoginComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    this->loginLabel  = nullptr ;
    this->loginText   = nullptr ;
    this->passLabel   = nullptr ;
    this->passText    = nullptr ;
    this->loginButton = nullptr ;
    this->anonButton  = nullptr ;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void LoginComponent::paint(Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black) ;

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void LoginComponent::resized()
{
    this->loginLabel ->setBounds( 96 ,  72 ,  72 , 24) ;
    this->loginText  ->setBounds(184 ,  72 , 160 , 24) ;
    this->passLabel  ->setBounds( 96 , 104 ,  72 , 24) ;
    this->passText   ->setBounds(184 , 104 , 160 , 24) ;
    this->loginButton->setBounds(368 ,  72 ,  96 , 24) ;
    this->anonButton ->setBounds(368 , 104 ,  96 , 24) ;
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void LoginComponent::buttonClicked(Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == this->loginButton)
    {
      //[UserButtonCode_loginButton] -- add your button handler code here..
DEBUG_TRACE_LOGIN_LOGINCLICKED

      this->setVisible(false) ;
      LinJam::Connect() ;
      //[/UserButtonCode_loginButton]
    }
    else if (buttonThatWasClicked == this->anonButton)
    {
        //[UserButtonCode_anonButton] -- add your button handler code here..
//        this->getTopLevelComponent ()->debugText = "buttonThatWasClicked == anonButton" ;

DEBUG_TRACE_LOGIN_ANONCLICKED

        //[/UserButtonCode_anonButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="LoginComponent" componentName="LoginComponent"
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="630" initialHeight="446">
  <BACKGROUND backgroundColour="ff000000"/>
  <LABEL name="loginLabel" id="96b0f56176f33f63" memberName="loginLabel"
         virtualName="" explicitFocusOrder="0" pos="96 72 72 24" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="Username:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="loginText" id="5490b33873f48ebc" memberName="loginText"
              virtualName="" explicitFocusOrder="0" pos="184 72 160 24" textcol="ff808080"
              bkgcol="0" outlinecol="ffffffff" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="1"/>
  <LABEL name="passLabel" id="14f83e5255766a2c" memberName="passLabel"
         virtualName="" explicitFocusOrder="0" pos="96 104 72 24" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="Password:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="passText" id="3962fd184843da61" memberName="passText" virtualName=""
              explicitFocusOrder="2" pos="184 104 160 24" textcol="ff808080"
              bkgcol="0" outlinecol="ffffffff" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="1"/>
  <TEXTBUTTON name="loginButton" id="2353714d1f249baf" memberName="loginButton"
              virtualName="" explicitFocusOrder="0" pos="368 72 96 24" buttonText="Connect"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="anonButton" id="42b61bb43a881103" memberName="anonButton"
                virtualName="" explicitFocusOrder="1" pos="368 104 96 24" txtcol="ff808080"
                buttonText="anonymous" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
