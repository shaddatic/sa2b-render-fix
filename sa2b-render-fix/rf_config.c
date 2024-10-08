#include <sa2b/core.h>
#include <sa2b/config.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_usermsg.h>

/** Self **/
#include <rf_config.h>

static bool ConfigSet;

static config* ConfigPointer;

void
RF_ConfigInit(void)
{
    ConfigPointer = ConfigOpen2(GetModPath(), "config.ini");
}

void
RF_ConfigEnd(void)
{
    if (ConfigSet)
        ConfigSave(ConfigPointer);

    ConfigClose(ConfigPointer);

    ConfigPointer = NULL;
}

#pragma region config_get

int32_t
RF_ConfigGetInt(const RFS_CNF_INT* pCnf)
{
    return RF_ConfigDirectGetInt(pCnf->sect, pCnf->key, pCnf->def);
}

bool
RF_ConfigGetBool(const RFS_CNF_BOOL* pCnf)
{
    return RF_ConfigDirectGetBool(pCnf->sect, pCnf->key, pCnf->def);
}

f64
RF_ConfigGetFloat(const RFS_CNF_FLOAT* pCnf)
{
    return RF_ConfigDirectGetFloat(pCnf->sect, pCnf->key, pCnf->def);
}

const utf8*
RF_ConfigGetString(const RFS_CNF_STRING* pCnf)
{
    return RF_ConfigDirectGetString(pCnf->sect, pCnf->key, pCnf->def);
}

#pragma endregion

#pragma region config_set

void
RF_ConfigSetInt(const RFS_CNF_INT* pCnf, int set)
{
    RF_ConfigDirectSetInt(pCnf->sect, pCnf->key, set);
}

void
RF_ConfigSetBool(const RFS_CNF_BOOL* pCnf, bool set)
{
    RF_ConfigDirectSetBool(pCnf->sect, pCnf->key, set);
}

void
RF_ConfigSetFloat(const RFS_CNF_FLOAT* pCnf, f64 set)
{
    RF_ConfigDirectSetFloat(pCnf->sect, pCnf->key, set);
}

void
RF_ConfigSetString(const RFS_CNF_STRING* pCnf, const utf8* set)
{
    RF_ConfigDirectSetString(pCnf->sect, pCnf->key, set);
}

#pragma endregion

#pragma region config_get_direct

int32_t
RF_ConfigDirectGetInt(const utf8* section, const utf8* key, int def)
{
    if (!ConfigPointer)
        RF_DebugFuncError("Config read after free");

    return ConfigGetInt(ConfigPointer, section, key, def);
}

bool
RF_ConfigDirectGetBool(const utf8* section, const utf8* key, bool def)
{
    if (!ConfigPointer)
        RF_DebugFuncError("Config read after free");

    return ConfigGetBool(ConfigPointer, section, key, def);
}

f64
RF_ConfigDirectGetFloat(const utf8* section, const utf8* key, f64 def)
{
    if (!ConfigPointer)
        RF_DebugFuncError("Config read after free");

    return ConfigGetFloat(ConfigPointer, section, key, def);
}

const utf8*
RF_ConfigDirectGetString(const utf8* section, const utf8* key, const utf8* def)
{
    if (!ConfigPointer)
        RF_DebugFuncError("Config read after free");

    return ConfigGetString(ConfigPointer, section, key, def);
}

#pragma endregion
#pragma region config_get_direct

void
RF_ConfigDirectSetInt(const utf8* section, const utf8* key, int set)
{
    ConfigSet = true;

    if (!ConfigPointer)
        RF_DebugFuncError("Config set after free");

    ConfigSetInt(ConfigPointer, section, key, set);
}

void
RF_ConfigDirectSetBool(const utf8* section, const utf8* key, bool set)
{
    ConfigSet = true;

    if (!ConfigPointer)
        RF_DebugFuncError("Config set after free");

    ConfigSetBool(ConfigPointer, section, key, set);
}

void
RF_ConfigDirectSetFloat(const utf8* section, const utf8* key, f64 set)
{
    ConfigSet = true;

    if (!ConfigPointer)
        RF_DebugFuncError("Config set after free");

    ConfigSetFloat(ConfigPointer, section, key, set);
}

void
RF_ConfigDirectSetString(const utf8* section, const utf8* key, const utf8* set)
{
    ConfigSet = true;

    if (!ConfigPointer)
        RF_DebugFuncError("Config set after free");

    ConfigSetString(ConfigPointer, section, key, set);
}

#pragma endregion
