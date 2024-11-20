/*
*   Sonic Adventure Mod Tools (SA2B) - '/modloader.h'
*
*   Description:
*       Functions and definitions for the Mod Loader and its HelperFunctions.
*
*   Contributors:
*     - SA2 Mod Loader/Manager Team
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SAMT_MODLOADER
#define H_SAMT_MODLOADER

/************************/
/*  External Headers    */
/************************/
/****** Utility *********************************************************************/
#include <sa2b/util/ml_type.h>  /* Mod loader types                                 */

EXTERN_START

/************************/
/*  Constants           */
/************************/
/****** Mod Loader Version **********************************************************/
#define ML_VERSION          (14) /* supported Mod loader version                    */

/************************/
/*  Functions           */
/************************/
/****** Get Helper Functions *********************************************************/
/*
*   Get Mod Loader HelperFunctions pointer.
*
*   Returns:
*       Current HelperFunctions pointer, as passed into SAMT_Init().
*/
const HelperFunctions* ML_GetHelperFunctions( void );

/****** Version >= 0 ****************************************************************/
/*
*   Get currently installed Mod Loader version.
*
*   Returns:
*       Installed version of the mod loader.
*/
int32_t     ML_GetVersion( void );

/****** Version >= 4 ****************************************************************/
/*
*   Get current game save folder paths.
*
*   Returns:
*       String folder path to the game saves
*/
const char* ML_GetMainSavePath( void );
const char* ML_GetChaoSavePath( void );

/****** Version >= 7 ****************************************************************/
/*
*   Get a redirected/replaced file path.
*
*   Examples:
*       ML_GetReplaceablePath("./resource/gd_PC/sonictex.prs");
*
*   Parameters:
*     - fpath   : full, original path to file
*
*   Returns:
*       Current path to the file. If the file isn't replaced, 'fpath' is returned
*/
const char* ML_GetReplaceablePath( const char* fpath );
/*
*   Manually replace a file.
*
*   Examples:
*       ML_ReplaceFile("./resource/gd_PC/teriosmdl.prs", "./resource/gd_PC/new/shadowmdl.prs");
*
*   Parameters:
*     - fpath     : full default path to file
*     - fpath_new : new full path to file
*/
void        ML_ReplaceFile( const char* fpath, const char* fpath_new );
/*
*   Change title of games's main window.
*
*   Parameters:
*     - wtitle  : new wide string title
*/
void        ML_SetWindowTitle( const wchar_t* wtitle );

/****** Version >= 8 ****************************************************************/
/*
*   Set scale and color of Mod Loaders's debug font.
*
*   Parameters:
*     - scale   : scale of the font in pixels (not independent of screen resolution)
*     - color   : color in ARGB format (eg. 0xFF'EE'DD'CC)
*/
void        ML_SetDebugFontScale( f32       scale );
void        ML_SetDebugFontColor( uint32_t  color );
/*
*   Register the display of a debug string for one frame. They're drawn at the end
*   of the current frame.
*
*   Examples:
*       ML_DisplayDebugString(NJM_LOCATION(1, 1), "string");
*       ML_DisplayDebugInt(NJM_LOCATION(12, 15), 1234, 4);
*
*   Parameters:
*     - njmLocation : position of the string as a NJM_LOCATION macro
*     - string      : string to display
*     - val         : number value to display
*     - nbDigits    : number of digits to render
*/
void        ML_DisplayDebugString( int njmLocation, const char* string    );
void        ML_DisplayDebugInt(    int njmLocation, int val, int nbDigits );
/*
*   Register the display of a formatted debug string for one frame.
*
*   Parameters:
*     - njmLocation : position of the string as a NJM_LOCATION macro
*     - pBuf        : pointer to a string buffer
*     - szBuf       : size of the string buffer in bytes
*     - format      : string format
*     - ...         : arguments to string format
*/
void        ML_DisplayDebugStringF( int njmLocation, char* pBuf, size_t szBuf, const char* format, ... );

/****** Version >= 10 ***************************************************************/
/*
*   Register a new voice ADX file. This can then be used in the regular PlayVoice
*   function.
*
*   Examples:
*       ML_RegiserVoice("./voice_jap.adx", "./voice_eng.adx");
*
*   Parameters:
*     - fileJP  : path to japanese voice adx file
*     - fileEN  : path to english voice adx file
*
*   Returns:
*       The ID of the voice line
*/
uint16_t    ML_RegisterVoice( const char* fileJP, const char* fileEN );

/****** Version >= 11 ***************************************************************/
/*
*   Replace and swap textures inside a texture file. This will only be effective
*   while the texture file is unloaded.
*
*   Examples:
*       ML_ReplaceTexture("SONICTEX", "sonic_soapshoes", "./new_tex.png", 1120, 0, 0);
*
*   Parameters:
*     - prs_name  : name of the texture file (not including file type, eg. ".pak")
*     - tex_name  : name of the texture to replace
*     - file_path : path to the new texture (must be a valid image file, eg. PNG)
*     - gbix      : new global texture index value
*     - width     : force width of the new texture (optional if '0')
*     - width     : force height of the new texture (optional if '0')
*/
void        ML_ReplaceTexture( const char* prs_name, const char* tex_name, const char* file_path, uint32_t gbix, uint32_t width, uint32_t height );

/****** Version >= 12 ***************************************************************/
/*
*   Reset a replaced file path to its original path.
*
*   Examples:
*       ML_ResetReplaceablePath("./resource/gd_PC/stg10_fog.bin");
*
*   Parameters:
*     - fpath   : full, original path to file that has been replaced
*/
void        ML_ResetReplaceablePath( const char* fpath );

/****** Version >= 13 ***************************************************************/
/*
*   Push and pop the Ninja Motion interpolation fix for a set of motion calls.
*   Ensure 'pop' is called after drawing is complete, as the fix shouldn't run for
*   all Motions.
*/
void    ML_PushMotionInterpolationFix( void );
void    ML_PopMotionInterpolationFix(  void );

EXTERN_END

#endif/*H_SAMT_MODLOADER*/
