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

/************************/
/*  External Includes   */
/************************/
/****** Self ************************************************************************/
#include <rf_draw/rfd_internal.h> /* grand parent                                   */
#include <rf_draw/rfd_cnk.h>      /* parent util                                    */

EXTERN_START

/************************/
/*  Constants           */
/************************/
/****** Chunk Context ***************************************************************/
#define CTXF_FUNC_EASY          (1<<0)  /* easy draw variant                        */
#define CTXF_FUNC_SIMPLE        (1<<1)  /* simple draw variant                      */
#define CTXF_FUNC_MULTI         (1<<2)  /* multi draw variant                       */
#define CTXF_FUNC_DIRECT        (1<<3)  /* direct draw                              */

#define CTXF_DRAW_TRANS         (1<<4)  /* draw trans strips, if off draw opaque    */
#define CTXF_DRAW_NORMAL        (1<<5)  /* draw normal triangles                    */
#define CTXF_DRAW_INVERSE       (1<<6)  /* draw inverse triangles                   */

#define CTXF_TINY               (1<<7)  /* new texture data to apply                */

#define CTXF_STATE_NONTEX        (1<<8)  /* current strip has no texture             */
#define CTXFLG_STRIP_NOUVS      (1<<9)  /* current strip has no UV info             */

#define CTXF_CTL_BACKFACECULL   (1<<10) /* uses simple inverted polygon calcs       */
#define CTXF_CTL_AMBIMATERIAL   (1<<11) /* read ambient material color              */
#define CTXF_CTL_MULTIVND8      (1<<12) /* use vertex color/light blending          */
#define CTXF_CTL_NONTEXSPEC     (1<<13) /* notex specular                           */

#define CTX_FUNC_NORMAL          (0)    /* render fix normal draw                   */
#define CTX_FUNC_EASY            (1)    /* easy draw                                */
#define CTX_FUNC_SIMPLE          (2)    /* simple draw                              */
#define CTX_FUNC_EASYMULTI       (5)    /* easy multi draw                          */
#define CTX_FUNC_SIMPLEMULTI     (6)    /* simple multi draw                        */
#define CTX_FUNC_DIRECT          (8)    /* direct draw                              */

#define CTXF_MASK_FUNC          (CTXF_FUNC_EASY|CTXF_FUNC_SIMPLE|CTXF_FUNC_MULTI|CTXF_FUNC_DIRECT)

#define CTXF_MASK_DRAW          (CTXF_DRAW_TRANS|CTXF_DRAW_NORMAL|CTXF_DRAW_INVERSE)

/****** Chunk Vertex ****************************************************************/
#define RJD_CVF_NORMAL          (1<<0)
#define RJD_CVF_COLOR           (1<<1)
#define RJD_CVF_SPECULAR        (1<<2)

#define RJD_CVT_POS             (0)
#define RJD_CVT_POS_NRM         (RJD_CVF_NORMAL)
#define RJD_CVT_POS_COL         (RJD_CVF_COLOR)
#define RJD_CVT_POS_NRM_COL     (RJD_CVF_NORMAL|RJD_CVF_COLOR)
#define RJD_CVT_POS_COL_SPC     (RJD_CVF_COLOR|RJD_CVF_SPECULAR)

/****** Depth Queue *****************************************************************/
#define RJD_CNK_DEPTHQUEUE_OFF      (0) /* depthqueue is disabled                   */
#define RJD_CNK_DEPTHQUEUE_NEAR     (1) /* depthqueue is on, but behind near plane  */
#define RJD_CNK_DEPTHQUEUE_ON       (2) /* depthqueue is enabled                    */

/************************/
/*  Function Types      */
/************************/
/****** Color Calculations **********************************************************/
typedef Uint32 (RJF_CNK_VCOLFUNC)(const CNK_VERTEX_BUFFER* restrict pVtx);
typedef Uint32 (RJF_CNK_SPECFUNC)(const CNK_VERTEX_BUFFER* restrict pVtx);

/****** Vlist Calculations **********************************************************/
typedef void (RJF_CNK_VLIST_POS)(NJS_POINT3* dst, const NJS_POINT3* src);
typedef void (RJF_CNK_VLIST_NRM)(NJS_VECTOR* dst, const NJS_VECTOR* src);
typedef void (RJF_CNK_VLIST_COL)(NJS_ARGB*   dst, const NJS_ARGB*   src);
typedef void (RJF_CNK_VLIST_SPC)(NJS_ARGB*   dst, const NJS_ARGB*   src);

/************************/
/*  Enums               */
/************************/
/****** Vertex Color Functions ******************************************************/
typedef enum
{
    RJE_CNK_VCOLFUNC_MATERIAL,
    RJE_CNK_VCOLFUNC_D8,
    RJE_CNK_VCOLFUNC_LIGHT,
    RJE_CNK_VCOLFUNC_LIGHTD8,

    NB_RJE_CNK_VCOLFUNC,
}
RJE_CNK_VCOLFUNC;

/****** Specular Functions **********************************************************/
typedef enum
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

