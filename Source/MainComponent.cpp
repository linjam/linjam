/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "Constants.h"
#include "MainComponent.h"
#include "MixerComponent.h"
#include "Trace.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
  // mainComponent
  this->setName("ContentComponent") ;
  this->setSize(GUI::CONTENT_W , GUI::CONTENT_H) ;

  // blankComponent
  this->blankComponent = new BlankComponent() ;
  this->addChildAndSetID(this->blankComponent , GUI::BLANK_GUI_ID) ;
  this->blankComponent->toFront(true) ;

  // loginComponent
  this->loginComponent = new LoginComponent() ;
  this->addChildAndSetID(this->loginComponent , GUI::LOGIN_GUI_ID) ;
  this->loginComponent->toBack() ;

  // licenseComponent
  this->licenseComponent = new LicenseComponent() ;
  this->addChildAndSetID(this->licenseComponent , GUI::LICENSE_GUI_ID) ;
  this->licenseComponent->toBack() ;

  // chatComponent
  this->chatComponent = new ChatComponent() ;
  this->addChildAndSetID(this->chatComponent , GUI::CHAT_GUI_ID) ;
  this->chatComponent->toBack() ;

  // mixerComponent
  this->mixerComponent = new MixerComponent() ;
  this->addChildAndSetID(this->mixerComponent , GUI::MIXER_GUI_ID) ;
  this->mixerComponent->toBack() ;

  // statusbarComponent
  this->statusbarComponent = new StatusBarComponent() ;
  this->addChildAndSetID(this->statusbarComponent , GUI::STATUS_GUI_ID) ;
  this->statusbarComponent->setAlwaysOnTop(true) ;
  this->statusbarComponent->setStatusL(GUI::DISCONNECTED_STATUS_TEXT) ;

  this->resized() ;
}

MainContentComponent::~MainContentComponent()
{
  this->loginComponent     = nullptr ;
  this->licenseComponent   = nullptr ;
  this->chatComponent      = nullptr ;
  this->statusbarComponent = nullptr ;
  this->mixerComponent     = nullptr ;
}

void MainContentComponent::paint(Graphics& g)
{
  g.fillAll (Colour (0xff202020));
  g.setFont (Font (16.0f));
  g.setColour (Colours::black);
}

void MainContentComponent::resized()
{
  // This is called when the MainContentComponent is resized.
  // If you add any child components, this is where you should
  // update their positions.

  int window_w = getWidth() ;
  int window_h = getHeight() ;

  // content div
  int content_w = window_w - GUI::PAD2 ;
  int content_h = window_h - GUI::STATUSBAR_H - GUI::PAD3 ;

  // mixer div
  int mixer_x = GUI::PAD ;
  int mixer_y = window_h - GUI::STATUSBAR_H - GUI::MIXER_H - GUI::PAD2 ;
  int mixer_w = content_w ;
  int mixer_h = GUI::MIXER_H ;

  // status div
  int status_x = GUI::PAD ;
  int status_y = window_h - GUI::STATUSBAR_H - GUI::PAD ;
  int status_w = content_w ;
  int status_h = GUI::STATUSBAR_H ;

  // loginComponent
  int login_x = GUI::PAD ;
  int login_y = GUI::PAD ;
  int login_w = content_w ;
  int login_h = content_h ;
  if (this->loginComponent != nullptr)
    this->loginComponent->setBounds(login_x , login_y , login_w , login_h) ;

  // licenseComponent
  int license_x = GUI::PAD ;
  int license_y = GUI::PAD ;
  int license_w = content_w ;
  int license_h = content_h ;
  if (this->licenseComponent != nullptr)
    this->licenseComponent->setBounds(license_x , license_y , license_w , license_h) ;

  // chatComponent
  int chat_x = GUI::PAD ;
  int chat_y = GUI::PAD ;
  int chat_w = content_w ;
  int chat_h = content_h - GUI::MIXER_H - GUI::PAD ;
  if (this->chatComponent != nullptr)
    this->chatComponent->setBounds(chat_x , chat_y , chat_w , chat_h) ;

  // mixerComponent
  if (this->mixerComponent != nullptr)
    this->mixerComponent->setBounds(mixer_x , mixer_y , mixer_w , mixer_h) ;

  // statusbarComponent
  if (this->statusbarComponent != nullptr)
    this->statusbarComponent->setBounds(status_x , status_y , status_w , status_h) ;
}

#ifdef DEBUG_LICENSE_MULTITHREADED // TODO: (issue #14)
bool MainContentComponent::prompt_license(String license_text)
{
DBG("MainContentComponent::prompt_license()") ; // license_text=\n" + license_text) ;
#  if DEBUG_BYPASS_LICENSE_PROMPT
return 1 ;
#  else // DEBUG_BYPASS_LICENSE_PROMPT
//this->licenseComponent->state = GUI::LICENCE_PENDING_STATE ;
//this->licenseComponent->setLabel
this->licenseComponent->toFront(true) ;
// while (this->licenseComponent->state == GUI::LICENCE_PENDING_STATE) Sleep(100) ; ;
this->licenseComponent->agreeEvent->wait() ;

return (this->licenseComponent->getIsAgreed()) ;
#  endif // DEBUG_BYPASS_LICENSE_PROMPT
}
#endif // DEBUG_LICENSE_MULTITHREADED
