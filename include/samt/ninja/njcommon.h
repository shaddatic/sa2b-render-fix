/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/ninja/njcommon.h'
*
*   Description:
*     Ninja common definitions.
*/
#ifndef H_NJ_COMMON
#define H_NJ_COMMON

/********************************/
/*  Includes                    */
/********************************/
/****** System **********************************************************************************/
#include <samt/shinobi/sg_xpt.h>    /* shinobi types                                            */

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** Texture *********************************************************************************/
typedef struct njtexname            NJS_TEXNAME;
typedef struct njtexlist            NJS_TEXLIST;

/****** Motion **********************************************************************************/
typedef struct njmot                NJS_MOTION;
typedef struct njmotlink            NJS_MOTION_LINK;

/****** Camera **********************************************************************************/
typedef struct njcamera             NJS_CAMERA;

/****** Action **********************************************************************************/
typedef struct njact                NJS_ACTION;
typedef struct njactlink            NJS_ACTION_LINK;

/****** Direct Draw *****************************************************************************/
typedef struct njdirhead            NJS_DIRECT_HEAD;

/****** Basic Model *****************************************************************************/
typedef struct njmdl                NJS_MODEL;
typedef struct njobj                NJS_OBJECT;

/****** Chunk Model *****************************************************************************/
typedef struct cnkmdl               NJS_CNK_MODEL;
typedef struct cnkobj               NJS_CNK_OBJECT;

/****** Ginja Model *****************************************************************************/
typedef struct gjmdl                GJS_MODEL;
typedef struct gjobj                GJS_OBJECT;

/********************************/
/*  Constants                   */
/********************************/
/****** Bits ************************************************************************************/
#define BIT_0                       (0x00000001) /* bit 1                                       */
#define BIT_1                       (0x00000002) /* bit 2                                       */
#define BIT_2                       (0x00000004) /* bit 3                                       */
#define BIT_3                       (0x00000008) /* bit 4                                       */
#define BIT_4                       (0x00000010) /* bit 5                                       */
#define BIT_5                       (0x00000020) /* bit 6                                       */
#define BIT_6                       (0x00000040) /* bit 7                                       */
#define BIT_7                       (0x00000080) /* bit 8                                       */
#define BIT_8                       (0x00000100) /* bit 9                                       */
#define BIT_9                       (0x00000200) /* bit 10                                      */
#define BIT_10                      (0x00000400) /* bit 11                                      */
#define BIT_11                      (0x00000800) /* bit 12                                      */
#define BIT_12                      (0x00001000) /* bit 13                                      */
#define BIT_13                      (0x00002000) /* bit 14                                      */
#define BIT_14                      (0x00004000) /* bit 15                                      */
#define BIT_15                      (0x00008000) /* bit 16                                      */
#define BIT_16                      (0x00010000) /* bit 17                                      */
#define BIT_17                      (0x00020000) /* bit 18                                      */
#define BIT_18                      (0x00040000) /* bit 19                                      */
#define BIT_19                      (0x00080000) /* bit 20                                      */
#define BIT_20                      (0x00100000) /* bit 21                                      */
#define BIT_21                      (0x00200000) /* bit 22                                      */
#define BIT_22                      (0x00400000) /* bit 23                                      */
#define BIT_23                      (0x00800000) /* bit 24                                      */
#define BIT_24                      (0x01000000) /* bit 25                                      */
#define BIT_25                      (0x02000000) /* bit 26                                      */
#define BIT_26                      (0x04000000) /* bit 27                                      */
#define BIT_27                      (0x08000000) /* bit 28                                      */
#define BIT_28                      (0x10000000) /* bit 29                                      */
#define BIT_29                      (0x20000000) /* bit 30                                      */
#define BIT_30                      (0x40000000) /* bit 31                                      */
#define BIT_31                      (0x80000000) /* bit 31                                      */

/****** π ***************************************************************************************/
#define NJD_PI                      (3.141592f) /* pi                                           */

