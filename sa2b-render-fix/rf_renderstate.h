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
*     - mode        : triangle culling mode
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
*     - mode        : transparency mode
*/
void    RFRS_SetTransMode( RFRS_TRANSMD mode );
/*
*   Description:
*     Set alpha test compare function and reference value.
*
*   Parameters:
*     - mode        : Compare mode to be used
*     - value       : A value from 0~255 to compare against
*/
void    RFRS_SetAlphaTestFunc( RFRS_CMPMD mode );
void    RFRS_SetAlphaTestRef(  int32_t   value );
/*
*   Description:
*     Set the draw mode of opaque/transparent Chunk strips, allowing for opaque and
*   transparant strips to be drawn seperately for sorting reasons.
*
*   Parameters:
*     - mode        : chunk draw mode
*/
void    RFRS_SetCnkDrawMode( RFRS_CNKDRAWMD mode );
/*
*   Description:
*     Set the Chunk draw function emulation mode. Dreamcast used a number of
*   different function variants for drawing, and this allows you to emulate each of
*   their quirks.
*
*   Parameters:
*     - mode        : chunk function emulation mode
*/
void    RFRS_SetCnkFuncMode( RFRS_CNKFUNCMD mode );
/*
*   Description:
*     Set the Chunk specular calculation mode. Each draw function variant used a
*   different method for calculating specular color, and this allows you to mix and
*   match them to your liking.
*
*   Parameters:
*     - mode        : chunk specular calculation mode
*/
void    RFRS_SetCnkSpecMode( RFRS_CNKSPECMD mode );
/*
*   Description:
*     Set the two pass lighting calculation mode. This enables two sided polygons to
*   be lit seperately - hence two-pass - when drawing Chunk models with 'SimpleDraw'.
*   When disabled, both sides of the polygon are lit the same; mimicking 'EasyDraw'.
*
*   Notes:
*     - There's no real reason to disable this, it was only created to support
*       models with broken triangle normals as this also then broke their lighting
*       too. If you're using this API, just fix your model.
*
*   Parameters:
*     - mode        : two pass lighting mode
*/
void    RFRS_SetTwoPassLightingMode( RFRS_TWOPASSLIGHTMD mode );

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
*     Get the current Chunk specular calculation mode.
*/
RFRS_CNKSPECMD RFRS_GetCnkSpecMode( void );
/*
*   Description:
*     Get the current two pass lighting calculation mode.
*/
RFRS_TWOPASSLIGHTMD RFRS_GetTwoPassLightingMode( void );

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
*     Set default Chunk specular calculation mode.
*
*   Parameters:
*     - mode        : chunk function emulation mode
*/
void    RFRS_SetDefaultCnkSpecMode( RFRS_CNKSPECMD mode );
/*
*   Description:
*     Set default two pass lighting calculation mode.
*
*   Parameters:
*     - mode        : chunk function emulation mode
*/
void    RFRS_SetDefaultTwoPassLightingMode( RFRS_TWOPASSLIGHTMD mode );

EXTERN_END

#endif/*H_RF_RENDERSTATE*/
