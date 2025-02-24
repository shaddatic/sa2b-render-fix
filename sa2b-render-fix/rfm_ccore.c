#include <samt/core.h>
#include <samt/model.h>
#include <samt/samdl.h>

/** Game **/
#include <samt/sonic/landtable.h>
#include <samt/sonic/datadll.h>

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

        snprintf(buf, sizeof(buf), "%s/model/stg37_land0032.sa2bmdl", mtGetModPath());

        GJS_OBJECT* object = mtSAModelLoad(buf, SAMDL_GINJA)->pGinja;

        ReplaceLandObject(land, 32, object);
    }

    if (RF_ConfigGetInt(CNF_CC_KURUMA))
    {
        NJS_CNK_OBJECT* object_kuruma = GetDataDllAddr(NJS_CNK_OBJECT, "object_lsonic_un4_kuruma_BK040506__un4_kuruma_BK040506_");

        object_kuruma = object_kuruma->child;

        object_kuruma->pos[0] = -450.0f;
        object_kuruma->pos[1] = -365.0f;
        object_kuruma->pos[2] = -2325.0f;

        object_kuruma = object_kuruma->sibling;

        object_kuruma->pos[0] = -510.0f;
        object_kuruma->pos[1] = -365.0f;
        object_kuruma->pos[2] = -2325.0f;

        object_kuruma = object_kuruma->sibling;

        object_kuruma->pos[0] = -570.0f;
        object_kuruma->pos[1] = -365.0f;
        object_kuruma->pos[2] = -2325.0f;
    }
}
