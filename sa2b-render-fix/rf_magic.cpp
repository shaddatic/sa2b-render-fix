#include <sa2b/core.h>

/** Magic **/
#include <sa2b/magic/magic.h>

/** Render Fix **/
#include <rf_core.h>

/** Self **/
#include <rf_magic.h>

/** Enum def **/
using enum Magic::RenderCore::RenderDevice::RenderState;

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
