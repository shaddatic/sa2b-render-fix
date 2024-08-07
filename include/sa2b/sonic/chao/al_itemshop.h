/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_itemshop.h'
*
*   Description:
*       Contains structs, data, and functions related to Chao
*   blackmarket items.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_ITEMSHOP_H_
#define _SA2B_CHAO_ITEMSHOP_H_

/************************/
/*  Structures          */
/************************/
typedef struct
{
    int8_t mCategory;
    int8_t mId;
}
SAlItem;

typedef struct
{
    int32_t mPriceBuy;
    int32_t mPriceSell;
    int16_t mEmblem;
    int16_t mName;
    int16_t mExpl;
}
SAlItemInfo;

typedef struct
{
    SAlItemInfo* mList;
    int32_t      mLen;
}
SAlItemTable;

typedef struct
{
    SAlItemTable* mList;
    int32_t       mLen;
}
SAlItemTableTable;

/************************/
/*  Data                */
/************************/
#define kAlItemInfo_CtgEgg      DATA_ARY(SAlItemInfo      , 0x008A7B68, [69])
#define kAlItemInfo_CtgFrui     DATA_ARY(SAlItemInfo      , 0x008A8028, [24])
#define kAlItemInfo_CtgSeed     DATA_ARY(SAlItemInfo      , 0x008A7FB8, [7])
#define kAlItemInfo_CtgMask     DATA_ARY(SAlItemInfo      , 0x008A81A8, [85])
#define kAlItemInfo_CtgMenu     DATA_ARY(SAlItemInfo      , 0x008A86F8, [3])

#define kAlItemCtg              DATA_REF(SAlItemTable     , 0x008A8728)

#define kAlItemAll              DATA_REF(SAlItemTableTable, 0x008A87B0)

/************************/
/*  Functions           */
/************************/
EXTERN_START
const SAlItemInfo*   AlItemGetInfo(const SAlItem* item);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define AlItemGetInfo_p          FUNC_PTR(const SAlItemInfo*, __fastcall, (const SAlItem* item), 0x00534150)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_ITEMSHOP_H_*/
