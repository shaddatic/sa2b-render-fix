/*
*   SA2 Render Fix - '/rf_modchk.h'
*
*   Description:
*       Module for checking mod issues and conflicts.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef H_RF_NJCNK
#define H_RF_NJCNK

/************************/
/*  External Includes   */
/************************/
/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h>   /* ninja                                            */

EXTERN_START

/************************/
/*  Prototypes          */
/************************/
/****** Easy ************************************************************************/
void    njCnkEasyDrawModel(const NJS_CNK_MODEL* model);
void    njCnkEasyDrawObject(const NJS_CNK_OBJECT* object);
void    njCnkEasyMultiDrawObject(const NJS_CNK_OBJECT* object);
void    njCnkEasyDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame);
void    njCnkEasyMultiDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame);
void    njCnkEasyDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame);
void    njCnkEasyMultiDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame);
void    njCnkEasyDrawShapeMotionBE(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame);
void    njCnkEasyMultiDrawShapeMotionBE(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame);

/****** Simple **********************************************************************/
void    njCnkSimpleDrawModel(const NJS_CNK_MODEL* model);
void    njCnkSimpleDrawObject(const NJS_CNK_OBJECT* object);
void    njCnkSimpleMultiDrawObject(const NJS_CNK_OBJECT* object);
void    njCnkSimpleDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame);
void    njCnkSimpleMultiDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame);
void    njCnkSimpleDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame);
void    njCnkSimpleMultiDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame);
void    njCnkSimpleDrawShapeMotionBE(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame);
void    njCnkSimpleMultiDrawShapeMotionBE(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame);

EXTERN_END

#endif/*H_RF_NJCNK*/
