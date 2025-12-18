/*
*   SA2 Render Fix - '/rfapi_core.h'
*
*   Description:
*     The 'Core' API is the central hub for accessing all other API modules. You can get it
*   through one of the mod export functions as an argument. Render Fix versions before '1.3'
*   did not have an API, and can't call your exported functions.
* 
*   Version History:
*     - v1.3.0.0        : Version 0, initial release
*     - v1.3.1.0        : Version 1, added Font API module
*     - v1.5.0.0        : Version 2, added Ninja, Ninja Draw, Chunk, & Light API modules
*/
#ifndef H_RFAPI_CORE
#define H_RFAPI_CORE

/********************************/
/*  Constants                   */
/********************************/
/****** API Module Version **********************************************************************/
#define RFAPI_CORE_VER              (2) /* core api version                                     */

/********************************/
/*  API Structures              */
/********************************/
/****** Core API ********************************************************************************/
typedef struct
{
    uint32_t version;               /* structure version                                        */

    /****** Version >= 0 ************************************************************************/

    /**** Mod Version ***************************************/

    struct
    {
        uint8_t release;            /* release version part           (eg. the '1' in v1.2.3.4) */
        uint8_t major;              /* major version part             (eg. the '2' in v1.2.3.4) */
        uint8_t semimajor;          /* semi-major version part        (eg. the '3' in v1.2.3.4) */
        uint8_t minor;              /* minor version part             (eg. the '4' in v1.2.3.4) */
    }
    modver;

    /**** API Modules ***************************************/

    const RFAPI_CONTROL*     pControl;          /* control module                               */
    const RFAPI_CONFIG*      pConfig;           /* config module                                */
    const RFAPI_FEATURE*     pFeature;          /* feature check module                         */
    const RFAPI_DRAW*        pDraw;             /* draw module                                  */
    const RFAPI_RENDERSTATE* pRenderState;      /* render state module                          */
    const RFAPI_SHADER*      pShader;           /* shader module                                */

    /****** Version >= 1 ************************************************************************/
    const RFAPI_FONT*        pFont;             /* font module                                  */

    /****** Version >= 2 ************************************************************************/
    const RFAPI_NINJA*       pNinja;            /* ninja system module                          */
    const RFAPI_NJDRAW*      pNjDraw;           /* ninja draw module                            */
    const RFAPI_CHUNK*       pChunk;            /* chunk model module                           */
    const RFAPI_LIGHT*       pLight;            /* lighting module                              */
}
RFAPI, RFAPI_CORE;

#endif/*H_RFAPI_CORE*/
