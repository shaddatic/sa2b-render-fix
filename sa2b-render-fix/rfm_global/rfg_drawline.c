/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */
#include <sa2b/writeop.h>   /* WriteJump                                            */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h> /* ninja                                              */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_draw.h>        /* core                                                 */

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
DrawLineExStart(const Uint32 BaseColor, const Sint32 Trans)
{
    rjDrawLineExStart(2.f, BaseColor, Trans);
}

static void
DrawLine3D(const NJS_POINT3* const vtx, const int Count)
{
    rjDrawLine3DExSetList(vtx, Count);
    rjDrawLineExEnd();
}

__declspec(naked)
static void
___DrawLineExStart(void)
{
    __asm
    {
        push [esp+4]
        push eax

        call DrawLineExStart

        pop eax
        add esp, 4
        retn
    }
}

__declspec(naked)
static void
___DrawLine3D(void)
{
    __asm
    {
        push eax
        push [esp+8]

        call DrawLine3D

        add esp, 4
        pop eax
        retn
    }
}

/****** Init ************************************************************************/
void
RFG_DrawLineInit(void)
{
    WriteJump(0x0077FE50, ___DrawLineExStart);
    WriteJump(0x0077FF90, ___DrawLine3D);
}