/************************/
/*  Game Structures     */
/************************/
/****** Chunk Context ***************************************************************/
typedef struct
{
    Uint32          flag;       /* context flags                                    */

    Sint16          fst;        /* strip flags, at the top for packing reasons      */
    Sint16          blend;      /* alpha blend mode                                 */
    CNK_TINY_HEAD   tiny;       /* texture material                                 */
    NJS_BGRA        diff;       /* diffuse material                                 */
    NJS_BGRA        ambi;       /* ambient material, 'a' is ignored                 */
    NJS_BGRA        spec;       /* specular material, 'a' is exponent               */
}
CNK_CTX;

/************************/
/*  Game References     */
/************************/
/****** Texture *********************************************************************/
#define pTexSurface                     DATA_REF(NJS_TEXSURFACE*, 0x01A55840)

/****** Old Strip Flag for Lighting *************************************************/
#define _nj_cnk_strip_flags_            DATA_REF(Uint32, 0x01A5583C)
#define _nj_cnk_last_strip_flags_       DATA_REF(Uint32, 0x01A55838)

/****** Chunk Polygon cache list ****************************************************/
#define _nj_cnk_polygon_cache_num_      DATA_REF(Sint32       , 0x025F0108)
#define _nj_cnk_polygon_cache_tbl_      DATA_ARY(const Sint16*, 0x02670340, [125])

/****** Chunk Vertex Attributes *****************************************************/
#define _nj_cnk_vtx_attrs_              DATA_REF(Sint32, 0x019346DC)

/****** Use Basic Draw for Shadows **************************************************/
#define ShadowCnkDraw                   DATA_REF(b32, 0x01A55798)

/************************/
/*  Data                */
/************************/
/****** Chunk Draw ******************************************************************/
EXTERN Uint32   _rj_cnk_vertex_attr_;  /* vertex attributes                         */

EXTERN Uint32   _rj_cnk_blend_mode_;   /* alpha blend                               */

EXTERN NJS_ARGB _rj_cnk_diff_material_; /* diffuse material                         */
EXTERN NJS_ARGB _rj_cnk_ambi_material_; /* ambient material                         */
EXTERN NJS_ARGB _rj_cnk_spec_material_; /* specular material                        */

EXTERN Sint32   _rj_cnk_shadow_tex_;    /* shadow tex count                         */

EXTERN Sint32   _rj_cnk_spec_mode_;     /* specular mode                            */

EXTERN Sint32   _rj_cnk_depth_queue_;

EXTERN RJF_CNK_VCOLFUNC* _rj_cnk_vcol_funcs_[NB_RJE_CNK_VCOLFUNC]; /* vcol funcs    */
EXTERN RJF_CNK_SPECFUNC* _rj_cnk_spec_funcs_[NB_RJE_CNK_SPECFUNC]; /* spec funcs    */

EXTERN RJF_CNK_VLIST_POS* _rj_cnk_vlist_pfunc_; /* vertex position function       */
EXTERN RJF_CNK_VLIST_NRM* _rj_cnk_vlist_nfunc_; /* vertex normal function         */
EXTERN RJF_CNK_VLIST_COL* _rj_cnk_vlist_cfunc_; /* vertex color function          */
EXTERN RJF_CNK_VLIST_SPC* _rj_cnk_vlist_sfunc_; /* vertex specular function       */

/****** UV Scroll *******************************************************************/
EXTERN RJS_UV _rj_cnk_uv_scroll_;   /* u offset                                     */
EXTERN RJS_UV _rj_cnk_env_scroll_;  /* u offset                                     */

/****** Obj/Mdl Callback ************************************************************/
EXTERN void(*_rj_cnk_object_callback_)(NJS_CNK_OBJECT*);
EXTERN void(*_rj_cnk_model_callback_)(NJS_CNK_MODEL*);

/****** Texture Callback ************************************************************/
EXTERN Sint16(__cdecl* _rj_cnk_texture_callback_)(Sint16); /* tex callback          */

/****** Intensity Multiply, for Simple **********************************************/
EXTERN Float _rj_cnk_inten_multiply_;

/************************/
/*  Prototypes          */
/************************/
/****** Chunk Context ***************************************************************/
/*
*   Description:
*     Begin a new Chunk context structure.
*
*   Parameters:
*     - pCtx        : chunk context
*/
void    rjCnkBeginContext( CNK_CTX* restrict pCtx );
/*
*   Description:
*     Apply a Chunk context to the render state
*
*   Parameters:
*     - pCtx        : chunk context
*/
void    rjCnkExecContext( CNK_CTX* restrict pCtx );
/*
*   Description:
*     Set blend types to context.
*
*   Parameters:
*     - pCtx        : chunk context
*     - plist       : bits/material plist header
*/
void    rjCnkSetBlend( CNK_CTX* restrict pCtx, const Sint16* plist );
/*
*   Description:
*     Set exponent bits type to context.
*
*   Parameters:
*     - pCtx        : chunk context
*     - plist       : bits plist header
*/
void    rjCnkSetExponent( CNK_CTX* restrict pCtx, const Sint16* plist );
/*
*   Description:
*     Set material colors to context.
*
*   Parameters:
*     - pCtx        : chunk context
*     - plist       : material plist header
*/
void    rjCnkSetMaterial( CNK_CTX* restrict pCtx, const Sint16* plist );
/*
*   Description:
*     Set texture parameters to context.
*
*   Parameters:
*     - pCtx        : chunk context
*     - plist       : tiny plist header
*/
void    rjCnkSetTexture( CNK_CTX* restrict pCtx, const Sint16* plist );
/*
*   Description:
*     Set strip flags and constant/func/render state flags to context
*
*   Parameters:
*     - pCtx        : chunk context
*     - plist       : strip plist header
*/
void    rjCnkSetStrip( CNK_CTX* restrict pCtx, const Sint16* plist );

