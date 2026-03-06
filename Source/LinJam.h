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


#pragma once

/* NOTE: the following refs require libninjam v0.07
             * function NJClient::GetLocalChannelName()
             * function audioStreamer::NewASIO()
             * function audioStreamer::NewALSA() override
             * function audioStreamer::GetASIODriverName()
             * function audioStreamer::getNInputChannels()
             * function audioStreamer::getSampleRate()
             * function audioStreamer::GetDsGuidByName()
             * function audioStreamer::GetDsNamesCSV()
             * enum     audioStreamer::WinApi
             * enum     audioStreamer::MacApi
             * enum     audioStreamer::NixApi              */
#include <ninjam/audiostream.h>
#include <ninjam/njclient.h>
#include <ninjam/njmisc.h> // VAL2DB and DB2VAL
#ifndef LIBNINJAM_VERSION
#define LIBNINJAM_VERSION_MAJ 0
#define LIBNINJAM_VERSION_MIN 07
#define LIBNINJAM_VERSION_REV 0
#define LIBNINJAM_VERSION LIBNINJAM_VERSION_MAJ.LIBNINJAM_VERSION_MIN.LIBNINJAM_VERSION_REV
#endif

#include "JuceHeader.h"
#include <array>

#include "LinJamConfig.h"
#include "MainContent.h"


/**
  LinJam is the main app controller class
  many of the view components handle their own interactions
      but most of the business eventually flows through here
*/
class LinJam
{
  friend class LinJamApplication ;
  friend class LinJamConfig ;
#if DEBUG
  friend class Trace ;
#endif // DEBUG


public:

  // state
  static void SignIn(String host_name , String login , String pass , bool is_anonymous) ;
  static void Connect() ;
  static void Disconnect() ;
  static void DisconnectNow() ;

  // getters/setters
  static ValueTree      GetCredentials(String host_name) ;
  static bool           IsAgreed() ;
  static SortedSet<int> GetFreeSources() ;
  static SortedSet<int> GetFreeSourcePairs() ;
  static uint8          GetBpi() ;
  static uint8          GetBpm() ;

  // GUI event handlers
  static bool AddLocalChannel(   ValueTree channel_store) ;
  static void RemoveLocalChannel(ValueTree channel_store) ;
  static void SendChat(          String chat_text) ;
  static void CleanSessionDir() ;


private:

  class RoomSort
  {
  public:

    static int compareElements(ValueTree a_server_store , ValueTree another_server_store)
    {
      int n_clients_a = a_server_store      .getChildWithName(CONFIG::CLIENTS_ID).getNumChildren() ;
      int n_clients_b = another_server_store.getChildWithName(CONFIG::CLIENTS_ID).getNumChildren() ;

      return (n_clients_a <  n_clients_b) ? 1 :
             (n_clients_a == n_clients_b) ? 0 : -1 ;
    }
  } ;

  // setup/teardown
  static NJClient*      Client ;
  static MainContent*   Gui ;
  static MultiTimer*    Timer ;
  static LinJamConfig*  Config ;
  static audioStreamer* Audio ;
  static String         AutoJoinHost ;
  static Value          Status ;
  static bool           IsAudioInitialized ;
  static SortedSet<int> FreeSources ;
  static SortedSet<int> FreeSourcePairs ;
  static double         GuiBeatOffset ;
  static File           SessionDir ;
  // networking (NINJAM client)
  static int            RetryLogin ;
  static String         PrevRecordingTime ;
  // update jams
  static URL            PollJamsUrl ;
  static UPTR<RoomSort> RoomSorter ;
  // logout
  static int            LogoutLoopCount ;
  // signalling
  static URL            PollSignalsUrl ;


  // setup/teardown
  static bool Initialize(NJClient*   nj_client   , MainContent*  main_content ,
                         MultiTimer* multi_timer , const String& cli_args     ) ;
  static bool PrepareSessionDirectory() ;
  static void ConfigureNinjam() ;
  static void ConfigureGui(const Identifier& a_key) ;
  static void ConfigureBlacklist() ;
  static bool InitializeAudio() ;
  static void ConfigureInitialChannels() ;
  static void Shutdown() ;
  static void Quit() ;

  // NJClient callbacks
  static int  OnLicense(int user32 , char* license_text) ;
  static void OnChatmsg(int          /*user32*/ , NJClient* /*instance*/ ,
                        const char** parms      , int       /*nparms*/   ) ;
  static void OnSamples(float** input_buffer  , int n_input_channels  ,
                        float** output_buffer , int n_output_channels ,
                        int     n_samples     , int sample_rate       ) ;

  // NJClient runtime routines and event handlers
  static void PumpClient() ;
  static void HandleTimer(   int timer_id) ;
  static void HandleTopicMsg(String chat_user , String chat_text) ;
  static void HandleBcastMsg(String chat_user , String chat_text) ;
  static void HandlePrivMsg( String chat_user , String chat_text) ;
  static void HandleJoinMsg( String chat_user) ;
  static void HandlePartMsg( String chat_user) ;
  static void HandleStatusChanged() ;
  static void HandleUserInfoChanged() ;
  static void UpdateGuiMode(Component* pane) ;
  static void UpdateGuiHighPriority() ;
  static void UpdateGuiMedPriority() ;
  static void UpdateGuiLowPriority() ;
  static void UpdateLoopProgress() ;
  static void UpdateVuMeters() ;
  static void PumpSpinner() ;
  static void UpdateJams() ;
  static void UpdateBpiBpm() ;
  static void UpdateStatus() ;
  static void UpdateRecordingTime() ;
  // static void UpdateSessionTime() ; // WIP: robust session time? Client->GetSessionPosition() and friends?
  static void WaitLogout() ;

  // NJClient configuration
  static void ConfigureAudio() ;
  static void ConfigureMasterChannel(Identifier a_key) ;
  static void ConfigureMetroChannel( Identifier a_key) ;
  static void ConfigureLocalChannel( ValueTree channel_store , Identifier a_key) ;
  static void ConfigureRemoteChannel(ValueTree user_store    ,
                                     ValueTree channel_store , Identifier a_key) ;

  // audio signal helpers
  static double AddDecibels(       double l_vu , double r_vu) ;
  static void   ComputePannedVus(  double pan , double* l_vu , double* r_vu) ;
  static void   ScalePannedMonoVus(double  vu_mono , double  pan ,
                                   double* l_vu    , double* r_vu) ;
  static float  ClientPan(         float pan , int stereo_status) ;

  // NJClient/audioStreamer helpers
  static int    GetNumAudioSources() ;
  static int    GetNumLocalChannels() ;
  // static uint8  GetNumRemoteChannels() ; // WIP: graceful disconnect - may not need
  static int    GetNumVacantChannels() ;
  static int    GetVacantLocalChannelIdx() ;
  static String GetStoredChannelName(      ValueTree channel_store) ;
  static String GetLocalChannelClientName( int channel_idx) ;
  static String GetRemoteUserName(         int user_idx) ;
  static String GetRemoteChannelClientName(int user_idx , int channel_idx) ;
  static bool   IsConfiguredChannel(       int channel_idx) ;
  static double GetChannelDb(              int channel_idx) ;
  static double GetChannelDb(              int user_idx , int channel_idx) ;
  // static bool   AreAnyXmit() ; // WIP: graceful disconnect - may not need

  // signalling
  static void SetPollUrl() ;


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinJam) ;
} ;
