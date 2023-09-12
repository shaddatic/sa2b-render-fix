#include <sa2b/core.h>
#include <sa2b/user.h>

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/texture.h>
#include <sa2b/src/landtable.h>

#include <tools.h>

static void
GjsMeshTintFix(GJS_MESHSET* pGinjaMesh, int nbMesh)
{
    while (nbMesh--)
    {
        GJS_MESHPARAM* param = pGinjaMesh->params;
        const int nbparam = pGinjaMesh->nbParam;

        for (int i = 0; i < nbparam; ++i)
        {
            if (param->type == GJD_MESH_DIFFUSE)
            {
                param->data = 0xFFFFFFFF;
                break;
            }
            ++param;
        }
        ++pGinjaMesh;
    }
}

void
GjsModelTintFix(GJS_MODEL* pModel)
{
    if (pModel->nbSolid)
        GjsMeshTintFix(pModel->meshsolid, pModel->nbSolid);
    if (pModel->nbTrans)
        GjsMeshTintFix(pModel->meshtrans, pModel->nbTrans);
}

void
GjsObjectTintFix(GJS_OBJECT* pObject)
{
    if (pObject->model)
        GjsModelTintFix(pObject->model);
    if (pObject->child)
        GjsObjectTintFix(pObject->child);
    if (pObject->sibling)
        GjsObjectTintFix(pObject->sibling);
}

void
CnkTintFix(Sint16* pPList)
{
    Sint16* plist = pPList;
    int type;

    while (1)
    {
        while (1)
        {
            while (1)
            {
                while (1)
                {
                    while (1)
                    {
                        while (1)
                        {
                            type = ((uint8*)plist)[0];

                            if (type >= NJD_BITSOFF)
                                break;

                            ++plist;
                        }

                        if (type >= NJD_TINYOFF)
                            break;

                        ++plist;
                    }

                    if (type >= NJD_MATOFF)
                        break;

                    plist += 2;
                }

                if (type >= NJD_VERTOFF)
                    break;

                plist += 2;

                switch (type) {
                case NJD_CM_D:
                    plist[0] = (sint16)0xFFFF;
                    plist[1] = (sint16)0xFFFF;
                case NJD_CM_A:
                case NJD_CM_S:
                    plist += 2;
                    break;
                case NJD_CM_DA:
                case NJD_CM_DS:
                    plist[0] = (sint16)0xFFFF;
                    plist[1] = (sint16)0xFFFF;
                case NJD_CM_AS:
                    plist += 4;
                    break;
                case NJD_CM_DAS:
                    plist[0] = (sint16)0xFFFF;
                    plist[1] = (sint16)0xFFFF;
                    plist += 6;
                    break;
                }
            }

            if (type >= NJD_STRIPOFF)
                break;
        }

        if (type == NJD_ENDOFF)
            break;

        plist += ((uint16*)plist)[1] + 2;
    }
}

void
CnkModelTintFix(NJS_CNK_MODEL* pModel)
{
    if (pModel->plist)
        CnkTintFix(pModel->plist);
}

void
CnkObjectTintFix(NJS_CNK_OBJECT* pObject)
{
    if (pObject->model)
        CnkModelTintFix(pObject->model);
    if (pObject->child)
        CnkObjectTintFix(pObject->child);
    if (pObject->sibling)
        CnkObjectTintFix(pObject->sibling);
}

/*
*   Triangle Strip Winding
*/

void
CnkModelFlipWinding(NJS_CNK_MODEL* pModel)
{
    CnkModelFlipStripWinding(pModel, -1, -1);
}

#define plist (*ppPList)
#define idxTri (*pIdxTri)

static void
FlipTriStrip(Sint16** ppPList, int* pIdxTri)
{
    int nbstrip = plist[2] & 0x3FFF;

    plist += 3;

    while (nbstrip--)
    {
        int len = *plist;

        if (idxTri < 0)
        {
            *plist = -len;
        }
        else if (idxTri-- == 0)
        {
            *plist = -len;
            return;
        }

        ++plist;

        if (len < 0)
            len = -len;

        plist += len * 3;
    }
}

#undef plist
#undef idxTri

