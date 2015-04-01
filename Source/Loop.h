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

#ifndef _LOOP_H_
#define _LOOP_H_

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  Loop is the interval progress indicator in the statusbar
                                                                    //[/Comments]
*/
class Loop  : public Component
{
public:
    //==============================================================================
    Loop ();
    ~Loop();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  void updateBeatN(int beat_n) ;


  double loopProgress ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ProgressBar> progressBar;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Loop)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // _LOOP_H_
