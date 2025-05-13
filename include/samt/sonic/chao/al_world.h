/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/chao/al_world.h'
*
*   Description:
*     Chao World communication between world entries and other general world execution module.
*/
#ifndef H_SA2B_CHAO_WORLD
#define H_SA2B_CHAO_WORLD

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** Task ************************************************************************************/
typedef struct task         task;   /* task struct                                              */

/********************************/
/*  Constants                   */
/********************************/
/****** ALW Flag ********************************************************************************/
#define ALW_FLAG_HELD               (1<<1) /* held by player or chao                            */

/****** Communication/Attention *****************************************************************/
#define ALW_COMMUID_OFF             ( -1) /* no communication/attention                         */
#define ALW_COMMUID_MAX             (255) /* communication/attention id max                     */

/********************************/
/*  Enums                       */
/********************************/
/****** World Category **************************************************************************/
enum
{
    ALW_CATEGORY_CHAO,              /* chao                                                     */
    ALW_CATEGORY_EGG,               /* chao egg                                                 */  
    ALW_CATEGORY_MINIMAL,           /* minimal, or chaos drive                                  */
    ALW_CATEGORY_FRUIT,             /* fruit                                                    */
    ALW_CATEGORY_TREE,              /* tree                                            [unused] */
    ALW_CATEGORY_GROWTREE,          /* garden tree                                              */
    ALW_CATEGORY_TOY,               /* garden toy                                               */
    ALW_CATEGORY_SEED,              /* tree seed                                                */
    ALW_CATEGORY_SOUND,             /* sound                                           [unused] */
    ALW_CATEGORY_MASK,              /* enum count                                               */
    ALW_CATEGORY_SPECIAL,           /* enum count                                               */

    NB_CATEGORY,                    /* enum count                                               */
};

/****** Sub-category ****************************************************************************/
enum
{
    ALW_KIND_NONE,                  /* no specific sub-category                                 */

    /** Minimal **/

    ALW_KIND_CDR,                   /* chaos drive                                              */

    /** Garden Toy **/

    ALW_KIND_TV,                    /* television                                               */
    ALW_KIND_RADICASE,              /* radio                                                    */
    ALW_KIND_BALL,                  /* chao ball                                                */
    ALW_KIND_PIANO,                 /* piano                                                    */
    ALW_KIND_ORGAN,                 /* organ                                                    */
    ALW_KIND_HORSE,                 /* rocking horse                                            */
    ALW_KIND_BOX,                   /* jack-in-the-box                                          */
};

/****** Command *********************************************************************************/
enum
{
    ALW_CMD_ERROR = -1,             /* command error                                            */

    ALW_CMD_NONE,                   /* command error                                            */
    ALW_CMD_GO,                     /* command error                                            */
    ALW_CMD_EAT,                    /* command error                                            */
    ALW_CMD_CHANGE,                 /* command error                                            */
    ALW_CMD_FINISH,                 /* command error                                            */
    ALW_CMD_PLANTED,                /* command error                                            */
    ALW_CMD_BYE,                    /* command error                                            */
};

/********************************/
/*  Structures                  */
/********************************/
/****** Grow Param ******************************************************************************/
typedef struct
{
    s16 mood;                       /* mood change, GBA                                [unused] */
    s16 belly;                      /* belly change, GBA                               [unused] */

    s16 addexp[8];                  /* chao stat experience add                                 */
}
GROW_PARAM;

/****** Entry Work ******************************************************************************/
typedef struct al_entry_work
{
    u16             category;       /* category index                                           */
    u16             num;            /* ???                                                      */
    u16             kind;           /* sub-category, kind                                       */

    u16             flag;           /* communication/attention flag                             */

    void*           pSaveInfo;      /* save info pointer, optional, '-1' when entry not active  */

    s32             CommuID;        /* communication/attention id                               */

    NJS_POINT3      pos;
    Angle3          ang;
    f32             radius;         /* holding radius                                           */
    f32             offset;         /* holding offset                                           */

    f32             CamDist;        /* distance from camera                                     */

    s16             command;        /* command id                                  [ALW_CMD_##] */
    s16             command_value;  /* command value                                            */

    s16             state;

    task*           tp;             /* entry task pointer                                       */

    struct al_entry_work* pCommu;   /* communication/attention entry                            */
    struct al_entry_work* pLockOn;  /* lock on entry                                            */
}
ALW_ENTRY_WORK;

