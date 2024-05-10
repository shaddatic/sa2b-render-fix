/*
*   SA2 Render Fix - '/rfm_cescape/ce_internal.h'
*
*   Description:
*       Internal header for City Escape module.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_API_INTERNAL_H_
#define _RF_API_INTERNAL_H_

/************************/
/*  External Headers    */
/************************/
/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** API (this is stupid) **/
#include <../api/renderfix_api.h>

/************************/
/*  API Structs         */
/************************/
EXTERN const RFAPI_CONTROL     rfapi_control;
EXTERN const RFAPI_CONFIG      rfapi_config;
EXTERN const RFAPI_FEATURE     rfapi_feature;
EXTERN const RFAPI_DRAW        rfapi_draw;
EXTERN const RFAPI_RENDERSTATE rfapi_rstate;
EXTERN const RFAPI_SHADER      rfapi_shader;
EXTERN const RFAPI_FONT        rfapi_font;

#endif/*_RF_API_INTERNAL_H_*/
