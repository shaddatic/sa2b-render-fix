/*
*   Common Utils - '/cnf_def.h'
*
*   Description:
*     Config options definitons for use with common config module.
*/
#ifndef H_CMN_CONFIG_DEF
#define H_CMN_CONFIG_DEF

/********************************/
/*  Enums                       */
/********************************/
/************************************************************************************************/
/*
*   Basic Types
*/
/****** Basic Bool ******************************************************************************/
typedef enum
{
    CNFE_BOOL_DISABLED,             /* off/disabled                                             */
    CNFE_BOOL_ENABLED               /* enabled                                                  */
}
CNFE_BOOL;

/************************************************************************************************/
/*
*   Graphics
*/
/****** Vsync ***********************************************************************************/
typedef enum
{
    CNFE_GFX_VSYNC_60               = 1,
    CNFE_GFX_VSYNC_30               = 2,
    CNFE_GFX_VSYNC_15               = 4,
}
CNFE_GFX_VSYNC;

/****** Anisotropic Filtering *******************************************************************/
typedef enum
{
    CNFE_GFX_ANISOTROPY_AUTO        = -1,
}
CNFE_GFX_ANISOTROPIC;

/****** Texture Filtering ***********************************************************************/
typedef enum
{
    CNFE_GFX_TEXFILTER_AUTO         = -1,

    CNFE_GFX_TEXFILTER_POINT,
    CNFE_GFX_TEXFILTER_BILINEAR,
    CNFE_GFX_TEXFILTER_TRILINEAR,
}
CNFE_GFX_TEXFILTER;

/****** Mipmap 'D' Adjust ***********************************************************************/
typedef enum
{
    CNFE_GFX_MIPDADJ_AUTO           = -1,
    CNFE_GFX_MIPDADJ_CLAMPPOS       = -2,
    CNFE_GFX_MIPDADJ_CLAMPNEG       = -3,
}
CNFE_GFX_MIPDADJ;

/************************************************************************************************/
/*
*   Global
*/
/****** Cheap Shadow Mode ***********************************************************************/
typedef enum
{
    CNFE_GLOBAL_CHSMD_DISABLED,
    CNFE_GLOBAL_CHSMD_PERFORMANCE,
    CNFE_GLOBAL_CHSMD_ENABLED,
}
CNFE_GLOBAL_CHSMD;

/************************************************************************************************/
/*
*   Font
*/
/****** Japanese Typeface ***********************************************************************/
typedef enum
{
    CNFE_FONT_KANJI_VANILLA,
    CNFE_FONT_KANJI_CLASSIC,
}
CNFE_FONT_KANJI;

/****** Latin Typeface **************************************************************************/
typedef enum
{
    CNFE_FONT_ASCII_VANILLA,
    CNFE_FONT_ASCII_IMPRESS,
    CNFE_FONT_ASCII_COMICSANS,
}
CNFE_FONT_ASCII;

/****** Character Spacing ***********************************************************************/
typedef enum
{
    CNFE_FONT_WIDTH_AUTO        = -1,

    CNFE_FONT_WIDTH_TOUCHING,
    CNFE_FONT_WIDTH_SQUISHED,
    CNFE_FONT_WIDTH_COMPACT,
    CNFE_FONT_WIDTH_COMFY,
    CNFE_FONT_WIDTH_SPACY,
}
CNFE_FONT_WIDTH;

/****** Space Width *****************************************************************************/
typedef enum
{
    CNFE_FONT_SPACE_AUTO        = -1,

    CNFE_FONT_SPACE_NONE,
    CNFE_FONT_SPACE_QUATER,
    CNFE_FONT_SPACE_THIRD,
    CNFE_FONT_SPACE_HALF,
    CNFE_FONT_SPACE_FULL,

    NB_CNFE_FONT_SPACE,
}
CNFE_FONT_SPACE;

