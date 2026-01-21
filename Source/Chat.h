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
              public Value::Listener,
              public juce::Label::Listener
{
public:
    //==============================================================================
    Chat (Value font_size, Value linjam_status);
    ~Chat() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  void setTopic(   String topic_text) ;
  void addChatLine(String chat_user , String chat_text) ;

    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void labelTextChanged (juce::Label* labelThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree guiStore ;
  Value     fontSize ;
  String    prevTopicText ;


  void valueChanged(              Value& a_value)            override ;
  void textEditorReturnKeyPressed(TextEditor& a_text_editor) override ;
  void setFontSize() ;
  int  getFontSize() ;
  bool shouldShowTopic() ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::TextEditor> chatText;
    std::unique_ptr<juce::Label> topicLabel;
    std::unique_ptr<juce::TextEditor> chatEntryText;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Chat)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
