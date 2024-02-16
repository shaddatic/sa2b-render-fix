/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_control.h'
*
*   Contains functions and data related to Chao execution.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_CONTROL_H_
#define _SA2B_CHAO_CONTROL_H_

/************************/
/*  Data                */
/************************/
#define alCtrlMove      DataRef(bool32_t, 0x01DBE634)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    AL_EnableMove(void);
void    AL_DisableMove(void);
bool32_t  AL_IsMovable(void);

EXTERN_END

#endif /* _SA2B_CHAO_CONTROL_H_ */
