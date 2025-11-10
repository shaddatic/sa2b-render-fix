/*
*   SA2 Render Fix - '/rf_magic.h'
*
*   Description:
*       Wrapper functions for Magic's C++ interface.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_MAGIC_H_
#define _RF_MAGIC_H_

/************************/
/*  Enums               */
/************************/
typedef enum
{
    MAGIC_CMP_NEVER,
    MAGIC_CMP_LESS,
    MAGIC_CMP_EQUAL,
    MAGIC_CMP_LESSEQUAL,
    MAGIC_CMP_GREATER,
    MAGIC_CMP_NOTEQUAL,
    MAGIC_CMP_GREATEREQUAL,
    MAGIC_CMP_ALWAYS,
}
RFE_MAGIC_CMP;

typedef enum
{
    MAGIC_SHADER_VERTEX,
    MAGIC_SHADER_PIXEL,
}
RFE_MAGIC_SHADER;

/************************/
/*  Structures          */
/************************/
/****** Magic Texture ***************************************************************/
typedef struct
{
    void* vtbl;
    int restype;
    int respool;
    void* texture;  // dx9_texture
    int resmask;
    byte cppstrs[56];
    int type;
    int size;
    int flags;
    int width;
    int height;
    int depth;
    int format;
    int usage;
    int mipmaplevels;
    bool locked;
}
RF_MAGICTEXTURE;

/****** Magic Sampler Data **********************************************************/
typedef struct
{
    s32     MinFilter;
    s32     MagFilter;
    s32     MipFilter;
    s32     AddressU;
    s32     AddressV;
    s32     AddressW;
    s32     BorderColor;
}
RF_MAGICSAMPLER;

/****** Magic Color *****************************************************************/
typedef struct
{
    f32     r, g, b, a;
}
RF_MAGICCOLOR;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Set alpha test params **/
void    RF_MagicSetAlphaTestEnable(bool state);
void    RF_MagicSetAlphaRef(uint32_t value);
void    RF_MagicSetAlphaTestFunc(RFE_MAGIC_CMP func);

/** Set Z test params **/
void    RF_MagicSetZEnable(bool state);
void    RF_MagicSetZWrite(bool state);
void    RF_MagicSetZFunc(RFE_MAGIC_CMP func);

/** Set size of point primitives in pixels **/
void    RF_MagicSetPointSize( float size );

/** Set shader constant using a matrix 4x4 **/
void    RF_MagicSetShaderConstantMatrix(RFE_MAGIC_SHADER type, int32_t reg, const float* mtx);

/** Set shader constant using a vector4 **/
void    RF_MagicSetShaderConstantVec4( RFE_MAGIC_SHADER type, int32_t reg, float x, float y, float z, float w );

/** Set shader constant using a float **/
void    RF_MagicSetShaderConstantFloat(RFE_MAGIC_SHADER type, int32_t reg, f32 f, int32_t i);

/** set texture shader constant **/
void    RF_MagicSetShaderConstantTexture(RFE_MAGIC_SHADER type, int32_t reg, void* pTex, RF_MAGICSAMPLER* pSamplerState);

/** set color shader constant **/
void    RF_MagicSetShaderConstantColor(RFE_MAGIC_SHADER type, int32_t reg, RF_MAGICCOLOR* p);

typedef struct
{
    void* vshader;
    void* pshader;
}
RF_MAGIC_SHADERCACHE;

typedef struct
{
    RF_MAGIC_SHADERCACHE* shader;
    void* vdecl;
    void* vbufs[4];
    void* ixbuf;
    void* vstexs[4];
    RF_MAGICSAMPLER vssampler[4];
    void* pstexs[16];
    RF_MAGICSAMPLER pssampler[16];
}
RF_MAGIC_STATECACHE;

RF_MAGIC_STATECACHE*  RF_MagicGetStateCache( void );

EXTERN_END

#endif/*_RF_MAGIC_H_*/
