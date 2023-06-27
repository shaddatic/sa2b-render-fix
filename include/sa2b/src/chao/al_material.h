#pragma once

/*
*	Includes
*/

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/chao/al_shape.h>

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

int		AL_MatSetChaoColor(task* tp, __int16 ColorNum);

void	AL_MatChangeModelTexture(al_model* pModel, uint16 TexID);

/*
*	Remade Functions
*/

void	AL_MatChangeObjectTexture(al_object* pObject, uint16 TexID);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* AL_MatSetChaoColor_p;

extern const void* AL_MatChangeModelTexture_p;

#endif