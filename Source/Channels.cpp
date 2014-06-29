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

//[/Headers]

#include "Channels.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Channels::Channels ()
{
    addAndMakeVisible (channelsLabel = new Label ("channelsLabel",
                                                  String::empty));
    channelsLabel->setFont (Font (12.00f, Font::plain));
    channelsLabel->setJustificationType (Justification::centredTop);
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

    setSize (132, 276);


    //[Constructor] You can add your own custom stuff here..
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

  int n_channels = getNumChannels() ;
  for (int channel_n = 0 ; channel_n < n_channels ; ++channel_n)
  {
    int channel_x = GUI::MIXERGROUP_W(channel_n) ;
    getChildComponent(channel_n)->setTopLeftPosition(channel_x , GUI::CHANNEL_Y) ;
  }

  if (n_channels) ((Mixer*)getParentComponent())->positionResizers() ;

    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* Channels class public class methods */

void Channels::addChannel(ValueTree channel_store)
{
DEBUG_TRACE_ADD_CHANNEL_GUI

  String channel_name = String(channel_store.getType()) ;
  if (findChildWithID(StringRef(channel_name))) return ;

  Channel* channel = newChannel(channel_store) ;
  this->addChildAndSetID(channel , channel_name) ;
  channel->toFront(false) ;
}

void Channels::removeChannel(Channel* channel)
{
DEBUG_REMOVE_CHANNEL

  delete channel ; getParentComponent()->resized() ;
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

MasterChannels::MasterChannels() { this->expandButton ->setVisible(false) ; }

LocalChannels::LocalChannels()
{
  this->expandButton ->setColour(TextButton::buttonColourId   , Colour(0xff004000)) ;
  this->expandButton ->setColour(TextButton::buttonOnColourId , Colour(0xff008000)) ;
  this->expandButton ->setColour(TextButton::textColourOnId   , Colour(0xff00ff00)) ;
  this->expandButton ->setColour(TextButton::textColourOffId  , Colour(0xff00ff00)) ;
  this->expandButton ->addListener(this) ;
}

RemoteChannels::RemoteChannels()
{
  this->expandButton ->setColour(TextButton::buttonColourId   , Colour(0xff404000)) ;
  this->expandButton ->setColour(TextButton::buttonOnColourId , Colour(0xff808000)) ;
  this->expandButton ->setColour(TextButton::textColourOnId   , Colour(0xffffff00)) ;
  this->expandButton ->setColour(TextButton::textColourOffId  , Colour(0xffffff00)) ;
  this->expandButton ->addListener(this) ;
  this->isExpanded = false ;
}


/* MasterChannels , LocalChannels , RemoteChannels classes private class methods */

void LocalChannels::buttonClicked(Button* a_button)
{
  // TODO: prompt ?
  if (a_button == expandButton) LinJam::AddLocalChannel(String::empty) ;
}

void RemoteChannels::buttonClicked(Button* a_button)
{
  if (a_button == expandButton) toggleExpandChannels() ;
}

void RemoteChannels::toggleExpandChannels()
{
  this->isExpanded = !this->isExpanded ;
// TODO:
DBG("toggleExpandChannels() this->isExpanded=" + String(this->isExpanded)) ;
}

Channel* MasterChannels::newChannel(ValueTree channel_store)
{
  return new MasterChannel(channel_store) ;
}

Channel* LocalChannels::newChannel(ValueTree channel_store)
{
  Channel* channel = new LocalChannel(channel_store) ;

  // show/hide remove channel button for this and the first/only channel
  bool     is_first_channel = !getNumChannels() ;
  Channel* first_channel    = (is_first_channel)? channel : (Channel*)getChildComponent(0) ;
  ((LocalChannel*)first_channel)->removeButton->setVisible(true) ;
  ((LocalChannel*)channel)      ->removeButton->setVisible(!is_first_channel) ;

  return channel ;
}

Channel* RemoteChannels::newChannel(ValueTree channel_store)
{
  return new RemoteChannel(channel_store) ;
}

void LocalChannels::removeChannel(Channel* channel)
{
  ((Channels*)this)->removeChannel(channel) ;

  int n_channels = getNumChannels() ;

#ifndef BUGGY_ADD_DUPLICATE_LOCAL_CHANNELS
  // rename any generic channel names to match their NJClient channelIdx
  for (int channel_n = 0 ; channel_n < n_channels ; ++channel_n)
  {
    String channel_name = getChildComponent(channel_n)->getComponentID() ;
    if (channel_name.startsWith(CONFIG::DEFAULT_CHANNEL_NAME))
    {
      int channel_idx     = LinJam::GetLocalChannelIdx(Identifier(channel_name)) ;
      Identifier new_name = Config->encodeChannelId(channel_c_name , channel_idx) ;
      // TODO: howto rename ValueTree
    }
  }
#endif // BUGGY_ADD_DUPLICATE_LOCAL_CHANNELS

  // hide remove channel button for only remaining channel
  if (n_channels == 1)
    ((LocalChannel*)getChildComponent(0))->removeButton->setVisible(false) ;
}

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
                 fixedSize="0" initialWidth="132" initialHeight="276">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10" fill="solid: ff101010" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <LABEL name="channelsLabel" id="11f182b0c62d16d1" memberName="channelsLabel"
         virtualName="" explicitFocusOrder="0" pos="4 4 8M 12" bkgCol="0"
         textCol="ff808080" outlineCol="0" edTextCol="0" edBkgCol="0"
         labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12"
         bold="0" italic="0" justification="12"/>
  <TEXTBUTTON name="expandButton" id="e6ac05f3ca896afc" memberName="expandButton"
              virtualName="" explicitFocusOrder="0" pos="15R 0 15 16" buttonText="+"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
