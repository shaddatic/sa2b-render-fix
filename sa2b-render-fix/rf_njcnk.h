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
void    njCnkDirectDrawObject(const NJS_CNK_OBJECT* object);

/****** Easy ************************************************************************/
void    njCnkEasyDrawObject(const NJS_CNK_OBJECT* object);
void    njCnkEasyDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame);
void    njCnkEasyDrawMotionLink(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float frame);
void    njCnkEasyDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame);
void    njCnkEasyDrawShapeMotionBE(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame);

/****** Simple **********************************************************************/
void    njCnkSimpleDrawObject(const NJS_CNK_OBJECT* object);
void    njCnkSimpleDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame);
void    njCnkSimpleDrawMotionLink(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float frame);
void    njCnkSimpleDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame);
void    njCnkSimpleDrawShapeMotionBE(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame);

/****** Easy Multi ******************************************************************/
void    njCnkEasyMultiDrawObject(const NJS_CNK_OBJECT* object);
void    njCnkEasyMultiDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame);
void    njCnkEasyMultiDrawMotionLink(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float frame);
void    njCnkEasyMultiDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame);
void    njCnkEasyMultiDrawShapeMotionBE(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame);

/****** Simple Multi ****************************************************************/
void    njCnkSimpleMultiDrawObject(const NJS_CNK_OBJECT* object);
void    njCnkSimpleMultiDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame);
void    njCnkSimpleMultiDrawMotionLink(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float frame);
void    njCnkSimpleMultiDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame);
void    njCnkSimpleMultiDrawShapeMotionBE(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame);

EXTERN_END

#endif/*H_RF_NJCNK*/
