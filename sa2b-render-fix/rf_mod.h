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
#ifndef H_RF_MOD
#define H_RF_MOD

EXTERN_START

/************************/
/*  Enums               */
/************************/
/****** Modifier Draw Mode **********************************************************/
typedef enum
{
    MODMD_FAST,
    MODMD_DEBUG,
}
RFE_MOD_MODE;

/************************/
/*  Structures          */
/************************/
/****** Mod Buffer Triangle *********************************************************/
typedef struct
{
    NJS_POINT3 vtx[3];
}
MOD_TRI;

/************************/
/*  Functions           */
/************************/
/****** Init ************************************************************************/
/*
*   Description:
*     Init modifier core module
*/
void    RFMOD_Init(void);

/****** Draw Modifier ***************************************************************/
/*
*   Description:
*     Get the top of the current modifier buffer.
*
*   Parameters:
*     - nbTri   : the number of tris you will add to the buffer
*
*   Returns:
*     A pointer to the top of the modifier buffer, or 'nullptr' if 'nbTri' would
*   breach the buffer bounds.
*/
MOD_TRI* RFMOD_GetBuffer( s32 nbTri );
/*
*   Description:
*     Get the current invert mode for the modifier render state. If this is true,
*   you must add the tris to the buffer with reversed winding.
*
*   Returns:
*     'true' if modifiers must be inverted, or 'false' if not
*/
bool    RFMOD_GetInvertMode( void );

/****** Draw Buffer *****************************************************************/
/*
*   Description:
*     Draw the current modifier buffer to the screen.
*/
void    RFMOD_DrawBuffer( void );
/*
*   Description:
*     Clear the modifier buffer for a new frame.
*/
void    RFMOD_ClearBuffer( void );

/****** Set Mod Parameters **********************************************************/
/*
*   Description:
*     Set the end color values of the modifiers.
*
*   Parameters:
*    - r, g, b  : color in range 0~1
*/
void    RFMOD_SetColor(float r, float g, float b);
/*
*   Description:
*     Set the end alpha value of the modifiers.
* 
*   Parameters:
*    - a        : alpha in range 0~1
*/
void    RFMOD_SetAlpha(float a);
/*
*   Description:
*     Set the modifier draw mode.
*
*   Parameters:
*     - mode    : modifier draw mode to set to
*/
void    RFMOD_SetDrawMode( RFE_MOD_MODE mode );
/*
*   Description:
*     Set the modifier inverted drawing mode.
*
*   Parameters:
*     - bInv    : inverted mode state
*/
void    RFMOD_SetInvertMode( bool bInv );

/****** Set Mod Parameters Int ******************************************************/
/*
*   Description:
*     Set the end color values of the modifiers using an int.
*
*   Parameters:
*    - r, g, b  : color in range 0~255
*/
void    RFMOD_SetColorI( uint8_t r, uint8_t g, uint8_t b );
/*
*   Description:
*     Set the end alpha value of the modifiers using an int.
* 
*   Parameters:
*    - a        : alpha in range 0~255
*/
void    RFMOD_SetAlphaI( uint8_t a );

/****** Control Modifier ************************************************************/
/*
*   Description:
*     Pause updating the modifier stencil buffer while drawing.
*/
void    RFMOD_Suspend( void );
/*
*   Description:
*     Resume updating the modifier stencil buffer when drawing.
*/
void    RFMOD_Resume( void );
/*
*   Description:
*     Write 'OnShadow' bit to the modifier stencil buffer.
*/
void    RFMOD_OnShadow(void);
/*
*   Description:
*     Unset 'OnShadow' bit to the modifier stencil buffer.
*/
void    RFMOD_OffShadow(void);

EXTERN_END

#endif/*H_RF_MOD*/
