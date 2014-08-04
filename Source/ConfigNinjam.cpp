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

#include "Constants.h"

//[/Headers]

#include "ConfigNinjam.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigNinjam::ConfigNinjam (ValueTree config_store)
    : configStore(config_store)
{
    addAndMakeVisible (saveAudioLabel = new Label ("saveAudioLabel",
                                                   TRANS("save audio")));
    saveAudioLabel->setFont (Font (15.00f, Font::plain));
    saveAudioLabel->setJustificationType (Justification::centredTop);
    saveAudioLabel->setEditable (false, false, false);
    saveAudioLabel->setColour (Label::textColourId, Colours::white);
    saveAudioLabel->setColour (TextEditor::textColourId, Colours::black);
    saveAudioLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (saveAudioComboBox = new ComboBox ("saveAudioComboBox"));
    saveAudioComboBox->setExplicitFocusOrder (1);
    saveAudioComboBox->setEditableText (false);
    saveAudioComboBox->setJustificationType (Justification::centredLeft);
    saveAudioComboBox->setTextWhenNothingSelected (String::empty);
    saveAudioComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    saveAudioComboBox->addItem (TRANS("delete asap"), 1);
    saveAudioComboBox->addItem (TRANS("dont save"), 2);
    saveAudioComboBox->addItem (TRANS("save ogg"), 3);
    saveAudioComboBox->addItem (TRANS("save ogg and wav"), 4);
    saveAudioComboBox->addListener (this);

    addAndMakeVisible (oggMixdownButton = new ToggleButton ("oggMixdownButton"));
    oggMixdownButton->setExplicitFocusOrder (2);
    oggMixdownButton->setButtonText (TRANS("ogg mixdown"));
    oggMixdownButton->addListener (this);
    oggMixdownButton->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (wavMixdownButton = new ToggleButton ("wavMixdownButton"));
    wavMixdownButton->setExplicitFocusOrder (3);
    wavMixdownButton->setButtonText (TRANS("wav mixdown"));
    wavMixdownButton->addListener (this);
    wavMixdownButton->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (debugLevelLabel = new Label ("debugLevelLabel",
                                                    TRANS("debug level")));
    debugLevelLabel->setFont (Font (15.00f, Font::plain));
    debugLevelLabel->setJustificationType (Justification::centredTop);
    debugLevelLabel->setEditable (false, false, false);
    debugLevelLabel->setColour (Label::textColourId, Colours::white);
    debugLevelLabel->setColour (TextEditor::textColourId, Colours::black);
    debugLevelLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (debugLevelComboBox = new ComboBox ("debugLevelComboBox"));
    debugLevelComboBox->setExplicitFocusOrder (4);
    debugLevelComboBox->setEditableText (false);
    debugLevelComboBox->setJustificationType (Justification::centredLeft);
    debugLevelComboBox->setTextWhenNothingSelected (String::empty);
    debugLevelComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    debugLevelComboBox->addItem (TRANS("silent"), 1);
    debugLevelComboBox->addItem (TRANS("audio"), 2);
    debugLevelComboBox->addItem (TRANS("audio and network"), 3);
    debugLevelComboBox->addItem (TRANS("linjam trace"), 4);
    debugLevelComboBox->addListener (this);

    addAndMakeVisible (saveLogButton = new ToggleButton ("saveLogButton"));
    saveLogButton->setExplicitFocusOrder (5);
    saveLogButton->setButtonText (TRANS("save log"));
    saveLogButton->addListener (this);
    saveLogButton->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (hideBotsButton = new ToggleButton ("hideBotsButton"));
    hideBotsButton->setExplicitFocusOrder (6);
    hideBotsButton->setButtonText (TRANS("hide bots"));
    hideBotsButton->addListener (this);
    hideBotsButton->setToggleState (true, dontSendNotification);
    hideBotsButton->setColour (ToggleButton::textColourId, Colours::white);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (192, 172);


    //[Constructor] You can add your own custom stuff here..

  int  save_audio_mode    = int( this->configStore[CONFIG::SAVE_AUDIO_MODE_ID]) ;
  int  mixdown_mode       = int( this->configStore[CONFIG::MIXDOWN_MODE_ID]) ;
  int  debug_level        = int( this->configStore[CONFIG::DEBUG_LEVEL_ID]) ;
  bool should_save_log    = bool(this->configStore[CONFIG::SHOULD_SAVE_LOG_KEY]) ;
  bool should_hide_bots   = bool(this->configStore[CONFIG::SHOULD_HIDE_BOTS_KEY]) ;
  bool should_mixdown_ogg = !!(mixdown_mode & (int)NJClient::SAVE_MIXDOWN_OGG) ;
  bool should_mixdown_wav = !!(mixdown_mode & (int)NJClient::SAVE_MIXDOWN_WAV) ;

  saveAudioComboBox ->setSelectedId(save_audio_mode + CONFIG::SAVE_AUDIO_ENUM_OFFSET) ;
  debugLevelComboBox->setSelectedItemIndex(debug_level) ;
  oggMixdownButton  ->setToggleState(should_mixdown_ogg , juce::dontSendNotification) ;
  wavMixdownButton  ->setToggleState(should_mixdown_wav , juce::dontSendNotification) ;
  saveLogButton     ->setToggleState(should_save_log    , juce::dontSendNotification) ;
  hideBotsButton    ->setToggleState(should_hide_bots   , juce::dontSendNotification) ;

    //[/Constructor]
}

