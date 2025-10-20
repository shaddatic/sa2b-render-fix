/*
*   SA2 Render Fix - '/rf_module/rfm_internal.h'
*
*   Description:
*     Internal header for Render Fix Module... module.
*/
#ifndef H_RF_MODULE_INTERNAL
#define H_RF_MODULE_INTERNAL

EXTERN_START

/********************************/
/*  Prototypes                  */
/********************************/
/****** Init ************************************************************************************/
/*
*   Description:
*     Init the 'Global' feature module.
*/
void    RFM_GlobalInit( void );
/*
*   Description:
*     Init the 'Shadow' feature module.
*/
void    RFM_ShadowsInit( void );
/*
*   Description:
*     Init the 'Common' feature module.
*/
void    RFM_CommonInit( void );
/*
*   Description:
*     Init the 'Emblem Get' feature module.
*/
void    RFM_EmblemGetInit( void );
/*
*   Description:
*     Init the game 'Menus' feature module.
*/
void    RFM_MenusInit( void );
/*
*   Description:
*     Init the 'Event' feature module.
*/
void    RFM_EventInit( void );
/*
*   Description:
*     Init the 'Player' feature module.
*/
void    RFM_PlayerInit( void );

/****** Stage Init ******************************************************************************/
/*
*   Description:
*     Init the 'White Jungle' feature module.
*/
void    RFM_WhiteJungleInit( void );
/*
*   Description:
*     Init the 'City Escape' feature module.
*/
void    RFM_CityEscapeInit( void );
/*
*   Description:
*     Init the 'Mission Street' feature module.
*/
void    RFM_MissionStreetInit( void );
/*
*   Description:
*     Init the 'Crazy Gadget' feature module.
*/
void    RFM_CrazyGadgetInit( void );
/*
*   Description:
*     Init the 'Aquatic Mine' feature module.
*/
void    RFM_AquaticMineInit( void );
/*
*   Description:
*     Init the 'Cannons Core (All Characters)' feature module.
*/
void    RFM_CannonsCoreInit( void );
/*
*   Description:
*     Init the 'King Boom Boo' feature module.
*/
void    RFM_BossBogyInit( void );
/*
*   Description:
*     Init the 'Cart Racing' feature module.
*/
void    RFM_CartInit( void );
/*
*   Description:
*     Init the 'Chao World' feature module.
*/
void    RFM_ChaoInit( void );

EXTERN_END

#endif/*H_RF_MODULE_INTERNAL*/
