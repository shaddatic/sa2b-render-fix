/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/ninja/gjmodel.h'
*
*   Description:
*     The GX Ninja model format.
*/
#ifndef H_GJ_MODEL
#define H_GJ_MODEL

/********************************/
/*  External Headers            */
/********************************/
/****** System **********************************************************************************/
#include <samt/shinobi/sg_xpt.h>    /* shinobi types                                            */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */
#include <samt/ninja/njmatrix.h>    /* ninja matrix                                             */

EXTERN_START

/********************************/
/*  Constants                   */
/********************************/
/****** Vlist Type ******************************************************************************/
#define GJD_VLIST_BASIC             (  0) /* vlist no weights entry, same as full weight        */
#define GJD_VLIST_START             (  1) /* vlist weight start entry                           */
#define GJD_VLIST_MIDDLE            (  2) /* vlist weight middle entry                          */
#define GJD_VLIST_END               (  3) /* vlist end, no data                                 */

/****** Strip Flags *****************************************************************************/
#define GJD_FST_DB               (0x8000) /* double sided                                       */

/********************************/
/*  Enums                       */
/********************************/
/****** Vertex Array ****************************************************************************/
typedef enum
{
    GJ_VA_PNMTXIDX,                 /* matrix data                                              */
    GJ_VA_POS,                      /* position                                                 */
    GJ_VA_NRM,                      /* normal                                                   */
    GJ_VA_CLR0,                     /* color 0                                                  */
    GJ_VA_CLR1,                     /* color 1                                                  */
    GJ_VA_TEX0,                     /* UV coords 0                                              */
    GJ_VA_TEX1,                     /* UV coords 1                                              */
    GJ_VA_TEX2,                     /* UV coords 2                                              */
    GJ_VA_TEX3,                     /* UV coords 3                                              */
    GJ_VA_TEX4,                     /* UV coords 4                                              */
    GJ_VA_TEX5,                     /* UV coords 5                                              */
    GJ_VA_TEX6,                     /* UV coords 6                                              */
    GJ_VA_TEX7,                     /* UV coords 7                                              */

    GJ_VA_NULL = 255,               /* null entry, list end                                     */
}
GJ_ATTR;

/****** Material ********************************************************************************/
typedef enum
{
    GJ_MT_VTXATTR,                  /* vertex attribute format                                  */
    GJ_MT_VCD,                      /* vertex declaration/description                           */
    GJ_MT_FST1,                     /* strip flags 1                                            */
    GJ_MT_FST2,                     /* strip flags 2 (unused)                                   */
    GJ_MT_BLEND,                    /* alpha blending                                           */
    GJ_MT_DIFFUSE,                  /* diffuse color                                            */
    GJ_MT_AMBIENT,                  /* ambient color                                            */
    GJ_MT_SPECULAR,                 /* specular color                                           */
    GJ_MT_TEXTURE,                  /* texture info (texid, wrap)                               */
    GJ_MT_TEVORDER,                 /* tev order & op                                           */
    GJ_MT_TEXGEN,                   /* texture coord generator                                  */

    GJ_MAX_MTTYPE,                  /* enum count                                               */
}
GJ_MTTYPE;

/****** Array Component *************************************************************************/
typedef enum
{
    GJ_POS_XY,                      /* position, xy                                             */
    GJ_POS_XYZ,                     /* position, xyz                                            */
    GJ_NRM_XYZ,                     /* normal, xyz                                              */
    GJ_NRM_NBT,                     /* normal, normal/binormal/tangent                          */
    GJ_NRM_NBT3,                    /* normal, normal/binormal/tangent (3?)                     */
    GJ_CLR_RGB,                     /* color, rgb                                               */
    GJ_CLR_RGBA,                    /* color, rgba                                              */
    GJ_TEX_S,                       /* uv, s (?)                                                */
    GJ_TEX_ST,                      /* uv, st (?)                                               */
}
GJ_COMP_CNT;

