/*
*   SA2 Render Fix - '/rfapi_rstate.h'
*
*   Description:
*     The 'Render State' API is for controlling how things will be drawn to the screen. This
*   is useful when the default states can't give the intended effect.
*     Once done you're done, call with applicable 'END' enum member to reset the render state
*   back to defaults.
* 
*   Version History:
*     - v1.3.0.0        : Version 0, initial release
*     - v1.3.2.0        : Version 1, added 'SetModifierMode' & 'SetCnkDrawMode'
*     - v1.4.0.0        : Version 2, added 'CnkFunc/PassMode' & 'Get' variants of all functions
*     - v1.4.0.1        : Version 3, added 'SocTexHackMode' functions
*     - v1.5.0.0        : Version 4, depricated 'CullMode', 'CnkDrawMode', 'SocTexHack',
*                         'CnkPass', & 'ModifierMode', and added 'CnkSpecMode'
* 
*   Availability:
*     - Before Init     : No
*     - At Init         : Yes
*     - After Init      : Yes
*/
#ifndef H_RFAPI_RENDERSTATE
#define H_RFAPI_RENDERSTATE

/********************************/
/*  Constants                   */
/********************************/
/****** API Module Version **********************************************************************/
#define RFAPI_RENDERSTATE_VER       (4) /* render state api version                             */

/********************************/
/*  Enums                       */
/********************************/
/****** Render State Enums **********************************************************************/
typedef enum
{
    RFRS_CULLMD_END = -1,           /* end and reset to default                                 */

    RFRS_CULLMD_AUTO,               /* set culling mode by model flags                [default] */
    RFRS_CULLMD_NONE,               /* no culling                                               */
    RFRS_CULLMD_NORMAL,             /* normal culling                                           */
    RFRS_CULLMD_INVERSE,            /* inverted culling                                         */
}
RFRS_CULLMD;

typedef enum
{
    RFRS_TRANSMD_END = -1,          /* end and reset to default                                 */

    RFRS_TRANSMD_AUTO,              /* set transparancy mode automatically            [default] */
    RFRS_TRANSMD_OPAQUE,            /* draw without transparancy                                */
    RFRS_TRANSMD_ALPHATEST,         /* draw transparancy w/ alpha test, & Z buffer              */
    RFRS_TRANSMD_TRANSPARENT,       /* draw transparancy, no Z buffer                           */

    /**** v1.3.2.0+ *****************************************/

    RFRS_TRANSMD_AUTO_ATEST,        /* auto, use alpha test for transparancy                    */
    RFRS_TRANSMD_AUTO_TRANS,        /* auto, do not use alpha test for transparancy             */

    /**** Version >= 4 **************************************/

    RFRS_TRANSMD_PUNCH,             /* draw with punchthrough (opaque+alphatest)                */
    RFRS_TRANSMD_AUTO_PUNCH,        /* auto, use punchthrough for transparency                  */
}
RFRS_TRANSMD;

typedef enum
{
    RFRS_CMPMD_END = -1,            /* end and reset to default                                 */

    RFRS_CMPMD_NVR,                 /* never                                                    */
    RFRS_CMPMD_LSS,                 /* less                                                     */
    RFRS_CMPMD_EQU,                 /* equal                                                    */
    RFRS_CMPMD_LEQ,                 /* less or equal                                            */
    RFRS_CMPMD_GTR,                 /* greater                                                  */
    RFRS_CMPMD_NEQ,                 /* not equal                                                */
    RFRS_CMPMD_GEQ,                 /* greater or equal                                         */
    RFRS_CMPMD_ALW,                 /* always                                                   */
}
RFRS_CMPMD;

typedef enum
{
    RFRS_ALPHAREF_END = -1,         /* end and reset to default                                 */
}
RFRS_ALPHAREF;

typedef enum
{
    RFRS_MODMD_END = -1,            /* end and reset to default                                 */

    RFRS_MODMD_NORMAL,              /* draw modifiers with regular winding            [default] */
    RFRS_MODMD_INVERSE,             /* draw modifiers with inverse winding                      */
}
RFRS_MODMD;

