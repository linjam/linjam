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

    addAndMakeVisible (sourceLabel = new Label ("sourceLabel",
                                                TRANS("in:")));
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
                                              TRANS("out:")));
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
                                                 TRANS("buffers")));
    buffersLabel->setFont (Font (15.00f, Font::plain));
    buffersLabel->setJustificationType (Justification::centredLeft);
    buffersLabel->setEditable (false, false, false);
    buffersLabel->setColour (Label::textColourId, Colours::white);
    buffersLabel->setColour (TextEditor::textColourId, Colours::black);
    buffersLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nBuffersSlider = new Slider ("nBuffersSlider"));
    nBuffersSlider->setExplicitFocusOrder (10);
    nBuffersSlider->setRange (0, 16, 0);
    nBuffersSlider->setSliderStyle (Slider::IncDecButtons);
    nBuffersSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
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

    addAndMakeVisible (latencyLabel = new Label ("latencyLabel",
                                                 TRANS("latency: 122.2ms")));
    latencyLabel->setFont (Font (15.00f, Font::plain));
    latencyLabel->setJustificationType (Justification::centredLeft);
    latencyLabel->setEditable (false, false, false);
    latencyLabel->setColour (Label::textColourId, Colours::white);
    latencyLabel->setColour (TextEditor::textColourId, Colours::black);
    latencyLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nixConfigLabel = new Label ("nixConfigLabel",
                                                   TRANS("name")));
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
                                                  TRANS("sources")));
    nSourcesLabel->setFont (Font (15.00f, Font::plain));
    nSourcesLabel->setJustificationType (Justification::centredLeft);
    nSourcesLabel->setEditable (false, false, false);
    nSourcesLabel->setColour (Label::textColourId, Colours::white);
    nSourcesLabel->setColour (TextEditor::textColourId, Colours::black);
    nSourcesLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nSourcesSlider = new Slider ("nSourcesSlider"));
    nSourcesSlider->setExplicitFocusOrder (13);
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
    nSinksSlider->setExplicitFocusOrder (14);
    nSinksSlider->setRange (0, 16, 0);
    nSinksSlider->setSliderStyle (Slider::IncDecButtons);
    nSinksSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    nSinksSlider->addListener (this);

    addAndMakeVisible (defaultsButton = new TextButton ("defaultsButton"));
    defaultsButton->setButtonText (TRANS("defaults"));
    defaultsButton->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (614, 434);


    //[Constructor] You can add your own custom stuff here..

  this->bufferComboBox->addItemList(CLIENT::BUFFER_SIZES  , 1) ;
  this->nBuffersSlider->setRange(   CLIENT::MIN_N_BUFFERS , CLIENT::MAX_N_BUFFERS , 0) ;
  this->nSourcesSlider->setRange(   CLIENT::MIN_N_SOURCES , CLIENT::MAX_N_SOURCES , 0) ;
  this->nSinksSlider  ->setRange(   CLIENT::MIN_N_SINKS   , CLIENT::MAX_N_SINKS   , 0) ;

  loadParams() ;

    //[/Constructor]
}

