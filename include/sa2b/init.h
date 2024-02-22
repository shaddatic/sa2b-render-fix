/*
*   Sonic Adventure Mod Tools (SA2B) - '/init.h'
*
*   Description:
*       Functions, utilities, & examples for initializing the
*   toolkit & the user mod.
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
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
/****** Global Init *********************************************************/
/** Initializes entire Toolkit & all modules **/
void    SAMT_Init(const char* path, const HelperFunctions* pHelpFuncs);

/****** Individual **********************************************************/
/** Mod path **/
void    SetModPath(const char* path);

/** Init Mod-Loader module **/
void    ML_Init(const HelperFunctions* pHelpFuncs);

/** Init D3D control module **/
void    D3D_InitRenderDevice();

/** Init SAMT input module **/
void    InputInit();

/** Init MT random number generator **/
void    mtRandAutoSeeds();

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
    Init(const char* path, const HelperFunctions* pHelpFuncs)
    {
        SAMT_Init(path, pHelpFuncs);
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
    OnExit(uint32_t uExitCode, int a1, int a2)
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
    ModInfo $ModInfo = { MODLOADER_VER };
*/