typedef enum
{
    RFRS_CNKDRAWMD_END = -1,        /* end and reset to default                                 */

    RFRS_CNKDRAWMD_ALL,             /* draw all strips                                [default] */
    RFRS_CNKDRAWMD_OPAQUE,          /* draw only opaque strips                                  */
    RFRS_CNKDRAWMD_TRANSPARENT,     /* draw only transparent strips                             */
}
RFRS_CNKDRAWMD;

typedef enum
{
    RFRS_CNKFUNCMD_END = -1,        /* end and reset to default                                 */

    RFRS_CNKFUNCMD_NORMAL,          /* model parsed normally (rf extension)                     */
    RFRS_CNKFUNCMD_EASY = 1,        /* use 'EasyDraw' emulation                                 */
    RFRS_CNKFUNCMD_SIMPLE,          /* use 'SimpleDraw' emulation                     [default] */
    RFRS_CNKFUNCMD_EASYMULTI = 5,   /* use 'EasyMultiDraw' emulation                            */
    RFRS_CNKFUNCMD_SIMPLEMULTI,     /* use 'SimpleMultiDraw' emulation                          */
    RFRS_CNKFUNCMD_DIRECT = 8,      /* use 'DirectDraw' emulation                               */
}
RFRS_CNKFUNCMD;

typedef enum
{
    RFRS_CNKPASSMD_END = -1,        /* end and reset to default                                 */

    RFRS_CNKPASSMD_NORMAL,          /* draw inverse tris first, then normal tris      [default] */
    RFRS_CNKPASSMD_INVERSE,         /* draw normal tris first, then inverse tris                */
}
RFRS_CNKPASSMD;

typedef enum
{
    RFRS_SOCTEXHACKMD_END = -1,     /* end and reset to default                                 */

    RFRS_SOCTEXHACKMD_DISABLED,     /* 2D tex params use the ninja context                      */
    RFRS_SOCTEXHACKMD_ENABLED,      /* context is overridden by soc tex param hack    [default] */
}
RFRS_SOCTEXHACKMD;

typedef enum
{
    RFRS_CNKSPECMD_END = -1,        /* end and reset to default                                 */

    RFRS_CNKSPECMD_NONE,            /* no specular calculations                                 */
    RFRS_CNKSPECMD_AUTO,            /* specular mode matches chunk function mode      [default] */
    RFRS_CNKSPECMD_NORMAL,          /* use 'normal' specular calculations                       */
    RFRS_CNKSPECMD_EASY,            /* use 'Easy'/'Direct' calculations                         */
    RFRS_CNKSPECMD_SIMPLE,          /* use 'Simple' calculations                                */
    RFRS_CNKSPECMD_MULTI,           /* use 'EasyMulti'/'SimpleMulti' calculations               */
}
RFRS_CNKSPECMD;

/********************************/
/*  Constants                   */
/********************************/
/****** Cnk Draw Func Bits **********************************************************************/
#define RFRS_CNKFUNCMD_EASYBIT      (0x01) /* using easy draw variant                           */
#define RFRS_CNKFUNCMD_SIMPLEBIT    (0x02) /* using simple draw variant                         */
#define RFRS_CNKFUNCMD_MULTIBIT     (0x04) /* using multi draw variant                          */
#define RFRS_CNKFUNCMD_DIRECTBIT    (0x08) /* using direct draw                                 */

