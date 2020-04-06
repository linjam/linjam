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

#ifndef _CHAT_H_
#define _CHAT_H_

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
              public ValueListener,
              public LabelListener
{
public:
    //==============================================================================
    Chat (Value font_size);
    ~Chat();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  void setTopic(   String topic_text) ;
  void addChatLine(String chat_user , String chat_text) ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void labelTextChanged (Label* labelThatHasChanged);



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
    ScopedPointer<TextEditor> chatText;
    ScopedPointer<TextEditor> chatEntryText;
    ScopedPointer<Label> topicLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Chat)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // _CHAT_H_
