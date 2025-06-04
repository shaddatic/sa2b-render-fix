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
*/
u32     mtOSGetTickCount( void );
/*
*   Description:
*     Get CPU tick count as a 'u64'.
*/
u64     mtOSGetTickCount64( void );

/****** Sleep ***********************************************************************/
/*
*   Description:
*     Sleep process for a set time in miliseconds.
*
*   Parameters:
*     - ms          : milliseconds to sleep for
*/
void    mtOSSleep( u32 ms );

/****** Clock ***********************************************************************/
/*
*   Description:
*     High resolution clock for performance critical tasks.
*
*   Returns:
*     Clock value in variable units < 1us.
*/
s64     mtOSHighResolutionClock( void );
/*
*   Description:
*     Get the number of 'clocks' per second for the above function.
*
*   Returns:
*     Clock frequency per second.
*/
s64     mtOSHighResolutionFrequency( void );

/****** Windows CMD *****************************************************************/
/*
*   Description:
*     Send a command string to command prompt.
*
*   Notes:
*     - Generally unsafe to do complex tasks with, keep it simple.
*
*   Parameters:
*     - pcCmd       : command string
*
*   Returns:
*     'true' if the command executed successfully; or 'false' on failure.
*/
bool    mtOSTerminal( const char* pcCmd );

#endif/*H_SAMT_OS*/
