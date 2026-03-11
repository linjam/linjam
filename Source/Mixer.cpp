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


//[Headers] You can add your own extra header files here...

#include "Constants.h"
#include "./Trace/TraceMixer.h"

//[/Headers]

#include "Mixer.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Mixer::Mixer (ValueTree blacklist_store, Value gui_layout)
    : blacklistStore(blacklist_store), guiLayout(gui_layout)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    setName ("Mixer");

    //[UserPreSize]

  this->masterChannels   = new MasterChannels(this->guiLayout) ;
  this->localChannels    = new LocalChannels (this->guiLayout) ;
  this->prevScrollButton = new TextButton("prevScrollButton") ;
  this->nextScrollButton = new TextButton("nextScrollButton") ;
  this->localsResizer    = new ResizableEdgeComponent(this->localChannels  , nullptr   ,
                                                      ResizableEdgeComponent::rightEdge) ;
  this->mastersResizer   = new ResizableEdgeComponent(this->masterChannels , nullptr   ,
                                                      ResizableEdgeComponent::leftEdge ) ;

  addChannels(    this->masterChannels , GUI::MASTERS_GUI_ID) ;
  addChannels(    this->localChannels  , GUI::LOCALS_GUI_ID ) ;
  addScrollButton(this->prevScrollButton , "<") ;
  addScrollButton(this->nextScrollButton , ">") ;
  addResizer(     this->localsResizer ) ;
  addResizer(     this->mastersResizer) ;

  this->masterChannels  ->setAlwaysOnTop(true) ;
  this->prevScrollButton->setAlwaysOnTop(true) ;
  this->nextScrollButton->setAlwaysOnTop(true) ;
  this->localsResizer   ->setAlwaysOnTop(true) ;
  this->mastersResizer  ->setAlwaysOnTop(true) ;

    //[/UserPreSize]

    setSize (622, 284);


    //[Constructor] You can add your own custom stuff here..

  this->scrollZ = 1 ;

  // configure listeners
  this->guiLayout.addListener(this) ;

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
void Mixer::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 0.0f, y = 0.0f, width = static_cast<float> (getWidth() - 0), height = static_cast<float> (getHeight() - 0);
        juce::Colour fillColour = juce::Colour (0xff070707);
        juce::Colour strokeColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Mixer::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..

DEBUG_TRACE_MIXER_COMPONENTS_VB

  // master channels
  int masters_x = getWidth() - this->masterChannels->getWidth() - GUI::PAD ;
  int masters_y = GUI::MIXERGROUP_Y ;
  int masters_w = this->masterChannels->getWidth() ;
  int masters_h = GUI::MIXERGROUP_H(this->guiLayout) ;
  this->masterChannels->setBounds(masters_x , masters_y , masters_w , masters_h) ;

  // local and remote channels
  int channels_x = GUI::PAD ;
  int channels_y = GUI::MIXERGROUP_Y ;
  int channels_h = GUI::MIXERGROUP_H(this->guiLayout) - GUI::PAD3 ;
  int n_groups   = getNumDynamicMixers() ;
  for (int group_n = GUI::LOCALS_IDX ; group_n < n_groups ; ++group_n)
  {
    Channels* channels = (Channels*)getChildComponent(group_n) ;

    // apply dynamic height
    channels->setSize(channels->getWidth() , channels_h) ;

#ifndef FADE_HIDDEN_REMOTES
    // hide scrolled previous remotes
    if (group_n > GUI::LOCALS_IDX && group_n < this->scrollZ)
    {
      channels->setVisible(false) ;
      if (group_n == GUI::FIRST_REMOTE_IDX)
        channels_x += GUI::CHANNEL_SCROLL_BTN_W + GUI::RESIZER_W - GUI::PAD ;

      continue ;
    }

    // position visible channels and increment next channel position
    channels->setTopLeftPosition(channels_x , channels_y) ;
    channels_x += GUI::PAD + channels->getWidth() ;

    // hide scrolled next remotes
    int masters_resizer_x = getMastersResizerNextX() ;
    channels->setVisible(channels_x <= masters_resizer_x) ;
#else // FADE_HIDDEN_REMOTES
    // hide scrolled previous remotes
    int channels_w = GUI::CHANNEL_SCROLL_BTN_W + GUI::RESIZER_W - GUI::PAD2 + channels->getWidth() ;
    if (group_n > GUI::LOCALS_IDX && group_n < this->scrollZ)
    {
      bool is_onscreen = group_n < this->scrollZ - 1 ;

      channels->setVisible(is_onscreen) ;

      if (is_onscreen) channels_x += channels_w ;
      else             continue ;
    }

    // hide scrolled next remotes
    int masters_resizer_x = getMastersResizerNextX() ;
    channels->setVisible(channels_x <= masters_resizer_x) ;

    // position visible channels and increment next channel position
    channels->setTopLeftPosition(channels_x , channels_y) ;
    channels_x += GUI::PAD + channels->getWidth() ;
#endif // FADE_HIDDEN_REMOTES
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
    int prev_button_x = locals_resizer_x + GUI::RESIZER_W - 1 ;
    prevScrollButton->setTopLeftPosition(prev_button_x , GUI::CHANNEL_SCROLL_BTN_Y) ;
  }
  if (should_show_next_scroll_button)
  {
    int next_button_x = masters_resizer_x - GUI::CHANNEL_SCROLL_BTN_W + 1 ;
    nextScrollButton->setTopLeftPosition(next_button_x , GUI::CHANNEL_SCROLL_BTN_Y) ;
  }
  prevScrollButton->setVisible(should_show_prev_scroll_button) ;
  nextScrollButton->setVisible(should_show_next_scroll_button) ;

    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* Mixer class public instence methods */

