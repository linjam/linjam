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

#include "Trace.h"
#include "LinJamConfig.h"
#include "MainContent.h"


class LinJam
{
  friend class LinJamConfig ;


public:

  // state methods
  static bool Initialize(NJClient* client , MainContent* mainContent , const String& args) ;
  static void Connect() ;
  static void Disconnect() ;
  static void Shutdown() ;

  // NJClient runtime routines
  static void DriveClient() ;
  static void UpdateGUI() ;

  // getters/setters
  static bool IsAgreed() ;

  // helpers
  static void AddLocalChannel(   String channel_name) ;
  static void RemoveLocalChannel(Identifier channel_id) ;
  static void SendChat(          String chat_text) ;


  static LinJamConfig* Config ;


private:

  static NJClient*      Client ;
  static MainContent*   Gui ;
  static audioStreamer* Audio ;
  static float          GuiBeatOffset ;
  static File           SessionDir ;
  static int            PrevStatus ;
  static bool           IsAudioEnabled ;


  // NJClient callbacks
  static int  OnLicense(int user32            , char* license_text) ;
  static void OnChatmsg(int user32            , NJClient* instance ,
                        const char** parms    , int nparms)        ;
  static void OnSamples(float** input_buffer  , int n_input_channels  ,
                        float** output_buffer , int n_output_channels ,
                        int n_samples         , int sample_rate)      ;


  // NJClient runtime helpers
  static void HandleStatusChanged(int status) ;
  static void HandleUserInfoChanged() ;
  static bool IsRoomFull() ;

  // helpers
  static bool  InitializeAudio() ;
  static void  ConfigureAudio() ;
  static bool  PrepareSessionDirectory() ;
  static void  ConfigureNinjam() ;
  static void  CleanSessionDir() ;
  static void  HandleChatCommand(    String chat_text) ;
  static char* GetChannelName(       int channel_idx) ;
  static int   GetVacantLocalChannelIdx() ;
  static int   GetLocalChannelIdx(   Identifier channel_id) ;
  static int   GetRemoteUserIdx(     Identifier user_id) ;
  static int   GetRemoteChannelIdx(  int user_idx , Identifier channel_id) ;
  static void  ConfigureLocalChannel(Identifier channel_id                               ,
                                     bool should_set_name     , bool should_set_volume   ,
                                     bool should_set_pan      , bool should_set_is_xmit  ,
                                     bool should_set_is_muted , bool should_set_is_solo  ,
                                     bool should_set_source_n , bool should_set_is_stereo) ;
  static void ConfigureRemoteUser(   int  user_idx                             ,
                                     bool should_set_volume   , float  volume  ,
                                     bool should_set_pan      , float  pan     ,
                                     bool should_set_is_muted , bool   is_muted) ;
  static void ConfigureRemoteChannel(int  user_idx             , int    channel_idx  ,
                                     bool should_set_volume    , float  volume       ,
                                     bool should_set_pan       , float  pan          ,
                                     bool should_set_is_rcv    , bool   is_rcv       ,
                                     bool should_set_is_muted  , bool   is_muted     ,
                                     bool should_set_is_solo   , bool   is_solo      ,
                                     bool should_set_sink_n    , int    sink_n       ,
                                     bool should_set_is_stereo , bool   is_stereo    ) ;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinJam) ;
} ;

#endif // _LINJAM_H_
