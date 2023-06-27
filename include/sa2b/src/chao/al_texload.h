#pragma once

/*
*	Includes
*/

#include <sa2b/ninja/ninja.h>

/*
*	Enums
*/

enum 
{ 
	TEX_LEV_COMMON, 
	TEX_LEV_STAGE, 
	TEX_LEV_LAND, 
	TEX_LEV_OTHER, 
	NB_TEX_LEV, 
};

/*
*	User Functions
*/

sint32	AL_LoadTex(const ansi* filename, NJS_TEXLIST* pTexlist, uint16 lev);

sint32	AL_ReleaseTex(uint16 lev);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* AL_LoadTex_p;

extern const void* AL_ReleaseTex_p;

#endif