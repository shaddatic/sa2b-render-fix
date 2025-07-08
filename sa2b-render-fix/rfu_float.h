/*
*   SA2 Render Fix - '/rf_util/rfu_float.h'
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
*     Change a float or double value pointer in an 'fld', 'fcom', 'fadd', 'fsub',
*   and etc instructions.
*
*   Parameters:
*     - addr        : address of float instruction
*     - pflt        : new float or double pointer
*/
bool    RFU_ReplaceFloat( pint pOpcode, f64 val );

EXTERN_END

#endif/*H_RF_UTIL_FLOAT*/
