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
Channels::Channels (String channels_id)
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

    addAndMakeVisible (addButton = new TextButton ("addButton"));
    addButton->setButtonText (TRANS("+"));
    addButton->addListener (this);
    addButton->setColour (TextButton::buttonColourId, Colour (0xff004000));
    addButton->setColour (TextButton::buttonOnColourId, Colours::green);
    addButton->setColour (TextButton::textColourOnId, Colours::lime);
    addButton->setColour (TextButton::textColourOffId, Colours::lime);


    //[UserPreSize]

  this->channelsLabel->setAlwaysOnTop(true) ;
  this->addButton->setAlwaysOnTop(true) ;

    //[/UserPreSize]

    setSize (132, 276);


    //[Constructor] You can add your own custom stuff here..

  bool are_local_channels = (Identifier(channels_id) == GUI::LOCAL_MIXERGROUP_IDENTIFIER) ;
  this->addButton    ->setVisible(are_local_channels) ;
  this->channelsLabel->setText(channels_id , juce::dontSendNotification) ;

    //[/Constructor]
}

Channels::~Channels()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    channelsLabel = nullptr;
    addButton = nullptr;


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
    addButton->setBounds (getWidth() - 15, 0, 15, 16);
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

void Channels::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == addButton)
    {
        //[UserButtonCode_addButton] -- add your button handler code here..

      // TODO: prompt ?
      LinJam::AddLocalChannel(LinJam::Config->encodeChannelId("" , getNumChannels() + 1 )) ;

        //[/UserButtonCode_addButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void Channels::addChannel(ValueTree channel_store)
{
  Channel* channel = new Channel(channel_store) ;
  this->addChildAndSetID(channel , String(channel_store.getType())) ;
  channel->toFront(false) ;
}

void Channels::removeChannel(Channel* channel)
{
DEBUG_REMOVE_CHANNEL

  delete channel ; getParentComponent()->resized() ;
}

int Channels::getNumChannels()
{ return this->getNumChildComponents() - GUI::N_STATIC_CHANNEL_CHILDREN; }

void Channels::updateChannelVU(String channel_id , double vu)
{
  Channel* channel = (Channel*)findChildWithID(StringRef(channel_id)) ;
  if (channel) channel->updateChannelVU(vu) ;

DEBUG_TRACE_INVALID_CHANNELID
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Channels" componentName=""
                 parentClasses="public Component" constructorParams="String channels_id"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="132" initialHeight="276">
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
  <TEXTBUTTON name="addButton" id="e6ac05f3ca896afc" memberName="addButton"
              virtualName="" explicitFocusOrder="0" pos="15R 0 15 16" bgColOff="ff004000"
              bgColOn="ff008000" textCol="ff00ff00" textColOn="ff00ff00" buttonText="+"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
