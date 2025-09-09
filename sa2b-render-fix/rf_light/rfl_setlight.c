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

/****** Self ************************************************************************/
#include <rf_light/rfl_internal.h> /* parent & siblings                             */

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
SetLightIndex_RF(s32 light)
{
    if ( LightsGC[light].flag & 1 )
    {
        const LIGHT_GC* p_light = &LightsGC[light];

        rjCnkSetLightColor(RJD_CNK_LIGHT_1, p_light->lr, p_light->lg, p_light->lb);

        rjCnkSetAmbient(p_light->ar, p_light->ag, p_light->ab);

        rjCnkSetLightVector(RJD_CNK_LIGHT_1, p_light->vec.x, p_light->vec.y, p_light->vec.z);
    }
    else // Dreamcast light
    {
        const LIGHT* p_light = &Lights[light];

        rjCnkSetLightColor(RJD_CNK_LIGHT_1, p_light->r, p_light->g, p_light->b);

        rjCnkSetLightIntensity(RJD_CNK_LIGHT_1, p_light->dif, p_light->amb);

        rjCnkSetLightVector(RJD_CNK_LIGHT_1, p_light->vec.x, p_light->vec.y, p_light->vec.z);
    }

    rjCnkSetLightMatrix(RJD_CNK_LIGHT_1);
    rjCnkSetLightSwitch(RJD_CNK_LIGHT_1, ON);

    // sync gx
    rjCnkPushLightToGX(RJD_CNK_LIGHT_1);
    rjCnkPushAmbientToGX();
}

static void
SetPlayerLightIndex_RF(s32 pno)
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
