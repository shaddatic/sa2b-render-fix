/*
*   SA2 Render Fix - '/rf_feature.h'
*
*   Description:
*       Render Fix feature checks.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_FEATURE_H_
#define _RF_FEATURE_H_

/************************/
/*  Functions           */
/************************/
EXTERN_START
/****** Global ******/
bool    RFF_BackColorDraw( void );
bool    RFF_SpotLightFix( void );
bool    RFF_EnvMapFlip( void );
bool    RFF_BackFaceCulling( void );

/****** Shadows ******/
float   RFF_ShadowOpacityGlobal( void );
float   RFF_ShadowOpacityChao( void );

/** Cheap shadows **/
bool    RFF_CheapShadow( void );
bool    RFF_CheapShadowPerformance( void );
bool    RFF_CheapShadowPlayer( void );

EXTERN_END

#endif/*_RF_FEATURE_H_*/
