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

#include "LinJam.h"
#include "Constants.h"
#include "ChannelConfig.h"

//[/Headers]

#include "Channels.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Channels::Channels ()
{
    addAndMakeVisible (channelsLabel = new Label ("channelsLabel",
                                                  TRANS("s")));
    channelsLabel->setFont (Font (12.00f, Font::plain));
    channelsLabel->setJustificationType (Justification::centredBottom);
    channelsLabel->setEditable (false, false, false);
    channelsLabel->setColour (Label::backgroundColourId, Colour (0x00000000));
    channelsLabel->setColour (Label::textColourId, Colours::grey);
    channelsLabel->setColour (Label::outlineColourId, Colour (0x00000000));
    channelsLabel->setColour (TextEditor::textColourId, Colour (0x00000000));
    channelsLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (expandButton = new TextButton ("expandButton"));
    expandButton->setButtonText (TRANS("+"));


    //[UserPreSize]

  this->channelsLabel->setAlwaysOnTop(true) ;
  this->expandButton ->setAlwaysOnTop(true) ;

    //[/UserPreSize]

    setSize (67, 276);


    //[Constructor] You can add your own custom stuff here..
  // prevent empty local group from collapsing (-1 forces resize on first addition)
//   channels->setSize(GUI::MIXERGROUP_W(1) - 1 , GUI::MIXERGROUP_H) ;
    //[/Constructor]
}

Channels::~Channels()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    channelsLabel = nullptr;
    expandButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..

  deleteAllChildren() ;

    //[/Destructor]
}

//==============================================================================
void Channels::paint (Graphics& g)
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

