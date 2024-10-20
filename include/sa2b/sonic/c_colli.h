/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/c_colli.h'
*
*   Description:
*       Contains structs, enums, and functions related to the
*   game's core collision engine.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CCOLLI_H_
#define _SA2B_CCOLLI_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/sonic/c_colli/ccl_info.h>

/************************/
/*  Abstracted Types    */
/************************/
typedef struct task         task;
typedef struct taskwk       taskwk;

/************************/
/*  Enums               */
/************************/
enum
{
    CI_KIND_OSAMPO          = 0x1,
    CI_KIND_PATTING_HAND,
    CI_KIND_SAPLING,
    CI_KIND_SAPLING_FIELD,
    CI_KIND_KAME_FIELD,
    CI_KIND_ENEMYBALL,
    CI_KIND_PUNCH,
    CI_KIND_2PLASER,
    CI_KIND_2PSHOTS,
    CI_KIND_2PMISSILES,
    CI_KIND_NO_RIDE,
    CI_KIND_NO_PUNCH,
    CI_KIND_NO_LOCKON,
    CI_KIND_NO_CATCH,
    CI_KIND_DO_CATCH,
    CI_KIND_NO_COLLIDE,
    CI_KIND_G_CYLINDER,
    CI_KIND_NO_HOLD_FIELD,
    CI_KIND_BOMB_EXPLOSION,
    CI_KIND_CHAOSDRIVE,
    CI_KIND_DUMMY           = 0x40,
};

enum
{
    CI_FORM_SPHERE,
    CI_FORM_CYLINDER,
    CI_FORM_CYLINDER2,
    CI_FORM_RECTANGLE,
    CI_FORM_RECTANGLE2,
    CI_FORM_RECTANGLE3,
    CI_FORM_CAPSULE,
    CI_FORM_PERSON,
    CI_FORM_LINE,
    CI_FORM_WALL_PLANE,
    CI_FORM_WALL_CIRCLE
};

enum
{
    CID_PLAYER,
    CID_BULLET,
    CID_ENEMY,
    CID_ENEMY2,
    CID_OBJECT,
    CID_OBJECT2,
    CID_ITEM,
    CID_ITEM2,
    CID_WALL,
    CID_CHAO,
};

/************************/
/*  Structures          */
/************************/
typedef struct
{
    task*   pTask;
    void*   FuncAddr;
    int32_t CurrNum;
    int32_t Kind;
}
CCL_SEARCH;

typedef struct c_colli_hit_info
{
    int8_t   my_num;
    int8_t   hit_num;
    uint16_t flag;
    task*    hit_tp;
}
CCL_HIT_INFO;

typedef struct colliwk
{
    uint16_t        id;
    int16_t         nbHit;
    uint16_t        flag;
    uint16_t        nbInfo;
    f32             colli_range;
    CCL_INFO*       info;
    CCL_HIT_INFO    hit_info[16];
    NJS_POINT3      normal;
    task*           mytask;
    int16_t         my_num;
    int16_t         hit_num;
    struct colliwk* hit_cwp;
}
COLLIWK;

/************************/
/*  Data                */
/************************/
#define Search      DATA_REF(CCL_SEARCH, 0x019468A0)

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t       CCL_Init(  task* tp, CCL_INFO* info, int32_t nbInfo, uint8_t id );
void          CCL_Entry( task* tp );

task*         CCL_IsHitKind( task* tp, uint8_t kind );

b32           CCL_IsPushed( taskwk* twp );

CCL_HIT_INFO* CCL_IsHitKindEx( task* tp, uint8_t kind );

void          CCL_ClearSearch( void );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define CCL_IsHitKindEx_p       FUNC_PTR(CCL_HIT_INFO*, __cdecl, (task*, uint8_t), 0x00486760)

/** User-Function ptrs **/
#   define CCL_Init_p              ((void*)0x0047E520)
#   define CCL_Entry_p             ((void*)0x0047E750)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CCOLLI_H_*/
