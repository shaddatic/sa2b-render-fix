/*
	Custom Ninja Library

	COPYRIGHT No-one probably lol
*/

/*
*	Ginja is a modified version of Ninja used for the GameCube and beyond (basically post Dreamcast)
*	We have no symbols for these (yet!), so a lot of this is guess work.
*/

#ifndef _GINJA_H_
#define _GINJA_H_

enum eGJS_VERTKIND
{
	GJS_VERTKIND_MATRIX,
	GJS_VERTKIND_VERTEX,
	GJS_VERTKIND_NORMAL,
	GJS_VERTKIND_COLOR,
	GJS_VERTKIND_COLOR2,
	GJS_VERTKIND_UV,
	GJS_VERTKIND_END = -1,
};

enum eGJS_PARAMKIND
{
	GJS_PARAMKIND_VTXATTR,
	GJS_PARAMKIND_ATTR,
	GJS_PARAMKIND_LIGHTING,
	GJS_PARAMKIND_UNUSED0,
	GJS_PARAMKIND_ALPHABLEND,
	GJS_PARAMKIND_DIFFUSE,
	GJS_PARAMKIND_UNUSED1,
	GJS_PARAMKIND_UNUSED2,
	GJS_PARAMKIND_TEXID,
	GJS_PARAMKIND_UNUSED3,
	GJS_PARAMKIND_TEXCOORDGEN
};

struct GJS_VERTDATA
{
	sint8			DataType; // 1 = Vertex, 3 = VColor?, 5 = UV?, 0xFF = end list
	sint8			ElementSize;
	sint16			ElementCount;
	sint32			attr;
	void*			Data;
	sint32			DataSize;
};

struct GJS_MESHPARAM
{
	sint32 type;
	sint32 param;
};

struct GJS_MESHDATA
{
	GJS_MESHPARAM*	ParameterOffset;
	sint32			ParameterCount;
	uint8*			PrimitiveOffset;
	sint32			PrimitiveCount;
};

struct GJS_MODEL
{
	GJS_VERTDATA*	vertexData;
	sint32			nbVertexData; // unknown
	GJS_MESHDATA*	opaqueMeshes;
	GJS_MESHDATA*	transparentMeshes;
	sint16			nbOpaque;
	sint16			nbTransparent;
	NJS_POINT3		center;
	float32			r;
};

typedef struct gjsobj
{
	uint32          evalflags;
	GJS_MODEL*		model;
	float32         pos[3];
	Angle           ang[3];
	float32         scl[3];
	struct gjsobj*	child;
	struct gjsobj*	sibling;
}
GJS_OBJECT;

/*
*	Data Refs
*/

DataRef(void*, _gj_motion_callback_, 0x01D19C48);

/*
*	Function Pointers
*/

FuncPtr(void, __cdecl, _gjTransformObject, (GJS_OBJECT* object, int(__cdecl* callback)(GJS_MODEL*)), 0x0042DC20);

FuncPtr(void, __cdecl, gjDrawObject, (GJS_OBJECT* object), 0x0042B530);

/*
*	User Functions
*/
void	gjCalcPoint(NJS_MATRIX* m, NJS_VECTOR* vs, NJS_VECTOR* vd, char b);

void	gjDrawMotion(GJS_OBJECT* object, NJS_MOTION* motion, float32 frame);
void	gjDrawMotionLink(GJS_OBJECT* object, NJS_MOTION_LINK* motionlink, float32 frame);

void	gjMultiMatrix(NJS_MATRIX* md, NJS_MATRIX* md2, NJS_MATRIX* ms);

void	gjDrawModel(GJS_MODEL* model);

/*
*	Remade Functions
*/

void	gjSetMotionCallback(void (*func)(GJS_OBJECT* gjsobj));

#endif /* _GINJA_H_ */