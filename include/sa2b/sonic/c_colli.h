/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/c_colli.h'
*
*   Description:
*       Contains structs, enums, and functions related to the
*   game's core collision engine.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SA2B_CCOLLI
#define H_SA2B_CCOLLI

/************************/
/*  External Includes   */
/************************/
/****** Self ************************************************************************/
#include <sa2b/sonic/c_colli/ccl_info.h> /* ccl info                                */

/************************/
/*  External Opaques    */
/************************/
/****** Task ************************************************************************/
typedef struct task             task;   /* task                                     */
typedef struct taskwk           taskwk; /* task work                                */

EXTERN_START

/************************/
/*  Constants           */
/************************/
/****** Colli Flags *****************************************************************/
#define CCL_FLAG_PUSHED         (0x10) /* is pushed                                 */

/************************/
/*  Enums               */
/************************/
/****** Colli Info Type *************************************************************/
enum
{
    CI_KIND_OSAMPO      = 0x01, /* walking                                          */
    CI_KIND_PATTING_HAND,       /* patting hand                                     */
    CI_KIND_SAPLING,            /* sapling                                          */
    CI_KIND_SAPLING_FIELD,      /* sapling area                                     */
    CI_KIND_KAME_FIELD,         /* turtle area                                      */
    CI_KIND_ENEMYBALL,          /* enemy ball                                       */
    CI_KIND_PUNCH,              /* punch                                            */
    CI_KIND_2PLASER,            /* 2P laser                              (& bosses) */
    CI_KIND_2PSHOTS,            /* 2P shots                              (& bosses) */
    CI_KIND_2PMISSILES,         /* 2P missiles                           (& bosses) */
    CI_KIND_NO_RIDE,            /* no ride                                          */
    CI_KIND_NO_PUNCH,           /* no punch                                         */
    CI_KIND_NO_LOCKON,          /* no lock-on                                       */
    CI_KIND_NO_CATCH,           /* no catch                                         */
    CI_KIND_DO_CATCH,           /* do catch                                         */
    CI_KIND_NO_COLLIDE,         /* no collide                                       */
    CI_KIND_G_CYLINDER,         /* gravity cylinder                                 */
    CI_KIND_NO_HOLD_FIELD,      /* no hold area                                     */
    CI_KIND_BOMB_EXPLOSION,     /* bomb explosion                                   */
    CI_KIND_CHAOSDRIVE,         /* chaos drive                                      */

    CI_KIND_DUMMY       = 0x40, /* dummy kind                                       */
};

/****** Colli Info Form *************************************************************/
enum
{
    CI_FORM_SPHERE,             /* sphere form                                      */
    CI_FORM_CYLINDER,           /* cylinder form                                    */
    CI_FORM_CYLINDER2,          /* cylinder 2 form                                  */
    CI_FORM_RECTANGLE,          /* rectangle form                                   */
    CI_FORM_RECTANGLE2,         /* rectangle 2 form                                 */
    CI_FORM_RECTANGLE3,         /* rectangle 3 form                                 */
    CI_FORM_CAPSULE,            /* capsule form                                     */
    CI_FORM_PERSON,             /* person form                                      */
    CI_FORM_LINE,               /* line form                                        */
    CI_FORM_WALL_PLANE,         /* wall plane form                                  */
    CI_FORM_WALL_CIRCLE         /* wall circle form                                 */
};

/****** Colli Info ID ***************************************************************/
enum
{
    CID_PLAYER,                 /* player id                                        */
    CID_BULLET,                 /* bullet id                                        */
    CID_ENEMY,                  /* enemy id                                         */
    CID_ENEMY2,                 /* enemy 2 id                                       */
    CID_OBJECT,                 /* object id                                        */
    CID_OBJECT2,                /* object 2 id                                      */
    CID_ITEM,                   /* item id                                          */
    CID_ITEM2,                  /* item 2 id                                        */
    CID_WALL,                   /* wall id                                          */
    CID_CHAO,                   /* chao world id                                    */
};

/************************/
/*  Structures          */
/************************/
/****** Colli Hit Info **************************************************************/
typedef struct c_colli_hit_info
{
    s8      my_num;             /* my hit colli info index                          */
    s8      hit_num;            /* their hit colli info index                       */
    u16     flag;               /* their flags                                      */
    task*   hit_tp;             /* their task pointer                               */
}
CCL_HIT_INFO;

/****** Colli Work ******************************************************************/
typedef struct colliwk
{
    u16             id;           /* colli id                                       */
    s16             nbHit;        /* colli hit number                               */
    u16             flag;         /* colli flags                                    */
    u16             nbInfo;       /* colli info count                               */
    f32             colli_range;  /* colli range                                    */
    CCL_INFO*       info;         /* colli info list                                */
    CCL_HIT_INFO    hit_info[16]; /* colli hit info list                            */
    NJS_POINT3      normal;       /* colli normal                                   */
    task*           mytask;       /* task pointer to this task                      */
    s16             my_num;       /* my colli info index                            */
    s16             hit_num;      /* hit colli info index                           */
    struct colliwk* hit_cwp;      /* hit colli work                                 */
}
colliwk;

#ifdef SAMT_INCL_INTERNAL

/****** Colli Search ****************************************************************/
typedef struct
{
    task*   pTask;              /* last search task                                 */
    void*   FuncAddr;           /* last search function                             */
    s32     CurrNum;            /* current hit info number                          */
    s32     Kind;               /* last search colli type                           */
}
CCL_SEARCH;

#endif/*SAMT_INCL_INTERNAL*/

