/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/texture.h'
*
*   Contains structs and functions related to texture loading.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SA2B_TEXTURE
#define H_SA2B_TEXTURE

/************************/
/*  External Headers    */
/************************/
#include <sa2b/ninja/njcommon.h>

EXTERN_START

/************************/
/*  Structures          */
/************************/
typedef struct prstable
{
    char*        pname;
    NJS_TEXLIST* ptexlist;
}
TEX_PRSTABLE;

typedef NJS_TEXLIST**      TEX_TEXTABLE;

/************************/
/*  Functions           */
/************************/
/****** Texname Buffer **************************************************************/
#define texname_tex         DATA_ARY(NJS_TEXNAME, 0x01940870, [512])

/************************/
/*  Functions           */
/************************/
/****** Texture File ****************************************************************/
/*
*   Description:
*     Load a texture PRS or PAK file 'fname' into the NJS_TEXLIST 'ptlo'
*
*   Parameters:
*     - fname   : name of the texture file, excluding file extension
*     - ptlo    : pointer to an NJS_TEXLIST to load the textures into
*
*   Returns:
*     '1' on success, '-1' on failure
*/
int32_t  texLoadTexturePrsFile( const char* fname, NJS_TEXLIST* ptlo );

/****** PVM Table *******************************************************************/
/*
*   Description:
*     Loads texture file 'pname' into 'ptexlist' in each 'pPrsList' entry, then
*   copies the TEXNAME information into every texlist contained in 'pTexLists'
*
*   Parameters:
*     - pPrsList  : array of TEX_PVMTABLE entries, ending with a null entry
*     - pTexLists : array of pointers to NJS_TEXLIST* arrays, all ending in nullptrs
*/
void    texLoadTexturePrsList( TEX_PRSTABLE* pPrsList, TEX_TEXTABLE* pTexLists );
/*
*   Description:
*     Release all textures in 'ptexlist' in each 'pPrsList' entry and their copies in
*   each NJS_TEXLIST entry in 'pTexLists'
* 
*   Parameters:
*     - pPrsList  : array of TEX_PVMTABLE entries, ending with a null entry
*     - pTexLists : array of pointers to NJS_TEXLIST* arrays, all ending in nullptrs
*/
void    texReleaseTexturePrsList( TEX_PRSTABLE* pPrsList, TEX_TEXTABLE* pTexLists );

/****** Create TexList **************************************************************/
/*
*   Description:
*     Allocates a new texlist & texname list with as many entries as their are
*   textures in 'fname', and loads 'fname' into it
*
*   Parameters:
*     - fname   : name of the texture file, excluding file extension
*
*   Returns:
*     A new NJS_TEXLIST, or 'nullptr' on failure to find file
*/
NJS_TEXLIST* texCreateTexlist( const char* fname );
/*
*   Description:
*     Frees texlists created by 'texCreateTexlist'. Also releases all textures
*   before freeing
*
*   Parameters:
*     - ptlo    : pointer to an NJS_TEXLIST to free
*/
void         texFreeTexlist( NJS_TEXLIST* ptlo );

/****** Utility *********************************************************************/
/*
*   Description:
*     Copies TexName entries with matching filenames from 'pTexSrc' to 'pTexDst'.
*   Does not copy texture data, only NJS_TEXNAME entries and pointers
*
*   Parameters:
*     - pTexDst : texlist to copy into
*     - pTexSrc : texlist to copy from
*/
void    texCopyTexture( NJS_TEXLIST* pTexDst, const NJS_TEXLIST* pTexSrc );

/****** Internal Functions **********************************************************/
/*
*   Description:
*     Load texture PAK file 'fname' into the NJS_TEXLIST 'ptlo'
*
*   Parameters:
*     - fname   : name of the texture file, excluding file extension
*     - ptlo    : pointer to an NJS_TEXLIST to load the textures into
*
*   Returns:
*     '1' on success, '-1' on failure
*/
int32_t  LoadPakMEM( const char* fname, NJS_TEXLIST* ptlo );
/*
*   Description:
*     Load texture PRS file 'fname' into the NJS_TEXLIST 'ptlo'
*
*   Parameters:
*     - fname   : name of the texture file, excluding file extension
*     - ptlo    : pointer to an NJS_TEXLIST to load the textures into
*
*   Returns:
*     '1' on success, '-1' on failure
*/
int32_t  LoadPrsMEM( const char* fname, NJS_TEXLIST* ptlo );

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/****** Function Pointer ************************************************************/
#   define texLoadTexturePrsFile_p          FUNC_PTR(int32_t     , __fastcall, (const char*, NJS_TEXLIST*), 0x0044C350)
#   define texCreateTexlist_p               FUNC_PTR(NJS_TEXLIST*, __fastcall, (const char*)              , 0x0044C510)

/****** User-Function Pointer *******************************************************/
#   define texLoadTexturePrsList_p          ((void*)0x0044C7B0)
#   define texReleaseTexturePrsList_p       ((void*)0x0044C810)
#   define texCopyTexture_p                 ((void*)0x0044C880)
#   define LoadPakMEM_p                     ((void*)0x00430B10)
#   define LoadPrsMEM_p                     ((void*)0x0044C620)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_TEXTURE*/
