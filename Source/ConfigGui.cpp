/*\
|*|  Copyright 2014,2015,2020,2026 bill-auger <bill-auger@programmer.net>
|*|
|*|  This file is part of the LinJam program.
|*|
|*|  LinJam is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  LinJam is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU General Public License for more details.
|*|
|*|  You should have received a copy of the GNU General Public License
|*|  along with LinJam.  If not, see <http://www.gnu.org/licenses/>.
\*/


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

    mixerGroup->setBounds (198, 100, 220, 76);

    chatGroup.reset (new juce::GroupComponent ("chatGroup",
                                               TRANS ("chat")));
    addAndMakeVisible (chatGroup.get());
    chatGroup->setTextLabelPosition (juce::Justification::centredLeft);
    chatGroup->setColour (juce::GroupComponent::outlineColourId, juce::Colours::grey);
    chatGroup->setColour (juce::GroupComponent::textColourId, juce::Colours::white);

    chatGroup->setBounds (198, 38, 220, 48);

    fontsizeLabel.reset (new juce::Label ("fontsizeLabel",
                                          TRANS ("chat font size:")));
    addAndMakeVisible (fontsizeLabel.get());
    fontsizeLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    fontsizeLabel->setJustificationType (juce::Justification::centredLeft);
    fontsizeLabel->setEditable (false, false, false);
    fontsizeLabel->setColour (juce::Label::textColourId, juce::Colours::white);
    fontsizeLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    fontsizeLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    fontsizeLabel->setBounds (206, 56, 96, 18);

    updateLabel.reset (new juce::Label ("updateLabel",
                                        TRANS ("vu update speed:")));
    addAndMakeVisible (updateLabel.get());
    updateLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    updateLabel->setJustificationType (juce::Justification::centredLeft);
    updateLabel->setEditable (false, false, false);
    updateLabel->setColour (juce::Label::textColourId, juce::Colours::white);
    updateLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    updateLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    updateLabel->setBounds (206, 118, 96, 18);

    updateComboBox.reset (new juce::ComboBox ("updateComboBox"));
    addAndMakeVisible (updateComboBox.get());
    updateComboBox->setExplicitFocusOrder (2);
    updateComboBox->setEditableText (false);
    updateComboBox->setJustificationType (juce::Justification::centredRight);
    updateComboBox->setTextWhenNothingSelected (juce::String());
    updateComboBox->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    updateComboBox->addListener (this);

    updateComboBox->setBounds (310, 118, 96, 18);

    fontsizeComboBox.reset (new juce::ComboBox ("fontsizeComboBox"));
    addAndMakeVisible (fontsizeComboBox.get());
    fontsizeComboBox->setExplicitFocusOrder (1);
    fontsizeComboBox->setEditableText (false);
    fontsizeComboBox->setJustificationType (juce::Justification::centredRight);
    fontsizeComboBox->setTextWhenNothingSelected (juce::String());
    fontsizeComboBox->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    fontsizeComboBox->addListener (this);

    fontsizeComboBox->setBounds (310, 56, 96, 18);

    layourLabel.reset (new juce::Label ("layourLabel",
                                        TRANS ("mixer height")));
    addAndMakeVisible (layourLabel.get());
    layourLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    layourLabel->setJustificationType (juce::Justification::centredLeft);
    layourLabel->setEditable (false, false, false);
    layourLabel->setColour (juce::Label::textColourId, juce::Colours::white);
    layourLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    layourLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    layourLabel->setBounds (206, 142, 96, 18);

    layoutComboBox.reset (new juce::ComboBox ("layoutComboBox"));
    addAndMakeVisible (layoutComboBox.get());
    layoutComboBox->setExplicitFocusOrder (2);
    layoutComboBox->setEditableText (false);
    layoutComboBox->setJustificationType (juce::Justification::centredRight);
    layoutComboBox->setTextWhenNothingSelected (juce::String());
    layoutComboBox->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    layoutComboBox->addListener (this);

    layoutComboBox->setBounds (310, 142, 96, 18);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..

  int font_size_n      = int(this->guiStore[CONFIG::FONT_SIZE_ID ]) ;
  int gui_update_ivl_n = int(this->guiStore[CONFIG::UPDATE_IVL_ID]) ;
  int gui_layout_n     = int(this->guiStore[CONFIG::GUI_LAYOUT_ID]) ;

  this->fontsizeComboBox->addItemList(GUI::FONT_SIZES  , 1) ;
  this->updateComboBox  ->addItemList(GUI::UPDATE_IVLS , 1) ;
  this->layoutComboBox  ->addItemList(GUI::GUI_LAYOUTS , 1) ;
  this->fontsizeComboBox->setSelectedItemIndex(font_size_n     ) ;
  this->updateComboBox  ->setSelectedItemIndex(gui_update_ivl_n) ;
  this->layoutComboBox  ->setSelectedItemIndex(gui_layout_n    ) ;

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
    layourLabel = nullptr;
    layoutComboBox = nullptr;


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
    else if (comboBoxThatHasChanged == layoutComboBox.get())
    {
        //[UserComboBoxCode_layoutComboBox] -- add your combo box handling code here..

      key   = CONFIG::GUI_LAYOUT_ID ;
      value = var((~option_n) ? option_n : 0) ;

      this->layoutComboBox->setSelectedItemIndex(option_n) ;

        //[/UserComboBoxCode_layoutComboBox]
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
                  virtualName="" explicitFocusOrder="0" pos="198 100 220 76" outlinecol="ff808080"
                  textcol="ffffffff" title="mixer" textpos="33"/>
  <GROUPCOMPONENT name="chatGroup" id="35b859a43662c4ca" memberName="chatGroup"
                  virtualName="" explicitFocusOrder="0" pos="198 38 220 48" outlinecol="ff808080"
                  textcol="ffffffff" title="chat" textpos="33"/>
  <LABEL name="fontsizeLabel" id="5cb85d669129843" memberName="fontsizeLabel"
         virtualName="" explicitFocusOrder="0" pos="206 56 96 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="chat font size:"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
  <LABEL name="updateLabel" id="116b9ce3acfaa0e6" memberName="updateLabel"
         virtualName="" explicitFocusOrder="0" pos="206 118 96 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="vu update speed:"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
  <COMBOBOX name="updateComboBox" id="bef2196516ab5821" memberName="updateComboBox"
            virtualName="" explicitFocusOrder="2" pos="310 118 96 18" editable="0"
            layout="34" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="fontsizeComboBox" id="128e0c382d0cdf83" memberName="fontsizeComboBox"
            virtualName="" explicitFocusOrder="1" pos="310 56 96 18" editable="0"
            layout="34" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="layourLabel" id="676e030333872865" memberName="layourLabel"
         virtualName="" explicitFocusOrder="0" pos="206 142 96 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="mixer height" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="layoutComboBox" id="3c0928bc60bf7c44" memberName="layoutComboBox"
            virtualName="" explicitFocusOrder="2" pos="310 142 96 18" editable="0"
            layout="34" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

