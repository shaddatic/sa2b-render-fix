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
#define COLORWRITE_NONE    (0x0)
#define COLORWRITE_RED     (0x1)
#define COLORWRITE_GREEN   (0x2)
#define COLORWRITE_BLUE    (0x4)
#define COLORWRITE_ALPHA   (0x8)

/************************/
/*  Enums               */
/************************/
typedef enum
{
    COMPARE_NEVER = 1,
    COMPARE_LESS = 2,
    COMPARE_EQUAL = 3,
    COMPARE_LESS_EQUAL = 4,
    COMPARE_GREATER = 5,
    COMPARE_NOT_EQUAL = 6,
    COMPARE_GREATER_EQUAL = 7,
    COMPARE_ALWAYS = 8
}
D3D_CompareOp;

typedef enum
{
    STENCIL_KEEP = 1,
    STENCIL_ZERO = 2,
    STENCIL_REPLACE = 3,
    STENCIL_INCREMENT_CLAMP = 4,
    STENCIL_DECREMENT_CLAMP = 5,
    STENCIL_INVERT = 6,
    STENCIL_INCREMENT = 7,
    STENCIL_DECREMENT = 8
}
D3D_StencilOp;

EXTERN_START

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
void    D3D_ZFunc(const D3D_CompareOp op);

/************************/
/*  Stencil Buffer      */
/************************/
void    D3D_StencilEnable();
void    D3D_StencilDisable();

/** Stencil Compare Function */
void    D3D_StencilFunc(const D3D_CompareOp op);

/** Stencil Operations **/
void    D3D_StencilFail(const D3D_StencilOp op);
void    D3D_StencilZFail(const D3D_StencilOp op);
void    D3D_StencilPass(const D3D_StencilOp op);

/** Stencil Values **/
void    D3D_StencilReference(const int ref);
void    D3D_StencilReadMask(const int mask);
void    D3D_StencilWriteMask(const int mask);
void    D3D_StencilMask(const int mask);    /* Read and Write combined */

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

/************************/
/*  Color Write         */
/************************/
void    D3D_ColorWrite(const int flags);

EXTERN_END

#endif /* _SAMT_D3DCONTROL_H_ */