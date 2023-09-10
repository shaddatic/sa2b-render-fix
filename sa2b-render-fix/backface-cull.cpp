#include <sa2b/core.h>
#include <sa2b/memtools.h>

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/landtable.h>
#include <sa2b/src/datadll.h>

#include <tools.h>

#define GXD_CULLMODE_NONE   0
#define GXD_CULLMODE_CW     1
#define GXD_CULLMODE_CCW    2

FuncPtr(int, __thiscall, GX_SetCullMode, (Int mode), 0x00420440);

DataRef(int, GX_Cull, 0x01933F14);
DataRef(int, GX_vtxcount, 0x01933F04);

DataRef(int, VertexBuffer, 0x01933EF8);

DataRef(int, VertexBufferStart, 0x01933F08);
DataRef(int, VertexBufferOffset, 0x01933F0C);
DataRef(int, VertexBuffOffCopy, 0x01933F10);

DataRef(int, GX_PrimType, 0x01933EFC);

DataRef(int, dword_1933F00, 0x01933F00);

struct __declspec(align(4)) VertexDeclarationInfo
{
    float gap0;
    int field_4;
    float field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    void* D3DVertexDeclaration;
    int field_20;
    uint32 StrideSize;
    int field_28;
    int field_2C;
    int field_30;
};

DataRef(VertexDeclarationInfo*, VertexDeclInfo, 0x0174F7E8);

static void
CopyLastVertex()
{
    int stride = VertexDeclInfo->StrideSize;
    int vtxbuf = VertexBuffer;
    int lastvtx = VertexBufferOffset - stride;

    memcpy((char*)vtxbuf + VertexBufferOffset, (char*)vtxbuf + lastvtx, stride);
    ++GX_vtxcount;
    VertexBufferOffset += stride;
}

static void
SetCull(sint16 vtxCount)
{
    bool ccw = false;

    if (vtxCount < 0)
    {
        vtxCount = -vtxCount;
        ccw = true;
    }

    int stride = VertexDeclInfo->StrideSize;
    
    if (!GX_vtxcount)
    {
        VertexBuffOffCopy = 0;
        GX_PrimType = 0x98;
        VertexBufferStart = VertexBufferOffset;
        GX_Cull = ccw;
        GX_vtxcount += vtxCount;

        if (ccw)
        {
            VertexBuffOffCopy = VertexBufferOffset;
            ++GX_vtxcount;
            VertexBufferOffset += stride;
        }

        return;
    }

    int v6 = (GX_vtxcount - 2) & 0x80000001;

    int lastvtx = VertexBufferOffset - stride;
    int vtxbuf = VertexBuffer;

    if (v6 == 0)
    {
        if (ccw)
        {
            CopyLastVertex();
            CopyLastVertex();
            VertexBuffOffCopy = VertexBufferOffset;
            GX_Cull = ccw;
            VertexBufferOffset += stride;
            GX_vtxcount += vtxCount + 1;
            return;
        }
    }
    else
    {
        if (!ccw)
        {
            CopyLastVertex();
            CopyLastVertex();
            VertexBuffOffCopy = VertexBufferOffset;
            GX_Cull = ccw;
            VertexBufferOffset += stride;
            GX_vtxcount += vtxCount + 1;
            return;
        }
    }

    CopyLastVertex();

    VertexBuffOffCopy = VertexBufferOffset;
    GX_Cull = ccw;
    VertexBufferOffset += stride;
    GX_vtxcount += vtxCount + 1;
}

__declspec(naked)
static void
__SetGXCull()
{
    __asm
    {
        push eax
        call SetCull
        add esp, 4
        retn
    }
}

static void
SetCullNone()
{
    GX_SetCullMode(GXD_CULLMODE_NONE);
}

__declspec(naked)
static void
__GXEndEnd()
{
    __asm
    {
        pop ebx
        jmp SetCullNone
    }
}

FuncPtr(void, __cdecl, DoStripFlags, (uint8), 0x42CA20);

static void
StripFlags(uint8 flag)
{
    GX_SetCullMode((flag & 0x10) ? GXD_CULLMODE_NONE : GXD_CULLMODE_CW);

    DoStripFlags(flag);
}

FuncPtr(void, __cdecl, UpdateFog, (), 0x0042A870);

static void
JumpAuraFixFlagOn()
{
    UpdateFog();

    SaveControl3D();
    SaveConstantAttr();

    OnControl3D(NJD_CONTROL_3D_CNK_CONSTANT_ATTR);
    njSetConstantAttr(NJD_FST_MASK, NJD_FST_DB);
}

static void
JumpAuraFixFlagOff()
{
    LoadConstantAttr();
    LoadControl3D();
    
    UpdateFog();
}

void
EnableJumpAuraFix()
{
    WriteCall(0x00756984, JumpAuraFixFlagOn);
    WriteJump(0x00756A56, JumpAuraFixFlagOff);
}

