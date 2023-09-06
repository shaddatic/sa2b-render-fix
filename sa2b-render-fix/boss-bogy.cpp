#include <sa2b/core.h>
#include <sa2b/config.h>

#include <sa2b/src/light.h>

#include <tools.h>

static LIGHT lights_bigbogy[] =
{
    { { 0.0f, 0.707f, 0.707f }, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f },
    { { 0.0f, 0.707f, 0.707f }, 0.3f, 0.6f, 1.0f, 1.0f, 1.0f },
    { { 0.0f, 0.707f, 0.707f }, 0.5f, 0.8f, 1.0f, 1.0f, 1.0f },
    { { 0.0f, 0.707f, 0.707f }, 0.0f, 1.0f, 1.0f, 0.5f, 0.5f }
};

static void
SunDoorsFix()
{
	SwapGVMTableIndex(0x0103622C, 2, 4);
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