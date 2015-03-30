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

#include "LinJam.h"
#include "./Trace/TraceConfig.h"

//[/Headers]

#include "ConfigAudio.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigAudio::ConfigAudio (ValueTree audio_store, Value linjam_status)
    : audioStore(audio_store)
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
    nixConfigText->setText (GUI::JACK_NAME_LABEL_TEXT);

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

  this->linjamStatus.referTo(linjam_status) ; this->linjamStatus.addListener(this) ;

  int audio_api_n = int(this->audioStore[CONFIG::AUDIO_API_ID]) ;
  this->modeComboBox  ->addItemList(CLIENT::AUDIO_APIS , 1) ;
  this->modeComboBox  ->setSelectedItemIndex(audio_api_n , juce::dontSendNotification) ;
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
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

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

  int audio_api_n = int(this->audioStore[CONFIG::AUDIO_API_ID]) ;
#ifdef _WIN32
  switch ((audioStreamer::WinApi)audio_api_n)
  {
    case audioStreamer::WIN_AUDIO_KS:
      sample_rate_key = CONFIG::KS_SAMPLERATE_ID ;
      bit_depth_key   = CONFIG::KS_BITDEPTH_ID ;
      break ;
    case audioStreamer::WIN_AUDIO_DS:
      sample_rate_key = CONFIG::DS_SAMPLERATE_ID ;
      bit_depth_key   = CONFIG::DS_BITDEPTH_ID ;
      break ;
    case audioStreamer::WIN_AUDIO_WAVE:
      sample_rate_key = CONFIG::WAVE_SAMPLERATE_ID ;
      bit_depth_key   = CONFIG::WAVE_BITDEPTH_ID ;
      break ;
    default: break ;
  }
#else // _WIN32
#  ifndef _MAC
  sample_rate_key = CONFIG::CA_SAMPLERATE_ID ;
  bit_depth_key   = CONFIG::CA_BITDEPTH_ID;
#  else // _MAC
  switch ((audioStreamer::NixApi)audio_api_n)
  {
    case audioStreamer::NIX_AUDIO_ALSA:
      sample_rate_key = CONFIG::ALSA_SAMPLERATE_ID ;
      bit_depth_key   = CONFIG::ALSA_BITDEPTH_ID ;
      break ;
    default: break ;
  }
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

    if      (buttonThatWasClicked == defaultsButton)
    {
        //[UserButtonCode_defaultsButton] -- add your button handler code here..

      restoreDefaults() ; loadParams() ;

        //[/UserButtonCode_defaultsButton]
    }
    else if (buttonThatWasClicked == asioButton)
    {
        //[UserButtonCode_asioButton] -- add your button handler code here..

      // TODO: make asioButton a checkbox
      config_key = CONFIG::ASIO_CONTROL_ID ;
      value      = var(!bool(this->audioStore[CONFIG::ASIO_CONTROL_ID])) ;

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

  int        audio_api_n = int(this->audioStore[CONFIG::AUDIO_API_ID]) ;
  int        option_n    = comboBoxThatHasChanged->getSelectedItemIndex() ;
  String     option_text = comboBoxThatHasChanged->getText() ;
  Identifier key ;
  var        value ;

    //[/UsercomboBoxChanged_Pre]

    if      (comboBoxThatHasChanged == modeComboBox)
    {
        //[UserComboBoxCode_modeComboBox] -- add your combo box handling code here..

      key   = CONFIG::AUDIO_API_ID ;
      value = var((~option_n) ? option_n : CONFIG::DEFAULT_AUDIO_API) ;

      this->modeComboBox->setSelectedItemIndex(option_n) ;

        //[/UserComboBoxCode_modeComboBox]
    }
    else if (comboBoxThatHasChanged == driverComboBox)
    {
        //[UserComboBoxCode_driverComboBox] -- add your combo box handling code here..

#ifdef _WIN32
      key = CONFIG::ASIO_DRIVER_ID ;
#else // _WIN32
#  ifndef _MAC
      key = CONFIG::JACK_SERVER_ID ;
#  endif // _MAC
#endif // _WIN32
      value = var((~option_n) ? option_n : 0) ;

      this->driverComboBox->setSelectedItemIndex(option_n) ;

        //[/UserComboBoxCode_driverComboBox]
    }
    else if (comboBoxThatHasChanged == sourceComboBox)
    {
        //[UserComboBoxCode_sourceComboBox] -- add your combo box handling code here..

#ifdef _WIN32
      switch ((audioStreamer::WinApi)audio_api_n)
      {
        case audioStreamer::WIN_AUDIO_ASIO:
          option_n = (~option_n) ? option_n     : CONFIG::DEFAULT_ASIO_INPUTBN ;
          key      = CONFIG::ASIO_INPUTB_ID ;
          value    = var(option_n) ;
          this->sourceComboBox->setSelectedItemIndex(option_n) ;                 break ;
        case audioStreamer::WIN_AUDIO_KS:
          key      = CONFIG::KS_INPUT_ID ;
          option_n = (~option_n) ? option_n - 1 : CONFIG::DEFAULT_KS_INPUTN ;
          value    = var(option_n) ;
          this->sourceComboBox->setSelectedItemIndex(option_n + 1) ;             break ;
        case audioStreamer::WIN_AUDIO_DS:
          key      = CONFIG::DS_INPUT_ID ;
          option_n = (~option_n) ? option_n     : GUI::DEFAULT_DS_INDEX ;
          value    = var(option_text) ;
          this->sourceComboBox->setSelectedItemIndex(option_n) ;                 break ;
        case audioStreamer::WIN_AUDIO_WAVE:
          option_n = (~option_n) ? option_n - 1 : CONFIG::DEFAULT_WAVE_INPUTN ;
          key      = CONFIG::WAVE_INPUT_ID ;
          value    = var(option_n) ;
          this->sourceComboBox->setSelectedItemIndex(option_n + 1) ;             break ;
        default:                                                                 break ;
      }
#else // _WIN32
#  ifndef _MAC
      switch ((audioStreamer::NixApi)audio_api_n)
      {
        case audioStreamer::NIX_AUDIO_ALSA: /* TODO: */ break ;
        default:                                        break ;
      }
#  endif //  _MAC
#endif // _WIN32

        //[/UserComboBoxCode_sourceComboBox]
    }
    else if (comboBoxThatHasChanged == sinkComboBox)
    {
        //[UserComboBoxCode_sinkComboBox] -- add your combo box handling code here..

#ifdef _WIN32
      switch ((audioStreamer::WinApi)audio_api_n)
      {
        case audioStreamer::WIN_AUDIO_ASIO:
          option_n = (~option_n) ? option_n     : CONFIG::DEFAULT_ASIO_OUTPUTBN ;
          key      = CONFIG::ASIO_OUTPUTB_ID ;
          value    = var(option_n) ;
          this->sinkComboBox->setSelectedItemIndex(option_n) ;                    break ;
        case audioStreamer::WIN_AUDIO_KS:
          key      = CONFIG::KS_OUTPUT_ID ;
          option_n = (~option_n) ? option_n - 1 : CONFIG::DEFAULT_KS_OUTPUTN ;
          value    = var(option_n) ;
          this->sinkComboBox->setSelectedItemIndex(option_n + 1) ;                break ;
        case audioStreamer::WIN_AUDIO_DS:
          key      = CONFIG::DS_OUTPUT_ID ;
          option_n = (~option_n) ? option_n     : GUI::DEFAULT_DS_INDEX ;
          value    = var(option_text) ;
          this->sinkComboBox->setSelectedItemIndex(option_n) ;                    break ;
        case audioStreamer::WIN_AUDIO_WAVE:
          option_n = (~option_n) ? option_n - 1 : CONFIG::DEFAULT_WAVE_OUTPUTN ;
          key      = CONFIG::WAVE_OUTPUT_ID ;
          value    = var(option_n) ;
          this->sinkComboBox->setSelectedItemIndex(option_n + 1) ;                break ;
        default:                                                                  break ;
      }
#else // _WIN32
#  ifndef _MAC
      switch ((audioStreamer::NixApi)audio_api_n)
      {
        case audioStreamer::NIX_AUDIO_ALSA: /* TODO: */ break ;
        default:                                        break ;
      }
#  endif //  _MAC
#endif // _WIN32

        //[/UserComboBoxCode_sinkComboBox]
    }
    else if (comboBoxThatHasChanged == bufferComboBox)
    {
        //[UserComboBoxCode_bufferComboBox] -- add your combo box handling code here..

#ifdef _WIN32
      switch ((audioStreamer::WinApi)audio_api_n)
      {
        case audioStreamer::WIN_AUDIO_KS:   key = CONFIG::KS_BLOCKSIZE_ID ;   break ;
        case audioStreamer::WIN_AUDIO_DS:   key = CONFIG::DS_BLOCKSIZE_ID ;   break ;
        case audioStreamer::WIN_AUDIO_WAVE: key = CONFIG::WAVE_BLOCKSIZE_ID ; break ;
        default:                                                              break ;
      }
#else // _WIN32
#  ifndef _MAC
      switch ((audioStreamer::NixApi)audio_api_n)
      {
        case audioStreamer::NIX_AUDIO_ALSA: key = CONFIG::ALSA_BLOCKSIZE_ID ; break ;
        default:                                                              break ;
      }
#  endif //  _MAC
#endif // _WIN32
      value = var(option_text.getIntValue()) ;

        //[/UserComboBoxCode_bufferComboBox]
    }

    //[UsercomboBoxChanged_Post]

  setConfig(key , value) ;

  if (comboBoxThatHasChanged == this->bufferComboBox) updateLatency() ;

    //[/UsercomboBoxChanged_Post]
}

