#pragma once

/*
*	Data References
*/

DataRef(sint32, loop_const, 0x01DEB50C);
DataRef(uint32, ulGlobalTimer, 0x0174B038);

DataRef(sint32, GameTimer, 0x0174B03C);

DataRef(uint8, ucFrames, 0x0174AFDD);
DataRef(uint8, ucSeconds, 0x0174AFDC);
DataRef(uint8, ucMinutes, 0x0174AFDB);

DataRef(bool, bWake, 0x0174AFF7);

DataRef(uint32, gu32TotalRing, 0x174B05C);

/*
*	Data Arrays
*/

DataAry(sint16, ssNumPlayer, 0x0174B024, [2]);

DataAry(sint16, ssNumRing, 0x0174B028, [2]);

/*
*	User Functions
*/
void	AddNumRing(sint8 player, sint16 ssNumber);
void	AddNumPlayer(sint8 player, sint16 ssNumber);

/*
*	Recreated Functions
*/

void	AdvanceGlobalTime();
uint32	GetGlobalTime();

void	SetTime(uint8 minutes, uint8 second);
void	GetTime(uint8* minutes, uint8* second);

void	SetTimeFrame(uint8 minutes, uint8 second, uint8 frame);
void	GetTimeFrame(uint8* minutes, uint8* second, uint8* frame);

void	SetTotalRing(uint32 num);
uint32	GetTotalRing();

sint32	GetNumRing(sint8 player);

void	ResetNumRing(sint8 player);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* AddNumRing_p;
extern const void* AddNumPlayer_p;

#endif