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
#include "Config.h"


/** this is the main GUI container class */
class MainContent : public Component , public ButtonListener
{
  friend class LinJam ;


public:

  MainContent(DocumentWindow* main_window , TextButton* config_button) ;
  ~MainContent() ;

  void paint(Graphics&) ;
  void resized() ;
  void showConfig() ;


private:

  ScopedPointer<Background> background ;
  ScopedPointer<Login>      login ;
  ScopedPointer<License>    license ;
  ScopedPointer<Chat>       chat ;
  ScopedPointer<Mixer>      mixer ;
  ScopedPointer<StatusBar>  statusbar ;
  ScopedPointer<Loop>       loop ;
  ScopedPointer<Config>     config ;
  DocumentWindow*           mainWindow ;
  TextButton*               configButton ;


  void buttonClicked(    Button* a_button) ;
  void instantiateConfig(ValueTree audio_store         , ValueTree client_store ,
                         ValueTree subscriptions_store                          ) ;
  void setTitle(         String title_text) ;


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContent)
} ;

#endif // _MAIN_CONTENT_H_
