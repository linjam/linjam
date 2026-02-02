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


// NOTE: in order to avoid "multiple definitions of WinMain()" compiler error
//         arrange that "windows.h" be included before "JuceHeader.h" in all contexts
//       also arrange to include "JuceHeader.h" before any "*Component.h"
#include "LinJam.h" // includes "windows.h" and "JuceHeader.h"
#include "Login.h"


class LinJamApplication : public JUCEApplication , NJClient , MultiTimer
{
public:

  LinJamApplication() {}

  void initialise(const String& command_line) override
  {
    this->mainWindow.reset(new MainWindow()) ;

    if (!LinJam::Initialize(this , this->mainWindow->mainContent.get() , this , command_line))
    {
      LinJam::Shutdown() ; quit() ;
    }
  }

  void anotherInstanceStarted(const String& command_line) override
  {
    // When another instance of the app is launched while this one is running,
    // this method is invoked, and the commandLine parameter tells you what
    // the other instance's command-line arguments were.
    String host = command_line ; this->mainWindow->mainContent->lobby->quickLogin(host) ;
  }

  void shutdown() override { LinJam::Shutdown() ; this->mainWindow = nullptr ; }

  void         systemRequestedQuit()        override { quit() ; }
  const String getApplicationName()         override { return ProjectInfo::projectName ; }
  const String getApplicationVersion()      override { return ProjectInfo::versionString ; }
  bool         moreThanOneInstanceAllowed() override { return false ; }


  /*
      This class implements the desktop window that contains an instance of
      our MainContentComponent class.
  */
  class MainWindow : public DocumentWindow
  {
    friend class LinJamApplication ;


  public:

    MainWindow() : DocumentWindow(GUI::APP_NAME             ,
                                  Colour(0xff202020)        ,
                                  DocumentWindow::allButtons)
    {
      // context-dependent nav button (config<->logout<->jam - managed by MainContent)
      this->modeButton.reset(new TextButton("modeButton")) ;
      Component::addAndMakeVisible(this->modeButton.get()) ;

      // main content (title managed by MainContent)
      this->mainContent.reset(new MainContent(this , this->modeButton.get())) ;
      this->mainContent->setComponentID(GUI::CONTENT_GUI_ID) ;
      setContentOwned(this->mainContent.get() , true) ;

      // this main desktop window
#ifdef _MAC
      setTitleBarButtonsRequired(DocumentWindow::allButtons , true) ;
#endif // _MAC
      setTitleBarHeight(GUI::TITLEBAR_H) ;
//      setIcon(const Image &imageToUse) ;
      centreWithSize(getWidth() , getHeight()) ;
      setVisible(true) ;
    }

    ~MainWindow()
    {
      this->modeButton  = nullptr ;
      this->mainContent = nullptr ;
    }

    void closeButtonPressed() { JUCEApplication::getInstance()->systemRequestedQuit() ; }


  private:

    UPTR<TextButton>  modeButton ;
    UPTR<MainContent> mainContent ;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
  } ;


private:

  UPTR<MainWindow> mainWindow ;


  void timerCallback(int timer_id) override { LinJam::HandleTimer(timer_id) ; }


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinJamApplication)
} ;


START_JUCE_APPLICATION(LinJamApplication)
