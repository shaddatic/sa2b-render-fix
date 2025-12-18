/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Self ************************************************************************************/
#include <rf_api/rfapi_internal.h>  /* parent & siblings                                        */
#include <rf_ninja.h>               /* rf ninja                                                 */

/********************************/
/*  Extern Variables            */
/********************************/
/****** API Structure ***************************************************************************/
EXTERN
const RFAPI_NJDRAW rfapi_njdraw =
{
    .version = RFAPI_NJDRAW_VER,

    .DrawPolygon  = rjDrawPolygon,
    .DrawTexture  = rjDrawTexture,
    .DrawTextureH = rjDrawTextureH,

    .DrawTextureEx  = rjDrawTextureEx,
    .DrawTextureHEx = rjDrawTextureHEx,

    .DrawPolygon3DEx  = rjDrawPolygon3DEx,
    .DrawTexture3DEx  = rjDrawTexture3DEx,
    .DrawTexture3DHEx = rjDrawTexture3DHEx,

    .DrawLineStrip2D  = rjDrawLineStrip2D,
    .DrawLineList2D   = rjDrawLineList2D,

    .DrawLineStrip3D  = rjDrawLineStrip3D,
    .DrawLineList3D   = rjDrawLineList3D,

    .DrawSprite2D = rjDrawSprite2D,
    .DrawSprite3D = rjDrawSprite3D,

    .DrawPolygon2D = rjDrawPolygon2D,
};
