/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/ninja/njmatrix.h'
*
*   Description:
*     Ninja matrix header.
*
*   Notes:
*     - Where the matrix parameter of a function is noted as (optional), a 'NULL' value will
*       use the current matrix instead of an arbitrary matrix.
*     - Noted rotation orders are reversed from their order in code. For example: XYZ order,
*       in code, will call 'njRotate#' in 'ZYX' order.
*     - Not all functions are strictly from Ninja2, some are extensions in SAMT/SA2 - or from
*       older versions of Ninja. These are:
*       - njFastPopPushMatrix               (SAMT/SA2)
*       - njAddMatrix, njSubMatrix          (Ninja1 only)
*       - njTransformA, njScaleA            (SAMT)
*       - njGetRotationXYZ/ZXY              (SAMT)
*       - njOuterProduct2                   (SAMT)
*       - njTranslateEx2, njScaleEx2        (SAMT)
*       - njGetMatrix44, njGetMatrix34      (SAMT)
*/
#ifndef H_NJ_MATRIX
#define H_NJ_MATRIX

/********************************/
/*  Includes                    */
/********************************/
/****** System **********************************************************************************/
#include <samt/shinobi/sg_xpt.h>    /* shinobi types                                            */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Structures                  */
/********************************/
/****** Ninja Matrix ****************************************************************************/
typedef union
{
    Float m[3][4];                  /* matrix in either 4x4 or 3x4 layout                       */
    Float f[12];                    /* matrix as float array                                    */
}
NJS_MATRIX;

/****** Ninja Matrix 4x4 ************************************************************************/
typedef union
{
    Float m[4][4];                  /* matrix in 4x4 layout                                     */
    Float f[16];                    /* matrix as float array                                    */
}
NJS_MATRIX44;

/********************************/
/*  Global Variables            */
/********************************/
/****** Current Matrix **************************************************************************/
#define _nj_curr_matrix_            DATA_REF(NJS_MATRIX*, 0x01A557FC)

/****** Matrix Stack Limits *********************************************************************/
#define _nj_min_matrix_             DATA_REF(NJS_MATRIX*, 0x0267053C)
#define _nj_max_matrix_             DATA_REF(NJS_MATRIX*, 0x02670588)

/****** Unit Matrix *****************************************************************************/
#define _nj_unit_matrix_            DATA_REF(const NJS_MATRIX, 0x025F02A0)

/********************************/
/*  Prototypes                  */
/********************************/
/************************************************************************************************/
/*
*   Core Matrix
*/
/****** Get/Set Matrix **************************************************************************/
/*
*   Description:
*     Copy current matrix into 'm'.
*
*   Parameters:
*     - m           : return pointer matrix
*/
void    njGetMatrix( NJS_MATRIX* m );
/*
*   Description:
*     Copy an arbitrary matrix into 'm'.
*
*   Parameters:
*     - md          : destination matrix                                         [opt: nullptr]
*     - ms          : matrix to set 'md' to
*/
void    njSetMatrix( NJS_MATRIX* md, const NJS_MATRIX* ms );

/****** Push/Pop Matrix *************************************************************************/
/*
*   Description:
*     Push a matrix onto the matrix stack.
*
*   Parameters:
*     - m           : matrix to set                                              [opt: nullptr]
*
*   Returns:
*     'true' on success; or 'false' if the top of the matrix stack is hit.
*/
Bool    njPushMatrix( const NJS_MATRIX* m );
/*
*   Description:
*     Pop a set number of entries off the matrix stack.
*
*   Parameters:
*     - n           : number to pop
*
*   Returns:
*     'true' on success; or 'false' if the bottom of the matrix stack is hit.
*/
Bool    njPopMatrix( Uint32 n );

/****** Fast Matrix *****************************************************************************/
/*
*   Description:
*     Quickly pop and push the matrix stack in one call. This function also skips matrix stack
*   boundary checks. This is functionally equivalent to, and faster than:
*   {
*     njPopMatrixEx();
*     njPushMatrixEx();
*   }
*
*   Returns:
*     Always 'true'.
*/
Bool    njFastPopPushMatrix( void );

