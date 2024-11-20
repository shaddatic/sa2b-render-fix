/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/file_ctl.h'
*
*   Description:
*     File control header; handles regular files and sub-program files (PRS/REL).
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SA2B_FILECTL
#define H_SA2B_FILECTL

/************************/
/*  Opaque Types        */
/************************/
/****** Task ************************************************************************/
typedef struct task             task; /* task                                       */

EXTERN_START

/************************/
/*  Enums               */
/************************/
/****** Sub-Program Return **********************************************************/
enum
{
    SUBPRG_RET_RESTART = -3,    /* restart action stage, else same as 'CONTINUE'    */
    SUBPRG_RET_TITLE,           /* return to title screen                           */
    SUBPRG_RET_EXIT,            /* stop execution                                   */
    SUBPRG_RET_CONTINUE,        /* continue execution                               */
    SUBPRG_RET_NEXT,            /* next global mode                                 */
};

/************************/
/*  Structures          */
/************************/
/****** Sub-Program *****************************************************************/
/*
*     Each sub-program defines an init function 'prolog', exit function 'epilog',
*   and execution function 'manager'. Depending on the sub-program type, the manager
*   function will take different responsibilities.
*     Stages use the 'EXEC' functions. The 'subprgmanager' function is used as the
*   'exec' of a Task created for the stage in LEV_2.
*     Alternatively, other sub-programs, like Advertise and the Cart Races, use the
*   'CTRL' functions. The 'subprgmanager' function is called directly in the main
*   game loop and handles task execution locally. The value returned from
*   'subprgmanager' will determine what action the main game loop will take after
*   calling it, as defined by the return value enum; each value may behave slightly
*   differently depending on the subprogram and its individual quirks.
*/
typedef struct
{
    void(__cdecl* subprgprolog)(void);   /* sub-program init function               */
    void(__cdecl* subprgepilog)(void);   /* sub-program exit function               */
    void(__cdecl* subprgmanager)(task*); /* sub-program task exec function          */
}
SUBPRG_EXEC;

typedef struct
{
    void(__cdecl* subprgprolog)(void);  /* sub-program init function                */
    void(__cdecl* subprgepilog)(void);  /* sub-program exit function                */
    s32 (__cdecl* subprgmanager)(void); /* sub-program game control function        */
}
SUBPRG_CTRL;

typedef struct
{
    char subprgname[8];     /* sub-program name, padded with spaces                 */
    s32  subprgtype;        /* sub-program type: '0' uses 'exec'; '> 0' uses 'ctrl' */
    union {
        SUBPRG_EXEC exec;   /* task exec type                                       */
        SUBPRG_CTRL ctrl;   /* game control type, handles task exec and draw        */
    };
}
SUBPRG_HEADER;

/************************/
/*  Game References     */
/************************/
/****** Sub-Program File Offset *****************************************************/
#define pfo                 DATA_REF(SUBPRG_HEADER*, 0x019420FC)

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
