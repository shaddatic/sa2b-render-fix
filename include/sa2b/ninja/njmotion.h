/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njmotion.h'
*
*   Description:
*     Header for Ninja motion and shape motion defintions and functions
*
*   Contributors:
*     - SEGA
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_NJ_MOTION
#define H_NJ_MOTION

/************************/
/*  External Headers    */
/************************/
/****** System **********************************************************************/
#include <sa2b/shinobi/sg_xpt.h> /* shinobi types                                   */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/njcommon.h> /* ninja common                                    */
#include <sa2b/ninja/njchunk.h>  /* ninja chunk                                     */

EXTERN_START

/************************/
/*  Constants           */
/************************/
/****** Motion Type Bits ************************************************************/
#define NJD_MTYPE_POS_0         BIT_0   /* use NJS_MKEY_F                           */
#define NJD_MTYPE_ANG_1         BIT_1   /* use NJS_MKEY_A                           */
#define NJD_MTYPE_SCL_2         BIT_2   /* use NJS_MKEY_F                           */
#define NJD_MTYPE_VEC_3         BIT_3   /* use NJS_MKEY_F                           */
#define NJD_MTYPE_VEC_0         BIT_4   /* use NJS_MKEY_F                           */
#define NJD_MTYPE_SANG_1        BIT_5   /* use NJS_MKEY_SA                          */
#define NJD_MTYPE_TARGET_3      BIT_6   /* use NJS_MKEY_F                           */
#define NJD_MTYPE_ROLL_6        BIT_7   /* use NJS_MKEY_SA1                         */
#define NJD_MTYPE_ANGLE_7       BIT_8   /* use NJS_MKEY_SA1                         */
#define NJD_MTYPE_RGB_8         BIT_9   /* use NJS_MKEY_F                           */
#define NJD_MTYPE_INTENSITY_9   BIT_10  /* use NJS_MKEY_F2                          */
#define NJD_MTYPE_POINT_9       BIT_12  /* use NJS_MKEY_F2                          */
#define NJD_MTYPE_QUAT_1        BIT_13  /* use NJS_MKEY_QUAT                        */
#define NJD_MTYPE_SHAPEID       BIT_14  /* use NJS_MKEY_SHAPEID     (compact shape) */
#define NJD_MTYPE_EVENT_4       BIT_15  /* use NJS_MKEY_UI16                        */

#define NJD_MTYPE_LINER        (0x0000) /* use liner                                */
#define NJD_MTYPE_SPLINE       (0x0040) /* use spline                               */
#define NJD_MTYPE_USER         (0x0080) /* use user function                        */
#define NJD_MTYPE_MASK         (0x00C0) /* motion function mask                     */

/****** Rotation Type ***************************************************************/
/*
*   These are returned by the 'njGetMotionNodeData' function
*/
#define NJD_MROT_ANGLEXYZ      (0) /* ninja angle in xyz order                      */
#define NJD_MROT_ANGLEZXY      (1) /* ninja angle in zxy (lightwave) order          */
#define NJD_MROT_QUATERNION    (2) /* ninja quaternion                              */

/************************/
/*  Structures          */
/************************/
/****** Motion Key Structs **********************************************************/
/*
*     Keyframe animation data structures. Depending on the type attributes of the
*   motion, different structures will be used to represent parts of the animation;
*   for example, a position attribute will use an MKEY_F struct, but an angle
*   attribute will use an MKEY_A struct. Their order in memory fixed to: pos, ang,
*   scl, shape, vec, etc.
*/

typedef struct
{
    Uint32      keyframe;   /* key frame                                            */
    Float       key[3];     /* float 3                                              */
}
NJS_MKEY_F;

typedef struct
{
    Uint32      keyframe;   /* key frame                                            */
    Angle       key[3];     /* angle                                                */
}
NJS_MKEY_A;

typedef struct
{
    Uint16      keyframe;   /* key frame                                            */
    Sangle      key[3];     /* short angle                                          */
}
NJS_MKEY_SA;

