/*
*   SA2 Render Fix - '/rfapi_control.h'
*
*   Description:
*     The 'Control' API module is for controlling aspects of RF and its features before the mod
*   has booted. This allows modders to turn certain features on/off as they need without
*   requiring the user to change a setting themselves.
* 
*   Version History:
*     - v1.3.0.0        : Version 0, initial release
*     - v1.4.0.0        : Version 1, added 'EventApplyModelDiffuse'
* 
*   Availability:
*     - RF_EarlyInit    : Yes
*     - RF_Init         : No
*     - After Init      : No
*/
#ifndef H_RFAPI_CONTROL
#define H_RFAPI_CONTROL

/********************************/
/*  API Structures              */
/********************************/
/****** Control API *****************************************************************************/
typedef struct
{
    uint32_t version;               /* structure version                                        */

    /****** Version >= 0 ************************************************************************/

    /**** Cheap Shadow **************************************/
    /*
    *   Description:
    *     Set Render Fix's modifier triangle buffer to a different size. Most
    *   useful for mods that draw a large number of modifiers and would otherwise
    *   max out the default buffer. If this is called multiple times, the largest
    *   values will be used.
    * 
    *   Notes:
    *     - The default values are: nbTri( 2048 ), nbTriList( 128 )
    * 
    *   Version History:
    *     - v1.3.2.0: the 'nbTriList' parameter is obsolete and does nothing
    * 
    *   Parameters:
    *     - nbTri     : Total number of triangles the buffer can store
    *     - nbTriList : Total number of models the buffer can store             [depricated]
    */
    void (__cdecl* SetModBufferSize)( int32_t nbTri, int32_t nbTriList );
    /*
    *   Description:
    *     Disable modifier shadows in Chao World. Useful if you intend to implement
    *   your own shadow system in Chao World.
    */
    void (__cdecl* CheapShadowChaoWorldDisable)( void );

    /****** Version >= 1 ************************************************************************/

    /**** Event *********************************************/
    /*
    *   Description:
    *     Set flag to apply model material diffuse in Events when using Render
    *   Fix's own Event Renderer.
    *
    *   Notes:
    *     - Diffuse will only be applied on models using a SimpleDraw variant.
    */
    void (__cdecl* EventApplyModelDiffuse)( void );
}
RFAPI_CONTROL;

#endif/*H_RFAPI_CONTROL*/
