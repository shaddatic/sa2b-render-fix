/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/modinfo.h>           /* mod info                                                 */
#include <samt/string.h>            /* string search                                            */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_usermsg.h>             /* rf alert                                                 */

/********************************/
/*  Enums                       */
/********************************/
/****** Check Mod *******************************************************************************/
typedef enum
{
    RF_CHKMOD_ID,                   /* check mod by mod id (mod-id)                             */
    RF_CHKMOD_DLL,                  /* check mod by dll name (name.dll)                         */
    RF_CHKMOD_NAMEANDAUTHOR,        /* check mod by name and author (name, author)              */
}
RF_CHKTYPE;

/********************************/
/*  Structures                  */
/********************************/
/****** Check Mod *******************************************************************************/
#define CHKMOD_ID(id)                       .type = RF_CHKMOD_ID,            .puID   = id
#define CHKMOD_DLL(dllname)                 .type = RF_CHKMOD_DLL,           .puDll  = dllname ".dll"
#define CHKMOD_NAMEANDAUTHOR(name, author)  .type = RF_CHKMOD_NAMEANDAUTHOR, .puName = name, .puAuthor = author

typedef struct
{
    RF_CHKTYPE type     : 16;       /* check type                                               */
    Bool       invchk   : 16;       /* invert check (alert when NOT found)                      */

    union
    {
        const c8* puID;             /* mod id                                                   */
        const c8* puDll;            /* mod dll name                                             */
        const c8* puName;           /* mod name                                                 */
    };
    union
    {
        const c8* puAuthor;         /* mod author                                               */
    };

    const c8* puHead;               /* alert header                                             */
    const c8* puBody;               /* alert body                                               */
}
RFS_CHKMOD;

/********************************/
/*  Data                        */
/********************************/
/****** Check Mod List **************************************************************************/
static const RFS_CHKMOD CheckModList[] =
{
    // Highest Quality Textures, by Speeps
    {
        CHKMOD_NAMEANDAUTHOR("High Quality Textures", "Speeps"),

        .puHead   = "Conflict (Highest Quality Textures, by Speeps)",
        .puBody   = "The 'High Quality Textures' mod is obsolete and has been superseded by Render Fix!\n\n"
                    "Please disable the 'High Quality Textures' mod!"
    },
    // Rendering Fixes, by End User
    {
        CHKMOD_NAMEANDAUTHOR("Rendering Fixes", "End User"),

        .puHead   = "Conflict (Rendering Fixes, by End User)",
        .puBody   = "The 'Rendering Fixes' mod is obsolete and has been superseded by Render Fix!\n\n"
                    "Please disable the 'Rendering Fixes' mod!"
    },
    // Enhanced Shadows by "The greatest programmer who ever lived" - Shaddatic, 2025
    {
        CHKMOD_DLL("enhanced-shadows"),

        .puHead   = "Conflict (Enhanced Shadows, by Shaddatic)",
        .puBody   = "The 'Enhanced Shadows' mod is obsolete and has been superseded by Render Fix!\n\n"
                    "Please disable the 'Enhanced Shadows' mod!"
    },
    // No Model Tinting, by Speeps
    {
        CHKMOD_DLL("NoTinting"),

        .puHead   = "Conflict (No Model Tinting, by Speeps)",
        .puBody   = "The 'No Model Tinting' mod is obsolete and has been superseded by Render Fix!\n\n"
                    "Please disable the 'No Model Tinting' mod!"
    },
    // Restored GUN Logos, by Speeps
    {
        CHKMOD_DLL("RestoredGUNLogos"),

        .puHead   = "Conflict (Restored GUN Logos, by Speeps)",
        .puBody   = "The 'Restored GUN Logos' mod is obsolete and has been superseded by Render Fix!\n\n"
                    "Please disable the 'Restored GUN Logos' mod!"
    },
    // Dreamcast Shadows, by Exant
    {
        CHKMOD_DLL("sa2-dc-lighting"),

        .puHead   = "Conflict (DC Shadows, by Exant)",
        .puBody   = "The 'Dreamcast Shadows' mod is obsolete! Render Fix now has it's own version called 'Modifier Shadows'!\n\n"
                    "Please disable the 'DC Shadows' mod!"
    },
    // Eggman Lighting Fix, by Exant
    {
        CHKMOD_DLL("NoLightingPatch"),

        .puHead   = "Conflict (Eggman Lighting Fix, by Exant)",
        .puBody   = "The 'Eggman Lighting Fix' mod is obsolete! Render Fix now includes an improved version this fix - with the help of Exant!\n\n"
                    "Please disable the 'Eggman Lighting Fix' mod!"
    },
    // Cutscene Revamp, by Speeps
    {
        CHKMOD_NAMEANDAUTHOR("Cutscene Revamp", "Speeps/End User"),

        .puHead   = "Conflict (Cutscene Revamp, by Speeps & End User)",
        .puBody   = "The 'Cutscene Revamp' mod is obsolete! Render Fix has restored the Dreamcast event/cutscene rendering logic, and ported the Dreamcast events as-is!\n\n"
                    "Because of this, Cutscene Revamp is now non-functional and will likely crash! If you're only interested in the Dreamcast events, just use Render Fix!\n\n"
                    "If you're looking for the other features of Cutscene Revamp, there are other mods including these features that use Render Fix's event port as a base.\n\n"
                    "Please disable the 'Cutscene Revamp' mod!"
    },
    // Dreamcast Object Lighting, by Firebow59
    {
        CHKMOD_NAMEANDAUTHOR("DC Object Lighting", "Firebow59"),

        .puHead   = "Conflict (DC Object Lighting, by Firebow59)",
        .puBody   = "The 'DC Object Lighting' mod is obsolete! Render Fix already uses the Dreamcast lighting files!\n\n"
                    "Please disable the 'DC Object Lighting' mod!"
    },
    // E0211 Fix, by Firebox59
    {
        CHKMOD_NAMEANDAUTHOR("e0211 Fix", "Firebow59"),

        .puHead   = "Conflict (e0211 Fix, by Firebow59)",
        .puBody   = "The 'E0211 Fix' mod is obsolete! Render Fix has already fixed this oversight!\n\n"
                    "Please disable the 'e0211 Fix' mod!"
    },
    /*
    *   Enable Check
    */
    // SA2 Input Controls
    {
        CHKMOD_ID("sa2-input-controls"),

        .invchk   = true,

        .puHead   = "Recommended (SA2 Input Controls)",
        .puBody   = "The 'SA2 Input Controls' mod is needed for some features in Render Fix to work correctly! Without it, analog controls will feel odd and some buttons will not work!\n\n"
                    "Please install and enable the 'SA2 Input Controls' mod!"
    },
};

