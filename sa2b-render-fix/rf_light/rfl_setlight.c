/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#define SAMT_INCL_FUNCPTRS
#include <samt/sonic/light.h>   /* light                                            */
#undef SAMT_INCL_FUNCPTRS

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_ninja.h>           /* ninja                                            */

/****** Self ************************************************************************/
#include <rf_light/rfl_internal.h> /* parent & siblings                             */

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
SetLightIndex_RF(i32 light)
{
    if ( LightsGC[light].flag & 1 )
    {
        const LIGHT_GC* p_light = &LightsGC[light];

        rjSetLightColor(RJ_LIGHT_1, p_light->lr, p_light->lg, p_light->lb);

        rjSetAmbient(p_light->ar, p_light->ag, p_light->ab);

        rjSetLightVector(RJ_LIGHT_1, p_light->x, p_light->y, p_light->z);
    }
    else // Dreamcast light
    {
        const LIGHT* p_light = &Lights[light];

        rjSetLightColor(RJ_LIGHT_1, p_light->r, p_light->g, p_light->b);

        rjSetLightIntensity(RJ_LIGHT_1, p_light->inten, p_light->ambient);

        rjSetLightVector(RJ_LIGHT_1, p_light->x, p_light->y, p_light->z);
    }

    rjSetLightMatrix(RJ_LIGHT_1);
    rjSetLightSwitch(RJ_LIGHT_1, ON);

    // sync gx
    RF_PushRjLightToGX(RJ_LIGHT_1);
    RF_PushRjAmbientToGX();
}

static void
SetPlayerLightIndex_RF(i32 pno)
{
    SetLightIndex_RF( PlayerLight[pno & 1] );
}

/****** Naked ***********************************************************************/
__declspec(naked)
static void
___SetLightIndex_RF(void)
{
    __asm
    {
        push eax
        call SetLightIndex_RF
        pop eax
        retn
    }
}

__declspec(naked)
static void
___SetPlayerLightIndex_RF(void)
{
    __asm
    {
        push eax
        call SetPlayerLightIndex_RF
        pop eax
        retn
    }
}

/****** Init ************************************************************************/
void
RFL_SetLightInit(void)
{
    WriteJump(SetLightIndex_p, ___SetLightIndex_RF);
    WriteJump(0x00486E50     , ___SetPlayerLightIndex_RF);
}