/****** Add/Sub Matrix **************************************************************************/
/*
*   Description:
*     Add a matrix onto another matrix.
*
*   Parameters:
*     - md          : destination matrix                                         [opt: nullptr]
*     - ms          : matrix to add
*/
void    njAddMatrix( NJS_MATRIX* md, const NJS_MATRIX* ms );
/*
*   Description:
*     Subtract a matrix from another matrix.
*
*   Parameters:
*     - md          : destination matrix                                         [opt: nullptr]
*     - ms          : matrix to subtract
*/
void    njSubMatrix( NJS_MATRIX* md, const NJS_MATRIX* ms );

/****** Unit/Identity Matrix ********************************************************************/
/*
*   Description:
*     Set a matrix to be a unit matrix
*
*   Parameters:
*     - m           : matrix to set to unit                                      [opt: nullptr]
*/
void    njUnitMatrix( NJS_MATRIX* m );

/****** Multiply Matrices ***********************************************************************/
/*
*   Description:
*     Pre-multiply a matrix with another matrix.
* 
*   Notes:
*     - ( md = md * ms )
*
*   Parameters:
*     - md          : destination matrix                                         [opt: nullptr]
*     - ms          : matrix to multiply with
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
*     - md          : destination matrix                                         [opt: nullptr]
*     - ms          : matrix to multiply with
*/
void    njPostMultiMatrix( NJS_MATRIX* md, const NJS_MATRIX* ms );

/****** Translate Matrix ************************************************************************/
/*
*   Description:
*     Transform a matrix by a point or vector in 3D space.
*
*   Parameters:
*     - m           : matrix                                                     [opt: nullptr]
*     - x,y,z       : point/vector components
*/
void    njTranslate( NJS_MATRIX* m, Float x, Float y, Float z );
/*
*   Description:
*     Transform a matrix by a point or vector in 3D space using a vector.
*
*   Parameters:
*     - m           : matrix                                                     [opt: nullptr]
*     - v           : point/vector
*/
void    njTranslateV( NJS_MATRIX* m, const NJS_VECTOR* v );
/*
*   Description:
*     Transform a matrix by a point or vector in 3D space using a float array.
*
*   Parameters:
*     - m           : matrix                                                     [opt: nullptr]
*     - pos         : point/vector as array
*/
void    njTranslateA( NJS_MATRIX* m, const Float pos[3] );

/****** Rotate Matrix ***************************************************************************/
/*
*   Description:
*     Rotate a matrix by an Angle
*
*   Parameters:
*     - m           : matrix                                                     [opt: nullptr]
*     - ang         : angle to rotate
*/
void    njRotateX( NJS_MATRIX* m, Angle ang );
void    njRotateY( NJS_MATRIX* m, Angle ang );
void    njRotateZ( NJS_MATRIX* m, Angle ang );
/*
*   Description:
*     Rotate a matrix by a euler angle in either XYZ or ZXY order
*
*   Parameters:
*     - m           : matrix                                                     [opt: nullptr]
*     - angx        : x part angle
*     - angy        : y part angle
*     - angz        : z part angle
*/
void    njRotateXYZ( NJS_MATRIX* m, Angle angx, Angle angy, Angle angz );
void    njRotateZXY( NJS_MATRIX* m, Angle angx, Angle angy, Angle angz );
/*
*   Description:
*     Rotate a matrix by an Angle on an axis defined by a vector
*
*   Parameters:
*     - m           : matrix                                                     [opt: nullptr]
*     - v           : vector axis
*     - ang         : angle to rotate
*/
void    njRotate( NJS_MATRIX* m, const NJS_VECTOR* v, Angle ang );