/************************************************************************************************/
/*
*   Players
*/
/****** Player Shadow Mode **********************************************************************/
typedef enum
{
    CNFE_PLAYER_SHADOWMD_VANILLA,
    CNFE_PLAYER_SHADOWMD_ENHANCED,
    CNFE_PLAYER_SHADOWMD_MODIFIER,
}
CNFE_PLAYER_SHADOWMD;

/****** Model Mode ******************************************************************************/
typedef enum
{
    CNFE_PLAYER_MODEL_GAMECUBE,
    CNFE_PLAYER_MODEL_DREAMCAST,

    NB_CNFE_PLAYER_MODEL,
}
CNFE_PLAYER_MODEL;

/****** LOD Model Mode **************************************************************************/
typedef enum
{
    CNFE_PLAYER_LOD_DISABLED,
    CNFE_PLAYER_LOD_2PONLY,
    CNFE_PLAYER_LOD_ENABLED,

    NB_CNFE_PLAYER_LOD,
}
CNFE_PLAYER_LOD;

/************************************************************************************************/
/*
*   Cart
*/
/****** Cart Sprites ****************************************************************************/
typedef enum
{
    CNFE_CART_CARTSPRITE_DISABLED,
    CNFE_CART_CARTSPRITE_DREAMCAST,
    CNFE_CART_CARTSPRITE_ENABLED,
}
CNFE_CART_CARTSPRITE;

/************************************************************************************************/
/*
*   Event
*/
/****** Vsync Mode ******************************************************************************/
typedef enum
{
    CNFE_EVENT_VSYNC_60,
    CNFE_EVENT_VSYNC_EVSET,
    CNFE_EVENT_VSYNC_30,
}
CNFE_EVENT_VSYNC;

/****** 4:3 Mode ********************************************************************************/
typedef enum
{
    CNFE_EVENT_43MD_NEVER,
    CNFE_EVENT_43MD_SPECIFIC,
    CNFE_EVENT_43MD_NOINTRO,
    CNFE_EVENT_43MD_ALWAYS,
}
CNFE_EVENT_43MD;

/****** Overlay Fit *****************************************************************************/
typedef enum
{
    CNFE_EVENT_MOVIE_FIT,
    CNFE_EVENT_MOVIE_STRETCH,
    CNFE_EVENT_MOVIE_CLAMP,
    CNFE_EVENT_MOVIE_MIRROR,
    CNFE_EVENT_MOVIE_CROP,
}
CNFE_EVENT_MOVIE;

/************************************************************************************************/
/*
*   Misc
*/
/****** Pause Font Color ************************************************************************/
typedef enum
{
    CNFE_MISC_PAUSEFONTCOL_DARKER,
    CNFE_MISC_PAUSEFONTCOL_LIGHTER,
}
CNFE_MISC_PAUSEFONTCOL;

/****** Shadow Texture Resolution ***************************************************************/
typedef enum
{
    CNFE_MISC_SHDWRES_VERYLOW,
    CNFE_MISC_SHDWRES_LOW,
    CNFE_MISC_SHDWRES_MEDIUM,
    CNFE_MISC_SHDWRES_HIGH,
    CNFE_MISC_SHDWRES_ULTRA,
    CNFE_MISC_SHDWRES_IMPERCEIVABLE
}
CNFE_MISC_SHDWRES;

/********************************/
/*  Constants                   */
/********************************/
/************************************************************************************************/
/*
*   Config Sections
*/
/****** Main ************************************************************************************/
#define CNFS_GFX            "graphics"
#define CNFS_GLOBAL         "main"
#define CNFS_FONT           "font"
#define CNFS_PLAYER         "player"
#define CNFS_COMMON         "common"

/****** Stages **********************************************************************************/
#define CNFS_AM             "a_mine"

/****** Others **********************************************************************************/
#define CNFS_CART           "cart"
#define CNFS_EVENT          "event"

/****** Miscellaneous ***************************************************************************/
#define CNFS_MISC           "misc"

/****** Experimental ****************************************************************************/
#define CNFS_EXP            "experimental"