typedef struct
{
    Uint32      keyframe;   /* key frame                                            */
    Angle       angle;      /* angle                                                */
    Float       axe[3];     /* axe vector                                           */
}
NJS_MKEY_AX;

typedef struct
{
    Uint32      keyframe;   /* key frame                                            */
    void*       key;        /* pointer                                              */
}
NJS_MKEY_P;

typedef struct
{
    Uint32      keyframe;   /* key frame                                            */
    Float       key;        /* float                                                */
}
NJS_MKEY_F1;

typedef struct
{
    Uint32      keyframe;   /* key frame                                            */
    Float       key[2];     /* float 2                                              */
}
NJS_MKEY_F2;

typedef struct
{
    Uint32      keyframe;   /* key frame                                            */
    Float       nrang;      /* near range                                           */
    Float       frang;      /* far range                                            */
    Angle       iang;       /* ???? angle                                           */
    Angle       oang;       /* ???? angle                                           */
}
NJS_MKEY_SPOT;

typedef struct
{
    Uint32      keyframe;   /* key frame                                            */
    Uint32      key;        /* unsigned int32                                       */
}
NJS_MKEY_UI32;

typedef struct
{
    Uint32      keyframe;   /* key frame                                            */
    Sint32      key;        /* signed int32                                         */
}
NJS_MKEY_SI32, NJS_MKEY_A1;

typedef struct
{
    Uint32      keyframe;   /* key frame                                            */
    Float       key[4];     /* quaternion (im[3], re[1])                            */
}
NJS_MKEY_QUAT;

typedef struct
{
    Uint32      keyframe;   /* key frame                                            */
    Uint32      shapeId;    /* shape id                                             */
}
NJS_MKEY_SHAPEID;

typedef struct
{
    Uint16      keyframe;   /* key frame                                            */
    Sangle      key;        /* short angle                                          */
}
NJS_MKEY_SA1;

typedef struct
{
    Uint16      keyframe;   /* key frame                                            */
    Uint16      key;        /* unsigned int16                                       */
}
NJS_MKEY_UI16;

typedef struct
{
    NJS_MKEY_SHAPEID* keys;     /* key list                                         */
    Uint16            nbKey;    /* key count                                        */
    Uint16            entryId;  /* entry id                                         */
}
NJS_CSHAPEDATA;

/****** Motion Data Structs *********************************************************/
/*
*     Motion data structures. These hold pointers to animation factor keyframes for
*   each object in the object tree being animated. They also store the number of
*   entries in each keyframe list. It is acceptable to use 'nullptr' for the motion
*   key pointers in cases where an object has no animation factors of that type and
*   the keyframe count is zero.
*     The order of the MDATA list is fixed, starting with the parent object, then
*   its children, then its siblings, with the children and siblings following the
*   same order. For example, starting from the top, down:
*
*     - parent
*     |-- child
*     | |-- grandchild
*     | - child's sibling
*     - sibling
*     |-- sibling's child
*/

/*
*   1 factor  : (pos) OR (ang) OR (scl) OR (shape) OR (vec)
*/
typedef struct
{
    void*       p[1];       /* factor pointer                                       */
    Uint32      nb[1];      /* factor count                                         */
}
NJS_MDATA1;
/*
*   2 factors : (pos, ang) OR (pos, vec) etc...
*/
typedef struct
{
    void*       p[2];       /* factor pointer                                       */
    Uint32      nb[2];      /* factor count                                         */
}
NJS_MDATA2;
/*
*   3 factors : (pos, ang, scl) OR (pos, ang, shape) etc...
*/
typedef struct
{
    void*       p[3];       /* factor pointer                                       */
    Uint32      nb[3];      /* factor count                                         */
}
NJS_MDATA3;
/*
*   4 factors : (pos, ang, scl, shape) etc...
*/
typedef struct
{
    void*       p[4];       /* factor pointer                                       */
    Uint32      nb[4];      /* factor count                                         */
}
NJS_MDATA4;
/*
*   5 factors : (pos, ang, scl, shape, vec) etc...
*/
typedef struct
{
    void*       p[5];       /* factor pointer                                       */
    Uint32      nb[5];      /* factor count                                         */
}
NJS_MDATA5;

