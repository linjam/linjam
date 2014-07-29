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
#include "Mixer.h"
#include "ChannelConfig.h"
#include "./Trace/TraceChannels.h"

//[/Headers]

#include "Channel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Channel::Channel (ValueTree channel_store)
{
    setName ("Channel");
    addAndMakeVisible (xmitButton = new ToggleButton ("xmitButton"));
    xmitButton->setExplicitFocusOrder (1);
    xmitButton->setButtonText (TRANS("XMIT"));
    xmitButton->setColour (ToggleButton::textColourId, Colours::grey);

    addAndMakeVisible (muteButton = new ToggleButton ("muteButton"));
    muteButton->setExplicitFocusOrder (2);
    muteButton->setButtonText (TRANS("MUTE"));
    muteButton->setColour (ToggleButton::textColourId, Colours::grey);

    addAndMakeVisible (soloButton = new ToggleButton ("soloButton"));
    soloButton->setExplicitFocusOrder (3);
    soloButton->setButtonText (TRANS("SOLO"));
    soloButton->setColour (ToggleButton::textColourId, Colours::grey);

    addAndMakeVisible (removeButton = new TextButton ("removeButton"));
    removeButton->setExplicitFocusOrder (4);
    removeButton->setButtonText (TRANS("X"));
    removeButton->setColour (TextButton::buttonColourId, Colour (0xff400000));
    removeButton->setColour (TextButton::buttonOnColourId, Colours::maroon);
    removeButton->setColour (TextButton::textColourOnId, Colours::red);
    removeButton->setColour (TextButton::textColourOffId, Colours::red);

    addAndMakeVisible (configButton = new TextButton ("configButton"));
    configButton->setExplicitFocusOrder (5);
    configButton->setButtonText (TRANS("?"));
    configButton->setColour (TextButton::buttonColourId, Colour (0xff404000));
    configButton->setColour (TextButton::buttonOnColourId, Colours::olive);
    configButton->setColour (TextButton::textColourOnId, Colours::yellow);
    configButton->setColour (TextButton::textColourOffId, Colours::yellow);

    addAndMakeVisible (panSlider = new Slider ("panSlider"));
    panSlider->setExplicitFocusOrder (6);
    panSlider->setRange (-1, 1, 0);
    panSlider->setSliderStyle (Slider::Rotary);
    panSlider->setTextBoxStyle (Slider::NoTextBox, true, 0, 12);
    panSlider->setColour (Slider::textBoxTextColourId, Colours::grey);
    panSlider->setColour (Slider::textBoxBackgroundColourId, Colours::black);
    panSlider->addListener (this);

    addAndMakeVisible (gainSlider = new Slider ("gainSlider"));
    gainSlider->setExplicitFocusOrder (7);
    gainSlider->setRange (-120, 20, 0);
    gainSlider->setSliderStyle (Slider::LinearVertical);
    gainSlider->setTextBoxStyle (Slider::NoTextBox, true, 48, 12);
    gainSlider->setColour (Slider::textBoxTextColourId, Colours::grey);
    gainSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00000000));
    gainSlider->addListener (this);

    addAndMakeVisible (nameLabel = new Label ("nameLabel",
                                              TRANS("channel name")));
    nameLabel->setExplicitFocusOrder (8);
    nameLabel->setFont (Font (12.00f, Font::plain));
    nameLabel->setJustificationType (Justification::centred);
    nameLabel->setEditable (true, true, true);
    nameLabel->setColour (Label::textColourId, Colours::grey);
    nameLabel->setColour (TextEditor::textColourId, Colours::black);
    nameLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    nameLabel->addListener (this);

    addAndMakeVisible (stereoLabel = new Label ("stereoLabel",
                                                TRANS("ST")));
    stereoLabel->setFont (Font (10.00f, Font::bold));
    stereoLabel->setJustificationType (Justification::centred);
    stereoLabel->setEditable (false, false, false);
    stereoLabel->setColour (Label::textColourId, Colours::green);
    stereoLabel->setColour (TextEditor::textColourId, Colours::black);
    stereoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (vuLeftSlider = new Slider ("vuLeftSlider"));
    vuLeftSlider->setRange (-120, 20, 0);
    vuLeftSlider->setSliderStyle (Slider::LinearBar);
    vuLeftSlider->setTextBoxStyle (Slider::NoTextBox, true, 48, 12);
    vuLeftSlider->setColour (Slider::textBoxTextColourId, Colours::grey);
    vuLeftSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00000000));
    vuLeftSlider->addListener (this);

    addAndMakeVisible (vuRightSlider = new Slider ("vuRightSlider"));
    vuRightSlider->setRange (-120, 20, 0);
    vuRightSlider->setSliderStyle (Slider::LinearBar);
    vuRightSlider->setTextBoxStyle (Slider::NoTextBox, true, 48, 12);
    vuRightSlider->setColour (Slider::textBoxTextColourId, Colours::grey);
    vuRightSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00000000));
    vuRightSlider->addListener (this);

    addAndMakeVisible (vuLeftLabel = new Label ("vuLeftLabel",
                                                TRANS("-120")));
    vuLeftLabel->setFont (Font (10.00f, Font::plain));
    vuLeftLabel->setJustificationType (Justification::centred);
    vuLeftLabel->setEditable (false, false, false);
    vuLeftLabel->setColour (Label::textColourId, Colours::grey);
    vuLeftLabel->setColour (TextEditor::textColourId, Colours::black);
    vuLeftLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (vuRightLabel = new Label ("vuRightLabel",
                                                 TRANS("-120")));
    vuRightLabel->setFont (Font (10.00f, Font::plain));
    vuRightLabel->setJustificationType (Justification::centred);
    vuRightLabel->setEditable (false, false, false);
    vuRightLabel->setColour (Label::textColourId, Colours::grey);
    vuRightLabel->setColour (TextEditor::textColourId, Colours::black);
    vuRightLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]

  this->vuLeftSlider ->setSliderStyle(Slider::LinearBarVertical) ;
  this->vuRightSlider->setSliderStyle(Slider::LinearBarVertical) ;
  this->vuLeftSlider ->setValue(CLIENT::VU_DB_MIN) ;
  this->vuRightSlider->setValue(CLIENT::VU_DB_MIN) ;

    //[/UserPreSize]

    setSize (60, 252);


    //[Constructor] You can add your own custom stuff here..

  String channel_name =        channel_store[CONFIG::CHANNEL_NAME_ID].toString() ;
  double volume       = double(channel_store[CONFIG::VOLUME_ID]) ;
  double pan          = double(channel_store[CONFIG::PAN_ID]) ;
  bool   is_xmit      = bool(  channel_store[CONFIG::IS_XMIT_RCV_ID]) ;
  bool   is_muted     = bool(  channel_store[CONFIG::IS_MUTED_ID]) ;
  bool   is_solo      = bool(  channel_store[CONFIG::IS_SOLO_ID]) ;
  double vu_min       = 0.0 ;
  double vu_max       = CLIENT::VU_DB_RANGE ;
  double gain_min     = CLIENT::VU_DB_MIN ;
  double gain_max     = CLIENT::VU_DB_MIN + CLIENT::VU_DB_RANGE ;

  this->nameLabel ->setText(       channel_name , juce::dontSendNotification) ;
  this->gainSlider->setValue(      volume) ;
  this->panSlider ->setValue(      pan) ;
  this->xmitButton->setToggleState(is_xmit      , juce::dontSendNotification) ;
  this->muteButton->setToggleState(is_muted     , juce::dontSendNotification) ;
  this->soloButton->setToggleState(is_solo      , juce::dontSendNotification) ;

  this->gainSlider   ->setDoubleClickReturnValue(true , 0.0) ;
  this->panSlider    ->setDoubleClickReturnValue(true , 0.0) ;
  this->vuLeftSlider ->setInterceptsMouseClicks(false , false) ;
  this->vuRightSlider->setInterceptsMouseClicks(false , false) ;
  this->vuLeftSlider ->setRange(vu_min   , vu_max   , 0) ;
  this->vuRightSlider->setRange(vu_min   , vu_max   , 0) ;
  this->gainSlider   ->setRange(gain_min , gain_max , 0) ;

  this->removeButton->addListener(this) ;
  this->configButton->addListener(this) ;
  this->xmitButton  ->addListener(this) ;
  this->muteButton  ->addListener(this) ;
  this->soloButton  ->addListener(this) ;

  // establish shared config storage and listeners
  this->configStore  = channel_store ;
  Value name_value   = getValueObject(CONFIG::CHANNEL_NAME_ID) ;
  Value stereo_value = getValueObject(CONFIG::STEREO_ID) ;
  Value vu_l_value   = getValueObject(CONFIG::VU_LEFT_ID) ;
  Value vu_r_value   = getValueObject(CONFIG::VU_RIGHT_ID) ;
  this->channelName .referTo(name_value) ;
  this->stereoStatus.referTo(stereo_value) ;
  this->vuLeft      .referTo(vu_l_value) ;
  this->vuRight     .referTo(vu_r_value) ;
  this->channelName .addListener(this) ;
  this->stereoStatus.addListener(this) ;
  this->vuLeft      .addListener(this) ;
  this->vuRight     .addListener(this) ;

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
void Channel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colours::black);
    g.fillRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), static_cast<float> (getHeight() - 0), 10.000f);

    g.setColour (Colours::white);
    g.drawRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), static_cast<float> (getHeight() - 0), 10.000f, 1.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Channel::resized()
{
    xmitButton->setBounds (4, 4, 36, 12);
    muteButton->setBounds (4, 20, 36, 12);
    soloButton->setBounds (4, 36, 36, 12);
    removeButton->setBounds (45, 0, 15, 16);
    configButton->setBounds (45, 16, 15, 16);
    panSlider->setBounds (12, 52, 36, 36);
    gainSlider->setBounds (22, 92, 16, 128);
    nameLabel->setBounds (4, 236, 52, 12);
    stereoLabel->setBounds (12, 72, 36, 12);
    vuLeftSlider->setBounds (6, 92, 16, 128);
    vuRightSlider->setBounds (38, 92, 16, 128);
    vuLeftLabel->setBounds (4, 224, 24, 12);
    vuRightLabel->setBounds (32, 224, 24, 12);
    //[UserResized] Add your own custom resize handling here..

  bool is_mono   = int(this->stereoStatus.getValue()) == CONFIG::MONO ;
  bool is_master = this->configStore.getParent().getType() == CONFIG::MASTERS_ID &&
                   this->configStore            .getType() == CONFIG::MASTER_ID   ;

  if (is_mono && !is_master)
  {
    vuLeftSlider->setBounds(6  , 92 , 24 , 128) ;
    gainSlider  ->setBounds(32 , 92 , 24 , 128) ;
  }

    //[/UserResized]
}

