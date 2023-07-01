#include <sa2b/core.h>
#include <sa2b/memtools.h>
#include <sa2b/config.h>

#include <sa2b/ninja/ninja.h>

#define SECT "a_mine"

extern NJS_CNK_MODEL model_minemizu[];

static void
MurkyWaterRestore()
{
	WritePointer(0x0162E024, model_minemizu->vlist);
}

void
AquaticMineSettings(const config* conf)
{
	if (ConfigGetInt(conf, SECT, "murky", 1))
	{
		MurkyWaterRestore();
	}
}