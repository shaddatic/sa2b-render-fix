/*
*   SA2 Render Fix - '/rf_light.h'
*
*   Description:
*       Functions for easily manipulating Ginja's light system.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_LIGHT_H_
#define _RF_LIGHT_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Enums               */
/************************/
typedef enum
{
    GJLIGHT_1,  /* Light 1              */
    GJLIGHT_2,  /* Light 2              */
    GJLIGHT_3,  /* Light 3              */
    GJLIGHT_4,  /* Light 4              */
    GJLIGHT_5,  /* Unimplemented        */
}
RFE_GJLIGHT;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Set Ginja light to global **/
void    RFL_SetGjGlobalLight( RFE_GJLIGHT idxLight, const NJS_VECTOR* pVec );

/** Set light color **/
void    RFL_SetGjLightColor( RFE_GJLIGHT idxLight, float r, float g, float b );

/** Turn light on and off **/
void    RFL_GjLightOn(  RFE_GJLIGHT idxLight );
void    RFL_GjLightOff( RFE_GJLIGHT idxLight );

EXTERN_END

#endif/*_RF_LIGHT_H_*/
