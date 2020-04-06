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

#ifndef _LOGIN_H_
#define _LOGIN_H_

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  Login is the initial lobby "screen" that contains quick-login buttons
      and custom server/login configuration
                                                                    //[/Comments]
*/
class Login  : public Component,
               public TextEditor::Listener,
               public ValueTree::Listener,
               public ButtonListener
{
public:
    //==============================================================================
    Login (ValueTree login_store, ValueTree servers_store);
    ~Login();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  // event handlers
  void broughtToFront            ()                                             override ;
  void textEditorTextChanged     (TextEditor& a_text_editor)                    override ;
  void valueTreeChildAdded       (ValueTree& a_parent_node , ValueTree& a_node) override ;
  void valueTreeChildRemoved     (ValueTree& a_parent_node , ValueTree& a_node) override ;
  void valueTreeChildOrderChanged(ValueTree& a_parent_node)                     override ;

  // unused ValueTree::Listener interface implementations
  void valueTreePropertyChanged(ValueTree& /*a_node*/ , const Identifier& /*key*/) override {} ;
  void valueTreeParentChanged  (ValueTree& /*a_node*/                            ) override {} ;
  void valueTreeRedirected     (ValueTree& /*a_node*/                            ) override {} ;

  // helpers
  bool quickLogin       (String host) ;
  bool signIn           () ;
  bool validateHost     () ;
  bool validateLogin    () ;
  bool validatePass     () ;
  void setTextErrorState(TextEditor* a_text_editor , bool is_error_state) ;
  void updateClients    (ValueTree clients_store) ;
  void arrangeRooms     () ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree              loginStore ;
  ValueTree              serversStore ;
  OwnedArray<TextButton> serverButtons ;
  OwnedArray<Label     > clientsLabels ;

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
    ScopedPointer<GroupComponent> groupComponent;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Login)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // _LOGIN_H_
