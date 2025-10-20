/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writeop.h>           /* writecall                                                */
#include <samt/writemem.h>          /* writedata                                                */
#include <samt/funchook.h>          /* functionhook                                             */

/****** Game ************************************************************************************/
#include <samt/sonic/task.h>        /* task                                                     */
#include <samt/sonic/display.h>     /* resolution                                               */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_config.h>              /* RF_ConfigGet                                             */
#include <rf_ninja.h>               /* drawtexture                                              */

/****** RF Util *********************************************************************************/
#include <rfu_file.h>               /* core                                                     */

/****** Self ************************************************************************************/
#include <rf_module/rfm_global/rfg_internal.h> /* parent & siblings                             */

#define HudDraw_p                       FUNC_PTR(void, __cdecl, (void) , 0x0044E9C0)
#define ActionWindowDisp_p              FUNC_PTR(void, __cdecl, (task*), 0x007951A0)
#define DispTechniqueScoreDisplayer_p   FUNC_PTR(void, __cdecl, (task*), 0x0044D360)

#define DispWinnerAndContinueDisp_p     FUNC_PTR(void, __cdecl, (task*), 0x00451250)
#define CalcTotalTimeDisp_p             FUNC_PTR(void, __cdecl, (task*), 0x00450B10)
#define CalcTotalScoreDisp_p            FUNC_PTR(void, __cdecl, (task*), 0x0044FD90)
#define DisplayTotalRingsDispLate_p     FUNC_PTR(void, __cdecl, (task*), 0x00453190)

//
#define HudDraw                         HudDraw_p
#define ActionWindowDisp                ActionWindowDisp_p
#define DispTechniqueScoreDisplayer     DispTechniqueScoreDisplayer_p

#define DispWinnerAndContinueDisp       DispWinnerAndContinueDisp_p
#define CalcTotalTimeDisp               CalcTotalTimeDisp_p
#define CalcTotalScoreDisp              CalcTotalScoreDisp_p
#define DisplayTotalRingsDispLate       DisplayTotalRingsDispLate_p

/********************************/
/*  Source                      */
/********************************/
/****** DrawTexture *****************************************************************************/
static void
DrawTextureExWithPoint(const NJS_TEXTURE_VTX* polygon, Int flag)
{
    njTextureFilterMode( NJD_TEXTUREFILTER_POINTSAMPLE );

    rjDrawTextureEx( polygon, 4, flag );

    njTextureFilterMode( NJD_TEXTUREFILTER_BILINEAR );
}

static void
DrawTextureWithPoint(const NJS_TEXTURE_VTX* polygon, Int count, Int tex, Int flag)
{
    njTextureFilterMode( NJD_TEXTUREFILTER_POINTSAMPLE );

    rjDrawTexture( polygon, count, tex, flag );

    njTextureFilterMode( NJD_TEXTUREFILTER_BILINEAR );
}

__declspec(naked)
___DrawTextureExWithPoint(void)
{
    __asm
    {
        push        [esp+4]
        push        eax

        call        DrawTextureExWithPoint

        add esp, 8
        retn
    }
}

__declspec(naked)
___DrawTextureWithPoint(void)
{
    __asm
    {
        push        [esp+4]
        push        edx
        push        eax
        push        ecx

        call        DrawTextureWithPoint

        add esp, 16
        retn
    }
}

/****** Main HUD ********************************************************************************/
static mt_hookinfo HudDrawHookInfo[1];
static void
HudDrawHook(void)
{
    njTextureFilterMode( NJD_TEXTUREFILTER_POINTSAMPLE );

    mtHookInfoCall( HudDrawHookInfo, HudDraw() );

    njTextureFilterMode( NJD_TEXTUREFILTER_BILINEAR );
}

/****** Action Window ***************************************************************************/
static mt_hookinfo ActionWindowDispHookInfo[1];
static void
ActionWindowDispHook(task* tp)
{
    njTextureFilterMode( NJD_TEXTUREFILTER_POINTSAMPLE );

    mtHookInfoCall( ActionWindowDispHookInfo, ActionWindowDisp(tp) );

    njTextureFilterMode( NJD_TEXTUREFILTER_BILINEAR );
}

/****** Technique *******************************************************************************/
static mt_hookinfo DispTechniqueScoreDisplayerHookInfo[1];
static void
DispTechniqueScoreDisplayerHook(task* tp)
{
    njTextureFilterMode( NJD_TEXTUREFILTER_POINTSAMPLE );

    mtHookInfoCall( DispTechniqueScoreDisplayerHookInfo, DispTechniqueScoreDisplayer(tp) );

    njTextureFilterMode( NJD_TEXTUREFILTER_BILINEAR );
}

