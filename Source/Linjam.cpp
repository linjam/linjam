/*
  ==============================================================================

    Linjam.cpp
    Created: 24 May 2014 5:03:01pm
    Author:  me

  ==============================================================================
*/

#include "JuceHeader.h"




#include "Linjam.h"
int (*licensecallback)(       int user32 , char *licensetext) ;
void (*audiostream_onsamples)(float** in_buffer , int in_n_channels ,
                              float** out_buffer , int out_n_channels ,
                              int len , int sample_rate) ;
void (*chatmsg_cb)(int user32 , NJClient* instance , const char** parms , int nparms) ;
void (*audiostream_onunder)() ;
void (*audiostream_onover)() ;
audioStreamer* Audio  ;
NJClient*      Client ;
int LinJamClient::initialise(NJClient* client)
{
  Client                           = client ;
  Client->config_savelocalaudio    = 0 ;
//   Client->LicenseAgreementCallback = licensecallback = (int (*)(int i, char* c))on_license ;
//   Client->ChatMessage_Callback     = chatmsg_cb      = (void (*)(int i, NJClient* n, const char** c, int ii))on_chatmsg ;
  Client->LicenseAgreementCallback = licensecallback = on_license ;
  Client->ChatMessage_Callback     = chatmsg_cb      = on_chatmsg ;
/*
audiostream_onsamples = on_samples ;
audiostream_onunder   = on_underflow ;
audiostream_onover    = on_overflow ;
*/
  int   audio_enable     = 0 ;
  char* audio_config_str = NULL ;
#ifdef _WIN32
  Audio = CreateConfiguredStreamer("linjam.ini" , !audio_config_str , NULL) ;
#else
  char *dev_name_in = audio_config_str ;
#  ifdef _MAC
  Audio = create_audioStreamer_CoreAudio(&dev_name_in , 48000 , 2 , 16 , on_samples) ;
#  else
  Audio = create_audioStreamer_JACK("linjam" , 4 , 4 , on_samples , Client) ;
#  endif
#endif

  if (!Audio) { printf("Error opening audio!\n") ; return 0 ; }

  printf("Opened audio at %dHz %d->%dch %dbps\n" ,
    Audio->m_srate , Audio->m_innch , Audio->m_outnch , Audio->m_bps) ;
}
int LinJamClient::on_license(int user32 , char* license_text)
{}
void LinJamClient::on_samples(float** in_buffer , int in_n_channels ,
                float** out_buffer , int out_n_channels ,
                int len , int sample_rate)
{}
void LinJamClient::on_chatmsg(int user32 , NJClient* instance , const char** parms , int nparms) {}
void LinJamClient::on_underflow() { }
void LinJamClient::on_overflow() { }








/* OK 1
#include "Linjam.h"
audioStreamer* Audio  ;
NJClient*      Client ;
int linJamMain(NJClient* client)
{
  Client                           = client ;
  Client->config_savelocalaudio    = 0 ;
  Client->LicenseAgreementCallback = on_license ;
  Client->ChatMessage_Callback     = on_chatmsg ;

  int   audio_enable     = 0 ;
  char* audio_config_str = NULL ;
#ifdef _WIN32
  Audio = CreateConfiguredStreamer("linjam.ini" , !audio_config_str , NULL) ;
#else
  char *dev_name_in = audio_config_str ;
#  ifdef _MAC
  Audio = create_audioStreamer_CoreAudio(&dev_name_in , 48000 , 2 , 16 , on_samples) ;
#  else
  Audio = create_audioStreamer_JACK("linjam" , 4 , 4 , on_samples , Client) ;
#  endif
#endif

  if (!Audio) { printf("Error opening audio!\n") ; return 0 ; }

  printf("Opened audio at %dHz %d->%dch %dbps\n" ,
    Audio->m_srate , Audio->m_innch , Audio->m_outnch , Audio->m_bps) ;


//   signal(SIGINT,sigfunc);
// 
//   JNL::open_socketlib() ;

}
int on_license(int user32 , char* license_text)
{}
void on_samples(float** in_buffer , int in_n_channels ,
                float** out_buffer , int out_n_channels ,
                int len , int sample_rate)
{}
void on_chatmsg(int user32 , NJClient* instance , const char** parms , int nparms) {}
void on_underflow() { }
void on_overflow() { }
*/










/* 0 - Thread experiment
#include "Linjam.h"

LinJamClient::LinJam() : Thread("LinJam Thread") { startThread() ; }
LinJamClient::~LinJam() { stopThread(2000) ; }

void LinJamClient::run() override
{

  audioStreamer* audio            = nullptr ;
  NJClient*      client           = nullptr ;
  int            audio_enable     = 0 ;
  char*          audio_config_str = NULL ;

  client = new NJClient() ;
  client->config_savelocalaudio    = 0 ;
  client->LicenseAgreementCallback = on_license ;
  client->ChatMessage_Callback     = on_chatmsg ;

#ifdef _WIN32
  Audio = CreateConfiguredStreamer("linjam.ini" , !audio_config_str , NULL) ;
#else
  char *dev_name_in = audio_config_str ;
#  ifdef _MAC
  audio = create_audioStreamer_CoreAudio(&dev_name_in , 48000 , 2 , 16 , on_samples) ;
#  else
  audio = create_audioStreamer_JACK("linjam" , 4 , 4 , on_samples , client) ;
#  endif
#endif

  if (!audio) { printf("Error opening audio!\n") ; return 0 ; }

  printf("Opened audio at %dHz %d->%dch %dbps\n" ,
    audio->m_srate , audio->m_innch , audio->m_outnch , audio->m_bps) ;
*/
/*
  signal(SIGINT,sigfunc);

  JNL::open_socketlib() ;
*/
/*
}

int LinJamClient::on_license(int user32 , char* license_text)
{}
void LinJamClient::on_samples(float** in_buffer , int in_n_channels ,
                        float** out_buffer , int out_n_channels ,
                        int len , int sample_rate)
{}

void LinJamClient::on_chatmsg(int user32 , NJClient* instance , const char** parms , int nparms) {}

void LinJamClient::on_underflow() { }

void LinJamClient::on_overflow() { }
*/
