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

#ifndef _RF_EXTERN_API_H_

/************************/
/*  Constants           */
/************************/
/****** Cnk Draw Func Bits **********************************************************/
#define RFRS_CNKFUNCMD_EASYBIT      (0x01) /* using easy draw variant               */
#define RFRS_CNKFUNCMD_SIMPLEBIT    (0x02) /* using simple draw variant             */
#define RFRS_CNKFUNCMD_MULTIBIT     (0x04) /* using multi draw variant              */
#define RFRS_CNKFUNCMD_DIRECTBIT    (0x08) /* using direct draw                     */

/************************/
/*  Enums               */
/************************/
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

typedef enum
{
    RFRS_CNKFUNCMD_END = -1,     /* end and reset to default                        */

    RFRS_CNKFUNCMD_NORMAL,       /* parameters will be parsed normally              */
    RFRS_CNKFUNCMD_EASY = 1,     /* parameters will be parsed as if EasyDraw        */
    RFRS_CNKFUNCMD_SIMPLE,       /* parameters will be parsed as if SimpleDraw      */
    RFRS_CNKFUNCMD_EASYMULTI = 5,/* parameters will be parsed as if EasyMultiDraw   */
    RFRS_CNKFUNCMD_SIMPLEMULTI,  /* parameters will be parsed as if SimpleMultiDraw */
    RFRS_CNKFUNCMD_DIRECT = 8,   /* parameters will be parsed as if DirectDraw      */
}
RFRS_CNKFUNCMD;

typedef enum
{
    RFRS_CNKPASSMD_END = -1,    /* end and reset to default                         */

    RFRS_CNKPASSMD_NORMAL,      /* draw inverse tris first, then normal tris        */
    RFRS_CNKPASSMD_INVERSE,     /* draw normal tris first, then inverse tris        */
}
RFRS_CNKPASSMD;

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

/** Set chunk func mode **/
void    RFRS_SetCnkFuncMode( RFRS_CNKFUNCMD mode );

/** Set chunk pass mode **/
void    RFRS_SetCnkPassMode( RFRS_CNKPASSMD mode );

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

/** Get chunk func mode **/
RFRS_CNKFUNCMD  RFRS_GetCnkFuncMode( void );

/** Get chunk pass mode **/
RFRS_CNKPASSMD  RFRS_GetCnkPassMode( void );

/****** Set Default *****************************************************************/
/** Set defaults **/
void    RFRS_SetDefaultCullMode(      RFRS_CULLMD  mode   );
void    RFRS_SetDefaultTransMode(     RFRS_TRANSMD mode   );
void    RFRS_SetDefaultAlphaTestFunc( RFRS_CMPMD   mode   );
void    RFRS_SetDefaultAlphaTestRef(  int32_t      value  );

void    RFRS_SetDefaultCnkDrawMode(   RFRS_CNKDRAWMD mode );

void    RFRS_SetDefaultCnkFuncMode( RFRS_CNKFUNCMD mode );
void    RFRS_SetDefaultCnkPassMode( RFRS_CNKPASSMD mode );

EXTERN_END

#endif/*_RF_RENDERSTATE_H_*/
