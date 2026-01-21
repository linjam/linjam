/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...

#include "LinJamConfig.h"
#include "Mixer.h"
#include "ConfigChannel.h"
#include "./Trace/TraceChannels.h"

//[/Headers]

#include "Channels.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Channels::Channels ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    loginLabel.reset (new juce::Label ("loginLabel",
                                       juce::String()));
    addAndMakeVisible (loginLabel.get());
    loginLabel->setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    loginLabel->setJustificationType (juce::Justification::centredBottom);
    loginLabel->setEditable (false, false, false);
    loginLabel->setColour (juce::Label::backgroundColourId, juce::Colour (0x00000000));
    loginLabel->setColour (juce::Label::textColourId, juce::Colours::grey);
    loginLabel->setColour (juce::Label::outlineColourId, juce::Colour (0x00000000));
    loginLabel->setColour (juce::TextEditor::textColourId, juce::Colour (0x00000000));
    loginLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    addButton.reset (new juce::TextButton ("addButton"));
    addAndMakeVisible (addButton.get());
    addButton->setButtonText (TRANS ("+"));
    addButton->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff004000));
    addButton->setColour (juce::TextButton::buttonOnColourId, juce::Colours::green);
    addButton->setColour (juce::TextButton::textColourOffId, juce::Colours::lime);
    addButton->setColour (juce::TextButton::textColourOnId, juce::Colours::lime);

    expandButton.reset (new juce::TextButton ("expandButton"));
    addAndMakeVisible (expandButton.get());
    expandButton->setButtonText (TRANS ("+"));
    expandButton->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff404000));
    expandButton->setColour (juce::TextButton::buttonOnColourId, juce::Colours::olive);
    expandButton->setColour (juce::TextButton::textColourOffId, juce::Colours::yellow);
    expandButton->setColour (juce::TextButton::textColourOnId, juce::Colours::yellow);

    ignoreButton.reset (new juce::TextButton ("ignoreButton"));
    addAndMakeVisible (ignoreButton.get());
    ignoreButton->setButtonText (TRANS ("X"));
    ignoreButton->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff400000));
    ignoreButton->setColour (juce::TextButton::buttonOnColourId, juce::Colours::maroon);
    ignoreButton->setColour (juce::TextButton::textColourOffId, juce::Colours::red);
    ignoreButton->setColour (juce::TextButton::textColourOnId, juce::Colours::red);


    //[UserPreSize]

  this->loginLabel  ->setAlwaysOnTop(true) ;
  this->addButton   ->setAlwaysOnTop(true) ;
  this->expandButton->setAlwaysOnTop(true) ;
  this->ignoreButton->setAlwaysOnTop(true) ;

    //[/UserPreSize]

    setSize (67, 276);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

Channels::~Channels()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    loginLabel = nullptr;
    addButton = nullptr;
    expandButton = nullptr;
    ignoreButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..

  deleteAllChildren() ;

    //[/Destructor]
}

//==============================================================================
void Channels::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 0.0f, y = 0.0f, width = static_cast<float> (getWidth() - 0), height = static_cast<float> (getHeight() - 0);
        juce::Colour fillColour = juce::Colour (0xff101010);
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

void Channels::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    loginLabel->setBounds (4, 4, getWidth() - 8, 12);
    addButton->setBounds (getWidth() - 15, 0, 15, 16);
    expandButton->setBounds (getWidth() - 15, 0, 15, 16);
    ignoreButton->setBounds (getWidth() - 15, 16, 15, 16);
    //[UserResized] Add your own custom resize handling here..

  // position add/config/expand buttons
  int btn_x = getWidth() - GUI::HOVER_BTN_W ;
  int btn_y = 0 ;
  int btn_w = GUI::HOVER_BTN_W ;
  int btn_h = GUI::HOVER_BTN_H ;
  this->addButton   ->setBounds(btn_x , btn_y , btn_w , btn_h) ;
  this->expandButton->setBounds(btn_x , btn_y , btn_w , btn_h) ;
  this->ignoreButton->setBounds(btn_x , btn_y , btn_w , btn_h) ;

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

/* Channels class public instance methods */

bool Channels::addChannel(ValueTree channel_store)
{
DEBUG_TRACE_ADD_CHANNEL_GUI_FAIL

  // ensure GUI for this channel does not already exist
  Identifier channel_id = channel_store.getType() ;
  if (!channel_store.isValid() || getChannel(channel_id)) return false ;

  // hide stereo slave channels
  if (int(channel_store[CONFIG::STEREO_ID]) == CONFIG::STEREO_R) return false ;

  // create channel GUI
  Channel* channel = newChannel(channel_store) ;
  addChildAndSetID(channel , Id2Str(channel_id)) ;
  channel->toFront(false) ;

  // resize and shift channel slices
  resized() ;

DEBUG_TRACE_ADD_CHANNEL_GUI

  return true ;
}

