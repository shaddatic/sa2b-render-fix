/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_path.h'
*
*   Description:
*       Contains data and functions related to Chao race paths.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_PARTS_H_
#define _SA2B_CHAO_PARTS_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/ninja.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task        TASK;

/************************/
/*  Data                */
/************************/
#define CurrPathNum         DATA_REF(int32_t, 0x01A5D13C)

#define PathMotionList      DATA_ARY(NJS_MOTION*, 0x01353278, [10])
#define PathMKeyList        DATA_ARY(NJS_MKEY_F*, 0x013532A0, [10][2])

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t AL_PathSearch(TASK* tp);

void    CrossProduct(NJS_POINT3* pPos0, NJS_POINT3* pPos1, NJS_POINT3* pPos2, NJS_POINT3* pAnswer);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define AL_PathSearch_p      FUNC_PTR(int32_t, __cdecl, (TASK* tp), 0x0053E3E0)

/** User-Function ptrs **/
#   define CrossProduct_p       ((void*)0x0053E390)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_PARTS_H_*/
