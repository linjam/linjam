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

#include "ChatComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ChatComponent::ChatComponent ()
{
    addAndMakeVisible (chatTextEditor = new TextEditor ("chatTextEditor"));
    chatTextEditor->setMultiLine (true);
    chatTextEditor->setReturnKeyStartsNewLine (false);
    chatTextEditor->setReadOnly (true);
    chatTextEditor->setScrollbarsShown (true);
    chatTextEditor->setCaretVisible (false);
    chatTextEditor->setPopupMenuEnabled (false);
    chatTextEditor->setColour (TextEditor::textColourId, Colours::grey);
    chatTextEditor->setColour (TextEditor::backgroundColourId, Colours::black);
    chatTextEditor->setText (String::empty);

    addAndMakeVisible (chatEntryTextEditor = new TextEditor ("chatEntryTextEditor"));
    chatEntryTextEditor->setMultiLine (false);
    chatEntryTextEditor->setReturnKeyStartsNewLine (false);
    chatEntryTextEditor->setReadOnly (false);
    chatEntryTextEditor->setScrollbarsShown (false);
    chatEntryTextEditor->setCaretVisible (true);
    chatEntryTextEditor->setPopupMenuEnabled (false);
    chatEntryTextEditor->setColour (TextEditor::textColourId, Colours::grey);
    chatEntryTextEditor->setColour (TextEditor::backgroundColourId, Colours::black);
    chatEntryTextEditor->setColour (TextEditor::highlightColourId, Colour (0x40000020));
    chatEntryTextEditor->setColour (TextEditor::outlineColourId, Colours::grey);
    chatEntryTextEditor->setColour (CaretComponent::caretColourId, Colours::white);
    chatEntryTextEditor->setText (String::empty);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (630, 446);


    //[Constructor] You can add your own custom stuff here..
  this->chatEntryTextEditor->setInputRestrictions(1024) ;
  this->chatEntryTextEditor->addListener(this) ;
    //[/Constructor]
}

ChatComponent::~ChatComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    chatTextEditor = nullptr;
    chatEntryTextEditor = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ChatComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff101010));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ChatComponent::resized()
{
    chatTextEditor->setBounds (4, 4, getWidth() - 8, getHeight() - 36);
    chatEntryTextEditor->setBounds (4, getHeight() - 4 - 24, getWidth() - 8, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ChatComponent::setTopic(String topic_text)
{}// TODO: this->topicLabel->setText(String("TOPIC: " + topic_text)) ; }

void ChatComponent::addChatLine(String chat_user , String chat_text)
{
DBG("ChatComponent::addChatLine() chat_user=" + chat_user + " chat_text=" + chat_text) ;

  this->chatTextEditor->moveCaretToEnd() ;
  this->chatTextEditor->insertTextAtCaret(chat_user + ": " + chat_text + "\n") ;
  this->chatTextEditor->moveCaretToEnd() ;
/*
void 	scrollEditorToPositionCaret (int desiredCaretX, int desiredCaretY)
 	Attempts to scroll the text edit
*/
}

void ChatComponent::textEditorReturnKeyPressed(TextEditor& a_text_editor)
{ LinJam::SendChat(this->chatEntryTextEditor->getText()) ; this->chatEntryTextEditor->clear() ; }
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ChatComponent" componentName=""
                 parentClasses="public Component, public TextEditor::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="630"
                 initialHeight="446">
  <BACKGROUND backgroundColour="ff101010"/>
  <TEXTEDITOR name="chatTextEditor" id="ba11ad8bfe4752c1" memberName="chatTextEditor"
              virtualName="" explicitFocusOrder="0" pos="4 4 8M 36M" textcol="ff808080"
              bkgcol="ff000000" initialText="" multiline="1" retKeyStartsLine="0"
              readonly="1" scrollbars="1" caret="0" popupmenu="0"/>
  <TEXTEDITOR name="chatEntryTextEditor" id="412133d948ede027" memberName="chatEntryTextEditor"
              virtualName="" explicitFocusOrder="0" pos="4 4Rr 8M 24" textcol="ff808080"
              bkgcol="ff000000" hilitecol="40000020" outlinecol="ff808080"
              caretcol="ffffffff" initialText="" multiline="0" retKeyStartsLine="0"
              readonly="0" scrollbars="0" caret="1" popupmenu="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
