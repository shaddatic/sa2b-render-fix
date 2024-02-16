/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njmatrix.h'
*
*   Contains Ninja matrix enums, values, and functions
*
*   Contributors:
*   -   SEGA,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef    _NJ_MATRIX_H_
#define    _NJ_MATRIX_H_

/*--------------------------------------*/
/*      Matrix                          */
/*--------------------------------------*/
typedef Float* NJS_MATRIX_PTR;

enum {
    M00, M10, M20, M30,
    M01, M11, M21, M31,
    M02, M12, M22, M32
};

/*******************************/
/* Global Variables for Matrix */
/*******************************/
#define _nj_unit_matrix_            DataRef(GJS_MATRIX, 0x025F02A0)

/*
    Prototype Declarations
*/

/*  Push and pop current matrix into a matrix stack */
Bool    njPushMatrix(NJS_MATRIX* m);
Bool    njPopMatrix(Uint32 n);

/*  Retrieve a current matrix or copy a matrix to another.  */
void    njGetMatrix(NJS_MATRIX* m);
void    njSetMatrix(NJS_MATRIX* md, NJS_MATRIX* ms);

/*  Add or subtract two specified matrices  */
void    njAddMatrix(NJS_MATRIX* md, NJS_MATRIX* ms);
void    njSubMatrix(NJS_MATRIX* md, NJS_MATRIX* ms);

/*  Make a specified matrix be unit     */
void    njUnitMatrix(NJS_MATRIX* m);

/*  Multiply two specified matrices */
void    njMultiMatrix(NJS_MATRIX* md, const NJS_MATRIX* ms);
void    njPostMultiMatrix(NJS_MATRIX* md, const NJS_MATRIX* ms);


/*
    Make and multiply matrix mainly for an object node.
*/
/*  Translation */
void    njTranslate(NJS_MATRIX* m, Float x, Float y, Float z);
void    njTranslateV(NJS_MATRIX* m, NJS_VECTOR* v);
/*  Rotation    */
void    njRotateX(NJS_MATRIX* m, Angle ang);
void    njRotateY(NJS_MATRIX* m, Angle ang);
void    njRotateZ(NJS_MATRIX* m, Angle ang);
void    njRotateXYZ(NJS_MATRIX* m, Angle angx, Angle angy, Angle angz);
void    njRotateZXY(NJS_MATRIX* m, Angle angx, Angle angy, Angle angz);
void    njRotate(NJS_MATRIX* m, NJS_VECTOR* v, Angle ang);
/*  Scaling */
void    njScale(NJS_MATRIX* m, Float sx, Float sy, Float sz);
void    njScaleV(NJS_MATRIX* m, NJS_VECTOR* v);


/*  Make an invert or transpose matrix  */
Bool    njInvertMatrix(NJS_MATRIX* m);
void    njTransposeMatrix(NJS_MATRIX* m);   // MIA

/*  Get some part of a sepcified matrix     */
void    njGetTranslation(NJS_MATRIX* m, NJS_POINT3* p);
void    njUnitTransPortion(NJS_MATRIX* m);
void    njUnitRotPortion(NJS_MATRIX* m);

/*  Calculate the determinant of a specified matrix */
Float    njDetMatrix(NJS_MATRIX* m);         // MIA


/*
    Transform the notation of specified vector(s) or point(s) by a specified matrix.
    In other words, multiply a specified matrix and specified vector(s) or point(s).
*/
void    njCalcPoint(NJS_MATRIX* m, NJS_POINT3* ps, NJS_POINT3* pd);
void    njCalcVector(NJS_MATRIX* m, NJS_VECTOR* vs, NJS_VECTOR* vd);
void    njCalcPoints(NJS_MATRIX* m, NJS_POINT3* ps, NJS_POINT3* pd, Int num);
void    njCalcVectors(NJS_MATRIX* m, NJS_VECTOR* vs, NJS_VECTOR* vd, Int num);

/*  Add or subtract vector    */
void    njAddVector(NJS_VECTOR* vd, NJS_VECTOR* vs);
void    njSubVector(NJS_VECTOR* vd, NJS_VECTOR* vs);

/*  Make the length of a specified vector to be unit    */
Float    njUnitVector(NJS_VECTOR* v);

/*  Calculate the length of a specified vector  */
Float    njScalor(NJS_VECTOR* v);
Float    njScalor2(NJS_VECTOR* v);

/*  Calculate the inner product or outer product of specified vectors   */
Float    njInnerProduct(NJS_VECTOR* v1, NJS_VECTOR* v2);
Float    njOuterProduct(NJS_VECTOR* v1, NJS_VECTOR* v2, NJS_VECTOR* ov);

/*  Make the mirror matrix of a specified plane     */
void    njMirror(NJS_MATRIX* m, NJS_PLANE* pl);         // MIA

/*  Make the projection matrix of a specified plane     */
void    njProject(NJS_MATRIX* m, NJS_PLANE* pl);                                // MIA
void    njProject2(NJS_MATRIX* m, NJS_PLANE* pl, NJS_POINT3* v, NJS_POINT3* p); // MIA


/*
    Transform a specified point with a specified matrix and calculate the projected 2D point.
    This function is equivalnt to the following :
    NJS_POINT3            cm;
    njCalcPoint( m, p3, &cm );
    njCalcScreen( &cm, p2->x, p2->y );
*/
void    njProjectScreen(NJS_MATRIX* m, NJS_POINT3* p3, NJS_POINT2* p2);


/*  Make a quaternion notation correspond to a specified euler notation */
void    njXYZAngleToQuaternion(const Angle ang[3], NJS_QUATERNION* qua);
void    njZXYAngleToQuaternion(const Angle ang[3], NJS_QUATERNION* qua);

/*  Make a quaternion notation correspond to the rotation around any specified axis */
void    njCreateQuaternion(Float nx, Float ny, Float nz, Angle ang, NJS_QUATERNION* qua);
void    njCreateQuaternionV(const NJS_VECTOR* pAxis, Angle ang, NJS_QUATERNION* qua);

/*  Calculate the interpolated quaternion between two specified quaternions at a specified rate*/
void    njInterpolateQuaternion(const NJS_QUATERNION* qua0, const NJS_QUATERNION* qua1, Float rate, NJS_QUATERNION* qua);

/*  Multiply two quaternions    */
void    njMultiQuaternion(const NJS_QUATERNION* q1, const NJS_QUATERNION* q2, NJS_QUATERNION* dq);

/************************/
/*  Matrix Ex Function  */
/************************/

/*  Push and pop current matrix into a matrix stack */
Bool    njPushMatrixEx(void);
Bool    njPopMatrixEx(void);

/*  Make and multiply matrix mainly for an object node. */
void    njTranslateEx(NJS_VECTOR* v);
void    njRotateEx(Angle* ang, Sint32 lv);
void    njScaleEx(NJS_VECTOR* v);
void    njQuaternionEx(NJS_QUATERNION* qua);
void    njQuaternionEx2(Float re, Float im[3]);

/*
    Transform the notation of a specified vectoror point by a current matrix.
    In other words, multiply a current matrix and a specified vector or point.
*/
void    njCalcPointEx(NJS_POINT3* ps, NJS_POINT3* pd);
void    njCalcVectorEx(NJS_VECTOR* vs, NJS_VECTOR* vd);

/****************************/
/*  Matrix Old Function     */
/****************************/

void    njAddMatrix(NJS_MATRIX* md, NJS_MATRIX* ms);
void    njSubMatrix(NJS_MATRIX* md, NJS_MATRIX* ms);

void    njClearMatrix();

#endif    /* _NJ_MATRIX_H_ */
