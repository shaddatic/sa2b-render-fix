/*
*   SA2 Render Fix - '/rf_config/rfcnf_def.h'
*
*   Description:
*       Render Fix config setting definitions and macros.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_CONFIG_DEF_H_
#define _RF_CONFIG_DEF_H_

/************************/
/*  Macro               */
/************************/
/** Config option macros **/
#define CNFO_INT(   _section, _key, _default)       &(const RFS_CNF_INT   ) { .sect = _section, .key = _key, .def = _default }
#define CNFO_BOOL(  _section, _key, _default)       &(const RFS_CNF_BOOL  ) { .sect = _section, .key = _key, .def = _default }
#define CNFO_FLOAT( _section, _key, _default)       &(const RFS_CNF_FLOAT ) { .sect = _section, .key = _key, .def = _default }
#define CNFO_STRING(_section, _key, _default)       &(const RFS_CNF_STRING) { .sect = _section, .key = _key, .def = _default }

/************************/
/*  Enums               */
/************************/
/****** Basic Bool **********************************************************/
typedef enum
{
    CNFE_BOOL_DISABLED,
    CNFE_BOOL_ENABLED
}
CNFE_BOOL;

/****** Global Section ******************************************************/
/** Cheap Shadow mode **/
typedef enum
{
    CNFE_GLOBAL_CHSMD_DISABLED,
    CNFE_GLOBAL_CHSMD_PERFORMANCE,
    CNFE_GLOBAL_CHSMD_ENABLED,
}
CNFE_GLOBAL_CHSMD;

/** Model tint fix mode **/
typedef enum
{
    CNFE_GLOBAL_MDLTINT_DISABLED,
    CNFE_GLOBAL_MDLTINT_DREAMCAST,
    CNFE_GLOBAL_MDLTINT_ENABLED,
    CNFE_GLOBAL_MDLTINT_EXTENDED,
}
CNFE_GLOBAL_MDLTINT;

/****** Font Section ********************************************************/
/** Japanese script **/
typedef enum
{
    CNFE_FONT_KANJI_VANILLA,
    CNFE_FONT_KANJI_CLASSIC,
}
CNFE_FONT_KANJI;

/** Latin script **/
typedef enum
{
    CNFE_FONT_ASCII_VANILLA,
    CNFE_FONT_ASCII_IMPRESS,
    CNFE_FONT_ASCII_COMICSANS,
}
CNFE_FONT_ASCII;

/** Character spacing **/
typedef enum
{
    CNFE_FONT_WIDTH_TOUCHING,
    CNFE_FONT_WIDTH_SQUISHED,
    CNFE_FONT_WIDTH_COMPACT,
    CNFE_FONT_WIDTH_COMFY,
    CNFE_FONT_WIDTH_SPACY,
}
CNFE_FONT_WIDTH;

/** Space Character Width **/
typedef enum
{
    CNFE_FONT_SPACE_NONE,
    CNFE_FONT_SPACE_QUATER,
    CNFE_FONT_SPACE_THIRD,
    CNFE_FONT_SPACE_HALF,
    CNFE_FONT_SPACE_FULL,

    NB_CNFE_FONT_SPACE,
}
CNFE_FONT_SPACE;

/****** Player Section ******************************************************/
/** Player Shadow Mode **/
typedef enum
{
    CNFE_PLAYER_SHADOWMD_VANILLA,
    CNFE_PLAYER_SHADOWMD_ENHANCED,
    CNFE_PLAYER_SHADOWMD_MODIFIER,
}
CNFE_PLAYER_SHADOWMD;

/** Player Model Mode **/
typedef enum
{
    CNFE_PLAYER_MODEL_GAMECUBE,
    CNFE_PLAYER_MODEL_DREAMCAST,

    NB_CNFE_PLAYER_MODEL,
}
CNFE_PLAYER_MODEL;

/****** Shadows Section *****************************************************/
/** Shadow map resolution **/
typedef enum
{
    CNFE_SHADOW_RES_VERY_LOW,
    CNFE_SHADOW_RES_LOW,
    CNFE_SHADOW_RES_MEDIUM,
    CNFE_SHADOW_RES_HIGH,
    CNFE_SHADOW_RES_ULTRA,
    CNFE_SHADOW_RES_IMPERCEIVABLE
}
CNFE_SHADOW_RES;

