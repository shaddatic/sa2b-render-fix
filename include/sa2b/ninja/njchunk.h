/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njchunk.h'
*
*   Description:
*     Contains structs and functions for the Ninja Chunk model
*
*   Contributors:
*     - SEGA
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_NJ_CHUNK
#define H_NJ_CHUNK

/************************/
/*  External Headers    */
/************************/
/****** System **********************************************************************/
#include <sa2b/shinobi/sg_xpt.h> /* shinobi types                                   */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/njcommon.h> /* ninja common                                    */

EXTERN_START

/************************/
/*  Chunk Table         */
/************************/
/****** Chunk Offset Bases **********************************************************/
#define NJD_NULLOFF             0 /* null chunk                      (16 bits size) */
#define NJD_BITSOFF             1 /* chunk bits offset               (16 bits size) */
#define NJD_TINYOFF             8 /* chunk tiny offset               (32 bits size) */
#define NJD_MATOFF             16 /* chunk material offset           (32 bits size) */
#define NJD_VERTOFF            32 /* chunk vertex offset             (32 bits size) */
#define NJD_VOLOFF             56 /* chunk volume offset             (32 bits size) */
#define NJD_STRIPOFF           64 /* chunk strip offset                             */
#define NJD_SHAPEOFF          128 /* chunk shape offset                             */
#define NJD_ENDOFF            255 /* end chunk offset                (16 bits size) */

/****** Chunk Type Headers **********************************************************/
#include <sa2b/ninja/njchunk/njcnk_null.h>     /* cnk null                          */
#include <sa2b/ninja/njchunk/njcnk_end.h>      /* cnk end                           */
#include <sa2b/ninja/njchunk/njcnk_bits.h>     /* cnk bits                          */
#include <sa2b/ninja/njchunk/njcnk_tiny.h>     /* cnk tiny                          */
#include <sa2b/ninja/njchunk/njcnk_material.h> /* cnk material                      */
#include <sa2b/ninja/njchunk/njcnk_vertex.h>   /* cnk vertex                        */
#include <sa2b/ninja/njchunk/njcnk_volume.h>   /* cnk volume                        */
#include <sa2b/ninja/njchunk/njcnk_strip.h>    /* cnk strip                         */

/****** UserFlag Offset *************************************************************/
#define NJD_UFO_SHIFT      14

#define NJD_UFO_0         (0<<NJD_UFO_SHIFT)
#define NJD_UFO_1         (1<<NJD_UFO_SHIFT)
#define NJD_UFO_2         (2<<NJD_UFO_SHIFT)
#define NJD_UFO_3         (3<<NJD_UFO_SHIFT)
#define NJD_UFO_MASK      (0x3<<NJD_UFO_SHIFT)

/************************/
/*  Constants           */
/************************/
/****** Object Eval Flags ***********************************************************/
#define NJD_EVAL_UNIT_POS       BIT_0  /* ignore translation                        */
#define NJD_EVAL_UNIT_ANG       BIT_1  /* ignore rotation                           */
#define NJD_EVAL_UNIT_SCL       BIT_2  /* ignore scaling                            */
#define NJD_EVAL_HIDE           BIT_3  /* do not draw model                         */
#define NJD_EVAL_BREAK          BIT_4  /* terminate tracing children                */
#define NJD_EVAL_ZXY_ANG        BIT_5  /* use LightWave rotation order              */
#define NJD_EVAL_SKIP           BIT_6  /* skip object for motion data               */
#define NJD_EVAL_SHAPE_SKIP     BIT_7  /* skip object for shape motion data         */
#define NJD_EVAL_CLIP           BIT_8  /* if the model is clipped, stop tracing object children */
#define NJD_EVAL_MODIFIER       BIT_9  /* object is a modifier volume               */
#define NJD_EVAL_QUATERNION     BIT_10 /* object uses quaternion rotation           */
#define NJD_EVAL_ROTATE_BASE    BIT_11 /* cache rotation data before the object is processed */
#define NJD_EVAL_ROTATE_SET     BIT_12 /* use cached rotation data                  */
#define NJD_EVAL_ENVELOPE       BIT_13 /* ????                                      */
#define NJD_EVAL_MASK           0x3fff 

/************************/
/*  Structures          */
/************************/
/****** Chunk Model *****************************************************************/
typedef struct cnkmdl
{
    Sint32*         vlist;  /* vertex list                                          */
    Sint16*         plist;  /* polygon list                                         */
    NJS_POINT3      center; /* model center                                         */
    Float           r;      /* radius                                               */
}
NJS_CNK_MODEL;

