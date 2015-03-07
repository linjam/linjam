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
#include "Constants.h"
#include "./Trace/TraceConfig.h"

//[/Headers]

#include "ConfigAudio.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigAudio::ConfigAudio (ValueTree config_store)
    : configStore(config_store)
{
    addAndMakeVisible (ioGroup = new GroupComponent ("ioGroup",
                                                     TRANS("i/o")));
    ioGroup->setTextLabelPosition (Justification::centredLeft);
    ioGroup->setColour (GroupComponent::outlineColourId, Colours::grey);
    ioGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (formatGroup = new GroupComponent ("formatGroup",
                                                         TRANS("format")));
    formatGroup->setTextLabelPosition (Justification::centredLeft);
    formatGroup->setColour (GroupComponent::outlineColourId, Colours::grey);
    formatGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (buffersGroup = new GroupComponent ("buffersGroup",
                                                          TRANS("buffers (122.2ms)")));
    buffersGroup->setTextLabelPosition (Justification::centredLeft);
    buffersGroup->setColour (GroupComponent::outlineColourId, Colours::grey);
    buffersGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (routingGroup = new GroupComponent ("routingGroup",
                                                          TRANS("routing")));
    routingGroup->setTextLabelPosition (Justification::centredLeft);
    routingGroup->setColour (GroupComponent::outlineColourId, Colours::grey);
    routingGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (defaultsButton = new TextButton ("defaultsButton"));
    defaultsButton->setButtonText (TRANS("defaults"));
    defaultsButton->addListener (this);

    addAndMakeVisible (asioButton = new TextButton ("asioButton"));
    asioButton->setButtonText (TRANS("asio config"));
    asioButton->addListener (this);

    addAndMakeVisible (modeLabel = new Label ("modeLabel",
                                              TRANS("interface:")));
    modeLabel->setFont (Font (15.00f, Font::plain));
    modeLabel->setJustificationType (Justification::centredLeft);
    modeLabel->setEditable (false, false, false);
    modeLabel->setColour (Label::textColourId, Colours::white);
    modeLabel->setColour (TextEditor::textColourId, Colours::black);
    modeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (modeComboBox = new ComboBox ("modeComboBox"));
    modeComboBox->setExplicitFocusOrder (1);
    modeComboBox->setEditableText (false);
    modeComboBox->setJustificationType (Justification::centredLeft);
    modeComboBox->setTextWhenNothingSelected (String::empty);
    modeComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    modeComboBox->addListener (this);

    addAndMakeVisible (driverLabel = new Label ("driverLabel",
                                                TRANS("driver:")));
    driverLabel->setFont (Font (15.00f, Font::plain));
    driverLabel->setJustificationType (Justification::centredLeft);
    driverLabel->setEditable (false, false, false);
    driverLabel->setColour (Label::textColourId, Colours::white);
    driverLabel->setColour (TextEditor::textColourId, Colours::black);
    driverLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (driverComboBox = new ComboBox ("driverComboBox"));
    driverComboBox->setExplicitFocusOrder (1);
    driverComboBox->setEditableText (false);
    driverComboBox->setJustificationType (Justification::centredLeft);
    driverComboBox->setTextWhenNothingSelected (String::empty);
    driverComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    driverComboBox->addListener (this);

    addAndMakeVisible (sourceLabel = new Label ("sourceLabel",
                                                TRANS("input:")));
    sourceLabel->setFont (Font (15.00f, Font::plain));
    sourceLabel->setJustificationType (Justification::centredLeft);
    sourceLabel->setEditable (false, false, false);
    sourceLabel->setColour (Label::textColourId, Colours::white);
    sourceLabel->setColour (TextEditor::textColourId, Colours::black);
    sourceLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sourceComboBox = new ComboBox ("sourceComboBox"));
    sourceComboBox->setExplicitFocusOrder (2);
    sourceComboBox->setEditableText (false);
    sourceComboBox->setJustificationType (Justification::centredLeft);
    sourceComboBox->setTextWhenNothingSelected (String::empty);
    sourceComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    sourceComboBox->addListener (this);

    addAndMakeVisible (sinkLabel = new Label ("sinkLabel",
                                              TRANS("output:")));
    sinkLabel->setFont (Font (15.00f, Font::plain));
    sinkLabel->setJustificationType (Justification::centredLeft);
    sinkLabel->setEditable (false, false, false);
    sinkLabel->setColour (Label::textColourId, Colours::white);
    sinkLabel->setColour (TextEditor::textColourId, Colours::black);
    sinkLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sinkComboBox = new ComboBox ("sinkComboBox"));
    sinkComboBox->setExplicitFocusOrder (3);
    sinkComboBox->setEditableText (false);
    sinkComboBox->setJustificationType (Justification::centredLeft);
    sinkComboBox->setTextWhenNothingSelected (String::empty);
    sinkComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    sinkComboBox->addListener (this);

    addAndMakeVisible (bitdepthLabel = new Label ("bitdepthLabel",
                                                  TRANS("bit depth:")));
    bitdepthLabel->setFont (Font (15.00f, Font::plain));
    bitdepthLabel->setJustificationType (Justification::centredLeft);
    bitdepthLabel->setEditable (false, false, false);
    bitdepthLabel->setColour (Label::textColourId, Colours::white);
    bitdepthLabel->setColour (TextEditor::textColourId, Colours::black);
    bitdepthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (bps16Button = new ToggleButton ("bps16Button"));
    bps16Button->setExplicitFocusOrder (4);
    bps16Button->setButtonText (TRANS("16bit"));
    bps16Button->setRadioGroupId (1);
    bps16Button->addListener (this);
    bps16Button->setToggleState (true, dontSendNotification);
    bps16Button->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (bps24Button = new ToggleButton ("bps24Button"));
    bps24Button->setExplicitFocusOrder (5);
    bps24Button->setButtonText (TRANS("24bit"));
    bps24Button->setRadioGroupId (1);
    bps24Button->addListener (this);
    bps24Button->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (bps32Button = new ToggleButton ("bps32Button"));
    bps32Button->setExplicitFocusOrder (6);
    bps32Button->setButtonText (TRANS("32bit"));
    bps32Button->setRadioGroupId (1);
    bps32Button->addListener (this);
    bps32Button->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (samplerateLabel = new Label ("samplerateLabel",
                                                    TRANS("sample rate:")));
    samplerateLabel->setFont (Font (15.00f, Font::plain));
    samplerateLabel->setJustificationType (Justification::centredLeft);
    samplerateLabel->setEditable (false, false, false);
    samplerateLabel->setColour (Label::textColourId, Colours::white);
    samplerateLabel->setColour (TextEditor::textColourId, Colours::black);
    samplerateLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (kHz44Button = new ToggleButton ("kHz44Button"));
    kHz44Button->setExplicitFocusOrder (7);
    kHz44Button->setButtonText (TRANS("44.1kHz"));
    kHz44Button->setRadioGroupId (2);
    kHz44Button->addListener (this);
    kHz44Button->setToggleState (true, dontSendNotification);
    kHz44Button->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (kHz48Button = new ToggleButton ("kHz48Button"));
    kHz48Button->setExplicitFocusOrder (8);
    kHz48Button->setButtonText (TRANS("48kHz"));
    kHz48Button->setRadioGroupId (2);
    kHz48Button->addListener (this);
    kHz48Button->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (kHz96Button = new ToggleButton ("kHz96Button"));
    kHz96Button->setExplicitFocusOrder (9);
    kHz96Button->setButtonText (TRANS("96kHz"));
    kHz96Button->setRadioGroupId (2);
    kHz96Button->addListener (this);
    kHz96Button->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (buffersLabel = new Label ("buffersLabel",
                                                 TRANS("# of buffers")));
    buffersLabel->setFont (Font (15.00f, Font::plain));
    buffersLabel->setJustificationType (Justification::centredLeft);
    buffersLabel->setEditable (false, false, false);
    buffersLabel->setColour (Label::textColourId, Colours::white);
    buffersLabel->setColour (TextEditor::textColourId, Colours::black);
    buffersLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nBuffersSlider = new Slider ("nBuffersSlider"));
    nBuffersSlider->setExplicitFocusOrder (10);
    nBuffersSlider->setRange (0, 16, 1);
    nBuffersSlider->setSliderStyle (Slider::IncDecButtons);
    nBuffersSlider->setTextBoxStyle (Slider::TextBoxLeft, true, 80, 20);
    nBuffersSlider->addListener (this);

    addAndMakeVisible (xLabel = new Label ("xLabel",
                                           TRANS("x")));
    xLabel->setFont (Font (15.00f, Font::plain));
    xLabel->setJustificationType (Justification::centredLeft);
    xLabel->setEditable (false, false, false);
    xLabel->setColour (Label::textColourId, Colours::white);
    xLabel->setColour (TextEditor::textColourId, Colours::black);
    xLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (bufferComboBox = new ComboBox ("bufferComboBox"));
    bufferComboBox->setExplicitFocusOrder (11);
    bufferComboBox->setEditableText (false);
    bufferComboBox->setJustificationType (Justification::centredLeft);
    bufferComboBox->setTextWhenNothingSelected (String::empty);
    bufferComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    bufferComboBox->addListener (this);

    addAndMakeVisible (bytesLabel = new Label ("bytesLabel",
                                               TRANS("bytes")));
    bytesLabel->setFont (Font (15.00f, Font::plain));
    bytesLabel->setJustificationType (Justification::centredLeft);
    bytesLabel->setEditable (false, false, false);
    bytesLabel->setColour (Label::textColourId, Colours::white);
    bytesLabel->setColour (TextEditor::textColourId, Colours::black);
    bytesLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nixConfigLabel = new Label ("nixConfigLabel",
                                                   TRANS("client name")));
    nixConfigLabel->setFont (Font (15.00f, Font::plain));
    nixConfigLabel->setJustificationType (Justification::centredLeft);
    nixConfigLabel->setEditable (false, false, false);
    nixConfigLabel->setColour (Label::textColourId, Colours::white);
    nixConfigLabel->setColour (TextEditor::textColourId, Colours::black);
    nixConfigLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nixConfigText = new TextEditor ("nixConfigText"));
    nixConfigText->setExplicitFocusOrder (12);
    nixConfigText->setMultiLine (false);
    nixConfigText->setReturnKeyStartsNewLine (false);
    nixConfigText->setReadOnly (false);
    nixConfigText->setScrollbarsShown (true);
    nixConfigText->setCaretVisible (true);
    nixConfigText->setPopupMenuEnabled (false);
    nixConfigText->setColour (TextEditor::textColourId, Colours::grey);
    nixConfigText->setColour (TextEditor::backgroundColourId, Colours::black);
    nixConfigText->setText (String::empty);

    addAndMakeVisible (nSourcesLabel = new Label ("nSourcesLabel",
                                                  TRANS("# of sources")));
    nSourcesLabel->setFont (Font (15.00f, Font::plain));
    nSourcesLabel->setJustificationType (Justification::centredLeft);
    nSourcesLabel->setEditable (false, false, false);
    nSourcesLabel->setColour (Label::textColourId, Colours::white);
    nSourcesLabel->setColour (TextEditor::textColourId, Colours::black);
    nSourcesLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nSourcesSlider = new Slider ("nSourcesSlider"));
    nSourcesSlider->setExplicitFocusOrder (13);
    nSourcesSlider->setRange (0, 16, 1);
    nSourcesSlider->setSliderStyle (Slider::IncDecButtons);
    nSourcesSlider->setTextBoxStyle (Slider::TextBoxLeft, true, 80, 20);
    nSourcesSlider->addListener (this);

    addAndMakeVisible (nSinksLabel = new Label ("nSinksLabel",
                                                TRANS("# of sinks")));
    nSinksLabel->setFont (Font (15.00f, Font::plain));
    nSinksLabel->setJustificationType (Justification::centredLeft);
    nSinksLabel->setEditable (false, false, false);
    nSinksLabel->setColour (Label::textColourId, Colours::white);
    nSinksLabel->setColour (TextEditor::textColourId, Colours::black);
    nSinksLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nSinksSlider = new Slider ("nSinksSlider"));
    nSinksSlider->setExplicitFocusOrder (14);
    nSinksSlider->setRange (0, 16, 1);
    nSinksSlider->setSliderStyle (Slider::IncDecButtons);
    nSinksSlider->setTextBoxStyle (Slider::TextBoxLeft, true, 80, 20);
    nSinksSlider->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (614, 434);


    //[Constructor] You can add your own custom stuff here..

