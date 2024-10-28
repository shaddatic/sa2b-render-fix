/*
*   SA2 Render Fix - '/rf_draw/rfd_internal.h'
*
*   Description:
*     Internal header for RF Draw module
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_DRAW_INTERNAL
#define H_RF_DRAW_INTERNAL

/************************/
/*  External Includes   */
/************************/
/****** Self ************************************************************************/
#include <rf_draw.h>            /* parent                                           */

/************************/
/*  Opaque Types        */
/************************/
/****** Cnk Draw ********************************************************************/
typedef struct cnk_vtx_buf      CNK_VERTEX_BUFFER;

EXTERN_START

/************************/
/*  Prototypes          */
/************************/
/****** Cnk Draw ********************************************************************/
/*
*   Description:
*     Begin Chunk draw.
*/
void    rjCnkBeginDrawModel( void );
/*
*   Description:
*     Sub-function for Chunk draw that doesn't check model clip or call 'BeginDraw'.
*
*   Paramters:
*     - model       : chunk model to draw
*/
void    rjCnkDrawModelSub( const NJS_CNK_MODEL* model );

EXTERN_END

#endif/*H_RF_DRAW_INTERNAL*/
