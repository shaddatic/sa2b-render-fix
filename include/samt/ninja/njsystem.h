/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/ninja/njsystem.h'
*
*   Description:
*     Ninja system header.
*/
#ifndef H_NJ_SYSTEM
#define H_NJ_SYSTEM

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>  /* ninja common                                               */

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** Ninja ***********************************************************************************/
typedef struct njtexsurface         NJS_TEXSURFACE; /* texture surface                          */

/********************************/
/*  Constants                   */
/********************************/
/****** Color Target ****************************************************************************/
#define NJD_SOURCE_COLOR                        (0) /* new rasterized pixel color               */
#define NJD_DESTINATION_COLOR                   (1) /* render target pixel color                */

/****** Color Blending Mode *********************************************************************/
#define NJD_COLOR_BLENDING_BOTHINVALPHA         ( 0) /* src = SA, dst = ISA; tgt param ignored  */
#define NJD_COLOR_BLENDING_BOTHSRCALPHA         ( 1) /* src = ISA, dst = SA; tgt param ignored  */

#define NJD_COLOR_BLENDING_DESTALPHA            ( 2) /* tgt * destination alpha                 */
#define NJD_COLOR_BLENDING_DESTCOLOR            ( 3) /* tgt * destination color            [sc] */
#define NJD_COLOR_BLENDING_INVDESTALPHA         ( 4) /* tgt * inverse destination alpha         */
#define NJD_COLOR_BLENDING_INVDESTCOLOR         ( 5) /* tgt * inverse destination color   [isc] */
#define NJD_COLOR_BLENDING_INVSRCALPHA          ( 6) /* tgt * inverse source alpha              */
#define NJD_COLOR_BLENDING_INVSRCCOLOR          ( 7) /* tgt * inverse source color              */
#define NJD_COLOR_BLENDING_SRCALPHA             ( 8) /* tgt * source alpha                      */
#define NJD_COLOR_BLENDING_SRCCOLOR             ( 9) /* tgt * source color                      */
#define NJD_COLOR_BLENDING_ONE                  (10) /* tgt * 1                                 */
#define NJD_COLOR_BLENDING_ZERO                 (11) /* tgt * 0                                 */

/****** Polygon Culling *************************************************************************/
#define NJD_POLYGON_NOCULLING                   (0x00000000) /* no culling                      */
#define NJD_POLYGON_CULLINGSMALL                (0x08000000) /* cull small polygons             */
#define NJD_POLYGON_CULLINGACW                  (0x10000000) /* cull anti-clockwise polygons    */
#define NJD_POLYGON_CULLINGCW                   (0x18000000) /* cull clockwise polygons         */

/****** Texture Shading Mode ********************************************************************/
/*
*   t = texture
*   c = color
*   o = offset color
*
*   pixel_color | pixel_alpha
*/
#define NJD_TEX_SHADING_MODE_DECAL              (0x00000000) /*  RGBt + RGBo                         | At       */
#define NJD_TEX_SHADING_MODE_MODULATE           (0x00000040) /* (RGBc * RGBt) + RGBo                 | Ac       */
#define NJD_TEX_SHADING_MODE_DECALALPHA         (0x00000080) /* (RGBt * At) + (RGBc * (1-At)) + RGBo | Ac       */
#define NJD_TEX_SHADING_MODE_MODULATEALPHA      (0x000000C0) /* (RGBc * RGBt) + RGBo                 | Ac * At  */

/****** Texture Filtering ***********************************************************************/
#define NJD_TEXTUREFILTER_POINT_SAMPLE          (0x00000000) /* point filtering (no filter)     */
#define NJD_TEXTUREFILTER_BILINEAR              (0x00002000) /* bilinear filtering              */
#define NJD_TEXTUREFILTER_TRILINEAR_A           (0x00004000) /* trilinear filtering A (+Z)      */
#define NJD_TEXTUREFILTER_TRILINEAR_B           (0x00006000) /* trilinear filtering B (+1-Z)    */

/****** Texture Clamping ************************************************************************/
#define NJD_TEXTURECLAMP_NOCLAMP                (0x00000000) /* no texture clamp                */
#define NJD_TEXTURECLAMP_CLAMP_V                (0x00008000) /* texture clamp V                 */
#define NJD_TEXTURECLAMP_CLAMP_U                (0x00010000) /* texture clamp U                 */
#define NJD_TEXTURECLAMP_CLAMP_UV               (0x00018000) /* texture clamp both              */