#ifdef _WIN32
  int win_interface_n = int(this->configStore[CONFIG::WIN_AUDIO_IF_ID]) ;
  this->modeComboBox->addItemList(CLIENT::WIN_AUDIO_IFS , 1) ;
  this->modeComboBox->setSelectedItemIndex(win_interface_n , juce::dontSendNotification) ;
#else // _WIN32
#  ifndef _MAC
  int firstNixAudioIf = audioStreamer::NIX_AUDIO_JACK ;
  int nix_interface_n = int(this->configStore[CONFIG::NIX_AUDIO_IF_ID]) - firstNixAudioIf ;
  this->modeComboBox->addItemList(CLIENT::NIX_AUDIO_IFS , 1) ;
  this->modeComboBox->setSelectedItemIndex(nix_interface_n , juce::dontSendNotification) ;
#  endif // _MAC
#endif // _WIN32

  this->nBuffersSlider->setRange(CLIENT::MIN_N_BUFFERS , CLIENT::MAX_N_BUFFERS , 1) ;
  this->nSourcesSlider->setRange(CLIENT::MIN_N_SOURCES , CLIENT::MAX_N_SOURCES , 1) ;
  this->nSinksSlider  ->setRange(CLIENT::MIN_N_SINKS   , CLIENT::MAX_N_SINKS   , 1) ;

    //[/Constructor]
}

ConfigAudio::~ConfigAudio()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    ioGroup = nullptr;
    formatGroup = nullptr;
    buffersGroup = nullptr;
    routingGroup = nullptr;
    defaultsButton = nullptr;
    asioButton = nullptr;
    modeLabel = nullptr;
    modeComboBox = nullptr;
    driverLabel = nullptr;
    driverComboBox = nullptr;
    sourceLabel = nullptr;
    sourceComboBox = nullptr;
    sinkLabel = nullptr;
    sinkComboBox = nullptr;
    bitdepthLabel = nullptr;
    bps16Button = nullptr;
    bps24Button = nullptr;
    bps32Button = nullptr;
    samplerateLabel = nullptr;
    kHz44Button = nullptr;
    kHz48Button = nullptr;
    kHz96Button = nullptr;
    buffersLabel = nullptr;
    nBuffersSlider = nullptr;
    xLabel = nullptr;
    bufferComboBox = nullptr;
    bytesLabel = nullptr;
    nixConfigLabel = nullptr;
    nixConfigText = nullptr;
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

    g.setColour (Colour (0xff002000));
    g.fillRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), static_cast<float> (getHeight() - 0), 10.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConfigAudio::resized()
{
    ioGroup->setBounds (132, 38, 350, 126);
    formatGroup->setBounds (132, 176, 350, 60);
    buffersGroup->setBounds (132, 250, 350, 48);
    routingGroup->setBounds (132, 312, 350, 74);
    defaultsButton->setBounds (getWidth() - 68, 4, 64, 24);
    asioButton->setBounds (getWidth() - 68, 4, 64, 24);
    modeLabel->setBounds (140, 56, 64, 18);
    modeComboBox->setBounds (212, 56, 256, 18);
    driverLabel->setBounds (140, 82, 64, 18);
    driverComboBox->setBounds (212, 82, 256, 18);
    sourceLabel->setBounds (140, 108, 64, 18);
    sourceComboBox->setBounds (212, 108, 256, 18);
    sinkLabel->setBounds (140, 134, 64, 16);
    sinkComboBox->setBounds (212, 134, 256, 18);
    bitdepthLabel->setBounds (140, 190, 64, 18);
    bps16Button->setBounds (212, 191, 64, 18);
    bps24Button->setBounds (288, 191, 64, 18);
    bps32Button->setBounds (364, 191, 64, 18);
    samplerateLabel->setBounds (140, 210, 72, 18);
    kHz44Button->setBounds (212, 211, 64, 18);
    kHz48Button->setBounds (288, 211, 64, 18);
    kHz96Button->setBounds (364, 211, 64, 18);
    buffersLabel->setBounds (140, 268, 64, 18);
    nBuffersSlider->setBounds (212, 268, 64, 18);
    xLabel->setBounds (275, 268, 16, 18);
    bufferComboBox->setBounds (292, 268, 52, 18);
    bytesLabel->setBounds (346, 268, 64, 18);
    nixConfigLabel->setBounds (140, 332, 64, 18);
    nixConfigText->setBounds (212, 332, 256, 18);
    nSourcesLabel->setBounds (140, 358, 64, 18);
    nSourcesSlider->setBounds (214, 358, 64, 18);
    nSinksLabel->setBounds (330, 358, 64, 18);
    nSinksSlider->setBounds (404, 358, 64, 18);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigAudio::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]

  Identifier bit_depth_key   = Identifier() ;
  Identifier sample_rate_key = Identifier() ;