/****** Compatibility ***************************************************************************/
#define CNFS_COMPAT         "compatibility"

/****** Debug ***********************************************************************************/
#define CNFS_DEBUG          "debug"

/************************************************************************************************/
/*
*   Config Options
*/
/****************************************************************************************************************************************/
/**                               | Type      | Section             | Key                   | Default                                  **/
/** Graphics section **/
#define CNF_GFX_VSYNC               CNFO_INT(   CNFS_GFX            , "vsync"               , CNFE_GFX_VSYNC_60                     )   /* Framerate */
#define CNF_GFX_ANISOTROPY          CNFO_INT(   CNFS_GFX            , "anisotropy"          , CNFE_GFX_ANISOTROPY_AUTO              )   /* Anisotropic Filtering */
#define CNF_GFX_TEXFILTER           CNFO_INT(   CNFS_GFX            , "texfilter"           , CNFE_GFX_TEXFILTER_AUTO               )   /* Texture Filtering */
#define CNF_GFX_MIPDADJ             CNFO_INT(   CNFS_GFX            , "mipdadj"             , CNFE_GFX_MIPDADJ_AUTO                 )   /* Mipmap Depth Adjust */
#define CNF_GFX_MIPMAPS             CNFO_INT(   CNFS_GFX            , "mipmaps"             , CNFE_BOOL_ENABLED                     )   /* Use Mipmaps */

/** Global section **/
#define CNF_GLOBAL_IGBIX            CNFO_INT(   CNFS_GLOBAL         , "gidx_ignore"         , CNFE_BOOL_ENABLED                     )   /* Ignore Global Texture Index */
#define CNF_GLOBAL_CHSMD            CNFO_INT(   CNFS_GLOBAL         , "mod_shadow"          , CNFE_GLOBAL_CHSMD_ENABLED             )   /* Cheap Shadow setting */
#define CNF_GLOBAL_CNKSPEC          CNFO_INT(   CNFS_GLOBAL         , "cnk_spec"            , CNFE_BOOL_ENABLED                     )   /* Specular Highlights */

/** Font section **/
#define CNF_FONT_KANJI              CNFO_INT(   CNFS_FONT           , "kanji"               , CNFE_FONT_KANJI_VANILLA               )   /* Japanese Script Font */
#define CNF_FONT_ASCII              CNFO_INT(   CNFS_FONT           , "ascii"               , CNFE_FONT_ASCII_VANILLA               )   /* Latin Script Font */
#define CNF_FONT_WIDTH              CNFO_INT(   CNFS_FONT           , "width"               , CNFE_FONT_WIDTH_AUTO                  )   /* Character Spacing */
#define CNF_FONT_SPACE              CNFO_INT(   CNFS_FONT           , "space"               , CNFE_FONT_SPACE_AUTO                  )   /* Space Character Width */
#define CNF_FONT_PTFILTER           CNFO_INT(   CNFS_FONT           , "ptfilter"            , CNFE_BOOL_DISABLED                    )   /* Use point filtering */

/** Player section **/
#define CNF_PLAYER_MODEL            CNFO_INT(   CNFS_PLAYER         , "model"               , CNFE_PLAYER_MODEL_GAMECUBE            )   /* Player model mode */
#define CNF_PLAYER_LODMDL           CNFO_INT(   CNFS_PLAYER         , "lod_mdl"             , CNFE_PLAYER_LOD_ENABLED               )   /* Lod Models */
#define CNF_PLAYER_CHAOS0ANIM       CNFO_INT(   CNFS_PLAYER         , "chaos0_texanim"      , CNFE_BOOL_ENABLED                     )   /* Use Chaos0 texture animation */
#define CNF_PLAYER_SHADLITEDASH     CNFO_INT(   CNFS_PLAYER         , "shadow_lightdash"    , CNFE_BOOL_ENABLED                     )   /* Shadow's Lightdash Effect */
#define CNF_PLAYER_MILESTAILMOD     CNFO_INT(   CNFS_PLAYER         , "miles_tailmod"       , CNFE_BOOL_ENABLED                     )   /* Draw Tails' Tail Modifier Shadows */
#define CNF_PLAYER_TWALKFOOTMOD     CNFO_INT(   CNFS_PLAYER         , "twalk_footmod"       , CNFE_BOOL_ENABLED                     )   /* Fix Tornado's Foot Modifiers */
#define CNF_PLAYER_SHADOWMD         CNFO_INT(   CNFS_PLAYER         , "shadow_md"           , CNFE_PLAYER_SHADOWMD_MODIFIER         )   /* Player Shadow Mode */
#define CNF_PLAYER_MDLSHADOW        CNFO_INT(   CNFS_PLAYER         , "mdl_shadow"          , CNFE_BOOL_ENABLED                     )   /* Disable player shadowing */

