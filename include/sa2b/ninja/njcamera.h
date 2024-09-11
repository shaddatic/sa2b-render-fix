/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njcamera.h'
*
*   Description:
*     Contains structs for the Ninja Camera
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_NJ_CAMERA
#define H_NJ_CAMERA

/************************/
/*  External Headers    */
/************************/
/****** System **********************************************************************/
#include <sa2b/shinobi/sg_xpt.h> /* shinobi types                                   */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/njcommon.h> /* ninja common                                    */

EXTERN_START

/************************/
/*  Constants           */
/************************/
/****** Camera Type *****************************************************************/
#define NJD_CTYPE_VECTOR        (1) /* camera vector                                */
#define NJD_CTYPE_TARGET        (2) /* camera target position                       */

/************************/
/*  Structures          */
/************************/
/****** Camera **********************************************************************/
typedef struct
{
    Float px, py, pz;           /* position                                         */
    Float vx, vy, vz;           /* look vector                                      */
    Angle roll;                 /* roll angle                                       */
    Angle ang;                  /* fov angle                                        */
    Float n_clip;               /* near clip                               (unused) */
    Float f_clip;               /* far clip                                (unused) */
}
NJS_CAMERA;

/************************/
/*  Prototypes          */
/************************/
/****** Set Camera ******************************************************************/
/*
*   Description:
*     Initiates an NJS_CAMERA to its default values.
*     These are:
*       - position      (px,py,pz) = world origin (0,0,0)  
*       - direction     (vx,vy,vz) = forward (0,0,-1)
*       - view tilt         (roll) = 0 degrees
*       - Angle of view      (ang) = 60 degrees
*       - near clip plane (n_clip) = -1
*       - far clip plane  (f_clip) = -60000
*/
void    njInitCamera( NJS_CAMERA* camera );

/****** Set Camera ******************************************************************/
/*
*   Description:
*     Set current matrix to a camera structure, multiplying from the left, and set
*   the field of view according to the 'ang' structure member.
*     The 'n_clip' & 'f_clip' members are ignored.
*
*   Paramters:
*     - camera  : pointer to a camera structure to set the matrix to
*/
void	njSetCamera( const NJS_CAMERA* camera );

EXTERN_END

#endif/*H_NJ_CAMERA*/
