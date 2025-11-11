/*
*   SA2 Render Fix - '/rf_system/rfsys_internal.h'
*
*   Description:
*     Internal header for Render Fix System module.
*/
#ifndef H_RF_SYSTEM_INTERNAL
#define H_RF_SYSTEM_INTERNAL

/********************************/
/*  Prototypes                  */
/********************************/
/****** Core ************************************************************************************/
#include <rf_system.h>

EXTERN_START

/********************************/
/*  Prototypes                  */
/********************************/
/****** Init ************************************************************************************/
/*
*   Description:
*     Init vsync/frameskip system.
*/
void    RF_SysVsyncInit( void );

EXTERN_END

#endif/*H_RF_SYSTEM_INTERNAL*/
