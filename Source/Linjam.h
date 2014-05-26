/*
  ==============================================================================

    Linjam.h
    Created: 24 May 2014 5:03:01pm
    Author:  me

  ==============================================================================
*/

#ifndef LINJAM_H_INCLUDED
#define LINJAM_H_INCLUDED


#include <ninjam/audiostream.h>
#include <ninjam/njclient.h>
#include <ninjam/njmisc.h>

class LinJamClient
{
public:

  static int initialise(NJClient* client) ;
  static int on_license(int user32 , char* license_text) ;
  static void on_samples(float** in_buffer , int in_n_channels ,
                  float** out_buffer , int out_n_channels ,
                  int len , int sample_rate) ;
  static void on_chatmsg(int user32 , NJClient* instance , const char** parms , int nparms) ;
  static void on_underflow() ;
  static void on_overflow() ;
} ;







/* OK 1
#include <ninjam/audiostream.h>
#include <ninjam/njclient.h>
#include <ninjam/njmisc.h>

int linJamMain(NJClient* client) ;
int on_license(int user32 , char* license_text) ;
void on_samples(float** in_buffer , int in_n_channels ,
                float** out_buffer , int out_n_channels ,
                int len , int sample_rate) ;
void on_chatmsg(int user32 , NJClient* instance , const char** parms , int nparms) ;
void on_underflow() ;
void on_overflow() ;
*/






/* 0 - thread experiment
#include <ninjam/audiostream.h>
#include <ninjam/njclient.h>


class LinJamClient : public Thread
{
public:

  LinJam() ;
  ~LinJam() ;

  void run() override ;

private:

  audioStreamer* audio ;
  NJClient*      client ;
  int            audio_enable ;
  char*          audio_config_str ;

  int  on_license(  int user32 , char* license_text) ;
  void on_chatmsg(  int user32 , NJClient* instance , const char** parms , int nparms) ;
  void on_samples(  float** in_buffer , int in_n_channels ,
                    float** out_buffer , int out_n_channels ,
                    int len , int sample_rate) ;
  void on_underflow() ;
  void on_overflow( ) ;
} ;
*/

#endif  // LINJAM_H_INCLUDED
