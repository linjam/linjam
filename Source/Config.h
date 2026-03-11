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


#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "ConfigAudio.h"
#include "ConfigClient.h"
#include "ConfigGui.h"
#include "ConfigBlacklist.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  Config is the configuration screen
  specific configuration options are distriibuted across several tabs
                                                                    //[/Comments]
*/
class Config  : public Component,
                public Value::Listener
{
public:
    //==============================================================================
    Config (ValueTree audio_store, ValueTree client_store, ValueTree gui_store, ValueTree blacklist_store, Value linjam_status);
    ~Config() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

//   ConfigAudio*     configAudio ;
//   ConfigClient*    configClient ;
//   ConfigGui*       configGui ;
//   ConfigBlacklist* configBlacklist ;
  UPTR<ConfigAudio>     configAudio ;
  UPTR<ConfigClient>    configClient ;
  UPTR<ConfigGui>       configGui ;
  UPTR<ConfigBlacklist> configBlacklist ;


  void valueChanged(Value& a_value) ;


  Value linjamStatus ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::TabbedComponent> configTabs;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Config)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