/****** Texture Flipping ************************************************************************/
#define NJD_TEXTUREFLIP_NOFLIP                  (0x00000000) /* no texture flip                 */
#define NJD_TEXTUREFLIP_FLIP_V                  (0x00020000) /* texture flip V                  */
#define NJD_TEXTUREFLIP_FLIP_U                  (0x00040000) /* texture flip U                  */
#define NJD_TEXTUREFLIP_FLIP_UV                 (0x00060000) /* texture flip both               */

/****** Modifier Mode ***************************************************************************/
#define NJD_MODIFIER_INSIDE                     (0x20000000) /* shade inside polygons           */
#define NJD_MODIFIER_OUTSIDE                    (0x40000000) /* shade outside polygons          */

/****** User Clipping ***************************************************************************/
#define NJD_CLIP_DISABLE                        (0) /* no clipping                              */
#define NJD_CLIP_RESERVE                        (1) /* reserved                                 */
#define NJD_CLIP_INSIDE                         (2) /* clip inside area                         */
#define NJD_CLIP_OUTSIDE                        (3) /* clip outside area                        */

/********************************/
/*  Enums                       */
/********************************/
/****** Ninja Context ***************************************************************************/
enum
{
    NJD_SYSTEM_CTX = 0,             /* system context                                           */
    NJD_DEBUG_CTX,                  /* debug context                                            */
    NJD_NINDOWS_CTX,                /* ninja windows context                                    */
    NJD_USER0_CTX,                  /* user context 1                                           */
    NJD_USER1_CTX,                  /* user context 2                                           */
    NJD_USER2_CTX,                  /* user context 3                                           */

    NJD_CONTEXT_MAX                 /* enum count                                               */
};

/********************************/
/*  Structures                  */
/********************************/
/****** System Attribute ************************************************************************/
typedef struct njsysattr
{
    Sint8 attr[64];                 /* system attribute (ninja context)                         */
}
NJS_SYS_ATTR;

/****** Ninja Screen ****************************************************************************/
typedef struct njscreen
{
    Float   xad, yad;               /* aspect * dist                                            */
    Float   cx, cy;                 /* screen center                                            */
    Float   ooxad, ooyad;           /* 1.0 / xad~yad                                            */
    Float   dist;                   /* screen distance	                                        */
    Float   ax, ay;                 /* aspect                                                   */
    Float   aspect;                 /* ay/ax                                                    */
    Float   w, h;                   /* screen size                                              */
}
NJS_SCREEN;

typedef struct njclip
{
    Float       f_clip;             /* far clip                                                 */
    Float       n_clip;             /* near clip                                                */
    Float       x1, x0, y1, y0;     /* screen clip                                              */
    NJS_POINT2  d[2];               /* 2d clip                                                  */
}
NJS_CLIP;

/********************************/
/*  Data                        */
/********************************/
/****** Current Screen **************************************************************************/
#define _nj_screen_                         DATA_REF(NJS_SCREEN  , 0x02670300)
#define _nj_clip_                           DATA_REF(NJS_CLIP    , 0x02670560)

/****** Control 3D ******************************************************************************/
#define _nj_control_3d_flag_                DATA_REF(Uint32      , 0x025F02D8)

/****** Constant Attribute **********************************************************************/
#define _nj_constant_attr_and_              DATA_REF(Uint32      , 0x025F0268)
#define _nj_constant_attr_or_               DATA_REF(Uint32      , 0x025F02D4)

/****** Constant Material ***********************************************************************/
#define _nj_constant_material_              DATA_REF(NJS_ARGB    , 0x025EFFD0)

/********************************/
/*  Prototypes                  */
/********************************/
/************************************************************************************************/
/*
*   Context
*/
/****** Context *********************************************************************************/
/*
*   Description:
*     Set current Ninja context slot.
*
*   Parameters:
*     - n           : context number                                              [NJD_###_CTX]
*/
void    njSetCurrentContext( Int n );

/************************************************************************************************/
/*
*   System Attribute
*/
/****** Get/Set System Attribute ****************************************************************/
/*
*   Description:
*     Get the current Ninja system attribute state.
*
*   Notes:
*     - Copies the current Ninja context as-is into 'attr'
*
*   Parameters:
*     - attr        : system attribute buffer
*/
void    njGetSystemAttr( NJS_SYS_ATTR* attr );
/*
*   Description:
*     Set the current Ninja system attribute state.
*
*   Notes:
*     - Copies attr' as-is into the current Ninja context
*
*   Parameters:
*     - attr        : system attribute buffer
*/
void    njSetSystemAttr( const NJS_SYS_ATTR* attr );

