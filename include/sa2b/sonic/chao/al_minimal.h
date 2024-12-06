/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_minimal.h'
*
*   Description:
*     Chao World minimals header.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SA2B_CHAO_MINIMAL
#define H_SA2B_CHAO_MINIMAL

/************************/
/*  External Includes   */
/************************/
/****** Ninja ***********************************************************************/
#include <sa2b/ninja/njcommon.h> /* ninja common                                    */

/****** Game ************************************************************************/
#include <sa2b/sonic/motion.h>  /* motion control                                   */

/****** Task ************************************************************************/
#include <sa2b/sonic/task/taskwk.h>   /* task work                                  */
#include <sa2b/sonic/task/taskexec.h> /* task executor                              */

/****** Colli ***********************************************************************/
#include <sa2b/sonic/c_colli/ccl_info.h> /* ccl_info                                */

/************************/
/*  External Opaques    */
/************************/
/****** Ninja ***********************************************************************/
typedef struct cnkobj           NJS_CNK_OBJECT;

/****** Task ************************************************************************/
typedef struct task             task;

/****** Chao Item Info **************************************************************/
typedef struct item_save_info   ITEM_SAVE_INFO;

EXTERN_START

/************************/
/*  Enums               */
/************************/
/****** Mini Type *******************************************************************/
/*
*   Minimal type, stored in 'btimer'
*/
enum
{
    MINI_PEN,                   /* penguin                                          */
    MINI_GOMA,                  /* seal                                             */
    MINI_RAKO,                  /* otter                                            */
    MINI_USA,                   /* rabbit                                           */
    MINI_CHIT,                  /* cheetah                                          */
    MINI_INO,                   /* warthog                                          */
    MINI_KUMA,                  /* bear                                             */
    MINI_TORA,                  /* tiger                                            */
    MINI_GORI,                  /* gorilla                                          */
    MINI_KUJA,                  /* peacock                                          */
    MINI_OUM,                   /* parrot                                           */
    MINI_KON,                   /* condor                                           */
    MINI_SKA,                   /* skunk                                            */
    MINI_SHEP,                  /* sheep                                            */
    MINI_ARA,                   /* raccoon                                          */
    MINI_HAN,                   /* half fish                                        */
    MINI_BONE,                  /* skeleton dog                                     */
    MINI_BATMAN,                /* batman                                           */
    MINI_DRA,                   /* dragon                                           */
    MINI_UNI,                   /* unicorn                                          */
    MINI_PHEN,                  /* phoenix                                          */

    NB_MINI,                    /* minimal count                                    */
};

/****** Mini 'mode' *****************************************************************/
/*
*   Used in the main executor function
*/
enum
{
    MD_NORMAL,                  /* normal func based on type                        */
    MD_HELD_P,                  /* minimal held by player                           */
    MD_HELD_C,                  /* minimal held by chao                             */
    MD_EXIT,                    /* destruct task                                    */
};

/****** Mini 'smode' ****************************************************************/
/*
*   Used in the 'ALM_FuncWalk' function
*/
enum
{
    SMD_FW_INIT,                /* minimal init                                     */
    SMD_FW_THROWN,              /* minimal thrown                                   */
    SMD_FW_MOVE,                /* minimal walk                                     */
    SMD_FW_BRAKE,               /* minimal stopping                                 */
    SMD_FW_STOP,                /* minimal stopped                                  */
    SMD_FW_WATER,               /* minimal swimming                                 */
    SMD_FW_JUMP,                /* minimal jumping up                               */
    SMD_FW_JUMP_FALL,           /* minimal falling after jump                       */
    SMD_FW_TURN_L,              /* minimal turning left                             */
    SMD_FW_TURN_R,              /* minimal turning right                            */
};

/****** Mini Motion *****************************************************************/
/*
*   Motion table list switch
*/
enum
{
    MINI_MTN_WAIT,              /* standing                                         */
    MINI_MTN_WALK,              /* walking                                          */
    MINI_MTN_HUG,               /* held by Chao                                     */
    MINI_MTN_FLY,               /* flying                                           */
};

/************************/
/*  Structures          */
/************************/
/****** Mini Work *******************************************************************/
/*
*   Get minimal work from task pointer.
*/
#define GET_MINIMAL_WORK(tp)    ((MINIMAL_WORK*)(tp)->twp)

typedef struct // taskwk
{
    TASKWK;

    f32          spd;
    int32_t      RangeOutTimer;
    MOTION_CTRL  MtnCtrl;
    MOTION_TABLE MtnTable[4];
    int32_t      CaptureFlag;
}
MINIMAL_WORK;

/************************/
/*  Data                */
/************************/
/****** Normal Mode Functions *******************************************************/
/*
*   Description:
*     Normal execution function list. Each minimal type uses a seperate entry.
*
*   Notes:
*     - Every entry is 'ALM_FuncWalk'.
*/
#define AL_MinimalNormalFunc        DATA_ARY(task_exec, 0x01316B00, [NB_MINI])