/****** Results Screen **************************************************************************/
static mt_hookinfo DispWinnerAndContinueDispHookInfo[1];
static void
DispWinnerAndContinueDispHook(task* tp)
{
    njTextureFilterMode( NJD_TEXTUREFILTER_POINTSAMPLE );

    mtHookInfoCall( DispWinnerAndContinueDispHookInfo, DispWinnerAndContinueDisp(tp) );

    njTextureFilterMode( NJD_TEXTUREFILTER_BILINEAR );
}

static mt_hookinfo CalcTotalTimeDispHookInfo[1];
static void
CalcTotalTimeDispHook(task* tp)
{
    njTextureFilterMode( NJD_TEXTUREFILTER_POINTSAMPLE );

    mtHookInfoCall( CalcTotalTimeDispHookInfo, CalcTotalTimeDisp(tp) );

    njTextureFilterMode( NJD_TEXTUREFILTER_BILINEAR );
}

static mt_hookinfo CalcTotalScoreDispHookInfo[1];
static void
CalcTotalScoreDispHook(task* tp)
{
    njTextureFilterMode( NJD_TEXTUREFILTER_POINTSAMPLE );

    mtHookInfoCall( CalcTotalScoreDispHookInfo, CalcTotalScoreDisp(tp) );

    njTextureFilterMode( NJD_TEXTUREFILTER_BILINEAR );
}

static mt_hookinfo DisplayTotalRingsDispLateHookInfo[1];
static void
DisplayTotalRingsDispLateHook(task* tp)
{
    njTextureFilterMode( NJD_TEXTUREFILTER_POINTSAMPLE );

    mtHookInfoCall( DisplayTotalRingsDispLateHookInfo, DisplayTotalRingsDispLate(tp) );

    njTextureFilterMode( NJD_TEXTUREFILTER_BILINEAR );
}

/****** Init ************************************************************************************/
void
RFG_UiFilterInit(void)
{
    const bool force_enable = ( 480.f >= DisplayResolutionY );

    if ( RF_ConfigGetInt( CNF_FONT_PTFILTER ) || force_enable ) // text filtering
    {
        WriteCall(0x006B5EF7, ___DrawTextureExWithPoint);
        WriteCall(0x006B6004, ___DrawTextureExWithPoint);
        WriteCall(0x0043F76F, ___DrawTextureExWithPoint);
        WriteCall(0x0043F7F4, ___DrawTextureExWithPoint);
        WriteCall(0x0043F962, ___DrawTextureExWithPoint);
        WriteCall(0x0043F9E5, ___DrawTextureExWithPoint);
        WriteCall(0x006B5B5B, ___DrawTextureExWithPoint);
        WriteCall(0x00585743, ___DrawTextureExWithPoint);
        WriteCall(0x006B57F1, ___DrawTextureExWithPoint);
        WriteCall(0x006B5A0B, ___DrawTextureExWithPoint);

        WriteCall(0x00496AAC, ___DrawTextureExWithPoint); // mission text, shadow
        WriteCall(0x00496B34, ___DrawTextureExWithPoint); // mission text

        WriteData(0x00543A73, 0, u32); // Chao World
        WriteData(0x00543A7D, 0, u32);
    }

    if ( RF_ConfigGetInt( CNF_EXP_UIFILTER ) ) // if ( force_enable ) // Hud filtering
    {
        mtHookFunc( HudDrawHookInfo                    , HudDraw_p                    , HudDrawHook );
        mtHookFunc( ActionWindowDispHookInfo           , ActionWindowDisp_p           , ActionWindowDispHook );
        mtHookFunc( DispTechniqueScoreDisplayerHookInfo, DispTechniqueScoreDisplayer_p, DispTechniqueScoreDisplayerHook );

        mtHookFunc( DispWinnerAndContinueDispHookInfo, DispWinnerAndContinueDisp_p, DispWinnerAndContinueDispHook );
        mtHookFunc( CalcTotalTimeDispHookInfo        , CalcTotalTimeDisp_p        , CalcTotalTimeDispHook );
        mtHookFunc( CalcTotalScoreDispHookInfo       , CalcTotalScoreDisp_p       , CalcTotalScoreDispHook );
        mtHookFunc( DisplayTotalRingsDispLateHookInfo, DisplayTotalRingsDispLate_p, DisplayTotalRingsDispLateHook );

        WriteCall(0x00496910, ___DrawTextureWithPoint); // mission number (1st, etc)
        WriteCall(0x00496986, ___DrawTextureWithPoint); // mission texture, left part (missio)
        WriteCall(0x004969E8, ___DrawTextureWithPoint); // mission texture, right part (on:)

        WriteCall(0x00471277, ___DrawTextureExWithPoint); // ribbon edge
        WriteCall(0x004712F7, ___DrawTextureExWithPoint); // ribbon main
    }
}
