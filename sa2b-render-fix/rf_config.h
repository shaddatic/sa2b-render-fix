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
/*  Constants           */
/************************/
/****** Config sections *****************************************************/
/** Main **/
#define CNF_SECT_GLOBAL     "main"
#define CNF_SECT_SHADOW     "shadows"
#define CNF_SECT_COMMON     "common"

/** Menus **/
#define CNF_SECT_MENUS      "m_menus"
#define CNF_SECT_EGET       "eget"

/** Stages **/
#define CNF_SECT_FG         "w_jungle"
#define CNF_SECT_CE         "c_escape"
#define CNF_SECT_AM         "a_mine"
#define CNF_SECT_CC         "c_core"

/** Bosses **/
#define CNF_SECT_BBOGY      "bossbogy"

/** Other **/
#define CNF_SECT_CART       "cart"
#define CNF_SECT_EVENT      "event"

/** Experimental **/
#define CNF_SECT_EXP        "experimental"

/** Debug **/
#define CNF_SECT_DEBUG      "debug"

/****** Config options ******************************************************************/
/**                           | Section             | Key                   | Default  **/
/** Global section **/
#define CNF_GLOBAL_IGBIX        CNF_SECT_GLOBAL     , "gidx_ignore"         , 1         /* Ignore Global Texture Index */
#define CNF_GLOBAL_BFACECULL    CNF_SECT_GLOBAL     , "backface_cull"       , 1         /* Back-Face Culling */
#define CNF_GLOBAL_BACKCOLOR    CNF_SECT_GLOBAL     , "backcolor"           , 1         /* Draw Back-Color */
#define CNF_GLOBAL_PTCLSCALE    CNF_SECT_GLOBAL     , "ptcl_scl"            , 1         /* Fix Particle Scale */
#define CNF_GLOBAL_SPRITE       CNF_SECT_GLOBAL     , "sprite"              , 1         /* Fix 3D Sprites */
#define CNF_GLOBAL_MDLTINT      CNF_SECT_GLOBAL     , "model_tint"          , 2         /* Fix Model Tints */
#define CNF_GLOBAL_SCRNTINT     CNF_SECT_GLOBAL     , "screen_tint"         , 1         /* Fix Screen Tint */
#define CNF_GLOBAL_SPOTLITE     CNF_SECT_GLOBAL     , "spotlite"            , 1         /* Fix Spot Lights */
#define CNF_GLOBAL_ENVFLIP      CNF_SECT_GLOBAL     , "env_flip"            , 1         /* Flip Environment Map Textures" */

/** Shadows section **/
#define CNF_SHADOW_CHS_MODE     CNF_SECT_SHADOW     , "cheap_shadow"        , 2         /* ???? */
#define CNF_SHADOW_GLMODE       CNF_SECT_SHADOW     , "mode_gl"             , 2         /* Global Shadow Mode */
#define CNF_SHADOW_PLMODE       CNF_SECT_SHADOW     , "mode_pl"             , 2         /* Character Shadows */
#define CNF_SHADOW_RES          CNF_SECT_SHADOW     , "resolution"          , 1         /* Shadow Map Resolution */
#define CNF_SHADOW_GLOPACITY    CNF_SECT_SHADOW     , "opacity_gl"          , 1         /* Global Opacity */
#define CNF_SHADOW_CHOPACITY    CNF_SECT_SHADOW     , "opacity_ch"          , 2         /* Chao World Opacity */

/** Restorations section **/
#define CNF_COMMON_EJET         CNF_SECT_COMMON     , "e_jet"               , 1         /* Enemy Jet Effects */
#define CNF_COMMON_EEMBLEM      CNF_SECT_COMMON     , "e_emblem"            , 1         /* GUN Emblems */
#define CNF_COMMON_AISHEILD     CNF_SECT_COMMON     , "e_ai_shield"         , 1         /* DC GUN Hunter Shield */
#define CNF_COMMON_ESTGTEX      CNF_SECT_COMMON     , "e_stg_tex"           , 1         /* Stage Specific Enemy Textures */
#define CNF_COMMON_TR_CHAOS     CNF_SECT_COMMON     , "e_chaos_trans"       , 1         /* Artificial Chaos Transparency */
#define CNF_COMMON_TR_BLOON     CNF_SECT_COMMON     , "balloon_trans"       , 1         /* Item Balloon Transparency */
#define CNF_COMMON_TR_GOAL      CNF_SECT_COMMON     , "goalring_trans"      , 1         /* Goal Ring Transparency */
#define CNF_COMMON_UDREEL       CNF_SECT_COMMON     , "udreel"              , 1         /* Up Down Reel Fix */
#define CNF_COMMON_ITEMBOX      CNF_SECT_COMMON     , "itembox"             , 1         /* Item-Box Fix */
#define CNF_COMMON_JOTREE       CNF_SECT_COMMON     , "jo_tree"             , 1         /* Tree Jungle Object */
#define CNF_COMMON_EXPLOSION    CNF_SECT_COMMON     , "e_explosion"         , 1         /* Explosion Draw Fix */
#define CNF_COMMON_MIZUGOMI     CNF_SECT_COMMON     , "mizugomi"            , 1         /* Water Particulates */
#define CNF_COMMON_DCRING       CNF_SECT_COMMON     , "dc_ring"             , 0         /* DC Ring Shadows */

