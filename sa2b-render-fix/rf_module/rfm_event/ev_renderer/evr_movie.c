/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writeop.h>           /* write call                                               */
#include <samt/writemem.h>          /* write data                                               */
#include <samt/funchook.h>          /* function hook                                            */

/****** Game ************************************************************************************/
#include <samt/sonic/task.h>        /* task                                                     */
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
    // make an exception for geralds diary, as it's not supposed to fit the screen
    if ( EventNum == 203 )
    {
        DrawMovie_Fill(x, y, w, h, z, color, CNFE_EVENT_MOVIE_FIT);
        return;
    }

    DrawMovie_Fill(x, y, w, h, z, color, MovieFmvFit);
}

/****** Hook Task *******************************************************************************/
static void
TextureMovieDestroyTask(task* tp)
{
    // only textureMovie uses this displayer
    // effectMovie uses a later one
    if ( !tp->disp ) 
    {
        DestroyTask(tp);
    }
    else // textureMovie, freeze!
    {
        tp->exec = nullptr;
    }
}

#define TextureMovieTask        DATA_REF(task*, 0x01AEDE0C)
#define EffectMovieTask         DATA_REF(task*, 0x01AEDE10)

static void
FreeMovieTasks(void)
{
    if ( TextureMovieTask )
    {
        DestroyTask(TextureMovieTask);
    }

    if ( EffectMovieTask )
    {
        DestroyTask(EffectMovieTask);
    }
}

#define TextureMovieCreate      FUNC_PTR(void, __cdecl, (char*, int), 0x005FADD0)
#define EffectMovieCreate       FUNC_PTR(void, __cdecl, (void*)     , 0x005FAFB0)

static mt_hookinfo TextureMovieHookInfo[1];
static void
TextureMovieHook(char* fname, int texnum)
{
    FreeMovieTasks();

    mtHookInfoCall( TextureMovieHookInfo, TextureMovieCreate(fname, texnum) );
}

static mt_hookinfo EffectMovieHookInfo[1];
static void
EffectMovieHook(void* moviewk)
{
    FreeMovieTasks();

    mtHookInfoCall( EffectMovieHookInfo, EffectMovieCreate(moviewk) );
}

/****** Init ************************************************************************************/
void
EVR_MovieInit(void)
{
    WriteCall(0x005FF311, DrawMovieEffect);
    WriteCall(0x0060190E, DrawMovieFMV);

    WriteJump(0x005FAEF7, TextureMovieDestroyTask);

    mtHookFunc(TextureMovieHookInfo, TextureMovieCreate, TextureMovieHook);
    mtHookFunc(EffectMovieHookInfo , EffectMovieCreate , EffectMovieHook);

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
