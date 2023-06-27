#pragma once

/*
*	Abstracted Structs
*/

typedef struct task		task;

/*
*	Includes
*/

#include <sa2b/ninja/ninja.h>

/*
*	Data References
*/

DataRef(sint32, CurrPathNum, 0x01A5D13C);

/*
*	Data Arrays
*/

DataAry(NJS_MOTION*, PathMotionList,	0x01353278, [10]);
DataAry(NJS_MKEY_F*, PathMKeyList,		0x013532A0, [10][2]);

/*
*	Function Pointers
*/

FuncPtr(sint32, __cdecl, AL_PathSearch, (task* tp), 0x0053E3E0);

/*
*	User Functions
*/

void	CrossProduct(NJS_POINT3* pPos0, NJS_POINT3* pPos1, NJS_POINT3* pPos2, NJS_POINT3* pAnswer);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* CrossProduct_p;

#endif