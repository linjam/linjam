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

//[/Headers]

#include "ChannelConfig.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ChannelConfig::ChannelConfig (ValueTree config_store)
{
    addAndMakeVisible (nameLabel = new Label ("nameLabel",
                                              TRANS("channel name")));
    nameLabel->setFont (Font (15.00f, Font::plain));
    nameLabel->setJustificationType (Justification::centredTop);
    nameLabel->setEditable (false, false, false);
    nameLabel->setColour (Label::textColourId, Colours::grey);
    nameLabel->setColour (TextEditor::textColourId, Colours::black);
    nameLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nameText = new TextEditor ("nameText"));
    nameText->setExplicitFocusOrder (1);
    nameText->setMultiLine (false);
    nameText->setReturnKeyStartsNewLine (false);
    nameText->setReadOnly (false);
    nameText->setScrollbarsShown (false);
    nameText->setCaretVisible (true);
    nameText->setPopupMenuEnabled (false);
    nameText->setColour (TextEditor::textColourId, Colours::grey);
    nameText->setColour (TextEditor::backgroundColourId, Colours::black);
    nameText->setText (String::empty);

    addAndMakeVisible (monoButton = new ToggleButton ("monoButton"));
    monoButton->setExplicitFocusOrder (2);
    monoButton->setButtonText (TRANS("mono"));
    monoButton->setRadioGroupId (1);
    monoButton->setToggleState (true, dontSendNotification);
    monoButton->setColour (ToggleButton::textColourId, Colours::grey);

    addAndMakeVisible (stereoButton = new ToggleButton ("stereoButton"));
    stereoButton->setExplicitFocusOrder (3);
    stereoButton->setButtonText (TRANS("stereo"));
    stereoButton->setRadioGroupId (1);
    stereoButton->setColour (ToggleButton::textColourId, Colours::grey);

    addAndMakeVisible (inputLabel = new Label ("inputLabel",
                                               TRANS("input channel")));
    inputLabel->setFont (Font (15.00f, Font::plain));
    inputLabel->setJustificationType (Justification::centredTop);
    inputLabel->setEditable (false, false, false);
    inputLabel->setColour (Label::textColourId, Colours::grey);
    inputLabel->setColour (TextEditor::textColourId, Colours::black);
    inputLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (channelSelect = new ComboBox ("channelSelect"));
    channelSelect->setExplicitFocusOrder (4);
    channelSelect->setEditableText (false);
    channelSelect->setJustificationType (Justification::centredLeft);
    channelSelect->setTextWhenNothingSelected (TRANS("(select channel)"));
    channelSelect->setTextWhenNoChoicesAvailable (TRANS("(no free channels)"));
    channelSelect->addListener (this);

    addAndMakeVisible (okButton = new TextButton ("okButton"));
    okButton->setExplicitFocusOrder (5);
    okButton->setButtonText (TRANS("ok"));

    addAndMakeVisible (cancelButton = new TextButton ("cancelButton"));
    cancelButton->setExplicitFocusOrder (6);
    cancelButton->setButtonText (TRANS("cancel"));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (200, 200);


    //[Constructor] You can add your own custom stuff here..

  this->monoButton  ->addListener(this) ;
  this->stereoButton->addListener(this) ;
  this->okButton    ->addListener(this) ;
  this->cancelButton->addListener(this) ;

  this->nameText     ->setColour(CaretComponent::caretColourId , Colours::white) ;
  this->channelSelect->setColour(ComboBox::textColourId        , Colours::grey) ;
  this->channelSelect->setColour(ComboBox::backgroundColourId  , Colours::black) ;
  // TODO: change option colors

  // set initial channel state and populate input select options
  this->configStore       =     config_store ;
  Identifier channel_id   =     config_store.getType() ;
  String     channel_name =     configStore[CONFIG::CHANNEL_NAME_ID].toString() ;
  this->sourceN           = int(configStore[CONFIG::SOURCE_N_ID]) ;
  this->isStereo          = int(configStore[CONFIG::STEREO_ID]) != CONFIG::MONO ;
  this->isSelectedStereo  = this->isStereo ;
  this->isNewChannel      = (channel_id == CONFIG::NEWCHANNEL_ID) ;

  nameText    ->setText(channel_name) ;
  stereoButton->setToggleState(this->isSelectedStereo , juce::dontSendNotification) ;

  createChannelSelectOptions() ; populateChannelSelect() ;

    //[/Constructor]
}

