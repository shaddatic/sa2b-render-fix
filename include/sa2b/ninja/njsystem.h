/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njsystem.h'
*
*   Description:
*     Ninja system header.
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_NJ_SYSTEM
#define H_NJ_SYSTEM

/************************/
/*  External Includes   */
/************************/
/****** Ninja ***********************************************************************/
#include <sa2b/ninja/njcommon.h>  /* ninja common                                   */
#ifdef SAMT_INCL_INTERNAL
#include <sa2b/ninja/njtexture.h> /* ninja texture                                  */
#endif/*SAMT_INCL_INTERNAL*/

EXTERN_START

/************************/
/*  Constants           */
/************************/
/****** Polygon Culling *************************************************************/
#define NJD_POLYGON_NOCULLING                   (0x00000000)
#define NJD_POLYGON_CULLINGSMALL                (0x08000000)
#define NJD_POLYGON_CULLINGACW                  (0x10000000)
#define NJD_POLYGON_CULLINGCW                   (0x18000000)

/****** Color Target ****************************************************************/
#define NJD_SOURCE_COLOR                        (0)
#define NJD_DESTINATION_COLOR                   (1)

/****** Color Blending **************************************************************/
#define NJD_COLOR_BLENDING_BOTHINVALPHA         (0)
#define NJD_COLOR_BLENDING_BOTHSRCALPHA         (1)
#define NJD_COLOR_BLENDING_DESTALPHA            (2)
#define NJD_COLOR_BLENDING_DESTCOLOR            (3)
#define NJD_COLOR_BLENDING_INVDESTALPHA         (4)
#define NJD_COLOR_BLENDING_INVDESTCOLOR         (5)
#define NJD_COLOR_BLENDING_INVSRCALPHA          (6)
#define NJD_COLOR_BLENDING_INVSRCCOLOR          (7)
#define NJD_COLOR_BLENDING_SRCALPHA             (8)
#define NJD_COLOR_BLENDING_SRCCOLOR             (9)
#define NJD_COLOR_BLENDING_ONE                  (10)
#define NJD_COLOR_BLENDING_ZERO                 (11)

/****** Texture Shading Mode ********************************************************/
#define NJD_TEX_SHADING_MODE_DECAL              (0x00000000)
#define NJD_TEX_SHADING_MODE_MODULATE           (0x00000040)
#define NJD_TEX_SHADING_MODE_DECALALPHA         (0x00000080)
#define NJD_TEX_SHADING_MODE_MODULATEALPHA      (0x000000C0)

/****** Polygon Clipping ************************************************************/
#define NJD_CLIP_DISABLE                        (0)
#define NJD_CLIP_RESERVE                        (1)
#define NJD_CLIP_INSIDE                         (2)
#define NJD_CLIP_OUTSIDE                        (3)

/****** Texture Filtering ***********************************************************/
#define NJD_TEXTUREFILTER_POINT_SAMPLE          (0x00000000)
#define NJD_TEXTUREFILTER_BILINEAR              (0x00002000)
#define NJD_TEXTUREFILTER_TRILINEAR_A           (0x00004000)
#define NJD_TEXTUREFILTER_TRILINEAR_B           (0x00006000)

/****** Texture Clamping ************************************************************/
#define NJD_TEXTURECLAMP_NOCLAMP                (0x00000000)
#define NJD_TEXTURECLAMP_CLAMP_V                (0x00008000)
#define NJD_TEXTURECLAMP_CLAMP_U                (0x00010000)
#define NJD_TEXTURECLAMP_CLAMP_UV               (0x00018000)

/****** Texture Flipping ************************************************************/
#define NJD_TEXTUREFLIP_NOFLIP                  (0x00000000)
#define NJD_TEXTUREFLIP_FLIP_V                  (0x00020000)
#define NJD_TEXTUREFLIP_FLIP_U                  (0x00040000)
#define NJD_TEXTUREFLIP_FLIP_UV                 (0x00060000)

/****** Modifier Mode **************************************************************/
#define NJD_MODIFIER_INSIDE                     (0x20000000)
#define NJD_MODIFIER_OUTSIDE                    (0x40000000)

/************************/
/*  Enums               */
/************************/
/****** Ninja Context ***************************************************************/
enum
{
    NJD_SYSTEM_CTX = 0,         /* system context                                   */
    NJD_DEBUG_CTX,              /* debug context                                    */
    NJD_NINDOWS_CTX,            /* ninja windows context                            */
    NJD_USER0_CTX,              /* user context 1                                   */
    NJD_USER1_CTX,              /* user context 2                                   */
    NJD_USER2_CTX,              /* user context 3                                   */

