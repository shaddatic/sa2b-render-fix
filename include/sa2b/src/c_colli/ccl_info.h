/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/c_colli/ccl_info.h'
*
*   Description:
*       Definition for the CCL_INFO struct type.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CCOLLI_INFO_H_
#define _SA2B_CCOLLI_INFO_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Structures          */
/************************/
typedef struct
{
    int8_t     kind;
    uint8_t    form;
    int8_t     push;
    int8_t     damage;
    uint32_t   attr;
    NJS_POINT3 center;
    float32_t  a;
    float32_t  b;
    float32_t  c;
    float32_t  d;
    int32_t    angx;
    int32_t    angy;
    int32_t    angz;
}
CCL_INFO;

#endif/*_SA2B_CCOLLI_INFO_H_*/
