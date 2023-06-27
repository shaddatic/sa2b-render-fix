/*
	Ninja Library
	
	COPYRIGHT (C) SEGA ENTERSRISES,LTD.
*/

#ifndef _NINJA_STR_H_
#define _NINJA_STR_H_

typedef sint8 NJS_SYS_ATTR[NJD_SYS_ATTR_SIZE];

typedef void (*NJS_INT_FUNC)(void);

typedef struct{
	uint32 NativeLimit;
	uint32 NativeCurrent;
	uint32 NativePeak;
	uint32 InternalVertexBufSize[5];
	uint32 MaxVertexBufSize[5];
	uint32 LastTATime;
	uint32 LastRenderTime;
	uint32 CurrentVertexBufSize[5];
	uint32 reserved0;
	uint32 reserved1;
	uint32 reserved2;
	uint32 reserved3;
	uint32 reserved4;
	uint32 reserved5;
	uint32 reserved6;
	uint32 reserved7;
	uint32 reserved8;
	uint32 reserved9;
	uint32 reserved10;
	uint32 reserved11;
} NJS_SYSTEMINFO;

typedef struct {
	sint16  u;
	sint16  v;
} NJS_TEX;

typedef	struct {
	uint8   b;
	uint8   g;
	uint8   r;
	uint8   a;
} NJS_BGRA;

typedef union {
	uint32  color;
	NJS_TEX tex;
	NJS_BGRA argb;
} NJS_COLOR;

typedef struct {
	float32   a;
	float32   r;
	float32   g;
	float32   b;
} NJS_ARGB;

typedef struct {
	sint16  x;
	sint16  y;
} NJS_POINT2I;

typedef struct {
	float32  x;
	float32  y;
} NJS_POINT2;

typedef struct {
	float32   x;
	float32   y;
	float32   z;
} NJS_POINT3, NJS_VECTOR;

typedef struct {
	NJS_POINT2  *p;
	NJS_COLOR   *col;
    NJS_COLOR   *tex;
    uint32      num;
} NJS_POINT2COL;

typedef struct {
	NJS_POINT3  *p;
	NJS_COLOR   *col;
    NJS_COLOR   *tex;
    uint32      num;
} NJS_POINT3COL;

typedef struct {
	float32   px,py,pz;
	float32   vx,vy,vz;
} NJS_LINE, NJS_PLANE, NJS_PVECTOR;


/* コリジョン用構造体追加 */
typedef struct{
    NJS_POINT3 c;
    float32      r;
} NJS_SPHERE;

typedef struct{
    NJS_POINT3 c1;
    NJS_POINT3 c2;
    float32      r;
} NJS_CAPSULE;

typedef struct{
    NJS_POINT3 v[8];
} NJS_BOX;

typedef struct{
    NJS_POINT3 v[4];
} NJS_RECT;
/* 追加終わり */


typedef struct {
	NJS_MATRIX m;
	float32   px,py,pz;
	float32   vx,vy,vz;
	Angle   roll;
	float32   apx,apy,apz;
	float32   avx,avy,avz;
	Angle   aroll;
} NJS_VIEW;

typedef struct {
	float32   tgtdist;
	float32   w,h;
	float32   cx,cy;
} NJS_SCREEN;


/*--------------------------------------*/
/*      Texture Structure               */
/*--------------------------------------*/
typedef struct{
	uint32 Type;
	uint32 BitDepth;
	uint32 PixelFormat;
	uint32 nWidth;
	uint32 nHeight;
	uint32 TextureSize;
	uint32 fSurfaceFlags;
	uint32 *pSurface;
	uint32 *pVirtual;
	uint32 *pPhysical;
}NJS_TEXSURFACE;
	
typedef struct{
	void*			   texaddr; /* texture address   			*/
	NJS_TEXSURFACE	texsurface;	/* texture surface 				*/
} NJS_TEXINFO;

typedef struct {
	void            *filename;  /* texture filename strings     */
	uint32               attr;  /* texture attribute            */
	uint32            texaddr;  /* texture memory list address  */
} NJS_TEXNAME;

