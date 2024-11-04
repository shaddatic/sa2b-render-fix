#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/writeop.h>
#include <sa2b/model.h>
#include <sa2b/funchook.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/task.h>
#include <sa2b/sonic/score.h>
#include <sa2b/sonic/njctrl.h>
#include <sa2b/sonic/texture.h>
#include <sa2b/sonic/set.h>
#include <sa2b/sonic/landtable.h>

/** Std **/
#include <stdio.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_usermsg.h>
#include <rf_file.h>
#include <rf_mdlutil.h>
#include <rf_util.h>
#include <rf_renderstate.h>

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

#define CurrentLevel            DATA_REF(int16_t, 0x01934B70)

static int __fastcall
EnemyLoadTextureStage(const char* fname, NJS_TEXLIST* ptlo)
{
    char strbuf[260];

    snprintf(strbuf, 260, "%s_STG%02i", fname, CurrentLevel);

    const int err = texLoadTexturePrsFile(strbuf, ptlo);

    if (err == -1)
        return texLoadTexturePrsFile(fname, ptlo);

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

#define ObjectGlobalLightManagerTaskPointer     DATA_REF(task*, 0x01A5A660)

static void
ObjectGlobalLightSWDestructor(task* tp)
{
    ObjectGlobalLightManagerTaskPointer = NULL;
}

#define ObjectGlobalLightManager    FUNC_PTR(void, __cdecl, (task*), 0x004CAB20)

static hook_info ObjectGlobalLightManagerHookInfo[1];
static void
ObjectGlobalLightManagerHook(task* tp)
{
    FuncHookCall( ObjectGlobalLightManagerHookInfo, ObjectGlobalLightManager(tp) );

    tp->dest = ObjectGlobalLightSWDestructor;
}

#define ObjectGoalringDisp          FUNC_PTR(void, __cdecl, (task*), 0x006C6CD0)
#define ObjectGoalringDispSort      FUNC_PTR(void, __cdecl, (task*), 0x006C6F10)

static void
ObjectGoalringDispSortNew(task* tp)
{
    ObjectGoalringDisp(tp);
    ObjectGoalringDispSort(tp);
}

#define LandDisplayer               FUNC_PTR(void, __cdecl, (task*), 0x0047C270)
#define LandDisplayerTrans          FUNC_PTR(void, __cdecl, (task*), 0x0047C270)
#define DrawMotLandEntry            FUNC_PTR(void, __cdecl, (void) , 0x0047C6E0)

static hook_info LandDisplayerHookInfo[1];
static void
LandDisplayerHook(task* const tp)
{
    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_OPAQUE);

    FuncHookCall( LandDisplayerHookInfo, LandDisplayer(tp) );

    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_END);
}

static hook_info LandDisplayerTransHookInfo[1];
static void
LandDisplayerTransHook(task* const tp)
{
    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_TRANSPARENT);

    FuncHookCall( LandDisplayerTransHookInfo, LandDisplayerTrans(tp) );

    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_END);
}

static hook_info DrawMotLandEntryHookInfo[1];
static void
DrawMotLandEntryHook(void)
{
    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_ALL);

    FuncHookCall( DrawMotLandEntryHookInfo, DrawMotLandEntry() );

    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_END);
}

#define gjSetShadow         FUNC_PTR(void, __cdecl, (const void*, const f32)  , 0x00495EB0)
#define gjTranslateShadow   FUNC_PTR(void, __cdecl, (const void*, const void*), 0x00496160)
#define gjClearLandShadow   FUNC_PTR(void, __cdecl, (void)                    , 0x00496310)

static void
CnkDrawLT(const OBJ_LANDENTRY* const pLandEntry)
{
    const NJS_CNK_OBJECT* const p_obj = pLandEntry->pObject;

    if ( !(pLandEntry->slAttribute & LANDATTR_NOSHADOW) )
    {
        gjSetShadow(&pLandEntry->xCenter, pLandEntry->r);
        gjTranslateShadow(p_obj->pos, p_obj->ang);

        njCnkDrawModel_Broken(p_obj->model);

        gjClearLandShadow();
    }
    else
        njCnkDrawModel_Broken(p_obj->model);
}