/********************************/
/*  Source                      */
/********************************/
/****** Check Mod *******************************************************************************/
static bool
___ChkByID(const c8* puID)
{
    return miGetInfoByID(puID) != nullptr;
}

static bool
___ChkByDll(const c8* puDll)
{
    return miGetInfoByDllName(puDll) != nullptr;
}

static bool
___ChkByNameAndAuthor(const c8* puName, const c8* puAuthor)
{
    const size nb_mod = miGetModCount();

    for ( size i = 0; i < nb_mod; ++i )
    {
        const ml_modinfo* mhp = miGetInfoByIndex(i);

        if ( mtStrSearch( mhp->puAuthor, puAuthor, STR_NOMAX ) != STR_NOINDEX
        &&   mtStrSearch( mhp->puName  , puName  , STR_NOMAX ) != STR_NOINDEX )
        {
            return true;
        }
    }

    return false;
}

/****** Init ************************************************************************************/
void
RF_ModCheckInit(void)
{
    /** Check Render Fix's mod-list position **/

    const ml_modinfo* mhp = miGetInfoByIndex(0);

    if ( !mtStrMatch(mhp->puID, "sa2-render-fix", STR_NOMAX) )
    {
        RF_Alert(
            "Mod Position",

            "SA2 Render Fix is incorrectly placed in your mod list.\n\n"
            "Please ensure Render Fix is placed first & is above all other mods.\n\n"
            "Not doing this will likely cause game instability, incorrect behavior, & crashes depending on your other installed mods.\n\n"
            "You can correct this issue using the arrow buttons on the right side of your mod list while having a mod selected."
        );
    }

    /** Check external mod conflicts / obsolete notices **/

    for ( int i = 0; i < ARYLEN(CheckModList); ++i )
    {
        const RFS_CHKMOD* restrict p_chkmod = &CheckModList[i];

        bool found = false;

        switch ( p_chkmod->type )
        {
            case RF_CHKMOD_ID:
            {
                found = ___ChkByID(p_chkmod->puID);
                break;
            }
            case RF_CHKMOD_DLL:
            {
                found = ___ChkByDll(p_chkmod->puDll);
                break;
            }
            case RF_CHKMOD_NAMEANDAUTHOR:
            {
                found = ___ChkByNameAndAuthor(p_chkmod->puName, p_chkmod->puAuthor);
                break;
            }
        }

        if ( found != p_chkmod->invchk )
        {
            RF_Alert(p_chkmod->puHead, p_chkmod->puBody);
        }
    }
}