typedef struct {
	NJS_TEXNAME     *textures;  /* texture array                */
	uint32          nbTexture;  /* texture count                */
} NJS_TEXLIST;

typedef struct {
	uint32			globalIndex;/* global unique texture ID     */
	uint32			bank;		/* palette bank 				*/
	uint32			tspparambuffer;/* TSPParambuffer			*/
	uint32			texparambuffer;/* TextureParambuffer		*/
	uint32			texaddr;	/* texture flag					*/
	NJS_TEXINFO		texinfo;	/* texinfo						*/
	uint16			count;		/* texture count  				*/
	uint16			dummy;
} NJS_TEXMEMLIST;

typedef struct {
	void 			*palette;	/*	palette pointer				*/
	uint16 			mode;		/*	color mode					*/
	sint16 			bank;		/*	bank						*/
	sint16 			offset;		/*	entry offset				*/
	sint16 			count;		/*	entry count					*/
}NJS_TEXPALETTE;

typedef struct {
	uint32	n;
	uint32	globalIndex;
	sint32	texerr;
	sint32	gdstat;
	sint32	gderr;
	sint32	reserved0;
	sint32	reserved1;
	sint32	reserved2;
}NJS_TEXERRSTAT;

typedef struct{
	uint32 nTextureType;
	uint16 nWidth;
	uint16 nHeight;
}NJS_PVRHEADERDATA;

/*--------------------------------------*/
/*      Model Structure                 */
/*--------------------------------------*/
/*
 * NJS_MODEL
 */
typedef struct {
	NJS_COLOR         diffuse;
	NJS_COLOR        specular;
	float32            exponent;
	uint32         attr_texId;  /* attribute and texture ID in texlist        */
    uint32          attrflags;  /* attribute flags */
} NJS_MATERIAL;

#ifdef _USE_OLD_OBJECT // Added by Shaddatic

typedef struct {
	uint16          type_matId; /* meshset type and attr index
								   14-15 : meshset type bits
									0-13 : material id(0-4095)  */
	uint16          nbMesh;     /* mesh count                   */
	sint16          *meshes;    /* mesh array                   */
	uint32          *attrs;     /* attribure                    */
    NJS_VECTOR      *normals;   /* mesh normal list             */
	NJS_COLOR       *vertcolor; /* polygon vertex color list    */
	NJS_COLOR       *vertuv;    /* polygon vertex uv list       */
} NJS_MESHSET;

typedef struct {
	NJS_POINT3      *points;    /* vertex list                  */
	NJS_VECTOR      *normals;   /* vertex normal list           */
	sint32          nbPoint;    /* vertex count                 */
	NJS_MESHSET     *meshsets;  /* meshset list                 */
	NJS_MATERIAL    *mats;      /* material list                */
	uint16          nbMeshset;  /* meshset count                */
    uint16          nbMat;      /* material count               */
	NJS_POINT3      center;     /* model center                 */
	fp32			r;			/* ??????????? */
} NJS_MODEL;

#else

typedef struct {
	uint16          type_matId; /* meshset type and attr index
								   14-15 : meshset type bits
									0-13 : material id(0-4095)  */
	uint16          nbMesh;     /* mesh count                   */
	sint16*			meshes;		/* mesh array                   */
	uint32*			attrs;		/* attribure                    */
	NJS_VECTOR*		normals;	/* mesh normal list             */
	NJS_COLOR*		vertcolor;	/* polygon vertex color list    */
	NJS_TEX*		vertuv;		/* polygon vertex uv list       */
	void*			ext;
} NJS_MESHSET;

typedef struct {
	NJS_POINT3*		points;		/* vertex list                  */
	NJS_POINT3*		normals;	/* vertex normal list           */
	sint32          nbPoint;    /* vertex count                 */
	NJS_MESHSET*	meshsets;	/* meshset list                 */
	NJS_MATERIAL*	mats;		/* material list                */
	uint16          nbMeshset;  /* meshset count                */
	uint16          nbMat;      /* material count               */
	NJS_POINT3      center;     /* model center                 */
	float32			r;			/* ??????????? */
	void*			res;
} NJS_MODEL;

