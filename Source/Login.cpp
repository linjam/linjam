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
#include "./Trace/TraceLogin.h"

//[/Headers]

#include "Login.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Login::Login (ValueTree login_store, ValueTree servers_store)
    : loginStore(login_store), serversStore(servers_store)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    setName ("Login");
    activeGroup.reset (new juce::GroupComponent ("activeGroup",
                                                 TRANS ("Active Jam Rooms")));
    addAndMakeVisible (activeGroup.get());
    activeGroup->setTextLabelPosition (juce::Justification::centred);
    activeGroup->setColour (juce::GroupComponent::outlineColourId, juce::Colours::grey);
    activeGroup->setColour (juce::GroupComponent::textColourId, juce::Colours::white);

    activeView.reset (new juce::Viewport ("activeView"));
    addAndMakeVisible (activeView.get());
    activeView->setScrollBarsShown (true, false);
    activeView->setViewedComponent (new Component());

    vacantGroup.reset (new juce::GroupComponent ("vacantGroup",
                                                 TRANS ("Vacant Jam Rooms")));
    addAndMakeVisible (vacantGroup.get());
    vacantGroup->setTextLabelPosition (juce::Justification::centred);
    vacantGroup->setColour (juce::GroupComponent::outlineColourId, juce::Colours::grey);
    vacantGroup->setColour (juce::GroupComponent::textColourId, juce::Colours::white);

    vacantView.reset (new juce::Viewport ("vacantView"));
    addAndMakeVisible (vacantView.get());
    vacantView->setScrollBarsShown (true, false);
    vacantView->setViewedComponent (new Component());

    hostLabel.reset (new juce::Label ("hostLabel",
                                      TRANS ("Server:")));
    addAndMakeVisible (hostLabel.get());
    hostLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    hostLabel->setJustificationType (juce::Justification::centredLeft);
    hostLabel->setEditable (false, false, false);
    hostLabel->setColour (juce::Label::textColourId, juce::Colours::white);
    hostLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    hostLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    loginLabel.reset (new juce::Label ("loginLabel",
                                       TRANS ("Username:")));
    addAndMakeVisible (loginLabel.get());
    loginLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    loginLabel->setJustificationType (juce::Justification::centredLeft);
    loginLabel->setEditable (false, false, false);
    loginLabel->setColour (juce::Label::textColourId, juce::Colours::white);
    loginLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    loginLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    passLabel.reset (new juce::Label ("passLabel",
                                      TRANS ("Password:")));
    addAndMakeVisible (passLabel.get());
    passLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    passLabel->setJustificationType (juce::Justification::centredLeft);
    passLabel->setEditable (false, false, false);
    passLabel->setColour (juce::Label::textColourId, juce::Colours::white);
    passLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    passLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    hostText.reset (new juce::TextEditor ("hostText"));
    addAndMakeVisible (hostText.get());
    hostText->setTooltip (TRANS ("Enter you server ip/port in the form: example.com:2050 or 123.123.123.123:2050 to use a private server."));
    hostText->setMultiLine (false);
    hostText->setReturnKeyStartsNewLine (false);
    hostText->setReadOnly (false);
    hostText->setScrollbarsShown (false);
    hostText->setCaretVisible (true);
    hostText->setPopupMenuEnabled (true);
    hostText->setColour (juce::TextEditor::textColourId, juce::Colours::grey);
    hostText->setColour (juce::TextEditor::backgroundColourId, juce::Colours::black);
    hostText->setColour (juce::TextEditor::outlineColourId, juce::Colours::grey);
    hostText->setColour (juce::CaretComponent::caretColourId, juce::Colours::white);
    hostText->setText (juce::String());

    loginText.reset (new juce::TextEditor ("loginText"));
    addAndMakeVisible (loginText.get());
    loginText->setTooltip (TRANS ("Enter a username using only the characters a-z 0-9 - and _"));
    loginText->setExplicitFocusOrder (1);
    loginText->setMultiLine (false);
    loginText->setReturnKeyStartsNewLine (false);
    loginText->setReadOnly (false);
    loginText->setScrollbarsShown (false);
    loginText->setCaretVisible (true);
    loginText->setPopupMenuEnabled (true);
    loginText->setColour (juce::TextEditor::textColourId, juce::Colours::grey);
    loginText->setColour (juce::TextEditor::backgroundColourId, juce::Colours::black);
    loginText->setColour (juce::TextEditor::outlineColourId, juce::Colours::grey);
    loginText->setColour (juce::CaretComponent::caretColourId, juce::Colours::white);
    loginText->setText (juce::String());

    passText.reset (new juce::TextEditor ("passText"));
    addAndMakeVisible (passText.get());
    passText->setTooltip (TRANS ("Some servers require a password. Try logging in with the anonymous button ticked first."));
    passText->setExplicitFocusOrder (2);
    passText->setMultiLine (false);
    passText->setReturnKeyStartsNewLine (false);
    passText->setReadOnly (false);
    passText->setScrollbarsShown (false);
    passText->setCaretVisible (true);
    passText->setPopupMenuEnabled (true);
    passText->setColour (juce::TextEditor::textColourId, juce::Colours::grey);
    passText->setColour (juce::TextEditor::backgroundColourId, juce::Colours::black);
    passText->setColour (juce::TextEditor::outlineColourId, juce::Colours::grey);
    passText->setColour (juce::CaretComponent::caretColourId, juce::Colours::white);
    passText->setText (juce::String());

    loginButton.reset (new juce::TextButton ("loginButton"));
    addAndMakeVisible (loginButton.get());
    loginButton->setTooltip (TRANS ("Click this to connect to the specified server."));
    loginButton->setExplicitFocusOrder (3);
    loginButton->setButtonText (TRANS ("<--   Connect"));
    loginButton->addListener (this);

    serverButton.reset (new juce::TextButton ("serverButton"));
    addAndMakeVisible (serverButton.get());
    serverButton->setTooltip (TRANS ("Click this to enter the adress of a private server."));
    serverButton->setExplicitFocusOrder (4);
    serverButton->setButtonText (TRANS ("Private Server"));
    serverButton->addListener (this);

    anonButton.reset (new juce::ToggleButton ("anonButton"));
    addAndMakeVisible (anonButton.get());
    anonButton->setExplicitFocusOrder (5);
    anonButton->setButtonText (TRANS ("anonymous"));
    anonButton->addListener (this);
    anonButton->setToggleState (true, juce::dontSendNotification);
    anonButton->setColour (juce::ToggleButton::textColourId, juce::Colours::white);


    //[UserPreSize]

  this->loginButton->setVisible(false) ;
  this->hostLabel  ->setVisible(false) ;
  this->hostText   ->setVisible(false) ;
  this->passLabel  ->setVisible(false) ;
  this->passText   ->setVisible(false) ;
  this->hostText   ->addListener(this) ;
  this->loginText  ->addListener(this) ;
  this->passText   ->addListener(this) ;
  this->hostText   ->setColour(TextEditor::textColourId            , GUI::TEXT_NORMAL_COLOR  ) ;
  this->loginText  ->setColour(TextEditor::textColourId            , GUI::TEXT_NORMAL_COLOR  ) ;
  this->passText   ->setColour(TextEditor::textColourId            , GUI::TEXT_NORMAL_COLOR  ) ;
  this->hostText   ->setColour(TextEditor::highlightColourId       , GUI::TEXT_HILITEBG_COLOR) ;
  this->loginText  ->setColour(TextEditor::highlightColourId       , GUI::TEXT_HILITEBG_COLOR) ;
  this->passText   ->setColour(TextEditor::highlightColourId       , GUI::TEXT_HILITEBG_COLOR) ;
  this->hostText   ->setColour(TextEditor::highlightedTextColourId , GUI::TEXT_HILITE_COLOR  ) ;
  this->loginText  ->setColour(TextEditor::highlightedTextColourId , GUI::TEXT_HILITE_COLOR  ) ;
  this->passText   ->setColour(TextEditor::highlightedTextColourId , GUI::TEXT_HILITE_COLOR  ) ;
  this->hostText   ->setTextToShowWhenEmpty(GUI::HOST_PROMPT_TEXT  , GUI::TEXT_EMPTY_COLOR   ) ;
  this->loginText  ->setTextToShowWhenEmpty(GUI::LOGIN_PROMPT_TEXT , GUI::TEXT_EMPTY_COLOR   ) ;
  this->passText   ->setTextToShowWhenEmpty(GUI::PASS_PROMPT_TEXT  , GUI::TEXT_EMPTY_COLOR   ) ;
  this->passText   ->setPasswordCharacter('*') ;

  // instantiate login and audition buttons for known hosts
  for (int server_n = 0 ; server_n < this->serversStore.getNumChildren() ; ++server_n)
  {
    ValueTree        server_store  = this->serversStore.getChild(server_n) ;
    ValueTree        clients_store = server_store      .getChildWithName(CONFIG::CLIENTS_ID) ;
    String           known_host    = server_store[CONFIG::HOST_ID] ;
    String           stream_url    = str(NETWORK::KNOWN_STREAMS[known_host]) ;
    HyperlinkButton* stream_button = new HyperlinkButton(GUI::STREAM_BUTTON_TEXT , URL(stream_url)) ;
    TextButton*      login_button  = new TextButton     (known_host + "Button") ;
    Label*           clients_label = new Label          (known_host + "Label" ) ;

    login_button ->setButtonText(known_host) ;
    login_button ->setExplicitFocusOrder(GUI::N_STATIC_LOGIN_CHILDREN + server_n) ;
    login_button ->addListener(this) ;
    stream_button->setTooltip(GUI::STREAM_BUTTON_TOOLTIP + "" + stream_url) ;
    clients_label->setColour(Label::textColourId , Colours::white) ;
    clients_label->setText(GUI::ROOM_VACANT_TOOLTIP , juce::dontSendNotification) ;

    this->serverButtons.add(login_button ) ;
    this->streamButtons.add(stream_button) ;
    this->clientsLabels.add(clients_label) ;
  }

  this->serversStore.addListener(this) ;

    //[/UserPreSize]

    setSize (622, 442);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