typedef enum
{
    GJ_U8,                          /* uint8                                                    */
    GJ_S8,                          /* sint8                                                    */
    GJ_U16,                         /* uint16                                                   */
    GJ_S16,                         /* sint16                                                   */
    GJ_F32,                         /* float                                                    */
    GJ_RGB565,                      /* rgb as 565                                               */
    GJ_RGB8,                        /* rgb as 888                                               */
    GJ_RGBX8,                       /* rgbx as 8888                                             */
    GJ_RGBA4,                       /* rgba as 4444                                             */
    GJ_RGBA6,                       /* rgba as 6666                                             */
    GJ_RGBA8,                       /* rgba as 8888                                             */
}
GJ_COMP_TYPE;

/********************************/
/*  Structures                  */
/********************************/
/****** Ginja Model *****************************************************************************/
typedef struct
{
    Uint8           id;             /* vertex attribute type                          [GJ_ATTR] */
    Uint8           stride;         /* vertex attribute size                                    */
    Uint16          count;          /* vertex attribute count                                   */
    /*
    *   Sint8  type : 4;            // component type                                           //
    *   Sint8  cnt  : 4;            // component kind                                           //
    *   Sint8  pad1;                // padding                                                  //
    *   Sint16 drawflags;           // set at runtime                                           //
    */
    Uint32          attrflags;      /* vertex attribute flags                         [GJ_COMP] */
    void*           base_ptr;       /* vertex component list                                    */
    Uint32          size;           /* total size of list, in bytes                             */
}
GJS_ARRAY;

typedef struct
{
    Uint16          type;           /* vlist type                                   [GJD_VLIST] */
    Uint16          size;           /* total size of vertex+weights, in s32's                   */
    Uint16          offset;         /* vlist start offset                                       */
    Uint16          num;            /* number of vertex/weight entries                          */
    /*
    *   Sint16 px,py,pz;            // vertex position as fractional integer, 256 == 1.f        //
    *   Sint16 nx,ny,nz;            // vertex normal as fractional integer    ^^^               //
    */  
    Sint16*         vertices;       /* vertex position+normal                                   */
    /*
    *   Uint16 weight;              // vertex weight as fractional integer, 256 == 1.f          //
    *   Uint16 vindex;              // vertex index for weight calculations                     //
    */
    Uint32*         weight;         /* vertex weights, only non-basic type                      */
}
GJS_VLIST;

typedef struct
{
    Uint8           id;             /* material type                                [GJ_MTTYPE] */
    Uint8           pad8;           /* padding                                                  */
    Uint16          pad16;          /* padding                                                  */
    Uint32          setting;        /* material setting                                         */
}
GJS_MATERIAL;

typedef struct
{
    GJS_MATERIAL*   mats;           /* material list                                            */
    Uint32          nbMat;          /* material count                                           */
    void*           pDisplayList;   /* mesh array                                               */
    Uint32         szDisplayList;   /* mesh count                                               */
}
GJS_MESHSET;

typedef struct gjmdl
{
    GJS_ARRAY*      arrays;         /* vertex comonent arrays                                   */
    GJS_VLIST*      vlist;          /* weighted vlist                                           */
    GJS_MESHSET*    opaque;         /* opaque mesh set                                          */
    GJS_MESHSET*    transparent;    /* transparent mesh set                                     */
    Uint16          nbOpaque;       /* opaque mesh set count                                    */
    Uint16          nbTrans;        /* transparent mesh set count                               */
    NJS_POINT3      center;         /* model center                                             */
    Float           r;              /* model radius                                             */
}
GJS_MODEL;

/****** Ginja Object ****************************************************************************/
typedef struct gjobj
{
    Uint32          evalflags;      /* evalation flags                                          */
    GJS_MODEL*      model;          /* model data pointer                                       */
    Float           pos[3];         /* translation                                              */
    Angle           ang[3];         /* rotation or im part of quat                              */
    Float           scl[3];         /* scaling                                                  */
    struct gjobj*   child;          /* child object                                             */
    struct gjobj*   sibling;        /* sibling object                                           */
    Float           re_quat;        /* re part of quat                                          */
}
GJS_OBJECT;

EXTERN_END

#endif/*H_GJ_MODEL*/
