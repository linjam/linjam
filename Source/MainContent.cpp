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


#include "LinJam.h"


MainContent::MainContent(DocumentWindow* main_window , TextButton* mode_btn)
{
  // MainWindow (parent)
  this->mainWindow = main_window ;
  this->modeButton = mode_btn ;
  this->modeButton->addListener(this) ;

  // MainContent (this)
  setName("MainContent") ;
  setSize(GUI::CONTENT_W , GUI::CONTENT_H) ;
}

MainContent::~MainContent()
{
  this->background = nullptr ;
  this->config     = nullptr ;
  this->lobby      = nullptr ;
  this->license    = nullptr ;
  this->chat       = nullptr ;
  this->mixer      = nullptr ;
  this->statusbar  = nullptr ;
  this->loop       = nullptr ;
}

void MainContent::paint(Graphics& g)
{
  g.fillAll (Colour (0xff202020));
  g.setFont (Font (16.0f));
  g.setColour (Colours::black);
}

void MainContent::resized()
{
  if ( this->modeButton == nullptr ||
       this->background == nullptr || this->config  == nullptr ||
       this->lobby      == nullptr || this->license == nullptr ||
       this->chat       == nullptr || this->mixer   == nullptr ||
       this->statusbar  == nullptr || this->loop    == nullptr  ) return ;

  // main window and content pane
  int window_w  = getWidth() ;
  int window_h  = getHeight() ;
  int content_w = window_w - GUI::PAD2 ;
  int content_h = window_h - GUI::STATUSBAR_H - GUI::PAD3 ;

  // mode switch
#ifdef _MAC
  int mode_btn_x = window_w - GUI::CONFIG_BTN_X - GUI::CONFIG_BTN_W ;
#else // _MAC
  int mode_btn_x = GUI::MODE_BTN_X ;
#endif // _MAC
  int mode_btn_y = GUI::MODE_BTN_Y ;
  int mode_btn_w = GUI::MODE_BTN_W ;
  int mode_btn_h = GUI::MODE_BTN_H ;

  // bg
  int bg_x = 0 ;
  int bg_y = 0 ;
  int bg_w = window_w ;
  int bg_h = window_h ;

  // config
  int config_x = GUI::PAD ;
  int config_y = GUI::PAD ;
  int config_w = content_w ;
  int config_h = content_h ;

  // lobby
  int lobby_x = GUI::PAD ;
  int lobby_y = GUI::PAD ;
  int lobby_w = content_w ;
  int lobby_h = content_h ;

  // license
  int license_x = GUI::PAD ;
  int license_y = GUI::PAD ;
  int license_w = content_w ;
  int license_h = content_h ;

  // chat
  int chat_x = GUI::PAD ;
  int chat_y = GUI::PAD ;
  int chat_w = content_w ;
  int chat_h = content_h - GUI::MIXER_H - GUI::PAD ;

  // mixer
  int mixer_x = GUI::PAD ;
  int mixer_y = window_h - GUI::STATUSBAR_H - GUI::MIXER_H - GUI::PAD2 ;
  int mixer_w = content_w ;
  int mixer_h = GUI::MIXER_H ;

  // statusbar
  int status_x = GUI::PAD ;
  int status_y = window_h - GUI::STATUSBAR_H - GUI::PAD ;
  int status_w = content_w ;
  int status_h = GUI::STATUSBAR_H ;

  // loop
  int loop_x = GUI::LOOP_X ;
  int loop_y = status_y + GUI::PAD ;
  int loop_w = content_w - GUI::PAD4 - (GUI::STATUS_W * 2) ;
  int loop_h = GUI::LOOP_H ;

  this->modeButton->setBounds(mode_btn_x , mode_btn_y , mode_btn_w  , mode_btn_h) ;
  this->background->setBounds(bg_x       , bg_y       , bg_w        , bg_h      ) ;
  this->config    ->setBounds(config_x   , config_y   , config_w    , config_h  ) ;
  this->lobby     ->setBounds(lobby_x    , lobby_y    , lobby_w     , lobby_h   ) ;
  this->license   ->setBounds(license_x  , license_y  , license_w   , license_h ) ;
  this->chat      ->setBounds(chat_x     , chat_y     , chat_w      , chat_h    ) ;
  this->mixer     ->setBounds(mixer_x    , mixer_y    , mixer_w     , mixer_h   ) ;
  this->statusbar ->setBounds(status_x   , status_y   , status_w    , status_h  ) ;
  this->loop      ->setBounds(loop_x     , loop_y     , loop_w      , loop_h    ) ;
}