Login::~Login()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    activeGroup = nullptr;
    activeView = nullptr;
    vacantGroup = nullptr;
    vacantView = nullptr;
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
void Login::paint (juce::Graphics& g)
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

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Login::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    activeGroup->setBounds (24, 16, getWidth() - 248, getHeight() - 152);
    activeView->setBounds (24 + 8, 16 + 12, (getWidth() - 248) - 12, (getHeight() - 152) - 18);
    vacantGroup->setBounds (getWidth() - 24 - 200, 16, 200, getHeight() - 152);
    vacantView->setBounds ((getWidth() - 24 - 200) + 8, 16 + 12, 200 - 12, (getHeight() - 152) - 18);
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

  layoutLoginBtns() ;

    //[/UserResized]
}

void Login::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == loginButton.get())
    {
        //[UserButtonCode_loginButton] -- add your button handler code here..

      signIn() ;

        //[/UserButtonCode_loginButton]
    }
    else if (buttonThatWasClicked == serverButton.get())
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
    else if (buttonThatWasClicked == anonButton.get())
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

  else if (this->serverButtons.contains((TextButton*)buttonThatWasClicked))
    quickLogin(buttonThatWasClicked->getButtonText().trim()) ;

    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* event handlers */

void Login::broughtToFront()
{
  // load previous login state
  String host         = str (this->loginStore[CONFIG::HOST_ID        ]) ;
  String login        = str (this->loginStore[CONFIG::LOGIN_ID       ]) ;
  String pass         = str (this->loginStore[CONFIG::PASS_ID        ]) ;
  bool   is_anonymous = bool(this->loginStore[CONFIG::IS_ANONYMOUS_ID]) ;

  // restore previous login state
  this->hostText ->setText(host ) ;
  this->loginText->setText(login) ;
  this->passText ->setText(pass ) ;

DEBUG_TRACE_LOGIN_LOAD

  // validate credentials and enable components
  bool is_custom_server = host.isNotEmpty() && !NETWORK::IsKnownHost(host) ;
  this->loginButton->setVisible(is_custom_server) ;
  this->hostLabel  ->setVisible(is_custom_server) ;
  this->hostText   ->setVisible(is_custom_server) ;
  this->passLabel  ->setVisible(!is_anonymous   ) ;
  this->passText   ->setVisible(!is_anonymous   ) ;
  this->hostText   ->setText((validateHost ()) ? host  : "") ;
  this->loginText  ->setText((validateLogin()) ? login : "") ;
  this->passText   ->setText((validatePass ()) ? pass  : "") ;
  this->anonButton ->setToggleState(is_anonymous , juce::dontSendNotification) ;
}

