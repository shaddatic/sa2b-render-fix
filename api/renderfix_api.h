/*
*   SA2 Render Fix - '/renderfix_api.h'
*
*   Description:
*       External header for interfacing with Render Fix's mod API. For instructions
*   on usage, read the 'readme.md' file.
        It's important to note that all API availabilites assume Render Fix is
    loaded first; if it is not then availability will rely on the user's mod layout
    & will essentially be random outside the user-exported functions.
*
*   Contributors:
*     - Shaddatic
*
*   Feel free to import this file into your project
*/
#ifndef H_RF_EXTERN_API
#define H_RF_EXTERN_API

/************************/
/*  Mod Loader          */
/************************/
#ifdef  SA2MODLOADER_H
typedef NJS_OBJECT          NJS_CNK_OBJECT; /* Mod Loader 'Object' compatibility    */

#endif/*SA2MODLOADER_H*/

/************************/
/*  Macros              */
/************************/
/****** RF Version ******************************************************************/
/*
*   Description:
*     Macro for checking the current Render Fix version against a given version.
* 
*   Examples:
*     - if ( !RFD_CHECKVER(pApiCore, 1,3,3,0) ) // check if RF version too low
*
*   Parameters:
*     - api         : core api pointer
*     - rel         : minimum release part value
*     - maj         : minimum major part value 
*     - sem         : minimum semi-major part value 
*     - min         : minimum minor part value 
* 
*   Returns:
*     'true' if the current version is equal to, or above, the given version, or 'false' if it is below
*/
#define RFD_CHECKVER(api, rel, maj, sem, min) \
          ( (int)(api)->modver.release   > (rel) || ( (int)(api)->modver.release   == (rel) && \
          ( (int)(api)->modver.major     > (maj) || ( (int)(api)->modver.major     == (maj) && \
          ( (int)(api)->modver.semimajor > (sem) || ( (int)(api)->modver.semimajor == (sem) && \
          ( (int)(api)->modver.minor     > (min) || ( (int)(api)->modver.minor     == (min) ))))))) )

/************************/
/*  Abstract Types      */
/************************/
/****** Shader **********************************************************************/
typedef struct dx9_vtx_shader   dx9_vtx_shader; /* 'IDirect3DVertexShader9'         */
typedef struct dx9_pxl_shader   dx9_pxl_shader; /* 'IDirect3DPixelShader9'          */

/****** Font ************************************************************************/
typedef struct rfs_font         RFS_FONT;       /* Render Fix font object           */

/************************/
/*  Types               */
/************************/
typedef double                  f64;        /* 8 byte wide float value              */
typedef char                    utf8;       /* supports UTF-8 strings               */

/************************/
/*  Constants           */
/************************/
/****** Cnk Draw Func Bits **********************************************************/
#define RFRS_CNKFUNCMD_EASYBIT      (0x01) /* using easy draw variant               */
#define RFRS_CNKFUNCMD_SIMPLEBIT    (0x02) /* using simple draw variant             */
#define RFRS_CNKFUNCMD_MULTIBIT     (0x04) /* using multi draw variant              */
#define RFRS_CNKFUNCMD_DIRECTBIT    (0x08) /* using direct draw                     */

/************************/
/*  Enums               */
/************************/
/****** Render State Enums **********************************************************/
typedef enum
{
    RFRS_CULLMD_END = -1,        /* end and reset to default                        */

    RFRS_CULLMD_AUTO,            /* set culling mode by model flags                 */
    RFRS_CULLMD_NONE,            /* no culling                                      */
    RFRS_CULLMD_NORMAL,          /* normal culling                                  */
    RFRS_CULLMD_INVERSE,         /* inverted culling                                */
}
RFRS_CULLMD;

typedef enum
{
    RFRS_TRANSMD_END = -1,      /* end and reset to default                         */

    RFRS_TRANSMD_AUTO,          /* set transparancy mode automatically    (default) */
    RFRS_TRANSMD_OPAQUE,        /* draw without transparancy                        */
    RFRS_TRANSMD_ALPHATEST,     /* draw transparancy and alpha test    (& Z buffer) */
    RFRS_TRANSMD_TRANSPARENT,   /* draw transparancy                  (no Z buffer) */
    /*
    *     The following modes only change which transparancy mode is used, and leave
    *   'OPAQUE' mode as-is. They were implemented in version 1.3.2 and will simply
    *   do nothing in earlier versions.
    */
    RFRS_TRANSMD_AUTO_ATEST,    /* auto, use alpha test for transparancy            */
    RFRS_TRANSMD_AUTO_TRANS,    /* auto, do not use alpha test for transparancy     */
}
RFRS_TRANSMD;

typedef enum
{
    RFRS_CMPMD_END = -1,        /* end and reset to default                         */

    RFRS_CMPMD_NVR,             /* never                                            */
    RFRS_CMPMD_LSS,             /* less                                             */
    RFRS_CMPMD_EQU,             /* equal                                            */
    RFRS_CMPMD_LEQ,             /* less or equal                                    */
    RFRS_CMPMD_GTR,             /* greater                                          */
    RFRS_CMPMD_NEQ,             /* not equal                                        */
    RFRS_CMPMD_GEQ,             /* greater or equal                                 */
    RFRS_CMPMD_ALW,             /* always                                           */
}
RFRS_CMPMD;

