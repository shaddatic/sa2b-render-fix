/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/os.h'
*
*   Description:
*     Header for interacting with Windows without needing to include 'Windows.h'.
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
u32     mtOSGetTickCount( void );
/*
*   Description:
*     Get CPU tick count as a 'u64'.
*
*   Returns:
*     CPU tick count as a 'u64'.
*/
u64     mtOSGetTickCount64( void );

#endif/*H_SAMT_OS*/
