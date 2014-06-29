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

  this->masterChannels   = (MasterChannels*)addChannels(GUI::MASTERS_GUI_ID) ;
  this->localChannels    = (LocalChannels*) addChannels(GUI::LOCALS_GUI_ID) ;
  this->prevScrollButton = addScrollButton("prevScrollButton") ;
  this->nextScrollButton = addScrollButton("nextScrollButton") ;
  this->localsResizer    = new ResizableEdgeComponent(localChannels  , nullptr ,
                                                      ResizableEdgeComponent::rightEdge) ;
  this->mastersResizer   = new ResizableEdgeComponent(masterChannels , nullptr ,
                                                      ResizableEdgeComponent::leftEdge) ;
  addAndMakeVisible(this->localsResizer) ;
  addAndMakeVisible(this->mastersResizer) ;

  this->prevScrollButton->setButtonText(TRANS("<")) ;
  this->nextScrollButton->setButtonText(TRANS(">")) ;
  this->masterChannels  ->setAlwaysOnTop(true) ;
  this->prevScrollButton->setAlwaysOnTop(true) ;
  this->nextScrollButton->setAlwaysOnTop(true) ;
  this->localsResizer   ->setAlwaysOnTop(true) ;
  this->mastersResizer  ->setAlwaysOnTop(true) ;
  this->localsResizer   ->setSize(GUI::RESIZER_W , GUI::MIXERGROUP_H) ;
  this->mastersResizer  ->setSize(GUI::RESIZER_W , GUI::MIXERGROUP_H) ;

    //[/UserPreSize]

    setSize (622, 284);


    //[Constructor] You can add your own custom stuff here..

  this->scrollZ = 1 ;

    //[/Constructor]
}

Mixer::~Mixer()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..

  this->masterChannels   = nullptr ;
  this->localChannels    = nullptr ;
  this->prevScrollButton = nullptr ;
  this->nextScrollButton = nullptr ;
  this->localsResizer    = nullptr ;
  this->mastersResizer   = nullptr ;
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

DEBUG_TRACE_MIXER_COMPONENTS_VB

  if (this->masterChannels   == nullptr || this->localChannels    == nullptr ||
      this->prevScrollButton == nullptr || this->nextScrollButton == nullptr  )
    return ;

  // master channels
  int master_x = getWidth() - GUI::MASTERS_W - GUI::PAD ;
  int master_y = GUI::MIXERGROUP_Y ;
  int master_w = GUI::MASTERS_W ;
  int master_h = GUI::MIXERGROUP_H ;
  this->masterChannels->setBounds(master_x , master_y , master_w , master_h) ;

  // local and remote channels
  int channels_x = GUI::PAD ;
  int channels_y = GUI::MIXERGROUP_Y ;
  int channels_w = 0 ;
  int channels_h = GUI::MIXERGROUP_H ;
  int n_groups   = getNumDynamicMixers() ;
  for (int group_n = GUI::LOCALS_IDX ; group_n < n_groups ; ++group_n)
  {
    Channels* channels = (Channels*)getChildComponent(group_n) ;

    // hide scrolled previous remotes
    if (group_n > GUI::LOCALS_IDX && group_n < this->scrollZ) // hidden remotes
    {
      channels->setVisible(false) ;
      if (group_n == GUI::FIRST_REMOTE_IDX)
        channels_x += GUI::CHANNEL_SCROLL_BTN_W + GUI::RESIZER_W - GUI::PAD ;

      continue ;
    }

    // position visible channels
    channels_w = GUI::MIXERGROUP_W(channels->getNumChannels()) ;
    channels->setBounds(channels_x , channels_y , channels_w , channels_h) ;

    // increment next channel position
    channels_x += GUI::PAD + channels_w ;

    // hide scrolled next remotes
    int masters_resizer_x = getMastersResizerNextX() ;
    channels->setVisible(channels_x <= masters_resizer_x && group_n == n_groups - 1 ||
                         channels_x <= masters_resizer_x - GUI::CHANNEL_SCROLL_BTN_W ) ;
  }

  // resizers
  positionResizers() ;

  // scroll buttons
  int  locals_resizer_x               = this->localsResizer ->getX() ;
  int  masters_resizer_x              = this->mastersResizer->getX() ;
  bool should_show_prev_scroll_button = this->scrollZ > GUI::FIRST_REMOTE_IDX ;
  bool should_show_next_scroll_button = (channels_x > masters_resizer_x) ;
  if (should_show_prev_scroll_button)
  {
    int prev_button_x = locals_resizer_x + GUI::RESIZER_W ;
    prevScrollButton->setTopLeftPosition(prev_button_x , GUI::CHANNEL_SCROLL_BTN_Y) ;
  }
  if (should_show_next_scroll_button)
  {
    int next_button_x = masters_resizer_x - GUI::CHANNEL_SCROLL_BTN_W ;
    nextScrollButton->setTopLeftPosition(next_button_x , GUI::CHANNEL_SCROLL_BTN_Y) ;
  }
  prevScrollButton->setVisible(should_show_prev_scroll_button) ;
  nextScrollButton->setVisible(should_show_next_scroll_button) ;

    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* Mixer class public methods */

