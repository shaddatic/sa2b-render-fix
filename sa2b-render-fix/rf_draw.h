/*
*   SA2 Render Fix - '/rf_draw.h'
*
*   Description:
*       Contains useful draw functions
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_DRAW_H_
#define _RF_DRAW_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/ninja.h>

#include <sa2b/util/anyobj.h>

#include <sa2b/src/motion.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
/*
*   Null draw
*/
/** No draw model **/
int     njCnkNullDrawModel(  NJS_CNK_MODEL*  model  );
void    njCnkNullDrawObject( NJS_CNK_OBJECT* object );

/** No draw motion **/
void    njCnkAnimateMotion(     NJS_CNK_OBJECT* object, NJS_MOTION*      motion,      float frame );
void    njCnkAnimateMotionLink( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, float frame );

/** No draw adv2 motion **/
void    AnimateMotion( ANY_OBJECT* pObject, MOTION_CTRL* pMtnCtrl );

/*
*   Modifier
*/
/** Modifier draw **/
int32_t njCnkModDrawModel(  NJS_CNK_MODEL*  model  );
void    njCnkModDrawObject( NJS_CNK_OBJECT* object );

/** Modifier draw motion **/
void    njCnkModDrawMotion(     NJS_CNK_OBJECT* object, NJS_MOTION*      motion,      float frame );
void    njCnkModDrawMotionLink( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, float frame );

/*
*   Generic shadows
*/
/** Basic shadow **/
void    DrawBasicShadow( void );

/** Chao shadow **/
void    AL_ShadowDraw( void );

EXTERN_END

#endif/*_RF_DRAW_H_*/
