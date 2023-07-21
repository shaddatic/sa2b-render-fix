/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/texture.h'
*
*   Contains structs and functions related to texture loading
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#pragma once

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Structures          */
/************************/
typedef struct
{
	char* pname;
	NJS_TEXLIST* ptexlist;
}
TEX_GVMTABLE;

/************************/
/*  Function Pointers   */
/************************/
FuncPtr(sint32, __fastcall, texLoadTextureGvmFile, (const char* fname, NJS_TEXLIST* ptlo), 0x44C350);

/************************/
/*  User Functions      */
/************************/
sint32 UpdateTexlistSomething(NJS_TEXLIST* a1, NJS_TEXLIST* a2);

/************************/
/*  User Function Ptrs  */
/************************/
#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* UpdateTexlistSomething_p;

#endif