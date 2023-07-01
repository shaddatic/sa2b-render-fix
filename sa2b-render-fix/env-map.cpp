#include <sa2b/core.h>
#include <sa2b/memtools.h>
#include <sa2b/config.h>

#include <sa2b/ninja/ninja.h>

const int njCnkDrawModel_p = 0x0042E660;

__declspec(naked)
static void
__FixCnkDrawModel()
{
	__asm
	{
		push eax
		call njCnkDrawModel_p
		pop eax
		retn
	}
}

static void
FlipEnv2(NJS_MATRIX* mat0, NJS_MATRIX* mat1, NJS_MATRIX* mat2)
{
	*mat0[0] = 0.5f;
	gjMultiMatrix(mat0, mat1, mat2);
}

__declspec(naked)
static void
__FlipEnv2()
{
	__asm
	{
		push ecx
		push edx
		push eax
		call FlipEnv2
		pop eax
		pop edx
		pop ecx
		retn
	}
}

#define SECT "env"

void
EnvMapSettings(const config* conf)
{
	if (ConfigGetInt(conf, SECT, "fix", 1))
	{
		WriteJump(0x0042E6C0, __FixCnkDrawModel);
	}

	if (ConfigGetInt(conf, SECT, "flip", 1))
	{
		WriteCall(0x0042D4B0, __FlipEnv2); // Chunk
		WriteCall(0x0042B6A4, __FlipEnv2); // Ginja
		WriteCall(0x0056DEEB, __FlipEnv2); // chDraw
	}
}