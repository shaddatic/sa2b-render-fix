/*
*   SA2 Render Fix - '/rf_cull.h'
*
*   Description:
*       Contains useful draw functions
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_CULL_H_
#define _RF_CULL_H_

/************************/
/*  Enums               */
/************************/
typedef enum
{
    CULLMD_AUTO,    // Set cull by model flags
    CULLMD_NONE,    // No culling
    CULLMD_NORMAL,  // Normal culling
    CULLMD_INVERSE, // Inverted culling
}
RFE_CULLMODE;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Set cull mode **/
void    RF_SetCullMode( RFE_CULLMODE mode );

EXTERN_END

#endif/*_RF_CULL_H_*/
