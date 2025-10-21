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
DrawMovieHook(int posX, int posY, int sclX, int sclY, float depth, int unk)
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

/****** Init ************************************************************************************/
void
EVR_MovieInit(void)
{
    if ( EventEnforce43 != EV_43MD_NEVER )
    {
        return;
    }

    WriteCall(0x005FF311, DrawMovieHook);
}
