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
/*  Functions           */
/************************/
EXTERN_START
/** Get installed mod-loader version **/
int32_t     ML_GetVersion(void);

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
void        ML_SetDebugFontColor(uint32_t color);

/** Register display of debug string **/
void        ML_DisplayDebugString(int njmLocation, const char* string);
void        ML_DisplayDebugStringF(int njmLocation, char* buffer, const char* format, ...);
void        ML_DisplayDebugInt(int njmLocation, int val, int nbDigits);

/*
*   Mod-Loader Version >= 10
*/
/** Register new character voice ADX file, returns ID of new voice line **/
uint16_t    ML_RegisterVoice(const char* fileJP, const char* fileEN);

/*
*   Mod-Loader Version >= 11
*/
/** Replace and swap textures inside a texture file in real time, 'file_path' must point to a valid image file (eg. PNG) **/
void        ML_ReplaceTexture(const char* prs_name, const char* tex_name, const char* file_path, uint32_t gbix, uint32_t width, uint32_t height);

EXTERN_END

#endif/*_SAMT_MODLOADER_H_*/
