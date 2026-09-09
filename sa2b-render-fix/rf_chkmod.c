/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/modinfo.h>           /* mod info                                                 */
#include <samt/string.h>            /* string search                                            */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Config **********************************************************************************/
#include <cnf.h>                    /* core                                                     */

/********************************/
/*  Enums                       */
/********************************/
/****** Check Mod *******************************************************************************/
typedef enum
{
    CHK_ID,                         /* check mod by mod id (mod-id)                             */
    CHK_DLL,                        /* check mod by dll name (name.dll)                         */
    CHK_NAME,                       /* check mod by name and author (name, author)              */
}
CHKMOD_TYPE;

typedef enum
{
    MSG_INFO,                       /* info message box                                         */
    MSG_WARN,                       /* warning message box                                      */
    MSG_ERROR,                      /* error message box                                        */
}
CHKMOD_MSG;

/********************************/
/*  Structures                  */
/********************************/
/****** Check Mod *******************************************************************************/
typedef struct
{
    CHKMOD_TYPE     chk_type :8;    /* check type                                               */
    CHKMOD_MSG      msg_type :8;    /* message type                                             */
    Bool            chk_if   :8;    /* check if mod is ON/OFF                                   */

    union
    {
        const c8*   chk_id;         /* mod id                                                   */
        const c8*   chk_dll;        /* mod dll name                                             */
        const c8*   chk_name;       /* mod name                                                 */
    };
    union
    {
        const c8*   chk_author;     /* mod author                                               */
    };

    const c8*       msg_head;       /* message header                                           */
    const c8*       msg_body;       /* message body                                             */

    bool(*chk_fn)( void );          /* additional check logic                                   */
}
CHKMOD;

#define CHKMOD_ID(   check, id,           msgtype, head, body)                                  \
                                                                                                \
                .chk_type = CHK_ID, .chk_if = check, .chk_id = id,                              \
                .msg_type = msgtype, .msg_head = head, .msg_body = body

#define CHKMOD_DLL(  check, dllname,      msgtype, head, body) \
\
                .chk_type = CHK_DLL,.chk_if = check, .chk_dll = dllname ".dll",                 \
                .msg_type = msgtype, .msg_head = head, .msg_body = body

#define CHKMOD_NAME( check, name, author, msgtype, head, body) \
\
                .chk_type = CHK_NAME, .chk_if = check, .chk_name = name, .chk_author = author,  \
                .msg_type = msgtype, .msg_head = head, .msg_body = body

/********************************/
/*  Forward Refs                */
/********************************/
/****** Mod Check *******************************************************************************/
bool    InputControlsCheck( void );

