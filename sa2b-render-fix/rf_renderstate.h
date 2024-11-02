/*
*   SA2 Render Fix - '/rf_renderstate.h'
*
*   Description:
*     For changing the current renderstate context. Such as changing the Chunk
*   function emulation mode or strip drawing mode for transparancy sorting reasons.
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_RENDERSTATE
#define H_RF_RENDERSTATE

EXTERN_START

#ifndef H_RF_EXTERN_API

/************************/
/*  Constants           */
/************************/
/****** Cnk Draw Func Bits **********************************************************/
#define RFRS_CNKFUNCMD_EASYBIT      (0x01) /* using easy draw variant               */
#define RFRS_CNKFUNCMD_SIMPLEBIT    (0x02) /* using simple draw variant             */
#define RFRS_CNKFUNCMD_MULTIBIT     (0x04) /* using multi draw variant              */
#define RFRS_CNKFUNCMD_DIRECTBIT    (0x08) /* using direct draw                     */

/************************/
/*  Enums               */
/************************/
typedef enum
{
    RFRS_CULLMD_END = -1,        /* end and reset to default                        */

    RFRS_CULLMD_AUTO,            /* set culling mode by model flags                 */
    RFRS_CULLMD_NONE,            /* no culling                                      */
    RFRS_CULLMD_NORMAL,          /* normal culling                                  */
    RFRS_CULLMD_INVERSE,         /* inverted culling (only draws double-sided tris) */
}
RFRS_CULLMD;

typedef enum
{
    RFRS_TRANSMD_END = -1,      /* end and reset to default                         */

    RFRS_TRANSMD_AUTO,          /* set transparency mode automatically              */
    RFRS_TRANSMD_OPAQUE,        /* draw without transparency                        */
    RFRS_TRANSMD_ALPHATEST,     /* draw transparency and alpha test    (& Z buffer) */
    RFRS_TRANSMD_TRANSPARENT,   /* draw transparency                  (no Z buffer) */
    /*
    *     The following modes only change which transparency mode is used, and leave
    *   'OPAQUE' mode as-is. They were implemented in version 1.3.2 and will simply
    *   do nothing in earlier versions.
    */
    RFRS_TRANSMD_AUTO_ATEST,    /* auto, use alpha test for transparency            */
    RFRS_TRANSMD_AUTO_TRANS,    /* auto, do not use alpha test for transparency     */
}
RFRS_TRANSMD;

typedef enum
{
    RFRS_CMPMD_END = -1,        /* End and reset to default                         */

    RFRS_CMPMD_NVR,             /* Never                                            */
    RFRS_CMPMD_LSS,             /* Less                                             */
    RFRS_CMPMD_EQU,             /* Equal                                            */
    RFRS_CMPMD_LEQ,             /* Less or equal                                    */
    RFRS_CMPMD_GTR,             /* Greater                                          */
    RFRS_CMPMD_NEQ,             /* Not equal                                        */
    RFRS_CMPMD_GEQ,             /* Greater or equal                                 */
    RFRS_CMPMD_ALW,             /* Always                                           */
}
RFRS_CMPMD;

typedef enum
{
    RFRS_ALPHAREF_END = -1,     /* End and reset to default                         */
}
RFRS_ALPHAREF;

typedef enum
{
    RFRS_MODMD_END = -1,        /* end and reset to default                         */

    RFRS_MODMD_NORMAL,          /* draw modifiers with regular winding              */
    RFRS_MODMD_INVERSE,         /* draw modifiers with inverse winding              */
}
RFRS_MODMD;

typedef enum
{
    RFRS_CNKDRAWMD_END = -1,    /* end and reset to default                         */

    RFRS_CNKDRAWMD_ALL,         /* draw all strips                                  */
    RFRS_CNKDRAWMD_OPAQUE,      /* draw only opaque strips                          */
    RFRS_CNKDRAWMD_TRANSPARENT, /* draw only transparent strips                     */
}
RFRS_CNKDRAWMD;

typedef enum
{
    RFRS_CNKFUNCMD_END = -1,     /* end and reset to default                        */

    RFRS_CNKFUNCMD_NORMAL,       /* parameters will be parsed normally              */
    RFRS_CNKFUNCMD_EASY = 1,     /* parameters will be parsed as if EasyDraw        */
    RFRS_CNKFUNCMD_SIMPLE,       /* parameters will be parsed as if SimpleDraw      */
    RFRS_CNKFUNCMD_EASYMULTI = 5,/* parameters will be parsed as if EasyMultiDraw   */
    RFRS_CNKFUNCMD_SIMPLEMULTI,  /* parameters will be parsed as if SimpleMultiDraw */
    RFRS_CNKFUNCMD_DIRECT = 8,   /* parameters will be parsed as if DirectDraw      */
}
RFRS_CNKFUNCMD;

typedef enum
{
    RFRS_CNKPASSMD_END = -1,    /* end and reset to default                         */

    RFRS_CNKPASSMD_NORMAL,      /* draw inverse tris first, then normal tris        */
    RFRS_CNKPASSMD_INVERSE,     /* draw normal tris first, then inverse tris        */
}
RFRS_CNKPASSMD;

#endif/*H_RF_EXTERN_API*/

/************************/
/*  Functions           */
/************************/
/****** Init ************************************************************************/
/*
*   Description:
*     Init Renderstate module.
*/
void    RF_RenderStateInit( void );

