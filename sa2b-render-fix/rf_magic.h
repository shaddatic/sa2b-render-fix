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

EXTERN_END

#endif/*_RF_MAGIC_H_*/
