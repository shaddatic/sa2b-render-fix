/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/ginja.h'
*
*   Ginja is a modified version of Ninja used for the GameCube
*   We have no symbols for these, so a lot of this is guess work
*
*   Contributors:
*   -   SEGA,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _GINJA_H_
#define _GINJA_H_

/* Vertex info type */
#define GJD_VERT_MATRIX			0
#define GJD_VERT_VERTEX			1
#define GJD_VERT_NORMAL			2
#define GJD_VERT_COLOR			3
#define GJD_VERT_COLOR2			4
#define GJD_VERT_UV				5
#define GJD_VERTEND		      255

/* Mesh param type */
#define GJD_MESH_VTXATTR		0
#define GJD_MESH_ATTR			1
#define GJD_MESH_LIGHTING		2
#define GJD_MESH_UNUSED0		3
#define GJD_MESH_ALPHABLEND		4
#define GJD_MESH_DIFFUSE		5
#define GJD_MESH_UNUSED1		6
#define GJD_MESH_UNUSED2		7
#define GJD_MESH_TEXID			8
#define GJD_MESH_UNUSED3		9
#define GJD_MESH_TEXCOORDGEN   10

/* Ginja flags */
// none yet

/*
 * GJS_MODEL
 */
typedef union
{
    void*           matrix;
    NJS_POINT3*     points;
    NJS_VECTOR*     normals;
    NJS_COLOR*      vertcolor;
    NJS_TEX*        vertuv;
    void*           vp;
}
GJS_VERTDATA;

typedef struct
{
    Uint8			type;		/* vertex info type				*/
    Sint8			datasize;	/* vertex data size				*/
    Sint16			nbData;		/* vertex data count			*/
    Sint32			attr;		/* vertex attribute				*/
    GJS_VERTDATA	data;		/* vertex data array			*/
    Sint32			size;		/* total array size				*/
}
GJS_VERTINFO;

typedef struct
{
    Sint8			type;		/* parameter type				*/
    Sint32			data;		/* parameter data				*/
}
GJS_MESHPARAM;

typedef struct
{
    GJS_MESHPARAM*  params;		/* parameter list				*/
    Sint32			nbParam;	/* parameter count				*/
    Sint8*          meshes;		/* mesh array					*/
    Sint32			nbMesh;		/* mesh count					*/
}
GJS_MESHSET;

typedef struct
{
    GJS_VERTINFO*   vertinfo;	/* vertex info list				*/
    void*           vp;			/* unkown pointer				*/
    GJS_MESHSET*    meshsolid;	/* solid mesh set list			*/
    GJS_MESHSET*    meshtrans;	/* transparent mesh set list	*/
    Sint16			nbSolid;	/* solid mesh set count			*/
    Sint16			nbTrans;	/* transparent mesh set count	*/
    NJS_POINT3		center;		/* model center					*/
    Float			r;			/* model radius					*/
}
GJS_MODEL;

/*
 * GJS_OBJECT
 */
typedef struct gjsobj
{
    Uint32          evalflags;	/* evalation flags              */
    GJS_MODEL*      model;		/* model data pointer           */
    Float           pos[3];		/* translation                  */
    Angle           ang[3];		/* rotation or im part of quat  */
    Float           scl[3];		/* scaling                      */
    struct gjsobj*  child;		/* child object                 */
    struct gjsobj*  sibling;	/* sibling object               */
    Float           re_quat;	/* re part of quat              */
}
GJS_OBJECT;

/************************/
/*  Data                */
/************************/
DataRef(void*, _gj_motion_callback_, 0x01D19C48);

/************************/
/*  Function Pointers   */
/************************/
FuncPtr(void, __cdecl, gjTransformObject, (GJS_OBJECT* object, int(__cdecl* callback)(GJS_MODEL*)), 0x0042DC20);

FuncPtr(void, __cdecl, gjDrawObject, (GJS_OBJECT* object), 0x0042B530);

/************************/
/*  User Functions      */
/************************/
void	gjCalcPoint(NJS_MATRIX* m, NJS_VECTOR* vs, NJS_VECTOR* vd, char b);

void	gjDrawMotion(GJS_OBJECT* object, NJS_MOTION* motion, float32 frame);
void	gjDrawMotionLink(GJS_OBJECT* object, NJS_MOTION_LINK* motionlink, float32 frame);

void	gjMultiMatrix(NJS_MATRIX* md, NJS_MATRIX* md2, NJS_MATRIX* ms);

void	gjDrawModel(GJS_MODEL* model);

/************************/
/*  Functions           */
/************************/
void	gjSetMotionCallback(void (*func)(GJS_OBJECT* gjsobj));

#endif /* _GINJA_H_ */