typedef enum
{
    RFRS_ALPHAREF_END = -1,     /* end and reset to default                         */
}
RFRS_ALPHAREF;

typedef enum
{
    RFRS_MODMD_END = -1,        /* end and reset to default                         */

    RFRS_MODMD_NORMAL,          /* draw modifiers with regular winding              */
    RFRS_MODMD_INVERSE,         /* draw modifiers with inverse winding              */
}
RFRS_MODMD;

typedef enum
{
    RFRS_CNKDRAWMD_END = -1,    /* end and reset to default                         */

    RFRS_CNKDRAWMD_ALL,         /* draw all strips                                  */
    RFRS_CNKDRAWMD_OPAQUE,      /* draw only opaque strips                          */
    RFRS_CNKDRAWMD_TRANSPARENT, /* draw only transparent strips                     */
}
RFRS_CNKDRAWMD;

typedef enum
{
    RFRS_CNKFUNCMD_END = -1,     /* end and reset to default                        */

    RFRS_CNKFUNCMD_NORMAL,       /* parameters will be parsed normally              */
    RFRS_CNKFUNCMD_EASY = 1,     /* parameters will be parsed as if EasyDraw        */
    RFRS_CNKFUNCMD_SIMPLE,       /* parameters will be parsed as if SimpleDraw      */
    RFRS_CNKFUNCMD_EASYMULTI = 5,/* parameters will be parsed as if EasyMultiDraw   */
    RFRS_CNKFUNCMD_SIMPLEMULTI,  /* parameters will be parsed as if SimpleMultiDraw */
    RFRS_CNKFUNCMD_DIRECT = 8,   /* parameters will be parsed as if DirectDraw      */
}
RFRS_CNKFUNCMD;

typedef enum
{
    RFRS_CNKPASSMD_END = -1,    /* end and reset to default                         */

    RFRS_CNKPASSMD_NORMAL,      /* draw inverse tris first, then normal tris        */
    RFRS_CNKPASSMD_INVERSE,     /* draw normal tris first, then inverse tris        */
}
RFRS_CNKPASSMD;

/****** Font Enums ******************************************************************/
/** Font language **/
typedef enum
{
    FONT_LANG_JAP,  /* Japanese                                                     */
    FONT_LANG_ENG,  /* English                                                      */
    FONT_LANG_GER,  /* German                                                       */
    FONT_LANG_FRE,  /* French                                                       */
    FONT_LANG_SPA,  /* Spanish                                                      */
    FONT_LANG_ITA,  /* Italian                                                      */

    NB_FONT_LANG,   /* count                                                        */
}
RFE_FONT_LANG;

/** Font file type **/
typedef enum
{
    FONT_FTYPE_RGBA_KANJI,  /* 32bit RGBA & contains Kanji & Kana           (SA2PC) */
    FONT_FTYPE_RGBA_ASCII,  /* 32bit RGBA & contains ASCII                  (SA2PC) */

    FONT_FTYPE_1BPP_KANJI,  /* 1bpp & contains Kanji & Kana          (SA1,SADX,SA2) */
    FONT_FTYPE_1BPP_ASCII,  /* 1bpp & contains ASCII                 (SA1,SADX,SA2) */

    NB_FONT_FTYPE,          /* count                                                */
}
RFE_FONT_FTYPE;

/** Font font script type **/
typedef enum
{
    FONT_TYPE_KANJI,    /* Kanji font page                                          */
    FONT_TYPE_ASCII,    /* Ascii font page                                          */

    NB_FONT_TYPE,       /* count                                                    */
}
RFE_FONT_TYPE;

/************************/
/*  Control API         */
/************************/
/*
*   The Render Fix 'Control' API is for controlling aspects of RF and its features.
* 
*   Availablility:
*     - RF_EarlyInit : Yes
*     - RF_Init      : No
*     - After Init   : No
*/
typedef struct
{
    /****** Version >= 0 ************************************************************/
    uint32_t version;                           /* structure version                */

    /**** Modifier *************/
    /*
    *   Description:
    *     Set Render Fix's modifier triangle buffer to a different size. Most
    *   useful for mods that draw a large number of modifiers and would otherwise
    *   max out the default buffer. If this is called multiple times, the largest
    *   values will be used.
    * 
    *   Updates:
    *     - 1.3.2 : the 'nbTriList' parameter is obsolete and does nothing.
          - 1.4   : both parameters switched to 'int32_t', over 'size_t'
    * 
    *   Parameters:
    *     - nbTri     : Total number of triangles the buffer can store (default 2048)
    *     - nbTriList : Total number of models the buffer can store (obsolete)
    */
    void (__cdecl* SetModBufferSize)( int32_t nbTri, int32_t nbTriList );
    /*
    *   Description:
    *     Disable modifier shadows in Chao World. Useful if you intend to implement
    *   your own shadow system in Chao World.
    */
    void (__cdecl* CheapShadowChaoWorldDisable)( void );

    /****** Version >= 1 ************************************************************/

    /**** Event ****************/
    /*
    *   Description:
    *     Set flag to apply model material diffuse in Events when using Render
    *   Fix's own Event Renderer.
    *
    *   Notes:
    *     - Diffuse will only be applied on models using a SimpleDraw variant.
    */
    void (__cdecl* EventApplyModelDiffuse)( void );
}
RFAPI_CONTROL;

