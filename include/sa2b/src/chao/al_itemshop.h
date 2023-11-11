/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_itemshop.h'
*
*   Contains structs, data, and functions related to Chao blackmarket items.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_ITEMSHOP_H_
#define _SA2B_CHAO_ITEMSHOP_H_

/************************/
/*  Structures          */
/************************/
typedef struct
{
    sint8 mCategory;
    sint8 mId;
}
SAlItem;

typedef struct
{
    sint32 mPriceBuy;
    sint32 mPriceSell;
    sint16 mEmblem;
    sint16 mName;
    sint16 mExpl;
}
SAlItemInfo;

typedef struct
{
    SAlItemInfo* mList;
    sint32 mLen;
}
SAlItemTable;

typedef struct
{
    SAlItemTable* mList;
    sint32 mLen;
}
SAlItemTableTable;

/************************/
/*  Data                */
/************************/
#define kAlItemInfo_CtgEgg      DataAry(SAlItemInfo      , 0x008A7B68, [69])
#define kAlItemInfo_CtgFrui     DataAry(SAlItemInfo      , 0x008A8028, [24])
#define kAlItemInfo_CtgSeed     DataAry(SAlItemInfo      , 0x008A7FB8, [7])
#define kAlItemInfo_CtgMask     DataAry(SAlItemInfo      , 0x008A81A8, [85])
#define kAlItemInfo_CtgMenu     DataAry(SAlItemInfo      , 0x008A86F8, [3])

#define kAlItemCtg              DataRef(SAlItemTable     , 0x008A8728)

#define kAlItemAll              DataRef(SAlItemTableTable, 0x008A87B0)

/************************/
/*  Functions           */
/************************/
EXTERN_START
const SAlItemInfo*   AlItemGetInfo(const SAlItem* item);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define AlItemGetInfo_p         FuncPtr(const SAlItemInfo*, __fastcall, (const SAlItem* item), 0x00534150)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_ITEMSHOP_H_ */