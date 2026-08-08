/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/ninja/njmath.h'
*
*   Description:
*     Ninja math, including random functions.
*/
#ifndef H_NJ_MATH
#define H_NJ_MATH

EXTERN_START

/********************************/
/*  Includes                    */
/********************************/
/****** System **********************************************************************************/
#include <samt/shinobi/sg_xpt.h>

/****** Std *************************************************************************************/
#include <math.h>

/********************************/
/*  Constants                   */
/********************************/
/****** Spline Integer Data *********************************************************************/
enum
{
    IP00, IP01, IP02,
    IP10, IP11, IP12,
    IP20, IP21, IP22,
    IP30, IP31, IP32
};

/********************************/
/*  Structures                  */
/********************************/
/****** Spline **********************************************************************************/
typedef struct njspline
{
    int        keys;                /* keyframes between two points which must be interpolated  */
    int     *iparam;                /* attribute data (integer)                                 */
    float   *fparam;                /* attribute data (float)                                   */
}
NJS_SPLINE;

/********************************/
/*  Function Macros             */
/********************************/
/****** Absolute ********************************************************************************/
#define njAbs(n)         ((Float)fabsf   ((Float)(n)))

/****** Rounding ********************************************************************************/
#define njCeil(n)        ((Float)ceilf   ((Float)(n)))
#define njFloor(n)       ((Float)floorf  ((Float)(n)))

/****** Arc *************************************************************************************/
#define njArcCos(n)      ((Angle)NJM_RAD_ANG(acosf  ((Float)(n)) ))
#define njArcCosec(n)    ((Angle)NJM_RAD_ANG(asinf  (1.0f/(Float)(n)) ))
#define njArcCot(n)      ((Angle)NJM_RAD_ANG(atanf  (1.0f/(Float)(n)) ))
#define njArcSec(n)      ((Angle)NJM_RAD_ANG(acosf  (1.0f/(Float)(n)) ))
#define njArcSin(n)      ((Angle)NJM_RAD_ANG(asinf  ((Float)(n)) ))
#define njArcTan(n)      ((Angle)NJM_RAD_ANG(atanf  ((Float)(n)) ))
#define njArcTan2(y,x)   ((Angle)NJM_RAD_ANG(atan2f ((Float)(y),(Float)(x)) ))

/****** Math ************************************************************************************/
#define njCosech(n)      ((Float)( 1.0f / sinhf((Float)NJM_ANG_RAD(n)) ))
#define njCosh(n)        ((Float)coshf   ((Float)NJM_ANG_RAD(n)))
#define njCoth(n)        ((Float)( 1.0f / tanhf((Float)NJM_ANG_RAD(n)) ))
#define njExp(x)         ((Float)expf((x)))
#define njHypot(x,y)     ((Float)sqrtf  ( (x)*(x) + (y)*(y) ))
#define njLog(n)         ((Float)logf    ((Float)(n)))
#define njLog10(n)       ((Float)log10f  ((Float)(n)))
#define njLog2(n)        ((Float)( njLog((n)) / njLog(2.f) ))
#define njPow(n1,n2)     ((Float)powf    ((Float)(n1),(Float)(n2)))
#define njSech(n)        ((Float)( 1.0 / coshf((Float)NJM_ANG_RAD(n)) ))
#define njSinh(n)        ((Float)sinhf   ((Float)NJM_ANG_RAD(n)))
#define njTanh(n)        ((Float)tanhf   ((Float)NJM_ANG_RAD(n)))

/********************************/
/*  Prototypes                  */
/********************************/
/****** Random **********************************************************************************/
/*
*   Description:
*     Get a random value between '0.f' and just below '1.f'.
*/
Float   njRandom( void );
/*
*   Description:
*     Set random seed.
*
*   Parameters:
*     - n           : seed
*/
void    njRandomSeed( Uint32 n );

/****** Round ***********************************************************************************/
/*
*   Description:
*     Round down to the lower absolute, whole value; in other words round toward '0.f'.
*
*   Parameters:
*     - n           : value to round
*
*   Returns:
*     Given value rounded down.
*/
Float   njRoundOff( Float n );
/*
*   Description:
*     Round up to the higher absolute, whole value; in other words round away '0.f'.
*
*   Parameters:
*     - n           : value to round
*
*   Returns:
*     Given value rounded up.
*/
Float   njRoundUp( Float n );

/****** Math ************************************************************************************/
Float   njCos( Angle n );
Float   njCosec( Angle n );
Float   njCot( Angle n );
Float   njFraction( Float n );
Float   njInvertSqrt( Float n );
Float   njSec( Angle n );
Float   njSin( Angle n );
Float   njSqrt( Float n );
Float   njTan( Angle n );

/****** Other ***********************************************************************************/
Sint32  njCombination( Sint32 n, Sint32 k );
void    njLinear(Float* idata, Float* odata, NJS_SPLINE* attr, Float frame);
void    njHermiteSpline(Float* idata, Float* odata, NJS_SPLINE* attr, Float frame);
void    njCardinalSpline(Float* idata, Float* odata, NJS_SPLINE* attr, Float frame);
void    njOverhauserSpline(Float* idata, Float* odata, NJS_SPLINE* attr, Float frame);
void    njKochanekSpline(Float* idata, Float* odata, NJS_SPLINE* attr, Float frame);
void    njCubicBezierSpline(Float* idata, Float* odata, NJS_SPLINE* attr, Float frame);
void    njBezierSpline(Float* idata, Float* odata, NJS_SPLINE* attr, Float frame);

EXTERN_END

#endif/*H_NJ_MATH*/
