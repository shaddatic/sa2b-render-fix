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

#include <samt/ninja/ninja.h>

typedef struct
{
    Sint32  texid;
    Sint16* pTiny;
}
EVENT_TEXANIM_TINYDATA;

typedef struct 
{
    NJS_CNK_OBJECT*           pObject;
    int                       count;
    EVENT_TEXANIM_TINYDATA** ppTinyData;
}
EVENT_TEXANIM_CHUNKDATA;

typedef struct 
{
    int startid;
    int countid;
}
EVENT_TEXANIM_TEXIDS;

typedef struct 
{
    EVENT_TEXANIM_CHUNKDATA* pChunkData;
    EVENT_TEXANIM_TEXIDS*    pTexIds;
    int                     nbTexId;
}
EVENT_TEXANIM;

typedef struct 
{
    EVENT_TEXANIM_CHUNKDATA* pChunkData;
    int                      startid;
    int                      countid;
}
EVENT_TEXANIM_DC;

typedef struct
{
    NJS_CNK_OBJECT* pObject;
    NJS_MOTION*     pMotion;
    NJS_MOTION*     pShape;
    GJS_OBJECT*     pGjsObject;
    NJS_CNK_OBJECT* pShadowModel;
    void*           pUvScroll;
    NJS_POINT3      position;
    u32             attr;
    int             layer;
}
EVENT_ENTRY;

typedef struct
{
    NJS_CNK_OBJECT* object;
    NJS_MOTION*     motion;
    NJS_MOTION*     shape;
    void*           pUvScroll;
    NJS_POINT3      position;
    int             attr;
}
EVENT_ENTRY_DC;

typedef struct
{
    NJS_MOTION* motion;
    NJS_MOTION* shape;
}
EVENT_BIG_MOTION;

typedef struct
{
    NJS_CNK_OBJECT*   object;
    EVENT_BIG_MOTION* motions;
    int               nbScene;
    int Unknown;
}
EVENT_BIG;

typedef struct
{
    EVENT_ENTRY* pEntries;
    int          nbEntry;

    NJS_MOTION** pCameraMotions;
    int         nbCameraMotion;

    int* pPtclMotionIds;
    int  nbPtclMotionId;

    EVENT_BIG* pBig;

    int nbFrame;
}
EVENT_SCENE;

typedef struct
{
    EVENT_ENTRY_DC* pEntries;
    int             nbEntry;

    int* pCameraMotionIds;
    int  nbCameraMotionId;

    int* pPtclMotionIds;
    int  nbPtclMotionId;

    EVENT_BIG* pBig;

    int nbFrame;
}
EVENT_SCENE_DC;

typedef struct
{
    int         count;
    int         AlphaValues[32];
    NJS_VECTOR* ReflectionVtxs;
}
EVENT_REFLECTION;

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
    EVENT_SCENE*      pScenes;
    NJS_TEXLIST*      pTexlist;
    int               nbScene;
    Sint16*           pSpriteSizes;
    EVENT_REFLECTION* pReflections;
    NJS_CNK_OBJECT**  pBlareObjects;
    NJS_CNK_OBJECT*   pWalkerObjects;
    NJS_CNK_OBJECT*   pMilesObjects;
    EVENT_EQUIPMENT*  pEquipment;
    EVENT_TEXANIM*    pTexAnims;
    int               dropShadow;
}
EVENT_HEADER;

typedef struct
{
    u32 frame;
    u32 time;
}
EV_EFF_SUBTITLE;

typedef struct
{
    u32 frame;

    u8 snd_begin;
    u8 staff_ctrl;
    s16 voice_num;

    c7 bgm[16];
    c7 jingle[16];

    u32 WaitVsyncCount;

    s32 padding[7];
}
EV_EFF_SOUND;

enum
{
    EV_EFF_SCREEN_NONE,

    EV_EFF_SCREEN_COLOR,
    EV_EFF_SCREEN_COLOR2,
    EV_EFF_SCREEN_SPRITE_FADEIN,
    EV_EFF_SCREEN_SPRITE,
    EV_EFF_SCREEN_BACKCOLOR,
    EV_EFF_SCREEN_BACKCOLOR2,
};

typedef struct
{
    uint32_t frame;
    int8_t type;
    NJS_COLOR color;
    int16_t fadeout;
    uint16_t texID;
    uint32_t frametime;
    int16_t posX;
    int16_t posY;
    float width;
    float height;
    int padding[8];
}
EV_EFF_SCREEN;

typedef struct
{
    uint32_t frame;
    int8_t type;
    int8_t motionID;
    float texID;
    float pulsectrl;
    float unkF;
    float scl;
    int padding[8];
}
EV_EFF_SIMPLEPTCL;

