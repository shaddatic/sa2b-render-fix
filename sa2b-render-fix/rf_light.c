#include <sa2b/core.h>

/** Mtx **/
#include <sa2b/c_mtx/c_mtx.h>

/** GX **/
#include <sa2b/gx/gxlight.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Game **/
#include <sa2b/sonic/light.h>

/** Self **/
#include <rf_light.h>

#define MAX_LIGHT       (4)

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
            gjSetLightColor(i, lr, lg, lb);
        }
    }
    else if (light <= MAX_LIGHT)
    {
        light--;

        gjSetLightColor(light, lr, lg, lb);
    }
}

void
rjCnkSetAmbient(Float ar, Float ag, Float ab)
{
    gjSetAmbient(ar, ag, ab);
}

void
rjCnkSetMultiAmbient(Float ar, Float ag, Float ab)
{
    gjSetAmbient(ar * 0.5f, ag * 0.5f, ab * 0.5f);
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