void Login::textEditorTextChanged(TextEditor& text_editor)
{
  if      (&text_editor == this->hostText .get()) validateHost() ;
  else if (&text_editor == this->loginText.get()) validateLogin() ;
  else if (&text_editor == this->passText .get()) validatePass() ;
}

void Login::valueTreeChildAdded(ValueTree& parent_node , ValueTree& /*node*/)
{
  if (parent_node.getType() == CONFIG::CLIENTS_ID) updateClients(parent_node) ;
}

void Login::valueTreeChildRemoved(ValueTree& parent_node  , ValueTree& /*node*/ ,
                                  int        /*prev_idx*/                       )
{
  if (parent_node.getType() == CONFIG::CLIENTS_ID) updateClients(parent_node) ;
}

void Login::valueTreeChildOrderChanged(ValueTree& parent_node  , int /*prev_idx*/ ,
                                       int        /*curr_idx*/                    )
{
  if (parent_node.getType() == CONFIG::SERVERS_ID) layoutLoginBtns() ;
}


/* helpers */

bool Login::quickLogin(String host)
{
  ValueTree credentials  = LinJam::GetCredentials(host) ;
  String    login        = str (credentials[CONFIG::LOGIN_ID       ]) ;
  String    pass         = str (credentials[CONFIG::PASS_ID        ]) ;
  bool      is_anonymous = bool(credentials[CONFIG::IS_ANONYMOUS_ID]) ;
  bool      should_agree = bool(credentials[CONFIG::SHOULD_AGREE_ID]) ;

DEBUG_TRACE_LOBBY_QUICKLOGIN

  // set current host and load stored credentials
  this->hostText->setText(host) ;
  if (credentials.isValid() && should_agree)
  {
    this->loginText ->setText       (login) ;
    this->passText  ->setText       (pass ) ;
    this->anonButton->setToggleState(is_anonymous , juce::dontSendNotification) ;
  }

  return signIn() ;
}