void
CnkModelFlipStripWinding(NJS_CNK_MODEL* pModel, int idxStrip, int idxTri)
{
    sint16* plist = pModel->plist;
    int type;

    while (1)
    {
        while (1)
        {
            while (1)
            {
                while (1)
                {
                    while (1)
                    {
                        while (1)
                        {
                            type = ((uint8*)plist)[0];

                            if (type >= NJD_BITSOFF)
                                break;

                            ++plist;
                        }

                        if (type >= NJD_TINYOFF)
                            break;

                        ++plist;
                    }

                    if (type >= NJD_MATOFF)
                        break;

                    plist += 2;
                }

                if (type >= NJD_VERTOFF)
                    break;

                plist += 2;

                switch (type) {
                case NJD_CM_D:
                case NJD_CM_A:
                case NJD_CM_S:
                    plist += 2;
                    break;
                case NJD_CM_DA:
                case NJD_CM_DS:
                case NJD_CM_AS:
                    plist += 4;
                    break;
                case NJD_CM_DAS:
                    plist += 6;
                    break;
                }
            }

            if (type >= NJD_STRIPOFF)
                break;
        }

        if (type == NJD_ENDOFF)
            break;

        if (idxStrip < 0)
        {
            int tmp = -1;
            FlipTriStrip(&plist, &tmp);
        }
        else if (idxStrip-- == 0)
        {
            FlipTriStrip(&plist, &idxTri);
            return;
        }
        else
        {
            plist += ((uint16*)plist)[1] + 2;
        }
    }
}

/*
*   Strip Flags
*/

void
CnkMaterialFlagOn(Sint16* pPList, int idxMat, uint32 flag)
{
    Sint16* plist = pPList;
    int type;

    while (1)
    {
        while (1)
        {
            while (1)
            {
                while (1)
                {
                    while (1)
                    {
                        while (1)
                        {
                            type = ((uint8*)plist)[0];

                            if (type >= NJD_BITSOFF)
                                break;

                            ++plist;
                        }

                        if (type >= NJD_TINYOFF)
                            break;

                        ++plist;
                    }

                    if (type >= NJD_MATOFF)
                        break;

                    plist += 2;
                }

                if (type >= NJD_VERTOFF)
                    break;

                plist += 2;

                switch (type) {
                case NJD_CM_D:
                case NJD_CM_A:
                case NJD_CM_S:
                    plist += 2;
                    break;
                case NJD_CM_DA:
                case NJD_CM_DS:
                case NJD_CM_AS:
                    plist += 4;
                    break;
                case NJD_CM_DAS:
                    plist += 6;
                    break;
                }
            }

            if (type >= NJD_STRIPOFF)
                break;
        }

        if (type == NJD_ENDOFF)
            break;

        if (idxMat == -1)
        {
            ((uint16*)plist)[0] |= flag;
        }
        else if (idxMat-- == 0)
        {
            ((uint16*)plist)[0] |= flag;
            return;
        }

        plist += ((uint16*)plist)[1] + 2;
    }
}

void
CnkModelMaterialFlagOn(NJS_CNK_MODEL* pModel, int idxMat, uint32 flag)
{
    CnkMaterialFlagOn(pModel->plist, idxMat, flag);
}

void
CnkObjectMaterialFlagOn(NJS_CNK_OBJECT* pObject, uint32 flag)
{
    if (pObject->model)
        CnkModelMaterialFlagOn(pObject->model, -1, flag);
    if (pObject->child)
        CnkObjectMaterialFlagOn(pObject->child, flag);
    if (pObject->sibling)
        CnkObjectMaterialFlagOn(pObject->sibling, flag);
}

void
CnkLandTableMaterialFlagOn(OBJ_LANDTABLE* pLand, uint32 flag)
{
    NJS_CNK_MODEL* models[32] = {};

    OBJ_LANDENTRY* plentry = pLand->pLandEntry;

    const sint16 nb = pLand->ssCount;

    for (int i = 0; i < nb; ++i)
    {
        NJS_CNK_OBJECT* object = plentry->pObject.cnk;

        for (int j = 0; j < arylen(models); ++j)
        {
            if (models[j] == NULL)
            {
                models[j] = object->model;
                CnkModelMaterialFlagOn(object->model, -1, NJD_FST_DB);
                goto LOOP;
            }

            if (models[j] == object->model)
                goto LOOP;
        }

        CnkModelMaterialFlagOn(object->model, -1, NJD_FST_DB); // Backup in case 'models' is full

    LOOP:

        ++plentry;
    }
}

void
CnkMaterialFlagOff(Sint16* pPList, int idxMat, uint32 flag)
{
    Sint16* plist = pPList;
    int type;

    while (1)
    {
        while (1)
        {
            while (1)
            {
                while (1)
                {
                    while (1)
                    {
                        while (1)
                        {
                            type = ((uint8*)plist)[0];

                            if (type >= NJD_BITSOFF)
                                break;

                            ++plist;
                        }

                        if (type >= NJD_TINYOFF)
                            break;

                        ++plist;
                    }

                    if (type >= NJD_MATOFF)
                        break;

                    plist += 2;
                }

                if (type >= NJD_VERTOFF)
                    break;

                plist += 2;

                switch (type) {
                case NJD_CM_D:
                case NJD_CM_A:
                case NJD_CM_S:
                    plist += 2;
                    break;
                case NJD_CM_DA:
                case NJD_CM_DS:
                case NJD_CM_AS:
                    plist += 4;
                    break;
                case NJD_CM_DAS:
                    plist += 6;
                    break;
                }
            }

            if (type >= NJD_STRIPOFF)
                break;
        }

        if (type == NJD_ENDOFF)
            break;

        if (idxMat == -1)
        {
            ((uint16*)plist)[0] &= ~flag;
        }
        else if (idxMat-- == 0)
        {
            ((uint16*)plist)[0] &= ~flag;
            return;
        }

        plist += ((uint16*)plist)[1] + 2;
    }
}

