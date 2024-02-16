/*
*   SA2 Render Fix - '/rf_core.h'
*
*   Description:
*       Contains project wide resources. Should always be
    included & should be first before other Render Fix headers.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_CORE_H_
#define _RF_CORE_H_

/************************/
/*  Includes            */
/************************/
/** Utility **/
#include <sa2b/util/devutil.h>
#include <sa2b/util/c_constexpr.h>

/** Source **/
#include <sa2b/src/debug.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    ___DebugFuncError(const utf8* func, const utf8* body);

#ifndef NDEBUG
#   define RF_DebugFuncError(body) ___DebugFuncError(__func__, body)
#else
#   define RF_DebugFuncError(body) ;
#endif

EXTERN_END

#endif/*_RF_CORE_H_*/
