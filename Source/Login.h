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

#ifndef _LOGIN_H_
#define _LOGIN_H_


//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Login  : public Component,
               public TextEditor::Listener,
               public Value::Listener,
               public ButtonListener
{
public:
    //==============================================================================
    Login ();
    ~Login();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  static StringRef HostValidationMask ;
  static StringRef Letters ;
  static StringRef Digits ;
  static StringRef UrlChars ;

  OwnedArray<TextButton> loginButtons ;


  // event handlers
  void broughtToFront()                                 override ;
  void textEditorTextChanged(TextEditor& a_text_editor) override ;
  void valueChanged(         Value& login_value)        override ;

  // helpers
  void preloadState() ;
  void sortLoginButtons() ;
  void login() ;
  bool validateHost() ;
  bool validateLogin() ;
  bool validatePass() ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> hostLabel;
    ScopedPointer<Label> loginLabel;
    ScopedPointer<Label> passLabel;
    ScopedPointer<TextEditor> hostText;
    ScopedPointer<TextEditor> loginText;
    ScopedPointer<TextEditor> passText;
    ScopedPointer<TextButton> loginButton;
    ScopedPointer<TextButton> serverButton;
    ScopedPointer<ToggleButton> anonButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Login)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // _LOGIN_H_
