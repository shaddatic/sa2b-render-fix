#define _CRT_SECURE_NO_WARNINGS

#define RF_MAIN

#include <sa2b/core.h>
#include <sa2b/init.h>
#include <sa2b/memutil.h>
#include <sa2b/mods.h>
#include <sa2b/model.h>
#include <sa2b/modloader.h>
#include <sa2b/string.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/display.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_util.h>
#include <rf_usermsg.h>
#include <rf_objpak.h>

/** Render Fix modules **/
#include <rfm_global.h>
#include <rfm_shadows.h>
#include <rfm_common.h>
#include <rfm_wjungle.h>
#include <rfm_cescape.h>
#include <rfm_mstreet.h>
#include <rfm_cgadget.h>
#include <rfm_amine.h>
#include <rfm_ccore.h>
#include <rfm_menus.h>
#include <rfm_eget.h>
#include <rfm_b_bigbogy.h>
#include <rfm_event.h>
#include <rfm_cart.h>

EXPORT_DLL
void __cdecl
Init(const char* path, const HelperFunctions* pHelpFuncs)
{
    /** SAModToolkit init **/
    SetModPath(path);
    ML_Init(pHelpFuncs);
    D3D_InitRenderDevice();

    /** Check Render Fix's mod-list position **/
    {
        const mod_handle* mhp = ModGetHandlePosition(0);

        if (!StringMatch( ModGetID(mhp), "sa2-render-fix" ))
        {
            RF_Alert("Mod Position",
                "SA2 Render Fix is incorrectly placed in your mod list.\n\n"
                "Please ensure Render Fix is placed first & is above all other mods.\n\n"
                "Not doing this will likely cause game instability, incorrect behavior, & crashes depending on your other installed mods.\n\n"
                "You can correct this issue using the arrow buttons on the right side of your mod list while having a mod selected."
            );
        }
    }

    /** Render Fix init **/
    RF_ConfigInit();
    RF_ObjPakInit();

    /** ALWAYS ON **/
    {
        SwitchDisplayer(0x006EDB91, DISP_SORT); // Water Ripples
        SwitchDisplayer(0x0075A166, DISP_DELY); // Bubble draw fix
        SwitchDisplayer(0x006FD65E, DISP_SORT); // PC Wall
    
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
    
        if (RF_ConfigGetInt(CNF_DEBUG_DCSHAD_PATCH))
        {
            WriteNoOP(0x00612C86, 0x00612CAA);  // DC Shadows crash patch for Boss Bogy
        }
    
        SwitchDisplayer(0x0044F845, DISP_LAST); // Results Score Text
        SwitchDisplayer(0x00450805, DISP_LAST); // Results Time Text
        SwitchDisplayer(0x0044F65B, DISP_LATE); // Results Window
        SwitchDisplayer(0x004531DF, DISP_LATE); // Results Ring Window
        SwitchDisplayer(0x004531E6, DISP_LAST); // Results Ring Window
    
        SwitchDisplayer(0x00476CAF, DISP_SORT); // "PlayerDrawMotionWithAlphaReducing"
    
        WriteData(0x0044FE36, 0x1, uint8_t); // Fix green hill "CLEAR!" text
    
        SwitchDisplayer(0x00545633, DISP_SORT); // ALO_ChaosDrive
    
        SwitchDisplayer(0x0061BB94, DISP_DELY); // Cart HUD

        SwitchDisplayer(0x006054F6, DISP_SORT); // Tails Prison search lights

        SwitchDisplayer(0x006A5D89, DISP_SORT); // Wild Canyon flags (upper)
    }

    RFM_GlobalInit();
    RFM_ShadowsInit();
    RFM_RestorationInit();
    RFM_EmblemGetInit();
    RFM_MenusInit();
    RFM_WhiteJungleInit();
    RFM_CityEscapeInit();
    RFM_MissionStreetInit();
    RFM_CrazyGadgetInit();
    RFM_AquaticMineInit();
    RFM_CannonsCoreInit();
    RFM_BossBogyInit();
    RFM_CartInit();
    RFM_EventInit();

    RF_ObjPakWriteChangesToFile();
    RF_ConfigEnd();
}

EXPORT_DLL
ModInfo SA2ModInfo = { MODLOADER_VER };
