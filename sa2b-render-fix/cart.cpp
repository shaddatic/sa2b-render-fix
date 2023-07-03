#include <sa2b/core.h>
#include <sa2b/memtools.h>
#include <sa2b/config.h>

#include <sa2b/ninja/ninja.h>

FuncPtr(void, __cdecl, CartSeaDisplay, (), 0x00621C90);


static void
DrawCartSea()
{
	njFogDisable();
	CartSeaDisplay();
	njFogEnable();
}

static void
CartSeaFix()
{
	WriteJump(0x00622075, DrawCartSea);
}

#define SECT "cart"

void
CartSettings(const config* conf)
{
	if (ConfigGetInt(conf, SECT, "seafix", 1))
	{
		CartSeaFix();
	}
}