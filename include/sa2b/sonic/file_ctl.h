/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/file_ctl.h'
*
*   Description:
*       Contains data and functions related to core game elements.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SA2B_FILECTL
#define H_SA2B_FILECTL

EXTERN_START

/************************/
/*  Functions           */
/************************/
/****** Free ************************************************************************/
/*
*   Description:
*     Free a file buffer. Just calls 'syFree()'
*/
void    FreeFile( void* file );

EXTERN_END

#endif/*H_SA2B_FILECTL*/
