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

//[/Headers]

#include "Chat.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Chat::Chat ()
{
    setName ("Chat");
    addAndMakeVisible (chatText = new TextEditor ("chatText"));
    chatText->setMultiLine (true);
    chatText->setReturnKeyStartsNewLine (false);
    chatText->setReadOnly (true);
    chatText->setScrollbarsShown (true);
    chatText->setCaretVisible (false);
    chatText->setPopupMenuEnabled (false);
    chatText->setColour (TextEditor::textColourId, Colours::grey);
    chatText->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    chatText->setColour (TextEditor::highlightColourId, Colour (0x00000000));
    chatText->setColour (TextEditor::outlineColourId, Colour (0x00000000));
    chatText->setText (String::empty);

    addAndMakeVisible (chatEntryText = new TextEditor ("chatEntryText"));
    chatEntryText->setExplicitFocusOrder (1);
    chatEntryText->setMultiLine (false);
    chatEntryText->setReturnKeyStartsNewLine (false);
    chatEntryText->setReadOnly (false);
    chatEntryText->setScrollbarsShown (false);
    chatEntryText->setCaretVisible (true);
    chatEntryText->setPopupMenuEnabled (false);
    chatEntryText->setColour (TextEditor::textColourId, Colours::grey);
    chatEntryText->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    chatEntryText->setColour (TextEditor::highlightColourId, Colour (0x00000000));
    chatEntryText->setColour (TextEditor::outlineColourId, Colour (0x00000000));
    chatEntryText->setColour (CaretComponent::caretColourId, Colours::white);
    chatEntryText->setText (String::empty);

    addAndMakeVisible (topicLabel = new Label ("topicLabel",
                                               String::empty));
    topicLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::bold));
    topicLabel->setJustificationType (Justification::centredTop);
    topicLabel->setEditable (true, true, true);
    topicLabel->setColour (Label::backgroundColourId, Colour (0x00000000));
    topicLabel->setColour (Label::textColourId, Colours::grey);
    topicLabel->setColour (TextEditor::textColourId, Colours::grey);
    topicLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    topicLabel->setColour (TextEditor::highlightColourId, Colour (0xffbbbbff));
    topicLabel->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (622, 162);


    //[Constructor] You can add your own custom stuff here..

  this->prevTopicText = String::empty ;
  this->topicLabel   ->setColour(CaretComponent::caretColourId , Colours::white) ;
  this->chatText     ->setWantsKeyboardFocus(false) ;
  this->chatEntryText->setWantsKeyboardFocus(true) ;
  this->chatEntryText->setInputRestrictions(1024) ;
  this->chatEntryText->addListener(this) ;

    //[/Constructor]
}

Chat::~Chat()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    chatText = nullptr;
    chatEntryText = nullptr;
    topicLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Chat::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0xff101010));
    g.fillRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), static_cast<float> (getHeight() - 0), 10.000f);

    g.setColour (Colours::white);
    g.drawRoundedRectangle (0.0f, 0.0f, static_cast<float> (getWidth() - 0), static_cast<float> (getHeight() - 0), 10.000f, 1.000f);

    g.setColour (Colours::black);
    g.fillRoundedRectangle (4.0f, 4.0f, static_cast<float> (getWidth() - 8), static_cast<float> (getHeight() - 36), 10.000f);

    g.setColour (Colours::grey);
    g.drawRoundedRectangle (4.0f, 4.0f, static_cast<float> (getWidth() - 8), static_cast<float> (getHeight() - 36), 10.000f, 1.000f);

    g.setColour (Colours::black);
    g.fillRoundedRectangle (4.0f, static_cast<float> (getHeight() - 28), static_cast<float> (getWidth() - 8), 24.0f, 10.000f);

    g.setColour (Colours::grey);
    g.drawRoundedRectangle (4.0f, static_cast<float> (getHeight() - 28), static_cast<float> (getWidth() - 8), 24.0f, 10.000f, 1.000f);

    g.setColour (Colour (0xff101010));
    g.fillRoundedRectangle (8.0f, 8.0f, static_cast<float> (getWidth() - 16), 20.0f, 10.000f);

    g.setColour (Colours::grey);
    g.drawRoundedRectangle (8.0f, 8.0f, static_cast<float> (getWidth() - 16), 20.0f, 10.000f, 1.000f);

    //[UserPaint] Add your own custom painting code here..

  bool is_topic_visible = (getHeight() > GUI::MIN_SHOW_TOPIC_CHAT_H) ;
  if (!is_topic_visible)
  {
    g.setColour (Colours::black) ;
    g.fillRoundedRectangle (8.0f, 8.0f, static_cast<float> (getWidth() - 16), 20.0f, 10.000f);

    g.setColour (Colours::black) ;
    g.drawRoundedRectangle (8.0f, 8.0f, static_cast<float> (getWidth() - 16), 20.0f, 10.000f, 2.000f);
  }
    //[/UserPaint]
}

