/*
*   SA2 Render Fix - '/rf_renderstate.h'
*
*   Description:
*       Contains useful draw functions
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_RENDERSTATE_H_
#define _RF_RENDERSTATE_H_

/************************/
/*  Enums               */
/************************/
#ifndef _RF_EXTERN_API_H_
typedef enum
{
    RFRS_CULLMD_END = -1,        /* End and reset to default                        */

    RFRS_CULLMD_AUTO,            /* Set culling mode by model flags                 */
    RFRS_CULLMD_NONE,            /* No culling                                      */
    RFRS_CULLMD_NORMAL,          /* Normal culling                                  */
    RFRS_CULLMD_INVERSE,         /* Inverted culling                                */
}
RFRS_CULLMD;

typedef enum
{
    RFRS_TRANSMD_END = -1,      /* end and reset to default                         */

    RFRS_TRANSMD_AUTO,          /* set transparancy mode automatically    (default) */
    RFRS_TRANSMD_OPAQUE,        /* draw without transparancy                        */
    RFRS_TRANSMD_ALPHATEST,     /* draw transparancy and alpha test    (& Z buffer) */
    RFRS_TRANSMD_TRANSPARENT,   /* draw transparancy                  (no Z buffer) */
    /*
    *     The following modes only change which transparancy mode is used, and leave
    *   'OPAQUE' mode as-is. They were implemented in version 1.3.2 and will simply
    *   do nothing in earlier versions.
    */
    RFRS_TRANSMD_AUTO_ATEST,    /* auto, use alpha test for transparancy            */
    RFRS_TRANSMD_AUTO_TRANS,    /* auto, do not use alpha test for transparancy     */
}
RFRS_TRANSMD;

typedef enum
{
    RFRS_CMPMD_END = -1,        /* End and reset to default                         */

    RFRS_CMPMD_NVR,             /* Never                                            */
    RFRS_CMPMD_LSS,             /* Less                                             */
    RFRS_CMPMD_EQU,             /* Equal                                            */
    RFRS_CMPMD_LEQ,             /* Less or equal                                    */
    RFRS_CMPMD_GTR,             /* Greater                                          */
    RFRS_CMPMD_NEQ,             /* Not equal                                        */
    RFRS_CMPMD_GEQ,             /* Greater or equal                                 */
    RFRS_CMPMD_ALW,             /* Always                                           */
}
RFRS_CMPMD;

typedef enum
{
    RFRS_ALPHAREF_END = -1,     /* End and reset to default                         */
}
RFRS_ALPHAREF;

typedef enum
{
    RFRS_MODMD_END = -1,        /* end and reset to default                         */

    RFRS_MODMD_NORMAL,          /* draw modifiers with regular winding              */
    RFRS_MODMD_INVERSE,         /* draw modifiers with inverse winding              */
}
RFRS_MODMD;

typedef enum
{
    RFRS_CNKDRAWMD_END = -1,    /* end and reset to default                         */

    RFRS_CNKDRAWMD_ALL,         /* draw all strips                                  */
    RFRS_CNKDRAWMD_OPAQUE,      /* draw only opaque strips                          */
    RFRS_CNKDRAWMD_TRANSPARENT, /* draw only transparent strips                     */
}
RFRS_CNKDRAWMD;

#endif/*_RF_EXTERN_API_*/

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Init **/
void    RF_RenderStateInit( void );

/** Set cull mode **/
void    RFRS_SetCullMode( RFRS_CULLMD mode );

/** Set transparancy mode **/
void    RFRS_SetTransMode( RFRS_TRANSMD mode );

/** Set alpha test func **/
void    RFRS_SetAlphaTestFunc( RFRS_CMPMD mode );

/** Set alpha test reference **/
void    RFRS_SetAlphaTestRef( int32_t value );

/** Set modifier mode **/
void    RFRS_SetModifierMode( RFRS_MODMD mode );

/** Set chunk draw mode **/
void    RFRS_SetCnkDrawMode( RFRS_CNKDRAWMD mode );

/****** Get Render State ************************************************************/
/** Get cull mode **/
RFRS_CULLMD RFRS_GetCullMode( void );

/** Get transparancy mode **/
RFRS_TRANSMD RFRS_GetTransMode( void );

/** Get alpha test func **/
RFRS_CMPMD RFRS_GetAlphaTestFunc( void );

/** Get alpha test reference **/
int32_t RFRS_GetAlphaTestRef( void );

/** Get modifier mode **/
RFRS_MODMD RFRS_GetModifierMode( void );

/** Get chunk draw mode **/
RFRS_CNKDRAWMD RFRS_GetCnkDrawMode( void );

/****** Set Default *****************************************************************/
/** Set defaults **/
void    RFRS_SetDefaultCullMode(      RFRS_CULLMD  mode   );
void    RFRS_SetDefaultTransMode(     RFRS_TRANSMD mode   );
void    RFRS_SetDefaultAlphaTestFunc( RFRS_CMPMD   mode   );
void    RFRS_SetDefaultAlphaTestRef(  int32_t      value  );

void    RFRS_SetDefaultCnkDrawMode(   RFRS_CNKDRAWMD mode );

EXTERN_END

#endif/*_RF_RENDERSTATE_H_*/
