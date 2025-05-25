/*
*   SA2 Render Fix - '/rf_light.h'
*
*   Description:
*     Render Fix's light data and control module.
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_LIGHT_INTERNAL
#define H_RF_LIGHT_INTERNAL

/************************/
/*  Includes            */
/************************/
/****** Self ************************************************************************/
#include <rf_light.h>                   /* root parent                              */

/************************/
/*  Prototypes          */
/************************/
/****** Init ************************************************************************/
/*
*   Description:
*     Light file sub-module init.
*/
void    RFL_FileInit( void );
/*
*   Description:
*     SetLight sub-module init.
*/
void    RFL_SetLightInit( void );

#endif/*H_RF_LIGHT_INTERNAL*/