typedef struct 
{
    uint32_t frame;
    int32_t fademode;
    NJS_VECTOR vec;
    float r;
    float g;
    float b;
    float ambi_inten;
    float ambi_r;
    float ambi_g;
    float ambi_b;
    int padding[5];
}
EV_EFF_LIGHT;

typedef struct 
{
    uint32_t frame;
    int32_t duration;
    uint8_t param1;
    uint8_t param2;
    uint8_t param3;
    uint8_t param4;
    uint8_t param5;
    uint8_t param6;
    uint32_t lifetime;
    int padding[11];
}
EV_EFF_BLARE;

typedef struct 
{
    NJS_POINT3 pos;
    NJS_VECTOR vec;
    uint16_t unk16_0;
    uint16_t unk16_1;
    uint16_t unk16_2;
    uint16_t unk16_3;
    uint32_t frame;
    NJS_VECTOR spread;
    int32_t count;
    int32_t unk32_0;
    int32_t type;
    int32_t unk32_1;
}
EV_EFF_PTCL;

typedef struct
{
    uint32_t frame;
    uint16_t posX;
    uint16_t posY;
    float depth;
    int8_t  type;
    int16_t texID;
    char fname[32];

    int padding[4];
}
EV_EFF_OVERLAY;

typedef struct
{
    EV_EFF_SUBTITLE     subtitle[256];
    EV_EFF_SOUND        sound[512];
    EV_EFF_SCREEN       screen[64];
    EV_EFF_SIMPLEPTCL   simpleptcl[2048];
    EV_EFF_LIGHT        lights[4][256];
    EV_EFF_BLARE        blares[64];
    EV_EFF_PTCL         ptcls[64];
    EV_EFF_OVERLAY      overlays[64];
}
EV_EFF_INFO;

typedef struct
{
    EVENT_SCENE_DC*   pScenes;
    NJS_TEXLIST*      pTexlist;
    int               nbScene;
    Sint16*           pSpriteSizes;
    EVENT_REFLECTION* pReflections;
    NJS_CNK_OBJECT*   pBlareObjects;
    NJS_CNK_OBJECT*   pWalkerObjects;
    NJS_CNK_OBJECT*   pMilesObjects;
    EVENT_EQUIPMENT*  pEquipment;
    EVENT_TEXANIM_DC* pTexAnims;
    int               dropShadow;
}
EVENT_HEADER_DC;

typedef struct 
{
    int enabled;
    int maxtimer;
    int maxdraw;
    int drawnum;
}
EV_BLARE_INFO;


enum
{
    EVENTMD_START,

    EVENTMD_UNK_1,

    EVENTMD_TIMECARD,
    EVENTMD_PLAY,
    EVENTMD_END,
    EVENTMD_RELEASE,

    EVENTMD_UNK_6,
    EVENTMD_UNK_7,
    EVENTMD_UNK_8,
};

#define EventData               DATA_REF(EVENT_HEADER, 0x0204FE20)
#define SceneData               DATA_REF(EVENT_SCENE*, 0x01DB0FD4)
#define EventFrame              DATA_REF(f32         , 0x01DB0EC0)
#define EventSceneFrame         DATA_REF(f32         , 0x01DB0FC4)
#define EventSceneNum           DATA_REF(int         , 0x01DB0FC8)
#define DisableCutscene         DATA_REF(bool        , 0x0174B007)
#define CutsceneMode            DATA_REF(int         , 0x01A283FC)
#define EventUseFlare           DATA_REF(int         , 0x01A298EC)
#define EventFlarePos           DATA_REF(NJS_POINT3  , 0x01A298E0)
#define EventActive             DATA_REF(bool        , 0x0174AFF9)
#define EventNum                DATA_REF(int         , 0x01A28AF4)

#define EventSpeed              DATA_REF(f32, 0x01DB0EAC)

#define EventLastFrame          DATA_REF(float, 0x01DB0FC0)

#define EventEffData            DATA_REF(EV_EFF_INFO , 0x01FEFE20)

#define EventBigScene           DATA_REF(s32         , 0x01DB0FBC)
#define EventBigFrame           DATA_REF(f32         , 0x01DB0F90)
#define EvBigActive             DATA_REF(b32         , 0x01DB0FD8)
#define EvBigLastScene          DATA_REF(s32         , 0x01DB0FDC)

#define EventCamera             DATA_REF(NJS_CAMERA  , 0x01D19C20)

#define EventBaseCamera         DATA_REF(NJS_CAMERA  , 0x01DB0E80)


#define EventReflectionListPos      DATA_ARY(NJS_POINT3, 0x01A28AF8, [32])
#define EventReflectionListNorm     DATA_ARY(NJS_VECTOR, 0x01A28C78, [32])

#define EvBlareInfo                 DATA_ARY(EV_BLARE_INFO, 0x01DB0100, [64])

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
