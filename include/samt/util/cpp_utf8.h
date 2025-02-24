/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/util/cpp_utf8.h'
*
*   Description:
*       SAMT utility header defining a macro for converting
*   char8_t unicode strings to regular char/utf8 strings. C++
*   does not allow implicit conversion of 'u8' prefixed strings
*   to any other character type. C++23 will improve the
*   situation, but not fully.
*/
#ifndef _UTIL_CPP_UTF8_H_
#define _UTIL_CPP_UTF8_H_

#ifdef  __cplusplus

/** char8_t (UTF-8) to char/utf8 macro ( eg. u8("Unicode string") ) **/

#   define u8(_str)     (char*)u8##_str

#endif/*__cplusplus*/

#endif/*_UTIL_CPP_UTF8_H_*/
