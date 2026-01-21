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

    mixerGroup.reset (new juce::GroupComponent ("mixerGroup",
                                                TRANS ("mixer")));
    addAndMakeVisible (mixerGroup.get());
    mixerGroup->setTextLabelPosition (juce::Justification::centredLeft);
    mixerGroup->setColour (juce::GroupComponent::outlineColourId, juce::Colours::grey);
    mixerGroup->setColour (juce::GroupComponent::textColourId, juce::Colours::white);

    mixerGroup->setBounds (214, 100, 188, 48);

    chatGroup.reset (new juce::GroupComponent ("chatGroup",
                                               TRANS ("chat")));
    addAndMakeVisible (chatGroup.get());
    chatGroup->setTextLabelPosition (juce::Justification::centredLeft);
    chatGroup->setColour (juce::GroupComponent::outlineColourId, juce::Colours::grey);
    chatGroup->setColour (juce::GroupComponent::textColourId, juce::Colours::white);

    chatGroup->setBounds (214, 38, 188, 48);

    fontsizeLabel.reset (new juce::Label ("fontsizeLabel",
                                          TRANS ("chat font size:")));
    addAndMakeVisible (fontsizeLabel.get());
    fontsizeLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    fontsizeLabel->setJustificationType (juce::Justification::centredLeft);
    fontsizeLabel->setEditable (false, false, false);
    fontsizeLabel->setColour (juce::Label::textColourId, juce::Colours::white);
    fontsizeLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    fontsizeLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    fontsizeLabel->setBounds (222, 56, 96, 18);

    updateLabel.reset (new juce::Label ("updateLabel",
                                        TRANS ("vu update speed:")));
    addAndMakeVisible (updateLabel.get());
    updateLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    updateLabel->setJustificationType (juce::Justification::centredLeft);
    updateLabel->setEditable (false, false, false);
    updateLabel->setColour (juce::Label::textColourId, juce::Colours::white);
    updateLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    updateLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    updateLabel->setBounds (222, 118, 96, 18);

    updateComboBox.reset (new juce::ComboBox ("updateComboBox"));
    addAndMakeVisible (updateComboBox.get());
    updateComboBox->setExplicitFocusOrder (2);
    updateComboBox->setEditableText (false);
    updateComboBox->setJustificationType (juce::Justification::centredRight);
    updateComboBox->setTextWhenNothingSelected (juce::String());
    updateComboBox->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    updateComboBox->addListener (this);

    updateComboBox->setBounds (326, 118, 64, 18);

    fontsizeComboBox.reset (new juce::ComboBox ("fontsizeComboBox"));
    addAndMakeVisible (fontsizeComboBox.get());
    fontsizeComboBox->setExplicitFocusOrder (1);
    fontsizeComboBox->setEditableText (false);
    fontsizeComboBox->setJustificationType (juce::Justification::centredRight);
    fontsizeComboBox->setTextWhenNothingSelected (juce::String());
    fontsizeComboBox->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    fontsizeComboBox->addListener (this);

    fontsizeComboBox->setBounds (326, 56, 64, 18);


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
void ConfigGui::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff000020));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConfigGui::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigGui::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]

  int        option_n    = comboBoxThatHasChanged->getSelectedItemIndex() ;
  String     option_text = comboBoxThatHasChanged->getText() ;
  Identifier key ;
  var        value ;

    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == updateComboBox.get())
    {
        //[UserComboBoxCode_updateComboBox] -- add your combo box handling code here..

      key   = CONFIG::UPDATE_IVL_ID ;
      value = var((~option_n) ? option_n : CONFIG::DEFAULT_UPDATE_IVL_N) ;
      this->updateComboBox->setSelectedItemIndex(option_n) ;

        //[/UserComboBoxCode_updateComboBox]
    }
    else if (comboBoxThatHasChanged == fontsizeComboBox.get())
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
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
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
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
  <LABEL name="updateLabel" id="116b9ce3acfaa0e6" memberName="updateLabel"
         virtualName="" explicitFocusOrder="0" pos="222 118 96 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="vu update speed:"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
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

