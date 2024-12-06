/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_misc.h'
*
*   Description:
*     Misc enums, structs, and functions for Chao World.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SA2B_CHAO_MISC
#define H_SA2B_CHAO_MISC

/************************/
/*  External Includes   */
/************************/
/****** Ninja ***********************************************************************/
#include <sa2b/ninja/njcommon.h> /* ninja common                                    */

/************************/
/*  External Opaques    */
/************************/
/****** Ninja ***********************************************************************/
typedef struct cnkobj           NJS_CNK_OBJECT; /* chunk object                     */

/****** Game ************************************************************************/
typedef struct task             task;          /* task                              */
typedef struct _OBJ_EDITTABLE   OBJ_EDITTABLE; /* edit table                        */

EXTERN_START

/************************/
/*  Enums               */
/************************/
/****** Collision Kind **************************************************************/
enum
{
    CI_KIND_AL_CHAO     = 0x81, /* chao                                             */
    CI_KIND_AL_CHAO_FIELD,      /* chao area                                        */
    CI_KIND_AL_FRUIT,           /* fruit                                            */
    CI_KIND_AL_FRUIT_FIELD,     /* fruit area                                       */
    CI_KIND_AL_SEED,            /* tree seed                                        */
    CI_KIND_AL_SEED_FIELD,      /* tree seed area                                   */
    CI_KIND_AL_MINIMAL,         /* minimal                                          */
    CI_KIND_AL_MINIMAL_FIELD,   /* minimal area                                     */
    CI_KIND_AL_TREE,            /* growtree                                         */
    CI_KIND_AL_TREE_FIELD,      /* growtree area                                    */
    CI_KIND_AL_TOY,             /* chao toy                                         */
    CI_KIND_AL_TOY_FIELD,       /* chao toy area                                    */
    CI_KIND_AL_EGG,             /* chao egg                                         */
    CI_KIND_AL_EGG_FIELD,       /* chao egg area                                    */
    CI_KIND_AL_TRASH,           /* trash                                            */
    CI_KIND_AL_TRASH_FIELD,     /* trash area                                       */
    CI_KIND_AL_DAKKO_FIELD,     /* hug area                                         */
    CI_KIND_AL_NADE_FIELD,      /* nade area                                        */
    CI_KIND_AL_OBAKE_HEAD,      /* chao mask                                        */
    CI_KIND_AL_CDR,             /* chaos drive                                      */
    CI_KIND_AL_PUNCH,           /* punch                                            */
    CI_KIND_AL_SHADOW,          /* chao shadow casting area                         */
    CI_KIND_AL_ONARA,           /* fart                                             */
    CI_KIND_AL_SOUND,           /* sound                                            */
    CI_KIND_AL_HELLO,           /* player hello                                     */
    CI_KIND_AL_TOBIKOMI,        /* diving area                                      */
    CI_KIND_AL_REQUEST_WATER,   /* request water                                    */
    CI_KIND_AL_NOISE,           /* noise                                            */
    CI_KIND_AL_CONTACT,         /* contact                                          */
    CI_KIND_AL_ACTION,          /* action                                           */
    CI_KIND_AL_SONG,            /* song                                             */
    CI_KIND_AL_BALL,            /* ball garden toy                                  */
    CI_KIND_AL_FIRE,            /* fire                                             */
    CI_KIND_AL_BIKKURI,         /* surprise                                         */
    CI_KIND_AL_BOX,             /* box garden toy                                   */
    CI_KIND_AL_WALL,            /* wall                                             */
    CI_KIND_AL_RANDOM_MUSIC,    /* random chao band event                           */
    CI_KIND_AL_DANCE,           /* dance                                            */
    CI_KIND_AL_SING,            /* sing                                             */
    CI_KIND_AL_SING_ONCHI,      /* sing badly                           (tone deaf) */
    CI_KIND_AL_RAKUGAKI,        /* grafitti                                         */
    CI_KIND_AL_FINISH,          /* finish                                           */
    CI_KIND_AL_NEST,            /* chao mating nest                                 */
    CI_KIND_AL_PLANT_POS,       /* seed planting position                           */
    CI_KIND_AL_WATER,           /* watering area                                    */
    CI_KIND_AL_THIRSTY,         /* growtree want water                              */
    CI_KIND_AL_TOUCH,           /* touch                                            */
    CI_KIND_AL_SWITCH,          /* switch                                           */
    CI_KIND_AL_CHANGE,          /* change                                           */

