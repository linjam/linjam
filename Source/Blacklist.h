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

#ifndef _BLACKLIST_H_
#define _BLACKLIST_H_

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  instances of BlacklistEntry are subcomponents of the Blacklist container
  they represent an individual user on the NJClient subscriptions list
                                                                    //[/Comments]
*/
class BlacklistEntry  : public Component,
                        public Button::Listener
{
public:
    //==============================================================================
    BlacklistEntry (ValueTree blacklist_store);
    ~BlacklistEntry();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree blacklistStore ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> removeButton;
    ScopedPointer<Label> userLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlacklistEntry)
};

//[EndFile] You can add extra defines here...

/**
  Blacklist is the GUI container for BlacklistEntry instances
*/
class Blacklist : public Component , public ValueTree::Listener
{
  friend class BlacklistEntry ;


public:

  Blacklist(ValueTree blacklist_store) ;
  ~Blacklist() ;


private:

  ValueTree blacklistStore ;


  void resized() ;
  void resize() ;
  void removeBlacklistEntry(BlacklistEntry* blacklist_entry) ;
  void valueTreeChildAdded( ValueTree& parent_node , ValueTree& node) override  ;

  // unused ValueTree::Listener interface implementations
  void valueTreePropertyChanged(  ValueTree& /*node*/ , const Identifier& /*key*/)   override {} ;
  void valueTreeChildRemoved(     ValueTree& /*parent_node*/ , ValueTree& /*node*/ ,
                                  int        /*prev_idx*/                          ) override {} ;
  void valueTreeChildOrderChanged(ValueTree& /*parent_node*/ ,
                                  int        /*prev_idx*/    , int /*curr_idx*/)     override {} ;
  void valueTreeParentChanged(    ValueTree& /*node*/)                               override {} ;
  void valueTreeRedirected(       ValueTree& /*node*/)                               override {} ;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Blacklist)
} ;

//[/EndFile]

#endif // _BLACKLIST_H_