__declspec(naked)
static void
___CnkDrawLT(void)
{
    __asm
    {
        push edi
        call CnkDrawLT
        pop edi
        retn
    }
}

void
RFM_CommonInit(void)
{
    RFC_TransparancyInit();

    /** Restore Big the Cat in Wild Canyon **/
    DATA_ARY(OBJ_ITEMENTRY, 0x00BD7440, [100])[82] = DATA_ARY(OBJ_ITEMENTRY, 0x0109E830, [100])[85];

    if (RF_ConfigGetInt(CNF_COMMON_EEMBLEM))
    {
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

    if (RF_ConfigGetInt(CNF_COMMON_TR_BLOON))
    {
        WriteNOP( 0x006DB64D, 0x006DB656); // Balloon
        WriteRetn(0x06DB3B0);

        WriteData(0x00624E45, DISP_SORT, uint8_t); // Baloon (Cart)
        WriteNOP( 0x00625199, 0x0062519B);

        static const double bloondbl = 85.0;

        ReplaceFloat(0x006251EE, &bloondbl);
    }

    if (RF_ConfigGetInt(CNF_COMMON_TR_GOAL))
    {
        CnkModelMaterialFlagOn(0x00B4EACC, 1, NJD_FST_UA);

        CnkModelMaterialFlagOff(0x00B4EC6C, 0, NJD_FST_DB); // GOAL text
        CnkModelMaterialFlagOff(0x00B4EE0C, 0, NJD_FST_DB); // BACK text

        /** It won't draw correctly unless we set it to use disp_sort,
            I've just combined the disp and disp_sort functions **/

        SwitchDisplayer(0x006C651E, DISP_SORT); // Disp
        WriteNOP(0x006C6525, 0x006C652C);       // tp->disp_sort = ObjectGoalringDispSort;

        WritePointer(0x006C6521, ObjectGoalringDispSortNew);
    }

    if (RF_ConfigGetInt(CNF_COMMON_EJET))
    {
        RFC_EnemyJet();
    }

    if (RF_ConfigGetInt(CNF_COMMON_UDREEL))
    {
        RFC_UDReelInit();
    }

    if (RF_ConfigGetInt(CNF_COMMON_JOTREE))
    {
        GJS_OBJECT* object_jo_tree = RF_GinjaLoadObjectFile("jo_tree");

        WritePointer(0x01072D5C, texlist_jo_tree); // Green Forest

        WritePointer(0x010737B4, object_jo_tree->model); // Green Forest
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

    FuncHook(ObjectGlobalLightManagerHookInfo, ObjectGlobalLightManager, ObjectGlobalLightManagerHook);

    /** Add two pass drawing for Chunk land tables **/
    FuncHook(LandDisplayerHookInfo     , LandDisplayer     , LandDisplayerHook);
    FuncHook(LandDisplayerTransHookInfo, LandDisplayerTrans, LandDisplayerTransHook);
    FuncHook(DrawMotLandEntryHookInfo  , DrawMotLandEntry  , DrawMotLandEntryHook);
    WriteNOP(0x0047C2B5, 0x0047C2BE); // Force Chunk to draw twice

    /** Add Chunk shadow map support for LTs **/
    WriteCall(0x0047C454, ___CnkDrawLT);
    WriteCall(0x0047C462, ___CnkDrawLT);
    WriteCall(0x0047C604, ___CnkDrawLT);
    WriteCall(0x0047C612, ___CnkDrawLT);

    /** Fix keys in Death Chamber & Egg Quaters glowing eye effect caused by the
        programmer referencing the wrong model array **/
    WritePointer(0x006D276B, 0x00B4324C);

    /** Fix Chao Key model not dissapearing when collected in 16:9 if the camera is too far away **/
    static const double chaokey_chk_fix = 300.0;
    ReplaceFloat(0x006E9B4A, &chaokey_chk_fix);
}
