/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/gjlight.h'
*
*   Description:
*       Ginja light control.
*
*   Contributors:
*   -   SEGA,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _GJLIGHT_H_
#define _GJLIGHT_H_

/************************/
/*  Includes            */
/************************/
/** System **/
#include <sa2b/shinobi/sg_xpt.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Enable/disable different lights **/
void    gjSetLightSwitch(Int light_id, Bool light_on);

/** Set global ambient light color **/
void    gjSetAmbient(Float b, Float g, Float r);

/** Set specific light attribute **/
void    gjSetLightColor(Int light_id, Float b, Float g, Float r);
void    gjSetLightVector(Int light_id, Float x, Float y, Float z);

/** Update light **/
void    gjLoadLight(Int light_id);

EXTERN_END

#endif/*_GJLIGHT_H_*/
