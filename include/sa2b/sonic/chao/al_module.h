/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_module.h'
*
*   Description:
*       Contains enums, structs, data, and functions related to Chao World modules.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_MODULE_H_
#define _SA2B_CHAO_MODULE_H_

/************************/
/*  Enums               */
/************************/
typedef enum
{
    CHAO_MODULE_HEAD,
    CHAO_MODULE_STAGE,
    CHAO_MODULE_LAND,
    CHAO_MODULE_ETC,
    MAX_CHAO_MODULE
}
EChaoModuleEntry;

/************************/
/*  Structures          */
/************************/
typedef struct
{
    const char*   al_subprgname;
    void(__cdecl* al_subprgprolog)(void);
    void(__cdecl* al_subprgepilog)(void);
#if 0 /* SA2DC only, maybe */
    void(__cdecl* al_subprgmanager)(task*);
#endif
}
AL_SUBPRG_HEADER;

/************************/
/*  Data                */
/************************/
#define ChaoModules     DATA_ARY(AL_SUBPRG_HEADER, 0x01366580, [48])

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    AL_LoadModule(const char* name, EChaoModuleEntry kind);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#define AL_LoadModule_p     FUNC_PTR(void, __cdecl, (const char*, EChaoModuleEntry), 0x00530C20)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_MODULE_H_*/
