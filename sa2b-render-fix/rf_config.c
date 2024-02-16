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
RF_ConfigInit()
{
    ConfigPointer = ConfigOpen2(GetModPath(), "config.ini");
}

void
RF_ConfigEnd()
{
    if (ConfigSet)
        ConfigSave(ConfigPointer);

    ConfigClose(ConfigPointer);

    ConfigPointer = NULL;
}

#pragma region config_get

int
RF_ConfigGetInt(const utf8* section, const utf8* key, int def)
{
    if (!ConfigPointer)
        RF_DebugFuncError("Config read after free");

    return ConfigGetInt(ConfigPointer, section, key, def);
}

bool
RF_ConfigGetBool(const utf8* section, const utf8* key, bool def)
{
    if (!ConfigPointer)
        RF_DebugFuncError("Config read after free");

    return ConfigGetBool(ConfigPointer, section, key, def);
}

const utf8*
RF_ConfigGetString(const utf8* section, const utf8* key, const utf8* def)
{
    if (!ConfigPointer)
        RF_DebugFuncError("Config read after free");

    return ConfigGetString(ConfigPointer, section, key, def);
}

#pragma endregion
#pragma region config_get

void
RF_ConfigSetInt(const utf8* section, const utf8* key, int set)
{
    ConfigSet = true;

    if (!ConfigPointer)
        RF_DebugFuncError("Config set after free");

    ConfigSetInt(ConfigPointer, section, key, set);
}

void
RF_ConfigSetBool(const utf8* section, const utf8* key, bool set)
{
    ConfigSet = true;

    if (!ConfigPointer)
        RF_DebugFuncError("Config set after free");

    ConfigSetInt(ConfigPointer, section, key, set);
}

void
RF_ConfigSetString(const utf8* section, const utf8* key, const utf8* set)
{
    ConfigSet = true;

    if (!ConfigPointer)
        RF_DebugFuncError("Config set after free");

    ConfigSetString(ConfigPointer, section, key, set);
}

#pragma endregion
