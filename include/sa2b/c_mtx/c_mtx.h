/*
*   Sonic Adventure Mod Tools (SA2B) - '/c_mtx/c_mtx.h'
*
*   Description:
*       Internal matrix functions used by Ginja. 'C' likely
*   stands for 'Core.' Some of these are prefixed 'PS' in
*   later game symbols but they contain other differences too.
*   I just stuck to the 'C' prefix.
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _C_MTX_H_
#define _C_MTX_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Typedefs            */
/************************/
typedef float   MATRIX_4X4[16];

/************************/
/*  Enums               */
/************************/
enum {
    M16_00, M16_01, M16_02, M16_03,
    M16_10, M16_11, M16_12, M16_13,
    M16_20, M16_21, M16_22, M16_23,
    M16_30, M16_31, M16_32, M16_33
};

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Make unit matrix **/
void    C_MTXIdentity(GJS_MATRIX* m);

/** Multiply vector, 'sr' to control scale and rotation only **/
void    C_MTXMultVec(GJS_MATRIX* m, NJS_VECTOR* vs, NJS_VECTOR* vd, bool sr);

/** Multiply vector with only scale and rotation (different function from above) **/
void    C_MTXMultVecSR(GJS_MATRIX* m, NJS_VECTOR* vs, NJS_VECTOR* vd);

/** Multiply matrices **/
void    C_MTXConcat(GJS_MATRIX* md, GJS_MATRIX* md2, GJS_MATRIX* ms);

/** Modify matrices **/
void    C_MTXScale(GJS_MATRIX* m, float x, float y, float z);
void    C_MTXTrans(GJS_MATRIX* m, float x, float y, float z);

/** Convert matrix (SAMT) **/
/*
*   Convert and transpose Ginja 3x4 matrix to 4x4 matrix.
*   Functions return non-const argument.
*/
GJS_MATRIX* C_MTX16To12(GJS_MATRIX* m12, const MATRIX_4X4* m16);
MATRIX_4X4* C_MTX12To16(MATRIX_4X4* m16, const NJS_MATRIX* m12);

EXTERN_END

#endif /* _C_MTX_H_ */
