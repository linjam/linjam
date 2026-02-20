/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.12

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...

#include "LinJam.h"

//[/Headers]

#include "ConfigChannel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigChannel::ConfigChannel (ValueTree channel_store)
    : channelStore(channel_store)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    nameLabel.reset (new juce::Label ("nameLabel",
                                      TRANS ("channel name")));
    addAndMakeVisible (nameLabel.get());
    nameLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    nameLabel->setJustificationType (juce::Justification::centredTop);
    nameLabel->setEditable (false, false, false);
    nameLabel->setColour (juce::Label::textColourId, juce::Colours::white);
    nameLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    nameLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    nameLabel->setBounds (24, 24, 152, 16);

    nameText.reset (new juce::TextEditor ("nameText"));
    addAndMakeVisible (nameText.get());
    nameText->setExplicitFocusOrder (1);
    nameText->setMultiLine (false);
    nameText->setReturnKeyStartsNewLine (false);
    nameText->setReadOnly (false);
    nameText->setScrollbarsShown (false);
    nameText->setCaretVisible (true);
    nameText->setPopupMenuEnabled (false);
    nameText->setColour (juce::TextEditor::textColourId, juce::Colours::grey);
    nameText->setColour (juce::TextEditor::backgroundColourId, juce::Colours::black);
    nameText->setText (juce::String());

    nameText->setBounds (24, 44, 152, 16);

    monoButton.reset (new juce::ToggleButton ("monoButton"));
    addAndMakeVisible (monoButton.get());
    monoButton->setExplicitFocusOrder (2);
    monoButton->setButtonText (TRANS ("mono"));
    monoButton->setRadioGroupId (1);
    monoButton->setToggleState (true, juce::dontSendNotification);
    monoButton->setColour (juce::ToggleButton::textColourId, juce::Colours::white);

    monoButton->setBounds (34, 64, 64, 16);

    stereoButton.reset (new juce::ToggleButton ("stereoButton"));
    addAndMakeVisible (stereoButton.get());
    stereoButton->setExplicitFocusOrder (3);
    stereoButton->setButtonText (TRANS ("stereo"));
    stereoButton->setRadioGroupId (1);
    stereoButton->setColour (juce::ToggleButton::textColourId, juce::Colours::white);

    stereoButton->setBounds (102, 64, 64, 16);

    inputLabel.reset (new juce::Label ("inputLabel",
                                       TRANS ("input channel")));
    addAndMakeVisible (inputLabel.get());
    inputLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    inputLabel->setJustificationType (juce::Justification::centredTop);
    inputLabel->setEditable (false, false, false);
    inputLabel->setColour (juce::Label::textColourId, juce::Colours::white);
    inputLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    inputLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    inputLabel->setBounds (24, 84, 152, 16);

    channelSelect.reset (new juce::ComboBox ("channelSelect"));
    addAndMakeVisible (channelSelect.get());
    channelSelect->setExplicitFocusOrder (4);
    channelSelect->setEditableText (false);
    channelSelect->setJustificationType (juce::Justification::centredLeft);
    channelSelect->setTextWhenNothingSelected (TRANS ("(select channel)"));
    channelSelect->setTextWhenNoChoicesAvailable (TRANS ("(no free channels)"));
    channelSelect->addListener (this);

    channelSelect->setBounds (24, 104, 152, 16);

    okButton.reset (new juce::TextButton ("okButton"));
    addAndMakeVisible (okButton.get());
    okButton->setExplicitFocusOrder (5);
    okButton->setButtonText (TRANS ("ok"));

    okButton->setBounds (34, 152, 64, 24);

    cancelButton.reset (new juce::TextButton ("cancelButton"));
    addAndMakeVisible (cancelButton.get());
    cancelButton->setExplicitFocusOrder (6);
    cancelButton->setButtonText (TRANS ("cancel"));

    cancelButton->setBounds (102, 152, 64, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (200, 200);


    //[Constructor] You can add your own custom stuff here..

  this->nameText     ->setColour(CaretComponent::caretColourId , Colours::white) ;
  this->channelSelect->setColour(ComboBox::textColourId        , Colours::grey) ;
  this->channelSelect->setColour(ComboBox::backgroundColourId  , Colours::black) ;
  // TODO: change option colors

  // set channel config state
  this->channelStore =     channel_store ;
  this->isNewChannel =    (channel_store.getType() == CONFIG::NEWCHANNEL_ID) ;
  String client_name = str(channel_store[CONFIG::CHANNEL_NAME_ID]) ;
  this->sourceN      = int(channel_store[CONFIG::SOURCE_N_ID    ]) ;
  this->isStereo     = int(channel_store[CONFIG::STEREO_ID      ]) != CONFIG::MONO ;

  // set GUI state and populate input select options
  this->nameText    ->setText(LinJamConfig::TrimStereoName(client_name)) ;
  this->stereoButton->setToggleState(this->isStereo , juce::dontSendNotification) ;
  createChannelSelectOptions() ; populateChannelSelect() ;

  // local event handlers
  this->monoButton  ->addListener(this) ;
  this->stereoButton->addListener(this) ;
  this->okButton    ->addListener(this) ;
  this->cancelButton->addListener(this) ;

    //[/Constructor]
}

