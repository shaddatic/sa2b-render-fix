#include <sa2b/core.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_draw.h>
#include <rf_feature.h>

/** Constants **/
#ifdef  NDEBUG
#   define RELEASE         (1)
#else
#   define RELEASE         (0)
#endif

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
    RF_VERSION version;
}
RFAPI_CORE;

typedef bool(__cdecl RF_FeatureTest)(void);

typedef struct
{
    uint32_t version;

    RF_FeatureTest* CheapShadowEnabled;
    RF_FeatureTest* CheapShadowPlayerEnabled;

    float(__cdecl* ShadowOpacityGlobal)(void);
    float(__cdecl* ShadowOpacityChao)(void);
}
RFAPI_FEATURE;

typedef struct
{
    uint32_t version;

    int32_t(__cdecl* CnkNullDrawModel)(NJS_CNK_MODEL* model);
    void(__cdecl* CnkNullDrawObject)(NJS_CNK_OBJECT* object);

    void(__cdecl* CnkAnimateMotion)(NJS_CNK_OBJECT* object, NJS_MOTION* motion, float frame);
    void(__cdecl* CnkAnimateMotionLink)(NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, float frame);

    int32_t(__cdecl* CnkModDrawModel)(NJS_CNK_MODEL* model);
    void(__cdecl* CnkModDrawObject)(NJS_CNK_OBJECT* object);

    void(__cdecl* DrawBasicShadow)(void);
    void(__cdecl* AL_ShadowDraw)(void);
}
RFAPI_DRAW;

__declspec(dllexport)
RFAPI_CORE rfapi_core =
{
    { RELEASE, MAJOR, MINOR, 0 },
};

__declspec(dllexport)
RFAPI_FEATURE rfapi_feature =
{
    FEAT_API_VER,

    RF_CheapShadow,
    RF_CheapShadowPlayer,
    RF_ShadowOpacityGlobal,
    RF_ShadowOpacityChao,
};

__declspec(dllexport)
RFAPI_DRAW rfapi_draw =
{
    DRAW_API_VER,

    njCnkNullDrawModel,
    njCnkNullDrawObject,

    njCnkAnimateMotion,
    njCnkAnimateMotionLink,

    njCnkModDrawModel,
    njCnkModDrawObject,

    DrawBasicShadow,
    AL_ShadowDraw,
};
