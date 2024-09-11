/*
*   Sonic Adventure Mod Tools (SA2B) - '/gx/gxlight.h'
*
*   Description:
*       Defines internal GX light structures.
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _GX_LIGHT_H_
#define _GX_LIGHT_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Structures          */
/************************/
typedef struct gxs_light_attr
{
    NJS_VECTOR vec;
    NJS_POINT3 pos;
    NJS_ARGB   color;
    NJS_ARGB   attenA;
    NJS_VECTOR attenK;
}
GXS_LIGHT_ATTR;

typedef struct gxs_light
{
    GXS_LIGHT_ATTR* pAttr;
    char _unk[60];
}
GXS_LIGHT;

#endif/*_GX_LIGHT_H_*/
