/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njdef.h'
*
*   Contains macros and defines for interpreting Ninja Ascii files
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _NJDEF_H_
#define _NJDEF_H_

/********************************************************
 *
 * Ninja Ascii
 *
 ********************************************************/
/*--------------*/
/* cast OBJTYPE */
/*--------------*/
#define _OBJPOINTERTYPE

/*-----------*/
/* Start/End */
/*-----------*/
#define START          ={
#define END            };

/*----*/
/* Uv */
/*----*/
/* Basic */
#define UV( _u, _v) (((((long)(_v))<<16)&0xffff0000)|((long)(_u))& 0x0000ffff)

/* Chunk */
#define Uvn( _u, _v)       (_u), (_v)
#define Uvh( _u, _v)       (_u), (_v)

/*-------*/
/* Angle */
/*-------*/
#define _NJAVAL             (65536.0F/360.0000F)
#define _NJANG1(_a)         (int32_t)(_NJAVAL*(_a))
#define _NJANG( _x, _y, _z)                               \
    {(int32_t)(_NJAVAL*(_x)), (int32_t)(_NJAVAL*(_y)), (int32_t)(_NJAVAL*(_z))}

/*------*/
/* ARGB */
/*------*/
#define _ARGB( _a, _r, _g, _b)                                           \
                ( (uint32_t)((_a)<<24)|(uint32_t)((_r)<<16)    \
                 |(uint32_t)((_g)<<8)|(_b) )
#define ARGB( _a, _r, _g, _b) _ARGB( _a, _r, _g, _b)
#define _NJARGB( _a, _r, _g, _b) _ARGB( _a, _r, _g, _b)

/*---------*/
/* TexList */
/*---------*/
#define TEXN(_texname)     {(void*)(_texname), 0x0, 0}
#define TEXN3(_texname, _attr, _texaddr) {(void*)(_texname), _attr, _texaddr}
#define TEXTURE_START
#define TEXTURENAME         NJS_TEXNAME
#define TEXTURELIST         NJS_TEXLIST
#define NO_TEXTURE          0
#define TEXTURE_END
#define TextureList
#define TextureNum

/* palette */
#define _SET_CNT(_f) (_f ? NJD_TEXATTR_TEXCONTINUE : 0)
#define _SET_BNK(_b) (((_b) << NJD_TEXBANK_SHIFT) & NJD_TEXBANK_MASK)
#define _SET_BNK2(_b, _g) (_SET_BNK(_b)|((_g) & ~NJD_TEXBANK_MASK))

#define PTEXN(_tname, _cnt, _bnk) {(_tname), _SET_CNT(_cnt), _SET_BNK(_bnk)}
#define PTEXN5(_tname, _attr, _texaddr, _cnt, _bnk)                     \
    {(_tname), _SET_CNT(_cnt)|(_attr), _SET_BNK2(_bnk, _texaddr)}

/*----------*/
/* instance */
/*----------*/
#define INSTANCE_PROTOTYPE_START
#define INSTANCE_PROTOTYPE_END

/*----------*/
/* Material */
/*----------*/
/* Basic */
#define MATERIAL            NJS_MATERIAL
#define MATSTART           {

#define Diffuse( _a, _r, _g, _b)  _ARGB(_a, _r, _g, _b)
#define Specular( _a, _r, _g, _b) _ARGB(_a, _r, _g, _b)
#define Exponent( _exp)           (_exp)
#define AttrTexId( _attr, _tid)   ((_attr)|(_tid))
#define AttrFlags( _atf)          ((_atf))

#define MATEND             },

/* Chunk */
#define MDiff( _a, _r, _g, _b) ((_g) << 8)|(_b), ((_a) << 8)|(_r)
#define MSpec( _a, _r, _g, _b) ((_g) << 8)|(_b), ((_a) << 8)|(_r)
#define MAmbi( _a, _r, _g, _b) ((_g) << 8)|(_b), ((_a) << 8)|(_r)
#define AttrF( _f ) ((_f) & 0xffff), (((_f) >> 16) & 0xffff)

/*--------*/
/* Vertex */
/*--------*/
/* Basic/Chunk */
#define VERT( _x, _y, _z)   (_x), (_y), (_z)
#define NORM( _x, _y, _z)   (_x), (_y), (_z)
#define POINT           NJS_POINT3
#define NORMAL          NJS_VECTOR

/* Chunk */
#define NORM32( _x, _y, _z)     ((_x)<<20|(_y)<<10|(_z))
#define D8888( _a, _r, _g, _b)  _ARGB(_a, _r, _g, _b)
#define UFlags( _f)             (_f)
#define NFlags( _f)             (_f)
#define _WPCa( _p)              ((uint32_t)(((_p)*255.0F)/100.0F+0.5F))
#define NFlagsW( _idx, _wp)     (((_WPCa(_wp) & 0xffff)<<16)|((_idx) & 0xffff))
#define _WPCa2( _p)              ((uint32_t)(((_p)*65535.0F)/100.0F+0.5F))
#define NFlagsW2( _idx, _wp)     (((_WPCa2(_wp) & 0xffff)<<16)|((_idx) & 0xffff))

