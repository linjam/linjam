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
#include "ConfigAudio.h"
#include "ConfigClient.h"
#include "ConfigSubscriptions.h"

//[/Headers]

#include "Config.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Config::Config (ValueTree audio_store, ValueTree client_store, ValueTree subscriptions_store ,
                Value linjam_status)
{
    addAndMakeVisible (configTabs = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    configTabs->setExplicitFocusOrder (1);
    configTabs->setTabBarDepth (24);
    configTabs->addTab (TRANS("audio"), Colour (0xff002000), new ConfigAudio (audio_store), true);
    configTabs->addTab (TRANS("client"), Colour (0xff202000), new ConfigClient (client_store), true);
    configTabs->addTab (TRANS("ignores"), Colour (0xff200000), new ConfigSubscriptions (subscriptions_store), true);
    configTabs->setCurrentTabIndex (0);

    addAndMakeVisible (dismissButton = new TextButton ("dismissButton"));
    dismissButton->setExplicitFocusOrder (4);
    dismissButton->setButtonText (TRANS("done"));
    dismissButton->addListener (this);
    dismissButton->setColour (TextButton::buttonColourId, Colour (0xff004000));
    dismissButton->setColour (TextButton::buttonOnColourId, Colours::green);
    dismissButton->setColour (TextButton::textColourOnId, Colours::lime);
    dismissButton->setColour (TextButton::textColourOffId, Colours::lime);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (622, 442);


    //[Constructor] You can add your own custom stuff here..

  this->linjamStatus.referTo(linjam_status) ;
  this->configTabs->setOutline(0) ;
  this->configTabs->setIndent(0) ;

    //[/Constructor]
}

Config::~Config()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    configTabs = nullptr;
    dismissButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Config::paint (Graphics& g)
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

void Config::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    configTabs->setBounds (4, 0, getWidth() - 8, getHeight() - 4);
    dismissButton->setBounds (getWidth() - 64, 0, 64, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Config::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == dismissButton)
    {
        //[UserButtonCode_dismissButton] -- add your button handler code here..

      this->linjamStatus = LinJam::LINJAM_STATUS_READY ;

        //[/UserButtonCode_dismissButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void Config::valueChanged(Value& a_value)
{
  int linjam_status = int(a_value.getValue()) ;
  if (!a_value.refersToSameSourceAs(this->linjamStatus) ||
      linjam_status < LinJam::LINJAM_STATUS_AUDIOERROR  ||
      linjam_status > LinJam::LINJAM_STATUS_CONFIGPENDING) return ;

  bool   is_audio_error   = linjam_status == LinJam::LINJAM_STATUS_AUDIOERROR ;
  Colour button_out_color = (is_audio_error) ? Colour(0xff400000) : Colour(0xff004000) ;
  Colour button_in_color  = (is_audio_error) ? Colours::maroon    : Colours::green ;
  Colour text_out_color   = (is_audio_error) ? Colours::red       : Colours::lime ;
  Colour text_in_color    = (is_audio_error) ? Colours::red       : Colours::lime ;
  String button_text      = (is_audio_error) ? GUI::DISMISS_BTN_ERROR_TEXT :
                                               GUI::DISMISS_BTN_TEXT ;

  this->dismissButton->setColour(TextButton::buttonColourId   , button_out_color) ;
  this->dismissButton->setColour(TextButton::buttonOnColourId , button_in_color ) ;
  this->dismissButton->setColour(TextButton::textColourOnId   , text_in_color   ) ;
  this->dismissButton->setColour(TextButton::textColourOffId  , text_out_color  ) ;
  this->dismissButton->setEnabled(!is_audio_error) ;
  this->dismissButton->setButtonText(button_text) ;

  if (is_audio_error) this->configTabs->setCurrentTabIndex(0 , false) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Config" componentName=""
                 parentClasses="public Component, public ValueListener" constructorParams="ValueTree audio_store, ValueTree client_store, ValueTree subscriptions_store"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="622" initialHeight="442">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10" fill="solid: ff202020" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <TABBEDCOMPONENT name="configTabs" id="72016394fc1784e9" memberName="configTabs"
                   virtualName="" explicitFocusOrder="1" pos="4 0 8M 4M" orientation="top"
                   tabBarDepth="24" initialTab="0">
    <TAB name="audio" colour="ff002000" useJucerComp="0" contentClassName="ConfigAudio"
         constructorParams="audio_store" jucerComponentFile=""/>
    <TAB name="client" colour="ff202000" useJucerComp="0" contentClassName="ConfigClient"
         constructorParams="client_store" jucerComponentFile=""/>
    <TAB name="ignores" colour="ff200000" useJucerComp="0" contentClassName="ConfigSubscriptions"
         constructorParams="subscriptions_store" jucerComponentFile=""/>
  </TABBEDCOMPONENT>
  <TEXTBUTTON name="dismissButton" id="becd368b728d32c0" memberName="dismissButton"
              virtualName="" explicitFocusOrder="4" pos="64R 0 64 24" bgColOff="ff004000"
              bgColOn="ff008000" textCol="ff00ff00" textColOn="ff00ff00" buttonText="done"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
