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
#include "ConfigChannel.h"
#include "./Trace/TraceChannels.h"

//[/Headers]

#include "Channel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Channel::Channel (ValueTree channel_store)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    setName ("Channel");
    xmitButton.reset (new juce::ToggleButton ("xmitButton"));
    addAndMakeVisible (xmitButton.get());
    xmitButton->setExplicitFocusOrder (1);
    xmitButton->setButtonText (TRANS ("XMIT"));
    xmitButton->setColour (juce::ToggleButton::textColourId, juce::Colours::grey);

    xmitButton->setBounds (4, 4, 40, 12);

    muteButton.reset (new juce::ToggleButton ("muteButton"));
    addAndMakeVisible (muteButton.get());
    muteButton->setExplicitFocusOrder (2);
    muteButton->setButtonText (TRANS ("MUTE"));
    muteButton->setColour (juce::ToggleButton::textColourId, juce::Colours::grey);

    muteButton->setBounds (4, 20, 40, 12);

    soloButton.reset (new juce::ToggleButton ("soloButton"));
    addAndMakeVisible (soloButton.get());
    soloButton->setExplicitFocusOrder (3);
    soloButton->setButtonText (TRANS ("SOLO"));
    soloButton->setColour (juce::ToggleButton::textColourId, juce::Colours::grey);

    soloButton->setBounds (4, 36, 40, 12);

    removeButton.reset (new juce::TextButton ("removeButton"));
    addAndMakeVisible (removeButton.get());
    removeButton->setExplicitFocusOrder (4);
    removeButton->setButtonText (TRANS ("X"));
    removeButton->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff400000));
    removeButton->setColour (juce::TextButton::buttonOnColourId, juce::Colours::maroon);
    removeButton->setColour (juce::TextButton::textColourOffId, juce::Colours::red);
    removeButton->setColour (juce::TextButton::textColourOnId, juce::Colours::red);

    removeButton->setBounds (45, 0, 15, 16);

    configButton.reset (new juce::TextButton ("configButton"));
    addAndMakeVisible (configButton.get());
    configButton->setExplicitFocusOrder (5);
    configButton->setButtonText (TRANS ("?"));
    configButton->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff404000));
    configButton->setColour (juce::TextButton::buttonOnColourId, juce::Colours::olive);
    configButton->setColour (juce::TextButton::textColourOffId, juce::Colours::yellow);
    configButton->setColour (juce::TextButton::textColourOnId, juce::Colours::yellow);

    configButton->setBounds (45, 16, 15, 16);

    panSlider.reset (new juce::Slider ("panSlider"));
    addAndMakeVisible (panSlider.get());
    panSlider->setExplicitFocusOrder (6);
    panSlider->setRange (-1, 1, 0);
    panSlider->setSliderStyle (juce::Slider::Rotary);
    panSlider->setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 12);
    panSlider->setColour (juce::Slider::textBoxTextColourId, juce::Colours::grey);
    panSlider->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colours::black);
    panSlider->addListener (this);

    panSlider->setBounds (12, 52, 36, 36);

    gainSlider.reset (new juce::Slider ("gainSlider"));
    addAndMakeVisible (gainSlider.get());
    gainSlider->setExplicitFocusOrder (7);
    gainSlider->setRange (-120, 20, 0);
    gainSlider->setSliderStyle (juce::Slider::LinearVertical);
    gainSlider->setTextBoxStyle (juce::Slider::NoTextBox, true, 48, 12);
    gainSlider->setColour (juce::Slider::textBoxTextColourId, juce::Colours::grey);
    gainSlider->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00000000));
    gainSlider->addListener (this);

    gainSlider->setBounds (22, 92, 16, 128);

    nameLabel.reset (new juce::Label ("nameLabel",
                                      TRANS ("channel name")));
    addAndMakeVisible (nameLabel.get());
    nameLabel->setExplicitFocusOrder (8);
    nameLabel->setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    nameLabel->setJustificationType (juce::Justification::centred);
    nameLabel->setEditable (true, true, true);
    nameLabel->setColour (juce::Label::textColourId, juce::Colours::grey);
    nameLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    nameLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    nameLabel->addListener (this);

    nameLabel->setBounds (4, 236, 52, 12);

    stereoLabel.reset (new juce::Label ("stereoLabel",
                                        TRANS ("ST")));
    addAndMakeVisible (stereoLabel.get());
    stereoLabel->setFont (juce::Font (10.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
    stereoLabel->setJustificationType (juce::Justification::centred);
    stereoLabel->setEditable (false, false, false);
    stereoLabel->setColour (juce::Label::textColourId, juce::Colours::green);
    stereoLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    stereoLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    stereoLabel->setBounds (12, 72, 36, 12);

    vuLeftSlider.reset (new juce::Slider ("vuLeftSlider"));
    addAndMakeVisible (vuLeftSlider.get());
    vuLeftSlider->setRange (-120, 20, 0);
    vuLeftSlider->setSliderStyle (juce::Slider::LinearBar);
    vuLeftSlider->setTextBoxStyle (juce::Slider::NoTextBox, true, 48, 12);
    vuLeftSlider->setColour (juce::Slider::textBoxTextColourId, juce::Colours::grey);
    vuLeftSlider->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00000000));
    vuLeftSlider->addListener (this);

    vuLeftSlider->setBounds (6, 92, 16, 128);

    vuRightSlider.reset (new juce::Slider ("vuRightSlider"));
    addAndMakeVisible (vuRightSlider.get());
    vuRightSlider->setRange (-120, 20, 0);
    vuRightSlider->setSliderStyle (juce::Slider::LinearBar);
    vuRightSlider->setTextBoxStyle (juce::Slider::NoTextBox, true, 48, 12);
    vuRightSlider->setColour (juce::Slider::textBoxTextColourId, juce::Colours::grey);
    vuRightSlider->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00000000));
    vuRightSlider->addListener (this);

    vuRightSlider->setBounds (38, 92, 16, 128);

    vuLeftLabel.reset (new juce::Label ("vuLeftLabel",
                                        TRANS ("-120")));
    addAndMakeVisible (vuLeftLabel.get());
    vuLeftLabel->setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
    vuLeftLabel->setJustificationType (juce::Justification::centred);
    vuLeftLabel->setEditable (false, false, false);
    vuLeftLabel->setColour (juce::Label::textColourId, juce::Colours::grey);
    vuLeftLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    vuLeftLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    vuLeftLabel->setBounds (4, 224, 24, 12);

    vuRightLabel.reset (new juce::Label ("vuRightLabel",
                                         TRANS ("-120")));
    addAndMakeVisible (vuRightLabel.get());
    vuRightLabel->setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
    vuRightLabel->setJustificationType (juce::Justification::centred);
    vuRightLabel->setEditable (false, false, false);
    vuRightLabel->setColour (juce::Label::textColourId, juce::Colours::grey);
    vuRightLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    vuRightLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    vuRightLabel->setBounds (32, 224, 24, 12);


    //[UserPreSize]

  this->vuLeftSlider ->setSliderStyle(Slider::LinearBarVertical) ;
  this->vuRightSlider->setSliderStyle(Slider::LinearBarVertical) ;
  this->vuLeftSlider ->setValue(GUI::VU_DB_MIN) ;
  this->vuRightSlider->setValue(GUI::VU_DB_MIN) ;

    //[/UserPreSize]

    setSize (64, 252);


    //[Constructor] You can add your own custom stuff here..

  String channel_name = str(   channel_store[CONFIG::CHANNEL_NAME_ID]) ;
  double volume       = double(channel_store[CONFIG::VOLUME_ID      ]) ;
  double pan          = double(channel_store[CONFIG::PAN_ID         ]) ;
  bool   is_xmit      = bool(  channel_store[CONFIG::IS_XMIT_RCV_ID ]) ;
  bool   is_muted     = bool(  channel_store[CONFIG::IS_MUTED_ID    ]) ;
  bool   is_solo      = bool(  channel_store[CONFIG::IS_SOLO_ID     ]) ;
  double vu_min       = 0.0 ;
  double vu_max       = GUI::VU_DB_RANGE ;
  double gain_min     = GUI::VU_DB_MIN ;
  double gain_max     = GUI::VU_DB_MIN + GUI::VU_DB_RANGE ;

  this->gainSlider->setValue(      volume) ;
  this->panSlider ->setValue(      pan) ;
  this->xmitButton->setToggleState(is_xmit      , juce::dontSendNotification) ;
  this->muteButton->setToggleState(is_muted     , juce::dontSendNotification) ;
  this->soloButton->setToggleState(is_solo      , juce::dontSendNotification) ;
  this->nameLabel ->setText(       channel_name , juce::dontSendNotification) ;

  setTickColor(this->xmitButton.get()) ;
  setTickColor(this->muteButton.get()) ;
  setTickColor(this->soloButton.get()) ;

  this->gainSlider   ->setDoubleClickReturnValue(true , 0.0) ;
  this->panSlider    ->setDoubleClickReturnValue(true , 0.0) ;
  this->vuLeftSlider ->setInterceptsMouseClicks(false , false) ;
  this->vuRightSlider->setInterceptsMouseClicks(false , false) ;
  this->gainSlider   ->setRange(gain_min , gain_max , 0) ;
  this->vuLeftSlider ->setRange(vu_min   , vu_max   , 0) ;
  this->vuRightSlider->setRange(vu_min   , vu_max   , 0) ;

  // local event handlers
  this->removeButton->addListener(this) ;
  this->configButton->addListener(this) ;
  this->xmitButton  ->addListener(this) ;
  this->muteButton  ->addListener(this) ;
  this->soloButton  ->addListener(this) ;

  // establish shared config value holders and listeners
  this->channelStore = channel_store ;
  this->channelName  .referTo(LinJamConfig::GetValueHolder(this->channelStore     ,
                                                           CONFIG::CHANNEL_NAME_ID)) ;
  this->stereoStatus .referTo(LinJamConfig::GetValueHolder(this->channelStore     ,
                                                           CONFIG::STEREO_ID      )) ;
  this->vuLeft       .referTo(LinJamConfig::GetValueHolder(this->channelStore     ,
                                                           CONFIG::VU_LEFT_ID     )) ;
  this->vuRight      .referTo(LinJamConfig::GetValueHolder(this->channelStore     ,
                                                           CONFIG::VU_RIGHT_ID    )) ;
  this->channelName  .addListener(this) ;
  this->stereoStatus .addListener(this) ;
  this->vuLeft       .addListener(this) ;
  this->vuRight      .addListener(this) ;

    //[/Constructor]
}

