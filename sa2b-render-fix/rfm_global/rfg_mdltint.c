#include <sa2b/core.h>
#include <sa2b/writemem.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/datadll.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_usermsg.h>
#include <rf_mdlutil.h>

/*
*    Ginja Lists
*/
static int GinjaObjectList[] =
{
    0x00B46A38, // Rocket Missile (base)
    0x00B3AA70, // Rocket (base)
    0x01176AE8, // Propeller Spring (blades & spring)
    0x0116598C, // Fire Skull (Sky Rail) (jaw & box)
    0x0161AA38, // Fire Skull (Aquatic Mine & Pool Quest) (jaw & box)
};

static int GinjaModelList[] =
{
    0x00B1ED2C, // 3SPRING (base)
    0x00B1E6AC, // 3SPRING 1
    0x00B54504, // SPRINGA (base)
    0x00B54214, // SPRINGA (spring)
    0x00B53E34, // SPRINGA (face)
    0x00B56160, // SPRINGB (base)
    0x00B54A4C, // SPRINGB (spring)
    0x00B5495C, // SPRINGB (face)
    0x00B0D7CC, // Knudai // Mystic Shrine
    0x00AEED4C, // Dammy // Metal Harbor Static Missiles
    0x011772D8, // Propeller Spring (base)
    0x01177334, // Propeller Spring (Bottom arrows)
    0x01177BF0, // Propeller Spring (Top arrows)
    0x011659C4, // Fire Skull (Sky Rail) (head)
    0x0160132C, // Fire Skull (Aquatic Mine & Pool Quest) (head)
    0x00B3B67C, // Nocol Skull
    0x01091CE4, // Tree ST Trunk
    0x01092464, // Tree SNB Trunk

//  0x00B16244, // Chao Cont    // DC was tinted too??
};

/*
*    Chunk Lists
*/
static int ChunkObjectList[] =
{
    0x00B39E7C, // Rocket
    0x00B452AC, // Rocket Missile
    0x014D05AC, // E Shouku // Jet planes
    0x00B00B3C, // mhmissile (idle)
    0x00AFE18C, // mhmissile (takeoff)
    0x00EA2D00, // Rolling Tuta // Swing vine (horizontal)
    0x0104FC38, // Rolling Tuta Tate // Swing vine (vertical)
    0x01071FD0, // Bangie Tuta // Bungie vine
    0x00942374, // E Batabata
    0x00940774, // E Beeton
    0x00B0B88C, // Chao Key // Possibly too bright
    0x014B69D4, // E AI
    0x014BD4FC, // E AI Sheild
    0x014BA0CC, // E AI Lazer
    0x01462374, // E Unidus
    0x01462664, // E Unidus Orbiter

    /* Levelupdai Equipment models */

    0x00B2190C, // Sonic Rubber Unit
    0x00B23EC4, // Sonic Shoes
    0x00B243C4, // Sonic Flame Ring
    0x00B26F4C, // Shadow Shoes
    0x00B25024, // Shadow Flame Ring
    0x00B27F64, // TWalker Booster
    0x00B29104, // TWalker Hypercannon
    0x00B2A42C, // TWalker Lazer Blaster
    0x00B2B53C, // EWalker Jet Engine
    0x00B2CD8C, // EWalker Bazooka
    0x00B2E644, // EWalker Powergun
    0x00B2FE1C, // Knuckles Claws
    0x00B2F644, // Knuckles Gloves
    0x00B301AC, // Knuckles Air
    0x00B30C24, // Rouge Scope
    0x00B32CB4, // Rouge Nails
    0x00B351EC, // Rouge Boots
    0x00B24B24, // Sonic Magic Wrist
    0x00B30744, // Knuckles Sunglasses

    0x0101DAEC, // Big Bogy

    0x013F8320, // Boss Last 1

    0x00BF627C, // Iron Gate sirens
};