/****** Ninja Control 3D ************************************************************************/
#define NJD_CONTROL_3D_DISP_AXIS                    BIT_0  /* display axist                     */
#define NJD_CONTROL_3D_NO_CLIP_CHECK                BIT_1  /* ???                               */
#define NJD_CONTROL_3D_CONSTANT_ATTR                BIT_2  /* use constant attribute, basic     */
#define NJD_CONTROL_3D_ENABLE_ALPHA                 BIT_3  /* ???                               */
#define NJD_CONTROL_3D_CONSTANT_MATERIAL            BIT_4  /* use constant material color       */
#define NJD_CONTROL_3D_OFFSET_MATERIAL              BIT_5  /* constant material color offset    */
#define NJD_CONTROL_3D_DEPTH_QUEUE                  BIT_6  /* vary vertex alpha by depth        */
#define NJD_CONTROL_3D_VERTEX_OFFSET                BIT_7  /* ???                               */
#define NJD_CONTROL_3D_MODEL_CLIP                   BIT_8  /* use clipping calcs with model     */
#define NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL    BIT_9  /* force white material with texture */
#define NJD_CONTROL_3D_SHADOW                       BIT_10 /* use cheap shadow                  */
#define NJD_CONTROL_3D_CNK_CONSTANT_ATTR            BIT_11 /* use constant attribute, chunk     */
#define NJD_CONTROL_3D_SHADOW_OPAQUE                BIT_12 /* use cheap shadow, opaque only     */
#define NJD_CONTROL_3D_TRANS_MODIFIER               BIT_13 /* use transparent modifier          */
#define NJD_CONTROL_3D_USE_PUNCHTHROUGH             BIT_14 /* use punchthrough                  */
#define NJD_CONTROL_3D_CNK_BLEND_MODE               BIT_15 /* use global blend mode for chunk   */
#define NJD_CONTROL_3D_DISABLE_NEAR_CLIP            BIT_16 /* disable near clip plane           */
#define NJD_CONTROL_3D_ENV_UV_SCROLL                BIT_17 /* environment uv scrolling          */
#define NJD_CONTROL_3D_DISABLE_OPAQUE_MODIFIER      BIT_18 /* disable opaque modifier           */
#define NJD_CONTROL_3D_MIRROR_MODEL                 BIT_31 /* model drawn with inverted scaling */

/****** Draw Attribute **************************************************************************/
#define NJD_DRAW_MASK               (0x0000000f) /* mask for triangle type                      */

#define NJD_DRAW_NORMAL             (0x00000000) /* draw triangle list                          */
#define NJD_DRAW_FAN                (0x00000001) /* draw triangle fan                           */
#define NJD_DRAW_CONNECTED          (0x00000002) /* draw triangle strip                         */
#define NJD_DRAW_INSCRIBED          (0x00000010) /* draw inscribed circle                       */
#define NJD_FILL                    (0x00000020) /* fill polygon, else wireframe                */
#define NJD_TRANSPARENT             (0x00000040) /* use alpha                                   */
#define NJD_CALC_LIGHT              (0x40000000) /* use light calculation                       */
#define NJD_USE_TEXTURE             (0x80000000) /* use texture                                 */

/****** Ninja Sprite ****************************************************************************/
#define NJD_SPRITE_ANGLE            BIT_0 /* rotate sprite around center by 'angle' param       */
#define NJD_SPRITE_COLOR            BIT_1 /* use constant material color, else white            */
#define NJD_SPRITE_HFLIP            BIT_2 /* horizontal texture flip                            */
#define NJD_SPRITE_VFLIP            BIT_3 /* vertical texture flip                              */
#define NJD_SPRITE_HVFLIP           (NJD_SPRITE_HFLIP|NJD_SPRITE_VFLIP)
#define NJD_SPRITE_SCALE            BIT_4 /* draw 3d sprite facing screen, eg. scale only       */
#define NJD_SPRITE_ALPHA            BIT_5 /* use alpha                                          */

/********************************/
/*  Basic Types                 */
/********************************/
/****** Bits ************************************************************************************/
typedef Sint32                      NJS_ANGLE , Angle;
typedef Sint16                      NJS_SANGLE, Sangle;

/********************************/
/*  Structures                  */
/********************************/
/****** Angle ***********************************************************************************/
typedef struct njang3
{
    NJS_ANGLE   x, y, z;            /* position/vector components                               */
}
NJS_ANGLE3, Angle3;

/****** UV Coords *******************************************************************************/
typedef struct njtex
{
    Sint16      u, v;               /* uv components                                            */
}
NJS_TEX;

/****** Int Color *******************************************************************************/
typedef struct njbgra
{
    Uint8       b, g, r, a;         /* color components                                         */
}
NJS_BGRA;

/****** Color Union *****************************************************************************/
typedef union njcolor
{
    Uint32      color;              /* raw integer value                                        */
    NJS_TEX     tex;                /* uv coordinates                                           */
    NJS_BGRA    argb;               /* color components                                         */
}
NJS_COLOR;

