/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/extra.h'
*
*   Contains data and functions related to Minimals in the main game
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
    sint32 num;
    sint32 timer;
}
EXTRA;

typedef struct
{
    EXTRA overflow[10];
    EXTRA list[10];
    sint32 nbExtra;
    float32 posx;
    float32 velo;
    float32 shiftx;
    sint32 timer;
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
EXTRA_LIST* Extra_Get(sint32 pno);
/** Add minimal to extra list **/
void        AddExtraDisplay(sint32 num, sint32 pno);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define Extra_Get_p        FuncPtr(EXTRA_LIST*, __fastcall, (sint32), 0x00487260)

/** User-Function ptrs **/
EXTERN const void* AddExtraDisplay_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_EXTRA_H_ */
