#include <sa2b/core.h>
#include <sa2b/memutil.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>

/** Self **/
#include <rfm_cart.h>

#define CartSeaDisplay      FuncPtr(void, __cdecl, (void), 0x00621C90)

static void
DrawCartSea(void)
{
    njFogDisable();
    CartSeaDisplay();
    njFogEnable();
}

void
RFM_CartInit(void)
{
    if (RF_ConfigGetInt(CNF_CART_SEAFIX))
    {
        WriteJump(0x00622075, DrawCartSea);
    }

    if (RF_ConfigGetInt(CNF_CART_KANBAN))
    {
        WriteNoOP(0x006220CE, 0x006220E5);
    }
}