/****** Motion Structs **************************************************************/
typedef struct
{
    void*           mdata;      /* NJS_MDATA array                                  */
    Uint32          nbFrame;    /* frame count                                      */
    Uint16          type;       /* motion type  NJD_MTYPE_...                       */
    Uint16          inp_fn;     /* interpolation & factor count                     */
}
NJS_MOTION;

typedef struct
{
    NJS_MOTION*     motion[2];      /* motion's pointers                            */
    Float           frame[2];       /* current frames                               */
}
NJS_MOTION_LINK;

/****** Action Structs **************************************************************/
typedef struct
{
    NJS_CNK_OBJECT* object;         /* object pointer                               */
    NJS_MOTION*     motion;         /* motion                                       */
}
NJS_ACTION;

typedef struct
{
    NJS_CNK_OBJECT*  object;        /* object pointer                               */
    NJS_MOTION_LINK* motionlink;    /* motion-link pointer                          */
}
NJS_ACTION_LINK;

/************************/
/*  Internal Types      */
/************************/
/****** Motion Function Types *******************************************************/
typedef	void	NJF_MOTION_INT_F3_FUNC( const NJS_MKEY_F*  key, Uint32 nbkeys, Float frame, Float*  dst);
typedef	void	NJF_MOTION_INT_A3_FUNC( const NJS_MKEY_A*  key, Uint32 nbkeys, Float frame, Angle*  dst);
typedef	void	NJF_MOTION_INT_A1_FUNC( const NJS_MKEY_A1* key, Uint32 nbkeys, Float frame, Angle*  dst);
typedef	void	NJF_MOTION_INT_SA3_FUNC(const NJS_MKEY_SA* key, Uint32 nbkeys, Float frame, Sangle* dst);

/****** Current Object Motion Info **************************************************/
typedef struct
{
    Float* pos_buf_ptr;			/*	_nj_mot_pos_buf_ptr_	                        */
    Float* scl_buf_ptr;			/*	_nj_mot_scl_buf_ptr_	                        */
    Angle* ang_buf_ptr;			/*	_nj_mot_ang_buf_ptr_	                        */

    Sint32(*draw_func_p)(NJS_CNK_MODEL* cnkmdl); /* cnk draw function               */
}
NJS_CUR_OBJMOTION_INFO;

/****** Current Motion Info *********************************************************/
typedef struct
{
    void*       mdata;           /* NJS_MDATA(n) structure                          */
    int         mdata_nbkeys_ofs;/* nbkeys offset from NUS_MDATA(n) structure top   */
    int         mdata_size;      /* sizeof NJS_MDATA(n) structure			        */
    void**      key;             /* Motion's pointer (mdata->p)                     */
    Uint32*     nbkeys;          /* array of the number of keyframes (mdata->nb)    */
    Float       frame;           /* current frame                                   */
    Uint32      nbframes;        /* total number of keyframes                       */
    Uint32      cnt;             /* array index for NJS_MDATA(n)'s members          */
    Uint32      type;            /* mtype attributes of NJS_MDATA(n) structure      */

    NJF_MOTION_INT_F3_FUNC*  int_f3_func_p;  /* Float[3] function                   */
    NJF_MOTION_INT_A3_FUNC*  int_a3_func_p;  /* Angle[3] function                   */
    NJF_MOTION_INT_A1_FUNC*  int_a1_func_p;  /* Angle[1] function                   */
    NJF_MOTION_INT_SA3_FUNC* int_sa3_func_p; /* Sangle[3] function                  */

    /** For GetMotion functions **/
    int     (*get_pos_func_p)( Float pos[3] ); /* get position                      */
    int     (*get_ang_func_p)( Angle ang[3] ); /* get angle                         */
    int     (*get_scl_func_p)( Float scl[3] ); /* get scale                         */
}
NJS_CUR_MOTION_INFO;

