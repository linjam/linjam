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

#include "LinJam.h"
#include "./Trace/TraceChat.h"

//[/Headers]

#include "Chat.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Chat::Chat (Value font_size) : fontSize(font_size)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

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

  // set fonts and sizes
  Font  topic_font    = this->topicLabel->getFont().withHeight(GUI::TOPIC_FONT_H) ;
  this->prevTopicText = String::empty ;
  this->topicLabel->setFont(topic_font) ;
  setFontSize() ;

    //[/UserPreSize]

    setSize (622, 162);

    //[Constructor] You can add your own custom stuff here..

  // set text editor colors
  this->topicLabel   ->setColour(Label::backgroundColourId           , GUI::CHAT_TEXT_BG_COLOR ) ;
  this->topicLabel   ->setColour(Label::textColourId                 , GUI::TOPIC_TEXT_COLOR   ) ;
  this->topicLabel   ->setColour(Label::outlineColourId              , Colour(0xffff0000));//GUI::CHAT_OUTLINE_COLOR ) ;
  this->topicLabel   ->setColour(CaretComponent::caretColourId       , GUI::TEXT_CARET_COLOR   ) ;
  this->chatEntryText->setColour(CaretComponent::caretColourId       , GUI::TEXT_CARET_COLOR   ) ;
  this->topicLabel   ->setColour(TextEditor::textColourId            , GUI::CHAT_TEXT_COLOR    ) ;
  this->chatText     ->setColour(TextEditor::textColourId            , GUI::CHAT_TEXT_COLOR    ) ;
  this->chatEntryText->setColour(TextEditor::textColourId            , GUI::CHAT_TEXT_COLOR    ) ;
  this->topicLabel   ->setColour(TextEditor::highlightColourId       , GUI::TEXT_HILITEBG_COLOR) ;
  this->chatText     ->setColour(TextEditor::highlightColourId       , GUI::TEXT_HILITEBG_COLOR) ;
  this->chatEntryText->setColour(TextEditor::highlightColourId       , GUI::TEXT_HILITEBG_COLOR) ;
  this->topicLabel   ->setColour(TextEditor::highlightedTextColourId , GUI::TEXT_HILITE_COLOR  ) ;
  this->chatText     ->setColour(TextEditor::highlightedTextColourId , GUI::TEXT_HILITE_COLOR  ) ;
  this->chatEntryText->setColour(TextEditor::highlightedTextColourId , GUI::TEXT_HILITE_COLOR  ) ;
  this->topicLabel   ->setColour(TextEditor::outlineColourId         , GUI::CHAT_OUTLINE_COLOR ) ;
  this->chatText     ->setColour(TextEditor::outlineColourId         , GUI::CHAT_OUTLINE_COLOR ) ;
  this->chatEntryText->setColour(TextEditor::outlineColourId         , GUI::CHAT_OUTLINE_COLOR ) ;
  this->topicLabel   ->setColour(TextEditor::focusedOutlineColourId  , GUI::CHAT_FOCUS_COLOR   ) ;
  this->chatText     ->setColour(TextEditor::focusedOutlineColourId  , GUI::CHAT_FOCUS_COLOR   ) ;
  this->chatEntryText->setColour(TextEditor::focusedOutlineColourId  , GUI::CHAT_FOCUS_COLOR   ) ;
  this->topicLabel   ->setColour(TextEditor::shadowColourId          , GUI::CHAT_SHADOW_COLOR  ) ;
  this->chatText     ->setColour(TextEditor::shadowColourId          , GUI::CHAT_SHADOW_COLOR  ) ;
  this->chatEntryText->setColour(TextEditor::shadowColourId          , GUI::CHAT_SHADOW_COLOR  ) ;
  this->topicLabel   ->setColour(TextEditor::backgroundColourId      , GUI::CHAT_TEXT_BG_COLOR ) ;
  this->chatText     ->setColour(TextEditor::backgroundColourId      , GUI::CHAT_TEXT_BG_COLOR ) ;
  this->chatEntryText->setColour(TextEditor::backgroundColourId      , GUI::CHAT_TEXT_BG_COLOR ) ;

  this->chatText     ->setPopupMenuEnabled(true) ;
  this->chatEntryText->setPopupMenuEnabled(true) ;
  this->chatEntryText->setSelectAllWhenFocused(true) ;
  this->chatEntryText->setTextToShowWhenEmpty(GUI::CHAT_PROMPT_TEXT , GUI::TEXT_EMPTY_COLOR) ;
  this->chatEntryText->setInputRestrictions(1024) ;

  // local event handlers
  this->fontSize      .addListener(this) ;
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
#ifdef DRAW_JUCER_BORDERS
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
#endif // DRAW_JUCER_BORDERS

  bool  should_show_topic   = shouldShowTopic() ;
  float chat_pane_w         = static_cast<float>(getWidth()) ;
  float chat_pane_h         = static_cast<float>(getHeight()) ;
  float font_size           = static_cast<float>(getFontSize()) ;
  float chat_entry_h        = font_size                   + GUI::CHAT_ENTRY_PADH ;
  float chat_entry_y        = chat_pane_h  - chat_entry_h - GUI::PAD2F ;
  float chat_entry_border_y = chat_entry_y                - GUI::PADF ;
  float chat_h              = chat_entry_y                - GUI::PAD5F ;
  float topic_border_w      = chat_pane_w                 - GUI::TOPIC_BORDER_PADW ;
  float chat_border_w       = chat_pane_w                 - GUI::CHAT_BORDER_PADW ;
  float chat_border_h       = chat_h                      + GUI::PAD2F ;
  float chat_entry_border_h = chat_entry_h                + GUI::PAD2F ;

  Colour panel_background_color = GUI::BACKGROUND_L1_COLOR ;
  Colour panel_border_color     = GUI::BORDER_L1_COLOR ;
  Colour chat_background_color  = GUI::BACKGROUND_LTOP_COLOR ;
  Colour chat_border_color      = GUI::BORDER_L2_COLOR ;
  Colour topic_background_color = (should_show_topic) ? GUI::BACKGROUND_L1_COLOR :
                                                        chat_background_color    ;
  Colour topic_border_color     = (should_show_topic) ? GUI::BORDER_L3_COLOR  :
                                                        chat_background_color ;

  // chat panel border and fill
  g.setColour(panel_background_color) ;
  g.fillRoundedRectangle(GUI::CHAT_PANE_BORDER_X , GUI::CHAT_PANE_BORDER_Y , chat_pane_w ,
                         chat_pane_h             , GUI::BORDER_RADIUS                    ) ;
  g.setColour(panel_border_color) ;
  g.drawRoundedRectangle(GUI::CHAT_PANE_BORDER_X , GUI::CHAT_PANE_BORDER_Y , chat_pane_w   ,
                         chat_pane_h             , GUI::BORDER_RADIUS      , GUI::BORDER_PX) ;

  // chat border and fill
  g.setColour(chat_background_color) ;
  g.fillRoundedRectangle(GUI::CHAT_BORDER_X , GUI::CHAT_BORDER_Y , chat_border_w ,
                         chat_border_h      , GUI::BORDER_RADIUS                 ) ;
  g.setColour(chat_border_color) ;
  g.drawRoundedRectangle(GUI::CHAT_BORDER_X , GUI::CHAT_BORDER_Y , chat_border_w ,
                         chat_border_h      , GUI::BORDER_RADIUS , GUI::BORDER_PX) ;

  // topic border and fill
  g.setColour(topic_background_color) ;
  g.fillRoundedRectangle(GUI::TOPIC_BORDER_X , GUI::TOPIC_BORDER_Y , topic_border_w ,
                         GUI::TOPIC_BORDER_H , GUI::BORDER_RADIUS                   ) ;
  g.setColour(topic_border_color) ;
  g.drawRoundedRectangle(GUI::TOPIC_BORDER_X , GUI::TOPIC_BORDER_Y , topic_border_w ,
                         GUI::TOPIC_BORDER_H , GUI::BORDER_RADIUS  , GUI::BORDER_PX ) ;

  // chat entry border and fill
  g.setColour(chat_background_color) ;
  g.fillRoundedRectangle(GUI::CHAT_BORDER_X  , chat_entry_border_y , chat_border_w ,
                         chat_entry_border_h , GUI::BORDER_RADIUS                  ) ;
  g.setColour(chat_border_color) ;
  g.drawRoundedRectangle(GUI::CHAT_BORDER_X  , chat_entry_border_y , chat_border_w ,
                         chat_entry_border_h , GUI::BORDER_RADIUS  , GUI::BORDER_PX) ;

    //[/UserPaint]
}