void ConfigAudio::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]

  int        audio_api_n = int(this->audioStore[CONFIG::AUDIO_API_ID]) ;
  Identifier config_key ;
  var        value       = var((int)sliderThatWasMoved->getValue()) ;

    //[/UsersliderValueChanged_Pre]

    if      (sliderThatWasMoved == nBuffersSlider)
    {
        //[UserSliderCode_nBuffersSlider] -- add your slider handling code here..

#ifdef _WIN32
      switch ((audioStreamer::WinApi)audio_api_n)
      {
        case audioStreamer::WIN_AUDIO_KS:   config_key = CONFIG::KS_NBLOCKS_ID ;   break ;
        case audioStreamer::WIN_AUDIO_DS:   config_key = CONFIG::DS_NBLOCKS_ID ;   break ;
        case audioStreamer::WIN_AUDIO_WAVE: config_key = CONFIG::WAVE_NBLOCKS_ID ; break ;
        default:                                                                   break ;
      }
#else // _WIN32
#  ifndef _MAC
      switch ((audioStreamer::NixApi)audio_api_n)
      {
        case audioStreamer::NIX_AUDIO_ALSA: config_key = CONFIG::ALSA_NBLOCKS_ID ; break ;
        default:                                                                   break ;
      }
#  endif // _MAC
#endif // _WIN32

        //[/UserSliderCode_nBuffersSlider]
    }
    else if (sliderThatWasMoved == nSourcesSlider)
    {
        //[UserSliderCode_nSourcesSlider] -- add your slider handling code here..

#ifndef _WIN32
#  ifdef _MAC
      config_key = CONFIG::CA_NINPUTS_KEY ;
#  else // _MAC
      switch ((audioStreamer::NixApi)audio_api_n)
      {
        case audioStreamer::NIX_AUDIO_JACK: config_key = CONFIG::JACK_NINPUTS_ID ;   break ;
        case audioStreamer::NIX_AUDIO_ALSA: config_key = CONFIG::ALSA_NCHANNELS_ID ; break ;
        default:                                                                     break ;
      }
#  endif // _MAC
#endif // _WIN32

        //[/UserSliderCode_nSourcesSlider]
    }
    else if (sliderThatWasMoved == nSinksSlider)
    {
        //[UserSliderCode_nSinksSlider] -- add your slider handling code here..

#ifndef _WIN32
#  ifndef _MAC
      switch ((audioStreamer::NixApi)audio_api_n)
      {
        case audioStreamer::NIX_AUDIO_JACK: config_key = CONFIG::JACK_NOUTPUTS_ID ; break ;
        default:                                                                    break ;
      }
#  endif // _MAC
#endif // _WIN32

        //[/UserSliderCode_nSinksSlider]
    }

    //[UsersliderValueChanged_Post]

  setConfig(config_key , value) ;

  if (sliderThatWasMoved == this->nBuffersSlider) updateLatency() ;

    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* ConfigAudio class private instance methods */

