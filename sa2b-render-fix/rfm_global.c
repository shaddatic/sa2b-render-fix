#include <sa2b/core.h>
#include <sa2b/writemem.h>
#include <sa2b/writeop.h>
#include <sa2b/funchook.h>

/** GX **/
#define SAMT_INCL_FUNCPTRS
#include <sa2b/gx/gx.h>
#undef  SAMT_INCL_FUNCPTRS

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/display.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_util.h>
#include <rf_objpak.h>
#include <rf_renderstate.h>
#include <rf_magic.h>

/** Self **/
#include <rfm_global.h>
#include <rfm_global/rfg_internal.h>

/** Globals **/
static bool RfgBackColor;
static bool RfgSpotLight;
static bool RfgEnvMapFlip;
static int  RfgFixMdlTint;

/** Static functions **/
static int __cdecl
njSearchTexMemList_(void)
{
    return -1;
}

static void __cdecl
RF_SetPointSize(uint8_t size)
{
    RF_MagicSetPointSize(((float)size) * GetDisplayRatioY());
}

__declspec(naked)
static void
__SetPointSize(void)
{
    __asm
    {
        push eax
        call RF_SetPointSize
        pop eax
        retn
    }
}

/** Extern functions **/
bool
RFF_BackColorDraw(void)
{
    return RfgBackColor;
}

bool
RFF_SpotLightFix(void)
{
    return RfgSpotLight;
}

bool
RFF_EnvMapFlip(void)
{
    return RfgEnvMapFlip;
}

bool
RFF_FixModelTint(void)
{
    return RfgFixMdlTint;
}

void
RFM_GlobalInit(void)
{
    if (RF_ConfigGetInt(CNF_GLOBAL_IGBIX))
    {
        WriteJump(0x0042FAD0, njSearchTexMemList_);
    }

    if (RF_ConfigGetInt(CNF_GLOBAL_BFACECULL))
    {
        RFG_BackfaceCullingInit();
    }
    else
        RFRS_SetDefaultCullMode(RFRS_CULLMD_NONE);

    if (RF_ConfigGetInt(CNF_GLOBAL_BACKCOLOR))
    {
        RfgBackColor = true;
        RFG_NinjaBackColorInit();
    }

    if (RF_ConfigGetInt(CNF_GLOBAL_PTCLSCALE))
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

        WriteData(0x006CF22E, 0x9090, uint16_t);// RocketMissile
        ReplaceFloat(0x006CF228, &ptcldbl05); // ^
        ReplaceFloat(0x006CF230, &ptcldbl01); // ^
        WriteData(0x006CEEF2, 0x9090, uint16_t);// ^
        ReplaceFloat(0x006CEEE8, &ptcldbl05); // ^
        ReplaceFloat(0x006CEEF4, &ptcldbl01); // ^

        ReplaceFloat(0x004B1290, &ptcldbl00); // StartRocketRocket (Final Rush)
        ReplaceFloat(0x004B1296, &ptcldbl01);

        WriteNOP(0x00492506, 0x0049250C); // ptcl * 0.5

        /** PtclPolygon **/
        static double ptclpolyscl;

        ptclpolyscl = RF_ConfigGetFloat(CNF_MISC_PTCLPOLYSCL);

        ReplaceFloat(0x007801A6, &ptclpolyscl);
        WriteJump(GX_SetPointSize_p, __SetPointSize);
    }

    const int mdl_tint = RF_ConfigGetInt(CNF_GLOBAL_MDLTINT);

    switch (mdl_tint) {
    case CNFE_GLOBAL_MDLTINT_EXTENDED:
        RFG_ModelTintFixBaseInit();
        RFG_ModelTintFixDefaultInit();
//      RFG_ModelTintFixExtendedInit();
        break;

    case CNFE_GLOBAL_MDLTINT_ENABLED:
        RFG_ModelTintFixBaseInit();
        RFG_ModelTintFixDefaultInit();
        break;

    case CNFE_GLOBAL_MDLTINT_DREAMCAST:
        RFG_ModelTintFixBaseInit();
        break;

    case CNFE_GLOBAL_MDLTINT_DISABLED:
        break;
    }

    RfgFixMdlTint = mdl_tint;

    if (RF_ConfigGetInt(CNF_GLOBAL_SCRNTINT))
    {
        RF_ObjPakRegisterTintFix(true);
    } 

    if (RF_ConfigGetInt(CNF_GLOBAL_SPOTLITE))
    {
        RfgSpotLight = true;
        RFG_SpotLightFixInit();
    }

    if (RF_ConfigGetInt(CNF_GLOBAL_ENVFLIP))
    {
        RfgEnvMapFlip = true;
        RFG_EnvMapFlip();
    }

    RFG_TaskDisplayInit();

    if (RF_ConfigGetInt(CNF_GLOBAL_SPRITE))
    {
        RFG_3DSpriteInit();
    }

    if (true) // Aspect test
    {
        static const double new_asp_test = (4/3);

        ReplaceFloat(0x00794778, &new_asp_test); // ActionWindow button sprite
        ReplaceFloat(0x0079499D, &new_asp_test); // ^

        /** Stage map completely breaks **/
        /*
        ReplaceFloat(0x00677B04, &new_asp_test); // Stage Map init
        ReplaceFloat(0x00675E09, &new_asp_test); // Stage Map
        */
    }

    if (RF_ConfigGetInt(CNF_GLOBAL_LINE))
    {
        RFG_DrawLineInit();
    }
}
