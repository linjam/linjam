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

#include "Subscriptions.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Subscription::Subscription (ValueTree config_store)
    : configStore(config_store)
{
    addAndMakeVisible (userLabel = new Label ("userLabel",
                                              TRANS("label text")));
    userLabel->setFont (Font (15.00f, Font::plain));
    userLabel->setJustificationType (Justification::centredLeft);
    userLabel->setEditable (false, false, false);
    userLabel->setColour (Label::textColourId, Colours::grey);
    userLabel->setColour (TextEditor::textColourId, Colours::black);
    userLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (removeButton = new TextButton ("removeButton"));
    removeButton->setButtonText (TRANS("X"));
    removeButton->addListener (this);
    removeButton->setColour (TextButton::buttonColourId, Colour (0xff400000));
    removeButton->setColour (TextButton::buttonOnColourId, Colours::maroon);
    removeButton->setColour (TextButton::textColourOnId, Colours::red);
    removeButton->setColour (TextButton::textColourOffId, Colours::red);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (132, 16);


    //[Constructor] You can add your own custom stuff here..

  setSize(GUI::SUBSCRIPTION_W , GUI::SUBSCRIPTION_H) ;

  userLabel->setText(String(config_store.getType()) , juce::dontSendNotification) ;

  this->configStore = config_store ;

    //[/Constructor]
}

Subscription::~Subscription()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    userLabel = nullptr;
    removeButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Subscription::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colours::black);
    g.fillRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), 16.0f, 10.000f);

    g.setColour (Colours::white);
    g.drawRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), 16.0f, 10.000f, 1.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Subscription::resized()
{
    userLabel->setBounds (16, 0, getWidth() - 16, 16);
    removeButton->setBounds (0, 0, 15, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Subscription::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == removeButton)
    {
        //[UserButtonCode_removeButton] -- add your button handler code here..

      // destroy storage for this subscription (configures NJClient asynchronously)
      this->configStore.getParent().removeChild(this->configStore , nullptr) ;

      // destroy this GUI component
      ((Subscriptions*)this->getParentComponent())->removeSubscription(this) ;

        //[/UserButtonCode_removeButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

Subscriptions::Subscriptions(ValueTree config_store)
{
  for (int user_n = 0 ; user_n < config_store.getNumChildren() ; ++user_n)
    addAndMakeVisible(new Subscription(config_store.getChild(user_n))) ;

  setSize(GUI::SUBSCRIPTIONS_W , computeHeight()) ;
}

Subscriptions::~Subscriptions() { deleteAllChildren() ; }

void Subscriptions::resized()
{
  bool is_scrollbar_visible = getHeight() > GUI::SUBSCRIPTIONS_H ;
  int  subscriptions_w      = (is_scrollbar_visible)?
                              GUI::SUBSCRIPTIONS_W - GUI::CONFIG_SCROLLBAR_W - GUI::PAD :
                              GUI::SUBSCRIPTIONS_W ;
  int  user_x               = 0 ;
  int  user_y               = 0 ;

  // resize and arrange user entries
  for (int user_n = 0 ; user_n < getNumChildComponents() ; ++user_n)
  {
    Component* subscription = getChildComponent(user_n) ;

    subscription->setSize(           subscriptions_w , GUI::SUBSCRIPTION_H) ;
    subscription->setTopLeftPosition(user_x          , user_y) ;

    user_y += GUI::SUBSCRIPTION_H + GUI::PAD ;
  }
}

int Subscriptions::computeHeight()
{
  return GUI::PAD + (getNumChildComponents() * (GUI::SUBSCRIPTION_H + GUI::PAD)) ;
}

void Subscriptions::removeSubscription(Subscription* a_subscription)
{
  delete a_subscription ; setSize(GUI::SUBSCRIPTIONS_W , computeHeight()) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Subscription" componentName=""
                 parentClasses="public Component" constructorParams="ValueTree config_store"
                 variableInitialisers="configStore(config_store)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="132" initialHeight="16">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 16" cornerSize="10" fill="solid: ff000000" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <LABEL name="userLabel" id="4316b113334d5ced" memberName="userLabel"
         virtualName="" explicitFocusOrder="0" pos="16 0 16M 16" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="label text" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="removeButton" id="5ea28eb29c334aeb" memberName="removeButton"
              virtualName="" explicitFocusOrder="0" pos="0 0 15 16" bgColOff="ff400000"
              bgColOn="ff800000" textCol="ffff0000" textColOn="ffff0000" buttonText="X"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