#if _WIN32
  int        interface_n     = int(this->configStore[CONFIG::WIN_AUDIO_IF_ID]) ;

  switch ((audioStreamer::Interface)interface_n)
  {
    case audioStreamer::WIN_AUDIO_KS:
      bit_depth_key   = CONFIG::KS_BITDEPTH_ID ;
      sample_rate_key = CONFIG::KS_SAMPLERATE_ID ;
      break ;
    case audioStreamer::WIN_AUDIO_DS:
      bit_depth_key   = CONFIG::DS_BITDEPTH_ID ;
      sample_rate_key = CONFIG::DS_SAMPLERATE_ID ;
      break ;
    case audioStreamer::WIN_AUDIO_WAVE:
      bit_depth_key   = CONFIG::WAVE_BITDEPTH_ID ;
      sample_rate_key = CONFIG::WAVE_SAMPLERATE_ID ;
      break ;
    default: break ;
  }
#else // _WIN32
#  ifndef _MAC
  bit_depth_key   = CONFIG::MAC_BITDEPTH_ID;
  sample_rate_key = CONFIG::MAC_SAMPLERATE_ID ;
#  endif // _MAC
#endif // _WIN32

  int bit_depth   = (this->bps16Button->getToggleState())? CLIENT::BIT_DEPTH_16 :
                    (this->bps24Button->getToggleState())? CLIENT::BIT_DEPTH_24 :
                    (this->bps32Button->getToggleState())? CLIENT::BIT_DEPTH_32 : 0 ;
  int sample_rate = (this->kHz44Button->getToggleState())? CLIENT::SAMPLE_RATE_44100 :
                    (this->kHz48Button->getToggleState())? CLIENT::SAMPLE_RATE_48000 :
                    (this->kHz96Button->getToggleState())? CLIENT::SAMPLE_RATE_96000 : 0 ;

  Identifier config_key ;
  var        value ;

    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == defaultsButton)
    {
        //[UserButtonCode_defaultsButton] -- add your button handler code here..

      restoreDefaults() ; loadParams() ; return ;

        //[/UserButtonCode_defaultsButton]
    }
    else if (buttonThatWasClicked == asioButton)
    {
        //[UserButtonCode_asioButton] -- add your button handler code here..
        //[/UserButtonCode_asioButton]
    }
    else if (buttonThatWasClicked == bps16Button)
    {
        //[UserButtonCode_bps16Button] -- add your button handler code here..

      config_key = bit_depth_key ;
      value      = var(bit_depth) ;

        //[/UserButtonCode_bps16Button]
    }
    else if (buttonThatWasClicked == bps24Button)
    {
        //[UserButtonCode_bps24Button] -- add your button handler code here..

      config_key = bit_depth_key ;
      value      = var(bit_depth) ;

        //[/UserButtonCode_bps24Button]
    }
    else if (buttonThatWasClicked == bps32Button)
    {
        //[UserButtonCode_bps32Button] -- add your button handler code here..

      config_key = bit_depth_key ;
      value      = var(bit_depth) ;

        //[/UserButtonCode_bps32Button]
    }
    else if (buttonThatWasClicked == kHz44Button)
    {
        //[UserButtonCode_kHz44Button] -- add your button handler code here..

      config_key = sample_rate_key ;
      value      = var(sample_rate) ;

        //[/UserButtonCode_kHz44Button]
    }
    else if (buttonThatWasClicked == kHz48Button)
    {
        //[UserButtonCode_kHz48Button] -- add your button handler code here..

      config_key = sample_rate_key ;
      value      = var(sample_rate) ;

        //[/UserButtonCode_kHz48Button]
    }
    else if (buttonThatWasClicked == kHz96Button)
    {
        //[UserButtonCode_kHz96Button] -- add your button handler code here..

      config_key = sample_rate_key ;
      value      = var(sample_rate) ;

        //[/UserButtonCode_kHz96Button]
    }

    //[UserbuttonClicked_Post]

  setConfig(config_key , value) ;

    //[/UserbuttonClicked_Post]
}

void ConfigAudio::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]

#if _WIN32
  int        interface_n     = int(this->configStore[CONFIG::WIN_AUDIO_IF_ID]) ;
  Identifier mode_config_key = CONFIG::WIN_AUDIO_IF_ID ;
  int        default_mode    = CONFIG::DEFAULT_WIN_AUDIO_IF ;
#else // _WIN32
#  ifndef _MAC
  Identifier mode_config_key = CONFIG::NIX_AUDIO_IF_ID ;
  int        default_mode    = CONFIG::DEFAULT_NIX_AUDIO_IF ;
#  endif // _MAC
#endif // _WIN32

  Identifier config_key ;
  var        value ;
  int        default_index ;

    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == modeComboBox)
    {
        //[UserComboBoxCode_modeComboBox] -- add your combo box handling code here..

#ifndef _MAC
      int selected_mode = this->modeComboBox->getSelectedItemIndex() ;

      config_key = mode_config_key ;
      value      = var((~selected_mode)? selected_mode : default_mode) ;
#endif // _MAC

        //[/UserComboBoxCode_modeComboBox]
    }
    else if (comboBoxThatHasChanged == driverComboBox)
    {
        //[UserComboBoxCode_driverComboBox] -- add your combo box handling code here..

      int selected_index = this->driverComboBox->getSelectedItemIndex() ;
#if _WIN32
      config_key         = CONFIG::ASIO_DRIVER_ID ;
#else // _WIN32
#  ifndef _MAC
      config_key         = CONFIG::JACK_SERVER_ID ;
#  endif // _MAC
#endif // _WIN32
      value              = var((~selected_index)? selected_index : 0) ;

        //[/UserComboBoxCode_driverComboBox]
    }
#if _WIN32
    else if (comboBoxThatHasChanged == sourceComboBox)
    {
        //[UserComboBoxCode_sourceComboBox] -- add your combo box handling code here..

      int selected_index = this->sourceComboBox->getSelectedItemIndex() ;

      switch ((audioStreamer::Interface)interface_n)
      {
        case audioStreamer::WIN_AUDIO_ASIO:
          config_key = CONFIG::ASIO_INPUT0_ID ;
          value      = var((~selected_index)? selected_index - 1         :
                                              CONFIG::DEFAULT_ASIO_INPUT0) ; break ;
        case audioStreamer::WIN_AUDIO_KS:
          config_key = CONFIG::KS_INPUT_ID ;
          value      = var((~selected_index)? selected_index - 1      :
                                              CONFIG::DEFAULT_KS_INPUT) ;    break ;
        case audioStreamer::WIN_AUDIO_DS:
          config_key = CONFIG::DS_INPUT0_ID ;
          value      = var((~selected_index)? selected_index           :
                                              CONFIG::DEFAULT_DS_INPUT0) ;   break ;
        case audioStreamer::WIN_AUDIO_WAVE:
          config_key = CONFIG::WAVE_INPUT_ID ;
          value      = var((~selected_index)? selected_index - 1        :
                                              CONFIG::DEFAULT_WAVE_INPUT) ;  break ;
        default:                                                             break ;
      }

        //[/UserComboBoxCode_sourceComboBox]
    }
    else if (comboBoxThatHasChanged == sinkComboBox)
    {
        //[UserComboBoxCode_sinkComboBox] -- add your combo box handling code here..

      switch ((audioStreamer::Interface)interface_n)
      {
        case audioStreamer::WIN_AUDIO_ASIO:
          config_key    = CONFIG::ASIO_OUTPUT0_ID ;
          default_index = CONFIG::DEFAULT_ASIO_OUTPUT0 ; break ;
        case audioStreamer::WIN_AUDIO_KS:
          config_key    = CONFIG::KS_OUTPUT_ID ;
          default_index = CONFIG::DEFAULT_KS_OUTPUT ;    break ;
        case audioStreamer::WIN_AUDIO_DS:
          config_key    = CONFIG::DS_OUTPUT0_ID ;
          default_index = CONFIG::DEFAULT_DS_OUTPUT0 ;   break ;
        case audioStreamer::WIN_AUDIO_WAVE:
          config_key    = CONFIG::WAVE_OUTPUT_ID ;
          default_index = CONFIG::DEFAULT_WAVE_OUTPUT ;  break ;
        default:                                         break ;
      }
      int selected_index = this->sourceComboBox->getSelectedItemIndex() ;
      value              = var((~selected_index)? selected_index - 1 : default_index) ;

        //[/UserComboBoxCode_sinkComboBox]
    }
    else if (comboBoxThatHasChanged == bufferComboBox)
    {
        //[UserComboBoxCode_bufferComboBox] -- add your combo box handling code here..

      switch ((audioStreamer::Interface)interface_n)
      {
        case audioStreamer::WIN_AUDIO_KS:   config_key = CONFIG::KS_BLOCKSIZE_ID ;   break ;
        case audioStreamer::WIN_AUDIO_DS:   config_key = CONFIG::DS_BLOCKSIZE_ID ;   break ;
        case audioStreamer::WIN_AUDIO_WAVE: config_key = CONFIG::WAVE_BLOCKSIZE_ID ; break ;
        default:                                                                     break ;
      }
      value = var(this->bufferComboBox->getText().getIntValue()) ;

        //[/UserComboBoxCode_bufferComboBox]
    }
