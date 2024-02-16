/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/shadow.h'
*
*   Contains structs and functions related to ground shadow information.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_SHADOW_H_
#define _SA2B_SHADOW_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Constants           */
/************************/
/** Returned when theres no ground shadow info **/
#define SHADOW_Y_NONE   (-10000000.0f)

/************************/
/*  Structures          */
/************************/
typedef struct shadowwk
{
    Angle angx;
    Angle angz;
    uint32_t Attr_top;
    uint32_t Attr_bottom;
    float32_t y_top;
    float32_t y_bottom;
    uint32_t _Attr_top;
    uint32_t _Attr_bottom;
    float32_t scl;
}
SHADOWWK;

typedef struct xssunit
{
    int32_t findflag;
    int32_t objatt;
    int32_t angx;
    int32_t angz;
    float32_t onpos;
    NJS_POINT3 normal;
}
XSSUNIT;

typedef struct zxsdwstr
{
    NJS_POINT3 pos;
    XSSUNIT lower;
    XSSUNIT upper;
}
ZXSDWSTR;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Calculate ground shadow position and angle **/
float32_t GetShadowPos(float32_t x, float32_t y, float32_t z, Angle3* ang);

/** Calculate shadow info below 'position' **/
void    GetCharacterShadowInfo(NJS_VECTOR* position, SHADOWWK* swp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function Ptrs **/
#define GetShadowPos_p              FuncPtr(float32_t, __cdecl, (float32_t, float32_t, float32_t, Angle3*), 0x00494C30)
#define GetCharacterShadowInfo_p    FuncPtr(void   , __cdecl, (NJS_VECTOR*, SHADOWWK*)            , 0x00494DF0)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_SHADOW_H_ */
