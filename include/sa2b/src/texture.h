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
typedef struct gvmtable
{
	char* pname;
	NJS_TEXLIST* ptexlist;
}
TEX_GVMTABLE;

/************************/
/*  Function Pointers   */
/************************/
FuncPtr(sint32,         __fastcall, texLoadTextureGvmFile, (const char* fname, NJS_TEXLIST* ptlo), 0x0044C350);

/** Loads file and creates a correctly sized TexList, use 'texFreeTexture()' to release **/
FuncPtr(NJS_TEXLIST*,   __thiscall, texCreateTextureGvmFile, (const char* fname), 0x0044C510);

/************************/
/*  User Functions      */
/************************/
/** Loads Gvm Table then copies TexName entries with matching filenames into pTexLists **/
void    texLoadTextureGvmTable(TEX_GVMTABLE* pGvmTable, NJS_TEXLIST*** pTexLists);

/** Copies TexName entries with matching filenames from Src to Dst **/
void    texCopyTexture(NJS_TEXLIST* pTexDst, NJS_TEXLIST* pTexSrc);

/************************/
/*  Functions           */
/************************/
void    texFreeTexture(NJS_TEXLIST* ptlo);

/************************/
/*  User Function Ptrs  */
/************************/
#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* texLoadTextureGvmTable_p;

extern const void* texCopyTexture_p;

#endif