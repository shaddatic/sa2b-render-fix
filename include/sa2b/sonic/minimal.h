/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/minimal.h'
*
*   ~~ Under Construction ~~
* 
*   Description:
*       Header for collectable Minimals in the main game.
*
*   Contributors:
*       SEGA - Sonic Team,
*       Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_MINIMAL_H_
#define _SA2B_MINIMAL_H_

/************************/
/*  Includes            */
/************************/
/** Colli Info **/
#include <sa2b/sonic/c_colli/ccl_info.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task         TASK;

/************************/
/*  Structs             */
/************************/
#define GET_MINIMALWK(_tp)  ((MINIMALWK*)(_tp)->awp)

typedef struct
{
    char gap[32];
}
MINIMALWK;

/************************/
/*  Data                */
/************************/
/** Collision info **/
#define colli_info_minimal      DATA_ARY(0x008AC728, CCL_INFO, [1])

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Base creator **/
TASK*   Minimal_Create(f32 posX, f32 posY, f32 posZ, int32_t num, uint32_t flag);

/** Create random minimal **/
TASK*   Minimal_Random(f32 posX, f32 posY, f32 posZ);

/** Create minimal from enemy **/
void    Minimal_Enemy(f32 posX, f32 posY, f32 posZ);

/** Jump from object/box and follow player **/
TASK*   Minimal_JumpOut(int32_t num, f32 posX, f32 posY, f32 posZ);

/*
*   Internal functions
*/
TASK*   MinimalCaptureEffect_Create(NJS_POINT3* pos);

/*
*   Task functions
*/
void    Minimal_Exec(TASK* tp);
void    Minimal_Disp(TASK* tp);
void    Minimal_DispSort(TASK* tp);
void    Minimal_Dest(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define Minimal_Create_p                 FUNC_PTR(TASK*, __cdecl, (f32, f32, f32, int32_t, uint32_t), 0x0048AAD0)
#   define Minimal_Random_p                 FUNC_PTR(TASK*, __cdecl, (f32, f32, f32)                   , 0x0048AD10)
#   define Minimal_Enemy_p                  FUNC_PTR(void , __cdecl, (f32, f32, f32)                   , 0x0048ADA0)
#   define Minimal_Exec_p                   FUNC_PTR(void , __cdecl, (TASK*)                           , 0x004898B0)
#   define Minimal_Disp_p                   FUNC_PTR(void , __cdecl, (TASK*)                           , 0x0048A390)
#   define Minimal_DispSort_p               FUNC_PTR(void , __cdecl, (TASK*)                           , 0x0048A4F0)
#   define Minimal_Dest_p                   FUNC_PTR(void , __cdecl, (TASK*)                           , 0x0048A6B0)

/** User-Function ptrs **/
#   define Minimal_JumpOut_p                ((void*)0x0048AC30)
#   define MinimalCaptureEffect_Create_p    ((void*)0x00489680)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_MINIMAL_H_*/
