#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/writemem.h>
#include <sa2b/writeop.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Game **/
#include <sa2b/sonic/light.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_util.h>

/** Self **/
#include <rfm_b_bigbogy.h>

static LIGHT lights_bigbogy[] =
{
    { { 0.0f, 0.707f, 0.707f }, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f },
    { { 0.0f, 0.707f, 0.707f }, 0.3f, 0.6f, 1.0f, 1.0f, 1.0f },
    { { 0.0f, 0.707f, 0.707f }, 0.5f, 0.8f, 1.0f, 1.0f, 1.0f },
    { { 0.0f, 0.707f, 0.707f }, 0.0f, 1.0f, 1.0f, 0.5f, 0.5f }
};

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

void
RFM_BossBogyInit(void)
{
    if (RF_ConfigGetInt(CNF_BBOGY_SUNDOORS))
    {
        SwapTexFileTableIndex(0x0103622C, 2, 4);
    }

    if (RF_ConfigGetInt(CNF_BBOGY_LIGHTS))
    {
        MemCopy((void*)0x01036738, lights_bigbogy, sizeof(lights_bigbogy));
    }

    if (RF_ConfigGetInt(CNF_BBOGY_PULSE))
    {
        WriteJump(0x006190A0, GetMatAlphaPointer);
        MemCopy((void*)0x010024D4, GlowPulseParams, sizeof(GlowPulseParams));
    }
}
