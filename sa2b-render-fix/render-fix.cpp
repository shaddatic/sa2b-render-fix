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

static int __cdecl
njSearchTexMemList_()
{
    return -1;
}

/*
*    Dll Export
*/
EXTERN __declspec(dllexport)
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

        SwitchDisplayer(0x005113AA, DISP_DELY); // Enemy Jet
        SwitchDisplayer(0x00511422, DISP_DELY); // ^

        WritePointer(0x005BA0F6, 0x0117EEEC); // Sky Rail clouds
        WritePointer(0x005BA13E, 0x0117EE34); // ^

        SwitchDisplayer(0x004B39CD, DISP_SORT); // P-Hill clouds

        SwitchDisplayer(0x006A5338, DISP_SORT); // W-Canyon Fans

        SwitchDisplayer(0x007048E6, DISP_SORT); // P-Cave Spiderwebs
        SwitchDisplayer(0x0070248C, DISP_SORT); // P-Cave Wall Eyes
        SwitchDisplayer(0x006FC851, DISP_SORT); // P-Cave Chimney
        SwitchDisplayer(0x00701F3E, DISP_SORT); // P-Cave Firepot Fire
        SwitchDisplayer(0x00707826, DISP_SORT); // P-Cave Snakedish Fire
        SwitchDisplayer(0x007042E7, DISP_SORT); // P-Cave Awning Fire
        SwitchDisplayer(0x00707E27, DISP_SORT); // P-Cave Snake Head Fire
        SwitchDisplayer(0x006FE59E, DISP_SORT); // P-Cave Torch Cup Fire

        SwitchDisplayer(0x00762D75, DISP_LAST); // Boss Title Text

        SwitchDisplayer(0x00501BA5, DISP_SORT); // Enemy Ghosts

        SwitchDisplayer(0x0060B5CE, DISP_SORT); // Boss Bogy
        SwitchDisplayer(0x00761C04, DISP_LAST); // Boss Bogy Powergauge

        if (ConfigGetInt(conf, "debug", "dcshadpatch", 1))
        {
            WriteNoOP(0x00612C86, 0x00612CAA);  // DC Shadows crash patch for Boss Bogy
        }

        SwitchDisplayer(0x0044F845, DISP_LAST); // Results Score Text
        SwitchDisplayer(0x00450805, DISP_LAST); // Results Time Text
        SwitchDisplayer(0x0044F65B, DISP_LATE); // Results Window
        SwitchDisplayer(0x004531DF, DISP_LATE); // Results Ring Window
        SwitchDisplayer(0x004531E6, DISP_LAST); // Results Ring Window

        WriteData(0x0044FE36, 0x1, uint8); // Fix green hill "CLEAR!" text

        FixWhiteJungleWater();
    }

    if(ConfigGetInt(conf, "main", "gidx_ignore", 1))
    {
        WriteJump(0x0042FAD0, njSearchTexMemList_);
    }

    if (ConfigGetInt(conf, "main", "backface_cull", 1))
    {
        EnableBackfaceCulling();

        if (ConfigGetInt(conf, "debug", "jmp_aura", 1))
            EnableJumpAuraFix();

        if (ConfigGetInt(conf, "debug", "bfc_event", 1))
            EnableBackfaceCullingWithEventDisabled();
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
        FixModelTints();

        if (modeltint == 2)
            FixExtraModelTints();
    }

    ShadowSettings(conf);

    RestorationSettings(conf);

    EnvMapSettings(conf);

    GetEmblemSettings(conf);

    StageMapSettings(conf);

    CityEscapeSettings(conf);

    AquaticMineSettings(conf);

    CannonsCoreSettings(conf);

    BossBogySettings(conf);

    CartSettings(conf);

    EventSettings(conf);

    if (!ModCheckDll("sa2-dc-lighting"))
    {
        if (ConfigGetInt(conf, "exp", "enemy_shadows", 0))
        {
            ExtraShadowEnable();
        }
    }

    if (ConfigGetInt(conf, "debug", "objpak_write", 1))
    {
        int screentint = ConfigGetInt(conf, "main", "screen_tint", 1);

        EditObjPak(screentint, GetShadowOpacitySetting());
    }

    ConfigClose(conf);
}

extern "C" __declspec(dllexport)
ModInfo SA2ModInfo = { MODLOADER_VER };