#define _RGB565( _r, _g, _b)                                           \
 ( (((_r) & 0x1f)<<11)|(((_g) & 0x3f)<<5)|((_b) & 0x1f) )
#define _ARGB4444( _a, _r, _g, _b)                                     \
 ( (((_a) & 0xf)<<12)|(((_r) & 0xf)<<8)|(((_g) & 0xf)<<4)|((_b) & 0xf) )

/*---------*/
/* Polygon */
/*---------*/
/* Basic */
#define POLYGON              Sint16

/*-------*/
/* Strip */
/*-------*/
/* Basic */
#define Strip( _flag, _len) ((_flag)|(_len))

/* Chunk */
#define StripL( _len)       (_len)
#define StripR( _len)       (_len) * -1

/*---------------*/
/* PolygonNormal */
/*---------------*/
/* Basic */
#define POLYNORMAL          NJS_VECTOR
#define STRIPNORMAL         NJS_VECTOR

#define PNORM( _x, _y, _z)  (_x), (_y), (_z)

/*-------------*/
/* VertexColor */
/*-------------*/
/* Basic */
#define VERTCOLOR           NJS_COLOR

/*---------------------*/
/* PolygonVertexNormal */
/*---------------------*/
#define _PVN_MAX 32767.0F

#define Pvn( _x, _y, _z) (_x)*_PVN_MAX, (_y)*_PVN_MAX, (_z)*_PVN_MAX

/*------*/
/* Bump */
/*------*/
#define _BuDir(_dx, _dy, _dz) Pvn(_dx, _dy, _dz)
#define _BuUp(_dx, _dy, _dz) Pvn(_dx, _dy, _dz)

/*----------*/
/* VertexUv */
/*----------*/
/* Basic */
#define VERTUV              NJS_COLOR

/*---------*/
/* Meshset */
/*---------*/
/* Basic */
#define MESHSET             NJS_MESHSET
#define MESHSTART           {
#define MESHEND             },

#define TypeMatId(_type, _mid) ((_type)|(_mid))
#define MeshNum
#define Meshes
#define PolyAttrs
#define PolyNormal
#define VertColor
#define VertUV

/*-------*/
/* Model */
/*-------*/
#define Center
#define Radius

/* Basic */
#define MODEL                NJS_MODEL
#define Model

#define Points
#define Normal
#define Meshset
#define PointNum
#define MeshsetNum
#define Materials
#define MatNum

/* Chunk */
#define CNKMODEL             NJS_CNK_MODEL
#define CNKModel

#define VList
#define PList

#define VLIST                Sint32
#define PLIST                Sint16

/*--------*/
/* Object */
/*--------*/
/* Basic */
#define OBJECT               NJS_OBJECT

#define OBJECT_START
#define OBJECT_END

/* Chunk */
#define CNKOBJECT            NJS_CNK_OBJECT

#define CNKOBJECT_START
#define CNKOBJECT_END

/* Basic/Chunk */
#define EvalFlags( _ef)        (_ef)
#define Child               _OBJPOINTERTYPE
#define Sibling             _OBJPOINTERTYPE

#define OPosition(_x, _y, _z)  (_x), (_y), (_z)
#define OAngle(_x, _y, _z)     _NJANG(_x, _y, _z)
#define OScale(_x, _y, _z)     (_x), (_y), (_z)

#define OQuatIm(_x, _y, _z)    (_x), (_y), (_z)
#define OQuatRe(_c)            (_c)

/*--------*/
/* Motion */
/*--------*/
#define _KEYVAL                (65536.0F/360.0000F)
#define MKEYF( _k, _x, _y, _z)                                      \
    {((Uint32)(_k)), ((float)(_x)), ((float)(_y)), ((float)(_z))}
#define MKEYF1( _k, _a)                                             \
    {((Uint32)(_k)), ((float)(_a))}
#define MKEYF2( _k, _n, _f)                                         \
    {((Uint32)(_k)), ((float)(_n)), ((float)(_f))}
#define MKEYA( _k, _x, _y, _z)                                      \
    {((Uint32)(_k)), ((Angle)(_KEYVAL*(_x))),                       \
     ((Angle)(_KEYVAL*(_y))),((Angle)(_KEYVAL*(_z)))}
#define MKEYSA( _k, _x, _y, _z)                                     \
    {((Uint16)(_k)), ((Sangle)(_KEYVAL*(_x))),                      \
     ((Sangle)(_KEYVAL*(_y))), ((Sangle)(_KEYVAL*(_z)))}
#define MKEYA1(_k, _v)        {((Uint32)(_k)),((Angle)(_KEYVAL*(_v)))}
#define MKEYSA1(_k, _v)       {((Uint16)(_k)),((Sangle)(_KEYVAL*(_v)))}
#define MKEYAX( _k, _a, _x, _y, _z)                                 \
    {((Uint32)(_k)), ((float)((_a))),                               \
     ((float)(_x)), ((float)(_y)), ((float)(_z))}
#define MKEYQ( _k, _a, _x, _y, _z)                                  \
    {((Uint32)(_k)), ((float)((_a))),                               \
     ((float)(_x)), ((float)(_y)), ((float)(_z))}