/************************/
/*  Config API          */
/************************/
/*
*   The Render Fix 'Config' API is for reading user-config entries directly from
*   RF's 'config' module. Its use should be restricted to extreme circumstances &
*   specific versions of Render Fix, as config entries are often renamed & moved
*   around. If it's important a feature is checked, use the Feature API first. If
*   the feature isn't available there yet, contact me and I'll add it.
* 
*   Availablility:
*     - RF_EarlyInit : Yes
*     - RF_Init      : Yes
*     - After Init   : No
*/
typedef struct
{
    /****** Version >= 0 ************************************************************/
    uint32_t version;                           /* structure version                */

    /*
    *   Read user-settings inside Render Fix's configuration (config.ini) file. It's
    *   important to remember that strings are stored in UTF-8 format, not basic ASCII.
    *
    *   Parameters:
    *     - section   : The section of the config option (eg. "main")
    *     - key       : The key of the config option (eg. "backface_cull")
    *     - deflt     : The default value for the option
    *
    *   Returns:
    *       The value of the config entry
    */
    int32_t    (__cdecl* ConfigGetInt)(    const char* section, const char* key, int32_t     deflt );
    bool       (__cdecl* ConfigGetBool)(   const char* section, const char* key, bool        deflt );
    f64        (__cdecl* ConfigGetFloat)(  const char* section, const char* key, f64         deflt );
    const utf8*(__cdecl* ConfigGetString)( const char* section, const char* key, const utf8* deflt );
}
RFAPI_CONFIG;

/************************/
/*  Feature Check API   */
/************************/
/*
*   The Render Fix 'Feature' API is for checking if specific features of RF are
*   enabled, or specific user-settings for those features.
*
*   Availablility:
*     - RF_EarlyInit : No
*     - RF_Init      : Yes
*     - After Init   : Yes
*/
typedef struct
{
    /****** Version >= 0 ************************************************************/
    uint32_t version;                           /* structure version                */

    /**** Global ***************/
    /*
    *   Description:
    *     If the back-color is enabled. If this is false, the back-color will
    *   always be black no matter what color it's actually set to.
    */
    bool (__cdecl* BackColorDraw)( void );
    /*
    *   Description:
    *     If spot light drawing has been fixed. This is used in Eggman stages for
    *   his walker's flashlight. If this is false, spot lights won't behave
    *   correctly.
    */
    bool (__cdecl* SpotLightFix)( void );
    /*
    *   [[deprecated( "Always 'true' as of version 1.4" )]] 
    * 
    *   Description:
    *     If environment maps have been flipped horizontally compared to vanilla.
    *   This is done to match Dreamcast, which also has env maps flipped compared
    *   to GC and PC.
    */
    bool (__cdecl* EnvMapFlip)( void );
    /*
    *   Description:
    *     If culling state is set to 'AUTO' by default. Some users may choose to
    *   turn it off, forcing the default state to 'NONE'. Even if that is the case,
    *   the culling render state can still be changed manually if needed.
    */
    bool (__cdecl* BackFaceCulling)( void );
    /*
    *   [[deprecated( "Always 'true' as of version 1.4" )]] 
    * 
    *   Description:
    *     If models have had their gray diffuse fixed. This is done by setting
    *   their diffuse material to white manually at startup.
    * 
    *   Notes:
    *     - As of version 1.3.3, models don't have their material data manually
    *       fixed. Instead, the renderer itself now correctly applies the
    *       'NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL' Ninja 3D flag.
    */
    bool (__cdecl* FixModelTint)( void );

    /**** Shadows **************/
    /*
    *   Description:
    *     Get the shadow opacity used for the main game. This is used for both
    *   modifier volumes and shadow maps.
    * 
    *   Returns:
    *     The shadow opacity ranging from 0.f (invisible) to 1.f (fully opaque).
    */
    float(__cdecl* ShadowOpacityGlobal)( void );
    /*
    *   Description:
    *     Get the shadow opacity used for Chao World. This is used for modifier
    *   volumes. Shadow maps can use this opacity, but only when the experimental
    *   feature for it is enabled.
    * 
    *   Returns:
    *     The shadow opacity ranging from 0.f (invisible) to 1.f (fully opaque).
    */
    float(__cdecl* ShadowOpacityChao)( void );

    /**** Cheap Shadows ********/
    /*
    *   Description:
    *     If Modifier Shadows, also known as 'Cheap Shadows', are enabled. If this
    *   is false, drawing modifier volumes will simply fail.
    */
    bool (__cdecl* CheapShadow)( void );
    /*
    *   Description:
    *     If Modifier Shadows are in performance mode. This reduces their 
    *   transparency sorting accuracy by drawing them in fewer Task layers.
    */
    bool (__cdecl* CheapShadowPerformance)( void );
    /*
    *   [[deprecated( "Always 'false' as of version 1.3.2" )]]
    * 
    *   Description:
    *     If Modifier Shadows are in ultra performance mode. This further reduces
    *   their transparency sorting accuracy by drawing them with the fastest method
    *   possible, without much consideration for quality.
    */
    bool (__cdecl* CheapShadowUltraPerformance)( void );
    /*
    *   Description:
    *     If the player characters are using Modifier Volumes as shadows. If this
    *   is false, they are still using the GC shadow maps.
    */
    bool (__cdecl* CheapShadowPlayer)( void );

    /****** Version >= 1 ************************************************************/

    /**** Event ****************/
    /*
    *   Description:
    *     If the "Enhanced Event Renderer" is enabled, which emulates Dreamcast
    *   draw functions, restores the original multi-light code, and more.
    */
    bool (__cdecl* NewEventRenderer)( void );

    /**** Player ********************************************/
    /*
    *   Description:
    *     If Chaos 0 is set to use his GameCube texture animation cycle.
    */
    bool (__cdecl* Chaos0TexAnim)( void );
}
RFAPI_FEATURE;