/****** Object Info *****************************************************************/

#define pObjectMinimal              DATA_ARY(NJS_CNK_OBJECT*, 0x012966F0, [NB_MINI])

/****** Motion Info *****************************************************************/
/*
*   Description:
*     Initial motion table states. This is copied directly into 'MtnTable[4]'.
*/
#define InitMtnTable                DATA_ARY(MOTION_TABLE, 0x01316B60, [4])
/*
*   Description:
*     Motion pointer lists.
*/
#define pMotionMinimalWait          DATA_ARY(NJS_MOTION*, 0x01296870, [NB_MINI])
#define pMotionMinimalWalk          DATA_ARY(NJS_MOTION*, 0x012967F0, [NB_MINI])
#define pMotionMinimalHug           DATA_ARY(NJS_MOTION*, 0x01296770, [NB_MINI])
#define pMotionMinimalFly           DATA_ARY(NJS_MOTION*, 0x012968D8, [NB_MINI])

/****** Colli Info ******************************************************************/
/*
*   Description:
*     Minimal collision info.
*/
#define alm_colli_info              DATA_ARY(CCL_INFO, 0x008A7488, [3])

/************************/
/*  Prototypes          */
/************************/
/****** Create Manager **************************************************************/
/*
*   Description:
*     Create the minimal create manager Task. Handles creating Minimals and Chaos
*   Drives from the player's inventory.
*/
void    AL_CreateMinimalCreateManager( void );

/****** Create Minimal **************************************************************/
/*
*   Description:
*     Create a minimal with set parameters.
*
*   Notes:
*     - If no save info is given, the minimal will not save
*
*   Parameters:
*     - num         : minimal type
*     - pPos        : set position
*     - AngY        : set angle
*     - pVelo       : set velocity
*     - pSaveInfo   : save info to use                                    (optional)
*
*   Returns:
*     Task pointer to created minimal; or 'nullptr' on failure.
*/
task*   AL_MinimalCreate( s8 num, const NJS_POINT3* pPos, Angle AngY, const NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo );

#ifndef SAMT_EXCL_INTLFUNC

/****** Exec Functions **************************************************************/
/*
*   Description:
*     Minimal walk cycle execution function. Used in 'AL_MinimalNormalFunc' list.
*
*   Paremeters:
*     - tp          : task pointer
*/
void    ALM_FuncWalk( task* tp );
/*
*   Description:
*     Minimal held by player execution function.
*
*   Paremeters:
*     - tp          : task pointer
*/
void    AL_MinimalHeldP( task* tp );
/*
*   Description:
*     Minimal held by chao execution function. Also known as 'HUG'.
*
*   Paremeters:
*     - tp          : task pointer
*/
void    AL_MinimalHeldC( task* tp );

/****** Task Functions **************************************************************/
/*
*   Description:
*     Minimal Task executor.
*
*   Paremeters:
*     - tp          : task pointer
*/
void    AL_MinimalExecutor( task* tp );
/*
*   Description:
*     Minimal Task displayer.
*
*   Paremeters:
*     - tp          : task pointer
*/
void    AL_MinimalDisplayer( task* tp );
/*
*   Description:
*     Minimal Task destructor.
*
*   Paremeters:
*     - tp          : task pointer
*/
void    AL_MinimalDestructor( task* tp );

#endif/*SAMT_EXCL_INTLFUNCS*/

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/************************************************************************************/
/*
*   Standard Functions
*/

/****** Create Manager **************************************************************/
#define AL_CreateMinimalCreateManager_p     FUNC_PTR(void , __cdecl, (void), 0x00549490)

/****** Create Minimal **************************************************************/
#define AL_MinimalCreate_p          FUNC_PTR(task*, __cdecl, (s8, const NJS_POINT3*, Angle, const NJS_VECTOR*, ITEM_SAVE_INFO*), 0x00548D30)

/****** Exec Functions **************************************************************/
#define ALM_FuncWalk_p              FUNC_PTR(void , __cdecl, (task*), 0x0057BD40)

/****** Task Functions **************************************************************/
#define AL_MinimalExecutor_p        FUNC_PTR(void , __cdecl, (task*), 0x00548C50)
#define AL_MinimalDisplayer_p       FUNC_PTR(void , __cdecl, (task*), 0x005489D0)
#define AL_MinimalDestructor_p      FUNC_PTR(void , __cdecl, (task*), 0x00548C30)

/************************************************************************************/
/*
*   Usercall/purge Functions
*/

/****** Exec Functions **************************************************************/
#define AL_MinimalHeldP_p            ((void*)0x00548730)/* ###(EDI)                 */
#define AL_MinimalHeldC_p            ((void*)0x00548870)/* ###(EAX)                 */

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_CHAO_MINIMAL*/