void MainContent::instantiate(ValueTree gui_store       , ValueTree client_store  ,
                              ValueTree blacklist_store , ValueTree audio_store   ,
                              ValueTree login_store     , ValueTree servers_store ,
                              Value     linjam_status                             )
{
  // cherry-pick component-specific value holders
  Value agreed_value   = LinJamConfig::GetValueHolder(login_store , CONFIG::IS_AGREED_ID   ) ;
  Value agree_value    = LinJamConfig::GetValueHolder(login_store , CONFIG::SHOULD_AGREE_ID) ;
  Value fontsize_value = LinJamConfig::GetValueHolder(gui_store   , CONFIG::FONT_SIZE_ID   ) ;

  // instantiate components requiring model hooks
  this->background.reset(new Background(                                           )) ;
  this->config    .reset(new Config    (audio_store     , client_store , gui_store ,
                                        blacklist_store , linjam_status            )) ;
  this->lobby     .reset(new Lobby     (login_store     , servers_store            )) ;
  this->license   .reset(new License   (agreed_value    , agree_value              )) ;
  this->chat      .reset(new Chat      (fontsize_value                             )) ;
  this->mixer     .reset(new Mixer     (blacklist_store                            )) ;
  this->statusbar .reset(new StatusBar (                                           )) ;
  this->loop      .reset(new Loop      (                                           )) ;

  this->addChildAndSetID(this->background.get() , GUI::BACKGROUND_GUI_ID) ;
  this->addChildAndSetID(this->config    .get() , GUI::CONFIG_GUI_ID    ) ;
  this->addChildAndSetID(this->lobby     .get() , GUI::LOBBY_GUI_ID     ) ;
  this->addChildAndSetID(this->license   .get() , GUI::LICENSE_GUI_ID   ) ;
  this->addChildAndSetID(this->chat      .get() , GUI::CHAT_GUI_ID      ) ;
  this->addChildAndSetID(this->mixer     .get() , GUI::MIXER_GUI_ID     ) ;
  this->addChildAndSetID(this->statusbar .get() , GUI::STATUS_GUI_ID    ) ;
  this->addChildAndSetID(this->loop      .get() , GUI::LOOP_GUI_ID      ) ;

  this->background->toFront(true) ;
  this->config    ->toBack() ;
  this->lobby     ->toBack() ;
  this->license   ->toBack() ;
  this->chat      ->toBack() ;
  this->mixer     ->toBack() ;
  this->loop      ->toFront(false) ;

  this->statusbar->setAlwaysOnTop(true) ;
  this->loop     ->setAlwaysOnTop(true) ;

  this->statusbar->setStatusL(GUI::DISCONNECTED_TEXT) ;

  this->linjamStatus.referTo(linjam_status) ;
  this->linjamStatus.addListener(this) ;

  resized() ;
}

void MainContent::setTitle(String title_text)
{
  this->mainWindow->setName(GUI::APP_NAME + " - " + title_text) ;
}

void MainContent::buttonClicked(Button* a_button)
{
  bool is_config = this->linjamStatus == APP::LINJAM_STATUS_CONFIGPENDING ;
  bool is_jam    = this->linjamStatus == APP::NJC_STATUS_OK ;

  if      (a_button == this->modeButton && is_config) this->linjamStatus = APP::LINJAM_STATUS_READY ;
  else if (a_button == this->modeButton && is_jam   ) this->linjamStatus = APP::LINJAM_STATUS_LOGOUTPENDING ;
  else                                                this->linjamStatus = APP::LINJAM_STATUS_CONFIGPENDING ;
}

