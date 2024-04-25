/*
*   Sonic Adventure Mod Tools (SA2B) - '/util/c_constexpr.h'
*
*   Description:
*       SAMT utility header defining the 'constexpr' keyword
*   for use in C. It will become part of the C standard in C23
*   & this header will be removed.
*       It's important to note that it will not be compatible
*   with functions, only variables, unlike C++.
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _UTIL_C_CONSTEXPR_H_
#define _UTIL_C_CONSTEXPR_H_

#ifndef __cplusplus

/** The 'constexpr' keyword allows for computing a variable at
    compile-time; similar to #define, but with additional type
    information. This macro doesn't mimick that behavior, but
    is useful for designing code now that's ready for C23 **/

#   define constexpr   const

#endif/*__cplusplus*/

#endif/*_UTIL_C_CONSTEXPR_H_*/