void ConfigAudio::valueChanged(Value& a_value)
{
  int linjam_status = int(a_value.getValue()) ;
  if (!a_value.refersToSameSourceAs(this->linjamStatus) ||
      linjam_status < LinJam::LINJAM_STATUS_AUDIOINIT   ||
      linjam_status > LinJam::LINJAM_STATUS_AUDIOERROR   ) return ;

  if (linjam_status == LinJam::LINJAM_STATUS_AUDIOINIT) disableComponents() ;
  else                                                  loadParams() ;
}

void ConfigAudio::loadParams()
{
  // initialize or reset GUI state
  populateDevices() ;

  // load config
  int    audio_api_n          = int(   this->audioStore[CONFIG::AUDIO_API_ID      ]) ;
#ifdef _WIN32
  int    asio_driver_n        = int(   this->audioStore[CONFIG::ASIO_DRIVER_ID    ]) ;
  int    asio_input_b_n       = int(   this->audioStore[CONFIG::ASIO_INPUTB_ID    ]) ;
  int    asio_input_e_n       = int(   this->audioStore[CONFIG::ASIO_INPUTE_ID    ]) ;
  int    asio_output_b_n      = int(   this->audioStore[CONFIG::ASIO_OUTPUTB_ID   ]) ;
  int    asio_output_e_n      = int(   this->audioStore[CONFIG::ASIO_OUTPUTE_ID   ]) ;
  int    should_show_asio_cp  = int(   this->audioStore[CONFIG::ASIO_CONTROL_ID   ]) ;
  int    ks_input_device_n    = int(   this->audioStore[CONFIG::KS_INPUT_ID       ]) ;
  int    ks_output_device_n   = int(   this->audioStore[CONFIG::KS_OUTPUT_ID      ]) ;
  int    ks_sample_rate       = int(   this->audioStore[CONFIG::KS_SAMPLERATE_ID  ]) ;
  int    ks_bit_depth         = int(   this->audioStore[CONFIG::KS_BITDEPTH_ID    ]) ;
  int    ks_n_buffers         = int(   this->audioStore[CONFIG::KS_NBLOCKS_ID     ]) ;
  int    ks_buffer_size       = int(   this->audioStore[CONFIG::KS_BLOCKSIZE_ID   ]) ;
  String ds_input_device      = String(this->audioStore[CONFIG::DS_INPUT_ID       ]) ;
  String ds_output_device     = String(this->audioStore[CONFIG::DS_OUTPUT_ID      ]) ;
  int    ds_sample_rate       = int(   this->audioStore[CONFIG::DS_SAMPLERATE_ID  ]) ;
  int    ds_bit_depth         = int(   this->audioStore[CONFIG::DS_BITDEPTH_ID    ]) ;
  int    ds_n_buffers         = int(   this->audioStore[CONFIG::DS_NBLOCKS_ID     ]) ;
  int    ds_buffer_size       = int(   this->audioStore[CONFIG::DS_BLOCKSIZE_ID   ]) ;
  int    wave_input_device_n  = int(   this->audioStore[CONFIG::WAVE_INPUT_ID     ]) ;
  int    wave_output_device_n = int(   this->audioStore[CONFIG::WAVE_OUTPUT_ID    ]) ;
  int    wave_sample_rate     = int(   this->audioStore[CONFIG::WAVE_SAMPLERATE_ID]) ;
  int    wave_bit_depth       = int(   this->audioStore[CONFIG::WAVE_BITDEPTH_ID  ]) ;
  int    wave_n_buffers       = int(   this->audioStore[CONFIG::WAVE_NBLOCKS_ID   ]) ;
  int    wave_buffer_size     = int(   this->audioStore[CONFIG::WAVE_BLOCKSIZE_ID ]) ;
#else // _WIN32
#  ifdef _MAC
  String ca_device_name       = String(this->audioStore[CONFIG::CA_DEVICE_ID      ]) ;
  int    ca_n_channels        = int(   this->audioStore[CONFIG::CA_NCHANNELS_ID   ]) ;
  int    ca_sample_rate       = int(   this->audioStore[CONFIG::CA_SAMPLERATE_ID  ]) ;
  int    ca_bit_depth         = int(   this->audioStore[CONFIG::CA_BITDEPTH_ID    ]) ;
#  else // _MAC
  int    jack_server_n        = int(   this->audioStore[CONFIG::JACK_SERVER_ID    ]) ;
  String jack_name            = String(this->audioStore[CONFIG::JACK_NAME_ID      ]) ;
  int    jack_n_inputs        = int(   this->audioStore[CONFIG::JACK_NINPUTS_ID   ]) ;
  int    jack_n_outputs       = int(   this->audioStore[CONFIG::JACK_NOUTPUTS_ID  ]) ;
  String alsa_input_device    = String(this->audioStore[CONFIG::ALSA_INPUT_ID     ]) ;
  String alsa_output_device   = String(this->audioStore[CONFIG::ALSA_OUTPUT_ID    ]) ;
  int    alsa_n_channels      = int(   this->audioStore[CONFIG::ALSA_NCHANNELS_ID ]) ;
  int    alsa_sample_rate     = int(   this->audioStore[CONFIG::ALSA_SAMPLERATE_ID]) ;
  int    alsa_bit_depth       = int(   this->audioStore[CONFIG::ALSA_BITDEPTH_ID  ]) ;
  int    alsa_n_buffers       = int(   this->audioStore[CONFIG::ALSA_NBLOCKS_ID   ]) ;
  int    alsa_buffer_size     = int(   this->audioStore[CONFIG::ALSA_BLOCKSIZE_ID ]) ;
#  endif // _MAC
#endif // _WIN32

  int    driver_n       = -1 ;
  int    source_n       = -1 ;
  int    sink_n         = -1 ;
  int    n_inputs       = 0 ;
  int    n_outputs      = 0 ;
  int    sample_rate    = 0 ;
  int    bit_depth      = 0 ;
  int    n_buffers      = 0 ;
  int    buffer_size    = 0 ;
  String jack_name_text = "" ;

  // set API-specific GUI state
#ifdef _WIN32
  switch ((audioStreamer::WinApi)audio_api_n)
  {
    case audioStreamer::WIN_AUDIO_ASIO:
    {
/* TODO: nyi GUI (issue #12)
      asio_input_e_n
      asio_output_e_n
*/
      driver_n = asio_driver_n ;
      source_n = asio_input_b_n ;
      sink_n   = asio_output_b_n ;
      this->asioButton->setToggleState(should_show_asio_cp , juce::dontSendNotification) ;

      break ;
    }
    case audioStreamer::WIN_AUDIO_KS:
    {
      source_n    = ks_input_device_n  + 1 ;
      sink_n      = ks_output_device_n + 1 ;
      sample_rate = ks_sample_rate ;
      bit_depth   = ks_bit_depth ;
      n_buffers   = ks_n_buffers ;
      buffer_size = ks_buffer_size ;

      break ;
    }
    case audioStreamer::WIN_AUDIO_DS:
    {
      source_n    = getItemIndex(this->sourceComboBox , ds_input_device ) ;
      sink_n      = getItemIndex(this->sinkComboBox   , ds_output_device) ;
      sample_rate = ds_sample_rate ;
      bit_depth   = ds_bit_depth ;
      n_buffers   = ds_n_buffers ;
      buffer_size = ds_buffer_size ;

      break ;
    }
    case audioStreamer::WIN_AUDIO_WAVE:
    {
      source_n    = wave_input_device_n  + 1 ;
      sink_n      = wave_output_device_n + 1 ;
      sample_rate = wave_sample_rate ;
      bit_depth   = wave_bit_depth ;
      n_buffers   = wave_n_buffers ;
      buffer_size = wave_buffer_size ;

      break ;
    }
    default: break ;
  }
#else // _WIN32
#  ifdef _MAC

  n_inputs    = ca_n_channels ;
  sample_rate = wave_sample_rate ;
  bit_depth   = wave_bit_depth ;

  this->nSourcesSlider->setValue(ca_n_inputs) ;

#  else // _MAC
  switch ((audioStreamer::NixApi)audio_api_n)
  {
    case audioStreamer::NIX_AUDIO_JACK:
    {
      driver_n       = jack_server_n ;
      n_inputs       = jack_n_channels ;
      n_outputs      = jack_n_channels ;
      jack_name_text = jack_name ;

      break ;
    }
    case audioStreamer::NIX_AUDIO_ALSA:
    {
      source_n    = getItemIndex(this->sourceComboBox , alsa_input_device) ;
      sink_n      = getItemIndex(this->sinkComboBox   , alsa_output_device) ;
      n_inputs    = alsa_n_channels ;
      sample_rate = alsa_sample_rate ;
      bit_depth   = alsa_bit_depth ;
      n_buffers   = alsa_n_buffers ;
      buffer_size = alsa_buffer_size ;

      break ;
    }
    default: break ;
  }
#  endif // _MAC
#endif // _WIN32

  bool is_44_khz     = sample_rate == CLIENT::SAMPLE_RATE_44100 ;
  bool is_48_khz     = sample_rate == CLIENT::SAMPLE_RATE_48000 ;
  bool is_96_khz     = sample_rate == CLIENT::SAMPLE_RATE_96000 ;
  bool is_16_bps     = bit_depth   == CLIENT::BIT_DEPTH_16 ;
  bool is_24_bps     = bit_depth   == CLIENT::BIT_DEPTH_24 ;
  bool is_32_bps     = bit_depth   == CLIENT::BIT_DEPTH_32 ;
  int  buffer_size_n = CLIENT::BUFFER_SIZES.indexOf(String(buffer_size)) ;

  this->driverComboBox->setSelectedItemIndex(driver_n) ;
  this->sourceComboBox->setSelectedItemIndex(source_n) ;
  this->sinkComboBox  ->setSelectedItemIndex(sink_n) ;
  this->bps16Button   ->setToggleState      (is_16_bps      , juce::dontSendNotification) ;
  this->bps24Button   ->setToggleState      (is_24_bps      , juce::dontSendNotification) ;
  this->bps32Button   ->setToggleState      (is_32_bps      , juce::dontSendNotification) ;
  this->kHz44Button   ->setToggleState      (is_44_khz      , juce::dontSendNotification) ;
  this->kHz48Button   ->setToggleState      (is_48_khz      , juce::dontSendNotification) ;
  this->kHz96Button   ->setToggleState      (is_96_khz      , juce::dontSendNotification) ;
  this->nBuffersSlider->setValue            (n_buffers) ;
  this->bufferComboBox->setSelectedItemIndex(buffer_size_n) ;
  this->nixConfigText ->setText             (jack_name_text , juce::dontSendNotification) ;
  this->nSourcesSlider->setValue            (n_inputs) ;
  this->nSinksSlider  ->setValue            (n_outputs) ;

  updateLatency() ; enableComponents() ;
}

