/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/alo_seed.h'
*
*   Description:
*       Contains enums, data, & functions related to Chao World
*   seeds.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_SEED_H_
#define _SA2B_CHAO_SEED_H_

/************************/
/*  Includes            */
/************************/
/** Ninja **/
#include <sa2b/ninja/njcommon.h>

/** Colli Info **/
#include <sa2b/sonic/c_colli/ccl_info.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task             task;
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
#define ALO_SeedColInfo     DATA_ARY(CCL_INFO, 0x008A73F8, [1])

/************************/
/*  Functions           */
/************************/
EXTERN_START
task*   ALO_SeedCreate(eSEED_KIND kind, NJS_POINT3* pPos, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo);

/** Task functions **/
void    ALO_SeedExecutor(task* tp);
void    ALO_SeedDisplayer(task* tp);
void    ALO_SeedDestructor(task* tp); // Same function as many other ALO objects

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define ALO_SeedCreate_p         FUNC_PTR(task*, __cdecl, (eSEED_KIND, NJS_POINT3*, NJS_VECTOR*, ITEM_SAVE_INFO*), 0x00549B00)
#   define ALO_SeedExecutor_p       FUNC_PTR(void , __cdecl, (task*)                                                , 0x00549860)
#   define ALO_SeedDisplayer_p      FUNC_PTR(void , __cdecl, (task*)                                                , 0x005498E0)
#   define ALO_SeedDestructor_p     FUNC_PTR(void , __cdecl, (task*)                                                , 0x0057B9B0) 

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_SEED_H_*/
