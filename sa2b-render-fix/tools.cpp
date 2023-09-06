#include <sa2b/core.h>
#include <sa2b/user.h>

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/texture.h>
#include <sa2b/src/landtable.h>

#include <tools.h>

void
FlipCnkModelWinding(NJS_CNK_MODEL* pModel)
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

        int nbstrip = plist[2] & 0x3FFF;

        plist += 3;

        while (nbstrip--)
        {
            int len = *plist;

            *plist = -len;

            ++plist;

            if (len < 0)
                len = -len;

            plist += len * 3;
        }
    }
}

void
FlipCnkModelStripWinding(NJS_CNK_MODEL* pModel, int idxStrip, int idxTri)
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

        if (idxStrip-- == 0)
        {
            int nbstrip = plist[2] & 0x3FFF;

            plist += 3;

            while (nbstrip--)
            {
                int len = *plist;

                if (idxTri-- == 0)
                {
                    *plist = -len;
                    return;
                }

                ++plist;

                if (len < 0)
                    len = -len;

                plist += len * 3;
            }

            ModNonFatalFuncError("'idxTri' param is out of range!");
            return;
        }

        plist += ((uint16*)plist)[1] + 2;
    }

    ModNonFatalFuncError("'idxStrip' param is out of range!");
}

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

void
SwapGVMTableIndex(TEX_GVMTABLE* pGvmTable, int idx1, int idx2)
{
	TEX_GVMTABLE tmp = pGvmTable[idx1];
    pGvmTable[idx1] = pGvmTable[idx2];
    pGvmTable[idx2] = tmp;
}

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