/*
*   SA2 Render Fix - '/rf_draw/rfd_cnkmdl/rfdcnk_internal.h'
*
*   Description:
*     Internal header for CnkDraw module.
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_DRAW_CNKMDL_INTERNAL
#define H_RF_DRAW_CNKMDL_INTERNAL

/********************************/
/*  Includes                    */
/********************************/
/****** Self ************************************************************************************/
#include <rf_ninja/rj_internal.h>   /* grand parent                                            */
#include <rf_ninja/rj_cnk.h>        /* parent util                                             */

EXTERN_START

/********************************/
/*  Constants                   */
/********************************/
/****** Chunk Control Shifts ********************************************************************/
#define RJD_CNK_CTRL_SHIFT_DRAW     ( 0)
#define RJD_CNK_CTRL_SHIFT_CULL     ( 2)
#define RJD_CNK_CTRL_SHIFT_MODEL    ( 4)
#define RJD_CNK_CTRL_SHIFT_VTX      ( 8)
#define RJD_CNK_CTRL_SHIFT_EFFECT   (12)

/****** Chunk conteXt Flag **********************************************************************/
#define RJD_CXF_BACKFACECULL        (1<<0) /* uses simple inverted polygon calcs                */
#define RJD_CXF_AMBIMATERIAL        (1<<1) /* read ambient material color                       */
#define RJD_CXF_VND8                (1<<2) /* use vertex color/light blending                   */
#define RJD_CXF_NONTEXSPEC          (1<<3) /* notex specular                                    */
#define RJD_CXF_TWOPASSLIGHT        (1<<4) /* use two pass lighting                             */

/****** Chunk Material Flag *********************************************************************/
#define RJD_CMF_DIFF                (1<<0)
#define RJD_CMF_AMBI                (1<<1)
#define RJD_CMF_SPEC                (1<<2)

/****** Chunk Strip Flags ***********************************************************************/
/*
*   Strip Flag Type Masks
*/
#define RJD_CSF_MASK_TYPE           (0x000000FF) /* chunk offset type                           */
#define RJD_CSF_MASK_FST            (0x0000FF00) /* chunk strip flags                           */
#define RJD_CSF_MASK_CTX            (0xFFFF0000) /* chunk strip context                         */
/*
*   Strip Flag Type Shifts
*/
#define RJD_CSF_SHIFT_TYPE          (0)             /* chunk offset type                        */
#define RJD_CSF_SHIFT_FST           (NJD_FST_SHIFT) /* chunk strip flags                        */
#define RJD_CSF_SHIFT_CTX           (16)            /* chunk strip context                      */
/*
*   Strip 'FST' Flags
*/
#define RJD_FST_TRANSLUCENT         (NJD_FST_UA|RJD_FST_EUA) /* translucent flags               */
/*
*   Strip Context Flags
*/
#define RJD_CSF_USETEX              (1<<(RJD_CSF_SHIFT_CTX+0)) /* strip will use a texture      */
#define RJD_CSF_USEOFF              (1<<(RJD_CSF_SHIFT_CTX+1)) /* use offset color              */
#define RJD_CSF_HASUVS              (1<<(RJD_CSF_SHIFT_CTX+2)) /* strip has uv 'UVN/UVH' data   */
#define RJD_CSF_HASNRM              (1<<(RJD_CSF_SHIFT_CTX+3)) /* strip has normal 'VN' data    */
#define RJD_CSF_HASCOL              (1<<(RJD_CSF_SHIFT_CTX+4)) /* strip has color 'D8' data     */

/****** Chunk Vertex (Flags/Type) ***************************************************************/
/*
*   Vertex Attribute Flags
*/
#define RJD_CVF_NORMAL              (1<<0) /* has vertex normals                                */
#define RJD_CVF_COLOR               (1<<1) /* has vertex colors                                 */
#define RJD_CVF_SPECULAR            (1<<2) /* has vertex offset color                           */
/*
*   Vertex Types
*/
#define RJD_CVT_P                   (0)                              /* position                */
#define RJD_CVT_PN                  (RJD_CVF_NORMAL)                 /* pos + normals           */
#define RJD_CVT_PC                  (RJD_CVF_COLOR)                  /* pos + color             */
#define RJD_CVT_PNC                 (RJD_CVF_NORMAL|RJD_CVF_COLOR)   /* pos + nrm + col         */
#define RJD_CVT_PCS                 (RJD_CVF_COLOR|RJD_CVF_SPECULAR) /* pos + col + specular    */

