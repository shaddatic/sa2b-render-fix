#include <render-fix.h>

#include <sa2b/config.h>
#include <sa2b/memtools.h>
#include <sa2b/user.h>
#include <sa2b/mods.h>

#include <sa2b/modloader.h>

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

/*
*	Ginja
*/

static int GinjaObjectList[] =
{
	0x00B46A38, // Rocket Missile (base)
	0x00B3AA70, // Rocket (base)
	0x01176AE8, // Propeller Spring (blades & spring)
	0x0116598C, // Fire Skull (Sky Rail) (jaw & box)
	0x0161AA38, // Fire Skull (Aquatic Mine & Pool Quest) (jaw & box)
};

static int GinjaModelList[] =
{
	0x00B1ED2C, // 3SPRING (base)
	0x00B1E6AC, // 3SPRING 1
	0x00B54504, // SPRINGA (base)
	0x00B54214,	// SPRINGA (spring)
	0x00B53E34,	// SPRINGA (face)
	0x00B56160, // SPRINGB (base)
	0x00B54A4C, // SPRINGB (spring)
	0x00B5495C, // SPRINGB (face)
	0x00B0D7CC, // Knudai // Mystic Shrine
	0x00AEED4C, // Dammy // Metal Harbor Static Missiles
	0x011772D8, // Propeller Spring (base)
	0x01177334, // Propeller Spring (Bottom arrows)
	0x01177BF0, // Propeller Spring (Top arrows)
	0x011659C4, // Fire Skull (Sky Rail) (head)
	0x0160132C, // Fire Skull (Aquatic Mine & Pool Quest) (head)
	0x00B3B67C, // Nocol Skull
	0x01091CE4, // Tree ST Trunk
	0x01092464, // Tree SNB Trunk
};

/*
*	Chunk
*/

static int ChunkObjectList[] =
{
	0x00B39E7C, // Rocket
	0x00B452AC, // Rocket Missile
	0x014D05AC, // E Shouku // Jet planes
//	0x00B00B3C, // mhmissile (idle)		// Causes shadows to go white
//	0x00AFE18C, // mhmissile (takeoff)	// ^
	0x00EA2D00, // Rolling Tuta // Swing vine (horizontal)
	0x0104FC38, // Rolling Tuta Tate // Swing vine (vertical)
	0x01071FD0, // Bangie Tuta // Bungie vine
	0x00942374, // E Batabata
	0x00940774, // E Beeton
	0x00B0B88C, // Chao Key // Possibly too bright
	0x014B69D4, // E AI
	0x014BD4FC, // E AI Sheild
	0x014BA0CC, // E AI Lazer
	/* Levelupdai Equipment models */
	0x00B2190C, // Sonic Rubber Unit
	0x00B23EC4, // Sonic Shoes
	0x00B243C4, // Sonic Flame Ring
	0x00B26F4C, // Shadow Shoes
	0x00B25024, // Shadow Flame Ring
	0x00B27F64, // TWalker Booster
	0x00B29104, // TWalker Hypercannon
	0x00B2A42C, // TWalker Lazer Blaster
	0x00B2B53C, // EWalker Jet Engine
	0x00B2CD8C, // EWalker Bazooka
	0x00B2E644, // EWalker Powergun
	0x00B2FE1C, // Knuckles Claws
	0x00B2F644, // Knuckles Gloves
	0x00B301AC, // Knuckles Air
	0x00B30C24, // Rouge Scope
	0x00B32CB4, // Rouge Nails
	0x00B351EC, // Rouge Boots
	0x00B24B24, // Sonic Magic Wrist
	0x00B30744, // Knuckles Sunglasses
};

static int ChunkModelList[] =
{
	0x00B5674C, // SGRing
	0x00B43E1C, // Dash Panel (anim)
//	0x00B43C54, // Dash Panel (body)	// Absolutely too bright
	0x00B1CBDC, // Save Point Something
	0x00B1BD1C, // Save Point R
	0x00B1B564, // Save Point L
//	0x00B459CC, // Rocket Missile (Button) // Goes black
	0x00B35DC4, // Big Jump
	0x00B3589C, // Big Jump (Screen)
//	0x00B497C4, // Itembox (Glass)		// Too bright
	0x00B492EC, // Itembox Air (Base)
	0x00B48F64, // Itembox Air (Top)
//	0x00B48B44,	// Itembox Air (Glass)	// Too bright
	0x00B11ECC, // Solidbox
	0x00B4EC6C, // Goalring (text)
	0x00B4EE0C, // Goalring (text restart)
	0x00B1DE5C, // Chao Pipe
//	0x01681D28, // Fire Skull
	0x00B3C53C, // Basic Skull
	0x00B17AA4, // Switch (base)
	0x00BD3F54, // Bone (Cow Skull)
	0x00B20C04, // Levelupdai (base)
	0x00B20CF4, // Levelupdai (glow)
	0x00B21124, // Levelupdai (light)
};