/********************************/
/*  API Structures              */
/********************************/
/****** Render State API ************************************************************************/
typedef struct
{
    uint32_t version;               /* structure version                                        */

    /****** Version >= 0 ************************************************************************/

    /********************************************************/
    /*
    *   Set Renderstate
    */
    /********************************************************/
    /*
    *   [[ DEPRICATED : Version 4 ]]
    * 
    *   Deprication Info:
    *     - state           : mostly functional ('NONE' maps to 'AUTO')
    *     - reason          : Added Chunk control flags, which do this better
    *     - alternative     : use 'rjCnkSetControl' with 'RJD_CNK_CTRL_NORMAL/INVERSE' flags
    * 
    *   Description:
    *     Set triangle culling mode for Chunk draw.
    *
    *   Notes:
    *     - 'NONE' draws all tris, but 'INVERSE' only draws double sided tris
    *     - Users may enabled 'NONE' by default by disabling back-face culling
    *     - Useful for transparency sorting
    *
    *   Parameters:
    *     - mode        : culling mode to set
    */
    void(__cdecl* SetCullMode)( RFRS_CULLMD mode );
    /*
    *   Description:
    *     Set transparency rendering mode.
    *
    *   Notes:
    *     - The 'AUTO_#' transparency states only force the alpha state of translucent
    *       polygons, while leaving opaque polygons as-is.
    *     - By default, 'ALPHATEST' is the same as 'TRANSPARENT' visually; but only 'ALPHATEST'
    *       writes to the Z buffer.
    *     - 'PUNCH' forces the 'PUNCHTHROUGH' alpha state, which is opaque blending + alpha
    *       test. Otherwise, you can enable it with 'NJD_CONTROL_3D_USE_PUNCHTHROUGH'.
    *
    *   Parameters:
    *     - mode        : transparency mode
    */
    void(__cdecl* SetTransMode)( RFRS_TRANSMD mode );
    /*
    *   Description:
    *     Set alpha test compare function and reference value.
    * 
    *   Notes:
    *     - Compare mode is 'NEQ' by default, with a ref of '0'
    *     - Older versions of RF (pre v1.4) use 'GTR', with a ref of '64'
    *
    *   Parameters:
    *     - mode        : Compare mode to be used
    *     - value       : A value from 0~255 to compare against
    */
    void(__cdecl* SetAlphaTestFunc)( RFRS_CMPMD mode );
    void(__cdecl* SetAlphaTestRef)(  int32_t   value );

    /****** Version >= 1 ************************************************************************/
    /*
    *   [[ DEPRICATED : Version 4 ]]
    * 
    *   Deprication Info:
    *     - state           : functional
    *     - reason          : ninja has a specific flag for this purpose
    *     - alternative     : use 'NJD_CONTROL_3D_MIRROR_MODEL' flag instead
    * 
    *   Description:
    *     Set modifier model winding mode. If modifiers have inverted normals, such
    *   as being drawn with inverted scaling, this must be set to 'INVERTED' for the
    *   modifiers to work correctly.
    *
    *   Parameters:
    *     - mode        : modifier mode
    */
    void(__cdecl* SetModifierMode)( RFRS_MODMD mode );
    /*
    *   [[ DEPRICATED : Version 4 ]]
    * 
    *   Deprication Info:
    *     - state           : functional
    *     - reason          : Added Chunk control flags, which do this better
    *     - alternative     : use 'rjCnkSetControl' with 'RJD_CNK_CTRL_OPAQUE/TRANSLUCENT' flags
    * 
    *   Description:
    *     Set the draw mode of opaque/transparent Chunk strips, allowing for opaque
    *   and transparant strips to be drawn seperately for sorting reasons.
    *
    *   Parameters:
    *     - mode        : chunk draw mode
    */
    void(__cdecl* SetCnkDrawMode)( RFRS_CNKDRAWMD mode );

    /****** Version >= 2 ************************************************************************/
    /*
    *   Description:
    *     Set the Chunk draw function emulation mode. Dreamcast used a number of
    *   different function variants for drawing, and this allows you to emulate each of
    *   their quirks.
    *
    *   Parameters:
    *     - mode        : chunk function emulation mode
    */
    void(__cdecl* SetCnkFuncMode)( RFRS_CNKFUNCMD mode );
    /*
    *   [[ DEPRICATED : Version 4 ]]
    * 
    *   Deprication Info:
    *     - state           : functional
    *     - reason          : ninja has a specific flag for this purpose
    *     - alternative     : use 'NJD_CONTROL_3D_MIRROR_MODEL' flag instead
    * 
    *   Description:
    *     Set the transparency pass mode. If the scaling is inverted, this should be set
    *   to 'INVERSE' so the front and back faces of transparent strips can be correctly
    *   sorted.
    *
    *   Parameters:
    *     - mode        : chunk transparency pass mode
    */
    void(__cdecl* SetCnkPassMode)( RFRS_CNKPASSMD mode );

    /********************************************************/
    /*
    *   Get Renderstate
    */
    /********************************************************/
    /*
    *   [[ DEPRICATED : Version 4 ]]
    *
    *   Deprication Info:
    *     - state           : mostly functional (can't return state with no flags enabled, defaults to 'INVERSE')
    *     - reason          : Added Chunk control flags, which do this better
    *     - alternative     : use 'rjCnkGetControl' with 'RJD_CNK_CTRL_NORMAL/INVERSE' flags
    *
    *   Description:
    *     Get the current triangle culling mode.
    */
    RFRS_CULLMD(__cdecl* GetCullMode)( void );
    /*
    *   Description:
    *     Get the current transparency mode.
    */
    RFRS_TRANSMD(__cdecl* GetTransMode)( void );
    /*
    *   Description:
    *     Get the current alpha test compare mode.
    */
    RFRS_CMPMD(__cdecl* GetAlphaTestFunc)( void );
    /*
    *   Description:
    *     Get the current alpha test reference value.
    */
    int32_t(__cdecl* GetAlphaTestRef)( void );
    /*
    *   [[ DEPRICATED : Version 4 ]]
    * 
    *   Deprication Info:
    *     - state           : functional
    *     - reason          : ninja has a specific flag for this purpose
    *     - alternative     : use 'NJD_CONTROL_3D_MIRROR_MODEL' flag instead
    * 
    *   Description:
    *     Get the current modifier mode.
    */
    RFRS_MODMD(__cdecl* GetModifierMode)( void );
    /*
    *   [[ DEPRICATED : Version 4 ]]
    *
    *   Deprication Info:
    *     - state           : mostly functional (can't return state with no flags enabled, defaults to 'TRANSLUCENT')
    *     - reason          : Added Chunk control flags, which do this better
    *     - alternative     : use 'rjCnkGetControl' with 'RJD_CNK_CTRL_OPAQUE/TRANSLUCENT' flags
    *
    *   Description:
    *     Get the current Chunk Draw mode.
    */
    RFRS_CNKDRAWMD(__cdecl* GetCnkDrawMode)( void );
    /*
    *   Description:
    *     Get the current Chunk function emulation mode.
    */
    RFRS_CNKFUNCMD(__cdecl* GetCnkFuncMode)( void );
    /*
    *   [[ DEPRICATED : Version 4 ]]
    * 
    *   Deprication Info:
    *     - state           : functional
    *     - reason          : ninja has a specific flag for this purpose
    *     - alternative     : use 'NJD_CONTROL_3D_MIRROR_MODEL' flag instead
    * 
    *   Description:
    *     Get the current Chunk transparancy pass mode.
    */
    RFRS_CNKPASSMD(__cdecl* GetCnkPassMode)( void );

    /****** Version >= 3 ************************************************************************/

    /**** SOC Texture Filtering Hack ************************/
    /*
    *   [[ DEPRICATED : Version 4 ]]
    * 
    *   Deprication Info:
    *     - state           : non-functional
    *     - reason          : most draw functions have been replaced, making it useless
    *     - alternative     : none
    * 
    *   Description:
    *     Set the state of SoC's texture param hack, which forces certain texture
    *   parameters depending on the draw function. If you wish to use custom
    *   texture settings via the Ninja context, this should be 'DISABLED' before
    *   doing so.
    *
    *   Parameters:
    *     - mode        : soc texture param hack mode (default: 'ENABLED')
    */
    void (__cdecl* SetSocTexHackMode)( RFRS_SOCTEXHACKMD mode );
    /*
    *   [[ DEPRICATED : Version 4 ]]
    * 
    *   Deprication Info:
    *     - state           : always returns 'DISABLED'
    *     - reason          : most draw functions have been replaced, making it useless
    *     - alternative     : none
    * 
    *   Description:
    *     Get the current SoC texture hack mode.
    */
    RFRS_SOCTEXHACKMD (__cdecl* GetSocTexHackMode)( void );

    /****** Version >= 4 ************************************************************************/

    /**** Chunk Specular ************************************/
    /*
    *   Description:
    *     Set the Chunk specular calculation mode. Each draw function variant used a different
    *   method for calculating specular color, and this allows you to mix and match them to
    *   your liking.
    *
    *   Parameters:
    *     - mode        : chunk specular calculation mode
    */
    void (__cdecl* SetCnkSpecMode)( RFRS_CNKSPECMD mode );
    /*
    *   Description:
    *     Get the current Chunk specular calculation mode.
    */
    RFRS_CNKSPECMD (__cdecl* GetCnkSpecMode)( void );
}
RFAPI_RENDERSTATE;

#endif/*H_RFAPI_RENDERSTATE*/
