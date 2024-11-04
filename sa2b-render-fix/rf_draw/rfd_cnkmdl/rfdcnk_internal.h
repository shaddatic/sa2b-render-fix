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
#define CTXFLG_DRAW_TRANS       (1<<0)  /* draw trans strips, if off draw opaque    */
#define CTXFLG_CULL_NORMAL      (1<<1)  /* draw normal triangles                    */
#define CTXFLG_CULL_INVERSE     (1<<2)  /* draw inverse triangles                   */

#define CTXFLG_CTX_BLEND        (1<<8)  /* blend is applied                         */
#define CTXFLG_CTX_TINY         (1<<9)  /* tiny is applied                          */
#define CTXFLG_CTX_DIFF         (1<<10) /* diffuse is applied                       */
#define CTXFLG_CTX_AMBI         (1<<11) /* ambient is applied                       */
#define CTXFLG_CTX_SPEC         (1<<12) /* specular is applied                      */

#define CTXFLG_SHIFT_MAT        (10)

#define CTXFLG_STRIP_NOTEX      (1<<16) /* current strip has no UV info             */

#define CTXFLG_MASK_DRAW        (CTXFLG_DRAW_TRANS)
#define CTXFLG_MASK_CULL        (CTXFLG_CULL_NORMAL|CTXFLG_CULL_INVERSE)

#define CTXFLG_MASK_STRIP       (CTXFLG_STRIP_NOTEX)

/************************/
/*  Game Structures     */
/************************/
/****** Vertex Decl *****************************************************************/
typedef struct
{
    float gap0;
    int field_4;
    float field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    void* D3DVertexDeclaration;
    int field_20;
    uint32_t StrideSize;
    int field_28;
    int field_2C;
    int field_30;
}
VertexDeclarationInfo;

/****** Chunk Context ***************************************************************/
typedef struct
{
    s8 b, g, r, e;
}
CNK_SPEC;

typedef struct
{
    Sint16 id;
    Uint16 flag;
}
CNK_TINY;

typedef struct
{
    Uint32   flag;

    Sint16   fst;   // at the top for packing reasons
    Sint16   blend;
    CNK_TINY tiny;
    NJS_BGRA diff;
    NJS_BGRA ambi;
    CNK_SPEC spec;
}
CNK_CTX;

/************************/
/*  Game Constants      */
/************************/
/****** Vertex Attr Flags ***********************************************************/
#define CNKVTX_NO_NORMALS       (1) /* no vertex normals                            */
#define CNKVTX_HAS_VCOLORS      (2) /* has vertex colors                            */

/************************/
/*  Game References     */
/************************/
/****** Vertex Decl *****************************************************************/
#define VertexDeclInfo                  DATA_REF(VertexDeclarationInfo*, 0x0174F7E8)

/****** Vertex Decl Types ***********************************************************/
#define VertexDecl_Pos                  DATA_REF(VertexDeclarationInfo*, 0x0174F7EC)
#define VertexDecl_PosNorm              DATA_REF(VertexDeclarationInfo*, 0x0174F7F0)
#define VertexDecl_PosCol               DATA_REF(VertexDeclarationInfo*, 0x0174F7F4)
#define VertexDecl_PosNormCol           DATA_REF(VertexDeclarationInfo*, 0x0174F7F8)
#define VertexDecl_PosColUV             DATA_REF(VertexDeclarationInfo*, 0x0174F804)
#define VertexDecl_PosNormUV            DATA_REF(VertexDeclarationInfo*, 0x0174F80C)
#define VertexDecl_PosNormColUV         DATA_REF(VertexDeclarationInfo*, 0x0174F814)

/****** Texture *********************************************************************/
#define pTexSurface                     DATA_REF(int*, 0x01A55840)

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
/*  Prototypes          */
/************************/
/****** Chunk Context ***************************************************************/
/*
*   Description:
*     Apply a Chunk context to the render state
*
*   Paramters:
*     - pCtx        : chunk context
*/
void    rjCnkContext( CNK_CTX* restrict pCtx );
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

