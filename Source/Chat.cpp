/*\
|*|  Copyright 2014,2015,2020,2026 bill-auger <bill-auger@programmer.net>
|*|
|*|  This file is part of the LinJam program.
|*|
|*|  LinJam is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  LinJam is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU General Public License for more details.
|*|
|*|  You should have received a copy of the GNU General Public License
|*|  along with LinJam.  If not, see <http://www.gnu.org/licenses/>.
\*/


//[Headers] You can add your own extra header files here...

#include "LinJam.h"
#include "./Trace/TraceChat.h"

//[/Headers]

#include "Chat.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Chat::Chat (Value font_size, Value linjam_status)
    : fontSize(font_size) , linjamStatus(linjam_status)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    setName ("Chat");
    chatText.reset (new juce::TextEditor ("chatText"));
    addAndMakeVisible (chatText.get());
    chatText->setMultiLine (true);
    chatText->setReturnKeyStartsNewLine (false);
    chatText->setReadOnly (true);
    chatText->setScrollbarsShown (true);
    chatText->setCaretVisible (false);
    chatText->setPopupMenuEnabled (true);
    chatText->setColour (juce::TextEditor::textColourId, juce::Colours::grey);
    chatText->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    chatText->setColour (juce::TextEditor::highlightColourId, juce::Colour (0x00000000));
    chatText->setColour (juce::TextEditor::outlineColourId, juce::Colour (0x00000000));
    chatText->setText (juce::String());

    chatEntryText.reset (new juce::TextEditor ("chatEntryText"));
    addAndMakeVisible (chatEntryText.get());
    chatEntryText->setExplicitFocusOrder (1);
    chatEntryText->setMultiLine (false);
    chatEntryText->setReturnKeyStartsNewLine (false);
    chatEntryText->setReadOnly (false);
    chatEntryText->setScrollbarsShown (false);
    chatEntryText->setCaretVisible (true);
    chatEntryText->setPopupMenuEnabled (true);
    chatEntryText->setColour (juce::TextEditor::textColourId, juce::Colours::grey);
    chatEntryText->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    chatEntryText->setColour (juce::TextEditor::highlightColourId, juce::Colour (0x00000000));
    chatEntryText->setColour (juce::TextEditor::outlineColourId, juce::Colour (0x00000000));
    chatEntryText->setColour (juce::CaretComponent::caretColourId, juce::Colours::white);
    chatEntryText->setText (juce::String());

    //[UserPreSize]

  // set fonts and sizes
  Font chat_font = Font(Font::getDefaultMonospacedFontName() , 16.00f, Font::plain) ;
  this->chatText->setFont(chat_font) ;
  setFontSize() ;

    //[/UserPreSize]

    setSize (622, 138);


    //[Constructor] You can add your own custom stuff here..

  // set text editor colors
  this->chatEntryText->setColour(CaretComponent::caretColourId       , GUI::TEXT_CARET_COLOR   ) ;
  this->chatText     ->setColour(TextEditor::textColourId            , GUI::CHAT_TEXT_COLOR    ) ;
  this->chatEntryText->setColour(TextEditor::textColourId            , GUI::CHAT_TEXT_COLOR    ) ;
  this->chatText     ->setColour(TextEditor::highlightColourId       , GUI::TEXT_HILITEBG_COLOR) ;
  this->chatEntryText->setColour(TextEditor::highlightColourId       , GUI::TEXT_HILITEBG_COLOR) ;
  this->chatText     ->setColour(TextEditor::highlightedTextColourId , GUI::TEXT_HILITE_COLOR  ) ;
  this->chatEntryText->setColour(TextEditor::highlightedTextColourId , GUI::TEXT_HILITE_COLOR  ) ;
  this->chatText     ->setColour(TextEditor::outlineColourId         , GUI::CHAT_OUTLINE_COLOR ) ;
  this->chatEntryText->setColour(TextEditor::outlineColourId         , GUI::CHAT_OUTLINE_COLOR ) ;
  this->chatText     ->setColour(TextEditor::focusedOutlineColourId  , GUI::CHAT_FOCUS_COLOR   ) ;
  this->chatEntryText->setColour(TextEditor::focusedOutlineColourId  , GUI::CHAT_FOCUS_COLOR   ) ;
  this->chatText     ->setColour(TextEditor::shadowColourId          , GUI::CHAT_SHADOW_COLOR  ) ;
  this->chatEntryText->setColour(TextEditor::shadowColourId          , GUI::CHAT_SHADOW_COLOR  ) ;
  this->chatText     ->setColour(TextEditor::backgroundColourId      , GUI::CHAT_TEXT_BG_COLOR ) ;
  this->chatEntryText->setColour(TextEditor::backgroundColourId      , GUI::CHAT_TEXT_BG_COLOR ) ;

  this->chatEntryText->setSelectAllWhenFocused(true) ;
  this->chatEntryText->setTextToShowWhenEmpty(GUI::CHAT_PROMPT_TEXT , GUI::TEXT_EMPTY_COLOR) ;
  this->chatEntryText->setInputRestrictions(1024) ;

  // local event handlers
  this->fontSize      .addListener(this) ;
  this->linjamStatus  .addListener(this) ;
  this->chatEntryText->addListener(this) ;

    //[/Constructor]
}

