/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/alo_seed.h'
*
*   Description:
*       Contains enums, data, & functions related to Chao World
*   seeds.
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
/** Ninja **/
#include <sa2b/ninja/njcommon.h>

/** Colli Info **/
#include <sa2b/src/c_colli/ccl_info.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task             TASK;
typedef struct item_save_info   ITEM_SAVE_INFO;

/************************/
/*  Enums               */
/************************/
typedef enum /* Toolkit addition */
{
    SEED_MORIMORI,  // Strong
    SEED_PAKUPAKU,  // Tasty
    SEED_HERO,      // Hero
    SEED_DARK,      // Dark
    SEED_MARU,      // Round
    SEED_SANKAKU,   // Triangle
    SEED_SIKAKU,    // Square
    NB_SEED_KIND
}
eSEED_KIND;

/************************/
/*  Data                */
/************************/
/** Collision info **/
#define ALO_SeedColInfo     DataAry(CCL_INFO, 0x008A73F8, [1])

/************************/
/*  Functions           */
/************************/
EXTERN_START
TASK*   ALO_SeedCreate(eSEED_KIND kind, NJS_POINT3* pPos, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo);

/** Task functions **/
void    ALO_SeedExecutor(TASK* tp);
void    ALO_SeedDisplayer(TASK* tp);
void    ALO_SeedDestructor(TASK* tp); // Same function as many other ALO objects

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALO_SeedCreate_p        FuncPtr(TASK*, __cdecl, (eSEED_KIND, NJS_POINT3*, NJS_VECTOR*, ITEM_SAVE_INFO*), 0x00549B00)
#define ALO_SeedExecutor_p      FuncPtr(void , __cdecl, (TASK*)                                                , 0x00549860)
#define ALO_SeedDisplayer_p     FuncPtr(void , __cdecl, (TASK*)                                                , 0x005498E0)
#define ALO_SeedDestructor_p    FuncPtr(void , __cdecl, (TASK*)                                                , 0x0057B9B0) 

#endif/*SAMT_INCLUDE_FUNC_PTRS*/

#endif/*_SA2B_CHAO_SEED_H_*/
