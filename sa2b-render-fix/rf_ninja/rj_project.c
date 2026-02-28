/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writeop.h>           /* WriteJump                                                */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */
#include <samt/ninja/njcontext.h>   /* ninja context                                            */

/****** Game ************************************************************************************/
#include <samt/sonic/display.h>     /* resolution                                               */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Dx9ctrl *********************************************************************************/
#include <dx9ctrl/dx9_renderstate.h> /* z func                                                  */

/****** Self ************************************************************************************/
#include <rf_ninja/rj_internal.h>  /* parent & siblings                                         */

/********************************/
/*  Game Variables              */
/********************************/
/****** Project *********************************************************************************/
#define mat_proj_screen             DATA_REF(NJS_MATRIX44, 0x01AF18C0)

/********************************/
/*  Source                      */
/********************************/
/****** Project *********************************************************************************/
static void
rjInitProjMatrix(NJS_MATRIX44* dm, f32 view, f32 ratio, f32 near, f32 far)
{
    const f32 vtan = tanf(view * 0.5f);

    const f32 clip_range = far - near;

    *dm = (NJS_MATRIX44)
    {
        .m[0][0] = 1.f / (vtan * ratio),
        .m[1][1] = 1.f / (vtan),
        .m[2][2] = near / clip_range,
        .m[2][3] = far * (near / clip_range),
        .m[3][2] = -1.f,
    };

    // undo ratio adjustment, why do it like this?
    ratio *= GetDisplayRatioY() / GetDisplayRatioX();

    mat_proj_screen = (NJS_MATRIX44)
    {
        .m[0][0] = 1.f / (vtan * ratio),
        .m[1][1] = 1.f / (vtan),
        .m[2][2] = far / clip_range,
        .m[2][3] = -1.f,
        .m[3][2] = far * (near / clip_range),
    };

    DX9_SetZFunc(DX9_CMP_GEQ);
}

__declspec(naked)
static void
___InitProjMatrix(void)
{
    __asm
    {
        push        [esp+16]
        push        [esp+16]
        push        [esp+16]
        push        [esp+16]
        push        eax

        call        rjInitProjMatrix

        add esp,    20
        retn
    }
}

/****** Init ************************************************************************************/
void
RJ_ProjectInit(void)
{
    WriteJump(0x00427220, ___InitProjMatrix);
}
