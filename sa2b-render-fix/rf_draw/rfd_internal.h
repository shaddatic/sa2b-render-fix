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

#include <rf_draw/rfd_core.h>

EXTERN_START

/************************/
/*  Prototypes          */
/************************/
/****** Init ************************************************************************/
/*
*   Description:
*     Init Core draw sub-module.
*/
void    RFD_CoreInit( void );
/*
*   Description:
*     Init Chunk draw sub-module.
*/
void    RFD_ChunkInit( void );
/*
*   Description:
*     Init Texture-Error sub-module.
*/
void    RFD_TexerrInit( void );

/****** Cnk Shape *******************************************************************/
/*
*   Description:
*     Draw shape motion with cnkobj tree and BE flag.
*
*   Parameters:
*     - cnkobj      : current object
*     - bBE         : big endian shape flag
*/
void    rjCnkPushPopShape( const NJS_CNK_OBJECT* cnkobj, int bBE );
/*
*   Description:
*     Draw shape motion link with cnkobj tree and BE flag.
*
*   Parameters:
*     - cnkobj      : current object
*     - bBE         : big endian shape flag
*/
void    rjCnkPushPopShapeLink( const NJS_CNK_OBJECT* cnkobj, int bBE );

EXTERN_END

#endif/*H_RF_DRAW_INTERNAL*/
