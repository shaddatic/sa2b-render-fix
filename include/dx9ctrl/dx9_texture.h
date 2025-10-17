/*
*   dx9ctrl (SA2B) - '/dx9_texture.h'
*
*   Description:
*     DirectX 9 control library for SA2PC texture header.
*/
#ifndef H_DX9CTRL_TEXTURE
#define H_DX9CTRL_TEXTURE

/********************************/
/*  Includes                    */
/********************************/
/****** DX9 Control *****************************************************************************/
#include <dx9ctrl/dx9_common.h>         /* dx9 common                                           */

DX9_HEADER_START

/********************************/
/*  Constants                   */
/********************************/
/****** Shader Constants ************************************************************************/
#define DX9_TSV_REGISTER_MAX        (3)  /* max texture sampler number (vertex)                 */
#define DX9_TSP_REGISTER_MAX        (15) /* max texture sampler number (pixel)                  */

/********************************/
/*  Opaque Types                */
/********************************/
/****** DirectX Types ***************************************************************************/
typedef struct dx9_texture          dx9_texture;    /* IDirect3DTexture9                        */

/********************************/
/*  Enums                       */
/********************************/
/****** Texture Formats *************************************************************************/
/*
*   Component Index:
*     - A       : Alpha
*     - R,G,B   : Red,Green,Blue
*     - X       : Nothing
*     - P       : Indexed Color (Palette)
*     - L       : Luminance
*     - Q,W,U,V : U/V Coords Data
*     - D       : Depth buffer
*     - S       : Stencil buffer
*     - I       : Index
*     - C       : Compressed
*/
typedef enum dx9_texfmt
{
    DX9_TEXFMT_UNKNOWN          = 0,

    /** Basic Color Formats *****************************************************************/

    DX9_TEXFMT_R8G8B8           = 20,       /* RGB  as unsigned 8,8,8                       */
    DX9_TEXFMT_A8R8G8B8,                    /* ARGB as unsigned 8,8,8,8                     */
    DX9_TEXFMT_X8R8G8B8,                    /* XRGB as unsigned 8,8,8,8                     */
    DX9_TEXFMT_R5G6B5,                      /* RGB  as unsigned 5,6,5                       */
    DX9_TEXFMT_X1R5G5B5,                    /* XRGB as unsigned 1,5,5,5                     */
    DX9_TEXFMT_A1R5G5B5,                    /* ARGB as unsigned 1,5,5,5                     */
    DX9_TEXFMT_A4R4G4B4,                    /* ARGB as unsigned 4,4,4,4                     */
    DX9_TEXFMT_R3G2B2,                      /* RGB  as unsigned 3,3,2                       */
    DX9_TEXFMT_A8,                          /* A    as unsigned 8                           */
    DX9_TEXFMT_A8R3G3B2,                    /* ARGB as unsigned 8,3,3,2                     */
    DX9_TEXFMT_X4R4G4B4,                    /* XRGB as unsigned 4,4,4,4                     */
    DX9_TEXFMT_A2B10G10R10,                 /* ABGR as unsigned 2,10,10,10                  */
    DX9_TEXFMT_A8B8G8R8,                    /* ABGR as unsigned 8,8,8,8                     */
    DX9_TEXFMT_X8B8G8R8,                    /* XBGR as unsigned 8,8,8,8                     */
    DX9_TEXFMT_G16R16,                      /* GR   as unsigned 16,16                       */
    DX9_TEXFMT_A2R10G10B10,                 /* ARGB as unsigned 2,10,10,10                  */
    DX9_TEXFMT_A16R16G16B16,                /* ARGB as unsigned 16,16,16,16                 */

    /** Palette Color Formats ***************************************************************/

    DX9_TEXFMT_A8P8             = 40,       /* AP   as unsigned 8,8                         */
    DX9_TEXFMT_P8,                          /* P    as unsigned 8                           */

    /** Luminance Color Formats *************************************************************/

    DX9_TEXFMT_L8               = 50,       /* L    as unsigned 8                           */
    DX9_TEXFMT_A8L8,                        /* AL   as unsigned 8,8                         */
    DX9_TEXFMT_A4L4,                        /* AL   as unsigned 4,4                         */

    DX9_TEXFMT_L16              = 81,       /* L    as unsigned 16                          */

    /** UV Coords Formats *******************************************************************/

    DX9_TEXFMT_V8U8             = 60,       /* VU   as signed 8,8                           */
    DX9_TEXFMT_L6V5U5,                      /* LVU  as unsigned 6; signed 5,5               */
    DX9_TEXFMT_X8L8V8U8,                    /* XLVU as unsigned 8,8; signed 8,8             */
    DX9_TEXFMT_Q8W8V8U8,                    /* QWVU as signed 8,8,8,8                       */
    DX9_TEXFMT_V16U16,                      /* VU   as signed 16,16                         */
    DX9_TEXFMT_A2W10V10U10      = 67,       /* AWVU as unsigned 2; signed 10,10,10          */

    DX9_TEXFMT_Q16W16V16U16     = 110,      /* QWVU as signed 16,16,16,16                   */

    DX9_TEXFMT_CV8U8            = 117,      /* VU   as signed 8,8; compressed               */

    /** Compressed Formats ******************************************************************/

    DX9_TEXFMT_UYVY             = 'YVYU',   /* UYVY                                         */
    DX9_TEXFMT_R8G8B8G8         = 'GBGR',   /* RGBG                                         */
    DX9_TEXFMT_YUY2             = '2YUY',   /* YUY2                                         */
    DX9_TEXFMT_G8R8G8B8         = 'BGRG',   /* GRGB                                         */
    DX9_TEXFMT_DXT1             = '1TXD',   /* DXT1                                         */
    DX9_TEXFMT_DXT2             = '2TXD',   /* DXT2                                         */
    DX9_TEXFMT_DXT3             = '3TXD',   /* DXT3                                         */
    DX9_TEXFMT_DXT4             = '4TXD',   /* DXT4                                         */
    DX9_TEXFMT_DXT5             = '5TXD',   /* DXT5                                         */

    /** Other Formats ***********************************************************************/

    DX9_TEXFMT_MET1             = '1TEM',   /* multi-element texture                        */

    DX9_TEXFMT_VERTEX           = 100,      /* vertex data                                  */

    /** Depth/Stencil Formats ***************************************************************/

    DX9_TEXFMT_D16_LCK          = 70,       /* D    as unsigned 16; Lockable                */
    DX9_TEXFMT_D32,                         /* D    as unsigned 32                          */
    DX9_TEXFMT_D15S1            = 73,       /* DS   as unsigned 15,1                        */
    DX9_TEXFMT_D24S8            = 75,       /* DS   as unsigned 24,8                        */
    DX9_TEXFMT_D24X8            = 77,       /* DX   as unsigned 24,8                        */
    DX9_TEXFMT_D24X4S4          = 79,       /* DXS  as unsigned 24,4,4                      */
    DX9_TEXFMT_D16,                         /* D    as unsigned 16                          */

    DX9_TEXFMT_D32_F_LCK        = 82,       /* D    as float 32                             */
    DX9_TEXFMT_D32S8_F          = 83,       /* DS   as float 32; unsigned 8                 */

    DX9_TEXFMT_I16              = 101,      /* I    as unsigned 16                          */
    DX9_TEXFMT_I32,                         /* I    as unsigned 32                          */

    /** Floating Point Formats **************************************************************/

    DX9_TEXFMT_R16_F            = 111,      /* R    as float 16                             */
    DX9_TEXFMT_G16R16_FF,                   /* GR   as float 16,16                          */
    DX9_TEXFMT_A16B16G16R16_FFFF,           /* ABGR as float 16,16,16,16                    */

    DX9_TEXFMT_R32_F            = 114,      /* R    as float 32                             */
    DX9_TEXFMT_G32R32_FF,                   /* GR   as float 32,32                          */
    DX9_TEXFMT_A32B32G32R32_FFFF,           /* ABGR as float 32,32,32,32                    */
}
dx9_texfmt;

