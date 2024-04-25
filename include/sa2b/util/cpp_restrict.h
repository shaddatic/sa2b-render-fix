/*
*   Sonic Adventure Mod Tools (SA2B) - '/util/cpp_restrict.h'
*
*   Description:
*       Defines the 'restrict' C keyword for use in C++.
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _UTIL_CPP_RESTRICT_H_
#define _UTIL_CPP_RESTRICT_H_

#ifdef  __cplusplus

/****** Restrict ********************************************************************/
/*
*   Restrict is used to inform the compilier that an object is not accessed outside
*   the pointer qualified as 'restrict'; this allows the compilier to take riskier
*   optimizations. Incorrect usage of the keyword can lead to undefined behavior.
*/
#   define restrict     __restrict

#endif/*__cplusplus*/

#endif/*_UTIL_CPP_RESTRICT_H_*/
