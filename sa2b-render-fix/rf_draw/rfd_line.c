/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */
#include <sa2b/writeop.h>   /* WriteJump                                            */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h> /* ninja                                              */

/****** Game ************************************************************************/
#include <sa2b/sonic/display.h> /* GetDisplayRatio                                  */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_util.h>        /* RFU_LerpPoints                                       */

/****** Self ************************************************************************/
#include <rf_draw/rfd_internal.h> /* parent & siblings                              */

/************************/
/*  Source Constants    */
/************************/
/****** Line Clipping ***************************************************************/
#define LINE_Z_MIN          (-1.f)

/****** Line Points *****************************************************************/
#define LINE_PTS_NUM        (4)

/************************/
/*  Source Data         */
/************************/
/****** Line Params *****************************************************************/
static Float  LineRadius;   /* set radius                                           */
static Uint32 LineColor;    /* set color                                            */
static Sint32 LineTrans;    /* set transparancy mode                                */

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
LineInitPolyVerts(NJS_POLYGON_VTX* const pVtx, const f32 zN, const f32 zF, const u32 color)
{
    const Float y = 0.5f * LineRadius;

    pVtx[0] = (NJS_POLYGON_VTX){ .x = 0.0f, .y = -y, .z = zN, .col = color }; /* near/left top vtx */
    pVtx[1] = (NJS_POLYGON_VTX){ .x = 1.0f, .y = -y, .z = zF, .col = color }; /* far/right top vtx */
    pVtx[2] = (NJS_POLYGON_VTX){ .x = 0.0f, .y = +y, .z = zN, .col = color }; /* near/left bottom vtx */
    pVtx[3] = (NJS_POLYGON_VTX){ .x = 1.0f, .y = +y, .z = zF, .col = color }; /* far/right bottom vtx */
}

static void
LineClipAtScreen(NJS_POINT3* pInOutPtB, const NJS_POINT3* pInPtF)
{
    const f32 ratio_b = (pInPtF->z + -LINE_Z_MIN) / ((pInPtF->z + -LINE_Z_MIN) + -(pInOutPtB->z + -LINE_Z_MIN));

    RFU_LerpPoints(pInOutPtB, pInOutPtB, pInPtF, ratio_b);
}

static f32
LineConvertZVal(const f32 z)
{
    return 1.f - z;
}

static void
LineDraw(const NJS_POINT2* const pPtN, const NJS_POINT2* const pPtF, const f32 oozN, const f32 oozF)
{
    NJS_MATRIX m;

    njUnitMatrix(&m);

    const f32 adj_x = (pPtF->x - pPtN->x);
    const f32 adj_y = (pPtF->y - pPtN->y);

    const Angle ang = njArcTan2( adj_y, adj_x );

    const f32 mag = sqrtf( (adj_x*adj_x) + (adj_y*adj_y) );

    njRotateZ(&m, ang);

    /** make poly list **/
    NJS_POLYGON_VTX poly[LINE_PTS_NUM];

    LineInitPolyVerts(poly, oozN, oozF, LineColor);

    /** calc poly list **/
    for (int i = 0; i < LINE_PTS_NUM; ++i)
    {
        NJS_POINT3 calc_d = { .x = poly[i].x * mag, .y = poly[i].y };

        njCalcPoint(&m, &calc_d, &calc_d);

        poly[i].x = calc_d.x + pPtN->x;
        poly[i].y = calc_d.y + pPtN->y;
    }

    njDrawPolygon(poly, ARYLEN(poly), LineTrans);
}

/****** Extern **********************************************************************/
void
rjDrawLineExStart(const Float r, const Uint32 BaseColor, const Sint32 Trans)
{
    LineRadius = r;
    LineColor  = BaseColor;
    LineTrans  = Trans;
}

void
rjDrawLine3DExSetStrip(const NJS_POINT3* vtx, const Sint32 Count)
{
    const size_t line_count = Count - 1;

    for (size_t line_index = 0; line_index < line_count; ++line_index, vtx += 1)
    {
        NJS_POINT3 pts[2];

        /** Calculate Z values **/
        njCalcPoint(NULL, &vtx[0], &pts[0]);
        njCalcPoint(NULL, &vtx[1], &pts[1]);

        /** Clip the line at the camera plane if it passes behind the camera.
            njProjectScreen can't handle positions that lie behind the screen **/
        if (pts[0].z > LINE_Z_MIN)
        {
            /** If both points are negative, the line is off screen. Skip to next point **/
            if (pts[1].z > LINE_Z_MIN)
                continue;

            LineClipAtScreen(&pts[0], &pts[1]);
        }
        else if (pts[1].z > LINE_Z_MIN)
        {
            LineClipAtScreen(&pts[1], &pts[0]);
        }

        NJS_POINT2 line_pos[2];

        /** Overwrite X & Y with screen coords **/
        RFU_CalculateScreen(&pts[0], &line_pos[0]);
        RFU_CalculateScreen(&pts[1], &line_pos[1]);

        /** make poly list **/
        const f32 ooz_n = -1.f / pts[0].z; /* near verts z */
        const f32 ooz_f = -1.f / pts[1].z; /* far verts z  */

        LineDraw(&line_pos[0], &line_pos[1], ooz_n, ooz_f);
    }
}

