/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/c_colli.h'
*
*   Description:
*     The core collision system.
*
*   Notes:
*     - All of the 'IsHit' functions can be called multiple times in sequence. This will return
*       different collision hit entries, up to 16. When a 'nullptr' is returned, that is the
*       final registered hit.
*     - To reset collision search info, call 'CCL_ClearSearch'
*
*   Examples:
*     - CCL_IsHitKind( tp, CI_KIND_OSAMPO ); // returns first hit of kind 'OSAMPO'
*       CCL_IsHitKind( tp, CI_KIND_OSAMPO ); // returns second hit
*       CCL_IsHitKind( tp, CI_KIND_OSAMPO ); // returns third hit, etc
*/
#ifndef H_SA2B_CCOLLI
#define H_SA2B_CCOLLI

/********************************/
/*  Includes                    */
/********************************/
/****** Self ************************************************************************************/
#include <samt/sonic/c_colli/ccl_info.h> /* ccl info                                            */

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** Task ************************************************************************************/
typedef struct task                 task;   /* task                                             */
typedef struct taskwk               taskwk; /* task work                                        */

/********************************/
/*  Constants                   */
/********************************/
/****** Colli Flags *****************************************************************************/
#define CF_HIT                      (0x0000'0001) /* is hit                                     */
#define CF_PUSHED                   (0x0000'0010) /* is pushed                                  */
#define CF_HURT                     (0x0000'0020) /* is hurt                                    */
#define CF_HOMING                   (0x0000'0040) /* allow player homing attack                 */

/****** Colli Info Type *************************************************************************/
enum
{
    CI_KIND_OSAMPO          = 0x01, /* chao osanpo/odekake machine                              */
    CI_KIND_PATTING_HAND,           /* patting hand                                             */
    CI_KIND_SAPLING,                /* sapling                                                  */
    CI_KIND_SAPLING_FIELD,          /* sapling area                                             */
    CI_KIND_KAME_FIELD,             /* turtle area                                              */
    CI_KIND_ENEMYBALL,              /* enemy ball                                               */
    CI_KIND_PUNCH,                  /* punch                                                    */
    CI_KIND_2PLASER,                /* 2P laser                                      (& bosses) */
    CI_KIND_2PSHOTS,                /* 2P shots                                      (& bosses) */
    CI_KIND_2PMISSILES,             /* 2P missiles                                   (& bosses) */
    CI_KIND_NO_RIDE,                /* no ride                                                  */
    CI_KIND_NO_PUNCH,               /* no punch                                                 */
    CI_KIND_NO_LOCKON,              /* no lock-on                                               */
    CI_KIND_NO_CATCH,               /* no catch                                                 */
    CI_KIND_DO_CATCH,               /* do catch                                                 */
    CI_KIND_NO_COLLIDE,             /* no collide                                               */
    CI_KIND_G_CYLINDER,             /* gravity cylinder                                         */
    CI_KIND_NO_HOLD_FIELD,          /* no hold area                                             */
    CI_KIND_BOMB_EXPLOSION,         /* bomb explosion                                           */
    CI_KIND_CHAOSDRIVE,             /* chaos drive                                              */

    CI_KIND_DUMMY           = 0x40, /* dummy kind                                               */
};

/****** Colli Info Form *************************************************************************/
enum
{
    CI_FORM_SPHERE,                 /* sphere form                                              */
    CI_FORM_CYLINDER,               /* cylinder form                                            */
    CI_FORM_CYLINDER2,              /* cylinder 2 form                                          */
    CI_FORM_RECTANGLE,              /* rectangle form                                           */
    CI_FORM_RECTANGLE2,             /* rectangle 2 form                                         */
    CI_FORM_RECTANGLE3,             /* rectangle 3 form                                         */
    CI_FORM_CAPSULE,                /* capsule form                                             */
    CI_FORM_PERSON,                 /* person form                                              */
    CI_FORM_LINE,                   /* line form                                                */
    CI_FORM_WALL_PLANE,             /* wall plane form                                          */
    CI_FORM_WALL_CIRCLE             /* wall circle form                                         */
};

/****** Colli Info Push *************************************************************************/
#define CIF_PUSH_NONE               (0x0000'0000) /* no flags                                   */
// Push, Push Out
#define CIF_PPO_PLAYER              (0x0000'0001) /* object push out player and chao            */
#define CIF_PPO_ENEMY               (0x0000'0002) /* object push out enemy                      */
#define CIF_PPO_OBJECT              (0x0000'0004) /* object push out object                     */
#define CIF_PPO_ITEM                (0x0000'0008) /* object push out item                       */
// Push, THrough
#define CIF_PTH_PLAYER              (0x0000'0010) /* player and chao cannot push object         */
#define CIF_PTH_ENEMY               (0x0000'0020) /* enemy cannot push object                   */
#define CIF_PTH_OBJECT              (0x0000'0040) /* object cannot push object                  */
#define CIF_PTH_ITEM                (0x0000'0080) /* item cannot push object                    */

