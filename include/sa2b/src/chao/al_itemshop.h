#pragma once

struct SAlItem;

const struct SAlItemInfo
{
	sint32 mPriceBuy;
	sint32 mPriceSell;
	sint16 mEmblem;
	sint16 mName;
	sint16 mExpl;
};

struct SAlItemTable
{
	const SAlItemInfo* mList;
	int mLen;
};

struct SAlItemTableTable
{
	const SAlItemTable* mList;
	int mLen;
};

DataAry(SAlItemInfo, kAlItemInfo_CtgEgg,	0x008A7B68, [69]);
DataAry(SAlItemInfo, kAlItemInfo_CtgFruit,	0x008A8028, [24]);
DataAry(SAlItemInfo, kAlItemInfo_CtgSeed,	0x008A7FB8, [7]);
DataAry(SAlItemInfo, kAlItemInfo_CtgMask,	0x008A81A8, [85]);
DataAry(SAlItemInfo, kAlItemInfo_CtgMenu,	0x008A86F8, [3]);

DataRef(SAlItemTable, kAlItemCtg, 0x008A8728);

DataRef(SAlItemTableTable, kAlItemAll, 0x008A87B0);

FuncPtr(SAlItemInfo*, __thiscall, AlItemGetInfo, (const SAlItem* item), 0x00534150);