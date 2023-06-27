/*
*	SOC audio system header
*
*/

#ifndef _SOC_AUDIOSYS_H_
#define _SOC_AUDIOSYS_H_

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

FuncPtr(SOCAudioSystem*, __cdecl, GetSOCAudioSystem, (), 0x004021E0);

FuncPtr(SOCAudioSystem*, __cdecl, SetupADXVolume, (sint32), 0x00439490);

#endif /* _SOC_AUDIOSYS_H_ */