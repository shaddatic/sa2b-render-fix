/*
*   dx9ctrl (SA2B) - '/dx9_renderstate.h'
*
*   Description:
*     DirectX 9 control library for SA2PC render state header.
*/
#ifndef H_DX9CTRL_RENDERSTATE
#define H_DX9CTRL_RENDERSTATE

/********************************/
/*  Includes                    */
/********************************/
/****** DX9 Control *****************************************************************************/
#include <dx9ctrl/dx9_common.h>         /* dx9 common                                           */

DX9_HEADER_START

/********************************/
/*  Basic Types                 */
/********************************/
/****** Write Color *****************************************************************************/
typedef dx9_flag                    dx9_writecolor;

/********************************/
/*  Constants                   */
/********************************/
/****** Color Write Flags ***********************************************************************/
#define DX9_WCOL_NONE               (0b0000'0000) /* no color write                             */
#define DX9_WCOL_ALL                (0b0000'1111) /* write all                                  */

#define DX9_WCOL_RED                (0b0000'0001) /* write red bit                              */
#define DX9_WCOL_GREEN              (0b0000'0010) /* write green bit                            */
#define DX9_WCOL_BLUE               (0b0000'0100) /* write blue bit                             */
#define DX9_WCOL_ALPHA              (0b0000'1000) /* write alpha bit                            */

/********************************/
/*  Enums                       */
/********************************/
/****** Common **********************************************************************************/
typedef enum
{
    DX9_CMP_ERROR = -1,             /* error return value                                       */

    DX9_CMP_NVR = 1,                /* never                                                    */
    DX9_CMP_LSS,                    /* less                                                     */
    DX9_CMP_EQU,                    /* equal                                                    */
    DX9_CMP_LEQ,                    /* less or equal                                            */
    DX9_CMP_GTR,                    /* greater                                                  */
    DX9_CMP_NEQ,                    /* not equal                                                */
    DX9_CMP_GEQ,                    /* greater or equal                                         */
    DX9_CMP_ALW,                    /* always                                                   */
}
dx9_compare_op;

/****** Shading Mode ****************************************************************************/
typedef enum dx9_shade_mode
{
    DX9_SHADE_ERROR = -1,           /* error return value                                       */

    DX9_SHADE_FLAT = 1,             /* first vertex color/normal is used for entire face        */
    DX9_SHADE_GOURAUD,              /* colors/normals are interpolated across the face          */

    DX9_SHADE_PHONG,                /* use phong shading for fixed function lighting            */
}
dx9_shade_mode;

/****** Stencil operations **********************************************************************/
typedef enum
{
    DX9_STCL_ERROR = -1,            /* error return value                                       */

    DX9_STCL_KEEP = 1,              /* keep                                                     */
    DX9_STCL_ZERO,                  /* set to zero                                              */
    DX9_STCL_REPL,                  /* replace                                                  */
    DX9_STCL_INCR_CLMP,             /* increment with clamp                                     */
    DX9_STCL_DECR_CLMP,             /* decrement with clamp                                     */
    DX9_STCL_INVT,                  /* invert                                                   */
    DX9_STCL_INCR,                  /* increment                                                */
    DX9_STCL_DECR,                  /* decrement                                                */
}
dx9_stencil_op;

/****** Blending operations *********************************************************************/
typedef enum
{
    DX9_BLND_ERROR = -1,            /* error return value                                       */
    
    DX9_BLND_ZERO = 1,              /* zero                                                     */
    DX9_BLND_ONE,                   /* one                                                      */
    DX9_BLND_SRCCOLOR,              /* source color                                             */
    DX9_BLND_INVSRCCOLOR,           /* inverse source color                                     */
    DX9_BLND_SRCALPHA,              /* source alpha                                             */
    DX9_BLND_INVSRCALPHA,           /* inverse source alpha                                     */
    DX9_BLND_DESTALPHA,             /* destination alpha                                        */
    DX9_BLND_INVDESTALPHA,          /* inverse destination alpha                                */
    DX9_BLND_DESTCOLOR,             /* destination color                                        */
    DX9_BLND_INVDESTCOLOR,          /* inverse destination color                                */
    DX9_BLND_SRCALPHASAT,           /* source alpha saturated                                   */
    DX9_BLND_BOTHSRCALPHA,          /* obsolete                                                 */
    DX9_BLND_BOTHINVSRCALPHA,       /* obsolete                                                 */
    DX9_BLND_BLENDFACTOR,           /* blend factor                                             */
    DX9_BLND_INVBLENDFACTOR,        /* inverse blend factor                                     */
    DX9_BLND_SRCCOLOR2,             /* source color 2, DX9Ex only                               */
    DX9_BLND_INVSRCCOLOR2,          /* inverse source color 2, DX9Ex only                       */
}
dx9_blend_op;

/****** Triangle Culling ************************************************************************/
typedef enum dx9_cull_mode
{
    DX9_CULL_ERROR = -1,            /* error return value                                       */

    DX9_CULL_NONE = 1,              /* cull no triangles                                        */
    DX9_CULL_CW,                    /* cull clock-wise triangles                                */
    DX9_CULL_CCW,                   /* cull counter-clock-wise triangles                        */
}
dx9_cull_mode;

