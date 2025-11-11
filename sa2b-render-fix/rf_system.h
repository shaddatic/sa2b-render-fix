/*
*   SA2 Render Fix - '/rf_system.h'
*
*   Description:
*     Game wide functions and utilities.
*/
#ifndef H_RF_SYSTEM
#define H_RF_SYSTEM

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Enums                       */
/********************************/
/****** Pillar Aspect Mode **********************************************************************/
typedef enum
{
    RF_SYS_PBA_43,
    RF_SYS_PBA_169,
}
RF_SYS_PBA;

/********************************/
/*  Prototypes                  */
/********************************/
/************************************************************************************************/
/*
*   Screen Fade
*/
/****** Draw ************************************************************************************/
/*
*   Description:
*     Draw screen wide fade effect.
*
*   Parameters:
*     - color       : fade color
*     - z           : polygon depth
*/
void    RF_SysDrawScreenFade( NJS_COLOR color, Float z );

/************************************************************************************************/
/*
*   Pillar Box
*/
/****** Pillar Aspect Ratio *********************************************************************/
/*
*   Description:
*     Set pillar box target aspect ratio for this frame, compared to 4:3.
*
*   Notes:
*     - An 'aspect' of '1.f' means restrict screen to 4:3, '1.33...f' would be 16:9.
*
*   Parameters:
*     - aspect      : target aspect ratio compared to 4:3
*/
void    RF_SysSetPillarAspect( Float aspect );
/*
*   Description:
*     Set pillar box target aspect ratio this frame, with easy enum.
*
*   Parameters:
*     - aspectmd    : target aspect ratio mode
*/
void    RF_SysEasySetPillarAspect( RF_SYS_PBA aspectmd );

/****** Pillar Decoration ***********************************************************************/
/*
*   Description:
*     Set pillar box color for this frame. If none is set, opaque black will be used.
*
*   Parameters:
*     - inner       : color for the inner edge of the pillar boxes
*     - edge        : color for the outer edge of the pillar boxes
*/
void    RF_SysSetPillarColor( Uint32 inner, Uint32 edge );
/*
*   Description:
*     Set pillar box texture for this frame. If none is set, no texture will be used.
*
*   Parameters:
*     - ptls        : ninja texlist
*     - n           : texture number in texlist
*     - trans       : if the texture should use transparent elements
*/
void    RF_SysSetPillarTexture( NJS_TEXLIST* ptls, Int n, Int trans );

/************************************************************************************************/
/*
*   System Control
*/
/****** Pillar Box ******************************************************************************/
/*
*   Description:
*     Draw pillar boxes onto the frame, should be drawn at the start and end of the frame.
*
*   Parameters:
*     - passFinal   : if this draw pass is the end of the frame
*/
void    RF_SysCtrlDrawPillar( bool passFinal );
/*
*   Description:
*     Reset pillar box parameters (color/texture/etc) at the end of the frame.
*/
void    RF_SysCtrlResetPillar( void );

/************************************************************************************************/
/*
*   Vsync Control
*/
/****** Vsync Wait Count ************************************************************************/
/*
*   Description:
*     Set the number of vsync frames to wait before starting a new frame.
*
*   Parameters:
*     - count       : vsync wait frames (1 = 60fps, 2 = 30fps, etc)
*/
void    RF_SysSetWaitVsyncCount( s32 count );
/*
*   Description:
*     Get the current vsync wait count.
*/
s32     RF_SysGetWaitVsyncCount( void );

EXTERN_END

#endif/*H_RF_SYSTEM*/
