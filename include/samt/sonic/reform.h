/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/reform.h'
*
*   Description:
*     Reform object functions.
*/
#ifndef H_SA2B_REFORM
#define H_SA2B_REFORM

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Structures                  */
/********************************/
/****** Reform Work *****************************************************************************/
typedef struct reformwk
{
    i8              mode;           /* reform mode                                              */
    i16             vnum;           /* vertex count in vlist                                    */
    f32             inten;          /* reform intensity                                         */
    Angle           freq;           /* reform frequency                                         */
    Angle           phase;          /* reform phase                                             */
    Angle           speed;          /* phase change speed                                       */
    NJS_CNK_OBJECT* baseobj;        /* base object to reference                                 */
    NJS_CNK_OBJECT* workobj;        /* work object to apply shape changes                       */
    NJS_CNK_OBJECT* altobj1;        /* alternate base object for some modes                     */
    NJS_CNK_OBJECT* altobj2;        /* ^^                                                       */
    NJS_VECTOR      vec;            /* vector attribute for some modes                          */
    Angle           ang;            /* angle attrubute, unused                                  */
    NJS_POINT3      pos[11];        /* position attr list for some modes                        */
    NJS_VECTOR      nrm[11];        /* normal attr list for some modes                          */
}
reformwk;

/********************************/
/*  Prototypes                  */
/********************************/
/****** Create/Free *****************************************************************************/
/*
*   Description:
*     Create a new reform work.
*
*   Parameters:
*     - object      : chunk object to reform
*
*   Returns:
*     Reform work; or 'nullptr' on failure.
*/
reformwk* CreateReform( const NJS_CNK_OBJECT* object );
/*
*   Description:
*     Free a reform work.
*
*   Parameters:
*     - rwp         : reform work
*/
void    FreeReform( reformwk* rwp );

/****** Exec Reform *****************************************************************************/
/*
*   Description:
*     Execute shape reform.
*
*   Parameters:
*     - rwp         : reform work
*/
void    ExecReform( reformwk* rwp );

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Pointers           */
/********************************/
/****** Function Pointers ***********************************************************************/
#define CreateReform_p                  FUNC_PTR(reformwk*, __cdecl, (const NJS_CNK_OBJECT*), 0x00447580)

/****** Usercall Pointers ***********************************************************************/
#define FreeReform_p                    ((void*)0x00447910)
#define ExecReform_p                    ((void*)0x004479E0)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_REFORM*/