/********************************/
/*  Function Types              */
/********************************/
/****** Color Calculations **********************************************************************/
typedef Uint32 (RJF_CNK_VCOLFUNC)(const RJS_VERTEX_BUF* restrict pVtx);
typedef Uint32 (RJF_CNK_SPECFUNC)(const RJS_VERTEX_BUF* restrict pVtx);

/****** Obj/Mdl Callbacks ***********************************************************************/
typedef void (RJF_CNK_OBJ)(NJS_CNK_OBJECT* object);
typedef void (RJF_CNK_MDL)(NJS_CNK_MODEL*  model);

/****** Plist Callbacks *************************************************************************/
typedef Sint16 (RJF_CNK_PLIST_TNUM)(Sint16 n);
typedef Uint32 (RJF_CNK_PLIST_MCOL)(NJS_BGRA* dst, const NJS_BGRA* src, Uint32 flag);

/********************************/
/*  Enums                       */
/********************************/
/****** Vertex Color Functions ******************************************************************/
typedef enum rjcnkvcolmd
{
    RJE_CNK_VCOLFUNC_MATERIAL,
    RJE_CNK_VCOLFUNC_D8,
    RJE_CNK_VCOLFUNC_LIGHT,
    RJE_CNK_VCOLFUNC_LIGHTD8,

    NB_RJE_CNK_VCOLFUNC,
}
RJE_CNK_VCOLFUNC;

/****** Specular Functions **********************************************************************/
typedef enum rjcnkspecmd
{
    RJE_CNK_SPECFUNC_NONE,

    RJE_CNK_SPECFUNC_NORMAL,
    RJE_CNK_SPECFUNC_EASY,
    RJE_CNK_SPECFUNC_SIMPLE,
    RJE_CNK_SPECFUNC_MULTI,
    RJE_CNK_SPECFUNC_S8,

    NB_RJE_CNK_SPECFUNC,
}
RJE_CNK_SPECFUNC;

/****** Depth Queue Mode ************************************************************************/
typedef enum rjcnkdq
{
    RJ_CNK_DQ_OFF,                  /* depthqueue is disabled                                   */
    RJ_CNK_DQ_NEAR,                 /* depthqueue is on, but behind near plane                  */
    RJ_CNK_DQ_ON,                   /* depthqueue is enabled                                    */
}
RJ_CNK_DEPTHQUEUE;

/****** Depth Queue Mode ************************************************************************/
typedef enum rjcnkmat
{
    RJ_CMC_DIFF,                    /* diffuse material color                                   */
    RJ_CMC_AMBI,                    /* ambient material color                                   */
    RJ_CMC_SPEC,                    /* specular material color                                  */

    RJ_NB_CMC,                      /* enum count                                               */
}
RJ_CNK_MATCOLOR;

/********************************/
/*  Game Structures             */
/********************************/
/****** Chunk Context ***************************************************************************/
typedef struct rjcnkctx
{
    Sint32          func;           /* draw function                                            */
    Uint16          flag;           /* context flags                                            */
    Uint16          vattr;          /* vertex attributes                                        */
    Sint16          cull;           /* last culling mode                                        */
    Sint16          texid;          /* last texture id                                          */
    CNK_TINY_HEAD   tiny;           /* last texture material                                    */
    Sint16          spec;           /* specular mode                                            */
    Sint16          depthq;         /* depth queue mode                                         */
}
RJS_CNK_CTX;

typedef struct rjcnkstrip
{
    Uint32                flag;            /* strip flags                                       */
    Sint16                blend;           /* alpha blend mode                                  */
    Sint16                texid;           /* texture id                                        */
    CNK_TINY_HEAD         tiny;            /* texture material                                  */
    NJS_BGRA              mats[RJ_NB_CMC]; /* material colors                                   */
    const CNK_STRIP_HEAD* striph;          /* strip header pointer                              */
    Uint32                pad32;
}
RJS_CNK_STRIP;

/********************************/
/*  Game References             */
/********************************/
/****** Texture *********************************************************************************/
#define pTexSurface                     DATA_REF(const NJS_TEXSURFACE*, 0x01A55840)

/****** Old Strip Flag for Lighting *************************************************************/
#define _nj_cnk_strip_flags_            DATA_REF(Uint32, 0x01A5583C)
#define _nj_cnk_last_strip_flags_       DATA_REF(Uint32, 0x01A55838)