/** Main Menus section **/
#define CNF_MENUS_FADEFIX       CNF_SECT_MENUS      , "fade_fix"            , 1         /* 16:9 Fade Fix */
#define CNF_MENUS_MAP_STRETCH   CNF_SECT_MENUS      , "map_stretch"         , 1         /* Stage Select: Stretch Fix */
#define CNF_MENUS_MAP_TEXTBAR   CNF_SECT_MENUS      , "map_textbar"         , 1         /* Stage Select: Restore Text Bar */

/** Emblem Get section **/
#define CNF_EGET_FADEIN         CNF_SECT_EGET       , "fade_in"             , 1         /* Fade Restore */
#define CNF_EGET_PTCLFIX        CNF_SECT_EGET       , "sparkle"             , 1         /* Fix Particles */

/** White Jungle section **/
#define CNF_FG_WATERFOG         CNF_SECT_FG         , "water_fog"           , 1         /* Fix water/fog draw order */

/** City Escape section **/
#define CNF_CE_LITEMOD          CNF_SECT_CE         , "lightmod"            , 1         /* Restore Lighting Modifiers */

/** Aquatic Mine section **/
#define CNF_AM_MURKY            CNF_SECT_AM         , "murky"               , 1         /* Restore Murky Water Effect */

/** Cannons Core section **/
#define CNF_CC_PITFALL          CNF_SECT_CC         , "pitfall"             , 1         /* Restore Pitfall */

/** City Escape section **/
#define CNF_BBOGY_PULSE         CNF_SECT_BBOGY      , "glowpulse"           , 1         /* Restore Pulsing Glow Effect */
#define CNF_BBOGY_LIGHTS        CNF_SECT_BBOGY      , "lights"              , 1         /* Restore Lighting */
#define CNF_BBOGY_SUNDOORS      CNF_SECT_BBOGY      , "sundoors"            , 1         /* Restore Sundoors */

/** City Escape section **/
#define CNF_CART_KANBAN         CNF_SECT_CART       , "kanban"              , 1         /* Restore Posters */
#define CNF_CART_SEAFIX         CNF_SECT_CART       , "seafix"              , 1         /* Sea Fix */

/** Event section **/
#define CNF_EVENT_DISPREPLCE    CNF_SECT_EVENT      , "disp_replace"        , 1         /* Enhanced Displayer */
#define CNF_EVENT_DRAWEQUIP     CNF_SECT_EVENT      , "draw_equip"          , 1         /* Draw Player Equipment */
#define CNF_EVENT_DRAWMOD       CNF_SECT_EVENT      , "draw_mod"            , 1         /* Draw Shadow Modifiers */
#define CNF_EVENT_43MD          CNF_SECT_EVENT      , "enforce_43"          , 0         /* Enforce 4:3 Mode */
#define CNF_EVENT_TEXANIM       CNF_SECT_EVENT      , "texanim"             , 1         /* Fix Texture Animations */

/** Experimental Section **/
#define CNF_EXP_SHD_OPACITY_SW  CNF_SECT_EXP        , "shd_opacity_sw"      , 0         /* Change Shadow Map Opacity in Chao World */
#define CNF_EXP_MILESTAILMOD   CNF_SECT_EXP         , "miles_tail_mod"      , 0         /* Draw Tails' Tail Modifier Shadows */

/** Debug section **/
#define CNF_DEBUG_OBJPAK_W      CNF_SECT_DEBUG      , "objpak_write"        , 1         /* Allow Writing To obj.pak */
#define CNF_DEBUG_ENVFIX        CNF_SECT_DEBUG      , "env_fix"             , 1         /* Fix Environment Map Rendering */
#define CNF_DEBUG_JUMPAURA      CNF_SECT_DEBUG      , "jmp_aura"            , 1         /* Force Jump Aura DB Flag */
#define CNF_DEBUG_BFC_EVENT     CNF_SECT_DEBUG      , "bfc_event"           , 1         /* Disable Back-Face Culling in Events */
#define CNF_DEBUG_CHAOS0TEX     CNF_SECT_DEBUG      , "chaos0tex"           , 1         /* Custom Chaos 0 Model Support */
#define CNF_DEBUG_DCSHAD_PATCH  CNF_SECT_DEBUG      , "dcshadpatch"         , 1         /* Patch DC Shadows Crash Issue */

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
