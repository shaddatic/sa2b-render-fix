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

static void
GetMatrixCol(NJS_VECTOR* pVec, size_t nbCol)
{
    pVec->x = (*_gj_matrix_)[0 + nbCol];
    pVec->y = (*_gj_matrix_)[4 + nbCol];
    pVec->z = (*_gj_matrix_)[8 + nbCol];
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
RFU_ProjectTo2D(const NJS_POINT3* const pInPos, NJS_POINT2* const pOutPos)
{
    f32 inv_dist = _nj_screen_.dist / pInPos->z;

    pOutPos->x = -(pInPos->x * _nj_screen_.ax * inv_dist) + 320.f;
    pOutPos->y =  (pInPos->y * _nj_screen_.ay * inv_dist) + 240.f;
}

void
RFU_ProjectPointTo2D(const NJS_POINT3* const pInPos, NJS_POINT2* const pOutPos)
{
    NJS_POINT3 pt3;

    njCalcPoint(NULL, pInPos, &pt3);

    RFU_ProjectPointTo2D(&pt3, pOutPos);
}

bool
CalculateMatrixInverted(void)
{
    NJS_VECTOR x1, y1, z1;

    GetMatrixCol(&x1, 0);
    GetMatrixCol(&y1, 1);
    GetMatrixCol(&z1, 2);

    NJS_VECTOR cz; // cx, cy, cz; // Calculated

    njOuterProduct(&x1, &y1, &cz);
//  njOuterProduct(&z1, &x1, &cy);
//  njOuterProduct(&y1, &z1, &cx);

    const f32 sz1 = njInnerProduct(&cz, &z1);
//  const f32 sy1 = njInnerProduct(&cy, &y1);
//  const f32 sx1 = njInnerProduct(&cx, &x1);

    return (sz1 < 0.0f);
}
