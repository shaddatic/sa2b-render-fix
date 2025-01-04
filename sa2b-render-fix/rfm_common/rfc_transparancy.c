/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */
#include <sa2b/writemem.h>  /* WriteData, WritePointer                              */
#include <sa2b/writeop.h>   /* WriteNOP                                             */
#include <sa2b/funchook.h>  /* FuncHook                                             */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h> /* ninja                                              */

/****** Game ************************************************************************/
#include <sa2b/sonic/task.h>    /* task                                             */
#include <sa2b/sonic/datadll.h> /* data_dll                                         */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_util.h>        /* ReplaceFloat, SwitchDisplayer                        */
#include <rf_config.h>      /* RF_ConfigGet                                         */
#include <rf_mdlutil.h>     /* cnkmatflag                                           */
#include <rf_renderstate.h> /* renderstate                                          */

/****** Self ************************************************************************/
#include <rfm_common/rfc_transparancy/rfct_internal.h> /* self                      */

/************************/
/*  Game Functions      */
/************************/
/****** MS Car Displayer ************************************************************/
#define ObjectMSCarDisp         FUNC_PTR(void, __cdecl, (task*), 0x005B56D0)

/************************/
/*  Game References     */
/************************/
/****** Dry Lagoon Models ***********************************************************/
#define ButterflyList           DATA_ARY(NJS_CNK_MODEL*, 0x00DDB64C, [9])

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static hook_info ObjectMSCarDispHookInfo[1];
static void
ObjectMSCarDispHook(task* tp)
{
    const int backup_rmode = _gj_render_mode_;

    _gj_render_mode_ = GJD_DRAW_SOLID | GJD_DRAW_TRANS;

    FuncHookCall( ObjectMSCarDispHookInfo, ObjectMSCarDisp(tp) );

    _gj_render_mode_ = backup_rmode;
}

static void
TransformObjectWithSorting(const NJS_CNK_OBJECT* object, void* pFunc)
{
    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_OPAQUE);

    njCnkTransformObject(object, pFunc);

    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_TRANSPARENT);

    njCnkTransformObject(object, pFunc);

    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_END);
}