static void
BGDisp_CCKFix(task* tp)
{
    TaskFuncPtr(BgDisp_CCK, 0x65F6D0);

    SaveControl3D();
    SaveConstantAttr();

    OnControl3D(NJD_CONTROL_3D_CNK_CONSTANT_ATTR);
    njSetConstantAttr(NJD_FST_MASK, NJD_FST_DB);

    BgDisp_CCK(tp);

    LoadConstantAttr();
    LoadControl3D();
}

static void
BGDisp_CCRFix(task* tp)
{
    TaskFuncPtr(BgDisp_CCR, 0x4DC140);

    SaveControl3D();
    SaveConstantAttr();

    OnControl3D(NJD_CONTROL_3D_CNK_CONSTANT_ATTR);
    njSetConstantAttr(NJD_FST_MASK, NJD_FST_DB);

    BgDisp_CCR(tp);

    LoadConstantAttr();
    LoadControl3D();
}

static void
BGDisp_CCSFix(task* tp)
{
    TaskFuncPtr(BgDisp_CCS, 0x4CB840);

    SaveControl3D();
    SaveConstantAttr();

    OnControl3D(NJD_CONTROL_3D_CNK_CONSTANT_ATTR);
    njSetConstantAttr(NJD_FST_MASK, NJD_FST_DB);

    BgDisp_CCS(tp);

    LoadConstantAttr();
    LoadControl3D();
}

