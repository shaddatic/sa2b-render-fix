/*
*   SA2 Render Fix - '/rf_light.h'
*
*   Description:
*     Render Fix's game light data control module. Also handles converting between RJ and GX
*   light systems, and keeping them in sync.
*/
#ifndef H_RF_LIGHT
#define H_RF_LIGHT

EXTERN_START

/****************************/
/*  Prototypes              */
/****************************/
/****** Sync GX *********************************************************************************/
/*
*   Description:
*     Sync light data with the game's vanilla GX light system.
*
*   Parameters:
*     - light       : light index                                                [RJ_LIGHT_1~4]
*/
void    RF_PushRjLightToGX( i32 light );
/*
*   Description:
*     Sync ambient light color data with the game's vanilla GX light system.
*/
void    RF_PushRjAmbientToGX( void );

EXTERN_END

#endif/*H_RF_LIGHT*/
