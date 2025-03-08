/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/init.h'
*
*   Description:
*     For initializing SAMT and setting up your exported mod functions.
*/
#ifndef H_SAMT_INIT
#define H_SAMT_INIT

/************************/
/*  Includes            */
/************************/
/****** Utility *********************************************************************/
#include <samt/util/dllexport.h>    /* export_dll                                   */
#include <samt/util/ml_type.h>      /* ml_helpfuncs                                 */

EXTERN_START

/************************/
/*  Prototypes          */
/************************/
/****** System Init *****************************************************************/
/*
*   Description:
*     Initialize SAMT and its core modules.
*
*   Notes:
*     - Should be called first in your mod's exported 'Init' function, using the
*       parameters as arguments for this function.
*
*   Parameters:
*     - pcPath      : path to this mod
*     - pHelpFuncs  : mod loader helperfunctions
*/
void    mtSystemInit( const char* pcPath, const ml_helpfuncs* pHelpFuncs );

EXTERN_END

#endif/*H_SAMT_INIT*/

/************************/
/*  Func Examples       */
/************************/
/*
*   Execute at game startup:
*
    EXPORT_DLL
    void __cdecl
    Init(const char* pcPath, const ml_helpfuncs* pHelpFuncs)
    {
        mtSystemInit( pcPath, pHelpFuncs );
    }
*
*   Execute every rendered frame:
*
    EXPORT_DLL
    void __cdecl
    OnFrame(void)
    {

    }
*
*   Execute before the game processes input:
*
    EXPORT_DLL
    void __cdecl
    OnInput(void)
    {

    }
*
*   Execute when the game processes input:
*
    EXPORT_DLL
    void __cdecl
    OnControl(void)
    {

    }
*
*   Execute on game close:
*
    EXPORT_DLL
    void __cdecl
    OnExit(u32 code, s32 a1, s32 a2)
    {
        
    }
*
*   Execute on device lost:
*
    EXPORT_DLL
    OnRenderDeviceLost(void)
    {
        
    }
*
*   Execute on device reset:
*
    EXPORT_DLL
    OnRenderDeviceReset(void)
    {
        
    }
*
*   Execute on scene start, but before screen clear:
*
    EXPORT_DLL
    OnRenderSceneStart(void)
    {
        
    }
*
*   Execute on scene end:
*
    EXPORT_DLL
    OnRenderSceneEnd(void)
    {
        
    }
*
*   Valid Mod Info (# == SA2 or SADX):
*
    EXPORT_DLL
    ml_modinfo #ModInfo = { ML_VERSION };
*/
