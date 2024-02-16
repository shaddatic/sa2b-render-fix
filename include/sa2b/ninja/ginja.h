/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/ginja.h'
*
*   Description:
*       Ginja constants, structs, and functions. It is a
*   modified version of Ninja used for the GameCube.
*
*   Contributors:
*   -   SEGA,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _GINJA_H_
#define _GINJA_H_

/************************/
/*  Includes            */
/************************/
/** System **/
#include <sa2b/shinobi/sg_xpt.h>

/************************/
/*  Constants           */
/************************/
/****** Vertex info type ****************************************************/
#define GJD_VERT_MATRIX         0   /* Info is matrix                       */
#define GJD_VERT_VERTEX         1   /* Info is vertex                       */
#define GJD_VERT_NORMAL         2   /* Info is normal                       */
#define GJD_VERT_COLOR          3   /* Info is color                        */
#define GJD_VERT_COLOR2         4   /* Info is another color                */
#define GJD_VERT_UV             5   /* Info is UV coordinates               */
#define GJD_VERT_END          255   /* End vertex info                      */

/****** Mesh param type *****************************************************/
#define GJD_MESH_VTXATTR        0
#define GJD_MESH_ATTR           1
#define GJD_MESH_LIGHTING       2
#define GJD_MESH_UNUSED0        3
#define GJD_MESH_ALPHABLEND     4
#define GJD_MESH_DIFFUSE        5
#define GJD_MESH_UNUSED1        6
#define GJD_MESH_UNUSED2        7
#define GJD_MESH_TEXID          8
#define GJD_MESH_UNUSED3        9
#define GJD_MESH_TEXCOORDGEN   10

/****** Ginja flags *********************************************************/
// none yet

/************************/
/*  Structures          */
/************************/
/****** Ginja model *********************************************************/
typedef struct
{
    Uint8           type;       /* vertex info type                         */
    Uint8           sizeData;   /* vertex data size                         */
    Uint16          nbList;     /* vertex list length                       */
    Uint32          attr;       /* vertex attribute                         */
    union {
        void*       vp;         /* void pointer                             */
        GJS_MATRIX* matrix;     /* vertex matrix list                       */
        NJS_POINT3* points;     /* vertex point list                        */
        NJS_VECTOR* normals;    /* vertex normal list                       */
        NJS_COLOR*  vertcolor;  /* vertex color list                        */
        NJS_TEX*    vertuv;     /* vertex UV coords list                    */
    };
    Uint32          sizeList;   /* total list size in bytes                 */
}
GJS_VERTINFO;

typedef struct
{
    Sint8           type;       /* parameter type                           */
    Sint32          data;       /* parameter data                           */
}
GJS_MESHPARAM;

typedef struct
{
    GJS_MESHPARAM*  params;     /* parameter list                           */
    Uint32          nbParam;    /* parameter count                          */
    Uint8*          meshes;     /* mesh array                               */
    Uint32          nbMesh;     /* mesh count                               */
}
GJS_MESHSET;

typedef struct
{
    GJS_VERTINFO*   vertinfo;   /* vertex info list                         */
    void*           vp;         /* unused pointer                           */
    GJS_MESHSET*    meshsolid;  /* solid mesh set list                      */
    GJS_MESHSET*    meshtrans;  /* transparent mesh set list                */
    Sint16          nbSolid;    /* solid mesh set count                     */
    Sint16          nbTrans;    /* transparent mesh set count               */
    NJS_POINT3      center;     /* model center                             */
    Float           r;          /* model radius                             */
}
GJS_MODEL;

/****** Ginja object ********************************************************/
typedef struct gjsobj
{
    Uint32          evalflags;  /* evalation flags                          */
    GJS_MODEL*      model;      /* model data pointer                       */
    Float           pos[3];     /* translation                              */
    Angle           ang[3];     /* rotation or im part of quat              */
    Float           scl[3];     /* scaling                                  */
    struct gjsobj*  child;      /* child object                             */
    struct gjsobj*  sibling;    /* sibling object                           */
    Float           re_quat;    /* re part of quat                          */
}
GJS_OBJECT;

/************************/
/*  Data                */
/************************/
/****** Matrix **************************************************************/
/** Current matrix pointer **/
#define _gj_matrix_                 DataRef(GJS_MATRIX*, 0x01A557FC)

/** Matrix limits **/
#define _gj_base_matrix_            DataRef(GJS_MATRIX*, 0x0267053C)
#define _gj_max_matrix_             DataRef(GJS_MATRIX*, 0x0267053C)

/****** Fog *****************************************************************/
/** Fog status **/
#define _gj_fog_enable_             DataRef(Int        , 0x025EFFCC)

/****** Motion **************************************************************/
/** Motion callback **/
#define _gj_motion_callback_        DataRef(void*      , 0x01D19C48)

/************************/
/*  Functions           */
/************************/
EXTERN_START
/****** Matrix **************************************************************/
void    gjInitMatrix(GJS_MATRIX* mb, Int count);

void    gjPushUnitMatrix();

void    gjTranslate(Float x, Float y, Float z);

void    gjRotateX(Angle ang);
void    gjRotateY(Angle ang);
void    gjRotateZ(Angle ang);

void    gjAddVector(NJS_VECTOR* vd, NJS_VECTOR* vs1, NJS_VECTOR* vs2);
void    gjSubVector(NJS_VECTOR* vd, NJS_VECTOR* vs1, NJS_VECTOR* vs2);

/****** Fog *****************************************************************/
void    gjEnableFog(void);
void    gjDisableFog(void);

void    gjUpdateFog(void);

/****** Motion **************************************************************/
/** Set Ginja motion callback **/
void    gjSetMotionCallback(void (*func)(GJS_OBJECT* gjsobj));

/** Draw Ginja Motion **/
void    gjDrawMotion(GJS_OBJECT* object, NJS_MOTION* motion, Float frame);
void    gjDrawMotionLink(GJS_OBJECT* object, NJS_MOTION_LINK* motionlink, Float frame);

/****** Ginja chunk *********************************************************/
/** Begin draw chunk models **/
void    gjBeginDrawCnkModel(void); 

/****** Ginja model *********************************************************/
/** Transform Ginja Object **/
void    gjTransformObject(GJS_OBJECT* object, int(__cdecl* callback)(GJS_MODEL*));

/** Begin Draw Ginja Models **/
void    gjBeginDrawModel(void);
void    gjDrawModel(GJS_MODEL* model);

EXTERN_END

#endif/*_GINJA_H_*/