/*
*	Extra
*/

static int GinjaModelListExtra[] =
{
	0x00B57134, // Ring LOD Far
	0x00B575C4, // Ring LOD Med
	0x00B57AD4, // Ring LOD Close
};

static int ChunkModelListExtra[] =
{
	0x00B3EA4C, // IronBall 2 Center
	0x00B3E49C, // IronBall 2 Cable
	0x00B3E374, // IronBall 2 Ball
};

/*
*	Environment Map Flip
*/

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

/*
*	Define Functions
*/

#define ModConflictWarning(body) UserWarningMessageBox("Render Fix: Mod Conflict", body)

/*
*	Dll Export
*/

extern "C" __declspec(dllexport)
void __cdecl
Init(const char* path, const HelperFunctions*)
{
	SAMT_Init(path, NULL);

	config* pconf = ConfigOpen2(path, "config.ini");

	int screentint = ConfigGetInt(pconf, "main", "objpak", 2);

	if (screentint)
		EditObjPak(screentint == 2, 0.5f);

	if (ConfigGetInt(pconf, "main", "stgsel_stretch", 1))
	{
		StageMapStretchFix();
	}

	if(ConfigGetInt(pconf, "main", "gidx_ignore", 1))
	{
		WriteValue(0x00431340, 0x9090, uint16);
	}

	if (ConfigGetInt(pconf, "env", "fix", 1))
	{
		WriteJump(0x0042E6C0, __FixCnkDrawModel);
	}

	if (ConfigGetInt(pconf, "env", "flip", 1))
	{
		WriteCall(0x0042D4B0, __FlipEnv2); // Chunk
		WriteCall(0x0042B6A4, __FlipEnv2); // Ginja
		WriteCall(0x0056DEEB, __FlipEnv2); // chDraw
	}

	if (ConfigGetInt(pconf, "rest", "emblem", 1))
	{
		if(CheckForMod("RestoredGUNLogos"))
		{
			ModConflictWarning(
				"The 'Restored GUN Logos' mod will conflict with Render Fix's 'GUN Emblem Fix' setting!\n\n"
				"Please disable either the 'Restored GUN Logos' mod, or the 'GUN Emblem Fix' setting!"
			);
		}

		GUNEmblemRestore();
	}

	if (ConfigGetInt(pconf, "rest", "jet", 1))
	{
		EnemyJetDisplayerFix();
	}

	if (ConfigGetInt(pconf, "rest", "dc_ring", 0))
	{
		DisableTintGinjaModel( (GJS_MODEL*) 0x00B58288 );
	}

	if (ConfigGetInt(pconf, "rest", "stgsel_text", 1))
	{
		StageMapTextBackdropRestore();
	}

	if (ConfigGetInt(pconf, "main", "ripple_fix", 1))
	{
		WriteValue(0x006EDB93, 0x1C, uint8);
	}

	int modeltint = ConfigGetInt(pconf, "main", "model_tint", 2);

	if (modeltint)
	{
		if (CheckForMod("NoTinting"))
		{
			ModConflictWarning(
				"The 'No Model Tinting' mod is obsolete and will conflict with Render Fix's 'Model Tint Fix' setting!\n\n"
				"Please disable the 'No Model Tinting' mod!"
			);
		}

		DefaultGinjaDiffuseEnable();

		DisableTintGinjaObjectListEx(GinjaObjectList);
		DisableTintChunkObjectListEx(ChunkObjectList);

		DisableTintGinjaModelListEx(GinjaModelList);
		DisableTintChunkModelListEx(ChunkModelList);

		if (modeltint == 2)
		{
			DisableTintGinjaModelListEx(GinjaModelListExtra);
			DisableTintChunkModelListEx(ChunkModelListExtra);
		}
	}

	if (ConfigGetInt(pconf, "exp", "enemy_shadows", 0) && !CheckForMod("sa2-dc-lighting"))
	{
		EnemyShadowEnable();
	}

	if (ConfigGetInt(pconf, "rest", "ce_lightmod", 1))
	{
		LightModifierFix();
	}

	if (ConfigGetInt(pconf, "main", "gh_clear", 1))
	{
		WriteValue(0x0044FE36, 0x1, uint8); // Fix green hill "CLEAR!" text
	}

	ConfigClose(pconf);
}

extern "C" __declspec(dllexport)
ModInfo SA2ModInfo = { ModLoaderVer };