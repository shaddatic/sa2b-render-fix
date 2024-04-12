/*
*   SA2 Render Fix - '/rf_ctrl.h'
*
*   Description:
*       Render Fix control functions.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_CTRL_H_
#define _RF_CTRL_H_

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Modifier buffer **/
void    RFCTRL_SetModBufferSize( size_t nbTri, size_t nbTriList );  /* Set Modifier buffer size                */

/** Cheap Shadows **/
void    RFCTRL_CheapShadowChaoWorldDisable( void );                 /* Don't apply cheap shadows in Chao World */

EXTERN_END

#endif/*_RF_CULL_H_*/