#define MKEYP(k,x)            {((Uint32)(k)),((void *)(x))}
#define MKEYUI32(_k, _v)      {((Uint32)(_k)),((uint32_t)(_v))}
#define MKEYSI32(_k, _v)      {((Uint32)(_k)),((int32_t)(_v))}
#define MKEYUI16(_k, _v)      {((Uint16)(_k)),((Uint16)(_v))}
#define MKEYSHID(_k, _id)     {((Uint32)(_k)), ((Uint32)(_id))}

#define MOTION_START
#define SHAPE_MOTION_START
#define POSITION    NJS_MKEY_F
#define QROTATION   NJS_MKEY_QUAT
#define ROTATION    NJS_MKEY_A
#define SROTATION   NJS_MKEY_SA
#define SCALE       NJS_MKEY_F
#define SCALE2D     NJS_MKEY_F2
#define EVENTBITS   NJS_MKEY_UI16
#define MDATA1      NJS_MDATA1
#define MDATA2      NJS_MDATA2
#define MDATA3      NJS_MDATA3
#define MDATA4      NJS_MDATA4
#define MDATA5      NJS_MDATA5
#define MOTION      NJS_MOTION
#define MOTION_END
#define SHAPE_MOTION_END

#define MdataArray
#define MFrameNum
#define MotionBit
#define InterpolFct
#define MotionBitF(_f)      (_f)
#define InterpolFctF(_f)    (_f)
#define ObjectHead     _OBJPOINTERTYPE
#define Motion

/* Flag Motion Key */
#define FMK_POS0    NJD_MTYPE_POS_0
#define FMK_ANG1    NJD_MTYPE_ANG_1
#define FMK_SCA2    NJD_MTYPE_SCL_2
#define FMK_VEC3    NJD_MTYPE_VEC_3
#define FMK_VEC0    NJD_MTYPE_VEC_0
#define FMK_SAN1    NJD_MTYPE_SANG_1
#define FMK_TAR3    NJD_MTYPE_TARGET_3
#define FMK_ROL6    NJD_MTYPE_ROLL_6
#define FMK_ANG7    NJD_MTYPE_ANGLE_7
#define FMK_RGB8    NJD_MTYPE_RGB_8
#define FMK_INT9    NJD_MTYPE_INTENSITY_9
#define FMK_POI9    NJD_MTYPE_POINT_9
#define FMK_QUA1    NJD_MTYPE_QUAT_1
#define FMK_SHID    NJD_MTYPE_SHAPEID
#define FMK_EVE4    NJD_MTYPE_EVENT_4

/* Flag Motion Type */
#define FMT_L       NJD_MTYPE_LINER
#define FMT_S       NJD_MTYPE_SPLINE
#define FMT_U       NJD_MTYPE_USER

/* Flag MDATA */
#define FMD_1       (1)
#define FMD_2       (2)
#define FMD_3       (3)
#define FMD_4       (4)
#define FMD_5       (5)

/* Flag Event Motion */
#define FEM_NONE    (0)
#define FEM_HD      (NJD_EVENT_HIDE)

/*---------*/
/* DEFAULT */
/*---------*/
/* Basic/Chunk */
#define DEFAULT_START
#define DEFAULT_END

/*-------------------------------------------------------
 * Chunk Flags
 *------------------------------------------------------*/
/*------------*/
/* Chunk Bits */
/*------------*/
/** EvalFlags **/
#define FEV_UT    NJD_EVAL_UNIT_POS
#define FEV_UR    NJD_EVAL_UNIT_ANG
#define FEV_US    NJD_EVAL_UNIT_SCL
#define FEV_HD    NJD_EVAL_HIDE
#define FEV_BR    NJD_EVAL_BREAK
#define FEV_ZXY   NJD_EVAL_ZXY_ANG
#define FEV_SK    NJD_EVAL_SKIP
#define FEV_SSK   NJD_EVAL_SHAPE_SKIP
#define FEV_CL    NJD_EVAL_CLIP
#define FEV_MD    NJD_EVAL_MODIFIER
#define FEV_QU    NJD_EVAL_QUATERNION
#define FEV_EN    NJD_EVAL_ENVELOPE

/** Flags Blending SRC **/
/* Flag Blending Src */
#define FBS_ZER   NJD_FBS_ZER
#define FBS_ONE   NJD_FBS_ONE
#define FBS_OC    NJD_FBS_OC
#define FBS_IOC   NJD_FBS_IOC
#define FBS_SA    NJD_FBS_SA
#define FBS_ISA   NJD_FBS_ISA
#define FBS_DA    NJD_FBS_DA
#define FBS_IDA   NJD_FBS_IDA

/* Flag Buffer Src SELect */
#define FBS_SEL   NJD_FBS_SEL

/* Flag Blending Dst */
#define FBD_ZER   NJD_FBD_ZER
#define FBD_ONE   NJD_FBD_ONE
#define FBD_OC    NJD_FBD_OC
#define FBD_IOC   NJD_FBD_IOC
#define FBD_SA    NJD_FBD_SA
#define FBD_ISA   NJD_FBD_ISA
#define FBD_DA    NJD_FBD_DA
#define FBD_IDA   NJD_FBD_IDA