/****** Chunk Polygon cache list ****************************************************************/
#define _nj_cnk_polygon_cache_num_      DATA_REF(Sint32       , 0x025F0108)
#define _nj_cnk_polygon_cache_tbl_      DATA_ARY(const Sint16*, 0x02670340, [125])

/****** Chunk Vertex Attributes *****************************************************************/
#define _nj_cnk_vtx_attrs_              DATA_REF(Sint32, 0x019346DC)

/****** Use Basic Draw for Shadows **************************************************************/
#define ShadowCnkDraw                   DATA_REF(b32, 0x01A55798)

/********************************/
/*  Data                        */
/********************************/
/****** Chunk Control ***************************************************************************/
EXTERN Uint32 _rj_cnk_ctrl_flag_;       /* control flags                                        */

/****** Chunk Draw ******************************************************************************/
EXTERN RJS_CNK_CTX _rj_cnk_context_;    /* chunk global context                                 */

EXTERN NJS_BGRA _rj_cnk_default_material_[RJ_NB_CMC]; /* chunk default materials                */

EXTERN NJS_ARGB _rj_cnk_diff_material_; /* diffuse material                                     */
EXTERN NJS_ARGB _rj_cnk_ambi_material_; /* ambient material                                     */
EXTERN NJS_ARGB _rj_cnk_spec_material_; /* specular material                                    */

EXTERN Sint32   _rj_cnk_shadow_tex_;    /* shadow tex count                                     */

EXTERN RJF_CNK_VCOLFUNC* _rj_cnk_vcol_funcs_[NB_RJE_CNK_VCOLFUNC]; /* vcol funcs                */
EXTERN RJF_CNK_SPECFUNC* _rj_cnk_spec_funcs_[NB_RJE_CNK_SPECFUNC]; /* spec funcs                */

/****** UV Scroll *******************************************************************************/
EXTERN RJS_UV _rj_cnk_uv_scroll_;   /* u offset                                                 */
EXTERN RJS_UV _rj_cnk_env_scroll_;  /* u offset                                                 */

/****** Obj/Mdl Callback ************************************************************************/
EXTERN RJF_CNK_OBJ* _rj_cnk_object_callback_; /* draw object callback                           */
EXTERN RJF_CNK_MDL* _rj_cnk_model_callback_;  /* model draw callback                            */

/****** Plist Callback **************************************************************************/
EXTERN RJF_CNK_PLIST_TNUM* _rj_cnk_texture_callback_;  /* texture callback                      */
EXTERN RJF_CNK_PLIST_MCOL* _rj_cnk_material_callback_; /* material color callback               */

/****** Intensity Multiply, for Simple **********************************************************/
EXTERN Float _rj_cnk_inten_multiply_;

/********************************/
/*  Prototypes                  */
/********************************/
/************************************************************************************************/
/*
*   Chunk Parts
*/
/****** Model Functions *************************************************************************/
/*
*   Description:
*     Parse a Chunk vertex list into a specified vertex buffer
*
*   Parameters:
*     - pVList      : base vlist pointer
*     - pVBuf       : vertex buffer
*
*   Returns:
*     'CNK_RETN_OK' on success; or 'CNK_RETN_CLIP' on failure.
*/
Sint32  rjCnkVList( const Sint32* restrict pVList, RJS_VERTEX_BUF* restrict pVBuf );
/*
*   Description:
*     Draw a Chunk polygon list using a specified vertex buffer
*
*   Parameters:
*     - pPList      : base plist pointer
*     - pVBuf       : vertex buffer to read from
*/
void    rjCnkPList( const Sint16* restrict pPList, const RJS_VERTEX_BUF* restrict pVBuf );

/****** External Functions (Draw) ***************************************************************/
/*
*   Description:
*     Parse and draw a Chunk model for shadowtex models. The difference is this
*   function draws all strips in 1 call with no additional info other than vertex
*   positioning.
*
*   Parameters:
*     - model       : chunk model
*     - vbuf        : vertex buffer
*/
int     CnkDrawShadow_Ext( const NJS_CNK_MODEL* model, const void* vbuf );

