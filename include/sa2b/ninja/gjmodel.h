/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/gjmodel.h'
*
*   Description:
*       Ginja model structure.
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _GJ_MODEL_H_
#define _GJ_MODEL_H_

EXTERN_START

/************************/
/*  Constants           */
/************************/
/****** Vertex info type ************************************************************/
#define GJD_VERT_MATRIX         0   /* Info is matrix                               */
#define GJD_VERT_VERTEX         1   /* Info is vertex                               */
#define GJD_VERT_NORMAL         2   /* Info is normal                               */
#define GJD_VERT_COLOR          3   /* Info is color                                */
#define GJD_VERT_COLOR2         4   /* Info is another color                        */
#define GJD_VERT_UV             5   /* Info is UV coordinates                       */
#define GJD_VERT_END          255   /* End vertex info                              */

/****** Mesh param type *************************************************************/
#define GJD_MESH_VTXATTR        0   /* param is a vertex attribute                  */
#define GJD_MESH_ATTR           1   /* param is a mesh attribute                    */
#define GJD_MESH_LIGHTING       2   /* param is a lighting attribute                */
#define GJD_MESH_UNUSED0        3   /* unused param                                 */
#define GJD_MESH_ALPHABLEND     4   /* param defines alpha blending                 */
#define GJD_MESH_DIFFUSE        5   /* param defines diffuse params                 */
#define GJD_MESH_UNUSED1        6   /* unused param                                 */
#define GJD_MESH_UNUSED2        7   /* unused param                                 */
#define GJD_MESH_TEXID          8   /* param is texture id                          */
#define GJD_MESH_UNUSED3        9   /* unused param                                 */
#define GJD_MESH_TEXCOORDGEN   10   /* param is texture coordinate generator        */

/************************/
/*  Structures          */
/************************/
/****** Ginja model *****************************************************************/
typedef struct
{
    Uint8           type;       /* vertex info type                                 */
    Uint8           sizeData;   /* vertex data size                                 */
    Uint16          nbList;     /* vertex list length                               */
    Uint32          attr;       /* vertex attribute                                 */
    union {
        void*       vp;         /* void pointer                                     */
        GJS_MATRIX* matrix;     /* vertex matrix list                               */
        NJS_POINT3* points;     /* vertex point list                                */
        NJS_VECTOR* normals;    /* vertex normal list                               */
        NJS_COLOR*  vertcolor;  /* vertex color list                                */
        NJS_TEX*    vertuv;     /* vertex UV coords list                            */
    };
    Uint32          sizeList;   /* total list size in bytes                         */
}
GJS_VERTINFO;

typedef struct
{
    Sint8           type;       /* parameter type                                   */
    Sint32          data;       /* parameter data                                   */
}
GJS_MESHPARAM;

typedef struct
{
    GJS_MESHPARAM*  params;     /* parameter list                                   */
    Uint32          nbParam;    /* parameter count                                  */
    Uint8*          meshes;     /* mesh array                                       */
    Uint32          nbMesh;     /* mesh count                                       */
}
GJS_MESHSET;

typedef struct
{
    GJS_VERTINFO*   vertinfo;   /* vertex info list                                 */
    void*           vp;         /* unused pointer                                   */
    GJS_MESHSET*    meshsolid;  /* solid mesh set list                              */
    GJS_MESHSET*    meshtrans;  /* transparent mesh set list                        */
    Sint16          nbSolid;    /* solid mesh set count                             */
    Sint16          nbTrans;    /* transparent mesh set count                       */
    NJS_POINT3      center;     /* model center                                     */
    Float           r;          /* model radius                                     */
}
GJS_MODEL;

/****** Ginja object ****************************************************************/
typedef struct gjsobj
{
    Uint32          evalflags;  /* evalation flags                                  */
    GJS_MODEL*      model;      /* model data pointer                               */
    Float           pos[3];     /* translation                                      */
    Angle           ang[3];     /* rotation or im part of quat                      */
    Float           scl[3];     /* scaling                                          */
    struct gjsobj*  child;      /* child object                                     */
    struct gjsobj*  sibling;    /* sibling object                                   */
    Float           re_quat;    /* re part of quat                                  */
}
GJS_OBJECT;

EXTERN_END

#endif/*_GJ_MODEL_H_*/
