/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njmotion.h'
*
*   Contains Ninja motion defines, structs, and functions
*
*   Contributors:
*   -   SEGA,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _NJ_MOTION_H_
#define _NJ_MOTION_H_

/*--------------------------------------*/
/*      Motion define                   */
/*--------------------------------------*/
/* motion type bits */

#define NJD_MTYPE_POS_0         BIT_0   /* use NJS_MKEY_F           */
#define NJD_MTYPE_ANG_1         BIT_1   /* use NJS_MKEY_A           */
#define NJD_MTYPE_SCL_2         BIT_2   /* use NJS_MKEY_F           */
#define NJD_MTYPE_VEC_3         BIT_3   /* use NJS_MKEY_F           */
#define NJD_MTYPE_VEC_0         BIT_4   /* use NJS_MKEY_F           */
#define NJD_MTYPE_SANG_1        BIT_5   /* use NJS_MKEY_SA          */
#define NJD_MTYPE_TARGET_3      BIT_6   /* use NJS_MKEY_F           */
#define NJD_MTYPE_ROLL_6        BIT_7   /* use NJS_MKEY_SA1         */
#define NJD_MTYPE_ANGLE_7       BIT_8   /* use NJS_MKEY_SA1         */
#define NJD_MTYPE_RGB_8         BIT_9   /* use NJS_MKEY_F           */
#define NJD_MTYPE_INTENSITY_9   BIT_10  /* use NJS_MKEY_F2          */
#define NJD_MTYPE_POINT_9       BIT_12  /* use NJS_MKEY_F2          */
#define NJD_MTYPE_QUAT_1        BIT_13  /* use NJS_MKEY_QUAT        */
#define NJD_MTYPE_SHAPEID       BIT_14  /* use NJS_MKEY_SHAPEID     *//* compact shape */
#define NJD_MTYPE_EVENT_4       BIT_15  /* use NJS_MKEY_UI16        */

#define NJD_MTYPE_LINER         0x0000  /* use liner                */
#define NJD_MTYPE_SPLINE        0x0040  /* use spline               */
#define NJD_MTYPE_USER          0x0080  /* use user function        */
#define NJD_MTYPE_MASK          0x00c0  /* motion function mask     */



/*    Rotate Type of the return code of njGetMotionNodeData function */
#define NJD_MROT_ANGLEXYZ       0
#define NJD_MROT_ANGLEZXY       1
#define NJD_MROT_QUATERNION     2

/* Motion event flag */
#define NJD_EVENT_HIDE          BIT_0

/*
 * NJS_MOTION
 */
/* key frame animation */
typedef struct {
    Uint32          keyframe;
    Float           key[3];
} NJS_MKEY_F;

typedef struct {
    Uint32          keyframe;
    Angle           key[3];     /* angle                        */
} NJS_MKEY_A;

typedef struct {
    Uint16          keyframe;
    Sangle          key[3];     /* angle                        */
} NJS_MKEY_SA;

typedef struct {
    Uint32          keyframe;
    Angle           angle;      /* angle                        */
    Float           axe[3];     /* axe vector                   */
} NJS_MKEY_AX;

typedef struct
{
    Uint32          keyframe;
    void*           key;        /* pointer                     */
} NJS_MKEY_P;

typedef struct {
    Uint32          keyframe;
    Float           key;
} NJS_MKEY_F1;

typedef struct {
    Uint32          keyframe;
    Float           key[2];
} NJS_MKEY_F2;

typedef struct {
    Uint32          keyframe;
    Float           nrang;
    Float           frang;
    Angle           iang;
    Angle           oang;
} NJS_MKEY_SPOT;

typedef struct {
    Uint32          keyframe;
    Uint32          key;
} NJS_MKEY_UI32;

typedef struct {
    Uint32          keyframe;
    Sint32          key;
} NJS_MKEY_SI32, NJS_MKEY_A1;

typedef struct {
    Uint32          keyframe;
    Float           key[4];
} NJS_MKEY_QUAT;

typedef struct {
    Uint32          keyframe;
    Uint32          shapeId;
} NJS_MKEY_SHAPEID;

typedef struct {
    Uint16          keyframe;
    Sangle          key;
} NJS_MKEY_SA1;

typedef struct {
    Uint16          keyframe;
    Uint16          key;
} NJS_MKEY_UI16;

typedef struct {
    NJS_MKEY_SHAPEID*   keys;
    Uint16              nbKey;
    Uint16              entryId;
} NJS_CSHAPEDATA;

/*
 * NJS_MDATA
 */
/* 1 factor  : pos or ang or scl or shape or vec                 */
typedef struct {
    void*           p[1];       /* factor pointer               */
    Uint32          nb[1];      /* factor count                 */
} NJS_MDATA1;

/* 2 factors : pos and ang, pos and vec(light motion), etc      */
typedef struct {
    void*           p[2];       /* factor pointer               */
    Uint32          nb[2];      /* factor count                 */
} NJS_MDATA2;