/* Flag Buffer Dst SELect */
#define FBD_SEL   NJD_FBD_SEL

/** Flag 'D' Adjust **/
#define FDA_025   NJD_FDA_025
#define FDA_050   NJD_FDA_050
#define FDA_075   NJD_FDA_075
#define FDA_100   NJD_FDA_100
#define FDA_125   NJD_FDA_125
#define FDA_150   NJD_FDA_150
#define FDA_175   NJD_FDA_175
#define FDA_200   NJD_FDA_200
#define FDA_225   NJD_FDA_225
#define FDA_250   NJD_FDA_250
#define FDA_275   NJD_FDA_275
#define FDA_300   NJD_FDA_300
#define FDA_325   NJD_FDA_325
#define FDA_350   NJD_FDA_350
#define FDA_375   NJD_FDA_375

/** Flag EXPonent range : 0-16 **/
#define FEXP_00   NJD_FEXP_00
#define FEXP_01   NJD_FEXP_01
#define FEXP_02   NJD_FEXP_02
#define FEXP_03   NJD_FEXP_03
#define FEXP_04   NJD_FEXP_04
#define FEXP_05   NJD_FEXP_05
#define FEXP_06   NJD_FEXP_06
#define FEXP_07   NJD_FEXP_07
#define FEXP_08   NJD_FEXP_08
#define FEXP_09   NJD_FEXP_09
#define FEXP_10   NJD_FEXP_10
#define FEXP_11   NJD_FEXP_11
#define FEXP_12   NJD_FEXP_12
#define FEXP_13   NJD_FEXP_13
#define FEXP_14   NJD_FEXP_14
#define FEXP_15   NJD_FEXP_15
#define FEXP_16   NJD_FEXP_16

/*------------*/
/* Chunk Tiny */
/*------------*/
/** TexId **/
/* Flag FLip <headbits> */
#define FFL_U    NJD_FFL_U
#define FFL_V    NJD_FFL_V
/* Flag CLamp <headbits> */
#define FCL_U    NJD_FCL_U
#define FCL_V    NJD_FCL_V
/* Flag Filter Mode<texbits> */
#define FFM_PS   NJD_FFM_PS
#define FFM_BF   NJD_FFM_BF
#define FFM_TFA  NJD_FFM_TF_A
#define FFM_TFB  NJD_FFM_TF_B
#define FFM_TF   NJD_FFM_TF_A // Legacy
/* Flag Super Sample<texbits> */
#define FSS      NJD_FSS

/*--------------*/
/* Chunk Vertex */
/*--------------*/
/** Flag WeightStatus (NF only) **/
#define FW_START    NJD_FW_START
#define FW_MIDDLE   NJD_FW_MIDDLE
#define FW_END      NJD_FW_END

/** Flag Vertex **/
#define FV_CONT     NJD_FV_CONT

/* Flag Compact Shape */
#define FV_SHAPE    NJD_FV_SHAPE

/*-------------*/
/* Chunk Strip */
/*-------------*/
/** Flag STrip **/
#define FST_IL   NJD_FST_IL
#define FST_IS   NJD_FST_IS
#define FST_IA   NJD_FST_IA
#define FST_UA   NJD_FST_UA
#define FST_DB   NJD_FST_DB
#define FST_FL   NJD_FST_FL
#define FST_ENV  NJD_FST_ENV

/** UserFlag Offset **/
#define UFO_0    NJD_UFO_0
#define UFO_1    NJD_UFO_1
#define UFO_2    NJD_UFO_2
#define UFO_3    NJD_UFO_3

/*-------*/
/* Chunk */
/*-------*/
/* Chunk */
/* UserFlag Offset and Number of Strips */
#define _NB(_ufo, _ns)             (_ufo)|(_ns)  /* UserFlag Offset and nbStrip */
#define Uf1( _ufo1 )               (_ufo1)
#define Uf2( _ufo1, _ufo2 )        (_ufo1), (_ufo2)
#define Uf3( _ufo1, _ufo2, _ufo3 ) (_ufo1), (_ufo2), (_ufo3)

/* Chunk End */
#define CnkEnd()         (NJD_CE)

/* Chunk Null */
#define CnkNull()        (NJD_CN)

/* Chunk Bits */
#define CnkB_BA( _bits)   (_bits)|NJD_CB_BA      /* Blending Alpha         */
#define CnkB_DA( _bits)   (_bits)|NJD_CB_DA      /* Mipmap 'D' adjust      */
#define CnkB_CP( _bits)   ((_bits)<<8)|NJD_CB_CP /* Cashe polygon list     */
#define CnkB_DP( _bits)   ((_bits)<<8)|NJD_CB_DP /* Draw polygon list      */

/* Chunk Tiny */
#define CnkT_TID( _bits)  (_bits)|NJD_CT_TID     /* Tiny TexId             */
#define _TID( _bits,_tid) (_bits)|(_tid)         /* TexId                  */

/* Chunk Tiny for 2 parameter modifier data */
#define CnkT_TID2( _bits) (_bits)|NJD_CT_TID2    /* Tiny TexId             */

