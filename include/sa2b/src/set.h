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
    float32_t fRangeOut;
    int32_t pObjSleepCondition;
}
UNION_STATUS;

typedef struct _OBJ_EDITENTRY
{
    uint16_t usID;
    int16_t rotx;
    int16_t roty;
    int16_t rotz;
    float32_t xpos;
    float32_t ypos;
    float32_t zpos;
    float32_t xscl;
    float32_t yscl;
    float32_t zscl;
}
OBJ_EDITENTRY;

typedef struct _OBJ_CONDITION
{
    uint8_t scCount;
    uint8_t scUserFlag;
    int16_t ssCondition;
    TASK* pTask;
    OBJ_EDITENTRY* pObjEditEntry;
    UNION_STATUS unionStatus;
}
OBJ_CONDITION;

typedef struct _OBJ_ITEMENTRY
{
    uint8_t ucInitMode;
    uint8_t ucLevel;
    int16_t ssAttribute;
    float32_t fRange;
    task_exec fnExec;
    char* strObjName;
}
OBJ_ITEMENTRY;

typedef struct _OBJ_ITEMTABLE
{
    int32_t slCount;
    OBJ_ITEMENTRY* pObjItemEntry;
}
OBJ_ITEMTABLE;

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t  CheckRangeOut(TASK* tp);
int32_t  CheckRangeOutWithR(TASK* tp, float fRange);

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
