/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/minimal.h'
*
*   Contains data and functions related to Minimals in the main game
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#pragma once

/************************/
/*  Structures          */
/************************/
typedef struct 
{
	sint32 num;
	sint32 timer;
}
EXTRA;

typedef struct
{
	EXTRA overflow[10];
	EXTRA list[10];
	sint32 nbExtra;
	float32 posx;
	float32 velo;
	float32 shiftx;
	sint32 timer;
}
EXTRA_LIST;

/************************/
/*  Data                */
/************************/
DataAry(EXTRA_LIST, extra_lists, 0x01946EC8, [3]);

/************************/
/*  Function Pointers   */
/************************/
FuncPtr(EXTRA_LIST*, __fastcall, Extra_Get, (sint32 pno), 0x00487260);

/************************/
/*  User Functions      */
/************************/
void	AddExtraDisplay(sint32 num, sint32 pno);

/************************/
/*  User Function Ptrs  */
/************************/
#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* AddExtraDisplay_p;

#endif