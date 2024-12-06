/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_stage.h'
*
*   Description:
*     
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SA2B_CHAO_STAGE
#define H_SA2B_CHAO_STAGE

/************************/
/*  Ext Opaque Structs  */
/************************/
/****** Task ************************************************************************/
typedef struct task             task;

EXTERN_START

/************************/
/*  Enums               */
/************************/
/****** Chao Stage ******************************************************************/
typedef enum
{    
    CHAO_STG_NONE,              /* initial stage                                    */

    CHAO_STG_NEUT,              /* neutral garden                                   */
    CHAO_STG_HERO,              /* hero garden                                      */
    CHAO_STG_DARK,              /* dark garden                                      */
    CHAO_STG_RACE,              /* chao race                                        */
    CHAO_STG_ENTRANCE,          /* race entrance                                    */
    CHAO_STG_KINDER,            /* kindergarten                                     */
    CHAO_STG_LOBBY,             /* chao lobby                                       */
    CHAO_STG_ENTRANCE_2P,       /* race entrance 2p                                 */
    CHAO_STG_STADIUM,           /* stadium (omochao cave)                           */
    CHAO_STG_KARATE,            /* karate                                           */
    CHAO_STG_KARATE_2P,         /* karate 2p                                        */
    CHAO_STG_ODEKAKE,           /* odekake (transporter)                            */

    NB_CHAO_STAGE,              /* chao stage number                                */
}
eCHAO_STAGE_NUMBER;

/****** Stage Master ****************************************************************/
typedef enum 
{
    MD_STAGE_START,
    MD_STAGE_LOAD_FILE,
    MD_STAGE_LOAD_FILE_WAIT,
    MD_STAGE_CONFIRM_CREATION,
    MD_STAGE_CONFIRM_CREATION_WAIT,
    MD_STAGE_CREATE_FILE,
    MD_STAGE_CREATE_FILE_WAIT,
    MD_STAGE_INIT,
    MD_STAGE_MANAGE,
    MD_STAGE_SLEEP,
    MD_STAGE_WHITE_OUT,
    MD_STAGE_SAVE_START,
    MD_STAGE_SAVE_WAIT,
    MD_STAGE_EXIT,
    MD_STAGE_ZOMBIE,
}
eMD_STAGE_MASTER;

/************************/
/*  Data                */
/************************/
/****** Chao Stage ******************************************************************/
#define ChaoStageNumber         DATA_REF(eCHAO_STAGE_NUMBER, 0x134046C)
#define ChaoOldStageNumber      DATA_REF(eCHAO_STAGE_NUMBER, 0x13402AC)
#define ChaoNextStageNumber     DATA_REF(eCHAO_STAGE_NUMBER, 0x134062C)

/****** Wait For Save ***************************************************************/
#define gChaoWaitForSaveTaskList    DATA_ARY(task*, 0x019F63F8, [4])
#define gChaoWaitForSaveTaskNum     DATA_REF(int  , 0x019F6164)

/************************/
/*  Prototypes          */
/************************/
/****** Chao Stage ******************************************************************/
/*
*   Description:
*     Get the current Chao stage number.
*
*   Returns:
*     The current Chao stage index.
*/
eCHAO_STAGE_NUMBER AL_GetStageNumber( void );
/*
*   Description:
*     Get the previous Chao stage number.
*
*   Returns:
*     The previous Chao stage index.
*/
eCHAO_STAGE_NUMBER AL_GetPreStageNumber( void );
/*
*   Description:
*     Get the next Chao stage number.
*
*   Returns:
*     The next Chao stage index.
*/
eCHAO_STAGE_NUMBER AL_GetNextStageNumber( void );

/****** Change Stage ****************************************************************/
/*
*   Description:
*     Change the current Chao stage after fading out.
*
*   Parameters:
*     - NextStage : stage index to change to
*/
void    AL_ChangeStage( eCHAO_STAGE_NUMBER NextStage );

/****** Chao Count ******************************************************************/
/*
*   Description:
*     Get the number of Chao saved in an arbitrary Chao stage.
*
*   Notes:
*     - Chao in class will still count toward the returned value
*
*   Parameters:
*     - stage   : stage index to get the Chao count of
*
*   Returns:
*     Chao count in the given stage
*/
s32     AL_GetLocalChaoCount( eCHAO_STAGE_NUMBER stage );
/*
*   Description:
*     Get the number of Chao saved in the current Chao stage.
*
*   Notes:
*     - Chao in class will still count toward the returned value
*
*   Returns:
*     Chao count in the current stage
*/
s32     AL_GetCurrGardenChaoCount( void );

/************************/
/*  Internal Protos     */
/************************/
/****** Wait For Save ***************************************************************/
/*
*   Description:
*     Add save Task to the wait list
*/
void    AL_WaitForSaveHookAdd( task* tp );
void    AL_WaitForSaveHookRemove( task* tp );

/************************/
/*  Macros              */
/************************/
#define AL_IsStageGarden(stg)       (stg >= CHAO_STG_NEUT && stg <= CHAO_STG_DARK)

#define AL_IsCurrStageGarden()      AL_IsStageGarden(AL_GetStageNumber())

#define AL_IsStageLoaded()          (AL_GetStageNumber() == AL_GetNextStageNumber())

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/****** Function Pointers ***********************************************************/
#   define AL_ChangeStage_p     FUNC_PTR(void, __cdecl, (eCHAO_STAGE_NUMBER), 0x0052B5B0)

/****** Usercall Pointers ***********************************************************/
#   define AL_GetLocalChaoCount_p       ((void*)0x005319F0)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_CHAO_STAGE*/