/****** Current Motion Link Info ****************************************************/
typedef struct
{
    Float       rate;           /* interpolation rate between motion0 and motion1   */
}
NJS_CUR_MOTIONLINK_INFO;

/****** Current Shape Info **********************************************************/
typedef struct 
{
    void*       mdata;           /* NJS_MDATA(n) structure                          */
    int         mdata_nbkeys_ofs;/* nbkeys offset from NUS_MDATA(n) structure top   */
    int         mdata_size;      /* sizeof NJS_MDATA(n) structure			        */
    void**      key;             /* Motion's pointer (mdata->p)                     */
    Uint32*     nbkeys;          /* array of the number of keyframes (mdata->nb)    */
    Float       frame;           /* current frame                                   */
    Uint32      nbframes;        /* total number of keyframes                       */
    Uint32      cnt;             /* array index for NJS_MDATA(n)'s members          */
    Uint32      type;            /* mtype attributes of NJS_MDATA(n) structure      */
}
NJS_CUR_SHAPE_INFO;

/************************/
/*  Motion Data         */
/************************/
/****** Motion Callback *************************************************************/
#define _nj_cnk_motion_callback_    FUNC_REF(void, __cdecl, (NJS_CNK_OBJECT*), 0x01A55834)

/****** Object Motion Info **********************************************************/
#define _nj_obj_motion_info_    DATA_ARY(NJS_CUR_OBJMOTION_INFO, 0x01D19C00, [2])

/****** Motion Info *****************************************************************/
#define _nj_motion_info_        DATA_ARY(NJS_CUR_MOTION_INFO , 0x025EFE60, [2])
#define _nj_motinfo_ptr_        DATA_REF(NJS_CUR_MOTION_INFO*, 0x025EFE54)

/****** Motion Link Info ************************************************************/
#define _nj_motionlink_info_    DATA_REF(NJS_CUR_MOTIONLINK_INFO, 0x01D19BFC)

/****** Shape VList Buffer **********************************************************/
#define _nj_shape_buf_          DATA_REF(Sint32*, 0x02670540)

/****** Shape Info ******************************************************************/
#define _nj_shape_info_         DATA_ARY(NJS_CUR_SHAPE_INFO , 0x01D19C60, [2])
#define _nj_shpinfo_ptr_        DATA_REF(NJS_CUR_SHAPE_INFO*, 0x01D19C5C)

/****** Shape Link Info *************************************************************/
#define _nj_shapelink_info_     DATA_REF(NJS_CUR_MOTIONLINK_INFO, 0x01D19BF8)

/************************/
/*  Prototypes          */
/************************/
/************************************************************************************/
/*
*   Shape Init
*/

/****** Set Shape Buffer ************************************************************/
/*
*   Description:
*     Init the shape vlist buffer.
*
*   Notes:
*     - The 'size' parameter is unused
*
*   Parameters:
*     - buf     : buffer to use for created shape vlists
*     - size    : size of buffer
*/
void    njInitShape( void* buf, Sint32 size );

/************************************************************************************/
/*
*   Draw Functions
*/

/****** Set Motion Callback *********************************************************/
/*
*   Description:
*     Set motion callback function. This is called just before every object in the
*   tree is drawn, the pointer to the next object to be drawn is the argument sent
*   into the callback.
*
*   Notes:
*     - Ensure to use 'nullptr' after your motions have been drawn
*
*   Parameters:
*     - func        : callback function
*/
void    njCnkSetMotionCallback( void (*func)(NJS_CNK_OBJECT* cnkobj) );

/****** Draw Motion *****************************************************************/
/*
*   Description:
*     Draw a motion with the default Chunk draw function.
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion      : motion data for 'object'
*     - frame       : frame of animation
*/
void    njCnkDrawMotion( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame );
/*
*   Description:
*     Interpolate two motions and draw the result with the default Chunk draw
*   function.
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion_link : motion link data and motion datas for 'object'
*     - rate        : ratio of transition from motion 1 to motion 2 (0~1)
*/
void    njCnkDrawMotionLink( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float rate );

