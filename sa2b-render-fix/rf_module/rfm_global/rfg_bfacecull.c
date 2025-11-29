#include <samt/core.h>
#include <samt/writemem.h>
#include <samt/writeop.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** GX **/
#include <samt/gx/gx.h>

/** Source **/
#include <samt/sonic/landtable.h>
#include <samt/sonic/datadll.h>
#include <samt/sonic/njctrl.h>

/** Std **/
#include <string.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_mdlutil.h>
#include <rf_renderstate.h>

static void
JumpAuraFixFlagOn(void)
{
    gjUpdateFog();

    SaveControl3D();
    SaveConstantAttr();

    OnControl3D(NJD_CONTROL_3D_CNK_CONSTANT_ATTR);
    njSetConstantAttr(NJD_FST_MASK, NJD_FST_DB);
}

static void
JumpAuraFixFlagOff(void)
{
    LoadConstantAttr();
    LoadControl3D();

    gjUpdateFog();
}

#define BgDisp_CCK      FUNC_PTR(void, __cdecl, (task*), 0x65F6D0)

static void
BGDisp_CCKFix(task* tp)
{
    SaveControl3D();
    SaveConstantAttr();

    OnControl3D(NJD_CONTROL_3D_CNK_CONSTANT_ATTR);
    njSetConstantAttr(NJD_FST_MASK, NJD_FST_DB);

    BgDisp_CCK(tp);

    LoadConstantAttr();
    LoadControl3D();
}

#define BgDisp_CCR      FUNC_PTR(void, __cdecl, (task*), 0x4DC140)

static void
BGDisp_CCRFix(task* tp)
{
    SaveControl3D();
    SaveConstantAttr();

    OnControl3D(NJD_CONTROL_3D_CNK_CONSTANT_ATTR);
    njSetConstantAttr(NJD_FST_MASK, NJD_FST_DB);

    BgDisp_CCR(tp);

    LoadConstantAttr();
    LoadControl3D();
}

#define BgDisp_CCS      FUNC_PTR(void, __cdecl, (task*), 0x4CB840)

static void
BGDisp_CCSFix(task* tp)
{
    SaveControl3D();
    SaveConstantAttr();

    OnControl3D(NJD_CONTROL_3D_CNK_CONSTANT_ATTR);
    njSetConstantAttr(NJD_FST_MASK, NJD_FST_DB);

    BgDisp_CCS(tp);

    LoadConstantAttr();
    LoadControl3D();
}

#define HataList1               DATA_ARY(NJS_CNK_MODEL* , 0x00A7E9F0, [74]) // Desert Banners
#define HataList2               DATA_ARY(NJS_CNK_MODEL* , 0x00A7E888, [90]) // ^
#define HataListSO              DATA_ARY(NJS_CNK_MODEL* , 0x00CDE5B0, [90]) // ^ (Sand Ocean)
#define LowFlagList             DATA_ARY(NJS_CNK_MODEL* , 0x00BC0B98, [48]) // Wild Canyon Wind Flags
#define FlagList                DATA_ARY(NJS_CNK_MODEL* , 0x00BD3560, [48]) // ^
#define ButterflyList           DATA_ARY(NJS_CNK_MODEL* , 0x00DDB64C, [9])  // Dry Lagoon Butterflies
#define PoisonHazardList        DATA_ARY(NJS_CNK_OBJECT*, 0x009CAD88, [22]) // Crazy Gadget Poison Objects
#define BatModelList            DATA_ARY(NJS_CNK_MODEL* , 0x00B6AD04, [6])
#define CCRBgWaterList          DATA_ARY(NJS_CNK_MODEL* , 0x01612CF8, [20])

