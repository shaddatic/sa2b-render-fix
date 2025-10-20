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
*     Init the module manager system.
*/
void    RF_ModuleInit( void );

/****** Mod Compat Checker **********************************************************************/
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
/*
*   Description:
*     Draw idle screen saver fade.
*/
void    RF_SysCtrlIdleFade( void );

EXTERN_END

#endif/*H_RF_INIT*/