/* Chunk Material */
#define CnkM_D( _bits)    (_bits)|NJD_CM_D       /* Diffuse                */
#define CnkM_S( _bits)    (_bits)|NJD_CM_S       /* Specular               */
#define CnkM_DS( _bits)   (_bits)|NJD_CM_DS      /* Diffuse, Specular      */
#define CnkM_A( _bits)    (_bits)|NJD_CM_A       /* Ambient                */
#define CnkM_DA( _bits)   (_bits)|NJD_CM_DA      /* Diffuse, Ambient       */
#define CnkM_AS( _bits)   (_bits)|NJD_CM_AS      /* Ambient, Specular      */
#define CnkM_DAS( _bits)  (_bits)|NJD_CM_DAS     /* Diff, Abmi, Spec       */

/* Chunk Material for 2 parameter modifier data */
#define CnkM_D2( _bits)   (_bits)|NJD_CM_D2      /* Diffuse                */
#define CnkM_S2( _bits)   (_bits)|NJD_CM_S2      /* Specular               */
#define CnkM_DS2( _bits)  (_bits)|NJD_CM_DS2     /* Diffuse, Specular      */
#define CnkM_A2( _bits)   (_bits)|NJD_CM_A2      /* Ambient                */
#define CnkM_DA2( _bits)  (_bits)|NJD_CM_DA2     /* Diffuse, Ambient       */
#define CnkM_AS2( _bits)  (_bits)|NJD_CM_AS2     /* Ambient, Specular      */
#define CnkM_DAS2( _bits) (_bits)|NJD_CM_DAS2    /* Diff, Abmi, Spec       */

/* Chunk Bump */
#define CnkM_BU(_bits)    NJD_CM_BU              /* bumpmap direction      */

/* Chunk Vertex */
#define _CkV(_f,_s)       (((_s)<<16)|(_f))

#define CnkV(_f,_s)       (_CkV(_f,_s)|NJD_CV)        /* x,y,z, ...               */
#define CnkV_D8(_f,_s)    (_CkV(_f,_s)|NJD_CV_D8)     /* x,y,z,D8888,...          */
#define CnkV_UF(_f,_s)    (_CkV(_f,_s)|NJD_CV_UF)     /* x,y,z,UserFlags32,...    */
#define CnkV_NF(_f,_s)    (_CkV(_f,_s)|NJD_CV_NF)     /* x,y,z,NinjaFlags32,...   */

#define CnkV_VN(_f, _s)   (_CkV(_f,_s)|NJD_CV_VN)     /* x,y,z, ...               */
#define CnkV_VN_D8(_f,_s) (_CkV(_f,_s)|NJD_CV_VN_D8)  /* x,y,z,nx,ny,nz,D8888,... */
#define CnkV_VN_UF(_f,_s) (_CkV(_f,_s)|NJD_CV_VN_UF)  /* x,y,z,nx,ny,nz,UFlags32, */
#define CnkV_VN_NF(_f,_s) (_CkV(_f,_s)|NJD_CV_VN_NF)  /* x,y,z,nx,ny,nz,NFlags32, */

#define CnkV_D8_S8(_f,_s) (_CkV(_f,_s)|NJD_CV_D8_S8)  /* x,y,z,D8888,S8888,...        for Ninja2   */
#define CnkV_NF_D8(_f,_s) (_CkV(_f,_s)|NJD_CV_NF_D8)  /* x,y,z,NinjaFlags32,D8888,... for Ninja2   */

/* Chunk Vertex for CompactShape */
#define CnkVN(_f,_s)      (_CkV(_f,_s)|NJD_VN)        /* nx,ny,nz,...             */
#define CnkVN_D8(_f,_s)   (_CkV(_f,_s)|NJD_VN_D8)     /* nx,ny,nz,D8888,...       */
#define CnkD8(_f,_s)      (_CkV(_f,_s)|NJD_D8)        /* D8888,...                */

#define OffnbIdx( _off, _nb) ((_nb)<<16)|(_off)

/* Chunk vOlume */
#define CnkO_P3(_bits)     NJD_CO_P3 /* volume polygon 3              */
#define CnkO_P4(_bits)     NJD_CO_P4 /* volume polygon 4              */
#define CnkO_ST(_bits)     NJD_CO_ST /* volume strip                  */

/* Chunk Strip */
#define CnkS(_bits)        (_bits)|NJD_CS
#define CnkS_UVN(_bits)    (_bits)|NJD_CS_UVN
#define CnkS_UVH(_bits)    (_bits)|NJD_CS_UVH

#define CnkS_VN(_bits)     (_bits)|NJD_CS_VN
#define CnkS_UVN_VN(_bits) (_bits)|NJD_CS_UVN_VN
#define CnkS_UVH_VN(_bits) (_bits)|NJD_CS_UVH_VN

#define CnkS_D8(_bits)     (_bits)|NJD_CS_D8
#define CnkS_UVN_D8(_bits) (_bits)|NJD_CS_UVN_D8
#define CnkS_UVH_D8(_bits) (_bits)|NJD_CS_UVH_D8

/* Chunk Strip for 2 parameter modifier data */
#define CnkS_2(_bits)      (_bits)|NJD_CS_2
#define CnkS_UVN2(_bits)   (_bits)|NJD_CS_UVN2
#define CnkS_UVH2(_bits)   (_bits)|NJD_CS_UVH2

