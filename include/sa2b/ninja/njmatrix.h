/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njmatrix.h'
*
*   Description:
*     Ninja matrix header.
*
*   Notes:
*     - Where the matrix parameter of a function is noted as (optional), a 'NULL'
*     value will use the current matrix instead of an arbitrary matrix.
*     - Noted rotation orders are reversed from their order in code. For example:
*     XYZ order, in code, will call 'njRotate#' in 'ZYX' order. 
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_NJ_MATRIX
#define H_NJ_MATRIX

/************************/
/*  External Headers    */
/************************/
/****** System **********************************************************************/
#include <sa2b/shinobi/sg_xpt.h> /* shinobi types                                   */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/njcommon.h> /* ninja common                                    */

EXTERN_START

/************************/
/*  Structures          */
/************************/
/****** Ninja Matrix ****************************************************************/
typedef struct
{
    Float m[3][4];          /* matrix in either 4x4 or 3x4 layout                   */
}
NJS_MATRIX;

/****** Ninja Matrix 4x4 ************************************************************/
typedef struct
{
    Float m[4][4];          /* matrix in 4x4 layout                                 */
}
NJS_MATRIX44;

/************************/
/*  Global Variables    */
/************************/
/****** Current Matrix **************************************************************/
#define _nj_curr_matrix_            DATA_REF(NJS_MATRIX*, 0x01A557FC)

/****** Matrix Stack Limits *********************************************************/
#define _nj_min_matrix_             DATA_REF(NJS_MATRIX*, 0x0267053C)
#define _nj_max_matrix_             DATA_REF(NJS_MATRIX*, 0x02670588)

/****** Unit Matrix *****************************************************************/
#define _nj_unit_matrix_            DATA_REF(const NJS_MATRIX, 0x025F02A0)

/************************/
/*  Prototypes          */
/************************/
/****** Push/Pop Matrix *************************************************************/
/*
*   Description:
*     Push the matrix stack, and set current matrix to 'm'
*
*   Parameters:
*     - m       : matrix to set (optional)
*
*   Returns:
*     'true' on success, or 'false' if the top of the matrix stack is reached
*/
Bool    njPushMatrix( const NJS_MATRIX* m );
/*
*   Description:
*     Pop the matrix stack 'n' times
*
*   Parameters:
*     - n       : number of matrices to pop
*
*   Returns:
*     'true' on success, or 'false' if the bottom of the matrix stack is reached
*/
Bool    njPopMatrix( Uint32 n );

/****** Get/Set Matrix **************************************************************/
/*
*   Description:
*     Copy current matrix into 'm'
*
*   Parameters:
*     - m       : return pointer matrix
*/
void    njGetMatrix( NJS_MATRIX* m );
/*
*   Description:
*     Copy a matrix into 'm'
*
*   Parameters:
*     - md      : destination matrix (optional)
*     - ms      : matrix to set 'md' to
*/
void    njSetMatrix( NJS_MATRIX* md, const NJS_MATRIX* ms );

/****** Add/Sub Matrix **************************************************************/
/*
*   Description:
*     Add a matrix onto another matrix
*
*   Parameters:
*     - md      : destination matrix (optional)
*     - ms      : matrix to add
*/
void    njAddMatrix( NJS_MATRIX* md, const NJS_MATRIX* ms );
/*
*   Description:
*     Subtract a matrix from another matrix
*
*   Parameters:
*     - md      : destination matrix (optional)
*     - ms      : matrix to subtract
*/
void    njSubMatrix( NJS_MATRIX* md, const NJS_MATRIX* ms );

/****** Unit/Identity Matrix ********************************************************/
/*
*   Description:
*     Set a matrix to be a unit matrix
*
*   Parameters:
*     - m       : matrix to set to unit (optional)
*/
void    njUnitMatrix( NJS_MATRIX* m );

/****** Multiply Matrices ***********************************************************/
/*
*   Description:
*     Pre-multiply a matrix with another matrix.
* 
*   Notes:
*     - ( md = md * ms )
*
*   Parameters:
*     - md      : destination matrix (optional)
*     - ms      : matrix to multiply with
*/
void    njMultiMatrix( NJS_MATRIX* md, const NJS_MATRIX* ms );
/*
*   Description:
*     Post-multiply a matrix with another matrix.
* 
*   Notes:
*     - ( md = ms * md )
* 
*   Parameters:
*     - md      : destination matrix (optional)
*     - ms      : matrix to multiply with
*/
void    njPostMultiMatrix( NJS_MATRIX* md, const NJS_MATRIX* ms );

