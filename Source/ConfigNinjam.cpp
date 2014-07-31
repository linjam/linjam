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
//[/Headers]

#include "ConfigNinjam.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigNinjam::ConfigNinjam ()
{
    addAndMakeVisible (saveAudioComboBox = new ComboBox ("saveAudioComboBox"));
    saveAudioComboBox->setExplicitFocusOrder (1);
    saveAudioComboBox->setEditableText (false);
    saveAudioComboBox->setJustificationType (Justification::centredLeft);
    saveAudioComboBox->setTextWhenNothingSelected (String::empty);
    saveAudioComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    saveAudioComboBox->addItem (TRANS("dont save"), 1);
    saveAudioComboBox->addItem (TRANS("save ogg"), 2);
    saveAudioComboBox->addItem (TRANS("save ogg and wav"), 3);
    saveAudioComboBox->addItem (TRANS("delete asap"), 4);
    saveAudioComboBox->addListener (this);

    addAndMakeVisible (saveAudioLabel = new Label ("saveAudioLabel",
                                                   TRANS("save audio")));
    saveAudioLabel->setFont (Font (15.00f, Font::plain));
    saveAudioLabel->setJustificationType (Justification::centredTop);
    saveAudioLabel->setEditable (false, false, false);
    saveAudioLabel->setColour (Label::textColourId, Colours::white);
    saveAudioLabel->setColour (TextEditor::textColourId, Colours::black);
    saveAudioLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

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
    debugLevelComboBox->addItem (TRANS("quiet"), 1);
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

    addAndMakeVisible (saveLogButton2 = new ToggleButton ("saveLogButton"));
    saveLogButton2->setExplicitFocusOrder (2);
    saveLogButton2->setButtonText (TRANS("ogg mixdown"));
    saveLogButton2->addListener (this);
    saveLogButton2->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (hideBotsButton2 = new ToggleButton ("hideBotsButton"));
    hideBotsButton2->setExplicitFocusOrder (3);
    hideBotsButton2->setButtonText (TRANS("wav mixdown"));
    hideBotsButton2->addListener (this);
    hideBotsButton2->setColour (ToggleButton::textColourId, Colours::white);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (192, 172);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ConfigNinjam::~ConfigNinjam()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    saveAudioComboBox = nullptr;
    saveAudioLabel = nullptr;
    debugLevelLabel = nullptr;
    debugLevelComboBox = nullptr;
    saveLogButton = nullptr;
    hideBotsButton = nullptr;
    saveLogButton2 = nullptr;
    hideBotsButton2 = nullptr;


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
    saveAudioComboBox->setBounds (20, 38, 152, 16);
    saveAudioLabel->setBounds (20, 18, 152, 16);
    debugLevelLabel->setBounds (20, 86, 152, 16);
    debugLevelComboBox->setBounds (20, 106, 152, 16);
    saveLogButton->setBounds (20, 130, 74, 16);
    hideBotsButton->setBounds (98, 130, 74, 16);
    saveLogButton2->setBounds (20, 58, 74, 16);
    hideBotsButton2->setBounds (98, 58, 74, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigNinjam::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == saveAudioComboBox)
    {
        //[UserComboBoxCode_saveAudioComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_saveAudioComboBox]
    }
    else if (comboBoxThatHasChanged == debugLevelComboBox)
    {
        //[UserComboBoxCode_debugLevelComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_debugLevelComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void ConfigNinjam::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == saveLogButton)
    {
        //[UserButtonCode_saveLogButton] -- add your button handler code here..
        //[/UserButtonCode_saveLogButton]
    }
    else if (buttonThatWasClicked == hideBotsButton)
    {
        //[UserButtonCode_hideBotsButton] -- add your button handler code here..
        //[/UserButtonCode_hideBotsButton]
    }
    else if (buttonThatWasClicked == saveLogButton2)
    {
        //[UserButtonCode_saveLogButton2] -- add your button handler code here..
        //[/UserButtonCode_saveLogButton2]
    }
    else if (buttonThatWasClicked == hideBotsButton2)
    {
        //[UserButtonCode_hideBotsButton2] -- add your button handler code here..
        //[/UserButtonCode_hideBotsButton2]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConfigNinjam" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="192" initialHeight="172">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10" fill="solid: ff002000" hasStroke="0"/>
  </BACKGROUND>
  <COMBOBOX name="saveAudioComboBox" id="195d38c0dfa0b780" memberName="saveAudioComboBox"
            virtualName="" explicitFocusOrder="1" pos="20 38 152 16" editable="0"
            layout="33" items="dont save&#10;save ogg&#10;save ogg and wav&#10;delete asap"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="saveAudioLabel" id="28e9c840504ea936" memberName="saveAudioLabel"
         virtualName="" explicitFocusOrder="0" pos="20 18 152 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="save audio" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <LABEL name="debugLevelLabel" id="a67b459c94aba72e" memberName="debugLevelLabel"
         virtualName="" explicitFocusOrder="0" pos="20 86 152 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="debug level" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <COMBOBOX name="debugLevelComboBox" id="3b81e2ff4dec7469" memberName="debugLevelComboBox"
            virtualName="" explicitFocusOrder="4" pos="20 106 152 16" editable="0"
            layout="33" items="quiet&#10;audio&#10;audio and network&#10;linjam trace"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="saveLogButton" id="a9eb5bfc0df5b172" memberName="saveLogButton"
                virtualName="" explicitFocusOrder="5" pos="20 130 74 16" txtcol="ffffffff"
                buttonText="save log" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="hideBotsButton" id="f7a06fb783648919" memberName="hideBotsButton"
                virtualName="" explicitFocusOrder="6" pos="98 130 74 16" txtcol="ffffffff"
                buttonText="hide bots" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="1"/>
  <TOGGLEBUTTON name="saveLogButton" id="ccb740c03ababc9f" memberName="saveLogButton2"
                virtualName="" explicitFocusOrder="2" pos="20 58 74 16" txtcol="ffffffff"
                buttonText="ogg mixdown" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="hideBotsButton" id="2bfc206fbb162f7f" memberName="hideBotsButton2"
                virtualName="" explicitFocusOrder="3" pos="98 58 74 16" txtcol="ffffffff"
                buttonText="wav mixdown" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
