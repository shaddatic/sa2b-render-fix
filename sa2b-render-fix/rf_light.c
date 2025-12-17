/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* WriteJump                                        */

/****** GX **************************************************************************/
#include <samt/gx/gxlight.h>    /* gxlight                                          */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <samt/sonic/light.h>   /* light                                            */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_ninja.h>           /* rf ninja                                         */
#include <rf_shader.h>          /* shader constant                                  */

/****** Self ************************************************************************/
#include <rf_light.h>              /* self                                          */
#include <rf_light/rfl_internal.h> /* children                                      */

/************************/
/*  Constants           */
/************************/
/****** Max Light Index *************************************************************/
#define RXD_LIGHT_MAX           (4) /* gx shader only supports 4 lights             */

/************************/
/*  Structures          */
/************************/
/****** GX Light ********************************************************************/
typedef struct
{
    f32 r, g, b, a;
}
RX_COLOR;

typedef struct
{
    NJS_POINT3 pos;
    NJS_VECTOR vec;
    RX_COLOR   color;

    f32        angle_const;
    f32        angle_linear;
    f32        angle_quad;
    f32        angle;

    f32        atten_const;
    f32        atten_linear;
    f32        atten_quad;
}
RX_LIGHT_ATTR;

typedef struct
{
    RX_LIGHT_ATTR* pAttr;
    char _unk[60];
}
RX_LIGHT;

/************************/
/*  Game Data           */
/************************/
/****** GX Lights *******************************************************************/
#define _gj_light_list_         DATA_ARY(RX_LIGHT, 0x025F0120, [5])

/************************/
/*  Source              */
/************************/
/****** Usercall ********************************************************************/
static void
GX_LoadLightObjImm(const RX_LIGHT_ATTR* pAttr, int num)
{
    static const void* const GX_LoadLightObjImm_p = (void*)0x004240D0;

    __asm
    {
        mov ecx, [num]
        mov eax, [pAttr]
        call GX_LoadLightObjImm_p
    }
}

static void
rjLoadGxLight(Int light)
{
    GX_LoadLightObjImm(_gj_light_list_[light].pAttr, light);
}

/****** Static **********************************************************************/
static void
___rjCnkPushLightToGX(Int light)
{
    if (light >= RXD_LIGHT_MAX)
    {
        return;
    }

    if ( _rj_light_sw_ & ( 1 << light ) )
    {
        const RJS_LIGHT* restrict p_lite = &_rj_lights_[light];

        RX_LIGHT_ATTR* const p_gx_lite = _gj_light_list_[light].pAttr;

        p_gx_lite->color.r = p_lite->r * -p_lite->inten;
        p_gx_lite->color.g = p_lite->g * -p_lite->inten;
        p_gx_lite->color.b = p_lite->b * -p_lite->inten;

        p_gx_lite->angle_const  = 0.f;
        p_gx_lite->angle_linear = 0.f;
        p_gx_lite->angle_quad   = 0.f;
        p_gx_lite->angle        = 90.f;

        p_gx_lite->atten_const  =  4.f;
        p_gx_lite->atten_linear =  0.f;
        p_gx_lite->atten_quad   = -3.f;

        p_gx_lite->pos.x = -p_lite->v.x * 100000.f;
        p_gx_lite->pos.y = -p_lite->v.y * 100000.f;
        p_gx_lite->pos.z = -p_lite->v.z * 100000.f;

        p_gx_lite->vec = (NJS_VECTOR){ 0 };

        gjSetLightSwitch(light, TRUE);
    }
    else
    {
        gjSetLightSwitch(light, FALSE);
    }

    rjLoadGxLight(light);
}

/****** Rj To Gx ********************************************************************/
void
RF_PushRjLightToGX(i32 light)
{
    if ( light == RJ_LIGHT_ALL ) // all lights
    {
        for ( i32 i = 0; i < RJ_LIGHT_NUM; ++i )
        {
            ___rjCnkPushLightToGX(i);
        }
    }
    else
    {
        ___rjCnkPushLightToGX(light);
    }
}

void
RF_PushRjAmbientToGX(void)
{
    RF_ShaderSetConstantF4( RF_SCFV_AMBIENTREG_0, _rj_ambient_.r, _rj_ambient_.g, _rj_ambient_.b, 1.f );
}

/****** Hooks ***********************************************************************/
static void
gjSetLightColor_Hook(int id, Float r, Float g, Float b)
{
    _gj_light_list_[id].pAttr->color.a = 0.f;
    _gj_light_list_[id].pAttr->color.r = r;
    _gj_light_list_[id].pAttr->color.g = g;
    _gj_light_list_[id].pAttr->color.b = b;
}

static void
gjSetAmbient_Hook(Float ar, Float ag, Float ab)
{
    _rj_ambient_.r = ar;
    _rj_ambient_.g = ag;
    _rj_ambient_.b = ab;

    _rj_ambient_.inten = MAX( MAX( ar, ag ), ab );

    RF_ShaderSetConstantF4( RF_SCFV_AMBIENTREG_0, ar, ag, ab, 1.f );
}

static void
gjLoadLight_Hook(Int light)
{
    //if ( light != 0 )
    {
        const RX_LIGHT_ATTR* p_attr = _gj_light_list_[light].pAttr;

        RJS_LIGHT* p_lite = &_rj_lights_[light];

        p_lite->r = p_attr->color.r;
        p_lite->g = p_attr->color.g;
        p_lite->b = p_attr->color.b;

        p_lite->inten = 1.f;

        if ( p_attr->vec.x != 0.f || p_attr->vec.y != 0.f || p_attr->vec.z != 0.f )
        {
            p_lite->mode = RJ_LIGHT_MD_SPOT;

            p_lite->v.x = -p_attr->vec.x;
            p_lite->v.y = -p_attr->vec.y;
            p_lite->v.z = -p_attr->vec.z;

            p_lite->p = p_attr->pos;

            p_lite->near = 0.f;
            p_lite->far  = 0.f;

            p_lite->iang = 0.f;
            p_lite->oang = acosf(p_attr->angle) * -16.837942f;
        }
        else
        {
            p_lite->mode = RJ_LIGHT_MD_DIR;

            NJS_VECTOR vec = p_attr->pos;

            njUnitVector(&vec);

            p_lite->v = vec;
        }
    }

    GX_LoadLightObjImm(_gj_light_list_[light].pAttr, light);
}

__declspec(naked)
static void
___gjLoadLight_Hook(void)
{
    __asm
    {
        push eax
        call gjLoadLight_Hook
        pop eax
        retn
    }
}

/****** Init ************************************************************************/
void
RF_LightInit(void)
{
    /** Replace SetLight and SetAmbient functions **/
    WriteJump(0x0042A8B0, gjSetAmbient_Hook);
    WriteJump(0x0042A950, gjSetLightColor_Hook);

    WriteJump(0x0042AA60, ___gjLoadLight_Hook);

    RFL_FileInit();
    RFL_SetLightInit();
}