/************************/
/*  Draw API            */
/************************/
/*
*   The Render Fix 'Draw' API is for drawing, or aiding in drawing, things to the
*   screen.
*
*   Availablility:
*     - RF_EarlyInit : No
*     - RF_Init      : Yes
*     - After Init   : Yes
*/
typedef struct
{
    /****** Version >= 0 ************************************************************/
    uint32_t version;                           /* structure version                */

    /**** Null Draw/Animate Motion ****/
    /*
    *   Description:
    *     Emulates a successful Chunk draw, but doesn't actually draw anything.
    * 
    *   Parameters:
    *     - model   : chunk model
    *
    *   Returns:
    *     Always '0' as if model was drawn.
    */
    Sint32 (__cdecl* CnkNullDrawModel)( const NJS_CNK_MODEL* model );
    /*
    *   Description:
    *     Goes through the steps of drawing, such as matrix transformations, without
    *   actually drawing anything.
    *
    *   Parameters:
    *     - object  : chunk object
    */
    void (__cdecl* CnkNullDrawObject)( const NJS_CNK_OBJECT* object );
    /*
    *   Description:
    *     Goes through the steps of animating, such as matrix calculations & calling
    *   motion callbacks, without actually drawing anything.
    *
    *   Parameters:
    *     - object      : chunk object to animate
    *     - motion      : motion data for 'object'
    *     - frame       : frame of animation
    */
    void (__cdecl* CnkAnimateMotion)( const NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame );
    /*
    *   Description:
    *     Goes through the steps of animating, such as interpolating the motions, matrix
    *   calculations, & calling motion callbacks, without actually drawing anything.
    *
    *   Parameters:
    *     - object      : chunk object to animate
    *     - motion_link : motion link data and motion datas for 'object'
    *     - rate        : ratio of transition from motion 1 to motion 2 (0~1)
    */
    void (__cdecl* CnkAnimateMotionLink)( const NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float rate );

    /********************************************************/
    /*
    *   Chunk Modifier Volume
    *
    *   Notes:
    *     - Modifiers should only be drawn inside the 'disp_shad' (offset 0x2C) task
    *       displayer function.
    */

    /**** Modifier Draw ********/
    /*
    *   Description:
    *     Draw a Chunk modifier volume model.
    *
    *   Parameters:
    *     - model       : chunk modifier volume model
    *
    *   Returns:
    *     '0' if drawn, or '-1' if the model was clipped.
    */
    Sint32 (__cdecl* CnkModDrawModel)( const NJS_CNK_MODEL* model );
    /*
    *   Description:
    *     Draw a modifier volume object tree.
    *
    *   Parameters:
    *     - object      : chunk modifier volume object
    */
    void (__cdecl* CnkModDrawObject)( const NJS_CNK_OBJECT* object );
    /*
    *   Description:
    *     Draw a Chunk modifier volume motion.
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion      : motion data for 'object'
    *     - frame       : frame of animation
    */
    void (__cdecl* CnkModDrawMotion)( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame );
    /*
    *   Description:
    *     Interpolate and draw two Chunk modifier volume motions.
    *
    *   Parameters:
    *     - object      : chunk modifier volume object to animate
    *     - motion_link : motion link data and motion datas for 'object'
    *     - rate        : ratio of transition from motion 1 to motion 2 (0~1)
    */
    void (__cdecl* CnkModDrawMotionLink)( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float rate );

    /**** Modifier Common Draw ****/
    /*
    *   Description:
    *     Draw common modifier models.
    */
    void (__cdecl* DrawBasicShadow)( void );
    void (__cdecl* AL_ShadowDraw)( void );

    /****** Version >= 1 ************************************************************/

    /********************************************************/
    /*
    *   2D Draw
    */
    /********************************************************/
    /*
    *   Draw a multi-vertex, 2D texture with 'count'.
    *
    *   Parameters:
    *     - polygon : NJS_TEXTURE_VTX list
    *     - count   : number of entries in 'polygon'
    *     - trans   : is transparent
    */
    void (__cdecl* DrawTextureEx)(const NJS_TEXTURE_VTX* polygon, Int count, Int trans);
    /*
    *   Draw a multi-vertex, 2D polygon with 'n'.
    *
    *   Examples:
    *     - p->DrawPolygon2D(poly, count, -1.0f, NJD_FILL|NJD_TRANSPARENT)
    *
    *   Parameters:
    *     - p       : POINT2COL list
    *     - n       : number of entries in 'p'
    *     - pri     : draw priority (-1<->-65535)
    *     - attr    : draw attributes
    */
    void (__cdecl* DrawPolygon2D)(const NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr);

    /****** Version >= 2 ************************************************************/

    /********************************************************/
    /*
    *   Draw Line (2D/3D)
    */
    /********************************************************/
    /*
    *   Description:
    *     Draw a 3D line in either strip or list mode. 'Strip' will use the end
    *   vertex of the last line as the start vertex of the next line; 'List' will
    *   draw each pair of vertexes as seperate lines. Eg:
    *
    *     - Strip: (0, 1), (1, 2), (2, 3), ...
    *     - List : (0, 1), (2, 3), (4, 5), ...
    *
    *   Parameters:
    *     - vtx     : list of line vertexes
    *     - Count   : number of line vertexes
    *     - r       : radius, in 480p pixels
    *     - Color   : line color to draw (in 0xAA'RR'GG'BB format)
    */
    void (__cdecl* DrawLineStrip3D)( const NJS_POINT3* vtx, Sint32 Count, Float r, Uint32 Color );
    void (__cdecl* DrawLineList3D)(  const NJS_POINT3* vtx, Sint32 Count, Float r, Uint32 Color );
    /*
    *   Description:
    *     Draw a 2D line in either strip or list mode. 'Strip' will use the end
    *   vertex of the last line as the start vertex of the next line; 'List' will
    *   draw each pair of vertexes as seperate lines. Eg:
    *
    *     - Strip: (0, 1), (1, 2), (2, 3), ...
    *     - List : (0, 1), (2, 3), (4, 5), ...
    *
    *   Parameters:
    *     - vtx     : list of line vertexes
    *     - ooz     : 1/z, 'z' being the depth of the line
    *     - Count   : number of line vertexes
    *     - r       : radius, in 480p pixels
    *     - Color   : line color to draw (in 0xAA'RR'GG'BB format)
    */
    void (__cdecl* DrawLineStrip2D)( const NJS_POINT2* vtx, Float ooz, Sint32 Count, Float r, Uint32 Color );
    void (__cdecl* DrawLineList2D)(  const NJS_POINT2* vtx, Float ooz, Sint32 Count, Float r, Uint32 Color );

    /****** Version >= 3 ************************************************************/

    /********************************************************/
    /*
    *   Chunk Modifier Volume (pt. 2)
    *
    *   Notes:
    *     - Modifiers should only be drawn inside the 'disp_shad' (offset 0x2C) task
    *       displayer function.
    */
    /**** Modifier Draw Shape Motion ************************/
    /*
    *   Description:
    *     Draw a Chunk modifier volume motion.
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion      : motion data for 'object'
    *     - shape       : shape data for 'object'   (optional)
    *     - frame       : frame of animation/shape
    */
    void (__cdecl* CnkModDrawShapeMotion)( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame );
    /*
    *   Description:
    *     Interpolate and draw two Chunk modifier volume motions.
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion_link : motion data for 'object'
    *     - shape_link  : shape data for 'object'   (optional)
    *     - rate        : ratio of transition from motion/shape 1 to motion/shape 2 (0~1)
    */
    void (__cdecl* CnkModDrawShapeMotionLink)( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate );
    /*
    *   Description:
    *     Draw a Chunk modifier volume motion.
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion      : motion data for 'object'
    *     - shape       : shape data for 'object'   (optional)
    *     - frame       : frame of animation/shape
    */
    void (__cdecl* CnkModDrawShapeMotionBE)( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame );
    /*
    *   Description:
    *     Interpolate and draw two Chunk modifier volume motions.
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion_link : motion data for 'object'
    *     - shape_link  : shape data for 'object'   (optional)
    *     - rate        : ratio of transition from motion/shape 1 to motion/shape 2 (0~1)
    */
    void (__cdecl* CnkModDrawShapeMotionLinkBE)( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate );

    /********************************************************/
    /*
    *   Chunk Draw
    */
    /**** Chunk Draw ****************************************/
    /*
    *   Description:
    *     Draw a Chunk model.
    *
    *   Parameters:
    *     - model       : chunk model pointer
    *
    *   Returns:
    *     '0' if drawn, or '-1' if the model was clipped.
    */
    Sint32 (__cdecl* CnkDrawModel)( const NJS_CNK_MODEL* model );
    /*
    *   Description:
    *     Draw a Chunk object tree.
    *
    *   Parameters:
    *     - object      : chunk object
    */
    void (__cdecl* CnkDrawObject)( const NJS_CNK_OBJECT* object );

    /**** Chunk Draw Motion *********************************/
    /*
    *   Description:
    *     Draw a Chunk motion.
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion      : motion data for 'object'
    *     - frame       : frame of animation
    */
    void (__cdecl* CnkDrawMotion)( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame );
    /*
    *   Description:
    *     Interpolate and draw two Chunk motions.
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion_link : motion link data and motion datas for 'object'
    *     - rate        : ratio of transition from motion 1 to motion 2 (0~1)
    */
    void (__cdecl* CnkDrawMotionLink)( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float rate );
    
    /**** Chunk Draw Shape Motion ***************************/
    /*
    *   Description:
    *     Draw a Chunk shape motion.
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion      : motion data for 'object'
    *     - shape       : shape data for 'object'   (optional)
    *     - frame       : frame of animation/shape
    */
    void (__cdecl* CnkDrawShapeMotion)( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame );
    /*
    *   Description:
    *     Interpolate and draw two Chunk shape motions.
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion_link : motion data for 'object'
    *     - shape_link  : shape data for 'object'   (optional)
    *     - rate        : ratio of transition from motion/shape 1 to motion/shape 2 (0~1)
    */
    void (__cdecl* CnkDrawShapeMotionLink)( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate );
    
    /**** Chunk Draw Shape Motion (Big Endian) **************/
    /*
    *   Description:
    *     Draw a big endian Chunk shape motion.
    *
    *   Notes:
    *     - The 'motion' data is still little endian
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion      : motion data for 'object'
    *     - shape       : shape data for 'object'   (optional)
    *     - frame       : frame of animation/shape
    */
    void (__cdecl* CnkDrawShapeMotionBE)( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame );
    /*
    *   Description:
    *     Interpolate and draw two big endian Chunk shape motions.
    *
    *   Notes:
    *     - The 'motion_link' data is still little endian
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion_link : motion data for 'object'
    *     - shape_link  : shape data for 'object'   (optional)
    *     - rate        : ratio of transition from motion/shape 1 to motion/shape 2 (0~1)
    */
    void (__cdecl* CnkDrawShapeMotionLinkBE)( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate );

    /**** Chunk Modify **************************************/
    /*
    *   Description:
    *     Set the Chunk UV offset value for regular UVs, for texture scrolling.
    *
    *   Notes:
    *     - This is a Render Fix extension, and is not part of base Ninja.
    *     - This will *not* affect environment maps.
    *     - Reset these values to '0.f' when drawing is complete.
    *
    *   Parameters:
    *     - u, v        : u and v scroll offset
    */
    void (__cdecl* CnkSetUvScroll)( Float u, Float v );
    /*
    *   Description:
    *     Set the Chunk UV offset value for environment mapping, for texture
    *   scrolling. Scrolling applies when 'NJD_CONTROL_3D_ENV_UV_SCROLL' is set.
    *
    *   Notes:
    *     - In base Ninja this is named 'njCnkSetUvScroll', but the functionality
    *       is otherwise the same excluding the 'SimpleDraw' only limitation.
    *     - Reset these values to '0.f' when drawing is complete.
    *     - Currently only applies to normal-less environment maps, as they aren't
    *       calculated in-shader.
    *
    *   Parameters:
    *     - u, v        : u and v scroll offset
    */
    void (__cdecl* CnkSetEnvUvScroll)( Float u, Float v );
    /*
    *   Description:
    *     Set the texture ID callback function, for texture animation.
    *
    *   Notes:
    *     - This is a Render Fix extension, and is not part of base Ninja.
    *     - The returned value will be used as the new texid.
    *     - Reset the callback to 'NULL' when drawing is complete.
    *
    *   Parameters:
    *     - callback    : texture callback function
    */
    void (__cdecl* CnkSetTextureCallback)( Sint16(__cdecl* callback)(Sint16 texid) );
}
RFAPI_DRAW;