void
RFG_BackfaceCullingInit(void)
{
    /*
    *   Model Fixes
    */
    /** Chao Pipe **/
    CnkModelMaterialFlagOn(0x00B1DE5C, 0, NJD_FST_DB);

    /** Levelup Dai Light **/
    WriteData(0x006D8DA8, 0x0800 | NJD_FST_DB, uint32_t);

    /** Crash 3D Displayer **/
    WriteData(0x006E2441, 0x0A00 | NJD_FST_DB, uint32_t);

    /** Weeds **/
    {
        CnkModelMaterialFlagOn(0x00A34744, 0, NJD_FST_DB); // Common Weed
        CnkModelMaterialFlagOn(0x00A34B74, 0, NJD_FST_DB); // ^

        CnkModelMaterialFlagOn(0x00AB754C, 0, NJD_FST_DB); // P-Cave Weed
        CnkModelMaterialFlagOn(0x00AB824C, 0, NJD_FST_DB); // ^
    }

    /** Pyramid Cave **/
    {
        CnkModelMaterialFlagOn(0x00AACBEC,  0, NJD_FST_DB); // Spiderweb

        CnkModelMaterialFlagOn(0x00AA28A4,  1, NJD_FST_DB); // Iron Bar Chains
        CnkModelMaterialFlagOn(0x00AA28A4,  2, NJD_FST_DB); // ^

        CnkModelMaterialFlagOn(0x00AA21A4,  1, NJD_FST_DB); // Snake Dish Chain
        CnkModelMaterialFlagOn(0x00ABA8E4,  1, NJD_FST_DB); // Snake Dish Chain 2

        CnkModelMaterialFlagOn(0x00AB171C, -1, NJD_FST_DB); // Hang Ring Chains

        CnkModelMaterialFlagOn(0x00A9A46C, 12, NJD_FST_DB); // Hanging Ship Chains (1)
        CnkModelMaterialFlagOn(0x00A9D014, 10, NJD_FST_DB); // Hanging Ship Chains (2)
    }

    /** Mine Mizu **/
    CnkModelFlipStripWinding(0x0162E024, 0, 0);
    CnkModelFlipStripWinding(0x0162E024, 0, 1);
    CnkModelFlipStripWinding(0x0162E024, 1, 0);
    CnkModelFlipWinding(0x0162E0CC);            // Second Mizu model

    /** Bg Models **/
    CnkModelFlipWinding(0x0168B354); // Pumpkin Hill
    CnkModelFlipWinding(0x015A16BC); // Radical Highway
    CnkModelFlipWinding(0x00BECE74); // Wild Canyon
    CnkModelFlipWinding(0x011B98E4); // Mission Street
    CnkModelFlipWinding(0x0115C4B4); // Meteor Herd
    CnkModelFlipWinding(0x0115B68C); // ^
    CnkModelFlipWinding(0x00DD1354); // Knux Vs Rouge
    CnkModelFlipWinding(0x00DD0524); // ^
    CnkModelFlipWinding(0x0097085C); // Mission Street 2P
    CnkModelFlipWinding(0x016555B4); // Sonic Vs Shadow 2
    CnkModelFlipWinding(0x00C7CEFC); // Planet Quest
    CnkModelFlipWinding(0x00C7C0D4); // ^
    CnkModelFlipWinding(0x01710B54); // Finalhazard

    /** Goal Ring **/
    CnkModelMaterialFlagOn(0x00B4EACC, 1, NJD_FST_DB);

    /** Tsubo (HB Pots) **/
    CnkModelMaterialFlagOn(0x00A2F034, 1, NJD_FST_DB); // Shadowed
    CnkModelMaterialFlagOn(0x00A31BA4, 0, NJD_FST_DB);

    /** Hata (Desert Banners) **/
    {
        for (int i = 0; i < ARYLEN(HataList1); ++i)
        {
            CnkModelMaterialFlagOn(HataList1[i], 0, NJD_FST_DB);
        }

        for (int i = 0; i < ARYLEN(HataList2); ++i)
        {
            CnkModelMaterialFlagOn(HataList2[i], 0, NJD_FST_DB);
        }
    }

    /** Hata (Sand Ocean) **/
    {
        for (int i = 0; i < ARYLEN(HataListSO); ++i)
        {
            CnkModelMaterialFlagOn(HataListSO[i], 0, NJD_FST_DB);
        }
    }

    /** Pots (Sand Ocean) **/
    {
        CnkModelMaterialFlagOn(0xCFCCA4, 0, NJD_FST_DB);
    }

    /** Wild Canyon **/
    {
        WriteData(0x006A2F9A, 0x8300 | NJD_FST_DB, uint32_t); // Wind Tunnel

        for (int i = 0; i < ARYLEN(LowFlagList); ++i)
        {
            CnkModelMaterialFlagOn(LowFlagList[i], 0, NJD_FST_DB);
        }

        for (int i = 0; i < ARYLEN(FlagList); ++i)
        {
            CnkModelMaterialFlagOn(FlagList[i], 0, NJD_FST_DB);
        }

        CnkModelMaterialFlagOn(0x00BD92F4, 2, NJD_FST_DB); // Fans  (Light)
        CnkModelMaterialFlagOn(0x00BDA924, 2, NJD_FST_DB); // ^     (Dark)
    }

    /** Dry Lagoon **/
    {
        WriteData(0x0063DEB7, 0x8300 | NJD_FST_DB, uint32_t); // Water currents
        WriteData(0x0063E0AA, 0x8300 | NJD_FST_DB, uint32_t); // ^
        WriteData(0x0063E317, 0x8300 | NJD_FST_DB, uint32_t); // ^

        CnkModelMaterialFlagOn(0x00E3524C, 0, NJD_FST_DB); // Fish
        CnkModelMaterialFlagOn(0x00E3539C, 0, NJD_FST_DB); // ^
        CnkModelMaterialFlagOn(0x00E352F4, 0, NJD_FST_DB); // ^

        for (int i = 0; i < ARYLEN(ButterflyList); ++i)
        {
            CnkModelMaterialFlagOn(ButterflyList[i], 0, NJD_FST_DB);
        }

        CnkModelMaterialFlagOn(0x00DF8C3C, -1, NJD_FST_DB); // Red Flowers
        CnkModelMaterialFlagOn(0x00DFDF54, -1, NJD_FST_DB); // ^

        CnkModelMaterialFlagOn(0x00DEC1B4, -1, NJD_FST_DB); // Leaf
        CnkModelMaterialFlagOn(0x00DED694, -1, NJD_FST_DB); // ^

        CnkObjectMaterialFlagOn(0x00E2DBDC, NJD_FST_DB);    // PLANT2
        CnkObjectMaterialFlagOn(0x00DEEE6C, NJD_FST_DB);    // PLANT3

        CnkModelMaterialFlagOn(0x00E5D9EC, -1, NJD_FST_DB); // Glass goblet thing
    }

    /** Big Foot Lightposts **/
    CnkModelMaterialFlagOn(0x0093D02C, -1, NJD_FST_DB);

    /** Pumpkin Hill Train **/
    CnkModelMaterialFlagOn(0x0167AD44, 2, NJD_FST_DB);
    CnkModelMaterialFlagOn(0x0167AD44, 5, NJD_FST_DB);
    CnkModelMaterialFlagOn(0x0167AD44, 8, NJD_FST_DB);

    /** Pumpkin Hill Shed **/
    CnkModelMaterialFlagOn(0x0167C644, 1, NJD_FST_DB);
    CnkModelMaterialFlagOn(0x0167C644, 3, NJD_FST_DB);

    /** Security Hall Money **/
    CnkModelMaterialFlagOn(0x00E76994, 0, NJD_FST_DB);

    /** Iron Gate / Prison Lane Sirens **/
    CnkModelMaterialFlagOn(0x01043FBC, 1, NJD_FST_DB); // PL
    CnkModelMaterialFlagOn(0x00BF5BC4, 1, NJD_FST_DB); // IG

    /** White Jungle Fixes **/
    CnkModelFlipWinding(0x00EADA7C);
    CnkModelFlipWinding(0x00EAD2A4);
    CnkModelFlipWinding(0x00EAD2A4);

    /** Crazy Gadget Matrix Effects **/
    {
        OBJ_LANDTABLE* pltable = GetDataDllAddr(OBJ_LANDTABLE, "objLandTable0022_uv");

        CnkLandTableMaterialFlagOn(pltable, NJD_FST_DB);
    }

    /** Crazy Gadget Glowing X's **/
    {
        OBJ_LANDTABLE* pltable = GetDataDllAddr(OBJ_LANDTABLE, "objLandTable0022_x");

        CnkLandTableMaterialFlagOn(pltable, NJD_FST_DB);
    }

    /** Crazy Gadget Poison Hazards **/
    {
        CnkModelMaterialFlagOn(0x009B046C, -1, NJD_FST_DB); // POISON Object
        CnkModelMaterialFlagOn(0x009B03CC, -1, NJD_FST_DB); // POISON Object Cap

        for (int i = 0; i < ARYLEN(PoisonHazardList); ++i)
        {
            CnkModelMaterialFlagOn(PoisonHazardList[i]->model, -1, NJD_FST_DB);
        }
    }

    /** Crazy Gadget LIGHT_A **/
    CnkModelFlipWinding(0x009A4D84);

    /** Death Chamber Bats **/
    {
        for (int i = 0; i < ARYLEN(BatModelList); ++i)
        {
            CnkModelMaterialFlagOn(BatModelList[i], -1, NJD_FST_DB);
        }
    }

    /** Tails v Eggman 2 Skybox **/
    {
        CnkModelFlipWinding(0x00C881A4);
        CnkModelFlipWinding(0x00C88FCC);
    }

    /** Final Rush BgDisplayer LT **/
    {
        OBJ_LANDTABLE* pltable = GetDataDllAddr(OBJ_LANDTABLE, "objLandTable0030_uv");

        CnkLandTableMaterialFlagOn(pltable, NJD_FST_DB);
    }

    /** Final Chase BgDisplayer LT **/
    {
        OBJ_LANDTABLE* pltable = GetDataDllAddr(OBJ_LANDTABLE, "objLandTable0040_uv");

        CnkLandTableMaterialFlagOn(pltable, NJD_FST_DB);
    }

    /** Big Foot Arena **/
    {
        CnkModelMaterialFlagOn(0x0093D6EC, 1, NJD_FST_DB); // Tree object
    }

    /** Cart Stage Objects **/
    {
        NJS_CNK_OBJECT* poster = GetDataDllAddr(NJS_CNK_OBJECT, "object_poster_body_body");

        CnkObjectMaterialFlagOn(poster, NJD_FST_DB);
    }

    /** Time Stop Switches **/
    {
        CnkObjectMaterialFlagOn(0x163FA74, NJD_FST_DB);
    }

    /** Meteor Herd LT Effects **/
    {
        OBJ_LANDTABLE* pltable = GetDataDllAddr(OBJ_LANDTABLE, "objLandTable0032_ma");

        CnkLandTableMaterialFlagOn(pltable, NJD_FST_DB);
    }

    /** Cannons Core Sonic **/
    {
        NJS_CNK_MODEL** mdl_list;

        mdl_list = GetDataDllAddr(NJS_CNK_MODEL*, "sUn0Tuuro0"); // I hope I never see these models again

        for (int i = 0; i < 16; ++i)
        {
            CnkModelFlipWinding(mdl_list[i]);
        }

        mdl_list = GetDataDllAddr(NJS_CNK_MODEL*, "sUn0Tuuro1");

        for (int i = 0; i < 16; ++i)
        {
            CnkModelFlipWinding(mdl_list[i]);
        }

        mdl_list = GetDataDllAddr(NJS_CNK_MODEL*, "sUn0Tuuro2");

        for (int i = 0; i < 16; ++i)
        {
            CnkModelFlipWinding(mdl_list[i]);
        }

        WritePointer(0x004CADBA, BGDisp_CCSFix); // Ick
    }

    /** Cannons Core Rouge/Knuckles **/
    {
        WritePointer(0x0065F18A, BGDisp_CCKFix); // I don't really like these fixes
        WritePointer(0x004DB82A, BGDisp_CCRFix); // ^

        for (int i = 0; i < ARYLEN(CCRBgWaterList); ++i)
        {
            CnkModelMaterialFlagOn(CCRBgWaterList[i], -1, NJD_FST_DB);
        }

        CnkModelFlipWinding(0x0095F74C); // Goal Door
    }
}