bool Login::signIn()
{
  String host         = this->hostText  ->getText().trim() ;
  String login        = this->loginText ->getText().trim() ;
  String pass         = this->passText  ->getText().trim() ;
  bool   is_anonymous = this->anonButton->getToggleState() ;

DEBUG_TRACE_LOGIN_VALIDATION

  bool are_valid_credentials = validateHost() && validateLogin() && validatePass() ;

  if (are_valid_credentials) LinJam::SignIn(host , login , pass , is_anonymous) ;

  return are_valid_credentials ;
}

bool Login::validateHost()
{
  // parse url tokens
  String host   = this->hostText->getText().trim() ;
  String server = host  .upToFirstOccurrenceOf(StringRef(":") , false , true) ;
  String name   = server.upToLastOccurrenceOf( StringRef(".") , false , true) ;
  String tld    = server.fromLastOccurrenceOf( StringRef(".") , false , true) ;
  String port   = host  .fromFirstOccurrenceOf(StringRef(":") , false , true) ;

  // validate
  bool is_devel_host  = !NETWORK::DEVEL_HOST.compare(server) ;
  bool is_known_host  = NETWORK::IsKnownHost(host) ;
  bool has_valid_form = host.matchesWildcard(NETWORK::HOST_MASK , true) ;
  bool is_valid_name  = name.containsOnly(   NETWORK::HOST_CHARS) && name.isNotEmpty() ;
  bool is_valid_tld   = tld .containsOnly(   NETWORK::LETTERS   ) && tld .isNotEmpty() ;
  bool is_valid_port  = port.containsOnly(   NETWORK::DIGITS    ) && port.isNotEmpty() ;
  bool is_custom_host = has_valid_form && is_valid_name && is_valid_tld && is_valid_port ;
  bool is_valid_host  = is_devel_host || is_known_host || is_custom_host ;

DEBUG_TRACE_LOGIN_HOST_VB

  setTextErrorState(this->hostText.get() , !is_valid_host) ;

  return is_valid_host ;
}