/************************************************************************
 * COMPACTSHAPE
 ************************************************************************/
#define CSHAPE_LIST_START
#define CSHAPE_LIST_END

#define CVLIST                  NJS_CSHAPECV
#define CSHAPEKGLIST            NJS_CSHAPE_KEYGROUP
#define CSHAPEKG(_e, _g)        (_e), (_g), 0

#define CSHAPELIST              NJS_CSHAPELIST
#define CShapeKgList
#define CShapeNum

#define CSHAPE_MOTION_START
#define CSHAPE_MOTION_END

#define CSHAPE                  NJS_MKEY_SHAPEID
#define CSHAPEDATA              NJS_CSHAPEDATA

 /********************************************************
  * CAMERA
  ********************************************************/
#define CAMERA                  NJS_CAMERA
#define CAMERA_START
#define CAMERA_END

#define CPosition(_x, _y, _z)   (_x), (_y), (_z)
#define CVector(_x, _y, _z)     (_x), (_y), (_z)
#define CTarget(_x, _y, _z)     (_x), (_y), (_z)
#define CRoll(_ang)             ((Sangle)(_KEYVAL*(_ang)))
#define CAngle(_ang)            ((Sangle)(_KEYVAL*(_ang)))
#define CType(_t)               (_t)

  /* Flag Camera Type */
#define FCT_VECTOR              NJD_CTYPE_VECTOR
#define FCT_TARGET              NJD_CTYPE_TARGET

/* Camera Motion */
#define CAMERA_MOTION_START
#define CAMERA_MOTION_END

#define CPOSITION               NJS_MKEY_F
#define CTARGET                 NJS_MKEY_F
#define CVECTOR                 NJS_MKEY_F
#define CROLL                   NJS_MKEY_SA1
#define CANGLE                  NJS_MKEY_SA1

/********************************************************
 * LIGHT
 ********************************************************/
#define LIGHT                   NJS_LIGHT
#define LIGHT_START
#define LIGHT_END

#define LVector(_x, _y, _z)     (_x), (_y), (_z)
#define LPosition(_x, _y, _z)   (_x), (_y), (_z)
#define LColor(_r, _g, _b)      (_r), (_g), (_b)
#define LIntensity(_f)          (_f)
#define LAmbient(_f)            (_f)
#define LNRange(_f)             (_f)
#define LFRange(_f)             (_f)
#define LFunc(_t)               (_t)            /* func type */
#define LType(_t)               (_t)            /* light type */
#define LNoopF(_x, _y, _z)      (_x), (_y), (_z)
#define LNoopF1(_f)             (_f)

 /* Flag Light Func */
#define FLF_UNDEFINE            NJD_MFUNC_UNDEFINE
#define FLF_EASY                NJD_MFUNC_EASY
#define FLF_SIMPLE              NJD_MFUNC_SIMPLE
#define FLF_EASY_MULTI          NJD_MFUNC_EASY_MULTI
#define FLF_SIMPLE_MULTI        NJD_MFUNC_SIMPLE_MULTI

/* Flag Light Type */
#define FLT_POINT               NJD_LTYPE_POINT
#define FLT_VECTOR              NJD_LTYPE_VECTOR
#define FLT_AMBIENT             NJD_LTYPE_AMBIENT

/* Light Motion */
#define LIGHT_MOTION_START
#define LIGHT_MOTION_END

#define LPOSITION               NJS_MKEY_F
#define LVECTOR                 NJS_MKEY_F
#define LCOLOR                  NJS_MKEY_F
#define LINTENSITY              NJS_MKEY_F2
#define LPOINT_FACTORS          NJS_MKEY_F2

/********************************************************
 * CellSprite
 ********************************************************/
 /**** Flag Cell Attr (for attr member) ****/
 /* Flag Blending Src(13-11) */
#define FCS_ZER                 NJD_FCS_ZER
#define FCS_ONE                 NJD_FCS_ONE
#define FCS_OC                  NJD_FCS_OC
#define FCS_IOC                 NJD_FCS_IOC
#define FCS_SA                  NJD_FCS_SA
#define FCS_ISA                 NJD_FCS_ISA
#define FCS_DA                  NJD_FCS_DA
#define FCS_IDA                 NJD_FCS_IDA

/* Flag Blending Dst(10-8) */
#define FCD_ZER                 NJD_FCD_ZER
#define FCD_ONE                 NJD_FCD_ONE
#define FCD_OC                  NJD_FCD_OC
#define FCD_IOC                 NJD_FCD_IOC
#define FCD_SA                  NJD_FCD_SA
#define FCD_ISA                 NJD_FCD_ISA
#define FCD_DA                  NJD_FCD_DA
#define FCD_IDA                 NJD_FCD_IDA

#define FCA_VC                  NJD_FCA_VC         /* vertex color   */
#define FCA_AL                  NJD_FCA_AL         /* use alpha      */
#define FCA_PT                  NJD_FCA_PT         /* punch throw    */
#define FCA_HF                  NJD_FCA_HF         /* h flip         */
#define FCA_VF                  NJD_FCA_VF         /* v flip         */
#define FCA_HI                  NJD_FCA_HI         /* hide           */
#define FCA_TR                  NJD_FCA_TR         /* time repeat    */