Chat::~Chat()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    chatText = nullptr;
    chatEntryText = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Chat::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..

#define JUCER_DRAW_CHAT_PAINT
#ifdef JUCER_DRAW_CHAT_PAINT

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

    {
        float x = 4.0f, y = 4.0f, width = static_cast<float> (getWidth() - 8), height = static_cast<float> (getHeight() - 36);
        juce::Colour fillColour = juce::Colours::black;
        juce::Colour strokeColour = juce::Colours::grey;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.000f);
    }

    {
        float x = 4.0f, y = static_cast<float> (getHeight() - 28), width = static_cast<float> (getWidth() - 8), height = 24.0f;
        juce::Colour fillColour = juce::Colours::black;
        juce::Colour strokeColour = juce::Colours::grey;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.000f);
    }

    //[UserPaint] Add your own custom painting code here..

#else // JUCER_DRAW_CHAT_PAINT

  UNUSED(g) ;


  float chat_pane_w         = static_cast<float>(getWidth()) ;
  float chat_pane_h         = static_cast<float>(getHeight()) ;
  float font_size           = static_cast<float>(getFontSize()) ;
  float chat_entry_h        = font_size                   + GUI::CHAT_ENTRY_PADH ;
  float chat_entry_y        = chat_pane_h  - chat_entry_h - GUI::PAD2F ;
  float chat_entry_border_y = chat_entry_y                - GUI::PADF ;
  float chat_h              = chat_entry_y                - GUI::PAD5F ;
  float chat_border_w       = chat_pane_w                 - GUI::CHAT_BORDER_PADW ;
  float chat_border_h       = chat_h                      + GUI::PAD2F ;
  float chat_entry_border_h = chat_entry_h                + GUI::PAD2F ;

  Colour panel_background_color = GUI::BACKGROUND_L1_COLOR ;
  Colour panel_border_color     = GUI::BORDER_L1_COLOR ;
  Colour chat_background_color  = GUI::BACKGROUND_LTOP_COLOR ;
  Colour chat_border_color      = GUI::BORDER_L2_COLOR ;

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

  // chat entry border and fill
  g.setColour(chat_background_color) ;
  g.fillRoundedRectangle(GUI::CHAT_BORDER_X  , chat_entry_border_y , chat_border_w ,
                         chat_entry_border_h , GUI::BORDER_RADIUS                  ) ;
  g.setColour(chat_border_color) ;
  g.drawRoundedRectangle(GUI::CHAT_BORDER_X  , chat_entry_border_y , chat_border_w ,
                         chat_entry_border_h , GUI::BORDER_RADIUS  , GUI::BORDER_PX) ;

