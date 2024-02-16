/*
*   Sonic Adventure Mod Tools (SA2B) - '/d3dcontrol.h'
*
*   Contains functions to control the DirectX renderer
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SAMT_D3DCONTROL_H_
#define _SAMT_D3DCONTROL_H_

/************************/
/*  Flags               */
/************************/
#define D3D_COLORWRITE_NONE    (0x0)
#define D3D_COLORWRITE_RED     (0x1)
#define D3D_COLORWRITE_GREEN   (0x2)
#define D3D_COLORWRITE_BLUE    (0x4)
#define D3D_COLORWRITE_ALPHA   (0x8)

/************************/
/*  Enums               */
/************************/
typedef enum
{
    D3D_COMPARE_NEVER = 1,
    D3D_COMPARE_LESS,
    D3D_COMPARE_EQUAL,
    D3D_COMPARE_LESS_EQUAL,
    D3D_COMPARE_GREATER,
    D3D_COMPARE_NOT_EQUAL,
    D3D_COMPARE_GREATER_EQUAL,
    D3D_COMPARE_ALWAYS,
}
d3d_compare_op;

typedef enum
{
    D3D_STENCIL_KEEP = 1,
    D3D_STENCIL_ZERO,
    D3D_STENCIL_REPLACE,
    D3D_STENCIL_INCREMENT_CLAMP,
    D3D_STENCIL_DECREMENT_CLAMP,
    D3D_STENCIL_INVERT,
    D3D_STENCIL_INCREMENT,
    D3D_STENCIL_DECREMENT,
}
d3d_stencil_op;

typedef enum
{
    D3D_BLEND_ZERO = 1,
    D3D_BLEND_ONE,
    D3D_BLEND_SRCCOLOR,
    D3D_BLEND_INVSRCCOLOR,
    D3D_BLEND_SRCALPHA,
    D3D_BLEND_INVSRCALPHA,
    D3D_BLEND_DESTALPHA,
    D3D_BLEND_INVDESTALPHA,
    D3D_BLEND_DESTCOLOR,
    D3D_BLEND_INVDESTCOLOR,
    D3D_BLEND_SRCALPHASAT,
    D3D_BLEND_BOTHSRCALPHA,
    D3D_BLEND_BOTHINVSRCALPHA,
    D3D_BLEND_BLENDFACTOR,
    D3D_BLEND_INVBLENDFACTOR,
    D3D_BLEND_SRCCOLOR2,
    D3D_BLEND_INVSRCCOLOR2,
}
d3d_blend_op;

/*
*   Vertex Element
*/
enum
{
    D3D_VTXELE_TYPE_FLOAT1,
    D3D_VTXELE_TYPE_FLOAT2,
    D3D_VTXELE_TYPE_FLOAT3,
    D3D_VTXELE_TYPE_FLOAT4,
    D3D_VTXELE_TYPE_COLOR,
    D3D_VTXELE_TYPE_UBYTE4,
    D3D_VTXELE_TYPE_SHORT2,
    D3D_VTXELE_TYPE_SHORT4,
    D3D_VTXELE_TYPE_UBYTE4N,
    D3D_VTXELE_TYPE_SHORT2N,
    D3D_VTXELE_TYPE_SHORT4N,
    D3D_VTXELE_TYPE_USHORT2N,
    D3D_VTXELE_TYPE_USHORT4N,
    D3D_VTXELE_TYPE_UDEC3,
    D3D_VTXELE_TYPE_DEC3N,
    D3D_VTXELE_TYPE_FLOAT16_2,
    D3D_VTXELE_TYPE_FLOAT16_4,
    D3D_VTXELE_TYPE_UNUSED,
};

enum
{
    D3D_VTXELE_METHOD_DEFAULT,
    D3D_VTXELE_METHOD_PARTIALU,
    D3D_VTXELE_METHOD_PARTIALV,
    D3D_VTXELE_METHOD_CROSSUV,
    D3D_VTXELE_METHOD_UV,
    D3D_VTXELE_METHOD_LOOKUP,
    D3D_VTXELE_METHOD_LOOKUPPRESAMPLED,
};