#endif // _WIN32

    //[UsercomboBoxChanged_Post]

  setConfig(config_key , value) ;

  if (comboBoxThatHasChanged == this->modeComboBox) loadParams() ;

    //[/UsercomboBoxChanged_Post]
}

void ConfigAudio::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]

  Identifier config_key ;
  var        value      = var((int)sliderThatWasMoved->getValue()) ;

    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == nBuffersSlider)
    {
        //[UserSliderCode_nBuffersSlider] -- add your slider handling code here..

#if _WIN32
      int interface_n = int(this->configStore[CONFIG::WIN_AUDIO_IF_ID]) ;

      switch ((audioStreamer::Interface)interface_n)
      {
        case audioStreamer::WIN_AUDIO_KS:   config_key = CONFIG::KS_NBLOCKS_ID ;   break ;
        case audioStreamer::WIN_AUDIO_DS:   config_key = CONFIG::DS_NBLOCKS_ID ;   break ;
        case audioStreamer::WIN_AUDIO_WAVE: config_key = CONFIG::WAVE_NBLOCKS_ID ; break ;
        default:                                                                   break ;
      }
#endif // _WIN32

        //[/UserSliderCode_nBuffersSlider]
    }
    else if (sliderThatWasMoved == nSourcesSlider)
    {
        //[UserSliderCode_nSourcesSlider] -- add your slider handling code here..

#ifndef _WIN32
#  ifdef _MAC
      config_key = CONFIG::MAC_NINPUTS_KEY ;
#  else // _MAC
      config_key = CONFIG::JACK_NINPUTS_ID ;
#  endif // _MAC
#endif // _WIN32

        //[/UserSliderCode_nSourcesSlider]
    }
    else if (sliderThatWasMoved == nSinksSlider)
    {
        //[UserSliderCode_nSinksSlider] -- add your slider handling code here..

#ifndef _WIN32
#  ifndef _MAC
      config_key = CONFIG::JACK_NOUTPUTS_ID ;
#  endif // _MAC
#endif // _WIN32

        //[/UserSliderCode_nSinksSlider]
    }

    //[UsersliderValueChanged_Post]

  setConfig(config_key , value) ;

    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* ConfigAudio class private instance methods */

void ConfigAudio::broughtToFront() { loadParams() ; }