/****** Draw Shape ******************************************************************/
/*
*   Description:
*     Draw a shape motion with the default Chunk draw function.
*
*   Notes:
*     - If 'shape' is 'nullptr', function is the same as 'DrawMotion'
*     - The 'frame' parameter is used for both the motion and shape frame
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion      : motion data for 'object'
*     - shape       : shape data for 'object'   (optional)
*     - frame       : frame of animation/shape
*/
void    njCnkDrawShapeMotion( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame );
/*
*   Description:
*     Interpolate two motions and two shape motion, and draw the result with the
*   default Chunk draw function.
*
*   Notes:
*     - If 'shape_link' is 'nullptr', function is the same as 'DrawMotionLink'
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion_link : motion data for 'object'
*     - shape_link  : shape data for 'object'   (optional)
*     - rate        : ratio of transition from motion/shape 1 to motion/shape 2 (0~1)
*/
void    njCnkDrawShapeMotionLink( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate );

/****** Big Endian Shape ************************************************************/
/*
*   Description:
*     Draw a big endian shape motion with the default Chunk draw function.
*
*   Notes:
*     - If 'shape' is 'nullptr', function is the same as 'DrawMotion'
*     - The 'frame' parameter is used for both the motion and shape frame
*     - The motion data is still little endian, only shape data is endi-swapped
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion      : motion data for 'object'
*     - shape       : shape data for 'object'   (optional)
*     - frame       : frame of animation/shape
*/
void    njCnkDrawShapeMotionBE( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame );
/*
*   Description:
*     Interpolate two motions and two big endian shape motions, and draw the result
*   with the default Chunk draw function.
*
*   Notes:
*     - If 'shape_link' is 'nullptr', function is the same as 'DrawMotionLink'
*     - The motion data is still little endian, only shape data is endi-swapped
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion_link : motion data for 'object'
*     - shape_link  : shape data for 'object'   (optional)
*     - rate        : ratio of transition from motion/shape 1 to motion/shape 2 (0~1)
*/
void    njCnkDrawShapeMotionLinkBE( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate );

/************************************************************************************/
/*
*   Low-Level Functions
*/

/****** Motion Core *****************************************************************/
/*
*   Description:
*     Start parameters inside current motion info.
*
*   Notes:
*     - Called by 'njStartMotionObjEx'
*
*   Parameters:
*     - motion      : motion structure
*     - frame       : animation frame
*/
void    njStartMotionEx( const NJS_MOTION* motion, Float frame );
/*
*   Description:
*     Moves the current motion info node to the next mdata entry.
*
*   Notes:
*     - Called by 'njMotionTransformEx'
*     - For motion link, use 'njSetNextMotionLinkNode'
*/
void    njSetNextMotionNodeEx( void );
/*
*   Description:
*     Set the current motion info slot. There are 2 slots, with each being used in
*   different instances; slot 0 is used for regular motions and motion links, slot 1
*   is only used for the second motion in motion links.
*
*   Notes:
*     - slot is set to 0 after 'njStartMotionObj', 'DrawMotion' funcs,
*       'njStartMotionLink', and 'njMotionLinkTransformEx'
*
*   Parameters:
*     - Slot        : motion info slot to use (0~1)
*/
void    njSetCurMotionInfoSlot( int Slot );

