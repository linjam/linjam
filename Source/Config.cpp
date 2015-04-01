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

#include "Constants.h"
#include "ConfigAudio.h"
#include "ConfigClient.h"
#include "ConfigGui.h"
#include "ConfigBlacklist.h"

//[/Headers]

#include "Config.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Config::Config (ValueTree audio_store, ValueTree client_store, ValueTree gui_store, ValueTree blacklist_store, Value linjam_status)
    : linjamStatus(linjam_status)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (configTabs = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    configTabs->setExplicitFocusOrder (1);
    configTabs->setTabBarDepth (24);
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

  // populate config tabs
  this->configAudio     = new ConfigAudio(    audio_store     ) ;
  this->configClient    = new ConfigClient(   client_store    ) ;
  this->configGui       = new ConfigGui(      gui_store       ) ;
  this->configBlacklist = new ConfigBlacklist(blacklist_store) ;
  this->configTabs->addTab(TRANS("audio")        , GUI::AUDIO_TAB_COLOR          ,
                           this->configAudio     , false , GUI::AUDIO_TAB_IDX    ) ;
  this->configTabs->addTab(TRANS("client")       , GUI::CLIENT_TAB_COLOR         ,
                           this->configClient    , false , GUI::CLIENT_TAB_IDX   ) ;
  this->configTabs->addTab(TRANS("gui")          , GUI::GUI_TAB_COLOR            ,
                           this->configGui       , false , GUI::GUI_TAB_IDX      ) ;
  this->configTabs->addTab(TRANS("ignores")      , GUI::BLACKLIST_TAB_COLOR      ,
                           this->configBlacklist , false , GUI::BLACKLIST_TAB_IDX) ;
  this->configTabs->setCurrentTabIndex(GUI::AUDIO_TAB_IDX) ;
  this->configTabs->setOutline(0) ;
  this->configTabs->setIndent(0) ;

  this->linjamStatus.addListener(this) ;

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

      this->linjamStatus = STATUS::LINJAM_STATUS_READY ;

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
      linjam_status < STATUS::LINJAM_STATUS_AUDIOINIT   ||
      linjam_status > STATUS::LINJAM_STATUS_AUDIOERROR   ) return ;

  bool   is_audio_init    = linjam_status == STATUS::LINJAM_STATUS_AUDIOINIT ;
  bool   is_audio_error   = linjam_status == STATUS::LINJAM_STATUS_AUDIOERROR ;
  Colour button_out_color = (is_audio_init ) ? GUI::DISMISS_BTN_OUT_INIT_COLOR    :
                            (is_audio_error) ? GUI::DISMISS_BTN_OUT_ERROR_COLOR   :
                                               GUI::DISMISS_BTN_OUT_NORMAL_COLOR  ;
  Colour button_in_color  = (is_audio_init ) ? GUI::DISMISS_BTN_IN_INIT_COLOR     :
                            (is_audio_error) ? GUI::DISMISS_BTN_IN_ERROR_COLOR    :
                                               GUI::DISMISS_BTN_IN_NORMAL_COLOR   ;
  Colour text_out_color   = (is_audio_init ) ? GUI::DISMISS_BTN_TEXT_INIT_COLOR   :
                            (is_audio_error) ? GUI::DISMISS_BTN_TEXT_ERROR_COLOR  :
                                               GUI::DISMISS_BTN_TEXT_NORMAL_COLOR ;
  Colour text_in_color    = (is_audio_init ) ? GUI::DISMISS_BTN_TEXT_INIT_COLOR   :
                            (is_audio_error) ? GUI::DISMISS_BTN_TEXT_ERROR_COLOR  :
                                               GUI::DISMISS_BTN_TEXT_NORMAL_COLOR ;
  String button_text      = (is_audio_init ) ? GUI::DISMISS_BTN_INIT_TEXT         :
                            (is_audio_error) ? GUI::DISMISS_BTN_ERROR_TEXT        :
                                               GUI::DISMISS_BTN_NORMAL_TEXT       ;

  // /disable/enable dismissButton
  this->dismissButton->setColour(TextButton::buttonColourId   , button_out_color) ;
  this->dismissButton->setColour(TextButton::buttonOnColourId , button_in_color ) ;
  this->dismissButton->setColour(TextButton::textColourOnId   , text_in_color   ) ;
  this->dismissButton->setColour(TextButton::textColourOffId  , text_out_color  ) ;
  this->dismissButton->setEnabled(!is_audio_error) ;
  this->dismissButton->setButtonText(button_text) ;

  // set ConfigAudio tab state
  this->configTabs->setCurrentTabIndex(GUI::AUDIO_TAB_IDX , false) ;
  if (is_audio_init) this->configAudio->disableComponents() ;
  else               this->configAudio->loadParams() ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Config" componentName=""
                 parentClasses="public Component, public ValueListener" constructorParams="ValueTree audio_store, ValueTree client_store, ValueTree gui_store, ValueTree blacklist_store, Value linjam_status"
                 variableInitialisers="linjamStatus(linjam_status)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="622" initialHeight="442">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10" fill="solid: ff202020" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <TABBEDCOMPONENT name="configTabs" id="72016394fc1784e9" memberName="configTabs"
                   virtualName="" explicitFocusOrder="1" pos="4 0 8M 4M" orientation="top"
                   tabBarDepth="24" initialTab="-1"/>
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
