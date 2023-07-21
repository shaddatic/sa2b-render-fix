#pragma once

EXTERN_START

DataRef(float32, DisplayResolutionX, 0x174BA64);
DataRef(float32, DisplayResolutionY, 0x174BA68);

/* Returns the difference in aspect ratio, as a ratio, compared to 4:3 */
float   GetDisplayRatio();

/* Returns the difference in resolution, as a ratio, compared to 640x480 */
float   GetDisplayRatioX();
float   GetDisplayRatioY();

/* Get Display Info */
float   GetDisplayAspectRatio();
int     GetDisplayRefreshRate();
bool32  GetDisplayIsFullscreen();

EXTERN_END
