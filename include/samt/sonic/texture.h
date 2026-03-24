/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/texture.h'
*
*   Description:
*     The game's texture module, for loading textures and other texture utilities.
*/
#ifndef H_SA2B_TEXTURE
#define H_SA2B_TEXTURE

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Structures                  */
/********************************/
/****** Pvm Table *******************************************************************************/
typedef struct pvmtable
{
    char*        pname;             /* pvm file name                                            */
    NJS_TEXLIST* ptexlist;          /* texlist                                                  */
}
TEX_PVMTABLE;

/********************************/
/*  Game Refs                   */
/********************************/
/****** Texname Buffer **************************************************************************/
#define texname_tex                 DATA_ARY(NJS_TEXNAME, 0x01940870, [512])

/********************************/
/*  Prototypes                  */
/********************************/
/****** Texture File ****************************************************************************/
/*
*   Description:
*     Load a PVM, PRS, or PAK (HD only) texture file into a texlist.
*
*   Parameters:
*     - fname           : name of the texture file, excluding file extension
*     - ptlo            : pointer to an NJS_TEXLIST to load the textures into
*
*   Returns:
*     '1' on success; or '-1' on failure.
*/
i32     texLoadTexturePvmFile( const char* fname, NJS_TEXLIST* ptlo );

/****** PVM Table *******************************************************************************/
/*
*   Description:
*     Load an array of PVM, PRS, or PAK (HD only) texture files into set texlists, then
*   distribute the loaded textures to a list of lists of texlists by the texture names.
*
*   Parameters:
*     - pvmtbls         : list of pvm entries, ending with null
*     - pptlos          : list of texlist lists, each ending with null
*/
void    texLoadTexturePvmList( TEX_PVMTABLE pvmtbls[], NJS_TEXLIST** pptlos[] );
/*
*   Description:
*     Release all textures as loaded by 'texLoadTexturePvmList'.
* 
*   Parameters:
*     - pvmtbls         : list of pvm entries, ending with null
*     - pptlos          : list of texlist lists, each ending with null
*/
void    texReleaseTexturePvmList( TEX_PVMTABLE pvmtbls[], NJS_TEXLIST** pptlos[] );

/****** Create TexList **************************************************************************/
/*
*   Description:
*     Allocates a new texlist & texname list with as many entries as their are textures in
*   'fname', and loads 'fname' into it.
*
*   Parameters:
*     - fname           : name of the texture file, excluding file extension
*
*   Returns:
*     A new texlist; or 'nullptr' on failure to find file.
*/
NJS_TEXLIST* texCreateTexlist( const char* fname );
/*
*   Description:
*     Frees texlists created by 'texCreateTexlist'. Also releases all textures before freeing.
*
*   Parameters:
*     - ptlo            : texlist
*/
void    texFreeTexlist( NJS_TEXLIST* ptlo );

/****** Utility *********************************************************************************/
/*
*   Description:
*     Copies TexName entries with matching filenames from 'pTexSrc' to 'pTexDst'. Does not copy
*   texture data, only NJS_TEXNAME entries and pointers.
*
*   Parameters:
*     - pTexDst         : texlist destination
*     - pTexSrc         : texlist source
*/
void    texCopyTexture( NJS_TEXLIST* pTexDst, const NJS_TEXLIST* pTexSrc );

/****** Internal Functions **********************************************************************/
/*
*   Description:
*     Load a PAK texture file into a texlist.
*
*   Parameters:
*     - fname           : name of the texture file, excluding file extension
*     - ptlo            : texlist
*
*   Returns:
*     '1' on success; or '-1' on failure.
*/
i32     LoadPakMEM( const char* fname, NJS_TEXLIST* ptlo );
/*
*   Description:
*     Load a PRS texture file into a texlist.
*
*   Parameters:
*     - fname           : name of the texture file, excluding file extension
*     - ptlo            : texlist
*
*   Returns:
*     '1' on success; or '-1' on failure.
*/
i32     LoadPrsMEM( const char* fname, NJS_TEXLIST* ptlo );

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Pointers           */
/********************************/
/****** Function Pointers ***********************************************************************/
#define texLoadTexturePvmFile_p          FUNC_PTR(i32         , __fastcall, (const char*, NJS_TEXLIST*), 0x0044C350)
#define texCreateTexlist_p               FUNC_PTR(NJS_TEXLIST*, __fastcall, (const char*)              , 0x0044C510)

/****** Usercall Pointers ***********************************************************************/
#define texLoadTexturePvmList_p          ((void*)0x0044C7B0) /* ###(EAX,STK)                    */
#define texReleaseTexturePvmList_p       ((void*)0x0044C810) /* ###(ECX,EAX)                    */
#define texCopyTexture_p                 ((void*)0x0044C880) /* ###(ECX,STK)                    */
#define LoadPakMEM_p                     ((void*)0x00430B10) /* EAX(EAX,STK)                    */
#define LoadPrsMEM_p                     ((void*)0x0044C620) /* EAX(STK,ECX)                    */

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_TEXTURE*/
