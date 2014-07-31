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

#include "ConfigSubscriptions.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigSubscriptions::ConfigSubscriptions ()
{
    addAndMakeVisible (debugLevelLabel = new Label ("debugLevelLabel",
                                                    TRANS("ignored users")));
    debugLevelLabel->setFont (Font (15.00f, Font::plain));
    debugLevelLabel->setJustificationType (Justification::centredTop);
    debugLevelLabel->setEditable (false, false, false);
    debugLevelLabel->setColour (Label::textColourId, Colours::white);
    debugLevelLabel->setColour (TextEditor::textColourId, Colours::black);
    debugLevelLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (saveLogButton = new ToggleButton ("saveLogButton"));
    saveLogButton->setExplicitFocusOrder (1);
    saveLogButton->setButtonText (TRANS("auto-receive"));
    saveLogButton->addListener (this);
    saveLogButton->setToggleState (true, dontSendNotification);
    saveLogButton->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (saveLogButton2 = new ToggleButton ("saveLogButton"));
    saveLogButton2->setExplicitFocusOrder (2);
    saveLogButton2->setButtonText (TRANS("auto-ignore"));
    saveLogButton2->addListener (this);
    saveLogButton2->setToggleState (true, dontSendNotification);
    saveLogButton2->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (textEditor = new TextEditor ("new text editor"));
    textEditor->setExplicitFocusOrder (3);
    textEditor->setMultiLine (true);
    textEditor->setReturnKeyStartsNewLine (true);
    textEditor->setReadOnly (false);
    textEditor->setScrollbarsShown (true);
    textEditor->setCaretVisible (true);
    textEditor->setPopupMenuEnabled (false);
    textEditor->setColour (TextEditor::textColourId, Colours::grey);
    textEditor->setColour (TextEditor::backgroundColourId, Colours::black);
    textEditor->setText (TRANS("(enter usernames here - separated by spaces , commas , or newlines)"));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (192, 172);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ConfigSubscriptions::~ConfigSubscriptions()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    debugLevelLabel = nullptr;
    saveLogButton = nullptr;
    saveLogButton2 = nullptr;
    textEditor = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConfigSubscriptions::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0xff200000));
    g.fillRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), static_cast<float> (getHeight() - 0), 10.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConfigSubscriptions::resized()
{
    debugLevelLabel->setBounds (20, 44, 152, 16);
    saveLogButton->setBounds (20, 20, 74, 16);
    saveLogButton2->setBounds (98, 20, 74, 16);
    textEditor->setBounds (20, 64, 152, getHeight() - 84);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigSubscriptions::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == saveLogButton)
    {
        //[UserButtonCode_saveLogButton] -- add your button handler code here..
        //[/UserButtonCode_saveLogButton]
    }
    else if (buttonThatWasClicked == saveLogButton2)
    {
        //[UserButtonCode_saveLogButton2] -- add your button handler code here..
        //[/UserButtonCode_saveLogButton2]
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

<JUCER_COMPONENT documentType="Component" className="ConfigSubscriptions" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="192" initialHeight="172">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10" fill="solid: ff200000" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="debugLevelLabel" id="a67b459c94aba72e" memberName="debugLevelLabel"
         virtualName="" explicitFocusOrder="0" pos="20 44 152 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="ignored users" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <TOGGLEBUTTON name="saveLogButton" id="a9eb5bfc0df5b172" memberName="saveLogButton"
                virtualName="" explicitFocusOrder="1" pos="20 20 74 16" txtcol="ffffffff"
                buttonText="auto-receive" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="1"/>
  <TOGGLEBUTTON name="saveLogButton" id="fdc09180d037febb" memberName="saveLogButton2"
                virtualName="" explicitFocusOrder="2" pos="98 20 74 16" txtcol="ffffffff"
                buttonText="auto-ignore" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="1"/>
  <TEXTEDITOR name="new text editor" id="41d99016d4a5ba58" memberName="textEditor"
              virtualName="" explicitFocusOrder="3" pos="20 64 152 84M" textcol="ff808080"
              bkgcol="ff000000" initialText="(enter usernames here - separated by spaces , commas , or newlines)"
              multiline="1" retKeyStartsLine="1" readonly="0" scrollbars="1"
              caret="1" popupmenu="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
