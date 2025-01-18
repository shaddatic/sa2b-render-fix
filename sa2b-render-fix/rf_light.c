/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>          /* core                                             */
#include <sa2b/writeop.h>       /* WriteJump                                        */

/****** GX **************************************************************************/
#include <sa2b/gx/gxlight.h>

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <sa2b/sonic/light.h>   /* light                                            */

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
    RX_COLOR   attenA;
    NJS_VECTOR attenK;
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

void
rjCnkSetLightVectorEx(Int light, Float vx, Float vy, Float vz)
{
    if (light == RFD_CNK_MULTILIGHT_ALL) // all lights
    {
        for (int i = 0; i < MAX_LIGHT; ++i)
        {
            GXS_LIGHT_ATTR* const litep = _gj_lights_[i].pAttr;

            litep->attenA.a =  0.0f;
            litep->attenA.r =  0.0f;
            litep->attenA.g =  0.0f;
            litep->attenA.b =  90.0f;

            litep->attenK.x =  4.0f;
            litep->attenK.y =  0.0f;
            litep->attenK.z = -3.0f;

            litep->vec.x = vx * -100000.0f;
            litep->vec.y = vy * -100000.0f;
            litep->vec.z = vz * -100000.0f;

            litep->pos = (NJS_VECTOR){ 0 };
        }
    }
    else if (light <= MAX_LIGHT)
    {
        light--;

        GXS_LIGHT_ATTR* const litep = _gj_lights_[light].pAttr;

        litep->attenA.a =  0.0f;
        litep->attenA.r =  0.0f;
        litep->attenA.g =  0.0f;
        litep->attenA.b =  90.0f;

        litep->attenK.x =  4.0f;
        litep->attenK.y =  0.0f;
        litep->attenK.z = -3.0f;

        litep->vec.x = vx * -100000.0f;
        litep->vec.y = vy * -100000.0f;
        litep->vec.z = vz * -100000.0f;

        litep->pos = (NJS_VECTOR){ 0 };
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
        light--;

        rjSetLightColor(light, lr, lg, lb);
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
