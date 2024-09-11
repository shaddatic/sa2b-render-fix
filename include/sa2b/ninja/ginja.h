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
/****** Fog *****************************************************************/
#define _gj_fog_enable_             DATA_REF(Int, 0x025EFFCC)

/************************/
/*  Functions           */
/************************/
/****** Set State *******************************************************************/
void    gjEnableFog(void);
void    gjDisableFog(void);

/****** Update State ****************************************************************/
void    gjUpdateFog(void);

EXTERN_END

#endif/*_GINJA_H_*/
