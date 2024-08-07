/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_misc.h'
*
*   Description:
*       Contains misc enums, structs, and functions related for
*   Chao World.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_MISC_H_
#define _SA2B_CHAO_MISC_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

#include <sa2b/sonic/set.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     TASK;
typedef struct cnkobj   NJS_CNK_OBJECT;

/************************/
/*  Enums               */
/************************/
enum
{
    CI_KIND_AL_CHAO = 0x81,
    CI_KIND_AL_CHAO_FIELD,
    CI_KIND_AL_FRUIT,
    CI_KIND_AL_FRUIT_FIELD,
    CI_KIND_AL_SEED,
    CI_KIND_AL_SEED_FIELD,
    CI_KIND_AL_MINIMAL,
    CI_KIND_AL_MINIMAL_FIELD,
    CI_KIND_AL_TREE,
    CI_KIND_AL_TREE_FIELD,
    CI_KIND_AL_TOY,
    CI_KIND_AL_TOY_FIELD,
    CI_KIND_AL_EGG,
    CI_KIND_AL_EGG_FIELD,
    CI_KIND_AL_TRASH,
    CI_KIND_AL_TRASH_FIELD,
    CI_KIND_AL_DAKKO_FIELD,
    CI_KIND_AL_NADE_FIELD,
    CI_KIND_AL_OBAKE_HEAD,
    CI_KIND_AL_CDR,
    CI_KIND_AL_PUNCH,
    CI_KIND_AL_SHADOW,
    CI_KIND_AL_ONARA,
    CI_KIND_AL_SOUND,
    CI_KIND_AL_HELLO,
    CI_KIND_AL_TOBIKOMI,
    CI_KIND_AL_REQUEST_WATER,
    CI_KIND_AL_NOISE,
    CI_KIND_AL_CONTACT,
    CI_KIND_AL_ACTION,
    CI_KIND_AL_SONG,
    CI_KIND_AL_BALL,
    CI_KIND_AL_FIRE,
    CI_KIND_AL_BIKKURI,
    CI_KIND_AL_BOX,
    CI_KIND_AL_WALL,
    CI_KIND_AL_RANDOM_MUSIC,
    CI_KIND_AL_DANCE,
    CI_KIND_AL_SING,
    CI_KIND_AL_SING_ONCHI,
    CI_KIND_AL_RAKUGAKI,
    CI_KIND_AL_FINISH,
    CI_KIND_AL_NEST,
    CI_KIND_AL_PLANT_POS,
    CI_KIND_AL_WATER,
    CI_KIND_AL_THIRSTY,
    CI_KIND_AL_TOUCH,
    CI_KIND_AL_SWITCH,
    CI_KIND_AL_CHANGE,
    CI_KIND_AL_SET_RACE_TREE,
    CI_KIND_AL_SET_RACE_GLIDE,
    CI_KIND_AL_SET_RACE_JUMP,
    CI_KIND_AL_SET_RACE_LAKE,
    CI_KIND_AL_SET_RACE_KARIMONO,
    CI_KIND_AL_SET_RACE_KOWAI,
    CI_KIND_AL_SET_RACE_GOAL,
    CI_KIND_AL_SET_RACE_ENABLE_TURN,
    CI_KIND_AL_SET_RACE_ALONG_LANE,
    CI_KIND_AL_SET_RACE_REMEMBER_POS,
    CI_KIND_AL_SET_RACE_THINK_POS,
    CI_KIND_AL_SET_RACE_PARALLEL,
    CI_KIND_AL_SET_RACE_GOAL_BANZAI,
    CI_KIND_AL_SET_RACE_PATHCOLLI,
    CI_KIND_AL_SET_RACE_POLYCOLLI,
    CI_KIND_AL_SET_RACE_EACHCOLLI,
    CI_KIND_AL_LOG,
    CI_KIND_AL_ROCK,
    CI_KIND_AL_HOLL,
    CI_KIND_AL_KANI,
    CI_KIND_AL_ANSWER_POS,
    CI_KIND_AL_ANSWER_OBJ,
    CI_KIND_AL_GOOD,
    CI_KIND_AL_TV,
    CI_KIND_AL_RADICASE,
    CI_KIND_AL_CLIMB,
    CI_KIND_AL_FURIMUKI,
    CI_KIND_AL_STAGE_CHANGER,
    CI_KIND_END = 0xFF,
};

/************************/
/*  Structures          */
/************************/
typedef struct
{
    uint16_t x, y, z;
}
SAngle3;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Calculate if position is on screen **/
b32     AL_IsOnScreen2(TASK* tp, f32 radius, f32 OffsetY);
b32     AL_IsOnScreen3(TASK* tp, f32 radius, f32 HalfHeight, f32 OffsetY);

/*
*   Description:
*     Loads '_s' & '_u' set files from one name. Internally calls 'LoadSetFileEx',
*   with 'objnum' argument set to '512'
*
*   Examples:
*     AL_LoadSetFile("set_chao_hero.bin");
*     AL_LoadSetFile("set_othr_name");
*
*   Parameters:
*     - set_name : name of the set files exluding '_s' & '_u'. Any extension is
*                  optional & trimmed away
*
*   Returns:
*     Loaded Set EditTable
*/
OBJ_EDITTABLE* AL_LoadSetFile( const char* set_name );

/** Clear CCL 'Search' and get task of first hit **/
TASK*   AL_IsHitKindWithNum(TASK* tp, int32_t info_num, uint8_t kind);

/** Interpolate 'p1' & 'p2' into 'pAnswer' at 'ratio' **/
void    AL_InterpolateAngle(Angle3* pAng1, Angle3* pAng2, Angle3* pAnswer, f32 ratio);
void    AL_InterpolateSAngle(SAngle3* pAng1, SAngle3* pAng2, SAngle3* pAnswer, f32 ratio);
void    AL_InterpolateObject(NJS_CNK_OBJECT* pObj1, NJS_CNK_OBJECT* pObj2, NJS_CNK_OBJECT* pAnswer, f32 ratio);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define AL_InterpolateObject_p       FUNC_PTR(void, __cdecl, (NJS_CNK_OBJECT*, NJS_CNK_OBJECT*, NJS_CNK_OBJECT*, f32), 0x0054AEB0)

/** User-Function ptrs **/
#   define AL_IsOnScreen3_p             ((void*)0x0054AC70)
#   define AL_LoadSetFile_p             ((void*)0x0054B190)
#   define AL_IsHitKindWithNum_p        ((void*)0x0054B1F0)
#   define AL_InterpolateAngle_p        ((void*)0x0054A770)
#   define AL_InterpolateSAngle_p       ((void*)0x0054A900)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_MISC_H_*/
