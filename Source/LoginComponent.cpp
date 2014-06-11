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
#include "LinJam.h"
#include "Constants.h"
#include "Trace.h"
//[/Headers]

#include "LoginComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
LoginComponent::LoginComponent ()
{
    setName ("LoginComponent");
    addAndMakeVisible (hostLabel = new Label ("hostLabel",
                                              TRANS("Server:")));
    hostLabel->setFont (Font (15.00f, Font::plain));
    hostLabel->setJustificationType (Justification::centredLeft);
    hostLabel->setEditable (false, false, false);
    hostLabel->setColour (Label::textColourId, Colours::grey);
    hostLabel->setColour (TextEditor::textColourId, Colours::black);
    hostLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (loginLabel = new Label ("loginLabel",
                                               TRANS("Username:")));
    loginLabel->setFont (Font (15.00f, Font::plain));
    loginLabel->setJustificationType (Justification::centredLeft);
    loginLabel->setEditable (false, false, false);
    loginLabel->setColour (Label::textColourId, Colours::grey);
    loginLabel->setColour (TextEditor::textColourId, Colours::black);
    loginLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (passLabel = new Label ("passLabel",
                                              TRANS("Password:")));
    passLabel->setFont (Font (15.00f, Font::plain));
    passLabel->setJustificationType (Justification::centredLeft);
    passLabel->setEditable (false, false, false);
    passLabel->setColour (Label::textColourId, Colours::grey);
    passLabel->setColour (TextEditor::textColourId, Colours::black);
    passLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (hostText = new TextEditor ("hostText"));
    hostText->setMultiLine (false);
    hostText->setReturnKeyStartsNewLine (false);
    hostText->setReadOnly (false);
    hostText->setScrollbarsShown (false);
    hostText->setCaretVisible (true);
    hostText->setPopupMenuEnabled (true);
    hostText->setColour (TextEditor::textColourId, Colours::grey);
    hostText->setColour (TextEditor::backgroundColourId, Colours::black);
    hostText->setColour (TextEditor::outlineColourId, Colours::white);
    hostText->setText (String::empty);

    addAndMakeVisible (loginText = new TextEditor ("loginText"));
    loginText->setMultiLine (false);
    loginText->setReturnKeyStartsNewLine (false);
    loginText->setReadOnly (false);
    loginText->setScrollbarsShown (false);
    loginText->setCaretVisible (true);
    loginText->setPopupMenuEnabled (true);
    loginText->setColour (TextEditor::textColourId, Colours::grey);
    loginText->setColour (TextEditor::backgroundColourId, Colours::black);
    loginText->setColour (TextEditor::outlineColourId, Colours::white);
    loginText->setText (String::empty);

    addAndMakeVisible (passText = new TextEditor ("passText"));
    passText->setExplicitFocusOrder (2);
    passText->setMultiLine (false);
    passText->setReturnKeyStartsNewLine (false);
    passText->setReadOnly (false);
    passText->setScrollbarsShown (false);
    passText->setCaretVisible (true);
    passText->setPopupMenuEnabled (true);
    passText->setColour (TextEditor::textColourId, Colours::grey);
    passText->setColour (TextEditor::backgroundColourId, Colours::black);
    passText->setColour (TextEditor::outlineColourId, Colours::white);
    passText->setText (String::empty);

    addAndMakeVisible (loginButton = new TextButton ("loginButton"));
    loginButton->setButtonText (TRANS("Connect"));
    loginButton->addListener (this);

    addAndMakeVisible (serverButton = new TextButton ("serverButton"));
    serverButton->setButtonText (TRANS("Custom Server"));
    serverButton->addListener (this);

    addAndMakeVisible (anonButton = new ToggleButton ("anonButton"));
    anonButton->setExplicitFocusOrder (1);
    anonButton->setButtonText (TRANS("anonymous"));
    anonButton->addListener (this);
    anonButton->setToggleState (true, dontSendNotification);
    anonButton->setColour (ToggleButton::textColourId, Colours::grey);


    //[UserPreSize]
  hostLabel  ->setVisible(false) ;
  hostText   ->setVisible(false) ;
  loginButton->setVisible(false) ;
    //[/UserPreSize]

    setSize (622, 442);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

LoginComponent::~LoginComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    hostLabel = nullptr;
    loginLabel = nullptr;
    passLabel = nullptr;
    hostText = nullptr;
    loginText = nullptr;
    passText = nullptr;
    loginButton = nullptr;
    serverButton = nullptr;
    anonButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void LoginComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0xff101010));
    g.fillRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), static_cast<float> (getHeight() - 0), 10.000f);

    g.setColour (Colours::white);
    g.drawRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), static_cast<float> (getHeight() - 0), 10.000f, 1.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void LoginComponent::resized()
{
    hostLabel->setBounds ((getWidth() / 2) + -190, getHeight() - 112, 72, 24);
    loginLabel->setBounds ((getWidth() / 2) + -190, getHeight() - 80, 72, 24);
    passLabel->setBounds ((getWidth() / 2) + -190, getHeight() - 48, 72, 24);
    hostText->setBounds ((getWidth() / 2) + -100, getHeight() - 112, 160, 24);
    loginText->setBounds ((getWidth() / 2) + -100, getHeight() - 80, 160, 24);
    passText->setBounds ((getWidth() / 2) + -100, getHeight() - 48, 160, 24);
    loginButton->setBounds ((getWidth() / 2) + 85, getHeight() - 112, 96, 24);
    serverButton->setBounds ((getWidth() / 2) + 85, getHeight() - 80, 96, 24);
    anonButton->setBounds ((getWidth() / 2) + 85, getHeight() - 48, 96, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void LoginComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == loginButton)
    {
        //[UserButtonCode_loginButton] -- add your button handler code here..

      LinJam::Connect() ;

        //[/UserButtonCode_loginButton]
    }
    else if (buttonThatWasClicked == serverButton)
    {
        //[UserButtonCode_serverButton] -- add your button handler code here..

      bool customHostToggleState = !this->hostText->isVisible() ;
      if (customHostToggleState) this->hostText->setText("") ;

      this->hostLabel  ->setVisible(customHostToggleState) ;
      this->hostText   ->setVisible(customHostToggleState) ;
      this->loginButton->setVisible(customHostToggleState) ;

        //[/UserButtonCode_serverButton]
    }
    else if (buttonThatWasClicked == anonButton)
    {
        //[UserButtonCode_anonButton] -- add your button handler code here..

      bool anonymousToggleState = this->anonButton->getToggleState() ;
      if (!anonymousToggleState) this->passText->setText("") ;

      this->passLabel->setVisible(anonymousToggleState) ;
      this->passText ->setVisible(anonymousToggleState) ;

        //[/UserButtonCode_anonButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

//bool validateHost(host) { return host.isNotEmpty() ; } // TODO:
void LoginComponent::broughtToFront()
{
// TODO: set textboxes from per host config
  if (LinJam::Config == nullptr) return ;

DBG("LoginComponent::broughtToFront() last Server=" + LinJam::Config->Host.toString()) ;
DBG("LoginComponent::broughtToFront() last Login=" + LinJam::Config->Login.toString()) ;
DBG("LoginComponent::broughtToFront() last Pass=" + LinJam::Config->Pass.toString()) ;
DBG("LoginComponent::broughtToFront() last Anon=" + LinJam::Config->IsAnonymous.toString()) ;

  String    host   = hostText->getText() ; String login ; String pass ; bool anon ;
  ValueTree server = LinJam::Config->getServerConfig(host) ;
  if (server.isValid())
  {
    login = server.getProperty(STORAGE::LOGIN_IDENTIFIER).toString() ;
    pass  = server.getProperty(STORAGE::PASS_IDENTIFIER).toString() ;
    anon  = bool(server.getProperty(STORAGE::ANON_IDENTIFIER)) ;
  }
  else
  {
    login =      LinJam::Config->Host.toString() ;
    pass  =      LinJam::Config->Pass.toString() ;
    anon  = bool(LinJam::Config->IsAnonymous.getValue()) ;
  }
  this->loginText ->setText(login) ;
  this->passText  ->setText(pass) ;
  this->anonButton->setToggleState(anon , dontSendNotification) ;

DBG("LoginComponent::broughtToFront() login=" + login) ;
DBG("LoginComponent::broughtToFront() pass=" + pass) ;
DBG("LoginComponent::broughtToFront() anon=" + String(anon)) ;
}

void LoginComponent::valueChanged(Value &login_value)
{
// TODO: probably all this wants to respond to is server status for quick-login buttons
DBG("LoginComponent::valueChanged()=" + login_value.getValue().toString()) ;
this->loginText->setText(login_value.getValue().toString()) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="LoginComponent" componentName="LoginComponent"
                 parentClasses="public Component, public Value::Listener" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="622" initialHeight="442">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10" fill="solid: ff101010" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <LABEL name="hostLabel" id="916aefc37fc4e730" memberName="hostLabel"
         virtualName="" explicitFocusOrder="0" pos="-190C 112R 72 24"
         textCol="ff808080" edTextCol="ff000000" edBkgCol="0" labelText="Server:"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="loginLabel" id="96b0f56176f33f63" memberName="loginLabel"
         virtualName="" explicitFocusOrder="0" pos="-190C 80R 72 24" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="Username:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="passLabel" id="14f83e5255766a2c" memberName="passLabel"
         virtualName="" explicitFocusOrder="0" pos="-190C 48R 72 24" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="Password:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="hostText" id="d540c830b7e8d52f" memberName="hostText" virtualName=""
              explicitFocusOrder="0" pos="-100C 112R 160 24" textcol="ff808080"
              bkgcol="ff000000" outlinecol="ffffffff" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="loginText" id="5490b33873f48ebc" memberName="loginText"
              virtualName="" explicitFocusOrder="0" pos="-100C 80R 160 24"
              textcol="ff808080" bkgcol="ff000000" outlinecol="ffffffff" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="passText" id="3962fd184843da61" memberName="passText" virtualName=""
              explicitFocusOrder="2" pos="-100C 48R 160 24" textcol="ff808080"
              bkgcol="ff000000" outlinecol="ffffffff" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="1"/>
  <TEXTBUTTON name="loginButton" id="7db8d8f23fee0f6a" memberName="loginButton"
              virtualName="" explicitFocusOrder="0" pos="85C 112R 96 24" buttonText="Connect"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="serverButton" id="2353714d1f249baf" memberName="serverButton"
              virtualName="" explicitFocusOrder="0" pos="85C 80R 96 24" buttonText="Custom Server"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="anonButton" id="42b61bb43a881103" memberName="anonButton"
                virtualName="" explicitFocusOrder="1" pos="85C 48R 96 24" txtcol="ff808080"
                buttonText="anonymous" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
