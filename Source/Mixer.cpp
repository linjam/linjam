/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...

#include "Constants.h"
#include "Trace.h"
#include "LinJam.h"

//[/Headers]

#include "Mixer.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Mixer::Mixer ()
{
    setName ("Mixer");

    //[UserPreSize]

  this->masterChannels         = addChannels(GUI::MASTER_MIXERGROUP_GUI_ID) ;
  this->localChannels          = addChannels(GUI::LOCAL_MIXERGROUP_GUI_ID) ;
  this->prevLocalScrollButton  = addScrollButton("prevLocalScrollButton") ;
  this->nextLocalScrollButton  = addScrollButton("nextLocalScrollButton") ;
  this->prevRemoteScrollButton = addScrollButton("prevRemoteScrollButton") ;
  this->nextRemoteScrollButton = addScrollButton("nextRemoteScrollButton") ;
  this->localsResizer          =
      new ResizableEdgeComponent(localChannels  , nullptr , ResizableEdgeComponent::rightEdge) ;
  this->mastersResizer         =
      new ResizableEdgeComponent(masterChannels , nullptr , ResizableEdgeComponent::leftEdge) ;
  addAndMakeVisible(this->localsResizer) ;
  addAndMakeVisible(this->mastersResizer) ;

  this->prevLocalScrollButton ->setButtonText(TRANS("<")) ;
  this->nextLocalScrollButton ->setButtonText(TRANS(">")) ;
  this->prevRemoteScrollButton->setButtonText(TRANS("<")) ;
  this->nextRemoteScrollButton->setButtonText(TRANS(">")) ;
  this->masterChannels        ->setAlwaysOnTop(true) ;
  this->prevLocalScrollButton ->setAlwaysOnTop(true) ;
  this->nextLocalScrollButton ->setAlwaysOnTop(true) ;
  this->prevRemoteScrollButton->setAlwaysOnTop(true) ;
  this->nextRemoteScrollButton->setAlwaysOnTop(true) ;
  this->localsResizer         ->setAlwaysOnTop(true) ;
  this->mastersResizer        ->setAlwaysOnTop(true) ;
  this->localsResizer         ->setSize(GUI::RESIZER_W , GUI::MIXERGROUP_H) ;
  this->mastersResizer        ->setSize(GUI::RESIZER_W , GUI::MIXERGROUP_H) ;
    //[/UserPreSize]

    setSize (622, 284);


    //[Constructor] You can add your own custom stuff here..

  this->localScrollZ = this->remoteScrollZ = 0 ;

    //[/Constructor]
}

Mixer::~Mixer()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..

  this->masterChannels         = nullptr ;
  this->localChannels          = nullptr ;
  this->prevLocalScrollButton  = nullptr ;
  this->nextLocalScrollButton  = nullptr ;
  this->prevRemoteScrollButton = nullptr ;
  this->nextRemoteScrollButton = nullptr ;
  this->localsResizer          = nullptr ;
  this->mastersResizer         = nullptr ;
  deleteAllChildren() ;

    //[/Destructor]
}

