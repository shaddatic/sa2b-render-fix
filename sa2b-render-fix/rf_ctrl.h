/*
*   SA2 Render Fix - '/rf_ctrl.h'
*
*   Description:
*     Render Fix mod control functions.
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_CTRL
#define H_RF_CTRL

EXTERN_START

/************************/
/*  Prototypes          */
/************************/
/****** Cheap Shadows ***************************************************************/
/*
*   Description:
*     Set modifier buffer size in triangles.
*
*   Notes:
*     - As of 1.3.2, 'nbTriList' has no effect.
*
*   Parameters:
*     - nbTri       : number of triangles to fit in the buffer
*     - nbTriList   : number of tri-list entries                       [depricated]
*/
void    RFCTRL_SetModBufferSize( i32 nbTri, i32 nbTriList );
/*
*   Description:
*     Disable Render Fix's own modifier shadow hooks in Chao World. This can be
*   used to apply your own modifier shadows without Render Fix getting in your way.
*/
void    RFCTRL_CheapShadowChaoWorldDisable( void );

/****** Event ***********************************************************************/
/*
*   Description:
*     Set flag to apply model material diffuse in Events when using Render Fix's
*   own Event Renderer.
*
*   Notes:
*     - Diffuse will only be applied on models using a SimpleDraw variant.
*/
void    RFCTRL_EventApplyModelDiffuse( void );

EXTERN_END

#endif/*H_RF_CTRL*/
