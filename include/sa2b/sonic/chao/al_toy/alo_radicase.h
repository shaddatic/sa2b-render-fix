/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_toy/alo_radicase.h'
*
*   Description:
*       Contains functions and data related to the radio
*   garden object.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_TOY_RADICASE_H_
#define _SA2B_CHAO_TOY_RADICASE_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     TASK;

/************************/
/*  Data                */
/************************/
#define ALO_RadicaseTaskPointer     DATA_REF(TASK*, 0x01AED2E0)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    ALO_RadicaseCreate( NJS_POINT3* pPos );

/** Internal task functions **/
void    ALO_RadicaseExecutor(   TASK* tp );
void    ALO_RadicaseDisplayer(  TASK* tp );
void    ALO_RadicaseDestructor( TASK* tp );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define ALO_RadicaseCreate_p         FUNC_PTR(void, __cdecl, (NJS_POINT3*), 0x0057CCA0)
#   define ALO_RadicaseExecutor_p       FUNC_PTR(void, __cdecl, (TASK*)      , 0x0057C840)
#   define ALO_RadicaseDisplayer_p      FUNC_PTR(void, __cdecl, (TASK*)      , 0x0057CA80)
#   define ALO_RadicaseDestructor_p     FUNC_PTR(void, __cdecl, (TASK*)      , 0x0057CC80)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_TOY_RADICASE_H_*/
