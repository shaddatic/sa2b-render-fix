/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/display.h'
*
*   Description:
*       Contains data and Toolkit-custom functions related to
*   the display.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_DISPLAY_H_
#define _SA2B_DISPLAY_H_

/************************/
/*  Data                */
/************************/
#define DisplayResolutionX      DataRef(float32_t, 0x174BA64)
#define DisplayResolutionY      DataRef(float32_t, 0x174BA68)

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Returns the difference in aspect ratio, as a ratio, compared to 4:3 **/
float       GetDisplayRatio( void );

/** Returns the difference in resolution, as a ratio, compared to 640x480 **/
float       GetDisplayRatioX( void );
float       GetDisplayRatioY( void );

/** Get Display Info **/
float       GetDisplayAspectRatio( void );
int         GetDisplayRefreshRate( void );
bool32_t    GetDisplayIsFullscreen( void );

EXTERN_END

#endif/*_SA2B_DISPLAY_H_*/
