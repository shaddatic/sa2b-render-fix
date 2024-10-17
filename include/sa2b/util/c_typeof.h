/*
*   Sonic Adventure Mod Tools (SA2B) - '/util/c_typeof.h'
*
*   Description:
*     SAMT utility header defining the 'typeof' operator. It will become part of the
*   C standard in C23, & this header will be removed.
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_UTIL_C_TYPEOF
#define H_UTIL_C_TYPEOF

#ifndef __cplusplus

#if (__STDC_VERSION__ < 202311L) /* ver < C23 */

/************************/
/*  Definitions         */
/************************/
/****** Typeof Operator *************************************************************/
/*
*   Description:
*     The 'typeof' operator is used to get the type of an expresion; this can be a
*   variable, function, or any other valid C expression. The 'typeof' expression
*   will be replaced at compile time with the returned type, including additional
*   qualifiers such as 'static', 'const', etc.
*
*   Examples:
*     - typeof(float) f;        // f is a 'float'
*     - static const int i;
*       typeof(i) j;            // j is a 'static const int'
*/
#   define typeof               __typeof__
/*
*   Description:
*     The 'typeof_unqual' operator is used to get the type of an expression,
*   excluding additional qualifiers such as 'static', 'const', etc; this can be a
*   variable, function, or any other valid C expression. The 'typeof' expression
*   will be replaced at compile time with the returned type.
*
*   Note:
*     - 'unqual' is short for 'unqualified'
*
*   Examples:
*     - typeof_unqual(float) f; // f is a 'float'
*     - static const int i;
*       typeof_unqual(i) j;     // j is an 'int'
*/
#   define typeof_unqual        __typeof_unqual__

#endif/*(__STDC_VERSION__ < 202311L)*/

#endif/*__cplusplus*/

#endif/*H_UTIL_C_TYPEOF*/
