#include <sa2b/core.h>
#include <sa2b/mods.h>
#include <sa2b/string.h>

#include <rf_core.h>
#include <rf_config.h>
#include <rf_feature.h>
#include <rf_usermsg.h>

void
RF_ModCheckInit(void)
{
    /** Check Render Fix's mod-list position **/
    {
        const mod_handle* mhp = ModGetHandlePosition(0);

        if (!StringMatch( ModGetID(mhp), "sa2-render-fix" ))
        {
            RF_ModConflict("Mod Position",
                "SA2 Render Fix is incorrectly placed in your mod list.\n\n"
                "Please ensure Render Fix is placed first & is above all other mods.\n\n"
                "Not doing this will likely cause game instability, incorrect behavior, & crashes depending on your other installed mods.\n\n"
                "You can correct this issue using the arrow buttons on the right side of your mod list while having a mod selected."
            );
        }
    }

    /** Check Highest Quality Textures by Speeps **/
    {
        const mod_handle* mhp = ModGetHandleName("High Quality Textures");

        if (mhp && StringMatch( ModGetAuthor(mhp), "Speeps" ))
        {
            RF_ModConflict("High Quality Textures",
                "The 'High Quality Textures' mod is obsolete and has been superseded by Render Fix's own High Quality Textures!\n\n"
                "Please disable either the 'High Quality Textures' mod!"
            );
        }
    }

    /** Check Enhanced Shadows by Shaddatic **/
    if (ModCheckDll("enhanced-shadows"))
        RF_ModConflict("Enhanced Shadows",
            "The 'Enhanced Shadows' mod is obsolete and will conflict with Render Fix!\n\n"
            "Please disable the 'Enhanced Shadows' mod!");

    /** Check No Model Tinting by Speeps **/
    if (RFF_FixModelTint() && ModCheckDll("NoTinting"))
        RF_ModConflictEx("No Model Tinting", "Fix Model Tint");

    /** Check Restored GUN Logos by Speeps **/
    if (RF_ConfigGetInt(CNF_COMMON_EEMBLEM) && ModCheckDll("RestoredGUNLogos"))
        RF_ModConflictEx("Restored GUN Logos", "GUN Emblem Fix");

    /** Check DC Shadows by Exant **/
    if (RFF_CheapShadow() && ModCheckDll("sa2-dc-lighting"))
        RF_ModConflictEx("DC Shadows", "Modifer Shadows");

    /** Check Eggman Lighting Fix by Exant **/
    if (RFF_SpotLightFix() && ModCheckDll("NoLightingPatch"))
        RF_ModConflictEx("Eggman Lighting Fix", "Spot Light Fix");
}
