/*
*   SA2 Render Fix - '/rf_light.h'
*
*   Description:
*     Render Fix's light data and control module.
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_LIGHT
#define H_RF_LIGHT

/************************/
/*  Includes            */
/************************/
/****** Ninja ***********************************************************************/
#include <samt/ninja/njcommon.h>        /* ninja common                             */

EXTERN_START

/************************/
/*  Constants           */
/************************/
/****** Light Indeces ***************************************************************/
#define	RJD_CNK_LIGHT_ALL          (-1) /* all lights                               */
#define	RJD_CNK_LIGHT_NUM           (6) /* max lights                               */

#define	RJD_CNK_LIGHT_1             (0) /* light 1                                  */
#define	RJD_CNK_LIGHT_2             (1) /* light 2                                  */
#define	RJD_CNK_LIGHT_3             (2) /* light 3                                  */
#define	RJD_CNK_LIGHT_4             (3) /* light 4                                  */
#define	RJD_CNK_LIGHT_5             (4) /* light 5                                  */
#define	RJD_CNK_LIGHT_6             (5) /* light 6                                  */

/****** Switch Flags ****************************************************************/
#define RJD_CNK_LIGHTSW_1        (1<<0) /* light 1 is active                        */
#define RJD_CNK_LIGHTSW_2        (1<<1) /* light 2 is active                        */
#define RJD_CNK_LIGHTSW_3        (1<<2) /* light 3 is active                        */
#define RJD_CNK_LIGHTSW_4        (1<<3) /* light 4 is active                        */
#define RJD_CNK_LIGHTSW_5        (1<<4) /* light 5 is active                        */
#define RJD_CNK_LIGHTSW_6        (1<<5) /* light 6 is active                        */

/****** Light Type ******************************************************************/
#define RJD_CNK_LIGHTMD_DIR         (0) /* directional light                        */
#define RJD_CNK_LIGHTMD_POINT       (1) /* point light                              */
#define RJD_CNK_LIGHTMD_SPOT        (2) /* spot light                      (GX emu) */

/************************/
/*  Structures          */
/************************/
/****** Rj Light ********************************************************************/
typedef struct
{
    s32         type;           /* light type                                       */

    /** Directional Light **/

    NJS_VECTOR  v;              /* light vector                                     */

    Float       r,g,b;          /* color                                            */
    Float       inten;          /* light intensity                                  */

    /** Point Light **/

    NJS_POINT3 p;               /* world position                                   */

    f32        near;            /* near light plane                                 */
    f32        far;             /* far light plane                                  */

    /** Spot Light **/

    f32        angmin;          /* minimum angle                                    */
    f32        angmax;          /* maximum angle                                    */
}
RJS_LIGHT;

/****** Ambient *********************************************************************/
typedef struct
{
    Float       r,g,b;          /* color                                            */
    Float       inten;          /* ambient intensity                                */
}
RJS_AMBIENT;

/************************/
/*  Extern Data         */
/************************/
/****** Light Switch ****************************************************************/
#define _rj_cnk_light_switch_               DATA_REF(Uint32, 0x026702E0)

/****** Light Data ******************************************************************/
EXTERN RJS_LIGHT   _rj_cnk_light_[6];       /* lights data                          */
EXTERN RJS_AMBIENT _rj_cnk_light_ambient_;  /* ambient data                         */

/************************/
/*  Functions           */
/************************/
/****** Light Param *****************************************************************/
/*
*   Description:
*     Switch a Chunk light on or off.
*
*   Parameters:
*     - light       : chunk light                                 [RJD_CNK_LIGHT_#]
*     - flag        : on/off flag                                          [ON/OFF]
*/
void    rjCnkSetLightSwitch( Int light, Int flag );
/*
*   Description:
*     Set a Chunk light color.
*
*   Notes:
*     - Internal light intensity is set to '1.f' when this function is called. To
*       set a custom intensity, use 'SetLightIntensity'.
*
*   Parameters:
*     - light       : chunk light                                 [RJD_CNK_LIGHT_#]
*     - lr,lg,lb    : color                                               [0.f~1.f]
*/
void    rjCnkSetLightColor( Int light, Float lr, Float lg, Float lb );
/*
*   Description:
*     Set the Chunk ambient light color.
*
*   Notes:
*     - Ambient is set here OR via intensity, but can't be both.
*     - Internal ambient intensity value is set to the largest color component
*       value when this function is called.
*
*   Parameters:
*     - ar,ag,ab    : color                                               [0.f~1.f]
*/
void    rjCnkSetAmbient( Float ar, Float ag, Float ab );
/*
*   Description:
*     Set a Chunk light intensity, and optionally the ambient intensity.
*
*   Notes:
*     - This will overwrite the ambient light color if ambient intensity is set.
*     - Ambient is not updated when 'LIGHT_ALL' is used.
*
*   Parameters:
*     - light       : chunk light                                 [RJD_CNK_LIGHT_#]
*     - inten       : light intensity                                     [0.f~1.f]
*     - ambient     : ambient intensity                        [opt: -1.f, 0.f~1.f]
*/
void    rjCnkSetLightIntensity( Int light, Float inten, Float ambient );

/****** Light Modes *****************************************************************/
/*
*   Description:
*     Set a Chunk light vector, and set the light mode to directional light.
*
*   Notes:
*     - Vector is not normalized in-function.
*
*   Parameters:
*     - light       : chunk light                                 [RJD_CNK_LIGHT_#]
*     - vx,vy,vz    : vector
*/
void    rjCnkSetLightVector( Int light, Float vx, Float vy, Float vz );
/*
*   Description:
*     Set a Chunk light position, and set the light mode to point light.
*
*   Parameters:
*     - light       : chunk light                                 [RJD_CNK_LIGHT_#]
*     - px,py,pz    : vector
*/
void    rjCnkSetLightPoint( Int light, Float px, Float py, Float pz );
/*
*   Description:
*     Set Chunk point light near and far ranges.
*
*   Notes:
*     - Anything closer than near is clamped to max intensity, then intensity falls
*       off linearly until the far range.
*
*   Parameters:
*     - light       : chunk light                                 [RJD_CNK_LIGHT_#]
*/
void    rjCnkSetLightRange( Int light, Float nrange, Float frange );
/*
*   Description:
*     Set Chunk light vectors/points to the current matrix, if it hasn't been done.
*s
*   Parameters:
*     - light       : chunk light                                 [RJD_CNK_LIGHT_#]
*/
void    rjCnkSetLightMatrix( Int light );

/****** Sync GX *********************************************************************/
/*
*   Description:
*     Sync light data with the game's vanilla GX light system.
*
*   Parameters:
*     - light       : chunk light                               [RJD_CNK_LIGHT_1~4]
*/
void    rjCnkPushLightToGX( Int light );
/*
*   Description:
*     Sync ambient light color data with the game's vanilla GX light system.
*/
void    rjCnkPushAmbientToGX( void );

EXTERN_END

#endif/*H_RF_LIGHT*/