void ConfigAudio::populateDevices()
{
  // re-populate API-specific device selection comboBoxes
  this->driverComboBox->clear(juce::dontSendNotification) ;
  this->sourceComboBox->clear(juce::dontSendNotification) ;
  this->sinkComboBox  ->clear(juce::dontSendNotification) ;
  this->bufferComboBox->clear(juce::dontSendNotification) ;

  int audio_api_n = int(this->audioStore[CONFIG::AUDIO_API_ID]) ;
#ifdef _WIN32
  switch ((audioStreamer::WinApi)audio_api_n)
  {
    case audioStreamer::WIN_AUDIO_ASIO: if (queryAsioDevices()) break ;
    case audioStreamer::WIN_AUDIO_KS:   if (queryKsDevices())   break ;
    case audioStreamer::WIN_AUDIO_DS:   if (queryDsDevices())   break ;
    case audioStreamer::WIN_AUDIO_WAVE: if (queryWaveDevices()) break ;
    default:                            restoreDefaults() ;     break ;
  }
#else // _WIN32
#  ifdef _MAC
  if (!queryCaDevices()) restoreDefaults() ;
#  else // _MAC
  switch ((audioStreamer::NixApi)audio_api_n)
  {
    case audioStreamer::NIX_AUDIO_JACK: if (queryJackServers()) break ;
    case audioStreamer::NIX_AUDIO_ALSA: if (queryAlsaDevices()) break ;
    default:                            restoreDefaults() ;     break ;
  }
#  endif // _MAC
#endif // _WIN32
}