/****** Object Motion ***************************************************************/
/*
*   Description:
*     Start current motion parameters for object motion.
*
*   Notes:
*     - Sets current node to first element in mdata
*
*   Parameters:
*     - motion      : motion structure
*     - frame       : animation frame
*/
void    njStartMotionObj( const NJS_MOTION* motion, Float frame );
/*
*   Description:
*     Start current motion parameters for object motion.
*
*   Notes:
*     - Called by 'njStartMotionObj'
*     - Sets current node to first element in mdata
*
*   Parameters:
*     - motion      : motion structure
*     - frame       : animation frame
*/
void    njStartMotionObjEx( const NJS_MOTION* motion, Float frame );
/*
*   Description:
*     Gets the position, rotation, and scaling information from the current motion
*   node.
*
*   Notes:
*     - Called by 'njMotionTransformEx'
*     - 'ang' and 'qua' are mutually exclusive. If the motion uses quats, then only
*       'qua' will be returned
*
*   Parameters:
*     - cnkobj      : current node object
*     - pos         : result position
*     - ang         : result ang        (if applicable)
*     - scl         : result scl
*     - qua         : result quaternion (if applicable)
*
*   Returns:
*     Rotation type as defined by 'NJD_MROT' constants
*/
int     njGetMotionNodeData( const NJS_CNK_OBJECT* cnkobj, Float (*pos)[3], Angle (*ang)[3], Float (*scl)[3], NJS_QUATERNION* qua );
/*
*   Description:
*     Transforms the current matrix by the current motion node.
*
*   Parameters:
*     - cnkobj      : current node object
*/
void    njMotionTransformEx( const NJS_CNK_OBJECT* cnkobj );

/****** Motion Link *****************************************************************/
/*
*   Description:
*     Start current motion parameters for motion link.
*
*   Notes:
*     - Sets current nodes to first element in mdatas
*
*   Parameters:
*     - motion_link : motion link structure
*     - rate        : ratio of transition from motion 1 to motion 2 (0~1)
*/
void    njStartMotionLink( const NJS_MOTION_LINK* motion_link, Float rate );
/*
*   Description:
*     Gets the position, rotation, and scaling information from the interpolated
*   current motion link nodes.
*
*   Notes:
*     - Called by 'njMotionLinkTransformEx'
*     - 'ang' is unused. Motions using Ninja angles will be converted to quat for
*       interpolation and returned as quat
*
*   Parameters:
*     - cnkobj      : current node object
*     - pos         : result position
*     - ang         : result ang        (not used)
*     - scl         : result scl
*     - qua         : result quaternion
*
*   Returns:
*     Rotation type as defined by 'NJD_MROT' constants, always 'QUATERNION'
*/
int     njGetMotionLinkNodeData( const NJS_CNK_OBJECT* cnkobj, Float (*pos)[3], Angle (*ang)[3], Float (*scl)[3], NJS_QUATERNION* qua );
/*
*   Description:
*     Transforms the current matrix by the interpolated current motion link nodes.
*
*   Parameters:
*     - cnkobj      : current node object
*/
void    njMotionLinkTransformEx( const NJS_CNK_OBJECT* cnkobj );
/*
*   Description:
*     Moves the current motion link nodes to the next mdata entries.
*/
void    njSetNextMotionLinkNode( void );

/****** Shape Motion *****************************************************************/
/*
*   Description:
*     Start current shape info parameters for shape motion.
*
*   Notes:
*     - Sets current node to first element in mdata
*
*   Parameters:
*     - motion      : shape motion
*     - frame       : animation frame
*/
void    njStartShapeEx( const NJS_MOTION* shape, Float frame );
/*
*   Description:
*     Moves the current shape info node to the next mdata entry.
*
*   Notes:
*     - Called by 'njMotionTransformEx'
*     - For motion link, use 'njSetNextShapeLinkNode'
*/
void    njSetNextShapeNodeEx( void );
/*
*   Description:
*     Set the current shape info slot. There are 2 slots, with each being used in
*   different instances; slot 0 is used for regular shape motions and shape links,
*   slot 1 is only used for the second shape motion in shape links.
*
*   Parameters:
*     - Slot        : motion info slot to use (0~1)
*/
void    njSetCurShapeInfoSlot( int Slot );

