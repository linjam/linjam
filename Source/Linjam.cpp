/*
  ==============================================================================

    Linjam.cpp
    Created: 24 May 2014 5:03:01pm
    Author:  me

  ==============================================================================
*/

#include "Constants.h"
#include "Linjam.h"
#include "Trace.h"


/* NJClient globals */

int  (*licensecallback)(      int user32 , char* licensetext) ;
void (*audiostream_onsamples)(float** in_buffer , int in_n_channels ,
                              float** out_buffer , int out_n_channels ,
                              int len , int sample_rate) ;
void (*chatmsg_cb)(int user32 , NJClient* instance , const char** parms , int nparms) ;
/*
int licensecallback(int user32 , char* licensetext)
{
DBG("LinJam::licensecallback() license_text=\n" + String(licensetext)) ;
}
void audiostream_onsamples(float** in_buffer , int in_n_channels ,
                              float** out_buffer , int out_n_channels ,
                              int len , int sample_rate)
{}
void chatmsg_cb(int user32 , NJClient* instance , const char** parms , int nparms)
{
DBG("LinJam::chatmsg_cb()\n") ;
}
*/
/*
void (*audiostream_onunder)() ;
void (*audiostream_onover)() ;
*/
// audioStreamer* Audio  ; // TODO: unused
// NJClient*      Client ; // TODO: unused


/* LinJam public class variables */

bool LinJam::IsAgreed = false ;


/* LinJam private class variables */

audioStreamer*        LinJam::Audio  = nullptr ; // Initialize()
NJClient*             LinJam::Client = nullptr ; // Initialize()
MainContentComponent* LinJam::Gui    = nullptr ; // Initialize()

bool   LinJam::ShouldAutoJoin = false ; // TODO: persistent config
String LinJam::Server         = "" ;    // TODO: persistent config
String LinJam::Login          = "" ;    // TODO: persistent config per Server
String LinJam::Pass           = ""  ;   // TODO: persistent config per Server
bool   LinJam::IsAnonymous    = true ;  // TODO: persistent config per Server
bool   LinJam::ShouldAgree    = false ; // TODO: persistent config per Server


/* LinJam public class methods */

