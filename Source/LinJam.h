/*
  ==============================================================================

    LinJam.h
    Created: 24 May 2014 5:03:01pm
    Author:  me

  ==============================================================================
*/
#ifndef _LINJAM_H_
#define _LINJAM_H_


#ifdef _WIN32
#  include "audioconfig.h" // TODO: reimplement audioconfig.cpp in this class (issue #27)
#endif // _WIN32

#include <ninjam/audiostream.h>
#include <ninjam/njclient.h>
#include <ninjam/njmisc.h>

#include "JuceHeader.h"

#include "LinJamConfig.h"
#include "MainContent.h"


class LinJam
{
#if DEBUG
  friend class Trace ;
#endif // DEBUG


  friend class LinJamConfig ;


public:

  // state methods
  static bool Initialize(NJClient*     njClient , MainContent* mainCcontent ,
                         const String& args                                 ) ;
  static void Connect() ;
  static void Disconnect() ;
  static void Shutdown() ;

  // NJClient runtime routines
  static void DriveClient() ;
  static void UpdateGuiHighPriority() ;
  static void UpdateGuiLowPriority() ;

  // getters/setters
  static bool           IsAgreed() ;
  static SortedSet<int> GetFreeInputChannels() ;
  static SortedSet<int> GetFreeInputChannelPairs() ;

  // GUI event handlers
  static bool AddLocalChannel(   ValueTree channel_store) ;
  static void RemoveLocalChannel(ValueTree channel_store) ;
  static void SendChat(String chat_text) ;

  // NJClient config helpers
  static int  GetMonoPairSourceN(     int source_n) ;
  static int  GetStereoPairSourceN(   int source_n) ;


  // persistent configuration storage
  static LinJamConfig* Config ;


private:

  static NJClient*      Client ;
  static MainContent*   Gui ;
  static audioStreamer* Audio ;
  static SortedSet<int> FreeInputChannels ;
  static SortedSet<int> FreeInputChannelPairs ;
  static bool           IsAudioEnabled ;
  static double         GuiBeatOffset ;
  static File           SessionDir ;
  static int            PrevStatus ;
  static bool           IsInitialized ;
  static String         PrevRecordingTime ;


  // NJClient callbacks
  static int  OnLicense(int user32 , char* license_text) ;
  static void OnChatmsg(int          user32 , NJClient* instance ,
                        const char** parms  , int       nparms   ) ;
  static void OnSamples(float** input_buffer  , int n_input_channels  ,
                        float** output_buffer , int n_output_channels ,
                        int     n_samples     , int sample_rate       ) ;

  // NJClient runtime helpers
  static void   HandleStatusChanged( int status) ;
  static void   HandleUserInfoChanged() ;
  static void   UpdateLoopProgress() ;
  static void   UpdateVuMeters() ;
  static void   UpdateRecordingTime() ;
  static void   HandleChatCommand(   String chat_text) ;

  // state helpers
  static bool InitializeAudio() ;
  static void ConfigureInitialChannels() ;
  static bool PrepareSessionDirectory() ;
  static void ConfigureNinjam() ;
  static void CleanSessionDir() ;

  // NJClient config helpers
  static int    GetNumActiveChannels() ;
  static int    GetNumVacantChannels() ;
  static int    GetVacantLocalChannelIdx() ;
  static String GetStoredChannelName(      ValueTree channel_store) ;
  static String GetLocalChannelClientName( int channel_idx) ;
  static String GetRemoteUserName(         int user_idx) ;
  static String GetRemoteChannelClientName(int user_idx , int channel_idx) ;
  static bool   IsConfiguredChannel(       int channel_idx) ;
  static float  ComputeStereoPan(          float pan , int stereo_status) ;
  static void   ConfigureMasterChannel(    Identifier a_key) ;
  static void   ConfigureMetroChannel(     Identifier a_key) ;
  static void   ConfigureLocalChannel(     ValueTree  channel_store , Identifier a_key) ;
  static void   ConfigureRemoteChannel(    ValueTree  user_store    ,
                                           ValueTree  channel_store , Identifier a_key) ;


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinJam) ;
} ;

#endif // _LINJAM_H_