void
rjDrawLine3DExSetList(const NJS_POINT3* vtx, const Sint32 Count)
{
    const size_t line_count = Count / 2;

    for (size_t line_index = 0; line_index < line_count; ++line_index, vtx += 2)
    {
        NJS_POINT3 pts[2];

        /** Calculate Z values **/
        njCalcPoint(NULL, &vtx[0], &pts[0]);
        njCalcPoint(NULL, &vtx[1], &pts[1]);

        /** Clip the line at the camera plane if it passes behind the camera.
            njProjectScreen can't handle positions that lie behind the screen **/
        if (pts[0].z > LINE_Z_MIN)
        {
            /** If both points are negative, the line is off screen. Skip to next point **/
            if (pts[1].z > LINE_Z_MIN)
                continue;

            LineClipAtScreen(&pts[0], &pts[1]);
        }
        else if (pts[1].z > LINE_Z_MIN)
        {
            LineClipAtScreen(&pts[1], &pts[0]);
        }

        NJS_POINT2 line_pos[2];

        /** Overwrite X & Y with screen coords **/
        RFU_CalculateScreen(&pts[0], &line_pos[0]);
        RFU_CalculateScreen(&pts[1], &line_pos[1]);

        /** make poly list **/
        const f32 ooz_n = -1.f / pts[0].z; /* near verts z */
        const f32 ooz_f = -1.f / pts[1].z; /* far verts z  */

        LineDraw(&line_pos[0], &line_pos[1], ooz_n, ooz_f);
    }
}

void
rjDrawLine2DExSetStrip(const NJS_POINT2* vtx, const Float ooz, const Sint32 Count)
{
    const size_t line_count = Count - 1; // Ignore lines with 1 point

    for (size_t line_index = 0; line_index < line_count; ++line_index)
    {
        /** line is already in 2D coordinates, draw **/
        LineDraw(&vtx[0], &vtx[1], ooz, ooz);

        /** next strip point **/
        vtx += 1;
    }
}

void
rjDrawLine2DExSetList(const NJS_POINT2* vtx, const Float ooz, const Sint32 Count)
{
    const size_t line_count = Count / 2; // Ignore lines with 1 point

    for (size_t line_index = 0; line_index < line_count; ++line_index)
    {
        /** line is already in 2D coordinates, draw **/
        LineDraw(&vtx[0], &vtx[1], ooz, ooz);

        /** next line **/
        vtx += 2;
    }
}

void
rjDrawLineExEnd(void)
{
    return;
}

/****** Combined ********************************************************************/
void
rjDrawLineStrip3D(const NJS_POINT3* const vtx, const Sint32 Count, const Float r, const Uint32 Color)
{
    rjDrawLineExStart(r, Color, (Color & 0xFF000000) != 0xFF000000);
    rjDrawLine3DExSetStrip(vtx, Count);
    rjDrawLineExEnd();
}

void
rjDrawLineList3D(const NJS_POINT3* const vtx, const Sint32 Count, const Float r, const Uint32 Color)
{
    rjDrawLineExStart(r, Color, (Color & 0xFF000000) != 0xFF000000);
    rjDrawLine3DExSetList(vtx, Count);
    rjDrawLineExEnd();
}

void
rjDrawLineStrip2D(const NJS_POINT2* const vtx, const Float ooz, const Sint32 Count, const Float r, const Uint32 Color)
{
    rjDrawLineExStart(r, Color, (Color & 0xFF000000) != 0xFF000000);
    rjDrawLine2DExSetStrip(vtx, ooz, Count);
    rjDrawLineExEnd();
}

void
rjDrawLineList2D(const NJS_POINT2* const vtx, const Float ooz, const Sint32 Count, const Float r, const Uint32 Color)
{
    rjDrawLineExStart(r, Color, (Color & 0xFF000000) != 0xFF000000);
    rjDrawLine2DExSetList(vtx, ooz, Count);
    rjDrawLineExEnd();
}
