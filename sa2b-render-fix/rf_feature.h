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
bool    RF_BackColorDraw( void );
bool    RF_SpotLightFix( void );
bool    RF_EnvMapFlip( void );

/****** Shadows ******/
float   RF_ShadowOpacityGlobal( void );
float   RF_ShadowOpacityChao( void );

/** Cheap shadows **/
bool    RF_CheapShadow( void );
bool    RF_CheapShadowPerformance( void );
bool    RF_CheapShadowPlayer( void );

EXTERN_END

#endif/*_RF_FEATURE_H_*/
