/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_path.h'
*
*   Contains data and functions related to Chao race paths.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
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
#define CurrPathNum         DataRef(int32_t, 0x01A5D13C)

#define PathMotionList      DataAry(NJS_MOTION*, 0x01353278, [10])
#define PathMKeyList        DataAry(NJS_MKEY_F*, 0x013532A0, [10][2])

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t  AL_PathSearch(TASK* tp);

void    CrossProduct(NJS_POINT3* pPos0, NJS_POINT3* pPos1, NJS_POINT3* pPos2, NJS_POINT3* pAnswer);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define AL_PathSearch_p     FuncPtr(int32_t, __cdecl, (TASK* tp), 0x0053E3E0)

/** User-Function ptrs **/
EXTERN const void* const CrossProduct_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_PARTS_H_ */
