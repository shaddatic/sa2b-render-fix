#pragma once

/*
*	Includes
*/

#include <sa2b/ninja/ninja.h>

/*
*	Structs
*/

typedef struct bankentry
{
	sint8 memBank;
	sint8 index;
	sint8 seBank;
	sint8 flags;
	sint16 unk;
	sint16 dist;
}
BANK_ENTRY;

typedef struct banklist
{
	sint32 nbEntry;
	BANK_ENTRY* pList;
}
BANK_LIST;

/*
*	User Functions
*/

#define SE(bank, idx) ((bank * 0x1000) + idx)

void	SE_Call(int SoundID, void* ptask, char unk, char volume);

void	SE_Call_TIMER(int SoundID, void* pTask, char Unk, signed char Volume, __int16 PlayTime);

sint8	SE_CallV2(int SoundID, NJS_POINT3* Location, void* pTask, char a4, char Volume);

sint8	SE_CallV2_TIMER(void* pTask, int SoundID, NJS_POINT3* pPos, char a4, char Volume, __int16 TimerSomething);

char	SE_CallV2_Loop(void* task, int SoundID, NJS_POINT3* pPos, sint8 volume);

uint32* SE_Add_Volume(__int8 a1, void* a2, int a3);

uint32* SE_Add_Pitch(signed __int16 Pitch, void* pTask, int SoundID);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* SE_Call_p;

extern const void* SE_Call_TIMER_p;

extern const void* SE_CallV2_p;

extern const void* SE_CallV2_TIMER_p;

extern const void* SE_CallV2_Loop_p;

extern const void* SE_Add_Volume_p;

extern const void* SE_Add_Pitch_p;

#endif