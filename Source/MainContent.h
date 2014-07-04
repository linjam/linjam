/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef _MAIN_CONTENT_H_
#define _MAIN_CONTENT_H_


#include "JuceHeader.h"

#include "Background.h"
#include "Login.h"
#include "License.h"
#include "Chat.h"
#include "Mixer.h"
#include "StatusBar.h"
#include "Loop.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

class MainContent : public Component
{
  friend class LinJam ;


public:
  //==============================================================================
  MainContent(DocumentWindow* main_window) ;
  ~MainContent() ;

  void paint(Graphics&) ;
  void resized() ;


private:

  ScopedPointer<Background> background ;
  ScopedPointer<Login>      login ;
  ScopedPointer<License>    license ;
  ScopedPointer<Chat>       chat ;
  ScopedPointer<Mixer>      mixer ;
  ScopedPointer<StatusBar>  statusbar ;
  ScopedPointer<Loop>       loop ;


  DocumentWindow* mainWindow ;
  String          appName ;


  void setTitle(String title_text) ;

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContent)
} ;

#endif // _MAIN_CONTENT_H_
