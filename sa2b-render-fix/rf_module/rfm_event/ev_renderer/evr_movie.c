/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writeop.h>           /* write call                                               */
#include <samt/writemem.h>          /* write data                                               */

/****** Game ************************************************************************************/
#include <samt/sonic/display.h>     /* display                                                  */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Config **********************************************************************************/
#include <cnf.h>                    /* config get                                               */

/****** Self ************************************************************************************/
#include <rf_module/rfm_event/ev_renderer/evr_internal.h> /* parent & siblings                  */

/********************************/
/*  Game Defs                   */
/********************************/
/****** Draw Movie ******************************************************************************/
#define DrawMovie                   FUNC_PTR(void, __cdecl, (int, int, int, int, float, int), 0x005F8D90)

/********************************/
/*  Source                      */
/********************************/
/****** Draw Movie ******************************************************************************/
static void
DrawMovieHook_Stretch(int posX, int posY, int sclX, int sclY, float depth, int unk)
{
    const float ratio = GetDisplayRatio();

    if ( ratio <= 1.f )
    {
        DrawMovie(posX, posY, sclX, sclY, depth, unk);
        return;
    }

    const float pos_adj = ((640.f * ratio) - 640.f) * 0.5f;

    const int new_xpos = (int)floorf((float)posX - pos_adj);
    const int new_xscl = (int)ceilf( (float)sclX * ratio);

    DrawMovie(new_xpos, posY, new_xscl, sclY, depth, unk);
}

static void
DrawMovieHook_Clamp(int posX, int posY, int sclX, int sclY, float depth, int unk)
{
    const float ratio = GetDisplayRatio();

    if ( ratio <= 1.f )
    {
        DrawMovie(posX, posY, sclX, sclY, depth, unk);
        return;
    }

    const int scl = sclX * 100;

    DrawMovie(posX      , posY, sclX, sclY, depth, unk);
    DrawMovie(posX      , posY, -scl, sclY, depth, unk);
    DrawMovie(sclX+(scl), posY, -scl, sclY, depth, unk);
}

static void
DrawMovieHook_Mirror(int posX, int posY, int sclX, int sclY, float depth, int unk)
{
    const float ratio = GetDisplayRatio();

    if ( ratio <= 1.f )
    {
        DrawMovie(posX, posY, sclX, sclY, depth, unk);
        return;
    }

    DrawMovie(posX       , posY,  sclX, sclY, depth, unk);
    DrawMovie(posX       , posY, -sclX, sclY, depth, unk);
    DrawMovie(sclX+(sclX), posY, -sclX, sclY, depth, unk);
}

static void
DrawMovieHook_Crop(int posX, int posY, int sclX, int sclY, float depth, int unk)
{
    const float ratio = GetDisplayRatio();

    if ( ratio <= 1.f )
    {
        DrawMovie(posX, posY, sclX, sclY, depth, unk);
        return;
    }

    const float pos_adj = ((640.f * ratio) - 640.f) * 0.5f;

    const int new_xpos = (int)floorf((float)posX - pos_adj);
    const int new_ypos = (int)floorf((float)posX - pos_adj);

    const int new_xscl = (int)ceilf((float)sclX * ratio);
    const int new_yscl = (int)ceilf((float)sclY * ratio);

    DrawMovie(new_xpos, new_ypos, new_xscl, new_yscl, depth, unk);
}

/****** Init ************************************************************************************/
void
EVR_MovieInit(void)
{
    if ( EventEnforce43 != EV_43MD_NEVER )
    {
        return;
    }

    switch ( CNF_GetInt(CNF_EVENT_OVERFIT) )
    {
        case CNFE_EVENT_OVERFIT_FIT: default:
        {
            break;
        }
        case CNFE_EVENT_OVERFIT_STRETCH:
        {
            WriteCall(0x005FF311, DrawMovieHook_Stretch);
            break;
        }
        case CNFE_EVENT_OVERFIT_CLAMP:
        {
            WriteCall(0x005FF311, DrawMovieHook_Clamp);
            break;
        }
        case CNFE_EVENT_OVERFIT_MIRROR:
        {
            WriteCall(0x005FF311, DrawMovieHook_Mirror);
            break;
        }
        case CNFE_EVENT_OVERFIT_CROP:
        {
            WriteCall(0x005FF311, DrawMovieHook_Crop);
            break;
        }
    }
}
