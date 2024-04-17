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
#ifndef _RF_EXTERN_API_
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
    RFRS_TRANSMD_END = -1,      /* End and reset to default                         */

    RFRS_TRANSMD_AUTO,          /* Set trans mode by model flags and global state   */
    RFRS_TRANSMD_OPAQUE,        /* Draw opaque                                      */
    RFRS_TRANSMD_ALPHATEST,     /* Draw with alpha test (and Z buffer)              */
    RFRS_TRANSMD_TRANSPARENT,   /* Draw fully transparant (no Z buffer)             */
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

/** Set defaults **/
void    RFRS_SetDefaultCullMode(      RFRS_CULLMD  mode  );
void    RFRS_SetDefaultTransMode(     RFRS_TRANSMD mode  );
void    RFRS_SetDefaultAlphaTestFunc( RFRS_CMPMD   mode  );
void    RFRS_SetDefaultAlphaTestRef(  int32_t      value );

EXTERN_END

#endif/*_RF_RENDERSTATE_H_*/