void ConfigAudio::loadParams()
{
  // load config
  int    win_interface_n   = int(this->configStore[CONFIG::WIN_AUDIO_IF_ID]) ;
  int    asio_driver       = int(this->configStore[CONFIG::ASIO_DRIVER_ID]) ;
  int    asio_input0       = int(this->configStore[CONFIG::ASIO_INPUT0_ID]) ;
  int    asio_input1       = int(this->configStore[CONFIG::ASIO_INPUT1_ID]) ;
  int    asio_output0      = int(this->configStore[CONFIG::ASIO_OUTPUT0_ID]) ;
  int    asio_output1      = int(this->configStore[CONFIG::ASIO_OUTPUT1_ID]) ;
  int    ks_input          = int(this->configStore[CONFIG::KS_INPUT_ID]) ;
  int    ks_output         = int(this->configStore[CONFIG::KS_OUTPUT_ID]) ;
  int    ks_sample_rate    = int(this->configStore[CONFIG::KS_SAMPLERATE_ID]) ;
  int    ks_bit_depth      = int(this->configStore[CONFIG::KS_BITDEPTH_ID]) ;
  int    ks_buffer_size    = int(this->configStore[CONFIG::KS_BLOCKSIZE_ID]) ;
  int    ks_n_buffers      = int(this->configStore[CONFIG::KS_NBLOCKS_ID]) ;
  int    ds_input0         = int(this->configStore[CONFIG::DS_INPUT0_ID]) ;
  int    ds_input1         = int(this->configStore[CONFIG::DS_INPUT1_ID]) ;
  int    ds_input2         = int(this->configStore[CONFIG::DS_INPUT2_ID]) ;
  int    ds_input3         = int(this->configStore[CONFIG::DS_INPUT3_ID]) ;
  int    ds_output0        = int(this->configStore[CONFIG::DS_OUTPUT0_ID]) ;
  int    ds_output1        = int(this->configStore[CONFIG::DS_OUTPUT1_ID]) ;
  int    ds_output2        = int(this->configStore[CONFIG::DS_OUTPUT2_ID]) ;
  int    ds_output3        = int(this->configStore[CONFIG::DS_OUTPUT3_ID]) ;
  int    ds_sample_rate    = int(this->configStore[CONFIG::DS_SAMPLERATE_ID]) ;
  int    ds_bit_depth      = int(this->configStore[CONFIG::DS_BITDEPTH_ID]) ;
  int    ds_buffer_size    = int(this->configStore[CONFIG::DS_BLOCKSIZE_ID]) ;
  int    ds_n_buffers      = int(this->configStore[CONFIG::DS_NBLOCKS_ID]) ;
  int    wave_input        = int(this->configStore[CONFIG::WAVE_INPUT_ID]) ;
  int    wave_output       = int(this->configStore[CONFIG::WAVE_OUTPUT_ID]) ;
  int    wave_sample_rate  = int(this->configStore[CONFIG::WAVE_SAMPLERATE_ID]) ;
  int    wave_bit_depth    = int(this->configStore[CONFIG::WAVE_BITDEPTH_ID]) ;
  int    wave_buffer_size  = int(this->configStore[CONFIG::WAVE_BLOCKSIZE_ID]) ;
  int    wave_n_buffers    = int(this->configStore[CONFIG::WAVE_NBLOCKS_ID]) ;
  String mac_device_name   =     this->configStore[CONFIG::MAC_DEVICE_ID].toString() ;
  int    mac_n_inputs      = int(this->configStore[CONFIG::MAC_NINPUTS_ID]) ;
  int    mac_sample_rate   = int(this->configStore[CONFIG::MAC_SAMPLERATE_ID]) ;
  int    mac_bit_depth     = int(this->configStore[CONFIG::MAC_BITDEPTH_ID]) ;
  int    nix_interface_n   = int(this->configStore[CONFIG::NIX_AUDIO_IF_ID]) ;
  int    jack_server       = int(this->configStore[CONFIG::JACK_SERVER_ID]) ;
  String jack_name         =     this->configStore[CONFIG::JACK_NAME_ID].toString() ;
  String alsa_config       =     this->configStore[CONFIG::ALSA_CONFIG_ID].toString() ;
  int    jack_n_inputs     = int(this->configStore[CONFIG::JACK_NINPUTS_ID]) ;
  int    jack_n_outputs    = int(this->configStore[CONFIG::JACK_NOUTPUTS_ID]) ;

  // disable components temporarily
  this->defaultsButton ->setVisible(false) ; this->asioButton    ->setVisible(false) ;
  this->ioGroup        ->setEnabled(false) ; this->modeLabel     ->setEnabled(false) ;
  this->modeComboBox   ->setEnabled(false) ; this->driverLabel   ->setEnabled(false) ;
  this->driverComboBox ->setEnabled(false) ; this->sourceLabel   ->setEnabled(false) ;
  this->sourceComboBox ->setEnabled(false) ; this->sinkLabel     ->setEnabled(false) ;
  this->sinkComboBox   ->setEnabled(false) ; this->formatGroup   ->setEnabled(false) ;
  this->bitdepthLabel  ->setEnabled(false) ; this->bps16Button   ->setEnabled(false) ;
  this->bps24Button    ->setEnabled(false) ; this->bps32Button   ->setEnabled(false) ;
  this->samplerateLabel->setEnabled(false) ; this->kHz44Button   ->setEnabled(false) ;
  this->kHz48Button    ->setEnabled(false) ; this->kHz96Button   ->setEnabled(false) ;
  this->buffersGroup   ->setEnabled(false) ; this->buffersLabel  ->setEnabled(false) ;
  this->nBuffersSlider ->setEnabled(false) ; this->xLabel        ->setEnabled(false) ;
  this->bufferComboBox ->setEnabled(false) ; this->bytesLabel    ->setEnabled(false) ;
  this->routingGroup   ->setEnabled(false) ; this->nixConfigLabel->setEnabled(false) ;
  this->nixConfigText  ->setEnabled(false) ; this->nSourcesLabel ->setEnabled(false) ;
  this->nSourcesSlider ->setEnabled(false) ; this->nSinksLabel   ->setEnabled(false) ;
  this->nSinksSlider   ->setEnabled(false) ;

  // clear select options temporarily
  this->driverComboBox->clear(juce::dontSendNotification) ;
  this->sourceComboBox->clear(juce::dontSendNotification) ;
  this->sinkComboBox  ->clear(juce::dontSendNotification) ;
  this->bufferComboBox->clear(juce::dontSendNotification) ;

  // set interface-specific GUI state
#ifdef _WIN32
  switch ((audioStreamer::Interface)win_interface_n)
  {
    case audioStreamer::WIN_AUDIO_ASIO:
    {
/* TODO: no GUI
      asio_input1
      asio_output1
*/
      if (queryAsioDevices()) enableComponents() ;

      this->driverComboBox->setSelectedItemIndex(asio_driver) ;
      this->sourceComboBox->setSelectedItemIndex(asio_input0) ;
      this->sinkComboBox  ->setSelectedItemIndex(asio_output0) ;

      break ;
    }
    case audioStreamer::WIN_AUDIO_KS:
    {
      if (queryKernelstreamingDevices()) enableComponents() ;

      bool is_16_bps         = ks_bit_depth   == CLIENT::BIT_DEPTH_16 ;
      bool is_24_bps         = ks_bit_depth   == CLIENT::BIT_DEPTH_24 ;
      bool is_32_bps         = ks_bit_depth   == CLIENT::BIT_DEPTH_32 ;
      bool is_44_khz         = ks_sample_rate == CLIENT::SAMPLE_RATE_44100 ;
      bool is_48_khz         = ks_sample_rate == CLIENT::SAMPLE_RATE_48000 ;
      bool is_96_khz         = ks_sample_rate == CLIENT::SAMPLE_RATE_96000 ;
      int  buffer_size_index = CLIENT::BUFFER_SIZES.indexOf(String(ks_buffer_size)) ;

      this->sourceComboBox->setSelectedItemIndex(ks_input  + 1) ;
      this->sinkComboBox  ->setSelectedItemIndex(ks_output + 1) ;
      this->bufferComboBox->setSelectedItemIndex(buffer_size_index) ;
      this->bps16Button   ->setToggleState(is_16_bps , juce::dontSendNotification) ;
      this->bps24Button   ->setToggleState(is_24_bps , juce::dontSendNotification) ;
      this->bps32Button   ->setToggleState(is_32_bps , juce::dontSendNotification) ;
      this->kHz44Button   ->setToggleState(is_44_khz , juce::dontSendNotification) ;
      this->kHz48Button   ->setToggleState(is_48_khz , juce::dontSendNotification) ;
      this->kHz96Button   ->setToggleState(is_96_khz , juce::dontSendNotification) ;
      this->nBuffersSlider->setValue(ks_n_buffers) ;

      break ;
    }
    case audioStreamer::WIN_AUDIO_DS:
    {
/* TODO: no GUI
      ds_input1
      ds_input2
      ds_input3
      ds_output1
      ds_output2
      ds_output3
*/
      if (queryDirectsoundDevices()) enableComponents() ;

      bool is_16_bps         = ds_bit_depth   == CLIENT::BIT_DEPTH_16 ;
      bool is_24_bps         = ds_bit_depth   == CLIENT::BIT_DEPTH_24 ;
      bool is_32_bps         = ds_bit_depth   == CLIENT::BIT_DEPTH_32 ;
      bool is_44_khz         = ds_sample_rate == CLIENT::SAMPLE_RATE_44100 ;
      bool is_48_khz         = ds_sample_rate == CLIENT::SAMPLE_RATE_48000 ;
      bool is_96_khz         = ds_sample_rate == CLIENT::SAMPLE_RATE_96000 ;
      int  buffer_size_index = CLIENT::BUFFER_SIZES.indexOf(String(ds_buffer_size)) ;

      this->sourceComboBox->setSelectedItemIndex(ds_input0  + 1) ;
      this->sinkComboBox  ->setSelectedItemIndex(ds_output0 + 1) ;
      this->bufferComboBox->setSelectedItemIndex(buffer_size_index) ;
      this->bps16Button   ->setToggleState(is_16_bps , juce::dontSendNotification) ;
      this->bps24Button   ->setToggleState(is_24_bps , juce::dontSendNotification) ;
      this->bps32Button   ->setToggleState(is_32_bps , juce::dontSendNotification) ;
      this->kHz44Button   ->setToggleState(is_44_khz , juce::dontSendNotification) ;
      this->kHz48Button   ->setToggleState(is_48_khz , juce::dontSendNotification) ;
      this->kHz96Button   ->setToggleState(is_96_khz , juce::dontSendNotification) ;
      this->nBuffersSlider->setValue(ds_n_buffers) ;

      break ;
    }
    case audioStreamer::WIN_AUDIO_WAVE:
    {
      if (queryWaveDevices()) enableComponents() ;

      bool is_16_bps         = wave_bit_depth   == CLIENT::BIT_DEPTH_16 ;
      bool is_24_bps         = wave_bit_depth   == CLIENT::BIT_DEPTH_24 ;
      bool is_32_bps         = wave_bit_depth   == CLIENT::BIT_DEPTH_32 ;
      bool is_44_khz         = wave_sample_rate == CLIENT::SAMPLE_RATE_44100 ;
      bool is_48_khz         = wave_sample_rate == CLIENT::SAMPLE_RATE_48000 ;
      bool is_96_khz         = wave_sample_rate == CLIENT::SAMPLE_RATE_96000 ;
      int  buffer_size_index = CLIENT::BUFFER_SIZES.indexOf(StringRef(String(wave_buffer_size))) ;

      this->sourceComboBox->setSelectedItemIndex(wave_input  + 1) ;
      this->sinkComboBox  ->setSelectedItemIndex(wave_output + 1) ;
      this->bufferComboBox->setSelectedItemIndex(buffer_size_index) ;
      this->bps16Button   ->setToggleState(is_16_bps , juce::dontSendNotification) ;
      this->bps24Button   ->setToggleState(is_24_bps , juce::dontSendNotification) ;
      this->bps32Button   ->setToggleState(is_32_bps , juce::dontSendNotification) ;
      this->kHz44Button   ->setToggleState(is_44_khz , juce::dontSendNotification) ;
      this->kHz48Button   ->setToggleState(is_48_khz , juce::dontSendNotification) ;
      this->kHz96Button   ->setToggleState(is_96_khz , juce::dontSendNotification) ;
      this->nBuffersSlider->setValue(wave_n_buffers) ;

      break ;
    }
    default: break ;
  }
#else // _WIN32
#  ifdef _MAC
  if (queryCoreaudioDevices()) enableComponents() ;

  bool is_16_bps = mac_bit_depth   == CONFIG::BIT_DEPTH_16 ;
  bool is_24_bps = mac_bit_depth   == CONFIG::BIT_DEPTH_24 ;
  bool is_32_bps = mac_bit_depth   == CONFIG::BIT_DEPTH_32 ;
  bool is_44_khz = mac_sample_rate == CONFIG::SAMPLE_RATE_44100 ;
  bool is_48_khz = mac_sample_rate == CONFIG::SAMPLE_RATE_48000 ;
  bool is_96_khz = mac_sample_rate == CONFIG::SAMPLE_RATE_96000 ;

  this->bps16Button   ->setToggleState(is_16_bps , juce::dontSendNotification) ;
  this->bps24Button   ->setToggleState(is_24_bps , juce::dontSendNotification) ;
  this->bps32Button   ->setToggleState(is_32_bps , juce::dontSendNotification) ;
  this->kHz44Button   ->setToggleState(is_44_khz , juce::dontSendNotification) ;
  this->kHz48Button   ->setToggleState(is_48_khz , juce::dontSendNotification) ;
  this->kHz96Button   ->setToggleState(is_96_khz , juce::dontSendNotification) ;
  this->nSourcesSlider->setValue(mac_n_inputs) ;

#  else // _MAC
  switch ((audioStreamer::Interface)nix_interface_n)
  {
    case audioStreamer::NIX_AUDIO_JACK:
    {
      if (queryJackServers()) enableComponents() ;

      this->driverComboBox->setSelectedItemIndex(jack_server) ;
      this->nixConfigLabel->setText(GUI::JACK_NAME_LABEL_TEXT , juce::dontSendNotification) ;
      this->nixConfigText ->setText(jack_name ,                 juce::dontSendNotification) ;
      this->nSourcesSlider->setValue(jack_n_inputs) ;
      this->nSinksSlider  ->setValue(jack_n_outputs) ;

      break ;
    }
    case audioStreamer::NIX_AUDIO_ALSA:
    {
      if (queryAlsaDevices()) enableComponents() ;

      this->nixConfigLabel->setText(GUI::ALSA_CONFIG_LABEL_TEXT , juce::dontSendNotification) ;
      this->nixConfigText ->setText(alsa_config ,                 juce::dontSendNotification) ;

      break ;
    }
    default: break ;
  }
#  endif // _MAC
#endif // _WIN32
}

