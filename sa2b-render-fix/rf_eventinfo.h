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
    int ShapeMotionID;
    GJS_OBJECT* GCModel;
    NJS_CNK_OBJECT* ShadowModel;
    int Unknown;
    NJS_POINT3 Position;
    int Attributes;
    int Layer;
}
EventEntityData;

typedef struct
{
    EventEntityData* EntityList;
    int EntityCount;
    int* CameraMotionIDList;
    int CameraMotionIDCount;
    int* ParticleMotionIDList;
    int ParticleMotionIDCount;
    void* Big;
    int FrameCount;
}
EventSceneData;

typedef struct
{
    EventSceneData* scenes;
    NJS_TEXLIST* texlist;
    int nbScene;
    Sint16* SpriteSizes;
    void* reflections;
    NJS_CNK_OBJECT* BlurModels;
    NJS_CNK_OBJECT* MechParts;
    NJS_CNK_OBJECT* MilesTails;
    void* UpgradeData;
    EventTexAnim* UVAnims;
    int dropShadow;
}
EventFileHeader;

#define EventData               DataRef(EventFileHeader, 0x0204FE20)
#define SceneData               DataRef(EventSceneData*, 0x01DB0FD4)
#define EventFrame              DataRef(float32_t      , 0x01DB0FC0)
#define EventSceneFrame         DataRef(float32_t      , 0x01DB0FC4)
#define EventScene              DataRef(int            , 0x01DB0FC8)
#define DisableCutscene         DataRef(bool           , 0x0174B007)
#define CutsceneMode            DataRef(int            , 0x01A283FC)
#define EventUseFlare           DataRef(int            , 0x01A298EC)
#define EventFlarePos           DataRef(NJS_POINT3     , 0x01A298E0)
#define EventActive             DataRef(bool           , 0x0174AFF9)
#define EventNum                DataRef(int            , 0x01A28AF4)

#define EventOverrideInfo       DataAry(int            , 0x01DB0BC0, [12])

#define EventCameraInit         FuncPtr(void, __cdecl, ()                                                , 0x005FA160)
#define EventDrawEquipment      FuncPtr(void, __cdecl, ()                                                , 0x00601BB0)
#define EventDrawObjects        FuncPtr(void, __cdecl, (int idxScene, int idxLayer, bool32_t bDrawShadow), 0x005F96B0)
#define EventLightInit          FuncPtr(void, __cdecl, ()                                                , 0x005FA2B0)
#define EventDrawFlare          FuncPtr(void, __cdecl, (NJS_POINT3*)                                     , 0x006C7600)
#define EventDrawSprites        FuncPtr(void, __cdecl, ()                                                , 0x00603E60)
#define EventDebug              FuncPtr(void, __cdecl, ()                                                , 0x00600C20)
#define EventDebugNull          FuncPtr(void, __cdecl, ()                                                , 0x00600E00)
#define EventDrawScreenQuad     FuncPtr(void, __cdecl, ()                                                , 0x005FA5D0)

#endif/*_RF_EVENTINFO_H_*/
