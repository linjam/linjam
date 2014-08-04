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
    tabbedComponent->setExplicitFocusOrder (1);
    tabbedComponent->setTabBarDepth (24);
    tabbedComponent->addTab (TRANS("client"), Colour (0xff002000), new ConfigNinjam (client_store), true);
    tabbedComponent->addTab (TRANS("audio"), Colour (0xff202000), new ConfigAudio (audio_store), true);
    tabbedComponent->addTab (TRANS("subscriptions"), Colour (0xff200000), new ConfigSubscriptions (subscriptions_store), true);
    tabbedComponent->setCurrentTabIndex (0);

    addAndMakeVisible (dismissButton = new TextButton ("dismissButton"));
    dismissButton->setExplicitFocusOrder (4);
    dismissButton->setButtonText (TRANS("X"));
    dismissButton->addListener (this);
    dismissButton->setColour (TextButton::buttonColourId, Colour (0xff400000));
    dismissButton->setColour (TextButton::buttonOnColourId, Colours::maroon);
    dismissButton->setColour (TextButton::textColourOnId, Colours::red);
    dismissButton->setColour (TextButton::textColourOffId, Colours::red);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (200, 200);


    //[Constructor] You can add your own custom stuff here..

    tabbedComponent->setOutline(0) ;
    tabbedComponent->setIndent(0) ;

    //[/Constructor]
}

ConfigClient::~ConfigClient()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    tabbedComponent = nullptr;
    dismissButton = nullptr;


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
    dismissButton->setBounds (getWidth() - 15, 0, 15, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigClient::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == dismissButton)
    {
        //[UserButtonCode_dismissButton] -- add your button handler code here..

      ((CallOutBox*)getParentComponent())->dismiss() ;

        //[/UserButtonCode_dismissButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
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
                   virtualName="" explicitFocusOrder="1" pos="4 0 8M 4M" orientation="top"
                   tabBarDepth="24" initialTab="0">
    <TAB name="client" colour="ff002000" useJucerComp="0" contentClassName="ConfigNinjam"
         constructorParams="client_store" jucerComponentFile=""/>
    <TAB name="audio" colour="ff202000" useJucerComp="0" contentClassName="ConfigAudio"
         constructorParams="audio_store" jucerComponentFile=""/>
    <TAB name="subscriptions" colour="ff200000" useJucerComp="0" contentClassName="ConfigSubscriptions"
         constructorParams="subscriptions_store" jucerComponentFile=""/>
  </TABBEDCOMPONENT>
  <TEXTBUTTON name="dismissButton" id="becd368b728d32c0" memberName="dismissButton"
              virtualName="" explicitFocusOrder="4" pos="15R 0 15 16" bgColOff="ff400000"
              bgColOn="ff800000" textCol="ffff0000" textColOn="ffff0000" buttonText="X"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
