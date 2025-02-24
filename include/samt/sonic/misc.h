/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/misc.h'
*
*   Description:
*     Miscellaneous game functions and utilities.
*/
#ifndef H_SA2B_MISC
#define H_SA2B_MISC

/************************/
/*  External Includes   */
/************************/
/****** Ninja ***********************************************************************/
#include <samt/ninja/njcommon.h> /* ninja common                                    */

EXTERN_START

/************************/
/*  Prototypes          */
/************************/
/****** Angle ***********************************************************************/
/*
*   Description:
*     Rotate a ninja angle a set distance toward a target angle. If the target is
*   closer than the set distance, the target angle is directly returned.
*
*   Examples:
*     - AdjustAngle(0x100, 0x200, 0x50) // returns '0x150'
*
*   Parameters:
*     - ang0        : base ninja angle
*     - ang1        : target ninja angle
*     - dang        : distance to rotate
*
*   Returns:
*     'ang0' rotated by 'dang' toward 'ang1'; or 'ang1'.
*/    
Angle   AdjustAngle( Angle ang0, Angle ang1, Angle dang );
/*
*   Description:
*     Get the absolute difference between two ninja angles
*
*   Parameters:
*     - ang0        : ninja angle 1
*     - ang1        : ninja angle 2
*
*   Returns:
*     The absolute difference between angle 1 and 2.
*/
Angle   DiffAngle( Angle ang0, Angle ang1 );

EXTERN_END

#endif/*H_SA2B_MISC*/
