#include <samt/core.h>
#include <samt/memory.h>
#include <samt/writeop.h>
#include <samt/model.h>
#include <samt/funchook.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Source **/
#include <samt/sonic/task.h>
#include <samt/sonic/score.h>
#include <samt/sonic/njctrl.h>
#include <samt/sonic/texture.h>
#include <samt/sonic/set.h>
#include <samt/sonic/datadll.h>

#define SAMT_INCL_FUNCPTRS
#include <samt/sonic/landtable.h>
#undef SAMT_INCL_FUNCPTRS

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

#define DrawGameHUD         FUNC_PTR(void, __cdecl, (void), 0x0044E9C0)

static hook_info DrawGameHUDHookInfo[1];
static void
DrawGameHUDHook(void)
{
    njTextureClampMode(NJD_TEXTURECLAMP_CLAMP_UV);

    FuncHookCall( DrawGameHUDHookInfo, DrawGameHUD() );

    njTextureClampMode(NJD_TEXTURECLAMP_NOCLAMP);
}

void
RFM_CommonInit(void)
{
    RFC_TransparancyInit();

    RFC_NewDisplayerInit();

    RFC_LandtableInit();

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
        mtMemCopy((void*)0x109B2CC, model_ce_truck_hood, sizeof(NJS_CNK_MODEL));
    }

    if (RF_ConfigGetInt(CNF_COMMON_AISHEILD))
    {
        ReplaceObjectModel(0x014BC1A4, model_e_s_ai_shield);
    }

    if (RF_ConfigGetInt(CNF_COMMON_ESTGTEX))
    {
        WriteCall(0x004FE3E6, EnemyLoadTextureStage);
    }

    FuncHook(ObjectGlobalLightManagerHookInfo, ObjectGlobalLightManager, ObjectGlobalLightManagerHook);

    /** Game HUD texture overdraw fix **/
    FuncHook(DrawGameHUDHookInfo, DrawGameHUD, DrawGameHUDHook);

    /** Fix keys in Death Chamber & Egg Quaters glowing eye effect caused by the
        programmer referencing the wrong model array **/
    WritePointer(0x006D276B, 0x00B4324C);

    /** Fix Chao Key model not dissapearing when collected in 16:9 if the camera is too far away **/
    static const double chaokey_chk_fix = 300.0;
    ReplaceFloat(0x006E9B4A, &chaokey_chk_fix);

    /** Fixing IA flags **/

    CnkObjectMaterialFlagOff(0x0096DE1C, NJD_FST_IA); // Emblem Get model

    // 2p menu characters
    {
        typedef struct
        {
            NJS_CNK_OBJECT *object;
            NJS_MOTION *motion;
            NJS_MOTION *motion1;
            NJS_MOTION *motion2;
            NJS_CNK_OBJECT* extra;
            char gap1[4];
            NJS_CNK_OBJECT *object_alt;
            NJS_MOTION *motion_alt;
            NJS_MOTION *motion1_alt;
            NJS_MOTION *motion2_alt;
            char gap3[20];
        }
        BATTLE_CHARA;

        BATTLE_CHARA* data = GetDataDllAddr(BATTLE_CHARA, "_charaObject");

        for (int i = 0; i < 15; ++i)
        {
            if (data[i].object)     RF_CnkObjectMaterialFlagOff(data[i].object    , NJD_FST_IA);
            if (data[i].object_alt) RF_CnkObjectMaterialFlagOff(data[i].object_alt, NJD_FST_IA);
            if (data[i].extra)      RF_CnkObjectMaterialFlagOff(data[i].extra     , NJD_FST_IA);
        }
    }

    // race carts
    {
        typedef struct
        {
            char data0[4];
            NJS_CNK_OBJECT* object;
            NJS_CNK_OBJECT* object2;
            NJS_TEXLIST* pTexlist;
            char data1[8];
            short shrt0;
        }
        SPECIAL_INFO;

        SPECIAL_INFO* data = GetDataDllAddr(SPECIAL_INFO, "specialInfo");

        for (int i = 0; i < 8; ++i)
        {
            if (data[i].object)  RF_CnkObjectMaterialFlagOff(data[i].object , NJD_FST_IA);
            if (data[i].object2) RF_CnkObjectMaterialFlagOff(data[i].object2, NJD_FST_IA);
        }
    }
}