    CI_KIND_AL_SET_RACE_TREE,         /* race tree                                  */
    CI_KIND_AL_SET_RACE_GLIDE,        /* race glide                                 */
    CI_KIND_AL_SET_RACE_JUMP,         /* race jump                                  */
    CI_KIND_AL_SET_RACE_LAKE,         /* race lake                                  */
    CI_KIND_AL_SET_RACE_KARIMONO,     /* race borrow                                */
    CI_KIND_AL_SET_RACE_KOWAI,        /* race scared                                */
    CI_KIND_AL_SET_RACE_GOAL,         /* race goal                                  */
    CI_KIND_AL_SET_RACE_ENABLE_TURN,  /* race enable turning                        */
    CI_KIND_AL_SET_RACE_ALONG_LANE,   /* race along lane                            */
    CI_KIND_AL_SET_RACE_REMEMBER_POS, /* race remember position                     */
    CI_KIND_AL_SET_RACE_THINK_POS,    /* race think                                 */
    CI_KIND_AL_SET_RACE_PARALLEL,     /* race parallel                              */
    CI_KIND_AL_SET_RACE_GOAL_BANZAI,  /* race goal celebrate                        */
    CI_KIND_AL_SET_RACE_PATHCOLLI,    /* race path                                  */
    CI_KIND_AL_SET_RACE_POLYCOLLI,    /* race poly                                  */
    CI_KIND_AL_SET_RACE_EACHCOLLI,    /* race each                                  */

    CI_KIND_AL_LOG,                 /* race log                                     */
    CI_KIND_AL_ROCK,                /* quiz falling rock                            */
    CI_KIND_AL_HOLL,                /* race pitfall                                 */
    CI_KIND_AL_KANI,                /* race crabs                                   */
    CI_KIND_AL_ANSWER_POS,          /* quiz answer set position                     */
    CI_KIND_AL_ANSWER_OBJ,          /* quiz answer object                           */
    CI_KIND_AL_GOOD,                /* good (?)                                     */
    CI_KIND_AL_TV,                  /* tv garden toy area                           */
    CI_KIND_AL_RADICASE,            /* radio garden toy area                        */
    CI_KIND_AL_CLIMB,               /* chao climb area                              */
    CI_KIND_AL_FURIMUKI,            /* turn around area                             */
    CI_KIND_AL_STAGE_CHANGER,       /* change stage                                 */

    CI_KIND_END         = 0xFF,     /* end count                                    */
};

/************************/
/*  Structures          */
/************************/
/****** Angle 3 *********************************************************************/
typedef struct
{
    uint16_t x, y, z;
}
SAngle3, USAngle3;

/************************/
/*  Data                */
/************************/
#ifdef SAMT_INCL_INTERNAL

/****** Screen Scale ****************************************************************/
#define OnScreenScale           (500.f)

#endif/*SAMT_INCL_INTERNAL*/

/************************/
/*  Prototypes          */
/************************/
/****** Is On Screen ****************************************************************/
/*
*   Description:
*     Calculate if a task is on the screen, with 2 parameters.
*
*   Notes:
*     - Calls 'IsOnScreen3' with 'radius' as the 'HalfHeight' argument.
*
*   Parameters:
*     - tp          : task pointer
*     - radius      : size of the task as a radius
*     - OffsetY     : y position offset from task center
*
*   Returns:
*     'true' if the task is on the screen; or 'false' if it is not.
*/
b32     AL_IsOnScreen2( const task* tp, f32 radius, f32 OffsetY );
/*
*   Description:
*     Calculate if a task is on the screen, with 3 parameters.
*
*   Parameters:
*     - tp          : task pointer
*     - radius      : size of the task as a radius
*     - HalfHeight  : vertical size of the task as a radius
*     - OffsetY     : y position offset from task center
*
*   Returns:
*     'true' if the task is on the screen; or 'false' if it is not.
*/
b32     AL_IsOnScreen3( const task* tp, f32 radius, f32 HalfHeight, f32 OffsetY );

