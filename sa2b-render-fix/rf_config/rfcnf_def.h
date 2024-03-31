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
/** Model tint fix mode **/
typedef enum
{
    CNFE_GLOBAL_MDLTINT_DISABLED,
    CNFE_GLOBAL_MDLTINT_DREAMCAST,
    CNFE_GLOBAL_MDLTINT_ENABLED,
}
CNFE_GLOBAL_MDLTINT;

/****** Shadows Section *****************************************************/
/** Cheap Shadow mode **/
typedef enum
{
    CNFE_SHADOW_CHSMD_DISABLED,
    CNFE_SHADOW_CHSMD_ULTRA_PERFORMANCE,
    CNFE_SHADOW_CHSMD_PERFORMANCE,
    CNFE_SHADOW_CHSMD_ENABLED,
}
CNFE_SHADOW_CHSMD;

/** Global mode **/
typedef enum
{
    CNFE_SHADOW_GLMD_DISABLED,
    CNFE_SHADOW_GLMD_VANILLA,
    CNFE_SHADOW_GLMD_MODIFIER,
}
CNFE_SHADOW_GLMD;

/** Player mode **/
typedef enum
{
    CNFE_SHADOW_PLMD_VANILLA,
    CNFE_SHADOW_PLMD_ENHANCED,
    CNFE_SHADOW_PLMD_EQUIPMENT,
    CNFE_SHADOW_PLMD_MODIFIER,
}
CNFE_SHADOW_PLMD;

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

/** Shadow opacity **/
typedef enum
{
    CNFE_SHADOW_OPACITY_VANILLA,
    CNFE_SHADOW_OPACITY_DREAMCAST,
    CNFE_SHADOW_OPACITY_DREAMCAST_CHAO,
}
CNFE_SHADOW_OPACITY;

/************************/
/*  Constants           */
/************************/
/****** Config sections *****************************************************/
/** Main **/
#define CNFS_GLOBAL         "main"
#define CNFS_SHADOW         "shadows"
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

/** Experimental **/
#define CNFS_EXP            "experimental"

/** Debug **/
#define CNFS_DEBUG          "debug"

/** Hidden **/
#define CNFS_HIDDEN         "internal"

/****** Config options *****************************************************************************************                        */
/**                               | Type      | Section             | Key                   | Default          *                        */
/** Global section **/
#define CNF_GLOBAL_IGBIX            CNFO_INT(   CNFS_GLOBAL         , "gidx_ignore"         , CNFE_BOOL_ENABLED                     )   /* Ignore Global Texture Index */
#define CNF_GLOBAL_BFACECULL        CNFO_INT(   CNFS_GLOBAL         , "backface_cull"       , CNFE_BOOL_ENABLED                     )   /* Back-Face Culling */
#define CNF_GLOBAL_BACKCOLOR        CNFO_INT(   CNFS_GLOBAL         , "backcolor"           , CNFE_BOOL_ENABLED                     )   /* Draw Back-Color */
#define CNF_GLOBAL_PTCLSCALE        CNFO_INT(   CNFS_GLOBAL         , "ptcl_scl"            , CNFE_BOOL_ENABLED                     )   /* Fix Particle Scale */
#define CNF_GLOBAL_SPRITE           CNFO_INT(   CNFS_GLOBAL         , "sprite"              , CNFE_BOOL_ENABLED                     )   /* Fix 3D Sprites */
#define CNF_GLOBAL_MDLTINT          CNFO_INT(   CNFS_GLOBAL         , "model_tint"          , CNFE_BOOL_ENABLED                     )   /* Fix Model Tints */
#define CNF_GLOBAL_SCRNTINT         CNFO_INT(   CNFS_GLOBAL         , "screen_tint"         , CNFE_BOOL_ENABLED                     )   /* Fix Screen Tint */
#define CNF_GLOBAL_SPOTLITE         CNFO_INT(   CNFS_GLOBAL         , "spotlite"            , CNFE_BOOL_ENABLED                     )   /* Fix Spot Lights */
#define CNF_GLOBAL_ENVFLIP          CNFO_INT(   CNFS_GLOBAL         , "env_flip"            , CNFE_BOOL_ENABLED                     )   /* Flip Environment Map Textures" */

