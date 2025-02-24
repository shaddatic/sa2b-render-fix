#include <samt/core.h>
#include <samt/writemem.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

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