/********************************/
/*  Data                        */
/********************************/
/****** Check Mod List **************************************************************************/
static const CHKMOD CheckModList[] =
{
    // Highest Quality Textures, by Speeps
    {
        CHKMOD_NAME( OFF, "High Quality Textures", "Speeps", MSG_WARN,

            "Conflict (Highest Quality Textures, by Speeps)",

            "The 'High Quality Textures' mod is obsolete and has been superseded by Render Fix!\n\n"
            "Please disable the 'High Quality Textures' mod!"
        ),
    },
    // Rendering Fixes, by End User
    {
        CHKMOD_NAME( OFF, "Rendering Fixes", "End User", MSG_WARN,

            "Conflict (Rendering Fixes, by End User)",

            "The 'Rendering Fixes' mod is obsolete and has been superseded by Render Fix!\n\n"
            "Please disable the 'Rendering Fixes' mod!"
        ),
    },
    // Enhanced Shadows by "The greatest programmer who ever lived" - Shaddatic, 2025
    {
        CHKMOD_DLL( OFF, "enhanced-shadows", MSG_WARN,

            "Conflict (Enhanced Shadows, by Shaddatic)",

            "The 'Enhanced Shadows' mod is obsolete and has been superseded by Render Fix!\n\n"
            "Please disable the 'Enhanced Shadows' mod!"
        ),
    },
    // No Model Tinting, by Speeps
    {
        CHKMOD_DLL( OFF, "NoTinting", MSG_WARN,

            "Conflict (No Model Tinting, by Speeps)",

            "The 'No Model Tinting' mod is obsolete and has been superseded by Render Fix!\n\n"
            "Please disable the 'No Model Tinting' mod!"
        ),
    },
    // Restored GUN Logos, by Speeps
    {
        CHKMOD_DLL( OFF, "RestoredGUNLogos", MSG_WARN,

            "Conflict (Restored GUN Logos, by Speeps)",

            "The 'Restored GUN Logos' mod is obsolete and has been superseded by Render Fix!\n\n"
            "Please disable the 'Restored GUN Logos' mod!"
        ),
    },
    // Dreamcast Shadows, by Exant
    {
        CHKMOD_DLL( OFF, "sa2-dc-lighting", MSG_WARN,

            "Conflict (DC Shadows, by Exant)",

            "The 'Dreamcast Shadows' mod is obsolete! Render Fix now has it's own version called 'Modifier Shadows'!\n\n"
            "Please disable the 'DC Shadows' mod!"
        ),
    },
    // Eggman Lighting Fix, by Exant
    {
        CHKMOD_DLL( OFF, "NoLightingPatch", MSG_WARN,

            "Conflict (Eggman Lighting Fix, by Exant)",

            "The 'Eggman Lighting Fix' mod is obsolete! Render Fix now includes an improved version this fix - with the help of Exant!\n\n"
            "Please disable the 'Eggman Lighting Fix' mod!"
        ),
    },
    // Cutscene Revamp, by Speeps
    {
        CHKMOD_NAME( OFF, "Cutscene Revamp", "Speeps/End User", MSG_WARN,

            "Conflict (Cutscene Revamp, by Speeps & End User)",

            "The 'Cutscene Revamp' mod is obsolete! Render Fix has restored the Dreamcast event/cutscene rendering logic, and ported the Dreamcast events as-is!\n\n"
            "Because of this, Cutscene Revamp is now non-functional and will likely crash! If you're only interested in the Dreamcast events, just use Render Fix!\n\n"
            "If you're looking for the other features of Cutscene Revamp, there are other mods including these features that use Render Fix's event port as a base.\n\n"
            "Please disable the 'Cutscene Revamp' mod!"
        ),
    },
    // Dreamcast Object Lighting, by Firebow59
    {
        CHKMOD_NAME( OFF, "DC Object Lighting", "Firebow59", MSG_WARN,

            "Conflict (DC Object Lighting, by Firebow59)",

            "The 'DC Object Lighting' mod is obsolete! Render Fix already uses the Dreamcast lighting files!\n\n"
            "Please disable the 'DC Object Lighting' mod!"
        ),
    },
    // E0211 Fix, by Firebox59
    {
        CHKMOD_NAME( OFF, "e0211 Fix", "Firebow59", MSG_WARN,

            "Conflict (e0211 Fix, by Firebow59)",

            "The 'E0211 Fix' mod is obsolete! Render Fix has already fixed this oversight!\n\n"
            "Please disable the 'e0211 Fix' mod!"
        ),
    },
    // Knuckles Animation Fix, by Shaddatic
    {
        CHKMOD_NAME( OFF, "Knuckles' Animation Fix", "Shaddatic", MSG_WARN,

            "Conflict (Knuckles Anim Fix, by Shaddatic)",

            "The 'Knuckles' Animation Fix' mod is obsolete! Render Fix restores the original player mtn files from GameCube!\n\n"
            "Please disable the 'Knuckles' Animation Fix' mod!"
        ),
    },
    // Event Timescale Fix, by Luks_18
    {
        CHKMOD_NAME( OFF, "Event Timescale Fix", "Luks_18", MSG_WARN,

            "Conflict (Event Timescale Fix, by Luks_18)",

            "The 'Event Timescale Fix' mod is obsolete! Render Fix has restored the Dreamcast event/cutscene rendering logic, and ported the Dreamcast events as-is - including lag emulation!\n\n"
            "Please disable the 'Event Timescale Fix' mod!"
        ),
    },
    // No Level-of-Detail models, by SF94
    {
        CHKMOD_NAME( OFF, "No Level-of-Detail models", "SonicFreak94", MSG_WARN,

            "Conflict (No LOD Models, by SonicFreak94)",

            "The 'No Level-of-Detail Models' mod is obsolete! Render Fix has options for disabling player LOD models in the config settings menu!\n\n"
            "Please disable the 'No Level-of-Detail Models' mod!"
        ),
        // explicitly don't check for DLL, in case another mod uses it
    },
    // Tails Cyclone Fix, by Broly#4302 & Samuel555v
    {
        CHKMOD_DLL( OFF, "TailsFix", MSG_WARN,

            "Conflict (Tails Cyclone Fix, by Broly#4302 & Samuel555v)",

            "The 'Tails Cyclone Fix' mod is obsolete! Render Fix fixes all model tinting issues by restoring a rendering flag left out of Battle!\n\n"
            "Please disable the 'Tails Cyclone Fix' mod!"
        ),
    },
    // E0129 Music Restoration, by HedgeWedge
    {
        CHKMOD_NAME( OFF, "E0129 Music Restoration", "HedgeWedge", MSG_WARN,

            "Conflict (E0129 Music Restoration, by HedgeWedge)",

            "The 'E0129 Music Restoration' mod is obsolete and non-functional! Render Fix has ported the Dreamcast events as-is - including music and effect files!\n\n"
            "Please disable the 'E0129 Music Restoration' mod!"
        ),
    },
    // Stage Atmosphere Tweaks, by Hoppy
    {
        CHKMOD_NAME( OFF, "Stage Atmosphere Tweaks", "HoppyBoppyBunny", MSG_WARN,

            "Conflict (Stage Atmosphere Tweaks, by HoppyBoppyBunny)",

            "The 'Stage Atmosphere Tweaks' mod is non-functional in the latest versions of Render Fix, and causes models to become pitch black! This is due to broken lighting and fog files that the vanilla game, through luck, ends up with semi-normal values!\n\n"
            "Please disable the 'Stage Atmosphere Tweaks' mod!"
        ),
    },
    // No Battle, by Main Memory
    {
        CHKMOD_DLL( OFF, "nobattle", MSG_WARN,

            "Conflict (No Battle, by MainMemory)",

            "The 'No Battle' mod is obsolete! Render Fix now has it's own 'Battle Branding' setting!\n\n"
            "Please disable the 'No Battle' mod!"
        ),
    },
    /*
    *   Enable Check
    */
    // SA2 Input Controls
    {
        CHKMOD_ID( ON, "sa2-input-controls", MSG_WARN,

            "Recommended (SA2 Input Controls)",

            "The 'SA2 Input Controls' mod is needed for some features in Render Fix to work correctly! Specifically for Input Controls' many input bug fixes, extra button support, and analog control improvements!\n\n"
            "Please install and enable the 'SA2 Input Controls' mod!"
        ),

        .chk_fn = InputControlsCheck,
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
___ChkByName(const c8* puName, const c8* puAuthor)
{
    const isize nb_mod = miGetModCount();

    for ( isize i = 0; i < nb_mod; ++i )
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

/****** Additional Logic ************************************************************************/
static bool
InputControlsCheck(void)
{
    // if frame controller is enabled, or event debug mode, flag that Input Controls is needed!
    return ( CNF_GetInt( CNF_GFX_VSYNC ) == CNFE_BOOL_ENABLED || CNF_GetInt( CNF_DEBUG_EVENT ) == CNFE_BOOL_ENABLED );
}

/****** Init ************************************************************************************/
i32
RF_ModCheckInit(void)
{
    i32 retcode = 0;

    /** Check Render Fix's mod-list position **/

    const ml_modinfo* mhp = miGetInfoByIndex(0);

    if ( !mtStrMatch(mhp->puID, "sa2-render-fix", STR_NOMAX) )
    {
        RF_MsgWarn(
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
        const CHKMOD* restrict p_chkmod = &CheckModList[i];

        bool found = false;

        switch ( p_chkmod->chk_type )
        {
            case CHK_ID:
            {
                found = ___ChkByID(p_chkmod->chk_id);
                break;
            }
            case CHK_DLL:
            {
                found = ___ChkByDll(p_chkmod->chk_dll);
                break;
            }
            case CHK_NAME:
            {
                found = ___ChkByName(p_chkmod->chk_name, p_chkmod->chk_author);
                break;
            }
        }

        if ( found != p_chkmod->chk_if
        && ( !p_chkmod->chk_fn || p_chkmod->chk_fn() ) )
        {
            switch ( p_chkmod->msg_type )
            {
                case MSG_INFO:
                {
                    RF_MsgInfo(p_chkmod->msg_head, p_chkmod->msg_body);
                    break;
                }
                case MSG_WARN:
                {
                    if ( !retcode ) retcode = 1;

                    RF_MsgWarn(p_chkmod->msg_head, p_chkmod->msg_body);
                    break;
                }
                case MSG_ERROR:
                {
                    retcode = -1;

                    RF_MsgError(p_chkmod->msg_head, p_chkmod->msg_body);
                    break;
                }
            }

            RF_MsgWarn(p_chkmod->msg_head, p_chkmod->msg_body);
        }
    }

    return retcode;
}