enum
{
    D3D_VTXELE_USAGE_POSITION,
    D3D_VTXELE_USAGE_BLENDWEIGHT,
    D3D_VTXELE_USAGE_BLENDINDICES,
    D3D_VTXELE_USAGE_NORMAL,
    D3D_VTXELE_USAGE_PSIZE,
    D3D_VTXELE_USAGE_TEXCOORD,
    D3D_VTXELE_USAGE_TANGENT,
    D3D_VTXELE_USAGE_BINORMAL,
    D3D_VTXELE_USAGE_TESSFACTOR,
    D3D_VTXELE_USAGE_POSITIONT,
    D3D_VTXELE_USAGE_COLOR,
    D3D_VTXELE_USAGE_FOG,
    D3D_VTXELE_USAGE_DEPTH,
    D3D_VTXELE_USAGE_SAMPLE,
};

enum 
{
    D3D_PRIMTYPE_POINTLIST = 1,
    D3D_PRIMTYPE_LINELIST,
    D3D_PRIMTYPE_LINESTRIP,
    D3D_PRIMTYPE_TRIANGLELIST,
    D3D_PRIMTYPE_TRIANGLESTRIP,
    D3D_PRIMTYPE_TRIANGLEFAN,
};

EXTERN_START

/************************/
/*  Get Device          */
/************************/
/** Get IDirect3DDevice9 **/
void*   D3D_GetDirect3DDevice();

/************************/
/*  Render State        */
/************************/
void    D3D_SaveRenderState();
void    D3D_LoadRenderState();

/** Individual Functions **/
void    D3D_SaveVertexShader();
void    D3D_LoadVertexShader();

void    D3D_SavePixelShader();
void    D3D_LoadPixelShader();

void    D3D_SaveVertexDecl();
void    D3D_LoadVertexDecl();

void    D3D_SaveAlphaTestState();
void    D3D_LoadAlphaTestState();

void    D3D_SaveAlphaBlendState();
void    D3D_LoadAlphaBlendState();

void    D3D_SaveSrcBlend();
void    D3D_LoadSrcBlend();

void    D3D_SaveDstBlend();
void    D3D_LoadDstBlend();

void    D3D_SaveAlphaFunc();
void    D3D_LoadAlphaFunc();

void    D3D_SaveColorWriteState();
void    D3D_LoadColorWriteState();

void    D3D_SaveZWriteState();
void    D3D_LoadZWriteState();

void    D3D_SaveZState();
void    D3D_LoadZState();

void    D3D_SaveZFunc();
void    D3D_LoadZFunc();

void    D3D_SaveCullMode();
void    D3D_LoadCullMode();

void    D3D_SaveTwoSidedStencilMode();
void    D3D_LoadTwoSidedStencilMode();

/************************/
/*  Z Buffer            */
/************************/
void    D3D_ZReadEnable();
void    D3D_ZReadDisable();

void    D3D_ZWriteEnable();
void    D3D_ZWriteDisable();

/** Read and Write **/
void    D3D_ZEnable();
void    D3D_ZDisable();

/** Z Buffer Operations **/
void    D3D_ZFunc( const d3d_compare_op op );

/************************/
/*  Stencil Buffer      */
/************************/
/** Global Enable **/
void    D3D_StencilEnable();
void    D3D_StencilDisable();

/** Two sided mode **/
void    D3D_StencilTwoSidedEnable();
void    D3D_StencilTwoSidedDisable();

/** Stencil Compare Function */
void    D3D_StencilFunc( const d3d_compare_op op );

/** Stencil Operations **/
void    D3D_StencilFail(  const d3d_stencil_op op );
void    D3D_StencilZFail( const d3d_stencil_op op );
void    D3D_StencilPass(  const d3d_stencil_op op );

