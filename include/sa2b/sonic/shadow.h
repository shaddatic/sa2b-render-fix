/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/shadow.h'
*
*   Contains structs and functions related to ground shadow information.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
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
    f32       y_top;
    f32       y_bottom;
    uint32_t _Attr_top;
    uint32_t _Attr_bottom;
    f32       scl;
}
SHADOWWK;

typedef struct xssunit
{
    int32_t findflag;
    int32_t objatt;
    int32_t angx;
    int32_t angz;
    f32       onpos;
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
f32       GetShadowPos(f32 x, f32 y, f32 z, Angle3* ang);

/** Calculate shadow info below 'position' **/
void    GetCharacterShadowInfo(NJS_VECTOR* position, SHADOWWK* swp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function Ptrs **/
#define GetShadowPos_p              FUNC_PTR(f32    , __cdecl, (f32, f32, f32, Angle3*), 0x00494C30)
#define GetCharacterShadowInfo_p    FUNC_PTR(void   , __cdecl, (NJS_VECTOR*, SHADOWWK*), 0x00494DF0)

#endif /* SAMT_INCL_FUNCPTRS */

#endif /* _SA2B_SHADOW_H_ */
