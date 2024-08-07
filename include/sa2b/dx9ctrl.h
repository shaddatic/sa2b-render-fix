/*
*   Sonic Adventure Mod Tools (SA2B) - '/dx9ctrl.h'
*
*   Description:
*       Functions to directly control the DirectX9 renderer.
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SAMT_DX9CTRL_H_
#define _SAMT_DX9CTRL_H_

/************************/
/*  D3D9 Device         */
/************************/
EXTERN_START
/** Get IDirect3DDevice* **/
void*   DX9_GetDevice( void );

/************************/
/*  Common              */
/************************/
/** Compare operations **/
typedef enum
{
    DX9_CMP_NVR = 1,    /* Never                    */
    DX9_CMP_LSS,        /* Less                     */
    DX9_CMP_EQU,        /* Equal                    */
    DX9_CMP_LEQ,        /* Less or equal            */
    DX9_CMP_GTR,        /* Greater                  */
    DX9_CMP_NEQ,        /* Not equal                */
    DX9_CMP_GEQ,        /* Greater or equal         */
    DX9_CMP_ALW,        /* Always                   */
}
dx9_compare_op;

/************************/
/*  Z Buffer            */
/************************/
/** Enable/disable read/write **/
bool    DX9_SetZRead(  bool state );
bool    DX9_SetZWrite( bool state );

/** Set Z compare operation **/
bool    DX9_SetZFunc( dx9_compare_op op );

/************************/
/*  Stencil Buffer      */
/************************/
/** Stencil operations **/
typedef enum
{
    DX9_STCL_KEEP = 1,  /* Keep                     */
    DX9_STCL_ZERO,      /* Set to zero              */
    DX9_STCL_REPL,      /* Replace                  */
    DX9_STCL_INCR_CLMP, /* Increment with clamp     */
    DX9_STCL_DECR_CLMP, /* Decrement with clamp     */
    DX9_STCL_INVT,      /* Invert                   */
    DX9_STCL_INCR,      /* Increment                */
    DX9_STCL_DECR,      /* Decrement                */
}
dx9_stencil_op;

/** Enable/disable stencil **/
bool    DX9_SetStencil( bool state );

/** Enable/disable two sided stencil **/
bool    DX9_SetStencilTwoSided( bool state );

/** Set stencil pass function **/
bool    DX9_SetStencilFunc( dx9_compare_op op );

/** Set stencil CW operations **/
bool    DX9_SetStencilFail(  dx9_stencil_op op );
bool    DX9_SetStencilZFail( dx9_stencil_op op );
bool    DX9_SetStencilPass(  dx9_stencil_op op );

/** Set stencil CCW operations **/
bool    DX9_SetStencilFailCCW(  dx9_stencil_op op );
bool    DX9_SetStencilZFailCCW( dx9_stencil_op op );
bool    DX9_SetStencilPassCCW(  dx9_stencil_op op );

/** Set stencil reference **/
bool    DX9_SetStencilRef( uint32_t ref );

/** Set stencil masks **/
bool    DX9_SetStencilReadMask(  uint32_t mask );
bool    DX9_SetStencilWriteMask( uint32_t mask );

/************************/
/*  Color Write         */
/************************/
/** Color flags **/
#define DX9_COL_NONE        (0b0000)
#define DX9_COL_RED         (0b0001)
#define DX9_COL_GREEN       (0b0010)
#define DX9_COL_BLUE        (0b0100)
#define DX9_COL_ALPHA       (0b1000)

/** Set color write **/
bool    DX9_SetColorWrite( uint32_t flags );

/************************/
/*  Blending            */
/************************/
/** Blending operations **/
typedef enum
{
    DX9_BLND_ZERO = 1,
    DX9_BLND_ONE,
    DX9_BLND_SRCCOLOR,
    DX9_BLND_INVSRCCOLOR,
    DX9_BLND_SRCALPHA,
    DX9_BLND_INVSRCALPHA,
    DX9_BLND_DESTALPHA,
    DX9_BLND_INVDESTALPHA,
    DX9_BLND_DESTCOLOR,
    DX9_BLND_INVDESTCOLOR,
    DX9_BLND_SRCALPHASAT,
    DX9_BLND_BOTHSRCALPHA,
    DX9_BLND_BOTHINVSRCALPHA,
    DX9_BLND_BLENDFACTOR,
    DX9_BLND_INVBLENDFACTOR,
    DX9_BLND_SRCCOLOR2,
    DX9_BLND_INVSRCCOLOR2,
}
dx9_blend_op;

