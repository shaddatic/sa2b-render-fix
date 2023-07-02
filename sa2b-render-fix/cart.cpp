#include <sa2b/core.h>
#include <sa2b/memtools.h>
#include <sa2b/config.h>

DataRef(int, FogEnable, 0x025EFFCC);

FuncPtr(void, __cdecl, CartSeaDisplay, (), 0x00621C90);
FuncPtr(void, __cdecl, UpdateFog, (), 0x0042A870);

static void
DrawCartSea()
{
	FogEnable = 0;
	UpdateFog();

	CartSeaDisplay();

	FogEnable = 1;
	UpdateFog();
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