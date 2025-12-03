/*
*   SA2 Render Fix - '/rfu_draw.h'
*
*   Description:
*     Draw utility functions.
*/
#ifndef H_RF_UTIL_DRAW
#define H_RF_UTIL_DRAW

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Prototypes                  */
/********************************/
/****** Null Draw *******************************************************************************/
/*
*   Description:
*     Emulates a successful Chunk draw, but doesn't actually draw anything.
* 
*   Parameters:
*     - model   : chunk model
*
*   Returns:
*     Always '0' as if model was drawn.
*/
Sint32  njCnkNullDrawModel( const NJS_CNK_MODEL* model );
/*
*   Description:
*     Goes through the steps of animating, such as matrix calculations & calling
*   motion callbacks, without actually drawing anything.
*
*   Parameters:
*     - object      : chunk object to animate
*     - motion      : motion data for 'object'
*     - frame       : frame of animation
*/
void    njCnkAnimateMotion( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame );
/*
*   Description:
*     Goes through the steps of animating, such as interpolating the motions, matrix
*   calculations, & calling motion callbacks, without actually drawing anything.
*
*   Parameters:
*     - object      : chunk object to animate
*     - motion_link : motion link data and motion datas for 'object'
*     - rate        : ratio of transition from motion 1 to motion 2 (0~1)
*/
void    njCnkAnimateMotionLink( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float rate );
/*
*   Description:
*     Animate an SA2 motion control without actually drawing anything.
*
*   Parameters:
*     - pObject  : a Ninja object of any type
*     - pMtnCtrl : a motion control pointer
*/
void    AnimateMotion( const ANY_OBJECT* pObject, const MOTION_CTRL* pMtnCtrl );

/****** Generic Shadows *************************************************************************/
/*
*   Draw common modifier models.
*/
void    DrawBasicShadow( void );
void    AL_ShadowDraw(   void );

EXTERN_END

#endif/*H_RF_UTIL_DRAW*/
