/*
*   SA2 Render Fix - '/rf_mod.h'
*
*   Description:
*       Contains functions to draw modifier volumes for the
*   cheap shadow system.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_MOD_H_
#define _RF_MOD_H_

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    RFMOD_Init();

void    RFMOD_CreateBuffer(size_t nbTri, size_t nbTriList);

void    RFMOD_PushPolygon(Sint16* plist, NJS_POINT3* vtxBuf, uint16_t nbPoly);

void    RFMOD_DrawBuffer();
void    RFMOD_ClearBuffer();

void    RFMOD_SetColor(float r, float g, float b);
void    RFMOD_SetAlpha(float a);

void    RFMOD_SetColorI(uint8_t r, uint8_t g, uint8_t b);
void    RFMOD_SetAlphaI(uint8_t a);

void    RFMOD_Suspend();
void    RFMOD_Resume();

void    RFMOD_OnShadow();
void    RFMOD_OffShadow();

EXTERN_END

#endif/*_RF_MOD_H_*/
