/*
*   SA2 Render Fix - '/rf_renderstate/rfrs_internal.h'
*
*   Description:
*     Internal header for RF Render State module
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_RENDERSTATE_INTERNAL
#define H_RF_RENDERSTATE_INTERNAL

/************************/
/*  External Includes   */
/************************/
/****** Self ************************************************************************/
#include <rf_renderstate.h> /* parent                                               */

EXTERN_START

/************************/
/*  Prototypes          */
/************************/
/****** Transparancy Mode ***********************************************************/
/*
*   Description:
*     Set opaque rendering
*/
void    SetTransModeOpaque( void );
/*
*   Description:
*     Set transparancy rendering with alpha test and Z writing
*
*   Parameters:
*     - func    : alpha test func
*     - ref     : alpha reference value
*/
void    SetTransModeAlphaTest( RFRS_CMPMD func, int32_t ref );
/*
*   Description:
*     Set transparancy rendering with no Z writing
*/
void    SetTransModeTransparent( void );

EXTERN_END

#endif/*H_RF_RENDERSTATE_INTERNAL*/
