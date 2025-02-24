/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/ninja/njbasic.h'
*
*   Description:
*     Constants and structures for the Ninja Basic model format.
*/
#ifndef H_NJ_BASIC
#define H_NJ_BASIC

/************************/
/*  External Headers    */
/************************/
/****** System **********************************************************************/
#include <samt/shinobi/sg_xpt.h> /* shinobi types                                   */

/****** Ninja ***********************************************************************/
#include <samt/ninja/njcommon.h> /* ninja common                                    */

EXTERN_START

/************************/
/*  Basic Constants     */
/************************/
/************************************************************************************/
/*
*   Alpha Blend Constants
*/
/****** Src Alpha Blend *************************************************************/
#define NJD_SA_ZERO             (0)                    /* zero                      */
#define NJD_SA_ONE              (BIT_29)               /* one                       */
#define NJD_SA_OTHER            (BIT_30)               /* other color               */
#define NJD_SA_INV_OTHER        (BIT_30|BIT_29)        /* inverse other color       */
#define NJD_SA_SRC              (BIT_31)               /* src alpha                 */
#define NJD_SA_INV_SRC          (BIT_31|BIT_29)        /* inverse src alpha         */
#define NJD_SA_DST              (BIT_31|BIT_30)        /* dst alpha                 */
#define NJD_SA_INV_DST          (BIT_31|BIT_30|BIT_29) /* inverse dst alpha         */
#define NJD_SA_MASK             (BIT_31|BIT_30|BIT_29) /* mask                      */

/****** Dst Alpha Blend *************************************************************/
#define NJD_DA_ZERO             (0)                    /* zero                      */
#define NJD_DA_ONE              (BIT_26)               /* one                       */
#define NJD_DA_OTHER            (BIT_27)               /* Other Color               */
#define NJD_DA_INV_OTHER        (BIT_27|BIT_26)        /* Inverse Other Color       */
#define NJD_DA_SRC              (BIT_28)               /* SRC Alpha                 */
#define NJD_DA_INV_SRC          (BIT_28|BIT_26)        /* Inverse SRC Alpha         */
#define NJD_DA_DST              (BIT_28|BIT_27)        /* DST Alpha                 */
#define NJD_DA_INV_DST          (BIT_28|BIT_27|BIT_26) /* Inverse DST Alpha         */
#define NJD_DA_MASK             (BIT_28|BIT_27|BIT_26) /* MASK                      */

/************************************************************************************/
/*
*   Texture Filter Constants
*/
/****** Texture Filter Mode *********************************************************/
#define NJD_FILTER_POINT        (0)             /* point sampling                   */
#define NJD_FILTER_BILINEAR     (BIT_13)        /* bilinear filter                  */
#define NJD_FILTER_TRILINEAR    (BIT_14)        /* trilinear filter                 */
#define NJD_FILTER_BLEND        (BIT_14|BIT_13) /* 'blend' filter                   */

#define NJD_FILTER_MASK         (BIT_14|BIT_13) /* filter mask                      */

/****** Mip-Map 'D' Adjust **********************************************************/
#define NJD_D_025               (BIT_8)						/* 0.25                 */
#define NJD_D_050               (BIT_9)						/* 0.50                 */
#define NJD_D_075               (BIT_9|BIT_8)				/* 0.75                 */
#define NJD_D_100               (BIT_10)					/* 1.00                 */
#define NJD_D_125               (BIT_10|BIT_8)				/* 1.25                 */
#define NJD_D_150               (BIT_10|BIT_9)				/* 1.50                 */
#define NJD_D_175               (BIT_10|BIT_9|BIT_8)		/* 1.75                 */
#define NJD_D_200               (BIT_11)					/* 2.00                 */
#define NJD_D_225               (BIT_11|BIT_8)				/* 2.25                 */
#define NJD_D_250               (BIT_11|BIT_9)				/* 2.50                 */
#define NJD_D_275               (BIT_11|BIT_9|BIT_8)		/* 2.75                 */
#define NJD_D_300               (BIT_11|BIT_10)		        /* 3.00                 */
#define NJD_D_325               (BIT_11|BIT_10|BIT_8)		/* 3.25                 */
#define NJD_D_350               (BIT_11|BIT_10|BIT_9)		/* 3.50                 */
#define NJD_D_375               (BIT_11|BIT_10|BIT_9|BIT_8)	/* 3.75                 */

#define NJD_D_MASK              (BIT_11|BIT_10|BIT_9|BIT_8)	/* 'd' adjust mask      */

/************************************************************************************/
/*
*   Material Constants
*/
/****** Material Flags **************************************************************/
#define NJD_FLAG_IGNORE_LIGHT       (BIT_25) /* ignore lighting                     */
#define NJD_FLAG_USE_FLAT           (BIT_24) /* flat shading                        */
#define NJD_FLAG_DOUBLE_SIDE        (BIT_23) /* double sided                        */
#define NJD_FLAG_USE_ENV            (BIT_22) /* environment                         */
#define NJD_FLAG_USE_TEXTURE        (BIT_21) /* use texture                         */
#define NJD_FLAG_USE_ALPHA          (BIT_20) /* use alpha                           */
#define NJD_FLAG_IGNORE_SPECULAR    (BIT_19) /* ignore specular                     */
#define NJD_FLAG_FLIP_U             (BIT_18) /* flip u                              */
#define NJD_FLAG_FLIP_V             (BIT_17) /* flip v                              */
#define NJD_FLAG_CLAMP_U            (BIT_16) /* clamp u                             */
#define NJD_FLAG_CLAMP_V            (BIT_15) /* clamp v                             */
#define NJD_FLAG_USE_ANISOTROPIC    (BIT_12) /* use anisotropic                     */
#define NJD_FLAG_PICK               (BIT_7)  /* pick                                */

