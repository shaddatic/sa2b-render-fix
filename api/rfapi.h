/*
*   SA2 Render Fix - '/rfapi.h'
*
*   Description:
*     Main header for Render Fix's external API modules. For instructions on usage, read the
*   'readme.md' file found with these headers.
*     These headers are to be imported into your project
*/
#ifndef H_RFAPI
#define H_RFAPI

/********************************/
/*  Types                       */
/********************************/
/****** Base Types ******************************************************************************/
typedef double                      f64;    /* 8 byte wide float value                          */
typedef char                        c8;     /* supports UTF-8 strings                           */

#ifdef SA2MODLOADER_H
/****** Mod Loader Compatibility ****************************************************************/
typedef NJS_OBJECT                  NJS_CNK_OBJECT; /* Mod Loader 'Object' compatibility        */

#endif/*SA2MODLOADER_H*/

/********************************/
/*  Macros                      */
/********************************/
/****** Mod Version *****************************************************************************/
/*
*   Description:
*     Macro for checking the current Render Fix version against a given version.
* 
*   Examples:
*     - if (!RFD_CHECKVER(pApi, 1,4,1,0) ) // check if RF version too low
*     - if ( RFD_CHECKVER(pApi, 1,4,1,0) ) // check if RF version equal to, or higher
*
*   Parameters:
*     - api         : core api pointer
*     - rel         : minimum release part
*     - maj         : minimum major part
*     - min         : minimum minor part
*     - hot         : minimum hotfix part
* 
*   Returns:
*     'true' if the current version is '>=' the given version; or 'false' if not.
*/
#define RFAPI_CHECKVER(api, rel, maj, min, hot) \
    ( (int)(api)->modver.release > (rel) || ( (int)(api)->modver.release == (rel) && \
    ( (int)(api)->modver.major   > (maj) || ( (int)(api)->modver.major   == (maj) && \
    ( (int)(api)->modver.minor   > (min) || ( (int)(api)->modver.minor   == (min) && \
    ( (int)(api)->modver.hotfix  > (hot) || ( (int)(api)->modver.hotfix  == (hot) ))))))) )

/********************************/
/*  Internal Includes           */
/********************************/
/****** API Modules *****************************************************************************/
#include "rfapi_control.h"          /* mod control api module                                   */
#include "rfapi_config.h"           /* mod config api module                                    */
#include "rfapi_feature.h"          /* mod feature api module                                   */
#include "rfapi_draw.h"             /* draw api module                                          */
#include "rfapi_rstate.h"           /* render state api module                                  */
#include "rfapi_shader.h"           /* shader api module                                        */
#include "rfapi_font.h"             /* font/text api module                                     */
#include "rfapi_ninja.h"            /* ninja system api module                                  */
#include "rfapi_njdraw.h"           /* ninja draw api module                                    */
#include "rfapi_chunk.h"            /* chunk model api module                                   */
#include "rfapi_light.h"            /* lighting api module                                      */
#include "rfapi_shadow.h"           /* cheap shadow api module                                  */

/****** Core API ********************************************************************************/
#include "rfapi_core.h"             /* api core                                                 */

#endif/*H_RFAPI*/