/****** Translate Matrix ************************************************************/
/*
*   Description:
*     Transform a matrix by a point or vector in 3D space
*
*   Parameters:
*     - m       : matrix (optional)
*     - x       : x part of point/vector
*     - y       : y part of point/vector
*     - z       : z part of point/vector
*/
void    njTranslate( NJS_MATRIX* m, Float x, Float y, Float z );
/*
*   Description:
*     Transform a matrix by a point or vector in 3D space using NJS_VECTOR
*
*   Parameters:
*     - m       : matrix (optional)
*     - v       : point/vector
*/
void    njTranslateV( NJS_MATRIX* m, const NJS_VECTOR* v );

/****** Rotate Matrix ***************************************************************/
/*
*   Description:
*     Rotate a matrix by an Angle
*
*   Parameters:
*     - m       : matrix (optional)
*     - ang     : angle to rotate
*/
void    njRotateX( NJS_MATRIX* m, Angle ang );
void    njRotateY( NJS_MATRIX* m, Angle ang );
void    njRotateZ( NJS_MATRIX* m, Angle ang );
/*
*   Description:
*     Rotate a matrix by a euler angle in either XYZ or ZXY order
*
*   Parameters:
*     - m       : matrix (optional)
*     - angx    : x part angle
*     - angy    : y part angle
*     - angz    : z part angle
*/
void    njRotateXYZ( NJS_MATRIX* m, Angle angx, Angle angy, Angle angz );
void    njRotateZXY( NJS_MATRIX* m, Angle angx, Angle angy, Angle angz );
/*
*   Description:
*     Rotate a matrix by an Angle on an axis defined by a vector
*
*   Parameters:
*     - m       : matrix (optional)
*     - v       : vector axis
*     - ang     : angle to rotate
*/
void    njRotate( NJS_MATRIX* m, const NJS_VECTOR* v, Angle ang );

/****** Scale Matrix ****************************************************************/
/*
*   Description:
*     Scale a matrix in 3D space
*
*   Parameters:
*     - m       : matrix (optional)
*     - sx      : x part of scale
*     - sy      : y part of scale
*     - sz      : z part of scale
*/
void    njScale( NJS_MATRIX* m, Float sx, Float sy, Float sz );
/*
*   Description:
*     Scale a matrix in 3D space using a vector
*
*   Parameters:
*     - m       : matrix (optional)
*     - v       : vector scale
*/
void    njScaleV( NJS_MATRIX* m, const NJS_VECTOR* v );

/****** Invert Matrix ***************************************************************/
/*
*   Description:
*    Invert a matrix
*
*   Parameters:
*     - m       : matrix to invert (optional)
* 
*   Returns:
*     Always 'true'
*/
Bool    njInvertMatrix( NJS_MATRIX* m );

/****** Transpose Matrix ************************************************************/
/*
*   Description:
*    Transpose a matrix
*
*   Parameters:
*     - m       : matrix to transpose (optional)
*/
void    njTransposeMatrix( NJS_MATRIX* m );

/****** Portion Matrix **************************************************************/
/*
*   Description:
*     Get translation portion of a matrix
*
*   Parameters:
*     - m       : matrix to get translation of
*     - p       : return pointer of translation
*/
void    njGetTranslation( const NJS_MATRIX* m, NJS_POINT3* p );
/*
*   Description:
*     Set translation portion of a matrix to unit
*
*   Parameters:
*     - m       : matrix to set translation portion of
*/
void    njUnitTransPortion( NJS_MATRIX* m );
/*
*   Description:
*     Set rotation portion of a matrix to unit (or essentially, non-translation
*   portion to unit)
*
*   Parameters:
*     - m       : matrix to set rotation portion of
*/
void    njUnitRotPortion( NJS_MATRIX* m );