/* 3 factors : pos and ang and scl, pos and ang and shape, etc  */
typedef struct {
    void*           p[3];       /* factor pointer               */
    Uint32          nb[3];      /* factor count                 */
} NJS_MDATA3;

/* 4 factors : pos and ang and scl and shape, etc               */
typedef struct {
    void*           p[4];       /* factor pointer               */
    Uint32          nb[4];      /* factor count                 */
} NJS_MDATA4;

/* 5 factors : etc               */
typedef struct {
    void*           p[5];       /* factor pointer               */
    Uint32          nb[5];      /* factor count                 */
} NJS_MDATA5;

typedef struct {
    void*           mdata;      /* NJS_MDATA array              */
    Uint32          nbFrame;    /* frame count                  */
    Uint16          type;       /* motion type  NJD_MTYPE_...   */
    Uint16          inp_fn;     /* interpolation & factor count */
} NJS_MOTION;

typedef struct
{
    NJS_MOTION*     motion[2];      /* motion's pointers */
    Float           frame[2];       /* current frames */
} NJS_MOTION_LINK;


typedef struct {
    NJS_CNK_OBJECT*     object;    /* Object Tree top pointer      */
    NJS_MOTION*         motion;    /* motion                       */
} NJS_ACTION;

typedef struct
{
    NJS_CNK_OBJECT*  object;        /* object's pointer */
    NJS_MOTION_LINK* motionlink;    /* motion-link's pointer */
} NJS_ACTION_LINK;


/*--------------------------------------*/
/*   Compact shape define               */
/*--------------------------------------*/

/*
 * NJS_CSHAPE
 */
/* compact shape animation */
typedef struct {
    Sint32*         cv;         /* chunk vertex pointer         */
} NJS_CSHAPECV;

typedef struct {
    NJS_CSHAPECV*   cvlist;     /* key frame group chunk vertex data */
    Uint16          groupId;    /* key frame group Id           */
    Uint16          reserved;   /* reserved zone                */
} NJS_CSHAPE_KEYGROUP;

typedef struct {
    NJS_CSHAPE_KEYGROUP* shapes;    /* key frame groups         */
    Uint32               nbShape;   /* key frame group count    */
} NJS_CSHAPELIST;


/*--------------------------------------*/
/*   Light & Camera Motion Structure    */
/*--------------------------------------*/

typedef struct {
    NJS_LIGHT*  light;
    NJS_MOTION* motion;
} NJS_LACTION;

typedef struct {
    NJS_CAMERA* camera;
    NJS_MOTION* motion;
} NJS_CACTION;

typedef struct {
    Float*  pos;
    Angle*  ang;
    Float*  scl;
} NJS_MOTION_DATA;

typedef struct {
    Float*  pos;
    Float*  vect;
    Sangle* roll;
    Sangle* ang;
} NJS_CMOTION_DATA;

typedef struct {
    Float*  pos;
    Float*  rgb;
    Float*  rang;
} NJS_LMOTION_DATA;

typedef struct {
    Int          n;
    NJS_LIGHT**  lights;
    NJS_MOTION** motions;
} NJS_MLIGHT_MOTION;

/*  Internal Structures     */
typedef	void	NJF_MOTION_INT_F3_FUNC(const NJS_MKEY_F* key, Uint32 nbkeys, Float frame, Float* dst);
typedef	void	NJF_MOTION_INT_A3_FUNC(const NJS_MKEY_A* key, Uint32 nbkeys, Float frame, Angle* dst);
typedef	void	NJF_MOTION_INT_A1_FUNC(const NJS_MKEY_A1* key, Uint32 nbkeys, Float frame, Angle* dst);
typedef	void	NJF_MOTION_INT_SA3_FUNC(const NJS_MKEY_SA* key, Uint32 nbkeys, Float frame, Sangle* dst);

typedef struct {
    void*       mdata;                  /* NJS_MDATA(n) structure                           */
    int         mdata_nbkeys_ofs;       /* nbkeys offset from NUS_MDATA(n) structure top	*/
    int         mdata_size;             /* sizeof NUS_MDATA(n) structure			        */
    void**      key;                    /* Motion's pointer (mdata->p)                      */
    Uint32*     nbkeys;                 /* array of the number of keyframes (mdata->nb)     */
    Float       frame;                  /* current frame                                    */
    Uint32      nbframes;               /* total number of keyframes                        */
    Uint32      cnt;                    /* array index for NUS_MDATA(n)'s members           */
    Uint32      type;

    NJF_MOTION_INT_F3_FUNC*  int_f3_func_p;     /*  Float * 3   補完関数 */
    NJF_MOTION_INT_A3_FUNC*  int_a3_func_p;     /*	Angle * 3   補完関数 */
    NJF_MOTION_INT_A1_FUNC*  int_a1_func_p;     /*	Angle * 1   補完関数 */
    NJF_MOTION_INT_SA3_FUNC* int_sa3_func_p;    /*	Sangle * 3  補完関数 */

    //	For Object-based motion functions
    int			(*get_pos_func_p)( Float pos[3] );
    int			(*get_ang_func_p)( Angle ang[3] );
    int			(*get_scl_func_p)( Float scl[3] );
} NJS_CUR_MOTION_INFO;

