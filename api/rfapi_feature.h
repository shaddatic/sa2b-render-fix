/*
*   SA2 Render Fix - '/rfapi_feature.h'
*
*   Description:
*     The 'Feature' API Module is for checking the current state of specific features of Render Fix are currently
* 
*   Version History:
*     - v1.3.0.0        : Version 0, initial release
*     - v1.4.0.0        : Version 1, added 'NewEventRenderer' and other player related functions
* 
*   Availability:
*     - Before Init     : No
*     - At Init         : Yes
*     - After Init      : Yes
*/
#ifndef H_RFAPI_FEATURE
#define H_RFAPI_FEATURE

/********************************/
/*  Constants                   */
/********************************/
/****** API Module Version **********************************************************************/
#define RFAPI_FEATURE_VER           (1) /* feature api version                                  */

/********************************/
/*  API Structures              */
/********************************/
/****** Feature API *****************************************************************************/
typedef struct
{
    uint32_t version;               /* structure version                                        */

    /****** Version >= 0 ************************************************************************/

    /**** Global ********************************************/
    /*
    *   Description:
    *     If the back-color is enabled. If this is false, the back-color will
    *   always be black no matter what color it's actually set to.
    */
    bool (__cdecl* BackColorDraw)( void );
    /*
    *   Description:
    *     If spot light drawing has been fixed. This is used in Eggman stages for
    *   his walker's flashlight. If this is false, spot lights won't behave
    *   correctly.
    */
    bool (__cdecl* SpotLightFix)( void );
    /*
    *   [[ DEPRICATED : v1.4.0.0 ]]
    *
    *   Deprication Info:
    *     - state           : always returns 'true'
    *     - reason          : no longer a feature, renderer matches Dreamcast by default
    *     - alternative     : none
    * 
    *   Description:
    *     If environment maps have been flipped horizontally compared to vanilla.
    *   This is done to match Dreamcast, which also has env maps flipped compared
    *   to GC and PC.
    */
    bool (__cdecl* EnvMapFlip)( void );
    /*
    *   Description:
    *     If culling state is set to 'AUTO' by default. Some users may choose to
    *   turn it off, forcing the default state to 'NONE'. Even if that is the case,
    *   the culling render state can still be changed manually if needed.
    */
    bool (__cdecl* BackFaceCulling)( void );
    /*
    *   [[ DEPRICATED : v1.4.0.0 ]]
    *
    *   Deprication Info:
    *     - state           : always returns 'true'
    *     - reason          : no longer a feature, as tinting is now fixed at render time
    *     - alternative     : none
    * 
    *   Description:
    *     If models have had their gray diffuse fixed. This is done by setting
    *   their diffuse material to white manually at startup.
    */
    bool (__cdecl* FixModelTint)( void );

    /**** Shadows *******************************************/
    /*
    *   [[ DEPRICATED : v1.4.0.0 ]]
    * 
    *   Deprication Info:
    *     - state           : always returns '0.6875'
    *     - reason          : the shadow intensity is no longer changeable by the user
    *     - alternative     : none
    *
    *   Description:
    *     Get the shadow opacity used for the main game. This is used for both
    *   modifier volumes and shadow maps.
    * 
    *   Returns:
    *     The shadow opacity ranging from 0.f (invisible) to 1.f (fully opaque).
    */
    float(__cdecl* ShadowOpacityGlobal)( void );
    /*
    *   [[ DEPRICATED : v1.4.0.0 ]]
    * 
    *   Deprication Info:
    *     - state           : always returns '0.55078125'
    *     - reason          : the shadow intensity is no longer changeable by the user
    *     - alternative     : none
    * 
    *   Description:
    *     Get the shadow opacity used for Chao World. This is used for modifier
    *   volumes. Shadow maps can use this opacity, but only when the experimental
    *   feature for it is enabled.
    * 
    *   Returns:
    *     The shadow opacity ranging from 0.f (invisible) to 1.f (fully opaque).
    */
    float(__cdecl* ShadowOpacityChao)( void );

    /**** Cheap Shadows *************************************/
    /*
    *   Description:
    *     If Modifier Shadows, also known as 'Cheap Shadows', are enabled. If this
    *   is false, drawing modifier volumes will simply fail.
    */
    bool (__cdecl* CheapShadow)( void );
    /*
    *   Description:
    *     If Modifier Shadows are in performance mode. This reduces their 
    *   transparency sorting accuracy by drawing them in fewer Task layers.
    */
    bool (__cdecl* CheapShadowPerformance)( void );
    /*
    *   [[ DEPRICATED : v1.3.2.0 ]]
    *   
    *   Deprication Info:
    *     - state           : always returns 'false'
    *     - reason          : no longer a feature, cheap shadows were optimized enough to not need it
    *     - alternative     : none
    * 
    *   Description:
    *     If Modifier Shadows are in ultra performance mode. This further reduces
    *   their transparency sorting accuracy by drawing them with the fastest method
    *   possible, without much consideration for quality.
    */
    bool (__cdecl* CheapShadowUltraPerformance)( void );
    /*
    *   Description:
    *     If the player characters are using Modifier Volumes as shadows. If this
    *   is false, they are still using the GC shadow maps.
    */
    bool (__cdecl* CheapShadowPlayer)( void );

    /****** Version >= 1 ************************************************************/

    /**** Event *********************************************/
    /*
    *   Description:
    *     If the "Enhanced Event Renderer" is enabled, which emulates Dreamcast
    *   draw functions, restores the original multi-light code, and more.
    */
    bool (__cdecl* NewEventRenderer)( void );

    /**** Player ********************************************/
    /*
    *   Description:
    *     If Chaos 0 is set to use his GameCube texture animation cycle.
    */
    bool (__cdecl* Chaos0TexAnim)( void );
    /*
    *   Description:
    *     If a player character is using their Dreamcast model.
    *
    *   Notes:
    *     - Even if the setting is enabled, this may still return 'false' if
    *       another mod changes the player models. If another mod uses
    *       'ReplaceFile' though, this may return 'true' even if the Dreamcast
    *       models won't display in-game.
    * 
    *   Parameters:
    *     - pno         : player character number                    [SONIC~CHAOS0]
    */
    bool (__cdecl* DreamcastPlayerModel)( int pno );
    /*
    *   Description:
    *     If player shadowing is disabled when using modifier shadows.
    */
    bool (__cdecl* DisablePlayerShadowing)( void );
}
RFAPI_FEATURE;

#endif/*H_RFAPI_FEATURE*/
