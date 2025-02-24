/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>      /* core                                                 */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h> /* ninja                                              */

/****** GX **************************************************************************/
#include <samt/gx/gx.h>     /* GX                                                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h> /* parent & siblings                */

/************************/
/*  Source              */
/************************/
/****** Extern **********************************************************************/
#pragma optimize("", off)
void
CnkParseTinyData_Ext(Sint32 tinyData, Sint32 texFlags)
{
    static const uintptr_t p = 0x0042C4D0;

    __asm
    {
        push     [texFlags]
        mov eax, [tinyData]
        call p
        add esp, 4
    }
}

void
CnkParseMatColor_Ext(const s32 flag, const Sint16* const color)
{
    static const uintptr_t p = 0x0042C3F0;

    __asm
    {
        push     [flag]
        mov ecx, [color]
        call p
        add esp, 4
    }
}

void
CnkSetupLights_Ext(s32 fst_shr8)
{
    static const uintptr_t p = 0x0042C730;

    __asm
    {
        mov ebx, [fst_shr8]
        call p
    }
}

int
CnkVListShadow_Ext(const Sint32* vlist, void* njvtxbuf, int is_not_broken)
{
    static const uintptr_t p = 0x0042D270;

    int result;

    __asm
    {
        mov eax, [is_not_broken]
        push [njvtxbuf]
        mov ecx, [vlist]
        call p
        add esp, 4
        mov [result], eax
    }

    return result;
}
#pragma optimize("", on)

void
CnkPListShadow_Ext(const Sint16* plist, const void* njvtxbuf)
{
    DATA_REF(void*, 0x0174F7E8) = DATA_REF(void*, 0x0174F7EC);
    FUNC_PTR(void, __cdecl, (const Sint16*, const void*), 0x0042CF30)(plist, njvtxbuf);
    GX_End();
}
