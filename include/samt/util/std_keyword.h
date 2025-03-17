/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/util/std_keyword.h'
*
*   Description:
*     Standard C/C++ keyword definitions.
*/
#ifndef H_SAMT_UTIL_STDKEYWORD
#define H_SAMT_UTIL_STDKEYWORD

/************************/
/*  Macros              */
/************************/
/****** C ***************************************************************************/
#ifndef __cplusplus

#define EXTERN          extern      /* extern                                       */
#define STATIC          static      /* static                                       */
#define RESTRICT        restrict    /* restrict                                     */
#define CONST           const       /* const                                        */
#define CONSTEXPR       const       /* constexpr                                    */

/****** C++ *************************************************************************/
#else/*__cplusplus*/

#define EXTERN          extern "C"  /* extern                                       */
#define STATIC          static      /* static                                       */
#define RESTRICT        __restrict  /* restrict                                     */
#define CONST           const       /* const                                        */
#define CONSTEXPR       constexpr   /* constexpr                                    */

#endif/*__cplusplus*/

#endif/*H_SAMT_UTIL_STDKEYWORD*/
