/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njbasic.h'
*
*   Contains structs for the Ninja Basic model
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _NINJA_BASIC_H_
#define _NINJA_BASIC_H_

/*--------------------------------------*/
/*      Model Structure                 */
/*--------------------------------------*/
/*
 * NJS_MODEL
 */
typedef struct {
    NJS_COLOR       diffuse;
    NJS_COLOR       specular;
    Float           exponent;
    Uint32          attr_texId; /* attribute and texture ID in texlist        */
    Uint32          attrflags;  /* attribute flags */
} NJS_MATERIAL;

typedef struct {
    Uint16          type_matId; /* meshset type and attr index
                                   14-15 : meshset type bits
                                    0-13 : material id(0-4095)  */
    Uint16          nbMesh;     /* mesh count                   */
    Sint16*         meshes;     /* mesh array                   */
    Uint32*         attrs;      /* attribure                    */
    NJS_VECTOR*     normals;    /* mesh normal list             */
    NJS_COLOR*      vertcolor;  /* polygon vertex color list    */
    NJS_TEX*        vertuv;     /* polygon vertex uv list       */
    void*           ext;        /* ???????????                  */
} NJS_MESHSET;

typedef struct {
    NJS_POINT3*     points;     /* vertex list                  */
    NJS_POINT3*     normals;    /* vertex normal list           */
    Sint32          nbPoint;    /* vertex count                 */
    NJS_MESHSET*    meshsets;   /* meshset list                 */
    NJS_MATERIAL*   mats;       /* material list                */
    Uint16          nbMeshset;  /* meshset count                */
    Uint16          nbMat;      /* material count               */
    NJS_POINT3      center;     /* model center                 */
    Float           r;          /* radius                       */
#if 0
    void*           res;        /* ???????????                  */
#endif
} NJS_MODEL;

/*
 * NJS_OBJECT
 */
typedef struct obj {
    Uint32          evalflags;  /* evalation flags              */
    NJS_MODEL*      model;      /* model data pointer           */
    Float           pos[3];     /* translation                  */
    Angle           ang[3];     /* rotation or im part of quat  */
    Float           scl[3];     /* scaling                      */
    struct obj*     child;      /* child object                 */
    struct obj*     sibling;    /* sibling object               */
    Float           re_quat;    /* re part of quat              */
} NJS_OBJECT;

#endif /* _NINJA_BASIC_H_ */
