#include <sa2b/core.h>
#include <sa2b/memtools.h>
#include <sa2b/config.h>

#include <sa2b/ninja/ninja.h>

#include <tools.h>

static void
ParticleFix()
{
	extern NJS_CNK_OBJECT object_eget[];

	SwitchDisplayer(0x0079860F, DISP_SORT);
	WriteData(0x0096DE1C, *object_eget, NJS_CNK_OBJECT);
}

static void
FadeRestore()
{
	WriteNoOP(0x006049A8, 0x006049AE); /* Stop FadeColor being set to 0 */
}

#define SECT "eget"

void
GetEmblemSettings(const config* conf)
{
	if (ConfigGetInt(conf, SECT, "fadein", 1))
	{
		FadeRestore();
	}

	if (ConfigGetInt(conf, SECT, "sparkle", 1))
	{
		ParticleFix();
	}
}