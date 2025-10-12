/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Game ************************************************************************************/
#include <samt/sonic/display.h>     /* dx9ctrl                                                  */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_ninja.h>               /* magic                                                    */

/****** Dx9ctrl *********************************************************************************/
#include <dx9ctrl/dx9ctrl.h>        /* dx9ctrl                                                  */

/****** Self ************************************************************************************/
#include <rf_system.h>              /* self                                                     */

/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#define Z_43BARS        (1.f)

/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
static NJS_TEXLIST* PbTexlist;
static Sint32       PbTexnum;
static bool         PbTexAlpha;
static NJS_COLOR    PbColorInnr = { 0xFF000000 };
static NJS_COLOR    PbColorEdge = { 0xFF000000 };

static Float        PbAspect    = 255.f;

/********************************/
/*  Includes                    */
/********************************/
/****** Pillar Box Modes ************************************************************************/
static inline void
SysDrawPillar_NonTex(f32 tgt_ratio, f32 dsp_ratio, Int trans)
{
    constexpr NJS_COLOR col_innr = PbColorInnr;
    constexpr NJS_COLOR col_edge = PbColorEdge;

    NJS_POLYGON_VTX poly[4];

    /** Init polyvtx **/
    {
        poly[0].y   = 0.0f;
        poly[0].z   = Z_43BARS;
        poly[0].col = col_edge.color;
        poly[1].y   = 480.0f;
        poly[1].z   = Z_43BARS;
        poly[1].col = col_edge.color;
        poly[2].y   = 0.0f;
        poly[2].z   = Z_43BARS;
        poly[2].col = col_innr.color;
        poly[3].y   = 480.0f;
        poly[3].z   = Z_43BARS;
        poly[3].col = col_innr.color;
    }

    const f32 res_shft = (dsp_ratio - 1.f) * (320.0f) + 1.f;
    const f32 tgt_shft = (tgt_ratio - 1.f) * (320.0f) + 1.f;

    // left bar
    {
        const f32 edge_pos = 0.f - res_shft;
        const f32 trgt_pos = 0.f - tgt_shft;

        poly[0].x = edge_pos;
        poly[1].x = edge_pos;
        poly[2].x = trgt_pos;
        poly[3].x = trgt_pos;

        rjDrawPolygon(poly, ARYLEN(poly), trans);
    }

    // right bar
    {
        const f32 edge_pos = 640.f + res_shft;
        const f32 trgt_pos = 640.f + tgt_shft;

        poly[0].x = edge_pos;
        poly[1].x = edge_pos;
        poly[2].x = trgt_pos;
        poly[3].x = trgt_pos;

        rjDrawPolygon(poly, ARYLEN(poly), trans);
    }
}

static inline void
SysDrawPillar_Tex(f32 tgt_ratio, f32 dsp_ratio, Int trans)
{
    constexpr NJS_COLOR col_innr = PbColorInnr;
    constexpr NJS_COLOR col_edge = PbColorEdge;

    NJS_TEXTURE_VTX poly[4];

    /** Init polyvtx **/
    {
        poly[0].y   = 0.0f;
        poly[0].z   = Z_43BARS;
        poly[0].col = col_innr.color;
        poly[1].y   = 480.0f;
        poly[1].z   = Z_43BARS;
        poly[1].col = col_innr.color;
        poly[2].y   = 0.0f;
        poly[2].z   = Z_43BARS;
        poly[2].col = col_edge.color;
        poly[3].y   = 480.0f;
        poly[3].z   = Z_43BARS;
        poly[3].col = col_edge.color;

        poly[0].v = 0.0f;
        poly[1].v = 1.0f;
        poly[2].v = 0.0f;
        poly[3].v = 1.0f;
    }

    const f32 res_shft = (dsp_ratio - 1.f) * (320.0f) + 1.f;
    const f32 tgt_shft = (tgt_ratio - 1.f) * (320.0f) + 1.f;

    const f32 bar_aspect = (res_shft - tgt_shft) / 480.f;

    // left bar
    {
        const f32 edge_pos = 0.f - res_shft;
        const f32 trgt_pos = 0.f - tgt_shft;

        poly[0].x = edge_pos;
        poly[1].x = edge_pos;
        poly[2].x = trgt_pos;
        poly[3].x = trgt_pos;

        poly[0].u = 0.5f - bar_aspect;
        poly[1].u = 0.5f - bar_aspect;
        poly[2].u = 0.5f;
        poly[3].u = 0.5f;

        rjDrawTextureEx(poly, ARYLEN(poly), trans);
    }

    // right bar
    {
        const f32 edge_pos = 640.f + res_shft;
        const f32 trgt_pos = 640.f + tgt_shft;

        poly[0].x = edge_pos;
        poly[1].x = edge_pos;
        poly[2].x = trgt_pos;
        poly[3].x = trgt_pos;

        poly[0].u = 0.5f + bar_aspect;
        poly[1].u = 0.5f + bar_aspect;
        poly[2].u = 0.5f;
        poly[3].u = 0.5f;

        rjDrawTextureEx(poly, ARYLEN(poly), trans);
    }
}

/****** Pillar Box ******************************************************************************/
void
RF_SysSetPillarColor(Uint32 inner, Uint32 edge)
{
    PbColorInnr.color = inner;
    PbColorEdge.color = edge;
}

void
RF_SysSetPillarTexture(NJS_TEXLIST* ptls, Int n, Int trans)
{
    PbTexlist  = ptls;
    PbTexnum   = n;
    PbTexAlpha = trans;
}

void
RF_SysEasySetPillarAspect(RF_SYS_PBA aspectmd)
{
    switch ( aspectmd )
    {
        case RF_SYS_PBA_43: default:
        {
            PbAspect = 1.f;
            break;
        }
        case RF_SYS_PBA_169:
        {
            PbAspect = 1.333333333333333f;
            break;
        }
    }
}

void
RF_SysSetPillarAspect(Float aspect)
{
    PbAspect = aspect;
}

/****** Pillar Box Draw ***********************************************************************&*/
void
RF_SysCtrlDrawPillar(bool passFinal)
{
    const f32 tgt_ratio = PbAspect;
    const f32 dsp_ratio = GetDisplayRatio();

    if ( dsp_ratio <= tgt_ratio )
    {
        return;
    }

    const Int trans = PbTexAlpha || (PbColorInnr.argb.a != 0xFF) || (PbColorEdge.argb.a != 0xFF);

    if ( trans && !passFinal )
    {
        return;
    }

    if ( PbTexlist )
    {
        njSetTexture(PbTexlist);
        njSetTextureNum(PbTexnum);

        SysDrawPillar_Tex(tgt_ratio, dsp_ratio, trans);
    }
    else
    {
        SysDrawPillar_NonTex(tgt_ratio, dsp_ratio, trans);
    }
}

void
RF_SysCtrlResetPillar(void)
{
    PbAspect          = 255.f;

    PbTexlist         = nullptr;
    PbTexnum          = -1;
    PbTexAlpha        = false;
    PbColorInnr.color = 0xFF000000;
    PbColorEdge.color = 0xFF000000;
}
