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
#include "Mixer.h"

//[/Headers]

#include "Channel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Channel::Channel (ValueTree channel_config)
{
    setName ("Channel");
    addAndMakeVisible (xmitButton = new ToggleButton ("xmitButton"));
    xmitButton->setButtonText (TRANS("XMIT"));
    xmitButton->addListener (this);
    xmitButton->setColour (ToggleButton::textColourId, Colours::grey);

    addAndMakeVisible (muteButton = new ToggleButton ("muteButton"));
    muteButton->setButtonText (TRANS("MUTE"));
    muteButton->addListener (this);
    muteButton->setColour (ToggleButton::textColourId, Colours::grey);

    addAndMakeVisible (soloButton = new ToggleButton ("soloButton"));
    soloButton->setButtonText (TRANS("SOLO"));
    soloButton->addListener (this);
    soloButton->setColour (ToggleButton::textColourId, Colours::grey);

    addAndMakeVisible (panSlider = new Slider ("panSlider"));
    panSlider->setRange (-1, 1, 0);
    panSlider->setSliderStyle (Slider::Rotary);
    panSlider->setTextBoxStyle (Slider::NoTextBox, true, 0, 12);
    panSlider->setColour (Slider::textBoxTextColourId, Colours::grey);
    panSlider->setColour (Slider::textBoxBackgroundColourId, Colours::black);
    panSlider->addListener (this);

    addAndMakeVisible (vuSlider = new Slider ("vuSlider"));
    vuSlider->setRange (-120, 20, 0);
    vuSlider->setSliderStyle (Slider::LinearBar);
    vuSlider->setTextBoxStyle (Slider::NoTextBox, true, 48, 12);
    vuSlider->setColour (Slider::textBoxTextColourId, Colours::grey);
    vuSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00000000));
    vuSlider->addListener (this);

    addAndMakeVisible (gainSlider = new Slider ("gainSlider"));
    gainSlider->setRange (-120, 20, 0);
    gainSlider->setSliderStyle (Slider::LinearVertical);
    gainSlider->setTextBoxStyle (Slider::NoTextBox, true, 48, 12);
    gainSlider->setColour (Slider::textBoxTextColourId, Colours::grey);
    gainSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00000000));
    gainSlider->addListener (this);

    addAndMakeVisible (vuLabel = new Label ("vuLabel",
                                            TRANS("-120")));
    vuLabel->setFont (Font (10.00f, Font::plain));
    vuLabel->setJustificationType (Justification::centred);
    vuLabel->setEditable (false, false, false);
    vuLabel->setColour (Label::textColourId, Colours::grey);
    vuLabel->setColour (TextEditor::textColourId, Colours::black);
    vuLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (gainLabel = new Label ("gainLabel",
                                              TRANS("-120")));
    gainLabel->setFont (Font (10.00f, Font::plain));
    gainLabel->setJustificationType (Justification::centred);
    gainLabel->setEditable (false, false, false);
    gainLabel->setColour (Label::textColourId, Colours::grey);
    gainLabel->setColour (TextEditor::textColourId, Colours::black);
    gainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nameLabel = new Label ("nameLabel",
                                              TRANS("channel name")));
    nameLabel->setFont (Font (12.00f, Font::plain));
    nameLabel->setJustificationType (Justification::centred);
    nameLabel->setEditable (false, false, false);
    nameLabel->setColour (Label::textColourId, Colours::grey);
    nameLabel->setColour (TextEditor::textColourId, Colours::black);
    nameLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (removeButton = new TextButton ("removeButton"));
    removeButton->setButtonText (TRANS("X"));
    removeButton->addListener (this);
    removeButton->setColour (TextButton::buttonColourId, Colour (0xff400000));
    removeButton->setColour (TextButton::buttonOnColourId, Colours::maroon);
    removeButton->setColour (TextButton::textColourOnId, Colours::red);
    removeButton->setColour (TextButton::textColourOffId, Colours::red);


    //[UserPreSize]

  this->vuSlider ->setSliderStyle(Slider::LinearBarVertical) ;

    //[/UserPreSize]

    setSize (60, 252);


    //[Constructor] You can add your own custom stuff here..

  String name      = String((this->configStore = channel_config).getType()) ;
  double volume    = double( this->configStore[CONFIG::VOLUME_IDENTIFIER]) ;
  double pan       = double( this->configStore[CONFIG::PAN_IDENTIFIER]) ;
  bool   is_xmit   = bool(   this->configStore[CONFIG::XMIT_IDENTIFIER]) ;
  bool   is_muted  = bool(   this->configStore[CONFIG::MUTE_IDENTIFIER]) ;
  bool   is_solo   = bool(   this->configStore[CONFIG::SOLO_IDENTIFIER]) ;
  int    source_ch = int(    this->configStore[CONFIG::SOURCE_N_IDENTIFIER]) ;
  bool   is_stereo = bool(   this->configStore[CONFIG::STEREO_IDENTIFIER]) ;

  this->nameLabel   ->setText(           name     , juce::dontSendNotification) ;
  this->gainSlider  ->setValue(          volume) ;
  this->gainLabel   ->setText(String(int(volume)) , juce::dontSendNotification) ;
  this->panSlider   ->setValue(          pan) ;
  this->xmitButton  ->setToggleState(    is_xmit  , juce::dontSendNotification) ;
  this->muteButton  ->setToggleState(    is_muted , juce::dontSendNotification) ;
  this->soloButton  ->setToggleState(    is_solo  , juce::dontSendNotification) ;
