#include <samt/core.h>
#include <samt/modinfo.h>
#include <samt/string.h>

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
    const ml_modinfo* mhp = miGetInfoByName(name);

    return (mhp && mtStrMatch( mhp->puAuthor, author, STR_NOMAX ));
}

void
RF_ModCheckInit(void)
{
    /** Check Render Fix's mod-list position **/
    {
        const ml_modinfo* mhp = miGetInfoByIndex(0);

        if ( !mtStrMatch(mhp->puID, "sa2-render-fix", STR_NOMAX) )
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
        if ( CheckModByNameAndAuthor("High Quality Textures", "Speeps") )
        {
            RF_ModConflictStrict("High Quality Textures", "Render Fix");
        }
    }

    /** Check Rendering Fixes by End User **/
    {
        if ( CheckModByNameAndAuthor("Rendering Fixes", "End User") )
        {
            RF_ModConflictStrict("Rendering Fixes", "Render Fix & Cutscene Revamp");
        }
    }

    /** Check Enhanced Shadows by Shaddatic **/
    {
        if ( miGetInfoByDllName("enhanced-shadows") )
        {
            RF_ModConflictStrict("Enhanced Shadows", "Render Fix");
        }
    }


    /** Check No Model Tinting by Speeps **/
    {
        if ( miGetInfoByDllName("NoTinting") )
        {
            RF_ModConflictStrict("No Model Tinting", "Render Fix");
        }
    }


    /** Check Restored GUN Logos by Speeps **/
    {
        if ( RF_ConfigGetInt(CNF_COMMON_EEMBLEM) && miGetInfoByDllName("RestoredGUNLogos") )
        {
            RF_ModConflictEither("Restored GUN Logos", "GUN Emblem Fix");
        }
    }

    /** Check DC Shadows by Exant **/
    {
        if ( RFF_CheapShadow() && miGetInfoByDllName("sa2-dc-lighting") )
        {
            RF_ModConflictEither("DC Shadows", "Modifer Shadows");
        }
    }

    /** Check Eggman Lighting Fix by Exant **/
    {
        if ( RFF_SpotLightFix() && miGetInfoByDllName("NoLightingPatch") )
        {
            RF_ModConflictEither("Eggman Lighting Fix", "Spot Light Fix");
        }
    }

}