void MainContent::valueChanged(Value& a_value)
{
  if (!a_value.refersToSameSourceAs(this->linjamStatus)) return ;

  bool is_config     = this->linjamStatus >= APP::LINJAM_STATUS_AUDIOINIT &&
                       this->linjamStatus <= APP::LINJAM_STATUS_AUDIOERROR ;
  bool is_jam        = this->linjamStatus == APP::NJC_STATUS_OK ;
  bool is_lobby      = ! is_config && ! is_jam ; // TODO: sophistimocate me?


// DBG("MainContent::valueChanged() status=" + String(linjam_status) + " - updating " + ( (is_lobby) ? "lobby" : ( (is_config) ? "config" : ( (is_jam) ? "jam" : "un-handled" ) ) ) ) ;


  // set mode switch text and colors
  if (is_lobby)
  {
    // entering lobby
    this->modeButton->setColour(TextButton::buttonColourId   , Colour(0xFF404000)) ;
    this->modeButton->setColour(TextButton::buttonOnColourId , Colour(0xFF808000)) ;
    this->modeButton->setColour(TextButton::textColourOnId   , Colour(0xFFFFFF00)) ;
    this->modeButton->setColour(TextButton::textColourOffId  , Colour(0xFFFFFF00)) ;
    this->modeButton->setButtonText(GUI::MODE_BTN_LOBBY_TEXT) ;
  }
  else if (is_config)
  {
    // entering config
    this->modeButton->setColour(TextButton::buttonColourId   , Colour(0xFF004000)) ;
    this->modeButton->setColour(TextButton::buttonOnColourId , Colour(0xFF008000)) ;
    this->modeButton->setColour(TextButton::textColourOnId   , Colour(0xFF00FF00)) ;
    this->modeButton->setColour(TextButton::textColourOffId  , Colour(0xFF00FF00)) ;

    bool   is_audio_init    = this->linjamStatus == APP::LINJAM_STATUS_AUDIOINIT ;
    bool   is_audio_error   = this->linjamStatus == APP::LINJAM_STATUS_AUDIOERROR ;
    Colour button_out_color = (is_audio_init ) ? GUI::MODE_BTN_OUT_INIT_COLOR    :
                              (is_audio_error) ? GUI::MODE_BTN_OUT_ERROR_COLOR   :
                                                 GUI::MODE_BTN_OUT_NORMAL_COLOR  ;
    Colour button_in_color  = (is_audio_init ) ? GUI::MODE_BTN_IN_INIT_COLOR     :
                              (is_audio_error) ? GUI::MODE_BTN_IN_ERROR_COLOR    :
                                                 GUI::MODE_BTN_IN_NORMAL_COLOR   ;
    Colour text_out_color   = (is_audio_init ) ? GUI::MODE_BTN_TEXT_INIT_COLOR   :
                              (is_audio_error) ? GUI::MODE_BTN_TEXT_ERROR_COLOR  :
                                                 GUI::MODE_BTN_TEXT_NORMAL_COLOR ;
    Colour text_in_color    = (is_audio_init ) ? GUI::MODE_BTN_TEXT_INIT_COLOR   :
                              (is_audio_error) ? GUI::MODE_BTN_TEXT_ERROR_COLOR  :
                                                 GUI::MODE_BTN_TEXT_NORMAL_COLOR ;
    String button_text      = (is_audio_init ) ? GUI::MODE_BTN_INIT_TEXT         :
                              (is_audio_error) ? GUI::MODE_BTN_ERROR_TEXT        :
                                                 GUI::MODE_BTN_CONFIG_TEXT       ;

    this->modeButton->setColour(TextButton::buttonColourId   , button_out_color) ;
    this->modeButton->setColour(TextButton::buttonOnColourId , button_in_color ) ;
    this->modeButton->setColour(TextButton::textColourOnId   , text_in_color   ) ;
    this->modeButton->setColour(TextButton::textColourOffId  , text_out_color  ) ;
    this->modeButton->setButtonText(button_text) ;
    this->modeButton->setEnabled(!is_audio_error) ;
  }
  else if (is_jam)
  {
    // entering jam
    this->modeButton->setColour(TextButton::buttonColourId   , Colour(0xff403000)) ;
    this->modeButton->setColour(TextButton::buttonOnColourId , Colour(0xff806000)) ;
    this->modeButton->setColour(TextButton::textColourOnId   , Colour(0xffFFFF00)) ;
    this->modeButton->setColour(TextButton::textColourOffId  , Colour(0xffFFFF00)) ;
    this->modeButton->setButtonText(GUI::MODE_BTN_JAM_TEXT) ;
  }
}
