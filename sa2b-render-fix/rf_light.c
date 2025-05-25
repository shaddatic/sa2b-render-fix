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
#include <rf_gx.h>              /* rf gx                                            */

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
/*  Export Data         */
/************************/
/****** Global Ambient Color ********************************************************/
RJS_AMBIENT _rj_cnk_light_ambient_;

/****** Global Lights ***************************************************************/
RJS_LIGHT _rj_cnk_light_[6];

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
___rjCnkSetLightVector(Int light, Float vx, Float vy, Float vz)
{
    RJS_LIGHT* p_lite = &_rj_cnk_light_[light];

    p_lite->type = RJD_CNK_LIGHTMD_DIR;

    p_lite->v.x = -vx;
    p_lite->v.y = -vy;
    p_lite->v.z = -vz;
}

static void
___rjCnkSetLightSwitch(Int light, Int flag)
{
    if ( flag )
    {
        _rj_cnk_light_switch_ |= ( 1<<light );
    }
    else
    {
        _rj_cnk_light_switch_ &= ~( 1<<light );
    }
}

static void
___rjCnkSetLightColor(Int light, Float lr, Float lg, Float lb)
{
    RJS_LIGHT* p_lite = &_rj_cnk_light_[light];

    p_lite->r = lr;
    p_lite->g = lg;
    p_lite->b = lb;

    p_lite->inten = 1.f;
}

static void
___rjCnkSetLightIntensity(Int light, Float inten, Float ambient)
{
    RJS_LIGHT* p_lite = &_rj_cnk_light_[light];

    p_lite->inten = CLAMP(inten, 0.f, 1.f);

    if (ambient >= 0.f)
    {
        const Float ambi = MIN(ambient, 1.f);

        _rj_cnk_light_ambient_.r = p_lite->r * ambi;
        _rj_cnk_light_ambient_.g = p_lite->g * ambi;
        _rj_cnk_light_ambient_.b = p_lite->b * ambi;

        _rj_cnk_light_ambient_.inten = ambi;
}
}

static void
___rjCnkSetLightMatrix(Int light)
{
    RJS_LIGHT* p_lite = &_rj_cnk_light_[light];

    switch ( p_lite->type )
    {
        case RJD_CNK_LIGHTMD_DIR:
        {
            njCalcVector(NULL, &p_lite->v, &p_lite->v);
            break;
        }
        case RJD_CNK_LIGHTMD_POINT:
        {
            njCalcPoint(NULL, &p_lite->p, &p_lite->p);
            break;
        }
        case RJD_CNK_LIGHTMD_SPOT:
        {
            njCalcVector(NULL, &p_lite->v, &p_lite->v);
            njCalcPoint( NULL, &p_lite->p, &p_lite->p);
            break;
        }
    }
}

static void
___rjCnkPushLightToGX(Int light)
{
    if (light >= RXD_LIGHT_MAX)
    {
        return;
    }

    if ( _rj_cnk_light_switch_ & ( 1 << light ) )
    {
        const RJS_LIGHT* restrict p_lite = &_rj_cnk_light_[light];

        RX_LIGHT_ATTR* const p_gx_lite = _gj_light_list_[light].pAttr;

        p_gx_lite->color.r = p_lite->r * p_lite->inten;
        p_gx_lite->color.g = p_lite->g * p_lite->inten;
        p_gx_lite->color.b = p_lite->b * p_lite->inten;

        p_gx_lite->angle_const  = 0.f;
        p_gx_lite->angle_linear = 0.f;
        p_gx_lite->angle_quad   = 0.f;
        p_gx_lite->angle        = 90.f;

        p_gx_lite->atten_const  =  4.f;
        p_gx_lite->atten_linear =  0.f;
        p_gx_lite->atten_quad   = -3.f;

        p_gx_lite->pos.x = p_lite->v.x * 100000.f;
        p_gx_lite->pos.y = p_lite->v.y * 100000.f;
        p_gx_lite->pos.z = p_lite->v.z * 100000.f;

        p_gx_lite->vec = (NJS_VECTOR){ 0 };

        gjSetLightSwitch(light, TRUE);
    }
    else
    {
        gjSetLightSwitch(light, FALSE);
    }

    rjLoadGxLight(light);
}

