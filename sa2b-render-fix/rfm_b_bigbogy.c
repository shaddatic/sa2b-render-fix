#include <samt/core.h>
#include <samt/memory.h>
#include <samt/writemem.h>
#include <samt/writeop.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Game **/
#include <samt/sonic/light.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_util.h>

static uint8_t GlowPulseParams[] = 
{ 
    0x32, 0xB4, 0x32, 0x0, 0xB4, 0x0, 0x0, 0x0 
};

static uint8_t*
GetMatAlphaPointer(NJS_CNK_OBJECT* pObject)
{
    if (!pObject || !pObject->model)
        return NULL;

    uint8_t* p = (u8*)pObject->model->plist;

    if (!p)
        return NULL;

    return p + 7;
}

static void
LoadBossBogyLightFile(void)
{
    LoadLightFile("stg63_light.bin");
}

void
RFM_BossBogyInit(void)
{
    if (RF_ConfigGetInt(CNF_BBOGY_SUNDOORS))
    {
        SwapTexFileTableIndex(0x0103622C, 2, 4);
    }

    if (RF_ConfigGetInt(CNF_BBOGY_PULSE))
    {
        WriteJump(0x006190A0, GetMatAlphaPointer);
        mtMemCopy((void*)0x010024D4, GlowPulseParams, sizeof(GlowPulseParams));
    }

    // load light file
    WriteNOP( 0x0060A8E2, 0x0060A939);
    WriteCall(0x0060A8E2, LoadBossBogyLightFile);
}
