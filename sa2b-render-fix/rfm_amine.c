#include <sa2b/core.h>
#include <sa2b/writemem.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>

/** Self **/
#include <rfm_amine.h>

EXTERN Sint32 vertex_minemizu[];

static void
MurkyWaterRestore(void)
{
    WritePointer(0x0162E024, vertex_minemizu);
}

void
RFM_AquaticMineInit(void)
{
    if (RF_ConfigGetInt(CNF_AM_MURKY))
    {
        MurkyWaterRestore();
    }
}
