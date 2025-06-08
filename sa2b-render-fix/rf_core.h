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
#include <samt/util/devutil.h>
#include <samt/util/c_constexpr.h>
#include <samt/util/c_nullptr.h>

/** System **/
#include <samt/shinobi/sg_xpt.h>

/** Source **/
#include <samt/sonic/debug.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    ___DebugFuncError(const c8* func, const c8* body);

#ifndef NDEBUG
#   define RF_DebugFuncError(body) ___DebugFuncError(__func__, body)
#else
#   define RF_DebugFuncError(body) ;
#endif

EXTERN_END

#endif/*_RF_CORE_H_*/
