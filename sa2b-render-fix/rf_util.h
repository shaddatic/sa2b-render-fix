/*
*   SA2 Render Fix - '/rf_util.h'
*
*   Description:
*     Common Render Fix utilities.
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_UTIL
#define H_RF_UTIL

/************************/
/*  External Includes   */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/writemem.h>      /* write protected memory                           */
#include <sa2b/writeop.h>       /* write operator                                   */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/njcommon.h> /* ninja common                                    */
#include <sa2b/ninja/njmatrix.h> /* ninja matrix                                    */

/************************/
/*  External Opaques    */
/************************/
/****** Texture Table ***************************************************************/
typedef struct prstable         TEX_PRSTABLE;

EXTERN_START

/************************/
/*  Functions           */
/************************/
/****** File Ownership **************************************************************/
/*
*   Description:
*     Swap two PRS table entries with each other, to fix issues with texture load
*   order.
*
*   Parameters:
*     - pPrsTable   : prs table to edit
*     - idx1        : entry index to swap 1
*     - idx2        : entry index to swap 2
*/
void    RF_SwapTexFileTableIndex( TEX_PRSTABLE* pTexTable, int idx1, int idx2 );

/****** Interpolation ***************************************************************/
/*
*   Description:
*     Interpolate 2 points with each other with a weight ratio
*
*   Parameters:
*     - pOutPt   : return pointer for new interpolated point
*     - pPt1     : pointer to point 1
*     - pPt2     : pointer to point 2
*     - ratioPt1 : weight ratio of point 1, point 2 will use a weight of ( 1.f - 'ratioPt1' )
*/
void    RFU_LerpPoints( NJS_POINT3* pOutPt, const NJS_POINT3* pPt1, const NJS_POINT3* pPt2, f32 ratioPt1 );

/****** Screen **********************************************************************/
/*
*   Description:
*     Calculate a 3D point in screenspace to a 2D point in screenspace. A 3D
*   screenspace point is calculated by using 'njCalcPoint' on a 3D worldspace point
*
*   Parameters:
*     - pInPos   : pointer to screenspace 3D point
*     - pOutPos  : return pointer for screenspace 2D point
*/
void    RFU_CalculateScreen( const NJS_POINT3* pInPos, NJS_POINT2* pOutPos );
/*
*   Description:
*     Project a 3D point in worldspace to a 2D point in screenspace. This is the same
*   as:
*     njCalcPoint(NULL, &pt3);
*     RFU_CalculateScreen(&pt3, &pt2);
*
*   Parameters:
*     - pInPos   : pointer to worldspace 3D point
*     - pOutPos  : return pointer for screenspace 2D point
*/
void    RFU_ProjectScreen( const NJS_POINT3* pInPos, NJS_POINT2* pOutPos );

/****** Matrix **********************************************************************/
/*
*   Description:
*     Calculate if a matrix has inverted scaling
*
*   Parameters:
*     - m       : matrix to calcluate, or '_nj_curr_matrix_' if 'NULL'
*/
bool    RFU_CalcInvertedMatrix( const NJS_MATRIX* m );

EXTERN_END

/************************/
/*  Macro               */
/************************/
/*
*   Display Order Fixes
*/
#define DISP        0x14
#define DISP_DELY   0x1C
#define DISP_SORT   0x20
#define DISP_LATE   0x24
#define DISP_LAST   0x28
#define DISP_SHAD   0x2C

/** Switch a displayer to a different level,
    use this on 'mov dword ptr' operations **/
#define SwitchDisplayer(addr, disp)                     WriteData(addr + 2, disp, uint8_t)

/*
*   Hook 'mov dword ptr'
*/
/** Replace a 'mov dword ptr' with a call to a function **/
#define WriteCallToMovDwordPtr(addr, func)              WriteNOP((addr), (addr) + 7); WriteCall((addr), (func))

/*
*   Replace float pointer
*/
/** Replace float used in many 'real' instruction **/
#define ReplaceFloat(addr, pflt)                        WritePointer(addr + 2, pflt)

/*
*   Func Macros
*/
#define SwapTexFileTableIndex(_textable, _idx1, _idx2)  RF_SwapTexFileTableIndex((TEX_PRSTABLE*)(_textable), (_idx1), (_idx2))

EXTERN_END

#endif/*H_RF_UTIL*/
