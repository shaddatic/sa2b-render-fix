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
*   -   Shaddatic
*
*   Feel free to import this file into your project
*/
#ifndef _RF_EXTERN_API_H_
#define _RF_EXTERN_API_H_

/************************/
/*  Mod Loader          */
/************************/
#ifdef  SA2MODLOADER_H
typedef NJS_OBJECT      NJS_CNK_OBJECT; /* Mod Loader 'Object' compatibility        */

#endif/*SA2MODLOADER_H*/

/************************/
/*  Abstract Types      */
/************************/
typedef void                d3d_vtx_shader; /* 'IDirect3DVertexShader9'             */
typedef void                d3d_pxl_shader; /* 'IDirect3DPixelShader9'              */

/************************/
/*  Types               */
/************************/
typedef double              float64_t;  /* 8 byte wide float value                  */
typedef char                utf8;       /* supports UTF-8 strings                   */

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

    RFRS_TRANSMD_AUTO,          /* set trans mode by model flags and global state   */
    RFRS_TRANSMD_OPAQUE,        /* draw opaque                                      */
    RFRS_TRANSMD_ALPHATEST,     /* draw with alpha test (and Z buffer)              */
    RFRS_TRANSMD_TRANSPARENT,   /* draw fully transparant (no Z buffer)             */
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
    *   Parameters:
    *     - nbTri     : Total number of triangles the buffer can store (default 2048)
    *     - nbTriList : Total number of models the buffer can store (default 128)
    */
    void(__cdecl* SetModBufferSize)(size_t nbTri, size_t nbTriList);

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
    float64_t  (__cdecl* ConfigGetFloat)(  const char* section, const char* key, float64_t   deflt );
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
    int32_t(__cdecl* CnkNullDrawModel)(  NJS_CNK_MODEL*  model  );
    void   (__cdecl* CnkNullDrawObject)( NJS_CNK_OBJECT* object );

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
    void   (__cdecl* CnkAnimateMotion)(     NJS_CNK_OBJECT* object, NJS_MOTION*      motion,      float frame );
    void   (__cdecl* CnkAnimateMotionLink)( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, float frame );

    /**** Modifier Draw ****/
    /*
    *   Draw modifier volume models and objects. Should only be called inside a
    *   Tasks' 'disp_shad' (offset 0x2C) displayer function.
    * 
    *   Parameters:
    *     - model   : Pointer to a Chunk modifier volume model
    *     - object  : Pointer to a Chunk modifier volume object
    */
    int32_t(__cdecl* CnkModDrawModel)(  NJS_CNK_MODEL*  model  );
    void   (__cdecl* CnkModDrawObject)( NJS_CNK_OBJECT* object );

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
    void   (__cdecl* CnkModDrawMotion)(     NJS_CNK_OBJECT* object, NJS_MOTION*      motion,      float frame );
    void   (__cdecl* CnkModDrawMotionLink)( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, float frame );

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
    void(__cdecl* DrawTextureEx)(NJS_TEXTURE_VTX* polygon, Int count, Int trans);
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
    void(__cdecl* DrawPolygon2D)(NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr);
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
    *   Set transparancy rendering to a specific mode. Only has an effect for Chunk
    *   model rendering.
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
    d3d_vtx_shader* (__cdecl* LoadVtxShader)( const utf8* fpath );
    d3d_pxl_shader* (__cdecl* LoadPxlShader)( const utf8* fpath );

    /**** Replace shader ****/
    /*
    *   Replace a vanilla game shader by index.
    *
    *   Parameters:
    *     - index       : Index of the shader as called for by the game
    *     - p___Shader  : Pointer to the new shader object
    */
    void(__cdecl* ReplaceVtxShader)( int index, d3d_vtx_shader* pVtxShader );
    void(__cdecl* ReplacePxlShader)( int index, d3d_pxl_shader* pPxlShader );
}
RFAPI_SHADER;

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
}
RFAPI_CORE;

#endif/*_RF_EXTERN_API_H_*/