#define NJD_FLAG_FLIP_MASK          (NJD_FLAG_FLIP_U |NJD_FLAG_FLIP_V)
#define NJD_FLAG_CLAMP_MASK         (NJD_FLAG_CLAMP_U|NJD_FLAG_CLAMP_V)

#define NJD_FLAG_HARD_MASK          (NJD_FLAG_USE_ALPHA|NJD_FLAG_FLIP_MASK|NJD_FLAG_CLAMP_MASK|NJD_FLAG_USE_ANISOTROPIC)

#define NJD_FLAG_SOFT_MASK          (NJD_FLAG_IGNORE_LIGHT|NJD_FLAG_PICK|NJD_FLAG_USE_TEXTURE|NJD_FLAG_DOUBLE_SIDE|NJD_FLAG_USE_ENV|NJD_FLAG_USE_FLAT)

#define NJD_FLAG_MASK               (NJD_FLAG_HARD_MASK|NJD_FLAG_SOFT_MASK)

/************************************************************************************/
/*
*   Material Constants
*/
/****** User/Sys Masks **************************************************************/
#define NJD_DEFAULT_USER_MASK	    (BIT_2|BIT_1|BIT_0)

#define NJD_DEFAULT_SYS_MASK	    (~NJD_DEFAULT_USER_MASK)

/************************************************************************************/
/*
*   Meshset Constants
*/
/****** Meshset Type ****************************************************************/
#define NJD_MESHSET_3           (0x0000)  /* polygon3 meshset                       */
#define NJD_MESHSET_4           (0x4000)  /* polygon4 meshset                       */
#define NJD_MESHSET_N           (0x8000)  /* polygonN meshset                       */
#define NJD_MESHSET_TRIMESH     (0xc000)  /* trimesh meshset                        */
#define NJD_MESHSET_MASK        (0xc000)  /* meshset type mask                      */

/****** Trimesh *********************************************************************/
#define NJD_TRIMESH_END         (0x8000)  /* trimesh end bit                        */

/************************************************************************************/
/*
*   Callback Constants
*/
/****** Callback Flags **************************************************************/
#define	NJD_POLYGON_CALLBACK	(BIT_31)        /* polygon callback                 */
#define	NJD_MATERIAL_CALLBACK	(BIT_30)        /* material callback                */

#define	NJD_CALLBACK_MASK		(BIT_31|BIT_30)	/* callback mask                    */

/************************/
/*  Structures          */
/************************/
/************************************************************************************/
/*
*   Model Structures
*/
/****** Material ********************************************************************/
typedef struct
{
    NJS_COLOR       diffuse;    /* diffuse color                                    */
    NJS_COLOR       specular;   /* specular color                                   */
    Float           exponent;   /* specular exponent                                */
    Uint32          attr_texId; /* attribute and texture ID in texlist              */
    Uint32          attrflags;  /* attribute flags                                  */
}
NJS_MATERIAL;

/****** Meshset *********************************************************************/
typedef struct
{
    Uint16          type_matId; /* meshset type and attr index                      */
    Uint16          nbMesh;     /* mesh count                                       */
    Sint16*         meshes;     /* mesh array                                       */
    Uint32*         attrs;      /* attribure                                        */
    NJS_VECTOR*     normals;    /* mesh normal list                                 */
    NJS_COLOR*      vertcolor;  /* polygon vertex color list                        */
    NJS_TEX*        vertuv;     /* polygon vertex uv list                           */
    void*           ext;        /* ???????????                                      */
}
NJS_MESHSET;

/****** Model ***********************************************************************/
typedef struct mdl
{
    NJS_POINT3*     points;     /* vertex list                                      */
    NJS_POINT3*     normals;    /* vertex normal list                               */
    Sint32          nbPoint;    /* vertex count                                     */
    NJS_MESHSET*    meshsets;   /* meshset list                                     */
    NJS_MATERIAL*   mats;       /* material list                                    */
    Uint16          nbMeshset;  /* meshset count                                    */
    Uint16          nbMat;      /* material count                                   */
    NJS_POINT3      center;     /* model center                                     */
    Float           r;          /* radius                                           */

#if (SAMT_CURR_GAME == SAMT_GAME_SADX)

    void*           res;        /* ???????????                                      */

#endif/*SAMT_CURR_GAME*/
}
NJS_MODEL;

/************************************************************************************/
/*
*   Object Structure
*/
/****** Object **********************************************************************/
typedef struct obj
{
    Uint32          evalflags;  /* evalation flags                                  */
    NJS_MODEL*      model;      /* model data pointer                               */
    Float           pos[3];     /* translation                                      */
    Angle           ang[3];     /* rotation or im part of quat                      */
    Float           scl[3];     /* scaling                                          */
    struct obj*     child;      /* child object                                     */
    struct obj*     sibling;    /* sibling object                                   */

#if (SAMT_CURR_GAME == SAMT_GAME_SA2B)

    Float           re_quat;    /* re part of quat                                  */

#endif/*SAMT_CURR_GAME*/
}
NJS_OBJECT;

EXTERN_END

#endif/*H_NJ_BASIC*/
