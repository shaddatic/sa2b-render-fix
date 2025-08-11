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

/********************************/
/*  Includes                    */
/********************************/
/****** Render State API ************************************************************************/
#include <rfapi_rstate.h>           /* render state api                                         */

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
*     Set modifier model winding mode. If modifiers have inverted normals, such
*   as being drawn with inverted scaling, this must be set to 'INVERTED' for the
*   modifiers to work correctly.
*
*   Parameters:
*     - mode        : modifier mode (default: 'NORMAL')
*/
void    RFRS_SetModifierMode( RFRS_MODMD mode );
/*
*   Description:
*     Set the draw mode of opaque/transparent Chunk strips, allowing for opaque and
*   transparant strips to be drawn seperately for sorting reasons.
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
/*
*   Description:
*     Set the state of SoC's texture param hack, which forces certain texture
*   parameters depending on the draw function. If you wish to use custom texture
*   settings via the Ninja context, this should be 'DISABLED' before doing so.
*
*   Notes:
*     - This is a temporary render state until the underlying UV issues for these
*       draw functions are fixed.
*
*   Parameters:
*     - mode        : soc texture param hack mode (default: 'ENABLED')
*/
void    RFRS_SetSocTexHackMode( RFRS_SOCTEXHACKMD mode );

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
/*
*   Description:
*     Get the current SoC texture hack mode.
*/
RFRS_SOCTEXHACKMD RFRS_GetSocTexHackMode( void );

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

EXTERN_END

#endif/*H_RF_RENDERSTATE*/
