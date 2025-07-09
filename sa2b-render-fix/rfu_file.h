/*
*   SA2 Render Fix - '/rfu_file.h'
*
*   Description:
*     File utility functions.
*/
#ifndef H_RF_UTIL_FILE
#define H_RF_UTIL_FILE

EXTERN_START

/********************************/
/*  Enums                       */
/********************************/
/****** File Ownership **************************************************************************/
typedef enum
{
    FOWN_ERROR = -1,                /* something went wrong                                     */

    FOWN_GAME,                      /* game has file ownership                                  */
    FOWN_RF,                        /* render fix has file ownership                            */
    FOWN_OTHER,                     /* another mod has file ownership                           */
}
eRFU_FOWN;

/********************************/
/*  Prototypes                  */
/********************************/
/****** File Ownership **************************************************************************/
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
eRFU_FOWN   RFU_GetFileOwnership( const c7* pcPath );

/****** Replace File ****************************************************************************/
/*
*   Description:
*     Replace a generic file with an optional variant stored in an 'optional' mod folder with
*   mod order and ownership tests.
*
*   Notes:
*     - Texture files should use 'ReplaceTexture' or 'ReplacePvr'.
*     - Player models/motions should use 'ReplacePlayerFile'.
*
*   Examples:
*     - RFU_ReplaceFile("set0013_s.bin", "setfile_new");
*
*   Paramters:
*     - pcGdPath     : 'gd_PC' path to file
*     - pcOptiFolder : the 'optional' folder with the replacement file
*
*   Returns:
*     'true' on success; or 'false' if the file wasn't replaced.
*/
bool    RFU_ReplaceFile( const c7* pcGdPath, const c7* pcOptiFolder );

/****** Replace Texture *************************************************************************/
/*
*   Description:
*     Replace a PRS texture file with an optional PAK variant stored in an 'optional' mod
*   folder with mod order and ownership tests.
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
bool    RFU_ReplaceTexture( const c7* pcTexName, const c7* pcOptiFolder );
/*
*   Description:
*     Replace a single PVR/GVR texture with an optional PAK variant stored in an 'optional' mod
*   folder with mod order and ownership tests.
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
bool    RFU_ReplacePvr( const c7* pcPvrName, const c7* pcOptiFolder );

/****** Replace Player File *********************************************************************/
/*
*   Description:
*     Replace player model/motion file with a variant stored in an 'optional' mod folder with
*   mod order and ownership tests.
*
*   Parameters:
*     - pcPrsName   : player file name, eg. 'SONICMDL'
*     - pcPrsName   : optional directory, eg. 'plmdl_dc'
*
*   Returns:
*     'true' if the replacement was successful; or 'false' if it wasn't possible.
*/
bool    RFU_ReplacePlayerPrs( const c7* pcPrsName, const c7* pcOptiFolder );

EXTERN_END

#endif/*H_RF_UTIL_FLOAT*/