#define GET_ALW_ENTRY_WORK(tp)          ((ALW_ENTRY_WORK*)tp->fwp)

/************************/
/*  Data                */
/************************/
/****** World State *****************************************************************************/
#define ChaoWorldLoadFlag       DATA_REF(b32                        , 0x01A5AF0C)

/****** ALW Core ********************************************************************************/
#define WorldMasterTask         DATA_REF(task*                      , 0x01A0F94C)

/****** ALW Entry *******************************************************************************/
#define WorldEntryList          DATA_ARY(ALW_ENTRY_WORK             , 0x01DC0FC0, [11][64])
#define nbWorldEntry            DATA_ARY(s32                        , 0x01DC0F80, [11])
#define nbMaxEntry              DATA_ARY(u32                        , 0x008AB838, [11])

/****** Grow Param ******************************************************************************/
#define FruitGrowParam          DATA_ARY(GROW_PARAM                 , 0x008A6448, [24])
#define MinimalGrowParam        DATA_ARY(GROW_PARAM                 , 0x008A6240, [26])

/****** Work ************************************************************************************/
#define Clock                   DATA_REF(s32                        , 0x01DBED74)
#define gCommuID                DATA_REF(u16                        , 0x01A5B5EC)

/********************************/
/*  Prototypes                  */
/********************************/
/****** ALW Core ********************************************************************************/
/*
*   Description:
*     Initialize world module params and create the 'ALW_Control' task.
*/
void    ALW_Create( void );
/*
*   Description:
*     Clear ALW entry lists.
*/
void    ALW_ClearEntry( void );

/****** ALW Entry *******************************************************************************/
/*
*   Description:
*     Set a new ALW entry, with optional save info parameter.
*
*   Parameters:
*     - category    : alw category
*     - tp          : new task entry
*     - kind        : alw kind, for toy                                     [opt: ALW_KIND_NONE]
*     - pSaveInfo   : optional save info parameter                                [opt: nullptr]
*
*   Returns:
*     '1' on success; or '0' on failure.
*/
s32     ALW_Entry(  u16 category, task* tp, u16 kind );
s32     ALW_Entry2( u16 category, task* tp, u16 kind, void* pSaveInfo );
/*
*   Description:
*     Release an ALW entry.
* 
*   Parameters:
*     - tp          : task entry
* 
*   Returns:
*     '1' on success.
*/
s32     ALW_CancelEntry( task* tp );

/****** World Query *****************************************************************************/
/*
*   Description:
*     Get number of active entries in a given category.
*
*   Parameters:
*     - category    : world category
*
*   Returns:
*     Entry count in that category.
*/
s32     ALW_CountEntry( s32 category );
/*
*   Description:
*     Get entry task via category and direct index.
*
*   Parameters:
*     - category    : world category
*     - num         : entry index number, up to 'nbMaxEntry[category]'
*
*   Returns:
*     Task pointer to entry; or 'nullptr' if no entry.
*/
task*   ALW_GetTask( s32 category, u16 num );
/*
*   Description:
*     Get entry task via category and count index. This function ensures no 'nullptr' until
*   the current entry count is reached by skipping 'nullptr' entries - hence 'Count'.
*
*   Parameters:
*     - category    : world category
*     - num         : entry count number, up to 'nbWorldEntry[category]'
*
*   Returns:
*     Task pointer to entry; or 'nullptr' if total entry count reached.
*/
task*   ALW_GetTaskCount( s32 category, u16 count );
/*
*   Description:
*     Get category of world entry task.
*
*   Parameters:
*     - tp          : task entry
*
*   Returns:
*     World category value; or '-1' if not a world entry.
*/
s32     ALW_GetCategory( const task* tp );

