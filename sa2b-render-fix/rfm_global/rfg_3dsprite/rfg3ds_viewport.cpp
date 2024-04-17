#include <sa2b/core.h>

/** Magic **/
#include <sa2b/magic/magic.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/display.h>

/** Render Fix **/
#include <rf_core.h>

EXTERN
void
RFG3DS_SendResToShader(void)
{
    const float adj_w = _nj_screen_.w / 640.0f;
    const float adj_h = _nj_screen_.h / 480.0f;

    const float res_w = DisplayResolutionX * adj_w;
    const float res_h = DisplayResolutionY * adj_h;

    const float asp_w = res_w / _nj_screen_.w;
    const float asp_h = res_h / _nj_screen_.h / asp_w;

    const Magic::MATH::Vector4<float> vec4 = {
        .x = res_w,
        .y = res_h,
        .z = asp_w / adj_h,
        .w = asp_h / adj_w
    };

    g_pRenderDevice->vft->ShaderSetConstant9(g_pRenderDevice, 0, 104, &vec4);
}