void Channel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == panSlider)
    {
        //[UserSliderCode_panSlider] -- add your slider handling code here..

      // set stored config for this channel pan (configures NJClient implicitly)
      double pan = sliderThatWasMoved->getValue() ;
      setChannelConfig(CONFIG::PAN_ID , var(pan)) ;

        //[/UserSliderCode_panSlider]
    }
    else if (sliderThatWasMoved == gainSlider)
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..

      // set stored config for this channel volume (configures NJClient implicitly)
      double gain = sliderThatWasMoved->getValue() ;
      setChannelConfig(CONFIG::VOLUME_ID , var(gain)) ;

        //[/UserSliderCode_gainSlider]
    }
    else if (sliderThatWasMoved == vuLeftSlider)
    {
        //[UserSliderCode_vuLeftSlider] -- add your slider handling code here..
        //[/UserSliderCode_vuLeftSlider]
    }
    else if (sliderThatWasMoved == vuRightSlider)
    {
        //[UserSliderCode_vuRightSlider] -- add your slider handling code here..
        //[/UserSliderCode_vuRightSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void Channel::labelTextChanged (Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == nameLabel)
    {
        //[UserLabelCode_nameLabel] -- add your label text handling code here..

      // store new channel name (configures NJClient asynchronously)
      setChannelConfig(CONFIG::CHANNEL_NAME_ID , var(this->nameLabel->getText())) ;

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
  if      (a_value.refersToSameSourceAs(this->vuLeft))
    updateChannelVU(this->vuLeftSlider  , this->vuLeftLabel  ,
                    double(this->vuLeft.getValue())) ;

  else if (a_value.refersToSameSourceAs(this->vuRight))
    updateChannelVU(this->vuRightSlider , this->vuRightLabel ,
                    double(this->vuRight.getValue())) ;

  else if (a_value.refersToSameSourceAs(this->stereoStatus)) setStereoState() ;

  else if (a_value.refersToSameSourceAs(this->channelName)) renameChannel() ;
}

void Channel::updateChannelVU(Slider* a_vu_slider , Label* a_vu_label , double vu)
{
  double actual_vu    = vu + CLIENT::VU_DB_MIN ;
  bool   is_metro     = this->configStore.getType() == CONFIG::METRO_ID ;
  bool   is_saturated = actual_vu >= 0.0 && !is_metro ;
  String label_text   = String((vu <= CLIENT::VU_DB_RANGE)? int(actual_vu) : '\u221E') ;

  a_vu_slider->setValue(vu) ;
  a_vu_label ->setText(label_text , juce::dontSendNotification) ;
  a_vu_slider->setColour(Slider::thumbColourId , (is_saturated)      ?
                                                 Colours::red        :
                                                 Colour(0xFFBBBBFF)) ;
  a_vu_slider->setColour(Slider::trackColourId , (is_saturated)      ?
                                                 Colour(0x01800000)  :
                                                 Colour(0x01008000)) ;
}

void Channel::renameChannel()
{
DEBUG_TRACE_RENAME_CHANNEL_GUI

  String new_name = this->channelName.getValue().toString() ;
  this->nameLabel->setText(new_name , juce::dontSendNotification) ;
}

Value Channel::getValueObject(Identifier a_key)
{
  return this->configStore.getPropertyAsValue(a_key , nullptr) ;
}

void Channel::setChannelConfig(Identifier config_key , var value)
{
  this->configStore.setProperty(config_key , value , nullptr) ;
}


/* Channel class protected instance methods */

bool Channel::handleButtonClicked(Button* a_button)
{
  // set stored config for this channel (configures NJClient implicitly)
  if      (a_button == this->xmitButton)
    setChannelConfig(CONFIG::IS_XMIT_RCV_ID , var(a_button->getToggleState())) ;
  else if (a_button == this->muteButton)
    setChannelConfig(CONFIG::IS_MUTED_ID    , var(a_button->getToggleState())) ;
  else if (a_button == this->soloButton)
    setChannelConfig(CONFIG::IS_SOLO_ID     , var(a_button->getToggleState())) ;
  else return false ;

  return true ;
}

void Channel::setStereoState()
{
DEBUG_TRACE_STEREO_STATE_GUI

  bool is_stereo = int(this->stereoStatus.getValue()) != CONFIG::MONO ;
  bool is_metro  = this->configStore.getType() == CONFIG::METRO_ID ;

  // show/hide stereo-only components
  this->stereoLabel  ->setVisible(is_stereo) ;
  this->vuRightSlider->setVisible(is_stereo) ;
  this->vuRightLabel ->setVisible(is_stereo && !is_metro) ;

  // set channel name
  String channel_name   = this->channelName.getValue().toString() ;
  String stereo_postfix = channel_name.getLastCharacters(CLIENT::STEREO_POSTFIX_N_CHARS) ;

  if (is_stereo && !stereo_postfix.compare(CLIENT::STEREO_L_POSTFIX))
    channel_name = LinJam::Config->trimStereoName(channel_name) ;
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
  if (this->configStore.getType() == CONFIG::METRO_ID)
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

  if      (a_button == this->removeButton)
    LinJam::RemoveLocalChannel(this->configStore) ;

  else if (a_button == this->configButton)
  {
    ChannelConfig* channelConfig = new ChannelConfig(this->configStore) ;
    Component*     mixer         = getParentComponent()->getParentComponent() ;
    Component*     mainContent   = mixer->getParentComponent() ;

    // compute CallOutBox arrow target posistion
    int modalX = mixer->getX() + getX() + configButton->getX() + (GUI::CONFIG_BTN_W / 2) ;
    int modalY = mixer->getY() + getY() + configButton->getY() + (GUI::CONFIG_BTN_H / 2) ;
    juce::Rectangle<int> modalRect = juce::Rectangle<int>(modalX , modalY , 1 , 1) ;

    // instantiate ChannelConfig as CallOutBox
    channelConfig->setSize(GUI::CHANNEL_CONFIG_W , GUI::CHANNEL_CONFIG_H) ;
    CallOutBox::launchAsynchronously(channelConfig , modalRect , mainContent) ;
  }
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Channel" componentName="Channel"
                 parentClasses="public Component, public ButtonListener, public SliderListener, public Value::Listener"
                 constructorParams="ValueTree channel_store" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="60" initialHeight="252">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10" fill="solid: ff000000" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <TOGGLEBUTTON name="xmitButton" id="f45f759640162c62" memberName="xmitButton"
                virtualName="" explicitFocusOrder="1" pos="4 4 36 12" txtcol="ff808080"
                buttonText="XMIT" connectedEdges="0" needsCallback="0" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="muteButton" id="263020526add917" memberName="muteButton"
                virtualName="" explicitFocusOrder="2" pos="4 20 36 12" txtcol="ff808080"
                buttonText="MUTE" connectedEdges="0" needsCallback="0" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="soloButton" id="3b096c8c7df5c792" memberName="soloButton"
                virtualName="" explicitFocusOrder="3" pos="4 36 36 12" txtcol="ff808080"
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
          textboxbkgd="ff000000" min="-1" max="1" int="0" style="Rotary"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="0" textBoxHeight="12"
          skewFactor="1"/>
  <SLIDER name="gainSlider" id="e34ef13291b2ec40" memberName="gainSlider"
          virtualName="" explicitFocusOrder="7" pos="22 92 16 128" textboxtext="ff808080"
          textboxbkgd="0" min="-120" max="20" int="0" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="48"
          textBoxHeight="12" skewFactor="1"/>
  <LABEL name="nameLabel" id="66bafa468220da02" memberName="nameLabel"
         virtualName="" explicitFocusOrder="8" pos="4 236 52 12" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="channel name" editableSingleClick="1"
         editableDoubleClick="1" focusDiscardsChanges="1" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="stereoLabel" id="deaf84482cab9f7d" memberName="stereoLabel"
         virtualName="" explicitFocusOrder="0" pos="12 72 36 12" textCol="ff008000"
         edTextCol="ff000000" edBkgCol="0" labelText="ST" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10" bold="1" italic="0" justification="36"/>
  <SLIDER name="vuLeftSlider" id="fbb656fdc87f46ed" memberName="vuLeftSlider"
          virtualName="" explicitFocusOrder="0" pos="6 92 16 128" textboxtext="ff808080"
          textboxbkgd="0" min="-120" max="20" int="0" style="LinearBar"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="48"
          textBoxHeight="12" skewFactor="1"/>
  <SLIDER name="vuRightSlider" id="31c942b6caa362dd" memberName="vuRightSlider"
          virtualName="" explicitFocusOrder="0" pos="38 92 16 128" textboxtext="ff808080"
          textboxbkgd="0" min="-120" max="20" int="0" style="LinearBar"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="48"
          textBoxHeight="12" skewFactor="1"/>
  <LABEL name="vuLeftLabel" id="cdc1fb3056af7c9b" memberName="vuLeftLabel"
         virtualName="" explicitFocusOrder="0" pos="4 224 24 12" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="-120" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="vuRightLabel" id="4bb31261e6795ae1" memberName="vuRightLabel"
         virtualName="" explicitFocusOrder="0" pos="32 224 24 12" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="-120" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
