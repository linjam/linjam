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
//[/Headers]

#include "MixerComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MixerComponent::MixerComponent ()
{
    setName ("MixerComponent");

    //[UserPreSize]
    //[/UserPreSize]

    setSize (622, 284);


    //[Constructor] You can add your own custom stuff here..

  this->localMixerGroupComponent  = addMixerSectionComponent(GUI::LOCAL_MIXER_GUI_ID) ;
  this->masterMixerGroupComponent = addMixerSectionComponent(GUI::MASTER_MIXER_GUI_ID) ;

  resized() ;

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

  int n_channels = this->getNumChildComponents() - 1 ;// if (!n_channels) n_channels = 1 ;
  int local_x    = GUI::PAD ;
  int local_y    = GUI::MIXERGROUP_Y ;
  int local_w    = GUI::MIXERGROUP_W(n_channels) ;
  int local_h    = GUI::MIXERGROUP_H ;
  if (this->localMixerGroupComponent != nullptr)
    this->localMixerGroupComponent->setBounds(local_x , local_y , local_w , local_h) ;

  int master_x = getWidth() - GUI::MASTERGROUP_W - GUI::PAD ;
  int master_y = GUI::MIXERGROUP_Y ;
  int master_w = GUI::MASTERGROUP_W ;
  int master_h = GUI::MIXERGROUP_H ;
  if (this->masterMixerGroupComponent != nullptr)
    this->masterMixerGroupComponent->setBounds(master_x , master_y , master_w , master_h) ;

    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MixerComponent::addRemoteMixerComponent(String gui_id)
{ addMixerSectionComponent(gui_id) ; }

void MixerComponent::addLocalChannelComponent(String gui_id)
{ addChannelComponent(gui_id , localMixerGroupComponent) ; }

void MixerComponent::addRemoteChannelComponent(String gui_id , String user_gui_id)
{
  MixerGroupComponent* remoteMixerComponent = (MixerGroupComponent*)findChildWithID(gui_id) ;
  if (remoteMixerComponent) addChannelComponent(gui_id , remoteMixerComponent) ;
}

void MixerComponent::addMasterChannelComponent(String gui_id)
{ addChannelComponent(gui_id , masterMixerGroupComponent) ; }


MixerGroupComponent* MixerComponent::addMixerSectionComponent(String gui_id)
{
  MixerGroupComponent* mixer_group_component = new MixerGroupComponent(gui_id) ;
  addChildAndSetID(mixer_group_component , gui_id) ;
  mixer_group_component->toFront(true) ;

  return mixer_group_component ;
}

void MixerComponent::addChannelComponent(String gui_id , MixerGroupComponent* mixer)
{ mixer->addChannelComponent(gui_id) ; }

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
