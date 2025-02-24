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
#include <rf_eventinfo.h>       /* event data                                       */
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_light.h>           /* render fix light                                 */

/****** Self ************************************************************************/
#include <rfm_event/ev_draw/evd_internal.h> /* parent & siblings                    */

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

#define EventLights             DATA_ARY(EVENT_LIGHT, 0x01DB0EE0, [4])

static AMBI_COLOR SingleAmbi;
static AMBI_COLOR MultiAmbi;

/************************/
/*  Source              */
/************************/
/****** Extern **********************************************************************/
void
EventLightSet(void)
{
    /** Color & Vector **/

    for (int i = 0, light = RFD_CNK_MULTILIGHT_1; i < ARYLEN(EventLights); ++i, ++light)
    {
        const EVENT_LIGHT* const p_light = &EventLights[i];

        NJS_VECTOR vec = p_light->vec;

        njUnitVector(&vec);

        rjCnkSetLightColor(light, p_light->r, p_light->g, p_light->b);
        rjCnkSetLightVectorEx(light, vec.x, vec.y, vec.z);
    }

    rjCnkSetLightMatrices(); // set vector reflect matrix

    /** Ambient **/

    const EVENT_LIGHT* const p_bl = &EventLights[0];

    MultiAmbi.r = p_bl->amb_r;
    MultiAmbi.g = p_bl->amb_g;
    MultiAmbi.b = p_bl->amb_b;

    SingleAmbi.r = p_bl->r * p_bl->ambi;
    SingleAmbi.g = p_bl->g * p_bl->ambi;
    SingleAmbi.b = p_bl->b * p_bl->ambi;
}

void
EventLightSwitchSingle(void)
{
    rjCnkSetLightSwitch(RFD_CNK_MULTILIGHT_1, true);

    rjCnkSetLightSwitch(RFD_CNK_MULTILIGHT_2, false);
    rjCnkSetLightSwitch(RFD_CNK_MULTILIGHT_3, false);
    rjCnkSetLightSwitch(RFD_CNK_MULTILIGHT_4, false);

    rjCnkSetAmbient(SingleAmbi.r, SingleAmbi.g, SingleAmbi.b);
}

void
EventLightSwitchMulti(Uint32 attr)
{
    rjCnkSetLightSwitch(RFD_CNK_MULTILIGHT_1, (attr & EV_ENTF_LIGHT1));
    rjCnkSetLightSwitch(RFD_CNK_MULTILIGHT_2, (attr & EV_ENTF_LIGHT2));
    rjCnkSetLightSwitch(RFD_CNK_MULTILIGHT_3, (attr & EV_ENTF_LIGHT3));
    rjCnkSetLightSwitch(RFD_CNK_MULTILIGHT_4, (attr & EV_ENTF_LIGHT4));

    rjCnkSetAmbient(MultiAmbi.r, MultiAmbi.g, MultiAmbi.b);
}