void ConfigAudio::restoreDefaults()
{
  int audio_api_n = int(this->audioStore[CONFIG::AUDIO_API_ID]) ;
  int n_apis      = this->modeComboBox->getNumItems() ;

  // sanity check
  if (audio_api_n < 0 || audio_api_n >= n_apis)
  {
    audio_api_n = CONFIG::DEFAULT_AUDIO_API ;
    this->modeComboBox->setSelectedItemIndex(audio_api_n , juce::dontSendNotification) ;
    setConfig(CONFIG::AUDIO_API_ID , audio_api_n) ;
  }

  // set per API default params
#ifdef _WIN32
  switch ((audioStreamer::WinApi)audio_api_n)
  {
    case audioStreamer::WIN_AUDIO_ASIO:
    {
      setConfig(CONFIG::ASIO_DRIVER_ID  , CONFIG::DEFAULT_ASIO_DRIVERN) ;
      setConfig(CONFIG::ASIO_INPUTB_ID  , CONFIG::DEFAULT_ASIO_INPUTBN) ;
      setConfig(CONFIG::ASIO_INPUTE_ID  , CONFIG::DEFAULT_ASIO_INPUTEN) ;
      setConfig(CONFIG::ASIO_OUTPUTB_ID , CONFIG::DEFAULT_ASIO_OUTPUTBN) ;
      setConfig(CONFIG::ASIO_OUTPUTE_ID , CONFIG::DEFAULT_ASIO_OUTPUTEN) ;

      break ;
    }
    case audioStreamer::WIN_AUDIO_KS:
    {
      setConfig(CONFIG::KS_INPUT_ID      , CONFIG::DEFAULT_KS_INPUTN) ;
      setConfig(CONFIG::KS_OUTPUT_ID     , CONFIG::DEFAULT_KS_OUTPUTN) ;
      setConfig(CONFIG::KS_SAMPLERATE_ID , CONFIG::DEFAULT_KS_SAMPLERATE) ;
      setConfig(CONFIG::KS_BITDEPTH_ID   , CONFIG::DEFAULT_KS_BITDEPTH) ;
      setConfig(CONFIG::KS_NBLOCKS_ID    , CONFIG::DEFAULT_KS_NBLOCKS) ;
      setConfig(CONFIG::KS_BLOCKSIZE_ID  , CONFIG::DEFAULT_KS_BLOCKSIZE) ;

      break ;
    }
    case audioStreamer::WIN_AUDIO_DS:
    {
      setConfig(CONFIG::DS_INPUT_ID      , CONFIG::DEFAULT_DS_INPUT) ;
      setConfig(CONFIG::DS_OUTPUT_ID     , CONFIG::DEFAULT_DS_OUTPUT) ;
      setConfig(CONFIG::DS_SAMPLERATE_ID , CONFIG::DEFAULT_DS_SAMPLERATE) ;
      setConfig(CONFIG::DS_BITDEPTH_ID   , CONFIG::DEFAULT_DS_BITDEPTH) ;
      setConfig(CONFIG::DS_NBLOCKS_ID    , CONFIG::DEFAULT_DS_NBLOCKS) ;
      setConfig(CONFIG::DS_BLOCKSIZE_ID  , CONFIG::DEFAULT_DS_BLOCKSIZE) ;

      break ;
    }
    case audioStreamer::WIN_AUDIO_WAVE:
    {
      setConfig(CONFIG::WAVE_INPUT_ID      , CONFIG::DEFAULT_WAVE_INPUTN) ;
      setConfig(CONFIG::WAVE_OUTPUT_ID     , CONFIG::DEFAULT_WAVE_OUTPUTN) ;
      setConfig(CONFIG::WAVE_SAMPLERATE_ID , CONFIG::DEFAULT_WAVE_SAMPLERATE) ;
      setConfig(CONFIG::WAVE_BITDEPTH_ID   , CONFIG::DEFAULT_WAVE_BITDEPTH) ;
      setConfig(CONFIG::WAVE_NBLOCKS_ID    , CONFIG::DEFAULT_WAVE_NBLOCKS) ;
      setConfig(CONFIG::WAVE_BLOCKSIZE_ID  , CONFIG::DEFAULT_WAVE_BLOCKSIZE) ;

      break ;
    }
  }
#else // _WIN32
#  ifdef _MAC
  setConfig(CONFIG::CA_DEVICE_ID     , CONFIG::DEFAULT_CA_DEVICE) ;
  setConfig(CONFIG::CA_NINPUTS_ID    , CONFIG::DEFAULT_N_INPUTS) ;
  setConfig(CONFIG::CA_SAMPLERATE_ID , CONFIG::DEFAULT_CA_SAMPLERATE) ;
  setConfig(CONFIG::CA_BITDEPTH_ID   , CONFIG::DEFAULT_CA_BITDEPTH) ;
#  else // _MAC
  switch ((audioStreamer::NixApi)audio_api_n)
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
      setConfig(CONFIG::ALSA_INPUT_ID      , CONFIG::DEFAULT_ALSA_INPUT) ;
      setConfig(CONFIG::ALSA_OUTPUT_ID     , CONFIG::DEFAULT_ALSA_OUTPUT) ;
      setConfig(CONFIG::ALSA_NCHANNELS_ID  , CONFIG::DEFAULT_ALSA_NCHANNELS) ;
      setConfig(CONFIG::ALSA_SAMPLERATE_ID , CONFIG::DEFAULT_ALSA_SAMPLERATE) ;
      setConfig(CONFIG::ALSA_BITDEPTH_ID   , CONFIG::DEFAULT_ALSA_BITDEPTH) ;
      setConfig(CONFIG::ALSA_NBLOCKS_ID    , CONFIG::DEFAULT_ALSA_NBLOCKS) ;
      setConfig(CONFIG::ALSA_BLOCKSIZE_ID  , CONFIG::DEFAULT_ALSA_BLOCKSIZE) ;

      break ;
    }
  }
#  endif // _MAC
#endif // _WIN32
}

