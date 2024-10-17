/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/alo_fruit.h'
*
*   Description:
*       Contains enums and functions related to Chao World fruits.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
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
typedef struct task             task;
typedef struct item_save_info   ITEM_SAVE_INFO;
typedef struct cnkobj           NJS_CNK_OBJECT;

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
#if 0
    FRUIT_DX_DEFAULT,
#endif
    FRUIT_END,
}
eFRUIT_KIND;

/************************/
/*  Game Data           */
/************************/
#define FruitObjectList             DATA_ARY(NJS_CNK_OBJECT*, 0x013340C8, [24])
#define SmallFruitObjectList        DATA_ARY(NJS_CNK_OBJECT*, 0x01334128, [24])

/************************/
/*  Functions           */
/************************/
EXTERN_START
task*   ALO_FruitCreate( eFRUIT_KIND kind, NJS_POINT3* pPos, int32_t AngY, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo );

/** Task functions **/
void    ALO_FruitExecutor(   task* tp );
void    ALO_FruitDisplayer(  task* tp );
void    ALO_FruitDestructor( task* tp ); /* Same destructor as many other Chao objects */

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define ALO_FruitCreate_p            FUNC_PTR(task*, __cdecl, (eFRUIT_KIND, NJS_POINT3*, int32_t, NJS_VECTOR*, ITEM_SAVE_INFO*), 0x00546180)
#   define ALO_FruitExecutor_p          FUNC_PTR(void , __cdecl, (task*)                                                          , 0x00545E40)
#   define ALO_FruitDisplayer_p         FUNC_PTR(void , __cdecl, (task*)                                                          , 0x00545EE0)
#   define ALO_FruitDestructor_p        FUNC_PTR(void , __cdecl, (task*)                                                          , 0x0057B9B0)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_FRUIT_H_*/
