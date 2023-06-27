#pragma once

/*
*	Includes
*/

#include <sa2b/ninja/ninja.h>

/*
*	Structs
*/

typedef struct
{
	char* pname;
	NJS_TEXLIST* ptexlist;
}
TEX_GVMTABLE;

/*
*	Function Pointers
*/

FuncPtr(sint32, __fastcall, texLoadTextureGvmFile, (const char* fname, NJS_TEXLIST* ptlo), 0x44C350);

/*
*	User Functions
*/

sint32 UpdateTexlistSomething(NJS_TEXLIST* a1, NJS_TEXLIST* a2);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* UpdateTexlistSomething_p;

#endif