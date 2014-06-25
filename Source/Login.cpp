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

#include "Login.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Login::Login ()
{
    setName ("Login");
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
    hostText->setTooltip (TRANS("Enter you server ip/port in the form: example.com:2050 or 123.123.123.123:2050 to use a private server."));
    hostText->setMultiLine (false);
    hostText->setReturnKeyStartsNewLine (false);
    hostText->setReadOnly (false);
    hostText->setScrollbarsShown (false);
    hostText->setCaretVisible (true);
    hostText->setPopupMenuEnabled (true);
    hostText->setColour (TextEditor::textColourId, Colours::grey);
    hostText->setColour (TextEditor::backgroundColourId, Colours::black);
    hostText->setColour (TextEditor::outlineColourId, Colours::white);
    hostText->setColour (CaretComponent::caretColourId, Colours::white);
    hostText->setText (String::empty);

    addAndMakeVisible (loginText = new TextEditor ("loginText"));
    loginText->setTooltip (TRANS("Enter a username using only the characters a-z 0-9 - and _"));
    loginText->setExplicitFocusOrder (1);
    loginText->setMultiLine (false);
    loginText->setReturnKeyStartsNewLine (false);
    loginText->setReadOnly (false);
    loginText->setScrollbarsShown (false);
    loginText->setCaretVisible (true);
    loginText->setPopupMenuEnabled (true);
    loginText->setColour (TextEditor::textColourId, Colours::grey);
    loginText->setColour (TextEditor::backgroundColourId, Colours::black);
    loginText->setColour (TextEditor::outlineColourId, Colours::white);
    loginText->setColour (CaretComponent::caretColourId, Colours::white);
    loginText->setText (String::empty);

    addAndMakeVisible (passText = new TextEditor ("passText"));
    passText->setTooltip (TRANS("Some servers require a password. Try logging in with the anonymous button ticked first."));
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
    passText->setColour (CaretComponent::caretColourId, Colours::white);
    passText->setText (String::empty);

    addAndMakeVisible (loginButton = new TextButton ("loginButton"));
    loginButton->setTooltip (TRANS("Click this to connect to the specified server."));
    loginButton->setExplicitFocusOrder (3);
    loginButton->setButtonText (TRANS("<--   Connect"));
    loginButton->addListener (this);

    addAndMakeVisible (serverButton = new TextButton ("serverButton"));
    serverButton->setTooltip (TRANS("Click this to enter the adress of a private server."));
    serverButton->setExplicitFocusOrder (4);
    serverButton->setButtonText (TRANS("Private Server"));
    serverButton->addListener (this);

    addAndMakeVisible (anonButton = new ToggleButton ("anonButton"));
    anonButton->setExplicitFocusOrder (5);
    anonButton->setButtonText (TRANS("anonymous"));
    anonButton->addListener (this);
    anonButton->setToggleState (true, dontSendNotification);
    anonButton->setColour (ToggleButton::textColourId, Colours::grey);


    //[UserPreSize]

  this->loginButton->setVisible(false) ;
  this->hostLabel  ->setVisible(false) ;
  this->hostText   ->setVisible(false) ;
  this->passLabel  ->setVisible(false) ;
  this->passText   ->setVisible(false) ;

    //[/UserPreSize]

    setSize (622, 442);


    //[Constructor] You can add your own custom stuff here..

  this->hostText ->addListener(this) ;
  this->loginText->addListener(this) ;
  this->passText ->addListener(this) ;
  this->passText ->setPasswordCharacter('*') ;

  for (int host_n = 0 ; host_n < NETWORK::N_KNOWN_HOSTS ; ++host_n)
  {
    String known_host = NETWORK::KNOWN_HOSTS.getUnchecked(host_n) ;
    TextButton* loginButton = new TextButton(known_host + "Button") ;
    this->loginButtons.add(loginButton) ;

    addAndMakeVisible(loginButton) ;
    loginButton->setExplicitFocusOrder(6 + host_n) ; // TODO: here be dragons
    loginButton->setButtonText(known_host) ;
    loginButton->addListener(this) ;
  }

    //[/Constructor]
}

Login::~Login()
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
void Login::paint (Graphics& g)
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

void Login::resized()
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

  sortLoginButtons() ;

    //[/UserResized]
}

