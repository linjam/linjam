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

#ifndef __JUCE_HEADER_C8CF85E1A55C1DDD__
#define __JUCE_HEADER_C8CF85E1A55C1DDD__

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
class Subscription  : public Component,
                      public ButtonListener
{
public:
    //==============================================================================
    Subscription (ValueTree config_store);
    ~Subscription();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree configStore ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> userLabel;
    ScopedPointer<TextButton> removeButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Subscription)
};

//[EndFile] You can add extra defines here...

/**
  this is the GUI container for Subscription instances                                                                  //[/Comments]
*/
class Subscriptions : public Component
{
  friend class Subscription ;

public:
  Subscriptions(ValueTree config_store) ;
  ~Subscriptions() ;


private:

  void resized() ;
  int computeHeight() ;
  void removeSubscription(Subscription* a_subscription) ;


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Subscriptions)
} ;

//[/EndFile]

#endif   // __JUCE_HEADER_C8CF85E1A55C1DDD__
