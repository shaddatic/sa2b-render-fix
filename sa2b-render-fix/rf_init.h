/*
*   SA2 Render Fix - '/rf_init.h'
*
*   Description:
*     Init function and other mod export function header.
*/
#ifndef H_RF_INIT
#define H_RF_INIT

EXTERN_START

/********************************/
/*  Prototypes                  */
/********************************/
/************************************************************************************************/
/*
*   Init
*/
/****** Core ************************************************************************************/
/*
*   Description:
*     Config Init, for opening RF's config file, and End, for saving and freeing the config
*   file, functions.
*/
void    RF_ConfigInit( void );
void    RF_ConfigEnd(  void );
/*
*   Description:
*     Init the user message(box) system.
*/
void    RF_UserMessageInit( void );
/*
*   Description:
*     Init the 'Renderstate' system.
*/
void    RF_RenderStateInit( void );
/*
*   Description:
*     Init the 'Render Fix Ninja' system.
*/
void    RF_NinjaInit( void );
/*
*   Description:
*     Init the Font system.
*/
void    RF_FontInit( void );
/*
*   Description:
*     Init the 'Render Fix GX' system.
*/
void    RF_GxInit( void );
/*
*   Description:
*     Init the 'Render Fix Ninja Light' system.
*/
void    RF_LightInit( void );
/*
*   Description:
*     Init the shader system, and load Render Fix's custom game shaders.
*/
void    RF_ShaderInit( void );
/*
*   Description:
*     Init the 'Mod Check' system.
*
*   Notes:
*     - This should be called after all other modules have been.
*/
void    RF_ModCheckInit( void );

/****** Render Fix API **************************************************************************/
/*
*   Description:
*     Render Fix API 'Init' and 'End' functions.
*/
void    RFAPI_Init( void );
void    RFAPI_End(  void );

/****** RF Modules ******************************************************************************/
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

/****** RF Modules (Stage) **********************************************************************/
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

/************************************************************************************************/
/*
*   On Scene Start
*/
/****** Core ************************************************************************************/
/*
*   Description:
*     Frameskip 'OnRenderSceneStart' function.
*/
void    RF_FrameSkipSceneStart( void );

/************************************************************************************************/
/*
*   On Scene End
*/
/****** Core ************************************************************************************/
/*
*   Description:
*     Frameskip 'OnRenderSceneEnd' function.
*/
void    RF_FrameSkipSceneEnd( void );

EXTERN_END

#endif/*H_RF_INIT*/