void ConfigAudio::disableComponents()
{
  this->defaultsButton ->setVisible(false) ; this->asioButton    ->setVisible(false) ;
  this->ioGroup        ->setEnabled(false) ; //---------------ioGroup---------------->
  this->modeLabel      ->setEnabled(false) ; this->modeComboBox  ->setEnabled(false) ;
  this->driverLabel    ->setEnabled(false) ; this->driverComboBox->setEnabled(false) ;
  this->sourceLabel    ->setEnabled(false) ; this->sourceComboBox->setEnabled(false) ;
  this->sinkLabel      ->setEnabled(false) ; this->sinkComboBox  ->setEnabled(false) ;
  this->formatGroup    ->setEnabled(false) ; //-------------formatGroup-------------->
  this->bitdepthLabel  ->setEnabled(false) ; this->bps16Button   ->setEnabled(false) ;
  this->bps24Button    ->setEnabled(false) ; this->bps32Button   ->setEnabled(false) ;
  this->samplerateLabel->setEnabled(false) ; this->kHz44Button   ->setEnabled(false) ;
  this->kHz48Button    ->setEnabled(false) ; this->kHz96Button   ->setEnabled(false) ;
  this->buffersGroup   ->setEnabled(false) ; //-------------buffersGroup------------->
  this->buffersLabel   ->setEnabled(false) ; this->nBuffersSlider->setEnabled(false) ;
  this->xLabel         ->setEnabled(false) ; this->bufferComboBox->setEnabled(false) ;
  this->bytesLabel     ->setEnabled(false) ;
  this->routingGroup   ->setEnabled(false) ; //-------------routingGroup------------->
  this->nixConfigLabel ->setEnabled(false) ; this->nixConfigText ->setEnabled(false) ;
  this->nSourcesLabel  ->setEnabled(false) ; this->nSourcesSlider->setEnabled(false) ;
  this->nSinksLabel    ->setEnabled(false) ; this->nSinksSlider  ->setEnabled(false) ;
}

void ConfigAudio::enableComponents()
{
  int audio_api_n = int(this->audioStore[CONFIG::AUDIO_API_ID]) ;
  bool is_asio , is_ks , is_ds , is_wave , is_ca , is_jack , is_alsa ;
       is_asio = is_ks = is_ds = is_wave = is_ca = is_jack = is_alsa = false ;

#ifdef _WIN32
  is_asio       = audio_api_n == audioStreamer::WIN_AUDIO_ASIO ; // ASIO
  is_ks         = audio_api_n == audioStreamer::WIN_AUDIO_KS ;   // KernelStreaming
  is_ds         = audio_api_n == audioStreamer::WIN_AUDIO_DS ;   // DirectSound
  is_wave       = audio_api_n == audioStreamer::WIN_AUDIO_WAVE ; // Wave
#else // _WIN32
#  ifdef _MAC
  is_ca         = audio_api_n == audioStreamer::MAC_AUDIO_CA ;   // CoreAudio
#  else // _MAC
  is_jack       = audio_api_n == audioStreamer::NIX_AUDIO_JACK ; // JACK
  is_alsa       = audio_api_n == audioStreamer::NIX_AUDIO_ALSA ; // ALSA
#  endif // _MAC
#endif // _WIN32

  // common
  this->defaultsButton ->setVisible(!is_asio                                           ) ;
  this->asioButton     ->setVisible( is_asio                                           ) ;
  // io group
  this->ioGroup        ->setEnabled(true                                               ) ;
  this->modeLabel      ->setEnabled(!is_ca                                             ) ;
  this->modeComboBox   ->setEnabled(!is_ca                                             ) ;
  this->driverLabel    ->setEnabled( is_asio || is_jack                                ) ;
  this->driverComboBox ->setEnabled( is_asio || is_jack                                ) ;
  this->sourceLabel    ->setEnabled(!is_asio && !is_jack                               ) ;
  this->sourceComboBox ->setEnabled(!is_asio && !is_jack                               ) ;
  this->sinkLabel      ->setEnabled(!is_asio && !is_jack                               ) ;
  this->sinkComboBox   ->setEnabled(!is_asio && !is_jack                               ) ;
  //  format group
  this->formatGroup    ->setEnabled( is_ks   || is_ds   || is_wave  || is_ca || is_alsa) ;
  this->bitdepthLabel  ->setEnabled( is_ks   || is_ds   || is_wave  || is_ca || is_alsa) ;
  this->bps16Button    ->setEnabled( is_ks   || is_ds   || is_wave  || is_ca || is_alsa) ;
  this->bps24Button    ->setEnabled( is_ks   || is_ds   || is_wave  || is_ca || is_alsa) ;
  this->bps32Button    ->setEnabled( is_ks   || is_ds   || is_wave  || is_ca || is_alsa) ;
  this->samplerateLabel->setEnabled( is_ks   || is_ds   || is_wave  || is_ca || is_alsa) ;
  this->kHz44Button    ->setEnabled( is_ks   || is_ds   || is_wave  || is_ca || is_alsa) ;
  this->kHz48Button    ->setEnabled( is_ks   || is_ds   || is_wave  || is_ca || is_alsa) ;
  this->kHz96Button    ->setEnabled( is_ks   || is_ds   || is_wave  || is_ca || is_alsa) ;
  // buffers group
  this->buffersGroup   ->setEnabled( is_ks   || is_ds   || is_wave || is_alsa          ) ;
  this->buffersLabel   ->setEnabled( is_ks   || is_ds   || is_wave || is_alsa          ) ;
  this->nBuffersSlider ->setEnabled( is_ks   || is_ds   || is_wave || is_alsa          ) ;
  this->xLabel         ->setEnabled( is_ks   || is_ds   || is_wave || is_alsa          ) ;
  this->bufferComboBox ->setEnabled( is_ks   || is_ds   || is_wave || is_alsa          ) ;
  this->bytesLabel     ->setEnabled( is_ks   || is_ds   || is_wave || is_alsa          ) ;
  // routing group
  this->routingGroup   ->setEnabled( is_jack || is_alsa || is_ca                       ) ;
  this->nixConfigLabel ->setEnabled( is_jack || is_alsa                                ) ;
  this->nixConfigText  ->setEnabled( is_jack || is_alsa                                ) ;
  this->nSourcesLabel  ->setEnabled( is_jack || is_ca   || is_alsa                     ) ;
  this->nSourcesSlider ->setEnabled( is_jack || is_ca   || is_alsa                     ) ;
  this->nSinksLabel    ->setEnabled( is_jack                                           ) ;
  this->nSinksSlider   ->setEnabled( is_jack                                           ) ;

DEBUG_TRACE_CONFIG_AUDIO_GUI_LOAD
}

