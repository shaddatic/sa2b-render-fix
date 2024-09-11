/*
*   Sonic Adventure Mod Tools (SA2B) - '/soc/render.h'
*
*   Description:
*       SoC's 'Render' struct.
*
*   Contributors:
*     - SEGA of China
*     - kellnc
*     - MainMemory
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SOC_RENDER_H_
#define _SOC_RENDER_H_

#ifdef  __cplusplus

/************************/
/*  Includes            */
/************************/
/****** Ninja ***********************************************************************/
#include <sa2b/ninja/njmatrix.h>

/****** Magic ***********************************************************************/
#include <sa2b/magic/rendercore.h>

/************************/
/*  Abstract Types      */
/************************/
#ifndef _D3D9_H_

typedef struct D3DVIEWPORT9
{
    u32 X;
    u32 Y;
    u32 Width;
    u32 Height;
    f32 MinZ;
    f32 MaxZ;
}
D3DVIEWPORT9;

#endif/*_D3D9_H_*/

/************************/
/*  Structures          */
/************************/
struct SOCRender
{
    char gap_0[20];
    int field_14;
    int field_18;
    int FogMode;
    float FogStart;
    float FogEnd;
    NJS_ARGB FogColor;
    char gap_28[752];
    NJS_MATRIX Matrix1;
    NJS_MATRIX Matrix2;
    NJS_MATRIX Matrix3;
    NJS_MATRIX TextureMatrices[4];
    char gap_36C[256];
    int field_5E8;
    int field_5EC;
    int field_5F0;
    int field_5F4;
    int field_5F8;
    int field_5FC;
    int field_600;
    int field_604;
    D3DVIEWPORT9 m_ViewPort;
    Magic::RenderCore::SamplerState_t m_SamplerState;
    int field_63C;
    char gap_640[4];
    byte ReloadShaders;
    void* pShaderData;
    int field_64C;
    int field_650;
    int field_654;
    int field_658;
    int field_65C;
    int field_660;
    int field_664;
    int field_668;
    int field_66C;
    int field_670;
    int field_674;
    int field_678;
    Magic::RenderCore::RenderDeviceInitInfo_t m_InitInfo;
};

/************************/
/*  Data                */
/************************/
#define g_pSOCRender        DATA_REF(SOCRender*, 0x01A557BC)

#endif/*__cplusplus*/

#endif/*_SOC_RENDER_H_*/
