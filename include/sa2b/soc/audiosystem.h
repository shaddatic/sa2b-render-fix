/*
*   Sonic Adventure Mod Tools (SA2B) - '/soc/audiosystem.h'
*
*   ~~ Under Construction ~~
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/

#ifndef _SOC_AUDIOSYS_H_
#define _SOC_AUDIOSYS_H_

#ifdef __cplusplus

#include <sa2b/magic/audio.h>

#pragma pack(push, 8)
struct __declspec(align(4)) SOCAudioSystem
{
    void* vtbl;
    int m_InitFlag;
    Magic::MEDIA::MC_Audio* m_Channel[36];
    void* wavMemPtr[36];
    int wavMemLen[36];
    void* m_pSubject;
};
#pragma pack(pop)

#define GetSOCAudioSystem FuncPtr(SOCAudioSystem*, __cdecl, (), 0x004021E0)

#define SetupADXVolume FuncPtr(SOCAudioSystem*, __cdecl, (sint32), 0x00439490)

#endif /* __cplusplus */

#endif /* _SOC_AUDIOSYS_H_ */