void ConfigAudio::setConfig(Identifier a_key , var a_value)
{
  this->configStore.setProperty(a_key , a_value , nullptr) ;
}

void ConfigAudio::restoreDefaults()
{
  int win_interface_n = int(this->configStore[CONFIG::WIN_AUDIO_IF_ID]) ;
  int nix_interface_n = int(this->configStore[CONFIG::NIX_AUDIO_IF_ID]) ;

#ifdef _WIN32
  switch ((audioStreamer::Interface)win_interface_n)
  {
    case audioStreamer::WIN_AUDIO_ASIO:
    {
      setConfig(CONFIG::ASIO_DRIVER_ID  , CONFIG::DEFAULT_ASIO_DRIVER) ;
      setConfig(CONFIG::ASIO_INPUT0_ID  , CONFIG::DEFAULT_ASIO_INPUT0) ;
      setConfig(CONFIG::ASIO_INPUT1_ID  , CONFIG::DEFAULT_ASIO_INPUT1) ;
      setConfig(CONFIG::ASIO_OUTPUT0_ID , CONFIG::DEFAULT_ASIO_OUTPUT0) ;
      setConfig(CONFIG::ASIO_OUTPUT1_ID , CONFIG::DEFAULT_ASIO_OUTPUT1) ;

      break ;
    }
    case audioStreamer::WIN_AUDIO_KS:
    {
      setConfig(CONFIG::KS_INPUT_ID      , CONFIG::DEFAULT_KS_INPUT) ;
      setConfig(CONFIG::KS_OUTPUT_ID     , CONFIG::DEFAULT_KS_OUTPUT) ;
      setConfig(CONFIG::KS_SAMPLERATE_ID , CONFIG::DEFAULT_KS_SAMPLERATE) ;
      setConfig(CONFIG::KS_BITDEPTH_ID   , CONFIG::DEFAULT_KS_BITDEPTH) ;
      setConfig(CONFIG::KS_BLOCKSIZE_ID  , CONFIG::DEFAULT_KS_BLOCKSIZE) ;
      setConfig(CONFIG::KS_NBLOCKS_ID    , CONFIG::DEFAULT_KS_N_BLOCKS) ;

      break ;
    }
    case audioStreamer::WIN_AUDIO_DS:
    {
      setConfig(CONFIG::DS_INPUT0_ID     , CONFIG::DEFAULT_DS_INPUT0) ;
      setConfig(CONFIG::DS_INPUT1_ID     , CONFIG::DEFAULT_DS_INPUT1) ;
      setConfig(CONFIG::DS_INPUT2_ID     , CONFIG::DEFAULT_DS_INPUT2) ;
      setConfig(CONFIG::DS_INPUT3_ID     , CONFIG::DEFAULT_DS_INPUT3) ;
      setConfig(CONFIG::DS_OUTPUT0_ID    , CONFIG::DEFAULT_DS_OUTPUT0) ;
      setConfig(CONFIG::DS_OUTPUT1_ID    , CONFIG::DEFAULT_DS_OUTPUT1) ;
      setConfig(CONFIG::DS_OUTPUT2_ID    , CONFIG::DEFAULT_DS_OUTPUT2) ;
      setConfig(CONFIG::DS_OUTPUT3_ID    , CONFIG::DEFAULT_DS_OUTPUT3) ;
      setConfig(CONFIG::DS_SAMPLERATE_ID , CONFIG::DEFAULT_DS_SAMPLERATE) ;
      setConfig(CONFIG::DS_BITDEPTH_ID   , CONFIG::DEFAULT_DS_BITDEPTH) ;
      setConfig(CONFIG::DS_BLOCKSIZE_ID  , CONFIG::DEFAULT_DS_BLOCKSIZE) ;
      setConfig(CONFIG::DS_NBLOCKS_ID    , CONFIG::DEFAULT_DS_N_BLOCKS) ;

      break ;
    }
    case audioStreamer::WIN_AUDIO_WAVE:
    {
      setConfig(CONFIG::WAVE_INPUT_ID      , CONFIG::DEFAULT_WAVE_INPUT) ;
      setConfig(CONFIG::WAVE_OUTPUT_ID     , CONFIG::DEFAULT_WAVE_OUTPUT) ;
      setConfig(CONFIG::WAVE_SAMPLERATE_ID , CONFIG::DEFAULT_WAVE_SAMPLERATE) ;
      setConfig(CONFIG::WAVE_BITDEPTH_ID   , CONFIG::DEFAULT_WAVE_BITDEPTH) ;
      setConfig(CONFIG::WAVE_BLOCKSIZE_ID  , CONFIG::DEFAULT_WAVE_BLOCKSIZE) ;
      setConfig(CONFIG::WAVE_NBLOCKS_ID    , CONFIG::DEFAULT_WAVE_N_BLOCKS) ;

      break ;
    }
  }
#else // _WIN32
#  ifdef _MAC
  setConfig(CONFIG::MAC_DEVICE_ID     , CONFIG::DEFAULT_MAC_DEVICE) ;
  setConfig(CONFIG::MAC_NINPUTS_ID    , CONFIG::DEFAULT_N_INPUTS) ;
  setConfig(CONFIG::MAC_SAMPLERATE_ID , CONFIG::DEFAULT_MAC_SAMPLERATE) ;
  setConfig(CONFIG::MAC_BITDEPTH_ID   , CONFIG::DEFAULT_MAC_BITDEPTH) ;
#  else // _MAC
  switch ((audioStreamer::Interface)nix_interface_n)
  {
    case audioStreamer::NIX_AUDIO_JACK:
    {
      setConfig(CONFIG::JACK_SERVER_ID   , CONFIG::DEFAULT_JACK_SERVER) ;
      setConfig(CONFIG::JACK_NAME_ID     , CONFIG::DEFAULT_JACK_NAME) ;
      setConfig(CONFIG::JACK_NINPUTS_ID  , CONFIG::DEFAULT_N_INPUTS) ;
      setConfig(CONFIG::JACK_NOUTPUTS_ID , CONFIG::DEFAULT_N_OUTPUTS) ;

      break ;
    }
    case audioStreamer::NIX_AUDIO_ALSA:
    {
      setConfig(CONFIG::ALSA_CONFIG_ID  , CONFIG::DEFAULT_ALSA_CONFIG) ;

      break ;
    }
  }
#  endif // _MAC
#endif // _WIN32
}

