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

EXTERN_START

/************************/
/*  Constants           */
/************************/
#define	RFD_CNK_MULTILIGHT_1            (1) /* light 1                              */
#define	RFD_CNK_MULTILIGHT_2            (2) /* light 2                              */
#define	RFD_CNK_MULTILIGHT_3            (3) /* light 3                              */
#define	RFD_CNK_MULTILIGHT_4            (4) /* light 4                              */
#define	RFD_CNK_MULTILIGHT_5            (5) /* unimplimented                        */
#define	RFD_CNK_MULTILIGHT_6            (6) /* unimplimented                        */

#define	RFD_CNK_MULTILIGHT_ALL          (0) /* all lights                           */

/************************/
/*  Functions           */
/************************/
/** Init Light module **/
void    RF_LightInit( void );

/** Set Ginja light to global **/
void    rjCnkSetLightVectorEx( Int light, Float vx, Float vy, Float vz );

/** Set light color **/
void    rjCnkSetLightColor( Int light, Float r, Float g, Float b );

/** Set light ambient color **/
void    rjCnkSetAmbient( Float r, Float g, Float b );

/** Turn light on and off **/
void    rjCnkSetLightSwitch( Int light, Int flag );

/** Set light vectors to reflect current matrix **/
void    rjCnkSetLightMatrices( void );

EXTERN_END

#endif/*_RF_LIGHT_H_*/
