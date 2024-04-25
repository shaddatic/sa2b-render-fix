/*
*   Sonic Adventure Mod Tools (SA2B) - '/util/c_nullptr.h'
*
*   Description:
*       SAMT utility header defining the 'nullptr' keyword
*   for use in C. It will become part of the C standard in C23
*   & this header will be removed.
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _UTIL_C_NULLPTR_H_
#define _UTIL_C_NULLPTR_H_

#ifndef __cplusplus

/** The 'nullptr' keyword is a null pointer constant, similar to
    the 'NULL' macro, but is also of type 'nullptr_t'.
    This definition doesn't include the 'nullptr_t' type
    parameter as defined in the C23 standard, so usage should be
    restricted to a formal replacement of 'NULL'. **/

#   define nullptr      ((void*)0)

#endif/*__cplusplus*/

#endif/*_UTIL_C_NULLPTR_H_*/