ConfigAudio::~ConfigAudio()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    modeLabel = nullptr;
    modeComboBox = nullptr;
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
    xLabel = nullptr;
    bufferComboBox = nullptr;
    latencyLabel = nullptr;
    nixConfigLabel = nullptr;
    nixConfigText = nullptr;
    nSourcesLabel = nullptr;
    nSourcesSlider = nullptr;
    nSinksLabel = nullptr;
    nSinksSlider = nullptr;
    defaultsButton = nullptr;


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
    modeLabel->setBounds (12, 18, 52, 18);
    modeComboBox->setBounds (68, 18, 108, 16);
    sourceLabel->setBounds (12, 38, 28, 18);
    sourceComboBox->setBounds (40, 38, 136, 16);
    sinkLabel->setBounds (12, 58, 28, 16);
    sinkComboBox->setBounds (40, 58, 136, 16);
    bps16Button->setBounds (12, 78, 48, 16);
    bps24Button->setBounds (72, 78, 48, 16);
    bps32Button->setBounds (132, 78, 48, 16);
    kHz44Button->setBounds (12, 98, 48, 16);
    kHz48Button->setBounds (72, 98, 48, 16);
    kHz96Button->setBounds (132, 98, 48, 16);
    buffersLabel->setBounds (12, 118, 40, 16);
    nBuffersSlider->setBounds (66, 118, 50, 16);
    xLabel->setBounds (116, 118, 16, 16);
    bufferComboBox->setBounds (132, 118, 44, 16);
    latencyLabel->setBounds (84, 138, 96, 16);
    nixConfigLabel->setBounds (12, 38, 40, 16);
    nixConfigText->setBounds (56, 38, 120, 16);
    nSourcesLabel->setBounds (12, 58, 50, 16);
    nSourcesSlider->setBounds (66, 58, 50, 16);
    nSinksLabel->setBounds (12, 78, 50, 16);
    nSinksSlider->setBounds (66, 78, 50, 16);
    defaultsButton->setBounds (12, 138, 40, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigAudio::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]

#if _WIN32
  int        interface_n     = int(this->configStore[CONFIG::WIN_AUDIO_IF_ID]) ;
  Identifier mode_config_key = CONFIG::WIN_AUDIO_IF_ID ;
#else // _WIN32
#  ifndef _MAC
  Identifier mode_config_key = CONFIG::NIX_AUDIO_IF_ID ;
#  endif // _MAC
#endif // _WIN32

  Identifier config_key ;
  var        value      ;

    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == modeComboBox)
    {
        //[UserComboBoxCode_modeComboBox] -- add your combo box handling code here..

      config_key = mode_config_key ;
      value      = var(this->modeComboBox->getSelectedItemIndex()) ;

        //[/UserComboBoxCode_modeComboBox]
    }
    else if (comboBoxThatHasChanged == sourceComboBox)
    {
        //[UserComboBoxCode_sourceComboBox] -- add your combo box handling code here..

      switch ((audioStreamer::Interface)interface_n)
      {
        case audioStreamer::WIN_AUDIO_ASIO: config_key = CONFIG::ASIO_INPUT0_ID ; break ;
        case audioStreamer::WIN_AUDIO_KS:   config_key = CONFIG::KS_INPUT_ID ;    break ;
        case audioStreamer::WIN_AUDIO_DS:   config_key = CONFIG::DS_INPUT0_ID ;   break ;
        case audioStreamer::WIN_AUDIO_WAVE: config_key = CONFIG::WAVE_INPUT_ID ;  break ;
        default:                                                                  break ;
      }
      value = var(this->sourceComboBox->getSelectedItemIndex() - 1) ;

        //[/UserComboBoxCode_sourceComboBox]
    }
    else if (comboBoxThatHasChanged == sinkComboBox)
    {
        //[UserComboBoxCode_sinkComboBox] -- add your combo box handling code here..

      switch ((audioStreamer::Interface)interface_n)
      {
        case audioStreamer::WIN_AUDIO_ASIO: config_key = CONFIG::ASIO_OUTPUT0_ID ; break ;
        case audioStreamer::WIN_AUDIO_KS:   config_key = CONFIG::KS_OUTPUT_ID ;    break ;
        case audioStreamer::WIN_AUDIO_DS:   config_key = CONFIG::DS_OUTPUT0_ID ;   break ;
        case audioStreamer::WIN_AUDIO_WAVE: config_key = CONFIG::WAVE_OUTPUT_ID ;  break ;
        default:                                                                   break ;
      }
      value = var(this->sinkComboBox->getSelectedItemIndex() - 1) ;

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
      value = var(CLIENT::BUFFER_SIZES[this->bufferComboBox->getSelectedItemIndex()]) ;

        //[/UserComboBoxCode_bufferComboBox]
    }

    //[UsercomboBoxChanged_Post]

  setConfig(config_key , value) ;

  if (comboBoxThatHasChanged == this->modeComboBox) loadParams() ;

    //[/UsercomboBoxChanged_Post]
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

    if (buttonThatWasClicked == bps16Button)
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
    else if (buttonThatWasClicked == defaultsButton)
    {
        //[UserButtonCode_defaultsButton] -- add your button handler code here..

      restoreDefaults() ; loadParams() ;

        //[/UserButtonCode_defaultsButton]
    }

    //[UserbuttonClicked_Post]

  setConfig(config_key , value) ;

    //[/UserbuttonClicked_Post]
}

