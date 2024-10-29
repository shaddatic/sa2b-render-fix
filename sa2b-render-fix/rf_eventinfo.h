/*
*   SA2 Render Fix - '/rf_eventinfo.h'
*
*   Description:
*       Contains working version of the event data while it's 
*   not included in SAMT.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_EVENTINFO_H_
#define _RF_EVENTINFO_H_

#include <sa2b/ninja/ninja.h>

typedef struct 
{
    NJS_CNK_OBJECT* pObject;
    int entries;
    char gap[4];
}
EventTexAnimSub1;

typedef struct 
{
    int startidx;
    int maxidx;
}
EventTexAnimSub0;

typedef struct 
{
    EventTexAnimSub1* somethingelse;
    EventTexAnimSub0* something;
    int count;
}
EventTexAnim;

typedef struct
{
    NJS_CNK_OBJECT* object;
    NJS_MOTION* motion;
    NJS_MOTION* shape;
    GJS_OBJECT* GjsObject;
    NJS_CNK_OBJECT* ShadowModel;
    int Unknown;
    NJS_POINT3 Position;
    int attr;
    int layer;
}
EventEntityData;

typedef struct
{
    NJS_MOTION* motion;
    NJS_MOTION* shape;
}
EventBigDataMotion;

typedef struct
{
    NJS_CNK_OBJECT* object;
    EventBigDataMotion* motions;
    int nbMotion;
    int Unknown;
}
EventBigData;

typedef struct
{
    EventEntityData* EntityList;
    int EntityCount;
    int* CameraMotionIDList;
    int CameraMotionIDCount;
    int* ParticleMotionIDList;
    int ParticleMotionIDCount;
    EventBigData* Big;
    int FrameCount;
}
EventSceneData;

typedef struct
{
    int count;
    int AlphaValues[32];
    NJS_VECTOR* ReflectionVtxs;
}
EV_REFLECT_DATA;

typedef struct
{
    NJS_CNK_OBJECT *pRoot;
    NJS_CNK_OBJECT *pAttach1;
    NJS_CNK_OBJECT *pObject1;
    NJS_CNK_OBJECT *pAttach2;
    NJS_CNK_OBJECT *pObject2;
}
EVENT_EQUIPMENT;

typedef struct
{
    EventSceneData* scenes;
    NJS_TEXLIST* texlist;
    int nbScene;
    Sint16* SpriteSizes;
    EV_REFLECT_DATA* reflections;
    NJS_CNK_OBJECT* BlareObjects;
    NJS_CNK_OBJECT* MechParts;
    NJS_CNK_OBJECT* MilesTails;
    EVENT_EQUIPMENT* Equipment;
    EventTexAnim* UVAnims;
    int dropShadow;
}
EventFileHeader;

#define EventData               DATA_REF(EventFileHeader, 0x0204FE20)
#define SceneData               DATA_REF(EventSceneData*, 0x01DB0FD4)
#define EventFrame              DATA_REF(f32            , 0x01DB0FC0)
#define EventSceneFrame         DATA_REF(f32            , 0x01DB0FC4)
#define EventScene              DATA_REF(int            , 0x01DB0FC8)
#define DisableCutscene         DATA_REF(bool           , 0x0174B007)
#define CutsceneMode            DATA_REF(int            , 0x01A283FC)
#define EventUseFlare           DATA_REF(int            , 0x01A298EC)
#define EventFlarePos           DATA_REF(NJS_POINT3     , 0x01A298E0)
#define EventActive             DATA_REF(bool           , 0x0174AFF9)
#define EventNum                DATA_REF(int            , 0x01A28AF4)

#define EventBigScene           DATA_REF(s32            , 0x01DB0FBC)
#define EventBigFrame           DATA_REF(f32            , 0x01DB0F90)

#define EventCamera             DATA_REF(NJS_CAMERA     , 0x01D19C20)

#define EventReflectionListPos      DATA_ARY(NJS_POINT3, 0x01A28AF8, [32])
#define EventReflectionListNorm     DATA_ARY(NJS_VECTOR, 0x01A28C78, [32])

#define EventEquipmentMatrices      DATA_ARY(NJS_MATRIX, 0x01DB0500, [36])
#define EventEquipmentFlags         DATA_ARY(Sint8     , 0x01DB0BC0, [36])

#define EventEquipmentIndexes       DATA_ARY(Sint32    , 0x0104CEA0, [18])

#define EventDebugInfo              DATA_REF(s32  , 0x01DB0BE8)

#define EventCameraInit         FUNC_PTR(void, __cdecl, (void)                                       , 0x005FA160)
#define EventDrawEquipment      FUNC_PTR(void, __cdecl, (void)                                       , 0x00601BB0)
#define EventDrawObjects        FUNC_PTR(void, __cdecl, (int idxScene, int idxLayer, b32 bDrawShadow), 0x005F96B0)
#define EventLightInit          FUNC_PTR(void, __cdecl, (void)                                       , 0x005FA2B0)
#define EventDrawFlare          FUNC_PTR(void, __cdecl, (NJS_POINT3*)                                , 0x006C7600)
#define EventDrawSprites        FUNC_PTR(void, __cdecl, (void)                                       , 0x00603E60)
#define EventDebug              FUNC_PTR(void, __cdecl, (void)                                       , 0x00600C20)
#define EventDebugNull          FUNC_PTR(void, __cdecl, (void)                                       , 0x00600E00)
#define EventDrawScreenQuad     FUNC_PTR(void, __cdecl, (void)                                       , 0x005FA5D0)

#endif/*_RF_EVENTINFO_H_*/