/** Shadows section **/
#define CNF_SHADOW_CHS_MODE         CNFO_INT(   CNFS_SHADOW         , "cheap_shadow"        , CNFE_SHADOW_CHSMD_ENABLED             )   /* ???? */
#define CNF_SHADOW_GLMODE           CNFO_INT(   CNFS_SHADOW         , "mode_gl"             , CNFE_SHADOW_GLMD_MODIFIER             )   /* Global Shadow Mode */
#define CNF_SHADOW_PLMODE           CNFO_INT(   CNFS_SHADOW         , "mode_pl"             , CNFE_SHADOW_PLMD_EQUIPMENT            )   /* Character Shadows */
#define CNF_SHADOW_RES              CNFO_INT(   CNFS_SHADOW         , "resolution"          , CNFE_SHADOW_RES_LOW                   )   /* Shadow Map Resolution */
#define CNF_SHADOW_GLOPACITY        CNFO_INT(   CNFS_SHADOW         , "opacity_gl"          , CNFE_SHADOW_OPACITY_DREAMCAST         )   /* Global Opacity */
#define CNF_SHADOW_CHOPACITY        CNFO_INT(   CNFS_SHADOW         , "opacity_ch"          , CNFE_SHADOW_OPACITY_DREAMCAST_CHAO    )   /* Chao World Opacity */

/** Restorations section **/
#define CNF_COMMON_EJET             CNFO_INT(   CNFS_COMMON         , "e_jet"               , CNFE_BOOL_ENABLED                     )   /* Enemy Jet Effects */
#define CNF_COMMON_EEMBLEM          CNFO_INT(   CNFS_COMMON         , "e_emblem"            , CNFE_BOOL_ENABLED                     )   /* GUN Emblems */
#define CNF_COMMON_AISHEILD         CNFO_INT(   CNFS_COMMON         , "e_ai_shield"         , CNFE_BOOL_ENABLED                     )   /* DC GUN Hunter Shield */
#define CNF_COMMON_ESTGTEX          CNFO_INT(   CNFS_COMMON         , "e_stg_tex"           , CNFE_BOOL_ENABLED                     )   /* Stage Specific Enemy Textures */
#define CNF_COMMON_TR_CHAOS         CNFO_INT(   CNFS_COMMON         , "e_chaos_trans"       , CNFE_BOOL_ENABLED                     )   /* Artificial Chaos Transparency */
#define CNF_COMMON_TR_BLOON         CNFO_INT(   CNFS_COMMON         , "balloon_trans"       , CNFE_BOOL_ENABLED                     )   /* Item Balloon Transparency */
#define CNF_COMMON_TR_GOAL          CNFO_INT(   CNFS_COMMON         , "goalring_trans"      , CNFE_BOOL_ENABLED                     )   /* Goal Ring Transparency */
#define CNF_COMMON_UDREEL           CNFO_INT(   CNFS_COMMON         , "udreel"              , CNFE_BOOL_ENABLED                     )   /* Up Down Reel Fix */
#define CNF_COMMON_ITEMBOX          CNFO_INT(   CNFS_COMMON         , "itembox"             , CNFE_BOOL_ENABLED                     )   /* Item-Box Fix */
#define CNF_COMMON_JOTREE           CNFO_INT(   CNFS_COMMON         , "jo_tree"             , CNFE_BOOL_ENABLED                     )   /* Tree Jungle Object */
#define CNF_COMMON_PRSIREN          CNFO_INT(   CNFS_COMMON         , "pr_siren"            , CNFE_BOOL_ENABLED                     )   /* Prison Siren Fix */
#define CNF_COMMON_EXPLOSION        CNFO_INT(   CNFS_COMMON         , "e_explosion"         , CNFE_BOOL_ENABLED                     )   /* Explosion Draw Fix */
#define CNF_COMMON_MIZUGOMI         CNFO_INT(   CNFS_COMMON         , "mizugomi"            , CNFE_BOOL_ENABLED                     )   /* Water Particulates */
#define CNF_COMMON_DCRING           CNFO_INT(   CNFS_COMMON         , "dc_ring"             , CNFE_BOOL_DISABLED                    )   /* DC Ring Shadows */

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