/** Common section **/
#define CNF_COMMON_TR_SORT          CNFO_INT(   CNFS_COMMON         , "trans_sorting"       , CNFE_BOOL_ENABLED                     )   /* Transparancy Sorting Fixes */
#define CNF_COMMON_EEMBLEM          CNFO_INT(   CNFS_COMMON         , "e_emblem"            , CNFE_BOOL_ENABLED                     )   /* GUN Emblems */
#define CNF_COMMON_AISHEILD         CNFO_INT(   CNFS_COMMON         , "e_ai_shield"         , CNFE_BOOL_ENABLED                     )   /* DC GUN Hunter Shield */
#define CNF_COMMON_ESTGTEX          CNFO_INT(   CNFS_COMMON         , "e_stg_tex"           , CNFE_BOOL_ENABLED                     )   /* Stage Specific Enemy Textures */

/** Aquatic Mine section **/
#define CNF_AM_MURKY                CNFO_INT(   CNFS_AM             , "murky"               , CNFE_BOOL_ENABLED                     )   /* Restore Murky Water Effect */

/** Cart section **/
#define CNF_CART_KANBAN             CNFO_INT(   CNFS_CART           , "kanban"              , CNFE_BOOL_ENABLED                     )   /* Restore Posters */
#define CNF_CART_CARTSPRITE         CNFO_INT(   CNFS_CART           , "cart_sprite"         , CNFE_CART_CARTSPRITE_ENABLED          )   /* DC Cart Height */
#define CNF_CART_ZANKI              CNFO_INT(   CNFS_CART           , "zanki"               , CNFE_BOOL_ENABLED                     )   /* Zanki Position Fix */

/** Event section **/
#define CNF_EVENT_VSYNC             CNFO_INT(   CNFS_EVENT          , "vsync_mode"          , CNFE_EVENT_VSYNC_EVSET                )   /* Vsync Mode */
#define CNF_EVENT_43MD              CNFO_INT(   CNFS_EVENT          , "43_mode"             , CNFE_EVENT_43MD_NOINTRO               )   /* Enforce 4:3 Mode */
#define CNF_EVENT_OVERLAYFIT        CNFO_INT(   CNFS_EVENT          , "overlay_fit"         , CNFE_EVENT_MOVIE_STRETCH              )   /* Overlay Fill Mode */
#define CNF_EVENT_MOVIEFIT          CNFO_INT(   CNFS_EVENT          , "movie_fit"           , CNFE_EVENT_MOVIE_FIT                  )   /* FMV Fill Mode */
#define CNF_EVENT_SUBTITLE          CNFO_INT(   CNFS_EVENT          , "subtitle"            , CNFE_BOOL_ENABLED                     )   /* Use Subtitles */

