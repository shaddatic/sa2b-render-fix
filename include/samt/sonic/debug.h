/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/debug.h'
*
*   Description:
*     Debug features.
*/
#ifndef H_SA2B_DEBUG
#define H_SA2B_DEBUG

EXTERN_START

/********************************/
/*  Game Defs                   */
/********************************/
/****** Overscan ********************************************************************************/
#define ShowOverscanGrid            DATA_REF(b32, 0x0174BA6C)

/********************************/
/*  Prototypes                  */
/********************************/
/****** Output Format ***************************************************************************/
/*
*   Description:
*     Output a formatted string for the debug console or OSD.
*
*   Parameters:
*     - str         : format string
*     - ...         : format arguments
*
*   Returns:
*     Number of characters printed to the buffer; or a negative value of failure.
*/
isize   ___OutputDebugString( const c7* str, ... );

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Ptrs               */
/********************************/
/****** Standard ********************************************************************************/
#define ___OutputDebugString_p      FUNC_PTR(i32, __cdecl, (const c7*, ...), 0x00426740)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_DEBUG*/
