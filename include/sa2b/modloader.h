/*
*   Sonic Adventure Mod Tools (SA2B) - '/modloader.h'
*
*   Description:
*       Contains functions and definitions for the Mod Loader
*   and its HelperFunctions.
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
/*  Includes            */
/************************/
#include <sa2b/util/ml_type.h>  /* Mod loader types                         */

/************************/
/*  Constants           */
/************************/
#define MODLOADER_VER      (12) /* Mod loader version                       */

/************************/
/*  Functions           */
/************************/
EXTERN_START
/****** Version >= 0 ********************************************************/
/** Get current HelperFunctions pointer **/
const HelperFunctions* ML_GetHelperFunctions( void );

/** Get installed mod-loader version **/
int32_t     ML_GetVersion( void );

/****** Version >= 4 ********************************************************/
/** Get current save paths **/
const char* ML_GetMainSavePath( void );
const char* ML_GetChaoSavePath( void );

/****** Version >= 7 ********************************************************/
/** Returns active, replaced gd_PC path for given file **/
const char* ML_GetReplaceablePath( const char* path );

/** Manually replace a gd_PC file path **/
void        ML_ReplaceFile( const char* path, const char* pathNew );

/** Change title of SA2's main window **/
void        ML_SetWindowTitle( const wchar_t* wTitle );

/****** Version >= 8 ********************************************************/
/** Set scale and color of ML's debug text font **/
void        ML_SetDebugFontScale( float scale    );
void        ML_SetDebugFontColor( uint32_t color );

/** Register display of debug string **/
void        ML_DisplayDebugString(  int njmLocation, const char* string                    );
void        ML_DisplayDebugStringF( int njmLocation, char* buffer, const char* format, ... );
void        ML_DisplayDebugInt(     int njmLocation, int val, int nbDigits                 );

/****** Version >= 10 *******************************************************/
/** Register new character voice ADX file, returns ID of new voice line **/
uint16_t    ML_RegisterVoice( const char* fileJP, const char* fileEN );

/****** Version >= 11 *******************************************************/
/** Replace and swap textures inside a texture file in real time, 'file_path' must point to a valid image file (eg. PNG) **/
void        ML_ReplaceTexture( const char* prs_name, const char* tex_name, const char* file_path, uint32_t gbix, uint32_t width, uint32_t height );

/****** Version >= 12 *******************************************************/
/** Reset given, replaceable file path to the default game directory **/
void        ML_ResetReplaceablePath( const char* fpath );

EXTERN_END

#endif/*_SAMT_MODLOADER_H_*/
