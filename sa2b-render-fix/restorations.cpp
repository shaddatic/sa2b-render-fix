#include <sa2b/core.h>
#include <sa2b/config.h>
#include <sa2b/memtools.h>
#include <sa2b/model.h>
#include <sa2b/mods.h>

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/task.h>
#include <sa2b/src/score.h>
#include <sa2b/src/njctrl.h>

#include <tools.h>

#include <enemy-jet.h>
#include <mizugomi.h>

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

static void
GUNEmblemRestore()
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
    WriteData(0x109B2CC, *model_ce_truck_hood, NJS_CNK_MODEL);
}

static void
UdreelFlashDraw(GJS_MODEL* model, TASK* tp)
{
    SaveControl3D();
    OnControl3D(NJD_CONTROL_3D_CONSTANT_MATERIAL);

    SaveConstantMaterial();

    if (GameTimer % 0x2Eu >= 0x17 && !(tp->twp->mode & 1))
    {
        SetConstantMaterial(1.0f, 1.0f, 1.0f, 1.0f);
    }
    else
    {
        SetConstantMaterial(1.0f, 0.7f, 0.7f, 0.7f);
    }

    gjDrawModel(model);

    LoadConstantMaterial();
    LoadControl3D();
}

__declspec(naked)
static void
__UdreelFlashDraw()
{
    __asm
    {
        push [esp+4Ch]  // tp
        push ebx        // model
        call UdreelFlashDraw
        pop ebx
        add esp, 4
        retn
    }
}

static void
UdreelFlashRestore()
{
    WriteCall(0x006E62E7, __UdreelFlashDraw);
    WritePointer(0x00B143B0, LoadGinjaObject2(GetModPath(), "model/udreel.sa2bmdl"));
}

EXTERN NJS_TEXLIST texlist_jo_tree[];

static void
JungleObjectTreeRestore()
{
    GJS_OBJECT* object_jo_tree = LoadGinjaObject2(GetModPath(), "model/jo_tree.sa2bmdl");

    WritePointer(0x01072D5C, texlist_jo_tree); // Green Forest
    
    WritePointer(0x010737B4, object_jo_tree->model); // Green Forest
}

#define SECT "rest"

void
RestorationSettings(const config* conf)
{
    if (ConfigGetInt(conf, SECT, "emblem", 1))
    {
        if (ModCheckDll("RestoredGUNLogos"))
        {
            ModConflictWarning(
                "The 'Restored GUN Logos' mod will conflict with Render Fix's 'GUN Emblem Fix' setting!\n\n"
                "Please disable either the 'Restored GUN Logos' mod, or the 'GUN Emblem Fix' setting!"
            );
        }

        GUNEmblemRestore();
    }

    if (ConfigGetInt(conf, SECT, "chaos_trans", 1))
    {
#define CHAOS_ALPHA 0xBB

        CnkMaterialDiffuse(0x01470D58, 0, CHAOS_ALPHA, -1, -1, -1);
        CnkMaterialDiffuse(0x01481448, 0, CHAOS_ALPHA, -1, -1, -1);
        CnkMaterialDiffuse(0x0147A608, 0, CHAOS_ALPHA, -1, -1, -1);
        CnkMaterialDiffuse(0x014869A0, 0, CHAOS_ALPHA, -1, -1, -1);
        CnkMaterialDiffuse(0x01476D78, 0, CHAOS_ALPHA, -1, -1, -1);
        CnkMaterialDiffuse(0x0148BE88, 0, CHAOS_ALPHA, -1, -1, -1);

        CnkMaterialFlagOn(0x01470D58, 0, NJD_FST_UA);
        CnkMaterialFlagOn(0x01481448, 0, NJD_FST_UA);
        CnkMaterialFlagOn(0x0147A608, 0, NJD_FST_UA);
        CnkMaterialFlagOn(0x014869A0, 0, NJD_FST_UA);
        CnkMaterialFlagOn(0x01476D78, 0, NJD_FST_UA);
        CnkMaterialFlagOn(0x0148BE88, 0, NJD_FST_UA);

        /** They won't draw correctly unless we set it to use disp_sort **/

        SwitchDisplayer(0x00508358, DISP_SORT);
    }

    if (ConfigGetInt(conf, SECT, "bloon_trans", 1))
    {
        WriteNoOP(0x006DB64D, 0x006DB656); // Balloon
        WriteRetn(0x6DB3B0);

        WriteData(0x00624E45, DISP_SORT, uint8); // Baloon (Cart)
        WriteNoOP(0x00625199, 0x0062519B);

        static const double bloondbl = 85.0;

        ReplaceFloat(0x006251EE, &bloondbl);
    }

    if (ConfigGetInt(conf, SECT, "goal_trans", 1))
    {
        CnkModelMaterialFlagOn(0x00B4EACC, 1, NJD_FST_UA);

        CnkModelMaterialFlagOff(0x00B4EC6C, 0, NJD_FST_DB); // GOAL text
        CnkModelMaterialFlagOff(0x00B4EE0C, 0, NJD_FST_DB); // BACK text

        /** It won't draw correctly unless we set it to use disp_sort,
            this flips things around so "it just works!" **/

        SwitchDisplayer(0x006C651E, DISP_SORT);
        SwitchDisplayer(0x006C6525, DISP);
    }

    if (ConfigGetInt(conf, SECT, "jet", 1))
    {
        EnemyJetDisplayerFix();
    }

    if (ConfigGetInt(conf, SECT, "jo_tree", 1))
    {
        JungleObjectTreeRestore();
    }

    if (ConfigGetInt(conf, SECT, "mizugomi", 1))
    {
        FixMizugomi();
    }

    if (ConfigGetInt(conf, SECT, "dc_ring", 0))
    {
        GjsModelTintFix((GJS_MODEL*)0x00B58288);
    }

    if (ConfigGetInt(conf, SECT, "udreel", 0))
    {
        UdreelFlashRestore();
    }
}