void Login::buttonClicked (Button* buttonThatWasClicked)
{
DEBUG_TRACE_LOGIN_BTNS

    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == loginButton)
    {
        //[UserButtonCode_loginButton] -- add your button handler code here..

      login(this->hostText->getText()) ;

        //[/UserButtonCode_loginButton]
    }
    else if (buttonThatWasClicked == serverButton)
    {
        //[UserButtonCode_serverButton] -- add your button handler code here..

      bool customHostToggleState = !this->hostText->isVisible() ;
      if (customHostToggleState) this->hostText->setText("") ;

      validateHost() ;
      this->hostLabel  ->setVisible(customHostToggleState) ;
      this->hostText   ->setVisible(customHostToggleState) ;
      this->loginButton->setVisible(customHostToggleState) ;

        //[/UserButtonCode_serverButton]
    }
    else if (buttonThatWasClicked == anonButton)
    {
        //[UserButtonCode_anonButton] -- add your button handler code here..

      bool anonymousToggleState = this->anonButton->getToggleState() ;
      if (anonymousToggleState) this->passText->setText("") ;

      validatePass() ;
      this->passLabel->setVisible(!anonymousToggleState) ;
      this->passText ->setVisible(!anonymousToggleState) ;

        //[/UserButtonCode_anonButton]
    }

    //[UserbuttonClicked_Post]

    else if (this->loginButtons.contains((TextButton*)buttonThatWasClicked))
    {
      String host = buttonThatWasClicked->getButtonText().trim() ;
      this->hostText->setText(host) ;

      login(host) ;
    }

    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* event handlers */

void Login::broughtToFront() { refreshState() ; }

void Login::textEditorTextChanged(TextEditor& a_text_editor)
{
  if      (&a_text_editor == &(*hostText))  validateHost() ;
  else if (&a_text_editor == &(*loginText)) validateLogin() ;
  else if (&a_text_editor == &(*passText))  validatePass() ;
}

void Login::valueChanged(Value& login_value)
{
// TODO: probably all this wants to respond to is server status for quick-login buttons (issue #7)
DBG("Login::valueChanged()=" + login_value.getValue().toString()) ;
}


/* helpers */

void Login::refreshState()
{
  if (LinJam::Config == nullptr) return ;

  String    host         =      LinJam::Config->currentHost.toString() ;
  String    login        =      LinJam::Config->currentLogin.toString() ;
  String    pass         =      LinJam::Config->currentPass.toString() ;
  bool      is_anonymous = bool(LinJam::Config->currentIsAnonymous.getValue()) ;
  ValueTree server       = LinJam::Config->getServer(host) ;

DEBUG_TRACE_LOGIN_LOAD

  if (!server.isValid())
    // could not connect to currentHost - reset current login state
    setCurrentConfig(host = "" , login = "" , pass = "" , is_anonymous = true) ;

  // initialize GUI
  validateHost() ; validateLogin() ; validatePass() ;
  bool is_custom_server = host.isNotEmpty() && !NETWORK::KNOWN_HOSTS.contains(host) ;
  this->loginButton->setVisible(is_custom_server) ;
  this->hostLabel  ->setVisible(is_custom_server) ;
  this->hostText   ->setVisible(is_custom_server) ;
  this->passLabel  ->setVisible(!is_anonymous) ;
  this->passText   ->setVisible(!is_anonymous) ;
  this->hostText   ->setText(host) ;
  this->loginText  ->setText(login) ;
  this->passText   ->setText(pass) ;
  this->anonButton ->setToggleState(is_anonymous , juce::dontSendNotification) ;
}

void Login::sortLoginButtons()
{
  // TODO: sort dynamically into occupied/vacant groups (issue #7)
  if (loginButtons.size() == NETWORK::N_KNOWN_HOSTS)
    for (int host_n = 0 ; host_n < NETWORK::N_KNOWN_HOSTS ; ++host_n)
    {
      int x = GUI::LOGIN_BUTTON_L ;
      int y = GUI::LOGIN_BUTTON_T + ((GUI::LOGIN_BUTTON_H + GUI::PAD) * host_n) ;
      int w = GUI::LOGIN_BUTTON_W ;
      int h = GUI::LOGIN_BUTTON_H ;
      this->loginButtons.getUnchecked(host_n)->setBounds(x , y , w , h) ;
    }
}
#  define DEBUG_TRACE_LOGIN_HOST                                                       \
    String h  = this->hostText->getText().trim() ; String dbg ;                        \
    String hn = h.upToLastOccurrenceOf( StringRef(".") , false , true) ;               \
    String ht = h.fromLastOccurrenceOf( StringRef(".") , false , true)                 \
                 .upToFirstOccurrenceOf(StringRef(":") , false , true) ;               \
    String hp = h.fromFirstOccurrenceOf(StringRef(":") , false , true) ;               \
    Trace::TraceConfig("validating host '" + h + "'"  +                                \
      "\n  parsed host="      + h  +                                                   \
      "\n  parsed host_tld="  + ht +                                                   \
      "\n  parsed host_port=" + hp +                                                   \
      "\n  is_valid_host="    + String(h .matchesWildcard(NETWORK::HOST_MASK , true) + \
      "\n  is_valid_url="     + String(hn.containsOnly(   NETWORK::URL_CHARS))       + \
      "\n  is_valid_tld="     + String(ht.containsOnly(   NETWORK::LETTERS))         + \
      "\n  is_valid_port="    + String(hp.containsOnly(   NETWORK::DIGITS))           )) ;
