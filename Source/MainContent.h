
#ifndef _MAIN_CONTENT_H_
#define _MAIN_CONTENT_H_


#include "Background.h"
#include "Chat.h"
#include "Mixer.h"
#include "StatusBar.h"
#include "Loop.h"
#include "Login.h"
#include "License.h"
#include "Config.h"


/** MainContent is the main view container class */
class MainContent : public Component , public ButtonListener
{
  friend class LinJamApplication ;
  friend class LinJam ;


public:

  MainContent(DocumentWindow* main_window , TextButton* config_button) ;
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
  ScopedPointer<Config>     config ;
  DocumentWindow*           mainWindow ;
  TextButton*               configButton ;
  Value                     linjamStatus ;


  void instantiate(  ValueTree gui_store       , ValueTree client_store ,
                     ValueTree blacklist_store , ValueTree audio_store  , 
                     ValueTree login_store     , Value     linjam_status) ;
  void setTitle(     String title_text) ;
  void buttonClicked(Button* a_button) ;


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContent)
} ;

#endif // _MAIN_CONTENT_H_