/****** Colli Info Damage ***********************************************************************/
#define CIF_DMG_NONE                (0x0000'0000) /* no flags                                   */

#define CIF_DMG_ATK_SHIFT           (0) /* attack shift                                         */
#define CIF_DMG_DEF_SHIFT           (2) /* defense shift                                        */

#define CIF_DMG_ATK_MASK            (0x03<<CIF_DMG_ATK_SHIFT) /* attack mask                    */
#define CIF_DMG_DEF_MASK            (0x03<<CIF_DMG_DEF_SHIFT) /* defense mask                   */

#define CIF_DMG_PLAYER              (0x0000'0020) /* damage player and chao                     */
#define CIF_DMG_ENEMY               (0x0000'0040) /* damage enemy                               */
#define CIF_DMG_OBJECT              (0x0000'0080) /* damage object                              */

/****** Colli Info Attr *************************************************************************/
#define CIF_ATTR_NONE               (0x0000'0000) /* no flags                                   */

#define CIF_ATTR_NOOUT              (0x0000'0004) /* cannot send info to other objects          */
#define CIF_ATTR_NOIN               (0x0000'0008) /* cannot recive object collision info        */
#define CIF_ATTR_UNK40              (0x0000'0040) /* unknown                                    */
#define CIF_ATTR_UNK80              (0x0000'0080) /* unknown                                    */
#define CIF_ATTR_NOPUSH             (0x0000'4000) /* cannot be pushed                           */
#define CIF_ATTR_NOPLAYER           (0x0004'0000) /* cannot collide player                      */
#define CIF_ATTR_NOENEMY            (0x0008'0000) /* cannot collide enemy                       */
#define CIF_ATTR_NOOBJECT           (0x0010'0000) /* cannot collide object                      */
#define CIF_ATTR_NOITEM             (0x0020'0000) /* cannot collide item                        */
#define CIF_ATTR_NOCHAO             (0x0040'0000) /* cannot collide chao                        */

/****** Colli Info ID ***************************************************************************/
enum
{
    CID_PLAYER,                     /* player id                                                */
    CID_BULLET,                     /* bullet id                                                */
    CID_ENEMY,                      /* enemy id                                                 */
    CID_ENEMY2,                     /* enemy 2 id                                               */
    CID_OBJECT,                     /* object id                                                */
    CID_OBJECT2,                    /* object 2 id                                              */
    CID_ITEM,                       /* item id                                                  */
    CID_ITEM2,                      /* item 2 id                                                */
    CID_WALL,                       /* wall id                                                  */
    CID_CHAO,                       /* chao world id                                            */
};

#ifdef SAMT_INCL_INTERNAL

/****** Entry Maximum ***************************************************************************/

#define CID_PLAYER_MAX              (16)  /* player entry                                       */
#define CID_BULLET_MAX              (128) /* bullet entry                                       */
#define CID_ENEMY_MAX               (128) /* enemy entry                                        */
#define CID_ENEMY2_MAX              (128) /* enemy 2 entry                                      */
#define CID_OBJECT_MAX              (512) /* object entry                                       */
#define CID_OBJECT2_MAX             (128) /* object 2 entry                                     */
#define CID_ITEM_MAX                (128) /* item entry                                         */
#define CID_ITEM2_MAX               (128) /* item 2 entry                                       */
#define CID_WALL_MAX                (256) /* wall entry                                         */
#define CID_CHAO_MAX                (16)  /* chao world entry                                   */

#endif/*SAMT_INCL_INTERNAL*/

/********************************/
/*  Structures                  */
/********************************/
/****** Colli Hit Info **************************************************************************/
typedef struct c_colli_hit_info
{
    i8              my_num;         /* my hit colli info index                                  */
    i8              hit_num;        /* their hit colli info index                               */
    u16             flag;           /* their flags                                              */
    task*           hit_tp;         /* their task pointer                                       */
}
CCL_HIT_INFO;

