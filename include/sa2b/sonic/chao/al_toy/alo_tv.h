/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_toy/alo_tv.h'
*
*   Description:
*       Contains functions and data related to the TV garden
*   object.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_TOY_TV_H_
#define _SA2B_CHAO_TOY_TV_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     task;

/************************/
/*  Data                */
/************************/
#define ALO_TVTaskPointer       DATA_REF(task*, 0x01AED288)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    ALO_TVCreate( const NJS_POINT3* pPos );

/** Internal task functions **/
void    ALO_TVExecutor(task* tp);
void    ALO_TVDisplayer(task* tp);
void    ALO_TVDestructor(task* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define ALO_TVCreate_p           FUNC_PTR(void, __cdecl, (const NJS_POINT3*), 0x0055CB90)
#   define ALO_TVExecutor_p         FUNC_PTR(void, __cdecl, (task*)            , 0x0055C540)
#   define ALO_TVDisplayer_p        FUNC_PTR(void, __cdecl, (task*)            , 0x0055C9E0)
#   define ALO_TVDestructor_p       FUNC_PTR(void, __cdecl, (task*)            , 0x0055CB70)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_TOY_TV_H_*/
