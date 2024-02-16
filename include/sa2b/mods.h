/*
*   Sonic Adventure Mod Tools (SA2B) - '/mods.h'
*
*   Contains functions for interacting with other mods
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SAMT_MODS_H_
#define _SAMT_MODS_H_

/************************/
/*  Abstract Types      */
/************************/
/** Handle types **/
typedef void                mod_handle;
typedef void                dll_handle;

/** Config type **/
typedef struct _config      config;

/************************/
/*  Mod Functions       */
/************************/
EXTERN_START
/*
*   Mod-Loader Version >= 9
* 
*   (In Order of Preferability)
* 
*   ID      : Mod's set ID
*   Dll     : Mod's .dll name
*   Name    : Mod's name
*/
/** Get mod handle **/
mod_handle* ModGetHandleID(const char* pID);
mod_handle* ModGetHandleDll(const char* pDllName);
mod_handle* ModGetHandleName(const char* pName);

/** Get total number of mods in active modlist **/
int         ModGetTotalNumber();

/** Get mod handle by active modlist postion **/
mod_handle* ModGetHandlePosition(int index);

/** Simple 'if exist' functions **/
bool        ModCheckID(const char* pID);
bool        ModCheckDll(const char* pDllName);
bool        ModCheckName(const char* pName);

/** Get dll handle **/
dll_handle* ModGetDllHandle(const mod_handle* pMod);

/** Get exported data pointers **/
void*       ModGetExport(const mod_handle* pMod, const char* pExportName);

/** Get external config files **/
config*     ModGetConfig(const mod_handle* pMod);

/** Get Mod Info **/
const char* ModGetName(const mod_handle* pMod);
const char* ModGetAuthor(const mod_handle* pMod);
const char* ModGetDescription(const mod_handle* pMod);
const char* ModGetVersion(const mod_handle* pMod);
const char* ModGetPath(const mod_handle* pMod); /* Local path to mod. eg. '/mods/f1/f2' */
const char* ModGetID(const mod_handle* pMod);

/** Check if mod has redirected save locations **/
bool        ModCheckSaveChangeGame(const mod_handle* pMod);
bool        ModCheckSaveChangeChao(const mod_handle* pMod);

/** (Ex)press **/
#define     ModGetExportEx(mod, type, exname) (type*)ModGetExport(mod, exname)

/************************/
/*  Mod DLL Functions   */
/************************/
/** Get already mounted dll **/
dll_handle* DllGetHandle(const char* pDllName);

/** Mount a global dll file, via name or path **/
dll_handle* DllMountGlobal(const char* pDllName);

/** Mount a dll file inside the mod's local folder, also runs 'Init' if available **/
dll_handle* DllMount(const char* pDllName);

/** Run other mod functions **/
void        DllRunOnInput(const dll_handle* pDll);
void        DllRunOnControl(const dll_handle* pDll);
void        DllRunOnFrame(const dll_handle* pDll);

/** Get exported data pointers **/
void*       DllGetExport(const dll_handle* pDll, const char* pExportName);

/** Unmount Dll **/
void        DllUnmount(dll_handle* pDll);

/** (Ex)press **/
#define     DllGetExportEx(dll, type, exname) (type*)DllGetExport(dll, exname)

EXTERN_END

#endif /* _SAMT_MODS_H_ */