#  define DEBUG_TRACE_LOGIN                                     \
    if (!validateHost() || !validateLogin() || !validatePass()) \
      DBG("Login::login() host='" + host + "'"                + \
          " is_valid_host=" + String(validateHost())          + \
          " is_valid_login=" + String(validateLogin())        + \
          " is_valid_pass=" + String(validatePass())) ;
bool Login::validateHost()
{
DEBUG_TRACE_LOGIN_HOST

  String host      = this->hostText->getText().trim() ;
  String host_name = host.upToLastOccurrenceOf( StringRef(".") , false , true) ;
  String host_tld  = host.fromLastOccurrenceOf( StringRef(".") , false , true)
                         .upToFirstOccurrenceOf(StringRef(":") , false , true) ;
  String host_port = host.fromFirstOccurrenceOf(StringRef(":") , false , true) ;

  bool is_valid = (host     .matchesWildcard(NETWORK::HOST_MASK , true) &&
                   host_name.containsOnly(   NETWORK::URL_CHARS)             &&
                   host_tld .containsOnly(   NETWORK::LETTERS)                     &&
                   host_port.containsOnly(   NETWORK::DIGITS)                       ) ;

  Colour border_color = (is_valid)? Colours::white : Colours::red ;
  this->hostText->setColour(TextEditor::outlineColourId , border_color) ;

  return is_valid ;
}

bool Login::validateLogin()
{
  bool is_valid = this->loginText->getText().trim().containsNonWhitespaceChars() ;

  Colour border_color = (is_valid)? Colours::white : Colours::red ;
  this->loginText->setColour(TextEditor::outlineColourId , border_color) ;

  return is_valid ;
}

bool Login::validatePass()
{
  String pass         = this->passText->getText().trim() ;
  bool   is_anonymous = this->anonButton ->getToggleState() ;

  bool is_valid = is_anonymous || pass.containsNonWhitespaceChars() ;

  Colour border_color = (is_valid)? Colours::white : Colours::red ;
  this->passText->setColour(TextEditor::outlineColourId , border_color) ;

  return is_valid ;
}

void Login::setCurrentConfig(String host , String login , String pass ,
                                      bool is_anonymous)
{
  LinJam::Config->currentHost        = host ;
  LinJam::Config->currentLogin       = login ;
  LinJam::Config->currentPass        = (is_anonymous)? "" : pass ;
  LinJam::Config->currentIsAnonymous = is_anonymous ;
  LinJam::Config->currentIsAgreed    = false ;
}

void Login::login(String host)
{
DEBUG_TRACE_LOGIN

  String login        = this->loginText  ->getText().trim() ;
  String pass         = this->passText   ->getText().trim() ;
  bool   is_anonymous = this->anonButton ->getToggleState() ;

  bool is_valid_host  = validateHost() ;
  bool is_valid_login = validateLogin() ;
  bool is_valid_pass  = validatePass() ;
  if (!is_valid_host || !is_valid_login || !is_valid_pass) return ;

  setCurrentConfig(host , login , pass , is_anonymous) ;
  LinJam::Connect() ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Login" componentName="Login"
                 parentClasses="public Component, public TextEditor::Listener, public Value::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="622"
                 initialHeight="442">
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
              explicitFocusOrder="0" pos="-100C 112R 160 24" tooltip="Enter you server ip/port in the form: example.com:2050 or 123.123.123.123:2050 to use a private server."
              textcol="ff808080" bkgcol="ff000000" outlinecol="ffffffff" caretcol="ffffffff"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="loginText" id="5490b33873f48ebc" memberName="loginText"
              virtualName="" explicitFocusOrder="1" pos="-100C 80R 160 24"
              tooltip="Enter a username using only the characters a-z 0-9 - and _"
              textcol="ff808080" bkgcol="ff000000" outlinecol="ffffffff" caretcol="ffffffff"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="passText" id="3962fd184843da61" memberName="passText" virtualName=""
              explicitFocusOrder="2" pos="-100C 48R 160 24" tooltip="Some servers require a password. Try logging in with the anonymous button ticked first."
              textcol="ff808080" bkgcol="ff000000" outlinecol="ffffffff" caretcol="ffffffff"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="1"/>
  <TEXTBUTTON name="loginButton" id="7db8d8f23fee0f6a" memberName="loginButton"
              virtualName="" explicitFocusOrder="3" pos="85C 112R 96 24" tooltip="Click this to connect to the specified server."
              buttonText="&lt;--   Connect" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="serverButton" id="2353714d1f249baf" memberName="serverButton"
              virtualName="" explicitFocusOrder="4" pos="85C 80R 96 24" tooltip="Click this to enter the adress of a private server."
              buttonText="Private Server" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TOGGLEBUTTON name="anonButton" id="42b61bb43a881103" memberName="anonButton"
                virtualName="" explicitFocusOrder="5" pos="85C 48R 96 24" txtcol="ff808080"
                buttonText="anonymous" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
