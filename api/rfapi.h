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
*     - if (!RFD_CHECKVER(pApiCore, 1,4,1,0) ) // check if RF version too low
*     - if ( RFD_CHECKVER(pApiCore, 1,4,1,0) ) // check if RF version equal to, or higher
*
*   Parameters:
*     - api         : core api pointer
*     - rel         : minimum release part value
*     - maj         : minimum major part value 
*     - sem         : minimum semi-major part value 
*     - min         : minimum minor part value 
* 
*   Returns:
*     'true' if the current version is '>=' the given version; or 'false' if not.
*/
#define RFD_CHECKVER(api, rel, maj, sem, min) \
    ( (int)(api)->modver.release   > (rel) || ( (int)(api)->modver.release   == (rel) && \
    ( (int)(api)->modver.major     > (maj) || ( (int)(api)->modver.major     == (maj) && \
    ( (int)(api)->modver.semimajor > (sem) || ( (int)(api)->modver.semimajor == (sem) && \
    ( (int)(api)->modver.minor     > (min) || ( (int)(api)->modver.minor     == (min) ))))))) )

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

/****** Core API ********************************************************************************/
#include "rfapi_core.h"             /* api core                                                 */

#endif/*H_RFAPI*/