/*---------------------------------*/
/* ascii cell sprite format (.spa) */
/*---------------------------------*/
#define CELLSPRITE              NJS_CELL_SPRITE

#define CSPRITE_START
#define CSPRITE_END

#define CELLLISTNAME            NJS_CELL
#define CELLSTART               {
#define CELLEND                 },

#define CellTexId(_tl)          (_tl)
#define CellAttr(_attr)         (_attr)
#define CellOffset(_ox, _oy)    (_ox), (_oy)
#define CellSize(_sx, _sy)      (_sx), (_sy)
#define CellZAng(_ang)          (_NJANG1(_ang) & 0xffff)
#define CellPriority(_cp)       (_cp)
#define CellCenter(_cx, _cy)    (_cx), (_cy)
#define CellVColor0(_a, _r, _g, _b) _ARGB(_a, _r, _g, _b)
#define CellVColor1(_a, _r, _g, _b) _ARGB(_a, _r, _g, _b)
#define CellVColor2(_a, _r, _g, _b) _ARGB(_a, _r, _g, _b)
#define CellVColor3(_a, _r, _g, _b) _ARGB(_a, _r, _g, _b)
#define CellUV0(_u, _v)         (_u), (_v)
#define CellUV2(_u, _v)         (_u), (_v)

#define CellList
#define CellNum
#define CSPosition(_x, _y, _z)  (_x), (_y), (_z)
#define CSZAngle(_z)            _NJANG1(_z)
#define CSScale(_sx, _sy)       (_sx), (_sy)
#define CSDiffuse(_a, _r, _g, _b) (_a), (_r), (_g), (_b)
#define CSSpecular(_e, _r, _g, _b) (_e), (_r), (_g), (_b)

/*---------------------------------*/
/* ascii cell sprite motion (.nam) */
/*---------------------------------*/
#define CSMOTION                NJS_MOTION
#define CSPOSITION              NJS_MKEY_F
#define CSANGLE                 NJS_MKEY_A1
#define CSSCALE                 NJS_MKEY_F2
#define CSCOLOR                 NJS_MKEY_UI32

/*---------------------------------*/
/* ascii cell stream format (.csa) */
/*---------------------------------*/
#define CELLSTREAM              NJS_CELL_STREAM

#define CSTREAM_START
#define CSTREAM_END

#define CELLSTREAMDATA          Sint32

#define CStreamData
#define CSCurrent
#define CSTimeOffset
#define CSTimeMax

/* block bits */
#define FCB_IA0                 NJS_FCB_IA0   /* texId and attr   */
#define FCB_MO1                 NJS_FCB_MO1   /* cell motion      */
#define FCB_PR2                 NJS_FCB_PR2   /* cell proirity    */
#define FCB_CE3                 NJS_FCB_CE3   /* texture center   */
#define FCB_VC4                 NJS_FCB_VC4   /* vertex color     */
#define FCB_UV5                 NJS_FCB_UV5   /* uv               */

/** timestamp      **/

#define CCnk_TE(_time) (NJD_CC_TE|((_time) & 0xffff)) /* time stamp end */

#define TS_L_SHIFT              16
#define TS_L_MASK               0x0fff0000
#define TS_T_MASK               0x0000ffff

#define CCnk_TS(_time, _lsize)                                       \
    (NJD_CC_TS|(((_lsize) << TS_L_SHIFT)&TS_L_MASK)|((_time) & TS_T_MASK))
                                               /* time stamp     */

/** cell           **/
#define CE_L_SHIFT              24
#define CE_L_MASK               0x0f000000
#define CE_H_SHIFT              16
#define CE_EID_MASK             0x0000ffff

#define CCnk_CE(_eid, _lsize, _hbits)                                 \
    (NJD_CC_CE|(((_lsize)<<CE_L_SHIFT)&CE_L_MASK)|(_hbits)|((_eid) & CE_EID_MASK))

/* cell block */
#define IA_T_SHIFT              16
#define IA_T_MASK               0xffff0000
#define IA_A_MASK               0x0000ffff

#define Bk_IA0(_tid, _att)                                            \
    ((((_tid) << IA_T_SHIFT) & IA_T_MASK)|((_att) & IA_A_MASK))

#define MO_Z_SHIFT              16
#define MO_Z1_MASK              0x0000ffff
#define MO_Z2_MASK              0xffff0000
#define MOPR_C_MASK             0x0000ffff
#define Bk_MO1(_cox, _coy, _csx, _csy, _czang)                        \
    (_cox), (_coy), (_csx), (_csy), ((_NJANG1(_czang))&MO_Z1_MASK)
#define Bk_MO1PR2(_cox, _coy, _csx, _csy, _czang, _cp)                \
    (_cox), (_coy), (_csx), (_csy),                                   \
    (((_NJANG1(_czang)<<MO_Z_SHIFT)&MO_Z2_MASK)|((_cp)&MOPR_C_MASK))

#define PR_C_MASK               0x0000ffff

