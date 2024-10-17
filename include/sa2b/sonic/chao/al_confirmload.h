/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_confirmload.h'
*
*   Description:
*     Chao World save file loading functions and state.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SA2B_CHAO_CONFIRMLOAD
#define H_SA2B_CHAO_CONFIRMLOAD

/************************/
/*  Ext Opaque Structs  */
/************************/
/****** Task ************************************************************************/
typedef struct task             task;

EXTERN_START

/************************/
/*  Game Data           */
/************************/
/****** Load State ******************************************************************/
#define gChaoLoadBusy           DATA_REF(s32, 0x019F6440)
#define gChaoLoadLoaded         DATA_REF(s32, 0x019F6444)

/************************/
/*  Prototypes          */
/************************/
/****** Load Start ******************************************************************/
/*
*   Description:
*     Start loading Chao World's ALF save file. State will be set to 'Busy' until
*   loading is complete.
*/
void    AL_ConfirmLoadStart( void );

/****** Load State ******************************************************************/
/*
*   Description:
*     Get 'Busy' state of the Chao Save loading task.
*
*   Returns:
*     '1' if the save file is being loaded, '0' if not.
*/
s32     AL_ConfirmLoadIsBusy( void );
/*
*   Description:
*     Get 'Loaded' state of the Chao Save loading task.
*
*   Returns:
*     '1' if the save file is loaded, '0' if not.
*/
s32     AL_ConfirmLoadIsLoaded( void );

/************************/
/*  Internal Protos     */
/************************/
/****** Task Functions **************************************************************/
/*
*   Description
*     Chao file load task functions.
*/
void    FExec_ChaoLoad( task* tp );
void    FDest_ChaoLoad( task* tp );

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/****** Function Pointers ***********************************************************/
#   define AL_ConfirmLoadStart_p        FUNC_PTR(void, __cdecl, (void) , 0x00530230)
#   define FExec_ChaoLoad_p             FUNC_PTR(void, __cdecl, (task*), 0x0052DD90)
#   define FDest_ChaoLoad_p             FUNC_PTR(void, __cdecl, (task*), 0x0052DD00)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_CHAO_CONFIRMLOAD*/
