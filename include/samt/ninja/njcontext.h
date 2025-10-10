/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/ninja/njcontext.h'
*
*   Description:
*     Ninja context header, not included as part of 'ninja.h'.
*/
#ifndef H_NJ_CONTEXT
#define H_NJ_CONTEXT

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */
#include <samt/ninja/njsystem.h>    /* ninja system                                             */

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** Ninja ***********************************************************************************/
typedef struct njtexsurface         NJS_TEXSURFACE; /* texture surface                          */

/********************************/
/*  Constants                   */
/********************************/
/************************************************************************************************/
/*
*   Global Param
*/
/****** Specular ********************************************************************************/
#define NJD_SPECULAR_ON                         (0x00000004) /* specular draw enabled           */

/************************************************************************************************/
/*
*   ISP Param
*/
/****** Polygon Culling *************************************************************************/
//      NJD_POLYGON_NOCULLING                   (0x00000000) /* no culling                      */
//      NJD_POLYGON_CULLINGSMALL                (0x08000000) /* cull small polygons             */
//      NJD_POLYGON_CULLINGACW                  (0x10000000) /* cull anti-clockwise polygons    */
//      NJD_POLYGON_CULLINGCW                   (0x18000000) /* cull clockwise polygons         */

/****** Z Buffer ********************************************************************************/
#define NJD_ZBUFFER_ON                          (0xC0000000) /* z buffer enabled                */
#define NJD_ZBUFFER_OFF                         (0xE0000000) /* z buffer disabled               */

/****** Z Write *********************************************************************************/
#define NJD_ZWRITE_OFF                          (0x04000000) /* z write disabled                */

/************************************************************************************************/
/*
*   TSP Param
*/
/****** Texture Shading Mode ********************************************************************/
//      NJD_TEX_SHADING_MODE_DECAL              (0x00000000) /* decal                           */
//      NJD_TEX_SHADING_MODE_MODULATE           (0x00000040) /* modulate                        */
//      NJD_TEX_SHADING_MODE_DECALALPHA         (0x00000080) /* decal alpha                     */
//      NJD_TEX_SHADING_MODE_MODULATEALPHA      (0x000000C0) /* modulate alpha                  */

/****** Mipmap Adjust ***************************************************************************/
#define NJD_MIPMAPADJUST_SHIFT                  (8)           /* mipmap adjust level shift      */
#define NJD_MIPMAPADJUST_MASK                   (~0x00000F00) /* mipmap adjust level mask       */

/****** Super Sampling **************************************************************************/
#define NJD_SUPERSAMPLE_ON                      (0x00001000) /* super sample enabled            */

/****** Texture Filtering ***********************************************************************/
//      NJD_TEXTUREFILTER_POINT_SAMPLE          (0x00000000) /* point filtering (no filter)     */
//      NJD_TEXTUREFILTER_BILINEAR              (0x00002000) /* bilinear filtering              */
//      NJD_TEXTUREFILTER_TRILINEAR_A           (0x00004000) /* trilinear filtering A (+Z)      */
//      NJD_TEXTUREFILTER_TRILINEAR_B           (0x00006000) /* trilinear filtering B (+1-Z)    */

/****** Texture Clamping ************************************************************************/
//      NJD_TEXTURECLAMP_NOCLAMP                (0x00000000) /* no texture clamp                */
//      NJD_TEXTURECLAMP_CLAMP_V                (0x00008000) /* texture clamp V                 */
//      NJD_TEXTURECLAMP_CLAMP_U                (0x00010000) /* texture clamp U                 */
//      NJD_TEXTURECLAMP_CLAMP_UV               (0x00018000) /* texture clamp both              */