Channels* Mixer::getOrAddRemoteChannels(String channels_name , ValueTree user_store)
{
  Channels* channels = getChannels(channels_name) ; if (channels) return channels ;

  channels = addChannels(channels_name) ;

  return channels ;
}

void Mixer::addChannel(String channels_name , ValueTree channel_store)
{
  Channels* channels = (Channels*)findChildWithID(StringRef(channels_name)) ;
  if (!channels || !channel_store.isValid()) return ;

  channels->addChannel(channel_store) ; resized() ;
  channels->setSize(GUI::MIXERGROUP_W(channels->getNumChannels()) , GUI::MIXERGROUP_H) ;
}

void Mixer::updateChannelVU(Identifier channels_id , String channel_id , double vu)
{
  Channels* channels = getChannels(String(channels_id)) ;
  if (channels) channels->updateChannelVU(channel_id , vu) ;
}

void Mixer::positionResizers()
{
  int locals_resizer_x  = getLocalsResizerNextX() ;
  int masters_resizer_x = getMastersResizerNextX() ;
  this->localsResizer ->setTopLeftPosition(locals_resizer_x  , GUI::MIXERGROUP_Y) ;
  this->mastersResizer->setTopLeftPosition(masters_resizer_x , GUI::MIXERGROUP_Y) ;
}

void Mixer::pruneRemotes(NamedValueSet active_users)
{
  // find GUI elements for parted users
  for (int user_n = GUI::FIRST_REMOTE_IDX ; user_n < getNumDynamicMixers() ; ++user_n)
  {
    Channels*  channels = (Channels*)getChildComponent(user_n) ; //ValueTree active_user ;
    Identifier user_id  = Identifier(channels->getComponentID()) ;
    if (active_users.contains(user_id))
    {
      // find GUI elements for removed channels of active user
      for (int channel_n = 0 ; channel_n < channels->getNumChannels() ; ++channel_n)
      {
        Channel*    channel         = (Channel*)channels->getChildComponent(channel_n) ;
        Array<var>* active_channels = active_users[user_id].getArray() ;
        var         channel_id_var  = var(channel->getComponentID()) ;
        if (active_channels->contains(channel_id_var)) continue ;

        // delete orphaned GUI elements for removed channel
        channels->removeChannel(channel) ; --channel_n ;
      }
    }
    // delete orphaned GUI elements for parted user
    else { removeChannels(channels) ; --user_n ; }
  }
}


/* Mixer class private methods */

void Mixer::buttonClicked(Button* buttonThatWasClicked)
{
  int n_remotes = getNumDynamicMixers() - GUI::FIRST_REMOTE_IDX ;
  if      (buttonThatWasClicked == prevScrollButton)
    --this->scrollZ ;
  else if (buttonThatWasClicked == nextScrollButton && this->scrollZ < n_remotes)
    ++this->scrollZ ;
  else return ;

  resized() ;
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

Channels* Mixer::addChannels(String channels_name)
{
  Channels* channels ;
  if      (!channels_name.compare(GUI::MASTERS_GUI_ID)) channels = new MasterChannels() ;
  else if (!channels_name.compare(GUI::LOCALS_GUI_ID))  channels = new LocalChannels() ;
  else                                                  channels = new RemoteChannels() ;
  addChildAndSetID(channels , channels_name) ;
  channels->toFront(true) ;

  resized() ;

  return channels ;
}

Channels* Mixer::getChannels(String channels_name)
{ return (Channels*)findChildWithID(StringRef(channels_name)) ; }

void Mixer::removeChannels(Channels* channels)
{
DEBUG_REMOVE_CHANNELS

  delete channels ; resized() ;
}

int Mixer::getNumDynamicMixers()
{
  return getNumChildComponents() - GUI::N_STATIC_MIXER_CHILDREN ;
}

int Mixer::getLocalsResizerNextX() { return localChannels->getRight() - 1 ; }

int Mixer::getMastersResizerNextX() { return masterChannels->getX() - GUI::RESIZER_W + 1 ; }

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
