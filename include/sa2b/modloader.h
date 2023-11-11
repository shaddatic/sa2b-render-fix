/*
*   Sonic Adventure Mod Tools (SA2B) - '/modloader.h'
*
*   Contains functions and definitions for the Mod Loader and its HelperFunctions
*
*   Contributors:
*   -   SA2 Mod Loader/Manager Team
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SAMT_MODLOADER_H_
#define _SAMT_MODLOADER_H_

/************************/
/*  Mod Loader Version  */
/************************/
#define MODLOADER_VER      (11)

/************************/
/*  Abstract Types      */
/************************/
#ifndef SAMT_INCLUDE_MODLOADER_NOABSTRACT
typedef int     ModInfo[10];
typedef void    HelperFunctions;

#endif /* SAMT_INCLUDE_MODLOADER_NOABSTRACT */

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Get installed mod-loader version **/
int         ML_GetVersion(void);

/*
*   Mod-Loader Version >= 4
*/
/** Get current save paths **/
const char* ML_GetMainSavePath(void);
const char* ML_GetChaoSavePath(void);

/*
*   Mod-Loader Version >= 7
*/
/** Returns active, replaced gd_PC path for given file **/
const char* ML_GetReplaceablePath(const char* path);

/** Manually replace a gd_PC file path **/
void        ML_ReplaceFile(const char* path, const char* pathNew);

/** Change title of SA2's main window **/
void        ML_SetWindowTitle(const wchar_t* wTitle);

/*
*   Mod-Loader Version >= 8
*/
/** Set scale and color of ML's debug text font **/
void        ML_SetDebugFontScale(float scale);
void        ML_SetDebugFontColor(uint32 color);

/** Register display of debug string **/
void        ML_DisplayDebugString(int njmLocation, const char* string);
void        ML_DisplayDebugStringF(int njmLocation, char* buffer, const char* format, ...);
void        ML_DisplayDebugInt(int njmLocation, int val, int nbDigits);

/*
*   Mod-Loader Version >= 10
*/
/** Register new character voice ADX file, returns ID of new voice line **/
uint16      ML_RegisterVoice(const char* fileJP, const char* fileEN);

/*
*   Mod-Loader Version >= 11
*/
/** Replace and swap textures inside a texture file in real time, 'file_path' must point to a valid image file (eg. PNG) **/
void        ML_ReplaceTexture(const char* prs_name, const char* tex_name, const char* file_path, uint32 gbix, uint32 width, uint32 height);

EXTERN_END

/************************/
/*  Macros              */
/************************/
#ifdef SAMT_INCLUDE_MODLOADER_MACROS
#ifdef __cplusplus

/** Data declarations **/
#define DataPointer(type, name, address)                            static auto& name = DataRef(type, address)
#define DataArray(type, name, address, len)                         static auto& name = DataAry(type, address, [len])

/** Function declarations **/
#define FunctionPointer(return_type, name, args, address)           static auto* name = FuncPtr(return_type, __cdecl   , args  , address)
#define StdcallFunctionPointer(return_type, name, args, address)    static auto* name = FuncPtr(return_type, __stdcall , args  , address)
#define FastcallFunctionPointer(return_type, name, args, address)   static auto* name = FuncPtr(return_type, __fastcall, args  , address)
#define ThiscallFunctionPointer(return_type, name, args, address)   static auto* name = FuncPtr(return_type, __thiscall, args  , address)
#define VoidFunc(name, address)                                     static auto* name = FuncPtr(void       , __cdecl   , (void), address)

#endif /* __cplusplus */
#endif /* SAMT_INCLUDE_MODLOADER_MACROS */

#endif /* _SAMT_MODLOADER_H_ */

/************************/
/*  Mod Examples        */
/************************/
/*
*   Execute at game startup:
*
    extern "C" __declspec(dllexport)
    void __cdecl
    Init(const char* pPath, const HelperFunctions* pHelperFunctions)
    {
        MT_Init(path, pHelperFunctions);
    }
*
*   Execute every rendered frame:
*
    extern "C" __declspec(dllexport)
    void __cdecl
    OnFrame()
    {
        
    }
*
*   Execute before the game processes input:
*
    extern "C" __declspec(dllexport)
    void __cdecl
    OnInput()
    {
        
    }
*
*   Execute when the game processes input:
*
    extern "C" __declspec(dllexport)
    void __cdecl
    OnControl()
    {
        
    }
*
*   Execute on game close:
*
    extern "C" __declspec(dllexport)
    void __cdecl
    OnExit(uint32 uExitCode, int a1, int a2)
    {
        
    }
*
*   Valid Mod Info ($ == SA2 or SADX):
* 
    extern "C" __declspec(dllexport)
    ModInfo $ModInfo = { MODLOADER_VER };
*/