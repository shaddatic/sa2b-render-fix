/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>          /* core                                                         */
#include <samt/writeop.h>       /* write jump                                                   */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                                        */

#include <samt/modloader.h>
#include <samt/sonic/score.h>

/****** Render Fix ******************************************************************************/
#include <rf_core.h>            /* core                                                         */

/********************************/
/*  Source                      */
/********************************/
/****** Init ************************************************************************************/
static Angle
GhostTrainGetAngle(const NJS_POINT3* p1, const NJS_POINT3* p2)
{
    const Float y = -(p2->x - p1->x);
    const Float x = -(p2->z - p1->z);

    return njArcTan2(y, x);
}

__declspec(naked)
static void
___GhostTrainGetAngle(void)
{
    __asm
    {
        push ecx
        push eax

        call GhostTrainGetAngle

        add esp, 8
        retn
    }
}

/****** Init ************************************************************************************/
void
RFM_PumpkinInit(void)
{
    // Fix ghost train's weird jerking motion while in the lower area, caused by the start and
    // end points being the same position, freaking 'arctan2' out

    // You may be asking what I changed, and that's the fun part!
    // Nothing! I didn't change anything, I just decomp'd the function and now it works!
    // Compilers are fun.
    WriteJump(0x004B7230, ___GhostTrainGetAngle);
}