/****** Internal Ctx ****************************************************************/
/*
*   Description:
*     Get strip flags from strip chunk, taking into account Ninja constant and
*   Render Fix renderstate.
*
*   Notes:
*     - called by 'rjCnkSetStrip'
*
*   Paramters:
*     - plist       : strip plist header
*
*   Returns:
*     Strip flags after applying Ninja constant and renderstate.
*/
Sint16  GetCnkStripFlags( const Sint16* plist );

/****** Cnk Functions ***************************************************************/
/*
*   Description:
*     Parse a Chunk VList into a specified vertex buffer
*
*   Paramters:
*     - pVList      : base vlist pointer
*     - njvtxbuf    : vertex buffer
*/
int     rjCnkVList( const Sint32* pVList, CNK_VERTEX_BUFFER* njvtxbuf );
/*
*   Description:
*     Parse and draw a Chunk PList using a specified vertex buffer
*
*   Paramters:
*     - pPList      : base plist pointer
*     - njvtxbuf    : vertex buffer
*/
void    rjCnkPList( const Sint16* pPList, const CNK_VERTEX_BUFFER* njvtxbuf );

/****** Cnk Shadow Map **************************************************************/
/*
*   Description:
*     Parse a Chunk VList into a specified vertex buffer with shadow map support.
*   Due to how shadow maps are handled, this function cannot handle weights or
*   object trees.
*
*   Paramters:
*     - pVList      : base vlist pointer
*     - njvtxbuf    : vertex buffer
*/
int     rjCnkVListSM( const Sint32* pVList, CNK_VERTEX_BUFFER* njvtxbuf );

/****** External Functions (Ctx) ****************************************************/
/*
*   Description:
*     Parse tiny (tex) data.
*
*   Paramters:
*     - tinyData    : tiny data
*     - texFlags    : texture flags
*/
void    CnkParseTinyData_Ext( Sint32 tinyData, Sint32 texFlags );
/*
*   Description:
*     Setup material shader data
*
*   Parameters:
*     - flag        : diff/ambi/spec flags (only diff used)
*     - color       : material color
*/
void    CnkParseMatColor_Ext( s32 flag, const Sint16* color );
/*
*   Description:
*     Setup light shader data
*
*   Parameters:
*     - fst_shr8    : strip flags, >> 8
*/
void    CnkSetupLights_Ext( s32 fst_shr8 );

/****** External Functions (Draw) ***************************************************/
/*
*   Description:
*     Parse a Chunk VList into a specified vertex buffer
*
*   Paramters:
*     - pVList       : base vlist pointer
*     - njvtxbuf     : vertex buffer
*     - is_not_cache : flag for the CnkCacheDraw, use 'true'
*/
int     CnkVListShadow_Ext( const Sint32* pVList, void* njvtxbuf, int is_not_cache );
/*
*   Description:
*     Parse and draw a Chunk PList using a specified vertex buffer for shadow
*   models. The difference is this function draws all strips in 1 call with no
*   additional info other than vertex positioning.
*
*   Paramters:
*     - pPList      : base plist pointer
*     - njvtxbuf    : vertex buffer
*/
void    CnkPListShadow_Ext( const Sint16* pPList, const void* njvtxbuf );

/************************/
/*  Function Ptrs       */
/************************/
/****** External Functions **********************************************************/
#define SetOpaqueDraw               FUNC_PTR(void, __cdecl, (void), 0x0042C030)
#define SetAlphaTestDraw            FUNC_PTR(void, __cdecl, (void), 0x0042C0A0)
#define SetTransparentDraw          FUNC_PTR(void, __cdecl, (void), 0x0042C170)

EXTERN_END

#endif/*H_RF_DRAW_CNKMDL_INTERNAL*/
