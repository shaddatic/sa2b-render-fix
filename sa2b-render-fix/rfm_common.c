#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/memutil.h>
#include <sa2b/model.h>
#include <sa2b/funchook.h>
#include <sa2b/mods.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/task.h>
#include <sa2b/src/score.h>
#include <sa2b/src/njctrl.h>
#include <sa2b/src/texture.h>

/** Std **/
#include <stdio.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_usermsg.h>
#include <rf_file.h>
#include <rf_mdlutil.h>
#include <rf_util.h>

/** Self **/
#include <rfm_common.h>
#include <rfm_common/rfc_internal.h>

#define ReplaceObjectModel(pobject, pmodel)        ((NJS_CNK_OBJECT*)pobject)->model = pmodel

EXTERN NJS_CNK_MODEL model_e_kumi_emblem[];
EXTERN NJS_CNK_MODEL model_e_g_kumi_emblem[];
EXTERN NJS_CNK_MODEL model_e_b_kumi_emblem[];
EXTERN NJS_CNK_MODEL model_e_gold_emblem[];
EXTERN NJS_CNK_MODEL model_e_kyoko_emblem[];

EXTERN NJS_CNK_MODEL model_e_shouko_wing_port[];
EXTERN NJS_CNK_MODEL model_e_shouko_wing_starboard[];
EXTERN NJS_CNK_MODEL model_e_shouko_aft[];

EXTERN NJS_CNK_MODEL model_e_g_pathkumi_emblem[];
EXTERN NJS_CNK_MODEL model_e_b_pathkumi_emblem[];

EXTERN NJS_CNK_MODEL model_e_t_emi_emblem[];
EXTERN NJS_CNK_MODEL model_e_a_emi_emblem[];

EXTERN NJS_CNK_MODEL model_ce_truck_hood[];

EXTERN NJS_CNK_MODEL model_e_s_ai_shield[];

#define CurrentLevel            DataRef(int16_t, 0x01934B70)

static int __fastcall
EnemyLoadTextureStage(const char* fname, NJS_TEXLIST* ptlo)
{
    char strbuf[260];

    snprintf(strbuf, 260, "%s_STG%02i", fname, CurrentLevel);

    const int err = texLoadTextureFile(strbuf, ptlo);

    if (err == -1)
        return texLoadTextureFile(fname, ptlo);

    return err;
}

EXTERN NJS_TEXLIST texlist_jo_tree[];

static GJS_OBJECT*
RF_GinjaLoadObjectFile(const utf8* fname)
{
    utf8 buf[260];

    snprintf(buf, 260, "%s/model/%s.sa2bmdl", GetModPath(), fname);

    return MDL_GinjaLoadObjectFile(buf);
}

#define ObjectGlobalLightManagerTaskPointer     DataRef(TASK*, 0x01A5A660)

static void
ObjectGlobalLightSWDestructor(TASK* tp)
{
    ObjectGlobalLightManagerTaskPointer = NULL;
}

#define ObjectGlobalLightManager    FuncPtr(void, __cdecl, (TASK*), 0x004CAB20)

static hook_info* ObjectGlobalLightManagerHookInfo;
static void
ObjectGlobalLightManagerHook(TASK* tp)
{
    FuncHookCall( ObjectGlobalLightManagerHookInfo, ObjectGlobalLightManager(tp) );

    tp->dest = ObjectGlobalLightSWDestructor;
}