/****** Shape Link *****************************************************************/
/*
*   Description:
*     Start current shape info parameters for motion link.
*
*   Notes:
*     - Sets current nodes to first element in mdatas
*
*   Parameters:
*     - motion_link : shape link structure
*     - rate        : ratio of transition from shape 1 to shape 2 (0~1)
*/
void    njStartShapeLink( const NJS_MOTION_LINK* shape_link, Float rate );
/*
*   Description:
*     Moves the current shape link nodes to the next mdata entries.
*/
void    njSetNextShapeLinkNode( void );

/************************************************************************************/
/*
*   Draw Functions with Specified Function
*/

/****** Draw Motion *****************************************************************/
/*
*   Description:
*     Draw a motion with a specified chunk draw function.
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion      : motion data for 'object'
*     - frame       : frame of animation
*     - pDrawFunc   : chunk draw function
*/
void	njDrawMotion( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame, Sint32(*pDrawFunc)(NJS_CNK_MODEL* cnkmodel) );
/*
*   Description:
*     Interpolate two motions and draw the result with a specified chunk draw
*   function.
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion_link : motion link data and motion datas for 'object'
*     - rate        : ratio of transition from motion 1 to motion 2 (0~1)
*     - pDrawFunc   : chunk draw function
*/
void	njDrawMotionLink( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float rate, Sint32(*pDrawFunc)(NJS_CNK_MODEL* cnkmodel) );

/****** Draw Shape ******************************************************************/
/*
*   Description:
*     Draw a shape motion with a specified chunk draw function.
*
*   Notes:
*     - If 'shape' is 'nullptr', function is the same as 'DrawMotion'
*     - Does not call the motion callback, removed for Battle
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion      : motion data for 'object'
*     - shape       : shape data for 'object'   (optional)
*     - frame       : frame of animation
*     - sframe      : frame of shape
*     - pDrawFunc   : chunk draw function
*/
void	njDrawShapeMotion( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame, Float sframe, Sint32(*pDrawFunc)(NJS_CNK_MODEL* cnkmodel) );
/*
*   Description:
*     Interpolate two motions and two shape motions, and draw the result with a
*   specified chunk draw function.
*
*   Notes:
*     - If 'shape_link' is 'nullptr', function is the same as 'DrawMotionLink'
*     - Does not call the motion callback, removed for Battle
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion_link : motion data for 'object'
*     - shape_link  : shape data for 'object'   (optional)
*     - rate        : ratio of transition from motion/shape 1 to motion/shape 2 (0~1)
*     - pDrawFunc   : chunk draw function
*/
void	njDrawShapeLink( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate, Sint32(*pDrawFunc)(NJS_CNK_MODEL* cnkmodel) );

/****** Big Endian Shape ************************************************************/
/*
*   Description:
*     Draw a big endian shape motion with a specified chunk draw function.
*
*   Notes:
*     - If 'shape' is 'nullptr', function is the same as 'DrawMotion'
*     - The motion data is still little endian, only shape data is endi-swapped
*     - Does not call the motion callback, removed for Battle
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion      : motion data for 'object'
*     - shape       : shape data for 'object'   (optional)
*     - frame       : frame of animation
*     - sframe      : frame of shape
*     - pDrawFunc   : chunk draw function
*/
void	njDrawShapeMotionBE( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame, Float sframe, Sint32(*pDrawFunc)(NJS_CNK_MODEL* cnkmodel) );
/*
*   Description:
*     Interpolate two motions and two big endian shape motions, and draw the result
*   with a specified chunk draw function.
*
*   Notes:
*     - If 'shape_link' is 'nullptr', function is the same as 'DrawMotionLink'
*     - The motion data is still little endian, only shape data is endi-swapped
*     - Does not call the motion callback, removed for Battle
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion_link : motion data for 'object'
*     - shape_link  : shape data for 'object'   (optional)
*     - rate        : ratio of transition from motion/shape 1 to motion/shape 2 (0~1)
*     - pDrawFunc   : chunk draw function
*/
void    njDrawShapeLinkBE( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate, Sint32(*pDrawFunc)(NJS_CNK_MODEL* cnkmodel) );

EXTERN_END

#endif/*H_NJ_MOTION*/
