#include <sa2b/core.h>
#include <sa2b/config.h>

#include <tools.h>

#define SECT "bossbogy"

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
}