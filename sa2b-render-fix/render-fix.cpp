#define _CRT_SECURE_NO_WARNINGS

#include <sa2b/core.h>

#include <sa2b/config.h>
#include <sa2b/memtools.h>
#include <sa2b/user.h>
#include <sa2b/mods.h>
#include <sa2b/model.h>

#include <sa2b/modloader.h>

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/display.h>

#include <render-fix.h>
#include <objpak.h>
#include <tint-disable.h>
#include <backcolor.h>
#include <backface-cull.h>
#include <explosion.h>
#include <tools.h>

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
	0x01462374, // E Unidus
	0x01462664, // E Unidus Orbiter

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

    0x0101DAEC, // Big Bogy
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
    0x00B1988C, // Balloon
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
    0x0162E024, // Minemizu

    0x00A2F034, // Tsubo
    0x0167856C, // PH Train Bed
    0x0167AD44, // PH Train
    0x016782E4, // PH Train Cylnder
    0x009B046C, // Poison
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
*	Dll Export
*/

extern "C" __declspec(dllexport)
void __cdecl
Init(const char* path, const HelperFunctions* pHelpFunc)
{
	SAMT_Init(path, pHelpFunc);

	config* conf = ConfigOpen2(path, "config.ini");

    /** ALWAYS ON **/
    {
        SwitchDisplayer(0x006EDB91, DISP_SORT); // Water Ripples
        SwitchDisplayer(0x0075A166, DISP_DELY); // Bubble draw fix
        SwitchDisplayer(0x006FD65E, DISP_SORT); // PC Wall
        
        FixExplosionSorting();

        SwitchDisplayer(0x005113AA, DISP_SORT); // Enemy Jet
        SwitchDisplayer(0x00511422, DISP_SORT); // ^

        WriteData(0x0044FE36, 0x1, uint8); // Fix green hill "CLEAR!" text
    }

	int screentint = ConfigGetInt(conf, "main", "objpak", 2);

	if (screentint)
	{
		EditObjPak(screentint == 2, 0.5f);
	}

	if(ConfigGetInt(conf, "main", "gidx_ignore", 1))
	{
		WriteData(0x00431340, 0x9090, uint16); // NOP
	}

    if (ConfigGetInt(conf, "main", "backface_cull", 1))
	{
        EnableBackfaceCulling();
	}

    if (ConfigGetInt(conf, "main", "backcolor", 1))
    {
        FixNinjaBackColor();
    }

    if (ConfigGetInt(conf, "main", "ptcl_scl", 1))
    {
        static const double ptcldbl00 = 1.5;
        static const double ptcldbl01 = 2.0;

        static const double ptcldbl02 = 1.0;

        static const double ptcldbl03 = 30.0;
        static const double ptcldbl04 = 32.5;

        static const double ptcldbl05 = 0.0000457763671875;

        /** Some particles were made 2x as big to counteract 
            the halvaning, this reverts that **/

#define ReplaceFloat(addr, pflt) WritePointer(addr + 2, pflt)

        ReplaceFloat(0x006D6117, &ptcldbl00); // RocketRocket
        ReplaceFloat(0x006D611D, &ptcldbl01); // ^

        ReplaceFloat(0x006D5455, &ptcldbl02); // Rocket
        ReplaceFloat(0x006D545B, &ptcldbl01); // ^

        ReplaceFloat(0x006F4FC3, &ptcldbl03); // MH Rocket
        ReplaceFloat(0x006F4FC9, &ptcldbl04);
        ReplaceFloat(0x006F500C, &ptcldbl03); // ^
        ReplaceFloat(0x006F5012, &ptcldbl04);
        ReplaceFloat(0x006F50C9, &ptcldbl03); // ^
        ReplaceFloat(0x006F50CF, &ptcldbl04);

        WriteData(0x006CF22E, 0x9090, uint16);// RocketMissile
        ReplaceFloat(0x006CF228, &ptcldbl05); // ^
        ReplaceFloat(0x006CF230, &ptcldbl01); // ^
        WriteData(0x006CEEF2, 0x9090, uint16);// ^
        ReplaceFloat(0x006CEEE8, &ptcldbl05); // ^
        ReplaceFloat(0x006CEEF4, &ptcldbl01); // ^

        ReplaceFloat(0x004B1290, &ptcldbl00); // StartRocketRocket (Final Rush)
        ReplaceFloat(0x004B1296, &ptcldbl01);

        WriteNoOP(0x00492506, 0x0049250C); // ptcl * 0.5

        /** Now just the polygon-particles **/

        static double ptclpolyscl;

        ptclpolyscl = (8.0 * GetDisplayRatioY());
        ReplaceFloat(0x007801A6, &ptclpolyscl);
    }

	int modeltint = ConfigGetInt(conf, "main", "model_tint", 2);

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

		DisableCartModelTints();

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

	RestorationSettings(conf);

	EnvMapSettings(conf);

	GetEmblemSettings(conf);

	StageMapSettings(conf);

    SkyRailSettings(conf);

	CityEscapeSettings(conf);

	AquaticMineSettings(conf);

	CannonsCoreSettings(conf);

	BossBogySettings(conf);

	CartSettings(conf);

    EventSettings(conf);

	if (!CheckForMod("sa2-dc-lighting"))
	{
		if (ConfigGetInt(conf, "exp", "enemy_shadows", 0))
		{
			ExtraShadowEnable();
		}
	}

	ConfigClose(conf);
}

extern "C" __declspec(dllexport)
ModInfo SA2ModInfo = { MOD_LOADER_VER };