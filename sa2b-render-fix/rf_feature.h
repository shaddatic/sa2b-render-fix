/*
*   SA2 Render Fix - '/rf_feature.h'
*
*   Description:
*     Render Fix feature checks.
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_FEATURE
#define H_RF_FEATURE

EXTERN_START

/************************/
/*  Prototypes          */
/************************/
/****** Global **********************************************************************/
/*
*   Description:
*     If the back-color is enabled. If this is false, the back-color will always be
*   black no matter what color it's actually set to.
*/
bool    RFF_BackColorDraw( void );
/*
*   Description:
*     If spot light drawing has been fixed. This is used in Eggman stages for his
*   walker's flashlight. If this is false, spot lights won't behave correctly.
*/
bool    RFF_SpotLightFix( void );
/*
*   Description:
*     If culling state is set to 'AUTO' by default. Some users may choose to turn
*   it off, forcing the default state to 'NONE'. Even if that is the case, the
*   culling render state can still be changed manually if needed.
*/
bool    RFF_BackFaceCulling( void );

/****** Shadows *********************************************************************/
/*
*   Description:
*     Get the shadow opacity used for the main game. This is used for both modifier
*   volumes and shadow maps.
* 
*   Returns:
*     The shadow opacity ranging from 0.f (invisible) to 1.f (fully opaque).
*/
f32     RFF_ShadowOpacityGlobal( void );
/*
*   Description:
*     Get the shadow opacity used for Chao World. This is used for modifier
*   volumes. Shadow maps can use this opacity, but only when the experimental
*   feature for it is enabled.
* 
*   Returns:
*     The shadow opacity ranging from 0.f (invisible) to 1.f (fully opaque).
*/
f32     RFF_ShadowOpacityChao( void );

/****** Cheap Shadows ***************************************************************/
/*
*   Description:
*     If Modifier Shadows, also known as 'Cheap Shadows', are enabled. If this is
*   false, drawing modifier volumes will simply fail.
*/
bool    RFF_CheapShadow( void );
/*
*   Description:
*     If Modifier Shadows are in performance mode. This reduces their transparency
*   sorting accuracy by drawing them in fewer Task layers.
*/
bool    RFF_CheapShadowPerformance( void );
/*
*   Description:
*     If the player characters are using Modifier Volumes as shadows. If this is
*   false, they are still using the GC shadow maps.
*/
bool    RFF_CheapShadowPlayer( void );

/****** Events **********************************************************************/
/*
*   Description:
*     If the "Enhanced Event Renderer" is enabled, which emulates Dreamcast draw
*   functions, restores the original multi-light code, and more.
*/
bool    RFF_NewEventRenderer( void );

/****** Player **********************************************************************/
/*
*   Description:
*     If Chaos 0 is set to use his GameCube texture animation cycle.
*/
bool    RFF_Chaos0TexAnim( void );

EXTERN_END

#endif/*H_RF_FEATURE*/
