#pragma once

/*
*	Structs
*/

struct EXTRA
{
	sint32 num;
	sint32 timer;
};

struct EXTRA_LIST
{
	EXTRA overflow[10];
	EXTRA list[10];
	sint32 nbExtra;
	float32 posx;
	float32 velo;
	float32 shiftx;
	sint32 timer;
};

/*
*	Data Arrays
*/

DataAry(EXTRA_LIST, extra_lists, 0x01946EC8, [3]);

/*
*	Function Pointers
*/

FuncPtr(EXTRA_LIST*, __fastcall, Extra_Get, (sint32 pno), 0x00487260);

/*
*	User Functions
*/

void	AddExtraDisplay(sint32 num, sint32 pno);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* AddExtraDisplay_p;

#endif