//   this->sourceLabel ->setText(String(    source_ch , juce::dontSendNotification) ;)) ; // TODO: (issue #25)
//   this->stereoButton->setToggleState(    is_stereo , juce::dontSendNotification) ;) ;  // TODO: (issue #25)

  this->removeButton->setVisible(false) ;
  this->gainSlider  ->setDoubleClickReturnValue(true , 0.0) ;
  this->panSlider   ->setDoubleClickReturnValue(true , 0.0) ;
  this->vuSlider    ->setInterceptsMouseClicks(false , false) ;

DEBUG_TRACE_ADDED_CHANNEL

    //[/Constructor]
}

Channel::~Channel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    xmitButton = nullptr;
    muteButton = nullptr;
    soloButton = nullptr;
    panSlider = nullptr;
    vuSlider = nullptr;
    gainSlider = nullptr;
    vuLabel = nullptr;
    gainLabel = nullptr;
    nameLabel = nullptr;
    removeButton = nullptr;


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
    panSlider->setBounds (12, 52, 36, 36);
    vuSlider->setBounds (4, 92, 24, 128);
    gainSlider->setBounds (32, 92, 24, 128);
    vuLabel->setBounds (4, 224, 24, 12);
    gainLabel->setBounds (32, 224, 24, 12);
    nameLabel->setBounds (4, 236, 52, 12);
    removeButton->setBounds (45, 0, 15, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Channel::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]

  handleButtonClicked(buttonThatWasClicked) ; return ;

    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == xmitButton)
    {
        //[UserButtonCode_xmitButton] -- add your button handler code here..
        //[/UserButtonCode_xmitButton]
    }
    else if (buttonThatWasClicked == muteButton)
    {
        //[UserButtonCode_muteButton] -- add your button handler code here..
        //[/UserButtonCode_muteButton]
    }
    else if (buttonThatWasClicked == soloButton)
    {
        //[UserButtonCode_soloButton] -- add your button handler code here..
        //[/UserButtonCode_soloButton]
    }
    else if (buttonThatWasClicked == removeButton)
    {
        //[UserButtonCode_removeButton] -- add your button handler code here..

        //[/UserButtonCode_removeButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
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
      setChannelConfig(CONFIG::PAN_IDENTIFIER , var(pan)) ;

        //[/UserSliderCode_panSlider]
    }
    else if (sliderThatWasMoved == vuSlider)
    {
        //[UserSliderCode_vuSlider] -- add your slider handling code here..

      // vuSlider control is user read/only

        //[/UserSliderCode_vuSlider]
    }
    else if (sliderThatWasMoved == gainSlider)
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..

      // set stored config for this channel volume (configures NJClient implicitly)
      double gain = sliderThatWasMoved->getValue() ;
      gainLabel->setText(String(int(gain)) , juce::dontSendNotification) ;
      setChannelConfig(CONFIG::VOLUME_IDENTIFIER , var(gain)) ;

        //[/UserSliderCode_gainSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* Channel class public class methods */

void Channel::updateChannelVU(double vu)
{
#if DEBUG_DUPLICATE_CHANNEL_NAMES_VU_BUG
DBG("Channel::updateChannelVU() vu=" + String(vu) + " " + getParentComponent()->getComponentID() + "->" + getComponentID()) ;
#endif // DEBUG_DUPLICATE_CHANNEL_NAMES_VU_BUG

  this->vuSlider->setValue(vu) ;
  this->vuLabel ->setText(String(int(vu)) , juce::dontSendNotification) ;
  this->vuSlider->setColour(Slider::thumbColourId , ((vu > 0.0)?
                                                        Colours::red :
                                                        Colour(0xFFBBBBFF))) ;
  this->vuSlider->setColour(Slider::trackColourId , ((vu > 0.0)?
                                                        Colour(0x01800000) :
                                                        Colour(0x01008000))) ;
}