/****** Float Color *****************************************************************************/
typedef struct njargb
{
    Float       a, r, g, b;         /* color components                                         */
}
NJS_ARGB;

/****** Point 2D ********************************************************************************/
typedef struct njpt2
{
    Float       x, y;               /* position/vector components                               */
}
NJS_POINT2;

typedef struct njpt2i
{
    Sint16      x, y;               /* position/vector components                               */
}
NJS_POINT2I;

typedef struct njpt2c
{
    NJS_POINT2* p;                  /* position                                                 */
    NJS_COLOR*  col;                /* color                                                    */
    NJS_COLOR*  tex;                /* uv coordinate                                            */
    Uint32      num;                /* texture number                                           */
}
NJS_POINT2COL;

/****** Point 3D ********************************************************************************/
typedef struct njpt3
{
    Float       x, y, z;            /* position/vector components                               */
}
NJS_POINT3, NJS_VECTOR;

typedef struct njpt3c
{
    NJS_POINT3* p;                  /* position                                                 */
    NJS_COLOR*  col;                /* color                                                    */
    NJS_COLOR*  tex;                /* uv coordinate                                            */
    Uint32      num;                /* texture number                                           */
}
NJS_POINT3COL;

/****** Line ************************************************************************************/
typedef struct njline
{
    Float       px, py, pz;         /* position                                                 */
    Float       vx, vy, vz;         /* direction                                                */
}
NJS_LINE, NJS_PLANE, NJS_PVECTOR;

/****** Quaternion ******************************************************************************/
typedef struct njquat
{
    Float       re;                 /* real (or scalor) part of quaternion                      */
    Float       im[3];              /* imaginary (or vector) part of quaternion                 */
}
NJS_QUATERNION;

/****** Non-Tex Vertex **************************************************************************/
typedef struct njpolyvtx
{
    Float       x, y, z;            /* vertex position                                          */
    Uint32      col;                /* vertex color                                             */
}
NJS_POLYGON_VTX;

/****** Texture Vertex **************************************************************************/
typedef struct njtexvtx
{
    Float       x, y, z;            /* vertex position                                          */
    Float       u, v;               /* uv coordnates                                            */
    Uint32      col;                /* vertex color                                             */
}
NJS_TEXTURE_VTX;

/****** Texture & Offset Vertex *****************************************************************/
typedef struct njtexhvtx
{
    Float       x, y, z;            /* vertex position                                          */
    Float       u, v;               /* uv coordnates                                            */
    Uint32      bcol;               /* vertex color                                             */
    Uint32      ocol;               /* vertex offset color (specular/highlight)                 */
}
NJS_TEXTUREH_VTX;

/********************************/
/*  Macros                      */
/********************************/
/************************************************************************************************/
/*
*   Basic Macro
*/
/****** Min/Max *********************************************************************************/
#define NJM_MAX(a,b)                ((a)>(b)?(a):(b))
#define NJM_MIN(a,b)                ((a)<(b)?(a):(b))

/************************************************************************************************/
/*
*   Convert Angle
*
*   DEG = Degrees           (360°            )
*   RAD = Radians           (6.283185|2π rad )
*   ANG = Ninja (S)Angle    (65536   |0x10000)
*
*   NJM_SRC_DST(n)
*/
/****** Angle ***********************************************************************************/
#define NJM_DEG_RAD(n)              ((n)*(NJD_PI/180.f))
#define NJM_DEG_ANG(n)              ((Angle)((n)*(65536.f/360.f)))
#define NJM_RAD_ANG(n)              ((Angle)((n)*(65536.f/(2.f*NJD_PI))))
#define NJM_RAD_DEG(n)              ((n)*(180.f/NJD_PI))
#define NJM_ANG_DEG(n)              ((n)*(360.f/65536.f))
#define NJM_ANG_RAD(n)              ((n)*((2.f*NJD_PI)/65536.f))

/****** Sangle **********************************************************************************/
#define NJM_DEG_SANG(n)             ((Sangle)((n)*(65536.f/360.f)))
#define NJM_RAD_SANG(n)             ((Sangle)((n)*(65536.f/(2.f*NJD_PI))))
#define NJM_SANG_DEG(n)             ((n)*(360.f/65536.f))
#define NJM_SANG_RAD(n)             ((n)*((2.f*NJD_PI)/65536.f))

EXTERN_END

#endif/*H_NJ_COMMON*/
