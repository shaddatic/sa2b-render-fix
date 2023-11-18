/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/set.h'
*
*   Contains structs and functions related to stage SETs
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_SET_H_
#define _SA2B_SET_H_

/************************/
/*  Abstracted Types    */
/************************/
typedef struct task        TASK;
typedef struct taskwk    TASKWK;

/************************/
/*  Typedefs            */
/************************/
typedef void(__cdecl* task_exec)(TASK*);

/************************/
/*  Structures          */
/************************/
typedef union _UNION_STATUS
{
    float32 fRangeOut;
    sint32 pObjSleepCondition;
}
UNION_STATUS;

typedef struct _OBJ_EDITENTRY
{
    uint16 usID;
    sint16 rotx;
    sint16 roty;
    sint16 rotz;
    float32 xpos;
    float32 ypos;
    float32 zpos;
    float32 xscl;
    float32 yscl;
    float32 zscl;
}
OBJ_EDITENTRY;

typedef struct _OBJ_CONDITION
{
    uint8 scCount;
    uint8 scUserFlag;
    sint16 ssCondition;
    TASK* pTask;
    OBJ_EDITENTRY* pObjEditEntry;
    UNION_STATUS unionStatus;
}
OBJ_CONDITION;

typedef struct _OBJ_ITEMENTRY
{
    uint8 ucInitMode;
    uint8 ucLevel;
    sint16 ssAttribute;
    float32 fRange;
    task_exec fnExec;
    char* strObjName;
}
OBJ_ITEMENTRY;

typedef struct _OBJ_ITEMTABLE
{
    sint32 slCount;
    OBJ_ITEMENTRY* pObjItemEntry;
}
OBJ_ITEMTABLE;

/************************/
/*  Functions           */
/************************/
EXTERN_START
sint32  CheckRangeOut(TASK* tp);
sint32  CheckRangeOutWithR(TASK* tp, float fRange);

void    ObjectGenericExec(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptr **/
#define ObjectGenericExec_p        FuncPtr(void, __cdecl, (TASK* tp), 0x005B4250)

/** User-Function ptr **/
extern const void* const CheckRangeOut_p;
extern const void* const CheckRangeOutWithR_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_SET_H_ */
