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
*     - In RF_EarlyInit : Yes
*     - In RF_Init      : No
*     - Otherwise       : No
*/
typedef struct
{
    /****** Version >= 0 ************************************************************/
    uint32_t version;

    /*
    *   Set Render Fix's modifier triangle buffer to a different size. Most useful
    *   for mods that draw a large number of modifiers and would otherwise max out
    *   the default buffer. If this is called multiple times, the largest values
    *   will be used.
    * 
    *   Updates:
    *     - 1.3.2 : the 'nbTriList' parameter is obsolete and does nothing.
          - 1.3.3 : both parameters switched to 'int32_t', over 'size_t'
    * 
    *   Parameters:
    *     - nbTri     : Total number of triangles the buffer can store (default 2048)
    *     - nbTriList : Total number of models the buffer can store (obsolete)
    */
    void(__cdecl* SetModBufferSize)(int32_t nbTri, int32_t nbTriList);

    /*
    *   Disable modifier shadows in Chao World. Useful if you intend to implement
    *   your own shadow system in Chao World.
    */
    void(__cdecl* CheapShadowChaoWorldDisable)(void);
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
*     - In RF_EarlyInit : Yes
*     - In RF_Init      : Yes
*     - Otherwise       : No
*/
typedef struct
{
    /****** Version >= 0 ************************************************************/
    uint32_t version;

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
*     - In RF_EarlyInit : No
*     - In RF_Init      : Yes
*     - Otherwise       : Yes
*/
typedef struct
{
    /****** Version >= 0 ************************************************************/
    uint32_t version;

    /**** Global ****/
    bool (__cdecl* BackColorDraw)(void);    /* the back-color is enabled            */
    bool (__cdecl* SpotLightFix)(void);     /* spot lights have been fixed          */
    bool (__cdecl* EnvMapFlip)(void);       /* env maps have been flipped           */
    bool (__cdecl* BackFaceCulling)(void);  /* back-face culling is AUTO by default */
    bool (__cdecl* FixModelTint)(void);     /* model tinting is fixed               */

    /**** Shadows ****/
    float(__cdecl* ShadowOpacityGlobal)(void);  /* opacity of shadows globally      */
    float(__cdecl* ShadowOpacityChao)(void);    /* opacity of shadows in Chao World */

    /**** Cheap Shadows ****/
    bool (__cdecl* CheapShadow)(void);                  /* modifier shadows are enabled                 */
    bool (__cdecl* CheapShadowPerformance)(void);       /* the modifiers are in Performance mode        */
    bool (__cdecl* CheapShadowUltraPerformance)(void);  /* the modifiers are in Ultra Performance mode  */
    bool (__cdecl* CheapShadowPlayer)(void);            /* the player is using modifier shadows         */
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
*     - In RF_EarlyInit : No
*     - In RF_Init      : Yes
*     - Otherwise       : Yes
*/
typedef struct
{
    /****** Version >= 0 ************************************************************/
    uint32_t version;

    /**** Null Draw ****/
    /*
    *   Goes through the steps of drawing, such as matrix calculations, without
    *   actually drawing anything. Useful if said calculations are all you need.
    * 
    *   Parameters:
    *     - model   : Pointer to a Chunk model
    *     - object  : Pointer to a Chunk object
    */
    int32_t(__cdecl* CnkNullDrawModel)(  const NJS_CNK_MODEL*  model  );
    void   (__cdecl* CnkNullDrawObject)( const NJS_CNK_OBJECT* object );

    /**** Animate Motion (Null Draw) ****/
    /*
    *   Goes through the steps of animating, such as matrix calculations & calling
    *   motion callbacks, without actually drawing anything. Useful if said
    *   calculations or callbacks are all you need.
    * 
    *   Parameters:
    *     - object      : Pointer to a Chunk object
    *     - motion      : Pointer to a Ninja Motion array
    *     - motion_link : Pointer to a Ninja Motion Link
    *     - frame       : Frame of the motion to draw
    */
    void   (__cdecl* CnkAnimateMotion)(     const NJS_CNK_OBJECT* object, NJS_MOTION*      motion,      float frame );
    void   (__cdecl* CnkAnimateMotionLink)( const NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, float frame );

    /**** Modifier Draw ****/
    /*
    *   Draw modifier volume models and objects. Should only be called inside a
    *   Tasks' 'disp_shad' (offset 0x2C) displayer function.
    * 
    *   Parameters:
    *     - model   : Pointer to a Chunk modifier volume model
    *     - object  : Pointer to a Chunk modifier volume object
    */
    int32_t(__cdecl* CnkModDrawModel)(  const NJS_CNK_MODEL*  model  );
    void   (__cdecl* CnkModDrawObject)( const NJS_CNK_OBJECT* object );

    /**** Modifier Draw Motion ****/
    /*
    *   Draw modifier volume motions. Should only be called inside a Tasks'
    *   'disp_shad' (offset 0x2C) displayer function.
    * 
    *   Parameters:
    *     - object      : Pointer to a Chunk modifier volume object
    *     - motion      : Pointer to a Ninja Motion array
    *     - motion_link : Pointer to a Ninja Motion Link
    *     - frame       : Frame of the motion to draw
    */
    void   (__cdecl* CnkModDrawMotion)(     const NJS_CNK_OBJECT* object, const NJS_MOTION*      motion,      float frame );
    void   (__cdecl* CnkModDrawMotionLink)( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, float frame );

    /**** Modifier Common Draw ****/
    /*
    *   Draw common modifier models. Should only be called inside a Tasks'
    *   'disp_shad' (offset 0x2C) displayer function.
    */
    void   (__cdecl* DrawBasicShadow)( void );
    void   (__cdecl* AL_ShadowDraw)(   void );

    /****** Version >= 1 ************************************************************/
    /*
    *   Draw a multi-vertex, 2D texture with 'count'.
    *
    *   Parameters:
    *     - polygon : NJS_TEXTURE_VTX list
    *     - count   : number of entries in 'polygon'
    *     - trans   : is transparent
    */
    void(__cdecl* DrawTextureEx)(const NJS_TEXTURE_VTX* polygon, Int count, Int trans);
    /*
    *   Draw a multi-vertex, 2D polygon with 'n'.
    *
    *   Examples:
    *       p->DrawPolygon2D(poly, count, -1.0f, NJD_FILL | NJD_TRANSPARENT)
    *
    *   Parameters:
    *     - p       : POINT2COL list
    *     - n       : number of entries in 'p'
    *     - pri     : draw priority (-1<->-65535)
    *     - attr    : draw attributes
    */
    void(__cdecl* DrawPolygon2D)(const NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr);

    /****** Version >= 2 ************************************************************/
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
    void(__cdecl* DrawLineStrip3D)( const NJS_POINT3* vtx, Sint32 Count, Float r, Uint32 Color );
    void(__cdecl* DrawLineList3D)(  const NJS_POINT3* vtx, Sint32 Count, Float r, Uint32 Color );
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
    void(__cdecl* DrawLineStrip2D)( const NJS_POINT2* vtx, Float ooz, Sint32 Count, Float r, Uint32 Color );
    void(__cdecl* DrawLineList2D)(  const NJS_POINT2* vtx, Float ooz, Sint32 Count, Float r, Uint32 Color );
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
*     - In RF_EarlyInit : Yes
*     - In RF_Init      : Yes
*     - Otherwise       : Yes
*/
typedef struct
{
    /****** Version >= 0 ************************************************************/
    uint32_t version;

    /**** Back Face Culling ****/
    /*
    *   Set back-face culling to a specific mode. Useful for forcing a specific cull
    *   mode for effects, or overriding the user setting for back-face culling. Only
    *   has an effect for Chunk model rendering.
    * 
    *   Parameters:
    *     - mode    : Culling mode to be set (default 'AUTO'/'NONE')
    */
    void(__cdecl* SetCullMode)( RFRS_CULLMD mode );

    /**** Transparancy Mode ****/
    /*
    *   Set transparancy rendering to a specific mode.
    *
    *   Parameters:
    *     - mode    : Transparancy mode to be set (default 'AUTO')
    */
    void(__cdecl* SetTransMode)( RFRS_TRANSMD mode );

    /**** Alpha Test ****/
    /*
    *   Set alpha test compare function and reference value.
    *
    *   Parameters:
    *     - mode    : Compare mode to be used (default 'GEQ')
    *     - ref     : A value from 0<->255 to compare against (default 64)
    */
    void(__cdecl* SetAlphaTestFunc)( RFRS_CMPMD mode );
    void(__cdecl* SetAlphaTestRef)(  int32_t    ref  );

    /****** Version >= 1 ************************************************************/
    /*
    *   Set the winding mode of modifier models. All modifiers must be drawn with
    *   matching normals. If a model has inverted normals, or is being drawn with
    *   negative scale, this must be set to 'INVERSE'.
    *
    *   Parameters:
    *     - mode    : winding mode to use (default 'NORMAL')
    */
    void(__cdecl* SetModifierMode)( RFRS_MODMD mode );
    /*
    *   Set the draw mode of opaque/transparent Chunk strips. This is useful for
    *   drawing Chunk models in two passes for transparancy sorting.
    *
    *   Parameters:
    *     - mode    : strip type(s) to draw (default 'ALL')
    */
    void(__cdecl* SetCnkDrawMode)( RFRS_CNKDRAWMD mode );
}
RFAPI_RENDERSTATE;

/************************/
/*  Shader API          */
/************************/
/*
*   The Render Fix 'Shader' API is for loading & replacing DirectX 9 shaders.
*
*   Availablility:
*     - In RF_EarlyInit : Yes
*     - In RF_Init      : Yes
*     - Otherwise       : Yes
*/
typedef struct
{
    /****** Version >= 0 ************************************************************/
    uint32_t version;

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
*     - In RF_EarlyInit : Yes
*     - In RF_Init      : Yes
*     - Otherwise       : Yes
*/
typedef struct
{
    /****** Version >= 0 ************************************************************/
    uint32_t version;

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
*   accessed through one of the RF mod function exports as a parameter, or directly
*   by searching Render Fix for the 'rfapi_core' dllexport. If it can't be found,
*   the loaded RF version is before v1.3.
*/
typedef struct
{
    uint8_t release, major, minor, hotfix;
}
RF_VERSION;

typedef struct
{
    /****** Version >= 0 ************************************************************/
    uint32_t version;

    /**** Mod version ****/
    RF_VERSION rf_version;                      /* current Render Fix version       */

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