Channel::~Channel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    xmitButton = nullptr;
    muteButton = nullptr;
    soloButton = nullptr;
    removeButton = nullptr;
    configButton = nullptr;
    panSlider = nullptr;
    gainSlider = nullptr;
    nameLabel = nullptr;
    stereoLabel = nullptr;
    vuLeftSlider = nullptr;
    vuRightSlider = nullptr;
    vuLeftLabel = nullptr;
    vuRightLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Channel::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 0.0f, y = 0.0f, width = static_cast<float> (getWidth() - 0), height = static_cast<float> (getHeight() - 0);
        juce::Colour fillColour = juce::Colours::black;
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

void Channel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..

  bool is_mono   = int(this->stereoStatus.getValue()) == CONFIG::MONO ;
  bool is_master = this->channelStore.getParent().getType() == CONFIG::MASTERS_ID &&
                   this->channelStore            .getType() == CONFIG::MASTER_ID   ;
  bool is_wider  = is_mono && ! is_master ;
  uint8 vu_w     = ( (is_wider) ? GUI::VU_LG_W : GUI::VU_SM_W ) ;
  uint8 gain_x   = ( (is_wider) ? GUI::PAD     : 0            ) + GUI::VU_X + vu_w ;

  vuLeftSlider->setBounds(GUI::VU_X , GUI::VU_Y , vu_w , GUI::VU_H) ;
  gainSlider  ->setBounds(gain_x    , GUI::VU_Y , vu_w , GUI::VU_H) ;

    //[/UserResized]
}

