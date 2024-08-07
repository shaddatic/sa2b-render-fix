/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/gjlight.h'
*
*   Description:
*       Ginja light control.
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _GJLIGHT_H_
#define _GJLIGHT_H_

/************************/
/*  Includes            */
/************************/
/** System **/
#include <sa2b/shinobi/sg_xpt.h>

/************************/
/*  Data                */
/************************/
/** Unique ID for each light index **/
#define _gj_light_ids_      DATA_ARY(uint32_t , 0x0174B468, [5])

/** Light list **/
#define _gj_lights_         DATA_ARY(GXS_LIGHT, 0x025F0120, [5]) /* Defined in '/gx/gxlight.h' */

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Enable/disable different lights **/
void    gjSetLightSwitch(Int light_idx, Bool light_on);

/** Set global ambient light color **/
void    gjSetAmbient(Float b, Float g, Float r);

/** Set specific light attribute **/
void    gjSetLightColor(Int light_idx, Float r, Float g, Float b);
void    gjSetLightVector(Int light_idx, Float x, Float y, Float z);

/** Update light **/
void    gjLoadLight(Int light_idx);

EXTERN_END

#endif/*_GJLIGHT_H_*/
