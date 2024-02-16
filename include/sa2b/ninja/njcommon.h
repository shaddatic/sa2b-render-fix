/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njcommon.h'
*
*   Contains structs, flags, and typedefs common to Ninja
*
*   Contributors:
*   -   SEGA,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _NJCOMMON_H_
#define _NJCOMMON_H_

#include <sa2b/shinobi/sg_xpt.h>

/*--------------------------------------*/
/*      BIT                             */
/*--------------------------------------*/
#define BIT_0   (0x00000001)
#define BIT_1   (0x00000002)
#define BIT_2   (0x00000004)
#define BIT_3   (0x00000008)
#define BIT_4   (0x00000010)
#define BIT_5   (0x00000020)
#define BIT_6   (0x00000040)
#define BIT_7   (0x00000080)
#define BIT_8   (0x00000100)
#define BIT_9   (0x00000200)
#define BIT_10  (0x00000400)
#define BIT_11  (0x00000800)
#define BIT_12  (0x00001000)
#define BIT_13  (0x00002000)
#define BIT_14  (0x00004000)
#define BIT_15  (0x00008000)
#define BIT_16  (0x00010000)
#define BIT_17  (0x00020000)
#define BIT_18  (0x00040000)
#define BIT_19  (0x00080000)
#define BIT_20  (0x00100000)
#define BIT_21  (0x00200000)
#define BIT_22  (0x00400000)
#define BIT_23  (0x00800000)
#define BIT_24  (0x01000000)
#define BIT_25  (0x02000000)
#define BIT_26  (0x04000000)
#define BIT_27  (0x08000000)
#define BIT_28  (0x10000000)
#define BIT_29  (0x20000000)
#define BIT_30  (0x40000000)
#define BIT_31  (0x80000000)

/*--------------------------------------*/
/*      Basic Define                    */
/*--------------------------------------*/
typedef Sint32  Angle;
typedef Sint16  Sangle;
typedef Float   GJS_MATRIX[12];
typedef Sint8   NJS_SYS_ATTR[64];
typedef void  (*NJS_INT_FUNC)(void);

typedef GJS_MATRIX NJS_MATRIX;

typedef struct
{
    Angle x, y, z;
}
Angle3;

/*--------------------------------------*/
/*      Attribute define                */
/*--------------------------------------*/
#define NJD_DRAW_MASK           0x0000000f  /* Mask for Drawing Attribute   */

#define NJD_DRAW_NORMAL         0x00000000  /* Draw Normally                */
#define NJD_DRAW_FAN            0x00000001  /* Draw Radially                */
#define NJD_DRAW_CONNECTED      0x00000002  /* Draw Continuously            */
#define NJD_DRAW_INSCRIBED      0x00000010  /* Draw Inscribed Circle        */
#define NJD_FILL                0x00000020  /* Fill Polygon                 */
#define NJD_TRANSPARENT         0x00000040  /* Be Transparent               */
#define NJD_CALC_LIGHT          0x40000000  /* Put under the Light Effect   */
#define NJD_USE_TEXTURE         0x80000000  /* Use Texture                  */

/*--------------------------------------*/
/*      Scroll define                   */
/*--------------------------------------*/
/* cell size */
#define NJD_CELL_8              8
#define NJD_CELL_16             16
#define NJD_CELL_32             32
#define NJD_CELL_64             64
#define NJD_CELL_128            128
#define NJD_CELL_256            256

/* the maximum of scroll's value */
#define NJD_CELL_NUM_MAX        0xFFFF  /* the maximum of cell's number */
#define NJD_MAP_W_MAX           0xFF    /* the maximum of map's width   */
#define NJD_MAP_H_MAX           0xFF    /* the muximum of map's height  */
#define NJD_MAP_MAX             (NJD_MAP_W_MAX*NJD_MAP_H_MAX)
                                        /* the muximum of map           */

/* 3d control */
#define NJD_CONTROL_3D_DISP_AXIS                    BIT_0
#define NJD_CONTROL_3D_NO_CLIP_CHECK                BIT_1
#define NJD_CONTROL_3D_CONSTANT_ATTR                BIT_2
#define NJD_CONTROL_3D_ENABLE_ALPHA                 BIT_3
#define NJD_CONTROL_3D_CONSTANT_MATERIAL            BIT_4
#define NJD_CONTROL_3D_OFFSET_MATERIAL              BIT_5
#define NJD_CONTROL_3D_DEPTH_QUEUE                  BIT_6
#define NJD_CONTROL_3D_VERTEX_OFFSET                BIT_7
#define NJD_CONTROL_3D_MODEL_CLIP                   BIT_8
#define NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL    BIT_9
#define NJD_CONTROL_3D_SHADOW                       BIT_10
#define NJD_CONTROL_3D_CNK_CONSTANT_ATTR            BIT_11
#define NJD_CONTROL_3D_SHADOW_OPAQUE                BIT_12
#define NJD_CONTROL_3D_TRANS_MODIFIER               BIT_13
#define NJD_CONTROL_3D_USE_PUNCHTHROUGH             BIT_14
#define NJD_CONTROL_3D_CNK_BLEND_MODE               BIT_15
#define NJD_CONTROL_3D_DISABLE_NEAR_CLIP            BIT_16
#define NJD_CONTROL_3D_ENV_UV_SCROLL                BIT_17
#define NJD_CONTROL_3D_DISABLE_OPAQUE_MODIFIER      BIT_18
#define NJD_CONTROL_3D_MIRROR_MODEL                 BIT_31