void ConfigAudio::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]

  Identifier config_key ;
  var        value      = var(sliderThatWasMoved->getValue()) ;

    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == nBuffersSlider)
    {
        //[UserSliderCode_nBuffersSlider] -- add your slider handling code here..

#if _WIN32
      int interface_n     = int(this->configStore[CONFIG::WIN_AUDIO_IF_ID]) ;

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
  int    jack_n_inputs     = int(this->configStore[CONFIG::JACK_NINPUTS_ID]) ;
  int    jack_n_outputs    = int(this->configStore[CONFIG::JACK_NOUTPUTS_ID]) ;
  String jack_name         =     this->configStore[CONFIG::JACK_NAME_ID].toString() ;
  String alsa_config       =     this->configStore[CONFIG::ALSA_CONFIG_ID].toString() ;

  // set GUI state
  this->defaultsButton->setButtonText(GUI::DEFAULTS_BTN_TEXT) ;
#ifdef _WIN32
  this->modeComboBox->clear(juce::dontSendNotification) ;
  this->modeComboBox->addItemList(CLIENT::WIN_AUDIO_IFS , 1) ;
  this->modeComboBox->setSelectedItemIndex(win_interface_n , juce::dontSendNotification) ;
  switch ((audioStreamer::Interface)win_interface_n)
  {
    case audioStreamer::WIN_AUDIO_ASIO:
    {
/* TODO: no GUI
      asio_driver
      asio_input1
      asio_output1
*/
      queryAsioDevices() ;

      this->sourceComboBox->setSelectedItemIndex(asio_input0) ;
      this->sinkComboBox  ->setSelectedItemIndex(asio_output0) ;
      this->defaultsButton->setButtonText(GUI::ASIO_CONFIG_BTN_TEXT) ;

      break ;
    }
    case audioStreamer::WIN_AUDIO_KS:
    {
      queryKernelstreamingDevices() ;

      bool is_16_bps         = ks_bit_depth   == CLIENT::BIT_DEPTH_16 ;
      bool is_24_bps         = ks_bit_depth   == CLIENT::BIT_DEPTH_24 ;
      bool is_32_bps         = ks_bit_depth   == CLIENT::BIT_DEPTH_32 ;
      bool is_44_khz         = ks_sample_rate == CLIENT::SAMPLE_RATE_44100 ;
      bool is_48_khz         = ks_sample_rate == CLIENT::SAMPLE_RATE_48000 ;
      bool is_96_khz         = ks_sample_rate == CLIENT::SAMPLE_RATE_96000 ;
      int  buffer_size_index = CLIENT::BUFFER_SIZES.indexOf(String(ks_buffer_size)) ;

      this->sourceComboBox->setSelectedItemIndex(ks_input) ;
      this->sinkComboBox  ->setSelectedItemIndex(ks_output) ;
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
      queryDirectsoundDevices() ;

      bool is_16_bps         = ds_bit_depth   == CLIENT::BIT_DEPTH_16 ;
      bool is_24_bps         = ds_bit_depth   == CLIENT::BIT_DEPTH_24 ;
      bool is_32_bps         = ds_bit_depth   == CLIENT::BIT_DEPTH_32 ;
      bool is_44_khz         = ds_sample_rate == CLIENT::SAMPLE_RATE_44100 ;
      bool is_48_khz         = ds_sample_rate == CLIENT::SAMPLE_RATE_48000 ;
      bool is_96_khz         = ds_sample_rate == CLIENT::SAMPLE_RATE_96000 ;
      int  buffer_size_index = CLIENT::BUFFER_SIZES.indexOf(String(ds_buffer_size)) ;

      this->sourceComboBox->setSelectedItemIndex(ds_input0) ;
      this->sinkComboBox  ->setSelectedItemIndex(ds_output0) ;
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
      queryWaveDevices() ;

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
  queryCoreaudioDevices() ; // TODO: device selection nyi

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
  this->modeComboBox->clear(juce::dontSendNotification) ;
  this->modeComboBox->addItemList(CONFIG::NIX_AUDIO_IFS , 1) ;
  this->modeComboBox->setSelectedItemIndex(nix_interface_n , juce::dontSendNotification) ;
  switch ((audioStreamer::Interface)nix_interface_n)
  {
    case audioStreamer::NIX_AUDIO_JACK:
    {
      queryJackServers() ;

      this->nixConfigLabel->setText(CONFIG::JACK_NAME_LABEL_TEXT) ;
      this->nixConfigText ->setText(jack_name) ;
      this->nSourcesSlider->setValue(jack_n_inputs) ;
      this->nSinksSlider  ->setValue(jack_n_outputs) ;

      break ;
    }
    case audioStreamer::NIX_AUDIO_ALSA:
    {
      queryAlsaDevices() ;

      this->nixConfigLabel->setText(CONFIG::ALSA_CONFIG_LABEL_TEXT) ;
      this->nixConfigText ->setText(alsa_config) ;

      break ;
    }
    default: break ;
  }
#  endif // _MAC
#endif // _WIN32

  // show/hide components
  bool is_win ; bool is_mac ; bool is_nix ;
#if _WIN32
  is_win = true  ; is_mac = false ; is_nix = false ;
#else // _WIN32
#  ifdef _MAC
  is_win = false ; is_mac = true  ; is_nix = false ;
#  else // _MAC
  is_win = false ; is_mac = false ; is_nix = true ;
#  endif // _MAC
#endif // _WIN32
  audioStreamer::Interface win_if_n = (audioStreamer::Interface)win_interface_n ;
  audioStreamer::Interface nix_if_n = (audioStreamer::Interface)nix_interface_n ;
  bool is_asio                      = is_win && win_if_n == audioStreamer::WIN_AUDIO_ASIO ;
  bool is_ks                        = is_win && win_if_n == audioStreamer::WIN_AUDIO_KS ;
  bool is_ds                        = is_win && win_if_n == audioStreamer::WIN_AUDIO_DS ;
  bool is_wave                      = is_win && win_if_n == audioStreamer::WIN_AUDIO_WAVE ;
  bool is_jack                      = is_nix && nix_if_n == audioStreamer::NIX_AUDIO_JACK ;
  bool is_alsa                      = is_nix && nix_if_n == audioStreamer::NIX_AUDIO_ALSA ;

  this->modeLabel     ->setVisible(!is_mac                                  ) ;
  this->modeComboBox  ->setVisible(!is_mac                                  ) ;
  this->sourceLabel   ->setVisible(is_ks   || is_ds   || is_wave  || is_asio) ;
  this->sourceComboBox->setVisible(is_ks   || is_ds   || is_wave  || is_asio) ;
  this->sinkLabel     ->setVisible(is_ks   || is_ds   || is_wave  || is_asio) ;
  this->sinkComboBox  ->setVisible(is_ks   || is_ds   || is_wave  || is_asio) ;
  this->buffersLabel  ->setVisible(is_ks   || is_ds   || is_wave            ) ;
  this->bufferComboBox->setVisible(is_ks   || is_ds   || is_wave            ) ;
  this->bps16Button   ->setVisible(is_ks   || is_ds   || is_wave  || is_mac ) ;
  this->bps24Button   ->setVisible(is_ks   || is_ds   || is_wave  || is_mac ) ;
  this->bps32Button   ->setVisible(is_ks   || is_ds   || is_wave  || is_mac ) ;
  this->kHz44Button   ->setVisible(is_ks   || is_ds   || is_wave  || is_mac ) ;
  this->kHz48Button   ->setVisible(is_ks   || is_ds   || is_wave  || is_mac ) ;
  this->kHz96Button   ->setVisible(is_ks   || is_ds   || is_wave  || is_mac ) ;
  this->nBuffersSlider->setVisible(is_ks   || is_ds   || is_wave            ) ;
  this->nSourcesLabel ->setVisible(is_jack || is_mac                        ) ;
  this->nSourcesSlider->setVisible(is_jack || is_mac                        ) ;
  this->nSinksLabel   ->setVisible(is_jack                                  ) ;
  this->nSinksSlider  ->setVisible(is_jack                                  ) ;
  this->nixConfigLabel->setVisible(is_jack || is_alsa                       ) ;
  this->nixConfigText ->setVisible(is_jack || is_alsa                       ) ;

DEBUG_TRACE_AUDIO_CONFIG_LOAD
}
/*
void ConfigAudio::queryDevices(String device_type_name)
{
  // NOTE: on windows juce handles only asio , directsound , and WASAPI
  //       so we must implement device enumeration for kernel streaming and wave
  //       including the juce audio modules allows this method to enumerate
  //       devices using asio , directsound , coreaudio and alsa
  //       but this is currently our only use for including the juce audio modules
  //       and it is not yet clear whether device indices will be consistent
  //       with the ones NJClient detects so it may be better to just ryo here

  // CLIENT:: namespace constants (these are the types supported by juce)
  static const String      ASIO_DEVICE_TYPE       = "ASIO" ;
  static const String      DS_DEVICE_TYPE         = "DirectSound" ;
  static const String      WASAPI_DEVICE_TYPE     = "WASAPI" ;
  static const String      CA_DEVICE_TYPE         = "CoreAudio" ;
  static const String      JACK_DEVICE_TYPE       = "JACK" ;
  static const String      ALSA_DEVICE_TYPE       = "ALSA" ;
  static const String      ROID_DEVICE_TYPE       = "Android" ;
  static const String      SLES_DEVICE_TYPE       = "OpenSLES" ;
  static const String      IOS_DEVICE_TYPE        = "iOSAudio" ;

  this->sourceComboBox->clear(juce::dontSendNotification) ;
  this->sinkComboBox  ->clear(juce::dontSendNotification) ;
  this->sourceComboBox->addItem("no directsound devices found" , 1) ;
  this->sinkComboBox  ->addItem("no directsound devices found" , 1) ;

  AudioDeviceManager*                  dev_mgr      = new AudioDeviceManager() ;
  const OwnedArray<AudioIODeviceType>& device_types = dev_mgr->getAvailableDeviceTypes() ;

  for (int device_type_n = 0 ; device_type_n < device_types.size() ; ++device_type_n)
  {
    AudioIODeviceType* device_type = device_types[device_type_n] ;
DBG("device_type[" + String(device_type_n) + "]='" + device_type->getTypeName() + "'") ;
    if (device_type->getTypeName().compare(device_type_name)) continue ;

    device_type->scanForDevices() ;
    StringArray device_names = device_type->getDeviceNames() ;

    this->sourceComboBox->clear(juce::dontSendNotification) ;
    this->sinkComboBox  ->clear(juce::dontSendNotification) ;
    for (int device_name_n = 0 ; device_name_n < device_names.size() ; ++device_name_n)
    {
      String device_name = device_names[device_name_n] ;
DBG("adding device[" + String(device_name_n) + "]='" + device_name + "'") ;

      this->sourceComboBox->addItem(device_name , device_name_n + 1) ;
      this->sinkComboBox  ->addItem(device_name , device_name_n + 1) ;
    }
  }
  delete dev_mgr ;
}
*/
void ConfigAudio::queryAsioDevices()
{
  // NOTE: see njasiodrv_if.h
  bool is_asio_available = njasiodrv_avail() ;

  this->sourceComboBox->clear(juce::dontSendNotification) ;
  this->sinkComboBox  ->clear(juce::dontSendNotification) ;
  if (is_asio_available)
  {
    this->sourceComboBox->addItem("default device" , 1) ;
    this->sinkComboBox  ->addItem("default device" , 1) ;
  }
  else
  {
    this->sourceComboBox->addItem("asio driver not found" , 1) ;
    this->sinkComboBox  ->addItem("asio driver not found" , 1) ;
  }
}

void ConfigAudio::queryKernelstreamingDevices()
{
  // NOTE: see njasiodrv_if.h
  bool is_ks_available = true ; // TODO:

  this->sourceComboBox->clear(juce::dontSendNotification) ;
  this->sinkComboBox  ->clear(juce::dontSendNotification) ;
  if (is_ks_available)
  {
    this->sourceComboBox->addItem("default device" , 1) ;
    this->sinkComboBox  ->addItem("default device" , 1) ;
  }
  else
  {
    this->sourceComboBox->addItem("kernel streaming unavailable" , 1) ;
    this->sinkComboBox  ->addItem("kernel streaming unavailable" , 1) ;
  }
}

void ConfigAudio::queryDirectsoundDevices() {} // TODO: juce or ryo ?

void ConfigAudio::queryWaveDevices()
{
  // NOTE: see MMsystem.h
  WAVEOUTCAPS capabilities ;
  UINT        caps_size    = sizeof(capabilities) ;
  int         n_devices    = (int)waveOutGetNumDevs() ;

  this->sourceComboBox->clear(juce::dontSendNotification) ;
  this->sinkComboBox  ->clear(juce::dontSendNotification) ;
  for (int device_n = -1 ; device_n < n_devices ; ++device_n)
  {
    if (waveOutGetDevCaps(device_n , &capabilities , caps_size) == MMSYSERR_NOERROR)
    {
      this->sourceComboBox->addItem(String(capabilities.szPname) , device_n + 2) ;
      this->sinkComboBox  ->addItem(String(capabilities.szPname) , device_n + 2) ;
    }
    else
    {
      this->sourceComboBox->addItem("no wave devices found" , device_n + 2) ;
      this->sinkComboBox  ->addItem("no wave devices found" , device_n + 2) ;
    }
  }
}

void ConfigAudio::queryCoreaudioDevices() {} // TODO: juce or ryo ?

void ConfigAudio::queryJackServers() {} // TODO: juce or ryo ?

void ConfigAudio::queryAlsaDevices() {} // TODO: juce or ryo ?

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
      setConfig(CONFIG::ASIO_INPUT0_ID  , CONFIG::DEFAULT_ASIO_DRIVER) ;
      setConfig(CONFIG::ASIO_INPUT1_ID  , CONFIG::DEFAULT_ASIO_DRIVER) ;
      setConfig(CONFIG::ASIO_OUTPUT0_ID , CONFIG::DEFAULT_ASIO_DRIVER) ;
      setConfig(CONFIG::ASIO_OUTPUT1_ID , CONFIG::DEFAULT_ASIO_DRIVER) ;

      break ;
    }
    case audioStreamer::WIN_AUDIO_KS:
    {
      setConfig(CONFIG::KS_INPUT_ID      , CONFIG::DEFAULT_KS_INPUT) ;
      setConfig(CONFIG::KS_OUTPUT_ID     , CONFIG::DEFAULT_KS_OUTPUT) ;
      setConfig(CONFIG::KS_SAMPLERATE_ID , CONFIG::DEFAULT_KS_SAMPLERATE) ;
      setConfig(CONFIG::KS_BITDEPTH_ID   , CONFIG::DEFAULT_BITDEPTH) ;
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
      setConfig(CONFIG::DS_BITDEPTH_ID   , CONFIG::DEFAULT_BITDEPTH) ;
      setConfig(CONFIG::DS_BLOCKSIZE_ID  , CONFIG::DEFAULT_DS_BLOCKSIZE) ;
      setConfig(CONFIG::DS_NBLOCKS_ID    , CONFIG::DEFAULT_DS_N_BLOCKS) ;

      break ;
    }
    case audioStreamer::WIN_AUDIO_WAVE:
    {
      setConfig(CONFIG::WAVE_INPUT_ID      , CONFIG::DEFAULT_WAVE_INPUT) ;
      setConfig(CONFIG::WAVE_OUTPUT_ID     , CONFIG::DEFAULT_WAVE_OUTPUT) ;
      setConfig(CONFIG::WAVE_SAMPLERATE_ID , CONFIG::DEFAULT_WAVE_SAMPLERATE) ;
      setConfig(CONFIG::WAVE_BITDEPTH_ID   , CONFIG::DEFAULT_BITDEPTH) ;
      setConfig(CONFIG::WAVE_BLOCKSIZE_ID  , CONFIG::DEFAULT_WAVE_BLOCKSIZE) ;
      setConfig(CONFIG::WAVE_NBLOCKS_ID    , CONFIG::DEFAULT_WAVE_N_BLOCKS) ;

      break ;
    }
  }