/****** Scale Matrix ****************************************************************************/
/*
*   Description:
*     Scale a matrix in 3D space
*
*   Parameters:
*     - m           : matrix                                                     [opt: nullptr]
*     - sx          : x part of scale
*     - sy          : y part of scale
*     - sz          : z part of scale
*/
void    njScale( NJS_MATRIX* m, Float sx, Float sy, Float sz );
/*
*   Description:
*     Scale a matrix in 3D space using a vector
*
*   Parameters:
*     - m           : matrix                                                     [opt: nullptr]
*     - v           : vector scale
*/
void    njScaleV( NJS_MATRIX* m, const NJS_VECTOR* v );
/*
*   Description:
*     Scale a matrix in 3D space using a float array
*
*   Parameters:
*     - m           : matrix                                                     [opt: nullptr]
*     - scl         : float array
*/
void    njScaleA( NJS_MATRIX* m, const Float scl[3] );

/****** Invert Matrix ***************************************************************************/
/*
*   Description:
*    Invert a matrix
*
*   Parameters:
*     - m           : matrix to invert                                           [opt: nullptr]
* 
*   Returns:
*     Always 'true'
*/
Bool    njInvertMatrix( NJS_MATRIX* m );

/****** Transpose Matrix ************************************************************************/
/*
*   Description:
*    Transpose a matrix
*
*   Parameters:
*     - m           : matrix to transpose                                        [opt: nullptr]
*/
void    njTransposeMatrix( NJS_MATRIX* m );

/****** Get Portion *****************************************************************************/
/*
*   Description:
*     Get translation portion of a matrix
*
*   Parameters:
*     - m           : matrix to get translation of                               [opt: nullptr]
*     - p           : destination translation
*/
void    njGetTranslation( const NJS_MATRIX* m, NJS_POINT3* p );
/*
*   Description:
*     Get rotation portion of a matrix, in XYZ order.
*
*   Parameters:
*     - m           : matrix to get translation of                               [opt: nullptr]
*     - a           : destination angle set
*/
void    njGetRotationXYZ( const NJS_MATRIX* m, NJS_ANGLE3* a );
/*
*   Description:
*     Get rotation portion of a matrix, in light wave order.
*
*   Parameters:
*     - m           : matrix to get translation of                               [opt: nullptr]
*     - a           : destination angle set
*/
void    njGetRotationZXY( const NJS_MATRIX* m, NJS_ANGLE3* a );

/****** Unit Portion ****************************************************************************/
/*
*   Description:
*     Set translation portion of a matrix to unit
*
*   Parameters:
*     - m           : matrix to set translation portion of                       [opt: nullptr]
*/
void    njUnitTransPortion( NJS_MATRIX* m );
/*
*   Description:
*     Set rotation portion of a matrix to unit (or essentially, non-translation
*   portion to unit)
*
*   Parameters:
*     - m           : matrix to set rotation portion of                          [opt: nullptr]
*/
void    njUnitRotPortion( NJS_MATRIX* m );

/****** Calculate Matrix ************************************************************************/
/*
*   Description:
*     Transform a point by a matrix
*
*   Parameters:
*     - m           : matrix                                                     [opt: nullptr]
*     - ps          : point to transform
*     - pd          : destination point
*/
void    njCalcPoint( const NJS_MATRIX* m, const NJS_POINT3* ps, NJS_POINT3* pd );
/*
*   Description:
*     Transform a vector by a matrix
*
*   Parameters:
*     - m           : matrix                                                     [opt: nullptr]
*     - ps          : source vector to transform 
*     - pd          : destination vector 
*/
void    njCalcVector( const NJS_MATRIX* m, const NJS_VECTOR* vs, NJS_VECTOR* vd );
/*
*   Description:
*     Transform a set of points by a matrix
*
*   Parameters:
*     - m           : matrix                                                     [opt: nullptr]
*     - ps          : source points to transform 
*     - pd          : destination points
*     - num         : number of points
*/
void    njCalcPoints( const NJS_MATRIX* m, const NJS_POINT3* ps, NJS_POINT3* pd, Int num );
/*
*   Description:
*     Transform a set of vectors by a matrix
*
*   Parameters:
*     - m           : matrix                                                     [opt: nullptr]
*     - ps          : source vectors to transform 
*     - pd          : destination vectors
*     - num         : number of vectors
*/
void    njCalcVectors( const NJS_MATRIX* m, const NJS_VECTOR* vs, NJS_VECTOR* vd, Int num );

