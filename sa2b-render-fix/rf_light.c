/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* WriteJump                                        */

/****** GX **************************************************************************/
#include <samt/gx/gxlight.h>

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <samt/sonic/light.h>   /* light                                            */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_gx.h>              /* rf gx                                            */

/****** Self ************************************************************************/
#include <rf_light.h>           /* self                                             */

/************************/
/*  Constants           */
/************************/
/****** Max Light Index *************************************************************/
#define MAX_LIGHT               (4) /* shader only supports 4 lights                */

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
    NJS_VECTOR vec;
    NJS_POINT3 pos;
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
NJS_ARGB _rj_ambi_color_;

/************************/
/*  Game Data           */
/************************/
/****** Global Ambient Color ********************************************************/
#define _gj_light_list_         DATA_ARY(RX_LIGHT, 0x025F0120, [5])

/************************/
/*  Source              */
/************************/
/****** Extern **********************************************************************/
void
rjSetLightColor(int id, Float r, Float g, Float b)
{
    _gj_light_list_[id].pAttr->color.a = 0.f;
    _gj_light_list_[id].pAttr->color.r = r;
    _gj_light_list_[id].pAttr->color.g = g;
    _gj_light_list_[id].pAttr->color.b = b;
}

void
rjSetAmbient(Float ar, Float ag, Float ab)
{
    _rj_ambi_color_.r = ar;
    _rj_ambi_color_.g = ag;
    _rj_ambi_color_.b = ab;

    RX_SetChanAmbColor_Direct(ar, ag, ab);
}

static void
SetLightVector(Int light, Float vx, Float vy, Float vz)
{
    RX_LIGHT_ATTR* const litep = _gj_light_list_[light].pAttr;

    litep->angle_const  = 0.f;
    litep->angle_linear = 0.f;
    litep->angle_quad   = 0.f;
    litep->angle        = 90.f;

    litep->atten_const  =  4.f;
    litep->atten_linear =  0.f;
    litep->atten_quad   = -3.f;

    litep->vec.x = vx * -100000.0f;
    litep->vec.y = vy * -100000.0f;
    litep->vec.z = vz * -100000.0f;

    litep->pos = (NJS_VECTOR){ 0 };
}

void
rjCnkSetLightVectorEx(Int light, Float vx, Float vy, Float vz)
{
    if (light == RFD_CNK_MULTILIGHT_ALL) // all lights
    {
        for (int i = 0; i < MAX_LIGHT; ++i)
        {
            SetLightVector(i, vx, vy, vz);
        }
    }
    else if (light <= MAX_LIGHT)
    {
        SetLightVector(light - 1, vx, vy, vz);
    }
}

void
rjCnkSetLightColor(Int light, Float lr, Float lg, Float lb)
{
    if (light == RFD_CNK_MULTILIGHT_ALL) // all lights
    {
        for (int i = 0; i < MAX_LIGHT; ++i)
        {
            rjSetLightColor(i, lr, lg, lb);
        }
    }
    else if (light <= MAX_LIGHT)
    {
        rjSetLightColor(light - 1, lr, lg, lb);
    }
}

void
rjCnkSetAmbient(Float ar, Float ag, Float ab)
{
    rjSetAmbient(ar, ag, ab);
}

void
rjCnkSetLightSwitch(Int light, Int flag)
{
    if (light == RFD_CNK_MULTILIGHT_ALL) // all lights
    {
        for (int i = 0; i < MAX_LIGHT; ++i)
        {
            gjSetLightSwitch(i, flag);
            gjLoadLight(i);
        }
    }
    else if (light <= MAX_LIGHT)
    {
        light--;

        gjSetLightSwitch(light, flag);
        gjLoadLight(light);
    }
}

void
rjCnkSetLightMatrices(void)
{
    for (int i = 0; i < MAX_LIGHT; ++i)
    {
        GXS_LIGHT_ATTR* const litep = _gj_lights_[i].pAttr;

        njCalcVector(NULL, &litep->vec, &litep->vec);
    }
}

/****** Init ************************************************************************/
void
RF_LightInit(void)
{
    /** Replace SetLight and SetAmbient functions **/
    WriteJump(0x0042A8B0, rjSetAmbient);
    WriteJump(0x0042A950, rjSetLightColor);
}