void Channels::resized()
{
    channelsLabel->setBounds (4, 4, getWidth() - 8, 12);
    expandButton->setBounds (getWidth() - 15, 0, 15, 16);
    //[UserResized] Add your own custom resize handling here..

  int expand_btn_x = getWidth() - GUI::EXPAND_BTN_W ;
  int expand_btn_y = 0 ;
  int expand_btn_w = GUI::EXPAND_BTN_W ;
  int expand_btn_h = GUI::EXPAND_BTN_H ;
  this->expandButton->setBounds(expand_btn_x , expand_btn_y , expand_btn_w , expand_btn_h) ;

  // resize this container
  int n_channels = getNumChannels() ;
  int channels_w = GUI::MIXERGROUP_W((n_channels)? n_channels : 1) ;
  int channels_h = GUI::MIXERGROUP_H ;
  setSize(channels_w , channels_h) ;

  // shift child channels
  for (int channel_n = 0 ; channel_n < n_channels ; ++channel_n)
  {
    int channel_x = GUI::MIXERGROUP_W(channel_n) ;
    getChildComponent(channel_n)->setTopLeftPosition(channel_x , GUI::CHANNEL_Y) ;
  }

  // update mixer layout
  Mixer* mixer = (Mixer*)getParentComponent() ; if (mixer) mixer->resized() ;

    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* Channels class public class methods */

bool Channels::addChannel(ValueTree channel_store)
{
DEBUG_TRACE_ADD_CHANNEL_GUI_FAIL

  // ensure GUI for this channel does not already exist
  String channel_name = String(channel_store.getType()) ;
  if (channel_name.isEmpty() || findChildWithID(StringRef(channel_name))) return false ;

  // hide stereo pair 'phantom' channels
  if (bool(channel_store[CONFIG::IS_STEREO_ID])  &&
      int( channel_store[CONFIG::SOURCE_N_ID]) % 2) return true ;

  // create channel GUI
  Channel* channel = newChannel(channel_store) ;
  this->addChildAndSetID(channel , channel_name) ;
  channel->toFront(false) ;

  // resize and shift channel slices
  resized() ;

  return true ;
}

void Channels::removeChannel(Channel* channel)
{
  // destroy channel and shift channel slices
  delete channel ; resized() ;
}

int Channels::getNumChannels()
{
  return this->getNumChildComponents() - GUI::N_STATIC_CHANNEL_CHILDREN ;
}

void Channels::updateChannelVU(String channel_id , double vu)
{
DEBUG_TRACE_INVALID_CHANNELID

  if (channel_id.isEmpty()) return ;

  Channel* channel = (Channel*)findChildWithID(StringRef(channel_id)) ;
  if (channel) channel->updateChannelVU(vu) ;
}


/* Channels class private class methods */

void Channels::broughtToFront()
{
  this->channelsLabel->setText(getComponentID() , juce::dontSendNotification) ;
}


/* MasterChannels , LocalChannels , RemoteChannels classes public class methods */

MasterChannels::MasterChannels() { this->expandButton->setVisible(false) ; }

LocalChannels::LocalChannels()
{
  this->expandButton->setColour(TextButton::buttonColourId   , Colour(0xff004000)) ;
  this->expandButton->setColour(TextButton::buttonOnColourId , Colour(0xff008000)) ;
  this->expandButton->setColour(TextButton::textColourOnId   , Colour(0xff00ff00)) ;
  this->expandButton->setColour(TextButton::textColourOffId  , Colour(0xff00ff00)) ;
  this->expandButton->addListener(this) ;
}

RemoteChannels::RemoteChannels(ValueTree user_store)
{
  this->expandButton->setColour(TextButton::buttonColourId   , Colour(0xff404000)) ;
  this->expandButton->setColour(TextButton::buttonOnColourId , Colour(0xff808000)) ;
  this->expandButton->setColour(TextButton::textColourOnId   , Colour(0xffffff00)) ;
  this->expandButton->setColour(TextButton::textColourOffId  , Colour(0xffffff00)) ;
  this->expandButton->addListener(this) ;
  this->isExpanded = false ;
}


/* MasterChannels , LocalChannels , RemoteChannels classes private class methods */

void LocalChannels::buttonClicked(Button* a_button)
{
  if (a_button == expandButton)
  {
    Component*     mixer         = getParentComponent() ;
    Component*     mainContent   = mixer->getParentComponent() ;
    ChannelConfig* channelConfig = new ChannelConfig() ;
    channelConfig->setSize(GUI::CHANNEL_CONFIG_W , GUI::CHANNEL_CONFIG_H) ;

    int modalX = mixer->getX() + getX() + expandButton->getX() + (GUI::EXPAND_BTN_W / 2) ;
    int modalY = mixer->getY() + getY() + expandButton->getY() + (GUI::EXPAND_BTN_H / 2) ;

    Rectangle<int> modalRect = Rectangle<int>(modalX , modalY , 1 , 1) ;
    CallOutBox&    modalBox  = CallOutBox::launchAsynchronously(channelConfig ,
                                                                modalRect     ,
                                                                mainContent   ) ;
  }
}

void RemoteChannels::buttonClicked(Button* a_button)
{
  if (a_button == expandButton) toggleExpandChannels() ;
}

void RemoteChannels::toggleExpandChannels()
{
  this->isExpanded = !this->isExpanded ;
// TODO: (issue #45)
DBG("toggleExpandChannels() this->isExpanded=" + String(this->isExpanded)) ;
}

Channel* MasterChannels::newChannel(ValueTree channel_store)
{
  return new MasterChannel(channel_store) ;
}

Channel* LocalChannels::newChannel(ValueTree channel_store)
{
  return new LocalChannel(channel_store) ;
}

Channel* RemoteChannels::newChannel(ValueTree channel_store)
{
  return new RemoteChannel(channel_store) ;
}

#if DEBUG
void LocalChannels::removeChannel(Channel* channel)
{
LocalChannel* ch = (LocalChannel*)channel ; DEBUG_REMOVE_CHANNEL

  ((Channels*)this)->removeChannel(channel) ;

#ifndef BUGGY_DUPLICATE_CHANNEL_NAMES
// untested (issue #46)
  // rename any generic channel names to match their NJClient channelIdx
  int n_channels = getNumChannels() ;
  for (int channel_n = 0 ; channel_n < n_channels ; ++channel_n)
  {
    Channel* channel      = getChildComponent(channel_n) ;
    String   channel_name = channel->getComponentID() ;
    if (channel_name.startsWith(CONFIG::DEFAULT_CHANNEL_NAME))
    {
      // 'rename' channel store node and set new component ID and label text
      int        channel_idx = LinJam::GetLocalChannelIdx(Identifier(channel_name)) ;
      Identifier new_name    = Config->encodeChannelId(channel_c_name , channel_idx) ;
      ValueTree  new_node    = ValueTree(new_name) ;
      new_node.copyPropertiesFrom(channel-configStore , nullptr) ;
      channel->setComponentID(String(new_name)) ;
      channel->nameLabel->setText(String(new_name)) ;
    }
  }
#endif // BUGGY_DUPLICATE_CHANNEL_NAMES
}
void RemoteChannels::removeChannel(Channel* channel)
{
RemoteChannel* ch = (RemoteChannel*)channel ; DEBUG_REMOVE_CHANNEL

  ((Channels*)this)->removeChannel(channel) ;
}
#endif // DEBUG

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Channels" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="67" initialHeight="276">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10" fill="solid: ff101010" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <LABEL name="channelsLabel" id="11f182b0c62d16d1" memberName="channelsLabel"
         virtualName="" explicitFocusOrder="0" pos="4 4 8M 12" bkgCol="0"
         textCol="ff808080" outlineCol="0" edTextCol="0" edBkgCol="0"
         labelText="s" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12"
         bold="0" italic="0" justification="20"/>
  <TEXTBUTTON name="expandButton" id="e6ac05f3ca896afc" memberName="expandButton"
              virtualName="" explicitFocusOrder="0" pos="15R 0 15 16" buttonText="+"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
