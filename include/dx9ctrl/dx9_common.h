/*
*   dx9ctrl (SA2B) - '/dx9_type.h'
*
*   Description:
*     DirectX 9 control library for SA2PC types header.
*/
#ifndef H_DX9CTRL_TYPE
#define H_DX9CTRL_TYPE

/********************************/
/*  Includes                    */
/********************************/
/****** Std *************************************************************************************/
#include <stdint.h>                 /* std int                                                  */
#include <stdbool.h>                /* std bool                                                 */

/********************************/
/*  Macro                       */
/********************************/
/****** Std *************************************************************************************/
#ifdef __cplusplus
#define DX9_HEADER_START            extern "C" {
#define DX9_HEADER_END              }
#else
#define DX9_HEADER_START
#define DX9_HEADER_END
#endif

DX9_HEADER_START

/********************************/
/*  Base Types                  */
/********************************/
/****** Base Types ******************************************************************************/
typedef int32_t                     dx9_int;        /* standard int                             */
typedef uint32_t                    dx9_uint;       /* standard uint                            */
typedef float                       dx9_float;      /* standard float                           */
typedef int32_t                     dx9_bool;       /* standard boolean                         */
typedef uint32_t                    dx9_flag;       /* flag parameter                           */
typedef uint32_t                    dx9_size;       /* size parameter                           */

/********************************/
/*  Constants                   */
/********************************/
/****** Usage Flags *****************************************************************************/
#define DX9_USAGE_RENDERTARGET      (1<< 0) /* resource will be a render target                 */
#define DX9_USAGE_DEPTHSTENCIL      (1<< 1) /* resource will be a depth stencil buffer          */
#define DX9_USAGE_DYNAMIC           (1<< 9) /* resource requires dynamic memory                 */

#define DX9_USAGE_WRITEONLY         (1<< 3) /* resource won't be read from                      */

#define DX9_USAGE_SWPROCESSING      (1<< 4) /* vertex processing done in software               */
#define DX9_USAGE_DONTCLIP          (1<< 5) /* vertex buffer contents will never be clipped     */
#define DX9_USAGE_POINTS            (1<< 6) /* vertex buffer will draw point sprites            */
#define DX9_USAGE_RTPATCHES         (1<< 7) /* vertex buffer will draw high-order primitives    */
#define DX9_USAGE_NPATCHES          (1<< 8) /* vertex buffer will draw n-patches                */

#define DX9_USAGE_AUTOGENMIPMAP     (1<<10) /* resource will auto-generate mipmaps              */
#define DX9_USAGE_DMAP              (1<<14) /* resource will be a displacement map              */

typedef dx9_flag                    dx9_usage;

/****** Usage Query *****************************************************************************/
#define DX9_USEQUE_LEGACYBUMPMAP    (1<<15) /* resource uses legacy bump map                    */
#define DX9_USEQUE_SRGBREAD         (1<<16) /* resource supports gamma correction during read   */
#define DX9_USEQUE_FILTER           (1<<17) /* resource supports non-point texture filters      */
#define DX9_USEQUE_SRGBWRITE        (1<<18) /* resource supports gamme correction during write  */
#define DX9_USEQUE_POSTPXLSHADER    (1<<19) /* resource supports post shader blending           */
#define DX9_USEQUE_VERTEXTEXTURE    (1<<20) /* resource supports vertex shader texture sampling */
#define DX9_USEQUE_WRAPANDMIP       (1<<21) /* resource supports texture wrap and mipmaps       */

typedef dx9_flag                    dx9_usagequery;

/****** Lock Flags ******************************************************************************/
#define DX9_LOCK_READONLY           (1<< 4) /* buffer is not to be written to                   */
#define DX9_LOCK_NOOVERWRITE        (1<<12) /* won't overwrite data drawn last call             */
#define DX9_LOCK_NOSYSLOCK          (1<<11) /* don't lock the system state during lock          */
#define DX9_LOCK_DISCARD            (1<<13) /* will discard contents of memory                  */
#define DX9_LOCK_DONOTWAIT          (1<<14) /* don't wait for draw to finish, return wait command if not ready */
#define DX9_LOCK_NODIRTYUPDATE      (1<<15) /* don't update dirty region of buffer              */

typedef dx9_flag                    dx9_lock;

/********************************/
/*  Structures                  */
/********************************/
/****** X4 Struct *******************************************************************************/
#pragma warning( push )
#pragma warning( disable : 4201 )   /* nonstandard extension used: nameless struct/union        */

typedef union dx9_float4
{
    struct 
    { 
        dx9_float x, y, z, w; 
    };
    struct 
    { 
        dx9_float r, g, b, a; 
    };
}
dx9_float4;

typedef union dx9_int4
{
    struct 
    { 
        dx9_int x, y, z, w; 
    };
    struct 
    { 
        dx9_int r, g, b, a; 
    };
}
dx9_int4;

#pragma warning( pop )

/****** Rectangle *******************************************************************************/
typedef struct dx9_rect
{
    dx9_int l,t;                    /* top left corner                                          */
    dx9_int r,b;                    /* bottom right corner                                      */
}
dx9_rect;

/****** Pool Flags ******************************************************************************/
typedef enum
{
    DX9_POOL_DEFAULT,
    DX9_POOL_MANAGED,
    DX9_POOL_SYSTEMMEM,
}
dx9_pool;

DX9_HEADER_END

#endif/*H_DX9CTRL_TYPE*/