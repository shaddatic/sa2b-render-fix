/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <samt/sonic/task.h>    /* task                                             */
#include <samt/sonic/njctrl.h>  /* ninja control                                    */
#include <samt/sonic/display.h> /* screen display                                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_light.h>           /* render fix light                                 */

/****** Self ************************************************************************/
#include <rf_module/rfm_event/ev_renderer/evr_internal.h> /* parent & siblings      */

/************************/
/*  Structures          */
/************************/
/****** Extern **********************************************************************/
typedef struct
{
    NJS_VECTOR vec; // light vector

    float r;        // light color
    float g;        // light color
    float b;        // light color

    float ambi;     // ambient value for single lighting

    float amb_r;    // ambient values for multi lighting
    float amb_g;    // ambient values for multi lighting
    float amb_b;    // ambient values for multi lighting
}
EVENT_LIGHT;

typedef struct
{
    f32 r, g, b;
}
AMBI_COLOR;

/************************/
/*  Game Defs           */
/************************/
/****** Extern **********************************************************************/
#define EventLights             DATA_ARY(EVENT_LIGHT, 0x01DB0EE0, [4])

/************************/
/*  Data                */
/************************/
/****** Extern **********************************************************************/
static Float    SingleAmbi;
static AMBI_COLOR MultiAmbi;

/************************/
/*  Source              */
/************************/
/****** Extern **********************************************************************/
void
EventLightSet(void)
{
    /** Color & Vector **/

    for (int ix_lt = 0; ix_lt < ARYLEN(EventLights); ++ix_lt)
    {
        const EVENT_LIGHT* p_lt = &EventLights[ix_lt];

        NJS_VECTOR vec = p_lt->vec;

        njUnitVector(&vec);

        rjCnkSetLightColor(ix_lt, p_lt->r, p_lt->g, p_lt->b);
        rjCnkSetLightVector(ix_lt, vec.x, vec.y, vec.z);

        rjCnkSetLightMatrix(ix_lt); // set vector reflect matrix

        rjCnkPushLightToGX(ix_lt);
    }

    /** Ambient **/

    const EVENT_LIGHT* p_bl = &EventLights[0];

    MultiAmbi.r = p_bl->amb_r;
    MultiAmbi.g = p_bl->amb_g;
    MultiAmbi.b = p_bl->amb_b;

    SingleAmbi = p_bl->ambi;
}

void
EventLightSwitchSingle(void)
{
    rjCnkSetLightSwitch(RJD_CNK_LIGHT_1, ON);

    rjCnkSetLightIntensity(RJD_CNK_LIGHT_1, 1.f, SingleAmbi);

    // turn off all other lights
    rjCnkSetLightSwitch(RJD_CNK_LIGHT_2, OFF);
    rjCnkSetLightSwitch(RJD_CNK_LIGHT_3, OFF);
    rjCnkSetLightSwitch(RJD_CNK_LIGHT_4, OFF);
}

void
EventLightSwitchMulti(Uint32 attr)
{
    rjCnkSetLightSwitch(RJD_CNK_LIGHT_1, (attr & EV_ENTF_LIGHT1));
    rjCnkSetLightSwitch(RJD_CNK_LIGHT_2, (attr & EV_ENTF_LIGHT2));
    rjCnkSetLightSwitch(RJD_CNK_LIGHT_3, (attr & EV_ENTF_LIGHT3));
    rjCnkSetLightSwitch(RJD_CNK_LIGHT_4, (attr & EV_ENTF_LIGHT4));

    rjCnkSetAmbient(MultiAmbi.r, MultiAmbi.g, MultiAmbi.b);
}
