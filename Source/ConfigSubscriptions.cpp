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

#include "Constants.h"
#include "LinJam.h"
#include "Subscriptions.h"

//[/Headers]

#include "ConfigSubscriptions.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigSubscriptions::ConfigSubscriptions (ValueTree config_store)
    : configStore(config_store)
{
    addAndMakeVisible (subscribeButton = new ToggleButton ("subscribeButton"));
    subscribeButton->setExplicitFocusOrder (1);
    subscribeButton->setButtonText (TRANS("auto-receive"));
    subscribeButton->addListener (this);
    subscribeButton->setToggleState (true, dontSendNotification);
    subscribeButton->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (ignoreButton = new ToggleButton ("ignoreButton"));
    ignoreButton->setExplicitFocusOrder (2);
    ignoreButton->setButtonText (TRANS("auto-ignore"));
    ignoreButton->addListener (this);
    ignoreButton->setToggleState (true, dontSendNotification);
    ignoreButton->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (bansLabel = new Label ("bansLabel",
                                              TRANS("ignored users")));
    bansLabel->setFont (Font (15.00f, Font::plain));
    bansLabel->setJustificationType (Justification::centredTop);
    bansLabel->setEditable (false, false, false);
    bansLabel->setColour (Label::textColourId, Colours::white);
    bansLabel->setColour (TextEditor::textColourId, Colours::black);
    bansLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (subscriptionsViewport = new Viewport ("subscriptionsViewport"));
    subscriptionsViewport->setExplicitFocusOrder (3);
    subscriptionsViewport->setScrollBarsShown (true, false);
    subscriptionsViewport->setScrollBarThickness (12);
    subscriptionsViewport->setViewedComponent (new Subscriptions (config_store));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (192, 172);


    //[Constructor] You can add your own custom stuff here..

  int  auto_subscribe_mode = int(this->configStore[CONFIG::SUBSCRIBE_MODE_KEY]) ;
  bool should_sub          = auto_subscribe_mode != (int)NJClient::SUBSCRIBE_ALLOW ;
  bool should_ban          = auto_subscribe_mode == (int)NJClient::SUBSCRIBE_DENY ;

  this->subscribeButton      ->setToggleState(should_sub , dontSendNotification) ;
  this->ignoreButton         ->setToggleState(should_ban , dontSendNotification) ;
  this->subscriptionsViewport->setScrollBarThickness(GUI::CONFIG_SCROLLBAR_W) ;
  this->subscriptionsViewport->setBounds(GUI::SUBSCRIPTIONS_X , GUI::SUBSCRIPTIONS_Y ,
                                         GUI::SUBSCRIPTIONS_W , GUI::SUBSCRIPTIONS_H ) ;

    //[/Constructor]
}

ConfigSubscriptions::~ConfigSubscriptions()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    subscribeButton = nullptr;
    ignoreButton = nullptr;
    bansLabel = nullptr;
    subscriptionsViewport = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConfigSubscriptions::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0xff200000));
    g.fillRoundedRectangle (0.0f, 0.0f, 192.0f, 172.0f, 10.000f);

    g.setColour (Colour (0xff101010));
    g.fillRoundedRectangle (20.0f, 64.0f, 152.0f, 84.0f, 10.000f);

    g.setColour (Colours::white);
    g.drawRoundedRectangle (20.0f, 64.0f, 152.0f, 84.0f, 10.000f, 1.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConfigSubscriptions::resized()
{
    subscribeButton->setBounds (20, 20, 74, 16);
    ignoreButton->setBounds (98, 20, 74, 16);
    bansLabel->setBounds (20, 44, 152, 16);
    subscriptionsViewport->setBounds (24, 68, 144, 76);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigSubscriptions::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == subscribeButton)
    {
        //[UserButtonCode_subscribeButton] -- add your button handler code here..
        //[/UserButtonCode_subscribeButton]
    }
    else if (buttonThatWasClicked == ignoreButton)
    {
        //[UserButtonCode_ignoreButton] -- add your button handler code here..
        //[/UserButtonCode_ignoreButton]
    }

    //[UserbuttonClicked_Post]

  bool should_subscribe = this->subscribeButton->getToggleState() ;
  bool should_ignore    = this->ignoreButton->getToggleState() ;
  int  subscribe_mode   = (should_ignore)   ? NJClient::SUBSCRIBE_DENY :
                          (should_subscribe)? NJClient::SUBSCRIBE_ALL  :
                                              NJClient::SUBSCRIBE_NONE ;

  setConfig(CONFIG::SUBSCRIBE_MODE_KEY , var(subscribe_mode)) ;

    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void ConfigSubscriptions::setConfig(Identifier a_key , var a_value)
{
  this->configStore.setProperty(a_key , a_value , nullptr) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConfigSubscriptions" componentName=""
                 parentClasses="public Component" constructorParams="ValueTree config_store"
                 variableInitialisers="configStore(config_store)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="192" initialHeight="172">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 192 172" cornerSize="10" fill="solid: ff200000" hasStroke="0"/>
    <ROUNDRECT pos="20 64 152 84" cornerSize="10" fill="solid: ff101010" hasStroke="1"
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
         fontsize="15" bold="0" italic="0" justification="12"/>
  <VIEWPORT name="subscriptionsViewport" id="1da1a4f83d3dffa2" memberName="subscriptionsViewport"
            virtualName="" explicitFocusOrder="3" pos="24 68 144 76" vscroll="1"
            hscroll="0" scrollbarThickness="12" contentType="2" jucerFile=""
            contentClass="Subscriptions" constructorParams="config_store"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
