
// TODO: transitional - this function is slightly modified from the win32 client
//           it functionality is to be reimplemented in juce client (issue #27)
// NOTE: this file is not included in the jucer project


#include "audioconfig.h"


struct
{
   int mode;
   int ks_srate;
   int ks_bps;
   int ks_device[2];
   int ks_blocksize;
   int ks_numblocks;

   int waveout_srate;
   int waveout_bps;
   int waveout_device[2];
   int waveout_blocksize;
   int waveout_numblocks;

   int dsound_srate;
   int dsound_bps;
   int dsound_device[2][4];
   int dsound_blocksize;
   int dsound_numblocks;

   int asio_driver;
   int asio_input[2];
   int asio_output[2];

} configdata = {
#ifndef NO_SUPPORT_ASIO
  audioStreamer::WINDOWS_AUDIO_ASIO    , // default to ASIO
#else // NO_SUPPORT_ASIO
#  ifndef NO_SUPPORT_KS
  audioStreamer::WINDOWS_AUDIO_KS      , // default to KS
#  else // NO_SUPPORT_KS
#    ifndef NO_SUPPORT_DS
  audioStreamer::WINDOWS_AUDIO_DS      , // default to DS
#    else // NO_SUPPORT_DS
  audioStreamer::WINDOWS_AUDIO_WAVE    , // default to WAVE
#    endif // NO_SUPPORT_DS
#  endif // NO_SUPPORT_ASIO
#endif // NO_SUPPORT_KS

   48000                               , // ks_srate ;
   16                                  , // ks_bps ;
   {-1 , -1}                           , // ks_device ;
   512                                 , // ks_blocksize ;
   8                                   , // ks_numblocks ;

   44100                               , // waveout_srate ;
   16                                  , // waveout_bps ;
   {-1 , -1}                           , // waveout_device ;
   4096                                , // waveout_blocksize ;
   8                                   , // waveout_numblocks ;

   44100                               , // dsound_srate ;
   16                                  , // dsound_bps ;
   {{0 , 0 , 0 , 0} , {0 , 0 , 0 , 0}} , // dsound_device ;
   1024                                , // dsound_blocksize ;
   16                                  , // dsound_numblocks ;

   0                                   , // asio_driver ;
   {0 , 1}                             , // asio_input ;
   {0 , 1}                               // asio_output ;
} ;


static WDL_String m_inifile;
#define MYRI(val,name) if (isload) { configdata.##val = GetPrivateProfileInt("audioconfig",#name,configdata.##val,m_inifile.Get()); } else { char buf[512]; wsprintf(buf,"%d",configdata.##val); WritePrivateProfileString("audioconfig",#name,buf,m_inifile.Get()); }
static void loadsave_config(int isload)
{
#ifndef NO_SUPPORT_ASIO

  MYRI(asio_driver,asio_driver)
  MYRI(asio_input[0],asio_input0)
  MYRI(asio_input[1],asio_input1)
  MYRI(asio_output[0],asio_output0)
  MYRI(asio_output[1],asio_output1)

#endif // NO_SUPPORT_ASIO
#ifndef NO_SUPPORT_KS

  MYRI(mode,mode)
  MYRI(ks_srate,ks_srate)
  MYRI(ks_bps,ks_bps)
  MYRI(ks_device[0],ks_devin)
  MYRI(ks_device[1],ks_devout)
  MYRI(ks_blocksize,ks_blocksize)
  MYRI(ks_numblocks,ks_numblocks)

#endif // NO_SUPPORT_KS
#ifndef NO_SUPPORT_DS

  MYRI(dsound_srate,dsound_srate)
  MYRI(dsound_bps,dsound_bps)
  MYRI(dsound_device[0][0],dsound_devicein_0)
  MYRI(dsound_device[0][1],dsound_devicein_1)
  MYRI(dsound_device[0][2],dsound_devicein_2)
  MYRI(dsound_device[0][3],dsound_devicein_3)
  MYRI(dsound_device[1][0],dsound_deviceout_0)
  MYRI(dsound_device[1][1],dsound_deviceout_1)
  MYRI(dsound_device[1][2],dsound_deviceout_2)
  MYRI(dsound_device[1][3],dsound_deviceout_2)
  MYRI(dsound_blocksize,dsound_blocksize)
  MYRI(dsound_numblocks,dsound_numblocks)

#endif // NO_SUPPORT_DS
#ifndef NO_SUPPORT_WAVE

  MYRI(waveout_srate,waveout_srate)
  MYRI(waveout_bps,waveout_bps)
  MYRI(waveout_device[0],waveout_devicein)
  MYRI(waveout_device[1],waveout_deviceout)
  MYRI(waveout_blocksize,waveout_blocksize)
  MYRI(waveout_numblocks,waveout_numblocks)

#endif // NO_SUPPORT_WAVE
#undef MYRI
}

audioStreamer* CreateConfiguredStreamer(char *ini_file                       ,
                                        audioStreamer::WinAudioIf audio_if_n ,
                                        SPLPROC audiostream_onsamples)
{
  if (!ini_file || !ini_file[0]) ini_file = "libninjam.ini" ;
  m_inifile.Set(ini_file);
  loadsave_config(1);
  configdata.mode = audio_if_n ;

  switch (configdata.mode)
  {
    case audioStreamer::WINDOWS_AUDIO_ASIO:
    {
  #ifndef NO_SUPPORT_ASIO
        static char tmpbuf[64];
        wsprintf(tmpbuf,"%d:%d,%d:%d,%d",configdata.asio_driver,
        configdata.asio_input[0],
        configdata.asio_input[1],
        configdata.asio_output[0],
        configdata.asio_output[1]
        );

        char *dev_name_in=tmpbuf;
        audioStreamer* asio = njasiodrv_create_asio_streamer(&dev_name_in,audiostream_onsamples);

        if (asio) { return asio ; break ; }
  #endif // NO_SUPPORT_ASIO
    }
    case audioStreamer::WINDOWS_AUDIO_KS:
    {
  #ifndef NO_SUPPORT_KS
      int nbufs=configdata.ks_numblocks;
      int bufsize=configdata.ks_blocksize;
      audioStreamer *ks=create_audioStreamer_KS(configdata.ks_srate, configdata.ks_bps, &nbufs, &bufsize,audiostream_onsamples);

      if (ks) { return ks ; break ; }
  #endif // NO_SUPPORT_KS
    }
    case audioStreamer::WINDOWS_AUDIO_DS:
    {
  #ifndef NO_SUPPORT_DS
      GUID bla[2];
      int nbufs   = configdata.dsound_numblocks ;
      int bufsize = configdata.dsound_blocksize ;
      memcpy(bla , configdata.dsound_device , sizeof(bla)) ;
      audioStreamer* ds = create_audioStreamer_DS(configdata.dsound_srate , configdata.dsound_bps ,
                                                  bla , &nbufs , &bufsize , audiostream_onsamples) ;
      if (ds) { return ds ; break ; }
  #endif // NO_SUPPORT_DS
    }
    case audioStreamer::WINDOWS_AUDIO_WAVE:
    default:
    {
  #ifndef NO_SUPPORT_WAVE
      int nbufs=configdata.waveout_numblocks;
      int bufsize=configdata.waveout_blocksize;
      audioStreamer* wave = create_audioStreamer_WO(configdata.waveout_srate,configdata.waveout_bps,configdata.waveout_device,&nbufs,&bufsize,audiostream_onsamples);

      if (wave) { return wave ; break ; }
  #endif // NO_SUPPORT_WAVE
    }
  }

  return NULL ;
}
