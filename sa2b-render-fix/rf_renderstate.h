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
/****** Set Render State ************************************************************/
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

/****** Get Render State ************************************************************/
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
*     Get the current Chunk function emulation mode.
*/
RFRS_CNKFUNCMD RFRS_GetCnkFuncMode( void );
/*
*   Description:
*     Get the current Chunk specular calculation mode.
*/
RFRS_CNKSPECMD RFRS_GetCnkSpecMode( void );

/****** Set Default *****************************************************************/
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

EXTERN_END

#endif/*H_RF_RENDERSTATE*/
