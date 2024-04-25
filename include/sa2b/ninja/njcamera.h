/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njcamera.h'
*
*   Contains structs for the Ninja Camera
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _NJ_CAMERA_H_
#define _NJ_CAMERA_H_

/* Camera Motion type */
#define NJD_CTYPE_VECTOR        1       /* camera vector */
#define NJD_CTYPE_TARGET        2        /* camera target position */

/*--------------------------------------*/
/*      Camera Structure                */
/*--------------------------------------*/
typedef struct {
    Float px, py, pz;
    Float vx, vy, vz;
    Sangle roll;
    Sangle ang;
    Uint32 type;
} NJS_CAMERA;

#endif    /*_NJ_CAMERA_H_*/
