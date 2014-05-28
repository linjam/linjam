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

  // statusComponent
  this->addChildAndSetID((this->statusComponent = new StatusBarComponent()) , GUI::STATUS_GUI_ID) ;
  this->statusComponent->setAlwaysOnTop(true) ;
  this->statusComponent->setStatusL("Initializing") ;

  this->resized() ;
}

MainContentComponent::~MainContentComponent()
{
  this->loginComponent  = nullptr ;
  this->statusComponent = nullptr ;
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

  // statusComponent
  int statusL = GUI::PAD ;
  int statusT = getHeight() - GUI::PAD - GUI::STATUSBAR_H ;
  int statusW = getWidth() - (2 * GUI::PAD) ;
  int statusH = GUI::STATUSBAR_H ;
  if (this->statusComponent != nullptr)
    this->statusComponent->setBounds(statusL , statusT , statusW , statusH) ;

DEBUG_TRACE_MAIN_RESIZED
}