/* Channel class private class methods */

void Channel::handleButtonClicked(Button* a_button)
{
  // set stored config for this channel (configures NJClient implicitly)
  if      (a_button == xmitButton)
    setChannelConfig(CONFIG::XMIT_IDENTIFIER , var(a_button->getToggleState())) ;
  else if (a_button == muteButton)
    setChannelConfig(CONFIG::MUTE_IDENTIFIER , var(a_button->getToggleState())) ;
  else if (a_button == soloButton)
    setChannelConfig(CONFIG::SOLO_IDENTIFIER , var(a_button->getToggleState())) ;
}

void Channel::setChannelConfig(Identifier config_key , var value)
{ this->configStore.setProperty(config_key , value , nullptr) ; }


/* MasterChannels , LocalChannels , RemoteChannels classes private class methods */

MasterChannel::MasterChannel(ValueTree channel_store) : Channel(channel_store)
{
  this->xmitButton  ->setVisible(false) ;
  this->soloButton  ->setVisible(false) ;
}

LocalChannel::LocalChannel(ValueTree channel_store) : Channel(channel_store)
{
  this->xmitButton->setButtonText(GUI::XMIT_LABEL_TEXT) ;
}

RemoteChannel::RemoteChannel(ValueTree channel_store) : Channel(channel_store)
{
  this->xmitButton->setButtonText(GUI::RCV_LABEL_TEXT) ;
}

void LocalChannel::buttonClicked(Button* a_button)
{
  handleButtonClicked(a_button) ;

  if (a_button == removeButton)
  {
// TODO: must we delete this ValueTree also ?
    // destroy stored config for this channel (configures NJClient implicitly)
    this->configStore.getParent().removeChild(this->configStore , nullptr) ;

    // remove this channel GUI
    ((LocalChannels*)getParentComponent())->removeChannel(this) ;
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
                 parentClasses="public Component" constructorParams="ValueTree channel_config"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="60" initialHeight="252">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10" fill="solid: ff000000" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <TOGGLEBUTTON name="xmitButton" id="f45f759640162c62" memberName="xmitButton"
                virtualName="" explicitFocusOrder="0" pos="4 4 36 12" txtcol="ff808080"
                buttonText="XMIT" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="muteButton" id="263020526add917" memberName="muteButton"
                virtualName="" explicitFocusOrder="0" pos="4 20 36 12" txtcol="ff808080"
                buttonText="MUTE" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="soloButton" id="3b096c8c7df5c792" memberName="soloButton"
                virtualName="" explicitFocusOrder="0" pos="4 36 36 12" txtcol="ff808080"
                buttonText="SOLO" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <SLIDER name="panSlider" id="aa7c4f80abb603e9" memberName="panSlider"
          virtualName="" explicitFocusOrder="0" pos="12 52 36 36" textboxtext="ff808080"
          textboxbkgd="ff000000" min="-1" max="1" int="0" style="Rotary"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="0" textBoxHeight="12"
          skewFactor="1"/>
  <SLIDER name="vuSlider" id="fbb656fdc87f46ed" memberName="vuSlider" virtualName=""
          explicitFocusOrder="0" pos="4 92 24 128" textboxtext="ff808080"
          textboxbkgd="0" min="-120" max="20" int="0" style="LinearBar"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="48"
          textBoxHeight="12" skewFactor="1"/>
  <SLIDER name="gainSlider" id="e34ef13291b2ec40" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="32 92 24 128" textboxtext="ff808080"
          textboxbkgd="0" min="-120" max="20" int="0" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="48"
          textBoxHeight="12" skewFactor="1"/>
  <LABEL name="vuLabel" id="cdc1fb3056af7c9b" memberName="vuLabel" virtualName=""
         explicitFocusOrder="0" pos="4 224 24 12" textCol="ff808080" edTextCol="ff000000"
         edBkgCol="0" labelText="-120" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="10"
         bold="0" italic="0" justification="36"/>
  <LABEL name="gainLabel" id="4bb31261e6795ae1" memberName="gainLabel"
         virtualName="" explicitFocusOrder="0" pos="32 224 24 12" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="-120" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="nameLabel" id="66bafa468220da02" memberName="nameLabel"
         virtualName="" explicitFocusOrder="0" pos="4 236 52 12" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="channel name" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="removeButton" id="becd368b728d32c0" memberName="removeButton"
              virtualName="" explicitFocusOrder="0" pos="45 0 15 16" bgColOff="ff400000"
              bgColOn="ff800000" textCol="ffff0000" textColOn="ffff0000" buttonText="X"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