/************************/
/*  Render State API    */
/************************/
/*
*   The Render Fix 'Render State' API is for controlling how things will be drawn to
*   the screen. This is useful when the game's default states can't give the
*   intended effect.
* 
*   Once done with, call with applicable 'END' parameter to fully reset the render
*   state back to default.
*
*   Availablility:
*     - RF_EarlyInit : Yes
*     - RF_Init      : Yes
*     - After Init   : Yes
*/
typedef struct
{
    /****** Version >= 0 ************************************************************/
    uint32_t version;                           /* structure version                */

    /********************************************************/
    /*
    *   Set Renderstate
    */
    /********************************************************/
    /*
    *   Description:
    *     Set triangle culling mode for Chunk draw.
    *
    *   Notes:
    *     - 'NONE' draws all tris, but 'INVERSE' only draws double sided tris
    *     - Users may enabled 'NONE' by default by disabling back-face culling
    *     - Useful for transparency sorting
    *
    *   Parameters:
    *     - mode        : culling mode to set (default: 'AUTO'/'NONE')
    */
    void(__cdecl* SetCullMode)( RFRS_CULLMD mode );
    /*
    *   Description:
    *     Set transparency rendering mode.
    *
    *   Notes:
    *     - Useful for forcing the Z buffer on & off via alpha test
    *
    *   Parameters:
    *     - mode        : transparency mode (default: 'AUTO')
    */
    void(__cdecl* SetTransMode)( RFRS_TRANSMD mode );
    /*
    *   Description:
    *     Set alpha test compare function and reference value.
    *
    *   Parameters:
    *     - mode        : Compare mode to be used (default: 'GTR')
    *     - value       : A value from 0~255 to compare against (default: 64)
    */
    void(__cdecl* SetAlphaTestFunc)( RFRS_CMPMD mode );
    void(__cdecl* SetAlphaTestRef)(  int32_t   value );

    /****** Version >= 1 ************************************************************/
    /*
    *   Description:
    *     Set modifier model winding mode. If modifiers have inverted normals, such
    *   as being drawn with inverted scaling, this must be set to 'INVERTED' for the
    *   modifiers to work correctly.
    *
    *   Parameters:
    *     - mode        : modifier mode (default: 'NORMAL')
    */
    void(__cdecl* SetModifierMode)( RFRS_MODMD mode );
    /*
    *   Description:
    *     Set the draw mode of opaque/transparent Chunk strips, allowing for opaque
    *   and transparant strips to be drawn seperately for sorting reasons.
    *
    *   Parameters:
    *     - mode        : chunk draw mode (default: 'ALL')
    */
    void(__cdecl* SetCnkDrawMode)( RFRS_CNKDRAWMD mode );

    /****** Version >= 2 ************************************************************/
    /*
    *   Description:
    *     Set the Chunk draw function emulation mode. Dreamcast used a number of
    *   different function variants for drawing, and this allows you to emulate each of
    *   their quirks.
    *
    *   Parameters:
    *     - mode        : chunk function emulation mode (default: 'SIMPLE')
    */
    void(__cdecl* SetCnkFuncMode)( RFRS_CNKFUNCMD mode );
    /*
    *   Description:
    *     Set the transparency pass mode. If the scaling is inverted, this should be set
    *   to 'INVERSE' so the front and back faces of transparent strips can be correctly
    *   sorted.
    *
    *   Parameters:
    *     - mode        : chunk transparency pass mode (default: 'NORMAL')
    */
    void(__cdecl* SetCnkPassMode)( RFRS_CNKPASSMD mode );

    /********************************************************/
    /*
    *   Get Renderstate
    */
    /********************************************************/
    /*
    *   Description:
    *     Get the current triangle culling mode.
    */
    RFRS_CULLMD(__cdecl* GetCullMode)( void );
    /*
    *   Description:
    *     Get the current transparency mode.
    */
    RFRS_TRANSMD(__cdecl* GetTransMode)( void );
    /*
    *   Description:
    *     Get the current alpha test compare mode.
    */
    RFRS_CMPMD(__cdecl* GetAlphaTestFunc)( void );
    /*
    *   Description:
    *     Get the current alpha test reference value.
    */
    int32_t(__cdecl* GetAlphaTestRef)( void );
    /*
    *   Description:
    *     Get the current modifier mode.
    */
    RFRS_MODMD(__cdecl* GetModifierMode)( void );
    /*
    *   Description:
    *     Get the current Chunk Draw mode.
    */
    RFRS_CNKDRAWMD(__cdecl* GetCnkDrawMode)( void );
    /*
    *   Description:
    *     Get the current Chunk function emulation mode.
    */
    RFRS_CNKFUNCMD(__cdecl* GetCnkFuncMode)( void );
    /*
    *   Description:
    *     Get the current Chunk transparancy pass mode.
    */
    RFRS_CNKPASSMD(__cdecl* GetCnkPassMode)( void );
}
RFAPI_RENDERSTATE;

