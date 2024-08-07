/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/ginja.h'
*
*   Description:
*       Ginja constants, structs, and functions. It is a
*   modified version of Ninja used for the GameCube.
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _GINJA_H_
#define _GINJA_H_

/************************/
/*  Includes            */
/************************/
/** System **/
#include <sa2b/shinobi/sg_xpt.h>

EXTERN_START

/************************/
/*  Data                */
/************************/
/****** Matrix **************************************************************/
/** Current matrix pointer **/
#define _gj_matrix_                 DATA_REF(GJS_MATRIX*, 0x01A557FC)

/** Matrix limits **/
#define _gj_base_matrix_            DATA_REF(GJS_MATRIX*, 0x0267053C)
#define _gj_max_matrix_             DATA_REF(GJS_MATRIX*, 0x0267053C)

/****** Fog *****************************************************************/
/** Fog status **/
#define _gj_fog_enable_             DATA_REF(Int        , 0x025EFFCC)

/************************/
/*  Functions           */
/************************/
/****** Matrix **************************************************************/
void    gjInitMatrix(GJS_MATRIX* mb, Int count);

void    gjPushUnitMatrix();

void    gjTranslate(Float x, Float y, Float z);

void    gjRotateX(Angle ang);
void    gjRotateY(Angle ang);
void    gjRotateZ(Angle ang);

void    gjAddVector(NJS_VECTOR* vd, NJS_VECTOR* vs1, NJS_VECTOR* vs2);
void    gjSubVector(NJS_VECTOR* vd, NJS_VECTOR* vs1, NJS_VECTOR* vs2);

/************************/
/*  Ginja Fog           */
/************************/
/****** Set State *******************************************************************/
void    gjEnableFog(void);
void    gjDisableFog(void);

/****** Update State ****************************************************************/
void    gjUpdateFog(void);

EXTERN_END

#endif/*_GINJA_H_*/
