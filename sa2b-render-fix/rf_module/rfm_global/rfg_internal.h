/*
*   SA2 Render Fix - '/rfm_global/rfg_internal.h'
*
*   Description:
*       Header for the Global feature module.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RFM_GLOBAL_INTERNAL_H_
#define _RFM_GLOBAL_INTERNAL_H_

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Initialize **/
void    RFG_BackfaceCullingInit( void );

void    RFG_DrawFunctionInit( void );

void    RFG_ModelTintInit( void );

void    RFG_EnvMapFlip( void );

void    RFG_TaskDisplayInit( void );

void    RFG_3DSpriteInit( void );

void    RFG_UiFilterInit( void );

EXTERN_END

#endif/*_RFM_GLOBAL_INTERNAL_H_*/