/** City Escape section **/
#define CNF_CART_KANBAN             CNFO_INT(   CNFS_CART           , "kanban"              , CNFE_BOOL_ENABLED                     )   /* Restore Posters */
#define CNF_CART_SEAFIX             CNFO_INT(   CNFS_CART           , "seafix"              , CNFE_BOOL_ENABLED                     )   /* Sea Fix */

/** Event section **/
#define CNF_EVENT_DISPREPLCE        CNFO_INT(   CNFS_EVENT          , "disp_replace"        , CNFE_BOOL_DISABLED                    )   /* Enhanced Displayer */
#define CNF_EVENT_DRAWEQUIP         CNFO_INT(   CNFS_EVENT          , "draw_equip"          , CNFE_BOOL_DISABLED                    )   /* Draw Player Equipment */
#define CNF_EVENT_DRAWMOD           CNFO_INT(   CNFS_EVENT          , "draw_mod"            , CNFE_BOOL_ENABLED                     )   /* Draw Shadow Modifiers */
#define CNF_EVENT_43MD              CNFO_INT(   CNFS_EVENT          , "enforce_43"          , CNFE_BOOL_DISABLED                    )   /* Enforce 4:3 Mode */
#define CNF_EVENT_TEXANIM           CNFO_INT(   CNFS_EVENT          , "texanim"             , CNFE_BOOL_ENABLED                     )   /* Fix Texture Animations */

/** Experimental section **/
#define CNF_EXP_SHD_OPACITY_SW      CNFO_INT(   CNFS_EXP            , "shd_opacity_sw"      , CNFE_BOOL_DISABLED                    )   /* Change Shadow Map Opacity in Chao World */
#define CNF_EXP_MILESTAILMOD        CNFO_INT(   CNFS_EXP            , "miles_tail_mod"      , CNFE_BOOL_DISABLED                    )   /* Draw Tails' Tail Modifier Shadows */
#define CNF_EXP_RACETREEMOD         CNFO_INT(   CNFS_EXP            , "race_tree_mod"       , CNFE_BOOL_DISABLED                    )   /* Draw Race Tree Modifier Shadows */

/** Debug section **/
#define CNF_DEBUG_OBJPAK_W          CNFO_INT(   CNFS_DEBUG          , "objpak_write"        , CNFE_BOOL_ENABLED                     )   /* Allow Writing To obj.pak */
#define CNF_DEBUG_ENVFIX            CNFO_INT(   CNFS_DEBUG          , "env_fix"             , CNFE_BOOL_ENABLED                     )   /* Fix Environment Map Rendering */
#define CNF_DEBUG_JUMPAURA          CNFO_INT(   CNFS_DEBUG          , "jmp_aura"            , CNFE_BOOL_ENABLED                     )   /* Force Jump Aura DB Flag */
#define CNF_DEBUG_BFC_EVENT         CNFO_INT(   CNFS_DEBUG          , "bfc_event"           , CNFE_BOOL_ENABLED                     )   /* Disable Back-Face Culling in Events */
#define CNF_DEBUG_CHAOS0TEX         CNFO_INT(   CNFS_DEBUG          , "chaos0tex"           , CNFE_BOOL_ENABLED                     )   /* Custom Chaos 0 Model Support */
#define CNF_DEBUG_DCSHAD_PATCH      CNFO_INT(   CNFS_DEBUG          , "dcshadpatch"         , CNFE_BOOL_ENABLED                     )   /* Patch DC Shadows Crash Issue */

/** Hidden section **/
#define CNF_HIDDEN_VERSION          CNFO_INT(   CNFS_HIDDEN         , "cnf_ver"             , 0                                     )   /* Config file version */
#define CNF_HIDDEN_DXVK_CHK         CNFO_INT(   CNFS_HIDDEN         , "dxvk_chk"            , false                                 )   /* If the user has been asked about DXVK */

#endif/*_RF_CONFIG_DEF_H_*/