/************************************************************************************************/
/*
*   Chunk Internal
*/
/****** Depth Queue *****************************************************************************/
/*
*   Description:
*     Start depth queue calculations (alpha fade at a distance) on a model about to be drawn.
*
*   Parameters:
*     - model       : model to be drawn
*/
void    rjCnkBeginDepthQueue( const NJS_CNK_MODEL* model );
/*
*   Description:
*     Calculate depth queue colors on the current vertex chunk head.
* 
*   Parameters:
*     - vhead       : vertex chunk head
*     - vbuf        : vertex buffer
*     - njflag      : ninja flag (weights)
*/
void    rjCnkCalculateDepthQueue( const CNK_VERTEX_HEAD* vhead, RJS_VERTEX_BUF* vbuf, bool njflag );

/****** Vertex Color ****************************************************************************/
/*
*   Description:
*     Directly get the buffered vertex color.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkVertexColorD8( const RJS_VERTEX_BUF* restrict pVtx );
/*
*   Description:
*     Get current Chunk material color.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkVertexColorMaterial( const RJS_VERTEX_BUF* restrict pVtx );
/*
*   Description:
*     Calculate all lighting on a vertex, and return the absolute light color.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkVertexColorLights( const RJS_VERTEX_BUF* restrict pVtx );
/*
*   Description:
*     Calculate all lighting on a VND8 vertex, and return the absolute light color.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkVertexColorLightsD8( const RJS_VERTEX_BUF* restrict pVtx );

/****** Specular ********************************************************************************/
/*
*   Description:
*     Get a black specular color to disable specular drawing.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkSpecularNone( const RJS_VERTEX_BUF* restrict pVtx );

/*
*   Description:
*     Get the buffered specular vertex color.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkSpecularS8( const RJS_VERTEX_BUF* restrict pVtx );
/*
*   Description:
*     Calculate Render Fix specular lighting on a vertex, and return the absolute
*   specular color.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkSpecularNormal( const RJS_VERTEX_BUF* restrict pVtx );
/*
*   Description:
*     Calculate Easy specular lighting on a vertex, and return the absolute
*   specular color.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkSpecularEasy( const RJS_VERTEX_BUF* restrict pVtx );
/*
*   Description:
*     Calculate Simple specular lighting on a vertex, and return the absolute
*   specular color.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkSpecularSimple( const RJS_VERTEX_BUF* restrict pVtx );
/*
*   Description:
*     Calculate MultiDraw specular lighting on a vertex, and return the absolute
*   specular color.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkSpecularMulti( const RJS_VERTEX_BUF* restrict pVtx );

/************************************************************************************************/
/*
*   Chunk Parts
*/
/****** Get UV Scroll ***************************************************************************/
/*
*   Description:
*     Get UV scroll values.
*/
RJS_UV  rjCnkGetUvScroll( void );
/*
*   Description:
*     Get Environment UV scroll values.
*/
RJS_UV  rjCnkGetEnvUvScroll( void );

/************************************************************************************************/
/*
*   Render Context
*/
/****** Polygon Culling *************************************************************************/
/*
*   Description:
*     Change the polygon culling mode for Chunk model.
*
*   Notes:
*     - The 'CW' mode is the default 'forward' for Chunk.
*
*   Parameters:
*     - cullmd      : culling mode
*/
void    rjCnkPolygonCulling( RJ_CULL cullmd );

/****** Two Pass Lighting ***********************************************************************/
/*
*   Description:
*     Inverts the Chunk light vectors for two pass lighting. It does this by inverting the
*   vertex light intensities during the final color function phase.
*
*   Parameters:
*     - sw          : ON/OFF
*/
void    rjCnkInvertLightDirection( Bool sw );

/****** Start/End Plist *************************************************************************/
/*
*   Description:
*     Start Chunk Plist draw by initializing first strip entry and setting context flags.
*
*   Parameters:
*     - basest      : base rj strip entry
*/
void    rjCnkStartPlist( RJS_CNK_STRIP* restrict basest );
/*
*   Description:
*     End Chunk Plist draw.
*/
void    rjCnkEndPlist( void );

/****** Start/End Vertex ************************************************************************/
/*
*   Description:
*     Setup shaders and render context for a textureless Chunk strip.
*
*   Parameters:
*     - pCtx        : current chunk context
*/
void    rjCnkStartVertexNonTex( void );
/*
*   Description:
*     Setup shaders and render context for a textured Chunk strip.
*
*   Parameters:
*     - pCtx        : current chunk context
*/
void    rjCnkStartVertexTex( void );
/*
*   Description:
*     Draw buffered polygons.
*/
void    rjCnkEndVertex( void );

EXTERN_END

#endif/*H_RF_DRAW_CNKMDL_INTERNAL*/
