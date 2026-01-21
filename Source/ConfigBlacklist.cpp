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
#include "Blacklist.h"

//[/Headers]

#include "ConfigBlacklist.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigBlacklist::ConfigBlacklist (ValueTree blacklist_store)
    : blacklistStore(blacklist_store)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    subscribeButton.reset (new juce::ToggleButton ("subscribeButton"));
    addAndMakeVisible (subscribeButton.get());
    subscribeButton->setExplicitFocusOrder (1);
    subscribeButton->setButtonText (TRANS ("auto-receive"));
    subscribeButton->addListener (this);
    subscribeButton->setToggleState (true, juce::dontSendNotification);
    subscribeButton->setColour (juce::ToggleButton::textColourId, juce::Colours::white);

    subscribeButton->setBounds (20, 20, 74, 16);

    ignoreButton.reset (new juce::ToggleButton ("ignoreButton"));
    addAndMakeVisible (ignoreButton.get());
    ignoreButton->setExplicitFocusOrder (2);
    ignoreButton->setButtonText (TRANS ("auto-ignore"));
    ignoreButton->addListener (this);
    ignoreButton->setToggleState (true, juce::dontSendNotification);
    ignoreButton->setColour (juce::ToggleButton::textColourId, juce::Colours::white);

    ignoreButton->setBounds (98, 20, 74, 16);

    bansLabel.reset (new juce::Label ("bansLabel",
                                      TRANS ("ignored users")));
    addAndMakeVisible (bansLabel.get());
    bansLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    bansLabel->setJustificationType (juce::Justification::centredTop);
    bansLabel->setEditable (false, false, false);
    bansLabel->setColour (juce::Label::textColourId, juce::Colours::white);
    bansLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    bansLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    bansLabel->setBounds (20, 44, 152, 16);

    blacklistViewport.reset (new juce::Viewport ("blacklistViewport"));
    addAndMakeVisible (blacklistViewport.get());
    blacklistViewport->setExplicitFocusOrder (3);
    blacklistViewport->setScrollBarsShown (true, false);
    blacklistViewport->setScrollBarThickness (12);
    blacklistViewport->setViewedComponent (new Blacklist (blacklist_store));

    blacklistViewport->setBounds (24, 68, 144, 76);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (614, 434);


    //[Constructor] You can add your own custom stuff here..

  int  auto_subscribe_mode = int(this->blacklistStore[CONFIG::SUBSCRIBE_MODE_KEY]) ;
  bool should_sub          = auto_subscribe_mode != (int)NJClient::SUBSCRIBE_ALLOW ;
  bool should_ban          = auto_subscribe_mode == (int)NJClient::SUBSCRIBE_DENY ;

  this->subscribeButton  ->setToggleState(should_sub , dontSendNotification) ;
  this->ignoreButton     ->setToggleState(should_ban , dontSendNotification) ;
  this->blacklistViewport->setScrollBarThickness(GUI::CONFIG_SCROLLBAR_W) ;
  this->blacklistViewport->setBounds(GUI::BLACKLIST_X , GUI::BLACKLIST_Y ,
                                     GUI::BLACKLIST_W , GUI::BLACKLIST_H ) ;

    //[/Constructor]
}

ConfigBlacklist::~ConfigBlacklist()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    subscribeButton = nullptr;
    ignoreButton = nullptr;
    bansLabel = nullptr;
    blacklistViewport = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConfigBlacklist::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 0.0f, y = 0.0f, width = 192.0f, height = 172.0f;
        juce::Colour fillColour = juce::Colour (0xff200000);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    {
        float x = 20.0f, y = 64.0f, width = 152.0f, height = 84.0f;
        juce::Colour fillColour = juce::Colour (0xff101010);
        juce::Colour strokeColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConfigBlacklist::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigBlacklist::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == subscribeButton.get())
    {
        //[UserButtonCode_subscribeButton] -- add your button handler code here..
        //[/UserButtonCode_subscribeButton]
    }
    else if (buttonThatWasClicked == ignoreButton.get())
    {
        //[UserButtonCode_ignoreButton] -- add your button handler code here..
        //[/UserButtonCode_ignoreButton]
    }

    //[UserbuttonClicked_Post]

  bool should_subscribe = this->subscribeButton->getToggleState() ;
  bool should_ignore    = this->ignoreButton   ->getToggleState() ;
  int  subscribe_mode   = (should_ignore)    ? NJClient::SUBSCRIBE_DENY :
                          (should_subscribe) ? NJClient::SUBSCRIBE_ALL  :
                                               NJClient::SUBSCRIBE_NONE ;

  setConfig(CONFIG::SUBSCRIBE_MODE_KEY , var(subscribe_mode)) ;

    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void ConfigBlacklist::setConfig(Identifier a_key , var a_value)
{
  this->blacklistStore.setProperty(a_key , a_value , nullptr) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConfigBlacklist" componentName=""
                 parentClasses="public Component" constructorParams="ValueTree blacklist_store"
                 variableInitialisers="blacklistStore(blacklist_store)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="614" initialHeight="434">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 192 172" cornerSize="10.0" fill="solid: ff200000" hasStroke="0"/>
    <ROUNDRECT pos="20 64 152 84" cornerSize="10.0" fill="solid: ff101010" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <TOGGLEBUTTON name="subscribeButton" id="a9eb5bfc0df5b172" memberName="subscribeButton"
                virtualName="" explicitFocusOrder="1" pos="20 20 74 16" txtcol="ffffffff"
                buttonText="auto-receive" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="1"/>
  <TOGGLEBUTTON name="ignoreButton" id="fdc09180d037febb" memberName="ignoreButton"
                virtualName="" explicitFocusOrder="2" pos="98 20 74 16" txtcol="ffffffff"
                buttonText="auto-ignore" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="1"/>
  <LABEL name="bansLabel" id="a67b459c94aba72e" memberName="bansLabel"
         virtualName="" explicitFocusOrder="0" pos="20 44 152 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="ignored users" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="12"/>
  <VIEWPORT name="blacklistViewport" id="1da1a4f83d3dffa2" memberName="blacklistViewport"
            virtualName="" explicitFocusOrder="3" pos="24 68 144 76" vscroll="1"
            hscroll="0" scrollbarThickness="12" contentType="2" jucerFile=""
            contentClass="Blacklist" constructorParams="blacklist_store"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