/************************************************************************************************/
/*
*   Back Texture
*/
/****** Back Color ******************************************************************************/
/*
*   Description:
*     Set the back color
*
*   Notes:
*     - Requires 'SA2 Render Fix' mod to take full effect.
*
*   Parameters:
*     - color1      : upper left color                                          [0xAA'RR'GG'BB]
*     - color2      : upper right color                                         [0xAA'RR'GG'BB]
*     - color3      : bottom color                                              [0xAA'RR'GG'BB]
*/
void    njSetBackColor( Uint32 color1, Uint32 color2, Uint32 color3 );

/************************************************************************************************/
/*
*   Global Param
*/
/****** Specular Mode ***************************************************************************/
/*
*   Descrption:
*     Set the specular behavior of draw functions.
*
*   Notes:
*     - Behavior not implemented, no effect
*     - Has no effect on model draw.
*
*   Parameters:
*     - mode        : specular mode                                                    [ON/OFF]
*/
void	njSpecularMode( Int mode );

/************************************************************************************************/
/*
*   ISP Param
*/
/****** Polygon Culling *************************************************************************/
/*
*   Description:
*     Set the polygon culling mode of draw functions.
*
*   Notes:
*     - Behavior not implemented, no effect
*     - Has no effect on model draw.
*
*   Parameters:
*     - mode        : polygon culling mode to set                             [NJD_POLYGON_###]
*/
void    njPolygonCullingMode( Int mode );

/****** Z Buffer ********************************************************************************/
/*
*   Description:
*     Set Z buffering behavior.
*
*   Notes:
*     - Behavior not implemented, no effect
*
*   Parameters:
*     - mode        : z buffer mode                                                    [ON/OFF]
*/
void    njZBufferMode( Int mode );
/*
*   Description:
*     Set Z writing behavior.
*
*   Notes:
*     - Behavior not implemented, no effect
*
*   Parameters:
*     - mode        : z write mode                                                     [ON/OFF]
*/
void    njZWriteMode( Int mode );

/************************************************************************************************/
/*
*   TSP Param
*/
/****** Texture Parameters **********************************************************************/
/*
*   Description:
*     Set the texture shading mode of draw functions.
*
*   Notes:
*     - Behavior not implemented, no effect
*     - Has no effect on model draw, set by model parameters
*
*   Parameters:
*     - mode        : texture flip mode                              [NJD_TEX_SHADING_MODE_###]
*/
void    njTextureShadingMode( Int mode );
/*
*   Descrption:
*     Set the anisotropic filtering behavior of draw functions.
*
*   Notes:
*     - Behavior not implemented, no effect
*     - Has no effect on model draw, set by model parameters
*
*   Parameters:
*     - mode        : super sample mode                                                [ON/OFF]
*/
void    njSuperSampleMode( Int mode );
/*
*   Description:
*     Set the mipmap depth adjust level.
*
*   Notes:
*     - Behavior not implemented, no effect
*     - Has no effect on model draw, set by model parameters
*     - 1 = 0.25
*       2 = 0.5
*       3 = 0.75, etc
*
*   Parameters:
*     - level       : mipmap depth adjust                                                [1~15]
*/
void    njMipmapAdjust( Int level );
/*
*   Description:
*     Set if texture alpha component should be ignored.
*
*   Notes:
*     - Behavior not implemented, no effect
*
*   Parameters:
*     - mode        : ignore texture alpha                                             [ON/OFF]
*/
void    njIgnoreTextureAlphaMode( Int mode );
/*
*   Description:
*     Set the texture filter behavior of draw functions.
*
*   Notes:
*     - Requires 'SA2 Render Fix' to take effect
*     - Has no effect on model draw, set by model parameters
*
*   Parameters:
*     - mode        : texture filter mode                               [NJD_TEXTUREFILTER_###]
*/
void    njTextureFilterMode( Int mode );
/*
*   Description:
*     Set the texture clamping behavior of draw functions. Texture clamping occurs when the UV
*   coordinate exceeds the 0~1 range, any value outside of that range will be clamped to 0 or
*   1; this will cause the texture to 'streak'. 
*
*   Notes:
*     - Has no effect on model draw, set by model parameters
*
*   Parameters:
*     - mode        : texture clamping mode                              [NJD_TEXTURECLAMP_###]
*/
void    njTextureClampMode( Int mode );
/*
*   Description:
*     Set the texture flip behavior of draw functions. Texture flipping occurs when the UV
*   coordinates exceed a 0~1 range: for example, a V coordinate of '1.2' will flip that part of
*   the texture vertically; A V of '2.2' will flip it again, matching the intial 0~1 range.
*
*   Notes:
*     - Has no effect if texture clamping is enabled
*     - Has no effect on model draw, set by model parameters
*
*   Parameters:
*     - mode        : texture flip mode                                   [NJD_TEXTUREFLIP_###]
*/
void    njTextureFlipMode( Int mode );

