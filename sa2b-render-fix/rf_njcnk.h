/*
*   SA2 Render Fix - '/rf_njcnk.h'
*
*   Description:
*     Complete Ninja draw functions for Chunk.
*/
#ifndef H_RF_NJCNK
#define H_RF_NJCNK

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Prototypes                  */
/********************************/
/****** Direct **********************************************************************************/
/*
*   Description:
*     Direct compile & draw emulation function.
*/
void    njCnkDirectDrawObject( NJS_CNK_OBJECT* object );

/****** Easy ************************************************************************************/
/*
*   Description:
*     Ninja Easy draw functions.
*/
void    njCnkEasyDrawObject( NJS_CNK_OBJECT* object );
void    njCnkEasyDrawMotion( NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame );
void    njCnkEasyDrawMotionLink( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float frame );
void    njCnkEasyDrawShapeMotion( NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame );
void    njCnkEasyDrawShapeMotionBE( NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame );

/****** Simple **********************************************************************************/
/*
*   Description:
*     Ninja Simple draw functions.
*/
void    njCnkSimpleDrawObject( NJS_CNK_OBJECT* object );
void    njCnkSimpleDrawMotion( NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame );
void    njCnkSimpleDrawMotionLink( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float frame );
void    njCnkSimpleDrawShapeMotion( NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame );
void    njCnkSimpleDrawShapeMotionBE( NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame );

/****** Easy Multi ******************************************************************************/
/*
*   Description:
*     Ninja EasyMulti draw functions.
*/
void    njCnkEasyMultiDrawObject( NJS_CNK_OBJECT* object );
void    njCnkEasyMultiDrawMotion( NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame );
void    njCnkEasyMultiDrawMotionLink( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float frame );
void    njCnkEasyMultiDrawShapeMotion( NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame );
void    njCnkEasyMultiDrawShapeMotionBE( NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame );

/****** Simple Multi ****************************************************************************/
/*
*   Description:
*     Ninja SimpleMulti draw functions.
*/
void    njCnkSimpleMultiDrawObject( NJS_CNK_OBJECT* object );
void    njCnkSimpleMultiDrawMotion( NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame );
void    njCnkSimpleMultiDrawMotionLink( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float frame );
void    njCnkSimpleMultiDrawShapeMotion( NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame );
void    njCnkSimpleMultiDrawShapeMotionBE( NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame );

/****** Modifier ********************************************************************************/
/*
*   Description:
*     Ninja Chunk modifier draw functions.
*/
void    njCnkModDrawObject( NJS_CNK_OBJECT* object );
void    njCnkModDrawMotion( NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame );

EXTERN_END

#endif/*H_RF_NJCNK*/