/****** Colli Work ******************************************************************************/
typedef struct colliwk
{
    u16             id;             /* colli id                                                 */
    i16             nbHit;          /* colli hit number                                         */
    u16             flag;           /* colli flags                                              */
    u16             nbInfo;         /* colli info count                                         */
    f32             colli_range;    /* colli range                                              */
    CCL_INFO*       info;           /* colli info list                                          */
    CCL_HIT_INFO    hit_info[16];   /* colli hit info list                                      */
    NJS_POINT3      normal;         /* colli normal                                             */
    task*           mytask;         /* task pointer to this task                                */
    i16             my_num;         /* my colli info index                                      */
    i16             hit_num;        /* hit colli info index                                     */
    struct colliwk* hit_cwp;        /* hit colli work                                           */
}
colliwk;

#ifdef SAMT_INCL_INTERNAL

/****** Colli Search ****************************************************************************/
typedef struct
{
    task*           pTask;          /* last search task                                         */
    void*           FuncAddr;       /* last search function                                     */
    i32             CurrNum;        /* current hit info number                                  */
    i32             Kind;           /* last search colli type                                   */
}
CCL_SEARCH;

#endif/*SAMT_INCL_INTERNAL*/

/********************************/
/*  Game Defs                   */
/********************************/
#ifdef SAMT_INCL_INTERNAL

/****** Colli Search ****************************************************************************/
#define Search                      DATA_REF(CCL_SEARCH, 0x019468A0)

/****** Entry Lists *****************************************************************************/
#define player_entry_list           DATA_ARY(task*, 0x01946660, [CID_PLAYER_MAX])
#define bullet_entry_list           DATA_ARY(task*, 0x019466A0, [CID_BULLET_MAX])
#define enemy_entry_list            DATA_ARY(task*, 0x01DE4EE0, [CID_ENEMY_MAX])
#define enemy2_entry_list           DATA_ARY(task*, 0x01DE6DA0, [CID_ENEMY2_MAX])
#define object_entry_list           DATA_ARY(task*, 0x01945E18, [CID_OBJECT_MAX])
#define object2_entry_list          DATA_ARY(task*, 0x019468B8, [CID_OBJECT2_MAX])
#define item_entry_list             DATA_ARY(task*, 0x01946AC8, [CID_ITEM_MAX])
#define item2_entry_list            DATA_ARY(task*, 0x01946CC8, [CID_ITEM2_MAX])
#define wall_entry_list             DATA_ARY(task*, 0x01945A08, [CID_WALL_MAX])
#define chao_entry_list             DATA_ARY(task*, 0x01946618, [CID_CHAO_MAX])

/****** Flag Tables *****************************************************************************/

#define flagtbl_ppo                 DATA_ARY(i8, 0x0171B2C4, [10])
#define flagtbl_pth                 DATA_ARY(i8, 0x0171B7E4, [10])

#endif/*SAMT_INCL_INTERNAL*/

/********************************/
/*  Prototypes                  */
/********************************/
/****** Execute *********************************************************************************/
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
i32     CCL_Analyze( void );

/****** Search ***********************************************************************************/
/*
*   Description:
*     Clear the current colli search data.
*/
void    CCL_ClearSearch( void );

/****** Init *************************************************************************************/
/*
*   Description:
*     Init collision info on a Task and allocate its collision work.
*
*   Parameters:
*     - tp          : object
*     - info        : collision info list
*     - nbInfo      : collision info count
*     - id          : collision id                                        [CID_###]
*
*   Returns:
*     'TRUE' on success; or 'FALSE' on failure.
*/
b32     CCL_Init( task* tp, CCL_INFO* info, i32 nbInfo, u8 id );
/*
*   Description:
*     Init collision info on a Task and allocate its collision work, but do not allocate memory
*   for copy of collision info array. In other words, share the array among all objects.
*
*   Parameters:
*     - tp          : object
*     - info        : collision info list
*     - nbInfo      : collision info count
*     - id          : collision id                                        [CID_###]
*
*   Returns:
*     'TRUE' on success; or 'FALSE' on failure.
*/
b32     CCL_InitShare( task* tp, CCL_INFO* info, i32 nbInfo, u8 id );

/****** Register *********************************************************************************/
/*
*   Description:
*     Register Task for collision calculations at the end of this execution frame.
*
*   Notes:
*     - Internally calls 'CCL_ClearInfo'. Collision checks should be done before calling.
*
*   Parameters:
*     - tp          : object
*/
void    CCL_Entry( task* tp );

/****** Clear Info ******************************************************************************/
/*
*   Description:
*     Clear all collision work info.
*
*   Parameters:
*     - tp          : object
*/
void    CCL_ClearInfo( task* tp );

/****** Colli Switch *****************************************************************************/
/*
*   Description:
*     Enable a collision info entry on a Task.
*
*   Notes:
*     - All collisions are enabled by default
*
*   Parameters:
*     - tp          : object
*     - info_num    : info index
*/
void    CCL_Enable( task* tp, i32 info_num );
/*
*   Description:
*     Disable a collision info entry on a Task.
*
*   Parameters:
*     - tp          : object
*     - info_num    : info index
*/
void    CCL_Disable( task* tp, i32 info_num );

