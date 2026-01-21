/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.12

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...

#include "Constants.h"

//[/Headers]

#include "Blacklist.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
BlacklistEntry::BlacklistEntry (ValueTree blacklist_store)
    : blacklistStore(blacklist_store)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    removeButton.reset (new juce::TextButton ("removeButton"));
    addAndMakeVisible (removeButton.get());
    removeButton->setButtonText (TRANS ("X"));
    removeButton->addListener (this);
    removeButton->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff400000));
    removeButton->setColour (juce::TextButton::buttonOnColourId, juce::Colours::maroon);
    removeButton->setColour (juce::TextButton::textColourOffId, juce::Colours::red);
    removeButton->setColour (juce::TextButton::textColourOnId, juce::Colours::red);

    removeButton->setBounds (0, 0, 15, 16);

    userLabel.reset (new juce::Label ("userLabel",
                                      TRANS ("label text")));
    addAndMakeVisible (userLabel.get());
    userLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    userLabel->setJustificationType (juce::Justification::centredLeft);
    userLabel->setEditable (false, false, false);
    userLabel->setColour (juce::Label::textColourId, juce::Colours::grey);
    userLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    userLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (132, 16);


    //[Constructor] You can add your own custom stuff here..

  setSize(GUI::BLACKLIST_ENTRY_W , GUI::BLACKLIST_ENTRY_H) ;

  userLabel->setText(Id2Str(blacklist_store.getType()) , juce::dontSendNotification) ;

    //[/Constructor]
}

BlacklistEntry::~BlacklistEntry()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    removeButton = nullptr;
    userLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void BlacklistEntry::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 0.0f, y = 0.0f, width = static_cast<float> (getWidth() - 0), height = 16.0f;
        juce::Colour fillColour = juce::Colours::black;
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

void BlacklistEntry::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    userLabel->setBounds (16, 0, getWidth() - 16, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void BlacklistEntry::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == removeButton.get())
    {
        //[UserButtonCode_removeButton] -- add your button handler code here..

      // destroy storage for this subscription (configures NJClient asynchronously)
      this->blacklistStore.getParent().removeChild(this->blacklistStore , nullptr) ;

      // destroy this GUI component
      ((Blacklist*)this->getParentComponent())->removeBlacklistEntry(this) ;

        //[/UserButtonCode_removeButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

Blacklist::Blacklist(ValueTree blacklist_store) : blacklistStore(blacklist_store)
{
  this->blacklistStore.addListener(this) ;

  for (int user_n = 0 ; user_n < this->blacklistStore.getNumChildren() ; ++user_n)
    addAndMakeVisible(new BlacklistEntry(this->blacklistStore.getChild(user_n))) ;

  resize() ;
}

Blacklist::~Blacklist() { deleteAllChildren() ; }

void Blacklist::resized()
{
  bool is_scrollbar_visible = getHeight() > GUI::BLACKLIST_H ;
  int  blacklist_entry_w    = (is_scrollbar_visible)?
                              GUI::BLACKLIST_W - GUI::CONFIG_SCROLLBAR_W - GUI::PAD :
                              GUI::BLACKLIST_W ;
  int  blacklist_entry_x    = 0 ;
  int  blacklist_entry_y    = 0 ;

  // resize and arrange user entries
  for (int user_n = 0 ; user_n < getNumChildComponents() ; ++user_n)
  {
    Component* blacklist_entry = getChildComponent(user_n) ;

    blacklist_entry->setSize(           blacklist_entry_w , GUI::BLACKLIST_ENTRY_H) ;
    blacklist_entry->setTopLeftPosition(blacklist_entry_x , blacklist_entry_y     ) ;

    blacklist_entry_y += GUI::BLACKLIST_ENTRY_H + GUI::PAD ;
  }
}

void Blacklist::resize()
{
  setSize(GUI::BLACKLIST_W ,
          GUI::PAD + (getNumChildComponents() * (GUI::BLACKLIST_ENTRY_H + GUI::PAD))) ;
}

void Blacklist::removeBlacklistEntry(BlacklistEntry* blacklist_entry)
{
  delete blacklist_entry ; resize() ;
}

void Blacklist::valueTreeChildAdded(ValueTree& /*parent_node*/ , ValueTree& node)
{
  addAndMakeVisible(new BlacklistEntry(node)) ; resize() ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="BlacklistEntry" componentName=""
                 parentClasses="public Component" constructorParams="ValueTree blacklist_store"
                 variableInitialisers="blacklistStore(blacklist_store)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="132" initialHeight="16">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 16" cornerSize="10.0" fill="solid: ff000000" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <TEXTBUTTON name="removeButton" id="5ea28eb29c334aeb" memberName="removeButton"
              virtualName="" explicitFocusOrder="0" pos="0 0 15 16" bgColOff="ff400000"
              bgColOn="ff800000" textCol="ffff0000" textColOn="ffff0000" buttonText="X"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="userLabel" id="4316b113334d5ced" memberName="userLabel"
         virtualName="" explicitFocusOrder="0" pos="16 0 16M 16" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="label text" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

