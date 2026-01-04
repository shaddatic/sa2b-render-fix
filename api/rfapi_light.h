/*
*   SA2 Render Fix - '/rfapi_light.h'
*
*   Description:
*     The 'Ninja Light' API module is for setting light parameters for model draw.
* 
*   Notes:
*     - Game functions handle much of this for you, so only use this module if you have an
*       explicit reason to, and know what you're doing.
*     - As of v1.5, these functions only apply to Chunk models and spotlight functions are
*       non-functional.
* 
*   Version History:
*     - v1.5.0.0        : Version 0, initial release
* 
*   Availability:
*     - Before Init     : No
*     - At Init         : Yes
*     - After Init      : Yes
*/
#ifndef H_RFAPI_LIGHT
#define H_RFAPI_LIGHT

/********************************/
/*  Constants                   */
/********************************/
/****** API Module Version **********************************************************************/
#define RFAPI_LIGHT_VER             (0) /* light api version                                    */

/********************************/
/*  Enums                       */
/********************************/
/****** Light Index *****************************************************************************/
typedef enum rjlight
{
    RJ_LIGHT_ALL = -1,              /* apply to all lights                                      */

    RJ_LIGHT_1,                     /* light index 1                                            */
    RJ_LIGHT_2,                     /* light index 2                                            */
    RJ_LIGHT_3,                     /* light index 3                                            */
    RJ_LIGHT_4,                     /* light index 4                                            */
    RJ_LIGHT_5,                     /* light index 5                                            */
    RJ_LIGHT_6,                     /* light index 6                                            */

    RJ_LIGHT_NUM,                   /* enum count                                               */
}
RJ_LIGHT;

/********************************/
/*  API Structures              */
/********************************/
/****** Font API ********************************************************************************/
typedef struct
{
    uint32_t version;               /* structure version                                        */

    /****** Version >= 0 ********************************************************************/

    /**** Light Switch **************************************/
    /*
    *   Description:
    *     Switch a light on/off.
    *
    *   Parameters:
    *     - light       : light index                                          [RJ_LIGHT_#]
    *     - flag        : on/off flag                                              [ON/OFF]
    */
    void (*SetLightSwitch)( Int light, Int flag );

    /**** Light Color ***************************************/
    /*
    *   Description:
    *     Set a light color.
    *
    *   Notes:
    *     - Light 'intensity' is set to '1.f'. To set a custom intensity, use
    *       'SetLightIntensity' after calling.
    *
    *   Parameters:
    *     - light       : chunk light                                          [RJ_LIGHT_#]
    *     - lr,lg,lb    : color                                                   [0.f~1.f]
    */
    void (*SetLightColor)( Int light, Float lr, Float lg, Float lb );
    /*
    *   Description:
    *     Set the ambient light color.
    *
    *   Notes:
    *     - Ambient 'intensity' value is set to the largest color component value. To set a
    *       custom intensity, use 'SetLightIntensity' instead.
    *
    *   Parameters:
    *     - ar,ag,ab    : ambient color                                           [0.f~1.f]
    */
    void (*SetAmbient)( Float ar, Float ag, Float ab );

    /**** Light Intensity ***********************************/
    /*
    *   Description:
    *     Set a light intensity, and optionally the ambient intensity. This is used
    *   to emulate lighting effects in intensity draw functions (non-multi funcs).
    *
    *   Notes:
    *     - Only 1 ambient color can be set. So, a color set with 'SetAmbient' will be
    *       overwritten by this function *if* ambient intensity is set (not -1).
    *     - Ambient is not updated when 'LIGHT_ALL' is used.
    *
    *   Parameters:
    *     - light       : chunk light                                          [RJ_LIGHT_#]
    *     - inten       : light intensity                                         [0.f~1.f]
    *     - ambient     : ambient intensity                            [opt: -1.f; 0.f~1.f]
    */
    void (*SetLightIntensity)( Int light, Float inten, Float ambient );

    /**** Light Modes ***************************************/
    /*
    *   Description:
    *     Set a light vector, and set the light mode to directional.
    *
    *   Notes:
    *     - Vector is *not* normalized.
    *
    *   Parameters:
    *     - light       : light index                                              [RJ_LIGHT_#]
    *     - vx,vy,vz    : direction vector
    */
    void (*SetLightVector)( Int light, Float vx, Float vy, Float vz );
    /*
    *   Description:
    *     Set a light position, and set the light mode to point.
    *
    *   Parameters:
    *     - light       : light index                                              [RJ_LIGHT_#]
    *     - px,py,pz    : position
    */
    void (*SetLightPoint)( Int light, Float px, Float py, Float pz );
    /*
    *   Description:
    *     Set a light position and vector, and set the light mode to spotlight.
    * 
    *   Notes:
    *     - Vector is *not* normalized.
    *     - Function not implemented, currently no-op.
    *
    *   Parameters:
    *     - light       : light index                                              [RJ_LIGHT_#]
    *     - p           : position                                               [opt: nullptr]
    *     - v           : direction                                              [opt: nullptr]
    */
    void (*SetLightSpot)( Int light, const NJS_POINT3* p, const NJS_VECTOR* v );

    /**** Light Param ***************************************/
    /*
    *   Description:
    *     Set light near and far ranges, for point/spot modes.
    *
    *   Notes:
    *     - Anything closer than near is clamped to max intensity, then intensity falls off
    *       linearly until the far range.
    *
    *   Parameters:
    *     - light       : light index                                              [RJ_LIGHT_#]
    *     - nrange      : near range
    *     - frange      : far range
    */
    void (*SetLightRange)( Int light, Float nrange, Float frange );
    /*
    *   Description:
    *     Set light inner and outer angles, for spot mode.
    *
    *   Notes:
    *     - Anything within the inner angle is clamped to max intensity, then intensity falls
    *       off linearly until the outer angle.
    *     - Function not implemented, currently no-op.
    *
    *   Parameters:
    *     - light       : light index                                              [RJ_LIGHT_#]
    *     - iang        : inner angle
    *     - oang        : outer angle
    */
    void (*SetLightAngle)( Int light, Angle iang, Angle oang );

    /**** Light Matrix **************************************/
    /*
    *   Description:
    *     Set light vector/position to the current matrix, keeping it fixed in world space.
    * 
    *   Notes:
    *     - If not handled, the light will remain relative to the camera.
    *
    *   Parameters:
    *     - light       : light index                                              [RJ_LIGHT_#]
    */
    void (*SetLightMatrix)( Int light );
}
RFAPI_LIGHT;

#endif/*H_RFAPI_LIGHT*/