void ConfigAudio::enableComponents()
{
  bool is_asio , is_ks , is_ds , is_wave , is_ca , is_jack , is_alsa ;
       is_asio = is_ks = is_ds = is_wave = is_ca = is_jack = is_alsa = false ;

#if _WIN32
  int interface_n = int(this->configStore[CONFIG::WIN_AUDIO_IF_ID]) ;
  is_asio         = interface_n == (int)audioStreamer::WIN_AUDIO_ASIO ; // asio
  is_ks           = interface_n == (int)audioStreamer::WIN_AUDIO_KS ;   // kernel streaming
  is_ds           = interface_n == (int)audioStreamer::WIN_AUDIO_DS ;   // directsound
  is_wave         = interface_n == (int)audioStreamer::WIN_AUDIO_WAVE ; // wave
#else // _WIN32
#  ifdef _MAC
  is_ca           = true ;                                              // coreaudio
#  else // _MAC
  int interface_n = int(this->configStore[CONFIG::NIX_AUDIO_IF_ID]) ;
  is_jack         = interface_n == (int)audioStreamer::NIX_AUDIO_JACK ; // jack
  is_alsa         = interface_n == (int)audioStreamer::NIX_AUDIO_ALSA ; // alsa
#  endif // _MAC
#endif // _WIN32

  // common
  this->defaultsButton ->setVisible(!is_asio                                  ) ;
  this->asioButton     ->setVisible( is_asio                                  ) ;
  // io group
  this->ioGroup        ->setEnabled(!is_ca                                    ) ;
  this->modeLabel      ->setEnabled(!is_ca                                    ) ;
  this->modeComboBox   ->setEnabled(!is_ca                                    ) ;
  this->driverLabel    ->setEnabled( is_jack || is_asio                       ) ;
  this->driverComboBox ->setEnabled( is_jack || is_asio                       ) ;
  this->sourceLabel    ->setEnabled( is_ks   || is_ds   || is_wave  || is_asio) ;
  this->sourceComboBox ->setEnabled( is_ks   || is_ds   || is_wave  || is_asio) ;
  this->sinkLabel      ->setEnabled( is_ks   || is_ds   || is_wave  || is_asio) ;
  this->sinkComboBox   ->setEnabled( is_ks   || is_ds   || is_wave  || is_asio) ;
  //  format group
  this->formatGroup    ->setEnabled( is_ks   || is_ds   || is_wave  || is_ca  ) ;
  this->bitdepthLabel  ->setEnabled( is_ks   || is_ds   || is_wave  || is_ca  ) ;
  this->bps16Button    ->setEnabled( is_ks   || is_ds   || is_wave  || is_ca  ) ;
  this->bps24Button    ->setEnabled( is_ks   || is_ds   || is_wave  || is_ca  ) ;
  this->bps32Button    ->setEnabled( is_ks   || is_ds   || is_wave  || is_ca  ) ;
  this->samplerateLabel->setEnabled( is_ks   || is_ds   || is_wave  || is_ca  ) ;
  this->kHz44Button    ->setEnabled( is_ks   || is_ds   || is_wave  || is_ca  ) ;
  this->kHz48Button    ->setEnabled( is_ks   || is_ds   || is_wave  || is_ca  ) ;
  this->kHz96Button    ->setEnabled( is_ks   || is_ds   || is_wave  || is_ca  ) ;
  // buffers group
  this->buffersGroup   ->setEnabled( is_ks   || is_ds   || is_wave            ) ;
  this->buffersLabel   ->setEnabled( is_ks   || is_ds   || is_wave            ) ;
  this->nBuffersSlider ->setEnabled( is_ks   || is_ds   || is_wave            ) ;
  this->xLabel         ->setEnabled( is_ks   || is_ds   || is_wave            ) ;
  this->bufferComboBox ->setEnabled( is_ks   || is_ds   || is_wave            ) ;
  this->bytesLabel     ->setEnabled( is_ks   || is_ds   || is_wave            ) ;
  // routing group
  this->routingGroup   ->setEnabled( is_jack || is_alsa || is_ca              ) ;
  this->nixConfigLabel ->setEnabled( is_jack || is_alsa                       ) ;
  this->nixConfigText  ->setEnabled( is_jack || is_alsa                       ) ;
  this->nSourcesLabel  ->setEnabled( is_jack || is_ca                         ) ;
  this->nSourcesSlider ->setEnabled( is_jack || is_ca                         ) ;
  this->nSinksLabel    ->setEnabled( is_jack                                  ) ;
  this->nSinksSlider   ->setEnabled( is_jack                                  ) ;

DEBUG_TRACE_CONFIG_AUDIO_GUI_LOAD
}

#ifdef _WIN32
bool ConfigAudio::queryAsioDevices()
{
  // TODO: asio nyi
  // NOTE: see njasiodrv_if.h
  bool is_asio_available = njasiodrv_avail() ;

  if (is_asio_available)
  {
    this->driverComboBox->addItem("asio driver 0" , 1) ;
    this->sourceComboBox->addItem("asio device 0" , 1) ;
    this->sinkComboBox  ->addItem("asio device 0" , 1) ;
    this->driverComboBox->addItem("asio driver 1" , 2) ;
    this->sourceComboBox->addItem("asio device 1" , 2) ;
    this->sinkComboBox  ->addItem("asio device 1" , 2) ;
  }
  else
  {
    this->driverComboBox->addItem("asio not supported" , 1) ;
    this->sourceComboBox->addItem("(no asio devices found)"    , 1) ;
    this->sinkComboBox  ->addItem("(no asio devices found)"    , 1) ;
  }

  return is_asio_available ;
}

bool ConfigAudio::queryKernelstreamingDevices()
{
  bool is_ks_available = true ; // TODO:

  this->sourceComboBox->clear(juce::dontSendNotification) ;
  this->sinkComboBox  ->clear(juce::dontSendNotification) ;
  if (is_ks_available)
  {
    this->sourceComboBox->addItem("default device" , 1) ;
    this->sinkComboBox  ->addItem("default device" , 1) ;
    this->bufferComboBox->addItemList(CLIENT::BUFFER_SIZES , 1) ;
  }
  else
  {
    this->sourceComboBox->addItem("kernel streaming unavailable" , 1) ;
    this->sinkComboBox  ->addItem("kernel streaming unavailable" , 1) ;
  }

  return is_ks_available ;
}


bool ConfigAudio::queryDirectsoundDevices()
{
  // see dsound.h
  StringArray      device_names ;
  LPDSENUMCALLBACK ds_enum_cb      = (LPDSENUMCALLBACK)DSEnumProc ;
  HRESULT          result          = DirectSoundEnumerate(ds_enum_cb , &device_names) ;
  bool             is_ds_available = !FAILED(result) ;

  if (is_ds_available)
  {
    this->sourceComboBox->addItemList(device_names         , 1) ;
    this->sinkComboBox  ->addItemList(device_names         , 1) ;
    this->bufferComboBox->addItemList(CLIENT::BUFFER_SIZES , 1) ;
  }
  else
  {
    this->sourceComboBox->addItem("(directsound unavaliable)" , 1) ;
    this->sinkComboBox  ->addItem("(directsound unavaliable)" , 1) ;
  }

  return is_ds_available ;
}

bool ConfigAudio::queryWaveDevices()
{
  // NOTE: see MMsystem.h
  WAVEOUTCAPS capabilities ;
  StringArray device_names ;
  UINT        caps_size         = sizeof(capabilities) ;
  int         n_devices         = (int)waveOutGetNumDevs() ;
  bool        is_wave_available = !!n_devices ;

  if (n_devices)
  {
    for (int device_n = -1 ; device_n < n_devices ; ++device_n)
    {
      UINT caps_result = waveOutGetDevCaps(device_n , &capabilities , caps_size) ;

      device_names.add((caps_result == MMSYSERR_NOERROR)?
                       String(capabilities.szPname)                                         :
                       String("(device error)")                                             ) ;
    }
    this->sourceComboBox->addItemList(device_names         , 1) ;
    this->sinkComboBox  ->addItemList(device_names         , 1) ;
    this->bufferComboBox->addItemList(CLIENT::BUFFER_SIZES , 1) ;
  }
/*
  if (n_devices)
  {
    for (int device_n = -1 ; device_n < n_devices ; ++device_n)
    {
      UINT   caps_result = waveOutGetDevCaps(device_n , &capabilities , caps_size) ;
      String device_name = (caps_result == MMSYSERR_NOERROR)?
                           String(capabilities.szPname)     :
                           String("(device error)")         ;
      this->sourceComboBox->addItem(device_name , device_n + 2) ;
      this->sinkComboBox  ->addItem(device_name , device_n + 2) ;
    }

    this->bufferComboBox->addItemList(CLIENT::BUFFER_SIZES , 1) ;
  }
*/
  else
  {
    this->sourceComboBox->addItem("(no wave devices found)" , 1) ;
    this->sinkComboBox  ->addItem("(no wave devices found)" , 1) ;
  }

  return is_wave_available ;
}
#else // _WIN32
#  ifdef _MAC
bool ConfigAudio::queryCoreaudioDevices() { return true ; } // TODO: juce or ryo ?
#  else // _MAC
bool ConfigAudio::queryJackServers() // TODO: juce or ryo ?
{
  this->driverComboBox->addItem("default jack server" , 1) ;

  return true ;
}

bool ConfigAudio::queryAlsaDevices() { enableComponents() ; } // TODO: juce or ryo ?
#  endif // _MAC
#endif // _WIN32