/****** Chunk Object ****************************************************************/
typedef struct cnkobj
{
    Uint32          evalflags;  /* evalation flags                                  */
    NJS_CNK_MODEL*  model;      /* model data pointer                               */
    Float           pos[3];     /* translation                                      */
    Angle           ang[3];     /* rotation or im part of quat                      */
    Float           scl[3];     /* scaling                                          */
    struct cnkobj*  child;      /* child object                                     */
    struct cnkobj*  sibling;    /* sibling object                                   */
    Float           re_quat;    /* re part of quat                                  */
}
NJS_CNK_OBJECT;

/****** Chunk Vertex Buffer *********************************************************/
typedef struct
{
    Float           dmy[16]; /* dummy data                               (size: 64) */
}
NJS_VERTEX_BUF;

/************************/
/*  Game Reference      */
/************************/
/****** Vertex buffer ***************************************************************/
#define _nj_vertex_buf_             DATA_REF(void*, 0x025EFE48)
#define _nj_vertex_buf_num_         DATA_REF(Int  , 0x025EFE4C)

/****** Cnk Blend Mode **************************************************************/
#define _nj_cnk_blend_mode_         DATA_REF(Uint32, 0x025F0264)

/************************/
/*  Prototypes          */
/************************/
/****** Internal Draw ***************************************************************/
/*
*   Description:
*     Set the vertex buffer and vertex buffer count used for Chunk
*
*   Parameters:
*     - vbuf        : vertex buffer to set
*     - vn          : vertex count (64 byte size)
*/
void    njInit3D( NJS_VERTEX_BUF* vbuf, Int vn );

/****** Constant Attr ***************************************************************/
/*
*   Description:
*     Set the Ninja Control 3D flag
*
*   Parameters:
*     - flag        : value to set
*/
void    njControl3D( Uint32 flag );
/*
*   Description:
*     Set the Ninja constant strip flag attributes
*
*   Parameters:
*     - and_attr    : attribute to '&' strip flags with (before OR)
*     - or_attr     : attribute to '|' strip flags with (after AND)
*/
void    njSetConstantAttr( Uint32 and_attr, Uint32 or_attr );
/*
*   Description:
*     Set the Ninja constant material color
*
*   Parameters:
*     - mat         : material color to set
*/
void    njSetConstantMaterial( NJS_ARGB* mat );

/****** Util Functions **************************************************************/
/*
*   Description:
*     Calculate if a model should be clipped using current camera data, current
*   matrix position, and set model radius.
*
*   Parameters:
*     - model       : chunk model
*/
Bool    njCnkModelClip( const NJS_CNK_MODEL* model );
/*
*   Description:
*     Transform and draw every object in an object tree using a specified function.
*
*   Notes:
*     - Called by 'njCnkDrawObject'
*
*   Parameters:
*     - object      : chunk object
*     - callback    : chunk model draw function to use
*/
void    njCnkTransformObject( const NJS_CNK_OBJECT* object, int(__cdecl* callback)(NJS_CNK_MODEL*) );

/****** Internal Draw ***************************************************************/
/*
*   Description:
*     Draw a Chunk model without calling 'BeginDrawModel'. Usually used in object
*   and motion calls.
*
*   Parameters:
*     - model       : chunk model
*/
Sint32  _njCnkDrawModel( const NJS_CNK_MODEL* model );

/****** Begin Draw ******************************************************************/
/*
*   Description:
*     Start Chunk parameters for new draw call
*/
void    njCnkBeginDrawModel( void );

/****** Draw Chunk ******************************************************************/
/*
*   Description:
*     Draw a Chunk model
*
*   Parameters:
*     - model       : chunk model
*/
Sint32  njCnkDrawModel( const NJS_CNK_MODEL* model );
/*
*   Description:
*     Draw a Chunk object tree with the default chunk draw function
*
*   Parameters:
*     - object      : chunk object
*/
void    njCnkDrawObject( const NJS_CNK_OBJECT* object );

/****** Draw Chunk (with cache) *****************************************************/
/*
*   Description:
*     Draw a Chunk model with caching. Can't handle env maps correctly.
*
*   Notes:
*     - Previously 'njCnkDrawModel_Broken'
*     - Introduced for GameCube
*     - Likely a replacement for the older 'njCnkDirectDraw', but operates differently
*
*   Parameters:
*     - model       : chunk model
*/
void    njCnkCacheDrawModel( const NJS_CNK_MODEL* model );

/****** Set Blending Mode ***********************************************************/
/*
*   Description:
*     Set the Chunk blend mode.
*
*   Parameters:
*     - attr        : blend mode attributes
*/
void    njSetCnkBlendMode( Uint32 attr );

EXTERN_END

#endif/*H_NJ_CHUNK*/