bool Login::validateLogin()
{
  String nick           = this->loginText->getText().trim() ;
  bool   is_valid_login = nick.containsOnly(NETWORK::NICK_CHARS) && nick.isNotEmpty() ;

  setTextErrorState(this->loginText.get() , !is_valid_login) ;

  return is_valid_login ;
}

bool Login::validatePass()
{
  String pass          = this->passText  ->getText().trim() ;
  bool   is_anonymous  = this->anonButton->getToggleState() ;
  bool   is_valid_pass = is_anonymous || pass.isNotEmpty() ;

  setTextErrorState(this->passText.get() , !is_valid_pass) ;

  return is_valid_pass ;
}

void Login::setTextErrorState(TextEditor* a_text_editor , bool is_error_state)
{
  Colour background_color = (is_error_state) ? GUI::PROMPT_BACKGROUND_ERROR_COLOR  :
                                               GUI::PROMPT_BACKGROUND_NORMAL_COLOR ;
  Colour border_color     = (is_error_state) ? GUI::PROMPT_BORDER_ERROR_COLOR      :
                                               GUI::PROMPT_BORDER_NORMAL_COLOR     ;
  Colour focus_color      = (is_error_state) ? GUI::PROMPT_FOCUS_ERROR_COLOR       :
                                               GUI::PROMPT_FOCUS_NORMAL_COLOR      ;

  a_text_editor->setColour(TextEditor::backgroundColourId     , background_color) ;
  a_text_editor->setColour(TextEditor::outlineColourId        , border_color    ) ;
  a_text_editor->setColour(TextEditor::focusedOutlineColourId , focus_color     ) ;
}

void Login::updateClients(ValueTree clients_store)
{
  String      host = str(clients_store.getParent()[CONFIG::HOST_ID]) ;
  StringArray clients ;

  for (int host_n = 0 ; host_n < this->serversStore.getNumChildren() ; ++host_n)
  {
    ValueTree   server_store  = this->serversStore .getChild(host_n) ;
    TextButton* login_button  = this->serverButtons.getUnchecked(host_n) ;
    Label*      clients_label = this->clientsLabels.getUnchecked(host_n) ;
    String      known_host    = login_button->getButtonText() ;
    // String      slots_msg ;
    // String      bpibpm_msg ;

    // find these clients' server
    if (clients_label->getName() != host + "Label") continue ;

    // WIP: display server stats
    // clients = StringArray( str(server_store[CONFIG::TOPIC_ID   ]) ,
    clients.add( ( str(server_store[CONFIG::N_USERS_ID ]) + "/"       +
                   str(server_store[CONFIG::N_SLOTS_ID ]) + " Slots"  ).paddedLeft(' ' , 11) ) ;
    clients.add( " | " ) ;
    clients.add( ( str(server_store[CONFIG::BPI_ID     ]) + " BPI @ " +
                   str(server_store[CONFIG::BPM_ID     ]) + " BPM"    ).paddedLeft(' ' , 16) ) ;
    clients.add( " | " ) ;

    int n_clients = clients_store.getNumChildren() ;
    if (n_clients == 0) clients.add(GUI::ROOM_VACANT_TOOLTIP) ;
    else for (int client_n = 0 ; client_n < n_clients ; ++client_n)
    {
      String login = str(clients_store.getChild(client_n)[CONFIG::LOGIN_ID]) ;

      clients.add(LinJamConfig::UserIdDisplay(login)) ;
    }

    // login_button ->setButtonText(known_host + "\n" + clients.joinIntoString("\n")) ;
    login_button ->setTooltip(GUI::LOGIN_BUTTON_TOOLTIP + "\n\t" + clients.joinIntoString("\n\t")) ;
    clients_label->setText   (clients.joinIntoString(" ") , juce::dontSendNotification) ;
  }

  layoutLoginBtns() ;
}