/****** Init ************************************************************************/
void
RFC_TransparancyInit(void)
{
    if (!RF_ConfigGetInt(CNF_COMMON_TR_SORT))
        return;

    /** Displayer switching **/
    {
        SwitchDisplayer(0x006EDB91, DISP_SORT); // Water Ripples
        SwitchDisplayer(0x0075A166, DISP_DELY); // Bubble draw fix
        SwitchDisplayer(0x006FD65E, DISP_SORT); // PC Wall

        SwitchDisplayer(0x005113AA, DISP_DELY); // Enemy Jet
        SwitchDisplayer(0x00511422, DISP_DELY); // ^

        WritePointer(0x005BA0F6, 0x0117EEEC); // Sky Rail clouds
        WritePointer(0x005BA13E, 0x0117EE34); // ^

        SwitchDisplayer(0x004B39CD, DISP_SORT); // P-Hill clouds

        SwitchDisplayer(0x006A5338, DISP_SORT); // W-Canyon Fans

        SwitchDisplayer(0x007048E6, DISP_SORT); // P-Cave Spiderwebs
        SwitchDisplayer(0x0070248C, DISP_SORT); // P-Cave Wall Eyes
        SwitchDisplayer(0x006FC851, DISP_SORT); // P-Cave Chimney
        SwitchDisplayer(0x00701F3E, DISP_SORT); // P-Cave Firepot Fire
        SwitchDisplayer(0x00707826, DISP_SORT); // P-Cave Snakedish Fire
        SwitchDisplayer(0x007042E7, DISP_SORT); // P-Cave Awning Fire
        SwitchDisplayer(0x00707E27, DISP_SORT); // P-Cave Snake Head Fire
        SwitchDisplayer(0x006FE59E, DISP_SORT); // P-Cave Torch Cup Fire

        SwitchDisplayer(0x00762D75, DISP_LAST); // Boss Title Text

        SwitchDisplayer(0x00501BA5, DISP_SORT); // Enemy Ghosts

        SwitchDisplayer(0x0060B5CE, DISP_SORT); // Boss Bogy
        SwitchDisplayer(0x00761C04, DISP_LAST); // Boss Bogy Powergauge

        SwitchDisplayer(0x0044F845, DISP_LAST); // Results Score Text
        SwitchDisplayer(0x00450805, DISP_LAST); // Results Time Text
        SwitchDisplayer(0x0044F65B, DISP_LATE); // Results Window
        SwitchDisplayer(0x004531DF, DISP_LATE); // Results Ring Window
        SwitchDisplayer(0x004531E6, DISP_LAST); // Results Ring Window

        SwitchDisplayer(0x00476CAF, DISP_SORT); // "PlayerDrawMotionWithAlphaReducing"

        SwitchDisplayer(0x00545633, DISP_SORT); // ALO_ChaosDrive

        SwitchDisplayer(0x0061BB94, DISP_DELY); // Cart HUD

        SwitchDisplayer(0x006054F6, DISP_SORT); // Tails Prison search lights

        SwitchDisplayer(0x006A5D89, DISP_SORT); // Wild Canyon flags (upper)

        SwitchDisplayer(0x006409E9, DISP_SORT); // Dry Lagoon Plant2
        SwitchDisplayer(0x006471F9, DISP_SORT); // Dry Lagoon Plant3
        SwitchDisplayer(0x0063D70F, DISP_DELY); // Dry Lagoon BgDisp

        SwitchDisplayer(0x005B4944, DISP_SORT); // Mission Street Cars
        FuncHook(ObjectMSCarDispHookInfo, ObjectMSCarDisp, ObjectMSCarDispHook);

        SwitchDisplayer(0x0070397F, DISP_SORT); // PC Chained Hoops
    }

    /** Chao World Lobby Exit **/
    WriteData(0x0057F39F, 0x54, u8);   // swap the draw calls for the base and plating models.
    WriteData(0x0057F3B3, 0xB7, u8);   // ^^
    WriteNOP( 0x0057F519, 0x0057F52D); // kill duplicate plate draw during 'disp_dely', as it breaks with the new LESSEQUAL Z compare
    WriteData(0x0057F54E, 0x08, u8);   // add esp, 10h -> add esp, 8h

    /** Dry Lagoon Butterfly flag fix (a material lacks UA when it should) **/
    for (int i = 0; i < ARYLEN(ButterflyList); ++i)
    {
        CnkModelMaterialFlagOn(ButterflyList[i], 0, NJD_FST_UA);
    }

    /** Enemy chaos transparancy fix **/
    {
        CnkMaterialFlagOn(0x01470D58, 0, NJD_FST_UA | NJD_FST_DB);
        CnkMaterialFlagOn(0x01481448, 0, NJD_FST_UA | NJD_FST_DB);
        CnkMaterialFlagOn(0x0147A608, 0, NJD_FST_UA | NJD_FST_DB);
        CnkMaterialFlagOn(0x014869A0, 0, NJD_FST_UA | NJD_FST_DB);
        CnkMaterialFlagOn(0x01476D78, 0, NJD_FST_UA | NJD_FST_DB);
        CnkMaterialFlagOn(0x0148BE88, 0, NJD_FST_UA | NJD_FST_DB);

        /** They won't draw correctly unless we set it to use disp_sort **/

        SwitchDisplayer(0x00508358, DISP_SORT);
    }

    /** Carts **/
    WriteCall(0x0061CB2F, TransformObjectWithSorting);
    WriteCall(0x0068B837, TransformObjectWithSorting); // menu

    /** Chaos Drives **/
    WriteCall(0x0054531F, TransformObjectWithSorting); // chao
    WriteCall(0x0048F305, TransformObjectWithSorting); // game

    /** clear text **/
    WriteData(0x0044FE36, 0x1, uint8_t); // Fix green hill "CLEAR!" text

    /** 2p character select cursor **/
    {
        NJS_CNK_OBJECT** p_obj = GetDataDllAddr(NJS_CNK_OBJECT*, "cursorObj");

        CnkObjectMaterialFlagOn(p_obj[0], NJD_FST_UA);
        CnkObjectMaterialFlagOn(p_obj[1], NJD_FST_UA);
    }

    /** Chao Garden Bunny Minimal Ears **/
    CnkObjectMaterialFlagOn(0x012941D4, NJD_FST_UA);
    CnkObjectMaterialFlagOn(0x01293FCC, NJD_FST_UA);

    RFCT_ExplosionInit();
    RFCT_ItemBoxInit();
    RFCT_PrisonSirenInit();
    RFCT_FinalChaseGravityCylinderInit();
}
