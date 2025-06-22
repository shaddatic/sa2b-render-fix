/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/modloader.h'
*
*   Description:
*     Functions and definitions for the Mod Loader and its HelperFunctions.
*/
#ifndef H_SAMT_MODLOADER
#define H_SAMT_MODLOADER

/********************************/
/*  External Headers            */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njdebug.h>         /* njmlocation                                          */

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** Helper Functions ************************************************************************/
typedef struct HelperFunctions          HelperFunctions; /* mod loader helper functions         */

/********************************/
/*  Constants                   */
/********************************/
/****** Current Version *************************************************************************/
#define ML_VERSION                      (16) /* samt max feature support version                */

/****** Minimum Versions ************************************************************************/
#define ML_MINVER_SAVEPATH              ( 4) /* minimum version for replace save path           */
#define ML_MINVER_REPLFILE              ( 7) /* minimum version for replace file                */
#define ML_MINVER_DEBUG                 ( 8) /* minimum version for debug text                  */
#define ML_MINVER_MODINFO               ( 9) /* minimum version for mod info                    */
#define ML_MINVER_SETTINGS              ( 9) /* minimum version for settings struct             */
#define ML_MINVER_REGVOICE              (10) /* minimum version for register voice              */
#define ML_MINVER_REPLTEX               (11) /* minimum version for replace texture             */
#define ML_MINVER_RESETFILE             (12) /* minimum version for reset replaced file         */
#define ML_MINVER_EXLIBPATH             (15) /* minimum version for exlibpath                   */
#define ML_MINVER_FILEMODIX             (16) /* minimum version for file mod index              */

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>        /* ninja common                                         */

#ifdef __cplusplus
/****** Std Cpp *********************************************************************************/
#include <string>                       /* cpp string                                           */
#endif

/********************************/
/*  Types                       */
/********************************/
/****** Wstring *********************************************************************************/
#ifdef __cplusplus
typedef std::wstring                    ml_std_wstring;
#else
typedef byte                            ml_std_wstring[24];
#endif

/********************************/
/*  Enums                       */
/********************************/
/****** Mod Loader User Settings ****************************************************************/
typedef enum ml_screenmode
{
    ML_SCREENMD_WINDOWED,
    ML_SCREENMD_FULLSCREEN,
    ML_SCREENMD_BORDERLESS,
    ML_SCREENMD_CUSTOM,
}
ml_screenmode;

/********************************/
/*  Structures                  */
/********************************/
/****** Mod Loader User Settings ****************************************************************/
typedef struct ml_scrnres
{
    s32 x, y;
}
ml_scrnres;

/****** Mod Loader User Settings ****************************************************************/
typedef struct ml_settings
{
    /****** Mod Loader Version >= 9 *********************************************************/    
    struct
    {
        bool             console;       /* output debug to console                          */
        bool              screen;       /* output debug to screen text                      */
        bool                file;       /* output debug to text file                        */
        bool            crashdmp;       /* create crash dumps                               */
    }
    Debug;

    bool           pausefocusloss;      /* pause game when window is not in focus           */
    bool             noexitprompt;      /* don't prompt when closing window                 */
    s32                 screennum;      /* display number                                   */
    bool               borderless;      /* use borderless window                            */
    bool               fullscreen;      /* use fullscreen                                   */
    bool                skipintro;      /* skip game intro                                  */
    bool                  noasync;      /* no asynchronous file loading                     */
    ml_scrnres         resolution;      /* screen resolution                                */

    // language settings
    struct
    {
        s32                speech;      /* set speech language                              */
        s32                  text;      /* set text language                                */
    }
    Language;

    bool         customwindowflag;      /* using custom window size                         */
    ml_scrnres   customwindowsize;      /* custom window size values                        */

    bool         resizewindowflag;      /* allow resizing of game window                    */
    bool           fixaspectratio;      /* deprecated, use 'screenStretch'                  */
    bool                 limitfps;      /* frame limiter                                    */

    // test spawn settings
    struct
    {
        s32           stagenum;         /* stage number to spawn into                       */
        s32             plnum1;         /* player 1 character                               */
        s32             plnum2;         /* player 2 character                               */

        bool         setposflag;        /* use custom spawn pos                             */
        s32          px, py, pz;        /* custom spawn position, xyz                       */
        Angle        ay;                /* custom spawn angle, Y                            */

        s32            eventnum;        /* event number                                     */
        s32             savenum;        /* save number                                      */
    }
    TestSpawn;

    bool              extendedvbuf;     /* using extended vertex buffer                     */

    // fixes
    bool                   envfix;      /* environment map fix                              */
    bool            screenfadefix;      /* screen fading fix                                */
    bool               citycarfix;      /* iGPU city escape tram car fix                    */
    bool                  ptclfix;      /* iGPU particle fix                                */

    // screen mode
    bool       keepaspectonresize;      /* deprecated, use 'aspectstretch'                  */
    ml_screenmode      screenmode;      /* current screen mode                              */

    /****** Mod Loader Version >= 14 ********************************************************/
    bool              noborderimg;      /* don't use border image PNG                       */
    bool            aspectstretch;      /* allow stretching of the game                     */

    /****** Mod Loader Version >= 15 ********************************************************/
    ml_std_wstring      exlibpath;      /* std::wstring, external library path              */
}
ml_settings;

