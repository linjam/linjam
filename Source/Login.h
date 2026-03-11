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
  Login is the initial lobby "screen" that contains quick-login buttons
      and custom server/login credentials
                                                                    //[/Comments]
*/
class Login  : public Component,
               public TextEditor::Listener,
               public ValueTree::Listener,
               public juce::Button::Listener
{
public:
    //==============================================================================
    Login (ValueTree login_store, ValueTree servers_store);
    ~Login() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  // event handlers
  void textEditorTextChanged     (TextEditor& text_editor)                         override ;
  void valueTreeChildAdded       (ValueTree& parent_node  , ValueTree& node)       override ;
  void valueTreeChildRemoved     (ValueTree& parent_node  , ValueTree& node ,
                                  int        /*prev_idx*/                   )      override ;
  void valueTreeChildOrderChanged(ValueTree& parent_node                    ,
                                  int        /*prev_idx*/ , int /*curr_idx*/)      override ;
  void valueTreePropertyChanged  (ValueTree& /*node*/ , const Identifier& /*key*/) override {} ; // unused
  void valueTreeParentChanged    (ValueTree& /*node*/                            ) override {} ; // unused
  void valueTreeRedirected       (ValueTree& /*node*/                            ) override {} ; // unused

  // helpers
  bool quickLogin       (String host) ;
  bool signIn           () ;
  bool validateHost     () ;
  bool validateLogin    () ;
  bool validatePass     () ;
  void setTextErrorState(TextEditor* a_text_editor , bool is_error_state) ;
  void populateJamsGui  () ;
  void updateClients    (ValueTree clients_store) ;
  void layoutLoginBtns  () ;
  void AddLoginButton   (TextButton* login_button  , HyperlinkButton* stream_button ,
                         Label*      clients_label , bool             is_vacant     ) ;

    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void visibilityChanged() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree                   loginStore ;
  ValueTree                   serversStore ;
  OwnedArray<TextButton     > serverButtons ;
  OwnedArray<HyperlinkButton> streamButtons ;
  OwnedArray<Label          > clientsLabels ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::GroupComponent> activeGroup;
    std::unique_ptr<juce::Viewport> activeView;
    std::unique_ptr<juce::GroupComponent> vacantGroup;
    std::unique_ptr<juce::Viewport> vacantView;
    std::unique_ptr<juce::Label> hostLabel;
    std::unique_ptr<juce::Label> loginLabel;
    std::unique_ptr<juce::Label> passLabel;
    std::unique_ptr<juce::TextEditor> hostText;
    std::unique_ptr<juce::TextEditor> loginText;
    std::unique_ptr<juce::TextEditor> passText;
    std::unique_ptr<juce::TextButton> loginButton;
    std::unique_ptr<juce::TextButton> serverButton;
    std::unique_ptr<juce::ToggleButton> anonButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Login)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

