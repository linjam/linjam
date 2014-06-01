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
  this->setName("ContentComponent") ; //JUCEApplication::getInstance()->getApplicationName()
  this->setSize(GUI::CONTAINER_W , GUI::CONTAINER_H) ;

  // loginComponent
  this->addChildAndSetID((this->loginComponent = new LoginComponent()) , GUI::LOGIN_GUI_ID) ;
  this->loginComponent->toFront(true) ;

  // licenseComponent
  this->addChildAndSetID((this->licenseComponent = new LicenseComponent()) , GUI::LICENSE_GUI_ID) ;
  this->licenseComponent->toBack() ;

  // statusComponent
  this->addChildAndSetID((this->statusComponent = new StatusBarComponent()) , GUI::STATUS_GUI_ID) ;
  this->statusComponent->setAlwaysOnTop(true) ;
  this->statusComponent->setStatusL("Initializing") ;

  this->resized() ;
}

MainContentComponent::~MainContentComponent()
{
  this->loginComponent   = nullptr ;
  this->licenseComponent = nullptr ;
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

  // loginComponent
  int loginL = 0 ;
  int loginT = 0 ;
  int loginW = getWidth() ;
  int loginH = getHeight() ;
  if (this->loginComponent != nullptr)
    this->loginComponent->setBounds(loginL , loginT , loginW , loginH) ;

  // licenseComponent
  int licenseL = 0 ;
  int licenseT = 0 ;
  int licenseW = getWidth() ;
  int licenseH = getHeight() ;
  if (this->licenseComponent != nullptr)
    this->licenseComponent->setBounds(licenseL , licenseT , licenseW , licenseH) ;

  // statusComponent
  int statusL = GUI::PAD ;
  int statusT = getHeight() - GUI::PAD - GUI::STATUSBAR_H ;
  int statusW = getWidth() - (2 * GUI::PAD) ;
  int statusH = GUI::STATUSBAR_H ;
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