void
EnableBackfaceCulling()
{
    WriteCall(0x0042CCA5, StripFlags);

    WriteCall(0x0042E22D, __SetGXCull);
    WriteCall(0x0042E388, __SetGXCull);
    WriteCall(0x0042E59D, __SetGXCull);
    WriteCall(0x0042E7B1, __SetGXCull);
    WriteCall(0x0042E9EE, __SetGXCull);
    WriteCall(0x0042F0FB, __SetGXCull);
    WriteCall(0x0042F1ED, __SetGXCull);
    WriteCall(0x0042F2FB, __SetGXCull);
    WriteCall(0x0042F40D, __SetGXCull);
    WriteCall(0x0077F908, __SetGXCull);

    WriteJump(0x0041C126, __GXEndEnd);

    /* 
    *   Model Fixes 
    */
    /** Chao Pipe **/
    CnkModelMaterialFlagOn(0x00B1DE5C, 0, NJD_FST_DB);

    /** Levelup Dai Light **/
    WriteData(0x006D8DA8, 0x800 | NJD_FST_DB, uint32);

    /** Pyramid Cave Weed **/
    CnkModelMaterialFlagOn(0x00A34744, 0, NJD_FST_DB);
    CnkModelMaterialFlagOn(0x00A34B74, 0, NJD_FST_DB);

    /** Mine Mizu **/
    FlipCnkModelStripWinding(0x0162E024, 0, 0);
    FlipCnkModelStripWinding(0x0162E024, 0, 1);
    FlipCnkModelStripWinding(0x0162E024, 1, 0);

    /** Bg Models **/
    FlipCnkModelWinding(0x0168B354); // Pumpkin Hill
    FlipCnkModelWinding(0x015A16BC); // Radical Highway
    FlipCnkModelWinding(0x00BECE74); // Wild Canyon
    FlipCnkModelWinding(0x011B98E4); // Mission Street
    FlipCnkModelWinding(0x0115C4B4); // Meteor Herd
    FlipCnkModelWinding(0x0115B68C); // ^
    FlipCnkModelWinding(0x00DD1354); // Knux Vs Rouge
    FlipCnkModelWinding(0x00DD0524); // ^
    FlipCnkModelWinding(0x0097085C); // Mission Street 2P
    FlipCnkModelWinding(0x016555B4); // Sonic Vs Shadow 2
    FlipCnkModelWinding(0x00C7CEFC); // Planet Quest
    FlipCnkModelWinding(0x00C7C0D4); // ^
    FlipCnkModelWinding(0x01710B54); // Finalhazard

    /** Goal Ring **/
    CnkModelMaterialFlagOn(0x00B4EACC, 1, NJD_FST_DB);

    /** Tsubo (HB Pots) **/
    CnkModelMaterialFlagOn(0x00A2F034, 1, NJD_FST_DB); // Shadowed
    CnkModelMaterialFlagOn(0x00A31BA4, 0, NJD_FST_DB);

    /** Hata (Desert Banners) **/
    {
        DataAry(NJS_CNK_MODEL*, HataList1, 0x00A7E9F0, [74]);

        for (int i = 0; i < arylen(HataList1); ++i)
        {
            CnkModelMaterialFlagOn(HataList1[i], 0, NJD_FST_DB);
        }

        DataAry(NJS_CNK_MODEL*, HataList2, 0x00A7E888, [90]);

        for (int i = 0; i < arylen(HataList2); ++i)
        {
            CnkModelMaterialFlagOn(HataList2[i], 0, NJD_FST_DB);
        }
    }

    /** Hata (Sand Ocean) **/
    {
        DataAry(NJS_CNK_MODEL*, HataListSO, 0x00CDE5B0, [90]);

        for (int i = 0; i < arylen(HataListSO); ++i)
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
        WriteData(0x006A2F9A, 0x8300 | NJD_FST_DB, uint32); // Wind Tunnel

        DataAry(NJS_CNK_MODEL*, LowFlagList, 0x00BC0B98, [48]);

        for (int i = 0; i < arylen(LowFlagList); ++i)
        {
            CnkModelMaterialFlagOn(LowFlagList[i], 0, NJD_FST_DB);
        }

        DataAry(NJS_CNK_MODEL*, FlagList, 0x00BD3560, [48]);

        for (int i = 0; i < arylen(FlagList); ++i)
        {
            CnkModelMaterialFlagOn(FlagList[i], 0, NJD_FST_DB);
        }

        CnkModelMaterialFlagOn(0x00BD92F4, 2, NJD_FST_DB); // Fans  (Light)
        CnkModelMaterialFlagOn(0x00BDA924, 2, NJD_FST_DB); // ^     (Dark)
    }

    /** Dry Lagoon **/
    {
        WriteData(0x0063DEB7, 0x8300 | NJD_FST_DB, uint32); // Water currents
        WriteData(0x0063E0AA, 0x8300 | NJD_FST_DB, uint32); // ^
        WriteData(0x0063E317, 0x8300 | NJD_FST_DB, uint32); // ^

        CnkModelMaterialFlagOn(0x00E3524C, 0, NJD_FST_DB); // Fish
        CnkModelMaterialFlagOn(0x00E3539C, 0, NJD_FST_DB); // ^
        CnkModelMaterialFlagOn(0x00E352F4, 0, NJD_FST_DB); // ^

        DataAry(NJS_CNK_MODEL*, ButterflyList, 0x00DDB64C, [9]);

        for (int i = 0; i < arylen(ButterflyList); ++i)
        {
            CnkModelMaterialFlagOn(ButterflyList[i], 0, NJD_FST_DB);
        }

        CnkModelMaterialFlagOn(0x00DF8C3C, -1, NJD_FST_DB); // Red Flowers
        CnkModelMaterialFlagOn(0x00DFDF54, -1, NJD_FST_DB); // ^
        
        CnkModelMaterialFlagOn(0x00DEC1B4, -1, NJD_FST_DB); // Leaf
        CnkModelMaterialFlagOn(0x00DED694, -1, NJD_FST_DB); // ^
        
    }

    /** Pumpkin Hill Train **/
    CnkModelMaterialFlagOn(0x0167AD44, 2, NJD_FST_DB);
    CnkModelMaterialFlagOn(0x0167AD44, 5, NJD_FST_DB);
    CnkModelMaterialFlagOn(0x0167AD44, 8, NJD_FST_DB);

    /** Security Hall Money **/
    CnkModelMaterialFlagOn(0x00E76994, 0, NJD_FST_DB);

    /** Iron Gate / Prison Lane Sirens **/
    CnkModelMaterialFlagOn(0x01043FBC, 1, NJD_FST_DB); // PL
    CnkModelMaterialFlagOn(0x00BF5BC4, 1, NJD_FST_DB); // IG
    
    /** White Jungle Fixes **/
    FlipCnkModelWinding(0x00EADA7C);
    FlipCnkModelWinding(0x00EAD2A4);

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

        DataAry(NJS_CNK_OBJECT*, PoisonHazardList, 0x009CAD88, [22]);

        for (int i = 0; i < arylen(PoisonHazardList); ++i)
        {
            CnkModelMaterialFlagOn(PoisonHazardList[i]->model, -1, NJD_FST_DB);
        }
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

    /** Cart Stage Objects **/
    {
        NJS_CNK_OBJECT* poster = GetDataDllAddr(NJS_CNK_OBJECT, "object_poster_body_body");

        CnkObjectMaterialFlagOn(poster, NJD_FST_DB);
    }

    /** Time Stop Switches **/
    {
        CnkObjectMaterialFlagOn(0x163FA74, NJD_FST_DB);
    }

    /** Cannons Core Sonic **/
    {
        NJS_CNK_MODEL** mdl_list;

        mdl_list = GetDataDllAddr(NJS_CNK_MODEL*, "sUn0Tuuro0"); // I hope I never see these models again

        for (int i = 0; i < 16; ++i)
        {
            FlipCnkModelWinding(mdl_list[i]);
        }

        mdl_list = GetDataDllAddr(NJS_CNK_MODEL*, "sUn0Tuuro1");

        for (int i = 0; i < 16; ++i)
        {
            FlipCnkModelWinding(mdl_list[i]);
        }

        mdl_list = GetDataDllAddr(NJS_CNK_MODEL*, "sUn0Tuuro2");

        for (int i = 0; i < 16; ++i)
        {
            FlipCnkModelWinding(mdl_list[i]);
        }

        WritePointer(0x004CADBA, BGDisp_CCSFix); // Ick
    }

    /** Cannons Core Rouge/Knuckles **/
    {
        WritePointer(0x0065F18A, BGDisp_CCKFix); // I don't really like these fixes
        WritePointer(0x004DB82A, BGDisp_CCRFix); // ^
    }
}