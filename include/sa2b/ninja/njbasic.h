/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njbasic.h'
*
*   Contains structs for the Ninja Basic model
*
*   Contributors:
*   -   SEGA,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
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
    NJS_COLOR         diffuse;
    NJS_COLOR        specular;
    float32          exponent;
    uint32         attr_texId;  /* attribute and texture ID in texlist        */
    uint32          attrflags;  /* attribute flags */
} NJS_MATERIAL;

typedef struct {
    uint16          type_matId; /* meshset type and attr index
                                   14-15 : meshset type bits
                                    0-13 : material id(0-4095)  */
    uint16          nbMesh;     /* mesh count                   */
    sint16*         meshes;		/* mesh array                   */
    uint32*         attrs;		/* attribure                    */
    NJS_VECTOR*     normals;	/* mesh normal list             */
    NJS_COLOR*      vertcolor;	/* polygon vertex color list    */
    NJS_TEX*        vertuv;		/* polygon vertex uv list       */
    void*           ext;
} NJS_MESHSET;

typedef struct {
    NJS_POINT3*     points;		/* vertex list                  */
    NJS_POINT3*     normals;	/* vertex normal list           */
    sint32          nbPoint;    /* vertex count                 */
    NJS_MESHSET*    meshsets;	/* meshset list                 */
    NJS_MATERIAL*   mats;		/* material list                */
    uint16          nbMeshset;  /* meshset count                */
    uint16          nbMat;      /* material count               */
    NJS_POINT3      center;     /* model center                 */
    float32			r;			/* ??????????? */
    void* res;
} NJS_MODEL;

/*
 * NJS_OBJECT
 */
typedef struct obj {
    uint32          evalflags;  /* evalation flags              */
    NJS_MODEL*      model;      /* model data pointer           */
    float32         pos[3];     /* translation                  */
    Angle           ang[3];     /* rotation                     */
    float32         scl[3];     /* scaling                      */
    struct obj*     child;      /* child object                 */
    struct obj*     sibling;    /* sibling object               */
} NJS_OBJECT;

#endif /* _NINJA_BASIC_H_ */