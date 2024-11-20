/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_behavior/albhv_life.h'
*
*   Description:
*       Contains functions related to the Chao life behaviors,
*   and Mayu task functions.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_ALBVH_LIFE_H_
#define _SA2B_CHAO_ALBVH_LIFE_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/sonic/chao/al_behavior.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t ALBHV_Mayu( task* tp );
int32_t ALBHV_Dead( task* tp );

/*
*   Mayu Functions
*/
void    CreateMayu( task* tp, char kind );

/** Task functions **/
void    MayuDisplayer( task* tp );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define MayuDisplayer_p      FUNC_PTR(void, __cdecl, (task*), 0x568A70)

/** Behavior ptrs **/
#   define ALBHV_Mayu_p         BHVFUNC_PTR(0x00568D30)
#   define ALBHV_Dead_p         BHVFUNC_PTR(0x00568F60)

/** User-Function ptrs **/
#   define CreateMayu_p         ((void*)0x00568CD0)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_ALBVH_LIFE_H_*/
