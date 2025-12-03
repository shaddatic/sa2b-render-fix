/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writeop.h>           /* writecall                                                */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_ninja.h>               /* rf ninja                                                 */
#include <rf_njcnk.h>               /* cnkdraw                                                  */

/****** Self ************************************************************************************/
#include <rf_module/rfm_global/rfg_internal.h> /* parent & siblings                             */

/********************************/
/*  Source                      */
/********************************/
/****** Draw ************************************************************************************/
static void
EasyDrawObject(NJS_CNK_OBJECT* object, void* fn)
{
    njCnkEasyDrawObject(object);
}

__declspec(naked)
static void
___njCnkEasyDrawModel(void)
{
    __asm
    {
        push        eax
        call        njCnkEasyDrawModel
        add esp,    4
        retn
    }
}

static void
MenuScreenEffectFix(NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame)
{
    const u32 nj3dflag = _nj_control_3d_flag_;

    _nj_control_3d_flag_ = nj3dflag & ~NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL;

    njCnkSimpleDrawMotion(object, motion, frame);

    _nj_control_3d_flag_ = nj3dflag;
}

__declspec(naked)
static void
___MenuScreenEffectFix(void)
{
    __asm
    {
        push        [esp+8]  // frame
        push        ecx      // motion
        push        [esp+12] // object
        call        MenuScreenEffectFix
        add esp,    12
        retn
    }
}

/****** Init ************************************************************************************/
void
RFG_DrawFunctionInit(void)
{
    /****** njCnkTransformObject : 0x0042EB30 ***********************************************/

    // -> njCnkEasyDrawObject

    WriteCall(0x00756A2E, EasyDrawObject);         // Jump Aura (bfc issue)
    WriteCall(0x00756D77, EasyDrawObject);         // Other Aura
    WriteCall(0x007561FF, EasyDrawObject);         // Spindash Aura

    WriteCall(0x0055D53E, EasyDrawObject);         // ALO ball

    /****** njCnkCacheDrawModel : 0x0042E6C0 ************************************************/

    // -> njCnkEasyDrawModel

    WriteCall(0x006D9F51, ___njCnkEasyDrawModel);  // Savepoint
    WriteCall(0x006D9FFE, ___njCnkEasyDrawModel);
    WriteCall(0x006DA08A, ___njCnkEasyDrawModel);

    WriteCall(0x00656B3A, ___njCnkEasyDrawModel); // Sand Ocean: Moon
    WriteCall(0x0051CFD6, ___njCnkEasyDrawModel); // ^ 2P

    WriteCall(0x004BACCF, ___njCnkEasyDrawModel); // Eternal Engine 2P: Space
    WriteCall(0x004BADBF, ___njCnkEasyDrawModel); // ^

    /****** Other ***************************************************************************/

    ___NOTE("This one is not technically a draw function issue...");

    WriteCall(0x0066838C, ___MenuScreenEffectFix); // DC menu screen effect text too bright
}
