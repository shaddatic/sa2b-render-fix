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
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _C_MTX_H_
#define _C_MTX_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njmatrix.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Make unit matrix **/
void    C_MTXIdentity(NJS_MATRIX* m);

/** Multiply vector, 'sr' to control scale and rotation only **/
void    C_MTXMultVec(const NJS_MATRIX* m, const NJS_VECTOR* vs, NJS_VECTOR* vd, bool sr);

/** Multiply vector with only scale and rotation (different function from above) **/
void    C_MTXMultVecSR(const NJS_MATRIX* m, const NJS_VECTOR* vs, NJS_VECTOR* vd);

/** Multiply matrices **/
void    C_MTXConcat(const NJS_MATRIX* mpre, const NJS_MATRIX* mpst, NJS_MATRIX* md);

/** Modify matrices **/
void    C_MTXScale(NJS_MATRIX* m, float x, float y, float z);
void    C_MTXTrans(NJS_MATRIX* m, float x, float y, float z);

EXTERN_END

#endif /* _C_MTX_H_ */
