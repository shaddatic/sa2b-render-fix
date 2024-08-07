/*
*   Sonic Adventure Mod Tools (SA2B) - '/util/modmnt.h'
*
*   Description:
*     For mounting other SA2 mod DLLs.
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_UTIL_MODMNT
#define H_UTIL_MODMNT

EXTERN_START

/************************/
/*  Function Types      */
/************************/
/****** Mod Functions ***************************************************************/
typedef void(__cdecl fn_mod_func)(void);
typedef void(__cdecl fn_mod_exit)(u32 code, s32 a1, s32 a2);

/************************/
/*  Structures          */
/************************/
/****** Mod Handle ******************************************************************/
typedef struct mod_handle
{
    dll_handle* pDLL;                 /* DLL handle                                 */

    fn_mod_func* OnInput;             /* OnInput mod function                       */
    fn_mod_func* OnControl;           /* OnControl mod function                     */
    fn_mod_func* OnFrame;             /* OnFrame mod function                       */
    fn_mod_exit* OnExit;              /* OnExit mod function                        */

    fn_mod_func* OnRenderDeviceLost;  /* OnRenderDeviceLost mod function            */
    fn_mod_func* OnRenderDeviceReset; /* OnRenderDeviceReset mod function           */
    fn_mod_func* OnRenderSceneStart;  /* OnRenderSceneStart mod function            */
    fn_mod_func* OnRenderSceneEnd;    /* OnRenderSceneEnd mod function              */
}
mod_handle;

/************************/
/*  Prototypes          */
/************************/
/****** Mount/Free Mod DLL **********************************************************/
/*
*   Description:
*     Mounts a mod DLL and handles ModInfo parameters and calls 'Init' with the
*   'uPath' argument and the HelperFunctions* given to 'SAMT_Init'.
*
*   Parameters:
*     - uPath   : path to mod folder containing DLL file
*     - uDLL    : name of the DLL
*
*   Returns:
*     A new mod handle, or nullptr of the DLL was not found in 'uPath' or it was not
*   a valid mod DLL
*/
mod_handle* MOD_Mount( const utf8* uPath, const utf8* uDLL );
/*
*   Description:
*     Unmount and free a mod DLL and handle info.
*
*   Parameters:
*     - pModHdl : mod handle pointer
*/
void    MOD_Unmount( mod_handle* pModHdl );

/****** DLL Export ******************************************************************/
/*
*   Description:
*     Get a mod DLL export via a mod_handle. Calls 'DLL_GetExport' internally.
*
*   Parameters:
*     - pModHdl : mod handle pointer
*     - cExName : DLL export identifier
* 
*   Returns:
*     A pointer to the DLL export, or nullptr if no export is found
*/
void*   MOD_GetExport( const mod_handle* pModHdl, const char* cExName );

EXTERN_END

#endif/*H_SAMT_MODMNT*/