#endif

/*
 * NJS_OBJECT
 */
typedef struct obj {
    uint32          evalflags;  /* evalation flags              */
	NJS_MODEL       *model;     /* model data pointer           */
	float32         pos[3];     /* translation                  */
	Angle           ang[3];     /* rotation                     */
	float32         scl[3];     /* scaling                      */
	struct obj      *child;     /* child object                 */
	struct obj      *sibling;   /* sibling object               */
} NJS_OBJECT;

/*
 * NJS_MOTION
 */
/* key frame animation */
typedef struct {
	uint32          keyframe;
	float32           key[3];
} NJS_MKEY_F;

typedef struct {
	uint32          keyframe;
	Angle           key[3];     /* angle                        */
} NJS_MKEY_A;

typedef struct {
	uint32          keyframe;
	Angle           angle;      /* angle                        */
	float32           axe[3];     /* axe vector                   */
} NJS_MKEY_AX;

typedef struct 
{
	uint32          keyframe;
	void            *key;        /* pointer                     */
} NJS_MKEY_P;

typedef struct {
	uint32          keyframe;
	float32           key;
} NJS_MKEY_F1;

typedef struct {
	uint32          keyframe;
	float32           key[2];
} NJS_MKEY_F2;

typedef struct {
	uint32          keyframe;
	float32           nrang;
	float32           frang;
	Angle           iang;
	Angle           oang;
} NJS_MKEY_SPOT;

typedef struct {
	uint32          keyframe;
	uint32          key;
} NJS_MKEY_UI32;

typedef struct {
	uint32          keyframe;
	sint32          key;
} NJS_MKEY_SI32, NJS_MKEY_A1;

typedef struct {
    uint32          keyframe;
    float32           key[4];
} NJS_MKEY_QUAT;

/*
 * NJS_MDATA
 */
/* 1 factor : pos or ang or scl or shape or vec */
typedef struct {
	void            *p[1];      /* factor pointer               */
	uint32          nb[1];      /* factor count                 */
} NJS_MDATA1;

/* 2 factors : pos and ang, pos and vec(light motion), etc      */
typedef struct {
	void            *p[2];      /* factor pointer               */
	uint32          nb[2];      /* factor count                 */
} NJS_MDATA2;

/* 3 factors : pos and ang and scl, pos and ang and shape, etc  */
typedef struct {
	void            *p[3];      /* factor pointer               */
	uint32          nb[3];      /* factor count                 */
} NJS_MDATA3;

/* 4 factors : pos and ang and scl and shape, etc               */
typedef struct {
	void            *p[4];      /* factor pointer               */
	uint32          nb[4];      /* factor count                 */
} NJS_MDATA4;

/* 5 factors : etc               */
typedef struct {
	void            *p[5];      /* factor pointer               */
	uint32          nb[5];      /* factor count                 */
} NJS_MDATA5;

typedef struct {
	void            *mdata;     /* NJS_MDATA array              */
	uint32          nbFrame;    /* frame count                  */
	uint16          type;       /* motion type  NJD_MTYPE_...   */
	uint16          inp_fn;     /* interpolation & factor count */
} NJS_MOTION;

typedef struct {
	NJS_OBJECT      *object;    /* Object Tree top pointer      */
	NJS_MOTION      *motion;    /* motion                       */
#if 0
	NJS_TEXLIST     *texlist;   /* current texture list         */
#endif
} NJS_ACTION;

typedef struct
{
	NJS_MOTION		*motion[2];		/* motion's pointers */
	float32			frame[2];		/* current frames */
} NJS_MOTION_LINK;

typedef struct
{
	NJS_OBJECT		*object;		/* object's pointer */
	NJS_MOTION_LINK	*motionlink;	/* motion-link's pointer */
} NJS_ACTION_LINK;


