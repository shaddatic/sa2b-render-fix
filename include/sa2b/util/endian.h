/*
*   Sonic Adventure Mod Tools (SA2B) - '/util/endian.h'
*
*   Description:
*     SAMT endian utility header
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_UTIL_ENDIAN
#define H_UTIL_ENDIAN

EXTERN_START

/************************/
/*  Prototypes          */
/************************/
/****** Endianness ******************************************************************/
/*
*   Description:
*     Swap endianness of data at 'pInOut' of size 16, 32, or 64 bits.
*
*   Parameters:
*     - pInOut  : pointer to data to swap endianness of
*/
void    EndianSwap16( void* pInOut );
void    EndianSwap32( void* pInOut );
void    EndianSwap64( void* pInOut );

/************************/
/*  Function Macros     */
/************************/
/****** Endianness ******************************************************************/
/*
*   Description:
*     Swap endianness of data at 'p', size is calculated at compile time
*
*   Parameters:
*     - p       : pointer to data to swap endianness of
*/
#define EndianSwap(p)       if (sizeof(*(p)) == 2) { EndianSwap16((p)); } else \
                            if (sizeof(*(p)) == 4) { EndianSwap32((p)); } else \
                            if (sizeof(*(p)) == 8) { EndianSwap64((p)); }

EXTERN_END

#endif/*H_UTIL_ENDIAN*/
