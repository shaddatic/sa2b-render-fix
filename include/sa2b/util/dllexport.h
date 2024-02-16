/*
*   Sonic Adventure Mod Tools (SA2B) - '/util/dllexport.h'
*
*   Description:
*       SAMT utility header containing a DLL export macro.
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _UTIL_DLLEXPORT_H_
#define _UTIL_DLLEXPORT_H_

/************************/
/*  Macros              */
/************************/
#define EXPORT_DLL          EXTERN __declspec(dllexport)

#endif/*_UTIL_DLLEXPORT_H_*/