void Chat::resized()
{
    chatText->setBounds (8, 8, getWidth() - 16, getHeight() - 44);
    chatEntryText->setBounds (8, getHeight() - 24, getWidth() - 16, 16);
    topicLabel->setBounds (8, 10, getWidth() - 16, 16);
    //[UserResized] Add your own custom resize handling here..

  bool is_topic_visible = (getHeight() > GUI::MIN_SHOW_TOPIC_CHAT_H) ;
  this->topicLabel->setVisible(is_topic_visible) ;
  if (is_topic_visible)
  {
    int new_y = this->chatText->getY() + GUI::TOPIC_PADDED_H ;
    int new_h = this->chatText->getHeight() - GUI::TOPIC_PADDED_H ;
    this->chatText->setTopLeftPosition(this->chatText->getX() , new_y) ;
    this->chatText->setSize(this->chatText->getWidth() , new_h) ;
  }

    //[/UserResized]
}

void Chat::labelTextChanged (Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == topicLabel)
    {
        //[UserLabelCode_topicLabel] -- add your label text handling code here..

      // post topic change message to server but defer updating GUI until ack
      LinJam::SendChat(CLIENT::CHATMSG_CMD_TOPIC + " " + this->topicLabel->getText()) ;
      this->topicLabel->setText(this->prevTopicText , juce::dontSendNotification) ;

        //[/UserLabelCode_topicLabel]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void Chat::setTopic(String topic_text)
{
  this->topicLabel->setText(topic_text , juce::dontSendNotification) ;
  this->prevTopicText = topic_text ;
}

void Chat::addChatLine(String chat_user , String chat_text)
{
  this->chatText->moveCaretToEnd() ;
  this->chatText->insertTextAtCaret(chat_user + ": " + chat_text + "\n") ;
  this->chatText->moveCaretToEnd() ;
}

void Chat::textEditorReturnKeyPressed(TextEditor& a_text_editor)
{
  LinJam::SendChat(this->chatEntryText->getText()) ;
  this->chatEntryText->clear() ;
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Chat" componentName="Chat"
                 parentClasses="public Component, public TextEditor::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="622"
                 initialHeight="162">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10" fill="solid: ff101010" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <ROUNDRECT pos="4 4 8M 36M" cornerSize="10" fill="solid: ff000000" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ff808080"/>
    <ROUNDRECT pos="4 28R 8M 24" cornerSize="10" fill="solid: ff000000" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ff808080"/>
    <ROUNDRECT pos="8 8 16M 20" cornerSize="10" fill="solid: ff101010" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ff808080"/>
  </BACKGROUND>
  <TEXTEDITOR name="chatText" id="ba11ad8bfe4752c1" memberName="chatText" virtualName=""
              explicitFocusOrder="0" pos="8 8 16M 44M" textcol="ff808080" bkgcol="0"
              hilitecol="0" outlinecol="0" initialText="" multiline="1" retKeyStartsLine="0"
              readonly="1" scrollbars="1" caret="0" popupmenu="0"/>
  <TEXTEDITOR name="chatEntryText" id="412133d948ede027" memberName="chatEntryText"
              virtualName="" explicitFocusOrder="1" pos="8 24R 16M 16" textcol="ff808080"
              bkgcol="0" hilitecol="0" outlinecol="0" caretcol="ffffffff" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="0"/>
  <LABEL name="topicLabel" id="3544f00ed11410e1" memberName="topicLabel"
         virtualName="" explicitFocusOrder="0" pos="8 10 16M 16" bkgCol="0"
         textCol="ff808080" edTextCol="ff808080" edBkgCol="0" hiliteCol="ffbbbbff"
         labelText="" editableSingleClick="1" editableDoubleClick="1"
         focusDiscardsChanges="1" fontname="Default monospaced font" fontsize="15"
         bold="1" italic="0" justification="12"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
