/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/chao/stg_kinder/alg_kinder.h'
*
*   ~~~ Under Construction ~~~
*
*   Description:
*     Chao Kindergarten
*/
#ifndef _SA2B_CHAO_KINDER_KINDER_H_
#define _SA2B_CHAO_KINDER_KINDER_H_

/************************/
/*  Includes            */
/************************/
#include <samt/sonic/chao/al_itemshop.h>

/************************/
/*  Data                */
/************************/
#define gAlItemBuyList              DATA_ARY(SAlItem, 0x01DBEDC0, [15])
#define gAlItemBuyNum               DATA_REF(int32_t, 0x01DBEDC0)

#define NextBuyListChangeTime       DATA_REF(int32_t, 0x01DBED8C)

#endif/*_SA2B_CHAO_KINDER_KINDER_H_*/
