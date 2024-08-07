/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_control.h'
*
*   Description:
*       Contains functions and data related to Chao execution.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_CONTROL_H_
#define _SA2B_CHAO_CONTROL_H_

/************************/
/*  Data                */
/************************/
#define alCtrlMove      DATA_REF(b32, 0x01DBE634)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void     AL_EnableMove(void);
void     AL_DisableMove(void);
b32 AL_IsMovable(void);

EXTERN_END

#endif/*_SA2B_CHAO_CONTROL_H_*/