ConfigNinjam::~ConfigNinjam()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    saveAudioLabel = nullptr;
    saveAudioComboBox = nullptr;
    oggMixdownButton = nullptr;
    wavMixdownButton = nullptr;
    debugLevelLabel = nullptr;
    debugLevelComboBox = nullptr;
    saveLogButton = nullptr;
    hideBotsButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConfigNinjam::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0xff002000));
    g.fillRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), static_cast<float> (getHeight() - 0), 10.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConfigNinjam::resized()
{
    saveAudioLabel->setBounds (20, 18, 152, 16);
    saveAudioComboBox->setBounds (20, 38, 152, 16);
    oggMixdownButton->setBounds (20, 58, 74, 16);
    wavMixdownButton->setBounds (98, 58, 74, 16);
    debugLevelLabel->setBounds (20, 86, 152, 16);
    debugLevelComboBox->setBounds (20, 106, 152, 16);
    saveLogButton->setBounds (20, 130, 74, 16);
    hideBotsButton->setBounds (98, 130, 74, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigNinjam::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]

  Identifier config_key ;
  var        value ;

    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == saveAudioComboBox)
    {
        //[UserComboBoxCode_saveAudioComboBox] -- add your combo box handling code here..

      config_key = CONFIG::SAVE_AUDIO_MODE_ID ;
      value      = var(saveAudioComboBox->getSelectedId() - CONFIG::SAVE_AUDIO_ENUM_OFFSET) ;

        //[/UserComboBoxCode_saveAudioComboBox]
    }
    else if (comboBoxThatHasChanged == debugLevelComboBox)
    {
        //[UserComboBoxCode_debugLevelComboBox] -- add your combo box handling code here..

      config_key = CONFIG::DEBUG_LEVEL_ID ;
      value      = var(debugLevelComboBox->getSelectedItemIndex()) ;

        //[/UserComboBoxCode_debugLevelComboBox]
    }

    //[UsercomboBoxChanged_Post]

  setConfig(config_key , value) ;

    //[/UsercomboBoxChanged_Post]
}

