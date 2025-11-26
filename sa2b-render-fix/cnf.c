/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/config.h>            /* config                                                   */

/****** Self ************************************************************************************/
#include <cnf.h>                    /* self                                                     */

/********************************/
/*  Data                        */
/********************************/
/****** Config Pointer **************************************************************************/
static mt_config* ConfigP;          /* config pointer                                           */

/********************************/
/*  Source                      */
/********************************/
/****** Get *************************************************************************************/
s32
CNF_GetInt(const CONFIG_INT* pCnf)
{
    return CNF_DirectGetInt(pCnf->sect, pCnf->key, pCnf->def);
}

f64
CNF_GetFloat(const CONFIG_FLOAT* pCnf)
{
    return CNF_DirectGetFloat(pCnf->sect, pCnf->key, (f64)pCnf->def);
}

bool
CNF_GetBool(const CONFIG_BOOL* pCnf)
{
    return CNF_DirectGetBool(pCnf->sect, pCnf->key, pCnf->def);
}

const c8*
CNF_GetString(const CONFIG_STRING* pCnf)
{
    return CNF_DirectGetString(pCnf->sect, pCnf->key, pCnf->def);
}

/****** Set *************************************************************************************/
void
CNF_SetInt(const CONFIG_INT* pCnf, s32 val)
{
    CNF_DirectSetInt(pCnf->sect, pCnf->key, val);
}

void
CNF_SetFloat(const CONFIG_FLOAT* pCnf, f64 val)
{
    CNF_DirectSetFloat(pCnf->sect, pCnf->key, val);
}

void
CNF_SetBool(const CONFIG_BOOL* pCnf, bool val)
{
    CNF_DirectSetBool(pCnf->sect, pCnf->key, val);
}

void
CNF_SetString(const CONFIG_STRING* pCnf, const c8* val)
{
    CNF_DirectSetString(pCnf->sect, pCnf->key, val);
}

/****** Direct Get ******************************************************************************/
s32
CNF_DirectGetInt(const c8* section, const c8* key, s32 def)
{
    return mtConfigGetInt(ConfigP, section, key, def);
}

f64
CNF_DirectGetFloat(const c8* section, const c8* key, f64 def)
{
    return mtConfigGetFloat(ConfigP, section, key, def);
}

bool
CNF_DirectGetBool(const c8* section, const c8* key, bool def)
{
    return mtConfigGetBool(ConfigP, section, key, def);
}

const c8*
CNF_DirectGetString(const c8* section, const c8* key, const c8* def)
{
    return mtConfigGetString(ConfigP, section, key, def);
}

/****** Direct Set ******************************************************************************/
void
CNF_DirectSetInt(const c8* section, const c8* key, s32 val)
{
    mtConfigSetInt(ConfigP, section, key, val);
}

void
CNF_DirectSetFloat(const c8* section, const c8* key, f64 val)
{
    mtConfigSetFloat(ConfigP, section, key, val);
}

void
CNF_DirectSetBool(const c8* section, const c8* key, bool val)
{
    mtConfigSetBool(ConfigP, section, key, val);
}

void
CNF_DirectSetString(const c8* section, const c8* key, const c8* val)
{
    mtConfigSetString(ConfigP, section, key, val);
}

/****** Init/End ********************************************************************************/
void
CNF_Init(void)
{
    ConfigP = mtConfigOpen2( mtGetModPath(), "config.ini" );
}

void
CNF_End(void)
{
    mtConfigFree( ConfigP );
}

void
CNF_Save(void)
{
    mtConfigSave2( ConfigP, mtGetModPath(), "config.ini" );
}
