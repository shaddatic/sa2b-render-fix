/*
*	Sonic Adventure Mod Tools - Memory Tools Header
*/

#ifndef _SAMT_MEMTOOLS_H_
#define _SAMT_MEMTOOLS_H_

/*
*	Includes
*/

#include <string.h>

/*
*	Constants
*/

#define CONST_THREASHOLD (void*)0x0087342C

/*
*	Tools
*/

#define GetCallFunction(calladdr)		(void*)((int)(calladdr) + 5 + *(int*)((int)calladdr + 1))

/*
*	Functions
*/

void	WriteProtectedMemory(void* writeaddr, void* dataaddr, size_t elemsize);

void	_WriteJump(void* writeaddr, void* jumpaddr);
void	_WriteCall(void* writeaddr, void* calladdr);

/*
*	Define Functions
*/

#define WriteMemory(WADDR, DADDR, SIZE)		if constexpr ((void*)WADDR < CONST_THREASHOLD) { WriteProtectedMemory((void*)WADDR, (void*)DADDR, (size_t)SIZE); } else { memcpy((void*)WADDR, (void*)DADDR, (size_t)SIZE); }

#define WriteValue(ADDR, VAL, TYPE)		{	TYPE v = (TYPE)(VAL); WriteMemory((ADDR), &v, sizeof(TYPE));	}
#define WritePointer(ADDR, PTR)				WriteValue((ADDR), (PTR), void*)

#define WriteMulti(WA, VAL, NB)			{	uint8 a[NB]; memset(a, VAL, NB); WriteMemory((void*)WA, a, NB);			}

#define WriteNoOP(from, to)					WriteMulti(from, 0x90, (to - from));
#define KillCall(WA)						WriteMulti(WA, 0x90, 0x05);

#define WriteJump(ADDR, JUMP)				_WriteJump((void*)ADDR, (void*)JUMP)
#define WriteCall(ADDR, CALL)				_WriteCall((void*)ADDR, (void*)CALL)

#define WriteArray(ADDR, ARY)				WriteMemory((void*)ADDR, (void*)ARY, sizeof(ARY))

/* Legacy */
#define WriteNoOPOld(WA, NB)				WriteMulti(WA, 0x90, NB);

#define WriteClearedCall(WA, CA, NB)		WriteNoOPOld(WA, NB); _WriteCall((void*)WA, (void*)CA);

#endif /* _SAMT_MEMTOOLS_H_ */