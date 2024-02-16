/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/texture.h'
*
*   Contains structs and functions related to texture loading.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_TEXTURE_H_
#define _SA2B_TEXTURE_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Structures          */
/************************/
typedef struct textable
{
    char* pname;
    NJS_TEXLIST* ptexlist;
}
TEX_FILETABLE;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Returns '-1' on failure, or '1' on success **/
int32_t  texLoadTextureFile(const char* fname, NJS_TEXLIST* ptlo);

/** Loads each 'pTexTables' entry, then copies its TexNames into every TexList in 'pTexListLists'.
    All arrays must end with a NULL entry. Free also NULLs texture info inside 'pTexListLists'. **/
void    texLoadTextureLists(TEX_FILETABLE* pTexTables, NJS_TEXLIST*** pTextureLists);
void    texFreeTextureLists(TEX_FILETABLE* pTexTables, NJS_TEXLIST*** pTextureLists);

/** Copies TexName entries with matching filenames from Src to Dst **/
void    texCopyTexture(NJS_TEXLIST* pTexDst, const NJS_TEXLIST* pTexSrc);

/** Loads file and creates a correctly sized TexList, use 'texFreeTexture()' to release **/
NJS_TEXLIST*    texCreateTextureFile(const char* fname);
void            texFreeTexture(NJS_TEXLIST* ptlo);

/** Internal Funcs **/
/** Returns '0' on failure, '1' on success **/
int32_t  texLoadTexturePakFile(const char* fname, NJS_TEXLIST* ptlo);
/** Returns '-1' on failure, or '1' on success **/
int32_t  texLoadTexturePrsFile(const char* fname, NJS_TEXLIST* ptlo);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptr **/
#define texLoadTextureFile_p        FuncPtr(int32_t      , __fastcall, (const char*, NJS_TEXLIST*), 0x0044C350)
#define texCreateTextureFile_p      FuncPtr(NJS_TEXLIST*, __fastcall, (const char*)              , 0x0044C510)

/** User-Function ptr **/
EXTERN const void* const texLoadTextureLists_p;
EXTERN const void* const texFreeTextureLists_p;
EXTERN const void* const texCopyTexture_p;
EXTERN const void* const texLoadTexturePakFile_p;
EXTERN const void* const texLoadTexturePrsFile_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_TEXTURE_H_ */
