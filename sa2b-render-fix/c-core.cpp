#include <sa2b/core.h>
#include <sa2b/config.h>
#include <sa2b/model.h>

#include <sa2b/src/landtable.h>
#include <sa2b/src/datadll.h>

#define SECT "c_core"

#define ReplaceLandObject(pland, idx, pobj) ((OBJ_LANDTABLE*)pland)->pLandEntry[idx].pObject.gjs = pobj

static void
PitFallRougeRestore()
{
    OBJ_LANDTABLE* land = GetDataDllAddr(OBJ_LANDTABLE, "objLandTable0037");
    GJS_OBJECT* object = LoadGinjaObject2(GetModPath(), "model/stg37_land0032.sa2bmdl");

    ReplaceLandObject(land, 32, object);
}

void
CannonsCoreSettings(const config* conf)
{
    if (ConfigGetInt(conf, SECT, "pitfall", 1))
    {
        PitFallRougeRestore();
    }
}
