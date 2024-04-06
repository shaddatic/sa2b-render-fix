#include <sa2b/core.h>
#include <sa2b/memutil.h>
#include <sa2b/mods.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_shader.h>
#include <rf_usermsg.h>

void
RFG_SpotLightFixInit(void)
{
    d3d_vtx_shader* sonic_vs = RF_LoadVtxShader("sonic_vs");

    for (int i = 1; i < 8; ++i)
        RF_ReplaceVtxShader(i, sonic_vs);
}
