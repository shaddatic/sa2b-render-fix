/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/memory.h>            /* memcopy                                                  */
#include <samt/writeop.h>           /* writecall                                                */
#include <samt/funchook.h>          /* funchook                                                 */
#include <samt/string.h>            /* strformat                                                */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Game ************************************************************************************/
#include <samt/sonic/task.h>        /* task                                                     */
#include <samt/sonic/texture.h>     /* texload                                                  */
#include <samt/sonic/set.h>         /* set                                                      */
#include <samt/sonic/datadll.h>     /* getdatadlladdr                                           */
#include <samt/sonic/game.h>        /* stagenumber                                              */

#define SAMT_INCL_FUNCPTRS
#include <samt/sonic/landtable.h>   /* landtable                                                */
#undef SAMT_INCL_FUNCPTRS

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_mdlutil.h>             /* materialflag                                             */
#include <rf_ninja.h>               /* rf ninja                                                 */
#include <rf_njcnk.h>               /* easysimpledirect                                         */

/****** Config **********************************************************************************/
#include <cnf.h>                    /* config get                                               */

/****** RF Utility ******************************************************************************/
#include <rfu_float.h>              /* replacefloat                                             */

/****** Self ************************************************************************************/
#include <rf_module/rfm_common/rfc_internal.h> /* children                                      */

/********************************/
/*  External Data               */
/********************************/
/****** Kumi Beetle *****************************************************************************/
EXTERN NJS_CNK_MODEL model_e_kumi_emblem[];
EXTERN NJS_CNK_MODEL model_e_g_kumi_emblem[];
EXTERN NJS_CNK_MODEL model_e_b_kumi_emblem[];
EXTERN NJS_CNK_MODEL model_e_gold_emblem[];
EXTERN NJS_CNK_MODEL model_e_kyoko_emblem[];

/****** Shouko Jet ******************************************************************************/
EXTERN NJS_CNK_MODEL model_e_shouko_wing_port[];
EXTERN NJS_CNK_MODEL model_e_shouko_wing_starboard[];
EXTERN NJS_CNK_MODEL model_e_shouko_aft[];

/****** Path Kumi Beetle ************************************************************************/
EXTERN NJS_CNK_MODEL model_e_g_pathkumi_emblem[];
EXTERN NJS_CNK_MODEL model_e_b_pathkumi_emblem[];

/****** Emi Tank ********************************************************************************/
EXTERN NJS_CNK_MODEL model_e_t_emi_emblem[];
EXTERN NJS_CNK_MODEL model_e_a_emi_emblem[];

/****** City Truck ******************************************************************************/
EXTERN NJS_CNK_MODEL model_ce_truck_hood[];

/****** Ai Hunter *******************************************************************************/
EXTERN NJS_CNK_MODEL model_e_s_ai_shield[];

/********************************/
/*  Macros                      */
/********************************/
/****** Replace Model ***************************************************************************/
#define ReplaceObjectModel(pobject, pmodel)        ((NJS_CNK_OBJECT*)pobject)->model = pmodel

/********************************/
/*  Game Defs                   */
/********************************/
/****** Global Light Manager ********************************************************************/
#define ObjectGlobalLightManagerTaskP       DATA_REF(task*, 0x01A5A660)
#define ObjectGlobalLightManager            FUNC_PTR(void, __cdecl, (task*), 0x004CAB20)

/****** Emerald Key Models **********************************************************************/
#define EmeraldKeys                 DATA_ARY(NJS_CNK_MODEL*, 0x00B43240, [3])
#define EmeraldKeyEyes              DATA_ARY(NJS_CNK_MODEL*, 0x00B4324C, [3])

/****** Game Hud ********************************************************************************/
#define DrawGameHUD                 FUNC_PTR(void, __cdecl, (void), 0x0044E9C0)

/********************************/
/*  Source                      */
/********************************/
/****** Static **********************************************************************************/
static int __fastcall
EnemyLoadTextureStage(const char* fname, NJS_TEXLIST* ptlo)
{
    c7 buf[260];

    mtStrFormat(buf, ARYLEN(buf), "%s_STG%02i", fname, ssStageNumber);

    const int err = texLoadTexturePrsFile(buf, ptlo);

    if (err == -1)
        return texLoadTexturePrsFile(fname, ptlo);

    return err;
}

static void
ObjectGlobalLightSWDestructor(task* tp)
{
    ObjectGlobalLightManagerTaskP = NULL;
}

static mt_hookinfo ObjectGlobalLightManagerHookInfo[1];
static void
ObjectGlobalLightManagerHook(task* tp)
{
    FuncHookCall( ObjectGlobalLightManagerHookInfo, ObjectGlobalLightManager(tp) );

    tp->dest = ObjectGlobalLightSWDestructor;
}

static int
DrawEmeraldKey(int i)
{
    njCnkSimpleDrawModel(EmeraldKeys[i]);
    njCnkSimpleDrawModel(EmeraldKeyEyes[i]);

    return 0;
}

__declspec(naked)
static int
___DrawEmeraldKey(void)
{
    __asm
    {
        push        esi
        call        DrawEmeraldKey
        add esp,    4
        retn
    }
}

/****** Init ************************************************************************************/
void
RFM_CommonInit(void)
{
    RFC_TransparancyInit();
    RFC_NewDisplayerInit();
    RFC_LandtableInit();

    /** Restore Big the Cat in Wild Canyon **/
    DATA_ARY(OBJ_ITEMENTRY, 0x00BD7440, [100])[82] = DATA_ARY(OBJ_ITEMENTRY, 0x0109E830, [100])[85];

    if ( CNF_GetInt(CNF_COMMON_EEMBLEM) )
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

    if ( CNF_GetInt(CNF_COMMON_AISHEILD) )
    {
        ReplaceObjectModel(0x014BC1A4, model_e_s_ai_shield);
    }

    if ( CNF_GetInt(CNF_COMMON_ESTGTEX) )
    {
        WriteCall(0x004FE3E6, EnemyLoadTextureStage);
    }

    FuncHook(ObjectGlobalLightManagerHookInfo, ObjectGlobalLightManager, ObjectGlobalLightManagerHook);

    /** Fix keys in Death Chamber & Egg Quaters glowing eye effect **/
    WriteCall(0x006D27A7, ___DrawEmeraldKey);

    /** Fix Chao Key model not dissapearing when collected in 16:9 if the camera is too far away **/
    RFU_ReplaceFloat(0x006E9B4A, 300.0);

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
}
