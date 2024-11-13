/*
*   Sonic Adventure Mod Tools (SA2B) - '/init.h'
*
*   Description:
*       Functions, utilities, & examples for initializing the
*   toolkit & the user mod.
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SAMT_INIT_H_
#define _SAMT_INIT_H_

/************************/
/*  Includes            */
/************************/
/** Core **/
#include <sa2b/modloader.h>

/** Utility **/
#include <sa2b/util/dllexport.h>
#include <sa2b/util/ml_type.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
/****** Base Init ***********************************************************/
/** Initializes core toolkit modules **/
void    SAMT_Init(const char* path, const HelperFunctions* pHelperFunctions);

EXTERN_END

#endif/*_SAMT_INIT_H_*/

/************************/
/*  Func Examples       */
/************************/
/*
*   Execute at game startup:
*
    EXPORT_DLL
    void __cdecl
    Init(const char* path, const HelperFunctions* pHelperFunctions)
    {
        SAMT_Init(path, pHelperFunctions);
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
*   Valid Mod Info ($ == SA2 or SADX):
*
    EXPORT_DLL
    ModInfo $ModInfo = { ML_VERSION };
*/