/************************/
/*  Shader API          */
/************************/
/*
*   The Render Fix 'Shader' API is for loading & replacing DirectX 9 shaders.
*
*   Availablility:
*     - RF_EarlyInit : Yes
*     - RF_Init      : Yes
*     - After Init   : Yes
*/
typedef struct
{
    /****** Version >= 0 ************************************************************/
    uint32_t version;                           /* structure version                */

    /**** Load shader ****/
    /*
    *   Load a pre-compiled shader file (usually .fxc).
    *
    *   Parameters:
    *     - fpath   : File path to compiled shader file
    *   
    *   Returns:
    *       A pointer to a DX9 shader object (IDirect3D(Vertex/Pixel)Shader9).
    */
    dx9_vtx_shader* (__cdecl* LoadVtxShader)( const utf8* fpath );
    dx9_pxl_shader* (__cdecl* LoadPxlShader)( const utf8* fpath );

    /**** Replace shader ****/
    /*
    *   Replace a vanilla game shader by index.
    *
    *   Parameters:
    *     - index       : Index of the shader as called for by the game
    *     - p___Shader  : Pointer to the new shader object
    */
    void(__cdecl* ReplaceVtxShader)( int index, dx9_vtx_shader* pVtxShader );
    void(__cdecl* ReplacePxlShader)( int index, dx9_pxl_shader* pPxlShader );
}
RFAPI_SHADER;