ChannelConfig::~ChannelConfig()
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
void ChannelConfig::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff202020));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ChannelConfig::resized()
{
    nameLabel->setBounds (24, 24, 152, 16);
    nameText->setBounds (24, 44, 152, 16);
    monoButton->setBounds (34, 64, 64, 16);
    stereoButton->setBounds (102, 64, 64, 16);
    inputLabel->setBounds (24, 84, 152, 16);
    channelSelect->setBounds (24, 104, 152, 16);
    okButton->setBounds (34, 152, 64, 24);
    cancelButton->setBounds (102, 152, 64, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ChannelConfig::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == channelSelect)
    {
        //[UserComboBoxCode_channelSelect] -- add your combo box handling code here..
        //[/UserComboBoxCode_channelSelect]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void ChannelConfig::buttonClicked(Button* a_button)
{
  if      (a_button == this->monoButton || a_button == this->stereoButton)
  {
    bool was_selected_stereo          = this->isSelectedStereo ;
    this->isSelectedStereo            = this->stereoButton->getToggleState() ;
    bool has_stereo_selection_changed = (was_selected_stereo != this->isSelectedStereo) ;
    if (has_stereo_selection_changed) populateChannelSelect() ;
  }
  else if (a_button == this->okButton)
  {
    String channel_name  = this->nameText->getText() ;
    int    selection_n   = this->channelSelect->getSelectedItemIndex() ;
    bool   is_stereo     = this->isSelectedStereo ;
    int    stereo_status = (!is_stereo)? CONFIG::MONO : CONFIG::STEREO_L ;
    int    source_n      = (!is_stereo)? this->freeInputChannelNs    [selection_n] :
                                         this->freeInputChannelPairNs[selection_n] ;

    // update existing channel asynchronously
    this->configStore.setProperty(CONFIG::CHANNEL_NAME_ID , channel_name  , nullptr) ;
    this->configStore.setProperty(CONFIG::SOURCE_N_ID     , source_n      , nullptr) ;
    this->configStore.setProperty(CONFIG::STEREO_ID       , stereo_status , nullptr) ;

    // or create new local channel
    if (this->isNewChannel) LinJam::AddLocalChannel(this->configStore) ;

    ((CallOutBox*)getParentComponent())->dismiss() ;
  }
  else if (a_button == this->cancelButton)
    ((CallOutBox*)getParentComponent())->dismiss() ;
}

String ChannelConfig::makeMonoSelectOption(int channel_n)
{
  int display_channel_n = channel_n + 1 ;
  return "input " + String(display_channel_n) ;
}

String ChannelConfig::makeStereoSelectOption(int channel_n)
{
  int display_channel_n = channel_n + 1 ;
  return "inputs " + String(display_channel_n)   +
         " & "     + String(display_channel_n + 1) ;
}

void ChannelConfig::createChannelSelectOptions()
{
  this->freeInputChannelNs     = LinJam::GetFreeInputChannels() ;
  this->freeInputChannelPairNs = LinJam::GetFreeInputChannelPairs() ;

  int n_channels      = this->freeInputChannelNs.size() ;
  int n_channel_pairs = this->freeInputChannelPairNs.size() ;

  for (int free_channel_n = 0 ; free_channel_n < n_channels ; ++free_channel_n)
  {
    int channel_n = this->freeInputChannelNs.getUnchecked(free_channel_n) ;
    this->freeInputChannelOptions.add(makeMonoSelectOption(channel_n)) ;
  }

  for (int free_pair_n = 0 ; free_pair_n < n_channel_pairs ; ++free_pair_n)
  {
    int channel_n = this->freeInputChannelPairNs.getUnchecked(free_pair_n) ;
    this->freeInputChannelPairOptions.add(makeStereoSelectOption(channel_n)) ;
  }
}

void ChannelConfig::populateChannelSelect()
{
  this->channelSelect->clear() ;
  StringArray options = (!this->isSelectedStereo)           ?
                          this->freeInputChannelOptions     :
                          this->freeInputChannelPairOptions ;
  this->channelSelect->addItemList(options , 1) ;

  // pre-select current config option for existing channel or de-select
  bool has_stereo_state_changed = (this->isStereo != this->isSelectedStereo) ;
  int  preselection_n = (this->isNewChannel)                                 ? 0 :
                        (!this->isSelectedStereo)                                ?
                          this->freeInputChannelNs    .indexOf(this->sourceN)    :
                          this->freeInputChannelPairNs.indexOf(this->sourceN)    ;
  if (!(~preselection_n)) preselection_n = 0 ;
  this->channelSelect->setSelectedItemIndex(preselection_n) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ChannelConfig" componentName=""
                 parentClasses="public Component, public ButtonListener" constructorParams="ValueTree config_store"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="200" initialHeight="200">
  <BACKGROUND backgroundColour="ff202020"/>
  <LABEL name="nameLabel" id="eb57b2d805d2eff8" memberName="nameLabel"
         virtualName="" explicitFocusOrder="0" pos="24 24 152 16" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="channel name" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <TEXTEDITOR name="nameText" id="f721d2f898b8b762" memberName="nameText" virtualName=""
              explicitFocusOrder="1" pos="24 44 152 16" textcol="ff808080"
              bkgcol="ff000000" initialText="" multiline="0" retKeyStartsLine="0"
              readonly="0" scrollbars="0" caret="1" popupmenu="0"/>
  <TOGGLEBUTTON name="monoButton" id="f830997aaae8295f" memberName="monoButton"
                virtualName="" explicitFocusOrder="2" pos="34 64 64 16" txtcol="ff808080"
                buttonText="mono" connectedEdges="0" needsCallback="0" radioGroupId="1"
                state="1"/>
  <TOGGLEBUTTON name="stereoButton" id="f0fa912c23c0064f" memberName="stereoButton"
                virtualName="" explicitFocusOrder="3" pos="102 64 64 16" txtcol="ff808080"
                buttonText="stereo" connectedEdges="0" needsCallback="0" radioGroupId="1"
                state="0"/>
  <LABEL name="inputLabel" id="9d36c2a259889270" memberName="inputLabel"
         virtualName="" explicitFocusOrder="0" pos="24 84 152 16" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="input channel" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
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