void Chat::resized()
{
    //[UserPreResize] Add your own custom resize code here..
#ifdef DRAW_JUCER_CHAT_RESIZE
    //[/UserPreResize]

    chatText->setBounds (8, 8, getWidth() - 16, getHeight() - 44);
    chatEntryText->setBounds (8, getHeight() - 24, getWidth() - 16, 16);
    topicLabel->setBounds (8, 10, getWidth() - 16, 16);
    //[UserResized] Add your own custom resize handling here..
#endif // DRAW_JUCER_CHAT_RESIZE

  bool should_show_topic = shouldShowTopic() ;
  int  chat_y            = ((should_show_topic) ? GUI::CHAT_WITH_TOPIC_Y : GUI::CHAT_Y) ;
  int  chat_entry_h      = getFontSize()                + GUI::CHAT_ENTRY_PADH ;
  int  chat_entry_y      = getHeight()   - chat_entry_h - GUI::CHAT_ENTRY_PADY ;
  int  chat_w            = getWidth()                   - GUI::CHAT_PADW ;
  int  chat_h            = chat_entry_y  - chat_y       - GUI::CHAT_PADH ;
  int  topic_w           = getWidth()                   - GUI::TOPIC_PADW ;

  // resize components according to topic visibility and font size
  this->topicLabel   ->setVisible(should_show_topic) ;
  this->topicLabel   ->setBounds(GUI::TOPIC_X , GUI::TOPIC_Y , topic_w , GUI::TOPIC_H);
  this->chatText     ->setBounds(GUI::CHAT_X  , chat_y       , chat_w  , chat_h      ) ;
  this->chatEntryText->setBounds(GUI::CHAT_X  , chat_entry_y , chat_w  , chat_entry_h) ;

  repaint() ;

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

/* Chat public instance methods */

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


/* Chat private instance methods */

void Chat::valueChanged(Value& a_value)
{
  if (a_value.refersToSameSourceAs(this->fontSize)) setFontSize() ;
}

void Chat::textEditorReturnKeyPressed(TextEditor& a_text_editor)
{
  if (&a_text_editor != this->chatEntryText)  return ;

  LinJam::SendChat(this->chatEntryText->getText()) ;
  this->chatEntryText->clear() ;
}

void Chat::setFontSize()
{
DEBUG_TRACE_SET_FONTSIZE

  Font current_font  = this->chatText->getFont() ;
  int  new_font_size = getFontSize() ;
  Font new_font      = current_font.withHeight(new_font_size) ;

  this->chatText     ->applyFontToAllText(new_font) ;
  this->chatEntryText->applyFontToAllText(new_font) ;
  resized() ;
}

int Chat::getFontSize()
{
  int font_size_n = int(this->fontSize.getValue()) ;
  int font_size   = GUI::FONT_SIZES[font_size_n].getIntValue() ;

  return font_size ;
}

bool Chat::shouldShowTopic() { return (getHeight() > GUI::MIN_SHOW_TOPIC_CHAT_H) ; }

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