/****** Cart Section ********************************************************/
/** Cart Sprite Fix **/
typedef enum
{
    CNFE_CART_CARTSPRITE_DISABLED,
    CNFE_CART_CARTSPRITE_DREAMCAST,
    CNFE_CART_CARTSPRITE_ENABLED,
}
CNFE_CART_CARTSPRITE;

/****** Event Section *******************************************************/
/** Cart Sprite Fix **/
typedef enum
{
    CNFE_EVENT_43MD_DISABLED,
    CNFE_EVENT_43MD_VANILLA,
    CNFE_EVENT_43MD_ALWAYS,
}
CNFE_EVENT_43MD;

/****** Misc Section ********************************************************/
/** Cart Sprite Fix **/
typedef enum
{
    CNFE_MISC_PAUSEFONTCOL_DARKER,
    CNFE_MISC_PAUSEFONTCOL_LIGHTER,
}
CNFE_MISC_PAUSEFONTCOL;

/************************/
/*  Constants           */
/************************/
/****** Config sections *****************************************************/
/** Main **/
#define CNFS_GLOBAL         "main"
#define CNFS_FONT           "font"
#define CNFS_PLAYER         "player"
#define CNFS_COMMON         "common"

/** Menus **/
#define CNFS_MENUS          "m_menus"
#define CNFS_EGET           "eget"

/** Stages **/
#define CNFS_FG             "w_jungle"
#define CNFS_CE             "c_escape"
#define CNFS_AM             "a_mine"
#define CNFS_CC             "c_core"

/** Bosses **/
#define CNFS_BBOGY          "bossbogy"

/** Other **/
#define CNFS_CART           "cart"
#define CNFS_EVENT          "event"

/** Miscellaneous **/
#define CNFS_MISC           "misc"

/** Experimental **/
#define CNFS_EXP            "experimental"

/** Compatibility **/
#define CNFS_COMPAT         "compatibility"

/** Debug **/
#define CNFS_DEBUG          "debug"

/** Hidden **/
#define CNFS_HIDDEN         "internal"

/****** Config options ******************************************************************************************************************/
/**                               | Type      | Section             | Key                   | Default                                  **/
/** Global section **/
#define CNF_GLOBAL_IGBIX            CNFO_INT(   CNFS_GLOBAL         , "gidx_ignore"         , CNFE_BOOL_ENABLED                     )   /* Ignore Global Texture Index */
#define CNF_GLOBAL_CHSMD            CNFO_INT(   CNFS_GLOBAL         , "mod_shadow"          , CNFE_GLOBAL_CHSMD_ENABLED             )   /* Cheap Shadow setting */
#define CNF_GLOBAL_BACKCOLOR        CNFO_INT(   CNFS_GLOBAL         , "backcolor"           , CNFE_BOOL_ENABLED                     )   /* Draw Back-Color */
#define CNF_GLOBAL_PTCLSCALE        CNFO_INT(   CNFS_GLOBAL         , "ptcl_scl"            , CNFE_BOOL_ENABLED                     )   /* Fix Particle Scale */
#define CNF_GLOBAL_SPRITE           CNFO_INT(   CNFS_GLOBAL         , "sprite"              , CNFE_BOOL_ENABLED                     )   /* Fix 3D Sprites */
#define CNF_GLOBAL_LINE             CNFO_INT(   CNFS_GLOBAL         , "line"                , CNFE_BOOL_ENABLED                     )   /* Fix line scale */
#define CNF_GLOBAL_SPOTLITE         CNFO_INT(   CNFS_GLOBAL         , "spotlite"            , CNFE_BOOL_ENABLED                     )   /* Fix Spot Lights */

