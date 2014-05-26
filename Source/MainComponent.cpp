/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "Trace.h"

#include "Constants.h"
#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
  // mainComponent
  setName("MainContentComponent") ; //JUCEApplication::getInstance()->getApplicationName()
  setSize(GUI::CONTAINER_W , GUI::CONTAINER_H) ;

  // loginComponent
  loginComponent = new LoginComponent() ;
  addAndMakeVisible(loginComponent) ;

  // statusComponent
  statusComponent = new StatusBarComponent() ;
  addAndMakeVisible(statusComponent) ;

  resized() ;
}

MainContentComponent::~MainContentComponent()
{
  loginComponent  = nullptr ;
  statusComponent = nullptr ;
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
  if (loginComponent != nullptr)
    loginComponent->setBounds(loginL , loginT , loginW , loginH) ;

  // statusComponent
  int statusL = GUI::PAD ;
  int statusT = getHeight() - GUI::PAD - GUI::STATUSBAR_H ;
  int statusW = getWidth() - (2 * GUI::PAD) ;
  int statusH = GUI::STATUSBAR_H ;
  if (statusComponent != nullptr)
    statusComponent->setBounds(statusL , statusT , statusW , statusH) ;

DEBUG_TRACE_MAIN_RESIZED
}
