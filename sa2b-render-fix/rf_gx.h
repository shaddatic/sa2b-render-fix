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

EXTERN_END

#endif/*H_RF_GX*/