/** Enable/disable color alpha blending **/
bool    DX9_SetAlphaBlend( bool state );

/** Set alpha compare operation **/
bool    DX9_SetAlphaFunc( dx9_compare_op op );

/** Set src/dst blending operation **/
bool    DX9_SetSrcBlend( dx9_blend_op op );
bool    DX9_SetDstBlend( dx9_blend_op op );

/************************/
/*  Culling             */
/************************/
/** Triangle culling modes **/
typedef enum
{
    DX9_CULL_NONE = 1,
    DX9_CULL_CW,
    DX9_CULL_CCW,
}
dx9_cull_mode;

/** Set triangle culling mode **/
bool    DX9_SetCulling( dx9_cull_mode mode );

/************************/
/*  Point Primitive     */
/************************/
/****** Point Primitive *************************************************/
bool    DX9_SetPointSize(   f32       size  );
bool    DX9_SetPointSprite( bool      state );
bool    DX9_SetPointScale(  bool      state );

/************************/
/*  Vertex Shader       */
/************************/
/** Shader type **/
typedef struct dx9_vtx_shader   dx9_vtx_shader;

/** Load pre-compiled shader file (.fxc) **/
dx9_vtx_shader*
        DX9_LoadVtxShader( const utf8* fpath );

/** Set vertex shader **/
bool    DX9_SetVtxShader( dx9_vtx_shader* pVtxShader );

/** Set shader constants
    p   : pointer to constant data
    reg : start register index
    nb# : number of data to set **/
bool    DX9_SetVtxShaderConstantF( const void* p, uint32_t reg, size_t nbFloat );
bool    DX9_SetVtxShaderConstantI( const void* p, uint32_t reg, size_t nbInt   );

/************************/
/*  Pixel Shader        */
/************************/
/** Shader type **/
typedef struct dx9_pxl_shader   dx9_pxl_shader;

/** Load pre-compiled shader file (.fxc) **/
dx9_pxl_shader*
        DX9_LoadPxlShader( const utf8* fpath );

/** Set pixel shader **/
bool    DX9_SetPxlShader( dx9_pxl_shader* pPxlShader );

/** Set shader constants
    p   : pointer to constant data
    reg : start register index
    nb# : number of data to set **/
bool    DX9_SetPxlShaderConstantF( const void* p, uint32_t reg, size_t nbFloat );
bool    DX9_SetPxlShaderConstantI( const void* p, uint32_t reg, size_t nbInt   );

/************************/
/*  Vertex Declaration  */
/************************/
/** Vertex element type **/
enum
{
    DX9_VTXTYPE_FLOAT1,
    DX9_VTXTYPE_FLOAT2,
    DX9_VTXTYPE_FLOAT3,
    DX9_VTXTYPE_FLOAT4,
    DX9_VTXTYPE_COLOR,
    DX9_VTXTYPE_UBYTE4,
    DX9_VTXTYPE_SHORT2,
    DX9_VTXTYPE_SHORT4,
    DX9_VTXTYPE_UBYTE4N,
    DX9_VTXTYPE_SHORT2N,
    DX9_VTXTYPE_SHORT4N,
    DX9_VTXTYPE_USHORT2N,
    DX9_VTXTYPE_USHORT4N,
    DX9_VTXTYPE_UDEC3,
    DX9_VTXTYPE_DEC3N,
    DX9_VTXTYPE_FLOAT16_2,
    DX9_VTXTYPE_FLOAT16_4,
    DX9_VTXTYPE_UNUSED,
};

/** Vertex element method **/
enum
{
    DX9_VTXMETH_DEFAULT,
    DX9_VTXMETH_PARTIALU,
    DX9_VTXMETH_PARTIALV,
    DX9_VTXMETH_CROSSUV,
    DX9_VTXMETH_UV,
    DX9_VTXMETH_LOOKUP,
    DX9_VTXMETH_LOOKUPPRESAMPLED,
};

/** Vertex element usage **/
enum
{
    DX9_VTXUSE_POSITION,
    DX9_VTXUSE_BLENDWEIGHT,
    DX9_VTXUSE_BLENDINDICES,
    DX9_VTXUSE_NORMAL,
    DX9_VTXUSE_PSIZE,
    DX9_VTXUSE_TEXCOORD,
    DX9_VTXUSE_TANGENT,
    DX9_VTXUSE_BINORMAL,
    DX9_VTXUSE_TESSFACTOR,
    DX9_VTXUSE_POSITIONT,
    DX9_VTXUSE_COLOR,
    DX9_VTXUSE_FOG,
    DX9_VTXUSE_DEPTH,
    DX9_VTXUSE_SAMPLE,
};

