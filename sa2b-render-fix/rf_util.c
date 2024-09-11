#include <sa2b/core.h>
#include <sa2b/user.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Game **/
#include <sa2b/sonic/texture.h>

/** Render Fix **/
#include <rf_core.h>

/** Self **/
#include <rf_util.h>

void
RF_SwapTexFileTableIndex(TEX_PRSTABLE* pTexTable, int idx1, int idx2)
{
    TEX_PRSTABLE tmp = pTexTable[idx1];
    pTexTable[idx1] = pTexTable[idx2];
    pTexTable[idx2] = tmp;
}

void
RFU_LerpPoints(NJS_POINT3* pOutPt, const NJS_POINT3* pPt1, const NJS_POINT3* pPt2, f32 ratioPt1)
{
    const f32 inv_ratio = 1.f - ratioPt1;

    pOutPt->x = (pPt1->x * ratioPt1) + (pPt2->x * inv_ratio);
    pOutPt->y = (pPt1->y * ratioPt1) + (pPt2->y * inv_ratio);
    pOutPt->z = (pPt1->z * ratioPt1) + (pPt2->z * inv_ratio);
}

void
RFU_CalculateScreen(const NJS_POINT3* const pInPos, NJS_POINT2* const pOutPos)
{
    const f32 inv_dist = _nj_screen_.dist / pInPos->z;

    pOutPos->x = -(pInPos->x * _nj_screen_.ax * inv_dist) + 320.f;
    pOutPos->y =  (pInPos->y * _nj_screen_.ay * inv_dist) + 240.f;
}

void
RFU_ProjectScreen(const NJS_POINT3* const pInPos, NJS_POINT2* const pOutPos)
{
    NJS_POINT3 pt3;

    njCalcPoint(NULL, pInPos, &pt3);

    RFU_CalculateScreen(&pt3, pOutPos);
}

bool
RFU_CalcInvertedMatrix(const NJS_MATRIX* m)
{
    if (!m)
        m = _nj_curr_matrix_;

    NJS_VECTOR x1 = { m->m[0][0], m->m[1][0], m->m[2][0] };
    NJS_VECTOR y1 = { m->m[0][1], m->m[1][1], m->m[2][1] };
    NJS_VECTOR z1 = { m->m[0][2], m->m[1][2], m->m[2][2] };

    NJS_VECTOR cz; // cx, cy, cz; // Calculated

    njOuterProduct2(&x1, &y1, &cz);

    const f32 sz1 = njInnerProduct(&cz, &z1);

    return (sz1 < 0.0f);
}
