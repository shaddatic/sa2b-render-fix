/*
*   SA2 Render Fix - '/rf_draw/rfd_cnkmdl/rfdcnk_internal.h'
*
*   Description:
*     Render Fix GX replacement code.
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_GX
#define H_RF_GX

EXTERN_START

/************************/
/*  Functions           */
/************************/
/****** Texture Info ****************************************************************/
typedef struct
{
    void* surface;
    int   address_u;
    int   address_v;
    int   min_filter;
    int   mag_filter;
    int   mip_level;
    int   palette;
    int   unk;
}
TEXTURE_INFO;

/************************/
/*  Functions           */
/************************/
/****** Init ************************************************************************/
/*
*   Description:
*     Init GX module.
*/
void    RF_GxInit( void );

/****** Init ************************************************************************/
/*
*   Description:
*     Set a texture to render state.
*
*   Parameters:
*     - pTex        : texture pointer
*     - index       : index slot
*/
void    RX_SetTexture( const TEXTURE_INFO* restrict pTex, int index );
/*
*   Description:
*     Set GX material color directly, without conversions.
*
*   Parameters:
*     - chan        : material channel number
*     - a           : alpha ambient color
*     - r           : red ambient color
*     - g           : green ambient color
*     - b           : blue ambient color
*/
void    RX_SetChanMatColor_Direct( int chan, float r, float g, float b, float a );
/*
*   Description:
*     Set GX ambient color directly, without conversions.
*
*   Parameters:
*     - r           : red ambient color
*     - g           : green ambient color
*     - b           : blue ambient color
*/
void    RX_SetChanAmbColor_Direct( float r, float g, float b );

EXTERN_END

#endif/*H_RF_GX*/
