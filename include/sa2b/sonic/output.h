/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/output.h'
*
*   ~~~ Under Construction ~~~
* 
*   Description:
*     Outputting to the player, such as controller vibration
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SA2B_OUTPUT
#define H_SA2B_OUTPUT

/************************/
/*  Ext. Opaque Types   */
/************************/
/****** Task ************************************************************************/
typedef struct task         TASK;

EXTERN_START

/************************/
/*  Structures          */
/************************/
/****** Vibration Param *************************************************************/
#define GET_VIBPARAM(tp_)       ((VIBPARAM*)(tp_)->fwp)

typedef struct /* forcewk */
{
    int8_t   unit;
    uint8_t  flag;
    int8_t   power;
    uint8_t  freq;
    uint32_t inc;
    int32_t  maxTime;
}
VIBPARAM;

/****** Vibration Work **************************************************************/
#define GET_VIBWK(tp_)          ((VIBWK*)(tp_)->awp)

typedef struct /* anywk */
{
    int32_t  unk_0;
    int32_t  timer;
    int32_t  unk_1;
    int32_t  unk_2;
}
VIBWK;

/************************/
/*  Data                */
/************************/
/****** VibTask *********************************************************************/
#define VibTaskP            DATA_ARY(TASK*, 0x01A5588C, [4])

/************************/
/*  Functions           */
/************************/
/****** VibTask *********************************************************************/
/*
*   Description:
*     Vibrate controller 'unit' for 's32Time' frames at 'power' strength. If called
*   multiple times, the most recent call will override previous calls
*
*   Parameters:
*     - pno     : index of the player controller unit to vibrate
*     - Flag    : vibration flags (not understood, '3' is safe)
*     - Power   : vibration strength (0<->7)
*     - Freq    : vibration frequency (unused)
*     - Inc     : vibration gradient period (unused)
*     - Time    : number of frames, plus 1, to vibrate for
*/
void    SetVibTask( int pno, char Flag, char Power, char Freq, int Inc, int Time );
/*
*   Description:
*     Stop all vibrations
*/
void    VibStop( void );

/****** VibTask Task Functions ******************************************************/
void    VibTask(     TASK* tp );    /* executor                                     */
void    VibTaskDest( TASK* tp );    /* destructor                                   */

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/****** Function Pointer ************************************************************/
#   define VibStop_p            FUNC_PTR(void, __cdecl, (void) , 0x00439060)
#   define VibTask_p            FUNC_PTR(void, __cdecl, (TASK*), 0x00438D30)
#   define VibTaskDest_p        FUNC_PTR(void, __cdecl, (TASK*), 0x00438C90)

/****** User-Function Pointer *******************************************************/
#   define SetVibTask_p         ((void*)0x00438DC0)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_OUTPUT*/
