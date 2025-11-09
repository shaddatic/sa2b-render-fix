/*
*   SA2 Render Fix - '/rf_graphics.h'
*
*   Description:
*     Render Fix GX replacement code.
*/
#ifndef H_RF_GRAPHICS
#define H_RF_GRAPHICS

/********************************/
/*  Includes                    */
/********************************/
/****** Dx9 Control *****************************************************************************/
#include <dx9ctrl/dx9ctrl.h>

EXTERN_START

/********************************/
/*  Prototypes                  */
/********************************/
/****** Dx9 Control *****************************************************************************/
/*
*   Description:
*     Convert a Dreamcast mipmap depth adjust to a DirectX 9 compatible mipmap LOD bias.
*
*   Parameters:
*     - mipdadjust  : mipmap 'd' adjust value
*
*   Returns:
*     Mipmap LOD bias float value as unsigned int.
*/
dx9_uint RFGX_GetMipmapDepthAdjust( int mipdadjust );
/*
*   Description:
*     Set a DirectX 9 texture sampler state with support for user defined overrides.
*
*   Parameters:
*     - index       : sampler index
*     - state       : sampler state to set to
*     - mode        : mode to set
*/
void    RFGX_SetSamplerState( int index, dx9_samplerstate state, dx9_uint mode );

EXTERN_END

#endif/*H_RF_GRAPHICS*/
