/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/extra.h'
*
*   Description:
*       Structs, data, and functions for the Minimal inventory
*   system.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_EXTRA_H_
#define _SA2B_EXTRA_H_

/************************/
/*  Structures          */
/************************/
typedef struct 
{
    int32_t num;
    int32_t timer;
}
EXTRA;

typedef struct
{
    EXTRA overflow[10];
    EXTRA list[10];
    int32_t nbExtra;
    float32_t posx;
    float32_t velo;
    float32_t shiftx;
    int32_t timer;
}
EXTRA_LIST;

/************************/
/*  Data                */
/************************/
#define extra_lists        DataAry(EXTRA_LIST, 0x01946EC8, [3])

/************************/
/*  Functions            */
/************************/
EXTERN_START
/** Get EXTRA_LIST via player's character alignment **/
EXTRA_LIST* Extra_Get( int32_t pno );

/** Add minimal to extra list **/
void        AddExtraDisplay( int32_t num, int32_t pno );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#   define Extra_Get_p             FuncPtr(EXTRA_LIST*, __fastcall, (int32_t), 0x00487260)

/** User-Function ptrs **/
#   define AddExtraDisplay_p       ((void*)0x004872F0)

#endif/*SAMT_INCLUDE_FUNC_PTRS*/

#endif/*_SA2B_EXTRA_H_*/
