/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "Constants.h"
#include "MainContent.h"
#include "Trace.h"


//==============================================================================
MainContent::MainContent(DocumentWindow* main_window)
{
  // Main
  this->mainWindow = main_window ;
  this->appName    = JUCEApplication::getInstance()->getApplicationName() ;

  // MainContent
  this->setName("MainContent") ;
  this->setSize(GUI::CONTENT_W , GUI::CONTENT_H) ;

  // background
  this->background = new Background() ;
  this->addChildAndSetID(this->background , GUI::BACKGROUND_GUI_ID) ;
  this->background->toFront(true) ;

  // login
  this->login = new Login() ;
  this->addChildAndSetID(this->login , GUI::LOGIN_GUI_ID) ;
  this->login->toBack() ;

  // license
  this->license = new License() ;
  this->addChildAndSetID(this->license , GUI::LICENSE_GUI_ID) ;
  this->license->toBack() ;

  // chat
  this->chat = new Chat() ;
  this->addChildAndSetID(this->chat , GUI::CHAT_GUI_ID) ;
  this->chat->toBack() ;

  // mixer
  this->mixer = new Mixer() ;
  this->addChildAndSetID(this->mixer , GUI::MIXER_GUI_ID) ;
  this->mixer->toBack() ;

  // statusbar
  this->statusbar = new StatusBar() ;
  this->addChildAndSetID(this->statusbar , GUI::STATUS_GUI_ID) ;
  this->statusbar->setAlwaysOnTop(true) ;
  this->statusbar->setStatusL(GUI::DISCONNECTED_STATUS_TEXT) ;

  // loop
  this->loop = new Loop() ;
  this->addChildAndSetID(this->loop , GUI::LOOP_GUI_ID) ;
  this->loop->setAlwaysOnTop(true) ;
  this->loop->toFront(false) ;

  this->resized() ;
}

MainContent::~MainContent()
{
  this->background = nullptr ;
  this->login      = nullptr ;
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
  // This is called when the MainContent is resized.
  // If you add any child components, this is where you should
  // update their positions.

  if (this->background == nullptr ||
      this->login      == nullptr || this->license == nullptr ||
      this->chat       == nullptr || this->mixer   == nullptr ||
      this->statusbar  == nullptr || this->loop    == nullptr) return ;

  int window_w = getWidth() ;
  int window_h = getHeight() ;

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

  this->background->setBounds(bg_x      , bg_y      , bg_w      , bg_h) ;
  this->login     ->setBounds(login_x   , login_y   , login_w   , login_h) ;
  this->license   ->setBounds(license_x , license_y , license_w , license_h) ;
  this->chat      ->setBounds(chat_x    , chat_y    , chat_w    , chat_h) ;
  this->mixer     ->setBounds(mixer_x   , mixer_y   , mixer_w   , mixer_h) ;
  this->statusbar ->setBounds(status_x  , status_y  , status_w  , status_h) ;
  this->loop      ->setBounds(loop_x    , loop_y    , loop_w    , loop_h) ;
}

void MainContent::setTitle(String title_text)
{
if (1) ;

  this->mainWindow->setName(this->appName + " - " + title_text) ;
}
