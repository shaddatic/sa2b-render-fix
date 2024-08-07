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
