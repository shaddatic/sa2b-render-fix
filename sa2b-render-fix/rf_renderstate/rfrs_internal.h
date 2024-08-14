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
/****** Chunk Draw ******************************************************************/
/*
*   Description:
*     Init back face culling rendering
*/
void    RFRS_BackFaceCullingInit( void );

/****** Chunk Draw ******************************************************************/
/*
*   Description:
*     Set hide/draw state for following Chunk strips
*
*   Parameters:
*     - bHide   : if following strips should be hidden
*/
void    SetChunkStripHideMode( bool bHide );

EXTERN_END

#endif/*H_RF_RENDERSTATE_INTERNAL*/
