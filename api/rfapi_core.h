/*
*   SA2 Render Fix - '/rfapi_core.h'
*
*   Description:
*     The 'Core' API is the central hub for accessing all other API modules. You can get it
*   through one of the mod export functions as an argument. Render Fix versions before '1.3'
*   did not have an API, and can't call your exported functions.
* 
*   Version History:
*     - v1.3.0.0: Version 0, initial release
*     - v1.3.1.0: Version 1, added Font API module
*     - v1.4.1.0: Version 2, ???
*/
#ifndef H_RFAPI_CORE
#define H_RFAPI_CORE

/********************************/
/*  API Structures              */
/********************************/
/****** Mod Version *****************************************************************************/
typedef struct
{
    uint8_t release;                /* release version part           (eg. the '1' in v1.2.3.4) */
    uint8_t major;                  /* major version part             (eg. the '2' in v1.2.3.4) */
    uint8_t semimajor;              /* semi-major version part        (eg. the '3' in v1.2.3.4) */
    uint8_t minor;                  /* minor version part             (eg. the '4' in v1.2.3.4) */
}
RF_VERSION;

/****** Core API ********************************************************************************/
typedef struct
{
    uint32_t version;               /* structure version                                        */

    /****** Version >= 0 ************************************************************************/

    /**** Mod Version ***************************************/

    RF_VERSION modver;                          /* current render fix version                   */

    /**** API Modules ***************************************/

    const RFAPI_CONTROL*     pApiControl;       /* Control API                                  */
    const RFAPI_CONFIG*      pApiConfig;        /* Config API                                   */
    const RFAPI_FEATURE*     pApiFeature;       /* Feature Check API                            */
    const RFAPI_DRAW*        pApiDraw;          /* Draw API                                     */
    const RFAPI_RENDERSTATE* pApiRenderState;   /* Render State API                             */
    const RFAPI_SHADER*      pApiShader;        /* Shader API                                   */

    /****** Version >= 1 ************************************************************************/
    const RFAPI_FONT*        pApiFont;          /* Font API                                     */
}
RFAPI_CORE;

#endif/*H_RFAPI_CORE*/
