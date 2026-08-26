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
*     - v1.5.5.0        : Version 3, added Shadow API module
*/
#ifndef H_RFAPI_CORE
#define H_RFAPI_CORE

/********************************/
/*  Constants                   */
/********************************/
/****** API Module Version **********************************************************************/
#define RFAPI_CORE_VER              (3) /* core api version                                     */

/********************************/
/*  API Structures              */
/********************************/
/****** Core API ********************************************************************************/
typedef struct
{
    int32_t version;                /* structure version                                        */

    /****** Version >= 0 ************************************************************************/

    /**** Mod Version ***************************************/

    struct
    {
        uint8_t release;            /* release version part           (eg. the '1' in v1.2.3.4) */
        uint8_t major;              /* major version part             (eg. the '2' in v1.2.3.4) */
        uint8_t minor;              /* minor version part             (eg. the '3' in v1.2.3.4) */
        uint8_t hotfix;             /* hotfix version part            (eg. the '4' in v1.2.3.4) */
    }
    modver;

    /**** API Modules ***************************************/

    const RFAPI_CONTROL*        api_control;    /* control module                               */
    const RFAPI_CONFIG*         api_config;     /* config module                                */
    const RFAPI_FEATURE*        api_feature;    /* feature check module                         */
    const RFAPI_DRAW*           api_draw;       /* draw module                                  */
    const RFAPI_RENDERSTATE*    api_rstate;     /* render state module                          */
    const RFAPI_SHADER*         api_shader;     /* shader module                                */

    /****** Version >= 1 ************************************************************************/

    const RFAPI_FONT*           api_font;       /* font module                                  */

    /****** Version >= 2 ************************************************************************/

    const RFAPI_NINJA*          api_ninja;      /* ninja system module                          */
    const RFAPI_NJDRAW*         api_njdraw;     /* ninja draw module                            */
    const RFAPI_CHUNK*          api_chunk;      /* chunk model module                           */
    const RFAPI_LIGHT*          api_light;      /* lighting module                              */

    /****** Version >= 3 ************************************************************************/

    const RFAPI_SHADOW*         api_shadow;     /* cheap shadow module                          */
}
RFAPI, RFAPI_CORE;

#endif/*H_RFAPI_CORE*/