    NJD_CONTEXT_MAX             /* enum count                                       */
};

/************************/
/*  Structures          */
/************************/
/****** System Attribute ************************************************************/
typedef struct
{
    Sint8 attr[64];
}
NJS_SYS_ATTR;

/****** Ninja Screen ****************************************************************/
typedef struct
{
    Float   xad, yad;           /* aspect * dist                                    */
    Float   cx, cy;             /* screen center                                    */
    Float   ooxad, ooyad;       /* 1.0 / xad~yad                                    */
    Float   dist;               /* screen distance	                                */
    Float   ax, ay;             /* aspect                                           */
    Float   aspect;             /* ay/ax                                            */
    Float   w, h;               /* screen size                                      */
}
NJS_SCREEN;

typedef struct
{
    Float       f_clip;         /* far clip                                         */
    Float       n_clip;         /* near clip                                        */
    Float       x1, x0, y1, y0; /* screen clip                                      */
    NJS_POINT2  d[2];           /* 2d clip                                          */
}
NJS_CLIP;

#ifdef SAMT_INCL_INTERNAL

/****** Ninja Context ***************************************************************/
typedef struct
{
    Uint32          drawmode;   /* drawing flags                                    */
    Uint32          cullmode;   /* culling flags                                    */
    NJS_TEXSURFACE* texsurface; /* current texture surface                          */
    Uint32          texmode;    /* texture flags                                    */ 
    Uint32          colormode;  /* color mode flags                                 */
    Uint32          gbix;       /* current global texture index                     */
    Uint32          bank;       /* palette bank                                     */
    Uint32          modmode;    /* modifier flags                                   */
    NJS_TEXLIST*    texlist;    /* current texlist                                  */
    int unk;
    Uint32          texnum;     /* current texture number                           */
}
NJS_CTX;

#endif/*SAMT_INCL_INTERNAL*/

/************************/
/*  Data                */
/************************/
/****** Current Screen **************************************************************/
#define _nj_screen_                         DATA_REF(NJS_SCREEN, 0x02670300)
#define _nj_clip_                           DATA_REF(NJS_CLIP  , 0x02670560)

/****** Control 3D ******************************************************************/
#define _nj_control_3d_flag_                DATA_REF(Uint32    , 0x025F02D8)

/****** Constant Attribute **********************************************************/
#define _nj_constant_attr_and_              DATA_REF(Uint32    , 0x025F0268)
#define _nj_constant_attr_or_               DATA_REF(Uint32    , 0x025F02D4)

/****** Constant Material ***********************************************************/
#define _nj_constant_material_              DATA_REF(NJS_ARGB  , 0x025EFFD0)

#ifdef SAMT_INCL_INTERNAL

/****** Current Context *************************************************************/
#define _nj_curr_ctx_                       DATA_REF(NJS_CTX*  , 0x02670544)

/****** Context List ****************************************************************/
#define _nj_context_                        DATA_ARY(NJS_CTX   , 0x025F0000, [6])

#endif/*SAMT_INCL_INTERNAL*/

/************************/
/*  Prototypes          */
/************************/
/************************************************************************************/
/*
*   System
*/

/****** Get/Set System Attribute ****************************************************/
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

/****** Back Color ******************************************************************/
/*
*   Description:
*     Set the back color
*
*   Notes:
*     - Requires 'SA2 Render Fix' mod to take full effect.
*
*   Parameters:
*     - color1      : upper left color                               [0xAA'RR'GG'BB]
*     - color2      : upper right color                              [0xAA'RR'GG'BB]
*     - color3      : bottom color                                   [0xAA'RR'GG'BB]
*/
void    njSetBackColor( Uint32 color1, Uint32 color2, Uint32 color3 );

/****** Draw Mode *******************************************************************/
/*
*   Descrption:
*     Set the specular behavior of draw functions.
*
*   Notes:
*     - Behavior not implemented, no effect
*     - Has no effect on model draw.
*
*   Parameters:
*     - mode        : specular mode                                         [ON/OFF]
*/
void	njSpecularMode( Int mode );

