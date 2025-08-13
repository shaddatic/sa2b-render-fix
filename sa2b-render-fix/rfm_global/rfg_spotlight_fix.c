#include <samt/core.h>
#include <samt/writemem.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_shader.h>
#include <rf_usermsg.h>

void
RFG_SpotLightFixInit(void)
{
    RFS_VSHADER* sonic_vs = RF_LoadVtxShader("sonic_vs");

    for (RFE_SHADERIX ix_shader = RFE_SHADERIX_MDL_NONE; ix_shader <= RFE_SHADERIX_MDL_PFS; ++ix_shader)
    {
        RF_SetGameVShader(ix_shader, sonic_vs);
    }
}
