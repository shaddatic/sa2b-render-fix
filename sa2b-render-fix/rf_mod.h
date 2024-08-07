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
/*  Enums               */
/************************/
typedef enum
{
    MODMD_FAST,
    MODMD_DEBUG,
}
RFE_MOD_MODE;

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    RFMOD_Init(void);

void    RFMOD_PushPolygon(Sint16* plist, NJS_POINT3* vtxBuf, uint16_t nbPoly);

void    RFMOD_DrawBuffer(void);
void    RFMOD_ClearBuffer(void);

void    RFMOD_SetColor(float r, float g, float b);
void    RFMOD_SetAlpha(float a);

void    RFMOD_SetColorI(uint8_t r, uint8_t g, uint8_t b);
void    RFMOD_SetAlphaI(uint8_t a);

void    RFMOD_SetDrawMode(RFE_MOD_MODE mode);

void    RFMOD_Suspend(void);
void    RFMOD_Resume(void);

void    RFMOD_OnShadow(void);
void    RFMOD_OffShadow(void);

void    RFMOD_SetInvertMode(bool bInv);

EXTERN_END

#endif/*_RF_MOD_H_*/