/****** Get Info *********************************************************************************/
/*
*   Description:
*     Get collision info of object.
*
*   Parameters:
*     - tp          : object
*     - info_num    : info index
*
*   Returns:
*     Collision info; or 'nullptr' on failure.
*/
CCL_INFO* CCL_GetInfo( task* tp, i32 info_num );

/****** Check Flag *******************************************************************************/
/*
*   Description:
*     Is object hit.
*
*   Parameters:
*     - tp          : task pointer
*
*   Returns:
*     'TRUE' if object hit; or 'FALSE' if not.
*/
b32     CCL_IsHit( const task* tp );
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

/****** Hit Number ******************************************************************************/
/*
*   Description:
*     Get number of collision hits.
*
*   Parameters:
*     - tp          : task pointer
*
*   Returns:
*     Number of collision hits.
*/
i32     CCL_GetHitCount( const task* tp );

/****** Is Hit **********************************************************************************/
/*
*   Description:
*     Get a player collision hit.
*
*   Parameters:
*     - tp          : task pointer
*
*   Returns:
*     Hit player; or 'nullptr' when no hit is found.
*/
task*   CCL_IsHitPlayer( task* tp );
/*
*   Description:
*     Get a bullet collision hit.
*
*   Parameters:
*     - tp          : task pointer
*
*   Returns:
*     Hit bullet; or 'nullptr' when no hit is found.
*/
task*   CCL_IsHitBullet( task* tp );
/*
*   Description:
*     Get a enemy collision hit.
*
*   Parameters:
*     - tp          : task pointer
*
*   Returns:
*     Hit enemy; or 'nullptr' when no hit is found.
*/
task*   CCL_IsHitEnemy( task* tp );
/*
*   Description:
*     Get a object collision hit.
*
*   Parameters:
*     - tp          : task pointer
*
*   Returns:
*     Hit object; or 'nullptr' when no hit is found.
*/
task*   CCL_IsHitObject( task* tp );
/*
*   Description:
*     Get a collision hit with a specific collision type.
*
*   Parameters:
*     - tp          : task pointer
*     - kind        : collision info type
*
*   Returns:
*     Hit object; or 'nullptr' when no hit is found.
*/
task*   CCL_IsHitKind( task* tp, u8 kind );

/****** Is Hit w Num ****************************************************************************/
/*
*   Description:
*     Get a player collision hit, with info index.
*
*   Parameters:
*     - tp          : task pointer
*     - info_num    : info index
*
*   Returns:
*     Hit player; or 'nullptr' when no hit is found.
*/
task*   CCL_IsHitPlayerWithNum( task* tp, i32 info_num );
/*
*   Description:
*     Get a collision hit with a specific collision type, with info index.
*
*   Parameters:
*     - tp          : task pointer
*     - info_num    : info index
*     - kind        : collision info type
*
*   Returns:
*     Hit object; or 'nullptr' when no hit is found.
*/
task*   CCL_IsHitKindWithNum( task* tp, i32 info_num, u8 kind );

/****** Is Hit Ex *******************************************************************************/
/*
*   Description:
*     Get a player collision hit info.
*
*   Parameters:
*     - tp          : task pointer
*
*   Returns:
*     Hit info; or 'nullptr' when no hit is found.
*/
CCL_HIT_INFO* CCL_IsHitPlayerEx( task* tp );
/*
*   Description:
*     Get a bullet collision hit info.
*
*   Parameters:
*     - tp          : task pointer
*
*   Returns:
*     Hit info; or 'nullptr' when no hit is found.
*/
CCL_HIT_INFO* CCL_IsHitBulletEx( task* tp );
/*
*   Description:
*     Get a enemy collision hit info.
*
*   Parameters:
*     - tp          : task pointer
*
*   Returns:
*     Hit info; or 'nullptr' when no hit is found.
*/
CCL_HIT_INFO* CCL_IsHitEnemyEx( task* tp );
/*
*   Description:
*     Get a object collision hit info.
*
*   Parameters:
*     - tp          : task pointer
*
*   Returns:
*     Hit info; or 'nullptr' when no hit is found.
*/
CCL_HIT_INFO* CCL_IsHitObjectEx( task* tp );
/*
*   Description:
*     Get a collision hit info with a specific collision type.
*
*   Parameters:
*     - tp          : task pointer
*     - info_num    : info index
*     - kind        : collision info type
*
*   Returns:
*     Hit info; or 'nullptr' when no hit is found.
*/
CCL_HIT_INFO* CCL_IsHitKindEx( task* tp, u8 kind );

