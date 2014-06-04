/*
  ==============================================================================

    Linjam.cpp
    Created: 24 May 2014 5:03:01pm
    Author:  me

  ==============================================================================
*/

#include "LinJam.h"
#include "Constants.h"
#include "Trace.h"


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

bool LinJam::Initialize(NJClient* client , MainContentComponent* contentComponent ,
                       const String& args)
{
DEBUG_TRACE_LINJAM_INIT

  Client = client ;
  Gui    = contentComponent ;

  // audio config defaults
//  int                     audio_enable           = 0 ;
  int                       save_local_audio       = 0 ;
#ifdef _WIN32
/*
#  define WINDOWS_AUDIO_KS 0 // TODO: enum in audioconfig.h
#  define WINDOWS_AUDIO_DS 1
#  define WINDOWS_AUDIO_WAVE 2
#  define WINDOWS_AUDIO_ASIO 3
*/
  audioStreamer::WinAudioIf win_audio_if_n         = audioStreamer::WINDOWS_AUDIO_WAVE ;
#else // _WIN32
#  ifdef _MAC
  int                       mac_n_input_channels   = 2 ;
  int                       mac_sample_rate        = 48000 ;
  int                       mac_bit_depth          = 16 ;
  char*                     audio_config           = "" ; // TODO: what is the form ? - can be empty ?
#  else // _MAC
  int                       nix_audio_driver       = 0 ;
  String                    jack_client_name       = "linjam" ;
  int                       jack_n_input_channels  = 2 ;
  int                       jack_n_output_channels = 2 ;
  char*                     audio_config           = "" ; // TODO: what is the form ? - can be empty - yes
#  endif // _MAC
#endif // _WIN32
/* TODO:
  audio_config =>
    win => "an_int?"
    mac => "input device name"
    nix => "alsa_config_string"
*/

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
  Client->LicenseAgreementCallback = OnLicense ;
  Client->ChatMessage_Callback     = OnChatmsg ;
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
//  Audio = CreateConfiguredStreamer(CLIENT::WIN_INI_FILE , !audio_config , NULL) ;
//  Audio = CreateConfiguredStreamer(CLIENT::WIN_INI_FILE , !audio_config , NULL , OnSamples) ;
  Audio = CreateConfiguredStreamer(CLIENT::WIN_INI_FILE , win_audio_if_n , OnSamples) ;
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

  if (!Audio) return false ;

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
/* from cursesclient
    else // set up defaults
    {
      g_client->SetLocalChannelInfo(0,"channel0",true,0,false,0,true,true);
      g_client->SetLocalChannelMonitoring(0,false,0.0f,false,0.0f,false,false,false,false);
    }
*/
  // initialize networking
  JNL::open_socketlib() ;

  return true ;
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
void   LinJam::SetShouldAgree(bool shouldAgree) { ShouldAgree = shouldAgree ; }
void   LinJam::SetIsAgreed(bool isAgreed) { IsAgreed = isAgreed ; }


/* NJClient callbacks */

int LinJam::OnLicense(int user32 , char* license_text)
{
#ifdef DEBUG_LICENSE_MULTITHREADED
return Gui->prompt_license(String(license_text)) ;
Gui->licenseComponent->toFront(true) ;
Gui->licenseComponent->agreeEvent->wait() ;
IsAgreed = (licenseComponent->getIsAgreed()) ;
#else // DEBUG_LICENSE_MULTITHREADED
  IsAgreed = (IsAgreed || GetShouldAgree()) ;
  if (!IsAgreed) Gui->licenseComponent->setLicenseText(license_text) ;
#endif // DEBUG_LICENSE_MULTITHREADED
DEBUG_TRACE_LICENSE

  return IsAgreed ;
}

void LinJam::OnChatmsg(int user32 , NJClient* instance , const char** parms , int nparms)
{
DEBUG_TRACE_CHAT_IN

  if (!parms[0]) return ;

  String chat_type = String(parms[CLIENT::CHATMSG_TYPE_IDX]) ;
  String chat_user = String(parms[CLIENT::CHATMSG_USER_IDX]).upToFirstOccurrenceOf("@", false , false) ;
  String chat_text = String(parms[CLIENT::CHATMSG_MSG_IDX]) ;
  bool is_topic_msg = (!chat_type.compare(CLIENT::CHATMSG_TYPE_TOPIC)) ;
  bool is_bcast_msg = (!chat_type.compare(CLIENT::CHATMSG_TYPE_MSG)) ;
  bool is_priv_msg  = (!chat_type.compare(CLIENT::CHATMSG_TYPE_PRIVMSG)) ;
  bool is_join_msg  = (!chat_type.compare(CLIENT::CHATMSG_TYPE_JOIN)) ;
  bool is_part_msg  = (!chat_type.compare(CLIENT::CHATMSG_TYPE_PART)) ;  

  if (is_topic_msg)
  {
    if (chat_text.isEmpty()) return ;

    if (chat_user.isEmpty()) chat_text = "Topic is: "                   + chat_text ;
    else                     chat_text = chat_user + " sets topic to: " + chat_text ;
    chat_user = GUI::SERVER_NICK.text ;

    Gui->chatComponent->setTopic(chat_text) ;
  }
  else if (is_bcast_msg)
    { if (chat_user.isEmpty() || chat_text.isEmpty()) return ; }
  else if (is_priv_msg)
  {
    if (chat_user.isEmpty() || chat_text.isEmpty()) return ;

    chat_user += " (whispers)" ;
  } 
  else if (is_join_msg || is_part_msg)
  {
    if (chat_user.isEmpty()) return ;

    chat_text = chat_user + " has " + ((is_join_msg)? "joined" : "left") + " the jam" ;
    chat_user = GUI::SERVER_NICK.text ;
  } 
  Gui->chatComponent->addChatLine(chat_user , chat_text) ;
}

void LinJam::OnSamples(float** in_buffer , int in_n_channels ,
                       float** out_buffer , int out_n_channels ,
                       int len , int sample_rate)
{
/* from cursesclient
void audiostream_onsamples(float **inbuf, int innch, float **outbuf, int outnch, int len, int srate) 
{ 
  if (!g_audio_enable) 
  {
    int x;
    // clear all output buffers
    for (x = 0; x < outnch; x ++) memset(outbuf[x],0,sizeof(float)*len);
    return;
  }
  g_client->AudioProc(inbuf,innch, outbuf, outnch, len,srate);
}


*/
}

/*
void LinJam::OnUnderflow() {}

void LinJam::OnOverflow() {}
*/


/* chat helpers */
void LinJam::SendChat(String chat_text)
{
DBG("LinJam::SendChat() =" + chat_text) ;

  if ((chat_text = chat_text.trim()).isEmpty()) return ;

  if (chat_text[0] == '/') HandleChatCommand(chat_text) ;
  else Client->ChatMessage_Send(CLIENT::CHATMSG_TYPE_MSG , chat_text.toRawUTF8()) ;
}

void LinJam::HandleChatCommand(String chat_text)
{
/* from cursesclient
                      if (!strncasecmp(m_chatinput_str,"/me ",4))
                      {
                        g_client->ChatMessage_Send("MSG",m_chatinput_str);
                      }
                      else if (!strncasecmp(m_chatinput_str,"/topic ",7)||
                               !strncasecmp(m_chatinput_str,"/kick ",6) ||                        
                               !strncasecmp(m_chatinput_str,"/bpm ",5) ||
                               !strncasecmp(m_chatinput_str,"/bpi ",5)
                        ) // alias to /admin *
                      {
                        g_client->ChatMessage_Send("ADMIN",m_chatinput_str+1);
                      }
                      else if (!strncasecmp(m_chatinput_str,"/admin ",7))
                      {
                        char *p=m_chatinput_str+7;
                        while (*p == ' ') p++;
                        g_client->ChatMessage_Send("ADMIN",p);
                      }
                      else if (!strncasecmp(m_chatinput_str,"/msg ",5))
                      {
                        char *p=m_chatinput_str+5;
                        while (*p == ' ') p++;
                        char *n=p;
                        while (*p && *p != ' ') p++;
                        if (*p == ' ') *p++=0;
                        while (*p == ' ') p++;
                        if (*p)
                        {
                          g_client->ChatMessage_Send("PRIVMSG",n,p);
                          WDL_String tmp;
                          tmp.Set("-> *");
                          tmp.Append(n);
                          tmp.Append("* ");
                          tmp.Append(p);
                          addChatLine(NULL,tmp.Get());
                        }
                        else
                        {
                          addChatLine("","error: /msg requires a username and a message.");
                        }
                      }
                      else
                      {
                        addChatLine("","error: unknown command.");
                      }
*/
}
