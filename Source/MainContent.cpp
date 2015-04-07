
#include "LinJam.h"


MainContent::MainContent(DocumentWindow* main_window , TextButton* config_button)
{
  // MainWindow (parent)
  this->mainWindow   = main_window ;
  this->configButton = config_button ;
  this->configButton->setButtonText(TRANS("?")) ;
  this->configButton->setColour(TextButton::buttonColourId   , Colour(0xff404000)) ;
  this->configButton->setColour(TextButton::buttonOnColourId , Colours::olive) ;
  this->configButton->setColour(TextButton::textColourOnId   , Colours::yellow) ;
  this->configButton->setColour(TextButton::textColourOffId  , Colours::yellow) ;
  this->configButton->addListener(this) ;

  // MainContent (this)
  setName("MainContent") ;
  setSize(GUI::CONTENT_W , GUI::CONTENT_H) ;
}

MainContent::~MainContent()
{
  this->background   = nullptr ;
  this->login        = nullptr ;
  this->license      = nullptr ;
  this->chat         = nullptr ;
  this->mixer        = nullptr ;
  this->statusbar    = nullptr ;
  this->loop         = nullptr ;
  this->config       = nullptr ;
}

void MainContent::paint(Graphics& g)
{
  g.fillAll (Colour (0xff202020));
  g.setFont (Font (16.0f));
  g.setColour (Colours::black);
}

void MainContent::resized()
{
  if (this->configButton == nullptr ||
      this->background   == nullptr || this->chat      == nullptr ||
      this->mixer        == nullptr || this->statusbar == nullptr ||
      this->loop         == nullptr || this->login     == nullptr ||
      this->license      == nullptr || this->config    == nullptr  ) return ;

  int window_w = getWidth() ;
  int window_h = getHeight() ;

  // config button
#ifdef _MAC
  int cfg_btn_x = window_w - GUI::CONFIG_BTN_X - GUI::CONFIG_BTN_W ;
#else // _MAC
  int cfg_btn_x = GUI::CONFIG_BTN_X ;
#endif // _MAC
  int cfg_btn_y = GUI::CONFIG_BTN_Y ;
  int cfg_btn_w = GUI::CONFIG_BTN_W ;
  int cfg_btn_h = GUI::CONFIG_BTN_H ;

  // content div
  int content_w = window_w - GUI::PAD2 ;
  int content_h = window_h - GUI::STATUSBAR_H - GUI::PAD3 ;

  // bg
  int bg_x = 0 ;
  int bg_y = 0 ;
  int bg_w = window_w ;
  int bg_h = window_h ;

  // login
  int login_x = GUI::PAD ;
  int login_y = GUI::PAD ;
  int login_w = content_w ;
  int login_h = content_h ;

  // license
  int license_x = GUI::PAD ;
  int license_y = GUI::PAD ;
  int license_w = content_w ;
  int license_h = content_h ;

  // mixer div
  int mixer_x = GUI::PAD ;
  int mixer_y = window_h - GUI::STATUSBAR_H - GUI::MIXER_H - GUI::PAD2 ;
  int mixer_w = content_w ;
  int mixer_h = GUI::MIXER_H ;

  // chat
  int chat_x = GUI::PAD ;
  int chat_y = GUI::PAD ;
  int chat_w = content_w ;
  int chat_h = content_h - GUI::MIXER_H - GUI::PAD ;

  // status div
  int status_x = GUI::PAD ;
  int status_y = window_h - GUI::STATUSBAR_H - GUI::PAD ;
  int status_w = content_w ;
  int status_h = GUI::STATUSBAR_H ;

  // loop
  int loop_x = GUI::LOOP_X ;
  int loop_y = status_y + GUI::PAD ;
  int loop_w = content_w - GUI::PAD4 - (GUI::STATUS_W * 2) ;
  int loop_h = GUI::LOOP_H ;

  // config
  int config_x = GUI::PAD ;
  int config_y = GUI::PAD ;
  int config_w = content_w ;
  int config_h = content_h ;

  this->configButton->setBounds(cfg_btn_x , cfg_btn_y , cfg_btn_w , cfg_btn_h) ;
  this->background  ->setBounds(bg_x      , bg_y      , bg_w      , bg_h) ;
  this->login       ->setBounds(login_x   , login_y   , login_w   , login_h) ;
  this->license     ->setBounds(license_x , license_y , license_w , license_h) ;
  this->chat        ->setBounds(chat_x    , chat_y    , chat_w    , chat_h) ;
  this->mixer       ->setBounds(mixer_x   , mixer_y   , mixer_w   , mixer_h) ;
  this->statusbar   ->setBounds(status_x  , status_y  , status_w  , status_h) ;
  this->loop        ->setBounds(loop_x    , loop_y    , loop_w    , loop_h) ;
  this->config      ->setBounds(config_x  , config_y  , config_w  , config_h) ;
}