/****** Calculate Matrix ************************************************************/
/*
*   Description:
*     Transform a point by a matrix
*
*   Parameters:
*     - m       : matrix (optional)
*     - ps      : point to transform
*     - pd      : destination point
*/
void    njCalcPoint( const NJS_MATRIX* m, const NJS_POINT3* ps, NJS_POINT3* pd );
/*
*   Description:
*     Transform a vector by a matrix
*
*   Parameters:
*     - m       : matrix (optional)
*     - ps      : vector to transform 
*     - pd      : destination vector 
*/
void    njCalcVector( const NJS_MATRIX* m, const NJS_VECTOR* vs, NJS_VECTOR* vd );
/*
*   Description:
*     Transform a set of points by a matrix
*
*   Parameters:
*     - m       : matrix (optional)
*     - ps      : points to transform 
*     - pd      : destination points
*     - num     : number of points
*/
void    njCalcPoints( const NJS_MATRIX* m, const NJS_POINT3* ps, NJS_POINT3* pd, Int num );
/*
*   Description:
*     Transform a set of vectors by a matrix
*
*   Parameters:
*     - m       : matrix (optional)
*     - ps      : vectors to transform 
*     - pd      : destination vectors
*     - num     : number of vectors
*/
void    njCalcVectors( const NJS_MATRIX* m, const NJS_VECTOR* vs, NJS_VECTOR* vd, Int num );

/****** Add/Sub Vector **************************************************************/
/*
*   Description:
*     Add a vector onto another vector
*
*   Parameters:
*     - vd      : destination vector
*     - vs      : vector to add
*/
void    njAddVector(NJS_VECTOR* vd, const NJS_VECTOR* vs);
/*
*   Description:
*     Subtract a vector from another vector
*
*   Parameters:
*     - vd      : destination vector
*     - vs      : vector to subtract
*/
void    njSubVector(NJS_VECTOR* vd, const NJS_VECTOR* vs);

/****** Unit Vector *****************************************************************/
/*
*   Description:
*     Set a vector to be a unit vector. In other words, normalize a vectors length
*   to between '0' and '1'
*
*   Parameters:
*     - v       : vector to normalize
*
*   Returns:
*     Length of vector before unit calculation
*/
Float   njUnitVector( NJS_VECTOR* v );

/****** Scalor Vector *****************************************************************/
/*
*   Description:
*     Calculate the length of a vector
*
*   Parameters:
*     - v       : vector
*
*   Returns:
*     Length of vector
*/
Float   njScalor( const NJS_VECTOR* v );
/*
*   Description:
*     Calculate the length of a vector without calling 'njSqrt'. Faster if only
*   relative length is important.
*
*   Parameters:
*     - v       : vector
*
*   Returns:
*     Length of vector before 'njSqrt'
*/
Float   njScalor2( const NJS_VECTOR* v );

/****** Vector Product **************************************************************/
/*
*   Description:
*     Calculate the dot/inner product of two vectors
*
*   Parameters:
*     - v1      : vector 1
*     - v2      : vector 2
*
*   Returns:
*     Dot/inner product of 'v1' and 'v2'
*/
Float   njInnerProduct( const NJS_VECTOR* v1, const NJS_VECTOR* v2 );
/*
*   Description:
*     Calculate the cross/outer product of two vectors
*
*   Parameters:
*     - v1      : vector 1
*     - v2      : vector 2
*     - ov      : destination cross/outer product
*
*   Returns:
*     Length of cross/outer product
*/
Float   njOuterProduct( const NJS_VECTOR* v1, const NJS_VECTOR* v2, NJS_VECTOR* ov );
/*
*   Description:
*     Calculate the cross/outer product of two vectors without calling 'njSqrt' for
*   the length value. Faster if only relative length is important, or you don't plan
*   to use the length value.
*
*   Parameters:
*     - v1      : vector 1
*     - v2      : vector 2
*     - ov      : destination cross/outer product
*
*   Returns:
*     Length of cross/outer product before 'njSqrt'
*/
Float   njOuterProduct2( const NJS_VECTOR* v1, const NJS_VECTOR* v2, NJS_VECTOR* ov );

/****** Project Screen **************************************************************/
/*
*   Description:
*     Calculate the projected 2D screen coordinates of an arbitrary 3D point with a
*   matrix. The calculated values are in hardware screen coordinates, and not
*   NJS_SCREEN local coordinates. This function is equivalent to:
*   {
*     NJS_POINT3 cm;
* 
*     njCalcPoint(m, p3, &cm);
*     njCalcScreen(&cm, &p2->x, &p2->y);
*   }
*
*   Notes:
*     - 'm' parameter is unused and always 'NULL'
*
*   Parameters:
*     - m       : matrix (optional)
*     - p3      : 3D point to project
*     - p2      : destination 2D coordinates
*/
void    njProjectScreen( const NJS_MATRIX* m, const NJS_POINT3* p3, NJS_POINT2* p2 );

