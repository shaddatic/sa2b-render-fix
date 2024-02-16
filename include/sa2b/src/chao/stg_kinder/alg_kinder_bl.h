/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/stg_kinder/alg_kinder.h'
*
*   Contains defines, typedefs, and functions for the Chao behavior system.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_KINDER_KINDER_H_
#define _SA2B_CHAO_KINDER_KINDER_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/src/chao/al_itemshop.h>

/************************/
/*  Data                */
/************************/
#define gAlItemBuyList              DataAry(SAlItem, 0x01DBEDC0, [15])
#define gAlItemBuyNum               DataRef(int32_t, 0x01DBEDC0)

#define NextBuyListChangeTime       DataRef(int32_t, 0x01DBED8C)

#endif /* _SA2B_CHAO_KINDER_KINDER_H_ */