bool Mixer::addRemoteUser(ValueTree user_store)
{
  // ensure GUI for this user does not already exist
  Identifier user_id = user_store.getType() ; if (getChannels(user_id)) return false ;

  // create remote user GUI
  addChannels(new RemoteChannels(this->guiLayout , user_store , this->blacklistStore) , user_id) ;

DEBUG_TRACE_ADD_REMOTE_USER

  return true ;
}

bool Mixer::addChannel(Identifier channels_id , ValueTree channel_store)
{
  // validate channels group GUI and storage
  Channels* channels = getChannels(channels_id) ;
  if (!channels || !channel_store.isValid()) return false ;

  // create channel GUI and update mixer layout
  bool was_added = channels->addChannel(channel_store) ;
  if (was_added && channels != this->masterChannels) resized() ;

  return was_added ;
}

void Mixer::removeChannel(Identifier channels_id , Identifier channel_id)
{
  Channels* channels = getChannels(channels_id) ;
  if (channels) channels->removeChannel(channel_id) ;
}

void Mixer::positionResizers()
{
  int locals_resizer_x  = getLocalsResizerNextX() ;
  int masters_resizer_x = getMastersResizerNextX() ;
  this->localsResizer ->setTopLeftPosition(locals_resizer_x  , GUI::MIXERGROUP_Y) ;
  this->mastersResizer->setTopLeftPosition(masters_resizer_x , GUI::MIXERGROUP_Y) ;
}

void Mixer::pruneRemotes(ValueTree active_users)
{
  // find GUI elements for parted users
  for (int user_n = GUI::FIRST_REMOTE_IDX ; user_n < getNumDynamicMixers() ; ++user_n)
  {
    RemoteChannels* channels        = (RemoteChannels*)getChildComponent(user_n) ;
    Identifier      user_id         = Identifier(channels->getComponentID()) ;
    Array<var>*     active_channels = active_users[user_id].getArray() ;

    if (active_users.hasProperty(user_id))
    {
      // find GUI elements for removed channels of active user (first is master)
      for (int channel_n = 1 ; channel_n < channels->getNumChannels() ; ++channel_n)
      {
        Component* channel    = channels->getChildComponent(channel_n) ;
        var        channel_id = var(channel->getComponentID()) ;

        if (active_channels->contains(channel_id)) continue ;

        // delete orphaned GUI elements for removed channel
        removeChannel(user_id , Identifier(channel_id.toString())) ; --channel_n ;
      }
    }
    // delete orphaned GUI elements for parted user
    else { removeChannels(channels) ; --user_n ; }
  }
}

int Mixer::getNumDynamicMixers()
{
  return getNumChildComponents() - GUI::N_STATIC_MIXER_CHILDREN ;
}


/* Mixer class private instance methods */

void Mixer::buttonClicked(Button* a_button)
{
  // shift scroll position by one channels group
  int n_remotes = getNumDynamicMixers() - GUI::FIRST_REMOTE_IDX ;
  if      (a_button == prevScrollButton)                              --this->scrollZ ;
  else if (a_button == nextScrollButton && this->scrollZ < n_remotes) ++this->scrollZ ;
  else return ;

  // update mixer layout
  resized() ;
}

void Mixer::valueChanged(Value& a_value)
{
  if (! a_value.refersToSameSourceAs(this->guiLayout)) return ;

  setSize(getWidth() , GUI::MIXERGROUP_H(this->guiLayout)) ;
}

void Mixer::addChannels(Channels* channels , Identifier channels_id)
{
  // add channels group to the mixer
  addChildAndSetID(channels , Id2Str(channels_id)) ; channels->toFront(true) ;

  // update mixer layout
  resized() ;
}

void Mixer::removeChannels(Channels* channels)
{
DEBUG_TRACE_REMOVE_CHANNELS

  // destroy channels group and update mixer layout
  delete channels ; resized() ;
}

void Mixer::addScrollButton(TextButton* scroll_button , String button_text)
{
  addChildComponent(scroll_button) ;
  scroll_button->addListener(this) ;
  scroll_button->setButtonText(button_text) ;
  scroll_button->setColour(TextButton::buttonColourId   , Colour(0xff004000)) ;
  scroll_button->setColour(TextButton::buttonOnColourId , Colours::green) ;
  scroll_button->setColour(TextButton::textColourOnId   , Colours::lime) ;
  scroll_button->setColour(TextButton::textColourOffId  , Colours::lime) ;
  scroll_button->setSize(GUI::CHANNEL_SCROLL_BTN_W , GUI::CHANNEL_SCROLL_BTN_H) ;
}

void Mixer::addResizer(ResizableEdgeComponent* resizer)
{
  int mixergroup_h = GUI::MIXERGROUP_H(this->guiLayout) ;

  addAndMakeVisible(resizer) ;
  resizer->setSize(GUI::RESIZER_W , mixergroup_h) ;
}

Channels* Mixer::getChannels(Identifier channels_id)
{
  return (Channels*)findChildWithID(StringRef(channels_id)) ;
}

int Mixer::getLocalsResizerNextX() { return localChannels->getRight() - 1 ; }

int Mixer::getMastersResizerNextX() { return masterChannels->getX() - GUI::RESIZER_W + 1 ; }

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Mixer" componentName="Mixer"
                 parentClasses="public Component, public Button::Listener, public Value::Listener"
                 constructorParams="ValueTree blacklist_store, Value gui_layout"
                 variableInitialisers="blacklistStore(blacklist_store), guiLayout(gui_layout)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="622" initialHeight="284">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10.0" fill="solid: ff070707" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