/****** Angle to Quaternion *********************************************************/
/*
*   Description:
*     Convert a euler angle in XYZ or ZXY order to a quaternion angle.
*
*   Parameters:
*     - ang     : euler angle
*     - qua     : destination quaternion
*/
void    njXYZAngleToQuaternion( const Angle ang[3], NJS_QUATERNION* qua );
void    njZXYAngleToQuaternion( const Angle ang[3], NJS_QUATERNION* qua );

/****** Interpolate Quaternion *********************************************************/
/*
*   Description:
*     Interpolate two quaternions at a given ratio.
*
*   Parameters:
*     - qua0    : quaternion 1
*     - qua1    : quaternion 2
*     - rate    : ratio of quat 2, quat 1 will use (1 - 'rate') (0~1)
*     - qua     : result quaternion
*/
void    njInterpolateQuaternion( const NJS_QUATERNION *qua0, const NJS_QUATERNION *qua1, Float rate, NJS_QUATERNION *qua );

/****** Push/Pop Matrix Ex **********************************************************/
/*
*   Description:
*     Push current matrix onto the matrix stack
*
*   Returns:
*     'true' on success, or 'false' if the top of the matrix stack is reached
*/
Bool    njPushMatrixEx( void );
/*
*   Description:
*     Pop matrix stack once
*
*   Returns:
*     'true' on success, or 'false' if the bottom of the matrix stack is reached
*/
Bool    njPopMatrixEx( void );

/****** Unit/Identity Matrix Ex *****************************************************/
/*
*   Description:
*     Set the current matrix to be a unit matrix
*/
void    njUnitMatrixEx( void );

/****** Transform Matrix Ex *********************************************************/
/*
*   Description:
*     Transform the current matrix by a point or vector in 3D space
*
*   Parameters:
*     - v       : point/vector
*/
void    njTranslateEx( const NJS_VECTOR* v );
/*
*   Description:
*     Rotate the current matrix by a euler Angle in XYZ or ZXY order
* 
*   Parameters:
*     - ang     : list of 3 angles
*     - lv      : use light wave rotation order (ZXY)
*/
void    njRotateEx( const Angle* ang, Sint32 lv );
/*
*   Description:
*     Scale the current matrix in 3D space using a vector
*
*   Parameters:
*     - v       : vector
*/
void    njScaleEx( const NJS_VECTOR* v );
/*
*   Description:
*     Rotate the current matrix using a quaternion
* 
*   Parameters:
*     - qua     : quaternion
*/
void    njQuaternionEx( const NJS_QUATERNION* qua );
/*
*   Description:
*     Rotate the current matrix using a quaternion
* 
*   Parameters:
*     - re      : real part of quaternion
*     - im      : imaginary part of quaternion
*/
void    njQuaternionEx2( Float re, const Float im[3] );

/****** Calculate Matrix Ex *********************************************************/
/*
*   Description:
*     Transform a point by the current matrix
*
*   Parameters:
*     - ps      : point to transform
*     - pd      : destination point
*/
void    njCalcPointEx( const NJS_POINT3* ps, NJS_POINT3* pd );
/*
*   Description:
*     Transform a vector by the current matrix
*
*   Parameters:
*     - ps      : vector to transform
*     - pd      : destination vector 
*/
void    njCalcVectorEx( const NJS_VECTOR* vs, NJS_VECTOR* vd );

/****** Convert Matrix (SAMT) *******************************************************/
/*
*   Description:
*     Get a 4x4 matrix from a 3x4 matrix
*
*   Parameters:
*     - md      : destination matrix
*     - ms      : source matrix
*/
void    njGetMatrix44(NJS_MATRIX44* md, const NJS_MATRIX* ms);
/*
*   Description:
*     Get a 3x4 matrix from a 4x4 matrix
*
*   Parameters:
*     - md      : destination matrix
*     - ms      : source matrix
*/
void    njGetMatrix34(NJS_MATRIX* md, const NJS_MATRIX44* ms);

EXTERN_END

#endif/*H_NJ_MATRIX*/
