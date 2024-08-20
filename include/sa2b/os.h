/*
*   Sonic Adventure Mod Tools (SA2B) - '/os.h'
*
*   Description:
*     Header for interacting with Windows without needing to include 'Windows.h'.
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SAMT_OS
#define H_SAMT_OS

/************************/
/*  Prototypes          */
/************************/
/****** CPU Tick Count **************************************************************/
/*
*   Description:
*     Get CPU tick count as a 'u32'. Will overflow every 49 days.
*
*   Returns:
*     CPU tick count as a 'u32'.
*/
u32     OS_GetTickCount( void );
/*
*   Description:
*     Get CPU tick count as a 'u64'.
*
*   Returns:
*     CPU tick count as a 'u64'.
*/
u64     OS_GetTickCount64( void );

#endif/*H_SAMT_OS*/
