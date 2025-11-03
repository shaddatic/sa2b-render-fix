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
#define DrawMovie                   FUNC_PTR(void, __cdecl, (int, int, int, int, float, u32), 0x005F8D90)

/********************************/
/*  Data                        */
/********************************/
/****** Settings ********************************************************************************/
static CNFE_EVENT_MOVIE MovieEffectFit;
static CNFE_EVENT_MOVIE MovieFmvFit;

/********************************/
/*  Source                      */
/********************************/
/****** Draw Movie ******************************************************************************/
static void
DrawMovie_Fill(int x, int y, int w, int h, float z, u32 color, CNFE_EVENT_MOVIE mode)
{
    const float ratio = (DisplayResolutionX / (f32)w) / (DisplayResolutionY / (f32)h);

    if ( ratio <= 1.f || EV_GetPillarbox(EventNum) )
    {
        DrawMovie(x, y, w, h, z, color);
        return;
    }

    switch ( mode )
    {
        case CNFE_EVENT_MOVIE_FIT: default:
        {
            DrawMovie(x, y, w, h, z, color);
            break;
        }
        case CNFE_EVENT_MOVIE_STRETCH:
        {
            const float pos_adj = ((640.f * ratio) - 640.f) * 0.5f;

            const int new_x = (int)floorf((float)x - pos_adj);
            const int new_w = (int)ceilf( (float)w * ratio);

            DrawMovie(new_x, y, new_w, h, z, color);
            break;
        }
        case CNFE_EVENT_MOVIE_CLAMP:
        {
            const int scl = w * 100;

            DrawMovie(x      , y, w   , h, z, color);
            DrawMovie(x      , y, -scl, h, z, color);
            DrawMovie(x+w+scl, y, -scl, h, z, color);
            break;
        }
        case CNFE_EVENT_MOVIE_MIRROR:
        {
            DrawMovie(x    , y,  w, h, z, color);
            DrawMovie(x    , y, -w, h, z, color);
            DrawMovie(x+w+w, y, -w, h, z, color);
            break;
        }
        case CNFE_EVENT_MOVIE_CROP:
        {
            const float pos_adj = ((640.f * ratio) - 640.f) * 0.5f;

            const int new_x = (int)floorf( (f32)x - pos_adj );
            const int new_y = (int)floorf( (f32)y - pos_adj );

            const int new_w = (int)ceilf( (f32)w * ratio );
            const int new_h = (int)ceilf( (f32)h * ratio );

            DrawMovie(new_x, new_y, new_w, new_h, z, color);
            break;
        }
    }
}

/****** Hook Movie ******************************************************************************/
static void
DrawMovieEffect(int x, int y, int w, int h, float z, u32 color)
{
    DrawMovie_Fill(x, y, w, h, z, color, MovieEffectFit);
}

static void
DrawMovieFMV(int x, int y, int w, int h, float z, u32 color)
{
    DrawMovie_Fill(x, y, w, h, z, color, MovieFmvFit);
}

/****** Init ************************************************************************************/
void
EVR_MovieInit(void)
{
    WriteCall(0x005FF311, DrawMovieEffect);
    WriteCall(0x0060190E, DrawMovieFMV);

    MovieEffectFit = CNF_GetInt(CNF_EVENT_OVERLAYFIT);
    MovieFmvFit    = CNF_GetInt(CNF_EVENT_MOVIEFIT);

    if ( MovieFmvFit == CNFE_EVENT_MOVIE_FIT )
    {
        for ( int i = 400; i < EV_PILLARBOX_NB; ++i )
        {
            EV_SetPillarbox(i, ON);
        }
    }
}
