#include <sa2b/core.h>
#include <sa2b/mods.h>
#include <sa2b/modloader.h>

/** Utility **/
#include <sa2b/util/ml_type.h>
#include <sa2b/util/dllexport.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_draw.h>
#include <rf_renderstate.h>
#include <rf_feature.h>
#include <rf_ctrl.h>

#define RELEASE         (1)
#define MAJOR           (3)
#define MINOR           (0)

#define CTRL_API_VER    (0)
#define CNFG_API_VER    (0)
#define FEAT_API_VER    (0)
#define DRAW_API_VER    (0)
#define STAT_API_VER    (0)

typedef struct
{
    uint8_t release, major, minor, _reserved;
}
RF_VERSION;

typedef struct
{
    /**** Version >= 0 ******************************/
    uint32_t version;

    /** Shadows **/
    void(__cdecl* CheapShadowChaoWorldDisable)(void);
}
RFAPI_CONTROL;

const RFAPI_CONTROL rfapi_control =
{
    .version = CTRL_API_VER,

    .CheapShadowChaoWorldDisable = RFCTRL_CheapShadowChaoWorldDisable,
};

typedef struct
{
    /**** Version >= 0 ******************************/
    uint32_t version;

    int32_t    (__cdecl* ConfigGetInt)(    const char* section, const char* key, int32_t     deflt );
    bool       (__cdecl* ConfigGetBool)(   const char* section, const char* key, bool        deflt );
    const char*(__cdecl* ConfigGetString)( const char* section, const char* key, const char* deflt );
}
RFAPI_CONFIG;

const RFAPI_CONFIG rfapi_config =
{
    .version = CNFG_API_VER,

    .ConfigGetInt    = RF_ConfigDirectGetInt,
    .ConfigGetBool   = RF_ConfigDirectGetBool,
    .ConfigGetString = RF_ConfigDirectGetString,
};

typedef struct
{
    /**** Version >= 0 ******************************/
    uint32_t version;

    /** Global **/
    bool (__cdecl* BackColorDraw)(void);
    bool (__cdecl* SpotLightFix)(void);
    bool (__cdecl* EnvMapFlip)(void);
    bool (__cdecl* BackFaceCulling)(void);

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

const RFAPI_FEATURE rfapi_feature =
{
    .version = FEAT_API_VER,

    .BackColorDraw = RFF_BackColorDraw,
    .SpotLightFix = RFF_SpotLightFix,
    .EnvMapFlip = RFF_EnvMapFlip,
    .BackFaceCulling = RFF_BackFaceCulling,

    .ShadowOpacityGlobal = RFF_ShadowOpacityGlobal,
    .ShadowOpacityChao = RFF_ShadowOpacityChao,

    .CheapShadow = RFF_CheapShadow,
    .CheapShadowPerformance = RFF_CheapShadowPerformance,
    .CheapShadowUltraPerformance = RFF_CheapShadowUltraPerformance,
    .CheapShadowPlayer = RFF_CheapShadowPlayer,
};

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
    int32_t(__cdecl* CnkModDrawModel)(  NJS_CNK_MODEL* model   );
    void   (__cdecl* CnkModDrawObject)( NJS_CNK_OBJECT* object );

    /** Modifier draw motion **/
    void   (__cdecl* CnkModDrawMotion)(     NJS_CNK_OBJECT* object, NJS_MOTION*      motion,      float frame );
    void   (__cdecl* CnkModDrawMotionLink)( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, float frame );

    /** Modifier common draw **/
    void   (__cdecl* DrawBasicShadow)( void );
    void   (__cdecl* AL_ShadowDraw)(   void );
}
RFAPI_DRAW;

const RFAPI_DRAW rfapi_draw =
{
    .version = DRAW_API_VER,

    .CnkNullDrawModel = njCnkNullDrawModel,
    .CnkNullDrawObject = njCnkNullDrawObject,

    .CnkAnimateMotion = njCnkAnimateMotion,
    .CnkAnimateMotionLink = njCnkAnimateMotionLink,

    .CnkModDrawModel = njCnkModDrawModel,
    .CnkModDrawObject = njCnkModDrawObject,

    .CnkModDrawMotion = njCnkModDrawMotion,
    .CnkModDrawMotionLink = njCnkModDrawMotionLink,

    .DrawBasicShadow = DrawBasicShadow,
    .AL_ShadowDraw = AL_ShadowDraw,
};

typedef struct
{
    /**** Version >= 0 ******************************/
    uint32_t version;

    /** Culling set **/
    void(__cdecl* SetCullMode)(RFRS_CULLMD mode);

    /** Transparancy set **/
    void(__cdecl* SetTransMode)(RFRS_TRANSMD mode);
}
RFAPI_RENDERSTATE;

const RFAPI_RENDERSTATE rfapi_rstate =
{
    .version = STAT_API_VER,

    .SetCullMode = RFRS_SetCullMode,

    .SetTransMode = RFRS_SetTransMode,
};

typedef struct
{
    /**** Version >= 0 ******************************/
    RF_VERSION           version;

    /** RF_EarlyInit APIs **/
    const RFAPI_CONTROL* pApiControl;

    /** RF_EarlyInit/Init APIs **/
    const RFAPI_CONFIG*  pApiConfig;

    /** APIs **/
    const RFAPI_FEATURE*     pApiFeature;
    const RFAPI_RENDERSTATE* pApiRenderState;
    const RFAPI_DRAW*        pApiDraw;
}
RFAPI_CORE;

EXPORT_DLL
RFAPI_CORE rfapi_core =
{
    .version = { RELEASE, MAJOR, MINOR, 0 },
};

typedef void(__cdecl RF_INIT)(const RFAPI_CORE*, const char*, const HelperFunctions*);

static void
ApiCallByFuncName(const char* name)
{
    const size_t nb_mod = ModGetTotalNumber();

    for (size_t i = 0; i < nb_mod; ++i)
    {
        const mod_handle* mhp = ModGetHandlePosition(i);

        RF_INIT* const init = ModGetExport(mhp, name);

        if (init)
            init(&rfapi_core, ModGetPath(mhp), ML_GetHelperFunctions());
    }
}

void
RFAPI_Init(void)
{
    /** Enable usable APIs **/
    rfapi_core.pApiControl = &rfapi_control;
    rfapi_core.pApiConfig  = &rfapi_config;

    ApiCallByFuncName("RF_EarlyInit");

    /** Disable Control API, as it can't be
        used past this point **/
    rfapi_core.pApiControl = nullptr;
}

void
RFAPI_End(void)
{
    /** Enable newly Init'd APIs **/
    rfapi_core.pApiFeature     = &rfapi_feature;
    rfapi_core.pApiRenderState = &rfapi_rstate;
    rfapi_core.pApiDraw        = &rfapi_draw;

    ApiCallByFuncName("RF_Init");

    /** Disable Config API, as it can't be
        used past this point **/
    rfapi_core.pApiConfig = nullptr;
}
