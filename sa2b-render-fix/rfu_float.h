/*
*   SA2 Render Fix - '/rfu_float.h'
*
*   Description:
*     Floating point utility functions.
*/
#ifndef H_RF_UTIL_FLOAT
#define H_RF_UTIL_FLOAT

EXTERN_START

/********************************/
/*  Prototypes                  */
/********************************/
/****** Replace Float ***************************************************************************/
/*
*   Description:
*     Change a float/double value in an 'fld', 'fcom', 'fadd', 'fsub', or etc operation.
*
*   Notes:
*     - Values are set into a constant buffer, and their buffer slot is used as the read pointer
*       in the operation.
*     - There are a limited number of float slots in the buffer, but duplicate floats reuse the
*       same slot.
*
*   Parameters:
*     - pOpcode     : address to floating point operation
*     - val         : new float or double value
*
*   Returns:
*     'true' on success; or 'false' if the opcode is unsupported or if the float list is full.
*/
bool    RFU_ReplaceFloat( pint pOpcode, f64 val );

/****** Direct Replace **************************************************************************/
/*
*   Description:
*     Directly replace a float value using a pointer, without any additional logic.
*
*   Notes:
*     - Floats/doubles used as replacements here must be static and last as long as the program
*       does. Stack allocated floats are undefined behavior.
*
*   Parameters:
*     - pOpcode     : address to floating point operation
*     - pFlt        : pointer to replacement float value
*/
void    RFU_DirectReplaceFloat( pint pOpcode, const void* pFlt );

EXTERN_END

#endif/*H_RF_UTIL_FLOAT*/