void
RFM_CommonInit(void)
{
    if (RF_ConfigGetInt(CNF_COMMON_TR_SORT))
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

        if (RF_ConfigGetInt(CNF_DEBUG_DCSHAD_PATCH))
        {
            WriteNoOP(0x00612C86, 0x00612CAA);  // DC Shadows crash patch for Boss Bogy
        }

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
    }

    WriteData(0x0044FE36, 0x1, uint8_t); // Fix green hill "CLEAR!" text

    if (RF_ConfigGetInt(CNF_COMMON_EEMBLEM))
    {
        if (ModCheckDll("RestoredGUNLogos"))
            RF_ModConflictEx("Restored GUN Logos", "GUN Emblem Fix");

        ReplaceObjectModel(0x014AB36C, model_e_kumi_emblem);
        ReplaceObjectModel(0x014ACF5C, model_e_g_kumi_emblem);
        ReplaceObjectModel(0x014AF6B4, model_e_b_kumi_emblem);

        ReplaceObjectModel(0x01492BA4, model_e_gold_emblem);

        ReplaceObjectModel(0x014CA69C, model_e_kyoko_emblem);

        ReplaceObjectModel(0x014CEA4C, model_e_shouko_wing_port);
        ReplaceObjectModel(0x014CE784, model_e_shouko_wing_starboard);
        ReplaceObjectModel(0x014CE4BC, model_e_shouko_aft);

        ReplaceObjectModel(0x01497AE4, model_e_g_pathkumi_emblem);
        ReplaceObjectModel(0x01495B8C, model_e_b_pathkumi_emblem);

        ReplaceObjectModel(0x014C9924, model_e_t_emi_emblem);
        ReplaceObjectModel(0x014C7744, model_e_a_emi_emblem);

        //WriteData(0x109D4B4, *model_ce_truck_hood, NJS_CNK_MODEL);
        MemCopy((void*)0x109B2CC, model_ce_truck_hood, sizeof(NJS_CNK_MODEL));
    }

    if (RF_ConfigGetInt(CNF_COMMON_AISHEILD))
    {
        ReplaceObjectModel(0x014BC1A4, model_e_s_ai_shield);
    }

    if (RF_ConfigGetInt(CNF_COMMON_ESTGTEX))
    {
        WriteCall(0x004FE3E6, EnemyLoadTextureStage);
    }

    if (RF_ConfigGetInt(CNF_COMMON_TR_CHAOS))
    {
        constexpr int chaos_alpha = 0xBB;

        CnkMaterialDiffuse(0x01470D58, 0, chaos_alpha, -1, -1, -1);
        CnkMaterialDiffuse(0x01481448, 0, chaos_alpha, -1, -1, -1);
        CnkMaterialDiffuse(0x0147A608, 0, chaos_alpha, -1, -1, -1);
        CnkMaterialDiffuse(0x014869A0, 0, chaos_alpha, -1, -1, -1);
        CnkMaterialDiffuse(0x01476D78, 0, chaos_alpha, -1, -1, -1);
        CnkMaterialDiffuse(0x0148BE88, 0, chaos_alpha, -1, -1, -1);

        CnkMaterialFlagOn(0x01470D58, 0, NJD_FST_UA);
        CnkMaterialFlagOn(0x01481448, 0, NJD_FST_UA);
        CnkMaterialFlagOn(0x0147A608, 0, NJD_FST_UA);
        CnkMaterialFlagOn(0x014869A0, 0, NJD_FST_UA);
        CnkMaterialFlagOn(0x01476D78, 0, NJD_FST_UA);
        CnkMaterialFlagOn(0x0148BE88, 0, NJD_FST_UA);

        /** They won't draw correctly unless we set it to use disp_sort **/

        SwitchDisplayer(0x00508358, DISP_SORT);
    }

    if (RF_ConfigGetInt(CNF_COMMON_TR_BLOON))
    {
        WriteNoOP(0x006DB64D, 0x006DB656); // Balloon
        WriteRetn(0x6DB3B0);

        WriteData(0x00624E45, DISP_SORT, uint8_t); // Baloon (Cart)
        WriteNoOP(0x00625199, 0x0062519B);

        static const double bloondbl = 85.0;

        ReplaceFloat(0x006251EE, &bloondbl);
    }

    if (RF_ConfigGetInt(CNF_COMMON_TR_GOAL))
    {
        CnkModelMaterialFlagOn(0x00B4EACC, 1, NJD_FST_UA);

        CnkModelMaterialFlagOff(0x00B4EC6C, 0, NJD_FST_DB); // GOAL text
        CnkModelMaterialFlagOff(0x00B4EE0C, 0, NJD_FST_DB); // BACK text

        /** It won't draw correctly unless we set it to use disp_sort,
            this flips things around so "it just works!" **/

        SwitchDisplayer(0x006C651E, DISP_SORT);
        SwitchDisplayer(0x006C6525, DISP);
    }

    if (RF_ConfigGetInt(CNF_COMMON_EJET))
    {
        RFC_EnemyJet();
    }

    if (RF_ConfigGetInt(CNF_COMMON_UDREEL))
    {
        RFC_UDReelInit();
    }

    if (RF_ConfigGetInt(CNF_COMMON_ITEMBOX))
    {
        RFC_ItemBoxInit();
    }

    if (RF_ConfigGetInt(CNF_COMMON_JOTREE))
    {
        GJS_OBJECT* object_jo_tree = RF_GinjaLoadObjectFile("jo_tree");

        WritePointer(0x01072D5C, texlist_jo_tree); // Green Forest

        WritePointer(0x010737B4, object_jo_tree->model); // Green Forest
    }

    if (RF_ConfigGetInt(CNF_COMMON_EXPLOSION))
    {
        RFC_ExplosionInit();
    }

    if (RF_ConfigGetInt(CNF_COMMON_MIZUGOMI))
    {
        RFC_MizugomiInit();
    }

    if (RF_ConfigGetInt(CNF_COMMON_DCRING))
    {
        GjsModelTintFix(0x00B58288);
    }

    if (RF_ConfigGetInt(CNF_DEBUG_CHAOS0TEX))
    {
        RFC_Chaos0TexInit();
    }

    if (RF_ConfigGetInt(CNF_COMMON_PRSIREN))
    {
        RFC_PrisonSirenInit();
    }

    ObjectGlobalLightManagerHookInfo = FuncHook(ObjectGlobalLightManager, ObjectGlobalLightManagerHook);
}