/****** Model Functions *************************************************************/
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
Sint32  rjCnkVList( const Sint32* restrict pVList, CNK_VERTEX_BUFFER* restrict pVBuf );
/*
*   Description:
*     Draw a Chunk polygon list using a specified vertex buffer
*
*   Parameters:
*     - pPList      : base plist pointer
*     - pVBuf       : vertex buffer to read from
*/
void    rjCnkPList( const Sint16* restrict pPList, const CNK_VERTEX_BUFFER* restrict pVBuf );

/****** Vlist Calculations **********************************************************/
void    rjCnkCalcVlistPosition( NJS_POINT3* dst, const NJS_POINT3* src );
void    rjCnkCalcVlistNormal(   NJS_VECTOR* dst, const NJS_VECTOR* src );
void    rjCnkCalcVlistColor(    NJS_ARGB*   dst, const NJS_ARGB*   src );
void    rjCnkCalcVlistSpecular( NJS_ARGB*   dst, const NJS_ARGB*   src );

void    rjCnkCalcVlistNormalUnit( NJS_VECTOR* dst, const NJS_VECTOR* src );

/****** Depth Queue *****************************************************************/
void    rjCnkBeginDepthQueue(const NJS_CNK_MODEL* model);

void    rjCnkCalculateDepthQueue(const CNK_VERTEX_HEAD* vhead, CNK_VERTEX_BUFFER* vbuf);
void    rjCnkCalculateDepthQueueNF(const CNK_VERTEX_HEAD* vhead, CNK_VERTEX_BUFFER* vbuf);

/****** Vertex Color ****************************************************************/
/*
*   Description:
*     Directly get the buffered vertex color.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkVertexColorD8( const CNK_VERTEX_BUFFER* restrict pVtx );
/*
*   Description:
*     Get current Chunk material color.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkVertexColorMaterial( const CNK_VERTEX_BUFFER* restrict pVtx );
/*
*   Description:
*     Calculate all lighting on a vertex, and return the absolute light color.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkVertexColorLights( const CNK_VERTEX_BUFFER* restrict pVtx );
/*
*   Description:
*     Calculate all lighting on a VND8 vertex, and return the absolute light color.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkVertexColorLightsD8( const CNK_VERTEX_BUFFER* restrict pVtx );

/****** Specular ********************************************************************/
/*
*   Description:
*     Get a black specular color to disable specular drawing.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkSpecularNone( const CNK_VERTEX_BUFFER* restrict pVtx );

/*
*   Description:
*     Get the buffered specular vertex color.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkSpecularS8( const CNK_VERTEX_BUFFER* restrict pVtx );
/*
*   Description:
*     Calculate Render Fix specular lighting on a vertex, and return the absolute
*   specular color.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkSpecularNormal( const CNK_VERTEX_BUFFER* restrict pVtx );
/*
*   Description:
*     Calculate Easy specular lighting on a vertex, and return the absolute
*   specular color.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkSpecularEasy( const CNK_VERTEX_BUFFER* restrict pVtx );
/*
*   Description:
*     Calculate Simple specular lighting on a vertex, and return the absolute
*   specular color.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkSpecularSimple( const CNK_VERTEX_BUFFER* restrict pVtx );
/*
*   Description:
*     Calculate MultiDraw specular lighting on a vertex, and return the absolute
*   specular color.
*
*   Parameters:
*     - pVtx        : vertex buffer entry
*/
Uint32  rjCnkSpecularMulti( const CNK_VERTEX_BUFFER* restrict pVtx );

/****** Chunk Control ***************************************************************/
void    rjCnkSetPolygonCullingMode(CNK_CTX* restrict pCtx, Bool light);

void    rjCnkBeginLighting(const CNK_CTX* restrict pCtx);

bool    rjCnkBeginTwoPassLighting(const CNK_CTX* restrict pCtx);

/****** Get UV Scroll ***************************************************/
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

/****** External Functions (Draw) ***************************************************/
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

/************************/
/*  Function Ptrs       */
/************************/
/****** External Functions **********************************************************/
#define SetOpaqueDraw               FUNC_PTR(void, __cdecl, (void), 0x0042C030)
#define SetAlphaTestDraw            FUNC_PTR(void, __cdecl, (void), 0x0042C0A0)
#define SetTransparentDraw          FUNC_PTR(void, __cdecl, (void), 0x0042C170)

EXTERN_END

#endif/*H_RF_DRAW_CNKMDL_INTERNAL*/
