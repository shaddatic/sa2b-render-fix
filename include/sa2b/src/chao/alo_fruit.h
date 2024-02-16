/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/alo_fruit.h'
*
*   Contains enums and functions related to Chao World fruits.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_FRUIT_H_
#define _SA2B_CHAO_FRUIT_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task             TASK;
typedef struct item_save_info   ITEM_SAVE_INFO;

/************************/
/*  Enums               */
/************************/
typedef enum
{
    FRUIT_NEUT_LOCAL,
    FRUIT_HERO_LOCAL,
    FRUIT_DARK_LOCAL,
    FRUIT_MORIMORI,
    FRUIT_PAKUPAKU,
    FRUIT_HERO,
    FRUIT_DARK,
    FRUIT_MARU,
    FRUIT_SANKAKU,
    FRUIT_SIKAKU,
    FRUIT_HEART,
    FRUIT_CHAO,
    FRUIT_ORIKOU,
    FRUIT_GBA_A,
    FRUIT_GBA_B,
    FRUIT_GBA_C,
    FRUIT_GBA_D,
    FRUIT_GBA_E,
    FRUIT_GBA_F,
    FRUIT_GBA_G,
    FRUIT_KINOKO_A,
    FRUIT_KINOKO_B,
    FRUIT_MINTCANDY,
    FRUIT_GRAPE,
    FRUIT_DX_DEFAULT,
    FRUIT_END,
}
eFRUIT_KIND;

/************************/
/*  Functions           */
/************************/
EXTERN_START
TASK*   ALO_FruitCreate(eFRUIT_KIND kind, NJS_POINT3* pPos, int32_t AngY, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo);

/** Task functions **/
void    ALO_FruitExecutor(TASK* tp);
void    ALO_FruitDisplayer(TASK* tp);
void    ALO_FruitDestructor(TASK* tp); /* Same destructor as many other Chao objects */

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALO_FruitCreate_p           FuncPtr(TASK*, __cdecl, (eFRUIT_KIND, NJS_POINT3*, int32_t, NJS_VECTOR*, ITEM_SAVE_INFO*), 0x00546180)
#define ALO_FruitExecutor_p         FuncPtr(void , __cdecl, (TASK*)                                                         , 0x00545E40)
#define ALO_FruitDisplayer_p        FuncPtr(void , __cdecl, (TASK*)                                                         , 0x00545EE0)
#define ALO_FruitDestructor_p       FuncPtr(void , __cdecl, (TASK*)                                                         , 0x0057B9B0)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_FRUIT_H_ */
