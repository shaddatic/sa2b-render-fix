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
    uint32 Attr_top;
    uint32 Attr_bottom;
    float32 y_top;
    float32 y_bottom;
    uint32 _Attr_top;
    uint32 _Attr_bottom;
    float32 scl;
}
SHADOWWK;

typedef struct xssunit
{
    sint32 findflag;
    sint32 objatt;
    sint32 angx;
    sint32 angz;
    float32 onpos;
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
float32 GetShadowPos(float32 x, float32 y, float32 z, Angle3* ang);

/** Calculate shadow info below 'position' **/
void    GetCharacterShadowInfo(NJS_VECTOR* position, SHADOWWK* swp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function Ptrs **/
#define GetShadowPos_p              FuncPtr(float32, __cdecl, (float32, float32, float32, Angle3*), 0x00494C30)
#define GetCharacterShadowInfo_p    FuncPtr(void   , __cdecl, (NJS_VECTOR*, SHADOWWK*)            , 0x00494DF0)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_SHADOW_H_ */