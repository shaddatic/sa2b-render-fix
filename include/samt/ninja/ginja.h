/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/ninja/ginja.h'
*
*   Description:
*     Ninja for GX (Ginja) library extensions.
*/
#ifndef _GINJA_H_
#define _GINJA_H_

/********************************/
/*  Includes                    */
/********************************/
/****** Fog *************************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Game Defs                   */
/********************************/
/****** Fog *************************************************************************************/
#define _gj_fog_enable_             DATA_REF(Int, 0x025EFFCC)

/********************************/
/*  Prototypes                  */
/********************************/
/****** Vertex **********************************************************************************/
void    gjStartVertex3D( const NJS_MATRIX* m, Uint32 index );

/****** View ************************************************************************************/
void    gjSetPerspective( Float screen_ratio, Float near_clip, Float far_clip );

/****** Set State *******************************************************************************/
void    gjEnableFog( void );
void    gjDisableFog( void );

/****** Update State ****************************************************************************/
void    gjUpdateFog( void );

EXTERN_END

#endif/*_GINJA_H_*/