void Login::layoutLoginBtns()
{
  if (this->serversStore.getNumChildren() != this->serverButtons.size() ||
      this->serversStore.getNumChildren() != this->clientsLabels.size()  ) return ; // TODO: assert fatal

DEBUG_TRACE_LOGIN_LAYOUT_LOGIN_BTNS

  Component* active_pane = this->activeView->getViewedComponent() ;
  Component* vacant_pane = this->vacantView->getViewedComponent() ;
  int        n_occupied  = 0 ;
  int        n_vacant    = 0 ;
  int        login_x     = GUI::LOGIN_BUTTON_L ;
  int        login_h     = GUI::LOGIN_BUTTON_H + GUI::PAD ;
  int        stream_x    = login_x  + GUI::LOGIN_BUTTON_W  + GUI::PAD2 ;
  int        clients_x   = stream_x + GUI::STREAM_BUTTON_W + GUI::PAD2 ;

  // layout buttons
  for (int host_n = 0 ; host_n < this->serversStore.getNumChildren() ; ++host_n)
  {
    TextButton*      login_button  = this->serverButtons.getUnchecked(host_n) ;
    HyperlinkButton* stream_button = this->streamButtons.getUnchecked(host_n) ;
    Label*           clients_label = this->clientsLabels.getUnchecked(host_n) ;
    bool             is_vacant     = clients_label->getText() == GUI::ROOM_VACANT_TOOLTIP ;
    String           host_name     = login_button->getButtonText() ;
    bool             has_stream    = ! NETWORK::KNOWN_STREAMS[host_name].isVoid() ;
    int              sort_order    = (is_vacant) ? n_vacant : n_occupied ;
    int              login_y       = GUI::LOGIN_BUTTON_T + (login_h * sort_order) ;
    Component*       sort_pane     = (is_vacant) ? vacant_pane : active_pane ;
    int              clients_w     = sort_pane->getWidth() - clients_x ;
    if (is_vacant) ++n_vacant ; else ++n_occupied ;

    AddLoginButton(login_button , stream_button , clients_label , is_vacant) ;
    stream_button->setVisible(  has_stream) ;
    clients_label->setVisible(! is_vacant ) ;
    login_button ->setBounds(login_x   , login_y , GUI::LOGIN_BUTTON_W  , GUI::LOGIN_BUTTON_H) ;
    stream_button->setBounds(stream_x  , login_y , GUI::STREAM_BUTTON_W , GUI::LOGIN_BUTTON_H) ;
    clients_label->setBounds(clients_x , login_y , clients_w            , GUI::LOGIN_BUTTON_H) ;
  }

  // resize viewport containers to fit buttons
  active_pane->setSize(getWidth() , GUI::LOGIN_BUTTON_T + (login_h * n_occupied)) ;
  vacant_pane->setSize(getWidth() , GUI::LOGIN_BUTTON_T + (login_h * n_vacant  )) ;
}

