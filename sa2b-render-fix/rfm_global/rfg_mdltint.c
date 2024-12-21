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

void
RFG_ModelTintInit(void)
{
    GjsObjectTintFix(0x00B46A38); // Rocket Missile (base)
    GjsObjectTintFix(0x00B3AA70); // Rocket (base)
    GjsObjectTintFix(0x01176AE8); // Propeller Spring (blades & spring)
    GjsObjectTintFix(0x0116598C); // Fire Skull (Sky Rail) (jaw & box)
    GjsObjectTintFix(0x0161AA38); // Fire Skull (Aquatic Mine & Pool Quest) (jaw & box)

//  GjsModelTintFix(0x00B1ED2C); // 3SPRING (base)
//  GjsModelTintFix(0x00B1E6AC); // 3SPRING 1
//  GjsModelTintFix(0x00B54504); // SPRINGA (base)
//  GjsModelTintFix(0x00B54214); // SPRINGA (spring)
//  GjsModelTintFix(0x00B53E34); // SPRINGA (face)
//  GjsModelTintFix(0x00B56160); // SPRINGB (base)
//  GjsModelTintFix(0x00B54A4C); // SPRINGB (spring)
//  GjsModelTintFix(0x00B5495C); // SPRINGB (face)
    GjsModelTintFix(0x00B0D7CC); // Knudai  // Mystic Shrine
    GjsModelTintFix(0x00AEED4C); // Dammy   // Metal Harbor Static Missiles
    GjsModelTintFix(0x011772D8); // Propeller Spring (base)
    GjsModelTintFix(0x01177334); // Propeller Spring (Bottom arrows)
    GjsModelTintFix(0x01177BF0); // Propeller Spring (Top arrows)
    GjsModelTintFix(0x011659C4); // Fire Skull (Sky Rail) (head)
    GjsModelTintFix(0x0160132C); // Fire Skull (Aquatic Mine & Pool Quest) (head)
    GjsModelTintFix(0x00B3B67C); // Nocol Skull
    GjsModelTintFix(0x01091CE4); // Tree ST Trunk
    GjsModelTintFix(0x01092464); // Tree SNB Trunk

    // to be removed when specular is restored

//  GjsModelTintFix(0x00B57134); // Ring LOD Far
//  GjsModelTintFix(0x00B575C4); // Ring LOD Med
//  GjsModelTintFix(0x00B57AD4); // Ring LOD Close

    CnkModelTintFix(0x00B5674C); // SGRing // Cart rings
}
