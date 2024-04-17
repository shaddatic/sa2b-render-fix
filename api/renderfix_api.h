/*
*   SA2 Render Fix - '/renderfix_api.h'
*
*   Description:
*       External header for interfacing with Render Fix's mod
*   API.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_EXTERN_API_
#define _RF_EXTERN_API_

/************************/
/*  Mod Loader          */
/************************/
#ifdef  SA2MODLOADER_H
typedef NJS_OBJECT      NJS_CNK_OBJECT;

#endif/*SA2MODLOADER_H*/

/************************/
/*  Abstract Types      */
/************************/
typedef void                d3d_vtx_shader;
typedef void                d3d_pxl_shader;

/************************/
/*  Types               */
/************************/
typedef double              float64_t;  /* 8 byte wide float value                  */
typedef char                utf8;       /* Supports UTF-8 strings                   */

/************************/
/*  Enums               */
/************************/
typedef enum
{
    RFRS_CULLMD_END = -1,        /* End and reset to default                        */

    RFRS_CULLMD_AUTO,            /* Set culling mode by model flags                 */
    RFRS_CULLMD_NONE,            /* No culling                                      */
    RFRS_CULLMD_NORMAL,          /* Normal culling                                  */
    RFRS_CULLMD_INVERSE,         /* Inverted culling                                */
}
RFRS_CULLMD;

typedef enum
{
    RFRS_TRANSMD_END = -1,      /* End and reset to default                         */

    RFRS_TRANSMD_AUTO,          /* Set trans mode by model flags and global state   */
    RFRS_TRANSMD_OPAQUE,        /* Draw opaque                                      */
    RFRS_TRANSMD_ALPHATEST,     /* Draw with alpha test (and Z buffer)              */
    RFRS_TRANSMD_TRANSPARENT,   /* Draw fully transparant (no Z buffer)             */
}
RFRS_TRANSMD;

/************************/
/*  Control API         */
/************************/
typedef struct
{
    /**** Version >= 0 ******************************/
    uint32_t version;

    /** Modifier buffer **/
    void(__cdecl* SetModBufferSize)(size_t nbTri, size_t nbTriList);

    /** Shadows **/
    void(__cdecl* CheapShadowChaoWorldDisable)(void);
}
RFAPI_CONTROL;

/************************/
/*  Config API          */
/************************/
typedef struct
{
    /**** Version >= 0 ******************************/
    uint32_t version;

    int32_t    (__cdecl* ConfigGetInt)(    const char* section, const char* key, int32_t     deflt );
    bool       (__cdecl* ConfigGetBool)(   const char* section, const char* key, bool        deflt );
    float64_t  (__cdecl* ConfigGetFloat)(  const char* section, const char* key, float64_t   deflt );
    const char*(__cdecl* ConfigGetString)( const char* section, const char* key, const char* deflt );
}
RFAPI_CONFIG;

/************************/
/*  Feature Check API   */
/************************/
typedef struct
{
    /**** Version >= 0 ******************************/
    uint32_t version;

    /** Global **/
    bool (__cdecl* BackColorDraw)(void);
    bool (__cdecl* SpotLightFix)(void);
    bool (__cdecl* EnvMapFlip)(void);
    bool (__cdecl* BackFaceCulling)(void);
    bool (__cdecl* FixModelTint)(void);

    /** Shadows **/
    float(__cdecl* ShadowOpacityGlobal)(void);
    float(__cdecl* ShadowOpacityChao)(void);

    /** Cheap Shadows **/
    bool (__cdecl* CheapShadow)(void);
    bool (__cdecl* CheapShadowPerformance)(void);
    bool (__cdecl* CheapShadowUltraPerformance)(void);
    bool (__cdecl* CheapShadowPlayer)(void);
}
RFAPI_FEATURE;

/************************/
/*  Draw API            */
/************************/
typedef struct
{
    /**** Version >= 0 ******************************/
    uint32_t version;

    /** Null draw **/
    int32_t(__cdecl* CnkNullDrawModel)(  NJS_CNK_MODEL*  model  );
    void   (__cdecl* CnkNullDrawObject)( NJS_CNK_OBJECT* object );

    /** Animate motion (null draw) **/
    void   (__cdecl* CnkAnimateMotion)(     NJS_CNK_OBJECT* object, NJS_MOTION*      motion,      float frame );
    void   (__cdecl* CnkAnimateMotionLink)( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, float frame );

    /** Modifier draw **/
    int32_t(__cdecl* CnkModDrawModel)(  NJS_CNK_MODEL*  model  );
    void   (__cdecl* CnkModDrawObject)( NJS_CNK_OBJECT* object );

    /** Modifier draw motion **/
    void   (__cdecl* CnkModDrawMotion)(     NJS_CNK_OBJECT* object, NJS_MOTION*      motion,      float frame );
    void   (__cdecl* CnkModDrawMotionLink)( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, float frame );

    /** Modifier common draw **/
    void   (__cdecl* DrawBasicShadow)( void );
    void   (__cdecl* AL_ShadowDraw)(   void );
}
RFAPI_DRAW;

/************************/
/*  Render State API    */
/************************/
typedef struct
{
    /**** Version >= 0 ******************************/
    uint32_t version;

    /** Culling set **/
    void(__cdecl* SetCullMode)( RFRS_CULLMD mode );

    /** Transparancy set **/
    void(__cdecl* SetTransMode)( RFRS_TRANSMD mode );
}
RFAPI_RENDERSTATE;

/************************/
/*  Shader API          */
/************************/
typedef struct
{
    /**** Version >= 0 ******************************/
    uint32_t version;

    /** Load shader **/
    d3d_vtx_shader* (__cdecl* LoadVtxShader)( const utf8* fpath );
    d3d_pxl_shader* (__cdecl* LoadPxlShader)( const utf8* fpath );

    /** Replace shader **/
    void(__cdecl* ReplaceVtxShader)( int index, d3d_vtx_shader* pVtxShader );
    void(__cdecl* ReplacePxlShader)( int index, d3d_pxl_shader* pVtxShader );
}
RFAPI_SHADER;

/************************/
/*  Core API            */
/************************/
typedef struct
{
    uint8_t release, major, minor, _reserved;
}
RF_VERSION;

typedef struct
{
    /**** Version >= 0 ******************************/
    RF_VERSION           version;

    /** RF_EarlyInit APIs **/
    const RFAPI_CONTROL* pApiControl;

    /** RF_EarlyInit/Init APIs **/
    const RFAPI_CONFIG*  pApiConfig;

    /** APIs **/
    const RFAPI_FEATURE* pApiFeature;
    const RFAPI_DRAW*    pApiDraw;

    /** Render State **/
    const RFAPI_RENDERSTATE* pApiRenderState;
    const RFAPI_SHADER*      pApiShader;
}
RFAPI_CORE;

#endif/*_RF_EXTERN_API_*/
