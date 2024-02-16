/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_toy/alo_ball.h'
*
*   Contains functions and data related to the ball garden object.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_TOY_BALL_H_
#define _SA2B_CHAO_TOY_BALL_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     TASK;

/************************/
/*  Structures          */
/************************/
#define GET_BALL_WORK(tp) (BALL_WORK*)(tp->awp)

typedef struct 
{
    float inv_radius;
    int32_t HeldAng;
    int32_t RotSpd;
    NJS_POINT3 axis;
    NJS_MATRIX mat;
}
BALL_WORK;

/************************/
/*  Data                */
/************************/
#define BallUsable              DataRef(int32_t, 0x01DBE574)
#define ALO_BallTaskPointer     DataRef(TASK* , 0x01DBE570)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    ALO_BallCreate(NJS_POINT3* pPos, NJS_VECTOR* pVelo);

/** Internal task functions **/
void    ALO_Ball(TASK* tp);
void    ALO_BallExecutor(TASK* tp);
void    ALO_BallDisplayer(TASK* tp);
void    ALO_BallDestructor(TASK* tp); // Same function as many other ALO objects

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALO_BallCreate_p        FuncPtr(void, __cdecl, (NJS_POINT3*, NJS_VECTOR*), 0x0055D6B0)
#define ALO_Ball_p              FuncPtr(void, __cdecl, (TASK*)                   , 0x0055D640)
#define ALO_BallExecutor_p      FuncPtr(void, __cdecl, (TASK*)                   , 0x0055D310)
#define ALO_BallDisplayer_p     FuncPtr(void, __cdecl, (TASK*)                   , 0x0055D3B0)
#define ALO_BallDestructor_p    FuncPtr(void, __cdecl, (TASK*)                   , 0x0057B9B0)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_TOY_BALL_H_ */
