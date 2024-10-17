/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_parts.h'
*
*   Description:
*       Contains enums, data, and functions related to Chao
*   parts.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_PARTS_H_
#define _SA2B_CHAO_PARTS_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task         task;
typedef struct cnkobj       NJS_CNK_OBJECT;
typedef struct al_object    AL_OBJECT;

/************************/
/*  Enums               */
/************************/
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

enum
{
    PARTS_KIND_ARM = 0x0,
    PARTS_KIND_EAR = 0x1,
    PARTS_KIND_FOREHEAD = 0x2,
    PARTS_KIND_HORN = 0x3,
    PARTS_KIND_REG = 0x4,
    PARTS_KIND_TAIL = 0x5,
    PARTS_KIND_WING = 0x6,
    PARTS_KIND_TONGUE = 0x7,
    NB_PARTS_KIND = 0x8,
};

/************************/
/*  Structures          */
/************************/
typedef struct
{
    NJS_CNK_OBJECT* pObject;
    NJS_TEXLIST*    pTexlist;
    NJS_POINT3      OffsetPos;
    Angle3          OffsetAng;
}
AL_ITEM_INFO;

/************************/
/*  Data                */
/************************/
#define PartsObjectTreeNumber   DATA_ARY(int32_t          , 0x012F59A8, [8][2])
#define PartsObjectListNumber   DATA_ARY(int32_t          , 0x012F59E8, [8][2])

#define pPartsObjectListChild   DATA_ARY(NJS_CNK_OBJECT**, 0x012E59A0, [20])
#define pPartsObjectListAdult   DATA_ARY(NJS_CNK_OBJECT**, 0x012E5938, [20])

#define AL_PartAttr             DATA_ARY(int16_t          , 0x011C47D0, [40])

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Place an item/object, like a toy, onto a part of the Chao **/
void    AL_SetItem(task* tp, int32_t TreeNum, NJS_CNK_OBJECT* pObject);
void    AL_SetItemOffset(task* tp, int32_t TreeNum, AL_ITEM_INFO* pInfo);

/** Clear items **/
void    AL_RemoveItemAll(task* tp);

/** Set minimal part **/
void    AL_SetMiminalParts(task* tp, int32_t PartsKind, int32_t MinimalType);
/** Clear minimal parts **/
void    AL_ClearParts(task* tp);

/** Internal functions **/
void    AL_RemoveItemAllSub(AL_OBJECT* pObject);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define AL_RemoveItemAllSub_p        FUNC_PTR(void, __cdecl, (AL_OBJECT *pObject), 0x00566AF0)

/** User-Function ptrs **/
#   define AL_SetItem_p                 ((void*)0x005669B0)
#   define AL_SetItemOffset_p           ((void*)0x00566A20)
#   define AL_SetMiminalParts_p         ((void*)0x005668B0)
#   define AL_ClearParts_p              ((void*)0x00566850)

#endif /* SAMT_INCL_FUNCPTRS */

#endif /* _SA2B_CHAO_PARTS_H_ */
