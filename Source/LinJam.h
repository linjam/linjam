
#ifndef _LINJAM_H_
#define _LINJAM_H_


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

#include "JuceHeader.h"

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

  // getters/setters
  static ValueTree      GetCredentials(String host_name) ;
  static bool           IsAgreed() ;
  static SortedSet<int> GetFreeAudioSources() ;
  static SortedSet<int> GetFreeAudioSourcePairs() ;

  // GUI event handlers
  static bool AddLocalChannel(   ValueTree channel_store) ;
  static void RemoveLocalChannel(ValueTree channel_store) ;
  static void SendChat(          String chat_text) ;
  static void CleanSessionDir() ;


private:

  static NJClient*      Client ;
  static MainContent*   Gui ;
  static MultiTimer*    Timer ;
  static LinJamConfig*  Config ;
  static audioStreamer* Audio ;
  static String         AutoJoinHost ;
  static Value          Status ;
  static bool           IsAudioInitialized ;
  static SortedSet<int> FreeAudioSources ;
  static SortedSet<int> FreeAudioSourcePairs ;
  static double         GuiBeatOffset ;
  static File           SessionDir ;
  static int            RetryLogin ;
  static String         PrevRecordingTime ;


  // setup
  static bool Initialize(NJClient*   nj_client   , MainContent*  main_content ,
                         MultiTimer* multi_timer , const String& cli_args     ) ;
  static bool PrepareSessionDirectory() ;
  static void ConfigureNinjam() ;
  static void ConfigureBlacklist() ;
  static bool InitializeAudio() ;
  static void ConfigureInitialChannels() ;
  static void ConfigureGui() ;
  static void Shutdown() ;

  // NJClient callbacks
  static int  OnLicense(int user32 , char* license_text) ;
  static void OnChatmsg(int          user32 , NJClient* instance ,
                        const char** parms  , int       nparms   ) ;
  static void OnSamples(float** input_buffer  , int n_input_channels  ,
                        float** output_buffer , int n_output_channels ,
                        int     n_samples     , int sample_rate       ) ;

  // NJClient runtime routines
  static void HandleTimer(int timer_id) ;
  static void UpdateStatus() ;
  static void PumpClient() ;
  static void HandleStatusChanged() ;
  static void HandleUserInfoChanged() ;
  static void UpdateGuiHighPriority() ;
  static void UpdateGuiLowPriority() ;
  static void UpdateLoopProgress() ;
  static void UpdateVuMeters() ;
  static void UpdateRecordingTime() ;

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
  static int    GetNumVacantChannels() ;
  static int    GetVacantLocalChannelIdx() ;
  static String GetStoredChannelName(      ValueTree channel_store) ;
  static String GetLocalChannelClientName( int channel_idx) ;
  static String GetRemoteUserName(         int user_idx) ;
  static String GetRemoteChannelClientName(int user_idx , int channel_idx) ;
  static bool   IsConfiguredChannel(       int channel_idx) ;
  static double GetChannelDb(              int channel_idx) ;
  static double GetChannelDb(              int user_idx , int channel_idx) ;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinJam) ;
} ;

#endif // _LINJAM_H_