/****** Extern **********************************************************************/
void
rjCnkSetLightSwitch(Int light, Int flag)
{
    if ( light == RJD_CNK_LIGHT_ALL )
    {
        for ( int i = 0; i < RJD_CNK_LIGHT_NUM; ++i )
        {
            ___rjCnkSetLightSwitch(i, flag);
        }
    }
    else
    {
        ___rjCnkSetLightSwitch(light, flag);
    }
}

void
rjCnkSetAmbient(Float ar, Float ag, Float ab)
{
    _rj_cnk_light_ambient_.r = ar;
    _rj_cnk_light_ambient_.g = ag;
    _rj_cnk_light_ambient_.b = ab;

    /** ambient intensity is set to the largest color value, as it's
        the best approximation that can be made **/

    _rj_cnk_light_ambient_.inten = MAX( MAX( ar, ag ), ab );
}

void
rjCnkSetLightColor(Int light, Float lr, Float lg, Float lb)
{
    if ( light == RJD_CNK_LIGHT_ALL )
    {
        for ( int i = 0; i < RJD_CNK_LIGHT_NUM; ++i )
        {
            ___rjCnkSetLightColor(i, lr, lg, lb);
        }
    }
    else
    {
        ___rjCnkSetLightColor(light, lr, lg, lb);
    }
}

void
rjCnkSetLightIntensity(Int light, Float inten, Float ambient)
{
    if ( light == RJD_CNK_LIGHT_ALL )
    {
        for ( int i = 0; i < RJD_CNK_LIGHT_NUM; ++i )
        {
            ___rjCnkSetLightIntensity(i, inten, -1.f);
}
    }
    else
    {
        ___rjCnkSetLightIntensity(light, inten, ambient);
    }
}

void
rjCnkSetLightVector(Int light, Float vx, Float vy, Float vz)
{
    if ( light == RJD_CNK_LIGHT_ALL )
    {
        for ( int i = 0; i < RJD_CNK_LIGHT_NUM; ++i )
        {
            ___rjCnkSetLightVector(i, vx, vy, vz);
        }
    }
    else
    {
        ___rjCnkSetLightVector(light, vx, vy, vz);
    }
}

void
rjCnkSetLightMatrix(Int light)
{
    if ( light == RJD_CNK_LIGHT_ALL )
    {
        for ( int i = 0; i < RJD_CNK_LIGHT_NUM; ++i )
        {
            ___rjCnkSetLightMatrix(i);
    }
}
    else
    {
        ___rjCnkSetLightMatrix(light);
    }
}

/****** Rj To Gx ********************************************************************/
void
rjCnkPushLightToGX(Int light)
{
    if ( light == RJD_CNK_LIGHT_ALL ) // all lights
    {
        for ( int i = 0; i < RJD_CNK_LIGHT_NUM; ++i )
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
rjCnkPushAmbientToGX(void)
{
    RX_SetChanAmbColor_Direct(_rj_cnk_light_ambient_.r, _rj_cnk_light_ambient_.g, _rj_cnk_light_ambient_.b);
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
    _rj_cnk_light_ambient_.r = ar;
    _rj_cnk_light_ambient_.g = ag;
    _rj_cnk_light_ambient_.b = ab;

    _rj_cnk_light_ambient_.inten = MAX( MAX( ar, ag ), ab );

    RX_SetChanAmbColor_Direct(ar, ag, ab);
}

static void
gjLoadLight_Hook(Int light)
{
    //if ( light != 0 )
    {
        const RX_LIGHT_ATTR* p_attr = _gj_light_list_[light].pAttr;

        RJS_LIGHT* p_lite = &_rj_cnk_light_[light];

        p_lite->r = p_attr->color.r;
        p_lite->g = p_attr->color.g;
        p_lite->b = p_attr->color.b;

        p_lite->inten = 1.f;

        if ( p_attr->vec.x != 0.f || p_attr->vec.y != 0.f || p_attr->vec.z != 0.f )
        {
            p_lite->type = RJD_CNK_LIGHTMD_SPOT;

            p_lite->v.x = -p_attr->vec.x;
            p_lite->v.y = -p_attr->vec.y;
            p_lite->v.z = -p_attr->vec.z;

            p_lite->p = p_attr->pos;

            p_lite->near = 0.f;
            p_lite->far  = 0.f;

            p_lite->angmin = 0.f;
            p_lite->angmax = acosf(p_attr->angle) * -16.837942f;
        }
        else
        {
            p_lite->type = RJD_CNK_LIGHTMD_DIR;

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