/** Miscellaneous section **/
#define CNF_MISC_PTCLPOLYSCL        CNFO_FLOAT( CNFS_MISC           , "ptcl_poly_scl"       , 8.0f                                  )   /* Particle Polygon Scale */
#define CNF_MISC_EVEQUIPMENT        CNFO_INT(   CNFS_MISC           , "ev_equip"            , CNFE_BOOL_ENABLED                     )   /* Player Equipment in Events */
#define CNF_MISC_RACETREEMOD        CNFO_INT(   CNFS_MISC           , "race_tree_mod"       , CNFE_BOOL_ENABLED                     )   /* Draw Race Tree Modifier Shadows */
#define CNF_MISC_PAUSEFONTCOL       CNFO_INT(   CNFS_MISC           , "pause_font_col"      , CNFE_MISC_PAUSEFONTCOL_LIGHTER        )   /* Pause Font Color */
#define CNF_MISC_DCRING             CNFO_INT(   CNFS_MISC           , "dc_ring"             , CNFE_BOOL_ENABLED                     )   /* DC Ring Shadows */
#define CNF_MISC_SHADOWRES          CNFO_INT(   CNFS_MISC           , "shadow_res"          , CNFE_MISC_SHDWRES_LOW                 )   /* Shadow Map Resolution */
#define CNF_MISC_NOSHADOWS          CNFO_INT(   CNFS_MISC           , "no_shadows"          , CNFE_BOOL_DISABLED                    )   /* Disable Shadows */

/** Experimental section **/
#define CNF_EXP_UIFILTER            CNFO_INT(   CNFS_EXP            , "uifilter"            , CNFE_BOOL_DISABLED                    )   /* Dreamcast UI Filtering */
#define CNF_EXP_DCMENUFADE          CNFO_INT(   CNFS_EXP            , "dc_menu_fade"        , CNFE_BOOL_DISABLED                    )   /* DC Main Menu Fading Fix */

/** Compatibility section **/
#define CNF_COMPAT_PLBROKENFIX      CNFO_INT(   CNFS_COMPAT         , "pl_brokenfix"        , CNFE_BOOL_DISABLED                    )   /* Broken Character Model Fix */
#define CNF_COMPAT_PLTEXMAT         CNFO_INT(   CNFS_COMPAT         , "pl_texmat"           , CNFE_BOOL_DISABLED                    )   /* Character Diffuse Material */
#define CNF_COMPAT_NOCHMOD          CNFO_INT(   CNFS_COMPAT         , "chw_mod"             , CNFE_BOOL_DISABLED                    )   /* Disable Modifiers in Chao World */
#define CNF_COMPAT_OLDATEST         CNFO_INT(   CNFS_COMPAT         , "old_atest"           , CNFE_BOOL_DISABLED                    )   /* Use Old Alpha Test Parameters */

/** Debug section **/
#define CNF_DEBUG_FRAMEINFO         CNFO_INT(   CNFS_DEBUG          , "frametime_info"      , CNFE_BOOL_DISABLED                    )   /* Debug framtime info */
#define CNF_DEBUG_GAMESPEED         CNFO_INT(   CNFS_DEBUG          , "game_speed"          , 0                                     )   /* Game speed modifier */
#define CNF_DEBUG_EVENT             CNFO_INT(   CNFS_DEBUG          , "event"               , CNFE_BOOL_DISABLED                    )   /* Event debug features */
#define CNF_DEBUG_MODIFIER          CNFO_INT(   CNFS_DEBUG          , "modifier"            , CNFE_BOOL_DISABLED                    )   /* Draw modifier models */
#define CNF_DEBUG_MAXMIPLEV         CNFO_INT(   CNFS_DEBUG          , "maxmiplev"           , 0                                     )   /* Maximum Mipmap Level */
#define CNF_DEBUG_DISABLE_ALERT     CNFO_INT(   CNFS_DEBUG          , "no_alerts"           , CNFE_BOOL_DISABLED                    )   /* Disable Alert Message Boxes */
#define CNF_DEBUG_EXTRAINFO         CNFO_INT(   CNFS_DEBUG          , "extra_info"          , CNFE_BOOL_DISABLED                    )   /* Disable Alert Message Boxes */

#endif/*H_CMN_CONFIG_DEF*/
