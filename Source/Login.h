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
      and custom server/login configuration
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
  void broughtToFront            ()                                           override ;
  void textEditorTextChanged     (TextEditor& text_editor)                    override ;
  void valueTreeChildAdded       (ValueTree& parent_node  , ValueTree& node)  override ;
  void valueTreeChildRemoved     (ValueTree& parent_node  , ValueTree& node ,
                                  int        /*prev_idx*/                   ) override ;
  void valueTreeChildOrderChanged(ValueTree& parent_node  ,
                                  int        /*prev_idx*/ , int /*curr_idx*/) override ;

  // unused ValueTree::Listener interface implementations
  void valueTreePropertyChanged(ValueTree& /*node*/ , const Identifier& /*key*/) override {} ;
  void valueTreeParentChanged  (ValueTree& /*node*/                            ) override {} ;
  void valueTreeRedirected     (ValueTree& /*node*/                            ) override {} ;

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

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree              loginStore ;
  ValueTree              serversStore ;
  OwnedArray<TextButton> serverButtons ;
  OwnedArray<Label     > clientsLabels ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> hostLabel;
    std::unique_ptr<juce::Label> loginLabel;
    std::unique_ptr<juce::Label> passLabel;
    std::unique_ptr<juce::TextEditor> hostText;
    std::unique_ptr<juce::TextEditor> loginText;
    std::unique_ptr<juce::TextEditor> passText;
    std::unique_ptr<juce::TextButton> loginButton;
    std::unique_ptr<juce::TextButton> serverButton;
    std::unique_ptr<juce::ToggleButton> anonButton;
    std::unique_ptr<juce::GroupComponent> groupComponent;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Login)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

