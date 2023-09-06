#include <sa2b/core.h>
#include <sa2b/memtools.h>
#include <sa2b/config.h>

#include <sa2b/ninja/ninja.h>

#define SECT "a_mine"

extern Sint32 vertex_minemizu[];

static void
MurkyWaterRestore()
{
	WritePointer(0x0162E024, vertex_minemizu);
}

void
AquaticMineSettings(const config* conf)
{
	if (ConfigGetInt(conf, SECT, "murky", 1))
	{
		MurkyWaterRestore();
	}
}