/************************************************************************************************/
/*
*   Other Math
*/
/****** Add/Sub Vector **************************************************************************/
/*
*   Description:
*     Add a vector onto another vector
*
*   Parameters:
*     - vd          : destination vector
*     - vs          : vector to add
*/
void    njAddVector(NJS_VECTOR* vd, const NJS_VECTOR* vs);
/*
*   Description:
*     Subtract a vector from another vector
*
*   Parameters:
*     - vd          : destination vector
*     - vs          : vector to subtract
*/
void    njSubVector(NJS_VECTOR* vd, const NJS_VECTOR* vs);

/****** Unit Vector *****************************************************************************/
/*
*   Description:
*     Set a vector to be a unit vector. In other words, normalize a vectors length
*   to between '0' and '1'
*
*   Parameters:
*     - v           : vector to normalize
*
*   Returns:
*     Length of vector before unit calculation
*/
Float   njUnitVector( NJS_VECTOR* v );

/****** Scalor Vector ***************************************************************************/
/*
*   Description:
*     Calculate the length of a vector
*
*   Parameters:
*     - v           : vector
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
*     - v           : vector
*
*   Returns:
*     Length of vector before 'njSqrt'
*/
Float   njScalor2( const NJS_VECTOR* v );

/****** Vector Product **************************************************************************/
/*
*   Description:
*     Calculate the dot/inner product of two vectors
*
*   Parameters:
*     - v1,v2       : source vectors
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
*     - v1,v2       : source vectors
*     - ov          : destination cross/outer product
*
*   Returns:
*     Length of cross/outer product
*/
Float   njOuterProduct( const NJS_VECTOR* v1, const NJS_VECTOR* v2, NJS_VECTOR* ov );
/*
*   Description:
*     Calculate the cross/outer product of two vectors without calling 'njSqrt' for the length
*   value. Faster if only relative length is important, or you don't plan to use the length
*   value.
*
*   Parameters:
*     - v1,v2       : source vectors
*     - ov          : destination cross/outer product
*
*   Returns:
*     Length of cross/outer product before 'njSqrt'
*/
Float   njOuterProduct2( const NJS_VECTOR* v1, const NJS_VECTOR* v2, NJS_VECTOR* ov );

/****** Project Screen **************************************************************************/
/*
*   Description:
*     Calculate the projected 2D screen coordinates of an arbitrary 3D point with a matrix. The
*   calculated values are in hardware screen coordinates, and not local screen coordinates.
*   This is functionally equivalent to:
*   {
*     NJS_POINT3 cm;
*   
*     njCalcPoint( m, p3, &cm );
*     njCalcScreen( &cm, &p2->x, &p2->y );
*   }
*
*   Notes:
*     - 'm' parameter is unused and always 'NULL'
*
*   Parameters:
*     - m           : matrix                                                     [opt: nullptr]
*     - p3          : 3D point to project
*     - p2          : destination 2D coordinates
*/
void    njProjectScreen( const NJS_MATRIX* m, const NJS_POINT3* p3, NJS_POINT2* p2 );

/************************************************************************************************/
/*
*   Quaternion
*/
/****** Angle to Quaternion *********************************************************************/
/*
*   Description:
*     Convert a euler angle in XYZ or ZXY order to a quaternion angle.
*
*   Parameters:
*     - ang         : euler angle
*     - qua         : destination quaternion
*/
void    njXYZAngleToQuaternion( const Angle ang[3], NJS_QUATERNION* qua );
void    njZXYAngleToQuaternion( const Angle ang[3], NJS_QUATERNION* qua );

