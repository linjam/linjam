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
    int n_channels = localMixerGroupComponent->getNumChildComponents() -GUI::N_NON_CHANNELS ;
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

void MixerComponent::addChannelComponent(Identifier mixergroup_id , ValueTree channel_store)
{
  StringRef            id_ref     = StringRef(String(mixergroup_id)) ;
  MixerGroupComponent* mixergroup = (MixerGroupComponent*)findChildWithID(id_ref) ;
  if (!mixergroup || !channel_store.isValid()) return ;

  // add channel GUI and resize the mixer group
  mixergroup->addChannelComponent(channel_store) ;
  int n_channels = mixergroup->getNumChildComponents() - GUI::N_NON_CHANNELS ;
  mixergroup->setSize(GUI::MIXERGROUP_W(n_channels) , GUI::MIXERGROUP_H) ;
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

MixerGroupComponent* MixerComponent::addMixerGroupComponent(String mixergroup_id)
{
  MixerGroupComponent* mixergroup_component = new MixerGroupComponent(mixergroup_id) ;
  addChildAndSetID(mixergroup_component , mixergroup_id) ;
  mixergroup_component->toFront(true) ;

  return mixergroup_component ;
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
