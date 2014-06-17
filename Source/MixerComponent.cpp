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

#include "MixerComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MixerComponent::MixerComponent ()
{
    setName ("MixerComponent");

    //[UserPreSize]

  this->localMixerGroupComponent  = addMixerGroupComponent(GUI::LOCAL_MIXERGROUP_GUI_ID) ;
  this->masterMixerGroupComponent = addMixerGroupComponent(GUI::MASTER_MIXERGROUP_GUI_ID) ;

    //[/UserPreSize]

    setSize (622, 284);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MixerComponent::~MixerComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
  deleteAllChildren() ;
    //[/Destructor]
}

//==============================================================================
void MixerComponent::paint (Graphics& g)
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

void MixerComponent::resized()
{
    //[UserResized] Add your own custom resize handling here..

  if (this->localMixerGroupComponent != nullptr)
  {
    int n_channels = localMixerGroupComponent->getNumChildComponents() - 1 ;
    int local_x    = GUI::PAD ;
    int local_y    = GUI::MIXERGROUP_Y ;
    int local_w    = GUI::MIXERGROUP_W(n_channels) ;
    int local_h    = GUI::MIXERGROUP_H ;
    this->localMixerGroupComponent->setBounds(local_x , local_y , local_w , local_h) ;
  }

  int master_x = getWidth() - GUI::MASTERGROUP_W - GUI::PAD ;
  int master_y = GUI::MIXERGROUP_Y ;
  int master_w = GUI::MASTERGROUP_W ;
  int master_h = GUI::MIXERGROUP_H ;
  if (this->masterMixerGroupComponent != nullptr)
    this->masterMixerGroupComponent->setBounds(master_x , master_y , master_w , master_h) ;

    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

ValueTree MixerComponent::getChannelConfig(MixerGroupComponent* mixerGroupComponent ,
                                           Identifier channel_id)
{
  if      (mixerGroupComponent == masterMixerGroupComponent)
    return LinJam::Config->masterChannels.getChildWithName(channel_id) ;
  else if (mixerGroupComponent == localMixerGroupComponent)
    return LinJam::Config->localChannels .getChildWithName(channel_id) ;
//   else if (mixerGroupComponent == remoteMixerGroupComponent)
//     return LinJam::Config->remoteChannels.getChildWithName(channel_id) ;
  else return ValueTree::invalid ;
}

void MixerComponent::addMasterChannelComponent(String channel_id)
{
DEBUG_TRACE_ADD_MASTER_CHANNEL

  bool   is_xmit_enabled = false ;
  bool   is_solo_enabled = false ;
  String xmit_rcv_text   = "" ;
  addChannelComponent(masterMixerGroupComponent , channel_id ,
                      is_xmit_enabled , is_solo_enabled , xmit_rcv_text) ;
}

void MixerComponent::addLocalChannelComponent(String channel_id)
{
DEBUG_TRACE_ADD_LOCAL_CHANNEL

  bool   is_xmit_enabled = true ;
  bool   is_solo_enabled = true ;
  String xmit_rcv_text   = GUI::XMIT_LABEL_TEXT ;
  addChannelComponent(localMixerGroupComponent , channel_id ,
                      is_xmit_enabled , is_solo_enabled , xmit_rcv_text) ;
}
/* TODO (issue #22)
void MixerComponent::addRemoteChannelComponent(String channel_id , String user_gui_id)
{
DEBUG_TRACE_ADD_REMOTE_CHANNEL

  MixerGroupComponent* remoteMixerComponent = (MixerGroupComponent*)findChildWithID(channel_id) ;
  if (!remoteMixerComponent) addMixerSectionComponent(user_gui_id) ;

  bool   is_xmit_enabled = false ;
  bool   is_solo_enabled = false ;
  String xmit_rcv_text   = GUI::RCV_LABEL_TEXT ;
  addChannelComponent(remoteMixerGroupComponent , channel_id ,
                      is_xmit_enabled , is_solo_enabled , xmit_rcv_text) ;
}
*/

MixerGroupComponent* MixerComponent::addMixerGroupComponent(String mixergroup_id)
{
  MixerGroupComponent* mixergroup_component = new MixerGroupComponent(mixergroup_id) ;
  addChildAndSetID(mixergroup_component , mixergroup_id) ;
  mixergroup_component->toFront(true) ;

  return mixergroup_component ;
}

void MixerComponent::addChannelComponent(MixerGroupComponent* mixer , String channel_id    ,
                                         bool   is_xmit_enabled     , bool   is_solo_enabled ,
                                         String xmit_rcv_text)
{
  ValueTree channel_config_values = getChannelConfig(mixer , channel_id) ;
  double volume  = double(channel_config_values[STORAGE::VOLUME_IDENTIFIER]) ;
  double pan     = double(channel_config_values[STORAGE::PAN_IDENTIFIER]) ;
  bool is_xmit   = bool(  channel_config_values[STORAGE::XMIT_IDENTIFIER]) ;
  bool is_muted  = bool(  channel_config_values[STORAGE::MUTE_IDENTIFIER]) ;
  bool is_solo   = bool(  channel_config_values[STORAGE::SOLO_IDENTIFIER]) ;
  int  source_ch = int(   channel_config_values[STORAGE::SOURCE_N_IDENTIFIER]) ;
  bool is_stereo = bool(  channel_config_values[STORAGE::STEREO_IDENTIFIER]) ;

  ChannelConfig* channel_config = new ChannelConfig(channel_id , is_xmit_enabled ,
                                                    is_solo_enabled , xmit_rcv_text ,
                                                    volume , pan , is_xmit , is_muted ,
                                                    is_solo , source_ch , is_stereo) ;
  mixer->addChannelComponent(channel_config) ; delete channel_config ;

  int n_channels = mixer->getNumChildComponents() - 1 ;
  mixer->setSize(GUI::MIXERGROUP_W(n_channels) , GUI::MIXERGROUP_H) ;
}

void MixerComponent::updateChannelVU(Identifier mixergroup_id ,
                                     String channel_id        , float vu)
{
  if      (mixergroup_id == GUI::MASTER_MIXERGROUP_IDENTIFIER)
    masterMixerGroupComponent->updateChannelVU(channel_id , vu) ;
  else if (mixergroup_id == GUI::LOCAL_MIXERGROUP_IDENTIFIER)
    localMixerGroupComponent ->updateChannelVU(channel_id , vu) ;
//   else if (mixergroup_id == GUI::REMOTE_MIXERGROUP_IDENTIFIER)
//     remoteMixerGroupComponent->updateChannelVU(channel_id , vu) ;
}

void MixerComponent::channelControlChanged(MixerGroupComponent* mixerGroupComponent ,
                                           Identifier           channel_id          ,
                                           Identifier           config_key          ,
                                           var                  value)
{
  ValueTree channel_config = getChannelConfig(mixerGroupComponent , channel_id) ;
  channel_config.setProperty(config_key , value , &LinJam::Config->configUndoManager) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MixerComponent" componentName="MixerComponent"
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="622" initialHeight="284">
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