void Channels::removeChannel(Identifier channel_id)
{
DEBUG_TRACE_REMOVE_CHANNEL_GUI

  // destroy channel , resize , and shift channel slices
  Component* channel = getChannel(channel_id) ;
  if (channel) { delete channel ; resized() ; }
}

int Channels::getNumChannels()
{
  return getNumChildComponents() - GUI::N_STATIC_CHANNELS_CHILDREN ;
}


/* Channels class protected instance methods */

Channel* Channels::getChannel(Identifier channel_id)
{
  return (Channel*)findChildWithID(StringRef(Id2Str(channel_id))) ;
}


/* MasterChannels , LocalChannels , RemoteChannels classes public class methods */

MasterChannels::MasterChannels()
{
  this->loginLabel  ->setText(GUI::MASTERS_LABEL_TEXT , juce::dontSendNotification) ;
  this->addButton   ->setVisible(false) ;
  this->expandButton->setVisible(false) ;
  this->ignoreButton->setVisible(false) ;
}

LocalChannels::LocalChannels()
{
  this->loginLabel  ->setText(GUI::LOCALS_LABEL_TEXT , juce::dontSendNotification) ;
  this->addButton   ->addListener(this) ;
  this->expandButton->setVisible(false) ;
  this->ignoreButton->setVisible(false) ;
}

RemoteChannels::RemoteChannels(ValueTree user_store , ValueTree blacklist_store)
                              : userStore(user_store) , blacklistStore(blacklist_store)
{
  this->loginLabel  ->setText(Id2Str(user_store.getType()) , juce::dontSendNotification) ;
  this->expandButton->addListener(this) ;
  this->ignoreButton->addListener(this) ;
  this->addButton   ->setVisible(false) ;

  this->isExpanded = false ;
}


/* MasterChannels , LocalChannels , RemoteChannels classes private instance methods */

void LocalChannels::buttonClicked(Button* a_button)
{
  if (a_button == this->addButton.get())
  {
    UPTR<Component> configChannel = std::make_unique<ConfigChannel>(LinJamConfig::NewChannel()) ;
    Component*      mixer         = getParentComponent() ;
    Component*      mainContent   = mixer->getParentComponent() ;

    // compute CallOutBox arrow target posistion
    int modalX = mixer->getX() + getX() + this->addButton->getX() + GUI::HOVER_BTN_XC ;
    int modalY = mixer->getY() + getY() + this->addButton->getY() + GUI::HOVER_BTN_YC ;
    juce::Rectangle<int> modalRect = juce::Rectangle<int>(modalX , modalY , 1 , 1) ;

    // instantiate ConfigChannel as CallOutBox
    configChannel->setSize(GUI::CHANNEL_CONFIG_W , GUI::CHANNEL_CONFIG_H) ;
    CallOutBox::launchAsynchronously(std::move(configChannel) , modalRect , mainContent) ;
  }
}

void RemoteChannels::buttonClicked(Button* a_button)
{
  if      (a_button == this->expandButton.get()) toggleExpandChannels() ;
  else if (a_button == this->ignoreButton.get()) addUserToBlacklist() ;
}

void RemoteChannels::toggleExpandChannels()
{
  this->isExpanded = !this->isExpanded ;

// TODO: (issue #45)
}

void RemoteChannels::addUserToBlacklist()
{
  ValueTree blacklist_entry_store = ValueTree(this->userStore.getType()) ;
  this->blacklistStore.addChild(blacklist_entry_store , -1  , nullptr) ;
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

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Channels" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="67" initialHeight="276">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10.0" fill="solid: ff101010" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <LABEL name="loginLabel" id="11f182b0c62d16d1" memberName="loginLabel"
         virtualName="" explicitFocusOrder="0" pos="4 4 8M 12" bkgCol="0"
         textCol="ff808080" outlineCol="0" edTextCol="0" edBkgCol="0"
         labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12.0"
         kerning="0.0" bold="0" italic="0" justification="20"/>
  <TEXTBUTTON name="addButton" id="e6ac05f3ca896afc" memberName="addButton"
              virtualName="" explicitFocusOrder="0" pos="15R 0 15 16" bgColOff="ff004000"
              bgColOn="ff008000" textCol="ff00ff00" textColOn="ff00ff00" buttonText="+"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="expandButton" id="b034e593677d00a0" memberName="expandButton"
              virtualName="" explicitFocusOrder="0" pos="15R 0 15 16" bgColOff="ff404000"
              bgColOn="ff808000" textCol="ffffff00" textColOn="ffffff00" buttonText="+"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="ignoreButton" id="4e531501a9190ef5" memberName="ignoreButton"
              virtualName="" explicitFocusOrder="0" pos="15R 16 15 16" bgColOff="ff400000"
              bgColOn="ff800000" textCol="ffff0000" textColOn="ffff0000" buttonText="X"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