/****** Interpolate Quaternion ******************************************************************/
/*
*   Description:
*     Interpolate two quaternions at a given ratio.
*
*   Parameters:
*     - qua0        : quaternion 1
*     - qua1        : quaternion 2
*     - rate        : ratio of quat 2, quat 1 will use (1 - 'rate')                       [0~1]
*     - qua         : result quaternion
*/
void    njInterpolateQuaternion( const NJS_QUATERNION *qua0, const NJS_QUATERNION *qua1, Float rate, NJS_QUATERNION *qua );

/************************************************************************************************/
/*
*   Matrix Ex
*/
/****** Push/Pop Matrix Ex **********************************************************************/
/*
*   Description:
*     Push core matrix stack once with current matrix.
*
*   Returns:
*     'true' on success, or 'false' if the top of the matrix stack is reached
*/
Bool    njPushMatrixEx( void );
/*
*   Description:
*     Pop core matrix stack once.
*
*   Returns:
*     'true' on success, or 'false' if the bottom of the matrix stack is reached
*/
Bool    njPopMatrixEx( void );

/****** Unit/Identity Matrix Ex *****************************************************************/
/*
*   Description:
*     Set the current matrix to be a unit matrix
*/
void    njUnitMatrixEx( void );

/****** Transform Matrix Ex *********************************************************************/
/*
*   Description:
*     Transform the current matrix by a point or vector in 3D space using a vector.
*
*   Parameters:
*     - v           : point/vector
*/
void    njTranslateEx( const NJS_VECTOR* v );
/*
*   Description:
*     Transform the current matrix by a point or vector in 3D space using a float array.
* 
*   Parameters:
*     - pos         : float array
*/
void    njTranslateEx2( const Float pos[3] );
/*
*   Description:
*     Rotate the current matrix by a euler Angle in XYZ or ZXY order.
* 
*   Parameters:
*     - ang         : list of 3 angles
*     - lv          : use light wave rotation order (ZXY)
*/
void    njRotateEx( const Angle* ang, Sint32 lv );
/*
*   Description:
*     Scale the current matrix in 3D space using a vector.
*
*   Parameters:
*     - v           : vector
*/
void    njScaleEx( const NJS_VECTOR* v );
/*
*   Description:
*     Scale the current matrix in 3D space using a float array.
* 
*   Parameters:
*     - scl         : 3 float array
*/
void    njScaleEx2( const Float scl[3] );
/*
*   Description:
*     Rotate the current matrix using a quaternion.
* 
*   Parameters:
*     - qua         : quaternion
*/
void    njQuaternionEx( const NJS_QUATERNION* qua );
/*
*   Description:
*     Rotate the current matrix using a quaternion.
* 
*   Parameters:
*     - re          : real part of quaternion
*     - im          : imaginary part of quaternion
*/
void    njQuaternionEx2( Float re, const Float im[3] );

/****** Calculate Matrix Ex *********************************************************************/
/*
*   Description:
*     Transform a point by the current matrix.
*
*   Parameters:
*     - ps          : point to transform
*     - pd          : destination point
*/
void    njCalcPointEx( const NJS_POINT3* ps, NJS_POINT3* pd );
/*
*   Description:
*     Transform a vector by the current matrix.
*
*   Parameters:
*     - ps          : vector to transform
*     - pd          : destination vector 
*/
void    njCalcVectorEx( const NJS_VECTOR* vs, NJS_VECTOR* vd );

/************************************************************************************************/
/*
*   Convert Matrix (SAMT)
*/
/****** Mtx -> 44 *******************************************************************************/
/*
*   Description:
*     Get a 4x4 matrix from a 3x4 matrix.
*
*   Parameters:
*     - md          : destination matrix
*     - ms          : source matrix
*/
void    njGetMatrix44(NJS_MATRIX44* md, const NJS_MATRIX* ms);

/****** 44 -> Mtx *******************************************************************************/
/*
*   Description:
*     Get a 3x4 matrix from a 4x4 matrix.
*
*   Parameters:
*     - md          : destination matrix
*     - ms          : source matrix
*/
void    njGetMatrix34(NJS_MATRIX* md, const NJS_MATRIX44* ms);

EXTERN_END

#endif/*H_NJ_MATRIX*/