/****** Set File ********************************************************************/
/*
*   Description:
*     Loads '_s' & '_u' set files from one name into an allocated Edit Table. The
*   allocated Edit Table must be freed using 'syFree'.

*   Notes:
*     - Internally calls 'LoadSetFileEx', with 'objnum' argument set to '512'. 
*
*   Examples:
*     - AL_LoadSetFile("set_chao_hero.bin");
*     - AL_LoadSetFile("set_chao_neut");
*
*   Parameters:
*     - set_name : name of the set files exluding '_s' & '_u'. Any extension is
*                  optional & trimmed away
*
*   Returns:
*     Allocated SET Edit Table pointer.
*/
OBJ_EDITTABLE* AL_LoadSetFile( const char* set_name );

/****** Interpolate Angle ***********************************************************/
/*
*   Description:
*     Interpolate two Angle3's at a set ratio.
*
*   Notes:
*     - 'pAnswer' can be 'pAng1' or 'pAng2'
*
*   Parameters:
*     - pAng1       : angle3 1
*     - pAng2       : angle3 2
*     - pAnswer     : result angle3 to be written to
*     - ratio       : ratio of ang 1 to ang 2                                 [0~1]
*/
void    AL_InterpolateAngle( const Angle3* pAng1, const Angle3* pAng2, Angle3* pAnswer, f32 ratio );
/*
*   Description:
*     Interpolate two SAngle3's at a set ratio.
*
*   Notes:
*     - 'pAnswer' can be 'pAng1' or 'pAng2'
* 
*   Parameters:
*     - pAng1       : sangle3 1
*     - pAng2       : sangle3 2
*     - pAnswer     : result sangle3 to be written to
*     - ratio       : ratio of angle 1 to angle 2                             [0~1]
*/
void    AL_InterpolateSAngle( const SAngle3* pAng1, const SAngle3* pAng2, SAngle3* pAnswer, f32 ratio );

/****** Interpolate Object **********************************************************/
/*
*   Description:
*     Interpolate two Ninja Chunk objects at a set ratio. Only the object's
*   translation info and their model's 'vlist' data are interpolated; 'plist' data
*   is not read. Object 1 and 2 must structurally match, excluding 'plist' data.
*     The 'answer' object dictates if models, children, and siblings are
*   interpolated. For example: if 'answer' has no model but the objects do, then
*   the model will be skipped and not interpolated. Alternatively, if 'answer' does
*   have a model but the objects do not, a 'nullptr' crash will occur.
*
*   Notes:
*     - 'pAnswer' can be 'pObj1' or 'pObj2'
*
*   Parameters:
*     - pObj1       : ninja chunk object 1
*     - pObj2       : ninja chunk object 2
*     - pAnswer     : result object to be written to
*     - ratio       : ratio of object 1 to object 2                           [0~1]
*/
void    AL_InterpolateObject( const NJS_CNK_OBJECT* pObj1, const NJS_CNK_OBJECT* pObj2, NJS_CNK_OBJECT* pAnswer, f32 ratio );

