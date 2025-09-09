/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/init.h'
*
*   Description:
*     For initializing SAMT and setting up your exported mod functions.
*/
#ifndef H_SAMT_INIT
#define H_SAMT_INIT

/********************************/
/*  Includes                    */
/********************************/
/****** Utility *********************************************************************************/
#include <samt/util/dllexport.h>        /* export_dll                                           */

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** Mod Loader ******************************************************************************/
typedef struct ml_helpfuncs             ml_helpfuncs;   /* helperfunctions                      */

/********************************/
/*  Prototypes                  */
/********************************/
/****** System Init *****************************************************************************/
/*
*   Description:
*     Initialize SAMT and its core modules.
*
*   Notes:
*     - Should be called first in your mod's exported 'Init' function, using the parameters as
*       arguments for this function.
*     - The arguments should not be used as-is, instead call this then use the dedicated SAMT
*       functions to access them.
*
*   Parameters:
*     - puPath      : path to this mod
*     - pHelpFuncs  : mod loader helperfunctions
*     - ixMod       : mod position index
*/
void    mtSystemInit( const c8* puPath, const ml_helpfuncs* pHelpFuncs, usize ixMod );

EXTERN_END

#endif/*H_SAMT_INIT*/

/********************************/
/*  Export Examples             */
/********************************/
/****** Predate Mod Loader Versions *************************************************************/
/*
*   Execute at game startup:
*
    EXPORT_DLL
    void __cdecl
    Init(const c8* puPath, const ml_helpfuncs* pHelpFuncs, usize ixMod)
    {
        mtSystemInit( puPath, pHelpFuncs, ixMod );
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
*/
/****** Mod Loader Version >= ~8 ****************************************************************/
/*
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
    void __cdecl
    OnRenderDeviceLost(void)
    {
        
    }
*
*   Execute on device reset:
*
    EXPORT_DLL
    void __cdecl
    OnRenderDeviceReset(void)
    {
        
    }
*
*   Execute on scene start, but before screen clear:
*
    EXPORT_DLL
    void __cdecl
    OnRenderSceneStart(void)
    {
        
    }
*
*   Execute on scene end:
*
    EXPORT_DLL
    void __cdecl
    OnRenderSceneEnd(void)
    {
        
    }
*/
