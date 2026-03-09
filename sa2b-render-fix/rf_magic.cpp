#include <samt/core.h>

/** Magic **/
#include <samt/magic/magic.h>

/** Render Fix **/
#include <rf_core.h>

/** Self **/
#include <rf_magic.h>

/** Enum def **/
using enum Magic::RenderCore::RenderDevice::RenderState;

EXTERN
void
RF_MagicSetAlphaTestEnable(bool state)
{
    g_pRenderDevice->vft->SetRenderState(g_pRenderDevice, RS_ALPHA_TEST_ENABLE, state);
}

EXTERN
void
RF_MagicSetAlphaRef(uint32_t value)
{
    g_pRenderDevice->vft->SetRenderState(g_pRenderDevice, RS_ALPHA_REF, value);
}

EXTERN
void
RF_MagicSetAlphaTestFunc(RFE_MAGIC_CMP func)
{
    g_pRenderDevice->vft->SetRenderState(g_pRenderDevice, RS_ALPHA_TEST_FUNC, func);
}

EXTERN
void
RF_MagicSetZEnable(bool state)
{
    g_pRenderDevice->vft->SetRenderState(g_pRenderDevice, RS_Z_ENABLE, state);
}

EXTERN
void
RF_MagicSetZWrite(bool state)
{
    g_pRenderDevice->vft->SetRenderState(g_pRenderDevice, RS_Z_WRITE_ENABLE, state);
}


EXTERN
void
RF_MagicSetZFunc(RFE_MAGIC_CMP func)
{
    g_pRenderDevice->vft->SetRenderState(g_pRenderDevice, RS_Z_TEST_FUNC, func);
}

EXTERN
void
RF_MagicSetPointSize(float size)
{
    g_pRenderDevice->vft->SetRenderState(g_pRenderDevice, RS_POINTSIZE, (uint32_t)(size * 0.300000011920929f));
}

EXTERN
void
RF_MagicSetShaderConstantMatrix(RFE_MAGIC_SHADER type, int32_t reg, const float* mtx)
{
    g_pRenderDevice->vft->ShaderSetConstant8(g_pRenderDevice, type, reg, (const Magic::MATH::Matrix4<float>*)mtx);
}

EXTERN
void
RF_MagicSetShaderConstantVec4(RFE_MAGIC_SHADER type, int32_t reg, float x, float y, float z, float w)
{
    const Magic::MATH::Vector4<float> vec4 = {
        .x = x,
        .y = y,
        .z = z,
        .w = w
    };

    g_pRenderDevice->vft->ShaderSetConstant9(g_pRenderDevice, type, reg, &vec4);
}

EXTERN
void
RF_MagicSetShaderConstantFloat(RFE_MAGIC_SHADER type, int32_t reg, f32 f, int32_t i)
{
    g_pRenderDevice->vft->ShaderSetConstant10(g_pRenderDevice, type, reg, &f, i);
}

EXTERN
void
RF_MagicSetShaderConstantTexture(RFE_MAGIC_SHADER type, int32_t reg, void* pTex, RF_MAGICSAMPLER* pSamplerState)
{
    g_pRenderDevice->vft->ShaderSetConstant7(g_pRenderDevice, type, reg, (Magic::RenderCore::Texture*)pTex, (Magic::RenderCore::SamplerState_t*)pSamplerState);
}

EXTERN
void
RF_MagicSetShaderConstantColor(RFE_MAGIC_SHADER type, int32_t reg, RF_MAGICCOLOR* p)
{
    g_pRenderDevice->vft->ShaderSetConstant10(g_pRenderDevice, type, reg, (float*)p, 4);
}

EXTERN
RF_MAGIC_STATECACHE*
RF_MagicGetStateCache(void)
{
    return (RF_MAGIC_STATECACHE*)&g_pRenderDevice->m_pShaderGroup;
}

#define DeviceResetFunc             DATA_REF(Magic::RenderCore::OnDeviceResetFunc*, 0x174F81C)
#define DeviceLostFunc              DATA_REF(Magic::RenderCore::OnDeviceLostFunc* , 0x174F820)

EXTERN
void
RF_MagicGetRenderDeviceInitInfo(RF_MAGIC_DEVICEINFO* pInfo)
{
    g_pRenderDevice->vft->GetRenderDeviceInitInfo(g_pRenderDevice, (Magic::RenderCore::RenderDeviceInitInfo_t*)pInfo);
}

EXTERN
void
RF_MagicResetRenderDeviceInitInfo(const RF_MAGIC_DEVICEINFO* pInfo)
{
    g_pRenderDevice->vft->ResetRenderDeviceInitInfo(g_pRenderDevice, (Magic::RenderCore::RenderDeviceInitInfo_t*)pInfo, &DeviceLostFunc, &DeviceResetFunc);
}

EXTERN
void
RF_MagicSetRenderDeviceInitInfo(const RF_MAGIC_DEVICEINFO* pInfo)
{
    #define FmtConv     DATA_ARY(u32, 0x0174BD08, [6][2])

    struct PRESENT_PARAMS
    {
        u32 BackBufferWidth;
        u32 BackBufferHeight;
        i32 BackBufferFormat;
        u32 BackBufferCount;
        i32 MultiSampleType;
        u32 MultiSampleQuality;
        i32 SwapEffect;
        void* hDeviceWindow;
        b32 Windowed;
        b32 EnableAutoDepthStencil;
        i32 AutoDepthStencilFormat;
        u32 Flags;
        u32 FullScreen_RefreshRateInHz;
        u32 PresentationInterval;
    };

    PRESENT_PARAMS* params = (PRESENT_PARAMS*) g_pRenderDevice->m_pDeviceCreator->m_D3DPP;

    params->BackBufferFormat = FmtConv[pInfo->BackBufferFormat][1];
    params->MultiSampleType  = pInfo->MultiSampleType;

    RF_MagicResetRenderDeviceInitInfo(pInfo);
}