/* sprite */
#define NJD_SPRITE_ANGLE            BIT_0
#define NJD_SPRITE_COLOR            BIT_1
#define NJD_SPRITE_HFLIP            BIT_2
#define NJD_SPRITE_VFLIP            BIT_3
#define NJD_SPRITE_HVFLIP           ( NJD_SPRITE_HFLIP | NJD_SPRITE_VFLIP )
#define NJD_SPRITE_SCALE            BIT_4
#define NJD_SPRITE_ALPHA            BIT_5

/*--------------------------------------*/
/*      MACRO                           */
/*--------------------------------------*/
#define NJD_PI  3.141592f

#define NJM_DEG_RAD(n)  ((n) * (NJD_PI / 180.f))                    /*  deg → rad  */
#define NJM_DEG_ANG(n)  ((Angle)((n) * (65536.f / 360.f)))          /*  deg → ang  */
#define NJM_RAD_ANG(n)  ((Angle)((n) * (65536.f / (2.f * NJD_PI)))) /*  rad → ang  */
#define NJM_RAD_DEG(n)  ((n) * (180.f / NJD_PI))                    /*  rad → deg  */
#define NJM_ANG_DEG(n)  ((n) * (360.f / 65536.f))                   /*  ang → deg  */
#define NJM_ANG_RAD(n)  ((n) * ((2.f * NJD_PI) / 65536.f))          /*  ang → rad  */

#define NJM_DEG_SANG(n)  ((Sangle)((n) * (65536.f / 360.f)))            /*  deg → ang  */
#define NJM_RAD_SANG(n)  ((Sangle)((n) * (65536.f / (2.f * NJD_PI))))   /*  rad → ang  */
#define NJM_SANG_DEG(n)  ((n) * (360.f / 65536.f))                      /*  ang → deg  */
#define NJM_SANG_RAD(n)  ((n) * ((2.f * NJD_PI) / 65536.f))             /*  ang → rad  */

#define NJM_MAX(a,b) ((a)>(b)?(a):(b))
#define NJM_MIN(a,b) ((a)<(b)?(a):(b))

/*--------------------------------------*/
/*      Structer                        */
/*--------------------------------------*/
typedef struct {
    Sint16  u;
    Sint16  v;
} NJS_TEX;

typedef struct {
    Uint8   b;
    Uint8   g;
    Uint8   r;
    Uint8   a;
} NJS_BGRA;

typedef union {
    Uint32  color;
    NJS_TEX tex;
    NJS_BGRA argb;
} NJS_COLOR;

typedef struct {
    Float   a;
    Float   r;
    Float   g;
    Float   b;
} NJS_ARGB;

typedef struct {
    Sint16  x;
    Sint16  y;
} NJS_POINT2I;

typedef struct {
    Float  x;
    Float  y;
} NJS_POINT2;

typedef struct {
    Float   x;
    Float   y;
    Float   z;
} NJS_POINT3, NJS_VECTOR;

typedef struct {
    NJS_POINT2* p;
    NJS_COLOR* col;
    NJS_COLOR* tex;
    Uint32      num;
} NJS_POINT2COL;

typedef struct {
    NJS_POINT3* p;
    NJS_COLOR* col;
    NJS_COLOR* tex;
    Uint32      num;
} NJS_POINT3COL;

typedef struct {
    Float   px, py, pz;
    Float   vx, vy, vz;
} NJS_LINE, NJS_PLANE, NJS_PVECTOR;

typedef struct {
    float    re;                /* real (or scalor) part of quaternion        */
    float    im[3];             /* imaginary (or vector) part of quaternion    */
} NJS_QUATERNION;

typedef struct {
    void            *filename;  /* texture filename strings     */
    Uint32               attr;  /* texture attribute            */
    Uint32            texaddr;  /* texture memory list address  */
} NJS_TEXNAME;

typedef struct {
    NJS_TEXNAME     *textures;  /* texture array                */
    Uint32          nbTexture;  /* texture count                */
} NJS_TEXLIST;

/*--------------------------------------*/
/*      Low Level                       */
/*--------------------------------------*/
typedef struct {
    Float    x;
    Float    y;
    Float    z;
    Uint32    col;
} NJS_POLYGON_VTX;

typedef struct {
    Float    x;
    Float    y;
    Float    z;
    Float    u;
    Float    v;
    Uint32    col;
} NJS_TEXTURE_VTX;

typedef struct {
    Float    x;
    Float    y;
    Float    z;
    Float    u;
    Float    v;
    Uint32    bcol;
    Uint32    ocol;
} NJS_TEXTUREH_VTX;

#endif