/** Stencil Operations (CCW) **/
void    D3D_StencilFailCCW(  const d3d_stencil_op op );
void    D3D_StencilZFailCCW( const d3d_stencil_op op );
void    D3D_StencilPassCCW(  const d3d_stencil_op op );

/** Stencil Values **/
void    D3D_StencilReference( const uint32_t ref );

void    D3D_StencilReadMask(  const uint32_t mask );
void    D3D_StencilWriteMask( const uint32_t mask );
void    D3D_StencilMask(      const uint32_t mask );    /* Read and Write combined */

/************************/
/*  Dither              */
/************************/
void    D3D_DitherEnable();
void    D3D_DitherDisable();

/************************/
/*  Specular            */
/************************/
void    D3D_SpecularEnable();
void    D3D_SpecularDisable();

/************************/
/*  Culling             */
/************************/
void    D3D_CullNone();
void    D3D_CullCCW();
void    D3D_CullCW();

/************************/
/*  Alpha Blending      */
/************************/
void    D3D_AlphaBlendEnable();
void    D3D_AlphaBlendDisable();

void    D3D_SrcBlend( const d3d_blend_op blend );
void    D3D_DstBlend( const d3d_blend_op blend );

/************************/
/*  Color Write         */
/************************/
void    D3D_ColorWrite( const uint32_t flags );

/************************/
/*  Depth Bias          */
/************************/
void    D3D_SlopeScaledDepthBias( const float32_t bias );
void    D3D_DepthBias( const float32_t bias );

/************************/
/*  Shader              */
/************************/
typedef void                d3d_vtx_shader;
typedef void                d3d_pxl_shader;

/*
*   Vertex Shader
*/
/** File must be pre-compiled before loading **/
d3d_vtx_shader* 
        D3D_LoadVtxShader(const utf8* fpath);

/** Set the current shader **/
bool    D3D_SetVtxShader(d3d_vtx_shader* pVtxShader);

/** Set shader constants
    p   : pointer to constant data
    reg : start register index
    nb# : number of data to set **/
bool    D3D_SetVtxShaderConstantF( const void* p, uint32_t reg, size_t nbFloat );
bool    D3D_SetVtxShaderConstantI( const void* p, uint32_t reg, size_t nbInt   );

/*
*   Pixel Shader
*/
/** File must be pre-compiled before loading **/
d3d_pxl_shader* 
        D3D_LoadPxlShader(const utf8* fpath);

/** Set the current shader **/
bool    D3D_SetPxlShader(d3d_pxl_shader* pPxlShader);

/** Set shader constants 
    p   : pointer to constant data 
    reg : start register index
    nb# : number of data to set **/
bool    D3D_SetPxlShaderConstantF( const void* p, uint32_t reg, size_t nbFloat );
bool    D3D_SetPxlShaderConstantI( const void* p, uint32_t reg, size_t nbInt   );

/************************/
/*  Vertex Declaration  */
/************************/
typedef struct _d3d_vtx_declaration     d3d_vtx_declaration;

typedef struct
{
    uint16_t    idxStream;
    uint16_t    idxOffset;
    uint8_t     type;
    uint8_t     method;
    uint8_t     usage;
    uint8_t     idxUsage;
}
d3d_vtx_element;

/** Use this as the last entry of your 'd3d_vtx_element' list **/
#define D3D_VTXELE_END()    { 0xFF, 0, D3D_VTXELE_TYPE_UNUSED, 0, 0, 0 }

/** Create a new 'd3d_vtx_decl' using a 'd3d_vtx_element' list **/
d3d_vtx_declaration*
        D3D_CreateVtxDeclaration( const d3d_vtx_element* pVtxElementList );

/** Set current vertex declaration **/
bool    D3D_SetVtxDeclaration( d3d_vtx_declaration* pVtxDeclaration );

/************************/
/*  Draw                */
/************************/
bool    D3D_DrawPrimitiveUP( int32_t typePrim, size_t nbPrim, const void* pVertexStream, size_t nbStride );

EXTERN_END

#endif/*_SAMT_D3DCONTROL_H_*/
