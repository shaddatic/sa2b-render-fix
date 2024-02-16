/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_landmark.h'
*
*   Contains structs, data, and functions related to Chao landmarks.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_LANDMARK_H_
#define _SA2B_CHAO_LANDMARK_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Enums               */
/************************/
typedef enum
{
    LMA_NONE = 0x0,
    LMA_GROUND1 = 0x1,
    LMA_GROUND2 = 0x2,
    LMA_GROUND3 = 0x3,
    LMA_SPECIAL1 = 0x4,
    LMA_SPECIAL2 = 0x5,
    LMA_BRIDGE = 0x6,
    LMA_NONE7 = 0x7,
    LMA_WG = 0x8,
    LMA_WATER = 0x9,
}
eLANDMARK_ATTR;

/************************/
/*  Structures          */
/************************/
typedef struct
{
    int32_t x;
    int32_t z;
}
POS_XZ;

typedef struct
{
    int32_t nbIndex;
    POS_XZ pos[512]; /* SADX = 1024 */
}
LAND_ATTR_INDEX;

/************************/
/*  Data                */
/************************/
#define AttrIndexList       DataAry(LAND_ATTR_INDEX, 0x01A15938, [16])

#define LandAttrNeut        DataAry(int32_t         , 0x01362130, [1280])
#define LandAttrHero        DataAry(int32_t         , 0x01363530, [1280])
#define LandAttrDark        DataAry(int32_t         , 0x01364930, [1280])

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Buffer landmark attributes of current garden into 'AttrIndexList' **/
void    AL_InitLandMark(void);

/** Put random position of a landmark, of kind 'attr,' into 'pPos' **/
bool32_t  AL_GetRandomAttrPos(eLANDMARK_ATTR attr, NJS_POINT3* pPos);

/** Get landmark attribute kind at position **/
int32_t  AL_GetCurrLandAttr(NJS_POINT3* pPos);

/************************/
/*  Inline Functions    */
/************************/
#ifdef  SAMT_INCLUDE_FUNC_INLINES
void    AL_GetRandomAttrPos_inl(LAND_ATTR_INDEX* pAttrIndex, NJS_VECTOR* pPos, int32_t nbIndex);

#endif/*SAMT_INCLUDE_FUNC_INLINES*/

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define AL_InitLandMark_p       FuncPtr(void, __cdecl, (void), 0x00534EF0)

/** User-Function ptrs **/
EXTERN const void* const AL_GetCurrLandAttr_p;
EXTERN const void* const AL_GetRandomAttrPos_inl_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_LANDMARK_H_ */
