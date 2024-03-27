#include <sa2b/core.h>
#include <sa2b/mods.h>
#include <sa2b/modloader.h>

/** Utility **/
#include <sa2b/util/ml_type.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_draw.h>
#include <rf_cull.h>
#include <rf_feature.h>

#define RELEASE         (1)
#define MAJOR           (3)
#define MINOR           (0)

#define FEAT_API_VER    (0)
#define DRAW_API_VER    (0)

typedef struct
{
    uint8_t release, major, minor, _reserved;
}
RF_VERSION;

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
    bool (__cdecl* CheapShadowPlayer)(void);
}
RFAPI_FEATURE;

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

    /** Culling set **/
    void   (__cdecl* SetCullMode)( RFE_CULLMODE mode );
}
RFAPI_DRAW;

typedef struct
{
    /**** Version >= 0 ******************************/
    RF_VERSION     version;

    const RFAPI_FEATURE* pApiFeature;
    const RFAPI_DRAW*    pApiDraw;
}
RFAPI_CORE;

__declspec(dllexport)
const RFAPI_FEATURE rfapi_feature =
{
    .version = FEAT_API_VER,

    .BackColorDraw   = RFF_BackColorDraw,
    .SpotLightFix    = RFF_SpotLightFix,
    .EnvMapFlip      = RFF_EnvMapFlip,
    .BackFaceCulling = RFF_BackFaceCulling,

    .ShadowOpacityGlobal = RFF_ShadowOpacityGlobal,
    .ShadowOpacityChao   = RFF_ShadowOpacityChao,

    .CheapShadow            = RFF_CheapShadow,
    .CheapShadowPerformance = RFF_CheapShadowPerformance,
    .CheapShadowPlayer      = RFF_CheapShadowPlayer,
};

__declspec(dllexport)
const RFAPI_DRAW rfapi_draw =
{
    DRAW_API_VER,

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

    .SetCullMode = RF_SetCullMode,
};

__declspec(dllexport)
const RFAPI_CORE rfapi_core =
{
    .version = { RELEASE, MAJOR, MINOR, 0 },

    .pApiFeature = &rfapi_feature,
    .pApiDraw    = &rfapi_draw,
};

typedef void(__cdecl RF_INIT)(const RFAPI_CORE*, const char*, const HelperFunctions*);

void
RFAPI_Init(void)
{
    const size_t nb_mod = ModGetTotalNumber();

    for (size_t i = 0; i < nb_mod; ++i)
    {
        const mod_handle* mhp = ModGetHandlePosition(i);

        RF_INIT* const init = ModGetExport(mhp, "RF_Init");

        if (init)
            init(&rfapi_core, ModGetPath(mhp), ML_GetHelperFunctions());
    }
}