#define Bk_PR2(_cp)               ((_cp)&PR_C_MASK)
#define Bk_CE3(_cx, _cy)          (_cx), (_cy)
#define Bk_VC4_0(_a, _r, _g, _b)  _ARGB(_a, _r, _g, _b)
#define Bk_VC4_1(_a, _r, _g, _b)  _ARGB(_a, _r, _g, _b)
#define Bk_VC4_2(_a, _r, _g, _b)  _ARGB(_a, _r, _g, _b)
#define Bk_VC4_3(_a, _r, _g, _b)  _ARGB(_a, _r, _g, _b)
#define Bk_UV5(_u0, _v0, _u2, _v2) (_u0), (_v0), (_u2), (_v2)

/* Sint16 data */
#define TD_T_MASK               0x0000ffff     /* texId mask */
#define TD_A_MASK               0x0000ffff     /* attr mask  */
#define TD_CZ_MASK              0x0000ffff     /* cz mask    */
#define TD_C_MASK               0x0000ffff     /* cp mask    */
#define TD_SHIFT                16
#define TD_MASK                 0x0fff0000

#define CCnk_TD(_eid, _tid)                                           \
    (NJD_CC_TD|(((_eid)<<TD_SHIFT)&TD_MASK)|((_tid) & TD_T_MASK))
#define CCnk_AT(_eid, _att)                                           \
    (NJD_CC_AT|(((_eid)<<TD_SHIFT)&TD_MASK)|((_att) & TD_A_MASK))
#define CCnk_CZ(_eid, _cz)                                            \
    (NJD_CC_CZ|(((_eid)<<TD_SHIFT)&TD_MASK)|(short)(_NJANG1(_cz) & TD_CZ_MASK))
#define CCnk_CP(_eid, _cp)                                            \
    (NJD_CC_CP|(((_eid)<<TD_SHIFT)&TD_MASK)|((_cp) & TD_C_MASK))

/* user event */
#define UE_E_MASK               0x0000ffff     /* eventId mask */
#define UE_SHIFT                16
#define UE_MASK                 0x0fff0000

#define CCnk_UE(_lsize, _evid)                                        \
    (NJD_CC_UE|(((_lsize)<<UE_SHIFT)&UE_MASK)|((_evid) & UE_E_MASK))

/* cell burst */
#define AD_LS_SHIFT             16
#define AD_LS_MASK              0x0fff0000
#define AD_LA_MASK              0x0000ffff

#define ED_LS_SHIFT             24
#define ED_LS_MASK              0x0f000000
#define ED_OF_SHIFT             16
#define ED_OF_MASK              0x00ff0000
#define ED_ED_MASK              0x0000ffff

#define CBCnk_AD(_laddr, _lsize)                                       \
    (NJD_CBC_AD|(((_lsize)<<AD_LS_SHIFT)&AD_LS_MASK)|((_laddr) & AD_LA_MASK))


#define CBCnk_ED(_eid, _off, _lsize)                                   \
    (NJD_CBC_ED|(((_lsize)<<ED_LS_SHIFT)&ED_LS_MASK)                   \
    |(((_off)<<ED_OF_SHIFT)&ED_OF_MASK)|((_eid)&ED_ED_MASK))

/********************************************************
 * Binary
 ********************************************************/
 /*
  * chunk name
  */
#define iff_NJINFO  'NJIN'     /* data information            */

#define iff_NJCM    'NJCM'     /* ninja chunk model tree      */
#define iff_NJBM    'NJBM'     /* ninja basic model tree      */
#define iff_N2CM    'N2CM'     /* ninja2 chunk model tree     */
#define iff_NJTL    'NJTL'     /* ninja texlist               */
#define iff_NJLI    'NJLI'     /* ninja light                 */
#define iff_NJCA    'NJCA'     /* ninja camera                */

#define iff_NMDM    'NMDM'     /* ninja model motion          */
#define iff_NLIM    'NLIM'     /* ninja light motion          */
#define iff_NCAM    'NCAM'     /* ninja camera motion         */
#define iff_NSSM    'NSSM'     /* ninja simple shape motion   */

#define iff_NJSP    'NJSP'     /* ninja cell sprite           */
#define iff_NJCS    'NJCS'     /* ninja cell stream           */
#define iff_NCSM    'NCSM'     /* ninja cell sprite motion    */

#define iff_NJAD    'NJAD'     /* absolute address            */
#define iff_POF0    'POF0'     /* pointer offset list type 0  */
#define iff_POF1    'POF1'     /* pointer offset list type 1  */

#define iff_CPSM    'CPSM'     /* ninja compact shape motion  */
#define iff_NJSL    'NJSL'     /* ninja compact shape list    */

/*
 * texture chunk name
 */
/* pvr */
#define iff_PVRT    'PVRT'     /* PowerVR texture             */
#define iff_GBIX    'GBIX'     /* globalIndex                 */
#define iff_PVRI    'PVRI'     /* texture Info                */

/* pvm */
#define iff_PVMH    'PVMH'     /* PVM hedder                  */
#define iff_COMM    'COMM'     /* Comment                     */
#define iff_CONV    'CONV'     /* PVM Converter               */
#define iff_MDLN    'MDLN'     /* model name                  */
#define iff_IMGC    'IMGC'     /* Image Container             */

#endif /* _NJDEF_H_ */