/** Font section **/
#define CNF_FONT_KANJI              CNFO_INT(   CNFS_FONT           , "kanji"               , CNFE_FONT_KANJI_VANILLA               )   /* Japanese Script Font */
#define CNF_FONT_ASCII              CNFO_INT(   CNFS_FONT           , "ascii"               , CNFE_FONT_ASCII_VANILLA               )   /* Latin Script Font */
#define CNF_FONT_WIDTH              CNFO_INT(   CNFS_FONT           , "width"               , CNFE_FONT_WIDTH_COMPACT               )   /* Character Spacing */
#define CNF_FONT_SPACE              CNFO_INT(   CNFS_FONT           , "space"               , CNFE_FONT_SPACE_THIRD                 )   /* Space Character Width */
#define CNF_FONT_NOKEY              CNFO_INT(   CNFS_FONT           , "nokey"               , CNFE_BOOL_ENABLED                     )   /* Use Original Text Dialogs */

/** Player section **/
#define CNF_PLAYER_MODEL            CNFO_INT(   CNFS_PLAYER         , "model"               , CNFE_PLAYER_MODEL_GAMECUBE            )   /* Player model mode */
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

/** Main Menus section **/
#define CNF_MENUS_FADEFIX           CNFO_INT(   CNFS_MENUS          , "fade_fix"            , CNFE_BOOL_ENABLED                     )   /* 16:9 Fade Fix */
#define CNF_MENUS_MAP_STRETCH       CNFO_INT(   CNFS_MENUS          , "map_stretch"         , CNFE_BOOL_ENABLED                     )   /* Stage Select: Stretch Fix */
#define CNF_MENUS_MAP_TEXTBAR       CNFO_INT(   CNFS_MENUS          , "map_textbar"         , CNFE_BOOL_ENABLED                     )   /* Stage Select: Restore Text Bar */

/** Emblem Get section **/
#define CNF_EGET_FADEIN             CNFO_INT(   CNFS_EGET           , "fade_in"             , CNFE_BOOL_ENABLED                     )   /* Fade Restore */
#define CNF_EGET_PTCLFIX            CNFO_INT(   CNFS_EGET           , "sparkle"             , CNFE_BOOL_ENABLED                     )   /* Fix Particles */

/** White Jungle section **/
#define CNF_FG_WATERFOG             CNFO_INT(   CNFS_FG             , "water_fog"           , CNFE_BOOL_ENABLED                     )   /* Fix water/fog draw order */

/** City Escape section **/
#define CNF_CE_LITEMOD              CNFO_INT(   CNFS_CE             , "lightmod"            , CNFE_BOOL_ENABLED                     )   /* Restore Lighting Modifiers */

/** Aquatic Mine section **/
#define CNF_AM_MURKY                CNFO_INT(   CNFS_AM             , "murky"               , CNFE_BOOL_ENABLED                     )   /* Restore Murky Water Effect */

/** Cannons Core section **/
#define CNF_CC_PITFALL              CNFO_INT(   CNFS_CC             , "pitfall"             , CNFE_BOOL_ENABLED                     )   /* Restore Pitfall */
#define CNF_CC_KURUMA               CNFO_INT(   CNFS_CC             , "kuruma"              , CNFE_BOOL_ENABLED                     )   /* Restore Gears */

/** City Escape section **/
#define CNF_BBOGY_PULSE             CNFO_INT(   CNFS_BBOGY          , "glowpulse"           , CNFE_BOOL_ENABLED                     )   /* Restore Pulsing Glow Effect */
#define CNF_BBOGY_LIGHTS            CNFO_INT(   CNFS_BBOGY          , "lights"              , CNFE_BOOL_ENABLED                     )   /* Restore Lighting */
#define CNF_BBOGY_SUNDOORS          CNFO_INT(   CNFS_BBOGY          , "sundoors"            , CNFE_BOOL_ENABLED                     )   /* Restore Sundoors */

/** Cart section **/
#define CNF_CART_KANBAN             CNFO_INT(   CNFS_CART           , "kanban"              , CNFE_BOOL_ENABLED                     )   /* Restore Posters */
#define CNF_CART_SEAFIX             CNFO_INT(   CNFS_CART           , "seafix"              , CNFE_BOOL_ENABLED                     )   /* Sea Fix */
#define CNF_CART_CARTSPRITE         CNFO_INT(   CNFS_CART           , "cart_sprite"         , CNFE_CART_CARTSPRITE_ENABLED          )   /* DC Cart Height */
#define CNF_CART_ZANKI              CNFO_INT(   CNFS_CART           , "zanki"               , CNFE_BOOL_ENABLED                     )   /* Zanki Position Fix */