int LinJam::Initialize(NJClient* client , MainContentComponent* contentComponent ,
                       const String& args)
{
DEBUG_TRACE_LINJAM_INIT

  Client = client ;
  Gui    = contentComponent ;

  // audio config defaults
//  int    audio_enable           = 0 ;
  int    save_local_audio       = 0 ;
  int    mac_n_input_channels   = 2 ;
  int    mac_sample_rate        = 48000 ;
  int    mac_bit_depth          = 16 ;
  int    nix_audio_driver       = 0 ;
  String jack_client_name       = "linjam" ;
  int    jack_n_input_channels  = 2 ;
  int    jack_n_output_channels = 2 ;
/* TODO:
  audio_config =>
    win => "an_int?"
    mac => "input device name"
    nix => "alsa_config_string"
*/
#ifdef _WIN32
  char* audio_config          = "" ; // TODO: what is the form ? - can be empty ?
#else // _WIN32
#  ifdef _MAC
  char* audio_config          = "" ; // TODO: what is the form ? - can be empty ?
#  else // _MAC
  char* audio_config          = "" ; // TODO: what is the form ? - can be empty - yes
#  endif // _MAC
#endif // _WIN32

  // master channels config defaults
  float master_vol  = 1.0 ;
  float master_pan  = 1.0 ;
  int   master_mute = 1 ;
  float metro_vol   = 1.0 ;
  float metro_pan   = 1.0 ;
  int   metro_mute  = 1 ;

  // input channels config defaults
  const int     MAX_INPUT_CHANNELS = Client->GetMaxLocalChannels() ;
  Array<String> channel_names ;   String channel_name    = String("unnamed channel") ;
  Array<int>    channel_sources ; int    channel_source  = 0 ;
  Array<int>    channel_xmits ;   int    channel_xmit    = 0 ;
  Array<int>    channel_mutes ;   int    channel_mute    = 0 ;
  Array<int>    channel_solos ;   int    channel_solo    = 0 ;
  Array<float>  channel_volumes ; float  channel_volume  = 0 ;
  Array<float>  channel_pans ;    float  channel_pan     = 0 ;
  channel_names  .insertMultiple(0 , channel_name   , MAX_INPUT_CHANNELS) ;
  channel_sources.insertMultiple(0 , channel_source , MAX_INPUT_CHANNELS) ; // TODO: check this
  channel_xmits  .insertMultiple(0 , channel_xmit   , MAX_INPUT_CHANNELS) ;
  channel_mutes  .insertMultiple(0 , channel_mute   , MAX_INPUT_CHANNELS) ;
  channel_solos  .insertMultiple(0 , channel_solo   , MAX_INPUT_CHANNELS) ;
  channel_volumes.insertMultiple(0 , channel_volume , MAX_INPUT_CHANNELS) ; // TODO: check this
  channel_pans   .insertMultiple(0 , channel_pan    , MAX_INPUT_CHANNELS) ; // TODO: check this

  // misc config defaults
  int debug_level            = 0 ; // TODO: what are the accepted values
/* cursesclient
WDL_String sessiondir;
int sessionspec=0;
int nolog=0,nowav=1,writeogg=0,g_nssf=0;
*/

// TODO: read persistent config
// TODO: parse command line args (autojoin)

  // initialize NINJAM client
//   Client->LicenseAgreementCallback = licensecallback = (int (*)(int i, char* c))on_license ;
//   Client->ChatMessage_Callback     = chatmsg_cb      = (void (*)(int i, NJClient* n, const char** c, int ii))on_chatmsg ;
  Client->LicenseAgreementCallback = licensecallback = OnLicense ;
  Client->ChatMessage_Callback     = chatmsg_cb      = OnChatmsg ;
/*
Client->LicenseAgreementCallback = licensecallback ;
Client->ChatMessage_Callback     = chatmsg_cb ;
*/
  Client->config_savelocalaudio    = save_local_audio ;
  Client->config_debug_level       = debug_level ;
/*
audiostream_onsamples = OnSamples ; // TODO:
audiostream_onunder   = OnUnderflow ;
audiostream_onover    = OnOverflow ;
*/

  // initialize audio
#ifdef _WIN32
  Audio = CreateConfiguredStreamer(WIN_INI_FILE , !audio_config , NULL) ;
#else // _WIN32
#  ifdef _MAC
  Audio = create_audioStreamer_CoreAudio(&audio_config , mac_sample_rate ,
                                         mac_n_input_channels , mac_bit_depth , OnSamples) ;
//                                          mac_n_input_channels , mac_bit_depth , audiostream_onsamples) ;
#  else // _MAC
  switch (nix_audio_driver == 0)
  {
    case 0: // JACK
      Audio = create_audioStreamer_JACK(jack_client_name.toRawUTF8() , jack_n_input_channels ,
                                        jack_n_output_channels , OnSamples , Client) ;
//                                         jack_n_output_channels , audiostream_onsamples , Client) ;

DEBUG_TRACE_JACK_INIT

      if (Audio) break ;
    default:
      Audio = create_audioStreamer_ALSA(audio_config , OnSamples) ;
//      Audio = create_audioStreamer_ALSA(audio_config , audiostream_onsamples) ;
  }
#  endif // _MAC
#endif // _WIN32

DEBUG_TRACE_AUDIO_INIT

  if (!Audio) return 0 ;

  // configure master channels
  Client->config_mastervolume   = master_vol ;
  Client->config_masterpan      = master_pan ;
  Client->config_mastermute     = !!master_mute ;
  Client->config_metronome      = metro_vol ;
  Client->config_metronome_pan  = metro_pan ;
  Client->config_metronome_mute = !!metro_mute ;

  // configure input channels
  int n_input_channels = Audio->m_innch ;
  for (int ch = 0 ; ch < n_input_channels ; ++ch)
  {
    Client->SetLocalChannelInfo(ch , channel_names[ch].toRawUTF8() , false , false , false , 0 , false , false) ;
    Client->SetLocalChannelInfo(ch , NULL , true , channel_sources[ch] , false , 0 , false , false) ;
    Client->SetLocalChannelInfo(ch , NULL , false , false , false , 0 , true , !!channel_xmits[ch]) ;
    Client->SetLocalChannelMonitoring(ch , false , false , false , false , true , !!channel_mutes[ch] , false , false) ;
    Client->SetLocalChannelMonitoring(ch , false , false , false , false , false , false , true , !!channel_solos[ch]) ;
    Client->SetLocalChannelMonitoring(ch , true , channel_volumes[ch] , false , false , false , false , false , false) ;
    Client->SetLocalChannelMonitoring(ch , false , false , true , channel_pans[ch] , false , false , false , false) ;
#ifdef INPUT_FX
#  ifdef _WIN32
    void *p=CreateJesusInstance(ch,"",Audio->m_srate);
    if (p) Client->SetLocalChannelProcessor(ch,jesusonic_processor,p);
#  endif
#endif
  }

  // initialize networking
  JNL::open_socketlib() ;
}

