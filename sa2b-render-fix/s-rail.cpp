#include <sa2b/core.h>
#include <sa2b/config.h>
#include <sa2b/memtools.h>

#include <sa2b/ninja/ninja.h>

static void
CloudLayerRestore()
{
    WritePointer(0x005BA0F6, 0x0117EEEC);
    WritePointer(0x005BA13E, 0x0117EE34);
}

#define SECT "s_rail"

void
SkyRailSettings(const config* conf)
{
    if (ConfigGetInt(conf, SECT, "clouds", 1))
    {
        CloudLayerRestore();
    }
}