/****** Set Render State ************************************************************/
/*
*   Description:
*     Set triangle culling mode for Chunk draw.
*
*   Notes:
*     - 'NONE' draws all tris, but 'INVERSE' only draws double sided tris
*     - Users may enabled 'NONE' by default by disabling back-face culling
*     - Useful for transparency sorting
*
*   Parameters:
*     - mode        : culling mode to set (default: 'AUTO'/'NONE')
*/
void    RFRS_SetCullMode( RFRS_CULLMD mode );
/*
*   Description:
*     Set transparency rendering mode.
*
*   Notes:
*     - Useful for forcing the Z buffer on & off via alpha test
*
*   Parameters:
*     - mode        : transparency mode (default: 'AUTO')
*/
void    RFRS_SetTransMode( RFRS_TRANSMD mode );
/*
*   Description:
*     Set alpha test compare function and reference value.
*
*   Parameters:
*     - mode        : Compare mode to be used (default: 'GTR')
*     - value       : A value from 0~255 to compare against (default: 64)
*/
void    RFRS_SetAlphaTestFunc( RFRS_CMPMD mode );
void    RFRS_SetAlphaTestRef(  int32_t   value );
/*
*   Description:
*     Set modifier winding mode. If modifiers are drawn with inverted scaling, this
*   must be set to 'INVERTED' for the modifiers to work correctly.
*
*   Parameters:
*     - mode        : modifier mode (default: 'NORMAL')
*/
void    RFRS_SetModifierMode( RFRS_MODMD mode );
/*
*   Description:
*     Set the Chunk strip draw mode, allowing for opaque and transparant strips
*   to be drawn seperately.
*
*   Notes:
*     - Useful for transparency sorting
*
*   Parameters:
*     - mode        : chunk draw mode (default: 'ALL')
*/
void    RFRS_SetCnkDrawMode( RFRS_CNKDRAWMD mode );
/*
*   Description:
*     Set the Chunk draw function emulation mode. Dreamcast used a number of
*   different function variants for drawing, and this allows you to emulate each of
*   their quirks.
*
*   Parameters:
*     - mode        : chunk function emulation mode (default: 'SIMPLE')
*/
void    RFRS_SetCnkFuncMode( RFRS_CNKFUNCMD mode );
/*
*   Description:
*     Set the transparency pass mode. If the scaling is inverted, this should be set
*   to 'INVERSE' so the front and back faces of transparent strips can be correctly
*   sorted.
*
*   Parameters:
*     - mode        : chunk transparency pass mode (default: 'NORMAL')
*/
void    RFRS_SetCnkPassMode( RFRS_CNKPASSMD mode );

/****** Get Render State ************************************************************/
/*
*   Description:
*     Get the current triangle culling mode.
*/
RFRS_CULLMD RFRS_GetCullMode( void );
/*
*   Description:
*     Get the current transparency mode.
*/
RFRS_TRANSMD RFRS_GetTransMode( void );
/*
*   Description:
*     Get the current alpha test compare mode.
*/
RFRS_CMPMD RFRS_GetAlphaTestFunc( void );
/*
*   Description:
*     Get the current alpha test reference value.
*/
int32_t RFRS_GetAlphaTestRef( void );
/*
*   Description:
*     Get the current modifier mode.
*/
RFRS_MODMD RFRS_GetModifierMode( void );
/*
*   Description:
*     Get the current Chunk Draw mode.
*/
RFRS_CNKDRAWMD RFRS_GetCnkDrawMode( void );
/*
*   Description:
*     Get the current Chunk function emulation mode.
*/
RFRS_CNKFUNCMD RFRS_GetCnkFuncMode( void );
/*
*   Description:
*     Get the current Chunk transparancy pass mode.
*/
RFRS_CNKPASSMD RFRS_GetCnkPassMode( void );

/****** Set Default *****************************************************************/
/*
*   Description:
*     Set default triangle cull mode.
*
*   Parameters:
*     - mode        : culling mode to set
*/
void    RFRS_SetDefaultCullMode( RFRS_CULLMD mode );
/*
*   Description:
*     Set default transparency mode.
*
*   Parameters:
*     - mode        : transparency mode
*/
void    RFRS_SetDefaultTransMode( RFRS_TRANSMD mode );
/*
*   Description:
*     Set default alpha test compare function and reference value.
*
*   Parameters:
*     - mode        : Compare mode to be used
*     - value       : A value from 0~255 to compare against
*/
void    RFRS_SetDefaultAlphaTestFunc( RFRS_CMPMD mode );
void    RFRS_SetDefaultAlphaTestRef(  int32_t   value );
/*
*   Description:
*     Set default Chunk strip draw mode.
*
*   Parameters:
*     - mode        : chunk draw mode
*/
void    RFRS_SetDefaultCnkDrawMode( RFRS_CNKDRAWMD mode );
/*
*   Description:
*     Set default Chunk function emulation mode.
*
*   Parameters:
*     - mode        : chunk function emulation mode
*/
void    RFRS_SetDefaultCnkFuncMode( RFRS_CNKFUNCMD mode );
/*
*   Description:
*     Set default Chunk transparency pass mode.
*
*   Parameters:
*     - mode        : chunk transparency pass mode
*/
void    RFRS_SetDefaultCnkPassMode( RFRS_CNKPASSMD mode );

EXTERN_END

#endif/*H_RF_RENDERSTATE*/