/****** Texture Flipping ************************************************************************/
//      NJD_TEXTUREFLIP_NOFLIP                  (0x00000000) /* no texture flip                 */
//      NJD_TEXTUREFLIP_FLIP_V                  (0x00020000) /* texture flip V                  */
//      NJD_TEXTUREFLIP_FLIP_U                  (0x00040000) /* texture flip U                  */
//      NJD_TEXTUREFLIP_FLIP_UV                 (0x00060000) /* texture flip both               */

/****** Ignore Texture Alpha ********************************************************************/
#define NJD_IGNORETEXALPHA_ON                   (0x00080000) /* ignore tex alpha on flag        */

/****** Color Clamp *****************************************************************************/
#define NJD_COLORCLAMP_ON                       (0x00200000) /* color clamp on flag             */

/****** Color Blending Modes ********************************************************************/
#define NJD_COLORBLEND_ZERO                     (0) /* tgt * { 0   , 0   , 0   , 0    }         */
#define NJD_COLORBLEND_ONE                      (1) /* tgt * { 1   , 1   , 1   , 1    }         */
#define NJD_COLORBLEND_SRCCOLOR                 (2) /* tgt * { As  , Rs  , Gs  , Bs   }         */
#define NJD_COLORBLEND_INVSRCCOLOR              (3) /* tgt * { 1-As, 1-Rs, 1-Gs, 1-Bs }         */
#define NJD_COLORBLEND_SRCALPHA                 (4) /* tgt * { As  , As  , As  , As   }         */
#define NJD_COLORBLEND_INVSRCALPHA              (5) /* tgt * { 1-As, 1-As, 1-As, 1-As }         */
#define NJD_COLORBLEND_DSTALPHA                 (6) /* tgt * { Ad  , Ad  , Ad  , Ad   }         */
#define NJD_COLORBLEND_INVDSTALPHA              (7) /* tgt * { 1-Ad, 1-Ad, 1-Ad, 1-Ad }         */

#define NJD_COLORBLEND_SHIFT_SRC                (29) /* source blend shift                      */
#define NJD_COLORBLEND_SHIFT_DST                (26) /* destination blend shift                 */

#define NJD_COLORBLEND_MASK_SRC                 (~0xE0000000) /* source mask                    */
#define NJD_COLORBLEND_MASK_DST                 (~0x1C000000) /* destination mask               */

#define NJD_COLORBLEND_MASK_BOTH                (NJD_COLORBLEND_MASK_SRC|NJD_COLORBLEND_MASK_DST)

/************************************************************************************************/
/*
*   Modifier Param
*/
/****** Modifier Mode ***************************************************************************/
//      NJD_MODIFIER_INSIDE                     (0x20000000) /* shade inside polygons           */
//      NJD_MODIFIER_OUTSIDE                    (0x40000000) /* shade outside polygons          */

/********************************/
/*  Structures                  */
/********************************/
/****** Ninja Context ***************************************************************************/
typedef struct njctx
{
    Uint32          globalparam;    /* global parameters                                        */
    Uint32          ispparam;       /* raster parameters                                        */
    NJS_TEXSURFACE* texture;        /* texture surface                                          */
    Uint32          tspparam;       /* texture/shading parameters                               */ 
    Uint32          colormode;      /* color mode parameters                                    */
    Uint32          gbix;           /* current global texture index                             */
    Uint32          bank;           /* palette bank                                             */
    Uint32          modparam;       /* modifier flags                                           */
    NJS_TEXLIST*    texlist;        /* current texlist                                          */
    Uint32          pad32;
    Uint32          texnum;         /* current texture number                                   */
}
NJS_CONTEXT;

/********************************/
/*  Data                        */
/********************************/
/****** Current Context *************************************************************************/
#define _nj_curr_ctx_                       DATA_REF(NJS_CONTEXT*, 0x02670544)

/****** Context List ****************************************************************************/
#define _nj_context_                        DATA_ARY(NJS_CONTEXT , 0x025F0000, [NJD_CONTEXT_MAX])

EXTERN_END

#endif/*H_NJ_CONTEXT*/