void LinJam::Connect()
{
  Client->Disconnect() ;
  String login = Login ;
  if (IsAnonymous)
  {
    login = "anonymous:" + ((Login == "")? "nobody" : Login) ;
    Pass  = "" ;
  }

Server = "ninbot.com:2050" ; // TODO: get Server Login Pass IsAnonymous from config
#if DEBUG_BYPASS_LICENSE
  IsAgreed = true ;
#endif
DEBUG_TRACE_CONNECT

  Client->Connect(Server.toRawUTF8() , login.toRawUTF8() , Pass.toRawUTF8()) ;
}

void LinJam::Disconnect() { Client->Disconnect() ; }

void LinJam::Shutdown() { delete Audio ; JNL::close_socketlib() ; }


/* getters/setters */

// TODO: get/set persistent config
bool   LinJam::GetShouldAutoJoin() { return ShouldAutoJoin ; }
String LinJam::GetServer() { return Server ; }
String LinJam::GetLogin() { return Login ; }
String LinJam::GetPass() { return Pass ; }
bool   LinJam::GetIsAnonymous() { return IsAnonymous; }
bool   LinJam::GetShouldAgree() { return ShouldAgree ; }
bool   LinJam::SetShouldAgree(bool shouldAgree) { ShouldAgree = shouldAgree ; }
bool   LinJam::SetIsAgreed(bool isAgreed) { IsAgreed = isAgreed ; }


/* NJClient callbacks */

int LinJam::OnLicense(int user32 , char* license_text)
{
#if DEBUG_LICENSE_MULTITHREADED
return Gui->prompt_license(String(license_text)) ;
Gui->licenseComponent->toFront(true) ;
Gui->licenseComponent->agreeEvent->wait() ;
IsAgreed = (licenseComponent->getIsAgreed()) ;
#else
  if (!(IsAgreed = (IsAgreed || GetShouldAgree())))
    Gui->licenseComponent->setLicenseText(license_text) ;
#endif
DEBUG_TRACE_LICENSE

  return IsAgreed ;
}

void LinJam::OnChatmsg(int user32 , NJClient* instance , const char** parms , int nparms)
{
DEBUG_TRACE_CHAT_IN
}

void LinJam::OnSamples(float** in_buffer , int in_n_channels ,
                       float** out_buffer , int out_n_channels ,
                       int len , int sample_rate)
{}

/*
void LinJam::OnUnderflow() {}

void LinJam::OnOverflow() {}
*/
