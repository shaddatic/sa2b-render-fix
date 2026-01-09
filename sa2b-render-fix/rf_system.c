/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Game ************************************************************************************/
#include <samt/sonic/display.h>     /* display settings                                         */
#include <samt/sonic/input.h>       /* player input                                             */
#include <samt/sonic/game.h>        /* game vars                                                */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_ninja.h>               /* magic                                                    */

/****** Dx9ctrl *********************************************************************************/
#include <dx9ctrl/dx9ctrl.h>        /* dx9ctrl                                                  */

/****** Self ************************************************************************************/
#include <rf_system.h>                /* self                                                   */
#include <rf_system/rfsys_internal.h> /* children                                               */

/********************************/
/*  Constants                   */
/********************************/
/****** Idle Fade *******************************************************************************/
#define IDLE_TIME                   (60 * 60 * 2) /* timer: frames * seconds * minutes          */
#define IDLE_MAX                    (196)         /* max intensity                              */
#define IDLE_ADD                    (4)           /* add intensity                              */

/****** Pillar Depth ****************************************************************************/
#define Z_43BARS                    (1.f)       /* polygon depth                                */

/********************************/
/*  Data                        */
/********************************/
/****** Idle Fade *******************************************************************************/
static i16 IdleInten;
static i16 IdleFrame;

/****** Pillar Box ******************************************************************************/
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
SysDrawPillar_NonTex(f32 tgt_shft, f32 dsp_shft, Int trans)
{
    const NJS_COLOR col_innr = PbColorInnr;
    const NJS_COLOR col_edge = PbColorEdge;

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

    // left bar
    {
        const f32 edge_pos = 0.f - dsp_shft;
        const f32 trgt_pos = 0.f - tgt_shft;

        poly[0].x = edge_pos;
        poly[1].x = edge_pos;
        poly[2].x = trgt_pos;
        poly[3].x = trgt_pos;

        rjDrawPolygon(poly, ARYLEN(poly), trans);
    }

    // right bar
    {
        const f32 edge_pos = 640.f + dsp_shft;
        const f32 trgt_pos = 640.f + tgt_shft;

        poly[0].x = edge_pos;
        poly[1].x = edge_pos;
        poly[2].x = trgt_pos;
        poly[3].x = trgt_pos;

        rjDrawPolygon(poly, ARYLEN(poly), trans);
    }
}

static inline void
SysDrawPillar_Tex(f32 tgt_shft, f32 dsp_shft, Int trans)
{
    const NJS_COLOR col_innr = PbColorInnr;
    const NJS_COLOR col_edge = PbColorEdge;

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

    const f32 bar_aspect = (dsp_shft - tgt_shft) / 480.f;

    // left bar
    {
        const f32 edge_pos = 0.f - dsp_shft;
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
        const f32 edge_pos = 640.f + dsp_shft;
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

void
RF_SysDrawScreenFade(const NJS_COLOR color, Float z)
{
    const Uint32 alpha = color.argb.a;

    if ( alpha == 0x00 )
    {
        return;
    }

    NJS_POLYGON_VTX poly[4];

    njFogDisable();

    const f32 res_shift = (GetDisplayRatio() - 1.f) * (320.0f) + 1.f;

    poly[0].x   = 0.f - res_shift;
    poly[0].y   = 0.f;
    poly[0].z   = z;
    poly[0].col = color.color;

    poly[1].x   = 0.f - res_shift;
    poly[1].y   = 480.f;
    poly[1].z   = z;
    poly[1].col = color.color;

    poly[2].x   = 640.f + res_shift;
    poly[2].y   = 0.f;
    poly[2].z   = z;
    poly[2].col = color.color;

    poly[3].x   = 640.f + res_shift;
    poly[3].y   = 480.f;
    poly[3].z   = z;
    poly[3].col = color.color;

    njColorBlendingMode(0, NJD_COLOR_BLENDING_BOTHSRCALPHA);

    rjDrawPolygon(poly, ARYLEN(poly), alpha != 0xFF);

    njFogEnable();
}

/****** Idle Fade Control ***********************************************************************/
static bool
SysCheckPlayerInput(void)
{
    for ( int i = 0; i < ARYLEN(per); ++i )
    {
        const PDS_PERIPHERAL* p_peri = per[i];

        if ( !p_peri )
        {
            continue;
        }

        if ( p_peri->on || p_peri->x1 || p_peri->x2 || p_peri->y1 || p_peri->y2 || p_peri->r || p_peri->l )
        {
            return false;
        }
    }

    return true;
}

void
RF_SysCtrlIdleFade(void)
{
    bool no_idle = false;

    i16 idle_frame = IdleFrame;
    i16 idle_inten = IdleInten;

    if ( ulGlobalMode != MD_ADVERTISE && ulGlobalMode != MD_ACTION )
    {
        no_idle = true;
    }

    if ( ssStageNumber == STAGE_CHAOWORLD && !ChkPause() )
    {
        // the Chao World bypass actually on Dreamcast too! Crazy that they thought this much
        // ahead (that people would want to be idle in the Chao Garden).
        // I added the pause check though!
        no_idle = true;
    }

    const bool is_idle = no_idle ? false : SysCheckPlayerInput();

    if ( is_idle )
    {
        idle_frame++;
    }
    else
    {
        idle_frame = 0;
    }

    if ( idle_frame >= IDLE_TIME )
    {
        idle_frame = IDLE_TIME;

        idle_inten += IDLE_ADD;

        if ( idle_inten > IDLE_MAX )
        {
            idle_inten = IDLE_MAX;
        }
    }
    else if ( idle_inten )
    {
        idle_inten -= IDLE_ADD;
    }

    IdleFrame = idle_frame;
    IdleInten = idle_inten;

    if ( !idle_inten )
    {
        return;
    }

    RF_SysDrawScreenFade( (NJS_COLOR){ .argb.a = (Uint8) idle_inten }, 1.f );
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

    const f32 dsp_shft = njCeil( (dsp_ratio - 1.f) * (320.0f) ); // to nearest pixel to be safe
    const f32 tgt_shft =       ( (tgt_ratio - 1.f) * (320.0f) );

    if ( PbTexlist )
    {
        njSetTexture(PbTexlist);
        njSetTextureNum(PbTexnum);

        SysDrawPillar_Tex(tgt_shft, dsp_shft, trans);
    }
    else
    {
        SysDrawPillar_NonTex(tgt_shft, dsp_shft, trans);
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

void
RF_SysInit(void)
{
    RF_SysVsyncInit();
}
