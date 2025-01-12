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

#define SAMT_INCL_FUNCPTRS
#include <sa2b/sonic/landtable.h>
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

        njCnkCacheDrawModel(p_obj->model);

        gjClearLandShadow();
    }
    else
        njCnkCacheDrawModel(p_obj->model);
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

#define DrawGameHUD         FUNC_PTR(void, __cdecl, (void), 0x0044E9C0)

static hook_info DrawGameHUDHookInfo[1];
static void
DrawGameHUDHook(void)
{
    njTextureClampMode(NJD_TEXTURECLAMP_CLAMP_UV);

    FuncHookCall( DrawGameHUDHookInfo, DrawGameHUD() );

    njTextureClampMode(NJD_TEXTURECLAMP_NOCLAMP);
}

static bool
LandTableIsGinja(const OBJ_LANDTABLE* pLand)
{
    int count = pLand->ssVisibleCount;

    if (count < 0)
        count = pLand->ssCount;

    for (int i = 0; i < count; ++i)
    {
        const OBJ_LANDENTRY* const p_entry = &pLand->pLandEntry[i];

        const NJS_CNK_OBJECT* const p_obj = p_entry->pObject;

        /** If entry isn't set to draw, skip **/

        if ( !(p_entry->slAttribute & LANDATTR_DRAW) )
        {
            continue;
        }

        /** Chunk models are unlikely to not have 'plist' data, while Ginja models
          never uses that pointer in SA2. If 'plist' exists, it's almost
          certainly a Chunk model; meaning a Chunk LandTable **/

        if (p_obj->model && p_obj->model->plist)
        {
            return false;
        }
    }

    return true;
}

static hook_info LandChangeLandTableHookInfo[1];
static void
LandChangeLandTableHook(OBJ_LANDTABLE* land)
{
    boolLandTableGinja = LandTableIsGinja(land);

    FuncHookCall( LandChangeLandTableHookInfo, LandChangeLandTable(land) );
}

void
RFM_CommonInit(void)
{
    RFC_TransparancyInit();

    RFC_NewDisplayerInit();

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

    /** Automatically determine landtable format type **/
    FuncHook(LandChangeLandTableHookInfo, LandChangeLandTable_p, LandChangeLandTableHook);

    /** Game HUD texture overdraw fix **/
    FuncHook(DrawGameHUDHookInfo, DrawGameHUD, DrawGameHUDHook);

    /** Fix keys in Death Chamber & Egg Quaters glowing eye effect caused by the
        programmer referencing the wrong model array **/
    WritePointer(0x006D276B, 0x00B4324C);

    /** Fix Chao Key model not dissapearing when collected in 16:9 if the camera is too far away **/
    static const double chaokey_chk_fix = 300.0;
    ReplaceFloat(0x006E9B4A, &chaokey_chk_fix);
}