/****** Attention *******************************************************************************/
/*
*   Description:
*     Check and get current attention (one-way communication) of a world entry.
*
*   Parameters:
*     - tp          : task entry
*
*   Returns:
*     Current attention entry; or 'nullptr' if no attention or not a world entry.
*/
ALW_ENTRY_WORK* ALW_IsAttention( const task* tp );
/*
*   Description:
*     Set attention (one-way communication) of a world entry.
*
*   Parameters:
*     - tp1         : task entry to set attention of
*     - tp2         : task entry to set attention to
*
*   Returns:
*     'TRUE' on success; or 'FALSE' if either task is not a world entry.
*/
s32     ALW_AttentionOn( task* tp1, const task* tp2 );
/*
*   Description:
*     Stop and clear attention (one-way communication) of a world entry.
*
*   Parameters:
*     - tp1         : task entry to stop attention of
*
*   Returns:
*     'TRUE' on success; or 'FALSE' if task is not a world entry.
*/
s32     ALW_AttentionOff( task* tp );

/****** Communication ***************************************************************************/
/*
*   Description:
*     Check and get current communication link of a world entry.
*
*   Parameters:
*     - tp          : task entry
*
*   Returns:
*     Current communication entry; or 'nullptr' if no communication, communication is not
*   mutual, or not a world entry.
*/
ALW_ENTRY_WORK* ALW_IsCommunication( task* tp );
/*
*   Description:
*     Check and get current communication link of a world entry with additional world category.
*
*   Parameters:
*     - tp          : task entry
*
*   Returns:
*     Current communication entry; or 'nullptr' if no communication, communication is not
*   mutual, communication entry is not the given category, or not a world entry.
*/
ALW_ENTRY_WORK* ALW_IsCommunicationEx( task* tp, u16 category );
/*
*   Description:
*     Set mutual communication link between two world entries.
*
*   Parameters:
*     - tp1         : task entry 1
*     - tp2         : task entry 2
*
*   Returns:
*     'TRUE' on success; or 'FALSE' if either task is not a world entry.
*/
s32     ALW_CommunicationOn( task* tp1, task* tp2 );
/*
*   Description:
*     Stop and clear communication link between task entry and its communication partner.
*
*   Notes:
*     - If partner entry is linked to another entry and not ours (aka. just an attention) then
*       only their communication ID is reset, but their other link data is left unchanged.
*
*   Parameters:
*     - tp          : task entry 1
*
*   Returns:
*     'TRUE' on success.
*/
s32     ALW_CommunicationOff( task* tp ); /* Communication off */

/****** Commu/Atten Command *********************************************************************/
/*
*   Description:
*     Get current command id of task entry, and reset value to 'ALW_CMD_NONE'.
*
*   Parameters:
*     - tp          : task entry
*
*   Returns:
*     Current command id; or 'ALW_CMD_NONE' if no command, or not a world entry.
*/
s32     ALW_RecieveCommand( task* tp );

/****** Chao Attention **************************************************************************/
/*
*   Description:
*     Check if entry - she - has attention (one-way communication) on a *different* world
*   entry other than us.
*
*   Parameters:
*     - pMyTask     : task entry to check attention for
*     - pHerTask    : task entry to check attention of
*
*   Returns:
*     'TRUE' if she *does* have attention on another entry; or 'FALSE' if she is not an entry,
*   has no attention, or her attention is on me.
*/
s32     ALW_IsSheAttentionOtherOne( const task* pMyTask, const task* pHerTask );

/****** SAMT Additions **************************************************************************/
/*
*   Description:
*     Get max ALW entry by category.
*
*   Parameters:
*     - category    : category to get max of
*
*   Returns:
*     Max number of entries for that category.
*/
s32     ALW_GetMaxEntry( u16 category );
/*
*   Description:
*     Get kind of ALW entry toy.
*
*   Parameters:
*     - tp          : alw entry task
*
*   Returns:
*     alw entry kind; or '0xFFFF' if it is not an alw entry.
*/
u16     ALW_GetKind( task* tp );

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Ptrs               */
/********************************/
/****** Function Pointer ************************************************************************/
#define ALW_Create_p                FUNC_PTR(void, __cdecl, (void), 0x00530B80)
#define ALW_ClearEntry_p            FUNC_PTR(void, __cdecl, (void), 0x00530370)

/****** User-Function Pointer *******************************************************************/
#define ALW_Entry2_p                ((void*)0x00530750) /* EAX( CX, EBX, EAX, STK)              */
#define ALW_CancelEntry_p           ((void*)0x005307F0) /* ###(###)                             */

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_CHAO_WORLD*/
