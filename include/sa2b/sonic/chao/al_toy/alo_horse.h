/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_toy/alo_horse.h'
*
*   Description:
*       Contains functions and data related to the horse
*   garden object.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_TOY_HORSE_H_
#define _SA2B_CHAO_TOY_HORSE_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task         task;

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    ALO_HorseCreate( const NJS_POINT3* pPos );

/** Internal task functions **/
void    ALO_Horse(task* tp);
void    ALO_HorseExecutor(task* tp);
void    ALO_HorseDisplayer(task* tp);
void    ALO_HorseDestructor(task* tp); // Same function as many other ALO objects

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define ALO_Horse_p              FUNC_PTR(void, __cdecl, (task*), 0x00580E80)
#   define ALO_HorseExecutor_p      FUNC_PTR(void, __cdecl, (task*), 0x00580BC0)
#   define ALO_HorseDisplayer_p     FUNC_PTR(void, __cdecl, (task*), 0x00580CA0)
#   define ALO_HorseDestructor_p    FUNC_PTR(void, __cdecl, (task*), 0x0057B9B0)

/** User-Function ptrs **/
#   define ALO_HorseCreate_p        ((void*)0x00580F30)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_TOY_HORSE_H_*/