/************************/
/*  Font API            */
/************************/
/*
*   The Render Fix 'Font' API is for loading and setting game text fonts.
*
*   Availablility:
*     - RF_EarlyInit : Yes
*     - RF_Init      : Yes
*     - After Init   : Yes
*/
typedef struct
{
    /****** Version >= 0 ************************************************************/
    uint32_t version;                           /* structure version                */

    /**** Font ****/
    /*
    *   Load a game font file. Character width and space width are automatically
    *   calculated and respect user-settings.
    *
    *   Parameters:
    *     - fpath   : full path to font file
    *     - ftype   : file type of font
    *
    *   Returns:
    *       Pointer to the created font object, or nullptr if there was an error
    */
    RFS_FONT*(__cdecl* LoadFontFile)( const utf8* fpath, RFE_FONT_FTYPE ftype );
    /*
    *   Half the current space character width.
    *
    *   Japanese ASCII spaces use half the width of their Latin counterpart. 
    *   Render Fix doesn't know what is ASCII & what is ASCII_J, so only applies
    *   regular ASCII space widths. Use this to fix your Japanese ASCII fonts.
    *
    *   Parameters:
    *     - pFont   : pointer to font object
    */
    void(__cdecl* HalfSpaceWidth)( RFS_FONT* pFont );

    /**** Advanced Font ****/
    /*
    *   Set a custom character width list. (optional)
    *
    *   The width list is made up of unsigned int8's, with each character in the
    *   font getting an entry defining how wide it is in pixels. You must ensure
    *   the width list has enough entries to cover every character. If this is not
    *   the case, it will lead to undefined behavior.
    *
    *   Parameters:
    *     - pFont   : pointer to font object
    *     - pWidths : pointer to u8 array with at least as many entries as there are characters in the font
    */
    void(__cdecl* SetWidthList)( RFS_FONT* pFont, uint8_t* pWidths );

    /**** Font State ****/
    /*
    *   Replace a font in the vanilla game by language and type.
    *
    *   Parameters:
    *     - language : language to apply the font to
    *     - type     : type of the font to replace
    *     - pFont    : pointer to font object to replace with
    */
    void(__cdecl* SetFont)( RFE_FONT_LANG language, RFE_FONT_TYPE type, RFS_FONT* pFont );
    /*
    *   Get current font by language and type. This can be used to temporarily
    *   replace a font for drawing, then re-applying the original font once you're
    *   done.
    *
    *   Parameters:
    *     - language : language to get the font from
    *     - type     : type of the font to get
    *
    *   Returns:
    *       The current font being used for that language and font type
    */
    RFS_FONT*(__cdecl* GetFont)( RFE_FONT_LANG language, RFE_FONT_TYPE type );
    /*
    *   Replace a font in Chao World by type.
    *
    *   Parameters:
    *     - type     : type of the font to replace
    *     - pFont    : pointer to font object to replace with
    */
    void(__cdecl* SetChaoFont)(RFE_FONT_TYPE type, RFS_FONT* pFont);
    /*
    *   Get current font in Chao World by type. This can be used to temporarily 
    *   replace a font for drawing, then re-applying the original font once you're
    *   done.
    *
    *   Parameters:
    *     - type     : type of the font to get
    * 
    *   Returns:
    *       The current font being used for that font type
    */
    RFS_FONT*(__cdecl* GetChaoFont)( RFE_FONT_TYPE type );
}
RFAPI_FONT;

