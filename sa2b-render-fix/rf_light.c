#include <sa2b/core.h>

/** Mtx **/
#include <sa2b/c_mtx/c_mtx.h>

/** GX **/
#include <sa2b/gx/gxlight.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Game **/
#include <sa2b/src/light.h>

/** Self **/
#include <rf_light.h>

void
RFL_SetGjGlobalLight(RFE_GJLIGHT idxLight, const NJS_VECTOR* pVec)
{
    GXS_LIGHT_ATTR* const litep = _gj_lights_[idxLight].pAttr;

    litep->attenA.a =  0.0f;
    litep->attenA.r =  0.0f;
    litep->attenA.g =  0.0f;
    litep->attenA.b =  90.0f;

    litep->attenK.x =  4.0f;
    litep->attenK.y =  0.0f;
    litep->attenK.z = -3.0f;

    {
        NJS_VECTOR ans_vec;

        C_MTXMultVecSR(_gj_matrix_, pVec, &ans_vec);

        litep->pos.x = -ans_vec.x * 100000000.0f;
        litep->pos.y = -ans_vec.y * 100000000.0f;
        litep->pos.z = -ans_vec.z * 100000000.0f;
    }
    {
        NJS_VECTOR new_vec;

        new_vec.x = pVec->x * -100000.0f;
        new_vec.y = pVec->y * -100000.0f;
        new_vec.z = pVec->z * -100000.0f;

        C_MTXMultVec(_gj_matrix_, &new_vec, &new_vec, false);

        litep->pos = new_vec;
    }

    litep->vec = (NJS_VECTOR){ 0 };
}

void
RFL_SetGjLightColor(RFE_GJLIGHT idxLight, float r, float g, float b)
{
    gjSetLightColor(idxLight, r, g, b);
}

void
RFL_GjLightOn(RFE_GJLIGHT idxLight)
{
    gjSetLightSwitch(idxLight, true);
    gjLoadLight(idxLight);
}

void
RFL_GjLightOff(RFE_GJLIGHT idxLight)
{
    gjSetLightSwitch(idxLight, false);
    gjLoadLight(idxLight);
}
