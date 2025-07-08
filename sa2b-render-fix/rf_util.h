/*
*   SA2 Render Fix - '/rf_util.h'
*
*   Description:
*     Common Render Fix utilities.
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_UTIL
#define H_RF_UTIL

/************************/
/*  External Includes   */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/writemem.h>      /* write protected memory                           */
#include <samt/writeop.h>       /* write operator                                   */

/****** Ninja ***********************************************************************/
#include <samt/ninja/njcommon.h> /* ninja common                                    */
#include <samt/ninja/njmatrix.h> /* ninja matrix                                    */
#include <samt/ninja/njchunk.h>  /* ninja chunk                                     */

/************************/
/*  External Opaques    */
/************************/
/****** Texture Table ***************************************************************/
typedef struct prstable         TEX_PRSTABLE;

EXTERN_START

/************************/
/*  Enums               */
/************************/
/****** File Ownership **************************************************************/
typedef enum
{
    FOWN_GAME,                  /* game has file ownership                          */
    FOWN_RF,                    /* render fix has file ownership                    */
    FOWN_OTHER,                 /* another mod has file ownership                   */
}
eRFU_FILE_OWNER;

/************************/
/*  Functions           */
/************************/
/****** File Ownership **************************************************************/
/*
*   Description:
*     Swap two PRS table entries with each other, to fix issues with texture load
*   order.
*
*   Parameters:
*     - pPrsTable   : prs table to edit
*     - idx1        : entry index to swap 1
*     - idx2        : entry index to swap 2
*/
void    RF_SwapTexFileTableIndex( TEX_PRSTABLE* pTexTable, int idx1, int idx2 );

/****** Interpolation ***************************************************************/
/*
*   Description:
*     Interpolate 2 points with each other with a weight ratio
*
*   Parameters:
*     - pOutPt   : return pointer for new interpolated point
*     - pPt1     : pointer to point 1
*     - pPt2     : pointer to point 2
*     - ratioPt1 : weight ratio of point 1, point 2 will use a weight of ( 1.f - 'ratioPt1' )
*/
void    RFU_LerpPoints( NJS_POINT3* pOutPt, const NJS_POINT3* pPt1, const NJS_POINT3* pPt2, f32 ratioPt1 );

/****** Screen **********************************************************************/
/*
*   Description:
*     Calculate a 3D point in screenspace to a 2D point in screenspace. A 3D
*   screenspace point is calculated by using 'njCalcPoint' on a 3D worldspace point
*
*   Parameters:
*     - pInPos   : pointer to screenspace 3D point
*     - pOutPos  : return pointer for screenspace 2D point
*/
void    RFU_CalculateScreen( const NJS_POINT3* pInPos, NJS_POINT2* pOutPos );
/*
*   Description:
*     Project a 3D point in worldspace to a 2D point in screenspace. This is the same
*   as:
*     njCalcPoint(NULL, &pt3);
*     RFU_CalculateScreen(&pt3, &pt2);
*
*   Parameters:
*     - pInPos   : pointer to worldspace 3D point
*     - pOutPos  : return pointer for screenspace 2D point
*/
void    RFU_ProjectScreen( const NJS_POINT3* pInPos, NJS_POINT2* pOutPos );

/****** Matrix **********************************************************************/
/*
*   Description:
*     Calculate if a matrix has inverted scaling
*
*   Parameters:
*     - m       : matrix to calcluate, or '_nj_curr_matrix_' if 'NULL'
*/
bool    RFU_CalcInvertedMatrix( const NJS_MATRIX* m );

/****** File Ownership **************************************************************/
/*
*   Description:
*     Check ownership of a file contained in the 'gd_PC' folder.
*
*   Examples:
*     - RFU_GetFileOwnership("./resource/gd_PC/set_bigbogy_s.bin");
*
*   Paramters:
*     - pcPath      : 'gd_PC' path to file
*
*   Returns:
*     File owner enum value.
*/
eRFU_FILE_OWNER RFU_GetFileOwnership( const char* pcPath );

/************************************************************************************/
/*
*   Optional Mod Directory File Replacement
* 
*   Notes:
*     - The 'optional' folders act as their own 'gd_PC' folder.
*/

/****** Replace File ****************************************************************/
/*
*   Description:
*     Replace a generic file with an optional variant stored in an 'optional' mod
*   folder with mod order and ownership tests.
*
*   Notes:
*     - Texture files should use 'ReplaceTexture' or 'ReplacePvr'.
*     - Player models/motions should use 'ReplaceMdl' or 'ReplaceMtn'.
*
*   Examples:
*     - RFU_ReplaceFile("set0013_s.bin", "setfile_new");
*
*   Paramters:
*     - pcPath       : 'gd_PC' path to file
*     - pcOptiFolder : the 'optional' folder with the replacement file
*
*   Returns:
*     'true' on success; or 'false' if the file wasn't replaced.
*/
bool    RFU_ReplaceFile( const char* pcPath, const char* pcOptiFolder );

