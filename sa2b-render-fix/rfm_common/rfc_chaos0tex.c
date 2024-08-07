#include <sa2b/core.h>
#include <sa2b/writemem.h>
#include <sa2b/writeop.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/player.h>

/** Figure **/
#include <sa2b/sonic/figure/knuckles.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_mdlutil.h>

static void __cdecl
SwapChaosTexID(KNUCKLESWK* kwp)
{
    NJS_CNK_OBJECT* objp = CHAR_OBJECTS[507].pObject->child;

    int16_t tex_id = (kwp->chaos0_texid >> 1) + 2;

    RF_CnkModelChangeTexID(objp->model, 0, tex_id);

    objp = objp->child->child->sibling->child->child->child->child->sibling->child->child->sibling->sibling->child;

    RF_CnkModelChangeTexID(objp->model, 0, tex_id);
}

__declspec(naked)
static void
__SwapChaosTexID()
{
    __asm
    {
        push eax
        push ebx
        push ecx
        push edx

        push ebp
        call SwapChaosTexID
        pop ebp

        pop edx
        pop ecx
        pop ebx
        pop eax
        retn
    }
}

static void __cdecl
SwapChaosTexID_Dely(KNUCKLESWK* kwp)
{
    NJS_CNK_OBJECT* objp = CHAR_OBJECTS[525].pObject->child;

    int16_t tex_id = (kwp->chaos0_texid >> 1) + 3;

    if (tex_id >= 7)
        tex_id = (kwp->chaos0_texid >> 1) - 4;

    tex_id += 2;

    RF_CnkModelChangeTexID(objp->model, 0, tex_id);

    objp = objp->child->child->sibling->child->child->child->child->sibling->child->child->sibling->sibling->child;

    RF_CnkModelChangeTexID(objp->model, 0, tex_id);
}

__declspec(naked)
static void
__SwapChaosTexID_Dely()
{
    __asm
    {
        push eax
        push ebx
        push ecx
        push edx

        push ebp
        call SwapChaosTexID_Dely
        pop ebp

        pop edx
        pop ecx
        pop ebx
        pop eax
        retn
    }
}

void
RFC_Chaos0TexInit()
{
    WriteNOP( 0x00731F0C, 0x00731FAA);
    WriteCall(0x00731F0C, __SwapChaosTexID);
    
    WriteNOP( 0x0073257F, 0x0073261A);
    WriteCall(0x0073257F, __SwapChaosTexID_Dely);
}