/** Vertex primitive type **/
typedef enum
{
    DX9_PRITYPE_POINTLIST = 1,
    DX9_PRITYPE_LINELIST,
    DX9_PRITYPE_LINESTRIP,
    DX9_PRITYPE_TRIANGLELIST,
    DX9_PRITYPE_TRIANGLESTRIP,
    DX9_PRITYPE_TRIANGLEFAN,
}
dx9_pri_type;

/** Vertex declaration type **/
typedef void        dx9_vtx_decl;

/** Vertex element structure **/
typedef struct
{
    uint16_t    idxStream;
    uint16_t    idxOffset;
    uint8_t     type;
    uint8_t     method;
    uint8_t     usage;
    uint8_t     idxUsage;
}
dx9_vtx_elem;

/** Use this as the last entry of your 'dx9_vtx_elem' list **/
#define DX9_VTX_ELEM_END()    { 0xFF, 0, DX9_VTXTYPE_UNUSED, 0, 0, 0 }

/** Create vertex declaration **/
dx9_vtx_decl*
        DX9_CreateVtxDecl( const dx9_vtx_elem* pVtxElements );

/** Set vertex declaration **/
bool    DX9_SetVtxDecl( dx9_vtx_decl* pVtxDeclaration );

/************************/
/*  Draw                */
/************************/
bool    DX9_DrawPrimitiveUP( dx9_pri_type typePri, size_t nbPri, const void* pVtxStream, size_t nbStride );

/************************/
/*  Render State        */
/************************/
/****** Vertex Shader ***************************************************/
bool    DX9_SaveVtxShaderState( void );
bool    DX9_LoadVtxShaderState( void );

/****** Pixel Shader ****************************************************/
bool    DX9_SavePxlShaderState( void );
bool    DX9_LoadPxlShaderState( void );

/****** Vertex Declaration **********************************************/
bool    DX9_SaveVtxDeclState( void );
bool    DX9_LoadVtxDeclState( void );

/****** Z Buffer ********************************************************/
bool    DX9_SaveZReadState( void );
bool    DX9_LoadZReadState( void );

bool    DX9_SaveZWriteState( void );
bool    DX9_LoadZWriteState( void );

/****** Stencil *********************************************************/
bool    DX9_SaveStencilState( void );
bool    DX9_LoadStencilState( void );

bool    DX9_SaveStencilTwoSidedState( void );
bool    DX9_LoadStencilTwoSidedState( void );

bool    DX9_SaveStencilFuncState( void );
bool    DX9_LoadStencilFuncState( void );

/****** Stencil CW ******************************************************/
bool    DX9_SaveStencilFailState( void );

bool    DX9_LoadStencilFailState( void );
bool    DX9_SaveStencilZFailState( void );

bool    DX9_LoadStencilZFailState( void );
bool    DX9_SaveStencilPassState( void );
bool    DX9_LoadStencilPassState( void );

/****** Stencil CCW *****************************************************/
bool    DX9_SaveStencilFailCCWState( void );
bool    DX9_LoadStencilFailCCWState( void );

bool    DX9_SaveStencilZFailCCWState( void );
bool    DX9_LoadStencilZFailCCWState( void );

bool    DX9_SaveStencilPassCCWState( void );
bool    DX9_LoadStencilPassCCWState( void );

bool    DX9_SaveStencilRefState( void );
bool    DX9_LoadStencilRefState( void );

bool    DX9_SaveStencilReadMaskState( void );
bool    DX9_LoadStencilReadMaskState( void );

bool    DX9_SaveStencilWriteMaskState( void );
bool    DX9_LoadStencilWriteMaskState( void );

/****** Culling *********************************************************/
bool    DX9_SaveCullingState( void );
bool    DX9_LoadCullingState( void );

/****** Color ***********************************************************/
bool    DX9_SaveColorWriteState( void );
bool    DX9_LoadColorWriteState( void );

/****** Blending ********************************************************/
bool    DX9_SaveAlphaBlendState( void );
bool    DX9_LoadAlphaBlendState( void );

bool    DX9_SaveAlphaFuncState( void );
bool    DX9_LoadAlphaFuncState( void );

bool    DX9_SaveSrcBlendState( void );
bool    DX9_LoadSrcBlendState( void );

bool    DX9_SaveDstBlendState( void );
bool    DX9_LoadDstBlendState( void );

EXTERN_END

#endif/*_SAMT_DX9CTRL_H_*/
