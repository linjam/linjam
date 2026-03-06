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


#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  Chat is a sub-section of the main jam "screen"
  it displays incoming chat text and handles outgoing chat entry
                                                                    //[/Comments]
*/
class Chat  : public Component,
              public TextEditor::Listener,
              public Value::Listener
{
public:
    //==============================================================================
    Chat (Value font_size, Value linjam_status);
    ~Chat() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  void addChatLine(String chat_user , String chat_text) ;
  void grabFocus  () ;

    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void visibilityChanged() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  Value fontSize ;
  Value linjamStatus ;


  void valueChanged              (Value& a_value)            override ;
  void textEditorEscapeKeyPressed(TextEditor& a_text_editor) override ;
  void textEditorReturnKeyPressed(TextEditor& a_text_editor) override ;

  void   setFontSize() ;
  int    getFontSize() ;
  bool   shouldShowTopic() ;
  String timestamp() ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::TextEditor> chatText;
    std::unique_ptr<juce::TextEditor> chatEntryText;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Chat)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

