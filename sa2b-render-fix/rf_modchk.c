#include <sa2b/core.h>
#include <sa2b/mods.h>
#include <sa2b/string.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_feature.h>
#include <rf_usermsg.h>

/** Macro **/
#define RF_ModConflictEither(_mod, _rf_feature)             RF_Alert("Mod Conflict ("_mod")", \
                                                                "The '" _mod "' mod is obsolete and is incompatible with Render Fix's '" _rf_feature "' feature!\n\n" \
                                                                "Please disable either the '" _mod "' mod, or the '" _rf_feature "' setting!")

#define RF_ModConflictStrict(_mod, _supersede_mods)         RF_Alert("Mod Conflict ("_mod")", \
                                                                "The '"_mod"' mod is obsolete and has been superseded by "_supersede_mods"!\n\n" \
                                                                "Please disable the '"_mod"' mod!")

static bool
CheckModByNameAndAuthor(const char* name, const char* author)
{
    const mod_handle* mhp = ModGetHandleName(name);

    return (mhp && StringMatch( ModGetAuthor(mhp), author ));
}

void
RF_ModCheckInit(void)
{
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

    /** Check Highest Quality Textures by Speeps **/
    {
        if (CheckModByNameAndAuthor("High Quality Textures", "Speeps"))
        {
            RF_ModConflictStrict("High Quality Textures", "Render Fix");
        }
    }

    /** Check Rendering Fixes by End User **/
    {
        if (CheckModByNameAndAuthor("Rendering Fixes", "End User"))
        {
            RF_ModConflictStrict("Rendering Fixes", "Render Fix & Cutscene Revamp");
        }
    }

    /** Check Enhanced Shadows by Shaddatic **/
    {
        if (ModCheckDll("enhanced-shadows"))
        {
            RF_ModConflictStrict("Enhanced Shadows", "Render Fix");
        }
    }


    /** Check No Model Tinting by Speeps **/
    {
        if (RFF_FixModelTint() && ModCheckDll("NoTinting"))
        {
            RF_ModConflictEither("No Model Tinting", "Fix Model Tint");
        }
    }


    /** Check Restored GUN Logos by Speeps **/
    {
        if (RF_ConfigGetInt(CNF_COMMON_EEMBLEM) && ModCheckDll("RestoredGUNLogos"))
        {
            RF_ModConflictEither("Restored GUN Logos", "GUN Emblem Fix");
        }
    }

    /** Check DC Shadows by Exant **/
    {
        if (RFF_CheapShadow() && ModCheckDll("sa2-dc-lighting"))
        {
            RF_ModConflictEither("DC Shadows", "Modifer Shadows");
        }
    }

    /** Check Eggman Lighting Fix by Exant **/
    {
        if (RFF_SpotLightFix() && ModCheckDll("NoLightingPatch"))
        {
            RF_ModConflictEither("Eggman Lighting Fix", "Spot Light Fix");
        }
    }

}
