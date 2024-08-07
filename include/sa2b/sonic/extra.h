/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/extra.h'
*
*   Description:
*       Structs, data, and functions for the Minimal inventory
*   system.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
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
    f32       posx;
    f32       velo;
    f32       shiftx;
    int32_t timer;
}
EXTRA_LIST;

/************************/
/*  Data                */
/************************/
#define extra_lists        DATA_ARY(EXTRA_LIST, 0x01946EC8, [3])

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
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define Extra_Get_p             FUNC_PTR(EXTRA_LIST*, __fastcall, (int32_t), 0x00487260)

/** User-Function ptrs **/
#   define AddExtraDisplay_p       ((void*)0x004872F0)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_EXTRA_H_*/
