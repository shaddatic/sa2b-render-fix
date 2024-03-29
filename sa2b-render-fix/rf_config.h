/*
*   SA2 Render Fix - '/rf_config.h'
*
*   Description:
*       Render Fix config reading, setting, & constants.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_CONFIG_H_
#define _RF_CONFIG_H_

/************************/
/*  Includes            */
/************************/
#include <rf_config/rfcnf_enum.h>
#include <rf_config/rfcnf_sect.h>

/************************/
/*  Constants           */
/************************/
/****** Config options ******************************************************************/
/**                           | Section             | Key                   | Default  **/
/** Global section **/
#define CNF_GLOBAL_IGBIX        CNFS_GLOBAL         , "gidx_ignore"         , 1         /* Ignore Global Texture Index */
#define CNF_GLOBAL_BFACECULL    CNFS_GLOBAL         , "backface_cull"       , 1         /* Back-Face Culling */
#define CNF_GLOBAL_BACKCOLOR    CNFS_GLOBAL         , "backcolor"           , 1         /* Draw Back-Color */
#define CNF_GLOBAL_PTCLSCALE    CNFS_GLOBAL         , "ptcl_scl"            , 1         /* Fix Particle Scale */
#define CNF_GLOBAL_SPRITE       CNFS_GLOBAL         , "sprite"              , 1         /* Fix 3D Sprites */
#define CNF_GLOBAL_MDLTINT      CNFS_GLOBAL         , "model_tint"          , 2         /* Fix Model Tints */
#define CNF_GLOBAL_SCRNTINT     CNFS_GLOBAL         , "screen_tint"         , 1         /* Fix Screen Tint */
#define CNF_GLOBAL_SPOTLITE     CNFS_GLOBAL         , "spotlite"            , 1         /* Fix Spot Lights */
#define CNF_GLOBAL_ENVFLIP      CNFS_GLOBAL         , "env_flip"            , 1         /* Flip Environment Map Textures" */

/** Shadows section **/
#define CNF_SHADOW_CHS_MODE     CNFS_SHADOW         , "cheap_shadow"        , 3         /* ???? */
#define CNF_SHADOW_GLMODE       CNFS_SHADOW         , "mode_gl"             , 2         /* Global Shadow Mode */
#define CNF_SHADOW_PLMODE       CNFS_SHADOW         , "mode_pl"             , 2         /* Character Shadows */
#define CNF_SHADOW_RES          CNFS_SHADOW         , "resolution"          , 1         /* Shadow Map Resolution */
#define CNF_SHADOW_GLOPACITY    CNFS_SHADOW         , "opacity_gl"          , 1         /* Global Opacity */
#define CNF_SHADOW_CHOPACITY    CNFS_SHADOW         , "opacity_ch"          , 2         /* Chao World Opacity */

/** Restorations section **/
#define CNF_COMMON_EJET         CNFS_COMMON         , "e_jet"               , 1         /* Enemy Jet Effects */
#define CNF_COMMON_EEMBLEM      CNFS_COMMON         , "e_emblem"            , 1         /* GUN Emblems */
#define CNF_COMMON_AISHEILD     CNFS_COMMON         , "e_ai_shield"         , 1         /* DC GUN Hunter Shield */
#define CNF_COMMON_ESTGTEX      CNFS_COMMON         , "e_stg_tex"           , 1         /* Stage Specific Enemy Textures */
#define CNF_COMMON_TR_CHAOS     CNFS_COMMON         , "e_chaos_trans"       , 1         /* Artificial Chaos Transparency */
#define CNF_COMMON_TR_BLOON     CNFS_COMMON         , "balloon_trans"       , 1         /* Item Balloon Transparency */
#define CNF_COMMON_TR_GOAL      CNFS_COMMON         , "goalring_trans"      , 1         /* Goal Ring Transparency */
#define CNF_COMMON_UDREEL       CNFS_COMMON         , "udreel"              , 1         /* Up Down Reel Fix */
#define CNF_COMMON_ITEMBOX      CNFS_COMMON         , "itembox"             , 1         /* Item-Box Fix */
#define CNF_COMMON_JOTREE       CNFS_COMMON         , "jo_tree"             , 1         /* Tree Jungle Object */
#define CNF_COMMON_PRSIREN      CNFS_COMMON         , "pr_siren"            , 1         /* Prison Siren Fix */
#define CNF_COMMON_EXPLOSION    CNFS_COMMON         , "e_explosion"         , 1         /* Explosion Draw Fix */
#define CNF_COMMON_MIZUGOMI     CNFS_COMMON         , "mizugomi"            , 1         /* Water Particulates */
#define CNF_COMMON_DCRING       CNFS_COMMON         , "dc_ring"             , 0         /* DC Ring Shadows */

/** Main Menus section **/
#define CNF_MENUS_FADEFIX       CNFS_MENUS          , "fade_fix"            , 1         /* 16:9 Fade Fix */
#define CNF_MENUS_MAP_STRETCH   CNFS_MENUS          , "map_stretch"         , 1         /* Stage Select: Stretch Fix */
#define CNF_MENUS_MAP_TEXTBAR   CNFS_MENUS          , "map_textbar"         , 1         /* Stage Select: Restore Text Bar */

