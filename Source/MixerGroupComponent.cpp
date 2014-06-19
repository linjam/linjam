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

#include "MixerGroupComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MixerGroupComponent::MixerGroupComponent (String mixergroup_id)
{
    addAndMakeVisible (mixerSectionLabel = new Label ("mixerSectionLabel",
                                                      String::empty));
    mixerSectionLabel->setFont (Font (12.00f, Font::plain));
    mixerSectionLabel->setJustificationType (Justification::centredTop);
    mixerSectionLabel->setEditable (false, false, false);
    mixerSectionLabel->setColour (Label::textColourId, Colours::grey);
    mixerSectionLabel->setColour (Label::outlineColourId, Colour (0x00000000));
    mixerSectionLabel->setColour (TextEditor::textColourId, Colours::black);
    mixerSectionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (132, 276);


    //[Constructor] You can add your own custom stuff here..
  mixerSectionLabel->setText(mixergroup_id , juce::dontSendNotification) ;
    //[/Constructor]
}

MixerGroupComponent::~MixerGroupComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    mixerSectionLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..

  deleteAllChildren() ;

    //[/Destructor]
}

//==============================================================================
void MixerGroupComponent::paint (Graphics& g)
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

void MixerGroupComponent::resized()
{
    mixerSectionLabel->setBounds ((getWidth() / 2) - ((getWidth() - 8) / 2), 4, getWidth() - 8, 12);
    //[UserResized] Add your own custom resize handling here..

  int n_channels = this->getNumChildComponents() ;
  for (int channel_n = 1 ; channel_n < n_channels ; ++channel_n) // first child is label
  {
    int channel_x = GUI::MIXERGROUP_W(channel_n - 1) ;
    getChildComponent(channel_n)->setTopLeftPosition(channel_x , GUI::CHANNEL_Y) ;
  }

    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MixerGroupComponent::addChannelComponent(ValueTree channel_store)
{
  ChannelComponent* channel_component = new ChannelComponent(channel_store) ;
  this->addChildAndSetID(channel_component , String(channel_store.getType())) ;
  channel_component->toFront(false) ;
}

void MixerGroupComponent::updateChannelVU(String channel_id , float vu)
{ ((ChannelComponent*)findChildWithID(StringRef(channel_id)))->updateChannelVU(vu) ; }

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MixerGroupComponent" componentName=""
                 parentClasses="public Component" constructorParams="String mixergroup_id"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="132" initialHeight="276">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10" fill="solid: ff101010" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <LABEL name="mixerSectionLabel" id="11f182b0c62d16d1" memberName="mixerSectionLabel"
         virtualName="" explicitFocusOrder="0" pos="0Cc 4 8M 12" textCol="ff808080"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText=""
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="12" bold="0" italic="0" justification="12"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
