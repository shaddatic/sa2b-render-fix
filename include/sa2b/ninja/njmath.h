/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njmath.h'
*
*   Contains Ninja math macros and functions
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _NJMATH_H_
#define _NJMATH_H_

#include <math.h>

enum {
    IP00, IP01, IP02,
    IP10, IP11, IP12,
    IP20, IP21, IP22,
    IP30, IP31, IP32
};

typedef struct {
    int        keys;        /* keyframes between two points which must be interpolated */
    int     *iparam;        /* attribute data (integer) */
    float   *fparam;        /* attribute data (float) */
} NJS_SPLINE;

#define njAbs(n)         ((Float)fabsf   ((Float)(n)))
#define njArcCos(n)      ((Angle)NJM_RAD_ANG(acosf  ((Float)(n)) ))
#define njArcCosec(n)    ((Angle)NJM_RAD_ANG(asinf  (1.0f/(Float)(n)) ))
#define njArcCot(n)      ((Angle)NJM_RAD_ANG(atanf  (1.0f/(Float)(n)) ))
#define njArcSec(n)      ((Angle)NJM_RAD_ANG(acosf  (1.0f/(Float)(n)) ))
#define njArcSin(n)      ((Angle)NJM_RAD_ANG(asinf  ((Float)(n)) ))
#define njArcTan(n)      ((Angle)NJM_RAD_ANG(atanf  ((Float)(n)) ))
#define njArcTan2(y,x)   ((Angle)NJM_RAD_ANG(atan2f ((Float)(y),(Float)(x)) ))

#define njCeil(n)        ((Float)ceilf   ((Float)(n)))
#define njCosech(n)      ((Float)( 1.0f / sinhf((Float)NJM_ANG_RAD(n)) ))
#define njCosh(n)        ((Float)coshf   ((Float)NJM_ANG_RAD(n)))
#define njCoth(n)        ((Float)( 1.0f / tanhf((Float)NJM_ANG_RAD(n)) ))
#define njExp(x)         ((Float)expf((x)))
#define njFloor(n)       ((Float)floorf  ((Float)(n)))
#define njHypot(x,y)     ((Float)sqrtf  ( (x)*(x) + (y)*(y) ))
#define njLog(n)         ((Float)logf    ((Float)(n)))
#define njLog10(n)       ((Float)log10f  ((Float)(n)))
#define njLog2(n)        ((Float)( njLog((n)) / njLog(2.f) ))
#define njPow(n1,n2)     ((Float)powf    ((Float)(n1),(Float)(n2)))
#define njSech(n)        ((Float)( 1.0 / coshf((Float)NJM_ANG_RAD(n)) ))
#define njSinh(n)        ((Float)sinhf   ((Float)NJM_ANG_RAD(n)))
#define njTanh(n)        ((Float)tanhf   ((Float)NJM_ANG_RAD(n)))

Float   njRandom();
void    njRandomSeed(Uint32 n);

Float   njCos       (Angle n);
Float   njCosec     (Angle n);
Float   njCot       (Angle n);
Float   njFraction  (Float n);
Float   njInvertSqrt(Float n);
Float   njRoundOff  (Float n);
Float   njRoundUp   (Float n);
Float   njSec       (Angle n);
Float   njSin       (Angle n);
Float   njSqrt      (Float n);
Float   njTan       (Angle n);

Sint32  njCombination(Sint32 n, Sint32 k);
void    njLinear(Float* idata, Float* odata, NJS_SPLINE* attr, Float frame);
void    njHermiteSpline(Float* idata, Float* odata, NJS_SPLINE* attr, Float frame);
void    njCardinalSpline(Float* idata, Float* odata, NJS_SPLINE* attr, Float frame);
void    njOverhauserSpline(Float* idata, Float* odata, NJS_SPLINE* attr, Float frame);
void    njKochanekSpline(Float* idata, Float* odata, NJS_SPLINE* attr, Float frame);
void    njCubicBezierSpline(Float* idata, Float* odata, NJS_SPLINE* attr, Float frame);
void    njBezierSpline(Float* idata, Float* odata, NJS_SPLINE* attr, Float frame);

#endif
