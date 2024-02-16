#include <sa2b/core.h>
#include <sa2b/model.h>

/** Game **/
#include <sa2b/src/landtable.h>
#include <sa2b/src/datadll.h>

/** Std **/
#include <stdio.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>

/** Self **/
#include <rfm_ccore.h>

#define ReplaceLandObject(pland, idx, pobj) ((OBJ_LANDTABLE*)pland)->pLandEntry[idx].pObject = (ANY_OBJECT*)pobj

void
RFM_CannonsCoreInit(void)
{
    if (RF_ConfigGetInt(CNF_CC_PITFALL))
    {
        OBJ_LANDTABLE* land = GetDataDllAddr(OBJ_LANDTABLE, "objLandTable0037");

        char buf[260];

        snprintf(buf, sizeof(buf), "%s/model/stg37_land0032.sa2bmdl", GetModPath());

        GJS_OBJECT* object = MDL_GinjaLoadObjectFile(buf);

        ReplaceLandObject(land, 32, object);
    }
}
