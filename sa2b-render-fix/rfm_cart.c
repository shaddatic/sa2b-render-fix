#include <sa2b/core.h>
#include <sa2b/writemem.h>
#include <sa2b/writeop.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_util.h>
#include <rf_config.h>

/** Self **/
#include <rfm_cart.h>

#define CartSeaDisplay      FUNC_PTR(void, __cdecl, (void), 0x00621C90)

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
        WriteData(0x006224EC, -1063 + 39, s32);
    }

    switch (RF_ConfigGetInt(CNF_CART_CARTSPRITE)) {

        static const double SpriteSubtract = 6.0;

    case CNFE_CART_CARTSPRITE_DREAMCAST:
        WriteNOP(0x0061CB07, 0x0061CB0C);
        break;

    case CNFE_CART_CARTSPRITE_ENABLED:
        ReplaceFloat(0x0061EE25, &SpriteSubtract);
        break;
    }

    if (RF_ConfigGetInt(CNF_CART_ZANKI))
    {
        /** Okay, but how does a mistake like this occur? **/
        static const float zanki_py = 424.0f + 3.0f + 7.0f;

        ReplaceFloat(0x0044E78F, &zanki_py);
    }
}