/********************************/
/*  Prototypes                  */
/********************************/
/****** Shading Mode ****************************************************************************/
/*
*   Description:
*     Set the triangle shading interpolation mode.
*
*   Parameters:
*     - mode        : triangle shading mode
* 
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetShadingMode( dx9_shade_mode mode );

/****** Z Buffer ********************************************************************************/
/*
*   Description:
*     Enable/disable Z buffering.
*
*   Parameters:
*     - state       : z buffer state
* 
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetZEnable( dx9_bool state );
/*
*   Description:
*     Enable/disable Z buffer write.
*
*   Parameters:
*     - state       : z write state
* 
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetZWrite( dx9_bool state );
/*
*   Description:
*     Set Z compare function.
*
*   Parameters:
*     - op          : z compare operation
* 
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetZFunc( dx9_compare_op op );

/****** Stencil Buffer **************************************************************************/
/*
*   Description:
*     Enable/disable the stencil buffer.
*
*   Parameters:
*     - state       : stencil buffer state
*
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetStencilEnable( dx9_bool state );
/*
*   Description:
*     Enable/disable two sided stencil mode. When enabled, the vertex buffer will be
*   drawn twice on the GPU; a CW pass and a CCW pass. This avoids the need and 
*   performance loss of handling it manually.
*     The CW pass will use the regular stencil operations, the CCW pass will use the
*   'CCW' variants of stencil operations.
*
*   Parameters:
*     - state       : two sided stencil state
*
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetStencilTwoSided( dx9_bool state );
/*
*   Description:
*     Set stencil compare function. The format of the test is: 'REF CMP VAL'
*
*   Parameters:
*     - op          : stencil compare operation
*
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetStencilFunc( dx9_compare_op op );
/*
*   Description:
*     Set stencil compare reference.
*
*   Parameters:
*     - value       : stencil reference value                                           [0~255]
*
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetStencilRef( dx9_uint value );
/*
*   Description:
*     Set stencil operations for CW triangles in the case of a stencil test fail, Z
*   test fail, and a stencil test pass.
*
*   Parameters:
*     - op          : stencil operation
*
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetStencilFail(  dx9_stencil_op op );
bool    DX9_SetStencilZFail( dx9_stencil_op op );
bool    DX9_SetStencilPass(  dx9_stencil_op op );
/*
*   Description:
*     Set stencil operations for CCW triangles in the case of a stencil test fail, Z
*   test fail, and a stencil test pass.
*
*   Parameters:
*     - op          : stencil operation
*
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetStencilFailCCW(  dx9_stencil_op op );
bool    DX9_SetStencilZFailCCW( dx9_stencil_op op );
bool    DX9_SetStencilPassCCW(  dx9_stencil_op op );
/*
*   Description:
*     Set stencil read and write value mask.
* 
*   Notes:
*     - Read:  (REF & MASK) CMP (VAL & MASK)
*     - Write: VAL = (VAL & ~MASK) | (NEWVAL & MASK)
*
*   Parameters:
*     - op          : stencil operation                                                 [0~255]
*
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetStencilReadMask(  dx9_uint mask );
bool    DX9_SetStencilWriteMask( dx9_uint mask );

/****** Color Write *****************************************************************************/
/*
*   Description:
*     Set color write bits.
* 
*   Parameters:
*     - flags       : color write bits                                           [DX9_WCOL_###]
*
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetColorWrite( dx9_writecolor flags );

/****** Color Blending **************************************************************************/
/*
*   Description:
*     Enable/disable alpha blending.
* 
*   Parameters:
*     - state       : alpha blending state
* 
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetAlphaBlendEnable( dx9_bool state );
/*
*   Description:
*     Set source and destination blending operations.
* 
*   Parameters:
*     - op          : color blending operation
* 
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetSrcBlend( dx9_blend_op op );
bool    DX9_SetDstBlend( dx9_blend_op op );

/****** Alpha Test ******************************************************************************/
/*
*   Description:
*     Set alpha test compare function
* 
*   Parameters:
*     - op          : alpha test compare operation
* 
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetAlphaFunc( dx9_compare_op op );

/****** Triangle Culling ************************************************************************/
/*
*   Description:
*     Set triangle culling mode
* 
*   Parameters:
*     - mode        : triangle culling mode
* 
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetFaceCulling( dx9_cull_mode mode );

/****** Point Primitive *************************************************************************/
/*
*   Description:
*     Set point primitive size in pixels.
* 
*   Parameters:
*     - size       : point primitive size
* 
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetPointSize( dx9_float size );
/*
*   Description:
*     Enable/disable point primitive scaling depending on distance.
* 
*   Parameters:
*     - state       : point scaling state
* 
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetPointScaleEnable( dx9_bool state );

DX9_HEADER_END

#endif/*H_DX9CTRL_RENDERSTATE*/