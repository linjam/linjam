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

#include "ConfigAudio.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigAudio::ConfigAudio ()
{
    addAndMakeVisible (sourceLabel = new Label ("sourceLabel",
                                                TRANS("in")));
    sourceLabel->setFont (Font (15.00f, Font::plain));
    sourceLabel->setJustificationType (Justification::centredLeft);
    sourceLabel->setEditable (false, false, false);
    sourceLabel->setColour (Label::textColourId, Colours::white);
    sourceLabel->setColour (TextEditor::textColourId, Colours::black);
    sourceLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sourceComboBox = new ComboBox ("sourceComboBox"));
    sourceComboBox->setExplicitFocusOrder (1);
    sourceComboBox->setEditableText (false);
    sourceComboBox->setJustificationType (Justification::centredLeft);
    sourceComboBox->setTextWhenNothingSelected (String::empty);
    sourceComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    sourceComboBox->addItem (TRANS("no"), 1);
    sourceComboBox->addItem (TRANS("ogg"), 2);
    sourceComboBox->addItem (TRANS("ogg and wav"), 3);
    sourceComboBox->addItem (TRANS("wav"), 4);
    sourceComboBox->addListener (this);

    addAndMakeVisible (sinkLabel = new Label ("sinkLabel",
                                              TRANS("out")));
    sinkLabel->setFont (Font (15.00f, Font::plain));
    sinkLabel->setJustificationType (Justification::centredLeft);
    sinkLabel->setEditable (false, false, false);
    sinkLabel->setColour (Label::textColourId, Colours::white);
    sinkLabel->setColour (TextEditor::textColourId, Colours::black);
    sinkLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sinkComboBox = new ComboBox ("sinkComboBox"));
    sinkComboBox->setExplicitFocusOrder (2);
    sinkComboBox->setEditableText (false);
    sinkComboBox->setJustificationType (Justification::centredLeft);
    sinkComboBox->setTextWhenNothingSelected (String::empty);
    sinkComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    sinkComboBox->addItem (TRANS("quiet"), 1);
    sinkComboBox->addItem (TRANS("audio"), 2);
    sinkComboBox->addItem (TRANS("audio and network"), 3);
    sinkComboBox->addItem (TRANS("linjam trace"), 4);
    sinkComboBox->addListener (this);

    addAndMakeVisible (bps16Button = new ToggleButton ("bps16Button"));
    bps16Button->setExplicitFocusOrder (3);
    bps16Button->setButtonText (TRANS("16bit"));
    bps16Button->setRadioGroupId (1);
    bps16Button->addListener (this);
    bps16Button->setToggleState (true, dontSendNotification);
    bps16Button->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (bps24Button = new ToggleButton ("bps24Button"));
    bps24Button->setExplicitFocusOrder (4);
    bps24Button->setButtonText (TRANS("24bit"));
    bps24Button->setRadioGroupId (1);
    bps24Button->addListener (this);
    bps24Button->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (bps32Button = new ToggleButton ("bps32Button"));
    bps32Button->setExplicitFocusOrder (5);
    bps32Button->setButtonText (TRANS("32bit"));
    bps32Button->setRadioGroupId (1);
    bps32Button->addListener (this);
    bps32Button->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (kHz44Button = new ToggleButton ("kHz44Button"));
    kHz44Button->setExplicitFocusOrder (6);
    kHz44Button->setButtonText (TRANS("44.1kHz"));
    kHz44Button->setRadioGroupId (2);
    kHz44Button->addListener (this);
    kHz44Button->setToggleState (true, dontSendNotification);
    kHz44Button->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (kHz48Button = new ToggleButton ("kHz48Button"));
    kHz48Button->setExplicitFocusOrder (7);
    kHz48Button->setButtonText (TRANS("48kHz"));
    kHz48Button->setRadioGroupId (2);
    kHz48Button->addListener (this);
    kHz48Button->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (kHz96Button = new ToggleButton ("kHz96Button"));
    kHz96Button->setExplicitFocusOrder (8);
    kHz96Button->setButtonText (TRANS("96kHz"));
    kHz96Button->setRadioGroupId (2);
    kHz96Button->addListener (this);
    kHz96Button->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (buffersLabel = new Label ("buffersLabel",
                                                 TRANS("buffers")));
    buffersLabel->setFont (Font (15.00f, Font::plain));
    buffersLabel->setJustificationType (Justification::centredLeft);
    buffersLabel->setEditable (false, false, false);
    buffersLabel->setColour (Label::textColourId, Colours::white);
    buffersLabel->setColour (TextEditor::textColourId, Colours::black);
    buffersLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nBuffersSlider = new Slider ("nBuffersSlider"));
    nBuffersSlider->setExplicitFocusOrder (9);
    nBuffersSlider->setRange (0, 16, 0);
    nBuffersSlider->setSliderStyle (Slider::IncDecButtons);
    nBuffersSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    nBuffersSlider->addListener (this);

    addAndMakeVisible (outputLabel3 = new Label ("outputLabel",
                                                 TRANS("x")));
    outputLabel3->setFont (Font (15.00f, Font::plain));
    outputLabel3->setJustificationType (Justification::centredLeft);
    outputLabel3->setEditable (false, false, false);
    outputLabel3->setColour (Label::textColourId, Colours::white);
    outputLabel3->setColour (TextEditor::textColourId, Colours::black);
    outputLabel3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (bufferComboBox = new ComboBox ("bufferComboBox"));
    bufferComboBox->setExplicitFocusOrder (10);
    bufferComboBox->setEditableText (false);
    bufferComboBox->setJustificationType (Justification::centredLeft);
    bufferComboBox->setTextWhenNothingSelected (String::empty);
    bufferComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    bufferComboBox->addItem (TRANS("32"), 1);
    bufferComboBox->addItem (TRANS("64"), 2);
    bufferComboBox->addItem (TRANS("128"), 3);
    bufferComboBox->addItem (TRANS("256"), 4);
    bufferComboBox->addItem (TRANS("512"), 5);
    bufferComboBox->addItem (TRANS("1024"), 6);
    bufferComboBox->addItem (TRANS("2048"), 7);
    bufferComboBox->addListener (this);

    addAndMakeVisible (latencyLabel = new Label ("latencyLabel",
                                                 TRANS("latency: 122.2ms")));
    latencyLabel->setFont (Font (15.00f, Font::plain));
    latencyLabel->setJustificationType (Justification::centredLeft);
    latencyLabel->setEditable (false, false, false);
    latencyLabel->setColour (Label::textColourId, Colours::white);
    latencyLabel->setColour (TextEditor::textColourId, Colours::black);
    latencyLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sourceLabel2 = new Label ("sourceLabel",
                                                 TRANS("in")));
    sourceLabel2->setFont (Font (15.00f, Font::plain));
    sourceLabel2->setJustificationType (Justification::centredLeft);
    sourceLabel2->setEditable (false, false, false);
    sourceLabel2->setColour (Label::textColourId, Colours::white);
    sourceLabel2->setColour (TextEditor::textColourId, Colours::black);
    sourceLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sourceComboBox2 = new ComboBox ("sourceComboBox"));
    sourceComboBox2->setExplicitFocusOrder (1);
    sourceComboBox2->setEditableText (false);
    sourceComboBox2->setJustificationType (Justification::centredLeft);
    sourceComboBox2->setTextWhenNothingSelected (String::empty);
    sourceComboBox2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    sourceComboBox2->addItem (TRANS("no"), 1);
    sourceComboBox2->addItem (TRANS("ogg"), 2);
    sourceComboBox2->addItem (TRANS("ogg and wav"), 3);
    sourceComboBox2->addItem (TRANS("wav"), 4);
    sourceComboBox2->addListener (this);

    addAndMakeVisible (jackNameLabel = new Label ("jackNameLabel",
                                                  TRANS("name")));
    jackNameLabel->setFont (Font (15.00f, Font::plain));
    jackNameLabel->setJustificationType (Justification::centredLeft);
    jackNameLabel->setEditable (false, false, false);
    jackNameLabel->setColour (Label::textColourId, Colours::white);
    jackNameLabel->setColour (TextEditor::textColourId, Colours::black);
    jackNameLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (textEditor = new TextEditor ("new text editor"));
    textEditor->setMultiLine (false);
    textEditor->setReturnKeyStartsNewLine (false);
    textEditor->setReadOnly (false);
    textEditor->setScrollbarsShown (true);
    textEditor->setCaretVisible (true);
    textEditor->setPopupMenuEnabled (false);
    textEditor->setColour (TextEditor::textColourId, Colours::grey);
    textEditor->setColour (TextEditor::backgroundColourId, Colours::black);
    textEditor->setText (String::empty);

    addAndMakeVisible (nSourcesLabel = new Label ("nSourcesLabel",
                                                  TRANS("sources")));
    nSourcesLabel->setFont (Font (15.00f, Font::plain));
    nSourcesLabel->setJustificationType (Justification::centredLeft);
    nSourcesLabel->setEditable (false, false, false);
    nSourcesLabel->setColour (Label::textColourId, Colours::white);
    nSourcesLabel->setColour (TextEditor::textColourId, Colours::black);
    nSourcesLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nSourcesSlider = new Slider ("nSourcesSlider"));
    nSourcesSlider->setExplicitFocusOrder (12);
    nSourcesSlider->setRange (0, 16, 0);
    nSourcesSlider->setSliderStyle (Slider::IncDecButtons);
    nSourcesSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    nSourcesSlider->addListener (this);

    addAndMakeVisible (nSinksLabel = new Label ("nSinksLabel",
                                                TRANS("sinks")));
    nSinksLabel->setFont (Font (15.00f, Font::plain));
    nSinksLabel->setJustificationType (Justification::centredLeft);
    nSinksLabel->setEditable (false, false, false);
    nSinksLabel->setColour (Label::textColourId, Colours::white);
    nSinksLabel->setColour (TextEditor::textColourId, Colours::black);
    nSinksLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nSinksSlider = new Slider ("nSinksSlider"));
    nSinksSlider->setExplicitFocusOrder (13);
    nSinksSlider->setRange (0, 16, 0);
    nSinksSlider->setSliderStyle (Slider::IncDecButtons);
    nSinksSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    nSinksSlider->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (192, 172);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ConfigAudio::~ConfigAudio()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    sourceLabel = nullptr;
    sourceComboBox = nullptr;
    sinkLabel = nullptr;
    sinkComboBox = nullptr;
    bps16Button = nullptr;
    bps24Button = nullptr;
    bps32Button = nullptr;
    kHz44Button = nullptr;
    kHz48Button = nullptr;
    kHz96Button = nullptr;
    buffersLabel = nullptr;
    nBuffersSlider = nullptr;
    outputLabel3 = nullptr;
    bufferComboBox = nullptr;
    latencyLabel = nullptr;
    sourceLabel2 = nullptr;
    sourceComboBox2 = nullptr;
    jackNameLabel = nullptr;
    textEditor = nullptr;
    nSourcesLabel = nullptr;
    nSourcesSlider = nullptr;
    nSinksLabel = nullptr;
    nSinksSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConfigAudio::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0xff202000));
    g.fillRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), static_cast<float> (getHeight() - 0), 10.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConfigAudio::resized()
{
    sourceLabel->setBounds (12, 46, 24, 18);
    sourceComboBox->setBounds (36, 46, 140, 16);
    sinkLabel->setBounds (12, 66, 24, 16);
    sinkComboBox->setBounds (36, 66, 140, 16);
    bps16Button->setBounds (12, 86, 48, 16);
    bps24Button->setBounds (72, 86, 48, 16);
    bps32Button->setBounds (132, 86, 48, 16);
    kHz44Button->setBounds (12, 106, 48, 16);
    kHz48Button->setBounds (72, 106, 48, 16);
    kHz96Button->setBounds (132, 106, 48, 16);
    buffersLabel->setBounds (12, 126, 40, 16);
    nBuffersSlider->setBounds (66, 126, 50, 16);
    outputLabel3->setBounds (116, 126, 16, 16);
    bufferComboBox->setBounds (136, 126, 40, 16);
    latencyLabel->setBounds (84, 146, 96, 16);
    sourceLabel2->setBounds (12, 26, 24, 18);
    sourceComboBox2->setBounds (36, 26, 140, 16);
    jackNameLabel->setBounds (12, 46, 40, 16);
    textEditor->setBounds (56, 46, 120, 16);
    nSourcesLabel->setBounds (12, 66, 50, 16);
    nSourcesSlider->setBounds (66, 66, 50, 16);
    nSinksLabel->setBounds (12, 86, 50, 16);
    nSinksSlider->setBounds (66, 86, 50, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigAudio::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == sourceComboBox)
    {
        //[UserComboBoxCode_sourceComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_sourceComboBox]
    }
    else if (comboBoxThatHasChanged == sinkComboBox)
    {
        //[UserComboBoxCode_sinkComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_sinkComboBox]
    }
    else if (comboBoxThatHasChanged == bufferComboBox)
    {
        //[UserComboBoxCode_bufferComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_bufferComboBox]
    }
    else if (comboBoxThatHasChanged == sourceComboBox2)
    {
        //[UserComboBoxCode_sourceComboBox2] -- add your combo box handling code here..
        //[/UserComboBoxCode_sourceComboBox2]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void ConfigAudio::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == bps16Button)
    {
        //[UserButtonCode_bps16Button] -- add your button handler code here..
        //[/UserButtonCode_bps16Button]
    }
    else if (buttonThatWasClicked == bps24Button)
    {
        //[UserButtonCode_bps24Button] -- add your button handler code here..
        //[/UserButtonCode_bps24Button]
    }
    else if (buttonThatWasClicked == bps32Button)
    {
        //[UserButtonCode_bps32Button] -- add your button handler code here..
        //[/UserButtonCode_bps32Button]
    }
    else if (buttonThatWasClicked == kHz44Button)
    {
        //[UserButtonCode_kHz44Button] -- add your button handler code here..
        //[/UserButtonCode_kHz44Button]
    }
    else if (buttonThatWasClicked == kHz48Button)
    {
        //[UserButtonCode_kHz48Button] -- add your button handler code here..
        //[/UserButtonCode_kHz48Button]
    }
    else if (buttonThatWasClicked == kHz96Button)
    {
        //[UserButtonCode_kHz96Button] -- add your button handler code here..
        //[/UserButtonCode_kHz96Button]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void ConfigAudio::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == nBuffersSlider)
    {
        //[UserSliderCode_nBuffersSlider] -- add your slider handling code here..
        //[/UserSliderCode_nBuffersSlider]
    }
    else if (sliderThatWasMoved == nSourcesSlider)
    {
        //[UserSliderCode_nSourcesSlider] -- add your slider handling code here..
        //[/UserSliderCode_nSourcesSlider]
    }
    else if (sliderThatWasMoved == nSinksSlider)
    {
        //[UserSliderCode_nSinksSlider] -- add your slider handling code here..
        //[/UserSliderCode_nSinksSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConfigAudio" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="192" initialHeight="172">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10" fill="solid: ff202000" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="sourceLabel" id="28e9c840504ea936" memberName="sourceLabel"
         virtualName="" explicitFocusOrder="0" pos="12 46 24 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="in" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="sourceComboBox" id="195d38c0dfa0b780" memberName="sourceComboBox"
            virtualName="" explicitFocusOrder="1" pos="36 46 140 16" editable="0"
            layout="33" items="no&#10;ogg&#10;ogg and wav&#10;wav" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <LABEL name="sinkLabel" id="a67b459c94aba72e" memberName="sinkLabel"
         virtualName="" explicitFocusOrder="0" pos="12 66 24 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="out" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="sinkComboBox" id="3b81e2ff4dec7469" memberName="sinkComboBox"
            virtualName="" explicitFocusOrder="2" pos="36 66 140 16" editable="0"
            layout="33" items="quiet&#10;audio&#10;audio and network&#10;linjam trace"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="bps16Button" id="ccb740c03ababc9f" memberName="bps16Button"
                virtualName="" explicitFocusOrder="3" pos="12 86 48 16" txtcol="ffffffff"
                buttonText="16bit" connectedEdges="0" needsCallback="1" radioGroupId="1"
                state="1"/>
  <TOGGLEBUTTON name="bps24Button" id="2bfc206fbb162f7f" memberName="bps24Button"
                virtualName="" explicitFocusOrder="4" pos="72 86 48 16" txtcol="ffffffff"
                buttonText="24bit" connectedEdges="0" needsCallback="1" radioGroupId="1"
                state="0"/>
  <TOGGLEBUTTON name="bps32Button" id="1cc075dc412ce404" memberName="bps32Button"
                virtualName="" explicitFocusOrder="5" pos="132 86 48 16" txtcol="ffffffff"
                buttonText="32bit" connectedEdges="0" needsCallback="1" radioGroupId="1"
                state="0"/>
  <TOGGLEBUTTON name="kHz44Button" id="56ab804241495c7b" memberName="kHz44Button"
                virtualName="" explicitFocusOrder="6" pos="12 106 48 16" txtcol="ffffffff"
                buttonText="44.1kHz" connectedEdges="0" needsCallback="1" radioGroupId="2"
                state="1"/>
  <TOGGLEBUTTON name="kHz48Button" id="415b27279e48004f" memberName="kHz48Button"
                virtualName="" explicitFocusOrder="7" pos="72 106 48 16" txtcol="ffffffff"
                buttonText="48kHz" connectedEdges="0" needsCallback="1" radioGroupId="2"
                state="0"/>
  <TOGGLEBUTTON name="kHz96Button" id="4241809c486a0995" memberName="kHz96Button"
                virtualName="" explicitFocusOrder="8" pos="132 106 48 16" txtcol="ffffffff"
                buttonText="96kHz" connectedEdges="0" needsCallback="1" radioGroupId="2"
                state="0"/>
  <LABEL name="buffersLabel" id="78ac240fcc5eed16" memberName="buffersLabel"
         virtualName="" explicitFocusOrder="0" pos="12 126 40 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="buffers" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="nBuffersSlider" id="76a832d1fac666e" memberName="nBuffersSlider"
          virtualName="" explicitFocusOrder="9" pos="66 126 50 16" min="0"
          max="16" int="0" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="outputLabel" id="5a9596c9eb8db178" memberName="outputLabel3"
         virtualName="" explicitFocusOrder="0" pos="116 126 16 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="x" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="bufferComboBox" id="bef2196516ab5821" memberName="bufferComboBox"
            virtualName="" explicitFocusOrder="10" pos="136 126 40 16" editable="0"
            layout="33" items="32&#10;64&#10;128&#10;256&#10;512&#10;1024&#10;2048"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="latencyLabel" id="f93456e3175d33d6" memberName="latencyLabel"
         virtualName="" explicitFocusOrder="0" pos="84 146 96 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="latency: 122.2ms"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="sourceLabel" id="582ccc898eac60c0" memberName="sourceLabel2"
         virtualName="" explicitFocusOrder="0" pos="12 26 24 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="in" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="sourceComboBox" id="d9fdbc02138c7335" memberName="sourceComboBox2"
            virtualName="" explicitFocusOrder="1" pos="36 26 140 16" editable="0"
            layout="33" items="no&#10;ogg&#10;ogg and wav&#10;wav" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <LABEL name="jackNameLabel" id="78568b552c534b6d" memberName="jackNameLabel"
         virtualName="" explicitFocusOrder="0" pos="12 46 40 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="name" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="fdccbcd88a94d4bb" memberName="textEditor"
              virtualName="" explicitFocusOrder="0" pos="56 46 120 16" textcol="ff808080"
              bkgcol="ff000000" initialText="" multiline="0" retKeyStartsLine="0"
              readonly="0" scrollbars="1" caret="1" popupmenu="0"/>
  <LABEL name="nSourcesLabel" id="fa0df2e2a11e57d8" memberName="nSourcesLabel"
         virtualName="" explicitFocusOrder="0" pos="12 66 50 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="sources" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="nSourcesSlider" id="3a13d77beb71d910" memberName="nSourcesSlider"
          virtualName="" explicitFocusOrder="12" pos="66 66 50 16" min="0"
          max="16" int="0" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="nSinksLabel" id="2da0a2441a20f3b0" memberName="nSinksLabel"
         virtualName="" explicitFocusOrder="0" pos="12 86 50 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="sinks" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="nSinksSlider" id="182ff4a5ae799417" memberName="nSinksSlider"
          virtualName="" explicitFocusOrder="13" pos="66 86 50 16" min="0"
          max="16" int="0" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
