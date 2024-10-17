/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_confirmsave.h'
*
*   Description:
*     Chao World save file saving functions and state.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SA2B_CHAO_CONFIRMSAVE
#define H_SA2B_CHAO_CONFIRMSAVE

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
#define gChaoSaveBusy           DATA_REF(s32, 0x019F645C)
#define gChaoSaveSaved          DATA_REF(s32, 0x01A0F940)
#define gChaoSaveAnother        DATA_REF(s32, 0x01A0F948)

/************************/
/*  Prototypes          */
/************************/
/****** Save Start ******************************************************************/
/*
*   Description:
*     Start saving Chao World's ALF save file. State will be set to 'Busy' until
*   saving is complete.
*/
void    AL_ConfirmSaveStart( void );

/****** Save State ******************************************************************/
/*
*   Description:
*     Get 'Busy' state of the Chao Save saving task.
*
*   Returns:
*     '1' if the save file is being loaded, '0' if not.
*/
s32     AL_ConfirmSaveIsBusy( void );

/************************/
/*  Internal Protos     */
/************************/
/****** Task Functions **************************************************************/
/*
*   Description
*     Chao file save task functions.
*/
void    FExec_ChaoSave( task* tp );
void    FDest_ChaoSave( task* tp );

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/****** Function Pointers ***********************************************************/
#   define AL_ConfirmSaveStart_p        FUNC_PTR(void, __cdecl, (void) , 0x00530230)
#   define FExec_ChaoSave_p             FUNC_PTR(void, __cdecl, (task*), 0x0052FC60)
#   define FDest_ChaoSave_p             FUNC_PTR(void, __cdecl, (task*), 0x0052FBC0)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_CHAO_CONFIRMSAVE*/
