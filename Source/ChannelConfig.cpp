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
ChannelConfig::ChannelConfig ()
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
    nameText->setText (TRANS("unnamed"));

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
    channelSelect->setTextWhenNothingSelected (String::empty);
    channelSelect->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
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

  nameText->setText(CONFIG::DEFAULT_CHANNEL_NAME) ;
  channelSelect->setColour(ComboBox::textColourId       , Colours::grey) ;
  channelSelect->setColour(ComboBox::backgroundColourId , Colours::black) ;
// TODO: none of these change option colors
//   channelSelect->setColour(ComboBox::buttonColourId     , Colours::red) ;
//   channelSelect->setColour(ComboBox::arrowColourId     , Colours::blue) ;
//   channelSelect->setColour(ComboBox::outlineColourId     , Colours::green) ;
//   channelSelect->setColour(Label::backgroundColourId , Colours::green) ;
//   channelSelect->setColour(TextEditor::backgroundColourId , Colours::green) ;

  this->is_stereo = false ; createChannelSelectOptions() ; populateChannelSelect() ;

  monoButton  ->addListener(this) ;
  stereoButton->addListener(this) ;
  okButton    ->addListener(this) ;
  cancelButton->addListener(this) ;

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
  bool was_stereo               = this->is_stereo ;
  bool is_stereo                = this->stereoButton->getToggleState() ;
  bool has_toggle_state_changed = (was_stereo != (this->is_stereo = is_stereo)) ;

  if      (has_toggle_state_changed) populateChannelSelect() ;
  else if (a_button == okButton)
  {
    String channel_name = this->nameText->getText() ;
    int    selection_n  = this->channelSelect->getSelectedItemIndex() ;
    LinJam::AddLocalChannel(channel_name , this->is_stereo , selection_n) ;

    ((CallOutBox*)getParentComponent())->dismiss() ;
  }
  else if (a_button == cancelButton)
    ((CallOutBox*)getParentComponent())->dismiss() ;
}

void ChannelConfig::createChannelSelectOptions()
{
  Array<int> free_channels = LinJam::GetFreeInputChannels() ;
  for (int free_channel_n = 0 ; free_channel_n < free_channels.size() ; ++free_channel_n)
  {
    int channel_n = free_channels.getUnchecked(free_channel_n) ;
    this->freeInputChannels.add("input " + String(channel_n)) ;
  }
  Array<int> free_channel_pairs = LinJam::GetFreeInputChannelPairs() ;
  for (int free_pair_n = 0 ; free_pair_n < free_channel_pairs.size() ; ++free_pair_n)
  {
    int channel_n = free_channel_pairs.getUnchecked(free_pair_n) ;
    this->freeInputChannelPairs.add("inputs " + String(channel_n)    +
                                    " & "     + String(channel_n + 1)) ;
  }
}

void ChannelConfig::populateChannelSelect()
{
  channelSelect->clear() ;
  if (!this->is_stereo)
       channelSelect->addItemList(this->freeInputChannels     , 1) ;
  else channelSelect->addItemList(this->freeInputChannelPairs , 1) ;
  channelSelect->setSelectedItemIndex(0) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ChannelConfig" componentName=""
                 parentClasses="public Component, public ButtonListener" constructorParams=""
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
              bkgcol="ff000000" initialText="unnamed" multiline="0" retKeyStartsLine="0"
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
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
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