/** Event section **/
#define CNF_EVENT_RFDISP            CNFO_INT(   CNFS_EVENT          , "rf_disp"             , CNFE_BOOL_ENABLED                     )   /* Render Fix Renderer */
#define CNF_EVENT_DRAWEQUIP         CNFO_INT(   CNFS_EVENT          , "draw_equip"          , CNFE_BOOL_ENABLED                     )   /* Draw Player Equipment */
#define CNF_EVENT_43MD              CNFO_INT(   CNFS_EVENT          , "enforce_43"          , CNFE_EVENT_43MD_ALWAYS                )   /* Enforce 4:3 Mode */

/** Miscellaneous section **/
#define CNF_MISC_PTCLPOLYSCL        CNFO_FLOAT( CNFS_MISC           , "ptcl_poly_scl"       , 8.0f                                  )   /* Particle Polygon Scale */
#define CNF_MISC_RACETREEMOD        CNFO_INT(   CNFS_MISC           , "race_tree_mod"       , CNFE_BOOL_ENABLED                     )   /* Draw Race Tree Modifier Shadows */
#define CNF_MISC_PAUSEFONTCOL       CNFO_INT(   CNFS_MISC           , "pause_font_col"      , CNFE_MISC_PAUSEFONTCOL_LIGHTER        )   /* Pause Font Color */
#define CNF_MISC_DCRING             CNFO_INT(   CNFS_MISC           , "dc_ring"             , CNFE_BOOL_ENABLED                     )   /* DC Ring Shadows */
#define CNF_MISC_SHADOWRES          CNFO_INT(   CNFS_MISC           , "shadow_res"          , CNFE_SHADOW_RES_LOW                   )   /* Shadow Map Resolution */
#define CNF_MISC_NOSHADOWS          CNFO_INT(   CNFS_MISC           , "no_shadows"          , CNFE_BOOL_DISABLED                    )   /* Disable Shadows */

/** Experimental section **/
#define CNF_EXP_DCMENUFADE          CNFO_INT(   CNFS_EXP            , "dc_menu_fade"        , CNFE_BOOL_DISABLED                    )   /* DC Main Menu Fading Fix */

/** Compatibility section **/
#define CNF_COMPAT_NOCHMOD          CNFO_INT(   CNFS_COMPAT         , "chw_mod"             , CNFE_BOOL_DISABLED                    )   /* Disable Modifiers in Chao World */
#define CNF_COMPAT_OLDATEST         CNFO_INT(   CNFS_COMPAT         , "old_atest"           , CNFE_BOOL_DISABLED                    )   /* Use Old Alpha Test Parameters */
#define CNF_COMPAT_OFFBFC           CNFO_INT(   CNFS_COMPAT         , "off_bfc"             , CNFE_BOOL_DISABLED                    )   /* Disable Back-Face Culling */

/** Debug section **/
#define CNF_DEBUG_FRAMEINFO         CNFO_INT(   CNFS_DEBUG          , "frametime_info"      , CNFE_BOOL_DISABLED                    )   /* Debug framtime info */
#define CNF_DEBUG_MODIFIER          CNFO_INT(   CNFS_DEBUG          , "modifier"            , CNFE_BOOL_DISABLED                    )   /* Draw modifier models */
#define CNF_DEBUG_DISABLE_ALERT     CNFO_INT(   CNFS_DEBUG          , "no_alerts"           , CNFE_BOOL_DISABLED                    )   /* Disable Alert Message Boxes */

/** Hidden section **/
#define CNF_HIDDEN_DXVK_CHK         CNFO_INT(   CNFS_HIDDEN         , "dxvk_chk"            , false                                 )   /* If the user has been asked about DXVK */

#endif/*_RF_CONFIG_DEF_H_*/