/** Emblem Get section **/
#define CNF_EGET_FADEIN         CNFS_EGET           , "fade_in"             , 1         /* Fade Restore */
#define CNF_EGET_PTCLFIX        CNFS_EGET           , "sparkle"             , 1         /* Fix Particles */

/** White Jungle section **/
#define CNF_FG_WATERFOG         CNFS_FG             , "water_fog"           , 1         /* Fix water/fog draw order */

/** City Escape section **/
#define CNF_CE_LITEMOD          CNFS_CE             , "lightmod"            , 1         /* Restore Lighting Modifiers */

/** Aquatic Mine section **/
#define CNF_AM_MURKY            CNFS_AM             , "murky"               , 1         /* Restore Murky Water Effect */

/** Cannons Core section **/
#define CNF_CC_PITFALL          CNFS_CC             , "pitfall"             , 1         /* Restore Pitfall */
#define CNF_CC_KURUMA           CNFS_CC             , "kuruma"              , 1         /* Restore Gears */

/** City Escape section **/
#define CNF_BBOGY_PULSE         CNFS_BBOGY          , "glowpulse"           , 1         /* Restore Pulsing Glow Effect */
#define CNF_BBOGY_LIGHTS        CNFS_BBOGY          , "lights"              , 1         /* Restore Lighting */
#define CNF_BBOGY_SUNDOORS      CNFS_BBOGY          , "sundoors"            , 1         /* Restore Sundoors */

/** City Escape section **/
#define CNF_CART_KANBAN         CNFS_CART           , "kanban"              , 1         /* Restore Posters */
#define CNF_CART_SEAFIX         CNFS_CART           , "seafix"              , 1         /* Sea Fix */

/** Event section **/
#define CNF_EVENT_DISPREPLCE    CNFS_EVENT          , "disp_replace"        , 0         /* Enhanced Displayer */
#define CNF_EVENT_DRAWEQUIP     CNFS_EVENT          , "draw_equip"          , 0         /* Draw Player Equipment */
#define CNF_EVENT_DRAWMOD       CNFS_EVENT          , "draw_mod"            , 1         /* Draw Shadow Modifiers */
#define CNF_EVENT_43MD          CNFS_EVENT          , "enforce_43"          , 0         /* Enforce 4:3 Mode */
#define CNF_EVENT_TEXANIM       CNFS_EVENT          , "texanim"             , 1         /* Fix Texture Animations */

/** Experimental section **/
#define CNF_EXP_SHD_OPACITY_SW  CNFS_EXP            , "shd_opacity_sw"      , 0         /* Change Shadow Map Opacity in Chao World */
#define CNF_EXP_MILESTAILMOD    CNFS_EXP            , "miles_tail_mod"      , 0         /* Draw Tails' Tail Modifier Shadows */
#define CNF_EXP_RACETREEMOD     CNFS_EXP            , "race_tree_mod"       , 0         /* Draw Race Tree Modifier Shadows */

/** Debug section **/
#define CNF_DEBUG_OBJPAK_W      CNFS_DEBUG          , "objpak_write"        , 1         /* Allow Writing To obj.pak */
#define CNF_DEBUG_ENVFIX        CNFS_DEBUG          , "env_fix"             , 1         /* Fix Environment Map Rendering */
#define CNF_DEBUG_JUMPAURA      CNFS_DEBUG          , "jmp_aura"            , 1         /* Force Jump Aura DB Flag */
#define CNF_DEBUG_BFC_EVENT     CNFS_DEBUG          , "bfc_event"           , 1         /* Disable Back-Face Culling in Events */
#define CNF_DEBUG_CHAOS0TEX     CNFS_DEBUG          , "chaos0tex"           , 1         /* Custom Chaos 0 Model Support */
#define CNF_DEBUG_DCSHAD_PATCH  CNFS_DEBUG          , "dcshadpatch"         , 1         /* Patch DC Shadows Crash Issue */

/** Hidden section **/
#define CNF_HIDDEN_VERSION      CNFS_HIDDEN         , "cnf_ver"             , 0         /* Config file version */
#define CNF_HIDDEN_DXVK_CHK     CNFS_HIDDEN         , "dxvk_chk"            , 0         /* If the user has been asked about DXVK */

/************************/
/*  Functions           */
/************************/
EXTERN_START
/****** Init ****************************************************************/
void        RF_ConfigInit( void );  /* Open config file                     */
void        RF_ConfigEnd(  void );  /* Save & free config file              */

/****** Config get **********************************************************/
int         RF_ConfigGetInt(    const utf8* section, const utf8* key, int         def );
bool        RF_ConfigGetBool(   const utf8* section, const utf8* key, bool        def );
const utf8* RF_ConfigGetString( const utf8* section, const utf8* key, const utf8* def );

/****** Config set *********************************************************/
void        RF_ConfigSetInt(    const utf8* section, const utf8* key, int         set );
void        RF_ConfigSetBool(   const utf8* section, const utf8* key, bool        set );
void        RF_ConfigSetString( const utf8* section, const utf8* key, const utf8* set );

EXTERN_END

#endif/*_RF_CONFIG_H_*/