/****** Texture Sampler *************************************************************************/
typedef enum dx9_texaddr
{
    DX9_TEXADDR_WRAP            = 1,        /* repeat texture outside 0~1 coords range          */
    DX9_TEXADDR_MIRROR,                     /* mirror texture outside 0~1 coords range          */
    DX9_TEXADDR_CLAMP,                      /* clamp coordinates to 0~1 coords range            */
    DX9_TEXADDR_BORDER,                     /* use border color outside 0~1 coords range        */
    DX9_TEXADDR_MIRRORONCE,                 /* mirror once, then clamp                          */
}
dx9_texaddr;

typedef enum dx9_texfilter
{
    DX9_TEXFILTER_NONE          = 0,        /* no filter                                        */

    DX9_TEXFILTER_POINT,                    /* point sampling                                   */
    DX9_TEXFILTER_LINEAR,                   /* bilinear filter                                  */
    DX9_TEXFILTER_ANISOTROPIC,              /* anisotropic filter                               */
    DX9_TEXFILTER_PYRAMIDALQUAD,            /* pyramidal quad                                   */
    DX9_TEXFILTER_GAUSSIANQUAD,             /* gaussian quad                                    */
    DX9_TEXFILTER_CONVOLUTIONMONO,          /* convolution mono                                 */
}
dx9_texfilter;