#ifdef _WIN32
bool ConfigAudio::queryAsioDevices()
{
#  ifndef NO_SUPPORT_ASIO
  bool   is_asio_available = audioStreamer::IsNjasiodrvAvailable() ;
  String driver_name       = audioStreamer::GetASIODriverName() ;

#  else // NO_SUPPORT_ASIO
  bool is_asio_available = false ;
#  endif // NO_SUPPORT_ASIO

  if (is_asio_available && driver_name.isNotEmpty())
  {
    this->driverComboBox->addItem(driver_name     , 1) ;
    this->sourceComboBox->addItem("ASIO device 0" , 1) ;
    this->sinkComboBox  ->addItem("ASIO device 0" , 1) ;
  }
  else
  {
    this->driverComboBox->addItem("(ASIO unavailable)" , 1) ;
    this->sourceComboBox->addItem("(ASIO unavailable)" , 1) ;
    this->sinkComboBox  ->addItem("(ASIO unavailable)" , 1) ;
  }

  return is_asio_available ;
}

bool ConfigAudio::queryKsDevices()
{
#  ifndef NO_SUPPORT_KS
  bool is_ks_available = true ; // TODO:
#  else // NO_SUPPORT_KS
  bool is_ks_available = false ;
#  endif // NO_SUPPORT_KS

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
    this->sourceComboBox->addItem("(kernel-streaming unavailable)" , 1) ;
    this->sinkComboBox  ->addItem("(kernel-streaming unavailable)" , 1) ;
  }

  return is_ks_available ;
}

bool ConfigAudio::queryDsDevices()
{
#  ifndef NO_SUPPORT_DS
  String      device_names    = audioStreamer::GetDsNamesCSV("\n") ;
  StringArray ds_device_names = StringArray::fromLines(device_names) ;
  bool        is_ds_available = !!ds_device_names.size() ;

  if (is_ds_available)
  {
    this->sourceComboBox->addItemList(ds_device_names      , 1) ;
    this->sinkComboBox  ->addItemList(ds_device_names      , 1) ;
    this->bufferComboBox->addItemList(CLIENT::BUFFER_SIZES , 1) ;
  }
  else
  {
    this->sourceComboBox->addItem("(directsound unavaliable)" , 1) ;
    this->sinkComboBox  ->addItem("(directsound unavaliable)" , 1) ;
  }

  return is_ds_available ;
#  else // NO_SUPPORT_DS
  return  false ;
#  endif // NO_SUPPORT_DS
}

bool ConfigAudio::queryWaveDevices()
{
#  ifndef NO_SUPPORT_WAVE
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

      device_names.add(String((caps_result == MMSYSERR_NOERROR) ? capabilities.szPname :
                                                                  "(device error)"     )) ;
    }
    this->sourceComboBox->addItemList(device_names         , 1) ;
    this->sinkComboBox  ->addItemList(device_names         , 1) ;
    this->bufferComboBox->addItemList(CLIENT::BUFFER_SIZES , 1) ;
  }
  else
  {
    this->sourceComboBox->addItem("(no wave devices found)" , 1) ;
    this->sinkComboBox  ->addItem("(no wave devices found)" , 1) ;
  }

  return is_wave_available ;
#  else // NO_SUPPORT_WAVE
  return  false ;
#  endif // NO_SUPPORT_WAVE
}
#else // _WIN32
#  ifdef _MAC
bool ConfigAudio::queryCaDevices() { return true ; } // TODO: juce or ryo ?
#  else // _MAC
bool ConfigAudio::queryJackServers() // TODO: juce or ryo ?
{
  // jackd -R -S -d portaudio -l // windows returns wav, ds, and asio devices
  // jackd -R -S -d alsa -l      // nix untested
  this->driverComboBox->addItem("default jack server" , 1) ;

  return true ;
}

bool ConfigAudio::queryAlsaDevices() { return true ; } // TODO: juce or ryo ?
#  endif // _MAC
#endif // _WIN32

int ConfigAudio::getItemIndex(ComboBox* combo_box , String item_text)
{
  int item_n = combo_box->getNumItems() ;
  while (item_n-- && combo_box->getItemText(item_n).compare(item_text)) ;
  return item_n ;
}

