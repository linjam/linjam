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

#include "ConfigClient.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigClient::ConfigClient (ValueTree client_store)
    : clientStore(client_store)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    saveAudioLabel.reset (new juce::Label ("saveAudioLabel",
                                           TRANS ("save audio")));
    addAndMakeVisible (saveAudioLabel.get());
    saveAudioLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    saveAudioLabel->setJustificationType (juce::Justification::centredTop);
    saveAudioLabel->setEditable (false, false, false);
    saveAudioLabel->setColour (juce::Label::textColourId, juce::Colours::white);
    saveAudioLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    saveAudioLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    saveAudioLabel->setBounds (20, 18, 152, 16);

    saveAudioComboBox.reset (new juce::ComboBox ("saveAudioComboBox"));
    addAndMakeVisible (saveAudioComboBox.get());
    saveAudioComboBox->setExplicitFocusOrder (1);
    saveAudioComboBox->setEditableText (false);
    saveAudioComboBox->setJustificationType (juce::Justification::centredLeft);
    saveAudioComboBox->setTextWhenNothingSelected (juce::String());
    saveAudioComboBox->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    saveAudioComboBox->addListener (this);

    saveAudioComboBox->setBounds (20, 38, 152, 16);

    oggMixdownButton.reset (new juce::ToggleButton ("oggMixdownButton"));
    addAndMakeVisible (oggMixdownButton.get());
    oggMixdownButton->setExplicitFocusOrder (2);
    oggMixdownButton->setButtonText (TRANS ("ogg mixdown"));
    oggMixdownButton->addListener (this);
    oggMixdownButton->setColour (juce::ToggleButton::textColourId, juce::Colours::white);

    oggMixdownButton->setBounds (20, 58, 74, 16);

    wavMixdownButton.reset (new juce::ToggleButton ("wavMixdownButton"));
    addAndMakeVisible (wavMixdownButton.get());
    wavMixdownButton->setExplicitFocusOrder (3);
    wavMixdownButton->setButtonText (TRANS ("wav mixdown"));
    wavMixdownButton->addListener (this);
    wavMixdownButton->setColour (juce::ToggleButton::textColourId, juce::Colours::white);

    wavMixdownButton->setBounds (98, 58, 74, 16);

    debugLevelLabel.reset (new juce::Label ("debugLevelLabel",
                                            TRANS ("debug level")));
    addAndMakeVisible (debugLevelLabel.get());
    debugLevelLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    debugLevelLabel->setJustificationType (juce::Justification::centredTop);
    debugLevelLabel->setEditable (false, false, false);
    debugLevelLabel->setColour (juce::Label::textColourId, juce::Colours::white);
    debugLevelLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    debugLevelLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    debugLevelLabel->setBounds (20, 86, 152, 16);

    debugLevelComboBox.reset (new juce::ComboBox ("debugLevelComboBox"));
    addAndMakeVisible (debugLevelComboBox.get());
    debugLevelComboBox->setExplicitFocusOrder (4);
    debugLevelComboBox->setEditableText (false);
    debugLevelComboBox->setJustificationType (juce::Justification::centredLeft);
    debugLevelComboBox->setTextWhenNothingSelected (juce::String());
    debugLevelComboBox->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    debugLevelComboBox->addListener (this);

    debugLevelComboBox->setBounds (20, 106, 152, 16);

    saveLogButton.reset (new juce::ToggleButton ("saveLogButton"));
    addAndMakeVisible (saveLogButton.get());
    saveLogButton->setExplicitFocusOrder (5);
    saveLogButton->setButtonText (TRANS ("save log"));
    saveLogButton->addListener (this);
    saveLogButton->setColour (juce::ToggleButton::textColourId, juce::Colours::white);

    saveLogButton->setBounds (20, 130, 74, 16);

    hideBotsButton.reset (new juce::ToggleButton ("hideBotsButton"));
    addAndMakeVisible (hideBotsButton.get());
    hideBotsButton->setExplicitFocusOrder (6);
    hideBotsButton->setButtonText (TRANS ("hide bots"));
    hideBotsButton->addListener (this);
    hideBotsButton->setToggleState (true, juce::dontSendNotification);
    hideBotsButton->setColour (juce::ToggleButton::textColourId, juce::Colours::white);

    hideBotsButton->setBounds (98, 130, 74, 16);

    cleanButton.reset (new juce::TextButton ("cleanButton"));
    addAndMakeVisible (cleanButton.get());
    cleanButton->setExplicitFocusOrder (7);
    cleanButton->setButtonText (TRANS ("clean session dir"));
    cleanButton->addListener (this);

    cleanButton->setBounds (20, 164, 150, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (614, 434);


    //[Constructor] You can add your own custom stuff here..

  int  save_audio_mode    = int( this->clientStore[CONFIG::SAVE_AUDIO_MODE_ID  ]) ;
  int  mixdown_mode       = int( this->clientStore[CONFIG::MIXDOWN_MODE_ID     ]) ;
  int  debug_level        = int( this->clientStore[CONFIG::DEBUG_LEVEL_ID      ]) ;
  bool should_save_log    = bool(this->clientStore[CONFIG::SHOULD_SAVE_LOG_KEY ]) ;
  bool should_hide_bots   = bool(this->clientStore[CONFIG::SHOULD_HIDE_BOTS_KEY]) ;
  bool should_mixdown_ogg = !!(mixdown_mode & (int)NJClient::MIXDOWN_OGG) ;
  bool should_mixdown_wav = !!(mixdown_mode & (int)NJClient::MIXDOWN_WAV) ;

  this->saveAudioComboBox ->addItemList(GUI::SAVE_MODES   , 1) ;
  this->debugLevelComboBox->addItemList(GUI::DEBUG_LEVELS , 1) ;

  saveAudioComboBox ->setSelectedId(save_audio_mode + CONFIG::SAVE_AUDIO_ENUM_OFFSET) ;
  debugLevelComboBox->setSelectedItemIndex(debug_level) ;
  oggMixdownButton  ->setToggleState(should_mixdown_ogg , juce::dontSendNotification) ;
  wavMixdownButton  ->setToggleState(should_mixdown_wav , juce::dontSendNotification) ;
  saveLogButton     ->setToggleState(should_save_log    , juce::dontSendNotification) ;
  hideBotsButton    ->setToggleState(should_hide_bots   , juce::dontSendNotification) ;

    //[/Constructor]
}

