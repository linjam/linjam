/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...

#include "Constants.h"

//[/Headers]

#include "ConfigGui.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigGui::ConfigGui (ValueTree gui_store)
    : guiStore(gui_store)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (mixerGroup = new GroupComponent ("mixerGroup",
                                                        TRANS("mixer")));
    mixerGroup->setTextLabelPosition (Justification::centredLeft);
    mixerGroup->setColour (GroupComponent::outlineColourId, Colours::grey);
    mixerGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (chatGroup = new GroupComponent ("chatGroup",
                                                       TRANS("chat")));
    chatGroup->setTextLabelPosition (Justification::centredLeft);
    chatGroup->setColour (GroupComponent::outlineColourId, Colours::grey);
    chatGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (fontsizeLabel = new Label ("fontsizeLabel",
                                                  TRANS("chat font size:")));
    fontsizeLabel->setFont (Font (15.00f, Font::plain));
    fontsizeLabel->setJustificationType (Justification::centredLeft);
    fontsizeLabel->setEditable (false, false, false);
    fontsizeLabel->setColour (Label::textColourId, Colours::white);
    fontsizeLabel->setColour (TextEditor::textColourId, Colours::black);
    fontsizeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (updateLabel = new Label ("updateLabel",
                                                TRANS("vu update speed:")));
    updateLabel->setFont (Font (15.00f, Font::plain));
    updateLabel->setJustificationType (Justification::centredLeft);
    updateLabel->setEditable (false, false, false);
    updateLabel->setColour (Label::textColourId, Colours::white);
    updateLabel->setColour (TextEditor::textColourId, Colours::black);
    updateLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (updateComboBox = new ComboBox ("updateComboBox"));
    updateComboBox->setExplicitFocusOrder (2);
    updateComboBox->setEditableText (false);
    updateComboBox->setJustificationType (Justification::centredRight);
    updateComboBox->setTextWhenNothingSelected (String::empty);
    updateComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    updateComboBox->addListener (this);

    addAndMakeVisible (fontsizeComboBox = new ComboBox ("fontsizeComboBox"));
    fontsizeComboBox->setExplicitFocusOrder (1);
    fontsizeComboBox->setEditableText (false);
    fontsizeComboBox->setJustificationType (Justification::centredRight);
    fontsizeComboBox->setTextWhenNothingSelected (String::empty);
    fontsizeComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    fontsizeComboBox->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..

  int font_size_n            = int(this->guiStore[CONFIG::FONT_SIZE_ID ]) ;
  int gui_update_hipri_ivl_n = int(this->guiStore[CONFIG::UPDATE_IVL_ID]) ;

  this->fontsizeComboBox->addItemList(GUI::FONT_SIZES  , 1) ;
  this->updateComboBox  ->addItemList(GUI::UPDATE_IVLS , 1) ;
  this->fontsizeComboBox->setSelectedItemIndex(font_size_n           ) ;
  this->updateComboBox  ->setSelectedItemIndex(gui_update_hipri_ivl_n) ;

    //[/Constructor]
}

ConfigGui::~ConfigGui()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    mixerGroup = nullptr;
    chatGroup = nullptr;
    fontsizeLabel = nullptr;
    updateLabel = nullptr;
    updateComboBox = nullptr;
    fontsizeComboBox = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConfigGui::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff000020));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConfigGui::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    mixerGroup->setBounds (214, 100, 188, 48);
    chatGroup->setBounds (214, 38, 188, 48);
    fontsizeLabel->setBounds (222, 56, 96, 18);
    updateLabel->setBounds (222, 118, 96, 18);
    updateComboBox->setBounds (326, 118, 64, 18);
    fontsizeComboBox->setBounds (326, 56, 64, 18);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigGui::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]

  int        option_n    = comboBoxThatHasChanged->getSelectedItemIndex() ;
  String     option_text = comboBoxThatHasChanged->getText() ;
  Identifier key ;
  var        value ;

    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == updateComboBox)
    {
        //[UserComboBoxCode_updateComboBox] -- add your combo box handling code here..

      key   = CONFIG::UPDATE_IVL_ID ;
      value = var((~option_n) ? option_n : CONFIG::DEFAULT_UPDATE_IVL_N) ;
      this->updateComboBox->setSelectedItemIndex(option_n) ;

        //[/UserComboBoxCode_updateComboBox]
    }
    else if (comboBoxThatHasChanged == fontsizeComboBox)
    {
        //[UserComboBoxCode_fontsizeComboBox] -- add your combo box handling code here..

      key   = CONFIG::FONT_SIZE_ID ;
      value = var((~option_n) ? option_n : 0) ;

      this->fontsizeComboBox->setSelectedItemIndex(option_n) ;

        //[/UserComboBoxCode_fontsizeComboBox]
    }

    //[UsercomboBoxChanged_Post]

  setConfig(key , value) ;

    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void ConfigGui::setConfig(Identifier a_key , var a_value)
{
  if (a_key.isValid()) this->guiStore.setProperty(a_key , a_value , nullptr) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConfigGui" componentName=""
                 parentClasses="public Component" constructorParams="ValueTree gui_store"
                 variableInitialisers="guiStore(gui_store)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ff000020"/>
  <GROUPCOMPONENT name="mixerGroup" id="5f4710d68a339cda" memberName="mixerGroup"
                  virtualName="" explicitFocusOrder="0" pos="214 100 188 48" outlinecol="ff808080"
                  textcol="ffffffff" title="mixer" textpos="33"/>
  <GROUPCOMPONENT name="chatGroup" id="35b859a43662c4ca" memberName="chatGroup"
                  virtualName="" explicitFocusOrder="0" pos="214 38 188 48" outlinecol="ff808080"
                  textcol="ffffffff" title="chat" textpos="33"/>
  <LABEL name="fontsizeLabel" id="5cb85d669129843" memberName="fontsizeLabel"
         virtualName="" explicitFocusOrder="0" pos="222 56 96 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="chat font size:"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="updateLabel" id="116b9ce3acfaa0e6" memberName="updateLabel"
         virtualName="" explicitFocusOrder="0" pos="222 118 96 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="vu update speed:"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="updateComboBox" id="bef2196516ab5821" memberName="updateComboBox"
            virtualName="" explicitFocusOrder="2" pos="326 118 64 18" editable="0"
            layout="34" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="fontsizeComboBox" id="128e0c382d0cdf83" memberName="fontsizeComboBox"
            virtualName="" explicitFocusOrder="1" pos="326 56 64 18" editable="0"
            layout="34" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