void Channel::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]

  var        value = var(sliderThatWasMoved->getValue()) ;
  Identifier key ;

    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == panSlider.get())
    {
        //[UserSliderCode_panSlider] -- add your slider handling code here..

      key = CONFIG::PAN_ID ;

        //[/UserSliderCode_panSlider]
    }
    else if (sliderThatWasMoved == gainSlider.get())
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..

      key = CONFIG::VOLUME_ID ;

        //[/UserSliderCode_gainSlider]
    }
    else if (sliderThatWasMoved == vuLeftSlider.get())
    {
        //[UserSliderCode_vuLeftSlider] -- add your slider handling code here..

      // read only - unhandled

        //[/UserSliderCode_vuLeftSlider]
    }
    else if (sliderThatWasMoved == vuRightSlider.get())
    {
        //[UserSliderCode_vuRightSlider] -- add your slider handling code here..

      // read only - unhandled

        //[/UserSliderCode_vuRightSlider]
    }

    //[UsersliderValueChanged_Post]

  setConfig(key , value) ;

    //[/UsersliderValueChanged_Post]
}

void Channel::labelTextChanged (juce::Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == nameLabel.get())
    {
        //[UserLabelCode_nameLabel] -- add your label text handling code here..

DEBUG_TRACE_RENAME_CHANNEL_GUI_VIA_LABEL

      String gui_name      = this->nameLabel->getText() ;
      int    stereo_status = int(this->stereoStatus.getValue()) ;
      String client_name   = LinJamConfig::MakeStereoName(gui_name , stereo_status) ;

      setConfig(CONFIG::CHANNEL_NAME_ID , var(client_name)) ;

        //[/UserLabelCode_nameLabel]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...


/* Channel class private instance methods */

void Channel::buttonClicked(Button* a_button) { handleButtonClicked(a_button) ; }

void Channel::valueChanged(Value& a_value)
{
  bool is_vu_left  = a_value.refersToSameSourceAs(this->vuLeft      ) ;
  bool is_vu_right = a_value.refersToSameSourceAs(this->vuRight     ) ;
  bool is_stereo   = a_value.refersToSameSourceAs(this->stereoStatus) ;
  bool is_name     = a_value.refersToSameSourceAs(this->channelName ) ;

  if      (is_vu_left ) updateVU(this->vuLeftSlider .get() , this->vuLeftLabel .get() , this->vuLeft ) ;
  else if (is_vu_right) updateVU(this->vuRightSlider.get() , this->vuRightLabel.get() , this->vuRight) ;
  else if (is_stereo  ) setStereoState() ;
  else if (is_name    )
  {
DEBUG_TRACE_RENAME_CHANNEL_GUI_VIA_CALLOUTBOX

    String client_name = str(this->channelName.getValue()) ;
    String gui_name    = LinJamConfig::TrimStereoName(client_name) ;
    this->nameLabel->setText(gui_name , juce::dontSendNotification) ;
  }
}

void Channel::updateVU(Slider* a_vu_slider , Label* a_vu_label , Value vu_var)
{
  double vu_value     = double(vu_var.getValue()) ;
  double actual_vu    = vu_value + GUI::VU_DB_MIN ;
  bool   is_metro     = this->channelStore.getType() == CONFIG::METRO_ID ;
  bool   is_saturated = actual_vu >= 0.0 && !is_metro ;
  String label_text   = (vu_value <= GUI::VU_DB_RANGE) ? String(int(actual_vu)    ) :
                                                         String(GUI::INFINITY_CHAR) ;

  a_vu_slider->setValue(vu_value) ;
  a_vu_label ->setText(label_text , juce::dontSendNotification) ;
  a_vu_slider->setColour(Slider::thumbColourId , (is_saturated)      ?
                                                 Colour(0xFFFF0000)  :
                                                 Colour(0xFFBBBBFF)) ;
  a_vu_slider->setColour(Slider::trackColourId , (is_saturated)      ?
                                                 Colour(0x80800000)  :
                                                 Colour(0x80008000)) ;
}

void Channel::setConfig(Identifier a_key , var a_value)
{
  if (a_key.isValid()) this->channelStore.setProperty(a_key , a_value , nullptr) ;
}


/* Channel class protected instance methods */

void Channel::setTickColor(Button* a_button)
{
  Colour off_color = Colours::grey ;
  Colour on_color  = ( (a_button == this->xmitButton.get()) ? Colour(0xFFFF00FF) :
                       (a_button == this->muteButton.get()) ? Colour(0xFF0000FF) :
                       (a_button == this->soloButton.get()) ? Colour(0xFF00FFFF) :
                                                              Colour(0xFFFFFFFF) ) ;
  Colour color     = a_button->getToggleState() ? on_color : off_color ;

  a_button->setColour(ToggleButton::tickDisabledColourId , color) ;
}

bool Channel::handleButtonClicked(Button* a_button)
{
  Identifier key   = (a_button == this->xmitButton.get()) ? CONFIG::IS_XMIT_RCV_ID :
                     (a_button == this->muteButton.get()) ? CONFIG::IS_MUTED_ID    :
                     (a_button == this->soloButton.get()) ? CONFIG::IS_SOLO_ID     :
                                                            Identifier::null       ;
  var        value = var(a_button->getToggleState()) ;
  bool was_handled = key.isValid() ;

  if (was_handled) { setConfig(key , value) ; setTickColor(a_button) ; }

  return was_handled ;
}

void Channel::setStereoState()
{
DEBUG_TRACE_STEREO_STATE_GUI

  bool is_stereo = int(this->stereoStatus.getValue()) != CONFIG::MONO ;
  bool is_metro  = this->channelStore.getType() == CONFIG::METRO_ID ;

  // show/hide stereo-only components
  this->stereoLabel  ->setVisible(is_stereo) ;
  this->vuRightSlider->setVisible(is_stereo) ;
  this->vuRightLabel ->setVisible(is_stereo && !is_metro) ;

  // set channel name
  String channel_name   = str(this->channelName.getValue()) ;
  String stereo_postfix = channel_name.getLastCharacters(CLIENT::STEREO_POSTFIX_N_CHARS) ;

  if (is_stereo && !stereo_postfix.compare(CLIENT::STEREO_L_POSTFIX))
    channel_name = LinJamConfig::TrimStereoName(channel_name) ;
  this->nameLabel->setText(channel_name , juce::dontSendNotification) ;

  resized() ;
}


/* MasterChannels , LocalChannels , RemoteChannels classes private class methods */

MasterChannel::MasterChannel(ValueTree channel_store) : Channel(channel_store)
{
  this->removeButton->setVisible(false) ;
  this->configButton->setVisible(false) ;
  this->xmitButton  ->setVisible(false) ;
  this->soloButton  ->setVisible(false) ;
  this->stereoLabel ->setVisible(true) ;
  this->nameLabel   ->setEditable(false , false , false) ;

  // metro VU used as loop progress indicator
  if (this->channelStore.getType() == CONFIG::METRO_ID)
  {
    this->vuLeftSlider ->setRange(0.0 , 1.0 , 0.0) ;
    this->vuRightSlider->setRange(0.0 , 1.0 , 0.0) ;
    this->vuLeftLabel  ->setVisible(false) ;
    this->vuRightLabel ->setVisible(false) ;
  }

  setStereoState() ;
}

LocalChannel::LocalChannel(ValueTree channel_store) : Channel(channel_store)
{
  this->xmitButton->setButtonText(GUI::XMIT_LABEL_TEXT) ;

  setStereoState() ;
}

RemoteChannel::RemoteChannel(ValueTree channel_store) : Channel(channel_store)
{
  this->nameLabel   ->setEditable(false , false , false) ;
  this->removeButton->setVisible(false) ;
  this->configButton->setVisible(false) ;
  this->xmitButton  ->setButtonText(GUI::RCV_LABEL_TEXT) ;

  setStereoState() ;
}


/* LocalChannel class private instance methods */

void LocalChannel::buttonClicked(Button* a_button)
{
  if (handleButtonClicked(a_button)) return ;

  if      (a_button == this->removeButton.get())
    LinJam::RemoveLocalChannel(this->channelStore) ;
  else if (a_button == this->configButton.get())
  {
    UPTR<Component> configChannel = std::make_unique<ConfigChannel>(this->channelStore) ;
    Component*      mixer         = getParentComponent()->getParentComponent() ;
    Component*      mainContent   = mixer->getParentComponent() ;

    // compute CallOutBox arrow target posistion
    int modalX = mixer->getX() + getX() + this->configButton->getX() + GUI::HOVER_BTN_XC ;
    int modalY = mixer->getY() + getY() + this->configButton->getY() + GUI::HOVER_BTN_YC ;
    juce::Rectangle<int> modalRect = juce::Rectangle<int>(modalX , modalY , 1 , 1) ;

    // instantiate ConfigChannel as CallOutBox
    configChannel->setSize(GUI::CHANNEL_CONFIG_W , GUI::CHANNEL_CONFIG_H) ;
    CallOutBox::launchAsynchronously(std::move(configChannel) , modalRect , mainContent) ;
  }
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Channel" componentName="Channel"
                 parentClasses="public Component, public ButtonListener, public SliderListener, public Value::Listener"
                 constructorParams="ValueTree channel_store" variableInitialisers=""
                 snapPixels="8" snapActive="0" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="64" initialHeight="252">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10.0" fill="solid: ff000000" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <TOGGLEBUTTON name="xmitButton" id="f45f759640162c62" memberName="xmitButton"
                virtualName="" explicitFocusOrder="1" pos="4 4 40 12" txtcol="ff808080"
                buttonText="XMIT" connectedEdges="0" needsCallback="0" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="muteButton" id="263020526add917" memberName="muteButton"
                virtualName="" explicitFocusOrder="2" pos="4 20 40 12" txtcol="ff808080"
                buttonText="MUTE" connectedEdges="0" needsCallback="0" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="soloButton" id="3b096c8c7df5c792" memberName="soloButton"
                virtualName="" explicitFocusOrder="3" pos="4 36 40 12" txtcol="ff808080"
                buttonText="SOLO" connectedEdges="0" needsCallback="0" radioGroupId="0"
                state="0"/>
  <TEXTBUTTON name="removeButton" id="becd368b728d32c0" memberName="removeButton"
              virtualName="" explicitFocusOrder="4" pos="45 0 15 16" bgColOff="ff400000"
              bgColOn="ff800000" textCol="ffff0000" textColOn="ffff0000" buttonText="X"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="configButton" id="f0a56a4ebe614916" memberName="configButton"
              virtualName="" explicitFocusOrder="5" pos="45 16 15 16" bgColOff="ff404000"
              bgColOn="ff808000" textCol="ffffff00" textColOn="ffffff00" buttonText="?"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <SLIDER name="panSlider" id="aa7c4f80abb603e9" memberName="panSlider"
          virtualName="" explicitFocusOrder="6" pos="12 52 36 36" textboxtext="ff808080"
          textboxbkgd="ff000000" min="-1.0" max="1.0" int="0.0" style="Rotary"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="0" textBoxHeight="12"
          skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="gainSlider" id="e34ef13291b2ec40" memberName="gainSlider"
          virtualName="" explicitFocusOrder="7" pos="22 92 16 128" textboxtext="ff808080"
          textboxbkgd="0" min="-120.0" max="20.0" int="0.0" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="48"
          textBoxHeight="12" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="nameLabel" id="66bafa468220da02" memberName="nameLabel"
         virtualName="" explicitFocusOrder="8" pos="4 236 52 12" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="channel name" editableSingleClick="1"
         editableDoubleClick="1" focusDiscardsChanges="1" fontname="Default font"
         fontsize="12.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="stereoLabel" id="deaf84482cab9f7d" memberName="stereoLabel"
         virtualName="" explicitFocusOrder="0" pos="12 72 36 12" textCol="ff008000"
         edTextCol="ff000000" edBkgCol="0" labelText="ST" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10.0" kerning="0.0" bold="1" italic="0" justification="36"
         typefaceStyle="Bold"/>
  <SLIDER name="vuLeftSlider" id="fbb656fdc87f46ed" memberName="vuLeftSlider"
          virtualName="" explicitFocusOrder="0" pos="6 92 16 128" textboxtext="ff808080"
          textboxbkgd="0" min="-120.0" max="20.0" int="0.0" style="LinearBar"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="48"
          textBoxHeight="12" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="vuRightSlider" id="31c942b6caa362dd" memberName="vuRightSlider"
          virtualName="" explicitFocusOrder="0" pos="38 92 16 128" textboxtext="ff808080"
          textboxbkgd="0" min="-120.0" max="20.0" int="0.0" style="LinearBar"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="48"
          textBoxHeight="12" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="vuLeftLabel" id="cdc1fb3056af7c9b" memberName="vuLeftLabel"
         virtualName="" explicitFocusOrder="0" pos="4 224 24 12" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="-120" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12.0" kerning="0.0" bold="1" italic="0" justification="36"
         typefaceStyle="Bold"/>
  <LABEL name="vuRightLabel" id="4bb31261e6795ae1" memberName="vuRightLabel"
         virtualName="" explicitFocusOrder="0" pos="32 224 24 12" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="-120" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12.0" kerning="0.0" bold="1" italic="0" justification="36"
         typefaceStyle="Bold"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

