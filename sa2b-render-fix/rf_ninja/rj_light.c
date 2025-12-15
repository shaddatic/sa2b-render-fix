/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Self ************************************************************************************/
#include <rf_ninja/rj_internal.h>   /* parent & siblings                                        */

/********************************/
/*  Extern Variables            */
/********************************/
/****** Lights **********************************************************************************/
RJS_LIGHT   _rj_lights_[6];         /* light data                                               */

/****** Ambient Light ***************************************************************************/
RJS_AMBIENT _rj_ambient_;           /* ambient light data                                       */

/********************************/
/*  Source                      */
/********************************/
/****** Static **********************************************************************************/
static void
___rjSetLightVector(Int light, Float vx, Float vy, Float vz)
{
    RJS_LIGHT* p_lite = &_rj_lights_[light];

    p_lite->mode = RJ_LIGHT_MD_DIR;

    p_lite->v.x = vx;
    p_lite->v.y = vy;
    p_lite->v.z = vz;
}

static void
___rjSetLightSwitch(Int light, Int flag)
{
    if ( flag )
    {
        _rj_light_sw_ |= ( 1<<light );
    }
    else
    {
        _rj_light_sw_ &= ~( 1<<light );
    }
}

static void
___rjSetLightColor(Int light, Float lr, Float lg, Float lb)
{
    RJS_LIGHT* p_lite = &_rj_lights_[light];

    p_lite->r = lr;
    p_lite->g = lg;
    p_lite->b = lb;

    p_lite->inten = -1.f;
}

static void
___rjSetLightIntensity(Int light, Float inten, Float ambient)
{
    RJS_LIGHT* p_lite = &_rj_lights_[light];

    p_lite->inten = -inten;

    if (ambient >= 0.f)
    {
        const Float ambi = MIN(ambient, 1.f);

        const Float ar = p_lite->r * ambi;
        const Float ag = p_lite->g * ambi;
        const Float ab = p_lite->b * ambi;

        _rj_ambient_.r = ar;
        _rj_ambient_.g = ag;
        _rj_ambient_.b = ab;

        _rj_ambient_.inten = ambi;
    }
}

static void
___rjSetLightPoint(Int light, Float px, Float py, Float pz)
{
    RJS_LIGHT* p_lite = &_rj_lights_[light];

    p_lite->mode = RJ_LIGHT_MD_POINT;

    p_lite->p.x = px;
    p_lite->p.y = py;
    p_lite->p.z = pz;
}

static void
___rjSetLightRange(Int light, Float nrange, Float frange)
{
    RJS_LIGHT* p_lite = &_rj_lights_[light];

    p_lite->near = nrange * nrange;

    const Float f_n = (frange - nrange);

    if ( f_n < 0.f )
    {
        p_lite->far = 0.f;
    }
    else if ( f_n == 0.f )
    {
        p_lite->far = -1.0f;
    }
    else
    {
        const Float f = 1.f / (frange - nrange);

        p_lite->far = -(f * f);
    }
}

static void
___rjSetLightMatrix(Int light)
{
    RJS_LIGHT* p_lite = &_rj_lights_[light];

    switch ( p_lite->mode )
    {
        case RJ_LIGHT_MD_DIR:
        {
            njCalcVector(NULL, &p_lite->v, &p_lite->v);
            break;
        }
        case RJ_LIGHT_MD_POINT:
        {
            njCalcPoint(NULL, &p_lite->p, &p_lite->p);
            break;
        }
        case RJ_LIGHT_MD_SPOT:
        {
            njCalcVector(NULL, &p_lite->v, &p_lite->v);
            njCalcPoint( NULL, &p_lite->p, &p_lite->p);
            break;
        }
    }
}

/****** Extern **********************************************************************************/
void
rjSetLightSwitch(Int light, Int flag)
{
    if ( light == RJ_LIGHT_ALL )
    {
        for ( int i = 0; i < RJ_LIGHT_NUM; ++i )
        {
            ___rjSetLightSwitch(i, flag);
        }
    }
    else
    {
        ___rjSetLightSwitch(light, flag);
    }
}

void
rjSetAmbient(Float ar, Float ag, Float ab)
{
    _rj_ambient_.r = ar;
    _rj_ambient_.g = ag;
    _rj_ambient_.b = ab;

    /** ambient intensity is set to the largest color value, as it's
        the best approximation that can be made **/

    _rj_ambient_.inten = MAX( MAX( ar, ag ), ab );
}

void
rjSetLightColor(Int light, Float lr, Float lg, Float lb)
{
    if ( light == RJ_LIGHT_ALL )
    {
        for ( int i = 0; i < RJ_LIGHT_NUM; ++i )
        {
            ___rjSetLightColor(i, lr, lg, lb);
        }
    }
    else
    {
        ___rjSetLightColor(light, lr, lg, lb);
    }
}

void
rjSetLightIntensity(Int light, Float inten, Float ambient)
{
    if ( light == RJ_LIGHT_ALL )
    {
        for ( int i = 0; i < RJ_LIGHT_NUM; ++i )
        {
            ___rjSetLightIntensity(i, inten, -1.f);
        }
    }
    else
    {
        ___rjSetLightIntensity(light, inten, ambient);
    }
}

void
rjSetLightVector(Int light, Float vx, Float vy, Float vz)
{
    if ( light == RJ_LIGHT_ALL )
    {
        for ( int i = 0; i < RJ_LIGHT_NUM; ++i )
        {
            ___rjSetLightVector(i, vx, vy, vz);
        }
    }
    else
    {
        ___rjSetLightVector(light, vx, vy, vz);
    }
}

void
rjSetLightPoint(Int light, Float px, Float py, Float pz)
{
    if ( light == RJ_LIGHT_ALL )
    {
        for ( int i = 0; i < RJ_LIGHT_NUM; ++i )
        {
            ___rjSetLightPoint(i, px, py, pz);
        }
    }
    else
    {
        ___rjSetLightPoint(light, px, py, pz);
    }
}

void
rjSetLightRange(Int light, Float nrange, Float frange)
{
    if ( light == RJ_LIGHT_ALL )
    {
        for ( int i = 0; i < RJ_LIGHT_NUM; ++i )
        {
            ___rjSetLightRange(i, nrange, frange);
        }
    }
    else
    {
        ___rjSetLightRange(light, nrange, frange);
    }
}

void
rjSetLightMatrix(Int light)
{
    if ( light == RJ_LIGHT_ALL )
    {
        for ( int i = 0; i < RJ_LIGHT_NUM; ++i )
        {
            ___rjSetLightMatrix(i);
        }
    }
    else
    {
        ___rjSetLightMatrix(light);
    }
}