static int ChunkModelList[] =
{
    0x00B5674C, // SGRing
    0x00B43E1C, // Dash Panel (anim)
//  0x00B43C54, // Dash Panel (body)        // Absolutely too bright
    0x00B1CBDC, // Save Point Something
    0x00B1BD1C, // Save Point R
    0x00B1B564, // Save Point L
    0x00B459CC, // Rocket Missile (Button)
    0x00B35DC4, // Big Jump
    0x00B3589C, // Big Jump (Screen)
    0x00B492EC, // Itembox Air (Base)
    0x00B48F64, // Itembox Air (Top)
    0x00B48B44, // Itembox Air (Glass)
    0x00B1988C, // Balloon
    0x00B11ECC, // Solidbox
    0x00B4EC6C, // Goalring (text)
    0x00B4EE0C, // Goalring (text restart)
    0x00B1DE5C, // Chao Pipe
//  0x01681D28, // Fire Skull
    0x00B3C53C, // Basic Skull
    0x00B17AA4, // Switch (base)
    0x00BD3F54, // Bone (Cow Skull)
    0x00B20C04, // Levelupdai (base)
    0x00B20CF4, // Levelupdai (glow)
    0x00B21124, // Levelupdai (light)
    0x0162E024, // Minemizu

    0x00A2F034, // Tsubo
    0x0167856C, // PH Train Bed
    0x0167AD44, // PH Train
    0x016782E4, // PH Train Cylnder
    0x009B046C, // Poison
    0x00CFCCA4, // Tsubo (Sand Ocean)

    0x00B18ECC, // Bunchin (Under)
    0x00B18E0C, // Bunchin (Rims)
    0x00B18094, // Bunchin (Handle)
};

/*
*    Extra Lists
*/
static int GinjaModelListExtra[] =
{
    0x00B57134, // Ring LOD Far
    0x00B575C4, // Ring LOD Med
    0x00B57AD4, // Ring LOD Close
};

static int ChunkModelListExtra[] =
{
    0x00B3EA4C, // IronBall 2 Center
    0x00B3E49C, // IronBall 2 Cable
    0x00B3E374, // IronBall 2 Ball
    0x00B497C4, // Itembox (Bubble)
};

void
RFG_ModelTintFixBaseInit(void)
{
    /** Chunk **/
    for (int i = 0; i < ARYLEN(ChunkObjectList); ++i)
    {
        CnkObjectTintFix(ChunkObjectList[i]);
    }

    for (int i = 0; i < ARYLEN(ChunkModelList); ++i)
    {
        CnkModelTintFix(ChunkModelList[i]);
    }

    /** Ginja **/
    for (int i = 0; i < ARYLEN(GinjaObjectList); ++i)
    {
        GjsObjectTintFix(GinjaObjectList[i]);
    }

    for (int i = 0; i < ARYLEN(GinjaModelList); ++i)
    {
        GjsModelTintFix(GinjaModelList[i]);
    }

    /** Cart Models **/
    typedef struct
    {
        char data0[4];
        NJS_CNK_OBJECT* pObject;
        NJS_CNK_OBJECT* pLODObject;
        NJS_TEXLIST* pTexlist;
        char data1[8];
        short shrt0;
    }
    SPECIAL_INFO;

    SPECIAL_INFO* psi = GetDataDllAddr(SPECIAL_INFO, "specialInfo");

    if (!psi)
        return;

    for (int i = 0; i < 8; ++i)
    {
        if (psi[i].pObject)
            CnkObjectTintFix(psi[i].pObject);
        if (psi[i].pLODObject)
            CnkObjectTintFix(psi[i].pLODObject);
    }

    NJS_CNK_OBJECT* object_limo = GetDataDllAddr(NJS_CNK_OBJECT, "object_chara_limoall_limoall");
    CnkObjectTintFix(object_limo);
    object_limo = GetDataDllAddr(NJS_CNK_OBJECT, "object_tornado_3rd_tornado_3rd");
    CnkObjectTintFix(object_limo);
}

void
RFG_ModelTintFixDefaultInit(void)
{
    for (int i = 0; i < ARYLEN(ChunkModelListExtra); ++i)
    {
        CnkModelTintFix(ChunkModelListExtra[i]);
    }

    for (int i = 0; i < ARYLEN(GinjaModelListExtra); ++i)
    {
        GjsModelTintFix(GinjaModelListExtra[i]);
    }
}
