/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/path.h'
*
*   ~~ Under Construction ~~
* 
*   Description:
*       Game path structures, mostly used by players for loops.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_PATH_H_
#define _SA2B_PATH_H_

/************************/
/*  Structs             */
/************************/
typedef struct pathtbl
{
    int16_t   slangx;
    int16_t   slangz;
    f32       length;
    f32       xpos;
    f32       ypos;
    f32       zpos;
}
PATH_TABLE;

typedef struct pathtag
{
    uint8_t     pathtype;
    uint16_t    points;
    f32         totallen;
    PATH_TABLE* tblhead;
    void*       pathtask;
}
PATH_TAG;

typedef struct pathgrp
{
    uint32_t   wanmb;
    PATH_TAG** tags;
}
PATH_GROUP;

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t ManagePathCreate(PATH_TAG** pPathList);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define ManagePathCreate_p       FUNC_PTR(int32_t, __cdecl, (PATH_TAG** pPathList), 0x00490110)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_PATH_H_*/