/*
 * 3DLIB WORK BUFFER
 */
typedef union {
	uint32		work;	/* work	*/
	uint32		clip;	/* clip	*/

} NJS_CLIP_BUF;

typedef struct {
	NJS_CLIP_BUF a;			/* union			: 32		*/
	float32		sx,sy;		/* screen point		: 36 40		*/
	float32		oow;		/* 1/w				: 44		*/
	NJS_POINT3	point;		/* vertex point		:  0  4  8	*/
	uint32		reserve;	/* clip				: 28		*/
	float32		u,v;		/* U, V				: 48 52		*/
	float32		inten[2];	/* Intensity		: 56 60		*/
	NJS_VECTOR	vector;		/* vertex normal	: 12 16 20	*/
	uint32		flag;		/* flag				: 24		*/
} NJS_VERTEX_BUF;			/* TotalSize		: 64		*/

typedef struct {
	NJS_CLIP_BUF a;			/* union			: 4	*/
	float32		sx,sy;		/* screen point		:12	*/
	float32		oow;		/* 1/w				:16	*/
	NJS_POINT3	point;		/* vertex point		:44	*/
	uint32		reserve;	/* clip				:64	*/
	NJS_ARGB	col;
	NJS_VECTOR	vector;		/* vertex normal	:56	*/
	uint32		flag;		/* flag				:58	*/
} NJS_VERTEX_BUF2;			/* TotalSize		: 64		*/


typedef struct {
	NJS_CLIP_BUF a;			/* union			: 32		*/
	float32		sx,sy;		/* screen point		: 36 40		*/
	float32		oow;		/* 1/w				: 44		*/
	NJS_POINT3	point;		/* vertex point		:  0  4  8	*/
	uint32		reserve;	/* clip				: 28		*/
	float32		u,v;		/* U, V				: 48 52		*/
	float32		inten[2];	/* Intensity		: 56 60		*/
	NJS_VECTOR	vector;		/* vertex normal	: 12 16 20	*/
	uint32		flag;		/* flag				: 24		*/
} NJS_VERTEX_BUF_0;

typedef struct {
	NJS_CLIP_BUF a;			/* union			: 4	*/
	float32		sx,sy;		/* screen point		:12	*/
	float32		oow;		/* 1/w				:16	*/
	NJS_POINT3	point;		/* vertex point		:44	*/
	uint32		reserve;	/* clip				:64	*/
	NJS_ARGB	col;
	NJS_VECTOR	vector;		/* vertex normal	:56	*/
	uint32		flag;		/* flag				:58	*/
} NJS_VERTEX_BUF_1;

typedef struct {
	NJS_CLIP_BUF a;			/* union			: 4	*/
	float32		sx,sy;		/* screen point		:12	*/
	float32		oow;		/* 1/w				:16	*/
	float32		u,v;		/* U V				:24	*/
	uint32		col[2];		/* pack col			:32	*/
	NJS_POINT3	point;		/* vertex point		:44	*/
	NJS_VECTOR	vector;		/* vertex normal	:56	*/
	uint32		flag;		/* flag				:58	*/
	uint32		reserve;	/* clip				:64	*/
} NJS_VERTEX_BUF_3;

typedef struct {
	NJS_CLIP_BUF a;			/* union			: 32		*/
	float32		sx,sy;		/* screen point		: 36 40		*/
	float32		oow;		/* 1/w				: 44		*/
	NJS_POINT3	point;		/* vertex point		:  0  4  8	*/
	uint32		reserve;	/* clip				: 28		*/
	float32		u,v;		/* U, V				: 48 52		*/
	float32		inten[2];	/* Intensity		: 56 60		*/
	NJS_VECTOR	vector;		/* vertex normal	: 12 16 20	*/
	uint32		flag;		/* flag				: 24		*/
} NJS_VERTEX_BUF_7;