/****** Color Clamp *****************************************************************************/
/*
*   Description:
*     Set the texture flip behavior of draw functions. Texture flipping occurs when the UV
*   coordinates exceed a 0~1 range: for example, a V coordinate of '1.2' will flip that part of
*   the texture vertically; A V of '2.2' will flip it again, matching the intial 0~1 range.
*
*   Notes:
*     - Behavior not implemented, no effect
*
*   Parameters:
*     - mode        : color clamp mode                                                 [ON/OFF]
*/
void    njColorClampMode( Int mode );

/****** Color Blending **************************************************************************/
/*
*   Description:
*     Set the color blending behavior of draw functions.
*
*   Notes:
*     - Has no effect on model draw, set by model parameters
*
*   Parameters:
*     - target      : color target (src/dst)                                    [NJD_###_COLOR]
*     - mode        : blending mode                                    [NJD_COLOR_BLENDING_###]
*/
void    njColorBlendingMode( Int target, Int mode );

/************************************************************************************************/
/*
*   Modifier Param
*/
/****** Modifier Mode ***************************************************************************/
/*
*   Description:
*     Set modifier inside/outside behavior.
*
*   Notes:
*     - Behavior not implemented, no effect
*
*   Parameters:
*     - mode        : modifier mode                                          [NJD_MODIFIER_###]
*/
void    njModifierMode( Int mode );

/************************************************************************************************/
/*
*   Screen
*/
/****** Set Screen ******************************************************************************/
/*
*   Description:
*     Initialize the screen and clip parameters.
*
*   Notes:
*     - Only cx, cy, dist, w, & h members are used, everything else is calculated
*     - Parameters will be automatically adjusted for non-4:3 display aspect ratios
*
*   Parameters:
*     - s           : ninja screen struct pointer
*/
void    njSetScreen( const NJS_SCREEN *s );
/*
*   Description:
*     Set the distance from the eye to the screen.
*
*   Notes:
*     - Sets all related parameters in '_nj_screen_'
*
*   Parameters:
*     - dist        : distance value
*/
void    njSetScreenDist( Float dist );
/*
*   Description:
*     Set the center coordinates of the screen.
*
*   Notes:
*     - Sets all related parameters in '_nj_screen_'
*
*   Parameters:
*     - ang         : perspective angle
*/
void    njSetScreenCenter( Float x, Float y );
/*
*   Description:
*     Set the aspect ratio of the screen.
*
*   Notes:
*     - Sets all related parameters in '_nj_screen_'
*
*   Examples:
*     - njSetAspect( 4.f, 3.f ); // 4:3 aspect ratio
*
*   Parameters:
*     - ax          : aspect x
*     - ay          : aspect y
*/
void    njSetAspect( Float ax, Float ay );
/*
*   Description:
*     Set and calculate the camera's horizontal view angle.
*
*   Examples:
*     - njSetPerspective( NJM_DEG_ANG(120.f) ); // 120 degrees horizontal angle
*
*   Parameters:
*     - ang         : horizontal view angle
*/
void    njSetPerspective( Angle ang );

/****** Set Clip ********************************************************************************/
/*
*   Description:
*     Set clipping range (viewport). Clipping is peformed on a pixel-by-pixel basis. Models,
*   when projected onto the screen + their radius, that are outside of this area will be
*   skipped and not drawn.
*
*   Notes:
*     - Clipping area is adjusted for non-4:3 display aspect ratios.
*
*   Parameters:
*     - v           : clipping range defined by top left & bottom right corners in
*                     hardware screenspace.                       [0/0~640/480, etc]
*/
void    njClip2D( const NJS_POINT2 v[2] );
/*
*   Description:
*     Set the near and far clipping limits. Lower values represent further
*   distances, with '-65535.f' representing the back of the screen and '-1.f' the
*   front of the screen.
*
*   Notes:
*     - Values outside of the expected range will be clamped to the nearest
*       expected value.
*
*   Parameters:
*     - n           : near clipping plane                                     [-65535.f ~ -1.f]
*     - f           : far clipping plane                                      [-65535.f ~ -1.f]
*/
void    njClipZ( Float n, Float f );

EXTERN_END

#endif/*H_NJ_SYSTEM*/