typedef enum dx9_samplerstate
{
    DX9_SAMPLER_ADDRESSU        = 1,        /* address mode for U component                     */
    DX9_SAMPLER_ADDRESSV,                   /* address mode for V component                     */
    DX9_SAMPLER_ADDRESSW,                   /* address mode for W component                     */
    DX9_SAMPLER_BORDERCOLOR,                /* border color                     [0xAA'RR'GG'BB] */
    DX9_SAMPLER_MAGFILTER,                  /* texture filter for magnification                 */
    DX9_SAMPLER_MINFILTER,                  /* texture filter for minification                  */
    DX9_SAMPLER_MIPFILTER,                  /* texture filter for mipmaps during minification   */
    DX9_SAMPLER_MIPMAPLODBIAS,              /* mipmap LOD bias                          [float] */
    DX9_SAMPLER_MAXMIPLEVEL,                /* maximum mipmap level                             */
    DX9_SAMPLER_MAXANISOTROPY,              /* maximum anisotropy                               */
    DX9_SAMPLER_SRGBTEXTURE,                /* is srgb texture                                  */
    DX9_SAMPLER_ELEMENTINDEX,               /* multi-element index                              */
    DX9_SAMPLER_DMAPOFFSET,                 /* displacement map offset                          */
}
dx9_samplerstate;

/********************************/
/*  Structures                  */
/********************************/
/****** Texture Lock ****************************************************************************/
typedef struct dx9_texlock
{
    dx9_size szRow;                 /* size of single pixel row in bytes                        */
    void*    pData;                 /* pointer to locked data                                   */
}
dx9_texlock;

/********************************/
/*  Prototypes                  */
/********************************/
/****** Device Functions ************************************************************************/
/*
*   Description:
*     Create a new, empty texture resource.
* 
*   Parameters:
*     - w,h         : texture width and height in pixels
*     - level       : mip levels
*     - usage       : resource usage flags
*     - format      : texture format
*     - pool        : memory pool setting
* 
*   Returns:
*     Texture resource handle; or 'nullptr' on failure.
*/
dx9_texture* DX9_CreateTexture( dx9_size w, dx9_size h, dx9_size level, dx9_usage usage, dx9_texfmt format, dx9_pool pool );
/*
*   Description:
*     Set texture to sampler index for drawing.
* 
*   Paramters:
*     - ix          : sampler index                                                          [0~15]
*     - pTexture    : texture resource handle
*/
bool    DX9_SetTexture( dx9_size ix, dx9_texture* pTexture );
/*
*   Description:
*     Set texture to sampler index for drawing.
* 
*   Paramters:
*     - ix          : sampler index                                                          [0~15]
*     - state       : sampler state to change
*     - mode        : new sampler state mode
*/
bool    DX9_SetSamplerState( dx9_size ix, dx9_samplerstate state, dx9_uint mode );

/****** Texture Functions ***********************************************************************/
/*
*   Description:
*     Release an open texture resource.
* 
*   Parameters:
*     - pTexture    : texture resource handle
* 
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_TextureRelease( dx9_texture* pTexture );
/*
*   Description:
*     Release an open texture resource.
* 
*   Notes:
*     - If no lock rect is given, the entire texture is locked
* 
*   Parameters:
*     - pTexture     : texture resource handle
*     - level        : mip level to lock
*     - pOptLockRect : rect area to lock                                          [opt:nullptr]
*     - flag         : resource lock flags
* 
*   Returns:
*     A filled 'dx9_texlock' structure; or a null'ed out structure on failure.
*/
dx9_texlock DX9_TextureLock( dx9_texture* pTexture, dx9_size level, const dx9_rect* pOptLockRect, dx9_lock flag );
/*
*   Description:
*     Unlock and push a texture resource.
* 
*   Parameters:
*     - pTexture    : texture resource handle
*     - level       : mip level to unlock
* 
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_TextureUnlock( dx9_texture* pTexture, dx9_size level );

DX9_HEADER_END

#endif/*H_DX9CTRL_TEXTURE*/