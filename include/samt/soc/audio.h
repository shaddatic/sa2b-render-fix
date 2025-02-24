/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/soc/audio.h'
*
*   Description:
*     SoC's Audio classes.
*/
#ifndef H_SOC_AUDIO
#define H_SOC_AUDIO

/************************/
/*  External Header     */
/************************/
/****** Magic ***********************************************************************/
#include <samt/magic/base.h>    /* Magic::Base::Singleton                           */
#include <samt/magic/media.h>   /* MEDIA::MC_Audio, MEDIA::MC_AudioSystem           */

/************************/
/*  Abstract Types      */
/************************/
typedef struct soc_audiosystem  SOCAudioSystem;

/************************/
/*  Structures          */
/************************/
#ifdef  __cplusplus
/****** SoC Audio System ************************************************************/
typedef struct soc_audiosystem
{
    char                          m_Unk[4];
    Magic::MEDIA::MC_Audio*       m_Channel[36];
    void*                         wavMemPtr[36];
    int                           wavMemLen[36];
    Magic::MEDIA::MC_AudioSystem* m_pSubject;
    int                           m_AdxVolume;
}
SOCAudioSystem;

#endif/*__cplusplus*/

/************************/
/*  Data                */
/************************/
#ifdef  __cplusplus
/****** Singleton *******************************************************************/
#define g_pSOCAudioSystem           DATA_REF(Magic::Base::Singleton, 0x01AF19E0)

#endif/*__cplusplus*/

/************************/
/*  Functions           */
/************************/
EXTERN_START
SOCAudioSystem* GetSOCAudioSystem( void );

/** Set PCM **/
void    SetVolumePCM( int ch, int volume );

/** Play/Stop PCM **/
void    PlayPCM( int ch );
void    StopPCM( int ch );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptr **/
#   define GetSOCAudioSystem_p      FUNC_PTR(SOCAudioSystem*, __cdecl, (void), 0x004021E0)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*H_SOC_AUDIO*/