void ConfigAudio::updateLatency()
{
  int    audio_api_n  = int(this->audioStore[CONFIG::AUDIO_API_ID]) ;
  String latency_text = "" ;
  int    n_channels , sample_rate , bit_depth , n_buffers , buffer_size ;
         n_channels = sample_rate = bit_depth = n_buffers = buffer_size = 0 ;

#ifdef _WIN32
  switch ((audioStreamer::WinApi)audio_api_n)
  {
    case audioStreamer::WIN_AUDIO_KS:
    {
      n_channels  = 2 ;
      sample_rate = int(this->audioStore[CONFIG::KS_SAMPLERATE_ID]) ;
      bit_depth   = int(this->audioStore[CONFIG::KS_BITDEPTH_ID  ]) ;
      n_buffers   = int(this->audioStore[CONFIG::KS_NBLOCKS_ID   ]) ;
      buffer_size = int(this->audioStore[CONFIG::KS_BLOCKSIZE_ID ]) ;

      break ;
    }
    case audioStreamer::WIN_AUDIO_DS:
    {
      n_channels  = 2 ;
      sample_rate = int(this->audioStore[CONFIG::DS_SAMPLERATE_ID]) ;
      bit_depth   = int(this->audioStore[CONFIG::DS_BITDEPTH_ID  ]) ;
      n_buffers   = int(this->audioStore[CONFIG::DS_NBLOCKS_ID   ]) ;
      buffer_size = int(this->audioStore[CONFIG::DS_BLOCKSIZE_ID ]) ;

      break ;
    }
    case audioStreamer::WIN_AUDIO_WAVE:
    {
      n_channels  = 2 ;
      sample_rate = int(this->audioStore[CONFIG::WAVE_SAMPLERATE_ID]) ;
      bit_depth   = int(this->audioStore[CONFIG::WAVE_BITDEPTH_ID  ]) ;
      n_buffers   = int(this->audioStore[CONFIG::WAVE_NBLOCKS_ID   ]) ;
      buffer_size = int(this->audioStore[CONFIG::WAVE_BLOCKSIZE_ID ]) ;

      break ;
    }
    default: break ;
  }
#else // _WIN32
#  ifndef _MAC
  switch ((audioStreamer::NixApi)audio_api_n)
  {
    case audioStreamer::NIX_AUDIO_JACK:
    {
      // TODO: ask jack? ask NJClient?
      break ;
    }
    case audioStreamer::NIX_AUDIO_ALSA:
    {
      n_channels  = 2 ;
      n_channels  = int(this->audioStore[CONFIG::ALSA_NCHANNELS_ID ]) ;
      sample_rate = int(this->audioStore[CONFIG::ALSA_SAMPLERATE_ID]) ;
      bit_depth   = int(this->audioStore[CONFIG::ALSA_BITDEPTH_ID  ]) ;
      n_buffers   = int(this->audioStore[CONFIG::ALSA_NBLOCKS_ID   ]) ;
      buffer_size = int(this->audioStore[CONFIG::ALSA_BLOCKSIZE_ID ]) ;

      break ;
    }
    default: break ;
  }
#  endif // _MAC
#endif // _WIN32

  if (!!n_channels)
  {
    int bytes_per_ms = (sample_rate * (bit_depth / 8) * n_channels) / 1000 ;
    int latency_ms   = (n_buffers * buffer_size) / bytes_per_ms ;
    latency_text     = (!!latency_ms) ? " (" + String(latency_ms) + "ms)" : "" ;

//DEBUG_TRACE_UPDATE_LATENCY
  }
  this->buffersGroup->setText(GUI::BUFFERS_GROUP_TEXT + latency_text) ;
}

void ConfigAudio::setConfig(Identifier a_key , var a_value)
{
  // loadParams() sets values to all GUI components
  //     even those non-applicable (and unhandled)
  //     so we must guard for null key here
  if (a_key.isValid()) this->audioStore.setProperty(a_key , a_value , nullptr) ;
}


#ifdef _WIN32_THESE_MOVED_TO_LIBNINJAM
/* ConfigAudio class public class methods */

StringPairArray ConfigAudio::getDsDevices()
{
  // see dsound.h
  StringPairArray  ds_devices ;
  LPDSENUMCALLBACK ds_enum_cb      = (LPDSENUMCALLBACK)DSEnumProc ;
  HRESULT          result          = DirectSoundEnumerate(ds_enum_cb , &ds_devices) ;
  bool             is_ds_available = !FAILED(result) ;

  if (is_ds_available) ds_devices.clear() ;

  return ds_devices ;
}

StringArray ConfigAudio::getDsDeviceNames() { return getDsDevices().getAllKeys() ; }

StringArray ConfigAudio::getDsDeviceGuids() { return getDsDevices().getAllValues() ; }


/* ConfigAudio class private class methods */

BOOL CALLBACK ConfigAudio::DSEnumProc(LPGUID  lpGUID      , LPCTSTR lpszDesc  ,
                                      LPCTSTR lpszDrvName , LPVOID  ds_devices)
{
// NOTE: DirectSound is currently hard-coded to use only default device (issue #12)

/* TODO: if we want to store guids
  LPGUID guid = nullptr ;
  if (lpGUID != nullptr) // NULL == "Primary Sound Driver" (always first)
  {
    if ((guid = (LPGUID)malloc(sizeof(GUID))) == nullptr) return TRUE ;

    memcpy(guid , lpGUID , sizeof(GUID)) ;
  }
  Array<LPGUID>.add(guid) ;
  return TRUE ;
  // free(guid) ; // then eventually for each
*/
/* TODO: if we want to marshall guids
/ * e.g. GUID: 6B29FC40-CA47-1067-B31D-00DD010662DA
typedef struct _GUID {
  DWORD Data1;    // Specifies the first 8 hexadecimal digits of the GUID.
  WORD  Data2;    // Specifies the first group of 4 hexadecimal digits.
  WORD  Data3;    // Specifies the second group of 4 hexadecimal digits.
  BYTE  Data4[8]; // Array of 8 bytes. The first 2 bytes contain the third group of 4 hexadecimal digits. The remaining 6 bytes contain the final 12 hexadecimal digits.
} GUID;
*/
#pragma comment(lib, "rpcrt4.lib")
if (lpGUID != nullptr)
{
  BYTE* guid_str ;
  UuidToString((UUID*)lpGUID , &guid_str) ;
  String guid_juce = String((LPTSTR)guid_str) ;
  RpcStringFree(&guid_str) ;

DBG("ConfigAudio::DSEnumProc() guid_juce=" + guid_juce) ;

  ((StringPairArray*)ds_devices)->set(String(lpszDesc) , guid_juce) ;
}
else { ((StringPairArray*)ds_devices)->set("Primary Sound Driver" , "") ;
DBG("ConfigAudio::DSEnumProc() guid_juce=NULL_GUID") ;}
/*
#ifdef _WIN32
struct DsDevice
{
  LPGUID  guid       ,
  LPCTSTR deviceName ,
  LPCTSTR driverName
} ;
#endif // _WIN32
  memcpy(&((DsDevice*)ds_devices)->guid       , lpGUID      , sizeof(GUID)) ;
  memcpy(&((DsDevice*)ds_devices)->deviceName , lpszDesc    , sizeof(GUID)) ;
  memcpy(&((DsDevice*)ds_devices)->driverName , lpszDrvName , sizeof(GUID)) ;
*/
/*
  ((WDL_String*)ds_devices)->Append("\"") ;
  ((WDL_String*)ds_devices)->Append(lpszDesc) ;
  ((WDL_String*)ds_devices)->Append("\" ") ;
*/
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
                 parentClasses="public Component" constructorParams="ValueTree audio_store"
                 variableInitialisers="audioStore(audio_store)" snapPixels="8"
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