void MainContent::instantiate(ValueTree gui_store       , ValueTree client_store ,
                              ValueTree blacklist_store , ValueTree audio_store  , 
                              ValueTree login_store     , Value     linjam_status)
                              
{
  // extract specific values for components that do not require an entire store
  Value agreed_value   = LinJamConfig::GetValueHolder(login_store , CONFIG::IS_AGREED_ID   ) ;
  Value agree_value    = LinJamConfig::GetValueHolder(login_store , CONFIG::SHOULD_AGREE_ID) ;
  Value fontsize_value = LinJamConfig::GetValueHolder(gui_store   , CONFIG::FONT_SIZE_ID   ) ;

  // instantiate components requiring model hooks
  this->background = new Background(                                           ) ;
  this->config     = new Config(    audio_store     , client_store , gui_store ,
                                    blacklist_store , linjam_status            ) ;
  this->login      = new Login(     login_store                                ) ;
  this->license    = new License(   agreed_value    , agree_value              ) ;
  this->chat       = new Chat(      fontsize_value                             ) ;
  this->mixer      = new Mixer(     blacklist_store                            ) ;
  this->statusbar  = new StatusBar(                                            ) ;
  this->loop       = new Loop(                                                 ) ;

  this->addChildAndSetID(this->background , GUI::BACKGROUND_GUI_ID) ;
  this->addChildAndSetID(this->config     , GUI::CONFIG_GUI_ID    ) ;
  this->addChildAndSetID(this->login      , GUI::LOGIN_GUI_ID     ) ;
  this->addChildAndSetID(this->license    , GUI::LICENSE_GUI_ID   ) ;
  this->addChildAndSetID(this->chat       , GUI::CHAT_GUI_ID      ) ;
  this->addChildAndSetID(this->mixer      , GUI::MIXER_GUI_ID     ) ;
  this->addChildAndSetID(this->statusbar  , GUI::STATUS_GUI_ID    ) ;
  this->addChildAndSetID(this->loop       , GUI::LOOP_GUI_ID      ) ;

  this->background->toFront(true) ;
  this->config    ->toBack() ;
  this->login     ->toBack() ;
  this->license   ->toBack() ;
  this->chat      ->toBack() ;
  this->mixer     ->toBack() ;
  this->loop      ->toFront(false) ;

  this->statusbar->setAlwaysOnTop(true) ;
  this->loop     ->setAlwaysOnTop(true) ;

  this->statusbar->setStatusL(GUI::DISCONNECTED_TEXT) ;

  this->linjamStatus.referTo(linjam_status) ;

  resized() ;
}

void MainContent::setTitle(String title_text)
{
  this->mainWindow->setName(GUI::APP_NAME + " - " + title_text) ;
}

void MainContent::buttonClicked(Button* a_button)
{
  if (a_button == this->configButton)
    this->linjamStatus = APP::LINJAM_STATUS_CONFIGPENDING ;
}
