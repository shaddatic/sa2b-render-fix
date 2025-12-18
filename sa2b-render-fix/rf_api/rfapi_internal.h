/*
*   SA2 Render Fix - '/rf_api/rfapi_internal.h'
*
*   Description:
*     Render Fix API module internal header .
*/
#ifndef H_RF_API_INTERNAL
#define H_RF_API_INTERNAL

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Render Fix API **************************************************************************/
#include <rfapi.h>                  /* api headers                                              */

/********************************/
/*  Extern Data                 */
/********************************/
/****** Ninja ***********************************************************************************/
EXTERN const RFAPI_CONTROL          rfapi_control;
EXTERN const RFAPI_CONFIG           rfapi_config;
EXTERN const RFAPI_FEATURE          rfapi_feature;
EXTERN const RFAPI_DRAW             rfapi_draw;
EXTERN const RFAPI_RENDERSTATE      rfapi_rstate;
EXTERN const RFAPI_SHADER           rfapi_shader;
EXTERN const RFAPI_FONT             rfapi_font;
EXTERN const RFAPI_NINJA            rfapi_ninja;
EXTERN const RFAPI_NJDRAW           rfapi_njdraw;
EXTERN const RFAPI_CHUNK            rfapi_chunk;
EXTERN const RFAPI_LIGHT            rfapi_light;

#endif/*H_RF_API_INTERNAL*/
