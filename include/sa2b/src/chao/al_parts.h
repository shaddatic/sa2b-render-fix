#pragma once

/*
*	Abstracted Types
*/

typedef struct task		task;
typedef struct cnkobj	NJS_CNK_OBJECT;

/*
*	Enums
*/

enum
{
	AL_PART_ROOT = 0x0,
	AL_PART_BODY = 0x1,
	AL_PART_ARM_L_POS = 0x2,
	AL_PART_ARM_L = 0x3,
	AL_PART_HAND_L = 0x4,
	AL_PART_REG_L_POS = 0x5,
	AL_PART_REG_L = 0x6,
	AL_PART_TAIL_POS = 0x7,
	AL_PART_TAIL = 0x8,
	AL_PART_ARM_R_POS = 0x9,
	AL_PART_ARM_R = 0xA,
	AL_PART_HAND_R = 0xB,
	AL_PART_REG_R_POS = 0xC,
	AL_PART_REG_R = 0xD,
	AL_PART_NECK = 0xE,
	AL_PART_HEAD_POS = 0xF,
	AL_PART_HEAD = 0x10,
	AL_PART_EYE_L_POS = 0x11,
	AL_PART_EYE_L = 0x12,
	AL_PART_EYELID_L = 0x13,
	AL_PART_EYE_R_POS = 0x14,
	AL_PART_EYE_R = 0x15,
	AL_PART_EYELID_R = 0x16,
	AL_PART_FEELER_L = 0x17,
	AL_PART_EAR_L = 0x18,
	AL_PART_FEELER_R = 0x19,
	AL_PART_EAR_R = 0x1A,
	AL_PART_MOUTH = 0x1B,
	AL_PART_TONGUE_POS = 0x1C,
	AL_PART_FOREHEAD = 0x1D,
	AL_PART_HORN_L = 0x1E,
	AL_PART_HORN_R = 0x1F,
	AL_PART_OFFICE_POS = 0x20,
	AL_PART_OFFICE = 0x21,
	AL_PART_BACK = 0x22,
	AL_PART_NAVEL = 0x23,
	AL_PART_WING_L_POS = 0x24,
	AL_PART_WING_L = 0x25,
	AL_PART_WING_R_POS = 0x26,
	AL_PART_WING_R = 0x27,
	AL_PART_END = 0x28,
};

/*
*	Data Arrays
*/

DataAry(sint32, PartsObjectTreeNumber, 0x012F59A8, [8][2]);
DataAry(sint32, PartsObjectListNumber, 0x012F59E8, [8][2]);

DataAry(NJS_CNK_OBJECT**, pPartsObjectListChild, 0x012E59A0, [20]);
DataAry(NJS_CNK_OBJECT**, pPartsObjectListAdult, 0x012E5938, [20]);

DataAry(sint16, AL_PartAttr, 0x011C47D0, [40]);

/*
*	User Functions
*/

void AL_SetItem(task* tp, sint32 TreeNum, NJS_CNK_OBJECT* pObject);

void AL_ClearParts(task* tp);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* AL_SetItem_p;

extern const void* AL_ClearParts_p;

#endif