/************************/
/*  Core API            */
/************************/
/*
*   The Render Fix 'Core' API is the central hub for all the other APIs. It can be
*   accessed through one of the RF mod function exports as a parameter. Versions
*   before 1.3 did not have an API, and therefore can't call the exported function.
*/
typedef struct
{
    uint8_t release;            /* release version part    (eg. the '1' in v1.2.3.4) */
    uint8_t major;              /* major version part      (eg. the '2' in v1.2.3.4) */
    uint8_t semimajor;          /* semi-major version part (eg. the '3' in v1.2.3.4) */
    uint8_t minor;              /* minor version part      (eg. the '4' in v1.2.3.4) */
}
RF_VERSION;

typedef struct
{
    /****** Version >= 0 ************************************************************/
    uint32_t version;                           /* structure version                */

    /**** Mod Version ****/
    RF_VERSION modver;                          /* current Render Fix version       */

    /**** APIs ****/
    const RFAPI_CONTROL*     pApiControl;       /* Control API                      */
    const RFAPI_CONFIG*      pApiConfig;        /* Config API                       */
    const RFAPI_FEATURE*     pApiFeature;       /* Feature Check API                */
    const RFAPI_DRAW*        pApiDraw;          /* Draw API                         */
    const RFAPI_RENDERSTATE* pApiRenderState;   /* Render State API                 */
    const RFAPI_SHADER*      pApiShader;        /* Shader API                       */

    /****** Version >= 1 ************************************************************/
    const RFAPI_FONT*        pApiFont;          /* Font API                         */
}
RFAPI_CORE;

#endif/*H_RF_EXTERN_API*/