void Login::AddLoginButton(TextButton* login_button  , HyperlinkButton* stream_button ,
                           Label*      clients_label , bool             is_vacant     )
{
    // WIP: 2-column layout
    Viewport*  scroll_view = (is_vacant) ? this->vacantView.get() : this->activeView.get() ;
    Component* toolbox     = scroll_view->getViewedComponent() ;

    toolbox->addAndMakeVisible(login_button ) ;
    toolbox->addAndMakeVisible(stream_button) ;
    toolbox->addAndMakeVisible(clients_label) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Login" componentName="Login"
                 parentClasses="public Component, public TextEditor::Listener, public ValueTree::Listener"
                 constructorParams="ValueTree login_store, ValueTree servers_store"
                 variableInitialisers="loginStore(login_store), serversStore(servers_store)"
                 snapPixels="8" snapActive="0" snapShown="0" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="622" initialHeight="442">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10.0" fill="solid: ff101010" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="activeGroup" id="23aa8a0b33d17718" memberName="activeGroup"
                  virtualName="" explicitFocusOrder="0" pos="24 16 248M 152M" outlinecol="ff808080"
                  textcol="ffffffff" title="Active Jam Rooms" textpos="36"/>
  <VIEWPORT name="activeView" id="86f19de139bb5f3e" memberName="activeView"
            virtualName="" explicitFocusOrder="0" pos="8 12 12M 18M" posRelativeX="23aa8a0b33d17718"
            posRelativeY="23aa8a0b33d17718" posRelativeW="23aa8a0b33d17718"
            posRelativeH="23aa8a0b33d17718" vscroll="1" hscroll="0" scrollbarThickness="8"
            contentType="2" jucerFile="" contentClass="Background" constructorParams=""/>
  <GROUPCOMPONENT name="vacantGroup" id="f047af8af9dee9df" memberName="vacantGroup"
                  virtualName="" explicitFocusOrder="0" pos="24Rr 16 200 152M"
                  outlinecol="ff808080" textcol="ffffffff" title="Vacant Jam Rooms"
                  textpos="36"/>
  <VIEWPORT name="vacantView" id="f671d4c2373d4fd" memberName="vacantView"
            virtualName="" explicitFocusOrder="0" pos="8 12 12M 18M" posRelativeX="f047af8af9dee9df"
            posRelativeY="f047af8af9dee9df" posRelativeW="f047af8af9dee9df"
            posRelativeH="f047af8af9dee9df" vscroll="1" hscroll="0" scrollbarThickness="8"
            contentType="2" jucerFile="" contentClass="Background" constructorParams=""/>
  <LABEL name="hostLabel" id="916aefc37fc4e730" memberName="hostLabel"
         virtualName="" explicitFocusOrder="0" pos="-190C 112R 72 24"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="Server:"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
  <LABEL name="loginLabel" id="96b0f56176f33f63" memberName="loginLabel"
         virtualName="" explicitFocusOrder="0" pos="-190C 80R 72 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Username:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="passLabel" id="14f83e5255766a2c" memberName="passLabel"
         virtualName="" explicitFocusOrder="0" pos="-190C 48R 72 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Password:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="hostText" id="d540c830b7e8d52f" memberName="hostText" virtualName=""
              explicitFocusOrder="0" pos="-100C 112R 160 24" tooltip="Enter you server ip/port in the form: example.com:2050 or 123.123.123.123:2050 to use a private server."
              textcol="ff808080" bkgcol="ff000000" outlinecol="ff808080" caretcol="ffffffff"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="loginText" id="5490b33873f48ebc" memberName="loginText"
              virtualName="" explicitFocusOrder="1" pos="-100C 80R 160 24"
              tooltip="Enter a username using only the characters a-z 0-9 - and _"
              textcol="ff808080" bkgcol="ff000000" outlinecol="ff808080" caretcol="ffffffff"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="passText" id="3962fd184843da61" memberName="passText" virtualName=""
              explicitFocusOrder="2" pos="-100C 48R 160 24" tooltip="Some servers require a password. Try logging in with the anonymous button ticked first."
              textcol="ff808080" bkgcol="ff000000" outlinecol="ff808080" caretcol="ffffffff"
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
                virtualName="" explicitFocusOrder="5" pos="85C 48R 96 24" txtcol="ffffffff"
                buttonText="anonymous" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

