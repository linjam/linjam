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

#include "Background.h"
#include "Config.h"
#include "Lobby.h"
#include "License.h"
#include "Toolbox.h"
#include "Chat.h"
#include "Mixer.h"
#include "StatusBar.h"
#include "Loop.h"


/** MainContent is the main view container class */
class MainContent : public Component        ,
                    public Button::Listener ,
                    public Value::Listener
{
  friend class LinJamApplication ;
  friend class LinJam ;


public:

  MainContent (DocumentWindow* main_window , TextButton* mode_btn) ;
  ~MainContent() ;

  void paint  (Graphics&) ;
  void resized() ;


private:

  UPTR<Background> background ;
  UPTR<Config>     config ;
  UPTR<Lobby>      lobby ;
  UPTR<License>    license ;
  UPTR<Toolbox>    toolbox ;
  UPTR<Chat>       chat ;
  UPTR<Mixer>      mixer ;
  UPTR<StatusBar>  statusbar ;
  UPTR<Loop>       loop ;
  DocumentWindow*  mainWindow ;
  TextButton*      modeButton ;
  Value            linjamStatus ;
  Value            guiLayout ;


  // setup/teardow
  void instantiate(ValueTree gui_store       , ValueTree client_store  ,
                   ValueTree blacklist_store , ValueTree audio_store   ,
                   ValueTree login_store     , ValueTree servers_store ,
                   Value     linjam_status                             ) ;
  void setTitle   (String title_text) ;

  // event handlers
  void buttonClicked(Button* a_button)         override ;
  void valueChanged (Value& a_value)           override ;
  bool keyPressed   (const KeyPress& keypress) override ;
  void updateModeBtn() ;
  void updateLayout () ;



  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContent)
} ;