/* ConfigAudio class private class methods */

#ifdef _WIN32
BOOL CALLBACK ConfigAudio::DSEnumProc(LPGUID  lpGUID      , LPCTSTR lpszDesc ,
                                      LPCTSTR lpszDrvName , LPVOID  device_names)
{
/* TODO: if we need guids
  LPGUID guid = nullptr ;
  if (lpGUID != nullptr) // NULL == "Primary Sound Driver" (always first)
  {
    if ((guid = (LPGUID)malloc(sizeof(GUID))) == nullptr) return TRUE ;

    memcpy(guid , lpGUID , sizeof(GUID)) ;
  }

  // store guid -->
  std::array<LPGUID> ???
  return TRUE ;
  // then eventually
  free(guid) ;
*/
  ((StringArray*)device_names)->add((lpGUID == nullptr)? "Primary Sound Driver" :
                                                         String(lpszDesc)       ) ;

  return TRUE ;
}
#endif // _WIN32

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConfigAudio" componentName=""
                 parentClasses="public Component" constructorParams="ValueTree config_store"
                 variableInitialisers="configStore(config_store)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="614" initialHeight="434">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10" fill="solid: ff002000" hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="ioGroup" id="35b859a43662c4ca" memberName="ioGroup" virtualName=""
                  explicitFocusOrder="0" pos="132 38 350 126" outlinecol="ff808080"
                  textcol="ffffffff" title="i/o" textpos="33"/>
  <GROUPCOMPONENT name="formatGroup" id="29fbf63c3d8d3e1b" memberName="formatGroup"
                  virtualName="" explicitFocusOrder="0" pos="132 176 350 60" outlinecol="ff808080"
                  textcol="ffffffff" title="format" textpos="33"/>
  <GROUPCOMPONENT name="buffersGroup" id="76ccd33b9d1f605a" memberName="buffersGroup"
                  virtualName="" explicitFocusOrder="0" pos="132 250 350 48" outlinecol="ff808080"
                  textcol="ffffffff" title="buffers (122.2ms)" textpos="33"/>
  <GROUPCOMPONENT name="routingGroup" id="65c871d13e6e8329" memberName="routingGroup"
                  virtualName="" explicitFocusOrder="0" pos="132 312 350 74" outlinecol="ff808080"
                  textcol="ffffffff" title="routing" textpos="33"/>
  <TEXTBUTTON name="defaultsButton" id="f03cc2695d9642e1" memberName="defaultsButton"
              virtualName="" explicitFocusOrder="0" pos="68R 4 64 24" buttonText="defaults"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="asioButton" id="130c484d97b7c34a" memberName="asioButton"
              virtualName="" explicitFocusOrder="0" pos="68R 4 64 24" buttonText="asio config"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="modeLabel" id="582ccc898eac60c0" memberName="modeLabel"
         virtualName="" explicitFocusOrder="0" pos="140 56 64 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="interface:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="modeComboBox" id="d9fdbc02138c7335" memberName="modeComboBox"
            virtualName="" explicitFocusOrder="1" pos="212 56 256 18" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="driverLabel" id="5cb85d669129843" memberName="driverLabel"
         virtualName="" explicitFocusOrder="0" pos="140 82 64 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="driver:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="driverComboBox" id="bc523f21b8e70676" memberName="driverComboBox"
            virtualName="" explicitFocusOrder="1" pos="212 82 256 18" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="sourceLabel" id="28e9c840504ea936" memberName="sourceLabel"
         virtualName="" explicitFocusOrder="0" pos="140 108 64 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="input:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="sourceComboBox" id="195d38c0dfa0b780" memberName="sourceComboBox"
            virtualName="" explicitFocusOrder="2" pos="212 108 256 18" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="sinkLabel" id="a67b459c94aba72e" memberName="sinkLabel"
         virtualName="" explicitFocusOrder="0" pos="140 134 64 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="output:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="sinkComboBox" id="3b81e2ff4dec7469" memberName="sinkComboBox"
            virtualName="" explicitFocusOrder="3" pos="212 134 256 18" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="bitdepthLabel" id="cca18f8e57581cc5" memberName="bitdepthLabel"
         virtualName="" explicitFocusOrder="0" pos="140 190 64 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="bit depth:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="bps16Button" id="ccb740c03ababc9f" memberName="bps16Button"
                virtualName="" explicitFocusOrder="4" pos="212 191 64 18" txtcol="ffffffff"
                buttonText="16bit" connectedEdges="0" needsCallback="1" radioGroupId="1"
                state="1"/>
  <TOGGLEBUTTON name="bps24Button" id="2bfc206fbb162f7f" memberName="bps24Button"
                virtualName="" explicitFocusOrder="5" pos="288 191 64 18" txtcol="ffffffff"
                buttonText="24bit" connectedEdges="0" needsCallback="1" radioGroupId="1"
                state="0"/>
  <TOGGLEBUTTON name="bps32Button" id="1cc075dc412ce404" memberName="bps32Button"
                virtualName="" explicitFocusOrder="6" pos="364 191 64 18" txtcol="ffffffff"
                buttonText="32bit" connectedEdges="0" needsCallback="1" radioGroupId="1"
                state="0"/>
  <LABEL name="samplerateLabel" id="e79ba6de77a4b042" memberName="samplerateLabel"
         virtualName="" explicitFocusOrder="0" pos="140 210 72 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="sample rate:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="kHz44Button" id="56ab804241495c7b" memberName="kHz44Button"
                virtualName="" explicitFocusOrder="7" pos="212 211 64 18" txtcol="ffffffff"
                buttonText="44.1kHz" connectedEdges="0" needsCallback="1" radioGroupId="2"
                state="1"/>
  <TOGGLEBUTTON name="kHz48Button" id="415b27279e48004f" memberName="kHz48Button"
                virtualName="" explicitFocusOrder="8" pos="288 211 64 18" txtcol="ffffffff"
                buttonText="48kHz" connectedEdges="0" needsCallback="1" radioGroupId="2"
                state="0"/>
  <TOGGLEBUTTON name="kHz96Button" id="4241809c486a0995" memberName="kHz96Button"
                virtualName="" explicitFocusOrder="9" pos="364 211 64 18" txtcol="ffffffff"
                buttonText="96kHz" connectedEdges="0" needsCallback="1" radioGroupId="2"
                state="0"/>
  <LABEL name="buffersLabel" id="78ac240fcc5eed16" memberName="buffersLabel"
         virtualName="" explicitFocusOrder="0" pos="140 268 64 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="# of buffers" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="nBuffersSlider" id="76a832d1fac666e" memberName="nBuffersSlider"
          virtualName="" explicitFocusOrder="10" pos="212 268 64 18" min="0"
          max="16" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="xLabel" id="5a9596c9eb8db178" memberName="xLabel" virtualName=""
         explicitFocusOrder="0" pos="275 268 16 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="x" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="bufferComboBox" id="bef2196516ab5821" memberName="bufferComboBox"
            virtualName="" explicitFocusOrder="11" pos="292 268 52 18" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="bytesLabel" id="f93456e3175d33d6" memberName="bytesLabel"
         virtualName="" explicitFocusOrder="0" pos="346 268 64 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="bytes" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="nixConfigLabel" id="78568b552c534b6d" memberName="nixConfigLabel"
         virtualName="" explicitFocusOrder="0" pos="140 332 64 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="client name" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="nixConfigText" id="fdccbcd88a94d4bb" memberName="nixConfigText"
              virtualName="" explicitFocusOrder="12" pos="212 332 256 18" textcol="ff808080"
              bkgcol="ff000000" initialText="" multiline="0" retKeyStartsLine="0"
              readonly="0" scrollbars="1" caret="1" popupmenu="0"/>
  <LABEL name="nSourcesLabel" id="fa0df2e2a11e57d8" memberName="nSourcesLabel"
         virtualName="" explicitFocusOrder="0" pos="140 358 64 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="# of sources" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="nSourcesSlider" id="3a13d77beb71d910" memberName="nSourcesSlider"
          virtualName="" explicitFocusOrder="13" pos="214 358 64 18" min="0"
          max="16" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="nSinksLabel" id="2da0a2441a20f3b0" memberName="nSinksLabel"
         virtualName="" explicitFocusOrder="0" pos="330 358 64 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="# of sinks" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="nSinksSlider" id="182ff4a5ae799417" memberName="nSinksSlider"
          virtualName="" explicitFocusOrder="14" pos="404 358 64 18" min="0"
          max="16" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