ConfigClient::~ConfigClient()
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
    cleanButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConfigClient::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 0.0f, y = 0.0f, width = static_cast<float> (getWidth() - 0), height = static_cast<float> (getHeight() - 0);
        juce::Colour fillColour = juce::Colour (0xff202000);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConfigClient::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigClient::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]

  Identifier config_key ;
  var        value ;

    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == saveAudioComboBox.get())
    {
        //[UserComboBoxCode_saveAudioComboBox] -- add your combo box handling code here..

      config_key = CONFIG::SAVE_AUDIO_MODE_ID ;
      value      = var(saveAudioComboBox->getSelectedId() - CONFIG::SAVE_AUDIO_ENUM_OFFSET) ;

        //[/UserComboBoxCode_saveAudioComboBox]
    }
    else if (comboBoxThatHasChanged == debugLevelComboBox.get())
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

void ConfigClient::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]

  int mixdown_mode                                      = (int)NJClient::MIXDOWN_NONE ;
  if (oggMixdownButton->getToggleState()) mixdown_mode |= (int)NJClient::MIXDOWN_OGG  ;
  if (wavMixdownButton->getToggleState()) mixdown_mode |= (int)NJClient::MIXDOWN_WAV  ;

  Identifier config_key ;
  var        value ;
  var        mixdown_value = var(mixdown_mode) ;
  var        toggle_value  = var(buttonThatWasClicked->getToggleState()) ;

    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == oggMixdownButton.get())
    {
        //[UserButtonCode_oggMixdownButton] -- add your button handler code here..

      config_key = CONFIG::MIXDOWN_MODE_ID ;
      value      = mixdown_value ;

        //[/UserButtonCode_oggMixdownButton]
    }
    else if (buttonThatWasClicked == wavMixdownButton.get())
    {
        //[UserButtonCode_wavMixdownButton] -- add your button handler code here..

      config_key = CONFIG::MIXDOWN_MODE_ID ;
      value      = mixdown_value ;

        //[/UserButtonCode_wavMixdownButton]
    }
    else if (buttonThatWasClicked == saveLogButton.get())
    {
        //[UserButtonCode_saveLogButton] -- add your button handler code here..

      config_key = CONFIG::SHOULD_SAVE_LOG_KEY ;
      value      = toggle_value ;

        //[/UserButtonCode_saveLogButton]
    }
    else if (buttonThatWasClicked == hideBotsButton.get())
    {
        //[UserButtonCode_hideBotsButton] -- add your button handler code here..

      config_key = CONFIG::SHOULD_HIDE_BOTS_KEY ;
      value      = toggle_value ;

        //[/UserButtonCode_hideBotsButton]
    }
    else if (buttonThatWasClicked == cleanButton.get())
    {
        //[UserButtonCode_cleanButton] -- add your button handler code here..

      LinJam::CleanSessionDir() ;

        //[/UserButtonCode_cleanButton]
    }

    //[UserbuttonClicked_Post]

  setConfig(config_key , value) ;

    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void ConfigClient::setConfig(Identifier a_key , var a_value)
{
  this->clientStore.setProperty(a_key , a_value , nullptr) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConfigClient" componentName=""
                 parentClasses="public Component" constructorParams="ValueTree client_store"
                 variableInitialisers="clientStore(client_store)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="614" initialHeight="434">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10.0" fill="solid: ff202000" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="saveAudioLabel" id="28e9c840504ea936" memberName="saveAudioLabel"
         virtualName="" explicitFocusOrder="0" pos="20 18 152 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="save audio" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="12"/>
  <COMBOBOX name="saveAudioComboBox" id="195d38c0dfa0b780" memberName="saveAudioComboBox"
            virtualName="" explicitFocusOrder="1" pos="20 38 152 16" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
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
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="12"/>
  <COMBOBOX name="debugLevelComboBox" id="3b81e2ff4dec7469" memberName="debugLevelComboBox"
            virtualName="" explicitFocusOrder="4" pos="20 106 152 16" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="saveLogButton" id="a9eb5bfc0df5b172" memberName="saveLogButton"
                virtualName="" explicitFocusOrder="5" pos="20 130 74 16" txtcol="ffffffff"
                buttonText="save log" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="hideBotsButton" id="f7a06fb783648919" memberName="hideBotsButton"
                virtualName="" explicitFocusOrder="6" pos="98 130 74 16" txtcol="ffffffff"
                buttonText="hide bots" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="1"/>
  <TEXTBUTTON name="cleanButton" id="6134f446448d4d2b" memberName="cleanButton"
              virtualName="" explicitFocusOrder="7" pos="20 164 150 24" buttonText="clean session dir"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