/****** Is Hit w Num Ex *************************************************************************/
/*
*   Description:
*     Get a player collision hit info, with info index.
*
*   Parameters:
*     - tp          : task pointer
*     - info_num    : info index
*
*   Returns:
*     Hit info; or 'nullptr' when no hit is found.
*/
CCL_HIT_INFO* CCL_IsHitPlayerWithNumEx( task* tp, i32 info_num );
/*
*   Description:
*     Get a collision hit info with a specific collision type.
*
*   Parameters:
*     - tp          : task pointer
*     - info_num    : info index
*     - kind        : collision info type
*
*   Returns:
*     Hit info; or 'nullptr' when no hit is found.
*/
CCL_HIT_INFO* CCL_IsHitKindWithNumEx( task* tp, i32 info_num, u8 kind );

#ifdef SAMT_INCL_INTERNAL

/****** Check ***********************************************************************************/
/*
*   Description:
*     Check if object is a nearby player homing target, and add it to homing list.
*
*   Parameters:
*     - twp1        : player task work
*     - twp2        : homing object
*     - dist2       : distance from twp1 to twp2
*/
void    CCL_CheckHoming( taskwk* twp1, taskwk* twp2, f32 dist2 );
/*
*   Description:
*     Check if two objects are within collision range.
*
*   Parameters:
*     - tp1,tp2     : objects
*
*   Returns:
*     'TRUE' if objects in range; 'FALSE' if not.
*/
b32     CCL_CheckColliRange( task* tp1, task* tp2 );
/*
*   Description:
*     Check if object should be pushed by another object, and apply pushed flag.
*
*   Notes:
*     - Assumes objects have already hit, and also applies hit flag.
*
*   Parameters:
*     - cwp1        : object
*     - info1       : object collision info
*     - cwp2        : hit object
*     - info2       : hit object collision info
*
*   Returns:
*     'TRUE' if object pushed by hit object; 'FALSE' if not.
*/
b32     CCL_CheckPushOut( colliwk* cwp1, CCL_INFO* info1, const colliwk* cwp2, const CCL_INFO* info2 );

#endif/*SAMT_INCL_INTERNAL*/

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Pointers           */
/********************************/
/****** Function Pointers ***********************************************************************/
#define CCL_Analyze_p               FUNC_PTR(i32          , __cdecl, (void)        , 0x00486190)
#define CCL_IsHitPlayerEx_p         FUNC_PTR(CCL_HIT_INFO*, __cdecl, (task*)       , 0x00486520)
#define CCL_IsHitBulletEx_p         FUNC_PTR(CCL_HIT_INFO*, __cdecl, (task*)       , 0x004865B0)
#define CCL_IsHitEnemyEx_p          FUNC_PTR(CCL_HIT_INFO*, __cdecl, (task*)       , 0x00486640)
#define CCL_IsHitObjectEx_p         FUNC_PTR(CCL_HIT_INFO*, __cdecl, (task*)       , 0x004866E0)
#define CCL_IsHitKindEx_p           FUNC_PTR(CCL_HIT_INFO*, __cdecl, (task*,u8)    , 0x00486760)
#define CCL_IsHitPlayerWithNumEx_p  FUNC_PTR(CCL_HIT_INFO*, __cdecl, (task*,i32)   , 0x00486800)
#define CCL_IsHitKindWithNumEx_p    FUNC_PTR(CCL_HIT_INFO*, __cdecl, (task*,i32,u8), 0x00486880)

/****** Usercall Pointers ***********************************************************************/
#define CCL_Init_p                  0x0047E520 /* EAX(EAX,STK,STK,STK)                          */
#define CCL_InitShare_p             0x0047E620 /* EAX(EDI,STK,STK, BL)                          */
#define CCL_Entry_p                 0x0047E750 /* ###(ESI)                                      */
#define CCL_ClearInfo_p             0x0047E6C0 /* ###(EAX)                                      */
#define CCL_CheckHoming_p           0x0047E960 /* ###(ECX,EDX,STK)                              */
#define CCL_CheckColliRange_p       0x0047EA90 /* EAX(EAX,EDX)                                  */
#define CCL_CheckPushOut_p          0x0047EB30 /* EAX(EAX,EDX,ECX,EDI)                          */
#define CCL_Enable_p                0x00486CD0 /* ###(EAX,ECX)                                  */
#define CCL_Disable_p               0x00486D00 /* ###(EAX,ECX)                                  */

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_CCOLLI*/
