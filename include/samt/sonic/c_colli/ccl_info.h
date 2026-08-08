/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/c_colli/ccl_info.h'
*
*   Description:
*     Core collision info.
*/
#ifndef H_SA2B_CCOLLI_INFO
#define H_SA2B_CCOLLI_INFO

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Structures                  */
/********************************/
/****** Colli Info ******************************************************************************/
typedef struct
{
    i8              kind;           /* collision kind                                           */
    u8              form;           /* collision form/shape                                     */
    i8              push;           /* push flags                                               */
    i8              damage;         /* damage flags                                             */
    u32             attr;           /* collision flags                                          */
    NJS_POINT3      center;         /* collision center                                         */
    f32             a;              /* size x                                                   */
    f32             b;              /* size y                                                   */
    f32             c;              /* size z                                                   */
    f32             d;              /* size w                                                   */
    i32             angx;           /* angle x                                                  */
    i32             angy;           /* angle y                                                  */
    i32             angz;           /* angle z                                                  */
}
CCL_INFO;

EXTERN_END

#endif/*H_SA2B_CCOLLI_INFO*/