void
CnkModelMaterialFlagOff(NJS_CNK_MODEL* pModel, int idxMat, uint32 flag)
{
    CnkMaterialFlagOff(pModel->plist, idxMat, flag);
}

void
CnkObjectMaterialFlagOff(NJS_CNK_OBJECT* pObject, uint32 flag)
{
    if (pObject->model)
        CnkModelMaterialFlagOff(pObject->model, -1, flag);
    if (pObject->child)
        CnkObjectMaterialFlagOff(pObject->child, flag);
    if (pObject->sibling)
        CnkObjectMaterialFlagOff(pObject->sibling, flag);
}

void
CnkLandTableMaterialFlagOff(OBJ_LANDTABLE* pLand, uint32 flag)
{
    NJS_CNK_MODEL* models[32] = {};

    OBJ_LANDENTRY* plentry = pLand->pLandEntry;

    const sint16 nb = pLand->ssCount;

    for (int i = 0; i < nb; ++i)
    {
        NJS_CNK_OBJECT* object = plentry->pObject.cnk;

        for (int j = 0; j < arylen(models); ++j)
        {
            if (models[j] == NULL)
            {
                models[j] = object->model;
                CnkModelMaterialFlagOff(object->model, -1, NJD_FST_DB);
                goto LOOP;
            }

            if (models[j] == object->model)
                goto LOOP;
        }

        CnkModelMaterialFlagOff(object->model, -1, NJD_FST_DB); // Backup in case 'models' is full

    LOOP:

        ++plentry;
    }
}

/*
*   Material Params
*/

void
CnkMaterialDiffuse(Sint16* pPList, int idxMat, int a, int r, int g, int b)
{
    Sint16* plist = pPList;
    int type;

    while (1)
    {
        while (1)
        {
            while (1)
            {
                while (1)
                {
                    while (1)
                    {
                        while (1)
                        {
                            type = ((uint8*)plist)[0];

                            if (type >= NJD_BITSOFF)
                                break;

                            ++plist;
                        }

                        if (type >= NJD_TINYOFF)
                            break;

                        ++plist;
                    }

                    if (type >= NJD_MATOFF)
                        break;

                    plist += 2;
                }

                if (type >= NJD_VERTOFF)
                    break;

                plist += 2;

                switch (type) {
                case NJD_CM_D:
                    if (!idxMat)
                    {
                        SET_COLOR:

                        uint8* col = (uint8*)plist;

                        if (a != -1)
                            col[3] = (uint8)a;
                        if (r != -1)
                            col[2] = (uint8)r;
                        if (g != -1)
                            col[1] = (uint8)g;
                        if (b != -1)
                            col[0] = (uint8)b;

                        return;
                    }

                    --idxMat;

                case NJD_CM_A:
                case NJD_CM_S:
                    plist += 2;
                    break;
                case NJD_CM_DA:
                case NJD_CM_DS:
                    if (!idxMat)
                        goto SET_COLOR;

                    --idxMat;

                case NJD_CM_AS:
                    plist += 4;
                    break;
                case NJD_CM_DAS:
                    if (!idxMat)
                        goto SET_COLOR;

                    --idxMat;

                    plist += 6;
                    break;
                }
            }

            if (type >= NJD_STRIPOFF)
                break;
        }

        if (type == NJD_ENDOFF)
            break;

        plist += ((uint16*)plist)[1] + 2;
    }

    ModNonFatalFuncError("'idxStrip' param is out of range!");
}

void
CnkModelMaterialDiffuse(NJS_CNK_MODEL* pModel, int idxMat, int a, int r, int g, int b)
{
    CnkMaterialDiffuse(pModel->plist, idxMat, a, r, g, b);
}


/*
*   GVM Tables
*/

void
SwapGVMTableIndex(TEX_GVMTABLE* pGvmTable, int idx1, int idx2)
{
	TEX_GVMTABLE tmp = pGvmTable[idx1];
    pGvmTable[idx1] = pGvmTable[idx2];
    pGvmTable[idx2] = tmp;
}

/*
*   Mod Tools
*/

void
__ModNonFatalFuncError(const char* func, const char* body)
{
    char str[128];

    snprintf(str, 128, "RenderFix: %s", func);

    UserWarningMessageBox(str, body);
}

void
ModConflictWarning(const char* body)
{
	UserWarningMessageBox("Render Fix: Mod Conflict", body);
}