/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "Constants.h"
#include "MainComponent.h"
#include "Trace.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
  // mainComponent
  this->setName("ContentComponent") ;
  this->setSize(GUI::CONTAINER_W , GUI::CONTAINER_H) ;

  // loginComponent
  this->loginComponent = new LoginComponent() ;
  this->addChildAndSetID(this->loginComponent , GUI::LOGIN_GUI_ID.text) ;
  this->loginComponent->toFront(true) ;

  // chatComponent
  this->chatComponent = new ChatComponent() ;
  this->addChildAndSetID(this->chatComponent , GUI::CHAT_GUI_ID.text) ;
  this->chatComponent->toBack() ;

  // licenseComponent
  this->licenseComponent = new LicenseComponent() ;
  this->addChildAndSetID(this->licenseComponent , GUI::LICENSE_GUI_ID.text) ;
  this->licenseComponent->toBack() ;

  // statusComponent
  this->statusComponent = new StatusBarComponent() ;
  this->addChildAndSetID(this->statusComponent , GUI::STATUS_GUI_ID.text) ;
  this->statusComponent->setAlwaysOnTop(true) ;
  this->statusComponent->setStatusL("Initializing") ;

  this->resized() ;
}

MainContentComponent::~MainContentComponent()
{
  this->loginComponent   = nullptr ;
  this->licenseComponent = nullptr ;
  this->chatComponent    = nullptr ;
  this->statusComponent  = nullptr ;
}

void MainContentComponent::paint(Graphics& g)
{
/*
  uint16 BG_COLOR = 0xffeeddff ;
  GUI::BG_COLOR
*/
  g.fillAll (Colour (0xffeeddff));
  g.setFont (Font (16.0f));
  g.setColour (Colours::black);
}

void MainContentComponent::resized()
{
  // This is called when the MainContentComponent is resized.
  // If you add any child components, this is where you should
  // update their positions.

  // loginComponent , licenseComponent , chatComponent
  int contentL = 0 ;
  int contentT = 0 ;
  int contentW = getWidth() ;
  int contentH = getHeight() - GUI::PAD2 - GUI::STATUSBAR_H ;

  int statusL = GUI::PAD ;
  int statusT = getHeight() - GUI::PAD - GUI::STATUSBAR_H ;
  int statusW = getWidth() - GUI::PAD2 ;
  int statusH = GUI::STATUSBAR_H ;

  // loginComponent
  int loginL = contentL ;
  int loginT = contentT ;
  int loginW = contentW ;
  int loginH = contentH ;
  if (this->loginComponent != nullptr)
    this->loginComponent->setBounds(loginL , loginT , loginW , loginH) ;

  // licenseComponent
  int licenseL = contentL ;
  int licenseT = contentT ;
  int licenseW = contentW ;
  int licenseH = contentH ;
  if (this->licenseComponent != nullptr)
    this->licenseComponent->setBounds(licenseL , licenseT , licenseW , licenseH) ;

  // chatComponent
  int chatL = contentL ;
  int chatT = contentT ;
  int chatW = contentW ;
  int chatH = contentH ;
  if (this->chatComponent != nullptr)
    this->chatComponent->setBounds(chatL , chatT , chatW , chatH) ;

  // statusComponent
  if (this->statusComponent != nullptr)
    this->statusComponent->setBounds(statusL , statusT , statusW , statusH) ;

DEBUG_TRACE_MAIN_RESIZED
}
/*
bool MainContentComponent::prompt_license(String license_text)
{
DBG("MainContentComponent::prompt_license()") ; // license_text=\n" + license_text) ;
#if DEBUG_BYPASS_LICENSE_PROMPT
return 1 ;
#else
//this->licenseComponent->state = GUI::LICENCE_PENDING_STATE ;
//this->licenseComponent->setLabel
this->licenseComponent->toFront(true) ;
// while (this->licenseComponent->state == GUI::LICENCE_PENDING_STATE) Sleep(100) ; ;
this->licenseComponent->agreeEvent->wait() ;

return (this->licenseComponent->getIsAgreed()) ;
#endif
}
*/
