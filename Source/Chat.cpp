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
    addAndMakeVisible (chatTextEditor = new TextEditor ("chatTextEditor"));
    chatTextEditor->setMultiLine (true);
    chatTextEditor->setReturnKeyStartsNewLine (false);
    chatTextEditor->setReadOnly (true);
    chatTextEditor->setScrollbarsShown (true);
    chatTextEditor->setCaretVisible (false);
    chatTextEditor->setPopupMenuEnabled (false);
    chatTextEditor->setColour (TextEditor::textColourId, Colours::grey);
    chatTextEditor->setColour (TextEditor::backgroundColourId, Colours::black);
    chatTextEditor->setColour (TextEditor::highlightColourId, Colour (0x00000000));
    chatTextEditor->setColour (TextEditor::outlineColourId, Colour (0x00000000));
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
    chatEntryTextEditor->setColour (TextEditor::highlightColourId, Colour (0x00000000));
    chatEntryTextEditor->setColour (TextEditor::outlineColourId, Colour (0x00000000));
    chatEntryTextEditor->setColour (CaretComponent::caretColourId, Colours::white);
    chatEntryTextEditor->setText (String::empty);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (622, 162);


    //[Constructor] You can add your own custom stuff here..
  this->chatEntryTextEditor->setInputRestrictions(1024) ;
  this->chatEntryTextEditor->addListener(this) ;
  this->chatTextEditor->setWantsKeyboardFocus(false) ;
  this->chatEntryTextEditor->setWantsKeyboardFocus(true) ;
    //[/Constructor]
}

Chat::~Chat()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    chatTextEditor = nullptr;
    chatEntryTextEditor = nullptr;


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

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Chat::resized()
{
    chatTextEditor->setBounds (8, 8, getWidth() - 16, getHeight() - 44);
    chatEntryTextEditor->setBounds (8, getHeight() - 8 - 16, getWidth() - 16, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void Chat::setTopic(String topic_text)
{}// TODO: this->topicLabel->setText(String("TOPIC: " + topic_text)) ; } (issue #13)

void Chat::addChatLine(String chat_user , String chat_text)
{
  this->chatTextEditor->moveCaretToEnd() ;
  this->chatTextEditor->insertTextAtCaret(chat_user + ": " + chat_text + "\n") ;
  this->chatTextEditor->moveCaretToEnd() ;
}

void Chat::textEditorReturnKeyPressed(TextEditor& a_text_editor)
{
  LinJam::SendChat(this->chatEntryTextEditor->getText()) ;
  this->chatEntryTextEditor->clear() ;
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
  </BACKGROUND>
  <TEXTEDITOR name="chatTextEditor" id="ba11ad8bfe4752c1" memberName="chatTextEditor"
              virtualName="" explicitFocusOrder="0" pos="8 8 16M 44M" textcol="ff808080"
              bkgcol="ff000000" hilitecol="0" outlinecol="0" initialText=""
              multiline="1" retKeyStartsLine="0" readonly="1" scrollbars="1"
              caret="0" popupmenu="0"/>
  <TEXTEDITOR name="chatEntryTextEditor" id="412133d948ede027" memberName="chatEntryTextEditor"
              virtualName="" explicitFocusOrder="0" pos="8 8Rr 16M 16" textcol="ff808080"
              bkgcol="ff000000" hilitecol="0" outlinecol="0" caretcol="ffffffff"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
