#pragma once

struct task;
struct ITEM_SAVE_INFO;

struct CCL_INFO;

enum eSEED_KIND : sint32	// Non-standard, enum created through context not official symbols
{
	SEED_MORIMORI = 0x00, // Strong
	SEED_PAKUPAKU = 0x01, // Tasty
	SEED_HERO = 0x02,
	SEED_DARK = 0x03,
	SEED_MARU = 0x04, // Round
	SEED_SANKAKU = 0x05, // Triangle
	SEED_SIKAKU = 0x06 // Square
};

TaskFuncPtr(ALO_SeedExecutor, 0x549860);
TaskFuncPtr(ALO_SeedDisplayer, 0x5498E0);
TaskFuncPtr(ALO_SeedDestructor, 0x0057B9B0); // Same function as many other ALO objects

FuncPtr(task*, __cdecl, ALO_SeedCreate, (eSEED_KIND kind, NJS_VECTOR* pPos, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo), 0x549B00);

DataRef(CCL_INFO, ALO_SeedColInfo, 0x008A73F8);