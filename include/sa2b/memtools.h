/*
*   Sonic Adventure Mod Tools (SA2B) - '/memtools.h'
*
*   Contains functions to modify or read executable data
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/

#ifndef _SAMT_MEMTOOLS_H_
#define _SAMT_MEMTOOLS_H_

/************************/
/*  External Functions  */
/************************/
EXTERN void* __cdecl memset(void* _Dst, int         _Val,   size_t _Size);
EXTERN void* __cdecl memcpy(void* _Dst, void const* _Src,   size_t _Size);

/************************/
/*  Constants           */
/************************/
#define STACK_THRESHOLD     ((void*)0x00400000)
#define CONST_THRESHOLD     ((void*)0x0087342C)

/************************/
/*  Functions           */
/************************/
EXTERN_START

void	WriteProtectedMemory(void* writeaddr, void* dataaddr, size_t elemsize);

void	_WriteJump(void* writeaddr, void* jumpaddr);
void	_WriteCall(void* writeaddr, void* calladdr);

void    SwapEndianness64(void* p);
void    SwapEndianness32(void* p);
void    SwapEndianness16(void* p);

EXTERN_END

/************************/
/*  Function Macros     */
/************************/
#define WriteMemory(WADDR, DADDR, SIZE)		WriteProtectedMemory((void*)WADDR, (void*)DADDR, (size_t)SIZE)

#define WriteData(addr, data, type)		{	type v = (type)(data); WriteMemory((addr), &v, sizeof(type));	}
#define WritePointer(ADDR, PTR)				WriteData((ADDR), (PTR), void*)

#define WriteMulti(WA, VAL, NB)			{	uint8 a[NB]; memset(a, VAL, NB); WriteMemory((void*)WA, a, NB);	}

#define WriteNoOP(from, to)					WriteMulti(from, 0x90, (to - from));
#define KillCall(WA)						WriteMulti(WA, 0x90, 0x05);

#define WriteJump(ADDR, JUMP)				_WriteJump((void*)ADDR, (void*)JUMP)
#define WriteCall(ADDR, CALL)				_WriteCall((void*)ADDR, (void*)CALL)
#define WriteRetn(addr)                     WriteData(addr, 0xC3, uint8)

#define WriteArray(ADDR, ARY)				WriteMemory((void*)ADDR, (void*)ARY, sizeof(ARY))

/** Check for Stack Pointer **/
#define IsOnStack(p)                        (((void*)p) < STACK_THRESHOLD)

/** Legacy Macro **/
#define WriteNOP(WA, NB)					WriteMulti(WA, 0x90, NB);

/** Endiness Macro **/
#define SwapEndianness(ptr)                 if constexpr (sizeof(*ptr) == 8) { SwapEndianness64(ptr); } else if constexpr (sizeof(*ptr) == 4) { SwapEndianness32(ptr); } else if constexpr (sizeof(*ptr) == 2) { SwapEndianness16(ptr); }

/** Get Call Address **/
#define GetCallAddress(addr)		        (void*)((int)(addr) + 5 + *(int*)((int)addr + 1))

#endif /* _SAMT_MEMTOOLS_H_ */