ConfigChannel::~ConfigChannel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    nameLabel = nullptr;
    nameText = nullptr;
    monoButton = nullptr;
    stereoButton = nullptr;
    inputLabel = nullptr;
    channelSelect = nullptr;
    okButton = nullptr;
    cancelButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConfigChannel::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 0.0f, y = 0.0f, width = static_cast<float> (getWidth() - 0), height = static_cast<float> (getHeight() - 0);
        juce::Colour fillColour = juce::Colour (0xff202020);
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

void ConfigChannel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigChannel::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == channelSelect.get())
    {
        //[UserComboBoxCode_channelSelect] -- add your combo box handling code here..
        //[/UserComboBoxCode_channelSelect]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* event handlers */

void ConfigChannel::buttonClicked(Button* a_button)
{
  if (a_button == this->monoButton  .get() ||
      a_button == this->stereoButton.get()  ) refreshHardwareChannels() ;
  if (a_button == this->okButton    .get()  ) configureLocalChannel() ;
  if (a_button == this->okButton    .get() ||
      a_button == this->cancelButton.get()  ) ((CallOutBox*)getParentComponent())->dismiss() ;
}


/* helpers */

String ConfigChannel::makeMonoSelectOption(int channel_n)
{
  int display_channel_n = channel_n + 1 ;
  return "input " + String(display_channel_n) ;
}

String ConfigChannel::makeStereoSelectOption(int channel_n)
{
  int display_channel_n = channel_n + 1 ;
  return "inputs " + String(display_channel_n)   +
         " & "     + String(display_channel_n + 1) ;
}

void ConfigChannel::createChannelSelectOptions()
{
  this->freeAudioSourceNs     = LinJam::GetFreeSources() ;
  this->freeAudioSourcePairNs = LinJam::GetFreeSourcePairs() ;

  int n_channels      = this->freeAudioSourceNs.size() ;
  int n_channel_pairs = this->freeAudioSourcePairNs.size() ;

  for (int free_channel_n = 0 ; free_channel_n < n_channels ; ++free_channel_n)
  {
    int channel_n = this->freeAudioSourceNs.getUnchecked(free_channel_n) ;
    this->freeAudioSourceOptions.add(makeMonoSelectOption(channel_n)) ;
  }

  for (int free_pair_n = 0 ; free_pair_n < n_channel_pairs ; ++free_pair_n)
  {
    int channel_n = this->freeAudioSourcePairNs.getUnchecked(free_pair_n) ;
    this->freeAudioSourcePairOptions.add(makeStereoSelectOption(channel_n)) ;
  }
}

void ConfigChannel::populateChannelSelect()
{
  this->channelSelect->clear() ;
  StringArray options = (!this->isStereo)                  ?
                          this->freeAudioSourceOptions     :
                          this->freeAudioSourcePairOptions ;
  this->channelSelect->addItemList(options , 1) ;

  // pre-select current input option for existing channel
  int preselection_n = ( this->isNewChannel                               ) ? 0 :
                       (!this->isStereo                                   ) ?
                         this->freeAudioSourceNs    .indexOf(this->sourceN) :
                         this->freeAudioSourcePairNs.indexOf(this->sourceN) ;
  this->channelSelect->setSelectedItemIndex((~preselection_n) ? preselection_n : 0) ;
}

void ConfigChannel::refreshHardwareChannels()
{
  bool was_selected_stereo          = this->isStereo ;
  this->isStereo                    = this->stereoButton->getToggleState() ;
  bool has_stereo_selection_changed = (was_selected_stereo != this->isStereo) ;
  if (has_stereo_selection_changed) populateChannelSelect() ;
}

void ConfigChannel::configureLocalChannel()
{
  String gui_name      = this->nameText     ->getText() ;
  int    selection_n   = this->channelSelect->getSelectedItemIndex() ;
  int    stereo_status = (!this->isStereo) ? CONFIG::MONO : CONFIG::STEREO_L ;
  int    source_n      = (!this->isStereo) ? this->freeAudioSourceNs    [selection_n] :
                                              this->freeAudioSourcePairNs[selection_n] ;
  String client_name   = LinJamConfig::MakeStereoName(gui_name , stereo_status) ;

  // update existing channel asynchronously
  this->channelStore.setProperty(CONFIG::CHANNEL_NAME_ID , client_name   , nullptr)
                    .setProperty(CONFIG::SOURCE_N_ID     , source_n      , nullptr)
                    .setProperty(CONFIG::STEREO_ID       , stereo_status , nullptr) ;

  // or create new local channel
  if (this->isNewChannel) LinJam::AddLocalChannel(this->channelStore) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConfigChannel" componentName=""
                 parentClasses="public Component, public ButtonListener" constructorParams="ValueTree channel_store"
                 variableInitialisers="channelStore(channel_store)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="200" initialHeight="200">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10.0" fill="solid: ff202020" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <LABEL name="nameLabel" id="eb57b2d805d2eff8" memberName="nameLabel"
         virtualName="" explicitFocusOrder="0" pos="24 24 152 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="channel name" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="12"/>
  <TEXTEDITOR name="nameText" id="f721d2f898b8b762" memberName="nameText" virtualName=""
              explicitFocusOrder="1" pos="24 44 152 16" textcol="ff808080"
              bkgcol="ff000000" initialText="" multiline="0" retKeyStartsLine="0"
              readonly="0" scrollbars="0" caret="1" popupmenu="0"/>
  <TOGGLEBUTTON name="monoButton" id="f830997aaae8295f" memberName="monoButton"
                virtualName="" explicitFocusOrder="2" pos="34 64 64 16" txtcol="ffffffff"
                buttonText="mono" connectedEdges="0" needsCallback="0" radioGroupId="1"
                state="1"/>
  <TOGGLEBUTTON name="stereoButton" id="f0fa912c23c0064f" memberName="stereoButton"
                virtualName="" explicitFocusOrder="3" pos="102 64 64 16" txtcol="ffffffff"
                buttonText="stereo" connectedEdges="0" needsCallback="0" radioGroupId="1"
                state="0"/>
  <LABEL name="inputLabel" id="9d36c2a259889270" memberName="inputLabel"
         virtualName="" explicitFocusOrder="0" pos="24 84 152 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="input channel" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="12"/>
  <COMBOBOX name="channelSelect" id="7a9c3a4f62832f42" memberName="channelSelect"
            virtualName="" explicitFocusOrder="4" pos="24 104 152 16" editable="0"
            layout="33" items="" textWhenNonSelected="(select channel)" textWhenNoItems="(no free channels)"/>
  <TEXTBUTTON name="okButton" id="504a4ad212ccb744" memberName="okButton" virtualName=""
              explicitFocusOrder="5" pos="34 152 64 24" buttonText="ok" connectedEdges="0"
              needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="cancelButton" id="4ec3eac10517595b" memberName="cancelButton"
              virtualName="" explicitFocusOrder="6" pos="102 152 64 24" buttonText="cancel"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