//==============================================================================
void Mixer::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0xff101010));
    g.fillRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), static_cast<float> (getHeight() - 0), 10.000f);

    g.setColour (Colours::white);
    g.drawRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), static_cast<float> (getHeight() - 0), 10.000f, 1.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Mixer::resized()
{
    //[UserResized] Add your own custom resize handling here..

  if (this->masterChannels         == nullptr || this->localChannels          == nullptr ||
      this->prevLocalScrollButton  == nullptr || this->nextLocalScrollButton  == nullptr ||
      this->prevRemoteScrollButton == nullptr || this->nextRemoteScrollButton == nullptr  )
    return ;

  // master channels
  int master_x = getWidth() - GUI::MASTERGROUP_W - GUI::PAD ;
  int master_y = GUI::MIXERGROUP_Y ;
  int master_w = GUI::MASTERGROUP_W ;
  int master_h = GUI::MIXERGROUP_H ;
  this->masterChannels->setBounds(master_x , master_y , master_w , master_h) ;

  // local and remote channels
  int channels_x = GUI::PAD ;
  int channels_y = GUI::MIXERGROUP_Y ;
  int channels_w = 0 ;
  int channels_h = GUI::MIXERGROUP_H ;
  int n_groups   = getNumDynamicMixers() ; Channels* channels ;
  for (int group_n = this->remoteScrollZ ; group_n < n_groups ; ++group_n)
  {
    channels    = (Channels*)getChildComponent(group_n) ;
    channels_w  = GUI::MIXERGROUP_W(channels->getNumChannels()) ;
    channels->setBounds(channels_x , channels_y , channels_w , channels_h) ;

    channels_x += GUI::PAD + channels_w ;
  }

  // scroll buttons
  int  locals_resizer_x               = this->localsResizer ->getX() ;
  int  masters_resizer_x              = this->mastersResizer->getX() ;
  int  n_channels                     = this->localChannels->getNumChannels() ;
  int  locals_w                       = GUI::MIXERGROUP_W(n_channels) ;
  bool should_show_prev_local_button  = this->localScrollZ  >  0 ;
  bool should_show_next_local_button  = locals_resizer_x < locals_w + GUI::PAD - 1 ;
  bool should_show_prev_remote_button = this->remoteScrollZ >  0 ;
  bool should_show_next_remote_button = (channels_x > masters_resizer_x) ;
  if (should_show_prev_local_button)
  {
    int prev_local_button_x = GUI::PAD ;
    prevLocalScrollButton->setTopLeftPosition(prev_local_button_x , GUI::CHANNEL_SCROLL_BTN_Y) ;
  }
  if (should_show_next_local_button)
  {
    int next_local_button_x = locals_resizer_x  - GUI::PAD - GUI::CHANNEL_SCROLL_BTN_W ;
    nextLocalScrollButton->setTopLeftPosition(next_local_button_x , GUI::CHANNEL_SCROLL_BTN_Y) ;
  }
  if (should_show_prev_remote_button)
  {
    int prev_button_x = locals_resizer_x + GUI::RESIZER_W + 1 ;
    prevRemoteScrollButton->setTopLeftPosition(prev_button_x , GUI::CHANNEL_SCROLL_BTN_Y) ;
  }
  if (should_show_next_remote_button)
  {
    int next_button_x = masters_resizer_x  - GUI::PAD - GUI::CHANNEL_SCROLL_BTN_W ;
    nextRemoteScrollButton->setTopLeftPosition(next_button_x , GUI::CHANNEL_SCROLL_BTN_Y) ;
  }
  prevLocalScrollButton ->setVisible(should_show_prev_local_button) ;
  nextLocalScrollButton ->setVisible(should_show_next_local_button) ;
  prevRemoteScrollButton->setVisible(should_show_prev_remote_button) ;
  nextRemoteScrollButton->setVisible(should_show_next_remote_button) ;

  // resizers
  positionResizers() ;

    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* Mixer class public methods */

Channels* Mixer::getRemoteChannelsGroup(Identifier user_id)
{
  Channels* a_component = (Channels*)findChildWithID(user_id) ;
  return (a_component)? a_component : addChannels(String(user_id)) ;
}

void Mixer::addChannel(Identifier channels_id , ValueTree channel_store)
{
  Channels* channels = (Channels*)findChildWithID(StringRef(String(channels_id))) ;
  if (!channels || !channel_store.isValid()) return ;

  channels->addChannel(channel_store) ; resized() ;
  channels->setSize(GUI::MIXERGROUP_W(channels->getNumChannels()) , GUI::MIXERGROUP_H) ;
}

void Mixer::updateChannelVU(Identifier channels_id , String channel_id , double vu)
{
  if      (channels_id == GUI::MASTER_MIXERGROUP_IDENTIFIER)
    masterChannels->updateChannelVU(channel_id , vu) ;
  else if (channels_id == GUI::LOCAL_MIXERGROUP_IDENTIFIER)
    localChannels ->updateChannelVU(channel_id , vu) ;
  else
  {
    Channels* channels = (Channels*)findChildWithID(channels_id) ;
    if (channels) channels->updateChannelVU(channel_id , vu) ;
  }
}

void Mixer::positionResizers()
{
  int locals_resizer_x  = localChannels->getWidth() + GUI::PAD2 - 1 ;
  int remotes_resizer_x = masterChannels->getX() - GUI::PAD - 1 ;
  this->localsResizer ->setTopLeftPosition(locals_resizer_x  , GUI::MIXERGROUP_Y) ;
  this->mastersResizer->setTopLeftPosition(remotes_resizer_x , GUI::MIXERGROUP_Y) ;
}


/* Mixer class private methods */

void Mixer::buttonClicked(Button* buttonThatWasClicked)
{
//   if (buttonThatWasClicked == prevScrollButton)
  {

  }

//  else if (buttonThatWasClicked == nextScrollButton)
  {

  }
}

TextButton* Mixer::addScrollButton(String button_id)
{
  TextButton* scroll_button = new TextButton(button_id) ;
  addChildComponent(scroll_button) ;
  scroll_button->addListener(this) ;
  scroll_button->setColour(TextButton::buttonColourId   , Colour(0xff004000)) ;
  scroll_button->setColour(TextButton::buttonOnColourId , Colours::green) ;
  scroll_button->setColour(TextButton::textColourOnId   , Colours::lime) ;
  scroll_button->setColour(TextButton::textColourOffId  , Colours::lime) ;
  scroll_button->setSize(GUI::CHANNEL_SCROLL_BTN_W , GUI::CHANNEL_SCROLL_BTN_H) ;

  return scroll_button ;
}

Channels* Mixer::addChannels(String channels_id)
{
  Channels* channels = new Channels(channels_id) ;
  addChildAndSetID(channels , channels_id) ;
  channels->toFront(true) ;

  resized() ;

  return channels ;
}

int Mixer::getNumDynamicMixers()
{ return getNumChildComponents() - GUI::N_STATIC_MIXER_CHILDREN ; }

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Mixer" componentName="Mixer"
                 parentClasses="public Component, public ButtonListener" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="622" initialHeight="284">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10" fill="solid: ff101010" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
