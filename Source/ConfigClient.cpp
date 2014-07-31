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

#include "ConfigNinjam.h"
#include "ConfigAudio.h"
#include "ConfigSubscriptions.h"

//[/Headers]

#include "ConfigClient.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigClient::ConfigClient (ValueTree client_store, ValueTree audio_store, ValueTree subscriptions_store)
{
    addAndMakeVisible (tabbedComponent = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    tabbedComponent->setTabBarDepth (24);
    tabbedComponent->addTab (TRANS("client"), Colour (0xff002000), new ConfigNinjam(), true);
    tabbedComponent->addTab (TRANS("audio"), Colour (0xff202000), new ConfigAudio(), true);
    tabbedComponent->addTab (TRANS("subscriptions"), Colour (0xff200000), new ConfigSubscriptions(), true);
    tabbedComponent->setCurrentTabIndex (0);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (200, 200);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ConfigClient::~ConfigClient()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    tabbedComponent = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConfigClient::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0xff202020));
    g.fillRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), static_cast<float> (getHeight() - 0), 10.000f);

    g.setColour (Colours::white);
    g.drawRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), static_cast<float> (getHeight() - 0), 10.000f, 1.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConfigClient::resized()
{
    tabbedComponent->setBounds (4, 0, getWidth() - 8, getHeight() - 4);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConfigClient" componentName=""
                 parentClasses="public Component" constructorParams="ValueTree client_store, ValueTree audio_store, ValueTree subscriptions_store"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="200" initialHeight="200">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10" fill="solid: ff202020" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <TABBEDCOMPONENT name="new tabbed component" id="72016394fc1784e9" memberName="tabbedComponent"
                   virtualName="" explicitFocusOrder="0" pos="4 0 8M 4M" orientation="top"
                   tabBarDepth="24" initialTab="0">
    <TAB name="client" colour="ff002000" useJucerComp="0" contentClassName="ConfigNinjam"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="audio" colour="ff202000" useJucerComp="0" contentClassName="ConfigAudio"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="subscriptions" colour="ff200000" useJucerComp="0" contentClassName="ConfigSubscriptions"
         constructorParams="" jucerComponentFile=""/>
  </TABBEDCOMPONENT>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