#endif // JUCER_DRAW_CHAT_PAINT

    //[/UserPaint]
}

void Chat::resized()
{
    //[UserPreResize] Add your own custom resize code here..

#define JUCER_DRAW_CHAT_RESIZED
#ifdef JUCER_DRAW_CHAT_RESIZED

    //[/UserPreResize]

    chatText->setBounds (8, 8, getWidth() - 16, getHeight() - 44);
    chatEntryText->setBounds (8, getHeight() - 24, getWidth() - 16, 16);
    //[UserResized] Add your own custom resize handling here..

#else // JUCER_DRAW_CHAT_RESIZED

  int chat_x       = GUI::CHAT_X
  int chat_y       = GUI::CHAT_WITH_TOPIC_Y ;
  int chat_entry_x = GUI::CHAT_X ;
  int chat_entry_h = getFontSize()                + GUI::CHAT_ENTRY_PADH ;
  int chat_entry_y = getHeight()   - chat_entry_h - GUI::CHAT_ENTRY_PADY ;
  int chat_w       = getWidth()                   - GUI::CHAT_PADW ;
  int chat_h       = chat_entry_y  - chat_y       - GUI::CHAT_PADH ;

  // resize components according to font size
  this->chatText     ->setBounds(chat_x       , chat_y       , chat_w , chat_h      ) ;
  this->chatEntryText->setBounds(chat_entry_x , chat_entry_y , chat_w , chat_entry_h) ;

  repaint() ;

#endif // JUCER_DRAW_CHAT_RESIZED

    //[/UserResized]
}


//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* Chat public instance methods */

void Chat::addChatLine(String chat_user , String chat_text)
{
  this->chatText->moveCaretToEnd() ;
  this->chatText->insertTextAtCaret(chat_user + ": " + chat_text + "\n") ;
  this->chatText->moveCaretToEnd() ;
}


/* Chat private instance methods */

/* event handlers */

void Chat::valueChanged(Value& a_value)
{
  if      (a_value.refersToSameSourceAs(this->fontSize    )) setFontSize() ;
  else if (a_value.refersToSameSourceAs(this->linjamStatus))
  {
    if (this->linjamStatus == APP::NJC_STATUS_PRECONNECT) this->chatText->clear() ;
  }
}

void Chat::textEditorReturnKeyPressed(TextEditor& a_text_editor)
{
  if (&a_text_editor != this->chatEntryText.get()) return ;

  LinJam::SendChat(this->chatEntryText->getText()) ;
  this->chatEntryText->clear() ;
}


/* helpers */

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
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Chat" componentName="Chat"
                 parentClasses="public Component, public TextEditor::Listener, public ValueListener"
                 constructorParams="Value font_size, Value linjam_status" variableInitialisers="fontSize(font_size) , linjamStatus(linjam_status)"
                 snapPixels="8" snapActive="0" snapShown="0" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="622" initialHeight="138">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10.0" fill="solid: ff101010" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <ROUNDRECT pos="4 4 8M 36M" cornerSize="10.0" fill="solid: ff000000" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ff808080"/>
    <ROUNDRECT pos="4 28R 8M 24" cornerSize="10.0" fill="solid: ff000000" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ff808080"/>
  </BACKGROUND>
  <TEXTEDITOR name="chatText" id="ba11ad8bfe4752c1" memberName="chatText" virtualName=""
              explicitFocusOrder="0" pos="8 8 16M 44M" textcol="ff808080" bkgcol="0"
              hilitecol="0" outlinecol="0" initialText="" multiline="1" retKeyStartsLine="0"
              readonly="1" scrollbars="1" caret="0" popupmenu="1"/>
  <TEXTEDITOR name="chatEntryText" id="412133d948ede027" memberName="chatEntryText"
              virtualName="" explicitFocusOrder="1" pos="8 24R 16M 16" textcol="ff808080"
              bkgcol="0" hilitecol="0" outlinecol="0" caretcol="ffffffff" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