#else // _WIN32
#  ifdef _MAC
  setConfig(CONFIG::MAC_DEVICE_ID     , CONFIG::DEFAULT_MAC_DEVICE) ;
  setConfig(CONFIG::MAC_NINPUTS_ID    , CONFIG::DEFAULT_N_INPUTS) ;
  setConfig(CONFIG::MAC_SAMPLERATE_ID , CONFIG::DEFAULT_SAMPLERATE) ;
  setConfig(CONFIG::MAC_BITDEPTH_ID   , CONFIG::DEFAULT_BITDEPTH) ;
#  else // _MAC
  switch ((audioStreamer::Interface)nix_interface_n)
  {
    case audioStreamer::NIX_AUDIO_JACK:
    {
      setConfig(CONFIG::JACK_NINPUTS_ID  , CONFIG::DEFAULT_N_INPUTS) ;
      setConfig(CONFIG::JACK_NOUTPUTS_ID , CONFIG::DEFAULT_N_OUTPUTS) ;
      setConfig(CONFIG::JACK_NAME_ID     , CONFIG::DEFAULT_JACK_NAME) ;

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
  <LABEL name="modeLabel" id="582ccc898eac60c0" memberName="modeLabel"
         virtualName="" explicitFocusOrder="0" pos="12 18 52 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="interface:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="modeComboBox" id="d9fdbc02138c7335" memberName="modeComboBox"
            virtualName="" explicitFocusOrder="1" pos="68 18 108 16" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="sourceLabel" id="28e9c840504ea936" memberName="sourceLabel"
         virtualName="" explicitFocusOrder="0" pos="12 38 28 18" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="in:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="sourceComboBox" id="195d38c0dfa0b780" memberName="sourceComboBox"
            virtualName="" explicitFocusOrder="2" pos="40 38 136 16" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="sinkLabel" id="a67b459c94aba72e" memberName="sinkLabel"
         virtualName="" explicitFocusOrder="0" pos="12 58 28 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="out:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="sinkComboBox" id="3b81e2ff4dec7469" memberName="sinkComboBox"
            virtualName="" explicitFocusOrder="3" pos="40 58 136 16" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="bps16Button" id="ccb740c03ababc9f" memberName="bps16Button"
                virtualName="" explicitFocusOrder="4" pos="12 78 48 16" txtcol="ffffffff"
                buttonText="16bit" connectedEdges="0" needsCallback="1" radioGroupId="1"
                state="1"/>
  <TOGGLEBUTTON name="bps24Button" id="2bfc206fbb162f7f" memberName="bps24Button"
                virtualName="" explicitFocusOrder="5" pos="72 78 48 16" txtcol="ffffffff"
                buttonText="24bit" connectedEdges="0" needsCallback="1" radioGroupId="1"
                state="0"/>
  <TOGGLEBUTTON name="bps32Button" id="1cc075dc412ce404" memberName="bps32Button"
                virtualName="" explicitFocusOrder="6" pos="132 78 48 16" txtcol="ffffffff"
                buttonText="32bit" connectedEdges="0" needsCallback="1" radioGroupId="1"
                state="0"/>
  <TOGGLEBUTTON name="kHz44Button" id="56ab804241495c7b" memberName="kHz44Button"
                virtualName="" explicitFocusOrder="7" pos="12 98 48 16" txtcol="ffffffff"
                buttonText="44.1kHz" connectedEdges="0" needsCallback="1" radioGroupId="2"
                state="1"/>
  <TOGGLEBUTTON name="kHz48Button" id="415b27279e48004f" memberName="kHz48Button"
                virtualName="" explicitFocusOrder="8" pos="72 98 48 16" txtcol="ffffffff"
                buttonText="48kHz" connectedEdges="0" needsCallback="1" radioGroupId="2"
                state="0"/>
  <TOGGLEBUTTON name="kHz96Button" id="4241809c486a0995" memberName="kHz96Button"
                virtualName="" explicitFocusOrder="9" pos="132 98 48 16" txtcol="ffffffff"
                buttonText="96kHz" connectedEdges="0" needsCallback="1" radioGroupId="2"
                state="0"/>
  <LABEL name="buffersLabel" id="78ac240fcc5eed16" memberName="buffersLabel"
         virtualName="" explicitFocusOrder="0" pos="12 118 40 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="buffers" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="nBuffersSlider" id="76a832d1fac666e" memberName="nBuffersSlider"
          virtualName="" explicitFocusOrder="10" pos="66 118 50 16" min="0"
          max="16" int="0" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="xLabel" id="5a9596c9eb8db178" memberName="xLabel" virtualName=""
         explicitFocusOrder="0" pos="116 118 16 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="x" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="bufferComboBox" id="bef2196516ab5821" memberName="bufferComboBox"
            virtualName="" explicitFocusOrder="11" pos="132 118 44 16" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="latencyLabel" id="f93456e3175d33d6" memberName="latencyLabel"
         virtualName="" explicitFocusOrder="0" pos="84 138 96 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="latency: 122.2ms"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="nixConfigLabel" id="78568b552c534b6d" memberName="nixConfigLabel"
         virtualName="" explicitFocusOrder="0" pos="12 38 40 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="name" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="nixConfigText" id="fdccbcd88a94d4bb" memberName="nixConfigText"
              virtualName="" explicitFocusOrder="12" pos="56 38 120 16" textcol="ff808080"
              bkgcol="ff000000" initialText="" multiline="0" retKeyStartsLine="0"
              readonly="0" scrollbars="1" caret="1" popupmenu="0"/>
  <LABEL name="nSourcesLabel" id="fa0df2e2a11e57d8" memberName="nSourcesLabel"
         virtualName="" explicitFocusOrder="0" pos="12 58 50 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="sources" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="nSourcesSlider" id="3a13d77beb71d910" memberName="nSourcesSlider"
          virtualName="" explicitFocusOrder="13" pos="66 58 50 16" min="0"
          max="16" int="0" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="nSinksLabel" id="2da0a2441a20f3b0" memberName="nSinksLabel"
         virtualName="" explicitFocusOrder="0" pos="12 78 50 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="sinks" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="nSinksSlider" id="182ff4a5ae799417" memberName="nSinksSlider"
          virtualName="" explicitFocusOrder="14" pos="66 78 50 16" min="0"
          max="16" int="0" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="defaultsButton" id="f03cc2695d9642e1" memberName="defaultsButton"
              virtualName="" explicitFocusOrder="0" pos="12 138 40 16" buttonText="defaults"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
