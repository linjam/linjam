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
                        public ButtonListener
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
  void removeBlacklistEntry(BlacklistEntry* a_blacklist_entry) ;
  void valueTreeChildAdded( ValueTree& a_parent_node , ValueTree& a_node) override  ;

  // unused ValueTree::Listener interface implementations
  void valueTreePropertyChanged(  ValueTree& a_node , const Identifier& a_key)  override { UNUSED(a_node) ;        UNUSED(a_key) ;  } ;
  void valueTreeChildRemoved(     ValueTree& a_parent_node , ValueTree& a_node) override { UNUSED(a_parent_node) ; UNUSED(a_node) ; } ;
  void valueTreeChildOrderChanged(ValueTree& a_parent_node)                     override { UNUSED(a_parent_node) ;                  } ;
  void valueTreeParentChanged(    ValueTree& a_node)                            override { UNUSED(a_node) ;                         } ;
  void valueTreeRedirected(       ValueTree& a_node)                            override { UNUSED(a_node) ;                         } ;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Blacklist)
} ;

//[/EndFile]

#endif // _BLACKLIST_H_