/****** Calculate Task **************************************************************/
/*
*   Description:
*     Calculate horizontal angle between two tasks from the perspective of
*   'pMyTask'.
*
*   Notes:
*     - Calculated angle is in world space, not local to 'pMyTask'.
*
*   Parameters:
*     - pMyTask     : perspective task with 'taskwk' compatible data
*     - pTargetTask : target task with 'taskwk' compatible data
*
*   Returns:
*     Horizontal angle between the given tasks.
*/
Angle   AL_CalcTaskAngle( const task* pMyTask, const task* pTargetTask );
/*
*   Description:
*     Calculate the distance between two tasks.
*
*   Parameters:
*     - pMyTask     : task with 'taskwk' compatible data 1
*     - pTargetTask : task with 'taskwk' compatible data 2
*
*   Returns:
*     Distance in 3D space between the given tasks.
*/
f32     AL_CalcDistFromTask( const task* pMyTask, const task* pTargetTask );

/****** Interpolate Angle ***********************************************************/
/*
*   Description:
*     Set X and Z acceleration parameters in a Task's 'MOVE_WORK' in the direction
*   of its forward facing vector.
*
*   Parameters:
*     - tp          : task with 'MOVE_WORK' compatible data
*     - acc         : acceleration value to set
*/
void    AL_ForwardAcc( task* tp, f32 acc );
/*
*   Description:
*     Move X and Z position parameters of a Task's 'taskwk' in the direction of its
*   forward facing vector.
*
*   Parameters:
*     - tp          : task with 'taskwk' compatible data
*     - spd         : amount to move task
*/
void    AL_ForwardSpd( task* tp, f32 spd );
/*
*   Description:
*     Multiply velocity parameters in a Task's 'MOVE_WORK' with a 'brake' value.
*
*   Notes:
*     - Although the name implies this is to slow down, values greater than '1.f'
*       can be used to accelerate instead
*
*   Parameters:
*     - tp          : taskwith a 'MOVE_WORK' compatible data
*     - brake       : value to multiply velocity parameters with
*/
void    AL_Brake( task* tp, f32 brake );

/****** Collision *******************************************************************/
/*
*   Description:
*     Search for a collision type hit and return the hit Task. CCL Search info is
*   cleared when calling, always returns first hit task.
*
*   Examples:
*     - AL_IsHitKindWithNum( tp, CI_TREE_SENSOR, CI_KIND_AL_WATER );  // sensor hit water
*     - AL_IsHitKindWithNum( tp, CI_NUM_BODY   , CI_KIND_AL_SHADOW ); // body hit a shadow
*
*   Parameters:
*     - tp          : task pointer to check collisions for
*     - info_num    : collision info number of 'tp'
*     - kind        : collision type of hit task
*
*   Returns:
*     task pointer to hit task; or 'nullptr' if no collision of that type has
*   occured.
*/
task*   AL_IsHitKindWithNum( task* tp, s32 info_num, u8 kind );

/****** Water Action ****************************************************************/
/*
*   Description:
*     Calculate water physics for inanimate Chao World objects, eg. fruit.
*
*   Notes:
*     - Also produces water ripples
*
*   Parameters:
*     - tp          : task pointer to check collisions for
*     - radius      : size of task defined as a radius
*/
void    AL_CalculateWaterAction( task* tp, f32 radius );

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS

/****** Standard ********************************************************************/
#define AL_InterpolateObject_p       FUNC_PTR(void, __cdecl, (const NJS_CNK_OBJECT*, const NJS_CNK_OBJECT*, NJS_CNK_OBJECT*, f32), 0x0054AEB0)

/****** Usercall ********************************************************************/
#define AL_IsOnScreen3_p             ((void*)0x0054AC70)/* EAX(EAX, STK, STK, STK)  */
#define AL_LoadSetFile_p             ((void*)0x0054B190)/* EAX(EDX)                 */
#define AL_IsHitKindWithNum_p        ((void*)0x0054B1F0)/* EAX(EDX, ECX, STK)       */
#define AL_InterpolateAngle_p        ((void*)0x0054A770)/* ###(EAX, ECX, ESI, STK)  */
#define AL_InterpolateSAngle_p       ((void*)0x0054A900)/* ###(EAX, ECX, ESI, STK)  */
#define AL_CalculateWaterAction_p    ((void*)0x0054B230)/* ###(EAX, STK)            */

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_CHAO_MISC*/
