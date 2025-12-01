/*
*   SA2 Render Fix - '/rf_njcnk.h'
*
*   Description:
*     Emulated Dreamcast draw functions for Chunk
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_NJCNK
#define H_RF_NJCNK

/************************/
/*  External Includes   */
/************************/
/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Render Fix ******************************************************************/
#include <rf_ninja.h>           /* rf ninja                                         */

EXTERN_START

/************************/
/*  Prototypes          */
/************************/
/****** Direct **********************************************************************/
void    njCnkDirectDrawObject(NJS_CNK_OBJECT* object);

/****** Easy ************************************************************************/
void    njCnkEasyDrawObject(NJS_CNK_OBJECT* object);
void    njCnkEasyDrawMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame);
void    njCnkEasyDrawMotionLink(NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float frame);
void    njCnkEasyDrawShapeMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame);
void    njCnkEasyDrawShapeMotionBE(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame);

/****** Simple **********************************************************************/
void    njCnkSimpleDrawObject(NJS_CNK_OBJECT* object);
void    njCnkSimpleDrawMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame);
void    njCnkSimpleDrawMotionLink(NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float frame);
void    njCnkSimpleDrawShapeMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame);
void    njCnkSimpleDrawShapeMotionBE(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame);

/****** Easy Multi ******************************************************************/
void    njCnkEasyMultiDrawObject(NJS_CNK_OBJECT* object);
void    njCnkEasyMultiDrawMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame);
void    njCnkEasyMultiDrawMotionLink(NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float frame);
void    njCnkEasyMultiDrawShapeMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame);
void    njCnkEasyMultiDrawShapeMotionBE(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame);

/****** Simple Multi ****************************************************************/
void    njCnkSimpleMultiDrawObject(NJS_CNK_OBJECT* object);
void    njCnkSimpleMultiDrawMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame);
void    njCnkSimpleMultiDrawMotionLink(NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float frame);
void    njCnkSimpleMultiDrawShapeMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame);
void    njCnkSimpleMultiDrawShapeMotionBE(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame);

/****** Modifier ********************************************************************/
void    njCnkModDrawObject( NJS_CNK_OBJECT* object );
void    njCnkModDrawMotion( NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame );

EXTERN_END

#endif/*H_RF_NJCNK*/
