/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/alo_seed.h'
*
*   Contains enums, data, & functions related to Chao World seeds.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_SEED_H_
#define _SA2B_CHAO_SEED_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task             TASK;
typedef struct item_save_info   ITEM_SAVE_INFO;
typedef struct ccl_info         CCL_INFO;

/************************/
/*  Enums               */
/************************/
typedef enum /* Toolkit addition */
{
    SEED_MORIMORI = 0x00, // Strong
    SEED_PAKUPAKU = 0x01, // Tasty
    SEED_HERO = 0x02,
    SEED_DARK = 0x03,
    SEED_MARU = 0x04, // Round
    SEED_SANKAKU = 0x05, // Triangle
    SEED_SIKAKU = 0x06 // Square
}
eSEED_KIND;

/************************/
/*  Data                */
/************************/
/** Collision info **/
#define ALO_SeedColInfo     DataPtr(CCL_INFO, 0x008A73F8)

/************************/
/*  Functions           */
/************************/
EXTERN_START
TASK* ALO_SeedCreate(eSEED_KIND kind, NJS_POINT3* pPos, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo);

/** Task functions **/
void ALO_SeedExecutor(TASK* tp);
void ALO_SeedDisplayer(TASK* tp);
void ALO_SeedDestructor(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALO_SeedCreate_p        FuncPtr(TASK*, __cdecl, (eSEED_KIND kind, NJS_VECTOR* pPos, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo), 0x549B00)
#define ALO_SeedExecutor_p      FuncPtr(void , __cdecl, (TASK*), 0x549860)
#define ALO_SeedDisplayer_p     FuncPtr(void , __cdecl, (TASK*), 0x5498E0)
#define ALO_SeedDestructor_p    FuncPtr(void , __cdecl, (TASK*), 0x0057B9B0) // Same function as many other ALO objects

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_SEED_H_ */