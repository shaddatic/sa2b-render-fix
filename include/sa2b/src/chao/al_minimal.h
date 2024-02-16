/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_material.h'
*
*   Contains structs, data, and functions related to Chao landmarks.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_MINIMAL_H_
#define _SA2B_CHAO_MINIMAL_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>
#include <sa2b/src/motion.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task             TASK;
typedef struct item_save_info   ITEM_SAVE_INFO;
typedef struct colliwk          COLLIWK;

/************************/
/*  Enums                */
/************************/
typedef enum
{
    eMinimalType_Pen,       // Penguin
    eMinimalType_Goma,      // Seal
    eMinimalType_Rako,      // Otter
    eMinimalType_Usa,       // Rabbit
    eMinimalType_Chit,      // Cheetah
    eMinimalType_Ino,       // Warthog
    eMinimalType_Kuma,      // Bear
    eMinimalType_Tora,      // Tiger
    eMinimalType_Gori,      // Gorilla
    eMinimalType_Kuja,      // Peacock
    eMinimalType_Oum,       // Parrot
    eMinimalType_Kon,       // Condor
    eMinimalType_Ska,       // Skunk
    eMinimalType_Shep,      // Sheep
    eMinimalType_Ara,       // Raccoon
    eMinimalType_Han,       // Half Fish
    eMinimalType_Bone,      // Skeleton Dog
    eMinimalType_Batman,    // Batman
    eMinimalType_Dra,       // Dragon
    eMinimalType_Uni,       // Unicorn
    eMinimalType_Phen,      // Phoenix
    eMinimalType__end,
}
EMinimalType;

enum
{
    FLICKY_GOMA = 0x0,    // Seal
    FLICKY_PENG = 0x1,    // Penguin
    FLICKY_RAKO = 0x2,    // Otter
    FLICKY_PEAC = 0x3,    // Peacock
    FLICKY_SWAL = 0x4,    // Swallow
    FLICKY_PARR = 0x5,    // Parrot
    FLICKY_DEER = 0x6,    // Deer
    FLICKY_BANY = 0x7,    // Bunny
    FLICKY_WARA = 0x8,    // Kangaroo
    FLICKY_GORI = 0x9,    // Gorilla
    FLICKY_LION = 0xA,    // Lion
    FLICKY_ELEP = 0xB,    // Elephant
    FLICKY_MOGU = 0xC,    // Mole
    FLICKY_KOAL = 0xD,    // Koala
    FLICKY_SKUN = 0xE,    // Skunk
    FLICKY_MAX = 0xF,
};

enum
{
    MINI_MTN_WAIT = 0x0,
    MINI_MTN_WALK = 0x1,
    MINI_MTN_HUG = 0x2,
    MINI_MTN_FLY = 0x3,
};

/************************/
/*  Structures          */
/************************/
#define GET_MINIMAL_WORK(tp) ((MINIMAL_WORK*)tp->twp)

typedef struct // TASKWK
{
    int8_t       mode;
    int8_t       smode;
    int8_t       id;
    int8_t       btimer;
    int16_t      flag;
    int16_t      wtimer;
    Angle3       ang;
    NJS_POINT3   pos;
    NJS_POINT3   scl;
    COLLIWK*     cwp;
    float32_t    spd;
    int32_t      RangeOutTimer;
    MOTION_CTRL  MtnCtrl;
    MOTION_TABLE MtnTable[4];
    int32_t      CaptureFlag;
}
MINIMAL_WORK;

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    AL_CreateMinimalCreateManager(void);

TASK*   AL_MinimalCreate(int8_t num, NJS_POINT3* pPos, Angle AngY, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo);

void    AL_MinimalExecutor(TASK* tp);
void    AL_MinimalDisplayer(TASK* tp);
void    AL_MinimalDestructor(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define AL_CreateMinimalCreateManager_p     FuncPtr(void , __cdecl, (void)                                                    , 0x00549490)
#define AL_MinimalCreate_p                  FuncPtr(TASK*, __cdecl, (int8_t, NJS_POINT3*, Angle, NJS_VECTOR*, ITEM_SAVE_INFO*), 0x00548D30)
#define AL_MinimalExecutor_p                FuncPtr(void , __cdecl, (TASK*)                                                   , 0x00548C50)
#define AL_MinimalDisplayer_p               FuncPtr(void , __cdecl, (TASK*)                                                   , 0x005489D0)
#define AL_MinimalDestructor_p              FuncPtr(void , __cdecl, (TASK*)                                                   , 0x00548C30)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_MINIMAL_H_ */