/********************************/
/*  Prototypes                  */
/********************************/
/****** HelperFuncs *****************************************************************************/
/*
*   Description:
*     Get the raw Mod Loader 'HelperFunctions' structure, as passed into 'mtSystemInit'.
*/
const HelperFunctions* mtGetHelperFunctions( void );

/****** Mod Loader Version **********************************************************************/
/*
*   Description:
*     Get the current Mod Loader version number.
*/
s32     mlGetVersion( void );

/****** Version >= 4 ****************************************************************************/
/*
*   Description:
*     Get current main and chao save paths.
*/
const c7* mlGetMainSavePath( void );
const c7* mlGetChaoSavePath( void );

/****** Version >= 7 ****************************************************************************/
/*
*   Description:
*     Get the redirected/replaced file path in the game's directory.
*
*   Examples:
*     - mlGetReplacedFile( "./resource/gd_PC/stg13_light.bin" );
*
*   Notes:
*     - This function is called 'GetReplaceablePath' in the raw 'HelperFunctions'.
*
*   Parameters:
*     - pcSrcPath   : original file path
*
*   Returns:
*     Replaced file path string; or the input path if it has not been replaced.
*/
const c7* mlGetReplacedFile( const c7* pcSrcPath );
/*
*   Description:
*     Get the redirected/replaced file path in the game's directory.
*
*   Examples:
*     - mlReplaceFile( "./resource/gd_PC/stg13_light.bin", "./mods/mymod/gd_PC/stg13_light.bin" );
*     - mlReplaceFile( "./resource/gd_PC/sonictex.prs"   , "./mods/mymod/other/sonictex.prs" );
*
*   Notes:
*     - This is functionally the same as 'mlReplaceFileAtIndex(src, dst, INT_MAX)'
*
*   Parameters:
*     - pcSrcPath   : original file path
*     - pcDstPath   : replacement file path
*/
void    mlReplaceFile( const c7* pcSrcPath, const c7* pcDstPath );
/*
*   Description:
*     Change the game's window title to a different string.
*
*   Parameters:
*     - puTitle     : new window title
*/
void    mlSetWindowTitle( const c16* puTitle );

/****** Version >= 8 ****************************************************************************/
/*
*   Description:
*     Set the scale of the debug text in standard pixels. This function is independent of
*   window resolution.
*
*   Examples:
*     - mlDebugSetScale( 16 ); // 16x16 text, if the screen was 640x480
*
*   Parameters:
*     - scale       : text scale in pixels
*/
void    mlDebugSetScale( u16 scale );
/*
*   Description:
*     Set the color of the debug text.
*
*   Parameters:
*     - scale       : text color in 0xBB'GG'RR'AA format
*/
void    mlDebugSetColor( u32 color );
/*
*   Description:
*     Register a formatted debug string to be drawn at the end of the current frame.
*
*   Notes:
*     - Uses an internal memory buffer that is expanded to fit each formatted string.
*
*   Parameters:
*     - loc         : position of the string on screen                           [NJM_LOCATION]
*     - s           : string to print
*/
void    mlDebugPrint( s32 loc, const c7* fmt, ... );
/*
*   Description:
*     Register a debug string to be drawn at the end of the current frame.
*
*   Notes:
*     - Only '128' debug registries can be made per frame, any more are just ignored.
*
*   Parameters:
*     - loc         : position of the string on screen                           [NJM_LOCATION]
*     - s           : string to print
*/
void    mlDebugPrintC( s32 loc, const c7* s );
/*
*   Description:
*     Register a debug integer to be drawn at the end of the current frame.
*
*   Parameters:
*     - loc         : position of the string on screen                           [NJM_LOCATION]
*     - val         : integer value
*     - digit       : number of digits
*/
void    mlDebugPrintD( s32 loc, s32 val, s32 digit );
/*
*   Description:
*     Register a debug binary sequence to be drawn at the end of the current frame.
*
*   Parameters:
*     - loc         : position of the string on screen                           [NJM_LOCATION]
*     - val         : binary value
*     - digit       : number of digits
*/
void    mlDebugPrintB( s32 loc, u32 val, s32 digit );
/*
*   Description:
*     Register a debug hexadecimal integer to be drawn at the end of the current frame.
*
*   Parameters:
*     - loc         : position of the string on screen                           [NJM_LOCATION]
*     - val         : integer value
*     - digit       : number of digits
*/
void    mlDebugPrintH( s32 loc, u32 val, s32 digit );
/*
*   Description:
*     Register a debug float to be drawn at the end of the current frame.
*
*   Parameters:
*     - loc         : position of the string on screen                           [NJM_LOCATION]
*     - val         : float value
*     - digit       : number of digits
*/
void    mlDebugPrintF( s32 loc, f32 val, s32 digit );
/*
*   Description:
*     Directly set the scale of the debug text in window surface pixels - which is different than
*   the 640x480 game screen.
*
*   Examples:
*     - mlDebugSetScaleDirect( 16.f ); // 16x16 text
*
*   Parameters:
*     - scale       : text scale in surface pixels
*/
void    mlDebugSetScaleDirect( f32 scale );