void ConfigNinjam::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]

  int mixdown_mode                                      = (int)NJClient::SAVE_MIXDOWN_NONE ;
  if (oggMixdownButton->getToggleState()) mixdown_mode |= (int)NJClient::SAVE_MIXDOWN_OGG ;
  if (wavMixdownButton->getToggleState()) mixdown_mode |= (int)NJClient::SAVE_MIXDOWN_WAV ;

  Identifier config_key ;
  var        value ;
  var        mixdown_value = var(mixdown_mode) ;
  var        toggle_value  = var(buttonThatWasClicked->getToggleState()) ;

    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == oggMixdownButton)
    {
        //[UserButtonCode_oggMixdownButton] -- add your button handler code here..

      config_key = CONFIG::MIXDOWN_MODE_ID ;
      value      = mixdown_value ;

        //[/UserButtonCode_oggMixdownButton]
    }
    else if (buttonThatWasClicked == wavMixdownButton)
    {
        //[UserButtonCode_wavMixdownButton] -- add your button handler code here..

      config_key = CONFIG::MIXDOWN_MODE_ID ;
      value      = mixdown_value ;

        //[/UserButtonCode_wavMixdownButton]
    }
    else if (buttonThatWasClicked == saveLogButton)
    {
        //[UserButtonCode_saveLogButton] -- add your button handler code here..

      config_key = CONFIG::SHOULD_SAVE_LOG_KEY ;
      value      = toggle_value ;

        //[/UserButtonCode_saveLogButton]
    }
    else if (buttonThatWasClicked == hideBotsButton)
    {
        //[UserButtonCode_hideBotsButton] -- add your button handler code here..

      config_key = CONFIG::SHOULD_HIDE_BOTS_KEY ;
      value      = toggle_value ;

        //[/UserButtonCode_hideBotsButton]
    }

    //[UserbuttonClicked_Post]

  setConfig(config_key , value) ;

    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void ConfigNinjam::setConfig(Identifier a_key , var a_value)
{
  this->configStore.setProperty(a_key , a_value , nullptr) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConfigNinjam" componentName=""
                 parentClasses="public Component" constructorParams="ValueTree config_store"
                 variableInitialisers="configStore(config_store)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="192" initialHeight="172">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10" fill="solid: ff002000" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="saveAudioLabel" id="28e9c840504ea936" memberName="saveAudioLabel"
         virtualName="" explicitFocusOrder="0" pos="20 18 152 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="save audio" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <COMBOBOX name="saveAudioComboBox" id="195d38c0dfa0b780" memberName="saveAudioComboBox"
            virtualName="" explicitFocusOrder="1" pos="20 38 152 16" editable="0"
            layout="33" items="delete asap&#10;dont save&#10;save ogg&#10;save ogg and wav"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="oggMixdownButton" id="ccb740c03ababc9f" memberName="oggMixdownButton"
                virtualName="" explicitFocusOrder="2" pos="20 58 74 16" txtcol="ffffffff"
                buttonText="ogg mixdown" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="wavMixdownButton" id="2bfc206fbb162f7f" memberName="wavMixdownButton"
                virtualName="" explicitFocusOrder="3" pos="98 58 74 16" txtcol="ffffffff"
                buttonText="wav mixdown" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <LABEL name="debugLevelLabel" id="a67b459c94aba72e" memberName="debugLevelLabel"
         virtualName="" explicitFocusOrder="0" pos="20 86 152 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="debug level" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <COMBOBOX name="debugLevelComboBox" id="3b81e2ff4dec7469" memberName="debugLevelComboBox"
            virtualName="" explicitFocusOrder="4" pos="20 106 152 16" editable="0"
            layout="33" items="silent&#10;audio&#10;audio and network&#10;linjam trace"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="saveLogButton" id="a9eb5bfc0df5b172" memberName="saveLogButton"
                virtualName="" explicitFocusOrder="5" pos="20 130 74 16" txtcol="ffffffff"
                buttonText="save log" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="hideBotsButton" id="f7a06fb783648919" memberName="hideBotsButton"
                virtualName="" explicitFocusOrder="6" pos="98 130 74 16" txtcol="ffffffff"
                buttonText="hide bots" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