/*        prototype declarations            */

/*
    High level motion functions
*/

#define _nj_cnk_motion_callback_        DataRef(void*, 0x01A55834)

/*  set shape buffer    */
void    njInitShape(void* buf, Sint32 size);
void    njSetShapeList(const NJS_CSHAPELIST* shape_list);
void    njCnkSetMotionCallback(void (*func)(NJS_CNK_OBJECT* obj));
void    njInitShapeLink(void* buf, Sint32 size);
void    njSetShapeLinkList(const NJS_CSHAPELIST* shape_list);

/*	draw motion */
void    njCnkDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame);
void    njCnkDrawMotionLink(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float rate);

/*  get draw motion */
void    njCnkGetDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, NJS_MOTION_DATA* data, Float frame);

/*  camera motion   */
void    njCameraAction(const NJS_CACTION* caction, Float frame);
void    njCameraMotion(const NJS_CAMERA* camera, const NJS_MOTION* motion, Float frame);

/*  get camera motion   */
void    njGetCameraAction(const NJS_CACTION* caction, NJS_CMOTION_DATA* data, Float frame);
void    njGetCameraMotion(const NJS_CAMERA* camera, const NJS_MOTION* motion, NJS_CMOTION_DATA* data, Float frame);

/*  light motion    */
void    njLightAction(Int light_num, const NJS_LACTION* laction, Float frame);
void    njLightMotion(Int light_num, const NJS_LIGHT* light, const NJS_MOTION* motion, Float frame);

/*  get light motion    */
void    njGetLightAction(const NJS_LACTION* laction, NJS_LMOTION_DATA* data, Float frame);
void    njGetLightMotion(const NJS_LIGHT* light, const NJS_MOTION* motion, NJS_LMOTION_DATA* data, Float frame);

/*  multilight motion */
void    njMultiLightMotion(const NJS_MLIGHT_MOTION* mlight, Float frame);

/*
    Low level motion functions
*/

#define _nj_motion_info_        DataAry(NJS_CUR_MOTION_INFO , 0x025EFE60, [2])
#define _nj_motinfo_ptr_        DataRef(NJS_CUR_MOTION_INFO*, 0x025EFE54)

//  motion core
void    njStartMotionEx(const NJS_MOTION* motion, Float frame);
void    njSetNextMotionNodeEx(void);
void    njSetCurMotionInfoSlot(int Slot);

//  object motion
void    njStartMotionObj(const NJS_MOTION* motion, Float frame);
void    njStartMotionObjEx(const NJS_MOTION* motion, Float frame);
int     njGetMotionNodeData(const NJS_CNK_OBJECT* cnkobj, Float pos[3], Angle ang[3], Float scl[3], NJS_QUATERNION* qua);
void    njMotionTransformEx(const NJS_CNK_OBJECT* cnkobj);
void    njChangeMotionObject(NJS_CNK_OBJECT* cnkobj);
Sint32  njGetMotionEventFlag(void);

//  motion link
void    njStartMotionLink(const NJS_MOTION_LINK* motion_link, Float rate);
int     njGetMotionLinkNodeData(const NJS_CNK_OBJECT* cnkobj, Float pos[3], Angle ang[3], Float scl[3], NJS_QUATERNION* qua);
void    njMotionLinkTransformEx(const NJS_CNK_OBJECT* cnkobj);
void    njSetNextMotionLinkNode(void);

//  shape motion
void    njSetCurShapeInfoSlot(int Slot);
void    njStartShapeEx(const NJS_MOTION* shape, Float frame);
void    njSetNextShapeNodeEx(void);
void    njCalcShapeVlist(const NJS_CNK_MODEL* cnkmodel);
void    njGetShapeGroupID(void);
void    njSetShapeVlist(Uint32* vlist, Uint32 vtype);

//  shape link
void    njStartShapeLink(const NJS_MOTION_LINK* shape_link, Float rate);
void    njSetNextShapeLinkNode(void);
void    njCalcShapeLinkVlist(const NJS_CNK_MODEL* cnkmodel);

//  Motion, Shape, MotionLink, ShapeLink with a specified function.
void	njDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame,
    Sint32(*pDrawFunc)(NJS_CNK_MODEL* cnkmodel));

void	njDrawMotionLink(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link,
    Float rate, Sint32(*pDrawFunc)(NJS_CNK_MODEL* cnkmodel));

void    njCnkDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame, Float sframe);
void    njCnkDrawShapeLink(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate);

#endif/*_NJ_MOTION_H_*/
