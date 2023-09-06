#include <sa2b/core.h>
#include <sa2b/memtools.h>
#include <sa2b/config.h>

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/light.h>

#include <tools.h>

static LIGHT lights_bigbogy[] =
{
    { { 0.0f, 0.707f, 0.707f }, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f },
    { { 0.0f, 0.707f, 0.707f }, 0.3f, 0.6f, 1.0f, 1.0f, 1.0f },
    { { 0.0f, 0.707f, 0.707f }, 0.5f, 0.8f, 1.0f, 1.0f, 1.0f },
    { { 0.0f, 0.707f, 0.707f }, 0.0f, 1.0f, 1.0f, 0.5f, 0.5f }
};

static uint8 GlowPulseParams[] = 
{
    0x32, 0xB4, 0x32, 0x0, 0xB4, 0x0, 0x0, 0x0 
};

static uint8*
GetMatAlphaPointer(NJS_CNK_OBJECT* pObject)
{
    if (!pObject || !pObject->model)
        return NULL;

    uint8* p = (uint8*)pObject->model->plist;

    if (!p)
        return NULL;

    return p + 7;
}

void
BossBogySettings(const config* conf)
{
	if (ConfigGetInt(conf, SECT, "sundoors", 1))
	{
        SwapGVMTableIndex(0x0103622C, 2, 4);
	}

    if (ConfigGetInt(conf, SECT, "lights", 1))
    {
        memcpy((void*)0x01036738, lights_bigbogy, sizeof(lights_bigbogy));
}

    if (ConfigGetInt(conf, SECT, "glowpulse", 1))
    {
        WriteJump(0x006190A0, GetMatAlphaPointer);
        memcpy((void*)0x010024D4, GlowPulseParams, sizeof(GlowPulseParams));
    }
}