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
#include <rf_ninja.h>           /* render fix ninja                                 */
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

        rjSetLightColor(ix_lt, p_lt->r, p_lt->g, p_lt->b);
        rjSetLightVector(ix_lt, vec.x, vec.y, vec.z);

        rjSetLightMatrix(ix_lt); // set vector reflect matrix

        RF_PushRjLightToGX(ix_lt);
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
    rjSetLightSwitch(RJ_LIGHT_1, ON);

    rjSetLightIntensity(RJ_LIGHT_1, 1.f, SingleAmbi);

    // turn off all other lights
    rjSetLightSwitch(RJ_LIGHT_2, OFF);
    rjSetLightSwitch(RJ_LIGHT_3, OFF);
    rjSetLightSwitch(RJ_LIGHT_4, OFF);
}

void
EventLightSwitchMulti(Uint32 attr)
{
    rjSetLightSwitch(RJ_LIGHT_1, (attr & EV_ENTF_LIGHT1));
    rjSetLightSwitch(RJ_LIGHT_2, (attr & EV_ENTF_LIGHT2));
    rjSetLightSwitch(RJ_LIGHT_3, (attr & EV_ENTF_LIGHT3));
    rjSetLightSwitch(RJ_LIGHT_4, (attr & EV_ENTF_LIGHT4));

    rjSetAmbient(MultiAmbi.r, MultiAmbi.g, MultiAmbi.b);
}
