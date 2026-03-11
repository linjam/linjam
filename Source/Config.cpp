/*\
|*|  Copyright 2014,2015,2020,2026 bill-auger <bill-auger@programmer.net>
|*|
|*|  This file is part of the LinJam program.
|*|
|*|  LinJam is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  LinJam is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU General Public License for more details.
|*|
|*|  You should have received a copy of the GNU General Public License
|*|  along with LinJam.  If not, see <http://www.gnu.org/licenses/>.
\*/


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

    configTabs.reset (new juce::TabbedComponent (juce::TabbedButtonBar::TabsAtTop));
    addAndMakeVisible (configTabs.get());
    configTabs->setExplicitFocusOrder (1);
    configTabs->setTabBarDepth (24);
    configTabs->setCurrentTabIndex (-1);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (622, 442);


    //[Constructor] You can add your own custom stuff here..

  // populate config tabs
  this->configAudio    .reset(new ConfigAudio    (audio_store    )) ;
  this->configClient   .reset(new ConfigClient   (client_store   )) ;
  this->configGui      .reset(new ConfigGui      (gui_store      )) ;
  this->configBlacklist.reset(new ConfigBlacklist(blacklist_store)) ;
  this->configTabs->addTab(TRANS("Audio")              , GUI::AUDIO_TAB_COLOR          ,
                           this->configAudio    .get() , false , GUI::AUDIO_TAB_IDX    ) ;
  this->configTabs->addTab(TRANS("Client")             , GUI::CLIENT_TAB_COLOR         ,
                           this->configClient   .get() , false , GUI::CLIENT_TAB_IDX   ) ;
  this->configTabs->addTab(TRANS("Gui")                , GUI::GUI_TAB_COLOR            ,
                           this->configGui      .get() , false , GUI::GUI_TAB_IDX      ) ;
  this->configTabs->addTab(TRANS("Ignores")            , GUI::BLACKLIST_TAB_COLOR      ,
                           this->configBlacklist.get() , false , GUI::BLACKLIST_TAB_IDX) ;
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


    //[Destructor]. You can add your own custom destruction code here..

  configAudio     = nullptr ;
  configClient    = nullptr ;
  configGui       = nullptr ;
  configBlacklist = nullptr ;

    //[/Destructor]
}

//==============================================================================
void Config::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 0.0f, y = 0.0f, width = static_cast<float> (getWidth() - 0), height = static_cast<float> (getHeight() - 0);
        juce::Colour fillColour = juce::Colour (0xff202020);
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

void Config::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    configTabs->setBounds (4, 0, getWidth() - 8, getHeight() - 4);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void Config::valueChanged(Value& a_value)
{
  int linjam_status  = int(a_value.getValue()) ;
  bool is_audio_init = linjam_status == APP::LINJAM_STATUS_AUDIOINIT ;

  if (!a_value.refersToSameSourceAs(this->linjamStatus)) return ;

  // set ConfigAudio tab state
  this->configTabs->setCurrentTabIndex(GUI::AUDIO_TAB_IDX , false) ;
  if (is_audio_init) this->configAudio->disableComponents() ;
  else               this->configAudio->loadParams() ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Config" componentName=""
                 parentClasses="public Component, public Value::Listener" constructorParams="ValueTree audio_store, ValueTree client_store, ValueTree gui_store, ValueTree blacklist_store, Value linjam_status"
                 variableInitialisers="linjamStatus(linjam_status)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="622" initialHeight="442">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10.0" fill="solid: ff202020" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <TABBEDCOMPONENT name="configTabs" id="72016394fc1784e9" memberName="configTabs"
                   virtualName="" explicitFocusOrder="1" pos="4 0 8M 4M" orientation="top"
                   tabBarDepth="24" initialTab="-1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