/****** Culling *********************************************************************/
/*
*   Description:
*     Set the polygon culling mode of draw functions.
*
*   Notes:
*     - Behavior not implemented, no effect
*     - Has no effect on model draw.
*
*   Parameters:
*     - mode        : polygon culling mode to set                  [NJD_POLYGON_###]
*/
void    njPolygonCullingMode( Int mode );

/****** Color Blending **************************************************************/
/*
*   Description:
*     Set the color blending behavior of draw functions.
*
*   Notes:
*     - Has no effect on model draw                        [set by model parameters]
*
*   Parameters:
*     - target      : color target (src/dst)                         [NJD_###_COLOR]
*     - mode        : blending mode                         [NJD_COLOR_BLENDING_###]
*/
void    njColorBlendingMode( Int target, Int mode );

/****** Texture *********************************************************************/
/*
*   Description:
*     Set the texture filter behavior of draw functions.
*
*   Notes:
*     - Requires 'SA2 Render Fix' to take effect
*     - Has no effect on model draw                        [set by model parameters]
*
*   Parameters:
*     - mode        : texture filter mode                    [NJD_TEXTUREFILTER_###]
*/
void    njTextureFilterMode( Int mode );
/*
*   Description:
*     Set the texture clamping behavior of draw functions. Texture clamping occurs
*   when the UV coordinate exceeds the 0~1 range, any value outside of that range
*   will be clamped to 0 or 1; this will cause the texture to 'streak'. 
*
*   Notes:
*     - Has no effect on model draw                        [set by model parameters]
*
*   Parameters:
*     - mode        : texture clamping mode                   [NJD_TEXTURECLAMP_###]
*/
void    njTextureClampMode( Int mode );
/*
*   Description:
*     Set the texture flip behavior of draw functions. Texture flipping occurs when
*   the UV coordinates exceed a 0~1 range: for example, a V coordinate of '1.2' will
*   flip that part of the texture vertically; A V of '2.2' will flip it again,
*   matching the intial 0~1 range.
*
*   Notes:
*     - Has no effect if texture clamping is enabled
*     - Has no effect on model draw                        [set by model parameters]
*
*   Parameters:
*     - mode        : texture flip mode                        [NJD_TEXTUREFLIP_###]
*/
void    njTextureFlipMode( Int mode );
/*
*   Description:
*     Set the texture shading mode of draw functions.
*
*   Notes:
*     - Behavior not implemented, no effect
*     - Has no effect on model draw                        [set by model parameters]
*
*   Parameters:
*     - mode        : texture flip mode                   [NJD_TEX_SHADING_MODE_###]
*/
void    njTextureShadingMode( Int mode );

/****** Z Buffer ********************************************************************/
/*
*   Description:
*     Set Z buffering behavior.
*
*   Notes:
*     - Behavior not implemented, no effect
*
*   Parameters:
*     - mode        : z buffer mode                                         [ON/OFF]
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
*     - mode        : z write mode                                          [ON/OFF]
*/
void    njZWriteMode( Int mode );

/****** Modifier Mode ***************************************************************/
/*
*   Description:
*     Set modifier inside/outside behavior.
*
*   Notes:
*     - Behavior not implemented, no effect
*
*   Parameters:
*     - mode        : modifier mode                               [NJD_MODIFIER_###]
*/
void    njModifierMode( Int mode );

/************************************************************************************/
/*
*   Screen
*/

/****** Set Screen ******************************************************************/
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

/****** Set Clip ********************************************************************/
/*
*   Description:
*     Set clipping range (viewport). Clipping is peformed on a pixel-by-pixel basis.
*   Models, when projected onto the screen + their radius, that are outside of this
*   area will be skipped and not drawn.
*
*   Notes:
*     - Clipping area is adjusted for non-4:3 display aspect ratios.
*
*   Parameters:
*     - v           : clipping range defined by top left & bottom right corners in
*                     hardware screenspace.                       (0/0~640/480, etc)
*/
void    njClip2D( const NJS_POINT2 v[2] );
/*
*   Description:
*     Set the near and far clipping limits. Lower values represent further
*   distances, with '-65535.f' representing the back of the screen and '1.f' the
*   front of the screen.
*
*   Notes:
*     - Values outside of the expected range will be clamped to the nearest
*       expected value.
*
*   Parameters:
*     - n           : near clipping plane                           (-65535.f~-1.f)
*     - f           : far clipping plane                            (-65535.f~-1.f)
*/
void    njClipZ( Float n, Float f );

EXTERN_END

#endif/*H_NJ_SYSTEM*/
