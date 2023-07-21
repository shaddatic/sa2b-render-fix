#pragma once

/*
*	Abstracted structs
*/

typedef struct task			TASK;

typedef struct al_model		AL_MODEL;
typedef struct al_object	AL_OBJECT;

/*
*	Includes
*/

#include <sa2b/ninja/njcommon.h>

/*
*	Data Arrays
*/

DataAry(int, ChaoColorList, 0x01298448, [16]);
DataAry(int, EggColorList, 0x01298414, [13]);

/*
*	Function Pointers
*/

FuncPtr(NJS_CNK_OBJECT*, __cdecl, AL_CopyObject, (NJS_CNK_OBJECT* pObject), 0x0055EBD0);	// no official names yet
FuncPtr(void,			 __cdecl, AL_FreeObject, (NJS_CNK_OBJECT* pObject), 0x0055EDF0);	// ^

/*
*	User Functions
*/

int		AL_MatSetChaoColor(TASK* tp, __int16 ColorNum);

void	AL_MatChangeModelTexture(AL_MODEL* pModel, uint16 TexID);

/*
*	Remade Functions
*/

void	AL_MatChangeObjectTexture(AL_OBJECT* pObject, uint16 TexID);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* AL_MatSetChaoColor_p;

extern const void* AL_MatChangeModelTexture_p;

#endif