typedef struct {
	NJS_VECTOR	vector;		/* vertex normal	:12	*/
	uint32		clip;		/* clip				:16	*/
	float32		sx,sy;		/* screen point		:24	*/
	float32		oow;		/* 1/w				:28	*/
	float32		inten;		/* intensity		:32	*/
} NJS_VERTEX_BUF_X;


/*--------------------------------------*/
/*      Light Structure                 */
/*--------------------------------------*/
/*
 * NJS_LIGHT_CAL
 */
typedef struct
{
/*************/
	float32       ratten;         /* attenuation rate             */
	float32       ipd;		    /* inner product                */
/*************/
	float32       nrr;            /* limit judgment value         */
	float32       frr;            /* limit judgment value         */
	float32       cosi;           /* limit judgment value         */
	float32       cose;           /* limit judgment value         */
	float32		idev;           /* judgment value of devision   */
	float32		odev;           /* judgment value of devision   */
	float32       rate;           /* attenuation rate(calculated) */
	float32       intns;          /* Intensity (0-1)              */
	Int         exp;            /* exponent(SGI):material       */
/*************/
	Int         reserve;        /*                              */
/*************/
	NJS_POINT3  lpnt;           /* point vector                 */
	NJS_VECTOR  lvctr;          /* directional vector           */
/*************/
	NJS_VECTOR  lmvctr;         /* directional vector           */
/*************/
	NJS_ARGB    atten;          /* intns * argb                 */
	NJS_ARGB    amb;            /* iamb*atten                   */
	NJS_ARGB    dif;            /* idif*atten                   */
	NJS_ARGB    spc;            /* ispc*atten                   */
/*************/
	NJS_ARGB    mamb;           /* amb*material                 */
	NJS_ARGB    mdif;           /* dif*material                 */
	NJS_ARGB    mspc;           /* spc*material                 */
/*************/
} NJS_LIGHT_CAL, *NJS_LIGHT_CAL_PTR;

/*
 * NJS_LIGHT_ATTR
 */
typedef struct {
	Int             lsrc;       /* the kind of light source     */
	float32           iamb;       /* ambient's intensity          */
	float32           idif;       /* deffuse light's intensity    */
	float32           ispc;       /* specular light's intensity   */
	float32           nrang;      /* limit value (nearest)        */
	float32           frang;      /* limit value (farthest)       */
	void*           func;       /* the pointer of Callback func.*/
	Angle           iang;       /* limit value (inside)         */
	Angle           oang;       /* limit value (outside)        */
	NJS_ARGB        argb;       /* light's color                */
} NJS_LIGHT_ATTR, *NJS_LIGHT_ATTR_PTR;

/*
 * NJS_LIGHT
 */
typedef struct {
	NJS_MATRIX      mtrx;       /* matrix                       */
	NJS_POINT3      pnt;        /* point vector                 */
	NJS_VECTOR      vctr;       /* directional vector           */
	Int             stat;       /* status                       */
	Int             reserve;    /* reserve                      */
	NJS_LIGHT_CAL   ltcal;      /* calculation                  */
	NJS_LIGHT_ATTR  attr;       /* attribute                    */
} NJS_LIGHT, *NJS_LIGHT_PTR;

/*
 * NJS_LIGHT_MATERIAL
 */
typedef  struct {
	NJS_ARGB        ambient;    /* Ambient color from Material	*/
	NJS_ARGB        diffuse;    /* Diffuse color from Material	*/
	NJS_ARGB        specular;   /* Specular color from Material	*/
	float32           exponent;   /* Exponent from Material		*/
} NJS_LIGHT_MATERIAL;

/*
 * NJF_LIGHT_FUNC
 */
typedef void (*NJF_LIGHT_FUNC)(NJS_ARGB*, NJS_POINT3*, NJS_VECTOR*, NJS_LIGHT_PTR);

/*--------------------------------------*/
/*      Camera Structure                */
/*--------------------------------------*/

typedef struct {
	float32 px, py, pz;
	float32 vx, vy, vz;
	Angle roll;
	Angle ang;
	float32 n_clip;
	float32 f_clip;
	NJS_VECTOR lx,ly;
} NJS_CAMERA;