/****** Version >= 9 ****************************************************************************/
/*
*   Description:
*     Get the global Mod Loader settings structure.
*
*   Notes:
*     - This pointer will remain constant for the liftime of the program.
*/
const ml_settings* mlGetUserSettings( void );

/****** Version >= 10 ***************************************************************************/
/*
*   Description:
*     Register a new voice audio file entry. This can then be used in the regular PlayVoice
*   functions.
*
*   Examples:
*     - mlRegiserVoice("./mods/mymod/voice_jp.mp3", "./mods/mymod/voice_en.wav");
*
*   Notes:
*     - Almost any valid audi file will work (ADX, MP3, WAV, etc.)
*
*   Parameters:
*     - pcPathJP    : path to japanese voice file
*     - pcPathEN    : path to english voice file
*
*   Returns:
*     The ID of the new voice line; or '0' on error.
*/
u16     mlRegisterVoice( const c7* pcPathJP, const c7* pcPathEN );

/****** Version >= 11 ***************************************************************************/
/*
*   Replace and swap textures inside a texture file. This will only be effective
*   while the texture file is unloaded.
*
*   Examples:
*     - ML_ReplaceTexture("SONICTEX", "sonic_soapshoes", "./mods/mymod/new_tex.png", 1120, 0, 0);
*
*   Notes:
*     - Almost any valid image file will work (PNG, GVM, DDS, etc.)
*
*   Parameters:
*     - pcFileName  : name of the texture file, excluding the extension
*     - pcTexName   : name of the texture to replace
*     - pcTexPath   : path to the new texture
*     - gbix        : new global texture index value
*/
void     mlReplaceTexture( const c7* pcFileName, const c7* pcTexName, const c7* pcTexPath, u32 gbix );

/****** Version >= 12 ***************************************************************************/
/*
*   Description:
*     Reset a replaced file path to its original path.
*
*   Examples:
*     - mlResetReplacedFile("./resource/gd_PC/stg10_fog.bin");
*
*   Parameters:
*     - pcSrcPath   : original file path
*/
void    mlResetReplacedFile( const c7* pcSrcPath );

/****** Version >= 13 ***************************************************************************/
/*
*   Description:
*     Push/Pop the alternate Ninja Motion interpolation logic, which lerps to the nearest
*   physical angle rather than simply the nearest value.
*/
void    mlMotionLerpNearestStart( void );
void    mlMotionLerpNearestEnd(   void );

/****** Version >= 15 ***************************************************************************/
/*
*   Description:
*     Get the path to the Mod Loader's external library directory. This is internally stored as
*   a 'c16' in the settings structure, so this function also converts it into a usable form.
*
*   Parameters:
*     - puOutPath   : destination string buffer
*     - szOutPath   : maximum size of the destination buffer
*
*   Returns:
*     Number of characters copied into the buffer, including terminator.
*/
size    mlGetExLibPath( c8* puOutPath, usize szOutPath );

/****** Version >= 16 ***************************************************************************/
/*
*   Description:
*     Get the mod index associated with a replaced file path.
*
*   Parameters:
*     - pcSrcPath   : original file path
*
*   Returns:
*     Mod with "ownership" of the replaced file; or '-1' if the file hasn't been replaced.
*/
s32     mlGetFileModIndex( const c7* pcSrcPath );
/*
*   Description:
*     Replace a file at a
*
*   Notes:
*     - It is best for the destination path to point directly into your mod folder.
*
*   Parameters:
*     - pcSrcPath   : original file path
*     - pcDstPath   : new, replacement file path
*     - index       : mod index to replace as
*/
void    mlReplaceFileAtIndex( const c7* pcSrcPath, const c7* pcDstPath, s32 index );

EXTERN_END

#endif/*H_SAMT_MODLOADER*/
