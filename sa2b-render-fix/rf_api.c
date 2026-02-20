/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/modinfo.h>           /* mod info                                                 */
#include <samt/modloader.h>         /* mod loader                                               */

/****** Utility *********************************************************************************/
#include <samt/util/dllexport.h>    /* dll export                                               */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Ninja ***********************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Self ************************************************************************************/
#include <rf_api.h>                 /* self                                                     */
#include <rf_api/rfapi_internal.h>  /* children                                                 */

/********************************/
/*  Types                       */
/********************************/
/****** API Module Version **********************************************************************/
typedef i32(__cdecl RF_INIT)(const RFAPI_CORE*, const c8*, const HelperFunctions*, isize);

/********************************/
/*  Extern Variables            */
/********************************/
/****** Core API ********************************************************************************/
EXPORT_DLL
const RFAPI_CORE rfapi_core =
{
    .version = RFAPI_CORE_VER,

    .modver = { 1,5,2,1 },

    .pControl     = &rfapi_control,
    .pConfig      = &rfapi_config,
    .pFeature     = &rfapi_feature,
    .pDraw        = &rfapi_draw,
    .pRenderState = &rfapi_rstate,
    .pShader      = &rfapi_shader,

    .pFont = &rfapi_font,

    .pNinja          = &rfapi_ninja,
    .pNjDraw         = &rfapi_njdraw,
    .pChunk          = &rfapi_chunk,
    .pLight          = &rfapi_light,
};

/********************************/
/*  Source                      */
/********************************/
/****** Call API ********************************************************************************/
void
RFAPI_CallFuncs(RF_APIFUNC apifn)
{
    /****** Static **************************************************************************/

    static const c7* const FuncNames[RF_NB_APIFUNC] =
    {
        [RF_APIFUNC_INIT]  = "RFAPI_Init",
        [RF_APIFUNC_EARLY] = "RFAPI_Early",
        [RF_APIFUNC_LATE]  = "RFAPI_Late",

        [RF_APIFUNC_OLD_INIT]  = "RF_Init",
        [RF_APIFUNC_OLD_EARLY] = "RF_EarlyInit",
    };

    /****** Start ***************************************************************************/

    const c7* pc_apifn = FuncNames[apifn];

    const isize nb_mod = miGetModCount();

    for ( isize i = 0; i < nb_mod; ++i )
    {
        const ml_modinfo* p_mi = miGetInfoByIndex(i);

        RF_INIT* fn_init = miGetExport(p_mi, pc_apifn);

        if ( !fn_init )
        {
            continue;
        }

        const i32 val = fn_init(&rfapi_core, p_mi->puPath, mtGetHelperFunctions(), i);

        if ( apifn < RF_APIFUNC_OLD_INIT && val != 0 )
        {
            RF_MsgWarn(
                "[API] Unexpected Return Value",

                "Return value from user-exported function was != 0 (%i). "
                "The function is either malformed or made for a later version of Render Fix!", val
            );
        }
    }
}