/****** Replace Texture *************************************************************/
/*
*   Description:
*     Replace a PRS texture file with an optional PAK variant stored in an
*   'optional' mod folder with mod order and ownership tests.
*
*   Examples:
*     - RFU_ReplaceTexture("SONICTEX", "sonictex_trial");
*
*   Parameters:
*     - pcTexName    : prs texture file name, excluding extension
*     - pcOptiFolder : the 'optional' folder with the replacement 'pak' file
*
*   Returns:
*     'true' on success; or 'false' if the file wasn't replaced.
*/
bool    RFU_ReplaceTexture( const char* pcTexName, const char* pcOptiFolder );
/*
*   Description:
*     Replace a single PVR/GVR texture with an optional PAK variant stored in an
*   'optional' mod folder with mod order and ownership tests.
*
*   Examples:
*     - RFU_ReplacePvr("zanki_sonic", "zanki_new");
*
*   Parameters:
*     - pcPvrName    : pvr/gvr texture file name, excluding extension
*     - pcOptiFolder : the 'optional' folder with the replacement 'pak' file
*
*   Returns:
*     'true' on success; or 'false' if the file wasn't replaced.
*/
bool    RFU_ReplacePvr( const char* pcPvrName, const char* pcOptiFolder );

/****** Replace Player File *********************************************************/
/*
*   Description:
*     Replace a player model file with an optional variant stored in an 'optional'
*   mod folder with mod order and ownership tests.
*
*   Notes:
*     - Also handles folder-based model replacement when checking ownership.
*
*   Examples:
*     - RFU_ReplaceMdl("TERIOSMDL", "plmdl_dc");
*
*   Parameters:
*     - pcMdlName    : player model file name, excluding extension
*     - pcOptiFolder : the 'optional' folder with the replacement model file
*
*   Returns:
*     'true' on success; or 'false' if the file wasn't replaced.
*/
bool    RFU_ReplaceMdl( const char* pcMdlName, const char* pcOptiFolder );
/*
*   Description:
*     Replace a player motion file with an optional variant stored in an 'optional'
*   mod folder with mod order and ownership tests.
*
*   Notes:
*     - Also handles folder-based motion replacement when checking ownership.
*
*   Examples:
*     - RFU_ReplaceMtn("MILESMTN", "plmtn_new");
*
*   Parameters:
*     - pcMtnName    : player motion file name, excluding extension
*     - pcOptiFolder : the 'optional' folder with the replacement model file
*
*   Returns:
*     'true' on success; or 'false' if the file wasn't replaced.
*/
bool    RFU_ReplaceMtn( const char* pcMtnName, const char* pcOptiFolder );

/****** Replace Model ***************************************************************/
/*
*   Description:
*     Replace a game's Chunk model with the data in a source .sa2mdl file contained
*   in RF's root 'model' folder.
*
*   Parameters:
*     - pDstModel   : destination model structure
*     - puSrcFile   : source file name (eg. "goalring" -> "/model/goalring.sa2mdl")
*
*   Returns:
*     'true' on success; or 'false' if the destination structure is too small.
*/
bool    RFU_ReplaceChunkModel( NJS_CNK_MODEL* pDstModel, const c8* puSrcFile );
/*
*   Description:
*     Replace a game's Chunk object with the data in a source .sa2mdl file contained
*   in RF's root 'model' folder.
*
*   Parameters:
*     - pDstObject  : destination object structure
*     - puSrcFile   : source file name (eg. "goalring" -> "/model/goalring.sa2mdl")
*
*   Returns:
*     'true' on success; or 'false' if the destination structure is too small.
*/
bool    RFU_ReplaceChunkObject( NJS_CNK_OBJECT* pDstObject, const c8* puSrcFile );

/************************/
/*  Macro               */
/************************/
/************************************************************************************/
/*
*   Change Task Displayer
*/
/****** Displayer Constants *********************************************************/
#define DISP                    (0x14) /* displayer                                 */
#define DISP_DELY               (0x1C) /* delayed displayer                         */
#define DISP_SORT               (0x20) /* sorted displayer                          */
#define DISP_LATE               (0x24) /* late displayer                            */
#define DISP_LAST               (0x28) /* last displayer                            */
#define DISP_SHAD               (0x2C) /* shadow displayer                          */

/****** Change Displayer ************************************************************/
/*
*   Description:
*     Change a 'mov' instruction to use a different displayer offset, for changing
*   Task displayer levels.
*
*   Parameters:
*     - addr        : mov instruction address
*     - disp        : displayer offset
*/
#define SwitchDisplayer(addr, disp)     WriteData((addr)+2, (disp), u8)

/************************************************************************************/
/*
*   Writeop
*/
/****** Modify Op *******************************************************************/
/*
*   Description:
*     Write a call instruction over a 'mov dword ptr' instruction for hooking
*   mid-function. This will likely be depricated at some point.
*
*   Parameters:
*     - addr        : address of 'mov' instruction
*     - func        : function to call
*/
#define WriteCallToMovDwordPtr(addr, func)              WriteNOP((addr), (addr) + 7); WriteCall((addr), (func))

/************************************************************************************/
/*
*   Function Wrappers (int -> type pointer)
*/
#define SwapTexFileTableIndex(_textable, _idx1, _idx2)  RF_SwapTexFileTableIndex((TEX_PRSTABLE*)(_textable), (_idx1), (_idx2))

EXTERN_END

#endif/*H_RF_UTIL*/