/*--------------------------------------*/
/*   Light & Camera Motion Structure    */
/*--------------------------------------*/

typedef struct {
	NJS_LIGHT	*light;
	NJS_MOTION	*motion;
} NJS_LACTION;

typedef struct {
	NJS_CAMERA	*camera;
	NJS_MOTION	*motion;
} NJS_CACTION;

typedef struct {
	float32	*pos;
	Angle	*ang;
	float32	*scl;
} NJS_MOTION_DATA;

/*--------------------------------------*/
/*      Scroll Structure                */
/*--------------------------------------*/
/*
 * NJS_SCLATTR
 */
typedef uint32 NJS_SCLATTR;     /* scroll attribute structure   */

/*
 * NJS_SCLMTRX
 */
typedef float32 NJS_SCLMTRX[4];   /* scroll rotation matrix       */

/*
 *NJS_SCROLL
 */
typedef struct {
	uint16      celps;          /* pixel size of the cells      */
	uint16      mapw;           /* number of the width of map   */
	uint16      maph;           /* number of the height of map  */
	uint16      sw,sh;          /* size of the scroll draw      */
	NJS_TEXLIST* list;			/* texlist ID                   */
	uint32      *map;           /* map array pointer            */
	float32       px,py;          /* scroll transration           */
	float32       bx,by;          /* map draw scroll              */
	float32       pr;             /* priority                     */
	uint16      sflag;          /* scale flag                   */
	float32       sx,sy;          /* scale x,y                    */
	float32		spx,spy;		/* center of scale x,y			*/
	uint16      mflag;          /* matrix flag                  */
	float32       cx,cy;          /* center of rotation x,y       */
	NJS_SCLMTRX m;              /* rotation matrix              */
	uint32      colmode;        /* color mode                   */
	NJS_POINT2	clip[2];
	NJS_SCLATTR attr;           /* scroll attribute             */
	NJS_COLOR	sclc;
}NJS_SCROLL;

enum{
	_SM00,_SM01,
	_SM10,_SM11
};

/*--------------------------------------*/
/*      Sprite                          */
/*--------------------------------------*/
typedef struct {
	sint16		sx,sy;			/* size				*/
	sint16      cx,cy;          /* center           */
	sint16      u1,v1;          /* upper left       */
	sint16      u2,v2;          /* lower right      */
	sint16      texid;          /* texture id       */
	sint16      attr;           /* attribute        */
} NJS_TEXANIM;

typedef struct {
	NJS_POINT3  p;              /* point            */
	float32       sx,sy;          /* scale            */
	Angle       ang;            /* angle            */
	NJS_TEXLIST *tlist;         /* texture list     */
	NJS_TEXANIM *tanim;         /* animation list   */
} NJS_SPRITE;

/*--------------------------------------*/
/*      Low Level                       */
/*--------------------------------------*/

typedef struct {
	float32	x;
	float32	y;
	float32	z;
	uint32	col;
} NJS_POLYGON_VTX;

typedef struct {
	float32	x;
	float32	y;
	float32	z;
	float32	u;
	float32	v;
	uint32	col;
} NJS_TEXTURE_VTX;

typedef struct {
	float32	x;
	float32	y;
	float32	z;
	float32	u;
	float32	v;
	uint32	bcol;
	uint32	ocol;
} NJS_TEXTUREH_VTX;

/*--------------------------------------*/
/*      Math                            */
/*--------------------------------------*/
typedef struct {
	int		keys;			/* keyframes between two points which must be interpolated */
	int		*iparam;		/* attribute data (integer) */
	float	*fparam;		/* attribute data (float) */
} NJS_SPLINE;

typedef	struct {
	float	re;					/* real (or scalor) part of quaternion		*/
	float	im[3];				/* imaginary (or vector) part of quaternion	*/
} NJS_QUATERNION;


#endif /* _NINJA_STR_H_ */