/************************/
/*  Data                */
/************************/
#ifdef SAMT_INCL_INTERNAL

/****** Colli Search ***************************************************************/
#define Search                  DATA_REF(CCL_SEARCH, 0x019468A0)

#endif/*SAMT_INCL_INTERNAL*/

/************************/
/*  Prototypes          */
/************************/
/****** Colli Execute ***************************************************************/
/*
*   Description:
*     Calculate collision entries at the end of the execution frame and update all
*   registered collision work.
*
*   Notes:
*     - Called just after all Task executors are ran.
*
*   Returns:
*     Always '0'.
*/
s32     CCL_Analyze( void );

/****** Colli Search ****************************************************************/
/*
*   Description:
*     Clear the current colli search data.
*/
void    CCL_ClearSearch( void );

/****** Init ************************************************************************/
/*
*   Description:
*     Initiate collision info on a Task and allocate its collision work.
*
*   Parameters:
*     - tp          : task pointer
*     - info        : collision info list
*     - nbInfo      : collision info count
*     - id          : collision id                                        [CID_###]
*
*   Returns:
*     'TRUE' on success; or 'FALSE' on failure.
*/
b32     CCL_Init( task* tp, CCL_INFO* info, s32 nbInfo, u8 id );

/****** Register ********************************************************************/
/*
*   Description:
*     Register Task for collision calculations at the end of this execution frame.
*   The collision work info is cleared when calling, all collision checks for this
*   frame should be performed before this.
*
*   Notes:
*     - Internally calls 'CCL_ClearInfo'
*
*   Parameters:
*     - tp          : task pointer
*/
void    CCL_Entry( task* tp );

/****** Reset ***********************************************************************/
/*
*   Description:
*     Clear all collision work info.
*
*   Parameters:
*     - tp          : task pointer
*/
void    CCL_ClearInfo( task* tp );

/****** Colli Switch ****************************************************************/
/*
*   Description:
*     Enable a collision info entry on a Task.
*
*   Notes:
*     - All collisions are enabled by default
*
*   Parameters:
*     - tp          : task pointer
*     - info_num    : 'CCL_INFO' index number
*/
void    CCL_Enable( task* tp, s32 info_num );
/*
*   Description:
*     Disable a collision info entry on a Task.
*
*   Parameters:
*     - tp          : task pointer
*     - info_num    : 'CCL_INFO' index number
*/
void    CCL_Disable( task* tp, s32 info_num );

/****** Get Hit *********************************************************************/
/*
*   Description:
*     Get a Task via collision hit with a specific collision type. Multiple calls,
*   in sequence, will return different collision hit entries, up to 16. When a
*   'nullptr' is returned, that is the final registered hit.
*
*   Notes:
*     - To reset collision search info, call 'CCL_ClearSearch'
*
*   Examples:
*     - CCL_IsHitKind( tp, CI_KIND_OSAMPO ); // returns first hit of kind 'OSAMPO'
*       CCL_IsHitKind( tp, CI_KIND_OSAMPO ); // returns second hit
*       CCL_IsHitKind( tp, CI_KIND_OSAMPO ); // returns third hit, etc
*
*   Parameters:
*     - tp          : task pointer
*     - kind        : collision info type
*
*   Returns:
*     Pointer to hit Task; or 'nullptr' when no hit is found.
*/
task*   CCL_IsHitKind( task* tp, u8 kind );
/*
*   Description:
*     Get a collision hit info with a specific collision type. Multiple calls,
*   in sequence, will return different collision hit entries, up to 16. When a
*   'nullptr' is returned, that is the final registered hit.
*
*   Notes:
*     - To reset collision search info, call 'CCL_ClearSearch'
*
*   Examples:
*     - CCL_IsHitKindEx( tp, CI_KIND_OSAMPO ); // returns first hit of kind 'OSAMPO'
*       CCL_IsHitKindEx( tp, CI_KIND_OSAMPO ); // returns second hit
*       CCL_IsHitKindEx( tp, CI_KIND_OSAMPO ); // returns third hit, etc
*
*   Parameters:
*     - tp          : task pointer
*     - kind        : collision info type
*
*   Returns:
*     Pointer to hit info; or 'nullptr' when no hit is found.
*/
CCL_HIT_INFO* CCL_IsHitKindEx( task* tp, u8 kind );

/****** Check Flag ******************************************************************/
/*
*   Description:
*     Check if Task was pushed via the 'PUSHED' flag.
*
*   Parameters:
*     - tp          : task pointer
*
*   Returns:
*     'TRUE' if Task has been pushed; or 'FALSE' if not.
*/
b32     CCL_IsPushed( const task* tp );

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS

/****** Standard ********************************************************************/
#define CCL_Analyze_p           FUNC_PTR(s32          , __cdecl, (void)     , 0x00486190)
#define CCL_IsHitKindEx_p       FUNC_PTR(CCL_HIT_INFO*, __cdecl, (task*, u8), 0x00486760)

/****** Usercall ********************************************************************/
#define CCL_Init_p              ((void*)0x0047E520)/* EAX(EAX,STK,STK,STK)          */
#define CCL_Entry_p             ((void*)0x0047E750)/* ###(ESI)                      */
#define CCL_ClearInfo_p         ((void*)0x0047E6C0)/* ###(EAX)                      */
#define CCL_Enable_p            ((void*)0x00486CD0)/* ###(EAX,ECX)                  */
#define CCL_Disable_p           ((void*)0x00486D00)/* ###(EAX,ECX)                  */

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_CCOLLI*/
